// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTree.generated.h"

class UButton;
class USkillTreeBranch;
class USkillTreeRow;
class USkillTreeNode;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTree : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void Show();

	UFUNCTION()
	void Hide();

	UFUNCTION()
	void OnCloseButtonPressed();

	UFUNCTION()
	void OnAddClick(USkillTreeNode* Node);

	int GetPointsLeftToDistribute() { return PointsToDistribute; }

	TArray<USkillTreeRow*> GetAllRows();
	TArray<USkillTreeNode*> GetAllNodes();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillTreeBranch> CunningBranch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillTreeBranch> FerocityBranch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<USkillTreeBranch> ResolveBranch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkillTreeBranch*> Branches;

	int PointsToDistribute = 30;

};
