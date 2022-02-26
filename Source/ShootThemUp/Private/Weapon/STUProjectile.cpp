// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	SphereComponent->SetSphereRadius(5.0f);
	SetRootComponent(SphereComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
	MovementComponent->InitialSpeed = 2000;
	MovementComponent->ProjectileGravityScale = 0;
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

	check(MovementComponent);
	check(SphereComponent);
	MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
	SphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ASTUProjectile::OnProjectiletHit);

	SetLifeSpan(5);
}

AController* ASTUProjectile::GetController() const
{
	auto Pawn = Cast<APawn>(GetOwner());

	return Pawn ? Pawn->GetController() : nullptr;
}

void ASTUProjectile::OnProjectiletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!GetWorld()) return;

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		Damage,
		GetActorLocation(),
		Radius,
		UDamageType::StaticClass(),
		{ GetOwner() },
		this,
		GetController(),
		true
	);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, FColor::Red, false, 5);

	Destroy();
}

