// Copyright 2025 DME Games


#include "PlayerStatsComp.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPlayerStatsComp::UPlayerStatsComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Water = 100.f;
}


// Called when the game starts
void UPlayerStatsComp::BeginPlay()
{
	Super::BeginPlay();

	Water = FMath::FRandRange(50.f, 80.f);
	GetWorld()->GetTimerManager().SetTimer(WaterAdjustTimer, this, &UPlayerStatsComp::EndOfWaterAdjustTimer, 0.1f, true, 0.1f);
	
}

// Called every frame
void UPlayerStatsComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatsComp::AdjustWater(double AmountToAdjust)
{
	if (!GetOwner()->HasAuthority())
	{
		Server_AdjustWater(AmountToAdjust);
	}
	else
	{
		if (AmountToAdjust != 0)
		{
			Water = FMath::Clamp(Water + AmountToAdjust, 0.f, 100.f);
			const FString StringToDisplay = GetOwner()->GetName() + " has set water to " + FString::SanitizeFloat(Water);
			GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Red, *StringToDisplay);
		}
	}
}

void UPlayerStatsComp::EndOfWaterAdjustTimer()
{
	AdjustWater(-1.0f);
}

void UPlayerStatsComp::Server_AdjustWater_Implementation(double AmountToAdjust)
{
	AdjustWater(AmountToAdjust);
}

bool UPlayerStatsComp::Server_AdjustWater_Validate(double AmountToAdjust)
{
	return true;
}

void UPlayerStatsComp::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{ 
	DOREPLIFETIME(UPlayerStatsComp, Water); 
}
