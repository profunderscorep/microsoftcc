#pragma once

#include "Vector3.h"
#include "Hacks.h"
extern float lineLBY;
extern float lineRealAngle;
extern float lineFakeAngle;
class Entity;

class CEsp : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);

	int GetTextPositionInList(int line);
private:

	void DrawLinesAA(Color color);
	IClientEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h;
	};

	void DrawPlayer(IClientEntity* pEntity, player_info_t pinfo);

	Color GetPlayerColor(IClientEntity* pEntity);
	void Corners(CEsp::ESPBox size, Color color, IClientEntity * pEntity);
	void FilledBox(CEsp::ESPBox size, Color color);
	bool GetBox(IClientEntity* pEntity, ESPBox &result);
	void drawBacktrackedSkelet(IClientEntity *base);
	void DrawBox(ESPBox size, Color color);
	void Barrel(CEsp::ESPBox size, Color color, IClientEntity * pEntity);
	void DrawWeapon(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawIcon(IClientEntity * pEntity, CEsp::ESPBox size);
	void DrawGlow();
	void EntityGlow();
	void DrawName(player_info_t pinfo, ESPBox size);
	void DrawHealth(IClientEntity* pEntity, ESPBox size);
	void DrawInfo(IClientEntity* pEntity, ESPBox size);
	void DrawCross(IClientEntity* pEntity);
	void DrawSkeleton(IClientEntity* pEntity);
	void DrawAngleSkeletons(IClientEntity * pEntity);
	
	void IsPlayerDefusing(player_info_t pinfo, CEsp::ESPBox size, IClientEntity * pEntity);


	void DrawMoney(IClientEntity * pEntity, CEsp::ESPBox size);

	void Armor(IClientEntity * pEntity, CEsp::ESPBox size);

	void DrawMolotov(IClientEntity * pEntity, ClientClass * cClass);

	void DrawSmoke(IClientEntity * pEntity, ClientClass * cClass);

	void DrawDecoy(IClientEntity * pEntity, ClientClass * cClass);

	void DrawHE(IClientEntity * pEntity, ClientClass * cClass);

	void Info(IClientEntity * pEntity, CEsp::ESPBox size);

	void GrenadeTrace();

	void DrawDistance(CEsp::ESPBox size, IClientEntity * pEntity);

	float DistanceTo(Vector vecSrc, Vector vecDst);

	void DrawChicken(IClientEntity* pEntity, ClientClass* cClass);
	void DrawDrop(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBomb(IClientEntity* pEntity, ClientClass* cClass);

	void BulletTrace(IClientEntity* pEntity, Color color);

	void LagCompensationSpoof();

	//int GetTextPositionInList(int line);

	void PassiveList();
};

class Listbase
{
public:
	int x, y;
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////PASTED///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Entity
{

public:
	void Discolights(Entity *base);
	int getTeam(); // needed
	Vector3 getViewOriginal2(); //needed
	int getIdx(); //needed
};

struct Offsets2
{
	DWORD localPlayer = 0x00,
		entityList = 0x00,
		entityLoopDist = 0x10,
		entTeam = 0x00,
		entGlowIndex = 0x1DB8,
		glowObjectBase = 0x00,
		glowObjectCount = 0x04,
		inCross = 0x00,
		stationary = 0xE9,
		engPtr = 0x00,
		viewOriginal = 0x00,
		aimPunch = 0x00,
		viewPunch = 0x00,
		gameRes = 0x00,
		metakFired = 0x00,
		compRank = 0x00,
		compWins = 0x00,
		radar = 0x00,
		skelet = 0x00,
		leben = 0x00,
		vecAechse = 0x00,
		activWeap = 0x00,
		itmDI = 0x00,
		coravDur = 0x00,
		c4Time = 0x00,
		c4Tick = 0x00,
		c4Def = 0x00,
		flags = 0x00,
		lifeSt = 0x00,
		coll = 0x00,
		collGrp = 0x00,
		rgflCoordinateFrame = 0x00,
		revealAllRank = 0x00,
		isRdy = 0x00,
		accPen = 0x00,
		glowMngr = 0x00,
		smokeCnt = 0x00,
		armVal = 0x00,
		hHelm = 0x00,
		tickBase = 0x00,
		vekVel = 0x00,
		nextPrimAtt = 0x00,
		clip = 0x00,
		angRot = 0x00,
		lowBodYtarg = 0x00,
		resConnected = 0x00,
		resTeam = 0x00,
		hitboxSet = 0x00,
		immun = 0x00,
		angEyeAechse = 0x00,
		uZum = 0x00,
		weapons = 0x00,
		modIdx = 0x00,
		viewModel = 0x00,
		viewModelIdx = 0x00,
		accId = 0x00,
		itemIdHigh = 0x00,
		custName = 0x00,
		fallbackPK = 0x00,
		fallbackS = 0x00,
		fallbackW = 0x00,
		fallbackST = 0x00,
		owner = 0x00,
		simulTime = 0x00,
		cycle = 0x00,
		sequence = 0x00,
		poseParams = 0x00,
		animTime = 0x00,
		lgtSmoke = 0x00,
		obsTrgt = 0x00,
		upisivaKost = 0x00,
		iCheckForOccl = 0x00,
		invalKostCache = 0x00,
		deadFlag4 = 0x00,
		hHeavArmor = 0x00,
		duckSpeed = 0x00,
		duckAmnt = 0x00,
		ducked = 0x00,
		ducking = 0x00;
};

extern Offsets2 offs;

struct ColorRGBExp32
{
	byte r, g, b;
	signed char exponent;
};
struct dlight_t
{
	int flags;
	Vector3 origin;
	float radius;
	ColorRGBExp32 color;
	float die; // stop lighting after this time
	float decay; // drop this each second
	float minLight; // don't add when contributing less
	int key;
	int style; // lightstyle

			   // For spotlights. Use m_OuterAngle == 0 for point lights
	Vector3 m_direction; // center of the light cone
	float m_innerAngle;
	float m_outerAngle;

	// If this ptr is set, the dlight will only affect this particular client renderable 
	const IClientRenderable* m_pExclusiveLightReceiver;

	dlight_t() : m_pExclusiveLightReceiver(NULL) {}

	float getRadius() const
	{
		return radius;
	}

	float getRadiusSquared() const
	{
		return radius * radius;
	}

	float isRadiusGreaterThanZero() const
	{
		return radius > 0.0f;
	}
};
namespace VT
{
	template<typename T> static T vfunc(void *base, int index)
	{
		DWORD *vTabella = *(DWORD**)base;
		return (T)vTabella[index];
	}
}

extern class Vector3;

class IVEffects
{
public:

	dlight_t *CL_AllocDlight(int key)
	{
		typedef dlight_t*(__thiscall *o_CL_AllocDlight)(PVOID, int);
		return VT::vfunc<o_CL_AllocDlight>(this, 4)(this, key);
	}

	dlight_t *CL_AllocElight(int key)
	{
		typedef dlight_t*(__thiscall *o_CL_AllocElight)(PVOID, int);
		return VT::vfunc<o_CL_AllocElight>(this, 5)(this, key);
	}
};

extern IVEffects *p_IVEffects;


class GlobVars
{
public:

	float realtime;
	int framecount;
	float absoluteframetime;
	float absoluteframestarttimestddev;
	float curtime;
	float frametime;
	int maxClients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	void *pSaveData;
	bool m_bClient;
	bool m_bRemoteClient;

private:

	int nTimestampNetworkingBase;
	int nTimestampRandomizeWindow;
};

extern GlobVars *p_Globalvars;

class ClientEntList2
{
public:
	virtual void Function0() = 0;
	virtual void Function1() = 0;
	virtual void Function2() = 0;

	virtual void *GetClientEntity(int iIndex) = 0;
	virtual void *GetClientEntityFromHandle(DWORD hHandle) = 0;
	virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int GetHighestEntityIndex() = 0;
};

extern ClientEntList2 *p_ClientEntList;


