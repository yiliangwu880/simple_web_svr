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
		su::LogMgr::Ins().Printf((su::LogLv)lv, file, line, fun, pattern, vp);
	}
};
void MyPrintf(su::LogLv lv, const char * file, int line, const char *fun, const char * pattern)
{
	//su::LogMgr::Ins().Printf((su::LogLv)lv, file, line, fun, pattern);
}

void AppMgr::Start(int argc, char* argv[], const string &app_name)
{
	FireEvent<AE_CFG_INI>(); //���ó�ʼ��
	SingleProgress::Ins().Check(argc, argv, app_name.c_str(), AppMgr::Ins().m_isDaemon); //�����رս��̹���
	lc::LogMgr::Ins().SetLogPrinter(MyLcLog::Ins());
	//su::LogMgr::Ins().SetLogPrinter(MyPrintf);
	SuMgr::Ins().Init();
	lc::Timer timer; //һ������ֻ��Ҫһ��lc::Timer��������ʱ����  svr_util ����
	auto f = std::bind(&AppMgr::OnTimer, this);
	timer.StartTimer(30, f, true);

	FireEvent<AE_AFTER_NET_INT>();
	EventMgr::Ins().Dispatch();
	L_INFO("main end");
}

void AppMgr::OnTimer()
{
	if (SingleProgress::Ins().IsExit())
	{
		L_INFO("OnExitProccess");
		EventMgr::Ins().StopDispatch();
		FireEvent<AE_ON_EXIT>();
		return;
	}
	SuMgr::Ins().OnTimer();
}
