
#include "scripts/RebirthPlayer.h"
#include "RebirthManager.h"

RebirthPlayer::RebirthPlayer()
    : PlayerScript("RebirthPlayer",
                   {PLAYERHOOK_ON_LOGIN, PLAYERHOOK_ON_GIVE_EXP,
                    PLAYERHOOK_ON_LEVEL_CHANGED}) {}

void RebirthPlayer::OnPlayerGiveXP(Player *player, uint32 &amount, Unit *victim,
                                   uint8 xpSource) {
  (void)victim;
  (void)xpSource;

  amount =
      uint32(float(amount) * rebirthManager->GetExperienceMultiplier(player));
}

void RebirthPlayer::OnPlayerLevelChanged(Player *player, uint8 oldLevel) {
  rebirthManager->ClearStats(player, oldLevel);
  rebirthManager->ApplyStats(player);

  if (player->GetLevel() == 80) {
    rebirthManager->SendMessage(player, "REBIRTH\tAVAILABLE:0");
  }
}

void RebirthPlayer::OnPlayerLogin(Player *player) {
  rebirthManager->ApplyStats(player);
}
