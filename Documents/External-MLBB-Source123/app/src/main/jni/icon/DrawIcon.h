/** xhasbi **/
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "IconList.h"
#include "base64.hpp"

void writeToFile(std::string dir, std::string buf) {
    std::ofstream os(dir.c_str(), std::ios::trunc);
    os.write(buf.c_str(), buf.length());
    os.close();
}

std::string IconAssets(int Id) {
    std::string strICHero;
    switch(Id) {
	default:
	strICHero += iconHeroList[Id];
	}
	return strICHero;
}

std::string SpellAssets(int Id) {
    std::string strICHero;
    switch(Id) {
	default:
	strICHero += iconSpellList[Id];
	}
	return strICHero;
}

bool LoadTextureFromFile(const char* filename, Icon* Image) {
    int image_width = 0;
    int image_height = 0;
    int n;
    unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    Image->texture = image_texture;
    Image->width = image_width;
    Image->height = image_height;

    return true;
}

bool AttachIconDone;
void AttachIcon() {
	std::string packageName = "com.vng.mlbbvn";
	std::ifstream input_file("/data/data/" + packageName + "/.bak");
	if (!input_file.is_open())
	    packageName = "com.mobile.legends";
	int size = sizeof(iconHeroList) / sizeof(iconHeroList[0]);
	for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = "/data/data/" + packageName + "/files/";
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(IconAssets(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        HeroIcon.push_back(Test);
    }
}

bool AttachSpellDone;
void AttachSpell() {
	std::string packageName = "com.vng.mlbbvn";
	std::ifstream input_file("/data/data/" + packageName + "/.bak");
	if (!input_file.is_open())
	    packageName = "com.mobile.legends";
	int size = sizeof(iconSpellList) / sizeof(iconSpellList[0]);
	for (int i = 0;i < size;i++) {
        Icon Test;
        string Path = "/data/data/" + packageName + "/files/";
        Path += to_string(i);
        writeToFile(Path, base64::from_base64(SpellAssets(i)));
        Test.IsValid = LoadTextureFromFile(Path.c_str(), &Test);
        std::remove(Path.c_str());
        SpellIcon.push_back(Test);
    }
}

static float ColorHealth[3] = {0.9f, 0.2f, 0.5f};
float IconAlpha = 1.0f;

namespace ICON {
    int ICSize = 38;
	int ICHealthThin = 3;
}
using namespace ICON;

void DrawIconHero(ImVec2 position, int HeroID, int Hp, int HpMax) {
    auto IconI = ICTexture(HeroID);
	float a_max = ((3.14159265359f * 2));
    float XDX = (ICSize / 2 + 0.121f), XDR = ICSize / 2;
    if (IconI.IsValid) {
        ImGui::GetBackgroundDrawList()->AddImageRounded((void*)(uintptr_t)IconI.texture, ImVec2(position.x - ICSize + XDX, position.y - ICSize + XDX), ImVec2(position.x + ICSize - XDX, position.y + ICSize - XDX), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255,255,255, IconAlpha * 255), 25.0f);
		ImGui::GetBackgroundDrawList()->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, IconAlpha * 255), ImDrawFlags_None, ICHealthThin);
    }
}

void DrawHero(ImVec2 position, int HeroID, int Hp, int HpMax, int Size = 64, int HealthThin = 3) {
    auto IconI = ICTexture(HeroID);
	float a_max = ((3.14159265359f * 2));
    float XDX = (Size / 2 + 0.121f), XDR = Size / 2;
    if (IconI.IsValid) {
        ImGui::GetBackgroundDrawList()->AddImageRounded((void*)(uintptr_t)IconI.texture, ImVec2(position.x - Size + XDX, position.y - Size + XDX), ImVec2(position.x + Size - XDX, position.y + Size - XDX), ImVec2(0, 0), ImVec2(1, 1), IM_COL32(255,255,255, IconAlpha * 255), 25.0f);
		ImGui::GetBackgroundDrawList()->PathArcTo(position, XDR, (-(a_max / 4.0f)) + (a_max / HpMax) * (HpMax - Hp), a_max - (a_max / 4.0f));
        ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(ColorHealth[0] * 255, ColorHealth[1] * 255, ColorHealth[2] * 255, IconAlpha * 255), ImDrawFlags_None, HealthThin);
    }
}

void RoomInfoHero(int HeroID, float Size = 38) {
    auto IconI = ICTexture(HeroID);
    if (IconI.IsValid) {
		ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(Size, Size));
	}
}

void RoomInfoSpell(int HeroID, float Size = 38) {
    auto IconI = SpellTexture(HeroID);
    if (IconI.IsValid) {
		ImGui::Image((void*)(uintptr_t)IconI.texture, ImVec2(Size, Size));
	}
}
