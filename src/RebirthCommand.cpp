#include "RebirthCommand.h"
#include "Chat.h"
#include "Common.h"
#include "RebirthManager.h"

Acore::ChatCommands::ChatCommandTable RebirthCommand::GetCommands() const {
  using namespace Acore::ChatCommands;

  ChatCommandTable commandTable = {
      {"rebirth", HandleRebirthCommand, SEC_PLAYER, Console::No}};

  return commandTable;
}

bool RebirthCommand::HandleRebirthCommand(ChatHandler *handler, const char *) {
  Player *player = handler->GetSession()->GetPlayer();

  if (!player) {
    return false;
  }

  if (player->GetLevel() < 80) {
    return false;
  }

  rebirthManager->Rebirth(player);

  return true;
}
