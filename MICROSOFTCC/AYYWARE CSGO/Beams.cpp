#include "iviewrender_beams.h"
#include "Menu.h"

#define strenc( s ) ( s )

//IViewRenderBeams *g_pViewRenderBeams;
IViewRenderBeams *g_pViewRenderBeams = *reinterpret_cast< IViewRenderBeams** >(GameUtils::FindPattern1(strenc("client.dll"), strenc("A1 ? ? ? ? 56 8B F1 B9 ? ? ? ? FF 50 08")) + 0x1);


std::string gayvis[] =
{
	"sprites/640_pain_down.vmt",
	"sprites/640_pain_left.vmt",
	"sprites/640_pain_right.vmt",
	"sprites/640_pain_up.vmt",
	"sprites/640hud1.vmt",
	"sprites/a_icons1.vmt",
	"sprites/ar2_muzzle1.vmt",
	"sprites/ar2_muzzle1b.vmt",
	"sprites/ar2_muzzle2b.vmt",
	"sprites/ar2_muzzle3b.vmt",
	"sprites/ar2_muzzle4b.vmt",
	"sprites/arrow.vmt",
	"sprites/bloodspray.vmt",
	"sprites/blueflare1.vmt",
	"sprites/blueflare1_noz.vmt",
	"sprites/blueglow1.vmt",
	"sprites/bomb_carried.vmt",
	"sprites/bomb_carried_ring.vmt",
	"sprites/bomb_carried_ring_offscreen.vmt",
	"sprites/bomb_dropped.vmt",
	"sprites/bomb_dropped_ring.vmt",
	"sprites/bomb_planted.vmt",
	"sprites/bomb_planted_ring.vmt",
	"sprites/bubble.vmt",
	"sprites/c4.vmt",
	"sprites/cbbl_smoke.vmt",
	"sprites/crosshairs.vmt",
	"sprites/crosshairs_tluc.vmt",
	"sprites/defuser.vmt",
	"sprites/flare_sprite_01.vmt",
	"sprites/glow.vmt",
	"sprites/glow01.vmt",
	"sprites/glow03.vmt",
	"sprites/glow04.vmt",
	"sprites/glow04_noz.vmt",
	"sprites/glow06.vmt",
	"sprites/glow07.vmt",
	"sprites/glow_test01.vmt",
	"sprites/glow_test01b.vmt",
	"sprites/glow_test02.vmt",
	"sprites/glow_test02_nofog.vmt",
	"sprites/gunsmoke.vmt",
	"sprites/halo.vmt",
	"sprites/heatwave.vmt",
	"sprites/heatwavedx70.vmt",
	"sprites/hostage_following.vmt",
	"sprites/hostage_following_offscreen.vmt",
	"sprites/hostage_rescue.vmt",
	"sprites/hud/v_crosshair1.vmt",
	"sprites/hud/v_crosshair2.vmt",
	"sprites/laserbeam.vmt",
	"sprites/ledglow.vmt",
	"sprites/light_glow02.vmt",
	"sprites/light_glow02_add.vmt",
	"sprites/light_glow02_add_noz.vmt",
	"sprites/light_glow02_noz	.vmt",
	"sprites/light_glow03.vmt",
	"sprites/light_glow03_nofog.vmt",
	"sprites/light_glow04.vmt",
	"sprites/light_glow04_add_noz.vmt",
	"sprites/muzzleflash4.vmt",
	"sprites/nuke_sunflare_001.vmt",
	"sprites/numbers.vmt",
	"sprites/obj_icons/c4.vmt",
	"sprites/obj_icons/defended.vmt",
	"sprites/obj_icons/flagcaptured.vmt",
	"sprites/obj_icons/kills.vmt",
	"sprites/objective_rescue.vmt",
	"sprites/objective_site_a.vmt",
	"sprites/objective_site_b.vmt",
	"sprites/physbeam.vmt",
	"sprites/player_blue.vmt",
	"sprites/player_blue_dead.vmt",
	"sprites/player_blue_dead_offscreen.vmt",
	"sprites/player_blue_offscreen.vmt",
	"sprites/player_blue_self.vmt",
	"sprites/player_blue_small.vmt",
	"sprites/player_hostage_dead.vmt",
	"sprites/player_hostage_dead_offscreen.vmt",
	"sprites/player_hostage_offscreen.vmt",
	"sprites/player_hostage_small.vmt",
	"sprites/player_radio_ring.vmt",
	"sprites/player_radio_ring_offscreen.vmt",
	"sprites/player_red.vmt",
	"sprites/player_red_dead.vmt",
	"sprites/player_red_dead_offscreen.vmt",
	"sprites/player_red_offscreen.vmt",
	"sprites/player_red_self.vmt",
	"sprites/player_red_small.vmt",
	"sprites/player_tick.vmt",
	"sprites/purpleglow1.vmt",
	"sprites/purplelaser1.vmt",
	"sprites/qi_center.vmt",
	"sprites/radar.vmt",
	"sprites/radar_trans.vmt",
	"sprites/radio.vmt",
	"sprites/richo1.vmt",
	"sprites/rico1.vmt",
	"sprites/rico1_noz.vmt",
	"sprites/scope_arc.vmt",
	"sprites/scope_line_blur.vmt",
	"sprites/scope_sprite3.vmt",
	"sprites/shopping_cart.vmt",
	"sprites/smoke.vmt",
	"sprites/spectator_3rdcam	.vmt",
	"sprites/spectator_eye.vmt",
	"sprites/spectator_freecam.vmt",
	"sprites/spotlight01_proxyfade.vmt",
	"sprites/steam1.vmt",
	"sprites/water_drop.vmt",
	"sprites/white.vmt",
	"sprites/wpn_select1.vmt",
	"sprites/wpn_select2.vmt",
	"sprites/wpn_select3.vmt",
	"sprites/wpn_select4.vmt",
	"sprites/wpn_select5.vmt",
	"sprites/wpn_select6.vmt",
	"sprites/wpn_select7.vmt",
	"sprites/xfireball3.vmt",
	"sprites/yelflare1.vmt",
	"sprites/yelflare2.vmt",
	"sprites/zerogxplode.vmt",
};

void IViewRenderBeams::BulletTracers()
{
	if (!Menu::Window.VisualsTab.BulletTracers.GetState())
		return;

	IClientEntity *pLocal = Interfaces::EntList->GetClientEntity(Interfaces::Engine->GetLocalPlayer());
	//if the player is not ingame, clear the shots
	if (!Interfaces::Engine->IsInGame() || !pLocal) //!pIVEngineClient->IsInGame() || !pLocal
	{
		//Impacts.clear();
		return;
	}

//	if (Impacts.size() > 30)
//		Impacts.pop_back();

	for (int i = 0; i < Impacts.size(); i++)
	{
		auto current = Impacts.at(i);

		if (!current.pPlayer)
			continue;

		if (current.pPlayer->IsDormant())
			continue;

		if (current.pPlayer == pLocal) //current.pPlayer == pLocal
			current.color = Color(255, 144, 0); //color of local player's tracers

		BeamInfo_t beamInfo;
		beamInfo.m_nType = TE_BEAMPOINTS;
		beamInfo.m_pszModelName = "sprites/physbeam.vmt";
		beamInfo.m_nModelIndex = -1;
		beamInfo.m_flHaloScale = 0.0f;
		beamInfo.m_flLife = 5.f; //duration of tracers
		beamInfo.m_flWidth = 3.f; //start width
		beamInfo.m_flEndWidth = 3.f; //end width
		beamInfo.m_flFadeLength = 0.0f;
		beamInfo.m_flAmplitude = 2.0f;
		beamInfo.m_flBrightness = 255.f;
		beamInfo.m_flSpeed = 0.2f;
		beamInfo.m_nStartFrame = 0;
		beamInfo.m_flFrameRate = 0.f;
		beamInfo.m_flRed = 255;
		beamInfo.m_flGreen = 144;
		beamInfo.m_flBlue = 0;
		beamInfo.m_nSegments = 2;
		beamInfo.m_bRenderable = true;
		beamInfo.m_nFlags = FBEAM_ONLYNOISEONCE | FBEAM_NOTILE | FBEAM_HALOBEAM;
		beamInfo.m_vecStart = current.pPlayer->GetEyePosition();
		beamInfo.m_vecEnd = current.vecImpactPos;

		auto beam = g_pViewRenderBeams->CreateBeamPoints(beamInfo);
		if (beam)
			g_pViewRenderBeams->DrawBeam(beam);

		Impacts.erase(Impacts.begin() + i);
	}
}