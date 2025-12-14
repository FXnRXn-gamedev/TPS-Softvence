// SoftvenceTypes.h
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Softvence_Types_Enums.generated.h"

// Forward Declarations
// class AWeaponBase;
// class ABuildableBase;
// class AResourceBase;

// ============================================================================
// ENUMERATIONS
// ============================================================================

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
    None            UMETA(DisplayName = "None"),
    Rifle           UMETA(DisplayName = "Rifle"),
    Shotgun         UMETA(DisplayName = "Shotgun"),
    Pistol          UMETA(DisplayName = "Pistol"),
    SMG             UMETA(DisplayName = "SMG"),
    Crossbow        UMETA(DisplayName = "Crossbow"),
    Sniper          UMETA(DisplayName = "Sniper Rifle"),
    Melee           UMETA(DisplayName = "Melee")
};

UENUM(BlueprintType)
enum class EWeaponFireMode : uint8
{
    Single          UMETA(DisplayName = "Single"),
    Burst           UMETA(DisplayName = "Burst"),
    Auto            UMETA(DisplayName = "Automatic")
};

UENUM(BlueprintType)
enum class EResourceType : uint8
{
    None            UMETA(DisplayName = "None"),
    ScrapMetal      UMETA(DisplayName = "Scrap Metal"),
    Wood            UMETA(DisplayName = "Wood"),
    Electronics     UMETA(DisplayName = "Electronics"),
    Cloth           UMETA(DisplayName = "Cloth"),
    Chemicals       UMETA(DisplayName = "Chemicals"),
    Food            UMETA(DisplayName = "Food"),
    Water           UMETA(DisplayName = "Water"),
    Medicine        UMETA(DisplayName = "Medicine"),
    Fuel            UMETA(DisplayName = "Fuel"),
    Ammo            UMETA(DisplayName = "Ammunition")
};

UENUM(BlueprintType)
enum class EBuildingType : uint8
{
    None            UMETA(DisplayName = "None"),
    Wall            UMETA(DisplayName = "Wall"),
    Floor           UMETA(DisplayName = "Floor"),
    Roof            UMETA(DisplayName = "Roof"),
    Door            UMETA(DisplayName = "Door"),
    Window          UMETA(DisplayName = "Window"),
    Workbench       UMETA(DisplayName = "Workbench"),
    Storage         UMETA(DisplayName = "Storage"),
    Barricade       UMETA(DisplayName = "Barricade"),
    Turret          UMETA(DisplayName = "Turret"),
    Trap            UMETA(DisplayName = "Trap"),
    Generator       UMETA(DisplayName = "Generator"),
    WaterPurifier   UMETA(DisplayName = "Water Purifier"),
    FarmPlot        UMETA(DisplayName = "Farm Plot")
};

UENUM(BlueprintType)
enum class EFactionType : uint8
{
    None            UMETA(DisplayName = "None"),
    Player          UMETA(DisplayName = "Player"),
    Raiders         UMETA(DisplayName = "Raiders"),
    Survivors       UMETA(DisplayName = "Survivors"),
    Military        UMETA(DisplayName = "Military Remnants"),
    Cultists        UMETA(DisplayName = "Cultists"),
    Traders         UMETA(DisplayName = "Traders"),
    Hostile         UMETA(DisplayName = "Hostile Wildlife")
};

UENUM(BlueprintType)
enum class EFactionRelation : uint8
{
    Allied          UMETA(DisplayName = "Allied"),
    Friendly        UMETA(DisplayName = "Friendly"),
    Neutral         UMETA(DisplayName = "Neutral"),
    Unfriendly      UMETA(DisplayName = "Unfriendly"),
    Hostile         UMETA(DisplayName = "Hostile")
};

UENUM(BlueprintType)
enum class EAIState : uint8
{
    Idle            UMETA(DisplayName = "Idle"),
    Patrol          UMETA(DisplayName = "Patrol"),
    Investigate     UMETA(DisplayName = "Investigate"),
    Alert           UMETA(DisplayName = "Alert"),
    Combat          UMETA(DisplayName = "Combat"),
    Flee            UMETA(DisplayName = "Flee"),
    Dead            UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EDetectionLevel : uint8
{
    Undetected      UMETA(DisplayName = "Undetected"),
    Suspicious      UMETA(DisplayName = "Suspicious"),
    Detected        UMETA(DisplayName = "Detected"),
    FullyDetected   UMETA(DisplayName = "Fully Detected")
};

UENUM(BlueprintType)
enum class EStatusEffectType : uint8
{
    None            UMETA(DisplayName = "None"),
    Bleeding        UMETA(DisplayName = "Bleeding"),
    Poisoned        UMETA(DisplayName = "Poisoned"),
    Irradiated      UMETA(DisplayName = "Irradiated"),
    Starving        UMETA(DisplayName = "Starving"),
    Dehydrated      UMETA(DisplayName = "Dehydrated"),
    Exhausted       UMETA(DisplayName = "Exhausted"),
    Infected        UMETA(DisplayName = "Infected"),
    BrokenLimb      UMETA(DisplayName = "Broken Limb")
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    Clear           UMETA(DisplayName = "Clear"),
    Cloudy          UMETA(DisplayName = "Cloudy"),
    Rain            UMETA(DisplayName = "Rain"),
    Storm           UMETA(DisplayName = "Storm"),
    Fog             UMETA(DisplayName = "Fog"),
    RadiationStorm  UMETA(DisplayName = "Radiation Storm"),
    DustStorm       UMETA(DisplayName = "Dust Storm")
};

UENUM(BlueprintType)
enum class EHazardType : uint8
{
    None            UMETA(DisplayName = "None"),
    Radiation       UMETA(DisplayName = "Radiation"),
    Toxic           UMETA(DisplayName = "Toxic Gas"),
    Fire            UMETA(DisplayName = "Fire"),
    Electrical      UMETA(DisplayName = "Electrical"),
    Explosive       UMETA(DisplayName = "Explosive")
};

UENUM(BlueprintType)
enum class EMissionType : uint8
{
    None            UMETA(DisplayName = "None"),
    Scavenge        UMETA(DisplayName = "Scavenge"),
    Rescue          UMETA(DisplayName = "Rescue"),
    Eliminate       UMETA(DisplayName = "Eliminate"),
    Defend          UMETA(DisplayName = "Defend"),
    Escort          UMETA(DisplayName = "Escort"),
    Investigate     UMETA(DisplayName = "Investigate"),
    Sabotage        UMETA(DisplayName = "Sabotage")
};

UENUM(BlueprintType)
enum class EObjectiveStatus : uint8
{
    Inactive        UMETA(DisplayName = "Inactive"),
    Active          UMETA(DisplayName = "Active"),
    Completed       UMETA(DisplayName = "Completed"),
    Failed          UMETA(DisplayName = "Failed")
};

UENUM(BlueprintType)
enum class ECoverType : uint8
{
    None            UMETA(DisplayName = "None"),
    Low             UMETA(DisplayName = "Low Cover"),
    High            UMETA(DisplayName = "High Cover")
};

UENUM(BlueprintType)
enum class EMovementStance : uint8
{
    Standing        UMETA(DisplayName = "Standing"),
    Crouching       UMETA(DisplayName = "Crouching"),
    Prone           UMETA(DisplayName = "Prone")
};

UENUM(BlueprintType)
enum class ETrapType : uint8
{
    None            UMETA(DisplayName = "None"),
    Tripwire        UMETA(DisplayName = "Tripwire"),
    Landmine        UMETA(DisplayName = "Landmine"),
    BearTrap        UMETA(DisplayName = "Bear Trap"),
    ElectricTrap    UMETA(DisplayName = "Electric Trap"),
    GasTrap         UMETA(DisplayName = "Gas Trap"),
    NoiseDistraction UMETA(DisplayName = "Noise Distraction")
};

// ============================================================================
// STRUCTURES
// ============================================================================

USTRUCT(BlueprintType)
struct FWeaponStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float Damage = 25.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float HeadshotMultiplier = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float Range = 5000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float FireRate = 600.0f; // Rounds per minute

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float ReloadTime = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 MagazineSize = 30;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float Accuracy = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float RecoilVertical = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float RecoilHorizontal = 0.5f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float RecoilRecovery = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float ADSSpeed = 0.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float MovementSpeedMultiplier = 0.9f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    int32 PelletCount = 1; // For shotguns

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
    float SpreadAngle = 0.5f;
};

// USTRUCT(BlueprintType)
// struct FWeaponData : public FTableRowBase
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     FName WeaponID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     FText DisplayName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     EWeaponType WeaponType = EWeaponType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     EWeaponFireMode FireMode = EWeaponFireMode::Single;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     FWeaponStats Stats;
//
//     // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     // TSubclassOf<AWeaponBase> WeaponClass;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     USkeletalMesh* WeaponMesh;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     UTexture2D* Icon;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     USoundCue* FireSound;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     USoundCue* ReloadSound;
//
//     // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//     // UNiagaraSystem* MuzzleFlash;
// };
//
// USTRUCT(BlueprintType)
// struct FResourceItem
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     FName ResourceID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     FText DisplayName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     EResourceType ResourceType = EResourceType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     int32 Quantity = 1;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     int32 MaxStackSize = 99;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     float Weight = 0.1f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     UTexture2D* Icon;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
//     UStaticMesh* WorldMesh;
//
//     bool operator==(const FResourceItem& Other) const
//     {
//         return ResourceID == Other.ResourceID;
//     }
// };
//
// USTRUCT(BlueprintType)
// struct FCraftingRequirement
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     EResourceType ResourceType = EResourceType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     int32 Quantity = 1;
// };
//
// USTRUCT(BlueprintType)
// struct FCraftingRecipe : public FTableRowBase
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     FName RecipeID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     FText DisplayName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     TArray<FCraftingRequirement> Requirements;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     FResourceItem ResultItem;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     float CraftingTime = 5.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     bool bRequiresWorkbench = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     int32 RequiredWorkbenchLevel = 0;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
//     UTexture2D* Icon;
// };
//
// USTRUCT(BlueprintType)
// struct FBuildingData : public FTableRowBase
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     FName BuildingID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     FText DisplayName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     EBuildingType BuildingType = EBuildingType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     TArray<FCraftingRequirement> Requirements;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     TSubclassOf<ABuildableBase> BuildingClass;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     float BuildTime = 5.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     float MaxHealth = 500.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     UTexture2D* Icon;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
//     UStaticMesh* PreviewMesh;
// };
//
// USTRUCT(BlueprintType)
// struct FFactionData : public FTableRowBase
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     EFactionType FactionType = EFactionType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     FText FactionName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     FLinearColor FactionColor = FLinearColor::White;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     UTexture2D* FactionIcon;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     TMap<EFactionType, EFactionRelation> DefaultRelations;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     float BaseAggression = 0.5f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     bool bCanTrade = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
//     bool bCanFormAlliance = false;
// };
//
// USTRUCT(BlueprintType)
// struct FReputationData
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
//     EFactionType FactionType = EFactionType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
//     float ReputationValue = 0.0f; // -100 to 100
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reputation")
//     EFactionRelation CurrentRelation = EFactionRelation::Neutral;
//
//     EFactionRelation CalculateRelation() const
//     {
//         if (ReputationValue >= 75.0f) return EFactionRelation::Allied;
//         if (ReputationValue >= 25.0f) return EFactionRelation::Friendly;
//         if (ReputationValue >= -25.0f) return EFactionRelation::Neutral;
//         if (ReputationValue >= -75.0f) return EFactionRelation::Unfriendly;
//         return EFactionRelation::Hostile;
//     }
// };
//
// USTRUCT(BlueprintType)
// struct FSurvivalStats
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float Health = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float MaxHealth = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float Stamina = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float MaxStamina = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float Hunger = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float Thirst = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float Radiation = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Survival")
//     float MaxRadiation = 100.0f;
// };
//
// USTRUCT(BlueprintType)
// struct FStatusEffect
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     EStatusEffectType EffectType = EStatusEffectType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     float Duration = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     float RemainingTime = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     float Intensity = 1.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     float DamagePerSecond = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status")
//     bool bIsPermanent = false;
// };
//
// USTRUCT(BlueprintType)
// struct FMissionObjective
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FName ObjectiveID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FText ObjectiveText;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     EObjectiveStatus Status = EObjectiveStatus::Inactive;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     int32 CurrentProgress = 0;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     int32 RequiredProgress = 1;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     bool bIsOptional = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FVector ObjectiveLocation = FVector::ZeroVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     bool bHasLocation = false;
// };
//
// USTRUCT(BlueprintType)
// struct FMissionData : public FTableRowBase
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FName MissionID;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FText MissionName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     FText Description;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     EMissionType MissionType = EMissionType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     TArray<FMissionObjective> Objectives;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     TArray<FResourceItem> Rewards;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     int32 ExperienceReward = 100;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     TMap<EFactionType, float> ReputationChanges;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     float TimeLimit = 0.0f; // 0 = no time limit
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mission")
//     bool bIsMainMission = false;
// };
//
// USTRUCT(BlueprintType)
// struct FCoverPoint
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     FVector Location = FVector::ZeroVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     FVector CoverDirection = FVector::ForwardVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     ECoverType CoverType = ECoverType::None;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     float CoverWidth = 100.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     bool bIsOccupied = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     bool bCanShootLeft = true;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     bool bCanShootRight = true;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cover")
//     bool bCanShootOver = false;
// };
//
// USTRUCT(BlueprintType)
// struct FDetectionData
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
//     AActor* DetectedActor = nullptr;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
//     FVector LastKnownLocation = FVector::ZeroVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
//     float DetectionLevel = 0.0f; // 0-100
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
//     float TimeSinceLastSeen = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Detection")
//     bool bIsCurrentlyVisible = false;
//
//     EDetectionLevel GetDetectionState() const
//     {
//         if (DetectionLevel >= 100.0f) return EDetectionLevel::FullyDetected;
//         if (DetectionLevel >= 75.0f) return EDetectionLevel::Detected;
//         if (DetectionLevel >= 25.0f) return EDetectionLevel::Suspicious;
//         return EDetectionLevel::Undetected;
//     }
// };
//
// USTRUCT(BlueprintType)
// struct FInventorySlot
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
//     FResourceItem Item;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
//     int32 SlotIndex = -1;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
//     bool bIsEmpty = true;
// };
//
// USTRUCT(BlueprintType)
// struct FWeatherData
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     EWeatherType WeatherType = EWeatherType::Clear;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     float Intensity = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     float Duration = 300.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     float VisibilityMultiplier = 1.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     float MovementSpeedMultiplier = 1.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weather")
//     float NoiseMultiplier = 1.0f;
// };
//
// USTRUCT(BlueprintType)
// struct FDamageInfo
// {
//     GENERATED_BODY()
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     float Damage = 0.0f;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     AActor* DamageCauser = nullptr;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     AActor* DamageInstigator = nullptr;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     FVector HitLocation = FVector::ZeroVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     FVector HitDirection = FVector::ZeroVector;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     FName HitBoneName;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     bool bIsHeadshot = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     bool bIsCritical = false;
//
//     UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
//     EWeaponType WeaponType = EWeaponType::None;
// };

// ============================================================================
// DELEGATES
// ============================================================================

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStaminaChanged, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponFired, AWeaponBase*, Weapon, int32, RemainingAmmo);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponReloaded, AWeaponBase*, Weapon);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponEquipped, AWeaponBase*, Weapon);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceCollected, FResourceItem, Resource, int32, Quantity);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingPlaced, ABuildableBase*, Building);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionUpdated, FMissionData, Mission);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectiveCompleted, FMissionObjective, Objective);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnReputationChanged, EFactionType, Faction, float, NewReputation);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusEffectApplied, FStatusEffect, Effect);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStatusEffectRemoved, EStatusEffectType, EffectType);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectionLevelChanged, EDetectionLevel, NewLevel);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeatherChanged, FWeatherData, NewWeather);
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDayNightChanged, float, TimeOfDay, bool, bIsNight);