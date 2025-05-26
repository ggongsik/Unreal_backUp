#include "ItemSpawner.h"
#include "Engine/World.h"
#include "TimerManager.h"

AItemSpawner::AItemSpawner()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AItemSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (bSpawnOnBeginPlay && SpawnClasses.Num() > 0)
    {
        // 한 번만 호출
        GetWorldTimerManager().SetTimer(
            TimerHandle_Spawn,
            this, &AItemSpawner::SpawnItem,
            InitialSpawnDelay,
            /*bLoop=*/ false
        );
    }
}

void AItemSpawner::SpawnItem()
{
    if (SpawnClasses.Num() == 0) return;

    int32 Index = FMath::RandRange(0, SpawnClasses.Num() - 1);
    TSubclassOf<AActor> ToSpawn = SpawnClasses[Index];
    if (!ToSpawn) return;

    UWorld* W = GetWorld();
    if (!W) return;

    FVector Loc = GetActorLocation();
    FRotator Rot = GetActorRotation();
    AActor* NewActor = W->SpawnActor<AActor>(ToSpawn, Loc, Rot);
    if (NewActor)
    {
        UE_LOG(LogTemp, Log, TEXT("[ItemSpawner] Spawned %s"), *NewActor->GetName());
    }

    // 스폰 후 타이머 클리어 (안 해도 반복 없음)
    GetWorldTimerManager().ClearTimer(TimerHandle_Spawn);
}
