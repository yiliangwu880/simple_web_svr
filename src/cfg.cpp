#include "cfg.h"
#include "svr.h"
#include "AppMgr.h"

using namespace su;

bool CfgMgr::Init()
{
	L_DEBUG("init cfg");
	Config cfg;
	cfg.init("cfg.txt");
	ip = cfg.GetStr("ip");
	port = (uint16)cfg.GetInt("port");
	AppMgr::Ins().m_isDaemon = cfg.GetInt("is_daemon");

	return true;
}

void ON_AE_CFG_INI()
{
	if (!CfgMgr::Ins().Init())
	{
		printf("read cfg fail!");
		exit(1);
		return;
	}
}
STATIC_RUN(RegEvent<AE_CFG_INI>(ON_AE_CFG_INI);)
