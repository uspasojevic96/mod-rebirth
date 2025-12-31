#include "RebirthAddon.h"
#include "Chat.h"
#include "RebirthCache.h"
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
    return false;

  std::string prefix = msg.substr(0, delimiter);
  std::string data = msg.substr(delimiter + 1);

  if (prefix != "REBIRTH")
    return false;

  if (data != "GET_LEVEL")
    return false;

  auto *cache = player->CustomData.Get<RebirthCache>(RebirthCache::CACHE_NAME);
  if (!cache)
    return false;

  uint32 rebirthLevel = cache->RebirthLevel();

  // MUST be prefix + \t + payload
  std::string response = "REBIRTH\tLEVEL:" + std::to_string(rebirthLevel);

  WorldPacket packet;

  ChatHandler::BuildChatPacket(
      packet,
      CHAT_MSG_ADDON,    // chatType
      LANG_ADDON,        // language
      ObjectGuid::Empty, // senderGUID (SERVER → CLIENT!)
      player->GetGUID(), // receiverGUID (TARGET PLAYER)
      response,          // "PREFIX\tPAYLOAD"
      CHAT_TAG_NONE,
      "", // senderName
      "", // receiverName
      0, false,
      "" // channelName
  );

  player->GetSession()->SendPacket(&packet);
  return false;
}
