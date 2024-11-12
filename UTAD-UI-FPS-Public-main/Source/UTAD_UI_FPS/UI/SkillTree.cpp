// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTree.h"
#include "Components/Button.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SkillTreeBranch.h"
#include "SkillTreeRow.h"
#include "SkillTreeNode.h"
#include "Components/VerticalBox.h"

void USkillTree::Show()
{
	SetVisibility(ESlateVisibility::SelfHitTestInvisible);
}

void USkillTree::Hide()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void USkillTree::OnCloseButtonPressed()
{
	Hide();
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->SetPause(false);
	PlayerController->bShowMouseCursor = false;
	UWidgetBlueprintLibrary::SetInputMode_GameOnly(PlayerController);
}

void USkillTree::OnAddClick(USkillTreeNode* Node)
{
	// Skill tree must have points to distribute
	if (PointsToDistribute == 0)
	{
		return;
	}

	USkillTreeRow* row = Node->GetParentRow();
	USkillTreeBranch* branch = row->GetParentBranch();
	int branchesWithPoints = 0;

	if (row)
	{
		if (row->IsSpecialRow() && row->GetPointsInvestedInRow() > 0)
		{
			return;
		}
	}

	if (branch)
	{
		if (branch->PointsInvestedInBranch == 0)
		{

			for (USkillTreeBranch* otherBranch : Branches)
			{
				if (otherBranch != branch && otherBranch->PointsInvestedInBranch > 0)
				{
					branchesWithPoints++;
				}
			}
			if (branchesWithPoints == 2)
			{
				return;
			}
		}

		else if (branch->PointsInvestedInBranch == 18)
		{
			return;
		}
	}

	if (Node->GetPointsInvested() == Node->GetMaxPointsInvested())
	{
		return;
	}
	
	if (branchesWithPoints == 1)
	{
		for (USkillTreeBranch* otherBranch : Branches)
		{
			if (otherBranch != branch && otherBranch->PointsInvestedInBranch == 0)
			{
				otherBranch->DisableBranch();
			}
		}
	}

	PointsToDistribute--;

	if (PointsToDistribute == 0)
	{
		for (USkillTreeNode* node : GetAllNodes())
		{
			if (node != Node && node->GetPointsInvested() == 0)
			{
				node->SetEnabled(false);
			}
		}
	}

	Node->AddSkillPoint();
}

void USkillTree::NativeConstruct()
{
	Super::NativeConstruct();

	CloseButton.Get()->OnPressed.AddDynamic(this, &USkillTree::OnCloseButtonPressed);
	Branches.Add(FerocityBranch);
	Branches.Add(CunningBranch);
	Branches.Add(ResolveBranch);

	for (USkillTreeBranch* branch : Branches)
	{
		branch->SetTree(this);
	}

	for (USkillTreeNode* node : GetAllNodes())
	{
		node->OnAddClick.AddDynamic(this, &USkillTree::OnAddClick);
	}
}

TArray<USkillTreeRow*> USkillTree::GetAllRows()
{
	TArray<USkillTreeRow*> AllRows;
	for (USkillTreeBranch* Branch : Branches)
	{
		if (Branch)
		{
			AllRows.Append(Branch->GetRows());
		}
	}
	return AllRows;
}

TArray<USkillTreeNode*> USkillTree::GetAllNodes()
{
	TArray<USkillTreeNode*> AllNodes;
	for (USkillTreeBranch* Branch : Branches)
	{
		for (USkillTreeRow* Row : Branch->GetRows())
		{
			if (Row)
			{
				AllNodes.Append(Row->GetNodes());
			}
		}
	}
	return AllNodes;
}
