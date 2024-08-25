// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()

public:
	AGunActor();
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent *Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent *Mesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *MuzzleFlash;

	UPROPERTY(EditAnywhere)
	class UParticleSystem *HitEffect;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;
};
