// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	void HealActor(float HealAmount) { SetHealth(Health + HealAmount); };

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return Health <= 0; };

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() { return Health / MaxHealth; }

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealUpdateTime = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealDelay = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
	float HealModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0", ClampMax = "100"))
	float MaxHealth = 100;

	// Called when the game starts
	virtual void BeginPlay() override;
		
private:
	float Health = 0.0f;
	FTimerHandle HealTimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	void HealTick();
	void SetHealth(float NewHealth);
};
