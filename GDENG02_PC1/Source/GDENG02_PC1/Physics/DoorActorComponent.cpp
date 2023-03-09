// Copyright Epic Games, Inc. All Rights Reserved.


#include "DoorActorComponent.h"

UDoorActorComponent::UDoorActorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

}

void UDoorActorComponent::BeginPlay()
{
    Super::BeginPlay();

    this->InitialYaw = this->GetOwner()->GetActorRotation().Yaw;
    this->CurrentYaw = this->InitialYaw;
    this->OpeningYaw += this->InitialYaw;
    this->ClosingYaw += this->InitialYaw;

    //this->ActorOpener = this->GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UDoorActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (this->State == EDoorStates::Open && this->GetOwner()->GetActorRotation().Yaw != this->OpeningYaw)
    {
        FRotator doorRot = this->GetOwner()->GetActorRotation();
        this->CurrentYaw = FMath::Lerp(this->CurrentYaw, this->OpeningYaw, DeltaTime * 2.0f);
        doorRot.Yaw = this->CurrentYaw;
        this->GetOwner()->SetActorRotation(doorRot);
    }
    else  if (this->State == EDoorStates::Closed && this->GetOwner()->GetActorRotation().Yaw != this->ClosingYaw)
    {
        if (this->Ticks < this->CLOSING_TIME)
        {
            this->Ticks += DeltaTime;
        }
        else
        {
            FRotator doorRot = this->GetOwner()->GetActorRotation();
            this->CurrentYaw = FMath::Lerp(this->CurrentYaw, this->ClosingYaw, DeltaTime * 2.0f);
            doorRot.Yaw = this->CurrentYaw;
            this->GetOwner()->SetActorRotation(doorRot);
        }
    }


    if (GetPressurePlateTotalMass() >= this->TotalMass && this->State == EDoorStates::Closed)
    {
        this->State = EDoorStates::Open;
        this->InitialYaw = this->GetOwner()->GetActorRotation().Yaw;
        this->Ticks = 0.0f;
    }
    else if (GetPressurePlateTotalMass() < this->TotalMass && this->State == EDoorStates::Open)
    {
        this->State = EDoorStates::Closed;
        this->InitialYaw = this->GetOwner()->GetActorRotation().Yaw;
        this->Ticks = 0.0f;
    }
}

float UDoorActorComponent::GetPressurePlateTotalMass() const
{
    if (this->PressurePlate == nullptr)
        return -1.0f;


    TArray<AActor*> actors;
    this->PressurePlate->GetOverlappingActors(actors);

    float mass = 0.0f;
    for (int32 i = 0; i < actors.Num(); i++)
    {
        UPrimitiveComponent* primitive = actors[i]->FindComponentByClass<UPrimitiveComponent>();
        mass += primitive->GetMass();
    }

    UE_LOG(LogTemp, Warning, TEXT("%f"), mass);

    return mass;
}