    // Updated: 2023-09-19 // GameVersion=v3.0.44.22
             
    #pragma once
    namespace offsets
    {
            // buttons
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            const long IN_ATTACK = (0x07422868 + 0x8);            // [Buttons] -> in_attack+0x8
            // core
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            const long REGION = 0x140000000;              // [Mine]          -> Region
            const long LEVEL = 0x16f71e0;                 // [Miscellaneous] -> LevelName
            const long LOCAL_PLAYER = 0x21d3758;       // [Miscellaneous] -> AVC_GameMovement+0x8
            const long ENTITY_LIST = 0x1e23418;           // [Miscellaneous] -> cl_entitylist
            // entity
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            const long LOCAL_ORIGIN = 0x0188; // [DataMap.CBaseViewModel]    -> 	m_localOrigin
            // player
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            const long GLOW_ENABLE = 0x0298;        // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x8
            const long GLOW_THROUGH_WALL = 0x0400; // [RecvTable.DT_HighlightSettings] -> m_highlightServerContextID + 0x10
            const long GLOW_COLOR = 0x200;                  // [Miscellaneous]                  -> glow_color
            const long TEAM_NUMBER = 0x0480;                // [RecvTable.DT_BaseEntity]        -> m_iTeamNum
            const long NAME = 0x05c1;                       // [RecvTable.DT_BaseEntity]        -> m_iName
            const long LIFE_STATE = 0x07d0;                 // [RecvTable.DT_Player]            -> m_lifeState
            const long VEC_PUNCH_WEAPON_ANGLE = 0x24e8;     // [DataMap.C_Player]               -> m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
            const long VIEW_ANGLE = (0x25e4 - 0x14);        // [DataMap.C_Player]               -> m_ammoPoolCapacity - 0x14
            const long BLEEDOUT_STATE = 0x2790;             // [RecvTable.DT_Player]            -> m_bleedoutState
            const long ZOOMING = 0x1c81;                    // [RecvTable.DT_Player]            -> m_bZooming
            const long LAST_VISIBLE_TIME = 0x1aa0;          // [Miscellaneous]                  -> CPlayer!lastVisibleTime
            const long CURRENT_SHIELDS = 0x01a0;            // [RecvTable.DT_BaseEntity]        -> m_shieldHealth
    }

