// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeBranch.h"
#include "SkillTreeRow.h"
#include "SkillTreeNode.h"
#include "SkillTree.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

void USkillTreeBranch::DisableBranch()
{
	for (USkillTreeRow* row : Rows)
	{
		row->LockRow();
	}
}

void USkillTreeBranch::EnableBranch()
{
}

void USkillTreeBranch::AddSkillPoint()
{
	PointsInvestedInBranch++;

	if (HighestUnlockedRow < Rows.Num() - 1)
	{
		int NextRow = HighestUnlockedRow + 1;
		if (PointsInvestedInBranch >= Rows[NextRow]->PointsRequiredToUnlockRow && Rows[HighestUnlockedRow]->GetPointsInvestedInRow() > 0)
		{
			Rows[NextRow]->UnlockRow();
			HighestUnlockedRow = NextRow;
		}
	}

	if (PointsInvestedInBranch == MaxPointsInBranch)
	{
		for (USkillTreeRow* row : Rows)
		{
			for (USkillTreeNode* node : row->Nodes)
			{
				if (node->GetPointsInvested() == 0)
				{
					node->SetEnabled(false);
				}
			}
		}
	}

	UpdateText();
}

void USkillTreeBranch::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < VerticalBox.Get()->GetChildrenCount(); i++)
	{
		if (USkillTreeRow* row = Cast<USkillTreeRow>(VerticalBox.Get()->GetChildAt(i)))
		{
			Rows.Add(row);
			row->SetParentBranch(this);
			row->SetTier(i);
		}
	}

	UpdateText();
}

void USkillTreeBranch::UpdateText()
{
	FString pointsString = FString::Printf(TEXT("%d / %d"), PointsInvestedInBranch, MaxPointsInBranch);
	PointsText.Get()->SetText(FText::FromString(pointsString));
}

void USkillTreeBranch::SetTree(USkillTree* Tree)
{
	SkillTree = Tree;

	for (USkillTreeRow* row : Rows)
	{
		row->SetTree(Tree);
	}
}
