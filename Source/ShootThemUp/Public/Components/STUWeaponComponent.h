// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();
	void StartFire();
	void StopFire();
	void NextWeapon();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<TSubclassOf<ASTUBaseWeapon>> WeaponClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	FName WeaponAttachPointName = "WeaponPoint";

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	FName WeaponArmoryPointName = "ArmorySocket";

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ASTUBaseWeapon* CurrentWeapon = nullptr;

	UPROPERTY()
	TArray<ASTUBaseWeapon*> Weapons;

	UPROPERTY()
	int32 CurrentWeaponIndex = 0;

	UPROPERTY()
	bool EquipWeaponInProgress = false;

	void SpawnWeapons();
	void EquipWeapon(int32 WeaponIndex);
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);

	bool CanEquip() const;
	bool CanFire() const;
};
