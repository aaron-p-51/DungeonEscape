// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DMenuWidgetBase.h"
#include "DPauseMenuWidget.generated.h"


/** Forward declarations */
class UButton;
class UDConfirmQuitWidget;


/**
 * Widget for pause menu
 */
UCLASS()
class DUNGEONESCAPE_API UDPauseMenuWidget : public UDMenuWidgetBase
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
	UWidgetSwitcher* PauseMenuWidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* PauseSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* SettingsSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UWidget* ConfirmMainMenuSubmenu;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SettingsBackButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* MainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelMainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ConfirmMainMenuButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* QuitButton;

	
/**
 * Methods
 */

private:

	/**************************************************************************/
	/* Widget event bindings */
	/**************************************************************************/
	UFUNCTION()
	void OnResumeButtonClick();

	UFUNCTION()
	void OnSettingsButtonClick();

	UFUNCTION()
	void OnSettingsBackButtonClick();

	UFUNCTION()
	void OnMainMenuButtonClick();

	UFUNCTION()
	void OnCancelMainMenuButtonClick();

	UFUNCTION()
	void OnConfirmMainMenuButtonClick();

	UFUNCTION()
	void OnQuitButtonClick();


protected:

	virtual bool BindWidgetEvents() override;


 public:

	/** Pause game when this widget is added to viewport */
	virtual void Setup() override;

};
