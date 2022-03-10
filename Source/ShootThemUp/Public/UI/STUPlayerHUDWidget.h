// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/STUBaseWeapon.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetAmmoData(FAmmoData& AmmoData) const;
};
