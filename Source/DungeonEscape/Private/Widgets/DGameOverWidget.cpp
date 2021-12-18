// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DGameOverWidget.h"


// Engine Includes
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


bool UDGameOverWidget::BindWidgetEvents()
{
	if (!PlayAgainButton) return false;
	if (!PlayAgainButton->OnClicked.IsBound())
	{
		PlayAgainButton->OnClicked.AddDynamic(this, &UDGameOverWidget::OnPlayAgainButtonClick);
	}

	if (!MainMenuButton) return false;
	if (!MainMenuButton->OnClicked.IsBound())
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UDGameOverWidget::OnMainMenuButtonClick);
	}

	if (!QuitButton) return false;
	if (!QuitButton->OnClicked.IsBound())
	{
		QuitButton->OnClicked.AddDynamic(this, &UDGameOverWidget::OnQuitButtonClick);
	}

	return true;
}


void UDGameOverWidget::OnPlayAgainButtonClick()
{
	TearDown();
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/DungeonEscape/Maps/Dungeon_Escape_L1");
}


void UDGameOverWidget::OnMainMenuButtonClick()
{
	TearDown();
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/DungeonEscape/Maps/MainMenu");
}


void UDGameOverWidget::OnQuitButtonClick()
{
	ShowConfirmQuitMenu(this);
}
