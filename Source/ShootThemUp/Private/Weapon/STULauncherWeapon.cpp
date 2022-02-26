// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/STULauncherWeapon.h"
#include "Weapon/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
	if (IsAmmoEmpty()) return;

	MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{
	const auto MuzzleTransform = SkeletalMesh->GetSocketTransform(MuzzleSocketName);
	ASTUProjectile* ProjectileInstance = GetWorld()->SpawnActorDeferred<ASTUProjectile>(Projectile, MuzzleTransform);

	DecreeseAmmo();

	FVector LineStart, LineEnd;
	FHitResult HitResult;
	if (!MakeTrace(HitResult, LineStart, LineEnd)) return;

	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : LineEnd;
	const FVector Direction = (EndPoint - GetMuzzleSocketTransform()).GetSafeNormal();

	if (ProjectileInstance) {
		ProjectileInstance->SetShotDirection(Direction);
		ProjectileInstance->SetOwner(GetOwner());
		ProjectileInstance->FinishSpawning(MuzzleTransform);
	}
}