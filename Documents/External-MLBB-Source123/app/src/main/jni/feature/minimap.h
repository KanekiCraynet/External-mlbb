//
// Created by hasbi on 4/9/2023.
//

namespace Minimap {
    ImVec2 StartPos = {(float)105, (float)0};
	int MapSize = 341; //width & height
}

using namespace Minimap;

Vector2 WorldToMinimap(uint CampType, Vector3 HeroPosition) {
    float angle = (CampType == 2 ? 314.60f : 134.76f) * 0.017453292519943295;
    float angleCos = (float)std::cos(angle);
    float angleSin = (float)std::sin(angle);
    Vector2 Res0;
    Res0.x = (angleCos * HeroPosition.x - angleSin * (HeroPosition.z * -1)) / 74.11f;
    Res0.y = (angleSin * HeroPosition.x + angleCos * (HeroPosition.z * -1)) / 74.11f;
    Vector2 Res1;
    Res1.x = (Res0.x * MapSize) + StartPos.x + MapSize / 2.f;
    Res1.y = (Res0.y * MapSize) + StartPos.y + MapSize / 2.f;
    return Res1;
}
