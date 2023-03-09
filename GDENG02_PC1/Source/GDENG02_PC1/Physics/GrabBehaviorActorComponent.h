// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "../PC1/UserDefinedDataTypes.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabBehaviorActorComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GDENG02_PC1_API UGrabBehaviorActorComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UGrabBehaviorActorComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION() void Grab();
	UFUNCTION() void Release();
	UFUNCTION() void Throw();
	
private:
	UPROPERTY() float REACH = 120.0f;
	UPROPERTY() AActor* GrabbedActor = nullptr;
	UPROPERTY() UPrimitiveComponent* GrabbedPrimitiveComp = nullptr;
	UPROPERTY() UPhysicsHandleComponent* GrabbedPhysicsHandle = nullptr;
	UPROPERTY() bool bHasGrabbed = false;
};
