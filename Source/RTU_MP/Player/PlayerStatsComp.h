// Copyright 2025 DME Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatsComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_AdjustWater(double AmountToAdjust);

	void AdjustWater(double AmountToAdjust);
	FTimerHandle WaterAdjustTimer;
	UFUNCTION()
	void EndOfWaterAdjustTimer();
	
};
