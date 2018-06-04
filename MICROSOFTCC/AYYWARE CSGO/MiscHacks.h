#pragma once

#include "Hacks.h"

Vector GetAutostrafeView();

class CMiscHacks : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	void walkbot(CUserCmd * pCmd, IClientEntity * pLocal);
	void AutoPistol(CUserCmd * pCmd);
	void PostProcces();
	void SvCheats();
	void SetClanTag(const char * tag, const char * name);
	void FakeWalk(CUserCmd * pCmd, bool & bSendPacket);
	void SlowMo(CUserCmd * pCmd);
	void Namespam();
	void NoName();
	void NameSteal();
	void RotateMovement(CUserCmd * pCmd, float rotation);
	bool CircularStrafe(CUserCmd * pCmd, Vector & OriginalView);
	void AutoJump(CUserCmd *pCmd);
	void LegitStrafe(CUserCmd *pCmd);
	void RageStrafe(CUserCmd *pCmd);
	int CircleFactor = 0;
	void Fakelag(CUserCmd *pCmd, bool &bSendPacket);
	void ChatSpam();
};


class bf_read
{
public:

	unsigned int base_address;
	unsigned int cur_offset;

	bf_read(unsigned int addr);
	void setOffset(unsigned int offset);
	void skip(unsigned int length);
	int readByte();
	bool readBool();
	std::string readString();
};

