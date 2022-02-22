// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUWeaponComponent::Fire()
{
	CurrentWeapon->Fire();
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
	if (!GetWorld()) return;

	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char) return;

	CurrentWeapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(WeaponClass);
	if (CurrentWeapon) {
		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
		CurrentWeapon->AttachToComponent(Char->GetMesh(), AttachmentRules, "WeaponPoint");
		CurrentWeapon->SetOwner(Char);
	}
}

