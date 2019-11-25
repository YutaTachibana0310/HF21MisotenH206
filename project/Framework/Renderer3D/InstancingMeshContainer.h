//=====================================
//
// InstancingMeshContainer.h
// 機能:インスタンシング用メッシュコンテナ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _INSTANCINGMESHCONTAINER_H_
#define _INSTANCINGMESHCONTAINER_H_

#include "../../main.h"
#include "MeshContainer.h"

#include <vector>

/**************************************
前方宣言
***************************************/
class InstancingMeshEffect;

/**************************************
クラス定義
***************************************/
class InstancingMeshContainer : public MeshContainer
{
	friend class MeshResource;
public:
	//コンストラクタ、デストラクタ
	InstancingMeshContainer(unsigned MaxNum);
	~InstancingMeshContainer();

	//リソース読み込み後の初期化処理
	//必ずメッシュ情報を取得した後に呼ぶこと
	void Init();

	//描画処理
	void Draw();

	//頂点バッファロック、アンロック処理
	void Lock();
	void Unlock();

	//SRT情報埋め込み処理
	bool EmbedTranform(const Transform& transform);

protected:
	const unsigned MaxInstance;

	LPDIRECT3DVERTEXBUFFER9 vtxBuff;
	LPDIRECT3DINDEXBUFFER9 indexBuff;
	DWORD fvf;
	LPDIRECT3DVERTEXDECLARATION9 declare;

	LPDIRECT3DVERTEXBUFFER9 transformBuffer;
	
	std::vector<D3DXATTRIBUTERANGE> attributeTable;

	InstancingMeshEffect *effect;

	D3DXMATRIX* pWorld;
	DWORD indexTransform;
	
	void MakeDeclaration(LPD3DXMESH mesh);
};

#endif