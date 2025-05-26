// Source/Robotlike/Public/Interactable.h
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class APawn;

UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interface for any actor that can be interacted with (e.g., pick up, use).
 */
class ROBOTLIKE_API IInteractable
{
    GENERATED_BODY()

public:

    /**
     * Called when a pawn interacts with this actor.
     * Blueprint classes can override this, or C++ can implement it.
     */
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
    void OnInteract(APawn* InstigatorPawn);

    virtual void OnInteract_Implementation(APawn* InstigatorPawn)
    {
        // (optional) default behavior, or leave empty
    }
    // NOTE: with BlueprintNativeEvent, you can provide a C++ default:
    // virtual void OnInteract_Implementation(APawn* InstigatorPawn) { /* default behavior */ }
};