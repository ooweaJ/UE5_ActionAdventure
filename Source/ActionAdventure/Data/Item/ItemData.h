#pragma once

#include "CoreMinimal.h"
#include "ItemData.generated.h"


USTRUCT()
struct ACTIONADVENTURE_API FItemData : public FTableRowBase
{
	GENERATED_BODY();

	FItemData() {}


public:
	UPROPERTY()
	FName ItemName;

	UPROPERTY()
	uint32 CurrentBundleCount = 0;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;

	UPROPERTY(EditAnywhere)
	uint32 MaxBundleCount = 1;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AItem> ItemClass;
};
