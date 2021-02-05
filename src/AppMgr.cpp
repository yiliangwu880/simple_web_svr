#include "AppMgr.h"
#include "su_mgr.h"
#include "single_progress.h"
#include "libevent_cpp/include/include_all.h"
#include "libevent_cpp/include/http.h"
#include "cfg.h"
#include "svr.h"

using namespace su;
using namespace lc;

class MyLcLog : public lc::ILogPrinter, public Singleton<MyLcLog>
{
public:
	virtual void Printf(lc::LogLv lv, const char * file, int line, const char *fun, const char * pattern, va_list vp) override
	{
		su::LogMgr::Obj().Printf((su::LogLv)lv, file, line, fun, pattern, vp);
	}
};

void AppMgr::Start(int argc, char* argv[])
{
	TriggerEvent<AE_CFG_INI>(); //���ó�ʼ��

	SingleProgress::Obj().Check(argc, argv, "web_svr", AppMgr::Ins().m_isDaemon); //�����رս��̹���
	SuMgr::Obj().Init();

	EventMgr::Ins().Init(&MyLcLog::Obj());
	L_INFO("after EventMgr::Ins().Init ");
	TriggerEvent<AE_AFTER_NET_INT>();
	lc::Timer timer; //һ������ֻ��Ҫһ��lc::Timer��������ʱ����  svr_util ����
	auto f = std::bind(&AppMgr::OnTimer, this);
	timer.StartTimer(30, f, true);
	
	EventMgr::Ins().Dispatch();
	L_INFO("main end");
}

void AppMgr::OnTimer()
{
	if (SingleProgress::Obj().IsExit())
	{
		L_INFO("OnExitProccess");
		EventMgr::Ins().StopDispatch();
		TriggerEvent<AE_ON_EXIT>();
		return;
	}
	SuMgr::Obj().OnTimer();
}
