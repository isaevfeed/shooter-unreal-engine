// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"

void ASTURifleWeapon::StartFire()
{
	if (!GetWorld() || IsAmmoEmpty()) {
		StopFire();
		return;
	}

	MakeShot();

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::MakeShot, DelayFire, true);
}

void ASTURifleWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	if (!GetWorld()) return;

	FVector LineStart, LineEnd;
	FHitResult HitResult;
	if (!MakeTrace(HitResult, LineStart, LineEnd)) return;

	MakeDamage(HitResult);

	DecreeseAmmo();

	if (HitResult.bBlockingHit) {

		DrawDebugLine(GetWorld(), GetMuzzleSocketTransform(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 5.0f, 0, 5.0f);
	}
	else {
		DrawDebugLine(GetWorld(), GetMuzzleSocketTransform(), LineEnd, FColor::Red, false, 3.0f, 0, 3.0f);
	}
}

bool ASTURifleWeapon::GetSocketTransform(FVector& LineStart, FVector& LineEnd)
{
	FVector ViewLocation;
	FRotator ViewRotator;
	if (!GetPlayerViewPoint(ViewLocation, ViewRotator)) return false;

	LineStart = ViewLocation;
	const FVector MuzzleDestination = ViewRotator.Vector();
	LineEnd = LineStart + MuzzleDestination * ShotDistance;

	return true;
}

