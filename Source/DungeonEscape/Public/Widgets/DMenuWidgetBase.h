// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DMenuWidgetBase.generated.h"

/** Forward declarations */
class UWidgetSwitcher;
class UDConfirmQuitWidget;

/**
 * Base class for menu widgets
 */
UCLASS()
class DUNGEONESCAPE_API UDMenuWidgetBase : public UUserWidget
{
	GENERATED_BODY()

/**
 * Members
 */

protected:

	/** Widget class for player to confirm they want to quit */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "QuitGame")
	TSubclassOf<UDConfirmQuitWidget> ConfirmQuitWidgetClass;

	UPROPERTY()
	UDConfirmQuitWidget* ConfirmQuitWidget;

/**
 * Methods
 */

protected:

	/** Setup the menu widget, set initial state of widget, This function should be overridden again in
	 * derived classes that need to bind widget events. */
	virtual bool Initialize() override;

	/**
	 * Switch UWidgetSwitcher child class.
	 *
	 * @param WidgetSwitcher		WidgetSwitcher Widget to switch current child. Must be parent of SubmenuWidget
	 * @param SubmenuWidget			Child of WidgetSwitcher to switch to. Must be child of WidgetSwitcher
	 *
	 * @return	Submenu switched
	 */
	UFUNCTION(BlueprintCallable)
	bool SwitchSubmenu(UWidgetSwitcher* WidgetSwitcher, UWidget* SubmenuWidget);

	/**
	 * Bind Widget Events, such as button click events for widgets in the menu. Called during Initialize. Is not required to override if no
	 * widget event binding is required
	 */
	UFUNCTION(BlueprintCallable)
	virtual bool BindWidgetEvents() { return true; }

	/** Quit game */
	UFUNCTION(BlueprintCallable)
	void QuitGame();

	/** Add a UDConfirmQuitWidget to Viewport. If a UDConfirmQuitWidget can not be found then one will be created */
	UFUNCTION(BlueprintCallable)
	void ShowConfirmQuitMenu(UWidget* SpawningParet);


public:

	/** Setup Widget. Adds widget to viewport, sets input mode to UI and show mouse courser for player */
	UFUNCTION(BlueprintCallable)
	virtual void Setup();

	/** Remove widget from viewport, sets input mode for game only and hides mouse courser */
	UFUNCTION(BlueprintCallable)
	virtual void TearDown();

};
