//=====================================
//
//StarRoad.h
//�@�\:���̓��p�[�e�B�N��
//Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _STARROAD_H_
#define _STARROAD_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/3D/Particle3D.h"
#include "../../../../Framework/Particle/BaseParticleController.h"

namespace Effect::Game
{
	/**************************************
	StarRoadController�N���X
	***************************************/
	class StarRoadController : public BaseParticleController
	{
	public:
		StarRoadController();
	};

	/**************************************
	StarRoad�N���X
	***************************************/
	class StarRoad : public Particle3D
	{
	public:
		StarRoad();

		void Init();
		void Update();

		void Toward(const D3DXVECTOR3& direction);

	private:
		static const float RangeX;
		static const float RangeY;
		static const float MaxRangeZ;
		static const float MinRangeZ;

		D3DXVECTOR3 direction;
	};

	/**************************************
	StarRoadEmitter�N���X
	***************************************/
	class StarRoadEmitter : public BaseEmitter
	{
	public:
		StarRoadEmitter();

		bool Emit(std::vector<BaseParticle*>& container) override;
		bool IsActive() const override;
	};
}

#endif