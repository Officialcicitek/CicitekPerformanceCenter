#include "LiveGraph.h"

#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPen>


LiveGraph::LiveGraph(
    const QString& lineColor,
    QWidget* parent
)
    : QWidget(parent),
      m_lineColor(lineColor),
      m_minimum(0.0),
      m_maximum(100.0),
      m_darkMode(true)
{
    setMinimumHeight(55);
    setMaximumHeight(65);

    setAttribute(
        Qt::WA_OpaquePaintEvent,
        false
    );
}


void LiveGraph::setRange(
    double minimum,
    double maximum
)
{
    m_minimum = minimum;
    m_maximum = maximum;

    if (m_maximum <= m_minimum)
    {
        m_minimum = 0.0;
        m_maximum = 100.0;
    }

    update();
}


void LiveGraph::setLineColor(
    const QString& color
)
{
    m_lineColor = color;

    update();
}


void LiveGraph::setDarkMode(
    bool darkMode
)
{
    m_darkMode = darkMode;

    update();
}


void LiveGraph::addValue(
    double value
)
{
    value = qBound(
        m_minimum,
        value,
        m_maximum
    );

    m_values.append(value);

    if (m_values.size() > MaxSamples)
    {
        m_values.removeFirst();
    }

    update();
}


void LiveGraph::paintEvent(
    QPaintEvent* event
)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(
        QPainter::Antialiasing,
        true
    );


    const int width =
        this->width();

    const int height =
        this->height();


    if (width <= 0 || height <= 0)
    {
        return;
    }


    // =========================================================
    // COLORS
    // =========================================================

    const QColor backgroundColor =
        m_darkMode
            ? QColor("#10141c")
            : QColor("#f8f9fb");

    const QColor gridColor =
        m_darkMode
            ? QColor("#1c2330")
            : QColor("#e1e5eb");


    // =========================================================
    // BACKGROUND
    // =========================================================

    painter.fillRect(
        rect(),
        backgroundColor
    );


    // =========================================================
    // GRID
    // =========================================================

    QPen gridPen(
        gridColor
    );

    gridPen.setWidth(
        1
    );

    painter.setPen(
        gridPen
    );


    const int gridLines[] =
    {
        height / 4,
        height / 2,
        (height * 3) / 4
    };


    for (int y : gridLines)
    {
        painter.drawLine(
            0,
            y,
            width,
            y
        );
    }


    // =========================================================
    // NO DATA
    // =========================================================

    if (m_values.isEmpty())
    {
        return;
    }


    // =========================================================
    // GRAPH PATH
    // =========================================================

    QPainterPath path;


    const double xStep =
        m_values.size() > 1
            ? static_cast<double>(width - 2) /
              static_cast<double>(MaxSamples - 1)
            : 0.0;


    const double range =
        m_maximum - m_minimum;


    for (int i = 0; i < m_values.size(); ++i)
    {
        const double value =
            m_values[i];


        const double normalized =
            range > 0.0
                ? (value - m_minimum) / range
                : 0.0;


        const double x =
            1.0 +
            static_cast<double>(i) *
            xStep;


        const double y =
            static_cast<double>(height - 2) -
            normalized *
            static_cast<double>(height - 4);


        if (i == 0)
        {
            path.moveTo(
                x,
                y
            );
        }
        else
        {
            path.lineTo(
                x,
                y
            );
        }
    }


    // =========================================================
    // AREA
    // =========================================================

    QPainterPath areaPath =
        path;


    areaPath.lineTo(
        width,
        height
    );

    areaPath.lineTo(
        0,
        height
    );

    areaPath.closeSubpath();


    QColor areaColor =
        QColor(m_lineColor);

    areaColor.setAlpha(
        m_darkMode ? 25 : 20
    );


    painter.fillPath(
        areaPath,
        areaColor
    );


    // =========================================================
    // LINE
    // =========================================================

    QPen linePen =
        QPen(
            QColor(m_lineColor)
        );


    linePen.setWidthF(
        1.8
    );

    linePen.setCapStyle(
        Qt::RoundCap
    );

    linePen.setJoinStyle(
        Qt::RoundJoin
    );


    painter.setPen(
        linePen
    );

    painter.drawPath(
        path
    );
}