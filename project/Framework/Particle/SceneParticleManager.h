//=====================================
//
//�V�[���p�[�e�B�N���}�l�[�W���w�b�_[SceneParticleManager.h]
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCENEPARTICLEMANAGER_H_
#define _SCENEPARTICLEMANAGER_H_

#include "../../main.h"
#include "../PostEffect/ScreenObject.h"
#include "BaseParticleController.h"
#include <vector>

/**************************************
�}�N����`
***************************************/

/**************************************
�N���X��`
***************************************/
class SceneParticleManager
{
public:
	SceneParticleManager();

	//�������A�I���A�X�V�A�`�揈��
	virtual void Init() = 0;
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	//�p�[�e�B�N����������
	virtual BaseEmitter* Generate(UINT id, const D3DXVECTOR3& pos);
	virtual BaseEmitter* Generate(UINT id, const Transform& transform);

protected:
	//�����_�[�^�[�Q�b�g�֘A
	LPDIRECT3DTEXTURE9 renderTexture;
	LPDIRECT3DSURFACE9 renderSurface;
	D3DVIEWPORT9 viewPort;
	ScreenObject *screenObj;

	//�L���b�V���p
	LPDIRECT3DSURFACE9 oldSuf;
	D3DVIEWPORT9 oldViewport;

	//�p�[�e�B�N���R���g���[���R���e�i
	std::vector<BaseParticleController*> controllers;

	//�`�揀��
	void CreateRenderTarget(void);
	void ChangeRenderParameter(void);
	void RestoreRenderParameter(void);

private:
	bool initialized;
};
#endif