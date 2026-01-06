#include "RebirthAddon.h"
#include "Chat.h"
#include "Opcodes.h"
#include "RebirthCache.h"
#include "RebirthManager.h"
#include "SharedDefines.h"

RebirthAddon::RebirthAddon()
    : PlayerScript("RebirthAddon", {PLAYERHOOK_CAN_PLAYER_USE_PRIVATE_CHAT}) {}

bool RebirthAddon::OnPlayerCanUseChat(Player *player, uint32 type,
                                      uint32 language, std::string &msg,
                                      Player *receiver) {
  if (language != LANG_ADDON)
    return true;

  size_t delimiter = msg.find('\t');
  if (delimiter == std::string::npos)
    return true;

  std::string prefix = msg.substr(0, delimiter);
  std::string data = msg.substr(delimiter + 1);
  std::string response;

  if (prefix != "REBIRTH")
    return true;

  auto *cache = player->CustomData.Get<RebirthCache>(RebirthCache::CACHE_NAME);

  if (!cache)
    return true;

  if (data == "GET_LEVEL") {
    uint32 rebirthLevel = cache->RebirthLevel();
    response = "REBIRTH\tLEVEL:" + std::to_string(rebirthLevel);
  }

  if (data == "GET_EXP") {
    response = "REBIRTH\tEXP:" +
               std::to_string(rebirthManager->GetExperienceMultiplier(player));
  }

  if (data == "GET_STATS") {
    uint32 rebirthLevel = cache->RebirthLevel();
    uint8 playerLevel = player->GetLevel();

    response =
        "REBIRTH\tSTATS:" +
        std::to_string(rebirthManager->GetStats(rebirthLevel, playerLevel));
  }

  if (data == "REBIRTH") {
    rebirthManager->Rebirth(player);
    response = "REBIRTH\tREBIRTHED:0";
  }

  rebirthManager->SendMessage(receiver, response);
  // WorldPacket packet(SMSG_MESSAGECHAT, 100);
  //
  // packet << uint8(type);
  // packet << uint32(language);
  // packet << ObjectGuid::Empty;
  // packet << uint32(0);
  // packet << receiver->GetGUID();
  // packet << uint32(response.size() + 1);
  // packet << response;
  // packet << uint8(0);
  //
  // player->GetSession()->SendPacket(&packet);
  return true;
}
