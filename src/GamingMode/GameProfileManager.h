#pragma once

#include <QString>
#include <QHash>

struct GameProfile
{
    QString gameName;
    QString processName;

    bool highCpuPriority = false;
    bool backgroundOptimization = false;
};

class GameProfileManager
{
public:
    GameProfileManager();

    bool hasProfile(
        const QString& processName
    ) const;

    GameProfile getProfile(
        const QString& processName
    ) const;

    void addProfile(
        const GameProfile& profile
    );

private:
    QHash<QString, GameProfile> m_profiles;
};