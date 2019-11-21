简介：
	C++实现的简单交换网页. 通常用来做简单的后台管理网页，用户通过网页交互，管理一群服务器。

编译方法：
	整个文件夹放到linux目录，安装cmake gcc git等。

	git submodule init      --更新子模块
	git submodule update			
	git checkout -f	master		--强制删掉本地分支， track远程master分支
	去目录 external里面，参考说明编译每个文件夹，生成依赖库。
	主目录执行：sh clearBuild.sh 完成编译

			
	
vs浏览代码：
	执行.\vs\run.bat,生成sln文件

	
使用方法： 在函数 Svr::RevRequest扩展自定义需求即可。

