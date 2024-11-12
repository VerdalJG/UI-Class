// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

class UAmmoCounter;
class UCrosshair;
class UPlayerHealthBar;
class UReloadBar;
class AUTAD_UI_FPSCharacter;
class UTP_WeaponComponent;
class UWidgetAnimation;
class UPlayerHitMarker;
class USplashScreen;
class USkillTree;
class UTexture2D;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeConstruct() override;

	/** Show the Minimap and the PlayerHealthBar */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowNoWeapon();

	/** Show all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void ShowAll();

	/** Hide all the widgets */
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	
	void UpdateHealthBar(int Health, int MaxHealth);
	void PlayDamageAnimation();
	void UpdateCrosshair(bool EnemyInSight);
	void PlaySplashScreen();
	void ShowSkillTree();

protected:
	TObjectPtr<AUTAD_UI_FPSCharacter> PlayerCharacter;

	UFUNCTION()
	void UpdateCurrentAmmo(int newCurrentAmmo);

	UFUNCTION()
	void UpdateTotalAmmo(int newTotalAmmo);

	UFUNCTION()
	void UpdateReloadBar(float percent);

	UFUNCTION()
	void OnFire();


	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UPlayerHealthBar> HealthBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UCrosshair> Crosshair;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UReloadBar> ReloadBar;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UAmmoCounter> AmmoCounter;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UPlayerHitMarker> PlayerHitMarker;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<USplashScreen> SplashScreen;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<USkillTree> SkillTreeSystem;
};
