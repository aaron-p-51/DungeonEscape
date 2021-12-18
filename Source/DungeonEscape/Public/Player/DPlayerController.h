// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"


/** Forward declarations */
class UDPauseMenuWidget;
class UDGameOverWidget;


/**
 * Base class for player controller
 */
UCLASS()
class DUNGEONESCAPE_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()

/**
 * Members
 */

private:

	/*******************************************************************/
	/* Widgets */
	/*******************************************************************/
	
	UPROPERTY()
	UDPauseMenuWidget* PauseMenuWidget;

	UPROPERTY()
	UDGameOverWidget* GameOverWidget;


 /**
  * Methods
  */
private:

	/** Player input to show pause menu */
	UFUNCTION()
	void ShowPauseMenu();

	/** Show GameOverWidget when OnLevelEscapeSuccess is called */
	UFUNCTION()
	void ShowGameOverMenu();


public:

	/* Sets default values for this Controller's properties */
	ADPlayerController();

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	/** Called when player has completed the level. Will created, if needed, and show GameOverWidget */
	void OnLevelEscapeSuccess();

};
