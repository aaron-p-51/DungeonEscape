// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMenuWidgetBase.h"
#include "DGameOverWidget.generated.h"

/** Forward declarations */
class UButton;

/**
 * Widget for game over, allow player select next options to play
 */
UCLASS()
class DUNGEONESCAPE_API UDGameOverWidget : public UDMenuWidgetBase
{
	GENERATED_BODY()
	
/**
 * Members
 */

protected:

	/**************************************************************************/
	/* Widgets */
	/**************************************************************************/
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidgetSwitcher* GameOverWidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* GameOverSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* PlayAgainButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitButton;


/**
 * Methods
 */

protected:

	virtual bool BindWidgetEvents() override;

private:
	/**************************************************************************/
	/* Widget event bindings */
	/**************************************************************************/
	UFUNCTION()
	void OnPlayAgainButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();

};
