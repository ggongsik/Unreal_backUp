#include "PassiveHealthItem.h"
#include "GameManager.h"
#include "Engine/World.h"

APassiveHealthItem::APassiveHealthItem()
{
    // �θ� PassiveItemBase �����ڿ��� MeshComp ���� ��
}

void APassiveHealthItem::OnInteract_Implementation(APawn* InstigatorPawn)
{
    if (!InstigatorPawn) return;

    // GameManager ����ý��� ���
    if (UGameManager* GM = InstigatorPawn->GetGameInstance()->GetSubsystem<UGameManager>())
    {
        // ���� maxHP/currentHP ���� ���� +10
        int32 NewMax = GM->GetMaxHP() + 10;
        GM->SetMaxHP(NewMax);

        int32 NewCurrent = GM->GetCurrentHP() + 10;
        GM->SetCurrentHP(NewCurrent);

        UE_LOG(LogTemp, Log,
            TEXT("[����(�ӽ�)] %s ����: maxHP %d �� %d, currentHP %d �� %d"),
            *GetName(),
            NewMax - 10, NewMax,
            NewCurrent - 10, NewCurrent
        );
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("[����(�ӽ�)] GameManager�� ã�� �� �����ϴ�."));
    }

    // ������ ��� ����
    Destroy();
}
