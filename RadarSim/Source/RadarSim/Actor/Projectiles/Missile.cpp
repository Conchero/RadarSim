// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Actor/Projectiles/Missile.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Enemies/Drones.h"

// Sets default values
AMissile::AMissile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");

	missileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	missileMesh->SetupAttachment(RootComponent);

	missileMesh->SetCollisionResponseToAllChannels(ECR_Overlap);

	boxCollision =CreateDefaultSubobject<UBoxComponent>("Box Collision");
	boxCollision->SetupAttachment(RootComponent);
	boxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");

}

void AMissile::OnTargetSent()
{
	projectileMovementComponent->ProjectileGravityScale = 0.1;
	projectileMovementComponent->AddForce((GetActorForwardVector() * (initialImpulseForce_Meter)));
}

void AMissile::SetTarget(AActor* _target)
{


	if (!_target)
	return;

	target  = _target;
	OnTargetSent();
}

// Called when the game starts or when spawned
void AMissile::BeginPlay()
{
	Super::BeginPlay();
	boxCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AMissile::OnComponentBeginOverlap_Action);
}

void AMissile::Destroyed()
{
	OnMissileDestroyed.Broadcast(target);

	Super::Destroyed();

}

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (target && fuel > 0)
	{
		FVector targetDirection = GetPredictedLocation(target->GetActorLocation(), lastTargetPos, DeltaTime);
		FVector missileDirection = GetPredictedLocation(GetActorLocation(), lastMissilePos,DeltaTime);

		//Vector between target and missile location
		FVector pushForce = (targetDirection - missileDirection);
		//Slow the rocket down 
		float maxSpeed = (1 / projectileMovementComponent->GetMaxSpeed())*100;
		//As the rocket approach target it slows down to get more precise
		float absoluteDistWithTarget = FMath::Abs(FVector::Dist(GetActorLocation(), target->GetActorLocation())) / maxSpeed;

		pushForce.Normalize();
		SetActorLocation(GetActorLocation() + (pushForce * absoluteDistWithTarget));

		FRotator lookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target->GetActorLocation());
		SetActorRotation(lookAtTarget);

		//Used in trajectory calculation
		lastTargetPos = target->GetActorLocation();
		lastMissilePos = GetActorLocation();
	}


}

FVector AMissile::GetPredictedLocation(FVector currentPos, FVector lastPos, float _dt)
{
	FVector dir = (currentPos - lastPos);
	//v=d/t
	float speed = FVector::Dist(currentPos,lastPos) / _dt;
	FVector predictedLocation  = currentPos + (dir* speed);

	return  predictedLocation;

}

void AMissile::OnComponentBeginOverlap_Action(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADrones>(OtherActor))
	{
		Cast<ADrones>(OtherActor)->Explode();
		Destroy();
	}
}

