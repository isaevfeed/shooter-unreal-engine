// Fill out your copyright notice in the Description page of Project Settings.

#include "STUCharacterMovementComponent.h"
#include "Player/STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();
	ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * 2 : MaxSpeed;
}