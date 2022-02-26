// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/STUBaseWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUBaseWeapon
{
	GENERATED_BODY()

public:
	virtual void StartFire() override;
	virtual void StopFire() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	float DelayFire = 0.1f;

	virtual void MakeShot() override;
	virtual bool GetSocketTransform(FVector& LineStart, FVector& LineEnd) override;

private:
	FTimerHandle FireTimerHandle;
};
