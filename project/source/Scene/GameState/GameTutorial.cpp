//=============================================================================
//
// �`���[�g���A���N���X [GameTutorial.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "GameTutorial.h"
#include "../../Field/FieldController.h"
#include "../../Field/Camera/FieldCamera.h"
#include "../../Event/EventController.h"
#include "../../Viewer/GameScene/Controller/GameViewer.h"
#include "../../Viewer/GameScene/GuideViewer/GuideViewer.h"
#include "../../Viewer/TitleScene/TitleViewer.h"
#include "../../Viewer/TutorialScene/TutorialViewer.h"
#include "../../Reward/RewardController.h"
#include "../../Sound/PlayBGM.h"
#include "../../Sound/SoundConfig.h"

#include "../../../Framework/Input/input.h"
#include "../../../Framework/Transition/TransitionController.h"
#include "../../../Framework/Task/TaskManager.h"

enum TutorialStep
{
	Road,
	Stock,
	Camera,
	Event,
	Score,
	Exit,
	WaitOver,
	Transition,
};

/**************************************
���ꏈ��
***************************************/
void GameScene::GameTutorial::OnStart(GameScene & entity)
{
	// �J�����̏œ_���Z�b�g
	entity.fieldCamera->SetFollowTarget(entity.field->GetFieldCursor());
	entity.fieldCamera->ChangeMode(FieldCamera::Mode::QuaterView);

	// �Q�[���V�[���Ŏg�p����UI�̕`���ON
	entity.field->SetViewerActive(true);
	entity.gameViewer->SetActive(true);
	GuideViewer::Instance()->SetActive(true);

	entity.remainTime = 30 * 999;
}

/**************************************
������
***************************************/
void GameScene::GameTutorial::Init(GameScene& entity)
{
	entity.step = Road;
	entity.tutorialViewer->Init();
	FrameCount = 0;
	ClearFlag = false;
}

/**************************************
�X�V����
***************************************/
GameScene::State GameScene::GameTutorial::OnUpdate(GameScene & entity)
{
	switch (entity.step)
	{
	case TutorialStep::Road:

		FrameCount++;

		// ������\������
		if (FrameCount == 15)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::LinkRoad);
		}

		// ������鑀����m�F
		if (entity.field->GetRoadNum() != 0 && !entity.tutorialViewer->GetIsShowTexture())
		{
			ClearFlag = true;
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Stock;
		}

		break;

	case TutorialStep::Stock:

		FrameCount++;

		// ������\������
		if (FrameCount == 120)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::Develop);
		}

		// �J�񑀍���m�F
		if (entity.field->IsDeveloped() && !entity.tutorialViewer->GetIsShowTexture())
		{
			ClearFlag = true;
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Camera;
		}
		break;

	case TutorialStep::Camera:

		FrameCount++;

		// ������\������
		if (FrameCount == 60)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::ChangeCamera);
		}

		// �J�����̑�����m�F
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			if (Keyboard::GetTrigger(DIK_C) || Keyboard::GetTrigger(DIK_SPACE) ||
				GamePad::GetTrigger(0, BUTTON_A) || GamePad::GetTrigger(0, BUTTON_Z))
			{
				ClearFlag = true;
			}
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Event;
		}
		break;

	case TutorialStep::Event:

		FrameCount++;

		// ������\������
		if (FrameCount == 60)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::EventHappend);
		}

		// �C�x���g�̔������m�F
		if (!entity.eventController->IsEmptyEventVec() ||
			(FrameCount >= 600 && !entity.tutorialViewer->GetIsShowTexture()))
		{
			ClearFlag = true;
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Score;
		}
		break;

	case TutorialStep::Score:

		FrameCount++;

		// ������\������
		if (FrameCount == 120)
		{
			entity.tutorialViewer->ShowTutorial(TutorialViewer::HelpTextureType::HighScore);
			ClearFlag = true;
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			FrameCount = 0;
			ClearFlag = false;
			entity.step = TutorialStep::Exit;
		}

		break;

	case TutorialStep::Exit:

		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			ClearFlag = true;
		}

		// �����B���A���̐����ɍs��
		if (ClearFlag)
		{
			ClearFlag = false;
			entity.step = TutorialStep::WaitOver;
		}

		break;
	case TutorialStep::WaitOver:

		// �`���[�g���A���I��
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			if (Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_Y))
			{
				entity.tutorialViewer->SetActive(false);
				entity.step = Transition;

				// ������
				entity.level = 0;
				entity.InTutorial = false;
				entity.remainTime = 30 * 180;

				// �g�����W�V����
				entity.ChangeState(GameScene::State::TransitionOut);
			}
		}
		break;

	default:
		break;
	}

	// �`���[�g���A�����Ɏ��т�B�����Ȃ����߂�
	RewardController::Instance()->ResetAllRewardData();

	if (entity.step != TutorialStep::Transition)
	{
		// ����������\�����Ă��Ȃ���΁A���͊m�F
		if (!entity.tutorialViewer->GetIsShowTexture())
		{
			// �C�x���g�X�V
			entity.eventController->Update();
			entity.eventController->UpdateViewer();

			entity.field->CheckInput();

			// �t�B�[���h�X�V
			entity.field->UpdateLogic();
			entity.field->UpdateObject();

			entity.tutorialViewer->SetHelpMessage();

			// ���i���[�h�ւ̑J�ڊm�F
			if (entity.field->ShouldSwicthCamera())
			{
				entity.ChangeState(State::FarView);
			}
			// �J��������]�����邩
			else if (entity.field->ShouldRotateCamera())
			{
				entity.fieldCamera->ChangeMode(FieldCamera::AngleRotate);
			}

			if (Keyboard::GetTrigger(DIK_V) || GamePad::GetTrigger(0, BUTTON_R))
			{
				entity.ChangeState(GameScene::State::Interrupt);
			}
		}
		else if (entity.step != TutorialStep::WaitOver)
		{
			// �����I��
			if (Keyboard::GetTrigger(DIK_Z) || Keyboard::GetTrigger(DIK_RETURN) || GamePad::GetTrigger(0, BUTTON_C))
			{
				GuideViewer::Instance()->SetActive(true);
				entity.tutorialViewer->SetIsShowTexture(false);
			}
		}
	}

	return State::Tutorial;
}