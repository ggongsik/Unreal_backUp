#include "PassiveMoveSpeedItem.h"
#include "GameManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"            // GEngine

APassiveMoveSpeedItem::APassiveMoveSpeedItem()
{
    // ºÎ¸ð PassiveItemBase ¿¡¼­ MeshComp »ý¼ºµÊ
}

void APassiveMoveSpeedItem::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (!InstigatorPawn) return;

    UGameManager* GM = InstigatorPawn
        ->GetGameInstance()
        ->GetSubsystem<UGameManager>();

    if (GM)
    {
        int32 Old = GM->GetMoveSpeed();
        int32 New = Old + 150;
        GM->SetMoveSpeed(New);

        UE_LOG(LogTemp, Log,
            TEXT("[MoveSpeedBoost] %s È¹µæ: moveSpeed %d -> %d"),
            *GetName(), Old, New);

        // È­¸é¿¡µµ Àá±ñ ¶ç¿öº¸±â (¼±ÅÃ)
        if (GEngine && InstigatorPawn->GetController())
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 3.f, FColor::Green,
                FString::Printf(TEXT("Speed: %d -> %d"), Old, New)
            );
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning,
            TEXT("[MoveSpeedBoost] GameManager ¸øÃ£À½"));
    }

    Destroy();
}
