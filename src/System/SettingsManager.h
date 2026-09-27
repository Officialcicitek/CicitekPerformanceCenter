#pragma once

#include <QSettings>
#include <QVariant>
#include <QString>

class SettingsManager
{
public:
    SettingsManager();

    QVariant value(
        const QString& key,
        const QVariant& defaultValue = QVariant()
    ) const;

    void setValue(
        const QString& key,
        const QVariant& value
    );

    void remove(const QString& key);
    void reset();

private:
    QSettings m_settings;
};