// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STUBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All);

// Sets default values
ASTUBaseWeapon::ASTUBaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);
}

void ASTUBaseWeapon::Fire()
{
	MakeShot();
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(SkeletalMesh);
}

void ASTUBaseWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector LineStart, LineEnd;
	FHitResult HitResult;
	if (!MakeTrace(HitResult, LineStart, LineEnd)) return;

	MakeDamage(HitResult);

	if (HitResult.bBlockingHit) {

		DrawDebugLine(GetWorld(), GetMuzzleSocketTransform(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 5.0f, 0, 5.0f);
	}
	else {
		DrawDebugLine(GetWorld(), GetMuzzleSocketTransform(), LineEnd, FColor::Red, false, 3.0f, 0, 3.0f);

	}
}

AController* ASTUBaseWeapon::GetPlayerController() const
{
	const auto Player = Cast<ACharacter>(GetOwner());
	if (!Player) return nullptr;

	return Player->GetController();
}


bool ASTUBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotator)
{
	const auto Controller = GetPlayerController();
	if (!Controller) return false;

	Controller->GetPlayerViewPoint(ViewLocation, ViewRotator);

	return true;
}

FVector ASTUBaseWeapon::GetMuzzleSocketTransform() const
{
	return SkeletalMesh->GetSocketTransform(MuzzleSocketName).GetLocation();
}

bool ASTUBaseWeapon::MakeTrace(FHitResult& HitResult, FVector& LineStart, FVector& LineEnd)
{
	if (!GetWorld()) return false;

	if (!GetSocketTransform(LineStart, LineEnd)) return false;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, LineStart, LineEnd, ECollisionChannel::ECC_Visibility, QueryParams);

	return true;
}

void ASTUBaseWeapon::MakeDamage(FHitResult& HitResult) const
{
	const auto DamageActor = HitResult.GetActor();

	if (!DamageActor) return;

	HitResult.GetActor()->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), GetOwner());
}

bool ASTUBaseWeapon::GetSocketTransform(FVector& LineStart, FVector& LineEnd)
{
	FVector ViewLocation;
	FRotator ViewRotator;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotator)) return false;

	LineStart = ViewLocation;
	const FVector MuzzleDestination = ViewRotator.Vector();
	LineEnd = LineStart + MuzzleDestination * ShotDistance;

	return true;
}
