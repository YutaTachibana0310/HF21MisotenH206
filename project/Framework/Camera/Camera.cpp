//=====================================
//
//�J��������[Camera.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "Camera.h"
#include "CameraShakePlugin.h"

/**************************************
static�����o
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
Camera::Camera()
{
	pluginList.push_back(ShakePlugin::Instance());
}

/**************************************
����������
***************************************/
void Camera::Init()
{
	//TODO:Camera�ŏ���������̂ł͂Ȃ��v���O�C�����쐬����
	const float CameraAngleXZ = D3DXToRadian(45.0f);
	const float CameraAngleY = D3DXToRadian(60.0f);
	const float CameraLength = 50.0f;

	const D3DXVECTOR3 InitPos = D3DXVECTOR3(
		cosf(CameraAngleY) * cosf(CameraAngleXZ),
		sinf(CameraAngleY),
		cosf(CameraAngleY) * -sinf(CameraAngleXZ)) * CameraLength;

	const D3DXVECTOR3 InitTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	const float InitViewAngle = D3DXToRadian(60.0f);
	const float InitViewAspect = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;
	const float InitViewNear = 10.0f;
	const float InitViewFar = 50000.0f;

	transform.SetPosition(InitPos);
	target = InitTarget;
	viewAngle = InitViewAngle;
	viewAspect = InitViewAspect;
	viewNear = InitViewNear;
	viewFar = InitViewFar;

	D3DXMatrixIdentity(&viewport);
	viewport._11 = SCREEN_WIDTH / 2.0f;
	viewport._22 = -SCREEN_HEIGHT / 2.0f;
	viewport._41 = SCREEN_WIDTH / 2.0f;
	viewport._42 = SCREEN_HEIGHT / 2.0f;

	D3DXMatrixInverse(&invVPV, NULL, &VPV);

	Set();
}

/**************************************
�Z�b�g����
***************************************/
void Camera::Set()
{
	//��Ɨ̈�Ɍ��݂̃p�����[�^��ݒ�
	eyeWork = transform.GetPosition();
	targetWork = target;
	upWork = transform.Up();

	//�v���O�C�����f
	for (auto& plugin : pluginList)
	{
		plugin->Apply(*this);
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�r���[�s��쐬
	D3DXMatrixIdentity(&view);
	D3DXMatrixLookAtLH(&view,
		&eyeWork,
		&targetWork,
		&upWork);

	//�r���[�s��ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &view);

	//�v���W�F�N�V�����s��쐬
	D3DXMatrixIdentity(&projection);
	D3DXMatrixPerspectiveFovLH(&projection,
		viewAngle,
		viewAspect,
		viewNear,
		viewFar);

	//�v���W�F�N�V�����s��ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &projection);

	//�ϊ��s����v�Z
	VPV = view * projection * viewport;

	//�t�s����v�Z
	D3DXMatrixInverse(&invView, NULL, &view);
	D3DXMatrixInverse(&invProjection, NULL, &projection);
	D3DXMatrixInverse(&invVPV, NULL, &VPV);
}

/**************************************
�X�V����
***************************************/
void Camera::Update()
{
	//�e�v���O�C���X�V
	for (auto& plugin : pluginList)
	{
		plugin->Update();
	}
}

/**************************************
�X�N���[�����e����
***************************************/
void Camera::Projection(D3DXVECTOR3& out, const D3DXVECTOR3& pos)
{
	D3DXVec3TransformCoord(&out, &pos, &mInstance->VPV);
}

/**************************************
�X�N���[���t���e����
***************************************/
void Camera::UnProjection(D3DXVECTOR3& out, const D3DXVECTOR3& pos, float z)
{
	D3DXVec3TransformCoord(&out, &D3DXVECTOR3(pos.x, pos.y, z), &mInstance->invVPV);
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetViewMtx()
{
	return mInstance->view;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetInverseViewMtx()
{
	return mInstance->invView;
}

/**************************************
�X�N���[���t���e����
***************************************/
D3DXMATRIX Camera::GetProjectionMtx()
{
	return mInstance->projection;
}
