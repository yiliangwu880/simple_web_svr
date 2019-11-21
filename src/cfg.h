/*
*/
#pragma once

#include "svr_util/include/read_cfg.h"
#include "svr_util/include/su_include.h"
#include "svr_util/include/string_tool.h"
#include "log_def.h"
#include "libevent_cpp/include/http.h"
#include <memory>

class CfgMgr : public Singleton<CfgMgr>
{
public:
	bool is_daemon = false;
	std::string ip;
	uint16 port = 80;
public:
	bool Init();


private:

};