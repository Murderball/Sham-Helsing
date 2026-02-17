using UnrealBuildTool;

public class VHPhasmaSlice : ModuleRules
{
    public VHPhasmaSlice(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG",
            "Slate",
            "SlateCore",
            "AIModule",
            "GameplayTags",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "NavigationSystem"
        });
    }
}
