// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/STUWeaponComponent.h"
#include "Weapon/STUBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animation/STUEquipAnimNotify.h"
#include "Animation/STUReloadAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USTUWeaponComponent::StartFire()
{
	if (!CanFire()) return;

	CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
	CurrentWeapon->StopFire();
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentWeaponIndex = 0;
	SpawnWeapons();
	InitAnimations();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!GetWorld() || !Char) return;

;	for (auto OneWeaponData : WeaponData) {
		auto Weapon = GetWorld()->SpawnActor<ASTUBaseWeapon>(OneWeaponData.WeaponClass);
		if (!Weapon) continue;

		Weapon->SetOwner(Char);
		Weapons.Add(Weapon);

		AttachWeaponToSocket(Weapon, Char->GetMesh(), WeaponArmoryPointName);
	}
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Weapon || !SceneComponent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char) return;

	Char->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
	const auto EquipAnimNotify = FindNotifyByClass<USTUEquipAnimNotify>(EquipAnimMontage);

	if (EquipAnimNotify) {
		EquipAnimNotify->OnEquipMontage.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
	}

	for (auto OneWeaponData : WeaponData) {
		const auto ReloadAnimNotify = FindNotifyByClass<USTUReloadAnimNotify>(OneWeaponData.ReloadAnimMontage);

		if (ReloadAnimNotify) {
			ReloadAnimNotify->OnEquipMontage.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
		}
	}
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char || Char->GetMesh() != MeshComp) return;

	EquipWeaponInProgress = false;
}

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char || Char->GetMesh() != MeshComp) return;

	ReloadWeaponInProgress = false;
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (!Char || !CanEquip()) return;

	EquipWeaponInProgress = true;

	if (CurrentWeapon) {
		AttachWeaponToSocket(CurrentWeapon, Char->GetMesh(), WeaponArmoryPointName);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	const auto CurrentReloadAnim = WeaponData.FindByPredicate([&](const FWeaponData& Data) {
		return Data.WeaponClass == CurrentWeapon->GetClass();
	});

	CurrentReloadAnimMontage = CurrentReloadAnim ? CurrentReloadAnim->ReloadAnimMontage : nullptr;

	AttachWeaponToSocket(CurrentWeapon, Char->GetMesh(), WeaponAttachPointName);
	PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::NextWeapon()
{
	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::Reload()
{
	if (!CanReload()) return;

	ReloadWeaponInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::CanEquip() const
{
	return !EquipWeaponInProgress && !ReloadWeaponInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
	return CurrentWeapon && !EquipWeaponInProgress && !ReloadWeaponInProgress;
}

bool USTUWeaponComponent::CanFire() const
{
	return CurrentWeapon && !EquipWeaponInProgress && !ReloadWeaponInProgress;
}

