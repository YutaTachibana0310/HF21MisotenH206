//=====================================
//
//GameInit.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "GameInit.h"
#include "../../../Framework/Renderer3D/SkyBox.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Field/FieldController.h"

/**************************************
入場処理
***************************************/
void GameScene::GameInit::OnStart(GameScene & entity)
{
	//スカイボックスのテクスチャをロード
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_up.png", SkyBox::Surface::Up);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_back.png", SkyBox::Surface::Back);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_down.jpg", SkyBox::Surface::Down);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_front.png", SkyBox::Surface::Front);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_left.png", SkyBox::Surface::Left);
	entity.skybox->LoadTexture("data/TEXTURE/Skybox/Sunny_01A_right.png", SkyBox::Surface::Right);

	//カメラの追従目標にカーソルを設定してモード切替
	FieldCamera *fieldCamera = dynamic_cast<FieldCamera*>(entity.sceneCamera);
	fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	fieldCamera->ChangeMode();
}

/**************************************
更新処理
***************************************/
GameScene::State GameScene::GameInit::OnUpdate(GameScene & entity)
{
	return GameScene::State::Idle;
}
