//=============================================================================
//
// Gameビュアー管理処理 [GameViewer.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include "StockViewer.h"
#include "TimerViewer.h"
#include "LevelViewer.h"
#include "GameViewerParam.h"
#include "GameViewer.h"

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
GameViewer::GameViewer()
{
	gameViewer.push_back(stockViewer = new StockViewer());
	gameViewer.push_back(timerViewer = new TimerViewer());
	gameViewer.push_back(levelViewer = new LevelViewer());

	gameViewerMax = gameViewer.size();
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
GameViewer::~GameViewer()
{
	//インスタンスを入れた配列をクリア
	gameViewer.clear();
}

//=============================================================================
// 更新処理
//=============================================================================
void GameViewer::Update()
{
	for (int i = 0; i < gameViewerMax; i++)
	{
		gameViewer[i]->Update();
	}
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

	for (int i = 0; i < gameViewerMax; i++)
	{
		gameViewer[i]->Draw();
	}

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

//=============================================================================
// パラメータ受け取り処理
//=============================================================================
void GameViewer::ReceiveParam(GameViewerParam&param)
{
	//ストックビュアー
	stockViewer->parameterBox[stockViewer->Bridge] = param.stockBuildItem;
	stockViewer->parameterBox[stockViewer->Drill] = param.stockBreakItem;
	stockViewer->parameterBox[stockViewer->EDF] = param.stockEDF;
	stockViewer->parameterBox[stockViewer->Insurance] = param.stockInsurance;

	//タイマービュアー
	timerViewer->parameterBox = param.remainTime;

	//AIレベルビュアー
	levelViewer->parameterBox[levelViewer->LevelAI] = param.levelAI;
	levelViewer->parameterBox[levelViewer->RatioLevel] = param.ratioLevel;
}
