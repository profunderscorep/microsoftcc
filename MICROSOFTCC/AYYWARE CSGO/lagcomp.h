/*
#pragma once
#include "Hacks.h"
#include <deque>

extern bool BacktrackCanShotEnemy;
extern int ResolverStage[65];

 struct LagRecord_A
{
	Vector m_vecVelocity;
	Vector m_vAbsOrigin;
	Vector m_vecAngles;
	Vector m_eyeAngles;
	int m_iTargetID;
	int m_nSequence;
	int m_iWantedTick;
	int m_iBacktrackedTick;
	float m_fSimulationTime;
	float m_flCycle;
	float m_flPoseParameter[24];
	float m_flLowerBodyYawTarget;
	unsigned char flags;
	bool m_bIsBreakingLagComp;
	bool m_bIsFixed;
	Vector headSpot;
	int m_iPrevBullets;

	LagRecord_A()
	{
		m_iPrevBullets = -1;
		m_iTargetID = -1;
		m_fSimulationTime = -1;
		m_iWantedTick = -1;
		m_bIsBreakingLagComp = false;
		m_bIsFixed = false;
		m_iBacktrackedTick = -1;
		m_vAbsOrigin = Vector(0, 0, 0);
		m_flCycle = -1;
		m_nSequence = -1;
		m_flLowerBodyYawTarget = 0;
		m_flPoseParameter[24] = 0;
		m_vecAngles = Vector(0, 0, 0);
		flags = -1;
		m_vecVelocity = Vector(0, 0, 0);
		m_eyeAngles = Vector(0, 0, 0);
		headSpot = Vector(0, 0, 0);
	}

	LagRecord_A(const LagRecord_A &src)
	{
		m_iPrevBullets = src.m_iPrevBullets;
		m_flCycle = src.m_flCycle;
		m_nSequence = src.m_nSequence;
		m_iTargetID = src.m_iTargetID;
		m_vecAngles = src.m_vecAngles;
		m_fSimulationTime = src.m_fSimulationTime;
		m_iWantedTick = src.m_iWantedTick;
		m_bIsBreakingLagComp = src.m_bIsBreakingLagComp;
		m_bIsFixed = src.m_bIsFixed;
		m_vAbsOrigin = src.m_vAbsOrigin;
		m_iBacktrackedTick = src.m_iBacktrackedTick;
		flags = src.flags;
		m_flLowerBodyYawTarget = src.m_flLowerBodyYawTarget;
		m_flPoseParameter[24] = src.m_flPoseParameter[24];
		m_vecVelocity = src.m_vecVelocity;
		m_eyeAngles = src.m_eyeAngles;
		headSpot = src.headSpot;
	}
};

class LagCompensation
{
public:

	LagRecord_A m_LagRecord[64][11] = {};
	LagRecord_A m_PrevRecords[64] = {};

public:


	void initLagRecord();


private:

	template<class T, class U>

};

extern LagCompensation *lagComp;

*/