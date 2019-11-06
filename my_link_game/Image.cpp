#include "pch.h"
#include "Image.h"
#include <time.h>
#pragma comment(lib,"Winmm.lib")
#include <thread>
#include <iostream>
#include "Music.h"


Image::~Image()
{
}

void Image::drawMap()
{
	//重置记录
	markCount = 0;
	//每次开始时coutImage要重新赋值为0；不然会数组越界
	countImage = 0;

	//重置最大图片数；计数当前图片数；
	/*if (infiniteMode == false) {
		maxImageNumber = INITo_IMAGE_NUMBER + level - 1;
	}
	else {
		maxImageNumber = INFI_IMAGE_NUMBER;
	}*/
	
	backGroundImage(level);
	putimage(0, 0, &bgImage[level-1]);
			

	srand((unsigned)time(NULL));	//用当前时间来做随机种子

	BeginBatchDraw();	//开始批量画图模式；
	int m=0;
	for (int n = 1; n <= mapRow * mapColumn/2; n++) {	
		//把n给m，防止生成随机数时n一直在[1,maxImageNumber]之间，从而出现死循环；
		m = n;
		//如果每种图片能重复2次及其以上；就必须重复两次；
		if ( m>maxImageNumber && m<=maxImageNumber*2) {
			m %= maxImageNumber;
			//当m取余==0，实际应加载maxImageNumer；
			if (m == 0) {
				m = maxImageNumber;
			}
		}
		else if (m > maxImageNumber * 2) {
			m = rand() % maxImageNumber + 1;//生成1到maxImageNumber的随机数；
		}
		Image::numberImage(m);
	}
	
	swapImage();		//交换位置，形成随机放置；
	
	m = 0;
	int n = -1;
	for (int i = 1; i <= mapRow; i++) {
		for (int j = 1; j <= mapColumn; j++) {
			if (m %2==0) {
				m = 0;
				n++;
			} else {
				m = 1;
			}
			putimage(positionX + i * gridSize, positionY + j * gridSize, &imageNumber[n][m]);
			gridAttribute[i][j] = imageAttribute[n][m];
			m++;
		}
	}
	
	//加载暂停和退出按钮；
	imagePause();
	imageExit();

	FlushBatchDraw(); 
	EndBatchDraw();// 结束批量绘制，并执行未完成的绘制任务;不结束batchDraw，后面的画图操作不会执行	

}

void Image::numberImage(int number)
{
	switch (number)
	{
	case 1: {
		//载入后羿的图片。图片属性值为1;
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("后羿"), gridSize, gridSize);
			imageAttribute[countImage][i] = 1;
		}
		countImage++;
		break;
	}
	case 2: {
		//载入妲己的图片。图片属性值为2；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("妲己"), gridSize, gridSize);
			imageAttribute[countImage][i] = 2;
		}
		countImage++;
		break;
	}
	case 3: {
		//载入韩信的图片。图片属性值为3；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("韩信"), gridSize, gridSize);
			imageAttribute[countImage][i] = 3;
		}
		countImage++;
		break;
	}
	case 4: {
		//载入安琪拉的图片。图片属性值为4；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("安琪拉"), gridSize, gridSize);
			imageAttribute[countImage][i] = 4;
		}
		countImage++;
		break;
	}
	case 5: {
		//载入凯的图片。图片属性值为5；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("凯"), gridSize, gridSize);
			imageAttribute[countImage][i] = 5;
		}
		countImage++;
		break;
	}
	case 6: {
		//载入王昭君的图片。图片属性值为6
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("王昭君"), gridSize, gridSize);
			imageAttribute[countImage][i] = 6;
		}
		countImage++;
		break;
	}
	case 7: {
		//载入亚瑟的图片。图片属性值为7；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("亚瑟"), gridSize, gridSize);
			imageAttribute[countImage][i] = 7;
		}
		countImage++;
		break;
	}
	case 8: {
		//载入貂蝉的图片。图片属性值为8；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("貂蝉"), gridSize, gridSize);
			imageAttribute[countImage][i] = 8;
		}
		countImage++;
		break;
	}
	case 9: {
		//载入李白的图片。图片属性值为9；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("李白"), gridSize, gridSize);
			imageAttribute[countImage][i] = 9;
		}
		countImage++;
		break;
	}
	case 10: {
		//载入花木兰的图片。图片属性值为10;
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("花木兰"), gridSize, gridSize);
			imageAttribute[countImage][i] = 10;
			//花木兰图片为jpg，不是png；注意图片格式；
		}
		countImage++;
		break;
	}
	case 11: {
		//载入狄仁杰的图片。图片属性值为11；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("狄仁杰"), gridSize, gridSize);
			imageAttribute[countImage][i] = 11;
		}
		countImage++;
		break;
	}
	case 12: {
		//载入阿轲的图片。图片属性值为12；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("阿轲"), gridSize, gridSize);
			imageAttribute[countImage][i] = 12;
		}
		countImage++;
		break;
	}
	case 13: {
		//载入的宫本武藏图片。图片属性值为13；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("宫本武藏"), gridSize, gridSize);
			imageAttribute[countImage][i] = 13;
		}
		countImage++;
		break;
	}
	case 14: {
		//载入的小乔图片。图片属性值为14；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("小乔"), gridSize, gridSize);
			imageAttribute[countImage][i] = 14;
		}
		countImage++;
		break;
	}
	case 15: {
		//载入的项羽图片。图片属性值为15；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("项羽"), gridSize, gridSize);
			imageAttribute[countImage][i] = 15;
		}
		countImage++;
		break;
	}
	case 16: {
		//载入的蔡文姬图片。图片属性值为16；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("蔡文姬"), gridSize, gridSize);
			imageAttribute[countImage][i] = 16;
		}
		countImage++;
		break;
	}
	case 17: {
		//载入的吕布图片。图片属性值为17；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("PNG"), _T("吕布"), gridSize, gridSize);
			imageAttribute[countImage][i] = 17;
		}
		countImage++;
		break;
	}
	case 18: {
		//载入的雅典娜图片。图片属性值为18；
			//雅典娜图片格式设置为IMAGE了，不是PNG；
		for (int i = 0; i < 2; i++) {
			loadimage(&imageNumber[countImage][i], _T("IMAGE"), _T("雅典娜"), gridSize, gridSize);
			imageAttribute[countImage][i] = 18;
		}
		countImage++;
		break;
	}
	}
}

void Image::swapImage()
{
	int  x;
	int  t;
	IMAGE img;

	//从0—mapRow * mapColumn/4-1与mapRow * mapColumn/2-mapRow * mapColumn/4-1的图片相交；实现最大化交换
	for (int j = 0; j < mapRow*mapColumn / 2; j++) {
		//x需要减一，应为数组从0开始，数组最大下标应该为mapRow * mapColumn /2-1
		x = mapRow * mapColumn / 2 - j-1;
		img = imageNumber[j][0];
		imageNumber[j][0] = imageNumber[x][0];
		imageNumber[x][0] = img;
		t = imageAttribute[j][0];
		imageAttribute[j][0] = imageAttribute[x][0];
		imageAttribute[x][0] = t;
	}

	//交换两次；
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {//imageNumber[j][i]中0,1各交换一次	 
			//从0—mapRow*mapColumn-1与其他随机的图片相交；实现最大化交换
			for (int k = 0; k < mapRow*mapColumn / 2; k++) {
				//x属于[0,mapRow*mapColumn-1]
				x = rand() % (mapRow*mapColumn / 2);
				img = imageNumber[k][j];
				imageNumber[k][j] = imageNumber[x][j];
				imageNumber[x][j] = img;
				t = imageAttribute[k][j];
				imageAttribute[k][j] = imageAttribute[x][j];
				imageAttribute[x][j] = t;
			}
		}
	}
}

//清除画线的函数；
void Image::clearLine()
{
//	backGroundImage(level);//必须要加载一次，不然会没有消除的线
	for (int x = 0; x < mapRow + 2; x++) {
		for (int y = 0; y < mapColumn + 2; y++) {
			if ((gridAttribute[x][y] == 0)) {
				putimage(positionX + gridSize * x, positionY + gridSize * y,
					gridSize, gridSize, &bgImage[level - 1], positionX + gridSize * x,
					positionY + gridSize * y);
			}
		}
	}
}

bool Image::judgeClear()
{
	//设置连线颜色和粗细
	setlinecolor(RGB(255, 128, 0));
	setlinestyle(PS_SOLID, 5);
	//比较大小便于判断
	comparePosition();

	bool judge = false;
	judge = oneLine();
	if (judge == false) {
		judge = twoLine();
		if (judge == false) {
			judge = thereLine();
		}
	}
	return judge;
}

void Image::comparePosition()
{
	if (Image::clickX[0] > Image::clickX[1]) {//判断x坐标大小
		minClickX = Image::clickX[1];
		maxClickX = Image::clickX[0];
	}
	else {//包含了相等
		minClickX = Image::clickX[0];
		maxClickX = Image::clickX[1];
	}
	if (Image::clickY[0] > Image::clickY[1]) {//判断y坐标大小
		minClickY = Image::clickY[1];
		maxClickY = Image::clickY[0];
	}
	else {//包含了相等
		minClickY = Image::clickY[0];
		maxClickY = Image::clickY[1];
	}
}

bool Image::oneLine()
{
	bool one = false;
	if (clickX[0] == clickX[1]) {
		one = true;
		if (maxClickY - minClickY > 1) {//相挨着的直接为真
			for (int y = minClickY + 1; maxClickY > y; y++) {
				//对于一个变量的初始值要被多次使用；可以在循环内定义一个循环变量与之相等；
				//减少恢复初始值的步骤；
				if (gridAttribute[minClickX][y] != 0) {//！=0表示之间有图片间隔
					one = false;
					break;
				}
			}
		}
		if (one == true) {//画消除连线
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
				positionX + clickX[0] * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
		}
	}

	if (clickY[0] == clickY[1]) {
		one = true;
		if (maxClickX - minClickX > 1) {
			for (int x = minClickX + 1; maxClickX > x; x++) {
				if (gridAttribute[x][minClickY] != 0) {
					one = false;
					break;
				}
			}
		}
		if (one) {//画消除连线;判断放在里面执行；否则第一次判断成功也会执行
			line(positionX + minClickX * gridSize + gridSize / 2, positionY + clickY[0] * gridSize + gridSize / 2,
				positionX + maxClickX * gridSize + gridSize / 2, positionY + clickY[0] * gridSize + gridSize / 2);

		}
	}
	return one;
}

bool Image::twoLine()
{
	bool two = false;//开始为假，进入判断开始为真；防止不满足判断条件而默认为真

	if ((clickX[0] > clickX[1] && clickY[0] > clickY[1]) || (clickX[0] < clickX[1] && clickY[0] < clickY[1])) {
		//第一组数据和第二组数组构成左上、右下的关系；
		two = true;
		for (int x = minClickX + 1; x <= maxClickX; x++) {//第一次判断，从左上角开始先行后列
			//+1防止判断本身
			if (gridAttribute[x][minClickY] != 0) {
				two = false;
				break;
			}
		}
		if (two == true) {//为真才执行，防止漏掉上一次的判断；
			for (int y = minClickY + 1; y < maxClickY; y++) {
				//+1减少循环次数；
				if (gridAttribute[maxClickX][y] != 0) {
					two = false;
					break;
				}
			}
		}
		if (two == true) {
			//画行
			line(positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
				positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
			//画列
			line(positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
				positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);

		}
		else {//第一次不成功，才走第二次判断；不加判断会两个都走，导致只要第二个不成功就判断false
			two = true;
			for (int y = minClickY + 1; y <= maxClickY; y++) {//第二次判断，从左上角开始先列后行
				if (gridAttribute[minClickX][y] != 0) {
					two = false;
					break;
				}
			}
			if (two == true) {
				for (int x = minClickX + 1; x < maxClickX; x++) {
					if (gridAttribute[x][maxClickY] != 0) {
						two = false;
						break;
					}
				}
			}
			if (two == true) {
				//画行
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
					positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
				//画列
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
					positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);

			}
		}
	}
	if ((clickX[0]<clickX[1] && clickY[0]>clickY[1]) || (clickX[0] > clickX[1] && clickY[0] < clickY[1])) {
		//第一组和第二组构成左下、右上的关系；true
		two = true;
		for (int x = minClickX + 1; x <= maxClickX; x++) {//第一次判断，从左下角开始先行后列
			//+1防止判断本身
			if (gridAttribute[x][maxClickY] != 0) {
				two = false;
				break;
			}
		}
		if (two == true) {
			for (int y = maxClickY - 1; y > minClickY; y--) {
				//-1减少循环次数；
				if (gridAttribute[maxClickX][y] != 0) {
					two = false;
					break;
				}
			}
		}
		if (two == true) {
			//画行
			line(positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
				positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
			//画列
			line(positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
				positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);

		}
		else {//第一次不成功，才走第二次判断；不加判断会两个都走，导致只要第二个不成功就判断false	
			two = true;//变真，开始判断；
			for (int y = maxClickY - 1; y >= minClickY; y--) {//第二次判断，从左下角开始先列后行
				if (gridAttribute[minClickX][y] != 0) {
					two = false;
					break;
				}
			}
			if (two == true) {
				for (int x = minClickX + 1; x < maxClickX; x++) {
					if (gridAttribute[x][minClickY] != 0) {
						two = false;
						break;
					}
				}
			}
			if (two == true) {//少些一个=号啊！！！，注意啊，判断相等为==（两个等号啊!!)
				//画行
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
					positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
				//画列
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
					positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
			}

		}
	}
	return two;
}

bool Image::thereLine()
{
	bool there = false;
	if (clickX[0] == clickX[1]) {//同列位置;判断要==啊；注意
		thereLineLeft(there);//向左走,"["形状	
		if (there == false) {
			thereLineRight(there);//向右走;"]"形状
		}
	}
	if (clickY[0] == clickY[1]) {//同行
		thereLineUp(there);//向上走;"∩"形状
		if (there == false) {
			thereLineDown(there);//向下走;"∪"形状
		}
	}
	if ((clickX[0] > clickX[1] && clickY[0] > clickY[1]) || (clickX[0] < clickX[1] && clickY[0] < clickY[1])) {
		//第一组数据和第二组数组构成左上、右下的关系；

		//先开始向坐标内进行判断
		//左上角先从行走再列再行 "￣｜__"形
		for (int x = minClickX + 1; x < maxClickX; x++) {//走行
			//不用包括最大的X，因为twoLine（）已经判断过了
			there = true;//每次循环开始都要为真
			if (gridAttribute[x][minClickY] != 0) {
				there = false;
				break;
			}
			for (int y = minClickY + 1; y <= maxClickY; y++) {//走列
				if (gridAttribute[x][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {//为真才开始，保证正确
				for (int x1 = x; x1 < maxClickX; x1++) {//走行，继续从x坐标开始判断;
					//算法的代码实现，虽然两个步骤很相似；不相同的话；最好还是自己手打出来
					//复制粘贴容易一些地方没改过来，调试最后比写代码的时间还要长
					//不能+1减少步骤；万一中间只隔了一个就GG了
					if (gridAttribute[x1][maxClickY] != 0) {
						there = false;
						break;
					}
				}
			}
			if (there == true) {
				//画线
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
					positionX + x * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
				line(positionX + x * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
					positionX + x * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
				line(positionX + x * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
					positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
				//记录

				break;//一次成功就行了
			}
		}
		if (there == false) {//左上角先从列走再行再列 "┗┓"形
			for (int y = minClickY + 1; y < maxClickY; y++) {//走列
				there = true;//每次循环开始都要为真
				if (gridAttribute[minClickX][y] != 0) {
					there = false;
					break;
				}
				for (int x = minClickX + 1; x <= maxClickX; x++) {//走行
					if (gridAttribute[x][y] != 0) {
						there = false;
						break;
					}
				}
				if (there == true) {//为真才开始，保证正确
					for (int y1 = y; y1 < maxClickY; y1++) {//走列，继续从y坐标开始判断
						if (gridAttribute[maxClickX][y1] != 0) {
							there = false;
							break;
						}
					}
				}
				if (there == true) {
					//画线
					line(positionX + minClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
						positionX + minClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2);
					line(positionX + minClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2,
						positionX + maxClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2);
					line(positionX + maxClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2,
						positionX + maxClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
					//记录

					break;//一次成功就行了
				}
			}
		}
		//开始向坐标外进行判断；
		if (there == false) {
			there = true;
			for (int x = maxClickX - 1; x >= minClickX; x--) {//右下角向左走到同列
				//判断x最大向左到x最小之间是否是空的
				if (gridAttribute[x][maxClickY] != 0) {
					there = false;
					break;//有图就不行
				}
			}
			if (there == true) {//老是忘记一个=，两个==是判断！！！！！！！！
				thereLineLeft(there);//同列继续向左走,"["形状
			}
		}

		if (there == false) {
			there = true;
			for (int x = minClickX + 1; x <= maxClickX; x++) {//左上角向右走到同列
			//判断x最大向左到x最小之间是否是空的
				if (gridAttribute[x][minClickY] != 0) {
					there = false;
					break;//有图就不行
				}
			}
			if (there == true) {
				thereLineRight(there);//同列继续向右走;"]"形状
			}
		}

		if (there == false) {
			there = true;//别忘记了，每次进入判断要赋值为true!!!!!!
			for (int y = maxClickY - 1; y >= minClickY; y--) {//右下角向上走到同行
				if (gridAttribute[maxClickX][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineUp(there);//同行继续向上走;"∩"形状
			}
		}

		if (there == false) {//左上角向下走到同行
			there = true;//别忘记了，每次进入判断要赋值为true!!!!!!
			for (int y = minClickY + 1; y <= maxClickY; y++) {
				if (gridAttribute[minClickX][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineDown(there);//向下走;"∪"形状
			}
		}
	}
	if ((clickX[0]<clickX[1] && clickY[0]>clickY[1]) || (clickX[0] > clickX[1] && clickY[0] < clickY[1])) {
		//第一组和第二组构成左下、右上的关系；

		//开始向坐标内进行判断
		//左下角先从行走再列再行 "__｜￣"形
		for (int x = minClickX + 1; x < maxClickX; x++) {//走行
			there = true;//每次循环开始都要为真
			if (gridAttribute[x][maxClickY] != 0) {
				there = false;
				break;
			}
			for (int y = maxClickY - 1; y >= minClickY; y--) {//走列
				if (gridAttribute[x][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {//为真才开始，保证正确
				for (int x1 = x; x1 < maxClickX; x1++) {//走行，继续从x坐标开始判断
					if (gridAttribute[x1][minClickY] != 0) {
						there = false;
						break;
					}
				}
			}
			if (there == true) {
				//画线
				line(positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
					positionX + x * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2);
				line(positionX + x * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
					positionX + x * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
				line(positionX + x * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2,
					positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
				//记录

				break;//一次成功就行了
			}
		}
		if (there == false) {//左下角先从列走再行再列；"┏┛"形
			for (int y = maxClickY - 1; y > minClickY; y--) {//走列,twoLine判断失败，矩形角肯定不能过
				there = true;//每次循环开始都要为真
				if (gridAttribute[minClickX][y] != 0) {
					there = false;
					break;
				}
				for (int x = minClickX + 1; x <= maxClickX; x++) {//走行
					if (gridAttribute[x][y] != 0) {
						there = false;
						break;
					}
				}
				if (there == true) {//为真才开始，保证正确
					for (int y1 = y; y1 > minClickY; y1--) {//走列，继续从y坐标开始判断
						if (gridAttribute[maxClickX][y1] != 0) {
							there = false;
							break;
						}
					}
				}
				if (there == true) {
					//画线
					line(positionX + minClickX * gridSize + gridSize / 2, positionY + maxClickY * gridSize + gridSize / 2,
						positionX + minClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2);
					line(positionX + minClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2,
						positionX + maxClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2);
					line(positionX + maxClickX * gridSize + gridSize / 2, positionY + y * gridSize + gridSize / 2,
						positionX + maxClickX * gridSize + gridSize / 2, positionY + minClickY * gridSize + gridSize / 2);
					//记录

					break;//一次成功就行了
				}
			}

		}

		//开始向坐标外进行判断；
		if (there == false) {
			there = true;
			for (int x = maxClickX - 1; x >= minClickX; x--) {//右上角向左走到同列
				if (gridAttribute[x][minClickY] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineLeft(there);//同列继续向左走,"["形状
			}
		}
		if (there == false) {
			there = true;//别忘记了，每次进入判断要赋值为true!!!!!!
			for (int x = minClickX + 1; x <= maxClickX; x++) {//向右走到同列
				if (gridAttribute[x][maxClickY] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineRight(there);//同列继续向右走;"]"形状
			}
		}
		if (there == false) {
			there = true;//别忘记了，每次进入判断要赋值为true!!!!!!
			for (int y = maxClickY - 1; y >= minClickY; y--) {//向上走到同行
				if (gridAttribute[minClickX][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineUp(there);//同行继续向上走;"∩"形状
			}
		}
		if (there == false) {
			there = true;//别忘记了，每次进入判断要赋值为true!!!!!!
			for (int y = minClickY + 1; y <= maxClickY; y++) {//向下走到同行
				if (gridAttribute[maxClickX][y] != 0) {
					there = false;
					break;
				}
			}
			if (there == true) {
				thereLineDown(there);//向下走;"∪"形状
			}
		}
	}
	return there;
}

void Image::thereLineLeft(bool & there)
{
	for (int x = minClickX - 1; x >= 0; x--) {//向左走,"["形状
		there = true;
		if (gridAttribute[x][minClickY] != 0 || gridAttribute[x][maxClickY] != 0) {
			//两边只要有一边有图，则为false！！！！；不是&&
			there = false;
			break;//最近的不行（必经之路），后面的肯定不行
		}
		for (int y = minClickY + 1; y < maxClickY; y++) {
			if (gridAttribute[x][y] != 0) {
				there = false;
				break;
			}
		}
		if (there == true) {//表明有一条通路可行,成功的列通路的坐标为x
			//连线；固定一组的click坐标到x坐标连线和x列通路的连线
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2);
			line(positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);
			line(positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);


			break;
		}
	}
}



void Image::thereLineRight(bool &there)
{
	for (int x = maxClickX + 1; x < mapRow + 2; x++) {//向右走;"]"形状，0—mapRow+1不包括mapRow+2；
		there = true;
		if (gridAttribute[x][minClickY] != 0 || gridAttribute[x][maxClickY] != 0) {
			there = false;
			break;
		}
		for (int y = minClickY + 1; y < maxClickY; y++) {
			if (gridAttribute[x][y] != 0) {
				there = false;
				break;
			}
		}
		if (there == true) {//表明有一条通路可行
			//连线；固定一组的click坐标到x坐标连线和x列通路的连线
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2);
			line(positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);
			line(positionX + x * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);

			break;
		}
	}
}

void Image::thereLineUp(bool & there)
{
	for (int y = minClickY - 1; y >= 0; y--) {//向上走;"∩"形状
		there = true;//每次循环要恢复为真
		if (gridAttribute[minClickX][y] != 0 || gridAttribute[maxClickX][y] != 0) {
			there = false;
			break;
		}
		for (int x = minClickX; x < maxClickX; x++) {
			if (gridAttribute[x][y] != 0) {
				there = false;
				break;
			}
		}
		if (there == true) {//表明有一条通路可行
			//连线；固定一组的click坐标到y坐标连线和y行通路的连线
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2);
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2);
			line(positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);
			//记录

			break;
		}
	}
}

void Image::thereLineDown(bool & there)
{
	for (int y = maxClickY + 1; y < mapColumn + 2; y++) {//向下走;"∪"形状
		there = true;//每次循环要恢复为真
		if (gridAttribute[minClickX][y] != 0 || gridAttribute[maxClickX][y] != 0) {
			there = false;
			break;
		}
		for (int x = minClickX + 1; x < maxClickX; x++) {
			if (gridAttribute[x][y] != 0) {
				there = false;
				break;
			}
		}
		if (there == true) {//表明有一条通路可行
			//连线；固定一组的click坐标到y坐标连线和y行通路的连线
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * clickY[0] + gridSize / 2,
				positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2);
			line(positionX + clickX[0] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2);
			line(positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * y + gridSize / 2,
				positionX + clickX[1] * gridSize + gridSize / 2, positionY + gridSize * clickY[1] + gridSize / 2);
			//记录

			break;
		}
	}
}

//判断图片是否全部消除；能否进入了下一关；
bool Image::judgePass()
{
	pass = false;
	int allGrid = 0;
	for (int x = 1; x <= mapRow; x++) {
		for (int y = 1; y <= mapColumn; y++) {
			allGrid = gridAttribute[x][y];
			if (allGrid != 0) {//减少执行次数
				break;
			}
		}
		if (allGrid != 0) {//减少执行次数
			break;
		}
	}
	if (allGrid == 0) {
		pass = true;
		
	}
	return pass;
}


void Image::gridJudgement(MOUSEMSG mouse) 
{	
	//每次判断开始前，重置为false
	clearOne = false;
	if (mouse.mkLButton) {// 鼠标左键是否按下
		if ((mouse.x >= positionX+gridSize && mouse.x <= positionX + gridSize * (mapRow+1))&&
			(mouse.y >= positionY+gridSize && mouse.y <= positionY + gridSize * (mapColumn+1))) {
			//判断鼠标是否在所画的地图内（不包括边界）
			int x = (int)((mouse.x - positionX)/gridSize);
			//计算所在格子的x坐标,原点为（0,0）,image从（1,1）开始
			int y = (int)((mouse.y - positionY) / gridSize);//计算所在格子的y坐标
			if (gridAttribute[x][y]!= 0) {//点击为空格不算

				clickAttribute[markCount] = gridAttribute[x][y];
				clickX[markCount] = x;
				clickY[markCount] = y;
				//画线颜色
				setcolor(RGB(85, 255, 255));
				setlinestyle(PS_SOLID, 3);
				//选中的标记
				rectangle(positionX + gridSize * clickX[markCount]+2, 
					positionY + gridSize * clickY[markCount]+2,
				positionX + gridSize * clickX[markCount] + gridSize-2, 
					positionY + gridSize * clickY[markCount] + gridSize-2);
	
				if (markCount == 1) {
					//如果两次点击的位置为同一个
					if (clickX[0] == clickX[1] && clickY[0] == clickY[1]) {
						//markCount每次要＋1，赋值-1使ClickX、Y数组从0开始;
						markCount =-1;
						//清除选框；两次选择相当于取消
						//imageNumber[i][j]与x，y的关系为
						//(x-1)*mapColumn+y-1=i*2+j;
						putimage(positionX + clickX[0] * gridSize, positionY + clickY[0] * gridSize,
							&imageNumber[((clickX[0]-1)*mapColumn+clickY[0]-1)/2]
							[((clickX[0] - 1)*mapColumn+clickY[0]-1)%2]);

					} //如果位置不同且记录的图片相等
					else if (clickAttribute[0] == clickAttribute[1]) {

						if (judgeClear() == true) {
							//创造一个线程；thread引用类外成员函数要类和对象的函数
							Music music1;
							std::thread t(&Music::clearMusic, &music1);
							t.detach();				//播放清除音乐；

							clearOne = true;

							backGroundImage(level);//必须要加载一次，不然会没有消除的线

							//停止一下；防止清除画线太快；肉眼观察不到
							Sleep(150);
							//消除第一张记录图片
							putimage(positionX + gridSize * clickX[0], positionY + gridSize * clickY[0],
							gridSize, gridSize, &bgImage[level-1], positionX + gridSize * clickX[0], 
								positionY + gridSize * clickY[0]);
							
							//消除第二张记录图片
							putimage(positionX + gridSize * clickX[1], positionY + gridSize * clickY[1],
							gridSize, gridSize, &bgImage[level-1], positionX + gridSize * clickX[1], 
								positionY + gridSize * clickY[1]);
							

							//消除连接的直线
							clearLine();
							//消除图片要消除格子属性；防止鼠标点击已消除的格子记录信息，而出现错误
							gridAttribute[clickX[0]][clickY[0]] = 0;
							gridAttribute[clickX[1]][clickY[1]] = 0;
							//markCount每次要＋1，故为使countClick[]=0，则赋值为-1；
							markCount = -1;							
						}//记录的图片不能消除
						else {
							//markCount每次要＋1，故为使countClick==0，则赋值为-1；
							markCount = -1;
							//清除选框
							for (int i = 0; i < 2; i++) {
								putimage(positionX + clickX[i] * gridSize, positionY + clickY[i] * gridSize,
									&imageNumber[((clickX[i] - 1)*mapColumn + clickY[i] - 1) / 2]
									[((clickX[i] - 1)*mapColumn + clickY[i] - 1) % 2]);
							}

						}
					} else {//因为两组图片记录不为同一个，且markCount==1时判断，
						//故要赋值给第一组记录(即markCount==0时）

						//清除选框
						for (int i = 0; i < 2; i++) {
							putimage(positionX + clickX[i] * gridSize, positionY + clickY[i] * gridSize,
								&imageNumber[((clickX[i] - 1)*mapColumn + clickY[i] - 1) / 2]
								[((clickX[i] - 1)*mapColumn + clickY[i] - 1) % 2]);
						}
						//记录次数为0次
						markCount = -1;	
					}
				}
				markCount++;
			}
		}
	}
	
}




void Image::imageVictory()					//胜利的图片
{
	IMAGE victoryImage;
	loadimage(&victoryImage, _T("PNG"), _T("VICTORY"), WINDOW_WIDE, WINDOW_HEIGTH);
	putimage(0, 0, &victoryImage);
}

void Image::imageDefeat()
{
	IMAGE defeatImage;
	loadimage(&defeatImage, _T("PNG"), _T("DEFEAT"), WINDOW_WIDE, WINDOW_HEIGTH);
	putimage(0, 0, &defeatImage);

}

void Image::backGroundImage(int number)
{
	switch (number)
	{
	case 1: {
		loadimage(&bgImage[0], _T("IMAGE"), _T("星空梦想-鲁班七号"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 2: {
		loadimage(&bgImage[1], _T("IMAGE"), _T("狗年限定皮肤壁纸-后羿杨戬"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 3: {
		loadimage(&bgImage[2], _T("IMAGE"), _T("神奇女侠-雅典娜"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 4: {
		loadimage(&bgImage[3], _T("IMAGE"), _T("夏侯惇-乘风破浪"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 5: {
		loadimage(&bgImage[4], _T("IMAGE"), _T("花木兰-青春决赛季"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 6: {
		loadimage(&bgImage[5], _T("IMAGE"), _T("程咬金—功夫厨神"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 7: {
		loadimage(&bgImage[6], _T("IMAGE"), _T("甄姬-游园惊梦"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 8: {
		loadimage(&bgImage[7], _T("IMAGE"), _T("孙悟空-至尊宝"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 9: {
		loadimage(&bgImage[8], _T("IMAGE"), _T("伽罗·花见巫女"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 10: {
		loadimage(&bgImage[9], _T("IMAGE"), _T("韩信-白龙吟"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 11: {
		loadimage(&bgImage[10], _T("IMAGE"), _T("后羿-黄金射手座"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 12: {
		loadimage(&bgImage[11], _T("IMAGE"), _T("李白-凤求凰"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	case 13: {
		loadimage(&bgImage[12], _T("IMAGE"), _T("武陵仙君-诸葛亮"),
			WINDOW_WIDE, WINDOW_HEIGTH);

		break;
	}
	}
}

//第0关，即游戏开始界面；
void Image::gameStartImage()
{
	IMAGE imgBegin;//载入开始的背景图片
	loadimage(&imgBegin, _T("PNG") ,_T("王者开始游戏界面"), 1000, 540);
	//没找到什么好的图片，故用的自己的手机截图
	putimage(0, 0, &imgBegin);
	//圈出游戏帮助；
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 3);
	circle(962, 81, 24);
	
	infiniteBttom();
	levelBttom();
}

void Image::finalVictoryImage()
{
	IMAGE finalVictory;
	loadimage(&finalVictory, _T("IMAGE"), _T("梦奇-胖达荣荣"), WINDOW_WIDE, WINDOW_HEIGTH);
	putimage(0, 0, &finalVictory);

}


void Image::imagePause()
{
	IMAGE imgP;
	loadimage(&imgP, _T("PNG"),_T("pause"), PAUSE_SIZE, PAUSE_SIZE);

	putimage(PAUSE_PX, PAUSE_PY, &imgP);
}
//游戏开始界面；
void Image::imageContinue()
{
	IMAGE imgS;
	loadimage(&imgS, _T("PNG"), _T("start"), PAUSE_SIZE, PAUSE_SIZE);

	putimage(PAUSE_PX, PAUSE_PY, &imgS);
}

void Image::imageExit()
{

	IMAGE imgE;
	loadimage(&imgE, _T("PNG"), _T("exit"), EXIT_SIZE, EXIT_SIZE);

	putimage(EXIT_PX, EXIT_PY, &imgE);

}

//通关按钮
void Image::passBottom()
{
	IMAGE passBottom;
	loadimage(&passBottom, _T("IMAGE"), _T("王者"), PASS_BOTTOM_SIZE, PASS_BOTTOM_SIZE);
	//将通关按钮画在右下角；
	putimage(WINDOW_WIDE-PASS_BOTTOM_SIZE, WINDOW_HEIGTH-PASS_BOTTOM_SIZE, &passBottom);
}

//闯关模式按钮
void Image::levelBttom()
{
	IMAGE imgL;
	loadimage(&imgL, _T("PNG"), _T("闯关模式"), MODE_LENGTH, MODE_WIDE);
	putimage(LEVEL_MODE_PX, MODE_PY, &imgL);
}

//无线模式按钮
void Image::infiniteBttom()
{
	IMAGE imgI;
	loadimage(&imgI, _T("PNG"), _T("无限模式"), MODE_LENGTH, MODE_WIDE);
	putimage(INFINITE_PX, MODE_PY, &imgI);
}

bool Image::getClearOne()
{
	return clearOne;
}

int Image::getLevel()
{
	return level;
}

void Image::initMaxImageNumber()
{
	maxImageNumber = INITo_IMAGE_NUMBER;
}

void Image::maxImageNumberPlus()
{
	maxImageNumber++;
}

void Image::levelPlus()
{
	//通关，关卡数加1；
	level++;

}

void Image::initLevel()
{
		level = 1;
}




