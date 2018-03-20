// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKartMovingComponent.h"
#include <Engine/World.h>


// Sets default values for this component's properties
UGoKartMovingComponent::UGoKartMovingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGoKartMovingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGoKartMovingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UGoKartMovingComponent::GetAirResistance()
{
	return -Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;
}

FVector UGoKartMovingComponent::GetRollingResistance()
{
	float AccelerationDueToGravity = -GetWorld()->GetGravityZ() / 100.0f;
	float NormalForce = AccelerationDueToGravity * Mass;

	return -Velocity.GetSafeNormal() * RollingResistenceCoefficient * NormalForce;
}

void UGoKartMovingComponent::ApplyRotation(float DeltaTime, float SteeringThrow)
{
	float DeltaLocation = FVector::DotProduct(GetOwner()->GetActorForwardVector(), Velocity) * DeltaTime;
	float RotationAngle = DeltaLocation / MinTurningRadius * SteeringThrow;
	FQuat RotationDelta(GetOwner()->GetActorUpVector(), RotationAngle);

	Velocity = RotationDelta.RotateVector(Velocity);

	GetOwner()->AddActorWorldRotation(RotationDelta);
}

void UGoKartMovingComponent::UpdateLocationFromVelocity(float DeltaTime)
{
	FVector Translation = Velocity * DeltaTime * 100;

	FHitResult OutHit;
	GetOwner()->AddActorWorldOffset(Translation, true, &OutHit);
	if (OutHit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

FGoKartMove UGoKartMovingComponent::CreateMove(float DeltaTime)
{
	FGoKartMove Move;
	Move.DeltaTime = DeltaTime;
	Move.SteeringThrow = SteeringThrow;
	Move.Throttle = Throttle;
	Move.Time = GetWorld()->TimeSeconds;

	return Move;
}

void UGoKartMovingComponent::SimulateMove(const FGoKartMove& Move)
{
	FVector Force = MaxDrivingForce * Move.Throttle * GetOwner()->GetActorForwardVector();
	Force += GetAirResistance();
	Force += GetRollingResistance();

	FVector Acceleration = Force / Mass;

	Velocity = Velocity + Acceleration * Move.DeltaTime;

	ApplyRotation(Move.DeltaTime, Move.SteeringThrow);

	UpdateLocationFromVelocity(Move.DeltaTime);
}


