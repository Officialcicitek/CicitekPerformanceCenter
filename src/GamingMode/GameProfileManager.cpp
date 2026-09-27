#include "GameProfileManager.h"

GameProfileManager::GameProfileManager()
{
    addProfile({
        "Roblox",
        "RobloxPlayerBeta.exe",
        true,
        true
    });

    addProfile({
        "Counter-Strike 2",
        "cs2.exe",
        true,
        true
    });

    addProfile({
        "VALORANT",
        "VALORANT-Win64-Shipping.exe",
        true,
        true
    });

    addProfile({
        "Fortnite",
        "FortniteClient-Win64-Shipping.exe",
        true,
        true
    });

    addProfile({
        "League of Legends",
        "LeagueClient.exe",
        true,
        true
    });

    addProfile({
        "Minecraft",
        "Minecraft.exe",
        false,
        true
    });

    addProfile({
        "Minecraft (Java)",
        "javaw.exe",
        false,
        true
    });
}

bool GameProfileManager::hasProfile(
    const QString& processName
) const
{
    return m_profiles.contains(
        processName.toLower()
    );
}

GameProfile GameProfileManager::getProfile(
    const QString& processName
) const
{
    return m_profiles.value(
        processName.toLower()
    );
}

void GameProfileManager::addProfile(
    const GameProfile& profile
)
{
    m_profiles.insert(
        profile.processName.toLower(),
        profile
    );
}