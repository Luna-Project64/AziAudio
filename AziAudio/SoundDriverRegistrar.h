#include "SoundDriverFactory.h"

#pragma once

#define REGISTER_DRIVER(cls, type, name, lvl) \
void cls##Probe() { \
	if (cls::ValidateDriver()) { \
		SoundDriverFactory::RegisterSoundDriver(type, cls::CreateSoundDriver, name, lvl); \
	} \
}
