// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeRow.h"
#include "SkillTreeBranch.h"
#include "SkillTreeNode.h"
#include "SkillTree.h"
#include "Components/HorizontalBox.h"

void USkillTreeRow::AddSkillPoint()
{
	PointsInvestedInRow++;

	if (IsSpecialRow())
	{
		for (USkillTreeNode* node : Nodes)
		{
			if (node->GetPointsInvested() == 0)
			{
				node->SetEnabled(false);
			}
		}
	}

	ParentBranch->AddSkillPoint();
}

void USkillTreeRow::UnlockRow()
{
	if (SkillTree.Get()->GetPointsLeftToDistribute() > 0)
	{
		for (USkillTreeNode* node : Nodes)
		{
			node->SetEnabled(true);
		}
	}
}

void USkillTreeRow::LockRow()
{
	for (USkillTreeNode* node : Nodes)
	{
		node->SetEnabled(false);
	}
}

void USkillTreeRow::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < HorizontalBox.Get()->GetChildrenCount(); i++)
	{
		if (USkillTreeNode* node = Cast<USkillTreeNode>(HorizontalBox.Get()->GetChildAt(i)))
		{
			Nodes.Add(node);
			node->SetParentRow(this);
		}
	}
}

void USkillTreeRow::SetTier(int Tier)
{
	RowTier = Tier;
	SetPointsRequired();
	for (USkillTreeNode* node : Nodes)
	{
		node->InitializeNode();
	}
}

void USkillTreeRow::SetPointsRequired()
{
	PointsRequiredToUnlockRow = 0;

	// Loop through each tier up to the target RowTier
	for (int i = 1; i <= RowTier; i++) // Start at 1 so we have 0 for row 0
	{
		if (i % 2 == 0)
		{
			// Even row: Add 1 point
			PointsRequiredToUnlockRow += 1;
		}
		else
		{
			// Odd row: Add 5 points
			PointsRequiredToUnlockRow += 5;
		}
	}
}
