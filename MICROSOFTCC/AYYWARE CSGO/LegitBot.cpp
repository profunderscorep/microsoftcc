//#include "Backtrack.h"
#include "LegitBot.h"
#include "RenderManager.h"
#include "MathFunctions.h"

#define    HITGROUP_GENERIC    0
#define    HITGROUP_HEAD        1
#define    HITGROUP_CHEST        2
#define    HITGROUP_STOMACH    3
#define HITGROUP_LEFTARM    4    
#define HITGROUP_RIGHTARM    5
#define HITGROUP_LEFTLEG    6
#define HITGROUP_RIGHTLEG    7
#define HITGROUP_GEAR        10

void CLegitBot::Init()
{
	IsLocked = false;
	TargetID = -1;
	HitBox = -1;
}

void CLegitBot::Draw()
{

}

static int CustomDelay = 0;
static int CustomBreak = 0;

void CLegitBot::Move(CUserCmd *pCmd, bool& bSendPacket)
{
	if (!Menu::Window.LegitBotTab.Active.GetState())
		return;

	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	static int CustomAimTime = 0;
	static int CustomAimStart = 0;
	if (Menu::Window.LegitBotTab.AimbotEnable.GetState())
	{
		if (StartAim > 0)
		{
			if (CustomAimStart < (StartAim * 333))
			{
				CustomAimStart++;
			}
			else
			{
				if (Aimtime > 0)
				{
					if (CustomAimTime < (Aimtime * 333))
					{
						DoAimbot(pCmd);
						CustomAimTime++;
					}
					if (!GUI.GetKeyState(Menu::Window.LegitBotTab.AimbotKeyBind.GetKey()) || Menu::Window.LegitBotTab.AimbotAutoFire.GetState())
					{
						CustomAimTime = 0;
						CustomAimStart = 0;
					}
				}
				else
				{
					DoAimbot(pCmd);
					CustomAimTime = 0;
					CustomAimStart = 0;
				}
			}

			if (!GUI.GetKeyState(Menu::Window.LegitBotTab.AimbotKeyBind.GetKey()) || Menu::Window.LegitBotTab.AimbotAutoFire.GetState())
			{
				CustomAimStart = 0;
				CustomAimTime = 0;
			}
		}
		else
		{
			if (Aimtime > 0)
			{
				if (CustomAimTime < (Aimtime * 333))
				{
					DoAimbot(pCmd);
					CustomAimTime++;
				}
				if (!GUI.GetKeyState(Menu::Window.LegitBotTab.AimbotKeyBind.GetKey()) || Menu::Window.LegitBotTab.AimbotAutoFire.GetState())
				{
					CustomAimTime = 0;
					CustomAimStart = 0;
				}
			}
			else
			{
				DoAimbot(pCmd);
				CustomAimTime = 0;
				CustomAimStart = 0;
			}
		}
	}
	if (Menu::Window.LegitBotTab.TriggerEnable.GetState() && ((Menu::Window.LegitBotTab.TriggerKeyPress.GetState() && GUI.GetKeyState(Menu::Window.LegitBotTab.TriggerKeyBind.GetKey()) || !Menu::Window.LegitBotTab.TriggerKeyPress.GetState())))
	{
		DoTrigger(pCmd);
	}
	//BackTrack* pBacktrack;
	//pBacktrack->legitBackTrack(pCmd, pLocal);
	SyncWeaponSettings();
}

void CLegitBot::SyncWeaponSettings()
{
	IClientEntity* pLocal = hackManager.pLocal();
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());

	if (!pWeapon)
		return;

	if (GameUtils::IsPistol(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponPistSpeed.GetValue() / 100;
		FoV = Menu::Window.LegitBotTab.WeaponPistFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponPistRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponPistHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = Menu::Window.LegitBotTab.WeaponPistAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponPistStartAimtime.GetValue() / 10;
	}
	else if (GameUtils::IsSniper(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponSnipSpeed.GetValue();
		FoV = Menu::Window.LegitBotTab.WeaponSnipFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponSnipRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponSnipHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = Menu::Window.LegitBotTab.WeaponSnipAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponSnipStartAimtime.GetValue() / 10;
	}
	else if (GameUtils::IsMachinegun(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponMGSpeed.GetValue() / 100;
		FoV = Menu::Window.LegitBotTab.WeaponMGFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponMGRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponMGHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = Menu::Window.LegitBotTab.WeaponMGAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponMGStartAimtime.GetValue() / 10;
	}
	else if (GameUtils::IsShotgun(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponShotgunSpeed.GetValue() / 100;
		FoV = Menu::Window.LegitBotTab.WeaponShotgunFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponShotgunRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponShotgunHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = Menu::Window.LegitBotTab.WeaponShotgunAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponShotgunStartAimtime.GetValue() / 10;
	}
	else if (GameUtils::IsMP(pWeapon))
	{
		Speed = Menu::Window.LegitBotTab.WeaponMpSpeed.GetValue() / 100;
		FoV = Menu::Window.LegitBotTab.WeaponMpFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponMpRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponMpHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}

		Aimtime = Menu::Window.LegitBotTab.WeaponMpAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponMpStartAimtime.GetValue() / 10;
	}
	else
	{
		Speed = Menu::Window.LegitBotTab.WeaponMainSpeed.GetValue() / 100;
		FoV = Menu::Window.LegitBotTab.WeaponMainFoV.GetValue() * 2;
		RecoilControl = Menu::Window.LegitBotTab.WeaponMainRecoil.GetValue();

		switch (Menu::Window.LegitBotTab.WeaponMainHitbox.GetIndex())
		{
		case 0:
			HitBox = ((int)CSGOHitboxID::Head);
			Multihitbox = false;
			break;
		case 1:
			HitBox = ((int)CSGOHitboxID::Neck);
			Multihitbox = false;
			break;
		case 2:
			HitBox = ((int)CSGOHitboxID::Chest);
			Multihitbox = false;
			break;
		case 3:
			HitBox = ((int)CSGOHitboxID::Stomach);
			Multihitbox = false;
			break;
		case 4:
			Multihitbox = true;
			break;
		}
		Aimtime = Menu::Window.LegitBotTab.WeaponMainAimtime.GetValue() / 10;
		StartAim = Menu::Window.LegitBotTab.WeaoponMainStartAimtime.GetValue() / 10;
	}
}

void CLegitBot::DoAimbot(CUserCmd *pCmd)
{
	IClientEntity* pTarget = nullptr;
	IClientEntity* pLocal = hackManager.pLocal();
	bool FindNewTarget = true;

	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(pLocal->GetActiveWeaponHandle());
	if (pWeapon)
	{
		if (pWeapon->GetAmmoInClip() == 0 || !GameUtils::IsBallisticWeapon(pWeapon))
		{
			return;
		}
		SyncWeaponSettings();

	}
	else
		return;

	if (IsLocked && TargetID >= 0 && HitBox >= 0)
	{
		pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		if (pTarget  && TargetMeetsRequirements(pTarget))
		{
			SyncWeaponSettings();
			if (HitBox >= 0)
			{
				Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
				Vector View; Interfaces::Engine->GetViewAngles(View);
				if (pLocal->GetVelocity().Length() > 45.f);
				View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * RecoilControl;
				float nFoV = FovToPlayer(ViewOffset, View, pTarget, HitBox);
				if (nFoV < FoV)
					FindNewTarget = false;
			}
		}
	}

	if (FindNewTarget)
	{
		TargetID = 0;
		pTarget = nullptr;
		HitBox = -1;

		TargetID = GetTargetCrosshair();

		if (TargetID >= 0)
		{
			pTarget = Interfaces::EntList->GetClientEntity(TargetID);
		}
		else
		{
			pTarget = nullptr;
			HitBox = -1;
		}
	}

	SyncWeaponSettings();

	if (TargetID >= 0 && pTarget)
	{
		SyncWeaponSettings();

		if (Menu::Window.LegitBotTab.AimbotKeyPress.GetState())
		{
			int Key = Menu::Window.LegitBotTab.AimbotKeyBind.GetKey();
			if (Key >= 0 && !GUI.GetKeyState(Key))
			{
				TargetID = -1;
				pTarget = nullptr;
				HitBox = -1;
				return;
			}
		}

		Vector AimPoint;

		if (Multihitbox)
		{
			AimPoint = GetHitboxPosition(pTarget, besthitbox);
		}
		else
		{
			AimPoint = GetHitboxPosition(pTarget, HitBox);
		}

		if (AimAtPoint(pLocal, AimPoint, pCmd))
		{
			if (Menu::Window.LegitBotTab.AimbotAutoFire.GetState() && !(pCmd->buttons & IN_ATTACK))
			{
				pCmd->buttons |= IN_ATTACK;
			}
		}
	}
}

bool CLegitBot::TargetMeetsTriggerRequirements(IClientEntity* pEntity)
{
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex() && pEntity->GetIndex() < 65)
	{
		if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum() || Menu::Window.LegitBotTab.AimbotFriendlyFire.GetState())
		{
			if (!pEntity->HasGunGameImmunity())
			{
				return true;
			}
		}
	}

	return false;
}

void CLegitBot::DoTrigger(CUserCmd *pCmd)
{
	IClientEntity* LocalPlayer = hackManager.pLocal();

	auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(LocalPlayer->GetWeaponHandle());
	auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

	if (LocalPlayerWeapon) {
		if (LocalPlayerWeapon->GetAmmoInClip() == 0)
			return;

		auto ClientClass = WeaponEntity->GetClientClass2();
		if (ClientClass->m_ClassID == (int)CSGOClassID::CKnife ||
			ClientClass->m_ClassID == (int)CSGOClassID::CHEGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CDecoyGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CIncendiaryGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CSmokeGrenade ||
			ClientClass->m_ClassID == (int)CSGOClassID::CC4) {
			return;
		}
	}
	else
		return;

	Vector ViewAngles = pCmd->viewangles;
	if (Menu::Window.LegitBotTab.TriggerRecoil.GetState())
		ViewAngles += LocalPlayer->GetAimPunch() * 2.0f;

	Vector CrosshairForward;
	AngleVectors(ViewAngles, &CrosshairForward);
	CrosshairForward *= 8000.f;


	Vector TraceSource = LocalPlayer->GetEyePosition();
	Vector TraceDestination = TraceSource + CrosshairForward;

	Ray_t Ray;
	trace_t Trace;
	CTraceFilter Filter;

	Filter.pSkip = LocalPlayer;

	Ray.Init(TraceSource, TraceDestination);
	Interfaces::Trace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

	if (!Trace.m_pEnt)
		return;
	if (!Trace.m_pEnt->IsAlive())
		return;
	if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
		return;
	if (Trace.m_pEnt->IsImmune())
		return;

	if (!Menu::Window.LegitBotTab.TriggerTeammates.GetState()) {
		if (LocalPlayer->GetTeamNum() == Trace.m_pEnt->GetTeamNum())
			return;
	}

	if (Menu::Window.LegitBotTab.TriggerSmokeCheck.GetState())
	{
		typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);

		static uint32_t GoesThroughSmokeOffset = (uint32_t)Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
		static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

		if (GoesThroughSmokeFunction(hackManager.pLocal()->GetEyePosition(), Trace.m_pEnt->GetBonePos(6)))
			return;
	}

	if ((Menu::Window.LegitBotTab.TriggerHead.GetState() && Trace.hitgroup == HITGROUP_HEAD) ||
		(Menu::Window.LegitBotTab.TriggerChest.GetState() && Trace.hitgroup == HITGROUP_CHEST) ||
		(Menu::Window.LegitBotTab.TriggerStomach.GetState() && Trace.hitgroup == HITGROUP_STOMACH) ||
		(Menu::Window.LegitBotTab.TriggerArms.GetState() && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM)) ||
		(Menu::Window.LegitBotTab.TriggerLegs.GetState() && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))) {
		pCmd->buttons |= IN_ATTACK;
	}
}

bool CLegitBot::TargetMeetsRequirements(IClientEntity* pEntity)
{
	if (pEntity && pEntity->IsDormant() == false && pEntity->IsAlive() && pEntity->GetIndex() != hackManager.pLocal()->GetIndex())
	{
		ClientClass *pClientClass = pEntity->GetClientClass();
		player_info_t pinfo;
		if (pClientClass->m_ClassID == (int)CSGOClassID::CCSPlayer && Interfaces::Engine->GetPlayerInfo(pEntity->GetIndex(), &pinfo))
		{
			if (pEntity->GetTeamNum() != hackManager.pLocal()->GetTeamNum() || Menu::Window.LegitBotTab.AimbotFriendlyFire.GetState())
			{
				if (Menu::Window.LegitBotTab.AimbotSmokeCheck.GetState()) {
					typedef bool(__cdecl* GoesThroughSmoke)(Vector, Vector);

					static uint32_t GoesThroughSmokeOffset = (uint32_t)Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0");
					static GoesThroughSmoke GoesThroughSmokeFunction = (GoesThroughSmoke)GoesThroughSmokeOffset;

					if (GoesThroughSmokeFunction(hackManager.pLocal()->GetEyePosition(), pEntity->GetBonePos(8)))
						return false;
				}

				if (Multihitbox)
				{
					if (!pEntity->HasGunGameImmunity())
					{
						if (GameUtils::IsVisible(hackManager.pLocal(), pEntity, 0) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 8) || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 4 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 1 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 2 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 3 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 5 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 7 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 9 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 10 || GameUtils::IsVisible(hackManager.pLocal(), pEntity, 6))))))))))
							return true;
						else
							return false;
					}
				}
				else
				{
					if (!pEntity->HasGunGameImmunity() && GameUtils::IsVisible(hackManager.pLocal(), pEntity, HitBox))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

float Get3dDistance(Vector me, Vector ent)
{
	return sqrt(pow(double(ent.x - me.x), 2.0) + pow(double(ent.y - me.y), 2.0) + pow(double(ent.z - me.z), 2.0));
}

float CLegitBot::FovToPlayer(Vector ViewOffSet, Vector View, IClientEntity* pEntity, int aHitBox)
{
	CONST FLOAT MaxDegrees = 180.0f;

	Vector Angles = View;

	Vector Origin = ViewOffSet;

	Vector Delta(0, 0, 0);

	Vector Forward(0, 0, 0);

	AngleVectors(Angles, &Forward);
	Vector AimPos = GetHitboxPosition(pEntity, aHitBox);

	VectorSubtract(AimPos, Origin, Delta);

	Normalize(Delta, Delta);

	float Distance = Get3dDistance(Origin, AimPos);

	float pitch = sin(Forward.x - Delta.x) * Distance;
	float yaw = sin(Forward.y - Delta.y) * Distance;
	float zaw = sin(Forward.z - Delta.z) * Distance;

	float mag = sqrt((pitch*pitch) + (yaw*yaw) + (zaw*zaw));
	return mag;
}

int CLegitBot::GetTargetCrosshair()
{
	SyncWeaponSettings();
	int target = -1;


	IClientEntity* pLocal = hackManager.pLocal();
	Vector ViewOffset = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector View; Interfaces::Engine->GetViewAngles(View);
	View += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);

		if (TargetMeetsRequirements(pEntity))
		{
			if (Multihitbox)
			{

				float fov1 = FovToPlayer(ViewOffset, View, pEntity, 0);
				float fov2 = FovToPlayer(ViewOffset, View, pEntity, 4);
				float fov3 = FovToPlayer(ViewOffset, View, pEntity, 6);

				if (fov1 < FoV || fov2 < FoV && fov1 < FoV || fov3 < FoV)
				{
					FoV = fov1;
					target = i;
					besthitbox = 0;
				}

				if (fov2 < FoV || fov1 < FoV && fov2 < FoV || fov3 < FoV)
				{
					FoV = fov2;
					target = i;
					besthitbox = 4;
				}

				if (fov3 < FoV || fov1 < FoV && fov3 < FoV || fov2 < FoV)
				{
					FoV = fov3;
					target = i;
					besthitbox = 6;
				}

			}
			else
			{
				int NewHitBox = HitBox;
				if (NewHitBox >= 0)
				{
					float fov = FovToPlayer(ViewOffset, View, pEntity, 0);
					if (fov < FoV)
					{
						FoV = fov;
						target = i;
					}
				}
			}
		}
	}

	return target;
}

bool CLegitBot::AimAtPoint(IClientEntity* pLocal, Vector point, CUserCmd *pCmd)
{
	if (point.Length() == 0) return false;

	Vector angles;
	Vector src = pLocal->GetOrigin() + pLocal->GetViewOffset();

	CalcAngle(src, point, angles);
	GameUtils::NormaliseViewAngle(angles);

	if (angles[0] != angles[0] || angles[1] != angles[1])
	{
		return false;
	}

	if (RecoilControl > 0)
	{
		Vector AimPunch = pLocal->localPlayerExclusive()->GetAimPunchAngle();
		if (AimPunch.Length2D() > 0 && AimPunch.Length2D() < 150)
		{
			angles -= AimPunch * RecoilControl;
			GameUtils::NormaliseViewAngle(angles);
		}
	}

	IsLocked = true;

	Vector shit = angles - pCmd->viewangles;
	bool v = false;
	GameUtils::NormaliseViewAngle(shit);
	if (shit.Length() > Speed)
	{
		Normalize(shit, shit);
		shit *= Speed;
	}
	else
	{
		v = true;
	}

	pCmd->viewangles += shit;
	Interfaces::Engine->SetViewAngles(pCmd->viewangles);

	return v;
}
