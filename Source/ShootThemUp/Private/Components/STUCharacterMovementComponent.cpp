// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/STUBaseCharacter.h"
#include "Components/STUCharacterMovementComponent.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	float MaxSpeed = Super::GetMaxSpeed();
	ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());

	return Player && Player->IsRunning() ? MaxSpeed * 2 : MaxSpeed;
}