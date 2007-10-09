/* Copyright (C) 2006,2007 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
 
#include "../../../sc_defines.h"

#define ENCOUNTERS     6

enum EncounterState
{
    NOT_STARTED   = 0,
    IN_PROGRESS   = 1,
    FAILED        = 2,
    DONE          = 3
};

/* Serpentshrine cavern encounters:
0 - Hydross The Unstable event
1 - Leotheras The Blind Event
2 - The Lurker Below Event
3 - Fathom-Lord Karathress Event
4 - Morogrim Tidewalker Event
5 - Lady Vashj Event
*/

struct MANGOS_DLL_DECL instance_serpentshrine_cavern : public ScriptedInstance
{
    instance_serpentshrine_cavern(Map *Map) : ScriptedInstance(Map) {Initialize();};

    uint64 Sharkkis;
    uint64 Tidalvess;
    uint64 Caribdis;
    uint64 LadyVashj;
    uint64 TaintedElemental;

    uint32 Encounters[ENCOUNTERS];

    void Initialize()
    {
        Sharkkis = 0;
        Tidalvess = 0;
        Caribdis = 0;
        LadyVashj = 0;
        TaintedElemental = 0;

        for(uint8 i = 0; i < ENCOUNTERS; i++)
            Encounters[i] = NOT_STARTED;
    }

    bool IsEncounterInProgress() const 
    {
        for(uint8 i = 0; i < ENCOUNTERS; i++)
            if(Encounters[i] == IN_PROGRESS) return true; 

        return false;
    }

    void OnCreatureCreate(Creature *creature, uint32 creature_entry)
    {
        switch(creature_entry)
        {
            case 21212:
            LadyVashj = creature->GetGUID();
            break;
 
            case 22009:
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
            TaintedElemental = creature->GetGUID();
            break;

            case 21966:
            Sharkkis = creature->GetGUID();
            break;

            case 21965:
            Tidalvess = creature->GetGUID();
            break;

            case 21964:
            Caribdis = creature->GetGUID();
            break;
        }
    }

    uint64 GetUnitGUID(char *identifier)
    {
        if(identifier == "Sharkkis")
            return Sharkkis;
        else if(identifier == "Tidalvess")
            return Tidalvess;
        else if(identifier == "Caribdis")
            return Caribdis;
        else if(identifier == "LadyVashj")
            return LadyVashj;

        return NULL;
    }

    void SetData(char *type, uint32 data)
    {
        if(type == "HydrossTheUnstableEvent")
            Encounters[0] = data;
        else if(type == "LeotherasTheBlindEvent")
            Encounters[1] = data;
        else if(type == "TheLurkerBelowEvent")
            Encounters[2] = data;
        else if(type == "FathomLordKarathressEvent")
            Encounters[3] = data;
        else if(type == "MorogrimTidewalkerEvent")
            Encounters[4] = data;
        else if(type == "LadyVashjEvent")
            Encounters[5] = data;
    }

    uint32 GetData(char *type)
    {
        if(type == "HydrossTheUnstableEvent")
            return Encounters[0];
        else if (type == "LeotherasTheBlindEvent")
            return Encounters[1];
        else if(type == "TheLurkerBelowEvent")
            return Encounters[2];
        else if(type == "FathomLordKarathressEvent")
            return Encounters[3];
        else if(type == "MorogrimTidewalkerEvent")
            return Encounters[4];
        else if(type == "LadyVashjEvent")
            return Encounters[5];

        return 0;
    }
};

InstanceData* GetInstanceData_instance_serpentshrine_cavern(Map* map)
{
    return new instance_serpentshrine_cavern(map);
}

void AddSC_instance_serpentshrine_cavern()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "raid_serpentshrine_cavern";
    newscript->GetInstanceData = GetInstanceData_instance_serpentshrine_cavern;
    m_scripts[nrscripts++] = newscript;
}