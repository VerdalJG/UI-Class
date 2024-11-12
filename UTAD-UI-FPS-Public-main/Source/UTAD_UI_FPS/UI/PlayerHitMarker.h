// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHitMarker.generated.h"

class UImage;



/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API UPlayerHitMarker : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Show();

	UFUNCTION(BlueprintCallable, Category = Visibility)
	void Hide();

	void PlayDamageAnimation();

	float AnimationTimer = 0.0f;
	const float AnimationLength = 0.5f;
	bool IsPlayingAnimation = false;

protected:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UImage> VignetteImage;
};
