//=====================================
//
// ゲームリザルト[GameResult.cpp]
// 機能：リザルト状態
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "GameResult.h"
#include "../../Field/FieldController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Viewer/GameScene/Controller/ResultViewer.h"
#include "../../Viewer/GameScene/Controller/NameEntryViewer.h"
#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Network/UDPClient.h"
#include "../../../Framework/Task/TaskManager.h"

#include "../../Field/FieldController.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

//=====================================
// 入場処理
//=====================================
void GameScene::GameResult::OnStart(GameScene & entity)
{
	entity.step = 0;

	// 最下位のスコアを取得
	//entity.Client->GetLastScore();

	//スコア表示、名前入力などなど
	// カメラのモード切り替え
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::Arround);

	// リザルト画面で使用するUIの描画をON(ネームエントリーは最初はオフ）
	entity.resultViewer->SetActive(true);
	entity.resultViewer->SlideScoreViewer(true);
	entity.resultViewer->SetAchieveViewerActive(false);

	// 使用しないUIの描画をOFF
	entity.field->SetViewerActive(false);
	entity.gameViewer->SetActive(false);
	entity.nemeEntryViewer->SetActive(false);
	GuideViewer::Instance()->SetActive(false);
	//entity.guideViewer->SetActive(false);

	//宇宙レベルのスコアを保存
	if (level == 2)
	{
		entity.field->SetScore();
	}

	// リザルト用のUIにAI発展レベルを渡す
	int cityScore = (int)entity.field->GetScore(Field::FieldLevel::City);
	int worldScore = (int)entity.field->GetScore(Field::FieldLevel::World);
	int spaceScore = (int)entity.field->GetScore(Field::FieldLevel::Space);
	entity.resultViewer->ReceiveParam(cityScore, worldScore, spaceScore);

	SE::Play(SoundConfig::SEID::Finish, 1.0f);
	PlayBGM::Instance()->FadeIn(SoundConfig::BGMID::Result, 0.1f, 30);

	//全体スコアを計算
	entity.entiretyScore = (int)(powf(10, 8) * spaceScore) + (int)(powf(10, 4) * worldScore) + cityScore;
}

//=====================================
// 更新処理
//=====================================
GameScene::State GameScene::GameResult::OnUpdate(GameScene & entity)
{
	// クライアント更新
	entity.Client->Update();

	//ロジック以外を更新
	entity.field->UpdateObject();

	switch (entity.step)
	{
		//TransitionController::Instance()->SetTransition(false, TransitionType::HexaPop, [&]()
	case Step::ScoreViewerIn:
		if (entity.resultViewer->IsPlayingAnimation() != ResultViewer::PlayingIn)
		{
			entity.step = Step::ScoreInputWait;
		}
		break;

	case Step::ScoreInputWait:
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			//ランキング更新があったらネームエントリーへ
			long long lastScore = entity.Client->GetLastScore();
			if (entity.entiretyScore > lastScore)
			{
				entity.nemeEntryViewer->SetActive(true);
				entity.step = Step::ScoreNameEntryWait;
			}
			//それ以外は達成実績表示へ遷移
			else
			{
				entity.step = Step::ScoreNameEntryFinish;
			}
		}
		break;

	case Step::ScoreNameEntryWait:
		//TODO:ネームエントリーの終了をコールバックで受け取るようにする
		entity.step = Step::ScoreNameEntryFinish;
		break;

	case Step::ScoreNameEntryFinish:
		//エンターキーが押されたらスコアビューワをスライドアウトさせる
		if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
		{
			entity.resultViewer->SlideScoreViewer(false);
			entity.nemeEntryViewer->SetActive(false);
			entity.step = Step::ScoreViewerOut;
		}
		break;

	case Step::ScoreViewerOut:
		if (entity.resultViewer->IsPlayingAnimation() != ResultViewer::PlayingOut)
		{
			entity.ChangeState(State::AchieveResult);
		}
		break;

	default:

		break;
	}


	return State::Result;
}
