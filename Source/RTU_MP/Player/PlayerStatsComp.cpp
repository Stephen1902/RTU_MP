// Copyright 2025 DME Games


#include "PlayerStatsComp.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPlayerStatsComp::UPlayerStatsComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Water = 80.f;
	Food = 80.f;
	Health = 80.f;
	Stamina = 80.f;

	MaxWater = 100.f;
	MaxFood = 100.f;
	MaxHealth = 100.f;
	MaxStamina = 100.f;

	WaterDrainPerSecond = -0.025f;
	FoodDrainPerSecond = -0.0125f;
	HealthRecoveryPerSecond = 0.125f;
	StaminaDrainPerSecond = -0.125f;
	StaminaRecoveryPerSecond = 0.25f;

	TimerCallTime = 0.1f;

	bIsSprinting = false;
	bIsHealing = true;
	
	PlayerWidgetRef = nullptr;
}


// Called when the game starts
void UPlayerStatsComp::BeginPlay()
{
	Super::BeginPlay();

	Water = FMath::FRandRange(50.f, 80.f);
	GetWorld()->GetTimerManager().SetTimer(WaterAdjustTimer, this, &UPlayerStatsComp::EndOfWaterAdjustTimer, TimerCallTime, true, TimerCallTime);
	GetWorld()->GetTimerManager().SetTimer(FoodAdjustTimer, this, &UPlayerStatsComp::EndOfFoodAdjustTimer, TimerCallTime, true, TimerCallTime);
	GetWorld()->GetTimerManager().SetTimer(HealthAdjustTimer, this, &UPlayerStatsComp::EndOfHealthAdjustTimer, TimerCallTime, true, TimerCallTime);
	GetWorld()->GetTimerManager().SetTimer(StaminaAdjustTimer, this, &UPlayerStatsComp::EndOfStaminaAdjustTimer, TimerCallTime, true, TimerCallTime);
}

// Called every frame
void UPlayerStatsComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerStatsComp::SetPlayerWidgetRef(UPlayerWidget* WidgetRefIn)
{
	if (WidgetRefIn)
	{
		PlayerWidgetRef = WidgetRefIn;
	}
}

void UPlayerStatsComp::AdjustWater(double AmountToAdjust)
{
	if (GetOwner()->HasAuthority())
	{
		if (AmountToAdjust != 0)
		{
			Water = FMath::Clamp(Water + AmountToAdjust, 0.f, 100.f);
		}
	}
	else
	{
		Server_AdjustWater(AmountToAdjust);
	}
}

void UPlayerStatsComp::AdjustFood(double AmountToAdjust)
{
	if (GetOwner()->HasAuthority())
	{
		if (AmountToAdjust != 0)
		{
			Food = FMath::Clamp(Food + AmountToAdjust, 0.f, 100.f);
		}
	}
	else
	{
		Server_AdjustFood(AmountToAdjust);
	}
}

void UPlayerStatsComp::AdjustHealth(double AmountToAdjust)
{
	if (GetOwner()->HasAuthority())
	{
		
	}
	else
	{
		Server_AdjustHealth(AmountToAdjust);
	}
}

void UPlayerStatsComp::AdjustStamina(double AmountToAdjust)
{
	if (GetOwner()->HasAuthority())
	{
		if (!bIsSprinting)
		{
			Stamina = FMath::Clamp(Stamina + (StaminaRecoveryPerSecond * TimerCallTime), 0.f, MaxStamina);
		}
		else
		{
			Stamina = FMath::Clamp(Stamina + (StaminaDrainPerSecond * TimerCallTime), 0.f, MaxStamina);
		}
	}
	else
	{
		Server_AdjustStamina(AmountToAdjust);
	}
}


void UPlayerStatsComp::EndOfWaterAdjustTimer()
{
	AdjustWater(WaterDrainPerSecond * TimerCallTime);
}

void UPlayerStatsComp::Server_AdjustFood_Implementation(double AmountToAdjust)
{
	AdjustFood(AmountToAdjust);
}

bool UPlayerStatsComp::Server_AdjustFood_Validate(double AmountToAdjust)
{
	return true;
}

void UPlayerStatsComp::EndOfFoodAdjustTimer()
{
	AdjustFood(FoodDrainPerSecond * TimerCallTime);
}

void UPlayerStatsComp::Server_AdjustHealth_Implementation(double AmountToAdjust)
{
	AdjustHealth(AmountToAdjust);
}

bool UPlayerStatsComp::Server_AdjustHealth_Validate(double AmountToAdjust)
{
	return true;
}

void UPlayerStatsComp::EndOfHealthAdjustTimer()
{
	AdjustHealth(HealthRecoveryPerSecond * TimerCallTime);
}

void UPlayerStatsComp::Server_AdjustStamina_Implementation(double AmountToAdjust)
{
	AdjustStamina(AmountToAdjust);
}

bool UPlayerStatsComp::Server_AdjustStamina_Validate(double AmountToAdjust)
{
	return true;
}

void UPlayerStatsComp::EndOfStaminaAdjustTimer()
{
	AdjustStamina(StaminaRecoveryPerSecond * TimerCallTime);
}

void UPlayerStatsComp::PlayerSprintChange(bool SprintingIn)
{
	if (GetOwner()->HasAuthority())
	{
		bIsSprinting = SprintingIn;
	}
	else
	{
		ServerPlayerSprintChange(SprintingIn);
	}
}

void UPlayerStatsComp::ServerPlayerSprintChange_Implementation(bool SprintingIn)
{
	PlayerSprintChange(SprintingIn);
}

void UPlayerStatsComp::PlayerHealingChange(bool HealingIn)
{
	if (GetOwner()->HasAuthority())
	{
		bIsHealing = HealingIn;
	}
	else
	{
		ServerPlayerHealingChange(HealingIn);
	}
}

void UPlayerStatsComp::ServerPlayerHealingChange_Implementation(bool HealingIn)
{
	PlayerHealingChange(HealingIn);
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
	DOREPLIFETIME(UPlayerStatsComp, Food);
	DOREPLIFETIME(UPlayerStatsComp, Health);
	DOREPLIFETIME(UPlayerStatsComp, Stamina);
	DOREPLIFETIME(UPlayerStatsComp, bIsSprinting);
	DOREPLIFETIME(UPlayerStatsComp, bIsHealing);
}
