#include "pch.h"
#include "Music.h"
#include "resource.h"
#pragma comment(lib,"Winmm.lib")

Music::Music()
{
}


Music::~Music()
{

}

//播放背景音乐
void Music::bgm()
{
	// 产生临时文件的文件名
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat_s(tmpmp3, _T("testapp_background.mp3"));		// VC2008、VC2010 请用 _tcscat_s 函数

	// 将 MP3 资源提取为临时文件
	extractResource(tmpmp3, _T("MP3"), _T("background.mp3"));
	// 注：如果 MP3 资源的 ID 为宏 IDR_BACKGROUND，这样做：
	// ExtractResource(tmpmp3, _T("MP3"), MAKEINTRESOURCE(IDR_BACKGROUND));

	// 打开音乐
	TCHAR mcicmd[300];
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);		// VC2008、VC2010 请用 _stprintf_s 函数
	mciSendString(mcicmd, NULL, 0, NULL);

	// 播放音乐
	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);//repeat重复循环播放

	////if(gameTime)
	//// 停止播放并关闭音乐
	//mciSendString(_T("stop mymusic"), NULL, 0, NULL);
	//mciSendString(_T("close mymusic"), NULL, 0, NULL);

	//// 删除临时文件
	//DeleteFile(tmpmp3);
}

void Music::victoryMusic()
{

	PlaySound(LPWSTR(IDR_WAVE3), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC );

	Sleep(2000);

	ExitThread(0);		//退出所在线程；
}

void Music::defeatMusic()
{
	PlaySound(LPWSTR(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	
	//等待两秒
	Sleep(2000);  
	ExitThread(0);		//退出所线程；
}

//////////////////////////////////////////////////////////////////
// 提取指定模块中的资源文件
// 参数：
//		strDstFile:		目标文件名。提取的资源将保存在这里；
//		strResType:		资源类型；
//		strResName:		资源名称；
// 返回值：
//		true: 执行成功；
//		false: 执行失败。
bool Music::extractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC	hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem = ::LoadResource(NULL, hRes);
	DWORD	dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0;  	// 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}

void Music::clearMusic()
{
	
	PlaySound(LPWSTR(IDR_WAVE4), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	ExitThread(0);		//退出线程；
}




