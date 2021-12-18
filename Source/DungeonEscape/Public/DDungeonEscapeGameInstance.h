// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DDungeonEscapeGameInstance.generated.h"


/** Forward declarations */
class UDMainMenuWidget;
class UDInGameInstructionsWidget;
class UDGameOverWidget;
class UDPauseMenuWidget;
class UDSettingsSaveGame;
class UUserWidget;
class USoundClass;
class USoundMix;


/**
 * Base class for GameInstnace
 */
UCLASS()
class DUNGEONESCAPE_API UDDungeonEscapeGameInstance : public UGameInstance
{
	GENERATED_BODY()

/**
 * Members
 */
	
public:

	/** Widget to spawn for game's main menu */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UDMainMenuWidget> MainMenuWidgetClass;

	/** Widget to spawn for game over screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UDGameOverWidget> GameOverWidgetClass;

	/** Widget to spawn for pause menu */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menus")
	TSubclassOf<UDPauseMenuWidget> PauseMenuWidgetClass;

	/** Class to hold all player set settings to save. Settings to save Graphics scaling and Audio levels */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveSettings")
	TSubclassOf<UDSettingsSaveGame> SaveGameSettingsClass;

	/** Instance of class set form SaveGameSettingsClass. Is set in derived BP class  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveSettings")
	UDSettingsSaveGame* SettingsSaveGame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveSettings")
	FString SettingsSaveSlot;

	/** Mix class for making audio level adjustments  */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundMix* SoundMix;

	/** Master Sound class for making audio level adjustments */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundClass* MasterSoundClass;

	/** Ambient Sound class for making audio level adjustments */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundClass* AmbientSoundClass;

	/** Effects Sound class for making audio level adjustments */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundClass* EffectsSoundClass;

	/** UI Sound class for making audio level adjustments */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	USoundClass* UISoundClass;


/**
 * Methods
 */

 private:

	/** Helper function to set settings via console */
	void SendConsoleCommand(const TCHAR* Command) const;


public:

	/* Sets default values */
	UDDungeonEscapeGameInstance();

	UFUNCTION()
	UDSettingsSaveGame* GetSettings() const {return SettingsSaveGame;}

	/** Set all settings stored in SettingsSaveGame */
	UFUNCTION(BlueprintCallable)
	void SetSettings() const;

	/** Set individual settings stored in SettingsSaveGame */
	void SetResolution(const FString& ResolutionArg) const;
	void SetViewDistance(const FString& ViewDistanceArg) const;
	void SetAntiAliasing(const FString& AntiAliasingArg) const;
	void SetShadowQuality(const FString& ShadowQualityArg) const;
	void SetTextureQuality(const FString& TextureQualityArg) const;
	void SetMaxFPS(const FString& MaxFPSArg) const;
	void SetEnalbeVsync(bool Enable) const;
	void SetMasterVolume(float Volume) const;
	void SetAmbientVolume(float Volume) const;
	void SetEffectsVolume(float Volume) const;
	void SetUIVolume(float Volume) const;

};
