//=====================================
//
//データ保存機能処理[PlayerPrefs.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "PlayerPrefs.h"


/**************************************
グローバル変数
***************************************/
const char* PlayerPrefs::FileName = "data/data.bin";

/**************************************
bool取得処理
***************************************/
bool PlayerPrefs::GetBool(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return false;

	return value.get<bool>();
}

/**************************************
int取得処理
***************************************/
int PlayerPrefs::GetInt(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return 0;

	return (int)value.get<double>();
}

/**************************************
float取得処理
***************************************/
float PlayerPrefs::GetFloat(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return 0.0f;

	return (float)value.get<double>();
}

/**************************************
String取得処理
***************************************/
std::string PlayerPrefs::GetString(const std::string & key)
{
	picojson::value value = GetData(key);

	if (!value.is<picojson::null>())
		return false;

	return value.get<std::string>();
}

/**************************************
JSON取得処理
***************************************/
picojson::value PlayerPrefs::GetData(const std::string & key)
{
	std::ifstream ifs;
	ifs.open(FileName, std::ios::binary);

	picojson::value val;
	ifs >> val;
	ifs.close();

	picojson::object object = val.get<picojson::object>();

	if (object.count(key) == 0)
		return picojson::value();
	
	return object[key];
}