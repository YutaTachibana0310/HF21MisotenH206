//=====================================
//
//GameScene.cpp
//機能:ゲームシーン
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameScene.h"
#include "../../Framework/Tool/DebugWindow.h"

#include "../../Framework/Renderer3D/SkyBox.h"
#include "../FieldObject/PlaceActor.h"
#include "../../Framework/Resource/ResourceManager.h"
#include "../Field/FieldController.h"

#include "GameState/GameInit.h"
#include "GameState/GameIdle.h"

/**************************************
初期化処理
***************************************/
void GameScene::Init()
{
	// 3Dオブジェクトのリソースをロード
	ResourceManager::Instance()->LoadMesh("Model", "data/MODEL/PlaceActor/Cross-Junction.x");

	//各インスタンス作成
	skybox = new SkyBox(D3DXVECTOR3(20000.0f, 20000.0f, 20000.0f));
	field = new FieldController();

	//ステートマシン作成
	fsm.resize(State::Max, NULL);
	fsm[State::Initialize] = new GameInit();
	fsm[State::Idle] = new GameIdle();

	//ステート初期化
	ChangeState(State::Initialize);
}

/**************************************
終了処理
***************************************/
void GameScene::Uninit()
{
	//インスタンス削除
	SAFE_DELETE(skybox);
	SAFE_DELETE(field);

	//ステートマシン削除
	Utility::DeleteContainer(fsm);
}

/**************************************
更新処理
***************************************/
void GameScene::Update()
{
	State next = fsm[currentState]->OnUpdate(*this);

	if (next != currentState)
	{
		ChangeState(next);
	}
}

/**************************************
描画処理
***************************************/
void GameScene::Draw()
{
	//背景描画
	skybox->Draw();

	//オブジェクト描画
	field->Draw();
}

/**************************************
ステート遷移処理
***************************************/
void GameScene::ChangeState(State next)
{
	prevState = currentState;

	currentState = next;

	if (fsm[currentState] != NULL)
	{
		fsm[currentState]->OnStart(*this);
	}
}
