//=====================================
//
//FieldController.cpp
//�@�\:�t�B�[���h�R���g���[��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#include "FieldController.h"
#include "FieldCursor.h"
#include "FieldGround.h"
#include "Place\FieldPlaceContainer.h"
#include "Place\OperatePlaceContainer.h"
#include "Place\FieldPlaceModel.h"
#include "Route\RouteModel.h"
#include "Route\RouteProcessor.h"

#include "State/BuildRoad.h"
#include "State/FieldControllerIdle.h"
#include "State/UseItem.h"

#include "../../Framework/Input/input.h"
#include "../../Framework/Tool/DebugWindow.h"

#include <algorithm>

namespace Field
{
	/**************************************
	static�����o
	***************************************/
	const float FieldController::PlaceOffset = 10.0f;				//Place��1�}�X���̃I�t�Z�b�g�l
	const int FieldController::InitFieldBorder = 30;				//�t�B�[���h�͈͂̏����l
	const int FieldController::InputLongWait = 15;					//���̓��s�[�g�̑ҋ@�t���[��
	const int FieldController::InputShortWait = 5;					//���̓��s�[�g�̑ҋ@�t���[��
	const unsigned FieldController::InitDevelopRiverStock = 10;		//��J���X�g�b�N�̏�����
	const unsigned FieldController::InitDevelopMountainStock = 10;	//�R�J���X�g�b�N�̏�����

	/**************************************
	�R���X�g���N�^
	***************************************/
	FieldController::FieldController() :
		fieldBorder(InitFieldBorder),
		inputRepeatCnt(0),
		stockDevelopRiver(InitDevelopRiverStock),
		stockDevelopMountain(InitDevelopMountainStock)
	{
		//�C���X�^���X�쐬
		cursor = new FieldCursor(PlaceOffset);
		ground = new FieldGround();
		placeContainer = new Model::PlaceContainer();
		operateContainer = new Model::OperatePlaceContainer();

		//�X�e�[�g�}�V���쐬
		fsm.resize(State::Max, NULL);
		fsm[State::Build] = new BuildRoadState();
		fsm[State::Idle] = new IdleState;
		fsm[State::Develop] = new UseItemState();

		//�X�e�[�g������
		ChangeState(State::Idle);
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	FieldController::~FieldController()
	{
		routeContainer.clear();

		SAFE_DELETE(cursor);
		SAFE_DELETE(ground);
		SAFE_DELETE(placeContainer);
		SAFE_DELETE(operateContainer);

		//�X�e�[�g�}�V���폜
		Utility::DeleteContainer(fsm);
	}

	/**************************************
	�X�V����
	***************************************/
	void FieldController::Update()
	{
		//�g��Ȃ��Ȃ������[�g�R���e�i���폜
		auto itr = std::remove_if(routeContainer.begin(), routeContainer.end(), [](auto& ptr)
		{
			return ptr->IsUnused();
		});
		routeContainer.erase(itr, routeContainer.end());

		//�e�X�V����
		cursor->Update();
		placeContainer->Update();

		for (auto&& route : routeContainer)
		{
			route->Update();
		}
	}

	/**************************************
	�`�揈��
	***************************************/
	void FieldController::Draw()
	{
		ground->Draw();

		placeContainer->Draw();

		operateContainer->DrawDebug();

		//�J�[�\���ɂ͓��߃I�u�W�F�N�g���܂܂��̂ōŌ�ɕ`��
		cursor->Draw();

		Debug::Log("ControllerState:%d", current);
		Debug::Log("StockRiver:%d", stockDevelopRiver);
		Debug::Log("StockMountain:%d", stockDevelopMountain);
	}

	/**************************************
	���͊m�F����
	TODO�F�ǂݍ��ރf�[�^��I���ł���悤�ɂ���
	***************************************/
	void FieldController::Load()
	{
		placeContainer->LoadCSV("data/FIELD/sample01.csv");

		//�J�[�\���̃t�B�[���h�̒����֐ݒ�
		FieldPosition border = placeContainer->GetPlaceBorder();
		cursor->SetModelPosition(border.x / 2, border.z / 2);

		//NOTE:���͂܂��ړ��͈͂̊g�又���������̂ł����ňړ��͈͂����肵�Ă��܂�
		cursor->SetBorder(border.z - 1, border.x - 1, 0, 0);
	}

	/**************************************
	���͊m�F����
	***************************************/
	void FieldController::CheckInput()
	{
		//�g���K�[�m�F
		float triggerX = 0.0f, triggerZ = 0.0f;

		triggerX = Input::GetTriggerHorizontal();
		triggerZ = Input::GetTriggerVertical();

		//���s�[�g�m�F
		float repeatX = 0.0f, repeatZ = 0.0f;
		if((Input::GetPressHorizontail() != 0.0f || Input::GetPressVertical() != 0.0f))
		{
			inputRepeatCnt++;
			if (inputRepeatCnt >= InputLongWait && inputRepeatCnt % InputShortWait == 0)
			{
				repeatX = Input::GetPressHorizontail();
				repeatZ = Input::GetPressVertical();
			}
		}
		else
		{
			inputRepeatCnt = 0;
		}

		//�J�[�\�����ړ�
		float x = Math::Clamp(-1.0f, 1.0f, triggerX + repeatX);
		float z = Math::Clamp(-1.0f, 1.0f, triggerZ + repeatZ);
		cursor->Move((int)x, (int)z);

		//���݂̃X�e�[�g�̍X�V���������s
		State next = state->OnUpdate(*this);
		if (next != current)
		{
			ChangeState(next);
		}
	}

	/**************************************
	�J�[�\���擾����
	***************************************/
	GameObject * FieldController::GetFieldCursor()
	{
		return cursor;
	}

	/**************************************
	�X�e�[�g�؂�ւ�����
	***************************************/
	void FieldController::ChangeState(State next)
	{
		if (fsm[next] == NULL)
			return;

		current = next;
		state = fsm[next];
		state->OnStart(*this);
	}

	/**************************************
	�J�[�\���ʒu�̃v���C�X���擾
	***************************************/
	Model::PlaceModel * FieldController::GetPlace()
	{
		return placeContainer->GetPlace(cursor->GetModelPosition());
	}

	/**************************************
	�������
	***************************************/
	void FieldController::BuildRoad()
	{
		using namespace Field::Model;

		//����Ώۂ̃v���C�X��Road�^�C�v�ɕϊ�
		std::vector<PlaceModel*> route = operateContainer->GetPlaces();
		for (auto&& place : route)
		{
			if (place->IsType(PlaceType::None))
				place->SetType(PlaceType::Road);
		}

		//���[�g���f���쐬
		RouteModelPtr ptr = RouteModel::Create(route);
		routeContainer.push_back(ptr);
	
		//�[�_�ݒ�
		ptr->SetEdge();

		//�I�u�W�F�N�g�ݒ�

		//�אڂ��郋�[�g�ƘA��������
		RouteProcessor::ConnectWithEdge(ptr, routeContainer);
		RouteProcessor::Process(ptr, routeContainer);
	}

	/**************************************
	��A�R���J������
	***************************************/
	void FieldController::DevelopPlace(PlaceVector& route, PlaceIterator start)
	{
		using namespace Field::Model;

		auto itr = std::find_if(start, route.end(), [](auto& place)
		{
			//��̊J�񏈗������Ă��Ȃ��̂ň�U�R�����g�A�E�g
			return place->IsType(PlaceType::Mountain) || place->IsType(PlaceType::River);
		});

		//�J��Ώۂ�������Ȃ��̂Ń��^�[��
		if (itr == route.end())
			return;

		//�R���J��
		if ((*itr)->IsType(PlaceType::Mountain))
		{
			itr = DevelopMountain(route, itr);
		}
		//����J��
		else if ((*itr)->IsType(PlaceType::River))
		{
			itr = DevelopRiver(route, itr);
		}

		//�J�񂪏I�������ʒu����ċA�I�ɊJ��
		DevelopPlace(route, itr);
	}

	/**************************************
	�R���J������
	***************************************/
	PlaceIterator FieldController::DevelopMountain(PlaceVector & route, PlaceIterator mountain)
	{
		using namespace Field::Model;

		//�Ώۂ̃v���C�X�̑O�ɂ���R,��ȊO�̃v���C�X��T��
		auto start = std::find_if(ReversePlaceIterator(mountain), route.rend(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ��������A��̏ꍇ�͑������^�[��
		if (start == route.rend() || (*(start + 1).base())->IsType(PlaceType::River))
		{
			return route.end();
		}

		//�Ώۂ̃v���C�X�̌��ɂ���R�A��ȊO�̃v���C�X��T��
		auto end = std::find_if(mountain, route.end(), [](auto& place)
		{
			return !place->IsType(PlaceType::Mountain);
		});

		//�R�ȊO��������Ȃ��������A��̏ꍇ�͑������^�[��
		if (end == route.end() || (*end)->IsType(PlaceType::River))
		{
			return route.end();
		}

		//start��end�����ԃv���C�X�̃R���e�i���쐬
		PlaceVector container;
		container.assign(start.base(), end);

		//�X�g�b�N������Ă���ΊJ��
		unsigned cntMountain = container.size();
		if (cntMountain <= stockDevelopMountain)
		{
			for (auto&& place : container)
			{
				place->SetType(PlaceType::None);
			}

			stockDevelopRiver -= cntMountain;
		}
		else
		{
			//�G���[���b�Z�[�W���Đ�
		}

		return end + 1;
	}

	/**************************************
	����J������
	***************************************/
	PlaceIterator FieldController::DevelopRiver(PlaceVector & route, PlaceIterator river)
	{
		using namespace Field::Model;

		//��̈�O�̃v���C�X�i�n�_�j���ǂ̕����ŗאڂ��Ă��邩�m�F
		PlaceModel* start = *(river - 1);
		Adjacency startAdjacency = (*river)->IsAdjacent(start);

		//�v���C�X��O�ֈ���m�F���Ă����I�_��T��
		PlaceIterator end = route.end();
		for (auto itr = river + 1; itr != route.end(); itr++)
		{
			PlaceModel* prev = *(itr - 1);
			PlaceModel* place = *itr;

			//�אڕ����������ɂȂ��Ă��Ȃ���Α������^�[��
			if (place->IsAdjacent(prev) != startAdjacency)
				return itr;

			//�J��\�ȊO�̃^�C�v�ł����break
			if (!place->IsDevelopableType())
			{
				end = itr;
				break;
			}
		}

		//�I�_��������Ȃ������̂ő������^�[��
		if(end == route.end())
			return route.end();

		//�n�_�ƏI�_�̊Ԃ̐�R���e�i���쐬
		PlaceVector riverVector;
		riverVector.assign(river, end);

		//�X�g�b�N������Ă���ΊJ��
		unsigned cntRiver = riverVector.size();
		if (cntRiver <= stockDevelopRiver)
		{
			Adjacency inverseStartAdjacency = GetInverseSide(startAdjacency);
			for (auto&& river : riverVector)
			{
				river->SetType(PlaceType::Bridge);
				river->SetDirection(startAdjacency, inverseStartAdjacency);
			}

			stockDevelopRiver -= cntRiver;
		}
		else
		{
			//�G���[���b�Z�[�W�̍Đ�
		}

		return end;
	}
}