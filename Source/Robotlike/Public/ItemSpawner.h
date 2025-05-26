#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSpawner.generated.h"

/**
 * IInteractable ���� ���� Ŭ���� �� �ϳ��� **�� ����** �������� �����ϴ� ������
 */
UCLASS()
class ROBOTLIKE_API AItemSpawner : public AActor
{
    GENERATED_BODY()

public:
    AItemSpawner();

    /** BeginPlay ���� �ڵ����� �������� ���� */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    bool bSpawnOnBeginPlay = true;

    /** BeginPlay ���� �� �� �ڿ� �������� */
    UPROPERTY(EditAnywhere, Category = "Spawner", meta = (EditCondition = "bSpawnOnBeginPlay"))
    float InitialSpawnDelay = 1.0f;

    /** ������ ������ Ŭ������ (IInteractable ����) */
    UPROPERTY(EditAnywhere, Category = "Spawner")
    TArray<TSubclassOf<AActor>> SpawnClasses;

    /** �������� �� �� ���� */
    UFUNCTION(BlueprintCallable, Category = "Spawner")
    void SpawnItem();

protected:
    virtual void BeginPlay() override;

private:
    FTimerHandle TimerHandle_Spawn;
};
