// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Crosshair.h"
#include "AmmoCounter.h"
#include "PlayerHealthBar.h"
#include "ReloadBar.h"
#include "PlayerHitMarker.h"
#include "SplashScreen.h"
#include "UTAD_UI_FPS/TP_WeaponComponent.h"
#include "UTAD_UI_FPS/UTAD_UI_FPSCharacter.h"
#include "SkillTree.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerCharacter = Cast<AUTAD_UI_FPSCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void UPlayerHUD::ShowNoWeapon()
{
	//Hide the widgets that are related to the weapon,
	ReloadBar->Hide();
	AmmoCounter->Hide();
	Crosshair->Hide();
}

void UPlayerHUD::ShowAll()
{
	ReloadBar->Show();
	AmmoCounter->Show();
	Crosshair->Show();

	if (UTP_WeaponComponent* WeaponComponent = PlayerCharacter->GetAttachedWeaponComponent())
	{
		WeaponComponent->OnFire.AddDynamic(this, &UPlayerHUD::OnFire);
		WeaponComponent->OnCurrentAmmoChange.AddDynamic(this, &UPlayerHUD::UpdateCurrentAmmo);
		WeaponComponent->OnTotalAmmoChange.AddDynamic(this, &UPlayerHUD::UpdateTotalAmmo);
		WeaponComponent->OnReload.AddDynamic(this, &UPlayerHUD::UpdateReloadBar);
	}
}

void UPlayerHUD::Hide()
{
	ReloadBar->Hide();
	AmmoCounter->Hide();
	Crosshair->Hide();
}

void UPlayerHUD::PlayDamageAnimation()
{
	PlayerHitMarker.Get()->PlayDamageAnimation();
}

void UPlayerHUD::UpdateCrosshair(bool EnemyInSight)
{
	Crosshair->UpdateCrosshair(EnemyInSight);
}

void UPlayerHUD::PlaySplashScreen()
{
	SplashScreen->Show();
}

void UPlayerHUD::UpdateCurrentAmmo(int newCurrentAmmo)
{
	AmmoCounter->UpdateCurrentAmmo(newCurrentAmmo);
}

void UPlayerHUD::ShowSkillTree()
{
	SkillTreeSystem->Show();
}

void UPlayerHUD::UpdateTotalAmmo(int newTotalAmmo)
{
	AmmoCounter->UpdateTotalAmmo(newTotalAmmo);
}

void UPlayerHUD::UpdateReloadBar(float percent)
{
	ReloadBar->UpdateReloadBar(percent);
}

void UPlayerHUD::OnFire()
{
	Crosshair->ActivateFireAnimation();
}

void UPlayerHUD::UpdateHealthBar(int Health, int MaxHealth)
{
	HealthBar->UpdatePlayerHealthBar(Health, MaxHealth);
}
