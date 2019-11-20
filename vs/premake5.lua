--
-- premake5 file to build RecastDemo
-- http://premake.github.io/
--
require "lib"

local action = _ACTION or ""
local outdir = action


WorkSpaceInit  "web_svr"



Project "web_svr"
	IncludeFile { 
		"../external/",
	}

	SrcPath { 
		"../src/**",  --**递归所有子目录，指定目录可用 "cc/*.cpp" 或者  "cc/**.cpp"
	}
	files {
	"../*.txt",
	"../*.lua",
	"../*.sh",
	}
	
    
 
Project "lib"
	IncludeFile { 
		"../external/",
	}

	SrcPath { 
		"../external/svr_util/include/**",  
		"../external/libevent_cpp/include/**",  
	}

	




