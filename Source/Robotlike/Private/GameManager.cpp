#include "GameManager.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

// 로그 카테고리 한 번만 선언
DEFINE_LOG_CATEGORY_STATIC(LogGameManager, Log, All);

void UGameManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    // 기존 스탯 초기화 로직
    UE_LOG(LogGameManager, Log, TEXT("GM 초기화: maxHP=%d, currentHP=%d"), maxHP, currentHP);
    SetCurrentHP(maxHP);

    // 액티브 아이템 초기화
    ActiveItemClass = nullptr;
    ActiveCooldownRemaining = 0.f;
    InventoryItems.Reset();
}

void UGameManager::Deinitialize()
{
    Super::Deinitialize();
    UE_LOG(LogGameManager, Log, TEXT("GM 리셋"));
}

void UGameManager::Tick(float DeltaTime)
{
    // (쿨다운 UI용 카운트다운 로직 등 필요 시 여기에)
}

bool UGameManager::CanUseActiveItem() const
{
    if (!ActiveItemClass) return false;
    if (UWorld* W = GetWorld())
    {
        float Now = W->GetTimeSeconds();
        float Cool = ActiveItemClass.GetDefaultObject()->GetCooldown();
        return (Now - LastUseTime) >= Cool;
    }
    return false;
}

void UGameManager::SetNewActiveItemClass(TSubclassOf<AActiveItemBase> ItemClass)
{
    ActiveItemClass = ItemClass;
    float Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
    float Cool = ActiveItemClass.GetDefaultObject()->GetCooldown();
    LastUseTime = Now - Cool;
    UE_LOG(LogGameManager, Log,
        TEXT("[GameManager] NewActiveItemClass: %s | now=%.2f cooldown=%.2f lastUse=%.2f"),
        *ActiveItemClass->GetName(), Now, Cool, LastUseTime);
}

void UGameManager::UseActiveItem(APawn* InstigatorPawn)
{
    float Now = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
    bool bCan = CanUseActiveItem();
    UE_LOG(LogGameManager, Log,
        TEXT("[GameManager] UseActiveItem called | now=%.2f lastUse=%.2f canUse=%d"),
        Now, LastUseTime, bCan ? 1 : 0);

    if (!ActiveItemClass || !bCan || !InstigatorPawn) return;

    UWorld* W = GetWorld();
    if (!W) return;

    FActorSpawnParameters Params;
    Params.Owner = InstigatorPawn;
    FVector SpawnLoc = InstigatorPawn->GetActorLocation()
        + InstigatorPawn->GetControlRotation().Vector() * 100.f;
    FRotator SpawnRot = InstigatorPawn->GetControlRotation();

    AActiveItemBase* NewItem = W->SpawnActor<AActiveItemBase>(
        ActiveItemClass, SpawnLoc, SpawnRot, Params);

    if (NewItem)
    {
        NewItem->OnUse(InstigatorPawn);
    }

    LastUseTime = Now;
}

void UGameManager::AddToInventory(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass)
    {
        UE_LOG(LogGameManager, Warning, TEXT("[Inventory] AddToInventory: invalid class"));
        return;
    }

    // 1) 새 아이템 추가
    InventoryItems.Add(ItemClass);

    // 2) 전체 인벤토리 로그 출력
    UE_LOG(LogGameManager, Log,
        TEXT("[Inventory] Picked up: %s — Total items: %d"),
        *ItemClass->GetName(),
        InventoryItems.Num()
    );

    // 3) 지금까지 획득한 모든 아이템들 나열
    FString AllItems;
    for (const auto& Cls : InventoryItems)
    {
        AllItems += Cls->GetName();
        AllItems += TEXT(", ");
    }
    // 맨 뒤 쉼표 제거
    if (AllItems.Len() > 2)
    {
        AllItems.RemoveAt(AllItems.Len() - 2, 2);
    }

    UE_LOG(LogGameManager, Log,
        TEXT("[Inventory] All items: %s"),
        *AllItems
    );
}

const TArray<TSubclassOf<AActor>>& UGameManager::GetInventoryItems() const
{
    return InventoryItems;
}

//───────────────────────────────────────────────────────────────────────
// 여기서부터 본격적인 ‘로그 추가된’ SetMax/SetCurrent
//───────────────────────────────────────────────────────────────────────

void UGameManager::SetMaxHP(int32 inputHP)
{
    int32 Old = maxHP;
    maxHP = inputHP;
    UE_LOG(LogGameManager, Log,
        TEXT("[Stats] maxHP 변경: %d → %d"), Old, maxHP);
}

void UGameManager::SetCurrentHP(int32 inputHP)
{
    int32 Old = currentHP;
    currentHP = inputHP;
    UE_LOG(LogGameManager, Log,
        TEXT("[Stats] currentHP 변경: %d → %d"), Old, currentHP);
}
