//method
#define Screen_get_width (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("get_width"))
#define Screen_get_height (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("get_height"))
#define Screen_SetResolution (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", OBFUSCATE("SetResolution"), 3)

class Screen {
    public:
	static void SetResolution(int width, int height, bool fullscreen) {
        auto _ = reinterpret_cast<void(*)(int , int , bool )>((uintptr_t)Screen_SetResolution);
        return _(width,height,fullscreen);
    }
	static int get_width() {
        auto _ = reinterpret_cast<int(*)()>((uintptr_t)Screen_get_width);
        return _();
    }
	static int get_height() {
        auto _ = reinterpret_cast<int(*)()>((uintptr_t)Screen_get_height);
        return _();
    }
};

#define Camera_get_main (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", OBFUSCATE("get_main"))
#define Camera_WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", OBFUSCATE("WorldToScreenPoint"), 1)

#define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "get_fieldOfView")
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "set_fieldOfView", 1)

#define LogicBattleManager_Instance (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "LogicBattleManager", OBFUSCATE("Instance"))
#define LogicBattleManager_GetBattleState (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "LogicBattleManager", OBFUSCATE("GetBattleState"))
#define LogicBattleManager_GetPlayerLogic (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "LogicBattleManager", OBFUSCATE("GetPlayerLogic"), 1)
#define LogicBattleManager_GetPlayerRealSelf (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "LogicBattleManager", OBFUSCATE("GetPlayerRealSelf"))

#define ShowSelfPlayer_OnUpdate (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowSelfPlayer", "OnUpdate")
#define ShowSelfPlayer_TryUseSkill (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowSelfPlayer", "TryUseSkill", 8)

#define SystemData_GetBattlePlayerInfo (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "SystemData", OBFUSCATE("GetBattlePlayerInfo"), 0)
#define SystemData_m_uiID (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll","","SystemData", OBFUSCATE("m_uiID"))
#define SystemData_battleId (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll","","SystemData", OBFUSCATE("_battleId"))

List<uintptr_t> *GetBattlePlayerInfo() {
    return reinterpret_cast<List<uintptr_t> *(__fastcall *)(void *)>(SystemData_GetBattlePlayerInfo)((void *)0);
}

#define RoomData_lUid (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("lUid"))
#define RoomData_uiZoneId (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("uiZoneId"))
#define RoomData_iCamp (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("iCamp"))
#define RoomData_heroid (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("heroid"))
#define RoomData_uiHeroIDChoose (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("uiHeroIDChoose"))
#define RoomData_iCertify (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("iCertify"))
#define RoomData_summonSkillId (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("summonSkillId"))
#define RoomData_sName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("_sName"))
#define RoomData_uiRankLevel (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("uiRankLevel"))
#define RoomData_iMythPoint (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "SystemData/RoomData", OBFUSCATE("iMythPoint"))

//field
/*
#define BattleData_m_BattleBridge (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "BattleData", OBFUSCATE("m_BattleBridge"))
#define BattleData_battleManager (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", "BattleData", OBFUSCATE("battleManager"))
*/

uintptr_t BattleData_m_BattleBridge, BattleData_battleManager;
void loadBattleData(std::string bData) {
	BattleData_m_BattleBridge = (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", bData.c_str(), OBFUSCATE("m_BattleBridge"));
	BattleData_battleManager = (uintptr_t) Il2CppGetStaticFieldOffset("Assembly-CSharp.dll", "", bData.c_str(), OBFUSCATE("battleManager"));
}

#define BattleBridge_bStartBattle (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleBridge", OBFUSCATE("bStartBattle"))

#define BattleManager_m_LocalPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_LocalPlayerShow"))
#define BattleManager_m_dicPlayerShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_dicPlayerShow"))
#define BattleManager_m_dicMonsterShow (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "BattleManager", OBFUSCATE("m_dicMonsterShow"))

#define ShowEntity_get_InTransformation (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("get_InTransformation"))
#define ShowEntity_Position (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("_Position"))
#define ShowEntity_bShowEntityLayer (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("bShowEntityLayer"))
#define ShowEntity_m_OwnSkillComp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_OwnSkillComp"))
#define ShowEntity_m_RoleName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowEntity", OBFUSCATE("m_RoleName"))

#define ShowOwnSkillComp_m_SkillList (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("ShowOwnSkillComp"), OBFUSCATE("m_SkillList"))
#define ShowOwnSkillComp_skillUseTypeList (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("ShowOwnSkillComp"), OBFUSCATE("skillUseTypeList"))

#define ShowSkillData_m_TranID (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", OBFUSCATE("ShowSkillData"), OBFUSCATE("m_TranID"))

#define ShowPlayer_m_iSummonSkillId (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_iSummonSkillId"))
#define ShowPlayer_m_HeroName (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_HeroName"))
#define ShowPlayer_m_killNum (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_killNum"))
#define ShowPlayer_m_assistNum (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_assistNum"))
#define ShowPlayer_m_KillWildTimes (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "", "ShowPlayer", OBFUSCATE("m_KillWildTimes"))

#define EntityBase_m_ID (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("m_ID"))
#define EntityBase_m_Level (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("<m_Level>k__BackingField"))
#define EntityBase_m_bDeath (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("<m_bDeath>k__BackingField"))
#define EntityBase_m_bSameCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("m_bSameCampType"))
#define EntityBase_m_Hp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("m_Hp"))
#define EntityBase_m_HpMax (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("m_HpMax"))
#define EntityBase_m_EntityCampType (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", "EntityBase", OBFUSCATE("m_EntityCampType"))

#define LogicFighter_m_SkillComp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("LogicFighter"), OBFUSCATE("m_SkillComp"))

#define LogicSkillComp_m_CoolDownComp (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("LogicSkillComp"), OBFUSCATE("m_CoolDownComp"))

#define CoolDownComp_m_DicCoolInfo (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("CoolDownComp"), OBFUSCATE("m_DicCoolInfo"))

#define CoolDownData_GetCoolTime (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "Battle", OBFUSCATE("CoolDownData"), OBFUSCATE("GetCoolTime"))

void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Camera_get_main)();
}

float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}

void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}

Vector3 WorldToScreen(Vector3 position) {
    return reinterpret_cast<Vector3(__fastcall *)(void *, Vector3)>(Camera_WorldToScreenPoint)(get_main(), position);
}

int GetBattleState() {
	auto instance = *(uintptr_t *) ((uintptr_t)LogicBattleManager_Instance);
    if (!instance) return 0;
    return reinterpret_cast<int(__fastcall *)(void*)>(LogicBattleManager_GetBattleState)((void*)instance);
}

uintptr_t GetPlayerLogic(uint id) {
    auto instance = *(uintptr_t *) ((uintptr_t)LogicBattleManager_Instance);
    if (!instance) return 0;
    return reinterpret_cast<uintptr_t(__fastcall *)(void *, uint)>(LogicBattleManager_GetPlayerLogic)((void *)instance, id);
}

int GetCoolTime(void* instance) {
    return reinterpret_cast<int(__fastcall *)(void *)>(CoolDownData_GetCoolTime)(instance);
}

bool get_InTransformation(void* instance) {
    return reinterpret_cast<bool(__fastcall *)(void *)>(ShowEntity_get_InTransformation)(instance);
}
