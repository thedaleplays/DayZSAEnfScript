enum ImpactTypes
{
	UNKNOWN;
	STOP;
	PENETRATE;
	RICOCHET;
	MELEE;
}

class ImpactMaterials
{
	ref static map<string, typename> 	m_ImpactEffect;
	static int 							m_LastRegisteredMaterial = 0;
	
	// Surface effects
	static int CONCRETE 					= RegisterSurface("Hit_Concrete");
	static int GRAVEL 						= RegisterSurface("Hit_Gravel");
	static int DIRT 						= RegisterSurface("Hit_Dirt");
	static int FOLIAGE 						= RegisterSurface("Hit_Foliage");
	static int WOOD 						= RegisterSurface("Hit_Wood");
	static int METAL 						= RegisterSurface("Hit_Metal");
	static int GLASS 						= RegisterSurface("Hit_Glass");
	static int RUBBER 						= RegisterSurface("Hit_Rubber");
	static int PLASTER 						= RegisterSurface("Hit_Plaster");
	static int MEATBONES					= RegisterSurface("Hit_MeatBones");
	static int MEATBONES_SHOVEL				= RegisterSurface("Hit_MeatBones_MeleeShovel");
	static int MEATBONES_PIPEWRENCH			= RegisterSurface("Hit_MeatBones_MeleePipeWrench");
	static int MEATBONES_WRENCH				= RegisterSurface("Hit_MeatBones_MeleeWrench");
	static int MEATBONES_FIST				= RegisterSurface("Hit_MeatBones_MeleeFist");
	static int UNDEFINED 					= RegisterSurface("Hit_Undefined");
	
	static int RegisterSurface(string surface)
	{
		if (!m_ImpactEffect)
			m_ImpactEffect = new map<string, typename>;
		
		m_ImpactEffect.Insert(surface, surface.ToType());
		 
		return ++m_LastRegisteredMaterial;
	}
	
	static typename GetImpactEffect(string surface, string ammoType)
	{
		string key = surface + "_" + ammoType;
		
		typename eff_type = m_ImpactEffect.Get(key);
		
		if (eff_type)
			return eff_type;
		else
		{
			return m_ImpactEffect.Get(surface);
		}
	}
	
	static void EvaluateImpactEffect(Object directHit, string surface, vector pos, int impact_type, vector surfNormal, vector exitPos, vector inSpeed, vector outSpeed, bool deflected, string ammoType)
	{
		Print(ammoType);
		
		if (impact_type == ImpactTypes.UNKNOWN)
			impact_type = ImpactTypes.STOP;
		
		if (deflected)
			impact_type = ImpactTypes.RICOCHET;
		else if (outSpeed)
			impact_type = ImpactTypes.PENETRATE;
		
		
		EffBulletImpactBase eff = GetImpactEffect(surface, ammoType).Spawn();
		
		if (!eff) // handle undefined surface
		{
			eff = EffBulletImpactBase.Cast( surface.ToType().Spawn() );
			
			if (eff)
			{
				RegisterSurface(surface);
				string error = "Warning! Unregistered surface for bullet impact effect (" + surface + "). Register this surface in ImpactEffects.c for better optimization.";
				Error(error);
			}
			else
			{
				if (directHit)
				{
					string classname = directHit.ClassName();
					string displayname = directHit.GetDisplayName();
					string object_type = directHit.GetType();
					
					if (object_type == "")
						object_type = "OBJECT_WITHOUT_CONFIG_CLASS";
					
					string error2 = "Error! Object '" + object_type + "' with model file: " + directHit.GetModelName() + ".p3d has undefined 'Hit_...' material! Thus cannot play appropriate impact effect.";
					Print(error2);
					string undefined_surface = "Hit_Undefined";
					eff = GetImpactEffect(undefined_surface, ammoType).Spawn();
				}
			}
		}
		
		if (eff)
		{
			eff.EvaluateEffect(pos, impact_type, surfNormal, exitPos, inSpeed, outSpeed, ammoType);
			SEffectManager.PlayInWorld( eff, pos );
		}
	}
}