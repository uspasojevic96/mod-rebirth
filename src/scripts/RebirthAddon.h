#pragma once

#include "Channel.h"
#include "Player.h"
#include "PlayerScript.h"

class RebirthAddon : public PlayerScript {
public:
  RebirthAddon();

  bool OnPlayerCanUseChat(Player *player, uint32 type, uint32 language,
                          std::string &msg, Player *receiver);
};
