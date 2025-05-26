#include "PassiveMoveSpeedItem.h"
#include "GameManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"            // GEngine

APassiveMoveSpeedItem::APassiveMoveSpeedItem()
{
    // �θ� PassiveItemBase ���� MeshComp ������
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
            TEXT("[MoveSpeedBoost] %s ȹ��: moveSpeed %d -> %d"),
            *GetName(), Old, New);

        // ȭ�鿡�� ��� ������� (����)
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
            TEXT("[MoveSpeedBoost] GameManager ��ã��"));
    }

    Destroy();
}
