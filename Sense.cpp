#pragma once
#include <vector>
#include "LocalPlayer.cpp"
#include "Player.cpp"
#include "Math.cpp"
#include "Level.cpp"
#include "X11Utils.cpp"
#include "ConfigLoader.cpp"
#include "Aimbot.cpp"
#include "Triggerbot.cpp"

class Sense
{
private:
    ConfigLoader *m_configLoader;
    Level *m_level;
    LocalPlayer *m_localPlayer;
    std::vector<Player *> *m_players;
    X11Utils *m_x11Utils;
    Aimbot *m_aimbot;  // added aimbot reference
	Triggerbot *m_triggerbot;  // added triggerbot reference


public:
	Sense(ConfigLoader *configLoader,
		  Level *level,
		  LocalPlayer *localPlayer,
		  std::vector<Player *> *players,
		  X11Utils *x11Utils,
		  Aimbot *aimbot,  // added comma here
		  Triggerbot *triggerbot)  // added triggerbot parameter
		  
	{
		m_configLoader = configLoader;
		m_level = level;
		m_localPlayer = localPlayer;
		m_players = players;
		m_x11Utils = x11Utils;
		m_aimbot = aimbot;  // assign aimbot
		m_triggerbot = triggerbot;  // assign triggerbot
	}
    void update()  
    {
	    if (!m_level->isPlayable())
		return;
	    for (int i = 0; i < m_players->size(); i++)
	    {
		Player *player = m_players->at(i);
		if (!player->isValid())
		    continue;
		if (player->getTeamNumber() == m_localPlayer->getTeamNumber())
		    continue;

		// Enable glow and set it to be visible through walls
		player->setGlowEnable(1);
		player->setGlowThroughWall(1);

		// If this player is the current target of the aimbot, make them red
		if (player == m_aimbot->getLockedOnPlayer())
		{
		    player->setGlowColorRed(1);
		    player->setGlowColorGreen(0);
		    player->setGlowColorBlue(0);
		}
		// If this player is the current target of the triggerbot, make them purple
        else if (player == m_triggerbot->getclosestPlayer())
        {
            player->setGlowColorRed(1);
            player->setGlowColorGreen(0);
            player->setGlowColorBlue(1);
			printf("Trying to apply purple glow to player: %s\n", player->getName().c_str());        
		}
		// If player is visible, make them green
		else if (player->isVisible())
		{
		    player->setGlowColorRed(0);
		    player->setGlowColorGreen(1);
		    player->setGlowColorBlue(0);
		}
		// Otherwise, make them white
		else
		{
		    player->setGlowColorRed(1);
		    player->setGlowColorGreen(1);
		    player->setGlowColorBlue(1);
		}
    	}
    }
};

