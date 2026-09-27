#include "SettingsManager.h"

SettingsManager::SettingsManager()
    : m_settings(
        QSettings::IniFormat,
        QSettings::UserScope,
        "CicitekInteractive",
        "CicitekPerformanceCenter"
    )
{
}

QVariant SettingsManager::value(
    const QString& key,
    const QVariant& defaultValue
) const
{
    return m_settings.value(key, defaultValue);
}

void SettingsManager::setValue(
    const QString& key,
    const QVariant& value
)
{
    m_settings.setValue(key, value);
    m_settings.sync();
}

void SettingsManager::remove(
    const QString& key
)
{
    m_settings.remove(key);
    m_settings.sync();
}

void SettingsManager::reset()
{
    m_settings.clear();
    m_settings.sync();
}