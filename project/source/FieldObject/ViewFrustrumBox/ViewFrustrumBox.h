//=====================================
//
// ビューフラストラムボックス[ViewFrustrumBox.h]
// 機能：視錐台カリング用ボックス
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _VIEWFRUSTRUMBOX_H_
#define _VIEWFRUSTRUMBOX_H_

#include "../../../main.h"

//**************************************
// クラス定義
//**************************************
class ViewFrustrumBox
{
public:
	enum Point
	{
		UpLeftFar,
		UpRightFar,
		UpLeftNear,
		UpRightNear,
		DownLeftFar,
		DownRightFar,
		DownLeftNear,
		DownRightNear,
		Max
	};

	ViewFrustrumBox(const D3DXVECTOR3 pos, float size);
	~ViewFrustrumBox();

	// 対象に最も近い、遠い座標を取得する
	D3DXVECTOR3 SearchNearPoint(const D3DXVECTOR3 target);
	D3DXVECTOR3 SearchFarPoint(const D3DXVECTOR3 target);

	static const float PlaceActorSize;
	static const float PassengerActorSize;

private:
	D3DXVECTOR3 pos;				// 基準座標
	D3DXVECTOR3 point[Point::Max];	// 8頂点
};

#endif
