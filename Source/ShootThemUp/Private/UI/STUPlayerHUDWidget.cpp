// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"

float USTUPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return 0.0f;

	const auto Component = Player->GetComponentByClass(USTUHealthComponent::StaticClass());
	const auto HealthComponent = Cast<USTUHealthComponent>(Component);
	if (!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetAmmoData(FAmmoData& AmmoData) const
{
	const auto Player = GetOwningPlayerPawn();
	if (!Player) return false;

	const auto Component = Player->GetComponentByClass(USTUWeaponComponent::StaticClass());
	const auto HealthComponent = Cast<USTUWeaponComponent>(Component);
	if (!HealthComponent) return false;

	return HealthComponent->GetWeaponAmmoData(AmmoData);
}