// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Missile.h"
#include "PNGMissile.generated.h"

/**
 * 
 */
//Used for UI, more specifically for the Saved Target UI
//Could have used the same as the enemy entities 
//But IRL Radar don't know what kind of target it located just that it's a target (here a AActor)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissileDestroyed, class AActor*, _target);

UCLASS()
class RADARSIM_API APNGMissile : public AMissile
{
	GENERATED_BODY()

private:

 APNGMissile();

 //Component Used for PNG Homing System
 UPROPERTY(EditAnywhere);
 class UMissileGuidance* missileGuidanceComponent;

protected:

virtual void Destroyed() override;

virtual void BeginPlay() override;

public:


class UMissileGuidance* GetMissileGuidanceComponent() {return missileGuidanceComponent;};
FOnMissileDestroyed OnMissileDestroyed;



};
