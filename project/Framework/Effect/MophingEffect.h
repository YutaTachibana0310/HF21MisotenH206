//=====================================
//
//MophingEffect.h
//機能:モーフィング用エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _MOPHINGEFFECT_H_
#define _MOPHINGEFFECT_H_

#include "../../main.h"
#include "RendererEffect.h"

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class MophingEffect : public RendererEffect
{
public:
	//コンストラクタ、デストラクタ
	MophingEffect();
	~MophingEffect();

	void SetTime(float t);

private:
	//シェーダへのハンドル
	D3DXHANDLE hTechnique;
	D3DXHANDLE hTime;
};
#endif