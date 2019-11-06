#pragma once
//闯关模式参数
#define LEVEL_GRID_SIZE		64			//闯关模式格子的大小
#define LEVEL_ROW			6			//闯关模式行数
#define LEVEL_COLUMN		6			//闯关模式列数
#define INIT_LEVEL_TIME		33			//最开始的第一关的游戏时间
#define LEVEL_PX			36			//闯关模式格子左上角x坐标
#define LEVEL_PY			0			//闯关模式格子左上角y坐标
#define INITo_IMAGE_NUMBER	6			//闯关模式第一关的图片对数；
#define MAX_LEVEL			13			//闯关模式最大关卡数
//无限模式参数
#define INFI_TIME			110			//无限模式的时间
#define INFI_GRID_SIZE		58			//无限模式格子的大小
#define INFI_ROW			10			//无限模式行数
#define INFI_COLUMN			 8			//无限模式列数
#define INFI_PX				36			//无限模式格子左上角x坐标
#define INFI_PY				-21			//无限模式格子左上角y坐标
#define INFI_IMAGE_NUMBER	16			//无限模式图片对数；
class Game
{
public:
	Game() :WINDOW_WIDE(1000), WINDOW_HEIGTH(540),levelTime(INIT_LEVEL_TIME), lastMoment(levelTime),
		gameTimePlus(3),PAUSE_PX(850), PAUSE_PY(400), PAUSE_SIZE(60), EXIT_PX(915), EXIT_PY(415), 
		EXIT_SIZE(45), PASS_LEFT_PX(450), PASS_LEFT_PY(200), PASS_RIGHT_PX(550),PASS_RIGHT_PY(290),
		countPassB(0),PASS_BOTTOM_SIZE(50),MODE_PY(359),INFINITE_PX(325),LEVEL_MODE_PX(530),MODE_LENGTH(180),
		MODE_WIDE(41),score(0),scorePlus(10){};
	//自定义默认构造函数
	~Game();

	void controller();									//整个游戏循环
	void window();										//建立一个图像窗口并标注自己的名字
	bool judgeStart(MOUSEMSG mouse);					//判断是否点击了游戏开始按钮
	void gameHelp(MOUSEMSG mouse);						//判断是否点击了游戏帮助按钮和进入游戏帮助界面
	void gameTime();									//判断游戏时间
	void gameVictory(int level);						//游戏胜利时（包括了通关）的加载
	void gameDefeat();									//游戏失败时的加载
	void levelWord(int level);							//游戏当前关卡字；
	bool judgePause(MOUSEMSG mouse);					//判断是否点击了游戏暂停按钮
	bool judgeExit(MOUSEMSG mouse);						//判断是否点击了游戏重新开始按钮
	void startPassMode(MOUSEMSG mouse);					//判断是否开启了通关按钮并加载通关按钮；
	bool judgePassBottom(MOUSEMSG mouse);				//判断是否点击了通关按钮；
	bool judgeMode(MOUSEMSG mouse);						//判断点击的模式；false为闯关模式；true为无线模式；
	void modeBottom();									//圈中选中的模式按钮
	void scoreWord();									//加载无限模式游戏分数
protected:

	const int WINDOW_WIDE;								//显示屏幕的宽度
	const int WINDOW_HEIGTH;							//显示屏幕的长度
	const int PAUSE_PX;									//暂停按钮左上角的x坐标
	const int PAUSE_PY;									//暂停按钮左上角的y坐标
	const int PAUSE_SIZE;								//暂停按钮的长度；
	const int EXIT_PX;									//退出开始新游戏按钮左上角的x坐标
	const int EXIT_PY;									//退出开始新游戏按钮左上角的y坐标
	const int EXIT_SIZE;								//退出开始新游戏按钮的长度；
	const int PASS_BOTTOM_SIZE;							//通关按钮的大小；
	const int INFINITE_PX;								//无限模式按钮左上角x坐标
	const int MODE_PY;									//模式按钮的y坐标
	const int LEVEL_MODE_PX;							//闯关模式按钮左上角x坐标；
	const int MODE_LENGTH;								//模式按钮的长度；
	const int MODE_WIDE;								//模式按钮的宽度；

	static MOUSEMSG mouse;								//定义一个静态的记录鼠标的变量；
	static	bool infiniteMode; 							//记录是否点击了无限模式；
private:
	int second;											//用来记录startTime和stopTime之间的间隔；
	int levelTime;										//用来记录每一关的游戏时间
	int lastMoment;										//最后时刻；用来记录还剩余多少时间
	 int gameTimePlus;									//关卡模式每通过一关（或是无线模式消除一对图片）增加的时间；
	bool judgeP=false;									//判断是否点击了暂停；true为游戏暂停，false为游戏正常。
	bool judgeE=false;									//判断是否点击了exit按钮；
	const int PASS_LEFT_PX;								//开启通关按钮左上角的x坐标
	const int PASS_LEFT_PY;								//开启通关按钮左上角的y坐标
	const int PASS_RIGHT_PX;							//开启通关按钮右下角的x坐标
	const int PASS_RIGHT_PY;							//开启通关按钮右下角的y坐标
	bool judgePassB=false;								//记录是否开启了通关按钮；
	int countPassB;										//记录点击开启通关按钮的次数；
	bool judgePb=false;									//是否点击了通关按钮；
	bool judgeS=false;									//记录是否点击了开始按钮；
	bool judgeH = false;								//记录是否点击了帮助按钮；
	int score;											//记录得到的分数
	const int scorePlus;								//消除一次增加的时间
};

