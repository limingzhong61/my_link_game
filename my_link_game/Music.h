#pragma once
class Music
{
public:
	Music();
	~Music();

	void clearMusic();				//清除图片的音乐；
	void bgm();						//游戏开始前加载背景图片和音乐
	void victoryMusic();			//胜利音乐；
	void defeatMusic();				//失败音乐；
	// 提取指定模块中的资源文件;代码来自easyx网站；
	bool extractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);			
};

