// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyHealthBar.h"

#include "Components/ProgressBar.h"

void UEnemyHealthBar::UpdateEnemyHealthBarValue(int Value, int MaxValue)
{
	float percent = static_cast<float>(Value) / MaxValue;
	EnemyHealthBar.Get()->SetPercent(percent);
}