// Fill out your copyright notice in the Description page of Project Settings.


#include "DSettingsSaveGame.h"


const TMap<FString, FString> UDSettingsSaveGame::ResolutionMap =
{
	{"800 x 600", "800x600f"},
	{"1024 x 768", "1024x768f"},
	{"1152 x 864", "1152x864f"},
	{"1280 x 720", "1280x720f"},
	{"1280 x 768", "1280x768f"},
	{"1280 x 800", "1280x800f"},
	{"1280 x 960", "1280x960f"},
	{"1280 x 1024", "1280x1024f"},
	{"1360 x 768", "1360x768f"},
	{"1366 x 768", "1366x768f"},
	{"1600 x 900", "1600x900f"},
	{"1600 x 1024",	"1600x1024f"},
	{"1600 x 1200",	"1600x1200f"},
	{"1680 x 1050",	"1680x1050f"},
	{"1920 x 1080",	"1920x1080f"},
	{"1920 x 1200",	"1920x1200f"},
	{"1920 x 1440",	"1920x1440f"},
	{"2048 x 1080",	"2048x1080f"},
	{"2560 x 1440",	"2560x1440f"},
	{"3440 x 1440",	"3440x1440f"}
};


const TMap<FString, FString> UDSettingsSaveGame::ViewDistanceMap =
{
	{"Near", "0.4"},
	{"Medium", "0.7"},
	{"Far", "1"}
};


const TMap<FString, FString> UDSettingsSaveGame::AntiAliasingMap =
{
	{"Low", "0"},
	{"Medium", "2"},
	{"High", "4"},
	{"Epic", "6"}
};


const TMap<FString, FString> UDSettingsSaveGame::ShadowsMap =
{
	//{"Low", "0"},
	{"Medium", "1"},
	{"High", "2"},
	{"Epic", "3"}
};


const TMap<FString, FString> UDSettingsSaveGame::TexturesMap =
{
	{"Low", "0"},
	{"Medium", "1"},
	{"High", "2"},
	{"Epic", "3"}
};


const TMap<FString, FString> UDSettingsSaveGame::MaxFPSMap =
{
	{"30", "30"},
	{"60", "60"},
	{"90", "90"},
	{"120", "120"}
};


UDSettingsSaveGame::UDSettingsSaveGame()
{
	SettingsData.MasterVolume = 0.5f;
	SettingsData.AmbientVolume = 0.5f;
	SettingsData.EffectsVolume = 0.5f;
	SettingsData.UIVolume = 0.5f;
	SettingsData.bVsync = false;

	TArray<FString> ValueStrings;
	ResolutionMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.Resolution = ValueStrings[0];
	}

	ValueStrings.Empty();
	ViewDistanceMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.ViewDistance = ValueStrings[0];
	}

	ValueStrings.Empty();
	AntiAliasingMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.AntiAliasing = ValueStrings[0];
	}

	ValueStrings.Empty();
	ShadowsMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.Shadows = ValueStrings[0];
	}

	ValueStrings.Empty();
	TexturesMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.Textures = ValueStrings[0];
	}

	ValueStrings.Empty();
	MaxFPSMap.GenerateValueArray(ValueStrings);
	if (ValueStrings.Num() >= 0)
	{
		SettingsData.MaxFPS = ValueStrings[0];
	}
}


void UDSettingsSaveGame::SetMasterVolume(float Value)
{
	Value = FMath::Clamp<float>(Value, 0.f, 1.f);
	SettingsData.MasterVolume = Value;
}


void UDSettingsSaveGame::SetAmbientVolume(float Value)
{
	Value = FMath::Clamp<float>(Value, 0.f, 1.f);
	SettingsData.AmbientVolume = Value;
}


void UDSettingsSaveGame::SetEffectsVolume(float Value)
{
	Value = FMath::Clamp<float>(Value, 0.f, 1.f);
	SettingsData.EffectsVolume = Value;
}


void UDSettingsSaveGame::SetUIVolume(float Value)
{
	Value = FMath::Clamp<float>(Value, 0.f, 1.f);
	SettingsData.UIVolume = Value;
}


void UDSettingsSaveGame::SetResolution(const FString& ResolutionSetting)
{
	const FString* ResolutionValue = UDSettingsSaveGame::ResolutionMap.Find(ResolutionSetting);
	if (ResolutionValue)
	{
		SettingsData.Resolution = *ResolutionValue;
	}
}


void UDSettingsSaveGame::SetViewDistance(const FString& ViewDistanceSetting)
{
	const FString* ViewDistanceValue = UDSettingsSaveGame::ViewDistanceMap.Find(ViewDistanceSetting);
	if (ViewDistanceValue)
	{
		SettingsData.ViewDistance = *ViewDistanceValue;
	}
}


void UDSettingsSaveGame::SetAntiAliasing(const FString& AntiAliasingSetting)
{
	const FString* AntiAliasingValue = UDSettingsSaveGame::AntiAliasingMap.Find(AntiAliasingSetting);
	if (AntiAliasingValue)
	{
		SettingsData.AntiAliasing = *AntiAliasingValue;
	}
}


void UDSettingsSaveGame::SetShadows(const FString& ShadowsSetting)
{
	const FString* ShadowsValue = UDSettingsSaveGame::ShadowsMap.Find(ShadowsSetting);
	if (ShadowsValue)
	{
		SettingsData.Shadows = *ShadowsValue;
	}
}


void UDSettingsSaveGame::SetTextures(const FString& TexturesSetting)
{
	const FString* TexturesValue = UDSettingsSaveGame::TexturesMap.Find(TexturesSetting);
	if (TexturesValue)
	{
		SettingsData.Textures = *TexturesValue;
	}
}


void UDSettingsSaveGame::SetMaxFPS(const FString& MaxFPSSetting)
{
	const FString* MaxFPSValue = UDSettingsSaveGame::MaxFPSMap.Find(MaxFPSSetting);
	if (MaxFPSValue)
	{
		SettingsData.MaxFPS = *MaxFPSValue;
	}
}


void UDSettingsSaveGame::SetVsync(bool Value)
{
	SettingsData.bVsync = Value;
}
