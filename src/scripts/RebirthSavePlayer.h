#pragma once

#include "PlayerScript.h"

class RebirthSavePlayer : public PlayerScript {
public:
  RebirthSavePlayer();

  void OnPlayerLogout(Player *player);
};
