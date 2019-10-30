//=============================================================================
//
// 新しい町イベントクラス [NewCityEvent.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "NewCityEvent.h"
#include "../../../Framework/Camera/CameraTranslationPlugin.h"
#include "../../Viewer/GameScene/EventViewer/EventViewer.h"
#include "../../Effect/GameParticleManager.h"
#include "../../../Framework/Task/TaskManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewCityEvent::NewCityEvent(EventViewer *Ptr) : eventViewer(Ptr)
{
	// 新しい町を作る予定地を取得
	NewTown = fieldEventHandler->GetNewTownPosition();
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(PositiveEvent01, [=]()
	{
		// 予定地にカメラを移動させる
		Camera::TranslationPlugin::Instance()->Move(TownPos, 30, [&]() {CreateNewCity(); });
	});
}

//=============================================================================
// デストラクタ
//=============================================================================
NewCityEvent::~NewCityEvent()
{

}

//=============================================================================
// 更新
//=============================================================================
void NewCityEvent::Update()
{
	//UseFlag = false;
}

//=============================================================================
// 描画
//=============================================================================
void NewCityEvent::Draw()
{

}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewCityEvent::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// 新しい町を作る
//=============================================================================
void NewCityEvent::CreateNewCity(void)
{
	const D3DXVECTOR3 TownPos = NewTown->GetPosition().ConvertToWorldPosition();

	fieldEventHandler->CreateNewTown(NewTown);
	GameParticleManager::Instance()->SetSingularityEffect(TownPos);
	TaskManager::Instance()->CreateDelayedTask(60, [&]() {EventOver(); });
}

//=============================================================================
// イベント終了処理
//=============================================================================
void NewCityEvent::EventOver(void)
{
	// イベント終了、ゲーム続行
	Camera::TranslationPlugin::Instance()->Restore(30, nullptr);
	fieldEventHandler->ResumeGame();
	UseFlag = false;
}