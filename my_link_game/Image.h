#pragma once
#include "Game.h"
#include <graphics.h>
#define GRID_MAX_ROW	12				//便于改变总的格子数（GRID_MAX_ROW*GRID_MAX_ROW）;加上了边界的外圈
#define GRID_MAX_COLUMN	10				//生成格子数组的最大列数（即二维数组的第二个的最大下标）
#define MAP_MAX_NUMBER	40				//无限模式最多能加载的图片对数 
#define MAX_LEVEL		13				//闯关模式最多能有的背景图片对数

class Image:public Game				//声明Image是Game的子类
{
public:
	//默认的构造函数；
	Image() : countImage(0), markCount(0), pass(false), gridSize(LEVEL_GRID_SIZE),
		positionX(LEVEL_PX),positionY(LEVEL_PY),level(1)
		 { 	
		//构造函数给数组赋值为0
		for (int i = 0; i < GRID_MAX_ROW; i++) {
			for (int j = 0; j < GRID_MAX_COLUMN; j++) {
				gridAttribute[i][j] = 0;
			}
		}
		//重置记录的图片和属性为0
		for (int i = 0; i < MAP_MAX_NUMBER; i++) {
			for (int j = 0; j < 2; j++) {
				imageAttribute[i][j] = 0;
				imageNumber[i][j] = NULL;
			}
		}
	}
	//重载的构造函数
	Image( int positionX, int positionY,int gridSize, int row, int column,int maxImageNumber)
		: countImage(0), markCount(0), pass(false),level(1) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->gridSize = gridSize;
		this->mapRow = row;
		this->mapColumn = column;
		this->maxImageNumber = maxImageNumber;
		//构造函数给数组赋值为0
		for (int i = 0; i < GRID_MAX_ROW; i++) {
			for (int j = 0; j < GRID_MAX_COLUMN; j++) {
				gridAttribute[i][j] = 0;
			}
		}
		//重置记录的图片和属性为0
		for (int i = 0; i < MAP_MAX_NUMBER; i++) {
			for (int j = 0; j < 2; j++) {
				imageAttribute[i][j] = 0;
				imageNumber[i][j] = NULL;
			}
		}
	}
	~Image();
	//画地图相关函数
	void drawMap();							//画消除的格子图。
	void swapImage();						//交换图片包括属性（数值记录）；
	bool judgePass();						//判断是否进入了下一关；

	//消除相关函数
	void gridJudgement(MOUSEMSG mouse);		//消除图片	

	void clearLine();						//清除画线的函数；
	//消除判断相关函数
	bool judgeClear();						//判断是否能够消除图片；
	void comparePosition();					//比较坐标大小
	bool oneLine();							//判断一条直线（0折）是否可行;如果可行画一条连接直线
	bool twoLine();							//判断两条直线（1折）是否可行;如果可行画两条连接直线
	bool thereLine();						//判断三条直线（2折）是否可行
	void thereLineLeft(bool & there);		//判断三条直线当x相等（同列）时向左的判断
	void thereLineRight(bool & there);		//判断三条直线当x相等（同列）时向右的判断
	void thereLineUp(bool & there);			//判断三条直线当y相等（同行）时向上的判断
	void thereLineDown(bool & there);		//判断三条直线当y相等（同行）时向下的判断

	//加载消除·图片函数
	void numberImage(int number);			//给每一个加载的图片一个数字；便于随机选择。

	void imageVictory();					//胜利的图片
	void imageDefeat();						//失败的图片；
	void gameStartImage();					//游戏开始界面；
	void finalVictoryImage();				//游戏通关后的图片；
	//加载背景图片函数
	void backGroundImage(int number);		//给背景图一个数字
	//加载按键图片；
	void imagePause();
	void imageContinue();
	void imageExit();
	void passBottom();									//通关按钮
	void levelBttom();									//闯关模式按钮
	void infiniteBttom();								//无线模式按钮
	bool getClearOne();									//得到记录的消除信息
	int getLevel();										//得到当前关卡数
	void initMaxImageNumber();							//最大图片数重置
	void maxImageNumberPlus();							//最大图片数加一
	void levelPlus();									//关卡数增加
	void initLevel();									//重置关卡数
private:
	int level;											//当前关卡数
	bool clearOne;										//记录消除了一对图片；
	int maxImageNumber;									//每一关的最大图片的对数;
	IMAGE imageNumber[MAP_MAX_NUMBER][2];				//确保载入的图片为偶数；
	int countImage;										//记录产生了多少对图片；
	int imageAttribute[MAP_MAX_NUMBER][2];				//记录加载的图片属性（即记录相同图片==相同的数值）	
	int clickAttribute[2];								//记录点击的图片的属性
	//记录标记次数（标记次数=markCount+1），如果标记次数为2（此时mark==1）时做判断	
	int markCount;							
	bool pass;											//记录是否通过关卡
	IMAGE bgImage[MAX_LEVEL];							//记录每一关的背景图；
	int positionX;										//格子边界左上角x坐标。
	int positionY;										//格子边界左上角y坐标。
	int gridSize;										//格子（消除图片）的大小
	int mapRow;											//消除地图的行数
	int mapColumn;										//消除地图的列数

	//记录格子状态（0和GRID_MAX_ROW表示边界，1到GRID_MAX_ROW表示图片状态）
	//记录图片属性数组下标为grid，因为数组从1开始记录，0表示边界位置，
	//gridMax也表示边界，判断时要判断边界；
	int gridAttribute[GRID_MAX_ROW][GRID_MAX_COLUMN];
	int clickX[2];										//记录点击图片的x坐标(gridAttribute[6][6])
	int clickY[2];										//记录点击图片的y坐标(gridAttribute[6][6])
	int minClickX;										//记录的两组格子中x的较小值
	int minClickY;										//记录的两组格子中y的较小值
	int maxClickX;										//记录的两组格子中x的较大值
	int maxClickY;										//记录的两组格子中y的较大值	
};

