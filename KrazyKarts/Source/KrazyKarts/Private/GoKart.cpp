// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"
#include <Components/InputComponent.h>
#include "GoKartMovingComponent.h"
#include "GoKartMovingReplicationComponent.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bReplicateMovement = false;

	MovementComponent = CreateDefaultSubobject<UGoKartMovingComponent>(TEXT("MovementComponent"));
	ReplicationComponent = CreateDefaultSubobject<UGoKartMovingReplicationComponent>(TEXT("ReplicationComponent"));
}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
	}
}


// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
}

void AGoKart::MoveForward(float Value)
{
	if (MovementComponent == nullptr) return;
	
	MovementComponent->SetThrottle(Value);
}

void AGoKart::MoveRight(float Value)
{
	if (MovementComponent == nullptr) return;
	
	MovementComponent->SetSteeringThrow(Value);
}