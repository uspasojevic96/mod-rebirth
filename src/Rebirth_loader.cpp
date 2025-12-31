#include "RebirthCommand.h"
#include "RebirthManager.h"
#include "scripts/RebirthAddon.h"
#include "scripts/RebirthLoadPlayer.h"
#include "scripts/RebirthPlayer.h"
#include "scripts/RebirthSavePlayer.h"

void AddRebirthScripts() {
  new RebirthManager();
  new RebirthLoadPlayer();
  new RebirthPlayer();
  new RebirthSavePlayer();
  new RebirthCommand();
  new RebirthAddon();
}

void Addmod_rebirthScripts() { AddRebirthScripts(); }
