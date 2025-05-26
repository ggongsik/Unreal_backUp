#include "PassiveItemBase.h"
#include "Components/StaticMeshComponent.h"

APassiveItemBase::APassiveItemBase()
{
    PrimaryActorTick.bCanEverTick = false;

    // �޽� ������Ʈ ���� �� ��Ʈ ����
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;
}

void APassiveItemBase::OnInteract_Implementation(APawn* InstigatorPawn)
{
    // ��ȣ�ۿ� ��� �ı�
    Destroy();
}
