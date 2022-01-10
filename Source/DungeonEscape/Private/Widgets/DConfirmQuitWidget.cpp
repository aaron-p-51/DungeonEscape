// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/DConfirmQuitWidget.h"

// Engine Includes
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


// Game Includes
#include "Widgets/DMenuWidgetBase.h"


bool UDConfirmQuitWidget::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	Success = BindWidgetEvents();
	return Success;
}


bool UDConfirmQuitWidget::BindWidgetEvents()
{
	if (!CancelQuitButton) return false;
	if (!CancelQuitButton->OnClicked.IsBound())
	{
		CancelQuitButton->OnClicked.AddDynamic(this, &UDConfirmQuitWidget::OnCancelQuitButtonClick);
	}

	if (!ConfirmQuitButton) return false;
	if (!ConfirmQuitButton->OnClicked.IsBound())
	{
		ConfirmQuitButton->OnClicked.AddDynamic(this, &UDConfirmQuitWidget::OnConfirmQuitButtonClick);
	}

	return true;
}


void UDConfirmQuitWidget::OnCancelQuitButtonClick()
{
	if (SpawningParentWidget)
	{
		SpawningParentWidget->SetIsEnabled(true);
	}

	this->RemoveFromViewport();
}


void UDConfirmQuitWidget::OnConfirmQuitButtonClick()
{
	// Close application
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), PlayerController, EQuitPreference::Quit, false);
	}
}


void UDConfirmQuitWidget::SetUp(UWidget* ParentWidget)
{
	if (ParentWidget)
	{
		SpawningParentWidget = ParentWidget;
		SpawningParentWidget->SetIsEnabled(false);
	}

	this->AddToViewport();
}
