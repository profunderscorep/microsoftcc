#define _CRT_SECURE_NO_WARNINGS

#include "MiscHacks.h"
#include "Interfaces.h"
#include "RenderManager.h"

#include <time.h>

template<class T, class U>
inline T clamp(T in, U low, U high)
{
	if (in <= low)
		return low;
	else if (in >= high)
		return high;
	else
		return in;
}

inline float bitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}

inline float FloatNegate(float f)
{
	return bitsToFloat(FloatBits(f) ^ 0x80000000);
}

Vector AutoStrafeView;

void CMiscHacks::Init()
{
}

void CMiscHacks::Draw()
{
	switch (Menu::Window.MiscTab.NameChanger.GetIndex())
	{
	case 0:
		break;
	case 1:
		Namespam();
		break;
	case 2:
		NoName();
		break;
	case 3:
		NameSteal();
		break;
	}

	if (Menu::Window.MiscTab.ChatSpam.GetState())
		ChatSpam();
}

void CMiscHacks::Move(CUserCmd *pCmd, bool &bSendPacket)
{
	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (Menu::Window.MiscTab.OtherAutoJump.GetState())
		AutoJump(pCmd);

	Interfaces::Engine->GetViewAngles(AutoStrafeView);
	switch (Menu::Window.MiscTab.OtherAutoStrafe.GetIndex())
	{
	case 0:
		break;
	case 1:
		LegitStrafe(pCmd);
		break;
	case 2:
		RageStrafe(pCmd);
		break;
	}

	if (Menu::Window.MiscTab.OtherCircleStrafe.GetState())
		CircularStrafe(pCmd, pCmd->viewangles);

	if (Menu::Window.MiscTab.FakeWalk.GetKey())
		FakeWalk(pCmd, bSendPacket);

	if (Menu::Window.MiscTab.OtherSlowMotion.GetKey())
		SlowMo(pCmd);

	if (Menu::Window.MiscTab.AutoPistol.GetState())
		AutoPistol(pCmd);

	if (Menu::Window.VisualsTab.DisablePostProcess.GetState())
		PostProcces();

	if (Menu::Window.MiscTab.CheatsByPass.GetState())
		SvCheats();

}

static __declspec(naked) void __cdecl Invoke_NET_SetConVar(void* pfn, const char* cvar, const char* value)
{
	__asm 
	{
		push    ebp
			mov     ebp, esp
			and     esp, 0FFFFFFF8h
			sub     esp, 44h
			push    ebx
			push    esi
			push    edi
			mov     edi, cvar
			mov     esi, value
			jmp     pfn
	}
}

void DECLSPEC_NOINLINE NET_SetConVar(const char* value, const char* cvar)
{
	static DWORD setaddr = Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x8D\x4C\x24\x1C\xE8\x00\x00\x00\x00\x56", "xxxxx????x");
	if (setaddr != 0) 
	{
		void* pvSetConVar = (char*)setaddr;
		Invoke_NET_SetConVar(pvSetConVar, cvar, value);
	}
}

void change_name(const char* name)
{
	if (Interfaces::Engine->IsInGame() && Interfaces::Engine->IsConnected())
		NET_SetConVar(name, "name");
}

void CMiscHacks::AutoPistol(CUserCmd* pCmd)
{
	CBaseCombatWeapon* pWeapon = (CBaseCombatWeapon*)Interfaces::EntList->GetClientEntityFromHandle(hackManager.pLocal()->GetActiveWeaponHandle());

	if (pWeapon)
	{
		if (GameUtils::IsBomb(pWeapon))
		{
			return;
		}

		if (!GameUtils::IsNotPistol(pWeapon))
		{
			return;
		}
	}

	static bool WasFiring = false;

	if (GameUtils::IsPistol)
	{
		if (pCmd->buttons & IN_ATTACK)
		{
			if (WasFiring)
			{
				pCmd->buttons &= ~IN_ATTACK;
			}
		}
		WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
	}
}

void CMiscHacks::PostProcces()
{
	ConVar* Meme = Interfaces::CVar->FindVar("mat_postprocess_enable");
	SpoofedConvar* meme_spoofed = new SpoofedConvar(Meme);
	meme_spoofed->SetString("mat_postprocess_enable 0");
}

void CMiscHacks::SvCheats()
{
	ConVar* sv = Interfaces::CVar->FindVar("sv_cheats");
	SpoofedConvar* sv_spoofed = new SpoofedConvar(sv);
	sv_spoofed->SetInt(2);
}

void CMiscHacks::FakeWalk(CUserCmd* pCmd, bool &bSendPacket)
{
	IClientEntity* pLocal = hackManager.pLocal();

	int FakeWalkKey = Menu::Window.MiscTab.FakeWalk.GetKey();
	if (FakeWalkKey > 0 && GUI.GetKeyState(FakeWalkKey))
	{
		static int iChoked = -1;
		iChoked++;

		if (iChoked < 1)
		{
			bSendPacket = false;

			pCmd->tick_count += 10;
			pCmd->command_number += 7 + pCmd->tick_count % 2 ? 0 : 1;

			pCmd->buttons |= pLocal->GetMoveType() == IN_BACK;
			pCmd->forwardmove = pCmd->sidemove = 0.f;
		}
		else
		{
			bSendPacket = true;
			iChoked = -1;

			Interfaces::Globals->frametime *= (pLocal->GetVelocity().Length2D()) / 1.f;
			pCmd->buttons |= pLocal->GetMoveType() == IN_FORWARD;
		}
	}
}

void CMiscHacks::SlowMo(CUserCmd *pCmd)
{
	int SlowMotionKey = Menu::Window.MiscTab.OtherSlowMotion.GetKey();
	if (SlowMotionKey > 0 && GUI.GetKeyState(SlowMotionKey))
	{
		static bool slowmo;
		slowmo = !slowmo;
		if (slowmo)
		{
			pCmd->tick_count = INT_MAX;
		}
	}
}

void CMiscHacks::Namespam()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	static bool wasSpamming = true;

	if (wasSpamming)
	{
		static bool useSpace = true;
		if (useSpace)
		{
			change_name("™AVOZ");
			useSpace = !useSpace;
		}
		else
		{
			change_name("™ AVOZ");
			useSpace = !useSpace;
		}
	}

	start_t = clock();
}

void CMiscHacks::NoName()
{
	change_name("\n­­­");
}

void CMiscHacks::NameSteal()
{
	static clock_t start_t = clock();
	double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	if (timeSoFar < 0.001)
		return;

	std::vector < std::string > Names;

	for (int i = 0; i < Interfaces::EntList->GetHighestEntityIndex(); i++)
	{

		IClientEntity *entity = Interfaces::EntList->GetClientEntity(i);

		player_info_t pInfo;

		if (entity && hackManager.pLocal()->GetTeamNum() == entity->GetTeamNum() && entity != hackManager.pLocal())
		{
			ClientClass* cClass = (ClientClass*)entity->GetClientClass();

			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				if (Interfaces::Engine->GetPlayerInfo(i, &pInfo))
				{
					if (!strstr(pInfo.name, "GOTV"))
						Names.push_back(pInfo.name);
				}
			}
		}
	}

	static bool wasSpamming = true;

	int randomIndex = rand() % Names.size();
	char buffer[128];
	sprintf_s(buffer, "%s ", Names[randomIndex].c_str());

	if (wasSpamming)
	{
		change_name(buffer);
	}
	else
	{
		change_name("p$i 1337");
	}

	start_t = clock();
}

void CMiscHacks::RotateMovement(CUserCmd* pCmd, float rotation)
{
	rotation = DEG2RAD(rotation);

	float cos_rot = cos(rotation);
	float sin_rot = sin(rotation);

	float new_forwardmove = (cos_rot * pCmd->forwardmove) - (sin_rot * pCmd->sidemove);
	float new_sidemove = (sin_rot * pCmd->forwardmove) + (cos_rot * pCmd->sidemove);

	pCmd->forwardmove = new_forwardmove;
	pCmd->sidemove = new_sidemove;
}

bool CMiscHacks::CircularStrafe(CUserCmd* pCmd, Vector& OriginalView)
{
	if (!(Menu::Window.MiscTab.OtherCircleStrafe.GetState()))
		return false;

	IClientEntity* pLocalEntity = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	if (!pLocalEntity)
		return false;

	if (!pLocalEntity->IsAlive())
		return false;

	CircleFactor++;
	if (CircleFactor > 360)
		CircleFactor = 0;

	int GetItDoubled = 3.0 * CircleFactor - Interfaces::Globals->interval_per_tick;

	Vector StoredViewAngles = pCmd->viewangles;

	int CIRCLEKey = Menu::Window.MiscTab.OtherCircleButton.GetKey();

	if (CIRCLEKey > 0 && GUI.GetKeyState(CIRCLEKey))
	{
		pCmd->viewangles = OriginalView;
		RotateMovement(pCmd, GetItDoubled);
	}
	return true;
}

void CMiscHacks::AutoJump(CUserCmd *pCmd)
{
	if (pCmd->buttons & IN_JUMP && GUI.GetKeyState(VK_SPACE))
	{
		int iFlags = hackManager.pLocal()->GetFlags();
		if (!(iFlags & FL_ONGROUND))
			pCmd->buttons &= ~IN_JUMP;

		if (hackManager.pLocal()->GetVelocity().Length() <= 50)
		{
			pCmd->forwardmove = 450.f;
		}
	}
}

void CMiscHacks::LegitStrafe(CUserCmd *pCmd)
{
	IClientEntity* pLocal = hackManager.pLocal();
	if (!(pLocal->GetFlags() & FL_ONGROUND))
	{
		pCmd->forwardmove = 0.0f;

		if (pCmd->mousedx < 0)
		{
			pCmd->sidemove = -450.0f;
		}
		else if (pCmd->mousedx > 0)
		{
			pCmd->sidemove = 450.0f;
		}
	}
}

void CMiscHacks::RageStrafe(CUserCmd *pCmd)
{

	IClientEntity* pLocal = (IClientEntity*)Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());

	static bool bDirection = true;

	static float move = 450.f;
	float s_move = move * 0.5065f;
	static float strafe = pCmd->viewangles.y;
	float rt = pCmd->viewangles.y, rotation;

	if ((pCmd->buttons & IN_JUMP) || !(pLocal->GetFlags() & FL_ONGROUND))
	{

		pCmd->forwardmove = move * 0.015f;
		pCmd->sidemove += (float)(((pCmd->tick_count % 2) * 2) - 1) * s_move;

		if (pCmd->mousedx)
			pCmd->sidemove = (float)clamp(pCmd->mousedx, -1, 1) * s_move;

		rotation = strafe - rt;

		strafe = rt;

		IClientEntity* pLocal = hackManager.pLocal();
		static bool bDirection = true;

		bool bKeysPressed = true;

		if (GUI.GetKeyState(0x41) || GUI.GetKeyState(0x57) || GUI.GetKeyState(0x53) || GUI.GetKeyState(0x44))
			bKeysPressed = false;
		if (pCmd->buttons & IN_ATTACK)
			bKeysPressed = false;

		float flYawBhop = 0.f;

		float sdmw = pCmd->sidemove;
		float fdmw = pCmd->forwardmove;

		static float move = 450.f;
		float s_move = move * 0.5276f;
		static float strafe = pCmd->viewangles.y;

		if (Menu::Window.MiscTab.OtherAutoStrafe.GetIndex() == 2 && !GetAsyncKeyState(VK_RBUTTON))
		{
			if (pLocal->GetVelocity().Length() > 45.f)
			{
				float x = 30.f, y = pLocal->GetVelocity().Length(), z = 0.f, a = 0.f;

				z = x / y;
				z = fabsf(z);

				a = x * z;

				flYawBhop = a;
			}

			if ((GetAsyncKeyState(VK_SPACE) && !(pLocal->GetFlags() & FL_ONGROUND)) && bKeysPressed)
			{

				if (bDirection)
				{
					AutoStrafeView -= flYawBhop;
					GameUtils::NormaliseViewAngle(AutoStrafeView);
					pCmd->sidemove = -450;
					bDirection = false;
				}
				else
				{
					AutoStrafeView += flYawBhop;
					GameUtils::NormaliseViewAngle(AutoStrafeView);
					pCmd->sidemove = 430;
					bDirection = true;
				}

				if (pCmd->mousedx < 0)
				{
					pCmd->forwardmove = 22;
					pCmd->sidemove = -450;
				}

				if (pCmd->mousedx > 0)
				{
					pCmd->forwardmove = +22;
					pCmd->sidemove = 450;
				}
			}
		}
	}
}

Vector GetAutostrafeView()
{
	return AutoStrafeView;
}

std::vector<std::string> blacklisted_words =
{
	"vac inc",
	"ow inc",
	" ow ",
	" vac ",
	"owns me and all",
	"skeet",
	" > all",
	" uff ",
	"hentaiware",
	"aimware",
	"Premium CSGO Cheat"
};

bf_read::bf_read(unsigned int addr)
{
	base_address = addr;
	cur_offset = 0;
}

void bf_read::setOffset(unsigned int offset)
{
	cur_offset = offset;
}

void bf_read::skip(unsigned int length)
{
	cur_offset += length;
}

int bf_read::readByte()
{
	auto val = *reinterpret_cast<char*>(base_address + cur_offset);
	++cur_offset;
	return val;
}

bool bf_read::readBool()
{
	auto val = *reinterpret_cast<bool*>(base_address + cur_offset);
	++cur_offset;
	return val;
}

std::string bf_read::readString()
{
	char buffer[256];

	auto str_length = *reinterpret_cast<char*>(base_address + cur_offset);
	++cur_offset;

	std::memcpy(buffer, reinterpret_cast<void*>(base_address + cur_offset), str_length > 255 ? 255 : str_length);

	buffer[str_length > 255 ? 255 : str_length] = '\0';
	cur_offset += str_length + 1;

	return std::string(buffer);
}
bool find_word(const std::string &text, const std::string &word)
{
	size_t pos = 0;

	while ((pos = text.substr(pos).find(word)) != std::string::npos)
	{
		if (!(isalpha(text[pos - 1])) || !(isalpha(text[pos + word.size() + 1])))
			return true;
	}
	return false;
}
void CMiscHacks::ChatSpam()
{
	/*
	
	//static clock_t start_t = clock();
	//int spamtime = Menu::Window.MiscTab.OtherChatDelay.GetValue();
	//double timeSoFar = (double)(clock() - start_t) / CLOCKS_PER_SEC;
	//if (timeSoFar < spamtime)
	//	return;

	//static bool holzed = true;
	
	
	bf_read data = bf_read(reinterpret_cast<unsigned int>(msg_data));
	data.setOffset(1);

	int ent_idx = data.readByte();
	data.skip(3);
	std::string msg_name = data.readString();
	std::string playerName = data.readString();
	std::string msg = data.readString();
	if (Menu::Window.MiscTab.OtherTeamChat.GetState())
	{
		//SayInTeamChat("avoz - Private CSGO Cheat");
		for (size_t i = 0; i < blacklisted_words.size(); i++)
			if (find_word(msg, blacklisted_words.at(i)))
			{
				SayInTeamChat("cringe");
			}
	}
	else
	{
		//SayInChat("avoz - Private CSGO Cheat");
		for (size_t i = 0; i < blacklisted_words.size(); i++)
			if (find_word(msg, blacklisted_words.at(i)))
			{
				SayInChat("cringe");
			}
	}


	
			
	//start_t = clock();
	*/
}
