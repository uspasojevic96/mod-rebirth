
#include "scripts/RebirthLoadPlayer.h"
#include "RebirthManager.h"

RebirthLoadPlayer::RebirthLoadPlayer()
    : PlayerScript("RebirthLoadPlayer", {PLAYERHOOK_ON_LOGIN}) {}

void RebirthLoadPlayer::OnPlayerLogin(Player *player) {
  rebirthManager->Load(player);
}
