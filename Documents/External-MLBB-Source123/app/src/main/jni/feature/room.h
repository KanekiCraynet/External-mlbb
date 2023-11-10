std::string strRank[] = {
    "Warrior III * 1",
    "Warrior III * 2",
    "Warrior III * 3",
    "Warrior II * 0",
    "Warrior II * 1",
    "Warrior II * 2",
    "Warrior II * 3",
    "Warrior I * 0",
    "Warrior I * 1",
    "Warrior I * 2",
    "Warrior I * 3",
    "Elite III * 0",
    "Elite III * 1",
    "Elite III * 2",
    "Elite III * 3",
    "Elite III * 4",
    "Elite II * 0",
    "Elite II * 1",
    "Elite II * 2",
    "Elite II * 3",
    "Elite II * 4",
    "Elite I * 0",
    "Elite I * 1",
    "Elite I * 2",
    "Elite I * 3",
    "Elite I * 4",
    "Master IV * 0",
    "Master IV * 1",
    "Master IV * 2",
    "Master IV * 3",
    "Master IV * 4",
    "Master III * 0",
    "Master III * 1",
    "Master III * 2",
    "Master III * 3",
    "Master III * 4",
    "Master II * 0",
    "Master II * 1",
    "Master II * 2",
    "Master II * 3",
    "Master II * 4",
    "Master I * 0",
    "Master I * 1",
    "Master I * 2",
    "Master I * 3",
    "Master I * 4",
    "Grandmaster V * 0",
    "Grandmaster V * 1",
    "Grandmaster V * 2",
    "Grandmaster V * 3",
    "Grandmaster V * 4",
    "Grandmaster V * 5",
    "Grandmaster IV * 0",
    "Grandmaster IV * 1",
    "Grandmaster IV * 2",
    "Grandmaster IV * 3",
    "Grandmaster IV * 4",
    "Grandmaster IV * 5",
    "Grandmaster III * 0",
    "Grandmaster III * 1",
    "Grandmaster III * 2",
    "Grandmaster III * 3",
    "Grandmaster III * 4",
    "Grandmaster III * 5",
    "Grandmaster II * 0",
    "Grandmaster II * 1",
    "Grandmaster II * 2",
    "Grandmaster II * 3",
    "Grandmaster II * 4",
    "Grandmaster II * 5",
    "Grandmaster I * 0",
    "Grandmaster I * 1",
    "Grandmaster I * 2",
    "Grandmaster I * 3",
    "Grandmaster I * 4",
    "Grandmaster I * 5",
    "Epic V * 0",
    "Epic V * 1",
    "Epic V * 2",
    "Epic V * 3",
    "Epic V * 4",
    "Epic V * 5",
    "Epic IV * 0",
    "Epic IV * 1",
    "Epic IV * 2",
    "Epic IV * 3",
    "Epic IV * 4",
    "Epic IV * 5",
    "Epic III * 0",
    "Epic III * 1",
    "Epic III * 2",
    "Epic III * 3",
    "Epic III * 4",
    "Epic III * 5",
    "Epic II * 0",
    "Epic II * 1",
    "Epic II * 2",
    "Epic II * 3",
    "Epic II * 4",
    "Epic II * 5",
    "Epic I * 0",
    "Epic I * 1",
    "Epic I * 2",
    "Epic I * 3",
    "Epic I * 4",
    "Epic I * 5",
    "Legend V * 0",
    "Legend V * 1",
    "Legend V * 2",
    "Legend V * 3",
    "Legend V * 4",
    "Legend V * 5",
    "Legend IV * 0",
    "Legend IV * 1",
    "Legend IV * 2",
    "Legend IV * 3",
    "Legend IV * 4",
    "Legend IV * 5",
    "Legend III * 0",
    "Legend III * 1",
    "Legend III * 2",
    "Legend III * 3",
    "Legend III * 4",
    "Legend III * 5",
    "Legend II * 0",
    "Legend II * 1",
    "Legend II * 2",
    "Legend II * 3",
    "Legend II * 4",
    "Legend II * 5",
    "Legend I * 0",
    "Legend I * 1",
    "Legend I * 2",
    "Legend I * 3",
    "Legend I * 4",
    "Legend I * 5",
    "Mythic Grading"
};

std::tuple<std::string, std::string> SplitRankAndStars(const int uiRankLevel, const int iMythPoint) {
    if (uiRankLevel <= 135) {
        std::string rankWithStars = strRank[uiRankLevel];
        std::size_t starPos = rankWithStars.find('*');
        if (starPos != std::string::npos) {
            std::string rankName = rankWithStars.substr(0, starPos - 1);
            std::string starCount = rankWithStars.substr(starPos + 2);
            return std::make_tuple(rankName, starCount);
        }
    }
    std::string nameMythic = "Mythic";
    float starMythic = (float)iMythPoint * (50.0 / 600.0);
    if ((int)starMythic > 24)  nameMythic = "Mythical Honor";
    if ((int)starMythic > 49)  nameMythic = "Mythical Glory";
    if ((int)starMythic > 99)  nameMythic = "Mythical Immortal";
    return std::make_tuple(nameMythic, std::to_string((int)starMythic));
}

std::string VerifiedToString(int iCertify) {
    std::string str = std::string(OBFUSCATE("-"));
    if (iCertify == 0) {
        str = std::string(OBFUSCATE("No"));
    } else {
        str = std::string(OBFUSCATE("Yes"));
    }
    return str;
}

struct PlayerData {
	std::string Name;
    std::string UserID;
	std::string Verified;
    std::string Rank;
    std::string Star;
    int HeroID;
    int Spell;
};

struct {
    PlayerData PlayerB[10];
    PlayerData PlayerR[10];
} RoomInfo;

void RoomInfoList() {
    auto iBattleState = GetBattleState();
    if (iBattleState == 2 || iBattleState == 3) {
        List<uintptr_t> *m_RoomPlayerInfo = GetBattlePlayerInfo();
        if (!m_RoomPlayerInfo) return;
		int PlayerB = 0, PlayerR = 0, iSelfCamp = -1;
		int m_uiID = *(int *)(SystemData_m_uiID);
        for (int i = 0; i < m_RoomPlayerInfo->getSize(); i++) {
            auto roomData = m_RoomPlayerInfo->getItems()[i];
            if (!roomData) continue;
            auto iCamp = *(int *) ((uintptr_t)roomData + RoomData_iCamp);
            auto lUid = *(int *) ((uintptr_t)roomData + RoomData_lUid);
            if (lUid != m_uiID) continue;
            iSelfCamp = iCamp;
            break;
        }
        for (int i = 0; i < m_RoomPlayerInfo->getSize(); i++) {
            auto roomData = m_RoomPlayerInfo->getItems()[i];
            if (!roomData) continue;
            auto iCamp = *(int *) ((uintptr_t)roomData + RoomData_iCamp);
            auto lUid = *(int *) ((uintptr_t)roomData + RoomData_lUid);
            auto uiZoneId = *(int *) ((uintptr_t)roomData + RoomData_uiZoneId);
			auto heroid = *(int *) ((uintptr_t)roomData + RoomData_heroid);
			auto uiHeroIDChoose = *(int *) ((uintptr_t)roomData + RoomData_uiHeroIDChoose);
            auto summonSkillId = *(int *) ((uintptr_t)roomData + RoomData_summonSkillId);
            auto *_sName = *(String **) ((uintptr_t)roomData + RoomData_sName);
            auto iCertify = *(int *) ((uintptr_t)roomData + RoomData_iCertify);
            auto uiRankLevel = *(int *) ((uintptr_t)roomData + RoomData_uiRankLevel);
            auto iMythPoint = *(int *) ((uintptr_t)roomData + RoomData_iMythPoint);
            auto splitRank = SplitRankAndStars(uiRankLevel, iMythPoint);
            std::string rankName = std::get<0>(splitRank);
            std::string starCount = std::get<1>(splitRank);
            if (iCamp == iSelfCamp) {

                RoomInfo.PlayerB[PlayerB].UserID = to_string(lUid) + " (" + to_string(uiZoneId) + ")";
                if (_sName) RoomInfo.PlayerB[PlayerB].Name = _sName->toString();
                RoomInfo.PlayerB[PlayerB].Rank = rankName;
                RoomInfo.PlayerB[PlayerB].Star = starCount;
                RoomInfo.PlayerB[PlayerB].Verified = VerifiedToString(iCertify);
				RoomInfo.PlayerB[PlayerB].HeroID = (uiHeroIDChoose) ? uiHeroIDChoose : heroid;
                RoomInfo.PlayerB[PlayerB].Spell = summonSkillId;

                PlayerB++;
            } else {

                RoomInfo.PlayerR[PlayerR].UserID = to_string(lUid) + " (" + to_string(uiZoneId) + ")";
                if (_sName) RoomInfo.PlayerR[PlayerR].Name = _sName->toString();
                RoomInfo.PlayerR[PlayerR].Rank = rankName;
                RoomInfo.PlayerR[PlayerR].Star = starCount;
                RoomInfo.PlayerR[PlayerR].Verified = VerifiedToString(iCertify);
                RoomInfo.PlayerR[PlayerR].HeroID = (uiHeroIDChoose) ? uiHeroIDChoose : heroid;
                RoomInfo.PlayerR[PlayerR].Spell = summonSkillId;

                PlayerR++;
            }
        }
    }
}
