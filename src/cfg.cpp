#include "cfg.h"

using namespace su;

bool CfgMgr::Init()
{
	L_DEBUG("init cfg");
	Config cfg;
	cfg.init("cfg.txt");
	ip = cfg.GetStr("ip");
	port = (uint16)cfg.GetInt("port");
	is_daemon = cfg.GetInt("is_daemon");
	return true;
}
