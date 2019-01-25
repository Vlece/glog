// testGlog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "glog/logging.h"
#include <process.h>
#include <windows.h>
#include <shlwapi.h>
#include <winbase.h>
#pragma comment(lib,"shlwapi.lib")  
#pragma comment(lib,"libglog.lib")  
#define GLOG_NO_ABBREVIATED_SEVERITIES
#define GOOGLE_GLOG_DLL_DECL

HANDLE hHandle =NULL;
DWORD WINAPI RunThread(PVOID para);
class testClass
{
public:
	testClass()
	{
		LOG(INFO)<<"testClass";
	}
};

int _tmain(int argc, char* argv[])
{
	FLAGS_log_dir = ".\\Logs";  //设置日志目录
// 	TCHAR strFileName[MAX_PATH]={0};
// 	GetModuleFileName(NULL,strFileName,MAX_PATH);
// 	PathRemoveFileSpec(strFileName);
	google::InitGoogleLogging(/*argv[0]*/"testlog"); 
	//FLAGS_stderrthreshold=google::INFO;
	google::SetLogDestination(google::GLOG_INFO, ".\\Logs\\INFO_");  //输出到文件
// 	google::SetLogDestination(google::GLOG_ERROR, ".\\Logs\\INFO_");  //输出到文件
// 	google::SetLogDestination(google::GLOG_FATAL, ".\\Logs\\INFO_");  //输出到文件
	google::SetStderrLogging(google::GLOG_INFO);  //大于等于google::GLOG_INFO级别，输出到屏幕
	//google::SetLogFilenameExtension("log_");  //文件名拓展
	FLAGS_colorlogtostderr = true;  // Set log color  
	FLAGS_logbufsecs = 0;			// Set log output speed(s)  
	FLAGS_max_log_size = 1;		// Set max log file size(MB)  
	FLAGS_stop_logging_if_full_disk = true;  // If disk is full  
	testClass testc;
	char str[20] = "hello log!";  
	LOG(INFO) << str;  
	LOG(INFO) << "info test " << "hello log!";  //输出一个Info日志  
	LOG(WARNING) << "warning test";				//输出一个Warning日志  
	LOG(ERROR) << "error test";					//输出一个Error日志  

	hHandle = ::CreateThread(NULL,0,RunThread,NULL,0,NULL);
	WaitForSingleObject(hHandle,INFINITE);
	google::ShutdownGoogleLogging();  
	system("pause");
	return 0;
}


DWORD WINAPI RunThread(PVOID para)
{
	for(int i =0 ; i<1; i++)
	{
		LOG(INFO)<<"CreateProcessBypassUAC begin";
		LOG(INFO)<<"CreateProcessBypassUAC end";		
	}
	//RAW_LOG
	Sleep(3*1000);
	CloseHandle(hHandle);
	hHandle =NULL;
	return 0;
}
