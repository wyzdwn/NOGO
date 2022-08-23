#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<iostream>
#include<stdio.h>
#include<tchar.h>
#include<string>
#include<cstring>
#include<time.h>
#include<vector>
#include<stdlib.h>
#include<fstream>
#include<windows.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;
bool ok1[100] = { 0 };//双方都能下的位置的数组
bool yan1[9][9] = { 0 };//AI已成的眼
int board[10][10] = { 0 };//棋盘，该棋盘用来记录落子，下标范围：0-8，-1白棋，1黑棋，0无 
bool airvisit[9][9];//用来判断是否考虑过这一位置（air函数是否操作过这一格） 
const int cx[4] = { -1,0,1,0 };
const int cy[4] = { 0,-1,0,1 };

bool flag1 = 0;//以下变量用来实现高亮标识
bool leave = 0;
bool biao[9][9] = { 0 };
bool end1 = 0;
bool saveflag = 0;
bool saveleave = 0;
bool quitflag = 0;
bool quitleave = 0;
bool huiqiflag = 0;
bool huiqileave = 0;
bool music1flag = 0;
bool music2flag = 0;
bool music3flag = 0;
bool music1leave = 0;
bool music2leave = 0;
bool music3leave = 0;
bool music1ing = 0;
bool music2ing = 0;
bool music3ing = 0;
bool tipflag = 0;
bool tipleave = 0;
bool fanhuiflag = 0;
bool fanhuileave = 0;
bool stopflag = 0;
bool stopleave = 0;
bool stoping = 0;

int hei[90] = { 0 }, bai[90] = { 0 };//记录黑白棋每一步的落子位置

int huihe;
bool inboard(int x, int y) { return x >= 0 && y >= 0 && x < 9 && y < 9; }//判断是否在棋盘上
void game(int mode,int col);//游戏界面
void begin();//开始界面

void choose()//选择黑白方
{
	IMAGE back;
	initgraph(1000, 650);
	loadimage(NULL, _T("开始界面.jpg"), 1000, 650);
	setfillcolor(RGB(192, 192, 192));
	setbkmode(TRANSPARENT);
	RECT nogo = { 100,100,700,600 };//游戏标题
	setcolor(LIGHTCYAN);
	settextstyle(150, 90, _T("Colonna MT"));
	drawtext(_T("NOGO"), &nogo, DT_CENTER);
	settextstyle(150, 100, _T("楷体"));
	drawtext(_T("\n不围棋"), &nogo, DT_CENTER);
	settextstyle(250, 70, _T("Colonna MT"));
	nogo.top += 280;
	drawtext(_T("AI"), &nogo, DT_CENTER);

	fillrectangle(800, 100, 970, 530);//选择菜单
	nogo = { 800,150,970,600 };
	settextstyle(30, 20, _T("楷体"));
	setcolor(BLACK);
	drawtext(_T("黑方先手"), &nogo, DT_CENTER);//top=150,bottom=180
	nogo.top += 150;
	drawtext(_T("白方后手"), &nogo, DT_CENTER);//top=300,bottom=330
	nogo.top += 150;
	drawtext(_T("返回"), &nogo, DT_CENTER);//top=450,bottom=480
	


	MOUSEMSG m;//鼠标
	bool flag = 0;
	bool leave = 0;
	int biao[3] = { 0 };
	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		flag = 0;
		for (int i = 0; i <= 2; i++)
		{
			if (m.x > 800 && m.x < 970 && m.y>150 + i * 150 && m.y < 180 + i * 150)
			{
				setlinecolor(LIGHTCYAN);
				rectangle(801, 150 + i * 150, 969, 180 + i * 150);
				flag = 1;
				biao[i] = 1;
				break;
			}
		}
		if (!flag) leave = 1;
		if (leave && flag)
		{
			setlinecolor(RGB(192, 192, 192));
			for (int i = 0; i <= 2; i++)
				rectangle(801, 150 + i * 150, 969, 180 + i * 150);
			memset(biao, 0, sizeof(biao));
			flag = 0;
			leave = 0;
		}
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (int i = 0; i <= 2; i++)
				if (biao[i])
					switch (i)
					{
					case 0:game(2,1); return;
					case 1:game(2,-1); return;
					case 2:begin(); return;
					}
		}
	}
}
void begin()//开始界面
{
	IMAGE back;
	initgraph(1000, 650);
	loadimage(NULL, _T("开始界面.jpg"),1000,650);
	setbkmode(TRANSPARENT);
	RECT nogo = { 100,100,700,400 };//游戏标题
	setcolor(RGB(255, 215, 0));
	settextstyle(100, 100, _T("楷体"));
	drawtext(_T("NOGO"), &nogo, DT_CENTER);
	settextstyle(150, 100, _T("楷体"));
	drawtext(_T("\n不围棋"), &nogo, DT_CENTER);

	setcolor(BLACK);
	setfillcolor(RGB(192, 192, 192));
	fillrectangle(800, 100, 970, 530);//选择菜单
	nogo = { 800,150,970,600 };
	settextstyle(30, 20,_T("楷体"));
	drawtext(_T("双人对战"), &nogo, DT_CENTER);//top=150,bottom=180
	nogo.top += 100;
	drawtext(_T("人机对战"), &nogo, DT_CENTER);//top=250,bottom=280
	nogo.top += 100;
	drawtext(_T("读取游戏"), &nogo, DT_CENTER);//top=350,bottom=380
	nogo.top += 100;
	drawtext(_T("退出游戏"), &nogo, DT_CENTER);//top=450,bottom=480


	mciSendString(_T("open 标题界面.mp3 alias m"),0,0,0);
	mciSendString(_T("play m repeat"), 0, 0, 0);
	


	MOUSEMSG m;//鼠标
	bool flag = 0;
	bool leave = 0;
	int biao[4] = { 0 };
	while (true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();
		flag = 0;
		for (int i = 0; i <= 3; i++)
		{
			if (m.x > 800&&m.x<970&&m.y>150+i*100&&m.y<180+i*100)
			{
				setlinecolor(RED);
				rectangle(801, 150+i*100,969,180+i*100);
				flag = 1;
				biao[i]= 1;
				break;
			}
		}
		if (!flag) leave = 1;
		if (leave && flag)
		{
			setlinecolor(RGB(192, 192, 192));
			for (int i = 0; i <= 3; i++)
					rectangle(801,  150+i*100,969,180+i*100);
			memset(biao, 0, sizeof(biao));
			flag = 0;
			leave = 0;
		}
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			
			for (int i = 0; i <= 4; i++)
				if (biao[i])
					switch (i)
					{
					case 0: game(1, 0); return;
					case 1:choose(); return;
					case 2: game(3, 0); return;
					case 3:closegraph(); return;
					}
		}
	}
}
bool air(int x, int y)//判断还有没有气，true为有气 
{
	airvisit[x][y] = 1;
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		int dx = x + cx[i], dy = y + cy[i];
		if (inboard(dx, dy))
		{
			if (board[dx][dy] == 0) flag = true;
			else if (board[dx][dy] == board[x][y] && !airvisit[dx][dy])
				if (air(dx, dy))
					flag = true;
		}
	}
	return flag;
}
bool ok(int x, int y, int i)//是否可落子，true可落，i是下棋方，1是黑棋，-1是白棋 
{
	if (board[x][y]) return false;//已有子落在上面
	board[x][y] = i;//先落子在上面，然后再看看会不会吃子或被吃 
	memset(airvisit, 0, sizeof(airvisit));
	if (!air(x, y))//被吃 
	{
		board[x][y] = 0;
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		int dx = x + cx[i], dy = y + cy[i];
		if (inboard(dx, dy))
		{
			if (board[dx][dy] && !airvisit[dx][dy])//吃子 
				if (!air(dx, dy))
				{
					board[x][y] = 0;//恢复（因为此时还没落子）
					return false;
				}
		}
	}
	board[x][y] = 0;//恢复（因为此时还没落子） 
	return true;
}
bool yan(int x, int y, int col,int mode)//下在x，y处会不会成眼，true是会 
{
	for (int dir = 0; dir < 4; dir++)
	{
		int dx = x + cx[dir], dy = y + cy[dir];
		if (!ok(dx, dy, col == 1 ? -1 : 1) || !inboard(dx, dy)) continue;//这里已是一个眼或超出边界 
		board[x][y] = col;
		if (!board[dx][dy] && !ok(dx, dy, col == 1 ? -1 : 1) && !yan1[dx][dy])
		{
			board[x][y] = 0;
			if (mode)yan1[dx][dy] = 1;
			return true;
		}
		board[x][y] = 0;
	}
	return false;
}
int robot(int nowplayer,int mode)//mode 1 AI模式 0提示模式
{
	memset(ok1, 0, sizeof(ok1));
	vector<int> oklist, alloklist, me;//可落子位置的集合,以及双方都可落子位置的集合 
	for (int i = 0; i < 9 && !flag1; i++)
		for (int j = 0; j < 9 && !flag1; j++)
		{
			if (ok(i, j, nowplayer))
			{
				oklist.push_back(i * 9 + j);
				if (yan(i, j, nowplayer,mode))
					return i * 9 + j;
				if (ok(i, j, nowplayer == 1 ? -1 : 1))
				{
					alloklist.push_back(i * 9 + j);
					ok1[i * 9 + j] = 1;
				}
				else me.push_back(i * 9 + j);
			}
		}
	if (oklist.size() == 0)
		return 100;//100表示结束
	for (int j = 0; j < 9 && !flag1; j++)//防止被破眼 
		for (int i = 0; i < 9 && !flag1; i++)
			if (ok1[i * 9 + j])
			{
				int n = me.size();
				board[i][j] = nowplayer;
				for (int k = 0; k < n; k++)
				{
					int x1 = me[k] / 9;
					int y1 = me[k] % 9;
					if (!ok(x1, y1, nowplayer))//敌方落在该处后我方损失一个眼
					{
						board[i][j] = 0;
						return i * 9 + j;
					}
				}
				board[i][j] = 0;
			}
	
	for (int i = 0, j = 1; i <= 8; i++)
	{
		if (ok1[i * 9 + j])
			return i * 9 + j;
		j = j == 1 ? 0 : 1;
	}
	
	for (int i = 2, j = 7; i <= 8; i++)
	{
		if (ok1[j * 9 + i])
			return j * 9 + i;
		j = j == 7 ? 8 : 7;
	}
	
	for (int i = 6, j = 7; i >= 0; i--)
	{
		if (ok1[i * 9 + j])
			return i * 9 + j;
		j = j == 8 ? 7 : 8;
	}
	
	for (int i = 6, j = 1; i >= 0; i--)
	{
		if (ok1[j * 9 + i])
			return j * 9 + i;
		j = j == 1 ? 0 : 1;
	}
	
	srand((unsigned)time(NULL));
	int result = 0;
	if (alloklist.size() == 0)result = oklist[rand() % oklist.size()];
	else result = alloklist[rand() % alloklist.size()];
	int i = result / 9, j = result % 9;
	return i * 9 + j;
}
void game(int mode,int human)//游戏界面,mode是模式,1为双人对战，2为人机对战,3为读取,col是人类方,1黑,-1白,0无
{
	mciSendString(_T("close m"), 0, 0, 0);
	mciSendString(_T("open 背景音1.mp3 alias music1"), NULL, 0, NULL);
	mciSendString(_T("open 背景音2.mp3 alias music2"), NULL, 0, NULL);
	mciSendString(_T("open 背景音3.mp3 alias music3"), NULL, 0, NULL);
	music1ing = 0;
	music2ing = 0;
	music3ing = 0;
	/*绘制界面*/
	int nowplayer = 1;//黑方先下
	memset(hei, -1, sizeof(hei));
	memset(bai, -1, sizeof(bai));
	initgraph(1000, 650);
	const int zongcolor = 0x005498;//棕色
	loadimage(NULL, _T("背景.jpg"), 1000, 650);
	setfillcolor(zongcolor);
	fillrectangle(79, 79, 521, 521);

	

	setfillcolor(zongcolor);
	setcolor(BLACK); //设置绘图笔颜色为黑色
	/*画横线*/
	for (int x = 100; x <= 500; x += 50) line(100, x, 500, x);
	/*画竖线*/
	for (int x = 100; x <= 500; x += 50) line(x, 100, x, 500);
	/*加粗边框线*/
	line(99, 99, 501, 99);
	line(99, 501, 501, 501);
	line(99, 99, 99, 501);
	line(501, 99, 501, 501);
	/*--end--*/


	int y = 250; int x = 250; int r = 3;// 中心点加粗
	setfillcolor(BLACK);
	fillcircle(x +50, y + 50, r);


	setbkcolor(WHITE);
	setfillcolor(WHITE);
	rectangle(600, 79, 900, 541);
	RECT rec = { 601,80,899,540 };//显示游戏规则
	floodfill(601, 80, BLACK, 0);
	settextstyle(30, 15, _T("楷体"));
	drawtext(_T("NOGO规则:"), &rec, DT_TOP | DT_LEFT | DT_SINGLELINE);
	rec.top += 30;
	settextstyle(16, 10, _T("雅黑"));
	drawtext(_T("1. 棋盘同九路围棋棋盘，9×9；"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 16;
	drawtext(_T("2. 黑子先手，双方轮流落子，落子后棋子不可移动；"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 32;
	drawtext(_T("3. 如果一方落子后吃掉了对方的棋子，则落子一方判负；"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 32;
	drawtext(_T("4.对弈禁止自杀，禁止空手(pass)，自杀一方判负，空手一方判负；"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 48;
	drawtext(_T("5. 对弈结果只有胜负，没有和棋。"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 32;
	drawtext(_T("吃子定义：一个棋子在棋盘上，与它直线紧邻的空点是这个棋子的“气”。 棋子直线紧邻的点上，"
		"如果有同色棋子存在，则它们便相互连接成一个不可分割的整体。它们的气也应一并计算。 棋子直线紧邻的点上，"
		"如果有异色棋子存在，这口气就不复存在。如所有的气均为对方所占据，便呈无气状态。无气状态的棋子不能在棋盘上存在，"
		"也就是提子。把无气之子提出盘外的手段叫“提子”。"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 210;
	drawtext(_T("悔棋会去掉一个黑子一个白子。开一个音乐后即可有落子声。"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);
	rec.top += 32;
	drawtext(_T("游戏愉快！！！"), &rec, DT_TOP | DT_LEFT | DT_WORDBREAK);

	fillrectangle(79, 20, 521, 60);//游戏结果及状态栏
	rec = { 80,21,520,59 };
	settextstyle(20, 12, _T("宋体"));
	
	RECT save = {601,561,719,609};//存档按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255,251,240));
	fillrectangle(600, 560, 720, 610);
	drawtext(_T("存档"), &save, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);

	RECT quit = { 781,561,899,609 };//退出按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255,251,240));
	fillrectangle(780, 560, 900, 610);
	drawtext(_T("退出"), &quit, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);

	RECT huiqi = { 441,541,519,569 };//悔棋按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255,251,240));
	fillrectangle(440, 540, 520, 570);
	drawtext(_T("悔棋"), &huiqi, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);

	RECT fanhui = { 701,21,899,59 };//返回至标题界面按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255, 251, 240));
	fillrectangle(700, 20, 900, 60);
	drawtext(_T("返回至标题界面"), &fanhui, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);

	RECT stop = { 601,21,659,59 };//暂停按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255,251,240));
	fillrectangle(600, 20, 660, 60);
	drawtext(_T("暂停"), &stop, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);

	RECT tip = { 341,541,419,569 };//提示按钮
	setfillcolor(RGB(255,251,240));
	setbkcolor(RGB(255,251,240));
	fillrectangle(340, 540, 420, 570);
	drawtext(_T("提示"), &tip, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setbkcolor(WHITE);


	setfillcolor(RGB(255, 251, 240));//音乐开关
	fillcircle(40, 160, 35);
	fillcircle(40, 305, 35);
	fillcircle(40, 450, 35);
	setbkcolor(RGB(255,251,240));
	outtextxy(10, 150, _T("音乐1"));
	outtextxy(10, 295, _T("音乐2"));
	outtextxy(10, 440, _T("音乐3"));
	setbkcolor(WHITE);

	setfillcolor(BLACK);
	MOUSEMSG m;		// 定义鼠标消息
	

	
	

	//读档
	if (mode == 3)
	{
		ifstream save("save.txt", ios::in);
		if (!save)
		{
			drawtext(_T("读档失败！请按退出"), &rec, DT_LEFT);
			end1 =1;
		}
		save >> mode>>human >> nowplayer;
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++) save >> board[i][j];
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j] == 1)
				{
					setfillcolor(BLACK);
					if (mode == 2 && human == -1) setfillcolor(LIGHTCYAN);
					fillcircle(100 + i * 50, 100 + j * 50, 20);
				}
				if (board[i][j] == -1) 
				{
					setfillcolor(WHITE);
					if (mode == 2 && human == 1) setfillcolor(LIGHTCYAN);
					fillcircle(100 + i * 50, 100 + j * 50, 20);
				}
			}
		if(!end1)drawtext(_T("读档成功！"), &rec, DT_LEFT);
		Sleep(2000);
		save.close();
	}
	if (nowplayer == 1) setfillcolor(BLACK);
	else if (nowplayer == -1) setfillcolor(WHITE);


	
	//游戏功能的实现部分
	while (true)
	{
		
		if (stoping)
		{
			int nowcolor = getfillcolor();
			setfillcolor(WHITE);
			fillrectangle(79, 20, 521, 60);
			drawtext(_T("游戏暂停中,无法落子、悔棋和提示"), &rec, DT_LEFT | DT_WORDBREAK);
			setfillcolor(nowcolor);
		}
		int num1 = 0, num2 = 0;//1黑2白
		huihe = 1;//huihe是回合数
		flag1 = 0;
		for (int i = 0; i < 9 ; i++)//统计回合数
			for (int j = 0; j < 9; j++)
			{
				if (board[i][j])
					huihe++;
				if (ok(i, j, 1))
					num1++;
				if (ok(i, j, -1))
					num2++;
			}

		//绘制界面
		if (!end1&&!stoping)
		{
			drawtext(_T("当前回合数：                   "), &rec, DT_LEFT);
			char s[10];
			sprintf_s(s, "%-9d", huihe);
			outtextxy(240, 21, s);
			char s1[5] = { 0 }, s2[5] = { 0 };
			sprintf_s(s1, "%-2d", num1);
			sprintf_s(s2, "%-2d", num2);
			if (mode == 1)
			{
				outtextxy(80, 40, "剩余可落位置: 黑: ");
				outtextxy(280, 40, s1);
				outtextxy(320, 40, "白:");
				outtextxy(360, 40, s2);
			}
			else if (mode == 2&&human==1)
			{
				outtextxy(80, 40, "剩余可落位置: 人类:");
				outtextxy(320, 40, s1);
				outtextxy(370, 40, "AI:");
				outtextxy(420, 40, s2);
			}
			else if (mode == 2 && human == -1)
			{
				outtextxy(80, 40, "剩余可落位置: 人类:");
				outtextxy(320, 40, s2);
				outtextxy(370, 40, "AI:");
				outtextxy(420, 40, s1);
			}
		}

		//判断游戏是否结束
		if (num1 == 0&&!end1&&!stoping)
		{
			drawtext(_T("黑方无处可下，白方胜利"), &rec, DT_LEFT);
			if (mode == 2 && human == -1)drawtext(_T("AI无处可下，人类胜利      "), &rec, DT_LEFT);
			if (mode == 2 && human == 1)drawtext(_T("人类无处可下，AI胜利      "), &rec, DT_LEFT);
			rec.top += 20;
			drawtext(_T("游戏结束，请按退出或返回至标题界面    "), &rec, DT_LEFT);
			rec.top -= 20;
			end1 = 1;
			continue;
		}
		if (num2 == 0&&!end1&&!stoping)
		{
			drawtext(_T("白方无处可下，黑方胜利"), &rec, DT_LEFT);
			if(mode==2&&human==1)drawtext(_T("电脑无处可下，人类胜利      "), &rec, DT_LEFT);
			if (mode == 2 && human == -1)drawtext(_T("人类无处可下，电脑胜利      "), &rec, DT_LEFT);
			rec.top += 20;
			drawtext(_T("游戏结束，请按退出或返回至标题界面"), &rec, DT_LEFT);
			rec.top -= 20;
			end1 = 1;
			continue;
		}

		//电脑AI
		if (mode == 2 && nowplayer != human&&!end1&&!stoping)
		{
			int result=robot(nowplayer,1);
			if (result == 100)//游戏结束
			{
				setfillcolor(WHITE);
				fillrectangle(79, 20, 521, 60);
				drawtext(_T("游戏结果："), &rec, DT_LEFT);
				rec.left += 120;
					drawtext(_T("AI无处可下，人类胜利"), &rec, DT_LEFT);
				rec.top += 20;
				drawtext(_T("游戏结束，请按退出或返回至标题界面"), &rec, DT_LEFT);
				rec.top -= 20;
				end1 = 1;
				continue;
			}
			int i = result / 9, j = result % 9;
			board[i][j] = nowplayer;
			setfillcolor(LIGHTCYAN);
			fillcircle(100 + i * 50, 100 + j * 50, 20);
			mciSendString(_T("open 落子声.mp3 alias luo"), NULL, 0, NULL);
			mciSendString(_T("play luo   "), NULL, 0, NULL);
			Sleep(300);
			mciSendString(_T("close luo"), NULL, 0, NULL);
			if (nowplayer == 1 )
			{
				hei[huihe] = i * 9 + j;
				setfillcolor(WHITE);
				nowplayer = -1;
			}
			else if (nowplayer == -1 )
			{
				bai[huihe] = i * 9 + j;
				nowplayer = 1;
				setfillcolor(BLACK);
			}
		}
		


		// 获取一条鼠标消息(以下是人类操作部分)
		m = GetMouseMsg();
		flag1 = 0;
		saveflag = 0;
		quitflag = 0;
		huiqiflag = 0;
		music1flag = 0;
		music2flag = 0;
		music3flag = 0;
		tipflag = 0;
		fanhuiflag = 0;
		stopflag = 0;

		for (int i = 0; i <= 8; i++)//落子高亮标识
			for (int j = 0; j <= 8; j++)
			{
				if (m.x > 80 + i * 50 && m.x < 120 + i * 50 && m.y>80 + j * 50 && m.y < 120 + j * 50 && flag1 == 0)
				{
					setlinecolor(RED);//高亮标识
					circle(100 + i * 50, 100 + j * 50, 20);
					flag1 = 1;
					biao[i][j] = 1;
					setlinecolor(zongcolor);
					break;
				}
			}
		if (!flag1) leave = 1;

		//存档高亮标识
		if (m.x > save.left && m.x<save.right && m.y>save.top && m.y < save.bottom)
		{
			setlinecolor(RED);
			rectangle(save.left+1, save.top+1, save.right-1, save.bottom-1);
			saveflag = 1;
			setlinecolor(zongcolor);
		}
		if (!saveflag) saveleave = 1;

		//撤销存档高亮标识
		if (saveleave )
		{
			setlinecolor(LIGHTGRAY);
			rectangle(save.left+1, save.top+1, save.right-1, save.bottom-1);
			saveflag = 0;
			saveleave = 0;
			setlinecolor(zongcolor);
		}
	

		//退出高亮标识
		if (m.x > quit.left && m.x<quit.right && m.y>quit.top && m.y < quit.bottom)
		{
			setlinecolor(RED);
			rectangle(quit.left + 1, quit.top + 1, quit.right - 1, quit.bottom - 1);
			quitflag = 1;
			setlinecolor(zongcolor);
		}
		if (!quitflag) quitleave = 1;

		//撤销退出高亮标识
		if (quitleave)
		{
			setlinecolor(LIGHTGRAY);
			rectangle(quit.left + 1, quit.top + 1, quit.right - 1, quit.bottom - 1);
			quitflag = 0;
			quitleave = 0;
			setlinecolor(zongcolor);
		}
		

		//音乐开关1高亮标识
		if ((m.x - 40) * (m.x - 40) + (m.y - 160) * (m.y - 160) < 35 * 35)
		{
			setlinecolor(RED);
			circle(40, 160, 33);
			music1flag = 1;
			setlinecolor(zongcolor);
		}
		if (!music1flag) music1leave = 1;

		//撤销音乐开关1高亮标识
		if (music1leave)
		{
			setlinecolor(LIGHTGRAY);
			circle(40, 160, 33);
			music1flag = 0;
			music1leave = 0;
			setlinecolor(zongcolor);
		}
		

		//音乐开关2高亮标识
		if ((m.x - 40) * (m.x - 40) + (m.y - 305) * (m.y - 305) < 35 * 35)
		{
			setlinecolor(RED);
			circle(40, 305, 33);
			music2flag = 1;
			setlinecolor(zongcolor);
		}
		if (!music2flag) music2leave = 1;

		//撤销音乐开关2高亮标识
		if (music2leave)
		{
			setlinecolor(LIGHTGRAY);
			circle(40, 305, 33);
			music2flag = 0;
			music2leave = 0;
			setlinecolor(zongcolor);
		}
		

		//音乐开关3高亮标识
		if ((m.x - 40) * (m.x - 40) + (m.y - 450) * (m.y - 450) < 35 * 35)
		{
			setlinecolor(RED);
			circle(40, 450, 33);
			music3flag = 1;
			setlinecolor(zongcolor);
		}
		if (!music3flag) music3leave = 1;

		//撤销音乐开关3高亮标识
		if (music3leave)
		{
			setlinecolor(LIGHTGRAY);
			circle(40, 450, 33);
			music3flag = 0;
			music3leave = 0;
			setlinecolor(zongcolor);
		}
		

		//悔棋高亮标识
		if (m.x > huiqi.left && m.x<huiqi.right && m.y>huiqi.top && m.y < huiqi.bottom)
		{
			setlinecolor(RED);
			rectangle(huiqi.left + 1, huiqi.top + 1, huiqi.right - 1, huiqi.bottom - 1);
			huiqiflag = 1;
			setlinecolor(zongcolor);
		}
		if (!huiqiflag) huiqileave = 1;

		//撤销悔棋高亮标识
		if (huiqileave)
		{
			setlinecolor(LIGHTGRAY);
			rectangle(huiqi.left + 1, huiqi.top + 1, huiqi.right - 1, huiqi.bottom - 1);
			huiqiflag = 0;
			huiqileave = 0;
			setlinecolor(zongcolor);
		}

		//返回标题界面高亮标识
		if (m.x > fanhui.left && m.x<fanhui.right && m.y>fanhui.top && m.y < fanhui.bottom)
		{
			setlinecolor(RED);
			rectangle(fanhui.left + 1, fanhui.top + 1, fanhui.right - 1, fanhui.bottom - 1);
			fanhuiflag = 1;
			setlinecolor(zongcolor);
		}
		if (!fanhuiflag) fanhuileave = 1;

		//撤销返回标题界面高亮标识
		if (fanhuileave)
		{
			setlinecolor(LIGHTGRAY);
			rectangle(fanhui.left + 1, fanhui.top + 1, fanhui.right - 1, fanhui.bottom - 1);
			fanhuiflag = 0;
			fanhuileave = 0;
			setlinecolor(zongcolor);
		}

		//暂停高亮标识
		if (m.x > stop.left && m.x<stop.right && m.y>stop.top && m.y < stop.bottom)
		{
			setlinecolor(RED);
			rectangle(stop.left + 1, stop.top + 1, stop.right - 1, stop.bottom - 1);
			stopflag = 1;
			setlinecolor(zongcolor);
		}
		if (!stopflag) stopleave = 1;

		//撤销暂停高亮标识
		if (stopleave)
		{
			setlinecolor(LIGHTGRAY);
			rectangle(stop.left + 1, stop.top + 1, stop.right - 1, stop.bottom - 1);
			stopflag = 0;
			stopleave = 0;
			setlinecolor(zongcolor);
		}
		
		//提示高亮标识
		if (m.x > tip.left && m.x<tip.right && m.y>tip.top && m.y < tip.bottom)
		{
			setlinecolor(RED);
			rectangle(tip.left + 1, tip.top + 1, tip.right - 1, tip.bottom - 1);
			tipflag = 1;
			setlinecolor(zongcolor);
		}
		if (!tipflag) tipleave = 1;

		//撤销提示高亮标识
		if (tipleave)
		{
			setlinecolor(LIGHTGRAY);
			rectangle(tip.left + 1, tip.top + 1, tip.right - 1, tip.bottom - 1);
			tipflag = 0;
			tipleave = 0;
			setlinecolor(zongcolor);
		}

		//撤销落子高亮标识
		if (leave )
		{
			for (int i = 0; i <= 8; i++)//复原
				for (int j = 0; j <= 8; j++)
				{
					circle(100 + i * 50, 100 + j * 50, 20);
					if(i!=8)putpixel(100 + i * 50 + 20, 100 + j * 50, BLACK);
					if(i!=0)putpixel(100 + i * 50 - 20, 100 + j * 50, BLACK);
					if(j!=8)putpixel(100 + i * 50 , 100 + j * 50+20, BLACK);
					if(j!=0)putpixel(100 + i * 50 , 100 + j * 50-20, BLACK);
					if (i != 8)putpixel(100 + i * 50 + 20, 99, BLACK);
					if (i != 0)putpixel(100 + i * 50 - 20, 99, BLACK);
					if (j != 8)putpixel(99, 100 + j * 50 + 20, BLACK);
					if (j != 0)putpixel(99, 100 + j * 50 - 20, BLACK);
					if (i != 8)putpixel(100 + i * 50 + 20, 501, BLACK);
					if (i != 0)putpixel(100 + i * 50 - 20, 501, BLACK);
					if (j != 8)putpixel(501, 100 + j * 50 + 20, BLACK);
					if (j != 0)putpixel(501, 100 + j * 50 - 20, BLACK);
				}
			memset(biao, 0, sizeof(biao));
			flag1 = 0;
			leave = 0;
		}

		

		//鼠标点击部分
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			bool fg = 0,savefg=0;

			//退出
			if (quitflag)
			{
				closegraph();
				return;
			}
			
			//存档
			if (saveflag)
			{
				if (end1)
				{
					setfillcolor(WHITE);
					fillrectangle(79, 20, 521, 60);
					drawtext(_T("游戏结束，无法存档"), &rec, DT_LEFT);
					continue;
				}
				int nowcolor = getfillcolor();
				setfillcolor(WHITE);
				fillrectangle(79, 20, 521, 60);
				ofstream save("save.txt", ios::out);
				if (!save)
				{
					drawtext(_T("存档失败！"), &rec, DT_LEFT);
					Sleep(2000);
					continue;
				}
				save <<mode<<' '<< human << ' ' << nowplayer << endl;
				for (int i = 0; i < 9; i++)
				{
					for (int j = 0; j < 9; j++)	save << board[i][j] << ' ';
					save << endl;
				}
				drawtext(_T("存档成功！"), &rec, DT_LEFT);
				rec.top += 20;
				drawtext(_T("可继续游戏或退出"), &rec, DT_LEFT);
				rec.top -= 20;
				setfillcolor(nowcolor);
				save.close();
				savefg = 1;
				Sleep(2000);
				continue;
			}

			//悔棋
			if (huiqiflag&&!stoping)
			{
				int nowcolor = nowplayer;
				if (end1)
				{
					setfillcolor(WHITE);
					fillrectangle(79, 20, 521, 60);
					drawtext(_T("游戏结束，无法悔棋"), &rec, DT_LEFT);
					continue;
				}
				if (nowplayer == 1&&!end1)//悔棋，清除黑白两方最近下的各一个子
				{
					if (bai[huihe - 1] == -1||hei[huihe-2]==-1)
					{
						int nowcolor = getfillcolor();
						setfillcolor(WHITE);
						fillrectangle(79, 20, 521, 60);
						drawtext(_T("无上一步记录，无法悔棋"), &rec, DT_LEFT);
						setfillcolor(nowcolor);
						Sleep(1500);
						continue;
					}
					int i = bai[huihe - 1] / 9, j = bai[huihe - 1] % 9;
					bai[huihe - 1] = -1;
					board[i][j] = 0;
					for (int dir = 0; dir < 4; dir++)
					{
						int dx = i + cx[dir], dy = j + cy[dir];
						if (inboard(dx, dy)) yan1[dx][dy] = 0;
					}
					i = hei[huihe - 2] / 9, j = hei[huihe - 2] % 9;
					hei[huihe - 2] = -1;
					board[i][j] = 0;
					for (int dir = 0; dir < 4; dir++)
					{
						int dx = i + cx[dir], dy = j + cy[dir];
						if (inboard(dx, dy)) yan1[dx][dy] = 0;
					}
				}
				else if (nowplayer == -1&&!end1)
				{
					if (hei[huihe - 1] == -1||bai[huihe-2]==-1)
					{
						int nowcolor = getfillcolor();
						setfillcolor(WHITE);
						fillrectangle(79, 20, 521, 60);
						drawtext(_T("无上一步记录，无法悔棋"), &rec, DT_LEFT);
						setfillcolor(nowcolor);
						Sleep(1500);
						continue;
					}
					int i = hei[huihe - 1] / 9, j = hei[huihe - 1] % 9;
					hei[huihe - 1] = -1;
					board[i][j] = 0;
					for (int dir = 0; dir < 4; dir++)
					{
						int dx = i + cx[dir], dy = j + cy[dir];
						if (inboard(dx, dy)) yan1[dx][dy] = 0;
					}
					i = bai[huihe - 2] / 9, j = bai[huihe - 2] % 9;
					bai[huihe - 2] = -1;
					board[i][j] = 0;
					for (int dir = 0; dir < 4; dir++)
					{
						int dx = i + cx[dir], dy = j + cy[dir];
						if (inboard(dx, dy)) yan1[dx][dy] = 0;
					}
				}

				setfillcolor(zongcolor);//以下为重绘棋盘
				fillrectangle(79, 79, 521, 521);
				setcolor(BLACK); //设置绘图笔颜色为黑色
				/*画横线*/
				for (int x = 100; x <= 500; x += 50) line(100, x, 500, x);
				/*画竖线*/
				for (int x = 100; x <= 500; x += 50) line(x, 100, x, 500);
				/*加粗边框线*/
				line(99, 99, 501, 99);
				line(99, 501, 501, 501);
				line(99, 99, 99, 501);
				line(501, 99, 501, 501);
				for (int i = 0; i < 9; i++)
					for (int j = 0; j < 9; j++)
					{
						if (board[i][j] == 1)
						{
							setfillcolor(BLACK);
							if (mode == 2 && human == -1)
								setfillcolor(LIGHTCYAN);
							fillcircle(100 + i * 50, 100 + j * 50, 20);
						}
						if (board[i][j] == -1)
						{
							setfillcolor(WHITE);
							if (mode == 2 && human == 1)
								setfillcolor(LIGHTCYAN);
							fillcircle(100 + i * 50, 100 + j * 50, 20);
						}
					}
				if (nowcolor == 1) setfillcolor(BLACK);
				else if (nowcolor == -1) setfillcolor(WHITE);
				continue;
			}

			//返回至标题界面
			if(fanhuiflag)
			{
				closegraph();
				if (music3ing == 1)
				{
					music3ing = 0;
					mciSendString(_T("close music3"), NULL, 0, NULL);
				}
				if (music2ing == 1)
				{
					music2ing = 0;
					mciSendString(_T("close music2"), NULL, 0, NULL);
				}
				if (music1ing == 1)
				{
					music1ing = 0;
					mciSendString(_T("close music1"), NULL, 0, NULL);
				}
				memset(board, 0, sizeof(board));
				memset(yan1, 0, sizeof(yan1));
				memset(hei, -1, sizeof(hei));
				memset(bai, -1, sizeof(bai));
				nowplayer = 0, human = 0, mode = 0,stoping=0;
				end1 = 0;
				begin();
				return;
			}

			//暂停
			if (stopflag&&!end1)
			{
				if (stoping == 0)
				{
					stoping = 1;
					continue;
				}
				else
				{
					stoping = 0;
					continue;
				}
			}

			//提示
			if (tipflag&&!stoping)
			{
				if (end1)
				{
					setfillcolor(WHITE);
					fillrectangle(79, 20, 521, 60);
					drawtext(_T("游戏结束，无法提示"), &rec, DT_LEFT);
					continue;
				}
				int result = robot(nowplayer,0);
				int i = result / 9, j = result % 9;
				int nowcolor = getlinecolor();
				setlinecolor(YELLOW);
				circle(100 + i * 50, 100 + j * 50, 20);
				setlinecolor(nowcolor);
				continue;
			}

			//音乐开关1
			if (music1flag)
			{
				if (music3ing == 1)
				{
					music3ing = 0;
					mciSendString(_T("stop music3"), NULL, 0, NULL);
				}
				if (music2ing == 1)
				{
					music2ing = 0;
					mciSendString(_T("stop music2"), NULL, 0, NULL);
				}
				if (music1ing == 0)
				{
					music1ing = 1;
					
					mciSendString(_T("play music1 "), NULL, 0, NULL);
					continue;
				}
				if (music1ing == 1)
				{
					music1ing = 0;
					mciSendString(_T("stop music1"), NULL, 0, NULL);
				}
			}

			//音乐开关2
			if (music2flag)
			{
				if (music3ing == 1)
				{
					music3ing = 0;
					mciSendString(_T("stop music3"), NULL, 0, NULL);
				}
				if (music1ing == 1)
				{
					music1ing = 0;
					mciSendString(_T("stop music1"), NULL, 0, NULL);
				}
				if (music2ing == 0)
				{
					music2ing = 1;
					
					mciSendString(_T("play music2 "), NULL, 0, NULL);
					continue;
				}
				if (music2ing == 1)
				{
					music2ing = 0;
					mciSendString(_T("stop music2"), NULL, 0, NULL);
				}
			}

			//音乐开关3
			if (music3flag)
			{
				if (music1ing == 1)
				{
					music1ing = 0;
					mciSendString(_T("stop music1"), NULL, 0, NULL);
				}
				if (music2ing == 1)
				{
					music2ing = 0;
					mciSendString(_T("stop music2"), NULL, 0, NULL);
				}
				if (music3ing == 0)
				{
					music3ing = 1;
					
					mciSendString(_T("play music3 "), NULL, 0, NULL);
					continue;
				}
				if (music3ing == 1)
				{
					music3ing = 0;
					mciSendString(_T("stop music3"), NULL, 0, NULL);
				}
			}

			//落子
			for (int i = 0; i <= 8&&!fg; i++)
				for (int j = 0; j <= 8&&!fg; j++)
					if (biao[i][j] && !board[i][j]&&!end1&&!stoping)
					{
						fillcircle(100 + i * 50, 100 + j * 50, 20);
						mciSendString(_T("open 落子声.mp3 alias luo"), NULL, 0, NULL);
						mciSendString(_T("play luo   "), NULL, 0, NULL);
						Sleep(300);
						mciSendString(_T("close luo"), NULL, 0, NULL);
						if (nowplayer == 1) hei[huihe] = i * 9 + j;
						else bai[huihe] = i * 9 + j;
						
						if (!ok(i, j, nowplayer) && nowplayer == -1)
						{
							setfillcolor(WHITE);
							fillrectangle(79, 20, 521, 60);
							drawtext(_T("游戏结果："), &rec, DT_LEFT);
							rec.left += 120;
							drawtext(_T("白方自杀或提子，黑方胜利"), &rec, DT_LEFT);
							if (mode == 2 )
								drawtext(_T("人类自杀或提子，AI胜利      "), &rec, DT_LEFT);
							rec.top += 20;
							drawtext(_T("游戏结束，请按退出或返回至标题界面"), &rec, DT_LEFT);
							rec.top -= 20;
							end1 = 1;
							break;
						}
						if (!ok(i, j, nowplayer) && nowplayer == 1)
						{
							setfillcolor(WHITE);
							fillrectangle(79, 20, 521, 60);
							drawtext(_T("游戏结果："), &rec, DT_LEFT);
							rec.left += 120;
							drawtext(_T("黑方自杀或提子，白方胜利"), &rec, DT_LEFT);
							if (mode == 2)
								drawtext(_T("人类自杀或提子，AI胜利      "), &rec, DT_LEFT);
							rec.top += 20;
							drawtext(_T("游戏结束，请按退出或返回至标题界面"), &rec, DT_LEFT);
							rec.top -= 20;
							end1 = 1;
							break;
						}
						board[i][j] = nowplayer;
						fg = 1;
						break;
					}

			//切换棋手
			if (nowplayer==1 && fg&&!end1&&!stoping)
			{
				if (!savefg)setfillcolor(WHITE);
				nowplayer = -1;
				fg = 0;
			}
			else if (nowplayer==-1&&fg&&!end1&&!stoping)
			{
				nowplayer = 1;
				setfillcolor(BLACK);
			}		
		}

		
	}
	

	closegraph();
	return ;
}
int main()
{
	begin();
}