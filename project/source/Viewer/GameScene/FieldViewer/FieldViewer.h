//=============================================================================
//
// Field�r���A�[�Ǘ����� [FieldViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _FIELD_VIEWER_H_
#define _FIELD_VIEWER_H_

#include <vector>
#include "FieldTelop.h"
#include "FieldErrorMessage.h"
#include "OperationExplanationViewer.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class FieldTelop;
class FieldErrorMessage;
class OperationExplanationViewer;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class FieldViewer
{
public:
	FieldViewer();
	~FieldViewer();

	void Update(void);
	void Draw(void);

	//�t�B�[���h�e���b�v���Z�b�g�i�������Ŏ������j
	void SetFieldTelop(FieldTelop::TelopID id, std::function<void(void)> Callback);

	//�t�B�[���h�G���[���b�Z�[�W���Z�b�g
	void SetFieldErroMessage(FieldErrorMessage::ErroID id);

	//��������r���[�A���Z�b�g
	void SetOperationExplanation(
		//Z�L�[�̑���ɕ\���������ID
		OperationExplanationViewer::OperationID id0, 
		//X�L�[�̑���ɕ\���������ID
		OperationExplanationViewer::OperationID id1, 
		//Space�L�[�̑���ɕ\���������ID
		OperationExplanationViewer::OperationID id2);

	std::vector <BaseViewer*> fieldViewer;

private:
	FieldTelop * fieldTelop;
	FieldErrorMessage * fieldErroMessage;
	OperationExplanationViewer *operationExplanation;
};

#endif
