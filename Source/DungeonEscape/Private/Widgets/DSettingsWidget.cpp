// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DSettingsWidget.h"

// Engine Includes
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"


// Game Includes
#include "DSettingsSaveGame.h"
#include "DDungeonEscapeGameInstance.h"


static const int32 INVALID_INDEX = -1;

bool UDSettingsWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;
	
	Success = BindWidgetEvents();
	if (!Success) return false;

	GetSettingsSaveGame();
	SetInitialWidgetProperties();
	
	return Success;
}


bool UDSettingsWidget::BindWidgetEvents()
{
	if (!GraphicsSettingsButton) return false;
	if (!GraphicsSettingsButton->OnClicked.IsBound())
	{
		GraphicsSettingsButton->OnClicked.AddDynamic(this, &UDSettingsWidget::OnGraphicsSettingsButtonClick);
	}

	if (!AudioSettingsButton) return false;
	if (!AudioSettingsButton->OnClicked.IsBound())
	{
		AudioSettingsButton->OnClicked.AddDynamic(this, &UDSettingsWidget::OnAudioSettingsButtonClick);
	}

	if (!ControlsSettingsButton) return false;
	if (!ControlsSettingsButton->OnClicked.IsBound())
	{
		ControlsSettingsButton->OnClicked.AddDynamic(this, &UDSettingsWidget::OnControlsSettingsButtonClick);
	}

	if (!ApplySettingsButton) return false;
	if (!ApplySettingsButton->OnClicked.IsBound())
	{
		ApplySettingsButton->OnClicked.AddDynamic(this, &UDSettingsWidget::OnApplySettingsButtonClick);
	}

	if (!ResolutionComboBox) return false;
	if (!ResolutionComboBox->OnSelectionChanged.IsBound())
	{
		ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnResolutionComboBoxChanged);
	}

	if (!ViewDistanceComboBox) return false;
	if (!ViewDistanceComboBox->OnSelectionChanged.IsBound())
	{
		ViewDistanceComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnViewDistanceComboBoxChanged);
	}

	if (!AntiAliasingComboBox) return false;
	if (!AntiAliasingComboBox->OnSelectionChanged.IsBound())
	{
		AntiAliasingComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnAntiAliasingComboBoxChanged);
	}

	if (!ShadowsComboBox) return false;
	if (!ShadowsComboBox->OnSelectionChanged.IsBound())
	{
		ShadowsComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnShadowsComboBoxChanged);
	}

	if (!TexturesComboBox) return false;
	if (!TexturesComboBox->OnSelectionChanged.IsBound())
	{
		TexturesComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnTexturesComboBoxChanged);
	}

	if (!MaxFPSComboBox) return false;
	if (!MaxFPSComboBox->OnSelectionChanged.IsBound())
	{
		MaxFPSComboBox->OnSelectionChanged.AddDynamic(this, &UDSettingsWidget::OnMaxFPSComboBoxChanged);
	}

	if (!VSyncCheckBox) return false;
	if (!VSyncCheckBox->OnCheckStateChanged.IsBound())
	{
		VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UDSettingsWidget::OnVSyncCheckBoxStateChanged);
	}

	if (!MasterVolumeSlider) return false;
	if (!MasterVolumeSlider->OnValueChanged.IsBound())
	{
		MasterVolumeSlider->OnValueChanged.AddDynamic(this, &UDSettingsWidget::OnMasterVolumeSliderChanged);
	}

	if (!AmbientVolumeSlider) return false;
	if (!AmbientVolumeSlider->OnValueChanged.IsBound())
	{
		AmbientVolumeSlider->OnValueChanged.AddDynamic(this, &UDSettingsWidget::OnAmbientVolumeSliderChanged);
	}

	if (!EffectsVolumeSlider) return false;
	if (!EffectsVolumeSlider->OnValueChanged.IsBound())
	{
		EffectsVolumeSlider->OnValueChanged.AddDynamic(this, &UDSettingsWidget::OnEffectsVolumeSliderChanged);
	}

	if (!UIVolumeSlider) return false;
	if (!UIVolumeSlider->OnValueChanged.IsBound())
	{
		UIVolumeSlider->OnValueChanged.AddDynamic(this, &UDSettingsWidget::OnUIVolumeSliderChanged);
	}



	return true;
}


/**************************************************************************/
/* Setup */
/**************************************************************************/
void UDSettingsWidget::SetInitialWidgetProperties()
{
	SetResolutionComboBoxProperties();
	SetViewDistanceComboBoxProperties();
	SetAntiAliasingComboBoxProperties();
	SetShadowsComboBoxProperties();
	SetTexturesComboBoxProperties();
	SetMaxFPSComboBoxProperties();
	SetVsyncCheckBoxProperties();
	SetMasterVolumeSliderProperties();
	SetAmbientVolumeSliderProperties();
	SetEffectsVolumeSliderProperties();
	SetUIVolumeSliderProperties();
}


void UDSettingsWidget::GetSettingsSaveGame()
{
	UDDungeonEscapeGameInstance* GameInstnace = GetGameInstance<UDDungeonEscapeGameInstance>();
	if (GameInstnace)
	{
		Settings = GameInstnace->GetSettings();
	}
}


void UDSettingsWidget::SetResolutionComboBoxProperties()
{
	if (!ResolutionComboBox) return;

	// Fill ResolutionComboBox with all possible resolution settings
	for (const auto& Elem : UDSettingsSaveGame::ResolutionMap)
	{
		ResolutionComboBox->AddOption(Elem.Key);
	}

	// Find the saved resolution setting. If valid set ResolutionComboBox index to saved setting
	if (Settings)
	{
		const FString* SavedResolutionKey = UDSettingsSaveGame::ResolutionMap.FindKey(Settings->GetResolution());
		if (SavedResolutionKey)
		{
			const int32 SavedIndex = ResolutionComboBox->FindOptionIndex(*SavedResolutionKey);
			if (SavedIndex != INVALID_INDEX)
			{
				ResolutionComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	ResolutionComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetViewDistanceComboBoxProperties()
{
	if (!ViewDistanceComboBox) return;

	// Fill ViewDistanceComboBox will all possible ViewDistance settings
	for (auto& Elem : UDSettingsSaveGame::ViewDistanceMap)
	{
		ViewDistanceComboBox->AddOption(Elem.Key);
	}

	// Find the saved ViewDistance setting. If valid set ViewDistanceComboBox index to saved setting
	if (Settings)
	{
		const FString* ViewDistanceKey = UDSettingsSaveGame::ViewDistanceMap.FindKey(Settings->GetViewDistance());
		if (ViewDistanceKey)
		{
			const int32 SavedIndex = ViewDistanceComboBox->FindOptionIndex(*ViewDistanceKey);
			if (SavedIndex != INVALID_INDEX)
			{
				ViewDistanceComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	ViewDistanceComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetAntiAliasingComboBoxProperties()
{
	if (!AntiAliasingComboBox) return;

	// Fill AntiAliasingComboBox with all possible AntiAliasing settings
	for (const auto& Elem : UDSettingsSaveGame::AntiAliasingMap)
	{
		AntiAliasingComboBox->AddOption(Elem.Key);
	}

	// Find the saved AntiAliasing setting. If valid set AntiAliasingComboBox index to saved setting
	if (Settings)
	{
		const FString* SavedAntiAliasingKey = UDSettingsSaveGame::AntiAliasingMap.FindKey(Settings->GetAntiAliasing());
		if (SavedAntiAliasingKey)
		{
			const int32 SavedIndex = AntiAliasingComboBox->FindOptionIndex(*SavedAntiAliasingKey);
			if (SavedIndex != INVALID_INDEX)
			{
				AntiAliasingComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	AntiAliasingComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetShadowsComboBoxProperties()
{
	if (!ShadowsComboBox) return;

	// Fill ShadowsComboBox with all possible Shadow settings
	for (const auto& Elem : UDSettingsSaveGame::ShadowsMap)
	{
		ShadowsComboBox->AddOption(Elem.Key);
	}

	// Find the saved Shadows setting. If valid set ShadowsComboBox index to saved setting
	if (Settings)
	{
		const FString* SavedShadowsKey = UDSettingsSaveGame::ShadowsMap.FindKey(Settings->GetShadows());
		if (SavedShadowsKey)
		{
			const int32 SavedIndex = ShadowsComboBox->FindOptionIndex(*SavedShadowsKey);
			if (SavedIndex != INVALID_INDEX)
			{
				ShadowsComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	ShadowsComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetTexturesComboBoxProperties()
{
	if (!TexturesComboBox) return;

	// Fill TexturesComboBox with all possible Textures settings
	for (const auto& Elem : UDSettingsSaveGame::TexturesMap)
	{
		TexturesComboBox->AddOption(Elem.Key);
	}

	// Find the saved Textures setting. If valid set TexturesComboBox index to saved setting
	if (Settings)
	{
		const FString* SavedTexturesKey = UDSettingsSaveGame::TexturesMap.FindKey(Settings->GetTextures());
		if (SavedTexturesKey)
		{
			const int32 SavedIndex = TexturesComboBox->FindOptionIndex(*SavedTexturesKey);
			if (SavedIndex != INVALID_INDEX)
			{
				TexturesComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	TexturesComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetMaxFPSComboBoxProperties()
{
	if (!MaxFPSComboBox) return;

	// Fill MaxFPSComboBox with all possible MaxFPS settings
	for (const auto& Elem : UDSettingsSaveGame::MaxFPSMap)
	{
		MaxFPSComboBox->AddOption(Elem.Key);
	}

	// Find the saved MaxFPS setting. If valid set MaxFPSComboBox index to saved setting
	if (Settings)
	{
		const FString* SavedMaxFPSKey = UDSettingsSaveGame::MaxFPSMap.FindKey(Settings->GetMaxFPS());
		if (SavedMaxFPSKey)
		{
			const int32 SavedIndex = MaxFPSComboBox->FindOptionIndex(*SavedMaxFPSKey);
			if (SavedIndex != INVALID_INDEX)
			{
				MaxFPSComboBox->SetSelectedIndex(SavedIndex);
				return;
			}
		}
	}

	MaxFPSComboBox->SetSelectedIndex(0);
}


void UDSettingsWidget::SetVsyncCheckBoxProperties()
{
	if (VSyncCheckBox && Settings)
	{
		VSyncCheckBox->SetIsChecked(Settings->GetVsync());
	}
}


void UDSettingsWidget::SetMasterVolumeSliderProperties()
{
	if (MasterVolumeSlider && Settings)
	{
		MasterVolumeSlider->SetValue(Settings->GetMasterVolume());
	}
}


void UDSettingsWidget::SetAmbientVolumeSliderProperties()
{
	if (AmbientVolumeSlider && Settings)
	{
		AmbientVolumeSlider->SetValue(Settings->GetAmbientVolume());
	}
}


void UDSettingsWidget::SetEffectsVolumeSliderProperties()
{
	if (EffectsVolumeSlider && Settings)
	{
		EffectsVolumeSlider->SetValue(Settings->GetEffectsVolume());
	}
}


void UDSettingsWidget::SetUIVolumeSliderProperties()
{
	if (UIVolumeSlider && Settings)
	{
		UIVolumeSlider->SetValue(Settings->GetUIVolume());
	}
}


/**************************************************************************/
/* Widget event bindings */
/**************************************************************************/
void UDSettingsWidget::OnGraphicsSettingsButtonClick()
{
	if (SettingsWidgetSwitcher && GraphicsSettingsSubmenu && SettingsWidgetSwitcher->HasChild(GraphicsSettingsSubmenu))
	{
		SettingsWidgetSwitcher->SetActiveWidget(GraphicsSettingsSubmenu);
	}
}


void UDSettingsWidget::OnAudioSettingsButtonClick()
{
	if (SettingsWidgetSwitcher && AudioSettingsSubmenu && SettingsWidgetSwitcher->HasChild(AudioSettingsSubmenu))
	{
		SettingsWidgetSwitcher->SetActiveWidget(AudioSettingsSubmenu);
	}
}


void UDSettingsWidget::OnControlsSettingsButtonClick()
{
	if (SettingsWidgetSwitcher && ControlsSettingsSubmenu && SettingsWidgetSwitcher->HasChild(ControlsSettingsSubmenu))
	{
		SettingsWidgetSwitcher->SetActiveWidget(ControlsSettingsSubmenu);
	}
}


void UDSettingsWidget::OnApplySettingsButtonClick()
{
	UDDungeonEscapeGameInstance* GameInstnace = GetGameInstance<UDDungeonEscapeGameInstance>();
	if (GameInstnace)
	{
		GameInstnace->SetSettings();
	}
}


void UDSettingsWidget::OnResolutionComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetResolution(SelectedItem);
	}
}


void UDSettingsWidget::OnViewDistanceComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetViewDistance(SelectedItem);
	}
}


void UDSettingsWidget::OnAntiAliasingComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetAntiAliasing(SelectedItem);
	}
}


void UDSettingsWidget::OnShadowsComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetShadows(SelectedItem);
	}
}


void UDSettingsWidget::OnTexturesComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetTextures(SelectedItem);
	}
}


void UDSettingsWidget::OnMaxFPSComboBoxChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (Settings)
	{
		Settings->SetMaxFPS(SelectedItem);
	}
}


void UDSettingsWidget::OnVSyncCheckBoxStateChanged(bool bIsChecked)
{
	if(Settings)
	{
		Settings->SetVsync(bIsChecked);
	}
}


void UDSettingsWidget::OnMasterVolumeSliderChanged(float Value)
{
	if (Settings)
	{
		Settings->SetMasterVolume(Value);
	}
}


void UDSettingsWidget::OnAmbientVolumeSliderChanged(float Value)
{
	if (Settings)
	{
		Settings->SetAmbientVolume(Value);
	}
}


void UDSettingsWidget::OnEffectsVolumeSliderChanged(float Value)
{
	if (Settings)
	{
		Settings->SetEffectsVolume(Value);
	}
}


void UDSettingsWidget::OnUIVolumeSliderChanged(float Value)
{
	if (Settings)
	{
		Settings->SetUIVolume(Value);
	}
}
