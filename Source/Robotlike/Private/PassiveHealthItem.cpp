#include "PassiveHealthItem.h"
#include "GameManager.h"
#include "Engine/World.h"

APassiveHealthItem::APassiveHealthItem()
{
    // 부모 PassiveItemBase 생성자에서 MeshComp 세팅 됨
}

void APassiveHealthItem::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (!InstigatorPawn) return;

    // GameManager 서브시스템 얻기
    if (UGameManager* GM = InstigatorPawn->GetGameInstance()->GetSubsystem<UGameManager>())
    {
        // 기존 maxHP/currentHP 에서 각각 +10
        int32 NewMax = GM->GetMaxHP() + 10;
        GM->SetMaxHP(NewMax);

        int32 NewCurrent = GM->GetCurrentHP() + 10;
        GM->SetCurrentHP(NewCurrent);

        UE_LOG(LogTemp, Log,
            TEXT("[근육(머슬)] %s 적용: maxHP %d → %d, currentHP %d → %d"),
            *GetName(),
            NewMax - 10, NewMax,
            NewCurrent - 10, NewCurrent
        );
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[근육(머슬)] GameManager를 찾을 수 없습니다."));
    }

    // 아이템 즉시 제거
    Destroy();
}
