/****************************************************************************
*                                                                           *
* Azimer's HLE Audio Plugin for Project64 Compatible N64 Emulators          *
* http://www.apollo64.com/                                                  *
* Copyright (C) 2000-2019 Azimer. All rights reserved.                      *
*                                                                           *
* License:                                                                  *
* GNU/GPLv2 http://www.gnu.org/licenses/gpl-2.0.html                        *
*                                                                           *
****************************************************************************/
#pragma once
#include "common.h"
#include "SoundDriverInterface.h"

#define SOUND_DRIVER(name) extern void name##Probe();
#include "XDrivers.h"
#undef SOUND_DRIVER

class SoundDriverFactory
{
private:
#define SOUND_DRIVER(name) friend void ::name##Probe();
#include "XDrivers.h"
#undef SOUND_DRIVER

	typedef SoundDriverInterface* (*SoundDriverCreationFunction)();
	struct FactoryDriversStruct
	{
		SoundDriverType DriverType;
		SoundDriverCreationFunction CreateFunction;
		int Priority;
		char Description[100];
	};

private:
	SoundDriverFactory() {};
	static int FactoryNextSlot;
	static const int MAX_FACTORY_DRIVERS = 20;
	static FactoryDriversStruct FactoryDrivers[MAX_FACTORY_DRIVERS];
	static bool RegisterSoundDriver(SoundDriverType DriverType, SoundDriverCreationFunction CreateFunction, char* Description, int Priority);

public:
	~SoundDriverFactory() {};

	static void Initialize();
	static SoundDriverInterface* CreateSoundDriver(SoundDriverType DriverID);
	static SoundDriverType DefaultDriver();
	static int EnumDrivers(SoundDriverType *drivers, int max_entries);
	static const char* GetDriverDescription(SoundDriverType driver);
	static bool DriverExists(SoundDriverType driver);
};

