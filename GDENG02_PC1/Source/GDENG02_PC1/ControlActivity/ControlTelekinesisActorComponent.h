// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ControlTelekinesisActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG02_PC1_API UControlTelekinesisActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UControlTelekinesisActorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION() void Telekinesis();
	UFUNCTION() void Grab();
	UFUNCTION() void Release();
	UFUNCTION() void Throw();


private:
	UPROPERTY() float Force;
	UPROPERTY() float REACH;
	UPROPERTY(VisibleAnywhere) bool bHasGrabbed;
	UPROPERTY() FVector GrabOffset;
	UPROPERTY() AActor* GrabbedActor;
	UPROPERTY() UPrimitiveComponent* GrabbedComponent;
	UPROPERTY() UPhysicsHandleComponent* GrabbedPhysicsHandle;
	UPROPERTY(EditAnywhere) ACameraActor* Camera;
};
