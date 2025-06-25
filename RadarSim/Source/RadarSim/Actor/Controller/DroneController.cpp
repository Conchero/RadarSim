
#include "DroneController.h"
#include "NavigationSystem.h"
#include "GameFramework/Actor.h"
#include "Navigation/PathFollowingComponent.h"
#include "../Enemies/Drones.h"



void ADroneController::BeginPlay()
{
    Super::BeginPlay();


}



void ADroneController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);
    GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Cyan, FString::Printf(TEXT("InMove completed")));


}
