#include "Backtrack.h"
#include "Vector.h"
#include "Menu.h"
#include "Entities.h"
#include "MiscClasses.h"
#include "Interfaces.h"

#define TICK_INTERVAL			( Interfaces::Globals->interval_per_tick )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )


struct lbyRecords
{
int tick_count;
float lby;
Vector headPosition;
};
struct backtrackData
{
float simtime;
Vector hitboxPos;
};

class BackTrack
{
int latest_tick;
bool IsTickValid(int tick);
void UpdateRecord(int i);
public:
lbyRecords records[64];
bool RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint);
void Update(int tick_count);
void legitBackTrack(CUserCmd* cmd, IClientEntity* pLocal); //legit is gay
};

BackTrack* backtracking = new BackTrack();
backtrackData headPositions[64][12];

void BackTrack::Update(int tick_count)
{
	if (!Menu::Window.RageBotTab.TargetBacktrack.GetState())
		return;

	latest_tick = tick_count;
	for (int i = 0; i < 64; i++)
	{
		UpdateRecord(i);
	}

}

bool BackTrack::IsTickValid(int tick)
{
	int delta = latest_tick - tick;
	float deltaTime = delta * Interfaces::Globals->interval_per_tick;
	return (fabs(deltaTime) <= 0.2f);
}

void BackTrack::UpdateRecord(int i)
{
	IClientEntity* pEntity = Interfaces::EntList->GetClientEntity(i);
	if (pEntity && pEntity->IsAlive() && !pEntity->IsDormant())
	{
		float lby = pEntity->GetLowerBodyYaw();
		if (lby != records[i].lby)
		{
			records[i].tick_count = latest_tick;
			records[i].lby = lby;
			records[i].headPosition = GetHitboxPosition(pEntity, 0);
		}
	}
	else
	{
		records[i].tick_count = 0;
	}
}

bool BackTrack::RunLBYBackTrack(int i, CUserCmd* cmd, Vector& aimPoint)
{
	if (IsTickValid(records[i].tick_count))
	{
		aimPoint = records[i].headPosition;
		cmd->tick_count = records[i].tick_count;
		return true;
	}
	return false;
}
void BackTrack::legitBackTrack(CUserCmd* cmd, IClientEntity* pLocal)
{
	if (Menu::Window.LegitBotTab.AimbotLegitBacktrack.GetState())
	{
	/*
		int bestTargetIndex = -1;
		float bestFov = FLT_MAX;
		player_info_t info;
		if (!pLocal->IsAlive())
			return;

		for (int i = 0; i <  Interfaces::Engine->GetMaxClients(); i++)
		{
			IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);

			if (!pEntity || !pLocal)
				continue;

			if (pEntity == pLocal)
				continue;

			if (!Interfaces::Engine->GetPlayerInfo(i, &info))
				continue;

			if (pEntity->IsDormant())
				continue;

			if (pEntity->GetTeamNum() == pLocal->GetTeamNum())
				continue;

			if (pEntity->IsAlive())
			{

				float simtime = pEntity->GetSimulationTime();
				Vector hitboxPos = GetHitboxPosition(pEntity, 0);

				headPositions[i][cmd->command_number % 13] = backtrackData{ simtime, hitboxPos };
				Vector ViewDir = AngleVectors(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
				float FOVDistance = distance_point_to_line(hitboxPos, pLocal->GetEyePosition(), ViewDir);

				if (bestFov > FOVDistance)
				{
					bestFov = FOVDistance;
					bestTargetIndex = i;
				}
			}
		}

		float bestTargetSimTime;
		if (bestTargetIndex != -1)
		{
			float tempFloat = FLT_MAX;
			Vector ViewDir = AngleVectors(cmd->viewangles + (pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f));
			for (int t = 0; t < 12; ++t)
			{
				float tempFOVDistance = distance_point_to_line(headPositions[bestTargetIndex][t].hitboxPos, pLocal->GetEyePosition(), ViewDir);
				if (tempFloat > tempFOVDistance && headPositions[bestTargetIndex][t].simtime > pLocal->GetSimulationTime() - 1)
				{
					tempFloat = tempFOVDistance;
					bestTargetSimTime = headPositions[bestTargetIndex][t].simtime;
				}
			}
			if (cmd->buttons & IN_ATTACK)
			{
				cmd->tick_count = TIME_TO_TICKS(bestTargetSimTime);
			}
		}
		*/
	}
}


