#pragma once

#include "PlayerScript.h"

class RebirthLoadPlayer : public PlayerScript {
public:
  RebirthLoadPlayer();

  void OnPlayerLogin(Player *player);
};
