#include "iGraphics.h"
#include <GL\glut.h>

void background();
void about();
void instructionpage();
void startpage();
// void draweasypage();
void drawscorepage();
void aboutbuttonclick();
void instructionbuttonclickhandler();
void startbuttonclickhandler();
void backbuttonclickhandler();
// void easybuttonclickhandler();
void scorebuttonclickhandler();
void shootBall(int mx, int my);
void moveGoalkeeper(unsigned char key);
int aboutpage = 0;
int aboutbutton = 0;
int instructionbuttonclick = 0;
int instructionpg = 0;
int startpg = 0;
int startbuttonclick = 0;
int bg = 1;
// int easypage = 0;
int scoreapage = 0;
bool musicOn = true;
int x = 470, y = 320, r = 20;
int bx = 470, by = 95;
/*
	function iDraw() is called again and again by the system.

	*/
void moveGoalkeeper(unsigned char key)
{
	if (key == 'w')
	{
		iShowBMP2(470, 320, "picture\\up.bmp", 0);
	}
	if (key == 'a')
	{
		iShowBMP2(470, 320, "picture\\bottom left.bmp", 0);
	}
	if (key == 'd')
	{
		iShowBMP2(470, 320, "picture\\bottom right.bmp", 0);
	}
	if (key == 'e')
	{
		iShowBMP2(470, 320, "picture\\right corner.bmp", 0);
	}
	if (key == 'q')
	{
		iShowBMP2(470, 320, "picture\\left corner.bmp", 0);
	}
}
void iDraw()
{
	// place your drawing codes here
	iClear();

	if (bg == 1)
	{
		background();
	}
	else if (aboutbutton == 1)
	{
		about();
	}
	else if (instructionpg == 1)
	{
		instructionpage();
	}
	else if (startpg == 1)
	{
		startpage();
	}
	/*else if (easypage == 1)
	{
		draweasypage();
	}*/
	else if (scoreapage == 1)
	{
		drawscorepage();
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		printf("x = %d, y= %d\n", mx, my);
		// x += 10;
		// y += 10;
		if (bg == 1 && (mx >= 434 && mx <= 564) && (my >= 337 && my <= 378))
		{
			aboutbuttonclick();
		}
		else if (bg == 1 && (mx >= 434 && mx <= 564) && (my >= 280 && my <= 320))
		{
			instructionbuttonclickhandler();
		}
		else if (bg == 1 && (mx >= 435 && mx <= 564) && (my >= 395 && my <= 450))
		{
			startbuttonclickhandler();
		}
		/*else if (bg == 1 && (mx >= 407 && mx <= 590) && (my >= 260 && my <= 300))
		{
			easybuttonclickhandler();
		}*/
		else if (bg == 1 && (mx >= 435 && mx <= 565) && (my >= 215 && my <= 258))
		{
			scorebuttonclickhandler();
		}
		else if (bg == 1 || aboutbutton == 1 || instructionpg == 1 || startpg == 1)
		{
			if ((mx >= 75 && mx <= 195) && (my >= 565 && my <= 600))
			{
				backbuttonclickhandler();
			}
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// place your codes here
		x -= 10;
		y -= 10;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key)
{
	if (key == 'u')
	{
		exit(0);
	}
	if (key == 'w')
	{
		iShowBMP2(470, 320, "picture\\up.bmp", 0);
	}
	if (key == 'a')
	{
		iShowBMP2(470, 320, "picture\\bottom left.bmp", 0);
	}
	if (key == 'd')
	{
		iShowBMP2(470, 320, "picture\\bottom right.bmp", 0);
	}
	if (key == 'e')
	{
		iShowBMP2(470, 320, "picture\\right corner.bmp", 0);
	}
	if (key == 'q')
	{
		iShowBMP2(470, 320, "picture\\left corner.bmp", 0);
	}
	if (key == GLUT_KEY_F1)
	{
		if (musicOn)
		{
			PlaySound(0, 0, 0);
			musicOn = false;
		}
		else
		{
			PlaySound("song.wav", NULL, SND_LOOP | SND_ASYNC);
			musicOn = true;
		}
	}
	if(key==' '){
		iShowBMP2(470, 320, "picture\\stand.bmp", 0);
	}
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	// place your codes for other keys here
}
void background()
{
	iShowBMP2(0, 0, "picture\\menu.bmp", 0);
	iSetColor(255, 255, 255);
	iText(430, 500, "Saving Penalty", GLUT_BITMAP_TIMES_ROMAN_24);
}
void instructionpage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(0, 0, "picture\\how.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
}
void startpage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(50, 0, "picture\\1.bmp", 0);
	// iShowBMP2(400, 150, "picture\\e-m-h.bmp", 0);
	iShowBMP2(470, 95, "picture\\ball.bmp", 0);
	iShowBMP2(250, 515, "picture\\target.bmp", 0);
	iShowBMP2(480, 520, "picture\\target.bmp", 0);
	iShowBMP2(740, 515, "picture\\target.bmp", 0);
	iShowBMP2(240, 340, "picture\\target.bmp", 0);
	iShowBMP2(750, 340, "picture\\target.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
}
/*void draweasypage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(50, 0, "picture\\1.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
}*/
void drawscorepage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(50, 0, "picture\\1.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
}
void aboutbuttonclick()
{
	bg = 0;
	aboutbutton = 1;
}
void instructionbuttonclickhandler()
{
	bg = 0;
	aboutbutton = 0;
	instructionpg = 1;
}
void startbuttonclickhandler()
{
	bg = 0;
	aboutbutton = 0;
	instructionpg = 0;
	startpg = 1;
}
void about()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(220, 0, "picture\\about me.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
}
void scorebuttonclickhandler()
{
	bg = 0;
	aboutbutton = 0;
	instructionpg = 0;
	startpg = 0;
	scoreapage = 1;
}
void backbuttonclickhandler()
{
	bg = 1;
	aboutbutton = 0;
	instructionpg = 0;
	startpg = 0;
	scoreapage = 0;
}
/*void easybuttonclickhandler()
{
	bg = 0;
	aboutbutton = 0;
	instructionpg = 0;
	startpg = 0;
	easypage = 1;
}
*/

int main()
{
	// place your own initialization codes here.
	if (musicOn)
	{
		PlaySound("song.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	iInitialize(1000, 600, "2D PENALTY SAVING GAME");
	return 0;
}
