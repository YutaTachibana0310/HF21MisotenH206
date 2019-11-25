//=====================================
//
//GameLevelUp.cpp
//機能:ゲームシーンレベルアップステート
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameLevelUp.h"
#include "../../Field/FieldController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameLevelUp::OnStart(GameScene & entity)
{
	//TODO:レベルアップ時の演出を再生する
	// スコアの加算
	entity.field->SetScore();
	//本来は演出終了のコールバックで遷移させる

	//レベルアップ処理
	entity.OnLevelUp();

	entity.ChangeState(GameScene::State::TransitionOut);
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameLevelUp::OnUpdate(GameScene & entity)
{
	return State::LevelUp;
}
