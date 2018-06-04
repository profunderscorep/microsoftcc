#include <array>
#include <string>
#include <deque>
#include <algorithm>
#include "Entities.h"
#include "CommonIncludes.h"
#include "Entities.h"
#include "Vector.h"
#include <map>
#include "Interfaces.h"
#include "Hacks.h"
#include "Hooks.h"

class CResolver
{
public:
	void Resolve(IClientEntity* pEntity); //resolve
	void FSN(IClientEntity* pEntity, ClientFrameStage_t stage);
	void CM(IClientEntity* pEntity);
	bool b_did_lby_update(IClientEntity* pEntity);
	bool b_lby_will_orgasm_in_five_nanoseconds(IClientEntity* pEntity);
	float newsimtime;
	float storedsimtime;
	float prime_lby_update;
	float second_lby_update;
	bool didhitHS;
	bool smartshoot;
	void baim(IClientEntity* pEntity);
	bool baim_entity = false;
private:
	IClientEntity* LocalPlayer = hackManager.pLocal(); // based on local player, dunno if this is accurate
	float flServerTime = (float)(LocalPlayer->GetTickBase()  * Interfaces::Globals->interval_per_tick);
};
namespace Globals
{
	extern CUserCmd* UserCmd;
	extern IClientEntity* Target;
	extern int Shots;
	extern bool change;
	extern int TargetID;
	extern bool didhitHS;
	extern int missedshots;
	extern std::map<int, QAngle> storedshit;
}
