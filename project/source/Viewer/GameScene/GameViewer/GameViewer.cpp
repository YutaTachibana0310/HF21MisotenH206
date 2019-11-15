//=============================================================================
//
// Gameビュアー管理処理 [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "ItemStockViewer.h"
#include "TimerViewer.h"
#include "LevelViewer.h"
#include "GameViewerParam.h"
#include "GameViewer.h"

#ifdef _DEBUG
#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"
#endif

////////////////テスト///////////
#include "../BeatGameViewer/BeatGameViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new ItemStockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());

	//テスト
	beatGameViewer = new BeatGameViewer();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameViewer::~GameViewer()
{
	//メモリを解放
	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		SAFE_DELETE(gameViewer[i]);
	}

	//インスタンスを入れた配列をクリア
	gameViewer.clear();

	////テスト/////
	SAFE_DELETE(beatGameViewer);
}

//=============================================================================
// 更新処理
//=============================================================================
void GameViewer::Update()
{
	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Update();
	}

	////テスト
	beatGameViewer->Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void GameViewer::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);

	for (unsigned int i = 0; i < gameViewer.size(); i++)
	{
		gameViewer[i]->Draw();
	}

	/////teat
	beatGameViewer->Draw();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// パラメータ受け取り処理
//=============================================================================
void GameViewer::ReceiveParam(GameViewerParam &param)
{
	//ストックビュアー
	stockViewer->parameterBox = param.stockNum;

	//タイマービュアー
	timerViewer->parameterBox = param.remainTime;

	//AIレベルビュアー
	levelViewer->parameterBox[levelViewer->LevelAI] = (float)param.levelAI;
	levelViewer->parameterBox[levelViewer->RatioLevel] = param.ratioLevel;
}
