// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FVector GetAirResistance();
	FVector GetRollingResistance();

	void UpdateLocationFromVelocity(float DeltaTime);
	void ApplyRotation(float DeltaTime);
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	
	FVector Velocity;
	
	//Mass of the car (in Kg)
	UPROPERTY(EditAnywhere)
	float Mass = 1000;
	
	//The force applied to the car when the throttle is fully down (in N)
	UPROPERTY(EditAnywhere)
	float MaxDrivingForce = 10000;
	
	//Min Turning Radius at full lock (in m)
	UPROPERTY(EditAnywhere)
	float MinTurningRadius = 10;
	
	//Higher means more drag (Kg/m)
	UPROPERTY(EditAnywhere)
	float DragCoefficient = 16;

	//Higher means more rolling resistance
	UPROPERTY(EditAnywhere)
	float RollingResistenceCoefficient = 0.015f;

	float Throttle;
	float SteeringThrow;
};
