// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DMainMenuWidget.h"

// Engine Includes
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


bool UDMainMenuWidget::BindWidgetEvents()
{
	if (!PlayButton) return false;
	if (!PlayButton->OnClicked.IsBound())
	{
		PlayButton->OnClicked.AddDynamic(this, &UDMainMenuWidget::OnPlayButtonClick);
	}

	if (!SettingsButton) return false;
	if (!SettingsButton->OnClicked.IsBound())
	{
		SettingsButton->OnClicked.AddDynamic(this, &UDMainMenuWidget::OnSettingsButtonClick);
	}

	if (!SettingsBackButton) return false;
	if (!SettingsBackButton->OnClicked.IsBound())
	{
		SettingsBackButton->OnClicked.AddDynamic(this, &UDMainMenuWidget::OnSettingsBackButtonClick);
	}

	if (!QuitButton) return false;
	if (!QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UDMainMenuWidget::OnQuitButtonClick);
	}

	return true;
}


void UDMainMenuWidget::OnPlayButtonClick()
{
	TearDown();

	UGameplayStatics::OpenLevel(GetWorld(), "/Game/DungeonEscape/Maps/Dungeon_Escape_L1");
}


void UDMainMenuWidget::OnSettingsButtonClick()
{
	SwitchSubmenu(MainMenuWidgetSwitcher, SettingsSubmenu);
}


void UDMainMenuWidget::OnSettingsBackButtonClick()
{
	SwitchSubmenu(MainMenuWidgetSwitcher, MainMenuSubmenu);
}


void UDMainMenuWidget::OnQuitButtonClick()
{
	ShowConfirmQuitMenu(this);
}
