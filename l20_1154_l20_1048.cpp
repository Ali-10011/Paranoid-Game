#include<iostream>
#include<string>
#include"mygraphics.h"
#include"myconsole.h"
#include<conio.h>   //For console Input Output 
#include <windows.h>
#include<fstream>
#include<ctime>
#include <cstdlib>  // For Random Function
#include<stdio.h>
using namespace std;
//Declarations of Global Variables
bool Save = false, ending = false; int Score = 0, CounterExtraBricks = 0, ExtraBrick = 12;
int TBricks; // Total Bricks on Screen string Player;
string HScPlayers[11], Player;
char CPlayer[30], ColourSelection;
double LifeLost = 3;
COLORREF GYellow = RGB(244, 180, 0);  COLORREF White = RGB(255, 255, 255);
COLORREF Yellow = RGB(255, 255, 0);   COLORREF Grey = RGB(32, 30, 30);
COLORREF GBlue = RGB(66, 133, 244);   COLORREF Lightyellow = RGB(255, 255, 51);
COLORREF GGreen = RGB(26, 162, 96);   COLORREF Blue = RGB(0, 0, 255);
COLORREF Green = RGB(0, 100, 0);      COLORREF Orange = RGB(253, 106, 2);
COLORREF Pink = RGB(255, 192, 203);   COLORREF MediumBlue = RGB(0, 0, 205);
COLORREF Indigo = RGB(75, 0, 130);    COLORREF Brown = RGB(222, 184, 135);
COLORREF GRed = RGB(219, 50, 54);     COLORREF SeaGreen = RGB(32, 178, 170);
COLORREF Black = RGB(0, 0, 0);        COLORREF Stone = RGB(96, 103, 107);
COLORREF Purple = RGB(102, 51, 153);  COLORREF DarkPink = RGB(153, 0, 153);
COLORREF LightPink = RGB(255,102,255); COLORREF Golden = RGB(153, 153,0);
COLORREF BallColour = MediumBlue, BatColour = Stone, BackGround = Black;

struct Brick {
	int x1, x2, y1, y2, ID;
	COLORREF Colour;
	char Shape;
	bool ColourPresence;
};
void Penalties(Brick[], int); // Prototype of overloaded Function

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void NameConversion() {
	int length = Player.length();
	int i = 0;
	while (i != length) {
		CPlayer[i] = char(Player.at(i));
		i++;
	}
	CPlayer[i] = '\0';
}
wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}
void Sorting(int TempScore[], int Size)
{ // Used to sort Array of High Scores
	int Temp = 0;
	string Temp2 = "s2323";
	for (int i = 0; i < (Size - 1); i++)
	{
		for (int j = 0; j < (Size - i - 1); j++)
		{
			if (TempScore[j] < TempScore[j + 1])
			{
				Temp = TempScore[j];
				Temp2 = HScPlayers[j];
				TempScore[j] = TempScore[j + 1];
				HScPlayers[j] = HScPlayers[j + 1];
				TempScore[j + 1] = Temp;
				HScPlayers[j + 1] = Temp2;
			}
		}
	}
}
void ColorBorders()
{
	//Sets border of Console
	ShowConsoleCursor(false);
	myLine(2, 2, 2, 720, GYellow);
	myLine(2, 2, 1312, 2, GYellow);
	myLine(1312, 2, 1312, 720, GYellow);
	myLine(2, 720, 1312, 720, GYellow);
	Sleep(18);
	myLine(2, 2, 2, 720, Pink);
	myLine(2, 2, 1312, 2, Pink);
	myLine(1312, 2, 1312, 720, Pink);
	myLine(2, 720, 1312, 720, Pink);
	Sleep(18);
	myLine(2, 2, 2, 720, GRed);
	myLine(2, 2, 1312, 2, GRed);
	myLine(1312, 2, 1312, 720, GRed);
	myLine(2, 720, 1312, 720, GRed);
	Sleep(18);
	myLine(2, 2, 2, 720, GGreen);
	myLine(2, 2, 1312, 2, GGreen);
	myLine(1312, 2, 1312, 720, GGreen);
	myLine(2, 720, 1312, 720, GGreen);
	Sleep(18);
	myLine(2, 2, 2, 720, GBlue);
	myLine(2, 2, 1312, 2, GBlue);
	myLine(1312, 2, 1312, 720, GBlue);
	myLine(2, 720, 1312, 720, GBlue);
	Sleep(18);
}
void BatBallColour()
{
	myRect(0, 0, 1900, 1500, BackGround, BackGround);
	bool Iterator = false;
	myDrawTextWithFont(480, 40, 60, "Colour Selection", GBlue, Black);
	myDrawTextWithFont(30, 130, 50, "Press", GBlue, Black);

	myDrawTextWithFont(30, 230, 45, " R:", GRed, BackGround);
	myLine(25, 230 + 42, 70, 230 + 42, BackGround);
	myRect(290, 240, 450, 270, BackGround, GRed);
	myEllipse(500, 235, 500 + 35, 235 + 35, BackGround, GGreen);

	myDrawTextWithFont(30, 330, 45, " G:", GGreen, BackGround);
	myLine(25, 330 + 42, 70, 330 + 42, BackGround);
	myRect(290, 340, 450, 370, BackGround, GGreen);
	myEllipse(500, 335, 500 + 35, 335 + 35, BackGround, GYellow);

	myDrawTextWithFont(30, 430, 45, " B:", Brown, BackGround);
	myLine(25, 430 + 42, 70, 430 + 42, Black);
	myRect(290, 440, 450, 470, BackGround, Brown);
	myEllipse(500, 435, 500 + 35, 435 + 35, BackGround, Orange);

	myDrawTextWithFont(700, 230, 45, " S:", Stone, BackGround);
	myLine(25 + 670, 230 + 42, 695 + 45, 230 + 42, BackGround);
	myRect(960, 240, 960 + 160, 270, BackGround, Stone);
	myEllipse(1170, 235, 1170 + 35, 235 + 35, BackGround, GBlue);

	myDrawTextWithFont(700, 330, 45, " W:", White, BackGround);
	myLine(25 + 670, 330 + 42, 695 + 50, 330 + 42, BackGround);
	myRect(960, 340, 960 + 160, 370, BackGround, White);
	myEllipse(1170, 335, 1170 + 35, 335 + 35, BackGround, White);

	myDrawTextWithFont(700, 430, 45, " M:",LightPink, BackGround);
	myLine(25 + 670, 430 + 42, 695 + 45, 430 + 42, BackGround);
	myRect(960, 440, 960 + 160, 470, BackGround, LightPink);
	myEllipse(1170, 435, 1170 + 35, 435 + 35, BackGround, Golden);

	myDrawTextWithFont(480, 530, 60, " Get Ready to Play ... ", Brown, BackGround);
	myLine(480, 590, 480 + 385, 590, Brown);
	while (!Iterator)
	{
		ColorBorders();
		if (GetKeyState('R') & 0x8000)
		{
			BatColour = GRed, BallColour = GGreen;
			Iterator = true;
		}
		else if (GetKeyState('G') & 0x8000)
		{
			BatColour = GGreen; BallColour = GYellow;
			Iterator = true;
		}
		else if (GetKeyState('B') & 0x8000)
		{
			BatColour = Brown; BallColour = Orange;
			Iterator = true;
		}
		else if (GetKeyState('S') & 0x8000)
		{
			BatColour =Stone; BallColour = GBlue;
			Iterator = true;
		}
		else if (GetKeyState('W') & 0x8000)
		{
			BatColour = White; BallColour = White;
			Iterator = true;
		}
		else if (GetKeyState('M') & 0x8000)
		{
			BatColour = LightPink; BallColour = Golden;
			Iterator = true;
		}
	}
	ClearScreen();
}
void Instructions(Brick Bricks[91])
{
	myRect(0, 0, 1900, 1500, Black, Black);
	bool stop = false;
	int r1x = 600;
	int r2x = 780;
	int r1y = 175;
	int r2y = 195;
	int incb = 37;
	int bx1 = (r1x + r2x - 25) / 2;
	int by1 = 150;
	int inc = 20;
	int Size = 15;
	int SizeParallelogram = 5;
	COLORREF color = GRed;
	myRect(550, 305, 650, 325, Pink, Pink);
	myRect(600, 365, 700, 385, Pink, Pink);
	myRect(1000, 485, 1100, 505, Pink, Pink);
	myRect(1000 + 32, 480 + 22, 1100 - 32, 510 - 22, Yellow, Yellow);
	for (int i = -SizeParallelogram; i < SizeParallelogram; i++)       // Brick enclosing Paralleogram
	{
		myLine(1000 + 36 + i, 480 + 7, 1000 + 31, 480 + 20, Pink);
	}
	for (int i = -SizeParallelogram; i < SizeParallelogram; i++)
	{
		myLine(1000 + 68, 480 + 7, 1000 + 63 + i, 480 + 21, Pink);
	}
	for (int i = -Size; i < Size; i++)
	{
		myLine(600 + 50 + i, 363 + 5, 600 + 50, 363 + 20, GRed);  // Brick enclosing Triangle
	}
	myRect(1150, 425, 1250, 445, Pink, Pink);
	myRect(1165, 430, 1235, 440, Grey, Grey);
	myRect(770, 570, 870, 590, Pink, Pink);
	myEllipse(811, 570, 830, 589, Green, Green);
	myDrawTextWithFont(15, 15, 40, "<-- BACK ( b )", GGreen, BackGround);
	myLine(3, 51, 180, 51, BackGround);
	myDrawTextWithFont(550, 25, 68, "How To Play", SeaGreen, BackGround);
	myDrawTextWithFont(30, 120, 30, "Move the bat using right(->) and Left(<-) arrow keys", Orange, BackGround);
	myLine(20, 147, 530, 147, BackGround);
	myDrawTextWithFont(30, 180, 30, "Press [SPACE] to launch the ball", Orange, BackGround);
	myLine(20, 207, 530, 207, BackGround);
	myDrawTextWithFont(30, 240, 30, "If the ball falls down the bat, 1 life will be lost", Orange, BackGround);
	myLine(20, 267, 630, 267, BackGround);
	myDrawTextWithFont(30, 300, 30, "Hitting This Brick will gain in two points ", Pink, BackGround);
	myLine(20, 327, 630, 327, BackGround);
	myDrawTextWithFont(30, 360, 30, "Hitting This Brick will result in lose of half life", GRed, BackGround);
	myLine(20, 387, 630, 387, BackGround);
	myDrawTextWithFont(30, 420, 30, "Hitting This Brick will print a new row ! However if there are already 7 rows than score will be reduced by 10 points", GBlue, BackGround);
	myLine(20, 447, 1200, 447, BackGround);
	myDrawTextWithFont(30, 480, 30, "Hitting This Brick will destroy the surrounding bricks and their respective scores will be added", Lightyellow, BackGround);
	myLine(20, 507, 1100, 507, BackGround);
	myDrawTextWithFont(30, 540, 30, "Hitting This Brick will add one life ! However if there are already 5 lives", Green, BackGround);
	myLine(20, 567, 700, 567, BackGround);
	myDrawTextWithFont(100, 590, 30, " - 10 points of score will be added (5 points if there are  4.5 lives)", Green, BackGround);
	myLine(20, 617, 900, 617, BackGround);
	while (!stop)
	{

		myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
		myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
		by1 = by1 - inc;
		if (by1 < 85) {
			by1 = 110;
			inc = -inc;
			color = GRed;
		}
		if ((by1 + 25) > 175) {
			by1 = 150;
			inc = -inc;
			color = GBlue;
		}
		r1x = incb + r1x;
		r2x = incb + r2x;
		bx1 = (r1x + r2x - 25) / 2;
		myEllipse(bx1, by1, bx1 + 25, by1 + 25, color, color);
		if (r2x >= 1312) {
			r2x = 1310;
			r1x = 1132;
			incb = -incb;
		}
		if (r1x <= 600) {
			r1x = 600;
			r2x = 780;
			incb = -incb;
		}
		myRect(r1x, r1y, r2x, r2y, Pink, Pink);
		ColorBorders();  // Function Calling
		if ((GetKeyState('B') & 0x8000)) {
			stop = true;
		}
	}
}
void Lives(double liveslost)
{
	// Show Lives on Screen


	int c = 5;
	int bx1 = 120;
	int by1 = 747;
	myRect(10, 735, 300, 780, GRed, BackGround);
	myDrawTextWithFont(20, 737, 45, "Lives ", GBlue, BackGround);
	myLine(10, 779, 300, 779, GRed);
	if (liveslost <= 2)
	{
		while (liveslost >= 1)
		{
			myEllipse(bx1, by1, bx1 + 25, by1 + 25, GRed, GRed);
			bx1 = bx1 + 30;
			liveslost--;
		}
		if (liveslost == 0.5)
		{
			myEllipse(bx1, by1, bx1 + 25, by1 + 25, GRed, GRed);
			myRect((bx1 + bx1 + 25) / 2, by1, (bx1 + bx1 + 25) / 2 + (25), by1 + 25, BackGround, BackGround);
			liveslost = 0;
		}

	}
	else if (liveslost <= 5)
	{
		while (liveslost >= 1)
		{
			myEllipse(bx1, by1, bx1 + 25, by1 + 25, GGreen, GGreen);
			bx1 = bx1 + 30;
			liveslost--;
		}
		if (liveslost == 0.5)
		{
			myEllipse(bx1, by1, bx1 + 25, by1 + 25, GGreen, GGreen);
			myRect((bx1 + bx1 + 25) / 2, by1, (bx1 + bx1 + 25) / 2 + (25), by1 + 25, BackGround, BackGround);
		}
	}

}
void sc1()
{
	// Show Score on Screen
	//myRect(1120, 740, 1400, 800, BackGround, BackGround);
	myRect(1070, 730, 1315, 800, GGreen, BackGround);
	int sc = Score;
	char str[10];
	int t = 0;
	int g = 0;
	int l = 0;
	if (sc < 0) {
		str[g] = char(45);
		g++;
		sc = -1 * (sc);
	}
	t = sc;
	if (sc == 0) {
		str[0] = char(48);
		g++;

	}
	else {
		while (t > 0) {
			t = t / 10;
			l++;
		}
		l--;
		t = sc;
		while (l > 0) {
			t = sc / pow(10, l);
			sc = sc - (t* pow(10, l));
			str[g] = char(t + 48);
			g++;
			l--;
		}
		str[g] = char(sc + 48);
		g++;
	}
	str[g] = '\0';
	myDrawTextWithFont(1120, 738, 45, "Score : ", GRed, BackGround);
	myDrawTextWithFont(1230, 738, 45, str, GBlue, BackGround);
	myLine(1100, 780, 1310, 780, BackGround);
}
char Start()
{

	// Starting Page
	myRect(0, 0, 1900, 1500, BackGround, BackGround);
	ShowConsoleCursor(false);
	char option = 'g';
	bool start = false;
	int bx1 = 70;
	int by1 = 675;
	int bx2 = 1225;
	int by2 = 7;
	int bh1 = 2;
	int bh2 = 1277;
	int incy1 = -22;
	int incy2 = +22;
	int incx1 = 40;
	int incx2 = -40;
	COLORREF color1 = GGreen;
	COLORREF color2 = GRed;
	COLORREF color3 = Purple;
	COLORREF color4 = Orange;
	myRect(0, 0, 1900, 1500, BackGround, BackGround);
	myDrawTextWithFont(440, 50, 70, "WELCOME TO PARANOID !", GBlue, BackGround);
	/*myDrawTextWithFont(300, 50, 70, " Hey Silver Mist Welcome to Paranoid ", GBlue, BackGround);*/

	myDrawTextWithFont(540, 160, 60, "Make a Selection", White, BackGround);
		myDrawTextWithFont(600, 260, 50, "C    -    Continue", GGreen, BackGround);
		myLine(595, 305, 900, 305, Black);
		myDrawTextWithFont(600, 320, 50, "N    -    New Game", GRed, BackGround);
		myLine(595, 365, 900, 365, Black);
		myDrawTextWithFont(600, 380, 50, "H    -    High Scores", GYellow, BackGround);
		myLine(595, 425, 900, 425, Black);
		myDrawTextWithFont(600, 440, 50, "I    -    Instructions", Purple, BackGround);
		myLine(595, 485, 900, 485, Black);
		myDrawTextWithFont(600, 500, 50, "E    -    Exit", Orange, BackGround);
		myLine(595, 545, 900, 545, Black);
		myDrawTextWithFont(32, 760, 30, "   B Y : ", GBlue, Black);
		myDrawTextWithFont(83, 760, 30, "   M U H A M M A D   A B D U L L A H", Stone, Black);
		myDrawTextWithFont(380, 760, 30, "    a n d     ", GRed, Black);
		myDrawTextWithFont(460, 760, 30, " A L I   H U S S N A I N", Orange, Black);
		myLine(0, 787, 1300, 787, Black);
		while (!(start)) {
			myEllipse(bx1, by1, bx1 + 35, by1 + 35, color1, color1);
			myEllipse(bx2, by2, bx2 + 35, by2 + 35, color2, color2);
			myEllipse(bh1, 10, bh1 + 35, 45, color3, color3);
			myEllipse(bh2, 680, bh2 + 35, 715, color4, color4);
			myEllipse(bx1 + 50, by2, bx1 + 85, by2 + 35, color2, color2);
			myEllipse(bx2 - 50, by1, bx2 - 15, by1 + 35, color1, color1);
		if (GetKeyState('N') & 0x8000) {
			start = true;
			option = 'n';
		}
		else if (GetKeyState('C') & 0x8000) {
			start = true;
			option = 'c';

		}
		else if (GetKeyState('H') & 0x8000) {
			start = true;
			option = 'h';
		}
		else if (GetKeyState('E') & 0x8000) {
			start = true;
			option = 'e';
		}
		else if (GetKeyState('I') & 0x8000) {
			start = true;
			option = 'i';
		}
		ColorBorders();
		myEllipse(bx1, by1, bx1 + 35, by1 + 35, BackGround, BackGround);
		myEllipse(bx2, by2, bx2 + 35, by2 + 35, BackGround, BackGround);
		myEllipse(bh1, 10, bh1 + 35, 45, BackGround, BackGround);
		myEllipse(bh2, 680, bh2 + 35, 715, BackGround, BackGround);
		myEllipse(bx1 + 50, by2, bx1 + 85, by2 + 35, BackGround, BackGround);
		myEllipse(bx2 - 50, by1, bx2 - 15, by1 + 35, BackGround, BackGround);
		by1 = by1 + incy1;
		by2 = by2 + incy2;
		bh1 = bh1 + incx1;
		bh2 = bh2 + incx2;
		if (by1 <= 7) {
			incy1 = -incy1;
			by1 = 2;
			color1 = GRed;
		}
		if (by1 > 690) {
			incy1 = -incy1;
			by1 = 675;
			color1 = GGreen;
		}
		if (by2 < 7) {
			incy2 = -incy2;
			by2 = 2;
			color2 = GRed;
		}
		if (by2 > 690) {
			incy2 = -incy2;
			by2 = 675;
			color2 = GGreen;
		}
		if (bh1 < 2) {
			bh1 = 2;
			incx1 = -incx1;
			color3 = Purple;
		}
		if ((bh1 + 35) > 1312) {
			bh1 = 1312 - 35;
			incx1 = -incx1;
			color3 = Orange;
		}
		if (bh2 < 2) {
			bh2 = 2;
			color4 = Purple;
			incx2 = -incx2;
		}
		if ((bh2 + 35) > 1312) {
			bh2 = 1312 - 35;
			incx2 = -incx2;
			color4 = Orange;
		}
	}
	return option;
	ClearScreen();
}
void Lost()
{
	// Show  End Page
	ShowConsoleCursor(false);
	Sleep(18);
	ClearScreen();
	int sc;
	sc = Score;
	char str[10];
	int t = 0;
	int g = 0;
	int l = 0;
	if (sc < 0) {
		str[g] = char(45);
		g++;
		sc = -1 * (sc);
	}
	t = sc;
	if (sc == 0) {
		str[0] = char(48);
		g++;

	}
	else {
		while (t > 0) {
			t = t / 10;
			l++;
		}
		l--;
		t = sc;
		while (l > 0) {
			t = sc / pow(10, l);
			sc = sc - (t* pow(10, l));
			str[g] = char(t + 48);
			g++;
			l--;
		}
		str[g] = char(sc + 48);
		g++;
	}
	str[g] = '\0';
	if (ending == true) {
		myRect(2, 2, 1310, 720, BackGround, BackGround);
		myDrawTextWithFont(510, 100, 90, " YOU WON   !", Green, BackGround);
		myLine(5, 180, 1200, 180, BackGround);
		myLine(5, 181, 1200, 181, BackGround);
		myLine(5, 182, 1200, 182, BackGround);
		myDrawTextWithFont(170, 440, 60, " Shabash Boht achi Game Kheli ha, ab prh bhi lo ... ", GBlue, BackGround);
		myLine(60, 496, 1290, 496, BackGround);
		//PlaySound(convertCharArrayToLPCWSTR("Applause.wav"), NULL, SND_ASYNC);  // Playing Sound
		PlaySound("Applause.wav", NULL, SND_ASYNC); // Play Sound

	}
	else
	{
		myRect(2, 2, 1310, 720, BackGround, BackGround);
		myDrawTextWithFont(510, 100, 90, " YOU LOST   !", Green, BackGround);
		myLine(5, 180, 1200, 180, BackGround);
		myLine(5, 181, 1200, 181, BackGround);
		myLine(5, 182, 1200, 182, BackGround);
		myDrawTextWithFont(70, 440, 60, "Chalo Shabash Chuti kro. Uap Game ky Level ky bandy nahi ho ", GBlue, BackGround);
		myLine(60, 496, 1290, 496, BackGround);
		//PlaySound(convertCharArrayToLPCWSTR("Lose.wav"), NULL, SND_ASYNC);  // Playing Sound
		PlaySound("Lose.wav", NULL, SND_ASYNC);  // Play Sound

	}
	myDrawTextWithFont(580, 250, 50, CPlayer, Yellow, BackGround);
	myDrawTextWithFont(550, 320, 50, "Score  ", GRed, BackGround);
	myDrawTextWithFont(680, 320, 50, str, Orange, BackGround);
	myLine(5, 365, 1200, 365, BackGround);
	myLine(5, 295, 1200, 295, BackGround);
	myLine(5, 296, 1200, 296, BackGround);

	while (1) {
		ColorBorders();
	}
}
void Ending()
{
	// Show End page
	ShowConsoleCursor(false);
	Sleep(18);
	ClearScreen();
	myRect(2, 2, 1312, 720, White, BackGround);
	ColorBorders(); // Calling Function
	myDrawTextWithFont(350, 200, 60, "THANK YOU FOR PLAYING PARANOID !", Green, BackGround);
	Sleep(2500);
}
void SaveGame(Brick Bricks[91])
{
	// Used to Write Data in File
	ofstream out;
	out.open("Save.txt");
	out << Score << endl;
	out << LifeLost << endl;
	out << TBricks << endl;
	out << Player << endl;
	out << BatColour << endl;
	out << BallColour << endl;
	for (int i = 0; i < TBricks; i++)
	{               // Writing Data 
		out << Bricks[i].x1 << "\t" << Bricks[i].x2 << "\t" << Bricks[i].y1 << "\t" << Bricks[i].y2 << "\t" << Bricks[i].ColourPresence << "\t" << Bricks[i].Shape << endl;
	}
	out.close();
}
void ShowBricks(Brick Bricks[91], int RandomRows)
{
	ShowConsoleCursor(false);
	// Used to Present Bricks on Screen
	COLORREF Black = RGB(0, 0, 0);
	COLORREF Red = RGB(255, 0, 0);
	COLORREF Pink = RGB(255, 192, 203);
	COLORREF Yellow = RGB(255, 255, 0);
	COLORREF White = RGB(255, 255, 255);
	COLORREF Green = RGB(0, 100, 0);
	COLORREF Grey = RGB(128, 128, 128);
	COLORREF SeaGreen = RGB(32, 178, 170);
	int X1 = 7, X2 = 107, Y1 = 8, Y2 = 38, CounterForID = 0, Size = 15, b = 0, t = 0, c = 0, p = 0, r = 0;
	int SizeParallelogram = 5;

	if (CounterExtraBricks > 0)
	{
		int i = ExtraBrick - 12;
		X1 = 7, X2 = 107;
		if (ExtraBrick == 12)
		{
			Y1 = 8, Y2 = 38;
		}
		else if (ExtraBrick == 25)
		{
			Y1 = 38, Y2 = 68;
		}
		else if (ExtraBrick == 38)
		{
			Y1 = 68, Y2 = 98;
		}
		else if (ExtraBrick == 51)
		{
			Y1 = 98, Y2 = 128;
		}
		else if (ExtraBrick == 64)
		{
			Y1 = 128, Y2 = 158;
		}
		else if (ExtraBrick == 77)
		{
			Y1 = 158, Y2 = 188;
		}
		else if (ExtraBrick == 90)
		{
			Y1 = 188, Y2 = 218;
		}
		for (; i <= ExtraBrick; i++)
		{
			if (Bricks[i].Shape == 'n')
			{
				myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink); // Normal Bricks
			}
			else if (Bricks[i].Shape == 'c')
			{
				myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
				myEllipse(X1 + 35, Y1 + 2, X2 - 40, Y2 - 4, Black, Green);   //Printing Circle inside brick
			}
			else if (Bricks[i].Shape == 'p')
			{
				myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
				myRect(Bricks[i].x1 + 32, Bricks[i].y1 + 22, Bricks[i].x2 - 32, Bricks[i].y2 - 22, Yellow, Yellow);
				for (int i = -SizeParallelogram; i < SizeParallelogram; i++)       // Printing Parallelogram
				{
					myLine(X1 + 36 + i, Y1 + 7, X1 + 31, Y1 + 20, Pink);
				}
				for (int i = -SizeParallelogram; i < SizeParallelogram; i++)
				{
					myLine(X1 + 68, Y1 + 7, X1 + 63 + i, Y1 + 21, Pink);
				}
			}
			else if (Bricks[i].Shape == 't')
			{
				myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
				for (int i = -Size; i < Size; i++)
				{
					myLine(X1 + 50 + i, Y1 + 5, X1 + 50, Y1 + 20, Red);  //Printing Triangle inside brick
				}
			}
			X1 = X2;  X2 = X2 + 100;
		}
		CounterExtraBricks = 0;
	}


	else
	{
		int TotalBricks = RandomRows * 13;
		myRect(2, 2, 1312, 720, White, Black);
		for (int i = 0; i < TotalBricks; i++)
		{
			if (Bricks[i].ColourPresence != false)
			{
				if (Bricks[i].Shape == 'n')
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink); // Normal Bricks
				}
				else if (Bricks[i].Shape == 'c')
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
					myEllipse(X1 + 35, Y1 + 2, X2 - 40, Y2 - 4, Black, Green);   //Printing Circle inside brick
				}
				else if (Bricks[i].Shape == 'p')
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
					myRect(Bricks[i].x1 + 32, Bricks[i].y1 + 22, Bricks[i].x2 - 32, Bricks[i].y2 - 22, Yellow, Yellow);
					for (int i = -SizeParallelogram; i < SizeParallelogram; i++)       // Printing Parallelogram
					{
						myLine(X1 + 36 + i, Y1 + 7, X1 + 31, Y1 + 20, Pink);
					}
					for (int i = -SizeParallelogram; i < SizeParallelogram; i++)
					{
						myLine(X1 + 68, Y1 + 7, X1 + 63 + i, Y1 + 21, Pink);
					}
				}
				else if (Bricks[i].Shape == 'r')
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
					myRect(Bricks[i].x1 + 15, Bricks[i].y1 + 7, Bricks[i].x2 - 15, Bricks[i].y2 - 7, Black, Grey);  // Printing Rectangle inside brick
				}
				else if (Bricks[i].Shape == 't')
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, Black, Pink);
					for (int i = -Size; i < Size; i++)
					{
						myLine(X1 + 50 + i, Y1 + 5, X1 + 50, Y1 + 20, Red);  //Printing Triangle inside brick
					}
				}
				X1 = X2;  X2 = X2 + 100;
				if (i == 12 || i == 25 || i == 38 || i == 51 || i == 64 || i == 77 || i == 90)
				{
					X1 = 7, X2 = 107;  Y1 = Y1 + 30; Y2 = Y2 + 30;
				}
			}
			else
			{
				X1 = X2;  X2 = X2 + 100;
				if (i == 12 || i == 25 || i == 38 || i == 51 || i == 64 || i == 77 || i == 90)
				{
					X1 = 7, X2 = 107;  Y1 = Y1 + 30; Y2 = Y2 + 30;
				}
			}
		}
	}
}
void ReadingGame(Brick Bricks[91])
{
	// Used to Read Data from File
	ifstream in;
	in.open("Save.txt");
	in >> Score;
	in >> LifeLost;
	in >> TBricks;
	in >> Player;
	in >> BatColour;
	in >> BallColour;
	int rows = 0;
	for (int i = 0; i < TBricks; i++) {
		in >> Bricks[i].x1;
		in >> Bricks[i].x2;
		in >> Bricks[i].y1;   // Reading Data 
		in >> Bricks[i].y2;
		in >> Bricks[i].ColourPresence;
		in >> Bricks[i].Shape;
	}
	in.close();
	if (TBricks <= 12) {
		rows = 1;
	}
	else if (TBricks <= 25) {
		rows = 2;
	}
	else if (TBricks <= 38) {
		rows = 3;
	}
	else if (TBricks <= 51) {
		rows = 4;
	}
	else if (TBricks <= 64) {
		rows = 5;
	}
	else if (TBricks <= 77) {
		rows = 6;
	}
	else if (TBricks <= 91) {
		rows = 7;
	}
	ShowBricks(Bricks, rows);  // Function Calling
}
void HighScoresOutput(int scores[10])
{
	// Present the High Scores
	ClearScreen();
	myRect(0, 0, 1900, 1500, Black, Black);
	myDrawTextWithFont(470, 50, 70, "High Scores", Purple, Black);
	int c = 0;
	int y = 150;
	while (c != 10) {
		int sc = scores[c];
		char str[10];
		int t = 0;
		int g = 0;
		int l = 0;
		if (sc < 0) {
			str[g] = char(45);
			g++;
			sc = -1 * (sc);
		}
		t = sc;
		if (sc == 0) {
			str[0] = char(48);
			g++;

		}
		else {
			while (t > 0) {
				t = t / 10;
				l++;
			}
			l--;
			t = sc;
			while (l > 0) {
				t = sc / pow(10, l);
				sc = sc - (t* pow(10, l));
				str[g] = char(t + 48);
				g++;
				l--;
			}
			str[g] = char(sc + 48);
			g++;
		}
		str[g] = '\0';
		if (scores[c] > 0) {
			Player = HScPlayers[c];
			NameConversion();
			myDrawTextWithFont(450, y, 50, CPlayer, GBlue, Black);
			myDrawTextWithFont(680, y, 50, str, GRed, Black);
			myLine(300, y + 45, 1200, y + 45, Black);
			myLine(300, y + 45, 1200, y + 45, Black);
		}
		y = y + 50;
		c++;
	}
	myDrawTextWithFont(15, 15, 40, "<-- BACK [b]", GGreen, Black);
	myLine(3, 51, 170, 51, Black);
	bool stop = false;
	while (!stop) {
		ColorBorders();  // Function Calling
		if ((GetKeyState('B') & 0x8000)) {
			stop = true;
		}
	}
}
void HighSc(int tempscore[11])
{
	int c = 0;
	ifstream in;
	in.open("Scores.txt");
	c = 0;
	while (c != 10) {
		tempscore[c] = 0;
		c++;
	}
	c = 0;
	while (c != 10) {
		in >> HScPlayers[c] >> tempscore[c];
		c++;
	}
	Sorting(tempscore, 10);  // Calling Function
	tempscore[10] = Score;
	HScPlayers[10] = Player;
	Sorting(tempscore, 11); // Calling Function
	in.close();
	c = 0;
	ofstream out;
	out.open("Scores.txt");
	while (c != 10) {
		out << HScPlayers[c] << "\t" << tempscore[c] << endl;
		c++;
	}
	out.close();

}
void ParallelogramPenalties(Brick Bricks[91], int Index)
{
	// Defines Penalties when ball hit brick enclosing Parallelogram
	if (Bricks[Index + 1].ColourPresence == true)
	{
		if (Bricks[Index].y2 == Bricks[Index + 1].y2)
		{
			myRect(Bricks[Index + 1].x1, Bricks[Index + 1].y1, Bricks[Index + 1].x2, Bricks[Index + 1].y2, BackGround, BackGround);
			Bricks[Index + 1].ColourPresence = false;
			Penalties(Bricks, Index);
		}
	}
	if (Bricks[Index - 1].ColourPresence == true)
	{
		if (Bricks[Index].y2 == Bricks[Index - 1].y2)
		{
			myRect(Bricks[Index - 1].x1, Bricks[Index - 1].y1, Bricks[Index - 1].x2, Bricks[Index - 1].y2, BackGround, BackGround);
			Bricks[Index - 1].ColourPresence = false;
			Penalties(Bricks, Index);
		}
	}
	if (Bricks[Index + 13].ColourPresence == true)
	{
		if (Bricks[Index].x2 == Bricks[Index + 13].x2)
		{
			myRect(Bricks[Index + 13].x1, Bricks[Index + 13].y1, Bricks[Index + 13].x2, Bricks[Index + 13].y2, BackGround, BackGround);
			Bricks[Index + 13].ColourPresence = false;
			Penalties(Bricks, Index);
		}
	}
	if (Bricks[Index - 13].ColourPresence == true)
	{
		if (Bricks[Index].x2 == Bricks[Index - 13].x2)
		{
			myRect(Bricks[Index - 13].x1, Bricks[Index - 13].y1, Bricks[Index - 13].x2, Bricks[Index - 13].y2, BackGround, BackGround);
			Bricks[Index - 13].ColourPresence = false;
			Penalties(Bricks, Index);
		}
	}
}
void Penalties(Brick Bricks[91], int Index)
{
	// Defines Penalties when Ball hit Different Bricks
	if (Bricks[Index].Shape == 'n')
	{
		Score = Score + 2;
		sc1();  // Calling Function
	}
	else if (Bricks[Index].Shape == 'r')
	{
		CounterExtraBricks++;
	}
	else if (Bricks[Index].Shape == 'p')
	{
		Score = Score + 2;
		ParallelogramPenalties(Bricks, Index);
		sc1();
	}
	else if (Bricks[Index].Shape == 'c')
	{
		if (LifeLost == 5)
		{
			Score = Score + 10;
			sc1();
		}
		else if (LifeLost == 4.5)
		{
			LifeLost = LifeLost + 0.5;
			Score = Score + 5;
			sc1();
			Lives(LifeLost); // Calling Function
		}
		else
		{
			LifeLost++;
			if (LifeLost > 5)
			{
				LifeLost = 5;
			}
			Lives(LifeLost);
		}

	}
	else if (Bricks[Index].Shape == 't')
	{
		LifeLost = LifeLost - 0.5;

		Lives(LifeLost);
	}
}
bool PresenceOfBricks(Brick Bricks[91])
{
	// Check Screen has bricks or not...
	for (int i = 0; (i < TBricks); i++)
	{
		if (Bricks[i].ColourPresence)
		{
			//cout << i << " ";
			return false; // Screen has Bricks

		}
	}
	return true;  // No Bricks on Screen
}
int randomNumber(int lowerLimit, int upperLimit)
{
	// Generates a Random Number Between Two Numbers 
	srand((unsigned)time(0));
	int number = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
	return number;
}
int randomNumber(int upperLimit)
{
	// Generates Random Number from zero to Number
	int number = (rand() % upperLimit);
	return number;
}
void ExtendedMovement(Brick Bricks[91], int&inc, int &bx1, int &by1, bool &LoopTerminator)
{
	// Check whether Ball hit a brick or not 
	int Terminator = true, Selector = true;
	if ((GetKeyState('S') & 0x8000))
	{
		Save = true;
		Terminator = false;
	}
	for (int i = 90; (i > -1 && Terminator == true); i--)
	{
		if (Bricks[i].ColourPresence != false)
		{
			if (((Bricks[i].y2) - by1) >= 0)
			{
				if ((Bricks[i].x1 <= (bx1 + 25)) && (Bricks[i].x2 >= bx1))    // If ball hit the Brick
				{
					myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, BackGround, BackGround);
					Bricks[i].ColourPresence = false;
					//PlaySound(convertCharArrayToLPCWSTR("BrickHit.wav"), NULL, SND_ASYNC);  // Playing Sound
					PlaySound("BrickHit.wav", NULL, SND_ASYNC);  // Playing Sound
					Penalties(Bricks, i);
					if (LifeLost <= 0)
					{
						Terminator = false;
						LoopTerminator = true;
					}
					else
					{
						inc = -inc;
						if (Bricks[i + 1].ColourPresence)
						{
							if ((Bricks[i + 1].x1 <= (bx1 + 25)) && (Bricks[i + 1].x2 >= bx1))  // If Ball hit the border 
							{
								myRect(Bricks[i + 1].x1, Bricks[i + 1].y1, Bricks[i + 1].x2, Bricks[i + 1].y2, BackGround, BackGround);
								Bricks[i + 1].ColourPresence = false;
								//PlaySound(convertCharArrayToLPCWSTR("BrickHit.wav"), NULL, SND_ASYNC);  // Playing Sound
								PlaySound("BrickHit.wav", NULL, SND_ASYNC);
								sc1();
								Penalties(Bricks, i + 1);
							}
						}
						if (LifeLost <= 0)
						{
							Terminator = false;
							LoopTerminator = true;
						}
						else
						{
							if (Bricks[i - 1].ColourPresence)
							{
								if ((Bricks[i - 1].x1 <= (bx1 + 25)) && (Bricks[i - 1].x2 >= bx1)) // If Ball hit the border 
								{
									myRect(Bricks[i - 1].x1, Bricks[i - 1].y1, Bricks[i - 1].x2, Bricks[i - 1].y2, BackGround, BackGround);
									Bricks[i - 1].ColourPresence = false;
									//PlaySound(convertCharArrayToLPCWSTR("BrickHit.wav"), NULL, SND_ASYNC);  // Playing Sound
									PlaySound("BrickHit.wav", NULL, SND_ASYNC);
									sc1();
									Penalties(Bricks, i - 1);
								}
							}
							if (LifeLost <= 0)
							{
								Terminator = false;
								LoopTerminator = true;
							}
						}
					}
					Terminator = false;  LoopTerminator = true;
				}
			}
			if (!((!(Terminator)) && (LoopTerminator)))
			{
				if ((bx1 + 25) - Bricks[i].x1 == 0)
				{

					if ((by1 <= Bricks[i].y2) && (by1 >= Bricks[i].y1))
					{
						myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, BackGround, BackGround);    // Checking Left Side
						Bricks[i].ColourPresence = false;
						Terminator = false;
						//PlaySound(convertCharArrayToLPCWSTR("BrickHit.wav"), NULL, SND_ASYNC);  // Playing Sound
						PlaySound("BrickHit.wav", NULL, SND_ASYNC);
						LoopTerminator = true; inc = -inc;
						sc1();
						Penalties(Bricks, i);
						if (LifeLost <= 0)
						{
							Terminator = false;
							LoopTerminator = true;
						}
					}
				}
			}
			else if (!((!(Terminator)) && (LoopTerminator)))
			{
				if ((bx1)-Bricks[i].x2 == 0)
				{
					if ((by1 <= Bricks[i].y2) && (by1 >= Bricks[i].y1))
					{
						myRect(Bricks[i].x1, Bricks[i].y1, Bricks[i].x2, Bricks[i].y2, BackGround, BackGround);    // Checking Right side
						Bricks[i].ColourPresence = false;
						//PlaySound(convertCharArrayToLPCWSTR("BrickHit.wav"), NULL, SND_ASYNC);  // Playing Sound
						PlaySound("BrickHit.wav", NULL, SND_ASYNC);
						Terminator = false;
						LoopTerminator = true; inc = -inc;
						sc1();
						Penalties(Bricks, i);
					}
				}
			}
		}
		if (LifeLost <= 0)
		{
			Terminator = false;
			LoopTerminator = true;
		}

		if (PresenceOfBricks(Bricks))
		{
			Terminator = false;
		}
	}

}
void ValuesInArray(Brick Bricks[91], int RandomRows)
{
	// Initializing Array with Attributes of Bricks
	int TotalBricks = RandomRows * 13; bool Terminator = true;
	int PinkBricks = ((TotalBricks * 60) / 100);
	int OtherShapes = TotalBricks - PinkBricks;
	int X1 = 7, X2 = 107, Y2 = 38, Y1 = 8, CounterForID = 0, PinkBrickCounter = 0, OtherBrickCounter = 0, TotalBrickCounter = 0;
	TBricks = TotalBricks;
	if (CounterExtraBricks > 0)
	{
		int i = 0;
		for (; (i <= ExtraBrick && Terminator == true); i++)
		{
			if (Bricks[i].ColourPresence == true)
			{
				i = ExtraBrick + 1;            // Checks Number of Current Rows on Screen
				ExtraBrick = ExtraBrick + 13;
			}
		}
		if (ExtraBrick <= 90)
		{
			if (ExtraBrick == 12)
			{
				X1 = 7, X2 = 107, Y1 = 8, Y2 = 38;
			}
			else if (ExtraBrick == 25)
			{
				X1 = 7, X2 = 107, Y1 = 38, Y2 = 68;
			}
			else if (ExtraBrick == 38)
			{
				X1 = 7, X2 = 107, Y1 = 68, Y2 = 98;
			}
			else if (ExtraBrick == 51)
			{
				X1 = 7, X2 = 107, Y1 = 98, Y2 = 128;
			}
			else if (ExtraBrick == 64)
			{
				X1 = 7, X2 = 107, Y1 = 128, Y2 = 158;
			}
			else if (ExtraBrick == 77)
			{
				X1 = 7, X2 = 107, Y1 = 158, Y2 = 188;
			}
			else if (ExtraBrick == 90)
			{
				X1 = 7, X2 = 107, Y1 = 188, Y2 = 218;
			}
			int j = ExtraBrick - 12; TBricks = ExtraBrick + 1;
			for (; j < ExtraBrick + 1; j++)
			{
				Bricks[j].x1 = X1; Bricks[j].x2 = X2, Bricks[j].y1 = Y1, Bricks[j].y2 = Y2;
				X1 = X2;  X2 = X2 + 100;
				if (j == ExtraBrick - 5 || j == ExtraBrick - 8 || j == ExtraBrick - 9 || j == ExtraBrick - 1 || j == ExtraBrick - 4 || j == ExtraBrick || j == ExtraBrick - 2)
				{
					Bricks[j].Shape = 'n';  // Normal Bricks
				}
				else if (j == ExtraBrick - 3 || j == ExtraBrick - 7)
				{
					Bricks[j].Shape = 'p';  // Bricks enclosing Parallelogram
				}
				else if (j == ExtraBrick - 6 || j == ExtraBrick - 10)
				{
					Bricks[j].Shape = 't';  // Bricks enclosing Triangle
				}
				else if (j == ExtraBrick - 11 || j == ExtraBrick - 12)
				{
					Bricks[j].Shape = 'c';  // Bricks enclosing Circle
				}
				Bricks[j].ColourPresence = true;
			}
			ShowBricks(Bricks, RandomRows); // Calling Function
		}
		else
		{
			CounterExtraBricks = 0;
			ExtraBrick = 12;
			Score = Score - 10;
			if (Score < 0)
			{
				Score = 0;
			}
			sc1();
		}

	}
	else
	{

		for (int i = 0; i < TotalBricks; i++)
		{
			int random = randomNumber(21);
			if ((random <= 16) && (PinkBrickCounter < PinkBricks))
			{
				Bricks[i].x1 = X1; Bricks[i].x2 = X2; Bricks[i].y1 = Y1; Bricks[i].y2 = Y2;
				Bricks[i].ID = CounterForID; CounterForID++; Bricks[i].Shape = 'n';  // Normal bricks
				Bricks[i].ColourPresence = true;
				PinkBrickCounter++;
				X1 = X2;  X2 = X2 + 100;
				TotalBrickCounter++;
				if ((TotalBrickCounter % 13) == 0)
				{
					X1 = 7, X2 = 107;  Y1 = Y2; Y2 = Y2 + 30;
				}
			}
			else if (random > 16 && OtherBrickCounter < OtherShapes)
			{
				Bricks[i].x1 = X1; Bricks[i].x2 = X2; Bricks[i].y1 = Y1; Bricks[i].y2 = Y2;
				X1 = X2;  X2 = X2 + 100;
				if (random == 17)
				{
					Bricks[i].Shape = 'r';   // Bricks enclosing Rectangle
					Bricks[i].ID = CounterForID; CounterForID++;
					Bricks[i].ColourPresence = true;
				}
				else if (random == 18)
				{
					Bricks[i].Shape = 'p';   // Bricks enclosing Parallelogram
					Bricks[i].ID = CounterForID; CounterForID++;
					Bricks[i].ColourPresence = true;
				}
				else if (random == 19)
				{
					Bricks[i].Shape = 'c';   // Bricks enclosing Circle
					Bricks[i].ID = CounterForID; CounterForID++;
					Bricks[i].ColourPresence = true;
				}
				else if (random == 20)
				{
					Bricks[i].Shape = 't';   // Bricks enclosing Triangle
					Bricks[i].ID = CounterForID; CounterForID++;
					Bricks[i].ColourPresence = true;
				}
				OtherBrickCounter++;

				TotalBrickCounter++;
				if ((TotalBrickCounter % 13) == 0)
				{
					X1 = 7, X2 = 107;  Y1 = Y2; Y2 = Y2 + 30;
				}
			}
			else
			{
				i--;
			}
		}
	}
}
void Movement(Brick Bricks[91], int & r1x, int & r2x, int & r1y, int & r2y, int RandomRows)
{
	// Controls Movement of Ball
	int bx1 = (r1x + r2x - 25) / 2;
	int by1 = 625; //upper y1 of the bat.
	int inc; int tempy; int tempx; bool Ter = false;
	bool Flag = false;
	int Rborder; // temp variable used to store the difference between right border and bx1 + 25(of ball)
	int Lborder; // temp variable used to store the difference between left border and bx1 (of ball)
	int RandomRows2 = 7 - RandomRows;
	int DirectionT = 0; // Checks the distance between the centre of the ball and the start of the bat
	bool loop2 = false;
	bool loop1 = false;
	inc = 13;
	while (!Flag)
	{
		loop1 = false;
		loop2 = false;
		DirectionT = ((bx1 + bx1 + 25) / 2) - r1x;
		if (DirectionT <= 36) {
			inc = 26;   // Angle 30
		}
		else if (DirectionT > 36 && DirectionT <= 72) {
			inc = 9; // Angle 60
		}
		else if (DirectionT > 72 && DirectionT <= 108) {
			inc = 0;  // Angle 0
		}
		else if (DirectionT > 108 && DirectionT <= 144) {
			inc = -9;  // Angle 120
		}
		else if (DirectionT > 144) {
			inc = -26;  // Angle 150
		}
		// just to randomize the ball every loop

		while (!(loop1))
		{
			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = 18 + r1x; r2x = 18 + r2x;  //Rightward
				if (r2x > 1300)
				{
					r2x = 1310;
					r1x = 1120;
				}

				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);

			}
			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = r1x - 18; r2x = r2x - 18;//Leftward
				if (r1x < 4)
				{
					r1x = 10;
					r2x = 190;
				}
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
			}
			if (GetKeyState('S') & 0x8000)
			{
				Save = true;
				Flag = true; loop1 = true;
			}
			else
			{
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
				by1 = by1 - 15;
				bx1 = bx1 - inc;
				if (by1 < 9)
				{
					inc = -inc;
					loop1 = true;
				}
				Rborder = 1312 - (bx1 + 25);
				Lborder = bx1 - 2;
				if (Rborder < 0) {
					bx1 = 1310 - 25;
				}
				if (Lborder < 0) {
					bx1 = 4;
				}
				if (Lborder < 15) {
					inc = -inc;
				}
				if (Rborder < 15) {
					inc = -inc;
				}
				//for tan 30, rate in change of x be +42, tan60 x be +13 and for the opposite direction switch signs
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, BallColour, BallColour);

				//tempy = (by1 + 25) - (248 - (RandomRows2 * 30));

				/*if (tempy > 0 && tempy <= 25)
				{
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, Black, Black);
				by1 = RandomRows * 30 + 8;
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, White, White);

				}*/
				for (int c = 90; (c > -1 && (!(Ter))); c--)
				{
					tempy = by1 - Bricks[c].y2;
					if (Bricks[c].ColourPresence)
					{
						if (tempy > 0 && tempy < 15)
						{
							myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
							by1 = Bricks[c].y2;
							myEllipse(bx1, by1, bx1 + 25, by1 + 25, BallColour, BallColour);
							Ter = true;
						}
					}
				}
				Ter = false;
				for (int c = 90; (c > -1 && (!(Ter))); c--)
				{
					tempx = bx1 - Bricks[c].x2;
					if (Bricks[c].ColourPresence)
					{
						if (tempx > 0 && tempx < 15)
						{
							if (by1 <= Bricks[c].y2&&by1 >= Bricks[c].y1)
							{
								myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
								bx1 = Bricks[c].x2;
								myEllipse(bx1, by1, bx1 + 25, by1 + 25, BallColour, BallColour);
								inc = -inc;
								Ter = true;
							}
						}
					}
				}
				Ter = false;
				for (int c = 90; (c > -1 && (!(Ter))); c--)
				{
					tempx = Bricks[c].x1 - (bx1 + 25);
					if (Bricks[c].ColourPresence)
					{
						if (tempx > 0 && tempx < 15)
						{
							if (by1 <= Bricks[c].y2&&by1 >= Bricks[c].y1)
							{
								myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
								bx1 = Bricks[c].x1 - 25;
								myEllipse(bx1, by1, bx1 + 25, by1 + 25, BallColour, BallColour);
								inc = -inc;
								Ter = true;
							}
						}
					}
				}
				Ter = false;
				Sleep(40);
				ExtendedMovement(Bricks, inc, bx1, by1, loop1);
			}
		}
		//inc = -inc;
		if (!Save)
		{
			myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
		}
		if (LifeLost <= 0)
		{
			loop2 = true;
			Flag = true;
		}
		while (!(loop2))
		{
			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = r1x - 18; r2x = r2x - 18;//Leftward
				if (r1x < 4)
				{
					r1x = 10;
					r2x = 190;
				}
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
			}
			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = 18 + r1x; r2x = 18 + r2x;  //Rightward
				if (r2x > 1300)
				{
					r2x = 1310;
					r1x = 1120;
				}
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
			}
			if (GetKeyState('S') & 0x8000)
			{
				Save = true;
				Flag = true; loop2 = true;
			}
			else
			{
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
				by1 = by1 + 15;
				bx1 = bx1 + inc;
				Rborder = 1312 - (bx1 + 25);
				Lborder = bx1 - 2;
				if (Rborder < 0) {
					bx1 = 1310 - 25;
				}
				if (Lborder < 0) {
					bx1 = 4;
				}
				if (Lborder < 25) {
					inc = -inc;
				}
				if (Rborder < 25) {
					inc = -inc;
				}
				tempy = r1y - (by1 + 25);
				if (tempy < 0) {
					myEllipse(bx1, r1y - 25, bx1 + 25, r1y, BallColour, BallColour);
					Sleep(40);
					loop2 = true;
					by1 = r1y - 25;
				}
				ExtendedMovement(Bricks, inc, bx1, by1, loop2);
				//for tan 30, rate in change of x be +42, tan60 x be +13 and for the opposite direction switch signs
				if (loop2 == false) {
					myEllipse(bx1, by1, bx1 + 25, by1 + 25, BallColour, BallColour);
				}
				if (by1 == r1y) {
					loop2 = true;
				}
				Sleep(40);
				if (CounterExtraBricks > 0 && loop2 == true)
				{
					CounterExtraBricks = 1;
					ValuesInArray(Bricks, RandomRows);
					//Sleep(500);
				}
				//Sleep(10);
				if (PresenceOfBricks(Bricks))
				{
					ending = true;
				}
				else
				{
					ending = false;
				}
			}
			if (ending)
			{
				Flag = true; loop2 = true;
			}
		}
		if (by1 + 25 >= r1y) {
			if ((bx1 > r2x) || (bx1 + 25 < r1x))
			{
				myEllipse(bx1, by1, bx1 + 25, by1 + 25, BackGround, BackGround);
				Sleep(150);
				Flag = true;
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
			}

		}
	}
}
void PreLaunch(int & r1x, int & r2x, int & r1y, int & r2y)
{
	// Controls Movement of Bat
	char Move = 'A'; bool Flag = false;
	int Temp = (r1x + r2x - 25) / 2;
	myRect(r1x, 650, r2x, r2y, BackGround, BatColour); // Bat
	myEllipse(Temp, 625, Temp + 25, 650, BallColour, BallColour); // Ball

	while (!Flag)
	{
		Move = _getch();

		if (r1x > 4 && r2x < 1300)
		{
			if (GetKeyState(VK_RIGHT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = 9 + r1x; r2x = 9 + r2x;  //Rightward
				if (r2x > 1300)
				{
					r2x = 1310;
					r1x = 1120;
				}
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
				myEllipse(Temp, 625, Temp + 25, 650, BackGround, BackGround);
				myEllipse((r1x + r2x - 25) / 2, 625, ((r1x + r2x - 25) / 2) + 25, 650, BallColour, BallColour);
				Temp = (r1x + r2x - 25) / 2;
			}

			if (GetKeyState(VK_LEFT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = r1x - 9; r2x = r2x - 9;//Leftward
				if (r1x < 4)
				{
					r1x = 10;
					r2x = 190;
				}
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
				myEllipse(Temp, 625, Temp + 25, 650, BackGround, BackGround);
				myEllipse((r1x + r2x - 25) / 2, 625, ((r1x + r2x - 25) / 2) + 25, 650, BallColour, BallColour);
				Temp = (r1x + r2x - 25) / 2;
			}
			if (GetKeyState('S') & 0x8000)
			{
				Save = true;
				Flag = true;
			}
		}
		else
		{
			if (r2x >= 1300 && GetKeyState(VK_LEFT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = r1x - 9; r2x = r2x - 9;        //Leftward
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
				myEllipse(Temp, 625, Temp + 25, 650, BackGround, BackGround);
				myEllipse((r1x + r2x - 25) / 2, 625, ((r1x + r2x - 25) / 2) + 25, 650, BallColour, BallColour);
				Temp = (r1x + r2x - 25) / 2;
			}
			if (r1x <= 10 && GetKeyState(VK_RIGHT) & 0x8000)
			{
				myRect(r1x, r1y, r2x, r2y, BackGround, BackGround);
				r1x = 9 + r1x; r2x = 9 + r2x;            //Rightward
				myRect(r1x, r1y, r2x, r2y, BackGround, BatColour);
				myEllipse(Temp, 625, Temp + 25, 650, BackGround, BackGround);
				myEllipse((r1x + r2x - 25) / 2, 625, ((r1x + r2x - 25) / 2) + 25, 650, BallColour, BallColour);
				Temp = (r1x + r2x - 25) / 2;
			}
			if (GetKeyState('S') & 0x8000)
			{
				Save = true;
				Flag = true;
			}
		}
		if (Move == ' ')
		{
			Flag = true;
		}
	}

}
int main()
{
	int RandomRows = 0;
	ShowConsoleCursor(false);
	Brick Bricks[91];
	int x1 = 7, x2 = 107, y2 = 38, y1 = 8, r1x = 500, r2x = 680, r1y = 650, r2y = 675;
	int c = 0, a = 1;
	int size = 5;
	int t1 = 625, t2 = 650, inc = 0, len = 180, result = 0, t = 0;
	int temp2 = 0;
	char option = 'g';
	int tempscore[11];
	while (!(option == 'n' || option == 'c')) {
		option = Start();
		if (option == 'n') {
			ClearScreen();
			BatBallColour();
			ClearScreen();
			cout << "Enter your name, Player: ";
			_getch();
			_getch();
			getline(cin, Player);
			ClearScreen();
			NameConversion();
			RandomRows = randomNumber(4, 7);
			randomNumber(4, 7);
			myRect(2, 2, 1312, 720, White, BackGround);
			ValuesInArray(Bricks, RandomRows);
			ShowBricks(Bricks, RandomRows);
		}
		else if (option == 'c') {
			ClearScreen();
			myRect(2, 2, 1312, 720, White, Black);
			ReadingGame(Bricks);
		}
		else if (option == 'i') {
			ClearScreen();
			Instructions(Bricks);
			ClearScreen();
		}
		else if (option == 'h')
		{
			myRect(0, 0, 1500, 1500, Black, Black);
			ifstream in;
			in.open("Scores.txt");
			int c = 0;
			while (c != 10) {
				tempscore[c] = 0;
				c++;
			}
			c = 0;
			while (c != 10) {
				in >> HScPlayers[c] >> tempscore[c];
				c++;
			}
			Sorting(tempscore, 10);
			c = 0;
			HighScoresOutput(tempscore);

		}
		else if (option == 'e') {
			return 0;
		}
	}
	while (LifeLost > 0 && !Save && !ending)
	{
		Lives(LifeLost);
		sc1();
		PreLaunch(r1x, r2x, r1y, r2y);
		if (Save)
		{
		}
		else
		{
			Movement(Bricks, r1x, r2x, r1y, r2y, RandomRows);
			if (ending == true)
			{
			}
			else
			{
				if (Save)
				{

				}
				else
				{
					r1x = 500, r2x = 680, r1y = 650, r2y = 675;
					LifeLost--;
				}
			}
		}
	}

	if (ending || (LifeLost <= 0))
	{
		HighSc(tempscore);
		Lost();

	}
	if (Save) {
		SaveGame(Bricks);
		Ending();
		Sleep(2500);
	}

	return 0;

}