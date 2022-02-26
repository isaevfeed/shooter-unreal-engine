// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STUEquipAnimNotify.h"

void USTUEquipAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	OnEquipMontage.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}