// Copyright 2025 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatsComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RTU_MP_API UPlayerStatsComp : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStatsComp();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Player Stats")
	double Water;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Player Stats")
	double Food;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Player Stats")
	double Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Player Stats")
	double Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double MaxWater;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double MaxFood;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double MaxStamina;

	// Value for all items changed by a timer, could change to individual if needed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerStats")
	double TimerCallTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double WaterDrainPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double FoodDrainPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double HealthRecoveryPerSecond;

	// Amount Stamina recovers when not running
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double StaminaRecoveryPerSecond;

	// Amount stamina drops whe player is running
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Stats")
	double StaminaDrainPerSecond;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPlayerWidgetRef(class UPlayerWidget* WidgetRefIn);

	// Functions to adjust stats, able to be called from other classes
	void AdjustWater(double AmountToAdjust);
	void AdjustFood(double AmountToAdjust);
	void AdjustHealth(double AmountToAdjust);
	void AdjustStamina(double AmountToAdjust);

	void PlayerSprintChange(bool SprintingIn);
	void PlayerHealingChange(bool HealingIn);
private:
	// Water Functions
	// Server function for altering water level
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_AdjustWater(double AmountToAdjust);
	FTimerHandle WaterAdjustTimer;
	UFUNCTION()
	void EndOfWaterAdjustTimer();

	// Food Functions
	// Server function for altering Food level
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_AdjustFood(double AmountToAdjust);
	FTimerHandle FoodAdjustTimer;
	UFUNCTION()
	void EndOfFoodAdjustTimer();
	
	// Health Functions
	// Server function for altering Health level
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_AdjustHealth(double AmountToAdjust);
	FTimerHandle HealthAdjustTimer;
	UFUNCTION()
	void EndOfHealthAdjustTimer();

	// Stamina Functions
	// Server function for altering Stamina level
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_AdjustStamina(double AmountToAdjust);
	FTimerHandle StaminaAdjustTimer;
	UFUNCTION()
	void EndOfStaminaAdjustTimer();

	// Player Sprinting
	UFUNCTION(Server, Reliable)
	void ServerPlayerSprintChange(bool SprintingIn);
	UPROPERTY(Replicated)
	bool bIsSprinting;

	// Player Healing
	UFUNCTION(Server, Reliable)
	void ServerPlayerHealingChange(bool HealingIn);
	UPROPERTY(Replicated)
	bool bIsHealing;

	UPROPERTY()
	UPlayerWidget* PlayerWidgetRef;


};
