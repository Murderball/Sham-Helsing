using UnrealBuildTool;

public class ShamHelsing : ModuleRules
{
    public ShamHelsing(ReadOnlyTargetRules Target) : base(Target)
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
            "AIModule",
            "NavigationSystem",
            "OnlineSubsystem",
            "OnlineSubsystemUtils"
        });
    }
}
