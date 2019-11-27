//=============================================================================
//
// 新しい町(宇宙レベル)イベントクラス [NewTownEvent_Space.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../../main.h"
#include "NewTownEvent_Space.h"
#include "../../EventActor/PlanetActor.h"
#include "../../../Viewer/GameScene/EventViewer/EventTelop.h"
#include "../../../Viewer/GameScene/Controller/EventViewer.h"
#include "../../../Effect/GameParticleManager.h"
#include "../../../Field/Camera/EventCamera.h"

#include "../../../../Framework/Task/TaskManager.h"
#include "../../../../Framework/Math/Easing.h"

enum State
{
	TelopExpanding,
	PlanetDebut,
	PlanetArrive,
};
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// 落下速度
const int FallFrame = 90;
// 惑星モデルのスケール
const D3DXVECTOR3 Scale = D3DXVECTOR3(0.25f, 0.25f, 0.25f);

//*****************************************************************************
// スタティック変数宣言
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
NewTownEvent_Space::NewTownEvent_Space(EventViewer *Ptr, std::function<void(void)> EventOverFunc, EventCamera *camera) :
	EventBase(true),
	eventViewer(Ptr),
	EventState(TelopExpanding),
	EventOverFunc(EventOverFunc),
	camera(camera),
	CountFrame(0)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
NewTownEvent_Space::~NewTownEvent_Space()
{
	eventViewer = nullptr;
	NewPlanet = nullptr;
	camera = nullptr;
	MoveTailEmitter = nullptr;
	StarDustEmitter = nullptr;
	SAFE_DELETE(PlanetModel);
}

//=============================================================================
// 初期化
//=============================================================================
void NewTownEvent_Space::Init()
{
	// 新しい惑星を作る予定座標を取得
	NewPlanet = fieldEventHandler->GetNewTownPosition();
	BuildPos = NewPlanet->GetPosition().ConvertToWorldPosition();

	// 惑星落下方向計算
	StartPos = BuildPos + D3DXVECTOR3(100.0f, 100.0f, 0.0f);

	// 惑星メッシュ作成
	PlanetModel = new PlanetActor(StartPos, Scale, "Space-Town");

	// ゲーム進行停止
	fieldEventHandler->PauseGame();

	// テロップ設置
	eventViewer->SetEventTelop(EventTelop::NewPlanet, [=]()
	{
		// 惑星にカメラを移動させる
		camera->Translation(StartPos, 30, [&]() {FallenStart(); });
	});

	// 初期化終了
	Initialized = true;
}

//=============================================================================
// 更新
//=============================================================================
void NewTownEvent_Space::Update()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	if (EventState == PlanetDebut)
	{
		CountFrame++;
		float Time = (float)CountFrame / (float)FallFrame;

		D3DXVECTOR3 PlanetPos = Easing::EaseValue(Time, StartPos, BuildPos, EaseType::OutQuart);
		PlanetModel->SetPosition(PlanetPos);
		MoveTailEmitter->SetPosition(PlanetPos);
		StarDustEmitter->SetPosition(PlanetPos);

		camera->Translation(PlanetPos, 1, nullptr);

		if (CountFrame >= FallFrame)
		{
			EventState = PlanetArrive;
			TaskManager::Instance()->CreateDelayedTask(30, [&]()
			{
				camera->Return(15, EventOverFunc);
			});
		}
	}
}

//=============================================================================
// 描画
//=============================================================================
void NewTownEvent_Space::Draw()
{
	// まだ初期化していない
	if (!Initialized)
		return;

	PlanetModel->Draw();
}

//=============================================================================
// イベントメッセージを取得
//=============================================================================
string NewTownEvent_Space::GetEventMessage(int FieldLevel)
{
	// ヌル
	return "";
}

//=============================================================================
// 惑星落下開始
//=============================================================================
void NewTownEvent_Space::FallenStart(void)
{
	EventState = PlanetDebut;

	// 惑星落下エフェクト
	GameParticleManager::Instance()->SetPlanetFallEffect(StartPos, &MoveTailEmitter, &StarDustEmitter);
	//GameParticleManager::Instance()->SetSingularityEffect(TownPos);
}

////=============================================================================
//// イベント終了処理
////=============================================================================
//void NewTownEvent_Space::EventOver(void)
//{
//	// イベント終了、ゲーム続行
//	CameraTranslationPlugin::Instance()->Restore(30, nullptr);
//	fieldEventHandler->ResumeGame();
//	UseFlag = false;
//}