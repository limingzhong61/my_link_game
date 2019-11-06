#include "pch.h"
#include "Game.h"
// 引用 Windows Multimedia API
#pragma comment(lib,"Winmm.lib")
#include  "Image.h"
#include "Music.h"
#include <conio.h>
#include <thread>


bool Game::infiniteMode = false;

Game::~Game()
{
}

//定义一个全局的Image类对象；便于按钮的判断；
Image image;

void Game::controller()
{
	Music music;		
	music.bgm();
	window();

	Image infiniteImage(INFI_PX, INFI_PY, INFI_GRID_SIZE, INFI_ROW, INFI_COLUMN, INFI_IMAGE_NUMBER);
	Image levelImage(LEVEL_PX, LEVEL_COLUMN, LEVEL_GRID_SIZE, LEVEL_ROW, LEVEL_COLUMN, INITo_IMAGE_NUMBER);

	//定义一个鼠标消息便于判断
	MOUSEMSG mouse;
	//定义一个bool使得步骤循环中只执行一次
	bool newStart = true;
	//记录关卡数；以便恢复

	while (1)
	{
		//newStart的判断使得判断内的语句只在循环中执行一次；
		if (newStart == true) {
			newStart = false;
			//重新清除图片（exit到游戏开始界面的）
			cleardevice();
			//开始游戏的背景图
			image.gameStartImage();
			//创建一个圈中模式的多线程
			std::thread modeB(&Game::modeBottom, this);
			modeB.detach();
		}
		//如果有新的鼠标消息；
		if (MouseHit()) {
			//每次循环都要得到鼠标消息
			mouse = GetMouseMsg();
		
			gameHelp(mouse);

			judgeMode(mouse);
			startPassMode(mouse);

			if (judgeStart(mouse)) {
				if (infiniteMode == true) {
				//重新进入无限模式的更新
					levelTime = INFI_TIME;
					gameTimePlus = 2;
					//重新开始；计分为0
					score = 0;
					//清除当前屏幕上的内容；
					cleardevice();
					//第一次开始画一个无限模式消除的格子地图
					infiniteImage.drawMap();
				}
				else {
					//重新进入闯关模式的更新
					gameTimePlus = 3;
					//防止exit回到游戏界面，时间为第一关的值
					levelTime = INIT_LEVEL_TIME+(levelImage.getLevel()-1)*gameTimePlus;
					//清除当前屏幕上的内容；
					cleardevice();
					//第一次开始画一个闯关模式消除的格子地图
					levelImage.drawMap();
				}
				//创建一个计时的多线程
				std::thread gameT(&Game::gameTime, this);
				gameT.detach();
				//点击之后赋值false；防止下一次exit判断仍为真；
				//不能放在exit判断里；只能放在开始；因为计时gameTime在judgeE==false才不计时；
				judgeE = false;
				//防止点击暂停后再点击exit重置后，游戏不为暂停；
				judgeP = false;
				//开始计时,重新给lastMoment值，防止是exit退出重新进入；
				lastMoment = levelTime;
				if (infiniteMode == false) {
					//第一关字显示
					levelWord(levelImage.getLevel());
				}
				else {
					scoreWord();
				}
				if (judgePassB) {
					//显示通关按钮图片，因为drawMap之后清掉了之前的图片；
					image.passBottom();
				}
				//游戏开始之后的循环
				while (1)
				{
					//如果有新的鼠标消息
					if (MouseHit()) {
						mouse = GetMouseMsg(); //每次循环都要得到鼠标消息
					//点击了暂停和开始区域
						if (judgePause(mouse)) {
							//取反，改变记录状态；
							judgeP = !judgeP;
							//点击了暂停按钮，游戏暂停
							if (judgeP == true) {
								//暂停按钮换成开始按钮；游戏暂停
								image.imageContinue();
							}
							else {//点击了开始按钮；
								//开始按钮换成暂停按钮；游戏开始
								image.imagePause();
							}
						}
						//点击了退出按钮
						if (judgeExit(mouse) == true) {
							//回到游戏开始界面；judgeS为false；不然圈中模式的线程检测不到；
							judgeS = false;
							//重置newStart
							newStart = true;
							break;
						}
						//游戏失败;
						if (lastMoment == 0) {
							lastMoment = -1;
							while (1) {
								//进入一个空循环防止进入其他执行步骤（消除图片）；
							}
						}
						judgePassBottom(mouse);
						//关卡模式判断
						if (infiniteMode == false) {
							//游戏通关；或者是开启了通关模式并点击了通关按钮；
							if (levelImage.judgePass() == true || (judgePb  && judgePassB)) {
								//如果是按了通关按钮，则重置为false
								judgePb = false;
								
								//重置游戏时间,=-1让计时多线程结束；
								lastMoment = -1;
								//防止使用通关按钮时点了暂停按钮;故重置为非暂停（即开始）；
								judgeP = false;
								//游戏胜利
								gameVictory(levelImage.getLevel());
								//如果通关了；
								//关卡最大图片数加一
								levelImage.maxImageNumberPlus();
								if (levelImage.getLevel() == MAX_LEVEL) {
									//回到游戏开始界面；judgeS为false；不然圈中模式的线程检测不到；
									judgeS = false;
									//重置关卡数
									levelImage.initLevel();
									//重置关卡图片数
									levelImage.initMaxImageNumber();
									//重置游戏时间
									levelTime = INIT_LEVEL_TIME;
									//回到游戏开始界面；
									//重置newStart
									newStart = true;
									break;
								}
								//关卡+1；如果内部实现会导致通关按钮失败
								levelImage.levelPlus();
								// 进入下一关;
								levelImage.drawMap() ;
								//其他关卡的字显示
								levelWord(levelImage.getLevel());
								//下一关开始才重置时间，不然影响判断；
								//记录每一关的限定时间；并重置计时变量lastMoment=0；
								levelTime += gameTimePlus;
								lastMoment = levelTime;
								//重新开始创建一个计时的多线程
								std::thread gameT(&Game::gameTime, this);
								gameT.detach();
								if (judgePassB) {
									//显示通关按钮图片，因为drawMap之后清掉了之前的图片；
									image.passBottom();
								}
								//清除鼠标缓存防止重复点击通关按钮；判断为通关
								FlushMouseMsgBuffer();
							}
						}//无限模式判断
						else {
							
							if (infiniteImage.getClearOne() == true) {
								//消除图片增加时间
								lastMoment += gameTimePlus;
								//增加记录分数
								score += scorePlus;
								scoreWord();
							}
							//清空了游戏图片；或者是开启了通关模式并点击了通关按钮；
							if (infiniteImage.judgePass() == true || (judgePb && judgePassB)) {
								//防止使用通关按钮时点了暂停按钮;故重置为非暂停（即开始）；
								judgeP = false;
								//关卡数加1；更新背景图
								infiniteImage.levelPlus();
								//重置关卡数；
								if (infiniteImage.getLevel() == MAX_LEVEL+1) {
									infiniteImage.initLevel();
								}
								//如果是按了通关按钮，则重置为false
								judgePb = false;
								//加载下一次的图片
								infiniteImage.drawMap();
								//加载分数
								scoreWord();
								//清除鼠标缓存防止重复点击通关按钮；判断为通关
								FlushMouseMsgBuffer();
							}
							if (judgePassB) {
								//显示通关按钮图片，因为drawMap之后清掉了之前的图片；
								image.passBottom();
							}
							
						}
						//游戏没有暂停，才能进行判断；
						if (judgeP == false) {
							//判断消除
							if (infiniteMode==false) {
								levelImage.gridJudgement(mouse);
							}
							else {
								infiniteImage.gridJudgement(mouse);
							}

						}
					}
					
				}
			}
		}
	}
}

//建立一个图像窗口并标注自己的名字
void Game::window()
{	
	//创建绘图窗口，大小为 WINDOW_WIDE×WINDOW_HEIGTH 像素
	initgraph(WINDOW_WIDE, WINDOW_HEIGTH);

	// 获取窗口句柄
	HWND hwnd = GetHWnd();
	// 设置窗口标题文字;署名
	SetWindowText(hwnd, _T("王者荣耀连连看       作者：李明忠"));
}

//判断是否点击了游戏开始按钮
bool Game::judgeStart(MOUSEMSG mouse)
{	 //每次进入需要重置为false	
	judgeS = false;
	if (mouse.mkLButton) {
		if (mouse.x >= 375 && mouse.x <= 624 && mouse.y >= 415 && mouse.y <= 470) {
			judgeS = true;
		}
	}
	
	return judgeS;
}

//判断是否点击了游戏帮助按钮；
void Game::gameHelp(MOUSEMSG mouse)
{
	//每次进入重置为false；
	judgeH = false;
	if (mouse.mkLButton) {
		//以包含圆圈的最小正方形代替；圆心：962, 81； 半径： 24。
		if (mouse.x >= 938 && mouse.x <= 986 && mouse.y >= 67 && mouse.y <= 105) {
			// 调用控制台 API，清空之前缓冲区内的所有按键。判断防止之前按了键盘；提前跳出；
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			//记录点击的帮助按钮
			judgeH = true;
			cleardevice();//清屏

			int textPx;//帮助字体左上角的x坐标
			int textPy;//帮助字体左上角的y坐标
			int textInterval;//帮助字体之间纵向的间隔
			textPx = 50;
			textPy = 50;
			textInterval = 60;
			//输出游戏说明
			setcolor(RGB(255, 255, 255));
			settextstyle(35, 0, _T("华文新魏"));
			setcolor(RGB(85, 255, 255));//颜色

			outtextxy(textPx, textPy, _T("本游戏分为无限和闯关两种模式。"));
			outtextxy(textPx, textPy + textInterval, _T("无限模式：每消除一对图案，倒计时增加2s，倒计时增加2s。"));
			outtextxy(textPx, textPy + textInterval * 2, _T("闯关模式：每通过一关，图片种类增加1种，倒计时增加3s。"));
			outtextxy(textPx, textPy + textInterval * 3, _T("加油吧，少年！祝你好运哦！"));
			outtextxy(textPx, textPy + textInterval * 4, _T("游戏继续按钮"));
			outtextxy(textPx, textPy + textInterval * 5, _T("游戏暂停按钮"));
			outtextxy(textPx, textPy + textInterval * 6, _T("游戏重新开始按钮"));

			IMAGE img1;
			loadimage(&img1, _T("PNG"), _T("start"), 40, 40);
			putimage(textPx + textInterval * 4, textPy + textInterval * 4, &img1);

			IMAGE img2;
			loadimage(&img2, _T("PNG"), _T("pause"), 40, 40);
			putimage(textPx + textInterval * 4, textPy + textInterval * 5, &img2);

			IMAGE img3;
			loadimage(&img3, _T("PNG"), _T("exit"), 40, 40);
			putimage(textPx + textInterval * 5, textPy + textInterval * 6, &img3);
			// 实现闪烁的“按任意键继续”
			int c = 255;
			while (!_kbhit())
			{
				setcolor(RGB(c, 0, 0));
				outtextxy(700, 470, _T("按任意键进入游戏"));
				c -= 4;
				if (c < 0) {
					c = 255;
				}
				Sleep(20);
			}
			setcolor(RGB(255, 255, 255));//颜色

			// 调用控制台 API，清空之前缓冲区内的所有按键。
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			//清屏
			cleardevice();
			//跳出之后会到主界面
			image.gameStartImage();
		}
	}

}

void Game::gameTime()
{
	//记录游戏开始时间;DWORD全称Double Word,unsigned long int；
	DWORD startTime=::GetTickCount();;
	//用来记录经过的时间
	DWORD stopTime= ::GetTickCount();;
	//当游戏时间为0时（即游戏失败时）和回到游戏界面时不计时；
	while (lastMoment > 0 && judgeS == true) {
		//每次重新进入计时需要重新记录最开始计时的时间
		if (judgeP == false && lastMoment > 0 && judgeE == false && judgeS == true) {
			startTime = ::GetTickCount();
		}
		//游戏没有点暂停才能计时；lastMoent=-1时游戏进入胜利和失败页面；
		//点了exit回到主界面不用计时;故false才能及时
		//点了游戏开始按钮才能计时
		//判断必须写在while里，进了while就只在while里面判断退出；
		while (judgeP == false && lastMoment > 0 && judgeE == false && judgeS==true ) {

			//记录下一次的时间
			stopTime = ::GetTickCount();
			//GettickCount单位为毫秒，故除以1000为second；
			second = (stopTime - startTime) / 1000;

			//点击了暂停按钮

			if (second == 1) {
				startTime = stopTime;
				lastMoment--;

				TCHAR s[5];
				settextcolor(RED);
				settextstyle(60, 50, _T("黑体"));
				//将数字转变成TCHAR类型；
				swprintf_s(s, _T("%d"), lastMoment);
				if (lastMoment > 99) {
					outtextxy(750, 50, s);
					outtextxy(900, 50, _T("s"));
				}//当lastMoment只有十位时，显示字的位置没有改变
				else if (lastMoment > 9) {
					outtextxy(750, 50, _T("0"));
					outtextxy(800, 50, s);
					outtextxy(900, 50, _T("s"));
				}
				else {
					outtextxy(750, 50, _T("00"));
					outtextxy(850, 50, s);
					outtextxy(900, 50, _T("s"));
				}
			}
		}
	}
	// 调用控制台 API，清空之前缓冲区内的所有按键。判断防止之前按了键盘；提前跳出；
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	//游戏失败；多进程判断防止鼠标不移动而不进入判断
	if (lastMoment == 0) {
		gameDefeat();
	}
	
	//关闭线程；
	ExitThread(0);				
}

//游戏胜利时（包括了通关）的加载
void Game::gameVictory(int level)
{
	Music musicV;
	//播放胜利音乐；
	//创造一个线程；thread引用类外成员函数要类的函数和对象
	std::thread t(&Music::victoryMusic, &musicV);
	t.detach();

	Image allImageV;

	// 调用控制台 API，清空之前缓冲区内的所有按键。判断防止之前按了键盘；提前跳出；
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	if (level ==MAX_LEVEL) {
		allImageV.finalVictoryImage();
		//设置字体大小和颜色
		settextstyle(35, 0, _T("华文新魏"));
		setcolor(RED);//颜色
		outtextxy(300, 430, _T("恭喜你通过了所有的关卡"));
		int c = 255;
		while (!_kbhit())
		{
			setcolor(RGB(c, 0, 0));
			outtextxy(300, 465, _T("点击任意键可返还主界面"));
			c -= 4;
			if (c < 0) {
				c = 255;
			}
			Sleep(20);
		}
	}
	else {
		//加载胜利图片；
		allImageV.imageVictory();
 		while (!_kbhit()) {
			//没有键盘输入的死循环卡住
		}
	}
	//_kbhit()每次记录会缓存到内存里，要用_getch()之类的得到记录的按键；
	//不然记录一次之后，每次循环到kbhit（），会永久判断点击按键为真。
	// 调用控制台 API，清空之前缓冲区内的所有按键。
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

}

//游戏失败时的加载
void Game::gameDefeat()
{
	Music musicD;
	//播放失败音乐；
	//创造一个线程；thread引用类外成员函数要类的函数和对象
	std::thread tD(&Music::defeatMusic, &musicD);
	tD.detach();

	image.imageDefeat();
	//无线模式结束提示分值；
	if (infiniteMode == true) {
		//设置字体
		settextstyle(35, 0, _T("华文新魏"));
		setcolor(RED);//颜色
		outtextxy(350, 410, _T("恭喜你获得了"));
		TCHAR s[10];
		swprintf_s(s, _T("%d"), score);
		outtextxy(560, 410, s);
		outtextxy(650, 410, _T("分"));
	}
	
	//_getch阻塞；
	_getch();
	//正常退出程序
	exit(0);
}



void Game::levelWord(int level)
{

	TCHAR s[5];
	//setcolor(RGB(255, 255, 255));
	settextstyle(35, 0, _T("华文新魏"));
	setcolor(RGB(85, 255, 255));//颜色
	//将数字转变成TCHAR类型；
	swprintf_s(s, _T("%d"), level);
	outtextxy(750, 150, _T("当前关卡："));
	setcolor(RGB(255, 255, 0));
	outtextxy(900, 200, s);
}


//判断是否点击了游戏暂停按钮
bool Game::judgePause(MOUSEMSG mouse)
{
	bool judge = false;
	if (mouse.mkLButton) {
		if (mouse.x >= PAUSE_PX && mouse.x <= PAUSE_PX+PAUSE_SIZE && 
			mouse.y >= PAUSE_PY && mouse.y <= PAUSE_PY+PAUSE_SIZE) {
			judge = true;
		}
	}
	return judge;
}

//判断是否点击了游戏重新开始按钮
bool Game::judgeExit(MOUSEMSG mouse)
{
	if (mouse.mkLButton) {
		if (mouse.x >= EXIT_PX && mouse.x <= EXIT_PX+EXIT_SIZE &&
			mouse.y >= EXIT_PY && mouse.y <= EXIT_PY+EXIT_SIZE) {
			judgeE = true;
		}
	}

	return judgeE;
}

//判断是否开启了通关按钮；
void Game::startPassMode(MOUSEMSG mouse)
{

	if ( mouse.mkRButton) {
		if (mouse.x >= PASS_LEFT_PX && mouse.x <= PASS_RIGHT_PX && mouse.y >> PASS_LEFT_PY && mouse.y << PASS_RIGHT_PY) {
				countPassB++;
		}
	}
	//点击多次以上才能开机通关按钮；防止误触；
	if (countPassB >= 5) {
		//显示通关按钮图片，表示开始通关按钮
		image.passBottom();
		judgePassB = true;
	}
	
}

//判断是否点击了通关按钮；
bool Game::judgePassBottom(MOUSEMSG mouse)
{

	if (mouse.mkRButton) {
		if (mouse.x >= WINDOW_WIDE - PASS_BOTTOM_SIZE && mouse.x <= WINDOW_WIDE &&
			mouse.y >= WINDOW_HEIGTH - PASS_BOTTOM_SIZE && mouse.y <= WINDOW_HEIGTH) {
			judgePb = true;
		}
	}
	return judgePb;
}

//判断点击的模式；
bool Game::judgeMode(MOUSEMSG mouse)
{
	if (mouse.mkLButton) {
		if (mouse.x >= INFINITE_PX && mouse.x <= INFINITE_PX + MODE_LENGTH && 
			mouse.y >= MODE_PY && mouse.y <= MODE_PY + MODE_WIDE) {
			infiniteMode = true;
		}
		else if(mouse.x>=LEVEL_MODE_PX && mouse.x<=LEVEL_MODE_PX+MODE_LENGTH && 
			mouse.y>=MODE_PY && mouse.y<=MODE_PY+MODE_WIDE ){
			infiniteMode = false;		
		}
	}
	return infiniteMode;
}

void Game::modeBottom()
{
	setlinestyle(PS_SOLID, 5);
	int c = 225;
	//只要没点开始进程就不结束；
	while (judgeS == false) {
		if (infiniteMode == true) {
			if (judgeH == false) {
				//消除圈中的闯关模式
				image.levelBttom();
				c = 225;
			}			
			//圈中无线模式按钮;
			//没有进入游戏界面和没有进入游戏帮助界面才能加载
			//必须写在while判断里；因为进入了while就只能用while判断退出了
			while (infiniteMode == true && judgeS == false && judgeH==false)
			{
				setcolor(RGB(c, 0, 0));
				rectangle(INFINITE_PX + 1, MODE_PY + 1, INFINITE_PX + MODE_LENGTH - 2, MODE_PY + MODE_WIDE - 2);
				c -= 4;
				if (c < 0) {
					c = 255;
				}
				Sleep(20);
			}
		}
		else {
			if (judgeH == false) {
				//消除圈中的无限模式
				image.infiniteBttom();
				//重置颜色
				c = 225;
			}
			//圈中闯关模式按钮
			//没有进入游戏界面和没有进入游戏帮助界面才能加载
			//必须写在while判断里；因为进入了while就只能用while判断退出了
			while (infiniteMode == false && judgeS == false && judgeH == false)
			{
				setcolor(RGB(c, 0, 0));
				rectangle(LEVEL_MODE_PX + 1, MODE_PY + 1, LEVEL_MODE_PX + MODE_LENGTH - 2, MODE_PY + MODE_WIDE - 2);
				c -= 4;
				if (c < 0) {
					c = 255;
				}
				Sleep(20);
			}
		}
	}
	

	ExitThread(0);			//关闭线程；	
}

void Game::scoreWord()
{
	TCHAR s[10];
	//setcolor(RGB(255, 255, 255));
	settextstyle(35, 0, _T("华文新魏"));
	setcolor(RGB(85, 255, 255));//颜色
	//将数字转变成TCHAR类型；
	swprintf_s(s, _T("%d"), score);
	outtextxy(750, 150, _T("当前分数："));
	setcolor(RGB(255,255,0));
	outtextxy(850, 200, s);
}















