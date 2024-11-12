// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeBranch.generated.h"

class UTextBlock;
class USkillTreeRow;
class USkillTree;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeBranch : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> PointsText;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox;

	void DisableBranch();
	void EnableBranch();

	void AddSkillPoint();

	int PointsInvestedInBranch = 0;
	int HighestUnlockedRow = 0;
	const int MaxPointsInBranch = 18;

protected:
	virtual void NativeConstruct() override;

	void UpdateText();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkillTreeRow*> Rows;

	UPROPERTY()
	TObjectPtr<USkillTree> SkillTree;


public:
	TArray<USkillTreeRow*> GetRows() { return Rows; }
	void SetTree(USkillTree* Tree);

};
