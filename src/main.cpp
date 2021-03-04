#include "svr_util/include/su_mgr.h"
#include "svr_util/include/single_progress.h"
#include "libevent_cpp/include/include_all.h"
#include "libevent_cpp/include/http.h"
#include <signal.h>
#include "cfg.h"
#include "svr.h"
#include "AppMgr.h"

using namespace su;
using namespace lc;
using namespace std;


int main(int argc, char* argv[])
{
	AppMgr::Ins().Start(argc, argv, "web_svr");
	return 0;
}

