// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DMenuWidgetBase.h"

// Engine Includes
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"


// Game Includes
#include "Widgets/DConfirmQuitWidget.h"


bool UDMenuWidgetBase::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	bIsFocusable = true;
	Setup();
	if (!BindWidgetEvents()) return false;

	return true;
}


bool UDMenuWidgetBase::SwitchSubmenu(UWidgetSwitcher* WidgetSwitcher, UWidget* SubmenuWidget)
{
	if (WidgetSwitcher && SubmenuWidget && WidgetSwitcher->HasChild(SubmenuWidget))
	{
		WidgetSwitcher->SetActiveWidget(SubmenuWidget);
		return true;
	}

	return false;
}


void UDMenuWidgetBase::Setup()
{
	this->AddToViewport();

	// Set the PlayerController input mode to interact with menu
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Set player control to UI input mode. Display mouse cursor.
		FInputModeUIOnly InputMode;
		InputMode.SetWidgetToFocus(this->TakeWidget());
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = true;
	}
}


void UDMenuWidgetBase::TearDown()
{
	this->RemoveFromViewport();

	// Set PlayerController input mode to interact with game
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		// Set player control to Game input mode. Hide mouse cursor.
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		PlayerController->bShowMouseCursor = false;
	}
}


void UDMenuWidgetBase::QuitGame()
{
	// Close application
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}


void UDMenuWidgetBase::ShowConfirmQuitMenu(UWidget* SpawningParet)
{
	if (!ConfirmQuitWidgetClass.Get()) return;

	if (!ConfirmQuitWidget)
	{
		ConfirmQuitWidget = CreateWidget<UDConfirmQuitWidget>(GetWorld(), ConfirmQuitWidgetClass);
	}

	if (ConfirmQuitWidget)
	{
		ConfirmQuitWidget->SetUp(SpawningParet);
	}
}
