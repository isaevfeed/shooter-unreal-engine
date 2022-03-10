// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SphereComponent.h"
#include "Components/STUHealthComponent.h"
#include "Pickups/STUBasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogPickup, All, All);

// Sets default values
ASTUBasePickup::ASTUBasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ColComp = CreateDefaultSubobject<USphereComponent>("ColComp");
	ColComp->SetSphereRadius(100);
	ColComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ColComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(ColComp);
}

void ASTUBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!OtherActor) return;

	const auto Component = OtherActor->FindComponentByClass<USTUHealthComponent>();
	if (!Component) return;

	Component->HealActor(20);

	UE_LOG(LogPickup, Warning, TEXT("PICK UP!"));

	Destroy();
}

// Called when the game starts or when spawned
void ASTUBasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASTUBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

