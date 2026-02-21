using UnrealBuildTool;
using System.Collections.Generic;

public class VH_HuntSliceEditorTarget : TargetRules
{
    public VH_HuntSliceEditorTarget(TargetInfo Target) : base(Target)
    {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V5;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;
        ExtraModuleNames.Add("VH_HuntSlice");
    }
}
