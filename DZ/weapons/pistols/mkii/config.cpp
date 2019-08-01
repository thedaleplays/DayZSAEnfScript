////////////////////////////////////////////////////////////////////
//DeRap: weapons_pistols\mkii\config.bin
//Produced from mikero's Dos Tools Dll version 7.27
//https://bytex.market/products/item/weodpphdknnzm70o0h8q/Mikero%27s%20Dos%20Tools
//'now' is Thu Aug 01 15:00:25 2019 : 'file' last modified on Wed Jun 12 15:00:50 2019
////////////////////////////////////////////////////////////////////

#define _ARMA_

//(8 Enums)
enum {
	destructengine = 2,
	destructdefault = 6,
	destructwreck = 7,
	destructtree = 3,
	destructtent = 4,
	destructno = 0,
	destructman = 5,
	destructbuilding = 1
};

class CfgPatches
{
	class DZ_Pistols_mkii
	{
		units[] = {"mkii"};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Pistols"};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class cfgWeapons
{
	class Pistol_Base;
	class MKII_Base: Pistol_Base
	{
		scope = 0;
		weight = 1300;
		absorbency = 0.0;
		repairableWithKits[] = {5,1};
		repairCosts[] = {30.0,25.0};
		modelOptics = "-";
		distanceZoomMin = 100;
		distanceZoomMax = 100;
		value = 0;
		chamberSize = 1;
		chamberedRound = "";
		magazines[] = {"Mag_MKII_10Rnd"};
		chamberableFrom[] = {"Ammo_22"};
		ejectType = 1;
		recoilModifier[] = {1,1,1};
		drySound[] = {"dz\sounds\weapons\firearms\FNX45\FNX_dry",0.5,1,20};
		reloadMagazineSound[] = {"dz\sounds\weapons\firearms\MkII\MkII_reload",0.7,1,20};
		reloadAction = "ReloadRugerMK2";
		modes[] = {"Single"};
		class Single: Mode_SemiAuto
		{
			soundSetShot[] = {"AmphibianS_Shot_SoundSet","AmphibianS_Tail_SoundSet","AmphibianS_InteriorTail_SoundSet"};
			soundSetShotExt[] = {{"AmphibianS_silencerHomeMade_SoundSet","AmphibianS_silencerHomeMadeTail_SoundSet","AmphibianS_InteriorTail_SoundSet"}};
			begin1[] = {"dz\sounds\weapons\firearms\MkII\MkII_close_0",0.8,1,80};
			begin2[] = {"dz\sounds\weapons\firearms\MkII\MkII_close_1",0.8,1,80};
			begin3[] = {"dz\sounds\weapons\firearms\MkII\MkII_close_2",0.8,1,80};
			soundBegin[] = {"begin1",0.33333,"begin2",0.33333,"begin3",0.33333};
			beginSilenced_HomeMade[] = {"dz\sounds\weapons\firearms\MkII\MkII_close_2",0.02,1,20};
			soundBeginExt[] = {{"beginSilenced_HomeMade",1}};
			reloadTime = 0.08;
			recoil = "recoil_mkii";
			recoilProne = "recoil_mkii_prone";
			dispersion = 0.006;
			magazineSlot = "magazine";
		};
		class NoiseShoot
		{
			strength = 10.0;
			type = "shot";
		};
	};
	class MKII: MKII_Base
	{
		scope = 2;
		displayName = "$STR_cfgWeapons_MKII0";
		descriptionShort = "$STR_cfgWeapons_MKII1";
		model = "\dz\weapons\pistols\mkii\rugerMKII.p3d";
		attachments[] = {"suppressorImpro"};
		itemSize[] = {3,3};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"DZ\weapons\pistols\mkii\data\ruger_metal_1.rvmat"}},{0.7,{"DZ\weapons\pistols\mkii\data\ruger_metal_1.rvmat"}},{0.5,{"DZ\weapons\pistols\mkii\data\ruger_metal_1_damage.rvmat"}},{0.3,{"DZ\weapons\pistols\mkii\data\ruger_metal_1_damage.rvmat"}},{0.0,{"DZ\weapons\pistols\mkii\data\ruger_metal_1_destruct.rvmat"}}};
				};
			};
		};
	};
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class Proxymkii: ProxyAttachment
	{
		scope = 2;
		inventorySlot = "pistol";
		model = "\dz\weapons\pistols\mkii\rugerMKII.p3d";
	};
};
