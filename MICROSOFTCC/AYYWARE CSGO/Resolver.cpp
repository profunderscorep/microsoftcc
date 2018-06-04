#include "Resolver.h"
#include "Ragebot.h"
#include "Hooks.h"
#include "Vector.h"

void CResolver::baim(IClientEntity* pEntity)
{
	baim_entity == true;
}

bool CResolver::b_did_lby_update(IClientEntity* pEntity)
{
	return false;

	float oldLBY = pEntity->GetLowerBodyYaw();

	if (oldLBY != pEntity->GetLowerBodyYaw())
	{
		return true;
		oldLBY = pEntity->GetLowerBodyYaw();
	}

	static bool isgay = false;

	if (pEntity->GetVelocity().Length2D() > 36 && pEntity->GetFlags() &FL_ONGROUND) // if walking
	{
		if (!isgay)
		{
			return true;
			isgay = true;
		}
		else if (isgay)
		{
			CResolver::prime_lby_update = flServerTime;
			CResolver::second_lby_update = CResolver::prime_lby_update + 0.22f;
			if (CResolver::second_lby_update == flServerTime)
			{
				isgay = false;
				return true;
			}
			
		}
	}
	else if (pEntity->GetVelocity().Length2D() <= 0.1f && pEntity->GetFlags() &FL_ONGROUND) // if standing still
	{

		CResolver::prime_lby_update = flServerTime;
		CResolver::second_lby_update = CResolver::prime_lby_update + 0.22f;
		if (CResolver::second_lby_update == flServerTime)
		{
			return true;
		}
	}
}

bool CResolver::b_lby_will_orgasm_in_five_nanoseconds(IClientEntity* entity)
{
	return false; //can't even get a gf smh

	float fl_firstlbyupdate; // time of first lby update
	float fl_nextlbyupdate; // time of next lby update
	if (b_did_lby_update(entity))
	{
		fl_firstlbyupdate = flServerTime;
		if (entity->GetVelocity().Length2D() > 36.f && entity->GetFlags() &FL_ONGROUND)
		{
			fl_nextlbyupdate = fl_firstlbyupdate + 0.22f;
		}
		else if (entity->GetVelocity().Length2D() == 0.f && entity->GetFlags() &FL_ONGROUND)
		{
			fl_nextlbyupdate = fl_firstlbyupdate + 1.1f;
		}
	}
	if (fl_nextlbyupdate - flServerTime < 0.1f)
		return true;

	/*
	bool bBool;

	if (F::Animations->m_serverAnimState->m_flSpeed > 0.1f)
	{
	F::Animations->m_flNextBodyUpdate = g_pGlobalVarsBase->curtime + 0.22f;
	F::Animations->m_flFirstBodyUpdate = F::Animations->m_flNextBodyUpdate;
	bBool = true;
	}

	else if (g_pGlobalVarsBase->curtime > F::Animations->m_flNextBodyUpdate)
	{
	if (F::Animations->m_flFirstBodyUpdate != F::Animations->m_flNextBodyUpdate)
	bBool = true;
	F::Animations->m_flNextBodyUpdate = g_pGlobalVarsBase->curtime + 1.1f;
	}

	if (bBool && g_pGlobalVarsBase->curtime > F::Animations->m_flFirstBodyUpdate &&  F::Animations->m_serverAnimState->m_flSpeed < 0.1f)
	{
	return true;
	}
	*/

}
typedef float interval[2]; // interval is angle -+ 5°  for example for angle 20° => [15°, 25°], target angle doesn't matter since it doesn't need to be clamped

bool is_in_interval(interval interv, int integer)
{
	if (interv[0] <= integer && interv[1] >= integer)
		return true;
	else return false;
}

int Patternfinding(std::array<interval, 5> input) // simple self crafted pattern finding algorithm
{
	return 0;

	for (int i = 30; i >= 180; i + 30)
	{
		for (int j = 0; j >= 5; j++)
		{
			//skipping 150
			if (i = 150)
				i = 180;

			if (is_in_interval((input[j]), i*j + ((input[0][j] + input[1][j]) / 2.f)))
			{
				return i;
				break;
			}
			if (i > 180) // couldn't find a linear pattern
				break;
		}
	}
	for (int j = 0; j >= 5; j++)
	{
		if (j <= 3)
		{
			if (is_in_interval(input[j], ((input[0][j + 2] + input[1][j + 2]) / 2.f)))
				return j;
			break;
		}
		if (j > 3)
		{
			if (is_in_interval(input[j], ((input[0][j - 2] + input[1][j - 2]) / 2.f)))
				return j;
			break;
		}
	}
}
void CResolver::Resolve(IClientEntity* pEntity)
{
	if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 0)
		return;

	if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 1) // bruteforce
		return; // to do: make bruteforce resolver


	for (auto i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		if (pEntity || pEntity != hackManager.pLocal() || !pEntity->IsDormant() || pEntity->IsAlive())
			continue;

		pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();

		player_info_t pTemp;
	

		if (!Interfaces::Engine->GetPlayerInfo(i, &pTemp))
			continue;

		

		float LBYhistory[2]; // checking if a static angle is broken, ugly shit
		float secondLBYhistory[5]; // for patternfinding, need to base everything on this array instead of these other arrays

	

		for (int i = 0; i <= 5; i++)
		{

			if (i = 5)
				i = 0;

			if (b_did_lby_update(pEntity))
				secondLBYhistory[i] = pEntity->GetLowerBodyYaw();
			else
				break;

		}

		for (int i = 0; i <= 2; i++)
		{
			if (i = 2)
				i = 0;

			if (b_did_lby_update(pEntity))
				LBYhistory[i] = pEntity->GetLowerBodyYaw();
			else
				break;

		}

		bool is_static = false;
		for (int i = 0; i <= 2; i++)
		{
			if (LBYhistory[i] == LBYhistory[i + 1])
				is_static = true;
			else
				is_static = false;
		}

		//lbyhistory from float array to 2x5 matrix
		std::array<interval, 5> intervalLBYHistory;
		for (int i = 0; i >= 5; i++)
		{
			intervalLBYHistory[0][i] = secondLBYhistory[i] - 5.f;
			intervalLBYHistory[1][i] = secondLBYhistory[i] + 5.f;
		}

		////////////////////////////////////////////////////////////

		if (pEntity->GetVelocity().Length2D() <= 36 && pEntity->GetVelocity().Length2D() > 0 && pEntity->GetFlags() &FL_ONGROUND) // if fagwalking
		{
			if (is_static && b_lby_will_orgasm_in_five_nanoseconds(pEntity))
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
				smartshoot == true;
			}
			else if (b_lby_will_orgasm_in_five_nanoseconds(pEntity))
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
				smartshoot == false;
				baim(pEntity);
			}
			else
				smartshoot == false;
		}

		if (pEntity->GetVelocity().Length2D() > 36 && pEntity->GetFlags() &FL_ONGROUND) // checks if player is walking and not fagwalking, also applyable for backtracking stuff
		{
			if (is_static && b_lby_will_orgasm_in_five_nanoseconds(pEntity)) // checks if breaking static angle
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
				smartshoot == true;
			}
			else if (!is_static) // is randomly changing angles
			{
				if (didhitHS && b_lby_will_orgasm_in_five_nanoseconds(pEntity)) // is breaking random angles
				{
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
					smartshoot == false;
					baim(pEntity);
				}
				else
				{
					switch (Patternfinding(intervalLBYHistory)) // costs 1 second to resolve
					{
					case 0:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][0] + intervalLBYHistory[1][0]) / 2.f);
						break;
					case 1:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][1] + intervalLBYHistory[1][1]) / 2.f);
						break;
					case 2:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][2] + intervalLBYHistory[1][2]) / 2.f);
						break;
					case 3:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][3] + intervalLBYHistory[1][3]) / 2.f);
						break;
					case 4:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][4] + intervalLBYHistory[1][4]) / 2.f);
						break;
					case 5:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][5] + intervalLBYHistory[1][5]) / 2.f);
						break;
					case 30:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 30.f;
						break;
					case 60:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 60.f;
						break;
					case 90:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 90.f;
						break;
					case 120:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 120.f;
						break;
						// friendly reminder that 150 doesn't exist
					case 180:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 180.f;
						break;
					default:
						if (b_lby_will_orgasm_in_five_nanoseconds(pEntity)) // is slightly changing angles, would be stupid if we can't resolve that since we know when it's gonna update
						{
							pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
							smartshoot == true;
						}
						b_lby_will_orgasm_in_five_nanoseconds(pEntity) ? smartshoot == true : smartshoot == false;
					}
				}
			}
			smartshoot == false;
		}

		if (pEntity->GetVelocity().Length2D() == 0 && pEntity->GetFlags() &FL_ONGROUND) // if is standing still
		{
			if (is_static && b_lby_will_orgasm_in_five_nanoseconds(pEntity))
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
				smartshoot == true;
				// predict when angle is going to flip, because who doesn't break angles in 2018
			}
			else if (!is_static)
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
				if (didhitHS && b_lby_will_orgasm_in_five_nanoseconds(pEntity)) // is breaking random angles
				{
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
					smartshoot == false;
				}
				else
				{
					switch (Patternfinding(intervalLBYHistory)) // costs 5 seconds to resolve
					{
					case 0:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][0] + intervalLBYHistory[1][0]) / 2.f);
						break;
					case 1:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][1] + intervalLBYHistory[1][1]) / 2.f);
						break;
					case 2:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][2] + intervalLBYHistory[1][2]) / 2.f);
						break;
					case 3:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][3] + intervalLBYHistory[1][3]) / 2.f);
						break;
					case 4:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][4] + intervalLBYHistory[1][4]) / 2.f);
						break;
					case 5:
						pEntity->GetEyeAnglesXY()->y = ((intervalLBYHistory[0][5] + intervalLBYHistory[1][5]) / 2.f);
						break;
					case 30:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 30.f;
						break;
					case 60:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 60.f;
						break;
					case 90:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 90.f;
						break;
					case 120:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 120.f;
						break;
						// friendly reminder that 150 doesn't exist
					case 180:
						pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 180.f;
						break;

					default:
						if (b_lby_will_orgasm_in_five_nanoseconds(pEntity)) // is slightly changing angles, would be stupid if we can't resolve that since we know when it's gonna update
						{
							pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
							smartshoot == true;
						}
						b_lby_will_orgasm_in_five_nanoseconds(pEntity) ? smartshoot == true : smartshoot == false;
					}
				}
			}
		}
		if (!(pEntity->GetFlags() &FL_ONGROUND)) // if is in air
		{
			pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
			if (didhitHS)
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
			else
			{
				for (int i = 0; i <= 180; i = i + 45)
				{
					if (i = 180)
						i = 0;
					pEntity->GetEyeAnglesXY()->y = i;
					if (!didhitHS)
						continue;
				}
			}
		}


		// testing this fucking shit boolean
		if (is_static && b_lby_will_orgasm_in_five_nanoseconds(pEntity))
		{
			//pEnt->GetEyeAngles().y = pEnt->GetLowerBodyYawTarget();
			// TO DO: place chams at according angle when this stupid boolean returns true 
			/*
			Vector absorg = pPlayer->GetOrigin();
			F::Backtrack->BackupPlayer( pPlayer );
			for ( int i = track.size(); i > 0; i-- )
			{
			if ( F::Backtrack->StartLagCompensation( pPlayer, NULL, i - 1 ) )
			{
			if ( fabsf( track.at( i - 1 ).m_vecOrigin.Length() - absorg.Length() ) < 3.f )
			break;

			ForceMaterial( M::hidden, Color( 50, 50, 255, 50 ) );
			G::InChams = true;
			pPlayer->DrawModel( STUDIO_RENDER, 50 );
			G::InChams = false;
			break;
			}
			}
			F::Backtrack->RestorePlayer( pPlayer );
			*/
		}
	}
}
	/*
	bool MeetsLBYReq;
	SpoofedConvar* convar;

	if (pEntity->GetFlags() & FL_ONGROUND)
		MeetsLBYReq = true;
	else
		MeetsLBYReq = false;

	bool IsMoving;
	if (pEntity->GetVelocity().Length2D() >= 0.5)
		IsMoving = true;
	else
		IsMoving = false;

	ResolverSetup::NewANgles[pEntity->GetIndex()] = *pEntity->GetEyeAnglesXY();
	ResolverSetup::newlby[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw();
	ResolverSetup::newsimtime = pEntity->GetSimulationTime();
	ResolverSetup::newdelta[pEntity->GetIndex()] = pEntity->GetEyeAnglesXY()->y;
	ResolverSetup::newlbydelta[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw();
	ResolverSetup::finaldelta[pEntity->GetIndex()] = ResolverSetup::newdelta[pEntity->GetIndex()] - ResolverSetup::storeddelta[pEntity->GetIndex()];
	ResolverSetup::finallbydelta[pEntity->GetIndex()] = ResolverSetup::newlbydelta[pEntity->GetIndex()] - ResolverSetup::storedlbydelta[pEntity->GetIndex()];
	if (newlby == storedlby)
		ResolverSetup::lbyupdated = false;
	else
		ResolverSetup::lbyupdated = true;

	if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 0)
	{

	}
	else if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 1)//level 1
	{
		if (MeetsLBYReq && lbyupdated)
			pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
		else if (!MeetsLBYReq && lbyupdated)
		{
			switch (Globals::Shots % 4)
			{
			case 1:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() - 15;
				break;
			case 2:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 40;
				break;
			case 3:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 15;
				break;
			case 4:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() - 40;
				break;
			}
		}
		else if (MeetsLBYReq && !lbyupdated)
		{
			switch (Globals::Shots % 4)
			{
			case 1:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y - 15;
				break;
			case 2:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y + 40;
				break;
			case 3:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y + 15;
				break;
			case 4:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y - 40;
				break;
			}
		}
		else
			pEntity->GetEyeAnglesXY()->y = rand() % 180 - rand() % 35;
	}
	else if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 2) //level 2 
	{
		if (Resolver::didhitHS)
		{
			if (MeetsLBYReq && lbyupdated)
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
			}
			switch (Globals::Shots % 6)
			{
			case 1:
				*pEntity->GetEyeAnglesXY() = StoredAngles[pEntity->GetIndex()];
				break;
			case 2:
				*pEntity->GetEyeAnglesXY() = StoredAngles[pEntity->GetIndex()];
				break;
			case 3:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() - 15;
				break;
			case 4:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y + 40;
				break;
			case 5:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y + 15;
				break;
			case 6:
				pEntity->GetEyeAnglesXY()->y = pEntity->GetEyeAnglesXY()->y - 40;
				break;
			}
		}
		else if (MeetsLBYReq && lbyupdated && !Resolver::didhitHS)
		{
			pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
		}
		else if (!MeetsLBYReq || !lbyupdated && !Resolver::didhitHS)
		{
			pEntity->GetEyeAnglesXY()->y = rand() % 180 - rand() % 35;
		}
		else
			pEntity->GetEyeAnglesXY()->y = rand() % 180;
	}
	else if (Menu::Window.RageBotTab.AimbotResolver.GetIndex() == 3)//level 3
	{
		if (Globals::missedshots > 3 && Globals::missedshots < 21)
		{
			if (MeetsLBYReq && lbyupdated)
			{
				pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw();
			}
			else if (!MeetsLBYReq && lbyupdated)
			{
				switch (Globals::Shots % 4)
				{
				case 1:
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() - 15;
					break;
				case 2:
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 40;
					break;
				case 3:
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() + 15;
					break;
				case 4:
					pEntity->GetEyeAnglesXY()->y = pEntity->GetLowerBodyYaw() - 40;
					break;
				}
			}
			else
				pEntity->GetEyeAnglesXY()->y = rand() % 180 - rand() % 35;
		}

		else if (Globals::missedshots >= 2 && Globals::missedshots <= 3)
		{
			if (MeetsLBYReq && lbyupdated)
			{
				pEntity->GetEyeAnglesXY()->y = ResolverSetup::finallbydelta[pEntity->GetIndex()];
			}
			else
				pEntity->GetEyeAnglesXY()->y = ResolverSetup::finaldelta[pEntity->GetIndex()];
		}
		else
		{
			if (MeetsLBYReq && lbyupdated)
			{
				bool timer = true;
				if (timer)
					pEntity->GetEyeAnglesXY()->y = ResolverSetup::finallbydelta[pEntity->GetIndex()] + rand() % 35;
				else
					pEntity->GetEyeAnglesXY()->y = ResolverSetup::finallbydelta[pEntity->GetIndex()] - rand() % 35;
				timer = !timer;
			}
			else
			{
				bool timer = true;
				if (timer)
					pEntity->GetEyeAnglesXY()->y = ResolverSetup::finaldelta[pEntity->GetIndex()] + rand() % 35;
				else
					pEntity->GetEyeAnglesXY()->y = ResolverSetup::finaldelta[pEntity->GetIndex()] - rand() % 35;
				timer = !timer;
			}
		}
	}
	LowerBodyYawFix(pEntity);
	PitchCorrection();
	*/


//not really needed
void CResolver::FSN(IClientEntity* pEntity, ClientFrameStage_t stage)
{
	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < Interfaces::Engine->GetMaxClients(); i++)
		{

			pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(i);

			if (!pEntity
				|| pEntity == hackManager.pLocal()
				|| pEntity->IsDormant()
				|| !pEntity->IsAlive())
				continue;

			CResolver::Resolve(pEntity);
		}
	}
}

void CResolver::CM(IClientEntity* pEntity)
{
	for (int x = 1; x < Interfaces::Engine->GetMaxClients(); x++)
	{

		pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(x);

		if (!pEntity
			|| pEntity == hackManager.pLocal()
			|| pEntity->IsDormant()
			|| !pEntity->IsAlive())
			continue;
	}
}
/*
void ResolverSetup::StoreThings(IClientEntity* pEntity)
{
	ResolverSetup::StoredAngles[pEntity->GetIndex()] = *pEntity->GetEyeAnglesXY();
	ResolverSetup::storedlby[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw();
	ResolverSetup::storedsimtime = pEntity->GetSimulationTime();
	ResolverSetup::storeddelta[pEntity->GetIndex()] = pEntity->GetEyeAnglesXY()->y;
	ResolverSetup::storedlby[pEntity->GetIndex()] = pEntity->GetLowerBodyYaw();
}

void ResolverSetup::StoreFGE(IClientEntity* pEntity)
{
	ResolverSetup::storedanglesFGE = pEntity->GetEyeAnglesXY()->y;
	ResolverSetup::storedlbyFGE = pEntity->GetLowerBodyYaw();
	ResolverSetup::storedsimtimeFGE = pEntity->GetSimulationTime();
}

void ResolverSetup::FSN(IClientEntity* pEntity, ClientFrameStage_t stage)
{
	if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		for (int i = 1; i < Interfaces::Engine->GetMaxClients(); i++)
		{

			pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(i);

			if (!pEntity
				|| pEntity == hackManager.pLocal()
				|| pEntity->IsDormant()
				|| !pEntity->IsAlive())
				continue;

			ResolverSetup::Resolve(pEntity);
		}
	}
}

void ResolverSetup::CM(IClientEntity* pEntity)
{
	for (int x = 1; x < Interfaces::Engine->GetMaxClients(); x++)
	{

		pEntity = (IClientEntity*)Interfaces::EntList->GetClientEntity(x);

		if (!pEntity
			|| pEntity == hackManager.pLocal()
			|| pEntity->IsDormant()
			|| !pEntity->IsAlive())
			continue;

		ResolverSetup::StoreThings(pEntity);
	}
}*/

/*
void PitchCorrection()
{
CUserCmd* pCmd;
for (int i = 0; i < Interfaces::Engine->GetMaxClients(); ++i)
{
IClientEntity* pLocal = hackManager.pLocal();
IClientEntity *player = (IClientEntity*)Interfaces::EntList->GetClientEntity(i);

if (!player || player->IsDormant() || player->GetHealth() < 1 || (DWORD)player == (DWORD)pLocal)
continue;

if (!player)
continue;

if (pLocal)
continue;

if (pLocal && player && pLocal->IsAlive())
{
if (Menu::Window.RageBotTab.AdvancedResolver.GetState())
{
Vector* eyeAngles = player->GetEyeAnglesXY();
if (eyeAngles->x < -179.f) eyeAngles->x += 360.f;
else if (eyeAngles->x > 90.0 || eyeAngles->x < -90.0) eyeAngles->x = 89.f;
else if (eyeAngles->x > 89.0 && eyeAngles->x < 91.0) eyeAngles->x -= 90.f;
else if (eyeAngles->x > 179.0 && eyeAngles->x < 181.0) eyeAngles->x -= 180;
else if (eyeAngles->x > -179.0 && eyeAngles->x < -181.0) eyeAngles->x += 180;
else if (fabs(eyeAngles->x) == 0) eyeAngles->x = std::copysign(89.0f, eyeAngles->x);
}
}
}
}

void LowerBodyYawFix(IClientEntity* pEntity)
{
if (Menu::Window.RageBotTab.LowerbodyFix.GetState())
{
if (!pEntity) return;
if (pEntity->GetClientClass()->m_ClassID != (int)CSGOClassID::CCSPlayer) return;
if (!pEntity->IsAlive() || !pEntity->GetActiveWeaponHandle()) return;
if (Interfaces::Engine->GetLocalPlayer()) return;

auto EyeAngles = pEntity->GetEyeAnglesXY();
if (pEntity->GetVelocity().Length() > 1 && (pEntity->GetFlags() & (int)pEntity->GetFlags() & FL_ONGROUND))
EyeAngles->y = pEntity->GetLowerBodyYaw();
}
}
*/