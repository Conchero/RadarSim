// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Actor/Projectiles/Missile.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

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

}

void AMissile::OnComponentBeginOverlap_Action(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

