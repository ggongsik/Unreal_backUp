#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/**
 * IInteractable 구현 액터 클래스 중 하나를 **한 번만** 랜덤으로 스폰하는 스포너
 */
UCLASS()
class ROBOTLIKE_API AItemSpawner : public AActor
{
    GENERATED_BODY()

public:
    AItemSpawner();

    /** BeginPlay 이후 자동으로 스폰할지 여부 */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    bool bSpawnOnBeginPlay = true;

    /** BeginPlay 이후 몇 초 뒤에 스폰할지 */
    UPROPERTY(EditAnywhere, Category = "Spawner", meta = (EditCondition = "bSpawnOnBeginPlay"))
    float InitialSpawnDelay = 1.0f;

    /** 스폰할 아이템 클래스들 (IInteractable 구현) */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TArray<TSubclassOf<AActor>> SpawnClasses;

    /** 수동으로 한 번 스폰 */
    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnItem();

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle TimerHandle_Spawn;
};
