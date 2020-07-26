#include "MolVizEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/ModuleInterface.h"

IMPLEMENT_GAME_MODULE(FMolVizEditorModule, MolVizEditor);

#define LOCTEXT_NAMESPACE "MolVizEditor"

void FMolVizEditorModule::StartupModule()
{
    //UE_LOG(MolVizEditor, Warning, TEXT("MolVizEditor: Log Started"));
}

void FMolVizEditorModule::ShutdownModule()
{
    //UE_LOG(MolVizEditor, Warning, TEXT("MolVizEditor: Log Ended"));
}

#undef LOCTEXT_NAMESPACE