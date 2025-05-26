#include "FPSPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameManager.h"
#include "ActiveItemBase.h"
#include "Interactable.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPSPlayer, Log, All);

AFPSPlayer::AFPSPlayer()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    FPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FPSCamera->SetupAttachment(GetCapsuleComponent());
    FPSCamera->bUsePawnControlRotation = true;
}

void AFPSPlayer::BeginPlay()
{
    Super::BeginPlay();

    GameManager = GetGameInstance()
        ? GetGameInstance()->GetSubsystem<UGameManager>()
        : nullptr;
    if (!GameManager)
    {
        UE_LOG(LogFPSPlayer, Warning, TEXT("GameManager subsystem not found"));
    }
}

void AFPSPlayer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (GameManager)
    {
        GameManager->Tick(DeltaTime);
    }
}

void AFPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("Forward", this, &AFPSPlayer::MoveForward);
    PlayerInputComponent->BindAxis("Right", this, &AFPSPlayer::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &AFPSPlayer::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &AFPSPlayer::AddControllerPitchInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSPlayer::Jump);
    PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &AFPSPlayer::Interact);
    PlayerInputComponent->BindAction("UseActive", IE_Pressed, this, &AFPSPlayer::UseActiveItem);
}

void AFPSPlayer::MoveForward(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        const FVector Dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
        AddMovementInput(Dir, Value);
    }
}

void AFPSPlayer::MoveRight(float Value)
{
    if (Controller && FMath::Abs(Value) > KINDA_SMALL_NUMBER)
    {
        const FVector Dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
        AddMovementInput(Dir, Value);
    }
}

bool AFPSPlayer::PerformTrace(float Distance, FHitResult& OutHit)
{
    const FVector Start = FPSCamera->GetComponentLocation();
    const FVector End = Start + FPSCamera->GetForwardVector() * Distance;

    FCollisionQueryParams Params(TEXT("InteractTrace"), false, this);
    const bool bHit = GetWorld()->LineTraceSingleByChannel(
        OutHit, Start, End, ECC_Visibility, Params);

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
    DrawDebugLine(GetWorld(), Start, End,
        bHit ? FColor::Green : FColor::Red,
        false, 1.5f, 0, 2.0f);
#endif

    return bHit;
}

void AFPSPlayer::Interact()
{
    UE_LOG(LogFPSPlayer, Warning, TEXT(">>> Interact() called"));

    if (!PerformTrace(TraceDistance, /*Out*/ *(new FHitResult()))) return;

    FHitResult Hit;
    if (!PerformTrace(TraceDistance, Hit) || !Hit.GetActor())
    {
        UE_LOG(LogFPSPlayer, Log, TEXT("Interact: No hit actor"));
        return;
    }

    AActor* HitActor = Hit.GetActor();

    // 액티브 아이템 클래스 획득
    if (AActiveItemBase* Active = Cast<AActiveItemBase>(HitActor))
    {
        GameManager->SetNewActiveItemClass(Active->GetClass());
        UE_LOG(LogFPSPlayer, Log, TEXT("Acquired Active Item"));
        HitActor->Destroy();
        return;
    }

    // 인터랙터블 호출
    if (HitActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
    {
        IInteractable::Execute_OnInteract(HitActor, this);
        UE_LOG(LogFPSPlayer, Log, TEXT("Execute_OnInteract called"));
    }
}

void AFPSPlayer::UseActiveItem()
{
    UE_LOG(LogFPSPlayer, Warning, TEXT("UseActiveItem pressed"));

    if (!GameManager)
    {
        UE_LOG(LogFPSPlayer, Warning, TEXT("GameManager missing"));
        return;
    }

    if (GameManager->CanUseActiveItem())
    {
        GameManager->UseActiveItem(this);
        UE_LOG(LogFPSPlayer, Log, TEXT("Used Active Item"));
    }
    else
    {
        UE_LOG(LogFPSPlayer, Log, TEXT("Active item not ready"));
    }
}
