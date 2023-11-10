#include "ICON.h"
#include "SPELL.h"

struct Icon {
    GLuint texture = 0;
    int width = 0;
    int height = 0;
    bool IsValid = false;
};

std::vector<Icon> HeroIcon;
std::vector<Icon> SpellIcon;

Icon ICTexture(int Id) {
    switch(Id) {
	case 9995:
		return HeroIcon[18];
        break;
	case 9996:
		return HeroIcon[16];
        break;
	case 9997:
		return HeroIcon[6];
        break;
	case 9998:
		return HeroIcon[16];
        break;
	case 9999:
		return HeroIcon[18];
        break;
	default:
	return HeroIcon[Id];
	}
	return HeroIcon[Id];
}

Icon SpellTexture(int Id) {
    switch(Id) {
	case 20060:
		return SpellIcon[1];
        break;
	case 20160:
		return SpellIcon[2];
        break;
	case 20150:
		return SpellIcon[3];
        break;
	case 20140:
		return SpellIcon[4];
        break;
	case 20100:
		return SpellIcon[5];
        break;
	case 20030:
		return SpellIcon[6];
        break;
	case 20070:
		return SpellIcon[7];
        break;    
	case 20080:
		return SpellIcon[8];
        break;
	case 20020:
		return SpellIcon[9];
        break;    
	case 20050:
		return SpellIcon[10];
        break;
	case 20040:
		return SpellIcon[11];
        break;
	case 20190:
		return SpellIcon[12];
        break;
	default:
	return SpellIcon[Id];
	}
	return SpellIcon[Id];
}