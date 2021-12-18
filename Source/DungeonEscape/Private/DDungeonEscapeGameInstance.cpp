// Fill out your copyright notice in the Description page of Project Settings.


#include "DDungeonEscapeGameInstance.h"

// Engine Includes
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"


// Game Includes
#include "DSettingsSaveGame.h"


UDDungeonEscapeGameInstance::UDDungeonEscapeGameInstance()
{
	SettingsSaveSlot = FString("Settings");
}


void UDDungeonEscapeGameInstance::SetSettings() const
{
	if (!SettingsSaveGame) return;

	SetResolution(SettingsSaveGame->GetResolution());
	SetViewDistance(SettingsSaveGame->GetViewDistance());
	SetAntiAliasing(SettingsSaveGame->GetAntiAliasing());
	SetShadowQuality(SettingsSaveGame->GetShadows());
	SetTextureQuality(SettingsSaveGame->GetTextures());
	SetMaxFPS(SettingsSaveGame->GetMaxFPS());
	SetEnalbeVsync(SettingsSaveGame->GetVsync());
	SetMasterVolume(SettingsSaveGame->GetMasterVolume());
	SetUIVolume(SettingsSaveGame->GetUIVolume());
	SetAmbientVolume(SettingsSaveGame->GetAmbientVolume());
	SetEffectsVolume(SettingsSaveGame->GetEffectsVolume());
}


void UDDungeonEscapeGameInstance::SetResolution(const FString& ResolutionArg) const
{
	const FString ResolutionChangeCommand = FString("r.SetRes ") + ResolutionArg;
	SendConsoleCommand(*ResolutionChangeCommand);
}


void UDDungeonEscapeGameInstance::SetViewDistance(const FString& ViewDistanceArg) const
{
	const FString ViewDistanceChangeCommmand = FString("r.ViewDistanceScale ") + ViewDistanceArg;
	SendConsoleCommand(*ViewDistanceChangeCommmand);
}


void UDDungeonEscapeGameInstance::SetAntiAliasing(const FString& AntiAliasingArg) const
{
	const FString AntiAliasingChangeCommand = FString("r.PostProcessAAQuality ") + AntiAliasingArg;
	SendConsoleCommand(*AntiAliasingChangeCommand);
}


void UDDungeonEscapeGameInstance::SetShadowQuality(const FString& ShadowQualityArg) const
{
	const FString ShadowQualityChangeCommand = FString("sg.ShadowQuality ") + ShadowQualityArg;
	SendConsoleCommand(*ShadowQualityChangeCommand);
}


void UDDungeonEscapeGameInstance::SetTextureQuality(const FString& TextureQualityArg) const
{
	const FString TextureQualityChangeCommand = FString("sg.TextureQuality ") + TextureQualityArg;
	SendConsoleCommand(*TextureQualityChangeCommand);
}


void UDDungeonEscapeGameInstance::SetMaxFPS(const FString& MaxFPSArg) const
{
	const FString MaxFPSChangeCommand = FString("t.maxfps ") + MaxFPSArg;
	SendConsoleCommand(*MaxFPSChangeCommand);
}


void UDDungeonEscapeGameInstance::SetEnalbeVsync(bool Enable) const
{
	const FString EnableFPS = (Enable) ? FString("1") : FString("0");
	const FString EnableFPSChangeCommand = FString("r.Vsync ") + EnableFPS;
	SendConsoleCommand(*EnableFPSChangeCommand);

}


void UDDungeonEscapeGameInstance::SetMasterVolume(float Volume) const
{
	if (SoundMix && MasterSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, MasterSoundClass, Volume);
	}
}


void UDDungeonEscapeGameInstance::SetAmbientVolume(float Volume) const
{
	if (SoundMix && AmbientSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, AmbientSoundClass, Volume);
	}
}


void UDDungeonEscapeGameInstance::SetEffectsVolume(float Volume) const
{
	if (SoundMix && EffectsSoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, EffectsSoundClass, Volume);
	}
}


void UDDungeonEscapeGameInstance::SetUIVolume(float Volume) const
{
	if (SoundMix && UISoundClass)
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMix, UISoundClass, Volume);
	}
}


void UDDungeonEscapeGameInstance::SendConsoleCommand(const TCHAR* Command) const
{
	if (GEngine)
	{
		GEngine->Exec(GetWorld(), Command);
	}
}


