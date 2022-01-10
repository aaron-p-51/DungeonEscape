// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMenuWidgetBase.h"
#include "DMainMenuWidget.generated.h"


/** Forward declarations */
class UButton;


/**
 * Widget for main menu
 */
UCLASS()
class DUNGEONESCAPE_API UDMainMenuWidget : public UDMenuWidgetBase
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
	UWidgetSwitcher* MainMenuWidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* MainMenuSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* SettingsSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* PlayButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SettingsBackButton;

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
	void OnPlayButtonClick();

	UFUNCTION()
	void OnSettingsButtonClick();

	UFUNCTION()
	void OnSettingsBackButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();

};
