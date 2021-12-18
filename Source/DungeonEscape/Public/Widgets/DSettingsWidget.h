// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DSettingsWidget.generated.h"


/** Forward declarations */
class UWidgetSwitcher;
class UButton;
class UComboBoxString;
class UCheckBox;
class UDSettingsSaveGame;
class USlider;


/**
 * Widget for settings menu
 */
UCLASS()
class DUNGEONESCAPE_API UDSettingsWidget : public UUserWidget
{
	GENERATED_BODY()

/**
 * Members
 */

protected:

	/** Saved game where player settings are stored */
	UPROPERTY()
	UDSettingsSaveGame* Settings;

	/**************************************************************************/
	/* Widgets */
	/**************************************************************************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* SettingsWidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* GraphicsSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* AudioSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ControlsSettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ApplySettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* GraphicsSettingsSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* AudioSettingsSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* ControlsSettingsSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ResolutionComboBox;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ViewDistanceComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* AntiAliasingComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* ShadowsComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* TexturesComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UComboBoxString* MaxFPSComboBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UCheckBox* VSyncCheckBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USlider* MasterVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USlider* AmbientVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USlider* EffectsVolumeSlider;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USlider* UIVolumeSlider;


 /**
  * Methods
  */
	
protected:

	virtual bool Initialize() override;


private:
	/**************************************************************************/
	/* Setup */
	/**************************************************************************/
	bool BindWidgetEvents();

	void GetSettingsSaveGame();

	void SetInitialWidgetProperties();
	void SetResolutionComboBoxProperties();
	void SetViewDistanceComboBoxProperties();
	void SetAntiAliasingComboBoxProperties();
	void SetShadowsComboBoxProperties();
	void SetTexturesComboBoxProperties();
	void SetMaxFPSComboBoxProperties();
	void SetVsyncCheckBoxProperties();
	void SetMasterVolumeSliderProperties();
	void SetAmbientVolumeSliderProperties();
	void SetEffectsVolumeSliderProperties();
	void SetUIVolumeSliderProperties();

	/**************************************************************************/
	/* Widget event bindings */
	/**************************************************************************/
	UFUNCTION()
	void OnGraphicsSettingsButtonClick();

	UFUNCTION()
	void OnAudioSettingsButtonClick();

	UFUNCTION()
	void OnControlsSettingsButtonClick();

	UFUNCTION()
	void OnApplySettingsButtonClick();

	UFUNCTION()
	void OnResolutionComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnViewDistanceComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnAntiAliasingComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnShadowsComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnTexturesComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnMaxFPSComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType);

	UFUNCTION()
	void OnVSyncCheckBoxStateChanged(bool bIsChecked);

	UFUNCTION()
	void OnMasterVolumeSliderChanged(float Value);

	UFUNCTION()
	void OnAmbientVolumeSliderChanged(float Value);

	UFUNCTION()
	void OnEffectsVolumeSliderChanged(float Value);

	UFUNCTION()
	void OnUIVolumeSliderChanged(float Value);

};
