//=====================================
//
// TestParticleManager.h
// �@�\:�Q�[���V�[���̃p�[�e�B�N���}�l�[�W��
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TESTPARTICLEMANAGER_H_
#define _TESTPARTICLEMANAGER_H_

#include "../../main.h"
#include "../../Framework/Particle/SceneParticleManager.h"
#include "../../Framework/Pattern/BaseSingleton.h"

/**************************************
�p�[�e�B�N���ʂ��ԍ�
***************************************/
namespace TestParticle
{
	enum ID
	{
		BlueSpark,
		BlueDebris,
		Max
	};
}

/**************************************
�N���X��`
***************************************/
class TestParticleManager : public SceneParticleManager, public BaseSingleton<TestParticleManager>
{
	using SceneParticleManager::SceneParticleManager;
public:
	void Init() override;
	void Update() override;
	void Draw() override;
};

#endif