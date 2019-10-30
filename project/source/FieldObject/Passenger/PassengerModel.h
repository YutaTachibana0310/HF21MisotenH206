//=====================================
//
// �p�b�Z���W���[���f��[PassengerModel.h]
// �@�\�F�p�b�Z���W���[�̃��f���N���X
// Author:GP12B332 19 ���J���u
//
//=====================================
#ifndef _PASSENGERMODEL_H_
#define _PASSENGERMODEL_H_

#include <vector>
#include "PassengerActor.h"

//**************************************
// �N���X��`
//**************************************
class PassengerModel
{
private:
	PassengerActor* actor;
	std::vector<D3DXVECTOR3> root;					// �o���n�_����ړI�n�܂ł̍��W���i�[
	int nextDest;									// root�̓Y���Ƃ��Ďg�p

	void CheckCallback();							// �R�[���o�b�N�̊m�F

public:
	PassengerModel(const std::vector<D3DXVECTOR3>& root);
	~PassengerModel();

	// �X�V�A�`��
	void Update();
	void Draw();

	// �g�p���m�F
	bool IsActive();

	// �A�N�^�[�̃Z�b�g
	void SetActor(const std::vector<D3DXVECTOR3>& root);
};

#endif