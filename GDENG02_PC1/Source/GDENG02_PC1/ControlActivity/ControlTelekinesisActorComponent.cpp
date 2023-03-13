// Copyright Epic Games, Inc. All Rights Reserved.


#include "ControlTelekinesisActorComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


UControlTelekinesisActorComponent::UControlTelekinesisActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

    this->GrabOffset = FVector(100, 100, 100);
    this->GrabbedActor = nullptr;
    this->GrabbedComponent = nullptr;
    this->REACH = 6000.0f;
    this->Force = 100.0f;
    this->bHasGrabbed = false;
}


void UControlTelekinesisActorComponent::BeginPlay()
{
	Super::BeginPlay();

    UInputComponent* inputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();
    if (inputComponent != nullptr)
    {
        inputComponent->BindAction("Telekinesis", EInputEvent::IE_Pressed, this, &UControlTelekinesisActorComponent::Telekinesis);
        inputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &UControlTelekinesisActorComponent::Throw);
    }
}


void UControlTelekinesisActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


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
                FVector GrabLocation = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() + this->GrabOffset;
                this->GrabbedPhysicsHandle->SetTargetLocation(GrabLocation);
            }
            else
            {
                //UE_LOG(LogTemp, Error, TEXT("MOVING ELSE"));
                FVector GrabLocation = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() + this->GrabOffset;
                this->GrabbedActor->SetActorLocation(GrabLocation);
            }
        }
    }
}

void UControlTelekinesisActorComponent::Telekinesis()
{
    if (this->bHasGrabbed)
    {
        Release();
    }
    else
    {
        Grab();
    }
}

void UControlTelekinesisActorComponent::Grab()
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

    DrawDebugLine(this->GetOwner()->GetWorld(), location, lineTraceEnd, FColor::Red, false, 4.f, 0.f, 1.0f);

    // check if the ray hits something
    this->GrabbedActor = hitResult.GetActor();
    if (this->GrabbedActor != nullptr)
    {
        this->bHasGrabbed = true;
        this->GrabbedComponent = hitResult.GetComponent();

        this->GrabbedPhysicsHandle = this->GrabbedActor->FindComponentByClass<UPhysicsHandleComponent>();
        if (this->GrabbedPhysicsHandle != nullptr)
        {
            FVector GrabLocation = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() + this->GrabOffset;
            this->GrabbedPhysicsHandle->GrabComponentAtLocation(this->GrabbedComponent, EName::None, GrabLocation);
        }
    }
}

void UControlTelekinesisActorComponent::Release()
{
    this->bHasGrabbed = false;
    this->GrabbedActor = nullptr;

    if (this->GrabbedPhysicsHandle != nullptr)
    {
        this->GrabbedPhysicsHandle->ReleaseComponent();
        this->GrabbedPhysicsHandle = nullptr;
    }
}

void UControlTelekinesisActorComponent::Throw()
{
    if (this->GrabbedActor)
    {

    }
}

