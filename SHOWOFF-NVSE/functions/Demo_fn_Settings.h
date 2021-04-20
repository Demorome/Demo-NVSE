#pragma once

//#include <ParamInfos.h>  //whyyyy did I have to add this? WTF

#include "GameSettings.h"
#include "GameRTTI.h"
#include "internal/jip_nvse.h"

DEFINE_COMMAND_PLUGIN(IsGameSetting, "Checks if a string refers to a valid Gamesetting", 0, 1, kParams_OneString);
bool Cmd_IsGameSetting_Execute(COMMAND_ARGS)
{
	char settingName[512];
	Setting* setting;
	GameSettingCollection* gmsts = GameSettingCollection::GetSingleton();

	if (ExtractArgs(EXTRACT_ARGS, &settingName)) {
		if (gmsts && gmsts->GetGameSetting(settingName, &setting)) {
			*result = 1;
			if (IsConsoleMode())
				Console_Print("IsGameSetting >> VALID GAMESETTING");
		}
		else {
			*result = 0;
			if (IsConsoleMode())
				Console_Print("IsGameSetting >> INVALID GAMESETTING");
		}
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(IsINISetting, "Checks if a string refers to a valid FalloutPrefs.ini / Fallout.ini setting.", 0, 1, kParams_OneString);
bool Cmd_IsINISetting_Execute(COMMAND_ARGS)
{
	char settingName[512];
	Setting* setting;

	if (ExtractArgs(EXTRACT_ARGS, &settingName)) {
		if (GetINISetting(settingName, &setting)) {
			*result = 1;
			if (IsConsoleMode())
				Console_Print("IsINISetting >> VALID INI SETTING");
		}
		else {
			*result = 0;
			if (IsConsoleMode())
				Console_Print("IsINISetting >> INVALID INI SETTING");
		}
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(ModNumericINISetting, , 0, 2, kParams_OneString_OneFloat);
bool Cmd_ModNumericINISetting_Execute(COMMAND_ARGS)
{
	char settingName[512];
	Setting* setting;
	float modVal = 0;
	double curVal = 0;

	if (ExtractArgs(EXTRACT_ARGS, &settingName, &modVal)) {
		if ((GetINISetting(settingName, &setting)) && (setting->Get(curVal)))
		{
			if (setting->Set(curVal + modVal))
			{
				*result = 1;
				if (IsConsoleMode())
				{
					double newVal;
					setting->Get(newVal);
					Console_Print("ModNumericINISetting >> %s -> %f", settingName, newVal);
				}
			}
		}
		else
		{
			*result = 0;
			if (IsConsoleMode())
				Console_Print("ModNumericINISetting >> INI SETTING NOT FOUND");
		}
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(ModNumericINISettingAlt, , 0, 2, kParams_OneString_OneFloat);
bool Cmd_ModNumericINISettingAlt_Execute(COMMAND_ARGS)
{
	char settingName[512];
	Setting* setting;
	float modVal = 0;
	double curVal = 0;

	if (ExtractArgs(EXTRACT_ARGS, &settingName, &modVal)) {
		if ((GetINISetting(settingName, &setting)) && (setting->Get(curVal)))
		{
			if (setting->Set(curVal + modVal))
			{
				*result = 1;
				if (IsConsoleMode())
				{
					double newVal;
					setting->Get(newVal);
					Console_Print("ModNumericINISetting >> %s -> %f", settingName, newVal);
				}
			}
		}
		else
		{
			*result = 0;
			if (IsConsoleMode())
				Console_Print("ModNumericINISetting >> INI SETTING NOT FOUND");
		}
	}

	return true;
}

DEFINE_COMMAND_PLUGIN(ModNumericGameSetting, , 0, 2, kParams_OneString_OneFloat);
bool Cmd_ModNumericGameSetting_Execute(COMMAND_ARGS)
{
	char settingName[512];
	float modVal = 0;
	*result = 0;

	if (ExtractArgs(EXTRACT_ARGS, &settingName, &modVal)) {
		Setting* setting;
		GameSettingCollection* gmsts = GameSettingCollection::GetSingleton();
		if (gmsts && gmsts->GetGameSetting(settingName, &setting))
		{
			double curVal;
			if (setting->Get(curVal))
			{
				double newVal = curVal + modVal;
				if (setting->Set(newVal))
				{
					*result = 1;
					if (IsConsoleMode())
						Console_Print("ModNumericGameSetting >> %s -> %f", settingName, newVal);
				}
			}
		}
		else if (IsConsoleMode())
			Console_Print("ModNumericGameSetting >> SETTING NOT FOUND");
	}

	return true;
}

/*
DEFINE_COMMAND_PLUGIN(SetNumericGameSettingAlt, , 0, 2, kParams_OneString_OneFloat);
bool Cmd_SetNumericGameSettingAlt_Execute(COMMAND_ARGS)
{

}

DEFINE_COMMAND_PLUGIN(SetNumericINISettingAlt, , 0, 2, kParams_OneString_OneFloat);
bool Cmd_SetNumericGameSettingAlt_Execute(COMMAND_ARGS)
{

}
*/
#if IFYOULIKEBROKENSHIT
DEFINE_COMMAND_PLUGIN(DumpGameSettings, , 0, 0, NULL);
bool Cmd_DumpGameSettings_Execute(COMMAND_ARGS)
{
	char settingName[512];
	GameSettingCollection* gmsts = GameSettingCollection::GetSingleton();
	//if (gmsts && gmsts->GetGameSetting(settingName, &setting))
		//;
	UINT32 const numGmsts = gmsts->settingMap.numItems;
	UINT32 const numBuckets = gmsts->settingMap.numBuckets;
	
	
	if (IsConsoleMode())
	{
		Console_Print("--- Dumping GameSettings Map, Size: %d, NumBuckets: %d ---", numGmsts, numBuckets);
		//NiTMapBase<char*, Setting*> map = gmsts->settingMap;
		//NiTMapBase<const char*, Setting*>::Entry **entry = gmsts->settingMap.buckets;
		//NiTMapBase<const char*, Setting*>::Entry.next = auto entry; // ::next;
		//&entry.next; 
		
	}

	return true;
}

#endif