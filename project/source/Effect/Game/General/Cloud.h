//=====================================
//
//Cloud.h
//機能:雲パーティクル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _CLOUDY_H_
#define _CLOUDY_H_

#include "../../../../main.h"
#include "../../../../Framework/Particle/BaseParticleController.h"
#include "../../../../Framework/Particle/2D/Particle2D.h"

namespace Effect::Game
{
	/**************************************
	CloudControllerクラス
	***************************************/
	class CloudController : public BaseParticleController
	{
	public:
		CloudController();
	};

	/**************************************
	Cloudクラス
	***************************************/
	class Cloud : public Particle2D
	{
	public:
		Cloud();

		void Init() override;
		void Update() override;

		void SetDirection(bool isDown);

		static const float MinSpeed;
		static const float MaxSpeed;
		static const float MinPositionX;
		static const float MaxPositionX;
		static const float MinPositionY;
		static const float MaxPositionY;

	private:
		D3DXVECTOR3 velocity;
		float initScale;
	};

	/**************************************
	CloudEmitterクラス
	***************************************/
	class CloudEmitter : public BaseEmitter
	{
	public:
		CloudEmitter();

		bool Emit() override;
	};
}

#endif