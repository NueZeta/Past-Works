#include "StageView.h"


void StageView::Initialize()
{
	renderer = gameObject->AddComponent<HWRenderer>("Assets/Stage/TrainingStage.mv1");
	modelHandle = renderer->GetModelHandle();
}
