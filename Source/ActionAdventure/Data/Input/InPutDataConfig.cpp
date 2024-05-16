#include "Data/Input/InPutDataConfig.h"
#include "InputMappingContext.h"
#include "InputAction.h"

UInPutDataConfig::UInPutDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/_dev/Characters/Players/Input/IMC_PlayerInput.IMC_PlayerInput'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Move.IA_Move'") };
		check(Asset.Succeeded());
		Move = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Look.IA_Look'") };
		check(Asset.Succeeded());
		Look = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_SpaceBar.IA_SpaceBar'") };
		check(Asset.Succeeded());
		Jump = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_Shift.IA_Shift'") };
		check(Asset.Succeeded());
		Shift = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_MouseL.IA_MouseL'") };
		check(Asset.Succeeded());
		MouseL = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_MouseR.IA_MouseR'") };
		check(Asset.Succeeded());
		MouseR = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_1.IA_1'") };
		check(Asset.Succeeded());
		Num1 = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_2.IA_2'") };
		check(Asset.Succeeded());
		Num2 = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_3.IA_3'") };
		check(Asset.Succeeded());
		Num3 = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_G.IA_G'") };
		check(Asset.Succeeded());
		G = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/_dev/Characters/Players/Input/IA_T.IA_T'") };
		check(Asset.Succeeded());
		T = Asset.Object;
	}
}
