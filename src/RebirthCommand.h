#pragma once

#include "ChatCommand.h"
#include "CommandScript.h"

class RebirthCommand : public CommandScript {

public:
  RebirthCommand() : CommandScript("RebirthCommand") {}

  Acore::ChatCommands::ChatCommandTable GetCommands() const;
  static bool HandleRebirthCommand(ChatHandler *handler, const char *);
};
