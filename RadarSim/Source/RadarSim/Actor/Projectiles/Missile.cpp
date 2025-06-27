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

// Called every frame
void AMissile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (target && fuel > 0)
	{
		FVector targetDirection = GetPredictedLocation(target->GetActorLocation(), lastTargetPos, DeltaTime);
		FVector missileDirection = GetPredictedLocation(GetActorLocation(), lastMissilePos,DeltaTime);


		DrawDebugSphere(GetWorld(), missileDirection, 50.f, 5, FColor::Magenta, false, -1.f, 0U, 10.f);
		DrawDebugSphere(GetWorld(), targetDirection, 10.f, 5,FColor::Green,false,-1.f,0U,1.f);
		DrawDebugLine(GetWorld(),missileDirection,targetDirection, FColor::Red, false, -1.f, 0U, 5.f);



		FVector pushForce = (targetDirection - missileDirection);
		float maxSpeed = (1 / projectileMovementComponent->GetMaxSpeed()) * 100;
		float absoluteDistWithTarget = FMath::Abs(FVector::Dist(GetActorLocation(), target->GetActorLocation())) / maxSpeed;

		pushForce.Normalize();

		SetActorLocation(GetActorLocation() + (pushForce * absoluteDistWithTarget));


		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("Push force %s"), *(pushForce).ToString()));


		FRotator lookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target->GetActorLocation());
		SetActorRotation(lookAtTarget);
		fuel -= DeltaTime;


		lastTargetPos = target->GetActorLocation();
		lastMissilePos = GetActorLocation();

		//if (fuel <= 0)
		//{
		//	target = nullptr;
		//}
	}


}

FVector AMissile::GetPredictedLocation(FVector currentPos, FVector lastPos, float _dt)
{

	FVector dir = (currentPos - lastPos);
	float speed = FVector::Dist(currentPos,lastPos) / (_dt*100);

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

