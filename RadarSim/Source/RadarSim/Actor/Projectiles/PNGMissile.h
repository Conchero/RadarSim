// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Missile.h"
#include "PNGMissile.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissileDestroyed, class AActor*, _target);

UCLASS()
class RADARSIM_API APNGMissile : public AMissile
{
	GENERATED_BODY()

private:

 APNGMissile();
 UPROPERTY(EditAnywhere);
 class UMissileGuidance* missileGuidanceComponent;

protected:

virtual void Destroyed() override;

virtual void BeginPlay() override;

public:


class UMissileGuidance* GetMissileGuidanceComponent() {return missileGuidanceComponent;};
FOnMissileDestroyed OnMissileDestroyed;



};
