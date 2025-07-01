// Fill out your copyright notice in the Description page of Project Settings.


#include "PNGMissile.h"
#include "../../Components/MissileGuidance.h"
#include "GameFramework/ProjectileMovementComponent.h"

APNGMissile::APNGMissile()
{
	missileGuidanceComponent = CreateDefaultSubobject<UMissileGuidance>("Missile Guidance Component");
}

void APNGMissile::Destroyed()
{
	if (!missileGuidanceComponent)
	return;

	OnMissileDestroyed.Broadcast(missileGuidanceComponent->GetTarget());
}

void APNGMissile::BeginPlay()
{
	Super::BeginPlay();

	if (missileGuidanceComponent)
	{
		missileGuidanceComponent->SetOwnerMaxSpeed(projectileMovementComponent->GetMaxSpeed());
	}
}
