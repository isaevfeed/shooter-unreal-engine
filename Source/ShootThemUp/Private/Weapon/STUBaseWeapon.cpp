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

void ASTUBaseWeapon::StartFire()
{
}

void ASTUBaseWeapon::StopFire()
{
}

// Called when the game starts or when spawned
void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	check(SkeletalMesh);
	CurrentAmmo = DefaultAmmo;
}

void ASTUBaseWeapon::MakeShot()
{
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

void ASTUBaseWeapon::DecreeseAmmo() {
	if (IsAmmoEmpty()) return;

	CurrentAmmo.Bullets -= 1;
	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty()) {
		ChangeClip();
	}
}

bool ASTUBaseWeapon::IsAmmoEmpty() const {
	return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTUBaseWeapon::IsClipEmpty() const {
	return CurrentAmmo.Bullets == 0;
}

void ASTUBaseWeapon::ChangeClip() {
	if (IsAmmoEmpty()) return;

	CurrentAmmo.Bullets = DefaultAmmo.Bullets;
	CurrentAmmo.Clips -= 1;
}

void ASTUBaseWeapon::LogAmmo() {
	FString Ammo = "Ammo : " + FString::FromInt(CurrentAmmo.Bullets) + "/";
	Ammo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);

	UE_LOG(LogBaseWeapon, Warning, TEXT("%s"), *Ammo);
}
