// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"

class ASTUBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<ASTUBaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	UAnimMontage* ReloadAnimMontage;
};

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
	void Reload();

	bool GetWeaponAmmoData(FAmmoData& Data) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TArray<FWeaponData> WeaponData;

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

	UAnimMontage* CurrentReloadAnimMontage = nullptr;

	UPROPERTY()
	bool EquipWeaponInProgress = false;
	bool ReloadWeaponInProgress = false;

	void SpawnWeapons();
	void EquipWeapon(int32 WeaponIndex);
	void AttachWeaponToSocket(ASTUBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
	void PlayAnimMontage(UAnimMontage* AnimMontage);
	void InitAnimations();
	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnReloadFinished(USkeletalMeshComponent* MeshComp);

	bool CanEquip() const;
	bool CanReload() const;
	bool CanFire() const;

	template<typename T>
	T* FindNotifyByClass(UAnimSequenceBase* Animation)
	{
		if (!Animation) return nullptr;

		for (auto Notify : Animation->Notifies) {
			auto NotifyInit = Cast<T>(Notify.Notify);

			if (NotifyInit) {
				return NotifyInit;
			}
		}

		return nullptr;
	}
};
