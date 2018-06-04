#pragma once

#include "Hacks.h"

class CRageBot : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:

	int GetTargetCrosshair();
	int GetTargetDistance();
	int GetTargetNextShot();
	void PositionAdjustment(CUserCmd* pCmd);
	int GetTargetThreat(CUserCmd * pCmd);
	int GetTargetHealth();
	bool TargetMeetsRequirements(IClientEntity* pEntity);
	void aimAtPlayer(CUserCmd * pCmd);
	float FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int HitBox);
	int HitScan(IClientEntity* pEntity);
	bool AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd, bool &bSendPacket);

	void DoAimbot(CUserCmd *pCmd, bool &bSendPacket);
	void DoNoRecoil(CUserCmd *pCmd);
	void DoAntiAim(CUserCmd *pCmd, bool&bSendPacket);


	bool IsAimStepping;
	Vector LastAimstepAngle;
	Vector LastAngle;

	bool IsLocked;
	int TargetID;
	int HitBox;
	Vector AimPoint;
};
extern int dynamicAntiAimSide;