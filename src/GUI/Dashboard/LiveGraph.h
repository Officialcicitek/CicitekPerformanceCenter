#pragma once

#include <QWidget>
#include <QVector>
#include <QString>

class LiveGraph : public QWidget
{
public:
    explicit LiveGraph(
        const QString& lineColor,
        QWidget* parent = nullptr
    );

    void addValue(double value);

    void setRange(
        double minimum,
        double maximum
    );

    void setLineColor(
        const QString& color
    );

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QVector<double> m_values;
    QString m_lineColor;

    double m_minimum;
    double m_maximum;

    static constexpr int MaxSamples = 60;
};