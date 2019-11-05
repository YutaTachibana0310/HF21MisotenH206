//=====================================
//
// �����N�C���t�H�A�N�^�[[LinkInfoActor.h]
// �@�\�F�����N���x���\��
// Author:GP12B332 19 ���J���u
//
//=====================================
#include "LinkInfoActor.h"
#include "../../../Framework/Resource/ResourceManager.h"

//**************************************
// �X�^�e�B�b�N�����o������
//**************************************
const D3DXVECTOR3 LinkInfoActor::digitPos[] =
{ D3DXVECTOR3(160.0f, 160.0f, 0.0f),
D3DXVECTOR3(96.0f, 160.0f, 0.0f) };
const D3DXVECTOR3 LinkInfoActor::logoPos = D3DXVECTOR3(128.8f, 80.0f, 0.0f);
const D3DXVECTOR2 LinkInfoActor::logoSize = D3DXVECTOR2(100.0f, 100.0f);
const D3DXVECTOR3 LinkInfoActor::upPos = D3DXVECTOR3(-3.0f ,20.0f, 3.0f);

//=====================================
// �R���X�g���N�^
//=====================================
LinkInfoActor::LinkInfoActor(const D3DXVECTOR3& townPos, const int& townLevel):
	InfoActor(townPos + upPos), linkLevel(townLevel)
{
	// ���S�\��
	logo = new Polygon2D();
	logo->SetPosition(logoPos);
	logo->LoadTexture("data/TEXTURE/Logo/Logo.png");
	logo->SetSize(logoSize.x, logoSize.y);
	logo->SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	logo->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	// ���x���\��
	linkLevel = Math::Clamp(0, 99, linkLevel);
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i] = new InfoDigit(digit[i], digitPos[i]);
	}

}

//=====================================
// �f�X�g���N�^
//=====================================
LinkInfoActor::~LinkInfoActor()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		SAFE_DELETE(digitActor[i]);
	}

	SAFE_DELETE(logo);
}

//=====================================
// �X�V
//=====================================
void LinkInfoActor::Update()
{
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->Update();
	}
}

//=====================================
// �`��
//=====================================
void LinkInfoActor::Draw()
{
	if (!this->IsActive())
		return;

	// ���ƂŃR���g���[���Ɉړ�
	LPDIRECT3DDEVICE9 device = GetDevice();
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	viewer->Begin2D();
	logo->Draw();
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->Draw();
	}
	viewer->End2D();

	viewer->Draw3D();

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

}

//=====================================
// ���x���ύX���g�p
//=====================================
void LinkInfoActor::SetLevel(const int& nextLevel)
{
	linkLevel = nextLevel;
	digit[0] = linkLevel % 10;
	digit[1] = linkLevel / 10;
	for (int i = 0; i < MaxDigit; i++)
	{
		digitActor[i]->ChangeDigit(digit[i]);
	}
}