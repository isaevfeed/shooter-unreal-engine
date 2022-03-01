// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/STUAnimNotify.h"

void USTUAnimNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	OnEquipMontage.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
