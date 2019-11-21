#pragma once
#include "libevent_cpp/include/http.h"
#include "cfg.h"

using namespace std;
using namespace lc;
class Svr : public lc::BaseHttpSvr
{
	std::string m_html;
	std::map<std::string, std::string> m_post;
public:

private:
	virtual void RevRequest();

	const std::string &SetHtml(const std::string &v1, const std::string &v2, const std::string &paragraph);
	//解析post参数：比如 “para1=1&para2=2”
	void ParsePostPara(const std::string &str);
};
