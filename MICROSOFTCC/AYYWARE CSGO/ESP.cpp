#include "ESP.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "GlowManager.h"
#include "Controls.h"
#include "MiscHacks.h"
#include "Hooks.h"
#include "Hacks.h"
#include <intrin.h>
#include "Menu.h"
#include "Gui.h"
#include "CRC32.h"
#include <WinUser.h>
#include "chams.h"
#include "iviewrender_beams.h"
#pragma region KeyBindersForList

char* KeyStringForList[254] = { nullptr, "Left Mouse", "Right Mouse", "Control+Break", "Middle Mouse", "Mouse 4", "Mouse 5",
nullptr, "Backspace", "TAB", nullptr, nullptr, nullptr, "ENTER", nullptr, nullptr, "SHIFT", "CTRL", "ALT", "PAUSE",
"CAPS LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "ESC", nullptr, nullptr, nullptr, nullptr, "SPACEBAR",
"PG UP", "PG DOWN", "END", "HOME", "Left", "Up", "Right", "Down", nullptr, "Print", nullptr, "Print Screen", "Insert",
"Delete", nullptr, "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X",
"Y", "Z", "Left Windows", "Right Windows", nullptr, nullptr, nullptr, "NUM 0", "NUM 1", "NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6",
"NUM 7", "NUM 8", "NUM 9", "*", "+", "_", "-", ".", "/", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
"F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24", nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, "NUM LOCK", "SCROLL LOCK", nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "LMENU", "RMENU", nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "Next Track", "Previous Track", "Stop", "Play/Pause", nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, ";", "+", ",", "-", ".", "/?", "~", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "[{", "\\|", "}]", "'\"", nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };

DWORD GlowManager = *(DWORD*)(Utilities::Memory::FindPatternV2("client.dll", "0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00") + 3);

#ifdef NDEBUG
#define strenc( s ) std::string( cx_make_encrypted_string( s ) )
#define charenc( s ) strenc( s ).c_str()
#define wstrenc( s ) std::wstring( strenc( s ).begin(), strenc( s ).end() )
#define wcharenc( s ) wstrenc( s ).c_str()
#else
#define strenc( s ) ( s )
#define charenc( s ) ( s )
#define wstrenc( s ) ( s )
#define wcharenc( s ) ( s )
#endif

#ifdef NDEBUG
#define XorStr( s ) ( XorCompileTime::XorString< sizeof( s ) - 1, __COUNTER__ >( s, std::make_index_sequence< sizeof( s ) - 1>() ).decrypt() )
#else
#define XorStr( s ) ( s )
#endif

#define MAXSTUDIOBONES 128
#include "lagcomp.h"
/*
void CEsp::drawBacktrackedSkelet(IClientEntity *base)
{
	IClientEntity *player = base;
	IClientEntity *locPlyr = hackManager.pLocal();
	if (!locPlyr)
		return;

	int idx = player->GetIndex();


	LagRecord_A *m_LagRecords = lagComp->m_LagRecord[idx];
	LagRecord_A recentLR = m_LagRecords[3];


	Vector screenSpot4;
	if (Render::WorldToScreen(recentLR.headSpot, screenSpot4))
	{
		if (player->GetTeamNum() != locPlyr->GetTeamNum())
			Render::fillRGBA(screenSpot4.x, screenSpot4.y, 3, 3, Color(255, 0, 235, 255));
	}



}
*/
void CEsp::Init()
{
	BombCarrier = nullptr;
}

void CEsp::Move(CUserCmd *pCmd,bool &bSendPacket) 
{
	//removed because anti ayyware paste Xd
}

void CEsp::Draw()
{
	IClientEntity *pLocal = hackManager.pLocal();
	PassiveList();
	Color Color;

	if (Menu::Window.VisualsTab.AntiAimLines.GetState())
	{
		DrawLinesAA(Color);

	}
	if (Menu::Window.VisualsTab.BulletTracers.GetState())
	{
		IViewRenderBeams *nigger;
		nigger->BulletTracers();
	}

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{
		IClientEntity *pEntity = Interfaces::EntList->GetClientEntity(i);
		player_info_t pinfo;

		if (pEntity &&  pEntity != pLocal && !pEntity->IsDormant())
		{
			if (Menu::Window.VisualsTab.OtherRadar.GetState())
			{
				DWORD m_bSpotted = NetVar.GetNetVar(0x839EB159);
				*(char*)((DWORD)(pEntity)+m_bSpotted) = 1;
			}

			if (Menu::Window.VisualsTab.FiltersPlayers.GetState() && Interfaces::Engine->GetPlayerInfo(i, &pinfo) && pEntity->IsAlive())
			{
				DrawPlayer(pEntity, pinfo);
			}

			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				if (cClass->m_ClassID == (int)CSGOClassID::CBaseCSGrenadeProjectile)
					DrawHE(pEntity, cClass);

				if (cClass->m_ClassID == (int)CSGOClassID::CMolotovProjectile)
					DrawMolotov(pEntity, cClass);

				if (cClass->m_ClassID == (int)CSGOClassID::CDecoyProjectile)
					DrawDecoy(pEntity, cClass);

				if (cClass->m_ClassID == (int)CSGOClassID::CSensorGrenadeProjectile)
					DrawMolotov(pEntity, cClass);

				if (cClass->m_ClassID == (int)CSGOClassID::CSmokeGrenadeProjectile)
					DrawSmoke(pEntity, cClass);
			}

			if (Menu::Window.VisualsTab.FiltersWeapons.GetState() && cClass->m_ClassID != (int)CSGOClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)CSGOClassID::CDEagle || cClass->m_ClassID == (int)CSGOClassID::CAK47)))
			{
				DrawDrop(pEntity, cClass);
			}

			if (Menu::Window.VisualsTab.FiltersC4.GetState())
			{
				if (cClass->m_ClassID == (int)CSGOClassID::CPlantedC4)
					DrawBombPlanted(pEntity, cClass);

				if (cClass->m_ClassID == (int)CSGOClassID::CC4)
					DrawBomb(pEntity, cClass);
			}

			if (Menu::Window.VisualsTab.FiltersChickens.GetState())
			{
				if (cClass->m_ClassID == (int)CSGOClassID::CChicken)
					DrawChicken(pEntity, cClass);
			}
		}
	}

	if (Menu::Window.VisualsTab.OtherNoFlash.GetState())
	{
		DWORD m_flFlashMaxAlpha = NetVar.GetNetVar(0xFE79FB98);
		*(float*)((DWORD)pLocal + m_flFlashMaxAlpha) = 0;
	}

	if (Menu::Window.VisualsTab.OptionsGlow.GetState())
	{
		DrawGlow();
	}
	if (Menu::Window.VisualsTab.EntityGlow.GetState())
	{
		EntityGlow();
	}

	if (Menu::Window.VisualsTab.GrenadeTrace.GetState())
	{
		GrenadeTrace();
	}
	if (Menu::Window.VisualsTab.LagCompensation.GetState())
	{
		LagCompensationSpoof();
	}
	

}

void CEsp::DrawPlayer(IClientEntity* pEntity, player_info_t pinfo)
{
	ESPBox Box;
	Color Color;
	
	
	if (Menu::Window.VisualsTab.FiltersEnemiesOnly.GetState() && (pEntity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()))
		return;

	if (GetBox(pEntity, Box))
	{
		Color = GetPlayerColor(pEntity);

		switch (Menu::Window.VisualsTab.OptionsBox.GetIndex())
		{
		case 0:
			break;
		case 1:
			DrawBox(Box, Color);
			break;
		case 2:
			FilledBox(Box, Color);
			break;
		case 3:
			Corners(Box, Color, pEntity);
			break;
		}

		switch (Menu::Window.VisualsTab.OptionsWeapon.GetIndex())
		{
		case 0:
			break;
		case 1:
			DrawWeapon(pEntity, Box);
			break;
		case 2:
			DrawIcon(pEntity, Box);
			break;
		}

		if (Menu::Window.VisualsTab.OptionsName.GetState())
			DrawName(pinfo, Box);

		if (Menu::Window.VisualsTab.OptionsHealth.GetState())
			DrawHealth(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsInfo.GetState())
			DrawInfo(pEntity, Box);

		if (Menu::Window.VisualsTab.OptionsArmor.GetState())
			Armor(pEntity, Box);

		if (Menu::Window.VisualsTab.Barrels.GetState())
			Barrel(Box, Color, pEntity);

		if (Menu::Window.VisualsTab.OptionsDefusing.GetState())
			IsPlayerDefusing(pinfo, Box, pEntity);

		if (Menu::Window.VisualsTab.OptionsAimSpot.GetState())
			DrawCross(pEntity);

		if (Menu::Window.VisualsTab.OptionsSkeleton.GetState())
			DrawSkeleton(pEntity);
		if (Menu::Window.VisualsTab.AngleChams.GetState())
			DrawAngleSkeletons(pEntity);

		if (Menu::Window.VisualsTab.Money.GetState())
			DrawMoney(pEntity, Box);

		if (Menu::Window.VisualsTab.Distance.GetState())
			DrawDistance(Box, pEntity);

		if (Menu::Window.VisualsTab.BulletTrace.GetState())
			BulletTrace(pEntity, Color);
		/*
		for (int i = 0; i < 64; i++)
		{
			 Entity *player = reinterpret_cast<Entity*>(p_ClientEntList->GetClientEntity(i)); 
			if (Menu::Window.VisualsTab.DiscoLights.GetState())
			{	
				
				player->Discolights(player);
			}
		}
		*/

		Info(pEntity, Box);
		

	}
}

bool CEsp::GetBox(IClientEntity* pEntity, CEsp::ESPBox &result)
{
	Vector  vOrigin, min, max, sMin, sMax, sOrigin,
		flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	vOrigin = pEntity->GetOrigin();
	min = pEntity->collisionProperty()->GetMins() + vOrigin;
	max = pEntity->collisionProperty()->GetMaxs() + vOrigin;

	Vector points[] = { Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z) };

	if (!Render::WorldToScreen(points[3], flb) || !Render::WorldToScreen(points[5], brt)
		|| !Render::WorldToScreen(points[0], blb) || !Render::WorldToScreen(points[4], frt)
		|| !Render::WorldToScreen(points[2], frb) || !Render::WorldToScreen(points[1], brb)
		|| !Render::WorldToScreen(points[6], blt) || !Render::WorldToScreen(points[7], flt))
		return false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	result.x = left;
	result.y = top;
	result.w = right - left;
	result.h = bottom - top;

	return true;
}

Color CEsp::GetPlayerColor(IClientEntity* pEntity)
{
	int TeamNum = pEntity->GetTeamNum();
	bool IsVis = GameUtils::IsVisible(hackManager.pLocal(), pEntity, (int)CSGOHitboxID::Head);

	Color color;

	if (TeamNum == TEAM_CS_T)
	{
		if (IsVis)
			color = Color(Menu::Window.ColorsTab.TColorVisR.GetValue(), Menu::Window.ColorsTab.TColorVisG.GetValue(), Menu::Window.ColorsTab.TColorVisB.GetValue(), 255);
		else
			color = Color(Menu::Window.ColorsTab.TColorNoVisR.GetValue(), Menu::Window.ColorsTab.TColorNoVisG.GetValue(), Menu::Window.ColorsTab.TColorNoVisB.GetValue(), 255);
	}
	else
	{
		if (IsVis)
			color = Color(Menu::Window.ColorsTab.CTColorVisR.GetValue(), Menu::Window.ColorsTab.CTColorVisG.GetValue(), Menu::Window.ColorsTab.CTColorVisB.GetValue(), 255);
		else
			color = Color(Menu::Window.ColorsTab.CTColorNoVisR.GetValue(), Menu::Window.ColorsTab.CTColorNoVisG.GetValue(), Menu::Window.ColorsTab.CTColorNoVisB.GetValue(), 255);
	}

	return color;
}

void CEsp::Corners(CEsp::ESPBox size, Color color, IClientEntity* pEntity)
{
	int VertLine = (((float)size.w) * (0.20f));
	int HorzLine = (((float)size.h) * (0.30f));

	Render::Clear(size.x, size.y - 1, VertLine, 1, Color(0, 0, 0, 255));
	Render::Clear(size.x + size.w - VertLine, size.y - 1, VertLine, 1, Color(0, 0, 0, 255));
	Render::Clear(size.x, size.y + size.h - 1, VertLine, 1, Color(0, 0, 0, 255));
	Render::Clear(size.x + size.w - VertLine, size.y + size.h - 1, VertLine, 1, Color(0, 0, 0, 255));

	Render::Clear(size.x - 1, size.y, 1, HorzLine, Color(0, 0, 0, 255));
	Render::Clear(size.x - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(0, 0, 0, 255));
	Render::Clear(size.x + size.w - 1, size.y, 1, HorzLine, Color(0, 0, 0, 255));
	Render::Clear(size.x + size.w - 1, size.y + size.h - HorzLine, 1, HorzLine, Color(0, 0, 0, 255));

	Render::Clear(size.x, size.y, VertLine, 1, color);
	Render::Clear(size.x + size.w - VertLine, size.y, VertLine, 1, color);
	Render::Clear(size.x, size.y + size.h, VertLine, 1, color);
	Render::Clear(size.x + size.w - VertLine, size.y + size.h, VertLine, 1, color);

	Render::Clear(size.x, size.y, 1, HorzLine, color);
	Render::Clear(size.x, size.y + size.h - HorzLine, 1, HorzLine, color);
	Render::Clear(size.x + size.w, size.y, 1, HorzLine, color);
	Render::Clear(size.x + size.w, size.y + size.h - HorzLine, 1, HorzLine, color);
}

void CEsp::FilledBox(CEsp::ESPBox size, Color color)
{
	int VertLine = (((float)size.w) * (0.20f));
	int HorzLine = (((float)size.h) * (0.20f));

	Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(0, 0, 0, 40));
	Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(0, 0, 0, 40));
	Render::Clear(size.x, size.y, VertLine, 1, color);
	Render::Clear(size.x + size.w - VertLine, size.y, VertLine, 1, color);
	Render::Clear(size.x, size.y + size.h, VertLine, 1, color);
	Render::Clear(size.x + size.w - VertLine, size.y + size.h, VertLine, 1, color);
	Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(0, 0, 0, 40));
	Render::Clear(size.x, size.y, 1, HorzLine, color);
	Render::Clear(size.x, size.y + size.h - HorzLine, 1, HorzLine, color);
	Render::Clear(size.x + size.w, size.y, 1, HorzLine, color);
	Render::Clear(size.x + size.w, size.y + size.h - HorzLine, 1, HorzLine, color);
	Render::Clear(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(0, 0, 0, 40));
}

void CEsp::DrawBox(CEsp::ESPBox size, Color color)
{
	Render::Outline(size.x, size.y, size.w, size.h, color);
	Render::Outline(size.x - 1, size.y - 1, size.w + 2, size.h + 2, Color(10, 10, 10, 150));
	Render::Outline(size.x + 1, size.y + 1, size.w - 2, size.h - 2, Color(10, 10, 10, 150));
}

void CEsp::Barrel(CEsp::ESPBox size, Color color, IClientEntity* pEntity)
{
	Vector src3D, src;
	src3D = pEntity->GetOrigin() - Vector(0, 0, 0);

	if (!Render::WorldToScreen(src3D, src))
		return;

	int ScreenWidth, ScreenHeight;
	Interfaces::Engine->GetScreenSize(ScreenWidth, ScreenHeight);

	int x = (int)(ScreenWidth * 0.5f);
	int y = 0;


	y = ScreenHeight;

	Render::Line((int)(src.x), (int)(src.y), x, y, Color(0, 255, 0, 255));
}

void CEsp::DrawWeapon(IClientEntity* pEntity, CEsp::ESPBox size)
{
	IClientEntity* pWeapon = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)pEntity->GetActiveWeaponHandle());
	if (Menu::Window.VisualsTab.OptionsWeapon.GetIndex() == 1 && pWeapon)
	{
		RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pWeapon->GetpWeaponName());
		Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + size.h + 8,
			Color(255, 255, 255, 255), Render::Fonts::ESP, pWeapon->GetpWeaponName());
	}
}

void CEsp::DrawIcon(IClientEntity* pEntity, CEsp::ESPBox size)
{
	IClientEntity* pWeapon = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)pEntity->GetActiveWeaponHandle());
	if (Menu::Window.VisualsTab.OptionsWeapon.GetIndex() == 2 && pWeapon)
	{
		RECT nameSize = Render::GetTextSize(Render::Fonts::Icon, pWeapon->GetGunIcon());
		Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y + size.h + 8,
			Color(255, 255, 255, 255), Render::Fonts::Icon, pWeapon->GetGunIcon());
	}
}

void CEsp::DrawGlow()
{
	int GlowR = Menu::Window.ColorsTab.GlowR.GetValue();
	int GlowG = Menu::Window.ColorsTab.GlowG.GetValue();
	int GlowB = Menu::Window.ColorsTab.GlowB.GetValue();
	int GlowZ = Menu::Window.VisualsTab.GlowZ.GetValue();

	CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)GlowManager;

	for (int i = 0; i < GlowObjectManager->size; ++i)
	{
		CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		IClientEntity* Entity = glowEntity->getEntity();

		if (glowEntity->IsEmpty() || !Entity)
			continue;

		switch (Entity->GetClientClass()->m_ClassID)
		{
		case 35:
			if (Menu::Window.VisualsTab.OptionsGlow.GetState())
			{
				if (!Menu::Window.VisualsTab.FiltersPlayers.GetState() && !(Entity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()))
					break;
				if (Menu::Window.VisualsTab.FiltersEnemiesOnly.GetState() && (Entity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()))
					break;

				if (GameUtils::IsVisible(hackManager.pLocal(), Entity, 0))
				{
					glowEntity->set((Entity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()) ? Color(GlowR, GlowG, GlowB, GlowZ) : Color(GlowR, GlowG, GlowB, GlowZ));
				}

				else
				{
					glowEntity->set((Entity->GetTeamNum() == hackManager.pLocal()->GetTeamNum()) ? Color(GlowR, GlowG, GlowB, GlowZ) : Color(GlowR, GlowG, GlowB, GlowZ));
				}
			}
		}
	}
}

void CEsp::EntityGlow()
{
	int GlowR = Menu::Window.ColorsTab.GlowR.GetValue();
	int GlowG = Menu::Window.ColorsTab.GlowG.GetValue();
	int GlowB = Menu::Window.ColorsTab.GlowB.GetValue();
	int GlowZ = Menu::Window.VisualsTab.GlowZ.GetValue();

	CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)GlowManager;

	for (int i = 0; i < GlowObjectManager->size; ++i)
	{
		CGlowObjectManager::GlowObjectDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		IClientEntity* Entity = glowEntity->getEntity();

		if (glowEntity->IsEmpty() || !Entity)
			continue;

		switch (Entity->GetClientClass()->m_ClassID)
		{
		case 1:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				if (Menu::Window.VisualsTab.EntityGlow.GetState())
					glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 9:
			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				if (Menu::Window.VisualsTab.EntityGlow.GetState())
					glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 29:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 39:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				if (Menu::Window.VisualsTab.FiltersC4.GetState())
					glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 41:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 66:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 87:
			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 98:
			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 108:
			if (Menu::Window.VisualsTab.FiltersC4.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 130:
			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		case 134:
			if (Menu::Window.VisualsTab.FiltersNades.GetState())
			{
				glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		default:
			if (Menu::Window.VisualsTab.EntityGlow.GetState())
			{
				if (strstr(Entity->GetClientClass()->m_pNetworkName, "Weapon"))
					glowEntity->set(Color(GlowR, GlowG, GlowB, GlowZ));
			}
		}
	}
}

static wchar_t* CharToWideChar(const char* text)
{
	size_t size = strlen(text) + 1;
	wchar_t* wa = new wchar_t[size];
	mbstowcs_s(NULL, wa, size/4, text, size);
	return wa;
}

void CEsp::DrawName(player_info_t pinfo, CEsp::ESPBox size)
{
	RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, pinfo.name);
	Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 16,
		Color(255, 255, 255, 255), Render::Fonts::ESP, pinfo.name);
}

void CEsp::DrawHealth(IClientEntity* pEntity, CEsp::ESPBox size)
{
	int HPEnemy = 100;
	HPEnemy = pEntity->GetHealth();
	char nameBuffer[512];
	sprintf_s(nameBuffer, "%d", HPEnemy);


	float h = (size.h);
	float offset = (h / 4.f) + 5;
	float w = h / 64.f;
	float health = pEntity->GetHealth();
	UINT hp = h - (UINT)((h * health) / 100);

	int Red = 255 - (health*2.55);
	int Green = health*2.55;

	Render::DrawOutlinedRect((size.x - 6) - 1, size.y - 1, 3, h + 2, Color(0, 0, 0, 180));

	Render::DrawLine((size.x - 6), size.y + hp, (size.x - 6), size.y + h, Color(Red, Green, 0, 180));

	if (health < 100) {

		Render::Text(size.x - 9, size.y + hp, Color(255, 255, 255, 255), Render::Fonts::ESP, nameBuffer);
	}
}

std::string CleanItemName(std::string name)
{
	std::string Name = name;
	if (Name[0] == 'C')
		Name.erase(Name.begin());

	auto startOfWeap = Name.find("Weapon");
	if (startOfWeap != std::string::npos)
		Name.erase(Name.begin() + startOfWeap, Name.begin() + startOfWeap + 6);

	return Name;
}

void CEsp::DrawInfo(IClientEntity* pEntity, CEsp::ESPBox size)
{
	std::vector<std::string> Info;

	if (Menu::Window.VisualsTab.OptionsInfo.GetState() && pEntity == BombCarrier)
	{
		Info.push_back("Bomb Carrier");
	}

	static RECT Size = Render::GetTextSize(Render::Fonts::Default, "Hi");
	int i = 0;
	for (auto Text : Info)
	{
		Render::Text(size.x + size.w + 3, size.y + (i*(Size.bottom + 2)), Color(255, 255, 255, 255), Render::Fonts::ESP, Text.c_str());
		i++;
	}
}

void CEsp::DrawCross(IClientEntity* pEntity)
{
	Vector cross = pEntity->GetHeadPos(), screen;
	static int Scale = 2;
	if (Render::WorldToScreen(cross, screen))
	{
		Render::Clear(screen.x - Scale, screen.y - (Scale * 2), (Scale * 2), (Scale * 4), Color(20, 20, 20, 160));
		Render::Clear(screen.x - (Scale * 2), screen.y - Scale, (Scale * 4), (Scale * 2), Color(20, 20, 20, 160));
		Render::Clear(screen.x - Scale - 1, screen.y - (Scale * 2) - 1, (Scale * 2) - 2, (Scale * 4) - 2, Color(250, 250, 250, 160));
		Render::Clear(screen.x - (Scale * 2) - 1, screen.y - Scale - 1, (Scale * 4) - 2, (Scale * 2) - 2, Color(250, 250, 250, 160));
	}
}

void CEsp::DrawDrop(IClientEntity* pEntity, ClientClass* cClass)
{
	Vector Box;
	IClientEntity* Weapon = (IClientEntity*)pEntity;
	IClientEntity* plr = Interfaces::EntList->GetClientEntityFromHandle((HANDLE)Weapon->GetOwnerHandle());
	if (!plr && Render::WorldToScreen(Weapon->GetOrigin(), Box))
	{
		if (Menu::Window.VisualsTab.FiltersWeapons.GetState())
		{
			Render::Outline(Box.x - 6, Box.y - 6, 12, 12, Color(255, 255, 255, 255));
		}
		if (Menu::Window.VisualsTab.FiltersWeapons.GetState())
		{
			RECT TextSize = Render::GetTextSize(Render::Fonts::Icon, Weapon->GetGunIcon());
			Render::Text(Box.x - (TextSize.right / 1), Box.y - 16, Color(255, 255, 255, 255), Render::Fonts::Icon, Weapon->GetGunIcon());
		}
	}
}

void CEsp::DrawChicken(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Chicken");
		if (Menu::Window.VisualsTab.FiltersChickens.GetState())
			DrawBox(Box, Color(255,255,255,255));

		if (Menu::Window.VisualsTab.FiltersChickens.GetState())
			DrawName(pinfo, Box);
	}
}

void CEsp::DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass) 
{
	BombCarrier = nullptr;

	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	CCSBomb* Bomb = (CCSBomb*)pEntity;

	if (Render::WorldToScreen(vOrig, vScreen))
	{
		float flBlow = Bomb->GetC4BlowTime();
		float TimeRemaining = flBlow - (Interfaces::Globals->interval_per_tick * hackManager.pLocal()->GetTickBase());
		char buffer[64];
		sprintf_s(buffer, "explodes in %.1f", TimeRemaining);
		Render::Text(vScreen.x, vScreen.y, Color(255, 255, 255, 255), Render::Fonts::ESP, buffer);
	}
}

void CEsp::DrawBomb(IClientEntity* pEntity, ClientClass* cClass)
{
	BombCarrier = nullptr;
	CBaseCombatWeapon *BombWeapon = (CBaseCombatWeapon *)pEntity;
	Vector vOrig; Vector vScreen;
	vOrig = pEntity->GetOrigin();
	bool adopted = true;
	HANDLE parent = BombWeapon->GetOwnerHandle();
	if (parent || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
	{
		IClientEntity* pParentEnt = (Interfaces::EntList->GetClientEntityFromHandle(parent));
		if (pParentEnt && pParentEnt->IsAlive())
		{
			BombCarrier = pParentEnt;
			adopted = false;
		}
	}

	if (adopted)
	{
		if (Render::WorldToScreen(vOrig, vScreen))
		{
			Render::Text(vScreen.x, vScreen.y, Color(112, 230, 20, 255), Render::Fonts::ESP, "Bomb");
		}
	}
}

void DrawBoneArray(int* boneNumbers, int amount, IClientEntity* pEntity, Color color)
{
	Vector LastBoneScreen;
	for (int i = 0; i < amount; i++)
	{
		Vector Bone = pEntity->GetBonePos(boneNumbers[i]);
		Vector BoneScreen;

		if (Render::WorldToScreen(Bone, BoneScreen))
		{
			if (i>0)
			{
				Render::Line(LastBoneScreen.x, LastBoneScreen.y, BoneScreen.x, BoneScreen.y, color);
			}
		}
		LastBoneScreen = BoneScreen;
	}
}

void DrawBoneTest(IClientEntity *pEntity)
{
	for (int i = 0; i < 127; i++)
	{
		Vector BoneLoc = pEntity->GetBonePos(i);
		Vector BoneScreen;
		if (Render::WorldToScreen(BoneLoc, BoneScreen))
		{
			char buf[10];
			_itoa_s(i, buf, 10);
			Render::Text(BoneScreen.x, BoneScreen.y, Color(255, 255, 255, 180), Render::Fonts::ESP, buf);
		}
	}
}

void CEsp::DrawSkeleton(IClientEntity* pEntity)
{
	studiohdr_t* pStudioHdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (int j = 0; j < pStudioHdr->numbones; j++)
	{
		mstudiobone_t* pBone = pStudioHdr->GetBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEntity->GetBonePos(j);
			vParent = pEntity->GetBonePos(pBone->parent);

			if (Render::WorldToScreen(vParent, sParent) && Render::WorldToScreen(vChild, sChild))
			{
				Render::Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255,255,255,255));
			}
		}
	}
}

void CEsp::DrawAngleSkeletons(IClientEntity* pEntity)
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	CUserCmd* pCmd;
	PVOID pebp;
	__asm mov pebp, ebp;
	bool* pbSendPacket = (bool*)(*(DWORD*)pebp - 0x1C);
	bool& bSendPacket = *pbSendPacket;
	vec_t LBYvec, Fakevec;
	LBYvec = pLocal->GetLowerBodyYaw();
	if (bSendPacket == true)
	{
		Fakevec = pCmd->viewangles.y;
	}
	Vector vParent, vChild, sParent, sChild;
	studiohdr_t* pStudioHdr = Interfaces::ModelInfo->GetStudiomodel(pEntity->GetModel());

	if (!pStudioHdr)
		return;


	
	/*if (pLocal && Menu::Window.MiscTab.OtherThirdperson.GetState())
	{
		for (int j = 0; j < pStudioHdr->numbones; j++)
		{
			mstudiobone_t* pBone = pStudioHdr->GetBone(j);
			if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
			{
				vChild = pEntity->GetBonePosForCustomAngle(j, Vector(0, LBYvec, 0));
				vParent = pEntity->GetBonePosForCustomAngle(pBone->parent, Vector(0, LBYvec, 0));
				if (Render::WorldToScreen(vParent, sParent) && Render::WorldToScreen(vChild, sChild))
				{
					Render::Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(210, 105, 30, 255));
				}
			}
		}
		for (int j = 0; j < pStudioHdr->numbones; j++)
		{
			mstudiobone_t* pBone = pStudioHdr->GetBone(j);
			if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
			{
				vChild = pEntity->GetBonePosForCustomAngle(j, Vector(0, Fakevec, 0));
				vParent = pEntity->GetBonePosForCustomAngle(pBone->parent, Vector(0, Fakevec, 0));
				if (Render::WorldToScreen(vParent, sParent) && Render::WorldToScreen(vChild, sChild))
				{
					Render::Line(sParent[0], sParent[1], sChild[0], sChild[1], Color(255, 0, 0, 255));
				}
			}
		}
	}
	*/
}
void CEsp::DrawLinesAA(Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	filter.pSkip = hackManager.pLocal();

	// LBY
	AngleVectors(QAngle(0, lineLBY, 0), &forward);
	src3D = hackManager.pLocal()->GetOrigin();
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(210, 105, 30, 255));
	// REAL AGNEL
	AngleVectors(QAngle(0, lineRealAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));

	// Fake AGNEL
	AngleVectors(QAngle(0, lineFakeAngle, 0), &forward);
	dst3D = src3D + (forward * 50.f); //replace 50 with the length you want the line to have

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, 0, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::Line(src.x, src.y, dst.x, dst.y, Color(255, 0, 0, 255));
}

void CEsp::IsPlayerDefusing(player_info_t pinfo, CEsp::ESPBox size, IClientEntity* pEntity)
{
	RECT defSize = Render::GetTextSize(Render::Fonts::ESP, "");
	if (pEntity->IsDefusing())
	{
		Render::Text(size.x + size.w + 3, size.y + (0.3*(defSize.bottom + 15)),
			Color(255, 0, 0, 255), Render::Fonts::ESP, charenc("Defusing"));
	}
}

void CEsp::DrawMoney(IClientEntity* pEntity, CEsp::ESPBox size)
{
	ESPBox ArmorBar = size;

	int MoneyEnemy = 100;
	MoneyEnemy = pEntity->GetMoney();
	char nameBuffer[512];
	sprintf_s(nameBuffer, "%d $", MoneyEnemy);

	RECT nameSize = Render::GetTextSize(Render::Fonts::ESP, nameBuffer);
	Render::Text(size.x + (size.w / 2) - (nameSize.right / 2), size.y - 27, Color(255, 255, 0, 255), Render::Fonts::ESP, nameBuffer);
}

void CEsp::Armor(IClientEntity* pEntity, CEsp::ESPBox size)
{
	ESPBox ArBar = size;
	ArBar.y += (ArBar.h + 3);
	ArBar.h = 6;

	float ArValue = pEntity->ArmorValue();
	float ArPerc = ArValue / 100.f;
	float Width = (size.w * ArPerc);
	ArBar.w = Width;

	Vertex_t Verts[4];
	Verts[0].Init(Vector2D(ArBar.x, ArBar.y));
	Verts[1].Init(Vector2D(ArBar.x + size.w + 0, ArBar.y));
	Verts[2].Init(Vector2D(ArBar.x + size.w, ArBar.y + 2));
	Verts[3].Init(Vector2D(ArBar.x - 0, ArBar.y + 2));

	Render::PolygonOutline(4, Verts, Color(50, 50, 50, 255), Color(50, 50, 50, 255));

	Vertex_t Verts2[4];
	Verts2[0].Init(Vector2D(ArBar.x, ArBar.y + 1));
	Verts2[1].Init(Vector2D(ArBar.x + ArBar.w + 0, ArBar.y + 1));
	Verts2[2].Init(Vector2D(ArBar.x + ArBar.w, ArBar.y + 2));
	Verts2[3].Init(Vector2D(ArBar.x, ArBar.y + 2));

	Color c = GetPlayerColor(pEntity);
	Render::Polygon(4, Verts2, Color(0, 120, 255, 200));
}


void CEsp::DrawMolotov(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Fire");

		if (Menu::Window.VisualsTab.FiltersNades.GetState())
			DrawName(pinfo, Box);
	}
}

void CEsp::DrawSmoke(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Smoke");

		if (Menu::Window.VisualsTab.FiltersNades.GetState() == 1)
			DrawName(pinfo, Box);
	}
}

void CEsp::DrawDecoy(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "Decoy");

		if (Menu::Window.VisualsTab.FiltersNades.GetState())
			DrawName(pinfo, Box);
	}
}

void CEsp::DrawHE(IClientEntity* pEntity, ClientClass* cClass)
{
	ESPBox Box;

	if (GetBox(pEntity, Box))
	{
		player_info_t pinfo; strcpy_s(pinfo.name, "HE or Flash");

		if (Menu::Window.VisualsTab.FiltersNades.GetState())
			DrawName(pinfo, Box);
	}
}

void CEsp::Info(IClientEntity* pEntity, CEsp::ESPBox size)
{
	std::vector<std::string> Info;

	if (Menu::Window.VisualsTab.HasDefuser.GetState() && pEntity->HasDefuser())
	{
		Info.push_back("Has Defuser");
	}

	if (Menu::Window.VisualsTab.IsScoped.GetState() && pEntity->IsScoped())
	{
		Info.push_back("Scoped");
	}

	static RECT Size = Render::GetTextSize(Render::Fonts::ESP, "Hi");
	int i = 0;
	for (auto Text : Info)
	{
		Render::Text(size.x + size.w + 3, size.y + (i*(Size.bottom + 2)), Color(255, 255, 255, 255), Render::Fonts::ESP, Text.c_str());
		i++;
	}
}

void CEsp::GrenadeTrace()
{
	auto granade = Interfaces::CVar->FindVar("sv_grenade_trajectory");
	auto granadespoof = new SpoofedConvar(granade);
	granadespoof->SetInt(1);
}

void CEsp::DrawDistance(CEsp::ESPBox size, IClientEntity* pEntity)
{
	IClientEntity *pLocal = hackManager.pLocal();

	Vector vecOrigin = pEntity->GetOrigin();
	Vector vecOriginLocal = pLocal->GetOrigin();
	static RECT defSize = Render::GetTextSize(Render::Fonts::Default, "");

	char dist_to[32];
	sprintf_s(dist_to, "%.0f ft", DistanceTo(vecOriginLocal, vecOrigin));

	Render::Text(size.x + size.w + 3, size.y + (0.6*(defSize.bottom + 28)), Color(255, 255, 255, 255), Render::Fonts::ESP, dist_to);
}

float CEsp::DistanceTo(Vector vecSrc, Vector vecDst)
{
	Vector vDelta = vecDst - vecSrc;

	float fDistance = ::sqrtf((vDelta.Length()));

	if (fDistance < 1.0f)
		return 1.0f;

	return fDistance;
}

void CEsp::BulletTrace(IClientEntity* pEntity, Color color)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	AngleVectors(pEntity->GetEyeAngles(), &forward);
	filter.pSkip = pEntity;
	src3D = pEntity->GetBonePos(6) - Vector(0, 0, 0);
	dst3D = src3D + (forward * Menu::Window.VisualsTab.BulletTraceLength.GetValue());

	ray.Init(src3D, dst3D);

	Interfaces::Trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (!Render::WorldToScreen(src3D, src) || !Render::WorldToScreen(tr.endpos, dst))
		return;

	Render::DrawLine(src.x, src.y, dst.x, dst.y, color);
	Render::DrawOutlinedRect(dst.x - 3, dst.y - 3, 6, 6, color);
}

Offsets2 offs;

Vector3 Entity::getViewOriginal2()
{
	return *(Vector3*)((DWORD)this + offs.viewOriginal);
}

GlobVars *p_GlobVars = nullptr;
IVEffects *p_IVEffects = nullptr;

int Entity::getIdx()
{
	void *netwable = (void*)((DWORD)(this) + 0x8);
	typedef int(__thiscall *o_GetIdx)(void*);
	return VT::vfunc<o_GetIdx>(netwable, 10)(netwable);
}

int Entity::getTeam()
{
	return *(int*)((DWORD)this + offs.entTeam);
}

void Entity::Discolights(Entity *base)
{
	
	Entity *player = base;
	bool playerTeam = player->getTeam() == 2;

	dlight_t *dLight = nullptr;
	dLight = p_IVEffects->CL_AllocDlight(player->getIdx());
	
	if (Menu::Window.VisualsTab.DLights.GetState())
	{
		if (playerTeam)
		{
			
			dLight->origin = player->getViewOriginal2();
			dLight->radius = 75.f;
			dLight->color.r = 255;
			dLight->color.g = 0;
			dLight->color.b = 0;
			dLight->color.exponent = 10.f;
			dLight->die = p_GlobVars->curtime + 0.05f;
			dLight->decay = dLight->radius / 5.0f;
			dLight->key = player->getIdx();
		}
		else
		{
			dLight->origin = player->getViewOriginal2();
			dLight->radius = 75.f;
			dLight->color.r = 0;
			dLight->color.g = 0;
			dLight->color.b = 255;
			dLight->color.exponent = 10.f;
			dLight->die = p_GlobVars->curtime + 0.05f;
			dLight->decay = dLight->radius / 5.0f;
			dLight->key = player->getIdx();
		}
	
	}
}

extern Entity *entity;



void CEsp::LagCompensationSpoof()
{
	if (Menu::Window.VisualsTab.LagCompensation.GetState())
	{
		try
		{
			auto lag = Interfaces::CVar->FindVar("sv_showlagcompensation"); //might not work or cause untrusted lol
			auto lagspoof = new SpoofedConvar(lag);
			lagspoof->SetInt(1);
		}
		catch (int err)
		{
			MessageBoxW(NULL, L"Could not manipulate CVar", L"Error", MB_OK);
		}
	}
}

int CEsp::GetTextPositionInList(int line)
{
	return line * 15;
}

void CEsp::PassiveList()
{
	//sets a list of main active hacks styled like x88 or pp-multi
	//initializing some stuff
	Listbase base;
	base.x = 300;
	base.y = 60;
	Color Activated, Passive, Main, Submain;
	Activated = Color(0, 255, 0, 255);
	Passive = Color(255, 0, 0, 255);
	Main = Color(255, 255, 255, 255);
	Submain = Color(0, 0, 255, 255);
	int tab = 120; // when putting text after the :

	Render::Text(base.x, base.y + GetTextPositionInList(0), Main, Render::Fonts::List, "Active Hacks:");


	//Ragebot
	Render::Text(base.x, base.y + GetTextPositionInList(1), Main, Render::Fonts::List, "HvH Settings:");
	if (Menu::Window.RageBotTab.Active.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(1), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(1), Passive, Render::Fonts::List, "Off");
	}
	Render::Text(base.x, base.y + GetTextPositionInList(2), Main, Render::Fonts::List, "Fake AntiAim:");
	switch (Menu::Window.RageBotTab.FakeYaw.GetIndex())
	{
	case 0:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Passive, Render::Fonts::List, "Off");
		break;
	case 1:
		// Fast Spin 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Fast Spin");
		break;
	case 2:
		// Slow Spin 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Slow Spin");
		break;
	case 3:
		// Jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Jitter");
		break;
	case 4:
		// 180 Jitter 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "180 Jitter");
		break;
	case 5:
		// backwards
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Backwards");
		break;
	case 6:
		// backwards jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Backwards Jitter");
		break;
	case 7:
		// Sideways-switch
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Sideways Switch");
		break;
	case 8:
		// Sideways Right
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Sideways Right");
		break;
	case 9:
		// Sideways Left
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Sideways Left");
		break;
	case 10:
		// LBY
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY");
		break;
	case 11:
		// LBY jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY Jitter");
		break;
	case 12:
		// Fake LBY Sideways
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY Sideways");
		break;
	case 13:
		// LBY Spin
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY Spin");
		break;
	case 14:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY Break");
		break;
	case 15:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "LBY Spin 2");
		break;
	case 16:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Tank AA");
		break;
	case 17:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Tank AA 2");
		break;
	case 18:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Tank AA 3");
		break;
	case 19:
		// Eyeangles
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Eye Angles");
		break;
	case 20:
		// Eyeangles - 180
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Eye Angles Reversed");
		break;
	}

	Render::Text(base.x, base.y + GetTextPositionInList(3), Main, Render::Fonts::List, "Real AntiAim:");
	switch (Menu::Window.RageBotTab.AntiAimYaw.GetIndex())
	{
	case 0:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Passive, Render::Fonts::List, "Off");
		break;
	case 1:
		// Fast Spin 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Fast Spin");
		break;
	case 2:
		// Slow Spin 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Slow Spin");
		break;
	case 3:
		// Jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Jitter");
		break;
	case 4:
		// 180 Jitter 
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "180 Jitter");
		break;
	case 5:
		// backwards
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Backwards");
		break;
	case 6:
		// backwards jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Backwards Jitter");
		break;
	case 7:
		// Sideways-switch
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Sideways Switch");
		break;
	case 8:
		// Sideways Right
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Sideways Right");
		break;
	case 9:
		// Sideways Left
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Sideways Left");
		break;
	case 10:
		// LBY
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY");
		break;
	case 11:
		// LBY jitter
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY Jitter");
		break;
	case 12:
		// Fake LBY Sideways
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY Sideways");
		break;
	case 13:
		// LBY Spin
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY Spin");
		break;
	case 14:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY Break");
		break;
	case 15:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "LBY Spin 2");
		break;
	case 16:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Tank AA");
		break;
	case 17:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Tank AA 2");
		break;
	case 18:
		// LBY Break
		Render::Text(base.x + tab, base.y + GetTextPositionInList(3), Submain, Render::Fonts::List, "Tank AA 3");
		break;
	case 19:
		// Eyeangles
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Eye Angles");
		break;
	case 20:
		// Eyeangles - 180
		Render::Text(base.x + tab, base.y + GetTextPositionInList(2), Submain, Render::Fonts::List, "Eye Angles Reversed");
		break;
	}
	Render::Text(base.x, base.y + GetTextPositionInList(4), Main, Render::Fonts::List, "Resolver:");
	switch (Menu::Window.RageBotTab.AimbotResolver.GetIndex())
	{
	case 0:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(4), Passive, Render::Fonts::List, "Off");
		break;
	case 1:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(4), Submain, Render::Fonts::List, "Level 1");
		break;
	case 2:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(4), Submain, Render::Fonts::List, "Level 2");
		break;
	case 3:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(4), Submain, Render::Fonts::List, "Level 3");
		break;
	case 4:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(4), Submain, Render::Fonts::List, "Level 4");
		break;
	}
	Render::Text(base.x, base.y + GetTextPositionInList(5), Main, Render::Fonts::List, "Hitchance:");

	char hitchance[32];
	sprintf_s(hitchance, "%.0f", Menu::Window.RageBotTab.AccuracyHitchance.GetValue());
	Render::Text(base.x + tab, base.y + GetTextPositionInList(5), Submain, Render::Fonts::List, hitchance);

	Render::Text(base.x, base.y + GetTextPositionInList(6), Main, Render::Fonts::List, "Autowall");
	if (Menu::Window.RageBotTab.AccuracyAutoWall.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(6), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(6), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(7), Main, Render::Fonts::List, "Min Autowall:");
	char autowalldmg[32];
	sprintf_s(autowalldmg, "%.0f", Menu::Window.RageBotTab.AccuracyMinimumDamage.GetValue());
	Render::Text(base.x + tab, base.y + GetTextPositionInList(7), Submain, Render::Fonts::List, autowalldmg);

	Render::Text(base.x, base.y + GetTextPositionInList(8), Main, Render::Fonts::List, "FOV:");
	char fov[32];
	sprintf_s(fov, "%.0f", Menu::Window.RageBotTab.AimbotFov.GetValue());
	Render::Text(base.x + tab, base.y + GetTextPositionInList(8), Submain, Render::Fonts::List, fov);

	Render::Text(base.x, base.y + GetTextPositionInList(9), Main, Render::Fonts::List, "Autofire:");
	if (Menu::Window.RageBotTab.AimbotAutoFire.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(9), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(9), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(10), Main, Render::Fonts::List, "Silent Aim:");
	if (Menu::Window.RageBotTab.AimbotSilentAim.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(10), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(10), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(11), Main, Render::Fonts::List, "Auto Revolver:");
	if (Menu::Window.RageBotTab.AutoRevolver.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(11), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(11), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(12), Main, Render::Fonts::List, "Hitscan:");
	switch (Menu::Window.RageBotTab.TargetHitscan.GetIndex())
	{
	case 0:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(12), Passive, Render::Fonts::List, "Off");
		break;
	case 1:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(12), Submain, Render::Fonts::List, "Low");
		break;
	case 2:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(12), Submain, Render::Fonts::List, "Medium");
		break;
	case 3:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(12), Submain, Render::Fonts::List, "High");
		break;
	}

	Render::Text(base.x, base.y + GetTextPositionInList(13), Main, Render::Fonts::List, "Fakelag:"); // 28
	if (Menu::Window.MiscTab.FakeLagEnable.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(13), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(13), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(14), Main, Render::Fonts::List, "Choke:"); //29
	char chokefactor[32];
	sprintf_s(chokefactor, "%.0f", Menu::Window.MiscTab.FakeLagChoke.GetValue());
	Render::Text(base.x + tab, base.y + GetTextPositionInList(14), Submain, Render::Fonts::List, chokefactor);

	Render::Text(base.x, base.y + GetTextPositionInList(15), Main, Render::Fonts::List, "Type:"); //30
	switch (Menu::Window.MiscTab.FakeLagTyp.GetIndex())
	{
	case 0:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Off");
		break;
	case 1:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Normal");
		break;
	case 2:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Adaptive");
		break;
	case 3:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Normal - In air");
		break;
	case 4:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Adaptive - In air");
		break;
	case 5:
		Render::Text(base.x + tab, base.y + GetTextPositionInList(15), Submain, Render::Fonts::List, "Normal - Break");
		break;
	}
	
	Render::Text(base.x, base.y + GetTextPositionInList(16), Main, Render::Fonts::List, "Anti-Untrust:"); //32
	if (Menu::Window.MiscTab.OtherSafeMode.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(16), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(16), Passive, Render::Fonts::List, "Off");
	}

	Render::Text(base.x, base.y + GetTextPositionInList(17), Main, Render::Fonts::List, "Airstuck:"); //33
	char airstuckkey[32];
	char* KeyName = "Not Bound";
	//sprintf_s(airstuckkey, "%.0f", Menu::Window.MiscTab.OtherAirStuck.GetKey());
	KeyName = KeyStringForList[Menu::Window.MiscTab.OtherAirStuck.GetKey()];
	GetKeyNameText(Menu::Window.MiscTab.OtherAirStuck.GetKey() << 16, airstuckkey, 127);
	Render::Text(base.x + tab, base.y + GetTextPositionInList(17), Submain, Render::Fonts::List, airstuckkey);
	
	Render::Text(base.x, base.y + GetTextPositionInList(18), Main, Render::Fonts::List, "Fakewalk:");
	char fakewalkkey[32];
	//sprintf_s(fakewalkkey, "%.0f", Menu::Window.MiscTab.FakeWalk.GetKey());
	KeyName = KeyStringForList[Menu::Window.MiscTab.FakeWalk.GetKey()];
	GetKeyNameText(Menu::Window.MiscTab.FakeWalk.GetKey() << 16, fakewalkkey, 127);
	Render::Text(base.x + tab, base.y + GetTextPositionInList(18), Submain, Render::Fonts::List, fakewalkkey);
	
	Render::Text(base.x, base.y + GetTextPositionInList(19), Main, Render::Fonts::List, "Backtrack:");
	if (Menu::Window.RageBotTab.TargetBacktrack.GetState())
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(19), Activated, Render::Fonts::List, "Enabled");
	}
	else
	{
		Render::Text(base.x + tab, base.y + GetTextPositionInList(19), Passive, Render::Fonts::List, "Off");
	}
	Render::Text(base.x, base.y + GetTextPositionInList(20), Main, Render::Fonts::List, "LBY:");
	char lby[32];
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	sprintf_s(lby, "%.0f", pLocal->GetLowerBodyYaw());
	Render::Text(base.x + tab, base.y + GetTextPositionInList(20), Submain, Render::Fonts::List, lby);

}
