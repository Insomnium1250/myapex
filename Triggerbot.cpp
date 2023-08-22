#pragma once
#include <random>
#include <thread>
#include <chrono>
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "math.h"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"

class Triggerbot
{
private:
    ConfigLoader *m_configLoader;
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;

public:
    Triggerbot(ConfigLoader *configLoader,
           Level *level,
           LocalPlayer *localPlayer,
           std::vector<Player *> *players,
           X11Utils *x11Utils)
        : m_configLoader(configLoader), m_level(level), 
          m_localPlayer(localPlayer), m_players(players), m_x11Utils(x11Utils) {}

    Player* findClosestEnemy() 
    {
        Player *closestPlayerSoFar = nullptr;
        double closestPlayerAngleSoFar;
        for (Player* player : *m_players) 
        {
            if (!player->isValid())
                continue;
            if (player->isKnocked())
                continue;
            if (player->getTeamNumber() == m_localPlayer->getTeamNumber())
                continue;
            if (!player->isVisible())
                continue;

            double desiredViewAngleYaw = calculateDesiredYaw(m_localPlayer->getLocationX(),
                                                             m_localPlayer->getLocationY(),
                                                             player->getLocationX(),
                                                             player->getLocationY());
            double angleDelta = calculateAngleDelta(m_localPlayer->getYaw(), desiredViewAngleYaw);

            if (closestPlayerSoFar == nullptr)
            {
                closestPlayerSoFar = player;
                closestPlayerAngleSoFar = abs(angleDelta);
            }
            else
            {
                if (abs(angleDelta) < closestPlayerAngleSoFar)
                {
                    closestPlayerSoFar = player;
                    closestPlayerAngleSoFar = abs(angleDelta);
                }
            }
        }
        return closestPlayerSoFar;
    }
          

    void update()
    {
        // Check if our trigger is a button
        if (m_configLoader->getTriggerbotTrigger() != 0x0000) 
        {
            // If the triggerbot button is not pressed.
            if (!m_x11Utils->keyDown(m_configLoader->getTriggerbotTrigger())) 
            {
                return;
            }
	    }
        
        if (!m_level->isPlayable())
        {
            return;
        }
        if (m_localPlayer->isDead())
        {   
            return;
        }
        if (m_localPlayer->isKnocked())
        {
            return;
        }

        Player* closestPlayer = findClosestEnemy();

        // Validate player conditions
        if (closestPlayer && closestPlayer->isValid())
        {
            // Calculate desired angles to this player
            double desiredViewAngleYaw = calculateDesiredYaw(m_localPlayer->getLocationX(),
                                                            m_localPlayer->getLocationY(),
                                                            closestPlayer->getLocationX(),
                                                            closestPlayer->getLocationY());

            double angleDeltaYaw = calculateAngleDelta(m_localPlayer->getYaw(), desiredViewAngleYaw);

            double distanceToTarget = math::calculateDistanceInMeters(m_localPlayer->getLocationX(), 
                                                                      m_localPlayer->getLocationY(), 
                                                                      m_localPlayer->getLocationZ(), 
                                                                      closestPlayer->getLocationX(), 
                                                                      closestPlayer->getLocationY(), 
                                                                      closestPlayer->getLocationZ());
            double angleThreshold = getAngleThreshold(distanceToTarget);

            if (abs(angleDeltaYaw) <= angleThreshold)
            {
                //randomDelayBeforeShooting();
                m_x11Utils->mouseClick(Button1);  // Trigger a shot using X11
            }
        }
    }
         
    double calculatePitchAngleDelta(double oldAngle, double newAngle)
    {
        return newAngle - oldAngle;
    }

    double calculateAngleDelta(double oldAngle, double newAngle)
    {
        double wayA = newAngle - oldAngle;
        double wayB = 360 - abs(wayA);
        if (wayA > 0 && wayB > 0)
            wayB *= -1;
        return (abs(wayA) < abs(wayB)) ? wayA : wayB;
    }

    double calculateDesiredYaw(double localPlayerLocationX, double localPlayerLocationY,
                               double enemyPlayerLocationX, double enemyPlayerLocationY)
    {
        double deltaX = enemyPlayerLocationX - localPlayerLocationX;
        double deltaY = enemyPlayerLocationY - localPlayerLocationY;
        return atan2(deltaY, deltaX) * (180 / M_PI);
    }

    double calculateDesiredPitch(double localPlayerLocationX, double localPlayerLocationY, double localPlayerLocationZ,
                                 double enemyPlayerLocationX, double enemyPlayerLocationY, double enemyPlayerLocationZ)
    {
        double deltaZ = enemyPlayerLocationZ - localPlayerLocationZ;
        double distance2D = math::calculateDistance2D(enemyPlayerLocationX, enemyPlayerLocationY, 
                                                      localPlayerLocationX, localPlayerLocationY);
        return atan2(-deltaZ, distance2D) * (180 / M_PI);
    }
    void randomDelayBeforeShooting()
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> dist(50, 100);  // Random delay between 100ms to 200ms

        int delay = dist(mt);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    double getAngleThreshold(double distanceToTarget) 
    {
        // Calculate yaw based on the target's half width and distance to the target
        double yaw = atan(0.3 / distanceToTarget) * (180 / M_PI);  // Convert from radians to degrees

        // You can add a safety margin here if you like, to increase the yaw slightly.
        // For example:
        yaw *= 1.8;  // 10% safety margin

        return yaw;
    }
};