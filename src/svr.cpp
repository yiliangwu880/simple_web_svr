#include "svr.h"
#include "AppMgr.h"
#include "static_reg.h"

using namespace su;

namespace{
void ON_AE_AFTER_NET_INT()
{
	SvrMgr::Ins().m_svr = new Svr();
	L_INFO("web svr addr:%s %d", CfgMgr::Obj().ip.c_str(), CfgMgr::Obj().port);
	L_COND(SvrMgr::Ins().m_svr->Init(nullptr, CfgMgr::Obj().port));
}
STATIC_RUN(RegEvent<AE_AFTER_NET_INT>(ON_AE_AFTER_NET_INT);)

void OnExit()
{
	delete SvrMgr::Ins().m_svr; // 在 EventMgr::Ins 前释放
	SvrMgr::Ins().m_svr = nullptr;
}
STATIC_RUN(RegEvent<AE_ON_EXIT>(OnExit);)
}

void Svr::RevRequest()
{
	string str;
	GetData(str);
	L_INFO("rev req: %s , path=%s", str.c_str(), GetPath().c_str());
	ParsePostPara(str);
	AddHeader("Content-Type", "text/html");
	AddHeader("charset", "utf-8");

	Send(SetHtml(m_post["p1"], m_post["p2"], string("我的输出:")+ m_post["p2"]));
}

/*
<form action = "/" method = "post" enctype = "multipart/form-data" accept-charset = "UTF-8">
File1<input type = "file" name = "uploadFile"><br / >
<input type = "submit" value = "提交">
<form action = "/" method = "post">
*/

namespace{
static const char *P1 = R"(
<html>
<head>
<title>simple_web</title >
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"> 
</head>
<body>
<p>)";

static const char *P12 = R"(
说明：xxx
)";

static const char *P13 = R"(</p>
<div style="width:100%;text-align:center">
<form action = "/" method = "post" accept-charset = "UTF-8">
参数1:<input type = "text" name = "p1" style="width:545px;height:35px" value=")";
//显示参数1
static const char *P2 = R"(">
<br><br>参数2:<input type = "text" name = "p2" style="width:545px;height:35px" autofocus value=")";
//显示参数2
static const char *P3 = R"(">
<br><input type = "submit" style="width:100px;height:35px" value = "提交">
</form>
</div>
<p>)"; 

//输出：日志
static const char *P4 = R"(</p>
</body>
</html>

)";
}
const std::string & Svr::SetHtml(const std::string &v1, const std::string &v2, const std::string &paragraph)
{
	m_html.clear();
	m_html.append(P1);
	m_html.append(P12);
	m_html.append(P13);
	m_html.append(v1);
	m_html.append(P2);
	m_html.append(v2);
	m_html.append(P3);
	m_html.append(paragraph);
	m_html.append(P4);
	return m_html;
}

void Svr::ParsePostPara(const std::string &str)
{
	m_post.clear();
	using CHAR_PRT = std::unique_ptr<char, decltype(&::free)>;
	CHAR_PRT decode_str(evhttp_uridecode(str.c_str(), 1, nullptr), ::free); //自动释放资源
	L_COND(decode_str.get());
	VecStr out;
	StrUtil::split(decode_str.get(), '&', out);
	for (uint32 i = 0; i < out.size(); ++i)
	{
		VecStr out2;
		StrUtil::split(out[i], '=', out2);
		if (out2.size() != 2)
		{
			continue;
		}
		m_post[out2[0]] = out2[1];
		//L_DEBUG("post %s %s", out2[0].c_str(), out2[1].c_str());
	}
}

