#include "feature/minimap.h"

bool showMenu = true;
bool bFullChecked = false;

unsigned int gpCrash = 0xfa91b9cd;
static int crash(int randomval){
    volatile int *p = (int *)gpCrash;
    p += randomval;
    p += *p + randomval;
    /* If it still doesnt crash..crash using null pointer */
    p = 0;
    p += *p;
    return *p;
}

void CenteredText(ImColor color, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    const char *text, *text_end;
    ImFormatStringToTempBufferV(&text, &text_end, fmt, args);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text, text_end).x) * 0.5);
    ImGui::TextColoredV(color, fmt, args);
    va_end(args);
}

inline ImVec4 RGBA2ImVec4(int r, int g, int b, int a) {
    float newr = (float)r / 255.0f;
    float newg = (float)g / 255.0f;
    float newb = (float)b / 255.0f;
    float newa = (float)a / 255.0f;
    return ImVec4(newr, newg, newb, newa);
}

struct sFeature {
    //ESP Player
    bool ESPLine;
    bool ESPRound;
    bool ESPName;
	bool ESPHero;
    bool ESPHealth;
    bool ESPAlert;

    //ESP Info
    bool ESPSkillCD;
    bool ESPSpellCD;

    //ESP Jungle
    bool ESPMRound;
    bool ESPMHealth;
	
	//Minimap
    bool MinimapIcon;
    bool HideLine;
};
sFeature Feature{0};

static float SetFieldOfView = 0, GetFieldOfView = 0;

void HideMenu(bool& bShow) {
    if (bShow) {
        ImGui::OpenPopup("ConfirmHide");
    }

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (ImGui::BeginPopupModal("ConfirmHide", 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse))
    {
        ImGui::Text("Are you sure you want to hide the menu?");
        if (ImGui::Button("Yes", ImVec2(ImGui::GetContentRegionAvail().x / 2, 0)))
        {
            showMenu = false;
            bShow = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("No", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
        {
            bShow = false;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

std::string msg;
void LoginThread(const std::string &user_key, bool *success) {
    msg = Login(g_vm, user_key.c_str(), success);
}

void ShowMenu()
{
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(650, 680), ImGuiCond_FirstUseEver);

    ImGuiIO& io = ImGui::GetIO();

    static float window_scale;
    if (!window_scale) window_scale = 1.0f;
    io.FontGlobalScale = window_scale;

    static bool isLogin = false, isSave = false;
    static char s[64];
    if (isLogin && !isSave) {
        SharedPreferences sharedPref(GetJNIEnv(g_vm), "divarvian_sharedpref");
        SharedPreferences_Editor editor=sharedPref.edit();
        editor.putString("key", s);
        editor.commit();
        isSave = true;
    }

    static bool isPopUpHide = false;
    HideMenu(isPopUpHide);
	
    static bool bFlagAutoResize = true;
    static ImGuiWindowFlags window_flags;
    if (bFlagAutoResize) {
        window_flags = ImGuiWindowFlags_AlwaysAutoResize;
    } else {
        window_flags = ImGuiWindowFlags_None;
    }

    if (isLogin && title == "") crash(0x3d5f);
	if (isLogin && title != "") {
		loadBattleData(battleData);
		bFullChecked = true;
	}
	std::string FULLTITLE = std::string(OBFUSCATE("SENSEI")) + std::string(" | ") + std::string("LITE 1.0") + std::string(" ") + std::string(ABI);
    if (!ImGui::Begin(FULLTITLE.c_str(), 0, window_flags))
    {
        ImGui::End();
        return;
    }

    if (!isLogin) {
        if (ImGui::BeginTabBar("TabLogin", ImGuiTabBarFlags_FittingPolicyScroll)) {
            if (ImGui::BeginTabItem("Login Menu")) {
                ImGui::BeginGroupPanel("Please Login! (Copy Key to Clipboard)", ImVec2(0.0f, 0.0f));
                {
                    ImGui::PushItemWidth(-1);
                    ImGui::InputText("##key", s, sizeof s);
                    ImGui::PopItemWidth();

                    if (ImGui::Button("Paste Key", ImVec2(ImGui::GetContentRegionAvail().x / 2, 0))) {
                        auto key = getClipboardText(g_vm);
                        strncpy(s, key.c_str(), sizeof s);
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Load Saved Key", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        SharedPreferences sharedPref(GetJNIEnv(g_vm), "divarvian_sharedpref");
                        auto key = sharedPref.getString("key");
                        strncpy(s, key.c_str(), sizeof s);
                    }

                    if (ImGui::Button("Login", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        std::thread login_thread(LoginThread, std::string(s), &isLogin);
                        login_thread.detach();
                    }

                    ImGui::TextColored(RGBA2ImVec4(255, 255, 0, 255), "%s", msg.c_str());
                    ImGui::Spacing();
                }
                ImGui::EndGroupPanel();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    } else {
        if (ImGui::BeginTabBar("Tab", ImGuiTabBarFlags_FittingPolicyScroll)) {
            if (ImGui::BeginTabItem("Visual Menu")) {
                ImGui::BeginGroupPanel("Player ESP", ImVec2(0.0f, 0.0f));
                {
                    ImGui::Checkbox("Line", &Feature.ESPLine);
                    //ImGui::Checkbox("Round", &Feature.ESPRound);
                    ImGui::Checkbox("Name", &Feature.ESPName);
					//ImGui::Checkbox("Hero", &Feature.ESPHero);
                    ImGui::Checkbox("Health", &Feature.ESPHealth);
                    ImGui::Spacing();
                }
                ImGui::EndGroupPanel();

                ImGui::SameLine();

                ImGui::BeginGroup();
                {
                    ImGui::BeginGroupPanel("Jungle ESP", ImVec2(-1.0f, 0.0f));
                    {
                        ImGui::Checkbox("ESP Round", &Feature.ESPMRound);
						//ImGui::SameLine();
                        //ImGui::Checkbox("ESP Health", &Feature.ESPMHealth);
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();

                    ImGui::BeginGroupPanel("Info ESP", ImVec2(-1.0f, 0.0f));
                    {
						ImGui::Checkbox("Skill CD", &Feature.ESPSkillCD);
                        ImGui::Checkbox("Spell CD", &Feature.ESPSpellCD);
                        //ImGui::Checkbox("Show Hero Alert", &Feature.ESPAlert);
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();
                }
                ImGui::EndGroup();
				
				ImGui::BeginGroupPanel("Additional", ImVec2(-1.0f, 0.0f));
                {
                    ImGui::Text("Drone View:");
                    ImGui::SliderFloat("##DroneView", &SetFieldOfView, 0, 30, "%.1f");
                    ImGui::Spacing();
                }
                ImGui::EndGroupPanel();
				
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Room Info")) {
				if (bFullChecked) RoomInfoList();
                ImGui::TextColored(ImVec4(0.0f, 0.8f, 1.0f, 1.0f), "Team");
                if (ImGui::BeginTable("##Team", 7, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                    ImGui::TableSetupColumn("Name");
					ImGui::TableSetupColumn("ID");
                    ImGui::TableSetupColumn("Verified");
                    ImGui::TableSetupColumn("Rank");
                    ImGui::TableSetupColumn("Star");
					ImGui::TableSetupColumn("Hero");
					ImGui::TableSetupColumn("Spell");
                    ImGui::TableHeadersRow();
                    for (int row = 0; row < 5; row++) {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 7; column++) {
                            ImGui::TableSetColumnIndex(column);
                            char buf[32];
                            if (column == 0) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Name.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 1) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].UserID.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 2) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Verified.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 3) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Rank.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 4) {
                                sprintf(buf, "%s", RoomInfo.PlayerB[row].Star.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 5) {
                                RoomInfoHero(RoomInfo.PlayerB[row].HeroID);
                            } else if (column == 6) {
                                RoomInfoSpell(RoomInfo.PlayerB[row].Spell);
                            }
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Enemy");
                if (ImGui::BeginTable("##Enemy", 7, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner)) {
                    ImGui::TableSetupColumn("Name");
					ImGui::TableSetupColumn("ID");
                    ImGui::TableSetupColumn("Verified");
                    ImGui::TableSetupColumn("Rank");
                    ImGui::TableSetupColumn("Star");
					ImGui::TableSetupColumn("Hero");
					ImGui::TableSetupColumn("Spell");
                    ImGui::TableHeadersRow();
                    for (int row = 0; row < 5; row++) {
                        ImGui::TableNextRow();
                        for (int column = 0; column < 7; column++) {
                            ImGui::TableSetColumnIndex(column);
                            char buf[32];
                            if (column == 0) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Name.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 1) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].UserID.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 2) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Verified.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 3) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Rank.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 4) {
                                sprintf(buf, "%s", RoomInfo.PlayerR[row].Star.c_str());
                                ImGui::TextUnformatted(buf);
                            } else if (column == 5) {
                                RoomInfoHero(RoomInfo.PlayerR[row].HeroID);
                            } else if (column == 6) {
                                RoomInfoSpell(RoomInfo.PlayerR[row].Spell);
                            }
                        }
                    }
                    ImGui::EndTable();
                }
                ImGui::EndTabItem();
            }
			//if (ImGui::BeginTabItem("Minimap Menu")) {
                //ImGui::Checkbox("Minimap Icon", &Feature.MinimapIcon);
               // if (!Feature.MinimapIcon) ImGui::BeginDisabled();
                //ImGui::SameLine();
                //ImGui::Checkbox("Hide Line", &Feature.HideLine);
                //ImGui::BeginGroup();
                //{
                    //ImGui::BeginGroupPanel("MiniMap Adjustable", ImVec2(-1.0f, 0.0f));
                   // {
                        //ImGui::BeginGroupPanel("Map Position", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
                        //{
                            //ImGui::PushItemWidth(-1);
                            //ImGui::SliderFloat("##MapPosition", &StartPos.x, 0.0f, (float)(screenWidth / 2));
                            //ImGui::PopItemWidth();
                            //ImGui::Spacing();
                        //}
                        //ImGui::EndGroupPanel();

                        //ImGui::BeginGroupPanel("Map Size", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
                        //{
                            //ImGui::PushItemWidth(-1);
                            //ImGui::SliderInt("##MapSize", &MapSize, 0, 800);
                            //ImGui::PopItemWidth();
                            //ImGui::Spacing();
                        //}
                        //ImGui::EndGroupPanel();

                        //ImGui::BeginGroupPanel("Icon Size", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
                        //{
                            //ImGui::PushItemWidth(-1);
                            //ImGui::SliderInt("##IconSize", &ICSize, 0, 100);
                            //ImGui::PopItemWidth();
                            //ImGui::Spacing();
                        //}
                        //ImGui::EndGroupPanel();

                        //ImGui::BeginGroupPanel("Health Thin", ImVec2(ImGui::GetContentRegionAvail().x, 0.0f));
                        //{
                            //ImGui::PushItemWidth(-1);
                            //ImGui::SliderInt("##HealthThin", &ICHealthThin, 0, 10);
                            //ImGui::PopItemWidth();
                            //ImGui::Spacing();
                        //}
                        //ImGui::EndGroupPanel();
                        //ImGui::Spacing();
                    //}
                    //ImGui::EndGroupPanel();
                    //if (ImGui::Button("Save Setting", ImVec2(ImGui::GetContentRegionAvail().x / 2, 0))) {
                        //SharedPreferences sharedPref(GetJNIEnv(g_vm), "divarvian_sharedpref");
                        //SharedPreferences_Editor editor=sharedPref.edit();
                        //editor.putFloat("StartPosX", StartPos.x);
                        //editor.putFloat("StartPosY", StartPos.y);
                        //editor.putFloat("MapSize", MapSize);
                        //editor.putFloat("ICSize", ICSize);
                        //editor.putFloat("ICHealthThin", ICHealthThin);
                        //editor.commit();
                    //}
					
					//ImGui::SameLine();
					
                    //if (ImGui::Button("Load Setting", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        //SharedPreferences sharedPref(GetJNIEnv(g_vm), "divarvian_sharedpref");
                        //StartPos.x = sharedPref.getFloat("StartPosX");
                        //StartPos.y = sharedPref.getFloat("StartPosY");
                        //MapSize = sharedPref.getFloat("MapSize");
                        //ICSize = sharedPref.getFloat("ICSize");
                        //ICHealthThin = sharedPref.getFloat("ICHealthThin");
                    //}
					
					//if (ImGui::Button("Restore Setting", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        //SharedPreferences sharedPref(GetJNIEnv(g_vm), "divarvian_sharedpref");
                        //StartPos.x = 105.0f;
                        //StartPos.y = 0.0f;
                        //MapSize = 341.0f;
                        //ICSize = 38.0f;
                        //ICHealthThin = 3.0f;
                    //}
                //}
                //ImGui::EndGroup();
                //if (!Feature.MinimapIcon) ImGui::EndDisabled();
                //ImGui::EndTabItem();
            //}
            if (ImGui::BeginTabItem("Setting")) {
                ImGui::BeginGroupPanel("Menu Setting", ImVec2(-1.0f, 0.0f));
                {
                    ImGui::Checkbox("Auto Resize", &bFlagAutoResize);
                    ImGui::BeginGroupPanel("Window Size", ImVec2(-1.0f, 0.0f));
                    {
                        ImGui::PushItemWidth(-1);
                        ImGui::SliderFloat("##Scale", &window_scale, 0.5f, 1.5f, "%.1f");
                        ImGui::PopItemWidth();
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();

                    if (ImGui::Button("Hide Menu", ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
                        isPopUpHide = true;
                    }

                    ImGui::BeginGroupPanel("English", ImVec2(-1.0f, 0.0f));
                    {
                        ImGui::TextColored(RGBA2ImVec4(255, 255, 0, 255), "To display the menu again,");
                        ImGui::TextColored(RGBA2ImVec4(255, 255, 0, 255), "simply touch on the lower left corner of your screen.");
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();

                    ImGui::BeginGroupPanel("Indonesia", ImVec2(-1.0f, 0.0f));
                    {
                        ImGui::TextColored(RGBA2ImVec4(255, 255, 0, 255), "Untuk menampilkan kembali menu,");
                        ImGui::TextColored(RGBA2ImVec4(255, 255, 0, 255), "cukup sentuh di pojok kiri bawah layar Anda.");
                        ImGui::Spacing();
                    }
                    ImGui::EndGroupPanel();

                    ImGui::Spacing();
                }
                ImGui::EndGroupPanel();
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        }
    }
}
