// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeNode.generated.h"


class UButton;
class UImage;
class UTexture2D;
class UTextBlock;
class USkillTreeRow;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddClick, USkillTreeNode*, Node);

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeNode : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> EnabledIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DisabledIcon;

	FOnAddClick OnAddClick;


	
	void InitializeNode();

protected:
	virtual void NativeConstruct() override;

	void UpdateText();

	UFUNCTION()
	void OnButtonPressed();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> Button;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> Icon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText;

	UPROPERTY()
	TObjectPtr<USkillTreeRow> ParentRow;

	int PointsInvested = 0;
	int MaxPointsInvested = 0;

public:
	void SetEnabled(bool Enabled);
	void SetParentRow(USkillTreeRow* Row);
	USkillTreeRow* GetParentRow() { return ParentRow; }

	int GetPointsInvested() { return PointsInvested; }
	int GetMaxPointsInvested() { return MaxPointsInvested; }

	void AddSkillPoint();
	void SubtractSkillPoint();
};
