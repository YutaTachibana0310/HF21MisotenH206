//=====================================
//
//GameMain.cpp
//�@�\:�Q�[�����C������
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "GameMain.h"
#include "../Framework/Core/SceneManager.h"
#include "GameConfig.h"

#include "Scene\GameScene.h"

/**************************************
�R���X�g���N�^
***************************************/
GameMain::GameMain(HINSTANCE hInstance, HWND hWnd) :
	BaseGame(hInstance, hWnd)
{
	//�V�[���}�l�[�W���ɃV�[���̃C���X�^���X��ǉ�
	sceneManager->Add(GameConfig::SceneID::Game, new GameScene());

	//�����V�[���ɑJ��
	const int InitScene = GameConfig::SceneID::Game;
	sceneManager->ChangeScene(InitScene);
}