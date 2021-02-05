/*
���� svr_util libevent_cpp ������app���� д��
*/
#pragma once
#include "game_util/publish_subscribe.h"
#include "singleton.h"
#include "include_all.h"
#include "log_def.h"

//100��ʼ
enum  APP_EVENT
{
	AE_CFG_INI = 1,
	AE_AFTER_NET_INT = 2, //��������ʼ����
	AE_ON_EXIT = 3, //���̽���
};

namespace su
{
	template<>
	struct EventTraits<AE_CFG_INI> {
		using Fun = void(*)();
	};
	template<>
	struct EventTraits<AE_AFTER_NET_INT> {
		using Fun = void(*)();
	};
	template<>
	struct EventTraits<AE_ON_EXIT> {
		using Fun = void(*)();
	};
}

class AppMgr : public Singleton<AppMgr>
{
public:
	bool m_isDaemon = false;

public:
	void Start(int argc, char* argv[]);
	void OnTimer();

private:

};