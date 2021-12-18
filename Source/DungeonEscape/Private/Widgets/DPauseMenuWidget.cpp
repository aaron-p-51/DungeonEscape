// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DPauseMenuWidget.h"

// Engine Includes
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UDPauseMenuWidget::Setup()
{
	Super::Setup();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}


bool UDPauseMenuWidget::BindWidgetEvents()
{
	if (!ResumeButton) return false;
	if (!ResumeButton->OnClicked.IsBound())
	{
		ResumeButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnResumeButtonClick);
	}

	if (!SettingsButton) return false;
	if (!SettingsButton->OnClicked.IsBound())
	{
		SettingsButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnSettingsButtonClick);
	}

	if (!SettingsBackButton) return false;
	if (!SettingsBackButton->OnClicked.IsBound())
	{
		SettingsBackButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnSettingsBackButtonClick);
	}

	if (!MainMenuButton) return false;
	if (!MainMenuButton->OnClicked.IsBound())
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnMainMenuButtonClick);
	}

	if (!CancelMainMenuButton) return false;
	if (!CancelMainMenuButton->OnClicked.IsBound())
	{
		CancelMainMenuButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnCancelMainMenuButtonClick);
	}

	if (!ConfirmMainMenuButton) return false;
	if (!ConfirmMainMenuButton->OnClicked.IsBound())
	{
		ConfirmMainMenuButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnConfirmMainMenuButtonClick);
	}

	if (!QuitButton) return false;
	if (!QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UDPauseMenuWidget::OnQuitButtonClick);
	}

	return true;
}


void UDPauseMenuWidget::OnResumeButtonClick()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	TearDown();
}


void UDPauseMenuWidget::OnSettingsButtonClick()
{
	SwitchSubmenu(PauseMenuWidgetSwitcher, SettingsSubmenu);
}


void UDPauseMenuWidget::OnSettingsBackButtonClick()
{
	SwitchSubmenu(PauseMenuWidgetSwitcher, PauseSubmenu);
}


void UDPauseMenuWidget::OnMainMenuButtonClick()
{
	SwitchSubmenu(PauseMenuWidgetSwitcher, ConfirmMainMenuSubmenu);
}


void UDPauseMenuWidget::OnCancelMainMenuButtonClick()
{
	SwitchSubmenu(PauseMenuWidgetSwitcher, PauseSubmenu);
}


void UDPauseMenuWidget::OnConfirmMainMenuButtonClick()
{
	TearDown();

	UGameplayStatics::OpenLevel(GetWorld(), "/Game/DungeonEscape/Maps/MainMenu");
}


void UDPauseMenuWidget::OnQuitButtonClick()
{
	ShowConfirmQuitMenu(this);
}

