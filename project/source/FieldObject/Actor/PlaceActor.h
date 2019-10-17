//=====================================
//
// プレイスアクター[PlaceActor.h]
// 機能：フィールド上に設置される3Dオブジェクト用の基底クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _PLACEACTOR_H_
#define _PLACEACTOR_H_

#include "../../../Framework/Core/GameObject.h"
#include "../../../Framework/Math/Easing.h"
#include "../../../Framework/Renderer3D/MeshContainer.h"
#include "../../Field/Place/PlaceConfig.h"

//**************************************
// マクロ定義
//**************************************

//**************************************
// 列挙子設定
//**************************************
namespace FModel = Field::Model;

//**************************************
// クラス定義
//**************************************
class PlaceActor :
	public GameObject
{
public:
	PlaceActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel);
	virtual ~PlaceActor();

	virtual void Update();
	virtual void Draw();

	// インターフェース
	void Rotate(float y);								// Y軸回転
	void SetColor(const D3DXCOLOR& color, UINT index);	// メッシュの色変更

protected:
	// ***継承先のクラスで読み込み***
	MeshContainer* mesh;				// メッシュコンテナ
	FModel::PlaceType type;				// アクターの種類
	// ******************************

private:
	static const D3DXVECTOR3 ActorScale;

#if _DEBUG
	void Debug();
#endif
};

#endif
