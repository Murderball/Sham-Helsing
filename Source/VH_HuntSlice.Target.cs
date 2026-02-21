using UnrealBuildTool;
using System.Collections.Generic;

public class VH_HuntSliceTarget : TargetRules
{
    public VH_HuntSliceTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("VH_HuntSlice");
    }
}
