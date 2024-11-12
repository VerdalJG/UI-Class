#include "SplashScreen.h"
#include "Components/Image.h"

void USplashScreen::Show()
{
	SetVisibility(ESlateVisibility::HitTestInvisible);
	FadeOutTimer = 0.0f;
	SplashScreenTimer = 0.0f;
}

void USplashScreen::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USplashScreen::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsVisible())
	{
		if (SplashScreenTimer >= SplashScreenDuration)
		{
			FadeOutTimer += InDeltaTime;

			// Normalize the time (0 to 1) based on the animation duration
			float normalizedTime = FMath::Fmod(FadeOutTimer, FadeOutDuration) / FadeOutDuration;

			// Use a sine wave to create the scale animation effect
			float currentOpacity = 1.0f - FMath::Lerp(0.0f, 1.0f, normalizedTime);

			SplashImage.Get()->SetOpacity(currentOpacity);

			if (FadeOutTimer > FadeOutDuration)
			{
				Hide();
				SplashImage.Get()->SetOpacity(0.0f);
			}
		}
		else
		{
			SplashScreenTimer += InDeltaTime;
		}
	}
}
