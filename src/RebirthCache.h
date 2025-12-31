#pragma once

#include "DataMap.h"
#include "Define.h"

class RebirthCache : public DataMap::Base {
private:
  uint32 rebirthLevel{0};

public:
  static constexpr char CACHE_NAME[] = "RebirthCache";
  explicit RebirthCache(uint32 rebirthLevel) : rebirthLevel(rebirthLevel) {}

  uint32 &RebirthLevel() { return rebirthLevel; }
};
