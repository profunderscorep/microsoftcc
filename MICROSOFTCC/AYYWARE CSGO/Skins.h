﻿#pragma once

#include "ClientRecvProps.h"

extern RecvVarProxyFn fnSequenceProxyFn;

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

#define	LIFE_ALIVE 0

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

extern void SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);


const char* skins_items[] =
{
	"", "",  "2: Groundwater","3: Candy Apple", "",
	"5: Forest DDPAT","6: Arctic Camo",  "",
	"8: Desert Storm","9: Bengal Tiger","10: Copperhead",
	"11: Skulls","12: Crimson Web","13: Blue Streak","14: Red Laminate"
	,"15: Gunsmoke","16: Jungle Tiger","17: Urban DDPAT",  "",
	"", "20: Virus","21: Granite Marbleized","22: Contrast Spray",
	"",  "", "25: Forest Leaves","26: Lichen Dashed",
	"27: Bone Mask","28: Anodized Navy",  "",  "30: Snake Camo",
	"",  "32: Silver","33: Hot Rod","34: Metallic DDPAT",  "",
	"36: Ossified","37: Blaze","38: Fade","39: Bulldozer","40: Night",
	"41: Copper","42: Blue Steel","43: Stained","44: Case Hardened",
	"",  "46: Contractor","47: Colony","48: Dragon Tattoo",
	"",   "",  "51: Lightning Strike",  "",
	"",   "",   "",   "",   "",
	"",    "59: Slaughter","60: Dark Water"
	,"61: Hypnotic","62: Bloomstick",  "",   ""
	,   "",   "",  "67: Cold Blooded",  "",   ""
	,  "70: Carbon Fiber","71: Scorpion","72: Safari Mesh","73: Wings","74: Polar Camo"
	,"75: Blizzard Marbleized","76: Winter Forest","77: Boreal Forest","78: Forest Night"
	,  "",   "",   "",   "",  "83: Orange DDPAT","84: Pink DDPAT"
	,  "",   "",   "",   "",  "",  "90: Mudder",  ""
	,  "92: Cyanospatter","93: Caramel",  "", "95: Grassland","96: Blue Spruce",  ""
	,  "98: Ultraviolet","99: Sand Dune","100: Storm","101: Tornado","102: Whiteout",  ""
	,  "104: Grassland Leaves",  "",   "", "107: Polar Mesh",  "",   ""
	, "110: Condemned","111: Glacier Mesh",  "",   "",   "",   "",  "116: Sand Mesh",  "",   "", "119: Sage Spray",  "",   "", "122: Jungle Spray",  "",  "124: Sand Spray",  ""
	,  "",  "",  "",  "",  "",  "",  "",  "",  "", "135: Urban Perforated"
	,"136: Waves Perforated",  "",   "",   "",  "", "141: Orange Peel",  "",  "143: Urban Masked", "", "", "", "147: Jungle Dashed"
	,"148: Sand Dashed","149: Urban Dashed", "", "151: Jungle", "", "153: Demolition","154: Afterimage","155: Bullet Rain","156: Death by Kitty","157: Palm","158: Walnut","159: Brass",
	"", "", "162: Splash", "","164: Modern Hunter","165: Splash Jam","166: Blaze Orange","167: Radiation Hazard","168: Nuclear Threat","169: Fallout Warning","170: Predator","171: Irradiated Alert",
	"172: Black Laminate", "","174: BOOM","175: Scorched","176: Faded Zebra","177: Memento","178: Doomkitty","179: Nuclear Threat","180: Fire Serpent","181: Corticera","182: Emerald Dragon","183: Overgrowth",
	"184: Corticera","185: Golden Koi","186: Wave Spray","187: Zirka","188: Graven","189: Bright Water","190: Black Limba","191: Tempest","192: Shattered","193: Bone Pile","194: Spitfire","195: Demeter",
	"196: Emerald","197: Anodized Navy","198: Hazard","199: Dry Season","200: Mayan Dreams","201: Palm","202: Jungle DDPAT","203: Rust Coat","204: Mosaico","205: Jungle","206: Tornado","207: Facets",
	"208: Sand Dune","209: Groundwater","210: Anodized Gunmetal","211: Ocean Foam","212: Graphite","213: Ocean Foam","214: Graphite","215: X-Ray","216: Blue Titanium","217: Blood Tiger","218: Hexane",
	"219: Hive","220: Hemoglobin","221: Serum","222: Blood in the Water","223: Nightshade","224: Water Sigil","225: Ghost Camo","226: Blue Laminate","227: Electric Hive","228: Blind Spot","229: Azure Zebra",
	"230: Steel Disruption","231: Cobalt Disruption","232: Crimson Web","233: Tropical Storm","234: Ash Wood","235: VariCamo","236: Night Ops","237: Urban Rubble","238: VariCamo Blue", "", "240: CaliCamo",
	"241: Hunting Blind","242: Army Mesh","243: Gator Mesh","244: Teardown","245: Army Recon","246: Amber Fade","247: Damascus Steel","248: Red Quartz","249: Cobalt Quartz","250: Full Stop","251: Pit Viper",
	"252: Silver Quartz","253: Acid Fade","254: Nitro","255: Asiimov","256: The Kraken","257: Guardian","258: Mehndi","259: Redline","260: Pulse","261: Marina","262: Rose Iron","263: Rising Skull","264: Sandstorm",
	"265: Kami","266: Magma","267: Cobalt Halftone","268: Tread Plate","269: The Fuschia Is Now","270: Victoria","271: Undertow","272: Titanium Bit","273: Heirloom","274: Copper Galaxy","275: Red FragCam",
	"276: Panther","277: Stainless","278: Blue Fissure","279: Asiimov","280: Chameleon","281: Corporal","282: Redline","283: Trigon","284: Heat","285: Terrain","286: Antique","287: Pulse","288: Sergeant",
	"289: Sandstorm","290: Guardian","291: Heaven Guard", "", "293: Death Rattle","294: Green Apple","295: Franklin","296: Meteorite","297: Tuxedo","298: Army Sheen","299: Caged Steel","300: Emerald Pinstripe",
	"301: Atomic Alloy","302: Vulcan","303: Isaac","304: Slashed","305: Torque","306: Antique","307: Retribution","308: Kami","309: Howl","310: Curse","311: Desert Warfare","312: Cyrex","313: Orion",
	"314: Heaven Guard","315: Poison Dart","316: Jaguar","317: Bratatat","318: Road Rash","319: Detour","320: Red Python","321: Master Piece","322: Nitro","323: Rust Coat", "", "325: Chalice","326: Knight",
	"327: Chainmail","328: Hand Cannon","329: Dark Age","330: Briar", "", "332: Royal Blue","333: Indigo","334: Twist","335: Module","336: Desert-Strike","337: Tatter","338: Pulse","339: Caiman","340: Jet Set",
	"341: First Class","342: Leather","343: Commuter","344: Dragon Lore","345: First Class","346: Coach Class","347: Pilot","348: Red Leather","349: Osiris","350: Tigris","351: Conspiracy","352: Fowl Play",
	"353: Water Elemental","354: Urban Hazard","355: Desert-Strike","356: Koi","357: Ivory","358: Supernova","359: Asiimov","360: Cyrex","361: Abyss","362: Labyrinth","363: Traveler","364: Business Class",
	"365: Olive Plaid","366: Green Plaid","367: Reactor","368: Setting Sun","369: Nuclear Waste","370: Bone Machine","371: Styx","372: Nuclear Garden","373: Contamination","374: Toxic","375: Radiation Hazard",
	"376: Chemical Green","377: Hot Shot","378: Fallout Warning","379: Cerberus","380: Wasteland Rebel","381: Grinder","382: Murky","383: Basilisk","384: Griffin","385: Firestarter","386: Dart","387: Urban Hazard",
	"388: Cartel","389: Fire Elemental","390: Highwayman","391: Cardiac","392: Delusion","393: Tranquility","394: Cartel","395: Man-o'-war","396: Urban Shock","397: Naga","398: Chatterbox","399: Catacombs",
	"400: 龍王 (Dragon King)","401: System Lock","402: Malachite","403: Deadly Poison","404: Muertos","405: Serenity","406: Grotto","407: Quicksilver","", "409: Tiger Tooth","410: Damascus Steel",
	"411: Damascus Steel", "", "413: Marble Fade","414: Rust Coat","415: Doppler","416: Doppler","417: Doppler","418: Doppler","419: Doppler","420: Doppler","421: Doppler","422: Elite Build","423: Armor Core",
	"424: Worm God","425: Bronze Deco","426: Valence","427: Monkey Business","428: Eco","429: Djinn","430: Hyper Beast","431: Heat","432: Man-o'-war","433: Neon Rider","434: Origami","435: Pole Position",
	"436: Grand Prix","437: Twilight Galaxy","438: Chronos","439: Hades","440: Icarus Fell","441: Minotaur's Labyrinth","442: Asterion","443: Pathfinder","444: Daedalus","445: Hot Rod","446: Medusa","447: Duelist",
	"448: Pandora's Box","449: Poseidon","450: Moon in Libra","451: Sun in Leo","452: Shipping Forecast","453: Emerald","454: Para Green","455: Akihabara Accept","456: Hydroponic","457: Bamboo Print",
	"458: Bamboo Shadow","459: Bamboo Forest","460: Aqua Terrace", "", "462: Counter Terrace","463: Terrace","464: Neon Kimono","465: Orange Kimono","466: Crimson Kimono","467: Mint Kimono","468: Midnight Storm",
	"469: Sunset Storm 壱","470: Sunset Storm 弐","471: Daybreak","472: Impact Drill","473: Seabird","474: Aquamarine Revenge","475: Hyper Beast","476: Yellow Jacket","477: Neural Net","478: Rocket Pop",
	"479: Bunsen Burner","480: Evil Daimyo","481: Nemesis","482: Ruby Poison Dart","483: Loudmouth","484: Ranger","485: Handgun","486: Elite Build","487: Cyrex","488: Riot","489: Torque","490: Frontside Misty",
	"491: Dualing Dragons","492: Survivor Z","493: Flux","494: Stone Cold","495: Wraiths","496: Nebula Crusader","497: Golden Coil","498: Rangeen","499: Cobalt Core","500: Special Delivery","501: Wingshot",
	"502: Green Marine","503: Big Iron","504: Kill Confirmed","505: Scumbria","506: Point Disarray","507: Ricochet","508: Fuel Rod","509: Corinthian","510: Retrobution","511: The Executioner","512: Royal Paladin",
	"", "514: Power Loader","515: Imperial","516: Shapewood","517: Yorick","518: Outbreak","519: Tiger Moth","520: Avalanche","521: Teclu Burner","522: Fade","523: Amber Fade","524: Fuel Injector","525: Elite Build",
	"526: Photic Zone","527: Kumicho Dragon","528: Cartel","529: Valence","530: Triumvirate", "", "532: Royal Legion","533: The Battlestar","534: Lapis Gator","535: Praetorian","536: Impire","537: Hyper Beast",
	"538: Necropos","539: Jambiya","540: Lead Conduit","541: Fleet Flock","542: Judgement of Anubis","543: Red Astor","544: Ventilators","545: Orange Crash","546: Firefight","547: Spectre","548: Chantico's Fire",
	"549: Bioleak","550: Oceanic","551: Asiimov","552: Fubar","553: Atlas","554: Ghost Crusader","555: Re-Entry","556: Primal Saber","557: Black Tie","558: Lore","559: Lore","560: Lore","561: Lore","562: Lore",
	"563: Black Laminate","564: Black Laminate","565: Black Laminate","566: Black Laminate","567: Black Laminate","568: Gamma Doppler","569: Gamma Doppler","570: Gamma Doppler","571: Gamma Doppler",
	"572: Gamma Doppler","573: Autotronic","574: Autotronic","575: Autotronic","576: Autotronic","577: Autotronic","578: Bright Water","579: Bright Water","580: Freehand","581: Freehand","582: Freehand",
	"583: Aristocrat","584: Phobos","585: Violent Daimyo","586: Wasteland Rebel","587: Mecha Industries","588: Desolate Space","589: Carnivore","590: Exo","591: Imperial Dragon","592: Iron Clad",
	"593: Chopper","594: Harvester","595: Reboot","596: Limelight","597: Bloodsport","598: Aerial","599: Ice Cap","600: Neon Revolution","601: Syd Mead","602: Imprint","603: Directive","604: Roll Cage",
	"605: Scumbria","606: Ventilator","607: Weasel","608: Petroglyph","609: Airlock","610: Dazzle","611: Grim","612: Powercore","613: Triarch","614: Fuel Injector","615: Briefing","616: Slipstream","617: Doppler",
	"618: Doppler","619: Doppler","620: Ultraviolet","621: Ultraviolet","622: Polymer","623: Ironwork","624: Dragonfire","625: Royal Consorts","626: Mecha Industries","627: Cirrus","628: Stinger","629: Black Sand",
	"630: Sand Scale","631: Flashback","632: Buzz Kill","633: Sonar","634: Gila","635: Turf","636: Shallow Grave","637: Cyrex","638: Wasteland Princess","639: Bloodsport","640: Fever Dream","641: Jungle Slipstream",
	"642: Blueprint","643: Xiangliu","644: Decimator","645: Oxide Blaze","646: Capillary","647: Crimson Tsunami","648: Emerald Poison Dart","649: Akoben","650: Ripple","651: Last Dive","652: Scaffold","653: Neo-Noir",
	"654: Seasons","655: Zander","656: Orbit Mk01","657: Blueprint","658: Cobra Strike","659: Macabre","660: Hyper Beast","661: Sugar Rush","662: Oni Taiji","663: Briefing","664: Hellfire","665: Aloha",
	"666: Hard Water","667: Woodsman","668: Red Rock","669: Death Grip","670: Death's Head","671: Cut Out","672: Metal Flowers","673: Morris","674: Triqua","675: The Empress","676: High Roller","677: Hunter",
	"678: See Ya Later","679: Goo","680: Off World","681: Leaded Glass","682: Oceanic","683: Llama Cannon","684: Cracked Opal","685: Jungle Slipstream","686: Phantom","687: Tacticat","688: Exposure","689: Ziggy"
};