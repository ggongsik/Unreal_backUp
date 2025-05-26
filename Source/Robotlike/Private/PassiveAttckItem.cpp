#include "PassiveAttckItem.h"
#include "GameManager.h"
#include "Engine/World.h"

APassiveAttckItem::APassiveAttckItem()
{
    // 부모 PassiveItemBase 에서 MeshComp 생성됨
}

void APassiveAttckItem::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (!InstigatorPawn) return;

    UGameManager* GM = InstigatorPawn
        ->GetGameInstance()
        ->GetSubsystem<UGameManager>();

    if (GM)
    {
        float Old = GM->GetPlayerAttc();
        float New = Old + 0.1f;
        GM->SetPlayerAttc(New);

        UE_LOG(LogTemp, Log,
            TEXT("[attack] %s get: playerAttc %.2f → %.2f"),
            *GetName(), Old, New);
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("[attack] GameManager not found."));
    }

    Destroy();
}
