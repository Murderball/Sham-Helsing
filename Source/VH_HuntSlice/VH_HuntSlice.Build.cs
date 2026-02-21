using UnrealBuildTool;

public class VH_HuntSlice : ModuleRules
{
    public VH_HuntSlice(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "UMG",
            "OnlineSubsystem",
            "OnlineSubsystemUtils",
            "AIModule",
            "NavigationSystem"
        });
    }
}
