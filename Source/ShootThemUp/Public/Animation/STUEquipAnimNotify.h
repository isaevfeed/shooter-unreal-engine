// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUEquipAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEquipMontage, USkeletalMeshComponent*);

UCLASS()
class SHOOTTHEMUP_API USTUEquipAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation) override;
	FOnEquipMontage OnEquipMontage;
};
