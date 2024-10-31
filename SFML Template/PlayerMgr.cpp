#include "stdafx.h"
#include "PlayerMgr.h"

void PlayerMgr::SetCharacterTexId(int playerId, const std::string& textureId)
{
    if (playerId == 1)
    {
        playerOneTexId = textureId;
        return;
    }
    else if (playerId == 2)
    {
        playerTwoTexId = textureId;
        return;
    }
    return;
}

std::string PlayerMgr::GetCharacterTexId(int playerId) const
{
    return (playerId == 1) ? playerOneTexId : playerTwoTexId;
}
