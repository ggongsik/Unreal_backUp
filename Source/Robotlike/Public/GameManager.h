#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ActiveItemBase.h"
#include "ItemBase.h"
#include "GameManager.generated.h"

/**
 * 게임 전반의 스탯과 아이템(액티브·패시브)을 관리하는 서브시스템
 */
UCLASS()
class ROBOTLIKE_API UGameManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    // 서브시스템 초기화/종료
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    // 매 프레임 호출 (FPSPlayer::Tick에서)
    void Tick(float DeltaTime);

    //──────────────────────────────────────────────────────────
    // 1) 플레이어 스탯 관리
    //──────────────────────────────────────────────────────────

    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 maxHP = 100;
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 currentHP = 100;
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    float playerAttc = 1.f;
    UPROPERTY(BlueprintReadOnly, Category = "Stats")
    int32 moveSpeed = 600;

    // 접근자
    int32 GetMaxHP()     const { return maxHP; }
    int32 GetCurrentHP() const { return currentHP; }
    int32 GetMoveSpeed() const { return moveSpeed; }
    float GetPlayerAttc()const { return playerAttc; }

    // 설정자 (로그 포함)
    void SetMaxHP(int32 inputHP);
    void SetCurrentHP(int32 inputHP);
    void SetMoveSpeed(int32 inputSpeed) { moveSpeed = inputSpeed; }
    void SetPlayerAttc(float inputAttc) { playerAttc = inputAttc; }
    void UpPlayerAttc(float upgradeCoex) { playerAttc += upgradeCoex; }

    //──────────────────────────────────────────────────────────
    // 2) 액티브 아이템 관리
    //──────────────────────────────────────────────────────────

    UPROPERTY(BlueprintReadOnly, Category = "ActiveItem")
    float ActiveCooldownRemaining = 0.f;

    bool CanUseActiveItem() const;
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void SetNewActiveItemClass(TSubclassOf<AActiveItemBase> ItemClass);
    void UseActiveItem(APawn* InstigatorPawn);
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    void AddToInventory(TSubclassOf<AActor> ItemClass);
    UFUNCTION(BlueprintCallable, Category = "Inventory")
    const TArray<TSubclassOf<AActor>>& GetInventoryItems() const;

protected:
    float LastUseTime = -FLT_MAX;
    UPROPERTY()
    TSubclassOf<AActiveItemBase> ActiveItemClass;
    UPROPERTY()
    AActiveItemBase* ActiveItem = nullptr;
    UPROPERTY(VisibleAnywhere, Category = "Inventory")
    TArray<TSubclassOf<AActor>> InventoryItems;
};