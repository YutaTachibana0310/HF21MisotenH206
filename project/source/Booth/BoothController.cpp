//=====================================
//
//BoothController.cpp
//機能:
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BoothController.h"
#include "../../Framework/Serial/SerialWrapper.h"
#include "../../Framework/Core/PlayerPrefs.h"

/**************************************
初期化処理
***************************************/
void BoothController::Init()
{
	int comNum = PlayerPrefs::GetNumber<int>("ComPort");

	serial = new SerialWrapper(comNum);
	serial->Begin(9600);
}

/**************************************
取得処理
***************************************/
void BoothController::Uninit()
{
	SAFE_DELETE(serial);
}

/**************************************
回転処理
***************************************/
void BoothController::RotateTable(unsigned char angle)
{
	size_t numPut = serial->Write(angle);
}

/**************************************
LED点滅処理
***************************************/
void BoothController::BlinkLED(bool isPlus)
{
	if (isPlus)
		serial->Write('p');
	else
		serial->Write('m');
}
