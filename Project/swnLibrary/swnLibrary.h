#pragma once

#include "Mof.h"

#include <variant>

constexpr float swnLibraryVersion = 1.00;

#include "./FileAction/FileAction.h"
#include "./AudioCtrl/AudioCtrl.h"
#include "./StringAction/StringAction.h"
#include "./WebColor/WebColor.h"
#include "./Socket/Socket.h"
#include "./Socket/Client/Client.h"
#include "./Socket/Server/Server.h"

using spCTexture = std::shared_ptr<CTexture>;