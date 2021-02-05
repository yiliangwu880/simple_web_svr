简介：
	作为 svr_util libevent_cpp 库使用的典型例子。
	当你需要一个极简单的网页，而不想配置部署nginx apache, 开发php。这项目是不错的选择
	C++实现的简单交换网页。
	应用场景：简单的后台管理网页,比如管理服务器群，作弊测试，查看服务器状态等。
	这只是个模板项目，自定义功能需要用户添加代码。

编译方法：
	整个文件夹放到linux目录，安装cmake gcc git等。

	git submodule init      --更新子模块
	git submodule update			
	git checkout -f	master		--强制删掉本地分支， track远程master分支
	去目录 external里面，参考说明编译每个文件夹，生成依赖库。
	主目录执行：sh clearBuild.sh 完成编译

	
使用方法： 在函数 Svr::RevRequest扩展自定义需求即可。

