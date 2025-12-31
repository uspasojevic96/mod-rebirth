#pragma once

#include "Define.h"
#include "Player.h"
#include "RebirthCache.h"

#define rebirthManager RebirthManager::instance()

class RebirthManager {
private:
  static RebirthManager *_instance;

  RebirthCache *GetCache(Player *player);
  uint32 GetStats(uint32 rebirthLevel, uint8 playerLevel);
  void UpdateStats(Player *player, uint32 value, bool increment);

public:
  RebirthManager();
  static RebirthManager *instance() { return RebirthManager::_instance; }
  void ApplyStats(Player *player);
  void ClearStats(Player *player, uint8 level = 0);
  float GetExperienceMultiplier(Player *player);
  void Load(Player *player);
  void Rebirth(Player *player);
  void Save(Player *player);
};
