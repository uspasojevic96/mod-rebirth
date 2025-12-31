#pragma once

#include "PlayerScript.h"

class RebirthPlayer : public PlayerScript {

public:
  RebirthPlayer();
  void OnPlayerGiveXP(Player *player, uint32 &amount, Unit *victim,
                      uint8 xpSource);
  void OnPlayerLevelChanged(Player *player, uint8 oldLevel);
  void OnPlayerLogin(Player *player);
};
