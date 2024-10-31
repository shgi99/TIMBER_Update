#pragma once
#include "Singleton.h"
#include <string>

class PlayerMgr : public Singleton<PlayerMgr>
{
	friend class Singleton<PlayerMgr>;

private:
	PlayerMgr() = default;

	std::string playerOneTexId;
	std::string playerTwoTexId;
public:
	void SetCharacterTexId(int playerId, const std::string& textureId);
	std::string GetCharacterTexId(int playerId) const;
};

#define PLAYER_MGR (PlayerMgr::Instance())