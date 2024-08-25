// Fill out your copyright notice in the Description page of Project Settings.

#include "GunActor.h"
#include "Components\SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGunActor::AGunActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGunActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return;
	AController *OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
		return;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	// the enemy is shooting himself, because his line trace is hitting his own capsule.
	// We need to ignore the gun and actor in the GunActor class by passing a parameter to LineTraceSingleByChannel that ignores these
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerPawn);

	FHitResult HitResult;
	bool Hit = GetWorld()->LineTraceSingleByChannel(HitResult, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if (Hit)
	{
		// DrawDebugPoint(GetWorld(), HitResult.Location, 20, FColor::Red, true);
		// DrawDebugSphere(GetWorld(), HitResult.Location, 4, 20, FColor::Red, true);

		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, HitResult.Location, ShotDirection.Rotation());

		AActor *Target = HitResult.GetActor();
		if (Target)
		{
			FPointDamageEvent DamageEvent(10, HitResult, ShotDirection, nullptr);
			Target->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
