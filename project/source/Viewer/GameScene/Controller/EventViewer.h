//=============================================================================
//
// �C�x���g�r���A�[�Ǘ����� [EventViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _EVENT_VIEWER_H_
#define _EVENT_VIEWER_H_

#include <vector>
#include <string>
#include <functional>
#include "../EventViewer/EventTelop.h"
#include "../../../../Framework/Pattern/Delegate.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class EventTelop;
class EventMessage;
class SealItemStockViewer;
class EventViewerParam;
class BaseViewer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EventViewer
{
public:
	EventViewer();
	~EventViewer();

	void Update(void);
	void Draw(void);

	//���b�Z�[�W�Z�b�g
	void SetEventMessage(const std::string message);

	//�e���b�v���Z�b�g
	void SetEventTelop(EventTelop::TelopID id, std::function<void(void)> Callback = nullptr);

	//�p�����[�^�󂯎��
	void ReceiveParam(EventViewerParam &param);

private:
	static const int messageMax = 5;

	std::vector <BaseViewer*> eventViewer;
	std::vector <std::string> messageContainer;

	EventTelop * eventTelop;
	EventMessage *eventMessage[messageMax];
	SealItemStockViewer *sealStockViewer;

	void CountMessage(void);
	void PlayMessage(void);

	//���b�Z�[�W���Z�b�g�����ƃJ�E���g�A�b�v����J�E���^�[
	int messageSetCnt;
};

#endif
