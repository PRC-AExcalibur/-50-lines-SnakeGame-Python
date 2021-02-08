#include <conio.h>
#include <deque>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <Windows.h>
using namespace std;
int main()
{
	//初始设置
	const int side = 8;              //屏幕尺寸 8*8
	int fps = 2;					 //帧率(每秒移动格子数)
	int length = 2;                  //蛇长度（初始）
	int direction[2] = { 1,0 };      //方向向量
	int snakehead[2] = { 5,4 };		 //蛇头位置
	deque<int>snake0 = { snakehead[0] ,snakehead[0] - direction[0] };//蛇0轴列
	deque<int>snake1 = { snakehead[1] ,snakehead[1] - direction[1] };//蛇1轴列
	int apple[2] = { 4,2 };    //苹果位置
	int ch;					   //键盘输入
	//主循环
	while (fps != -1) {
		if (_kbhit()) {
			ch = _getch();//键盘输入[s_115_(0,1),w_119_(0,-1),d_100_(1,0),a_97_(-1,0)]
			if (ch == 100 and direction[0] != -1) direction[0] = 1, direction[1] = 0;
			else if (ch == 97 && direction[0] != 1) direction[0] = -1, direction[1] = 0;
			else if (ch == 115 && direction[1] != -1) direction[0] = 0, direction[1] = 1;
			else if (ch == 119 && direction[1] != 1) direction[0] = 0, direction[1] = -1;
		}
		//主程序
		int snakehit = 0;
		int applehit = 0;
		snakehead[0] = snakehead[0] + direction[0], snakehead[1] = snakehead[1] + direction[1];//确定新蛇头
		for (int i = 0; i < length; i = i + 1) if (snakehead[0] == snake0[i] && snakehead[1] == snake1[i]) snakehit = 1;//蛇头是否与蛇身重合
		snake1.push_front(snakehead[1]), snake0.push_front(snakehead[0]);//补全蛇身
		if (snakehead[0] == apple[0] && snakehead[1] == apple[1]) {
			length = length + 1;
			do {applehit = 0;
				srand((unsigned int)(time(NULL)));
				apple[0] = (rand() % side) + 1, apple[1] = (rand() % side) + 1;//随机苹果位置
				for (int i = 0; i < length; i = i + 1) if (apple[0] == snake0[i] && apple[1] == snake1[i]) applehit = 1;
			} while (applehit==1);//苹果是否与蛇身重合)
		}
		snake0.resize(length), snake1.resize(length);//截断蛇身
		if (snakehead[0] > side || snakehead[1] > side || snakehead[0] == 0 || snakehead[1] == 0 || snakehit==1) {
			fps = -1;
			cout << "fail";//碰墙壁或碰自己>>失败
		}
		else if (length == 8 * 8 - 1) {
			fps = -1;
			cout << "success";//全部吃到>>成功
		}
		else {
			//渲染
			string screen[8][8] = {};
			for (int i1 = 0; i1 < 8; i1++) for (int i0 = 0; i0 < 8; i0++) screen[i0][i1] = {" ."};//填充空位
			screen[apple[0] - 1][apple[1] - 1] = "*.";
			for (int i = 0; i < length; i = i + 1) screen[snake0[i] - 1][snake1[i] - 1] = "o.";
			system("cls");
			cout << "SCORE:" << (length - 2) << " FPS:" << fps << " Side:" << side << "\n";
			for (int i1 = 0; i1 < 8; i1 ++) {
				for (int i0 = 0; i0 < 8; i0 ++) cout << screen[i0][i1];
				cout<< "\n";
			}
		}
		Sleep(1000 / fps); //时间循环
	}
}