// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillTreeNode.h"
#include "SkillTreeRow.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void USkillTreeNode::SetEnabled(bool Enabled)
{
	if (Enabled)
	{
		Button->SetIsEnabled(true);
		Icon->SetBrushFromTexture(EnabledIcon);
	}
	else
	{
		Button->SetIsEnabled(false);
		Icon->SetBrushFromTexture(DisabledIcon);
	}	
}

void USkillTreeNode::SetParentRow(USkillTreeRow* Row)
{
	ParentRow = Row;
}

void USkillTreeNode::AddSkillPoint()
{
	PointsInvested++;
	ParentRow->AddSkillPoint();

	UpdateText();
}

// This would be used if unreal engine actually allowed us to get which button was clicked in OnPressed, we could override that in a custom button however
void USkillTreeNode::SubtractSkillPoint()
{
	//PointsInvested--;

	//UpdateText();
}

void USkillTreeNode::InitializeNode()
{
	int tier = ParentRow->GetTier();
	if (tier == 0)
	{
		SetEnabled(true);
	}
	else
	{
		SetEnabled(false);
	}

	bool isSpecialTier = tier % 2 == 1; // If the tier is odd then it is special
	if (isSpecialTier)
	{
		MaxPointsInvested = 1;
	}
	else
	{
		MaxPointsInvested = 5;
	}
}

void USkillTreeNode::NativeConstruct()
{
	Super::NativeConstruct();

	Button.Get()->OnPressed.AddDynamic(this, &USkillTreeNode::OnButtonPressed);
}

void USkillTreeNode::UpdateText()
{
	FString pointsString = FString::Printf(TEXT("%d / %d"), PointsInvested, MaxPointsInvested);
	PointsText.Get()->SetText(FText::FromString(pointsString));
}

void USkillTreeNode::OnButtonPressed()
{
	OnAddClick.Broadcast(this);
}
