// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USTUHealthComponent;
class UTextRenderComponent;
class USTUWeaponComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASTUBaseCharacter(const FObjectInitializer& InitObj);

	UFUNCTION(BlueprintCallable)
	bool IsRunning();

	UFUNCTION(BlueprintCallable)
	float GetInputDirection() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamageVelocity = FVector2D(900, 1200);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamage = FVector2D(10, 100);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	UTextRenderComponent* HealthRenderComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* DeathAnimMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons")
	USTUWeaponComponent* WeaponComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	bool WantToRunning = false;

	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void StartRun();
	void StopRun();

	void OnDeath();
	void OnHealthChanged(float Health);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
