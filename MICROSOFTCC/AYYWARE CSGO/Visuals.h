#pragma once

#include "Hacks.h"


class CVisuals : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool &bSendPacket);
private:
	void DrawCrosshair();
	void NoScopeCrosshair();
	void DrawRecoilCrosshair();
	void DefaultCrosshair();
	void SpreadCrosshair();
	void DrawDamageIndicator();
	void DrawRadar();

};