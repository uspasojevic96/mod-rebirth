#include "RebirthManager.h"
#include "DatabaseEnv.h"

RebirthManager *RebirthManager::_instance = nullptr;

RebirthManager::RebirthManager() { _instance = this; }

/// PRIVATE

RebirthCache *RebirthManager::GetCache(Player *player) {
  return player->CustomData.Get<RebirthCache>(RebirthCache::CACHE_NAME);
}

uint32 RebirthManager::GetStats(uint32 rebirthLevel, uint8 playerLevel) {

  return rebirthLevel * playerLevel *
         sConfigMgr->GetOption<uint32>("Rebirth.StatsPerLevelPerRebirth", 1);
}

void RebirthManager::UpdateStats(Player *player, uint32 value, bool increment) {
  player->HandleStatFlatModifier(UNIT_MOD_STAT_STRENGTH, BASE_VALUE, value,
                                 increment);
  player->HandleStatFlatModifier(UNIT_MOD_STAT_AGILITY, BASE_VALUE, value,
                                 increment);
  player->HandleStatFlatModifier(UNIT_MOD_STAT_STAMINA, BASE_VALUE, value,
                                 increment);
  player->HandleStatFlatModifier(UNIT_MOD_STAT_INTELLECT, BASE_VALUE, value,
                                 increment);
  player->HandleStatFlatModifier(UNIT_MOD_STAT_SPIRIT, BASE_VALUE, value,
                                 increment);
}

/// PUBLIC

void RebirthManager::ApplyStats(Player *player) {
  RebirthCache *cache = GetCache(player);
  uint32 &rebirthLevel = cache->RebirthLevel();

  if (rebirthLevel == 0)
    return;

  uint32 bonus = GetStats(rebirthLevel, player->GetLevel());

  UpdateStats(player, bonus, true);
}

void RebirthManager::ClearStats(Player *player, uint8 level) {
  RebirthCache *cache = GetCache(player);

  uint32 &rebirthLevel = cache->RebirthLevel();

  if (rebirthLevel == 0)
    return;

  if (level == 0)
    level = player->GetLevel();

  uint32 bonus = GetStats(rebirthLevel, level);

  UpdateStats(player, bonus, false);
}

float RebirthManager::GetExperienceMultiplier(Player *player) {
  RebirthCache *cache = GetCache(player);

  return 1.0f +
         (cache->RebirthLevel() *
          sConfigMgr->GetOption<float>("Rebirth.ExperienceMultiplier", 0.25f));
}

void RebirthManager::Load(Player *player) {
  QueryResult result =
      CharacterDatabase.Query("SELECT * FROM rebirth_character WHERE guid = {}",
                              player->GetGUID().GetCounter());

  uint32 rebirthLevel = 0;

  if (result) {
    Field *fields = result->Fetch();
    rebirthLevel = fields[1].Get<uint32>();
  }

  player->CustomData.Set(RebirthCache::CACHE_NAME,
                         new RebirthCache(rebirthLevel));
}

void RebirthManager::Rebirth(Player *player) {
  ClearStats(player, 80);
  RebirthCache *cache = GetCache(player);

  uint32 &rebirthLevel = cache->RebirthLevel();
  rebirthLevel++;
  player->SetLevel(1);
  ApplyStats(player);
  player->SendSystemMessage("You have rebirthed");
}

void RebirthManager::Save(Player *player) {
  RebirthCache *cache = GetCache(player);

  CharacterDatabase.Execute(
      "INSERT INTO rebirth_character (guid, level) VALUES ({}, {}) AS new ON "
      "DUPLICATE KEY UPDATE level = new.level",
      player->GetGUID().GetCounter(), cache->RebirthLevel());
}
