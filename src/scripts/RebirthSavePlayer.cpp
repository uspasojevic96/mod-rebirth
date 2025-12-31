#include "scripts/RebirthSavePlayer.h"
#include "RebirthManager.h"

RebirthSavePlayer::RebirthSavePlayer()
    : PlayerScript("RebirthSavePlayer", {PLAYERHOOK_ON_LOGOUT}) {}

void RebirthSavePlayer::OnPlayerLogout(Player *player) {
  rebirthManager->Save(player);
}
