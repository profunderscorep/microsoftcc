#pragma once

#include "GUI.h"
#include "Controls.h"

class CRageBotTab : public CTab
{
public:
	void Setup();

	CLabel ActiveLabel;
	CCheckBox Active;

	CGroupBox AimbotGroup;
	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CSlider2  AimbotFov;
	CCheckBox AimbotSilentAim;
	CCheckBox PVSFix;
	CComboBox AimbotResolver;
	CCheckBox AdvancedResolver;
	CCheckBox AutoRevolver;
	CSlider2 AddFakeYaw;
	CSlider2 CustomPitch;
	CCheckBox LBY;
	CComboBox FakeYaw;
	CCheckBox LowerbodyFix;
	CCheckBox PreferBodyAim;
	CCheckBox AWPAtBody;
	CSlider2 BaimIfUnderXHealth;
	CSlider2 XShots;
	CCheckBox EnginePrediction;
	CCheckBox AimbotAimStep;
	CCheckBox AimbotKeyPress;
	CKeyBind  AimbotKeyBind;
	CKeyBind  AimbotStopKey;

	CGroupBox TargetGroup;
	CComboBox TargetSelection;
	CCheckBox TargetFriendlyFire;
	CComboBox TargetHitbox;
	CComboBox TargetHitscan;
	CCheckBox TargetMultipoint;
	CCheckBox PositionAdjustment;
	CCheckBox TargetBacktrack;
	CSlider   TargetPointscale;

	CGroupBox AccuracyGroup;
	CCheckBox AccuracyRecoil;
	CCheckBox AccuracyAutoWall;
	CSlider2 AccuracyMinimumDamage;
	CCheckBox AccuracyAutoStop;
	CCheckBox AccuracyAutoCrouch;
	CCheckBox AccuracyAutoScope;
	CSlider2   AccuracyHitchance;
	CComboBox AccuracyResolver;

	CGroupBox AntiAimGroup;
	CCheckBox AntiAimEnable;
	CComboBox AntiAimPitch;
	CComboBox FakePitch;
	CComboBox AntiAimYaw;
	CCheckBox FlipAA;
	CCheckBox AntiAimEdge;
	CSlider2 AntiAimOffset;
	CCheckBox AntiAimKnife;
	CCheckBox AntiAimTarget;
};

class CLegitBotTab : public CTab
{
public:
	void Setup();

	// Master Switch
	CLabel ActiveLabel;
	CCheckBox Active;

	CGroupBox AimbotGroup;

	CCheckBox AimbotEnable;
	CCheckBox AimbotAutoFire;
	CCheckBox AimbotFriendlyFire;
	CCheckBox AimbotKeyPress;
	CCheckBox AimbotLegitBacktrack;
	CKeyBind  AimbotKeyBind;
	CCheckBox AimbotSmokeCheck;

	CGroupBox TriggerGroup;
	CCheckBox TriggerEnable;
	CCheckBox TriggerKeyPress;
	CKeyBind  TriggerKeyBind;
	CCheckBox TriggerHitChance;
	CSlider   TriggerHitChanceAmmount;
	CSlider   TriggerDelay;
	CSlider   TriggerBurst;
	CSlider   TriggerBreak;
	CCheckBox TriggerRecoil;

	CGroupBox TriggerFilterGroup;
	CCheckBox TriggerHead;
	CCheckBox TriggerChest;
	CCheckBox TriggerStomach;
	CCheckBox TriggerArms;
	CCheckBox TriggerLegs;
	CCheckBox TriggerTeammates;
	CCheckBox TriggerFlashCheck;
	CCheckBox TriggerSmokeCheck;

	CGroupBox WeaponMainGroup;
	CSlider   WeaponMainSpeed;
	CSlider   WeaponMainFoV;
	CSlider WeaponMainRecoil;
	CComboBox WeaponMainHitbox;
	CSlider WeaponMainAimtime;
	CSlider WeaoponMainStartAimtime;

	CGroupBox WeaponPistGroup;
	CSlider   WeaponPistSpeed;
	CSlider   WeaponPistFoV;
	CSlider WeaponPistRecoil;
	CComboBox WeaponPistHitbox;
	CSlider WeaponPistAimtime;
	CSlider WeaoponPistStartAimtime;

	CGroupBox WeaponSnipGroup;
	CSlider   WeaponSnipSpeed;
	CSlider   WeaponSnipFoV;
	CSlider WeaponSnipRecoil;
	CComboBox WeaponSnipHitbox;
	CSlider WeaponSnipAimtime;
	CSlider WeaoponSnipStartAimtime;

	CGroupBox WeaponMpGroup;
	CSlider   WeaponMpSpeed;
	CSlider   WeaponMpFoV;
	CSlider WeaponMpRecoil;
	CComboBox WeaponMpHitbox;
	CSlider WeaponMpAimtime;
	CSlider WeaoponMpStartAimtime;

	CGroupBox WeaponShotgunGroup;
	CSlider   WeaponShotgunSpeed;
	CSlider   WeaponShotgunFoV;
	CSlider WeaponShotgunRecoil;
	CComboBox WeaponShotgunHitbox;
	CSlider WeaponShotgunAimtime;
	CSlider WeaoponShotgunStartAimtime;

	CGroupBox WeaponMGGroup;
	CSlider   WeaponMGSpeed;
	CSlider   WeaponMGFoV;
	CSlider WeaponMGRecoil;
	CComboBox WeaponMGHitbox;
	CSlider WeaponMGAimtime;
	CSlider WeaoponMGStartAimtime;
};

class CVisualTab : public CTab
{
public:
	void Setup();

	CLabel ActiveLabel;
	CCheckBox Active;

	CGroupBox OptionsGroup;
	CComboBox OptionsBox;
	CCheckBox OptionsName;
	CCheckBox HitmarkerSound;
	CCheckBox OtherHitmarker;
	CCheckBox OptionsHealth;
	CComboBox OptionsWeapon;
	CCheckBox OptionsInfo;
	CCheckBox Barrels;
	CCheckBox ChamsVisibleOnly;
	CCheckBox Ammo;
	CCheckBox Clock;
	CSlider AmbientBlue;
	CCheckBox HostageGlow;
	CSlider AmbientRed;
	CCheckBox Watermark;
	CCheckBox LBYIndicator;
	CSlider AmbientGreen;
	CCheckBox OptionsHelmet;
	CCheckBox NightMode;
	CCheckBox OptionsKit;
	CCheckBox SpecList;
	CCheckBox IsScoped;
	CCheckBox CompRank;
	CCheckBox HasDefuser;
	CCheckBox GrenadeTrace;
	CCheckBox Distance;
	CCheckBox DiscoLights;
	CCheckBox Money;
	CCheckBox OptionsDefuse;
	CComboBox OptionsChams;
	CCheckBox OptionsArmor;
	CCheckBox OptionsDefusing;
	CCheckBox SniperCrosshair;
	CSlider2  GlowZ;
	CCheckBox OptionsSkeleton;
	CCheckBox NightSky;
	CCheckBox OptionsAimSpot;
	CCheckBox WeaponChams;
	CCheckBox OtherNoScope;
	CCheckBox OptionsCompRank;
	CCheckBox DLights;

	CGroupBox FiltersGroup;
	CCheckBox FiltersAll;
	CCheckBox FiltersPlayers;
	CCheckBox FiltersEnemiesOnly;
	CCheckBox FiltersWeapons;
	CCheckBox FiltersChickens;
	CCheckBox FiltersNades;
	CCheckBox FiltersC4;

	CGroupBox OtherGroup;
	CComboBox OtherCrosshair;
	CComboBox OtherRecoilCrosshair;
	CCheckBox OptionsGlow;
	CCheckBox EntityGlow;
	CCheckBox DisablePostProcess;
	CCheckBox OtherRadar;
	CCheckBox OtherNoVisualRecoil;
	CCheckBox OtherNoSky; 
	CCheckBox OtherNoFlash; 
	CCheckBox OtherNoSmoke;
	CCheckBox OtherAsusWalls;
	CComboBox OtherNoHands;
	CCheckBox LagCompensation;
	CCheckBox AngleChams;
	CCheckBox BulletTracers;
	CCheckBox AntiAimLines;
	CCheckBox BulletTrace;
	CSlider2 BulletTraceLength;
	CSlider2 OtherViewmodelFOV;
	CSlider2 OtherFOV;
};

class CSkinchangerTab : public CTab
{
public:
	void Setup();

	CLabel SkinActive;
	CCheckBox SkinEnable;
	CButton   SkinApply;

	CGroupBox KnifeGroup;
	CComboBox KnifeModel;
	CTextField KnifeSkin;

	CGroupBox PistolGroup;
	CComboBox GLOCKSkin;
	CComboBox USPSSkin;
	CComboBox DEAGLESkin;
	CComboBox MAGNUMSkin;
	CComboBox DUALSSkin;
	CComboBox RevolverSkin;
	CComboBox FIVESEVENSkin;
	CComboBox TECNINESkin;
	CComboBox P2000Skin;
	CComboBox P250Skin;

	CGroupBox MPGroup;
	CComboBox MAC10Skin;
	CComboBox P90Skin;
	CComboBox UMP45Skin;
	CComboBox BIZONSkin;
	CComboBox MP7Skin;
	CComboBox MP9Skin;

	CGroupBox Riflegroup;
	CComboBox M41SSkin;
	CComboBox M4A4Skin;
	CComboBox AK47Skin;
	CComboBox AUGSkin;
	CComboBox FAMASSkin;
	CComboBox GALILSkin;
	CComboBox SG553Skin;

	CGroupBox MachinegunsGroup;
	CComboBox NEGEVSkin;
	CComboBox M249Skin;

	CGroupBox Snipergroup;
	CComboBox SCAR20Skin;
	CComboBox G3SG1Skin;
	CComboBox SSG08Skin;
	CComboBox AWPSkin;

	CGroupBox Shotgungroup;
	CComboBox MAG7Skin;
	CComboBox XM1014Skin;
	CComboBox SAWEDOFFSkin;
	CComboBox NOVASkin;

	CGroupBox SkinsettingsGroup;
	CCheckBox StatTrakEnable;
	CTextField StatTrackAmount;
	CTextField SkinName;
	CTextField KnifeName;
};

class CColorTab : public CTab
{
public:
	void Setup();

	CGroupBox RGBGroup;
	CSlider2   MenuR;
	CSlider2   MenuG;
	CSlider2   MenuB;


	CGroupBox ColorsGroup;
	CSlider2 CTColorVisR;
	CSlider2 CTColorVisG;
	CSlider2 CTColorVisB;

	CSlider2 TChams;
	CSlider2 CTChams;
	CSlider2 CTChamsR;
	CSlider2 CTChamsG;
	CSlider2 CTChamsB;
	CSlider2 TChamsR;
	CSlider2 TChamsB;
	CSlider2 TChamsG;

	CGroupBox Gloves;
	CCheckBox EnableGloves;
	CComboBox GloveSkin;
	CComboBox GloveModel;
	CButton GlovesApply;

	CSlider2 CTColorNoVisR;
	CSlider2 CTColorNoVisG;
	CSlider2 CTColorNoVisB;

	CLabel ColorSpacer;

	CSlider2 TColorVisR;
	CSlider2 TColorVisG;
	CSlider2 TColorVisB;

	CSlider2 TColorNoVisR;
	CSlider2 TColorNoVisG;
	CSlider2 TColorNoVisB;

	CSlider2 GlowR;
	CSlider2 GlowG;
	CSlider2 GlowB;

	CComboBox ConfigBox;
	CGroupBox ConfigGroup;
	CGroupBox Settings;
	CButton SettingsSave;
	CButton SettingsLoad;
};

class CMiscTab : public CTab
{
public:
	void Setup();

	CGroupBox OtherGroup;
	CCheckBox OtherAutoJump;
	CCheckBox OtherEdgeJump;
	CComboBox OtherAutoStrafe;
	CCheckBox OtherSafeMode;
	CCheckBox ChatSpam;
	CKeyBind OtherCircleButton;
	CCheckBox OtherCircleStrafe;
	CKeyBind OtherCircle;
	CTextField CustomClantag;
	CCheckBox CheatsByPass;
	CCheckBox AutoAccept;
	CCheckBox BuyBotKevlar;
	CCheckBox BuyBotDefuser;
	CComboBox BuyBotGrenades;
	CSlider CircleAmount;
	CKeyBind OtherSlowMotion;
	CKeyBind FakeWalk;

	CCheckBox OtherRadar;
	CSlider2 OtherRadarEnemyR;
	CSlider2 OtherRadarEnemyG;
	CSlider2 OtherRadarEnemyB;
	CSlider2 OtherRadarFriendlyR;
	CSlider2 OtherRadarFriendlyG;
	CSlider2 OtherRadarFriendlyB;

	CComboBox FakeLagTyp;
	CCheckBox OtherTeamChat;
	CSlider ClanTagSpeed;
	CSlider	  OtherChatDelay;
	CComboBox NameChanger;
	CCheckBox AutoPistol;
	CCheckBox ClanTag;
	CCheckBox TrashTalk;
	CKeyBind  OtherAirStuck;
	CCheckBox OtherSpectators;
	CCheckBox OtherThirdperson;
	CComboBox OtherClantag;
	CCheckBox EnableBuyBot;
	CComboBox BuyBot;
	CGroupBox BuyBotGroup;
	CSlider WalkBotDistance;
	CSlider WalkBotEdge;
	CCheckBox WalkBot;
	CGroupBox WalkBotGroup;

	CGroupBox FakeLagGroup;
	CCheckBox FakeLagEnable;
	CSlider   FakeLagChoke;
};

class CCheatSkinTab : public CTab
{
public:
	void Setup();

	
	CGroupBox CheatSkinTab;
	CComboBox Preset;

	//UI_COL_MAIN
	CGroupBox UI_COL_MAIN;
	CSlider rUI_COL_MAIN;
	CSlider gUI_COL_MAIN;
	CSlider bUI_COL_MAIN;

	//UI_COL_SHADOW
	CGroupBox UI_COL_SHADOW;
	CSlider2 rUI_COL_SHADOW;
	CSlider2 gUI_COL_SHADOW;
	CSlider2 bUI_COL_SHADOW;

	//UI_COURSOUR
	CGroupBox UI_COURSOUR;
	CSlider2 rUI_COURSOUR;
	CSlider2 gUI_COURSOUR;
	CSlider2 bUI_COURSOUR;

	//UI_COL_TABSEPERATOR
	CGroupBox UI_COL_TABSEPERATOR;
	CSlider2 rUI_COL_TABSEPERATOR;
	CSlider2 gUI_COL_TABSEPERATOR;
	CSlider2 bUI_COL_TABSEPERATOR;

	//UI_CURSORFILL
	CGroupBox UI_CURSORFILL;
	CSlider2 rUI_CURSORFILL;
	CSlider2 gUI_CURSORFILL;
	CSlider2 bUI_CURSORFILL;

	//BACKGROUND
	CGroupBox BACKGROUND;
	CSlider2 rBACKGROUND;
	CSlider2 gBACKGROUND;
	CSlider2 bBACKGROUND;

	//Text
	CGroupBox Text;
	CSlider2 rText;
	CSlider2 gText;
	CSlider2 bText;

};

class AvozWindow : public CWindow
{
public:
	void Setup();

	CRageBotTab RageBotTab;
	CLegitBotTab LegitBotTab;
	CVisualTab VisualsTab;
	CMiscTab MiscTab;
	CColorTab ColorsTab;
	CSkinchangerTab SkinchangerTab;
	CCheatSkinTab CheatSkinTab;

	CButton SaveButton1;
	CButton LoadButton1;
	CButton SaveButton;
	CButton LoadButton;
	CButton UnloadButton;
	CButton PanicButton;
	CButton ThirdButton;
	CButton ByPass;
	CButton FirstButton;
	CComboBox ConfigBox;
};

namespace Menu
{
	void SetupMenu();
	void DoUIFrame();

	extern AvozWindow Window;
	
};