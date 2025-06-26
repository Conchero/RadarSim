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
	projectileMovementComponent->AddForce((GetActorForwardVector() * (initialImpulseForce_Meter * 1000) ) );
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


		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("%s is target"), *target->GetName()));

		projectileMovementComponent->AddForce((GetActorForwardVector() * (onGoingImpulseForce_Meter * 1000)));
		FRotator lookAtTarget = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target->GetActorLocation());
		SetActorRotation(lookAtTarget);
		fuel -= DeltaTime;

		if (fuel <= 0)
		{
			target = nullptr;
		}
	}


}

void AMissile::OnComponentBeginOverlap_Action(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ADrones>(OtherActor))
	{
		Cast<ADrones>(OtherActor)->Explode();
		Destroy();
	}
}

