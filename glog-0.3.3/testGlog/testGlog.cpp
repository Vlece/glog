// testGlog.cpp : �������̨Ӧ�ó������ڵ㡣
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
	FLAGS_log_dir = ".\\Logs";  //������־Ŀ¼
// 	TCHAR strFileName[MAX_PATH]={0};
// 	GetModuleFileName(NULL,strFileName,MAX_PATH);
// 	PathRemoveFileSpec(strFileName);
	google::InitGoogleLogging(/*argv[0]*/"testlog"); 
	//FLAGS_stderrthreshold=google::INFO;
	google::SetLogDestination(google::GLOG_INFO, ".\\Logs\\INFO_");  //������ļ�
// 	google::SetLogDestination(google::GLOG_ERROR, ".\\Logs\\INFO_");  //������ļ�
// 	google::SetLogDestination(google::GLOG_FATAL, ".\\Logs\\INFO_");  //������ļ�
	google::SetStderrLogging(google::GLOG_INFO);  //���ڵ���google::GLOG_INFO�����������Ļ
	//google::SetLogFilenameExtension("log_");  //�ļ�����չ
	FLAGS_colorlogtostderr = true;  // Set log color  
	FLAGS_logbufsecs = 0;			// Set log output speed(s)  
	FLAGS_max_log_size = 1;		// Set max log file size(MB)  
	FLAGS_stop_logging_if_full_disk = true;  // If disk is full  
	testClass testc;
	char str[20] = "hello log!";  
	LOG(INFO) << str;  
	LOG(INFO) << "info test " << "hello log!";  //���һ��Info��־  
	LOG(WARNING) << "warning test";				//���һ��Warning��־  
	LOG(ERROR) << "error test";					//���һ��Error��־  

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
