// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();
	void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; };

protected:
	UPROPERTY(EditAnywhere, Category = "Component")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Component")
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, Category = "Component")
	float Radius = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Component")
	float Damage = 50.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FVector ShotDirection;
	UFUNCTION()
	void OnProjectiletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	AController* GetController() const;
};
