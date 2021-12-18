// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DSettingsSaveGame.generated.h"


/** Struct to hold all currently set graphics and audio settings */
USTRUCT(BlueprintType)
struct FSettingsData
{
	GENERATED_BODY()

	UPROPERTY()
	float MasterVolume;

	UPROPERTY()
	float AmbientVolume;

	UPROPERTY()
	float EffectsVolume;

	UPROPERTY()
	float UIVolume;

	UPROPERTY()
	bool bVsync;

	UPROPERTY()
	FString Resolution;

	UPROPERTY()
	FString ViewDistance;

	UPROPERTY()
	FString AntiAliasing;

	UPROPERTY()
	FString Shadows;

	UPROPERTY()
	FString Textures;

	UPROPERTY()
	FString MaxFPS;
};


/**
 * Base class for Settings data to save
 */
UCLASS()
class DUNGEONESCAPE_API UDSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()


/**
 * Members
 */

private:

	UPROPERTY()
	FSettingsData SettingsData;


public:

	/** Maps used to map user displayed options to engine scalability settings */
	static const TMap<FString, FString> ResolutionMap;
	static const TMap<FString, FString> ViewDistanceMap;
	static const TMap<FString, FString> AntiAliasingMap;
	static const TMap<FString, FString> ShadowsMap;
	static const TMap<FString, FString> TexturesMap;
	static const TMap<FString, FString> MaxFPSMap;


/**
 * Methods
 */

public:
	
	/** Set default settings. Lowest possible graphics settings, and 50 percent for all volume settings */
	UDSettingsSaveGame();

	/** Set settings in SettingsData */
	void SetMasterVolume(float Value);
	void SetAmbientVolume(float Value);
	void SetEffectsVolume(float Value);
	void SetUIVolume(float Value);
	void SetResolution(const FString& ResolutionSetting);
	void SetViewDistance(const FString& ViewDistanceSetting);
	void SetAntiAliasing(const FString& AntiAliasingSetting);
	void SetShadows(const FString& ShadowsSetting);
	void SetTextures(const FString& TexturesSetting);
	void SetMaxFPS(const FString& MaxFPSSetting);
	void SetVsync(bool Value);

	/** Get settings from SettingsData  */
	float GetMasterVolume() const { return SettingsData.MasterVolume; }
	float GetAmbientVolume() const { return SettingsData.AmbientVolume; }
	float GetEffectsVolume() const { return SettingsData.EffectsVolume; }
	float GetUIVolume() const { return SettingsData.UIVolume; }
	FString GetResolution() const { return SettingsData.Resolution; }
	FString GetViewDistance() const { return SettingsData.ViewDistance; }
	FString GetAntiAliasing() const  { return SettingsData.AntiAliasing; }
	FString GetShadows() const { return SettingsData.Shadows; }
	FString GetTextures() const { return SettingsData.Textures; }
	FString GetMaxFPS() const { return SettingsData.MaxFPS; }
	bool GetVsync() const { return SettingsData.bVsync; }
		
};
