// Copyright Epic Games, Inc. All Rights Reserved.


#include "GrabBehaviorActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UGrabBehaviorActorComponent::UGrabBehaviorActorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UGrabBehaviorActorComponent::BeginPlay()
{
    Super::BeginPlay();

    UInputComponent* inputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();
    if (inputComponent != nullptr)
    {
        inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabBehaviorActorComponent::Grab);
        inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabBehaviorActorComponent::Release);
        inputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &UGrabBehaviorActorComponent::Throw);
    }
}

void UGrabBehaviorActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    //UE_LOG(LogTemp, Warning, TEXT("%d"), (int32)this->bHasGrabbed);

    if (this->bHasGrabbed)
    {
        FVector location;
        FRotator rotation;
        this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
        FVector lineTraceEnd = location + rotation.Vector() * this->REACH;

        if (this->GrabbedActor != nullptr)
        {
            //UE_LOG(LogTemp, Error, TEXT("WORKING"));

            if (this->GrabbedPhysicsHandle != nullptr)
            {
                //UE_LOG(LogTemp, Error, TEXT("MOVING"));
                this->GrabbedPhysicsHandle->SetTargetLocation(lineTraceEnd);
            }
            else
            {
                //UE_LOG(LogTemp, Error, TEXT("MOVING ELSE"));
                FVector grabbedLocation = lineTraceEnd;
                this->GrabbedActor->SetActorLocation(grabbedLocation);
            }            
        }
    }
}

void UGrabBehaviorActorComponent::Grab()
{
    // initialize the ray to be traced
    FVector location;
    FRotator rotation;
    this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);
    FVector lineTraceEnd = location + rotation.Vector() * this->REACH;

    // configure the hit properties of the ray
    FHitResult hitResult;
    FCollisionObjectQueryParams objectTypeParams(ECollisionChannel::ECC_PhysicsBody);
    FCollisionQueryParams traceParams(FName(TEXT("traceQuery")), false, this->GetOwner());
    this->GetWorld()->LineTraceSingleByObjectType(hitResult, location, lineTraceEnd, objectTypeParams, traceParams);

    // check if the ray hits something
    this->GrabbedActor = hitResult.GetActor();
    if (this->GrabbedActor != nullptr)
    {
        this->bHasGrabbed = true;
        this->GrabbedPrimitiveComp = hitResult.GetComponent();

        this->GrabbedPhysicsHandle = this->GrabbedActor->FindComponentByClass<UPhysicsHandleComponent>();
        if (this->GrabbedPhysicsHandle != nullptr)
        {
            this->GrabbedPhysicsHandle->GrabComponentAtLocation(this->GrabbedPrimitiveComp, EName::None, lineTraceEnd);
        }
    }
}

void UGrabBehaviorActorComponent::Release()
{
    this->bHasGrabbed = false;
    this->GrabbedActor = nullptr;

    if (this->GrabbedPhysicsHandle != nullptr)
    {
        this->GrabbedPhysicsHandle->ReleaseComponent();
        this->GrabbedPhysicsHandle = nullptr;
    }
}

void UGrabBehaviorActorComponent::Throw()
{

}