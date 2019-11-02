//=====================================
//
//FieldTownModel.h
//機能:街のロジックモデル
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _FIELDTOWNMODEL_H_
#define _FIELDTOWNMODEL_H_

#include "../../../main.h"
#include "../FieldConfig.h"

#include <list>
#include <vector>
#include <functional>
#include <utility>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;

	/**************************************
	クラス定義
	***************************************/
	class TownModel
	{
	public:
		//コンストラクタ、デストラクタ
		TownModel(const PlaceModel* place, std::function<void(const PlaceModel *start, const PlaceModel *goal)> *action);
		~TownModel();

		//更新処理
		void Update();

		//出口追加処理
		void AddGate(const PlaceModel* gate);

		//出てくる人数の取得処理
		float DepatureNum();

		//出口数取得処理
		int GateNum();

		//リンクレベル取得処理
		int LinkLevel();

		//発展度取得処理
		float DevelopmentLevel();

		//繋がっている街を探す処理
		void FindLinkedTown();

		//リンクレベル加算処理
		void AddLinkLevel(int num);

		//プレイス取得処理
		const PlaceModel* GetPlace();
		
		//経路追加処理
		void AddLinkedTown(const PlaceModel *place);

	private:
		static const float BaseDepatureNum;		//基準となる出発数

		//ID
		static unsigned incrementID;
		const int uniqueID;

		//参照するプレイスモデル
		const PlaceModel* place;

		//リンクレベル
		int linkLevel;

		//リンクレベルバイアス
		int biasLinkLevel;

		//発展度
		float developmentLevel;

		//フレームカウンタ
		int cntFrame;

		//どの街へ向かわせるか
		int indexDestination;

		//パッセンジャー出発処理
		std::function<void(const PlaceModel* start, const PlaceModel *end)> *departPassenger;

		//繋がってる街への経路
		//first : 相手の街, second : 出口
		std::vector<std::pair<const PlaceModel*, const PlaceModel*>> linkedTown;

		//出口
		std::vector<const PlaceModel*> gateList;

		//探索中の出口のインデックス
		unsigned indexSearchingGate;
	};
}
#endif