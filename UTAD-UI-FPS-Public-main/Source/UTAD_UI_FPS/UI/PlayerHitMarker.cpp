#include "PlayerHitMarker.h"
#include "Components/Image.h"

void UPlayerHitMarker::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UPlayerHitMarker::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UPlayerHitMarker::PlayDamageAnimation()
{
	AnimationTimer = 0.0f;
	IsPlayingAnimation = true;
}

void UPlayerHitMarker::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsPlayingAnimation)
	{
		AnimationTimer += InDeltaTime;

		// Normalize the time (0 to 1) based on the animation duration
		float normalizedTime = FMath::Fmod(AnimationTimer, AnimationLength) / AnimationLength;

		// Use a sine wave to create the scale animation effect
		float currentOpacity = 0.5f * FMath::Sin(normalizedTime * PI); // 0 - 0.5 - 0;

		// Apply the opacity to the vignette image
		VignetteImage.Get()->SetOpacity(currentOpacity);

		// Reset when animation completes
		if (AnimationTimer >= AnimationLength)
		{
			AnimationTimer = 0.0f;
			IsPlayingAnimation = false;

			// Set the final opacity back to 0.0
			VignetteImage.Get()->SetOpacity(0.0f);
		}
	}
}
