// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHealthBar.h"
#include "Kismet/GameplayStatics.h"
#include "../UTAD_UI_FPSCharacter.h"
#include "Components/ProgressBar.h"
#include "Math/Color.h"
#include "Styling/SlateColor.h"

#define BLINK_ANIMATION_TIME 1.f
#define BLINK_THRESHOLD 0.25f

void UPlayerHealthBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (bIsLowHealth)
	{
		LowHealthBlink(InDeltaTime);
	}
}

void UPlayerHealthBar::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHealthBar::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHealthBar::UpdatePlayerHealthBar(int NewHealth, int MaxHealth)
{
	NewHealth = FMath::Clamp(NewHealth, 0, MaxHealth);

	float percent = static_cast<float>(NewHealth) / MaxHealth;

	PlayerHealthBar->SetPercent(percent);

	if (percent <= BLINK_THRESHOLD)
	{
		bIsLowHealth = true;
	}
	else
	{
		bIsLowHealth = false;
		BlinkTimer = 0.0f;
		PlayerHealthBar->SetFillColorAndOpacity(FLinearColor::Green);
	}
}

void UPlayerHealthBar::LowHealthBlink(float DeltaTime)
{
	FProgressBarStyle Style = PlayerHealthBar.Get()->GetWidgetStyle();

	float normalizedTime = FMath::Fmod(BlinkTimer, BLINK_ANIMATION_TIME) / BLINK_ANIMATION_TIME;

	// Interpolate color between red and green based on the normalized time
	float alpha = FMath::Abs(FMath::Sin(normalizedTime * PI)); //  Use a sin wave for oscillation
	FLinearColor CurrentColor = FMath::Lerp(FLinearColor::Red, FLinearColor::Green, alpha);

	// Apply the color to the health bar
	Style.FillImage.TintColor = CurrentColor;

	PlayerHealthBar->SetWidgetStyle(Style);
	PlayerHealthBar->SetFillColorAndOpacity(CurrentColor);

	BlinkTimer += DeltaTime;
}
