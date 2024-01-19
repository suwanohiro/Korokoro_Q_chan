#pragma once

#include "Mof.h"

#include <variant>

constexpr float swnLibraryVersion = 1.00;

#include "./FileAction/FileAction.h"
#include "./StringAction/StringAction.h"
#include "./WebColor/WebColor.h"

using spCTexture = std::shared_ptr<CTexture>;