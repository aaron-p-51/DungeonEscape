// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/DPlayerController.h"


// Game Includes
#include "DDungeonEscapeGameInstance.h"
#include "Widgets/DGameOverWidget.h"
#include "Widgets/DPauseMenuWidget.h"


ADPlayerController::ADPlayerController()
{
	PauseMenuWidget = nullptr;
	GameOverWidget = nullptr;
}


void ADPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("ShowMenu"), EInputEvent::IE_Pressed, this, &ADPlayerController::ShowPauseMenu);
}


void ADPlayerController::OnLevelEscapeSuccess()
{
	ShowGameOverMenu();
}


void ADPlayerController::ShowPauseMenu()
{
	if (!PauseMenuWidget)
	{
		// UDPauseMenuWidget to used is set in UDDungeonEscapeGameInstance 
		UDDungeonEscapeGameInstance* DungeonEscapeGameInstance = GetWorld()->GetGameInstance<UDDungeonEscapeGameInstance>();
		if (DungeonEscapeGameInstance)
		{
			PauseMenuWidget = CreateWidget<UDPauseMenuWidget>(GetWorld(), DungeonEscapeGameInstance->PauseMenuWidgetClass);
		}
	}
	else
	{
		PauseMenuWidget->Setup();
	}
}


void ADPlayerController::ShowGameOverMenu()
{
	if (!GameOverWidget)
	{
		// UDGameOverWidget to used is set in UDDungeonEscapeGameInstance 
		UDDungeonEscapeGameInstance* DungeonEscapeGameInstance = GetWorld()->GetGameInstance<UDDungeonEscapeGameInstance>();
		if (DungeonEscapeGameInstance)
		{
			GameOverWidget = CreateWidget<UDGameOverWidget>(GetWorld(), DungeonEscapeGameInstance->GameOverWidgetClass);
		}
	}
	else
	{
		GameOverWidget->Setup();
	}
}
