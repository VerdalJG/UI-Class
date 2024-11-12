// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillTreeRow.generated.h"

class USkillTreeNode;
class USkillTree;
class USkillTreeBranch;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class UTAD_UI_FPS_API USkillTreeRow : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> HorizontalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<USkillTreeNode*> Nodes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PointsRequiredToUnlockRow = 0;

	void AddSkillPoint();

	void UnlockRow();
	void LockRow();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
	TObjectPtr<USkillTreeBranch> ParentBranch;

	UPROPERTY()
	TObjectPtr<USkillTree> SkillTree;

	int RowTier = 0;
	int PointsInvestedInRow = 0;

public:
	int GetPointsInvestedInRow() { return PointsInvestedInRow; }
	int GetTier() { return RowTier; }
	bool IsSpecialRow() { return RowTier % 2 == 1; }
	void SetTier(int Tier);
	void SetParentBranch(USkillTreeBranch* Branch) { ParentBranch = Branch; }
	void SetTree(USkillTree* Tree) { SkillTree = Tree; }
	USkillTreeBranch* GetParentBranch() { return ParentBranch; }
	TArray<USkillTreeNode*> GetNodes() { return Nodes; }
	void SetPointsRequired();
};
