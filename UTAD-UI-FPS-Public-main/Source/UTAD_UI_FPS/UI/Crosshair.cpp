#include "Crosshair.h"
#include "Components/Image.h"

void UCrosshair::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCrosshair::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UCrosshair::UpdateCrosshair(bool EnemyInSight)
{
	if (EnemyInSight)
	{
		Crosshair.Get()->SetColorAndOpacity(FLinearColor::Red);
	}
	else
	{
		Crosshair.Get()->SetColorAndOpacity(FLinearColor::Black);
	}
}

void UCrosshair::ActivateFireAnimation()
{
	IsFiring = true;
	AnimationTimer = 0.0f;
}

void UCrosshair::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsFiring)
	{
		AnimationTimer += InDeltaTime;

		// Normalize the time (0 to 1) based on the animation duration
		float normalizedTime = FMath::Clamp(AnimationTimer / AnimationLength, 0.0f, 1.0f);

		float growth = 0.4f * FMath::Sin(normalizedTime * PI); // 1.0 -> 1.2 -> 1.0

		// Use a sine wave to create the scale animation effect
		float scaleValue = 1.0f + growth; 

		// Apply the scale to the crosshair image
		Crosshair.Get()->SetRenderScale(FVector2D(scaleValue, scaleValue));

		// Reset when animation completes
		if (AnimationTimer >= AnimationLength)
		{
			AnimationTimer = 0.0f;
			IsFiring = false;

			// Set the final scale back to 1.0
			Crosshair->SetRenderScale(FVector2D(1.0f, 1.0f));
		}
	}
}
