//=====================================
//
// タイトルビュアー[TitleViewer.h]
// 機能：タイトル画面UI表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

#include "../../../main.h"

class TitleLogo;
class SelectViewer;
class GameScene;
class RewardViewer;

//**************************************
// クラス定義
//**************************************
class TitleViewer
{
private:
	TitleLogo* logo;
	SelectViewer* selectViewer;
	RewardViewer* rewardViewer;

	bool isActive;

public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

	void SetActive(bool flag);

	bool CheckSceneChange();
	void SetNextScene(GameScene& entity);
	// セレクトロゴの表示が"ゲーム開始"に設定する
	void InitSelectLogo(void);
};

#endif
