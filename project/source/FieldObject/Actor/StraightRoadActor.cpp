//=====================================
//
// ストレートロードアクター[StraightRoadActor.cpp]
// 機能：まっすぐな道用3Dモデル表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "StraightRoadActor.h"
#include "../../../Framework/Resource/ResourceManager.h"
#include "State/CreateActorState.h"

//=====================================
// コンストラクタ
//=====================================
StraightRoadActor::StraightRoadActor(const D3DXVECTOR3& pos, FModel::FieldLevel currentLevel)
	: PlaceActor(pos, currentLevel)
{
	// モデルデータ参照
	switch (currentLevel)
	{
	case FModel::City:
		ResourceManager::Instance()->GetMesh("StraightRoad-City", mesh);
		break;
	case FModel::World:
		break;
	case FModel::Space:
		break;
	default:
		break;
	}

	type = FModel::River;

	// テスト
	state = new CreateActorState();
	state->OnStart(*this);

}

//=====================================
// デストラクタ
//=====================================
StraightRoadActor::~StraightRoadActor()
{
}
