#include "iGraphics.h"
#include <GL\glut.h>
#include <math.h>

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
void collision(int mx, int my, unsigned char key);
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
int x = 430, y = 300, r = 20;
int bx = 470, by = 95;
int state;
char click;
int ballspeed = 2;
int ballstate = 0;
int ax, ay;
int ballx, bally;
int score = 0;
int sx,sy;
char point[10000];
int mouseX = 0, mouseY = 0;
char lastKey = '\0';
/*
	function iDraw() is called again and again by the system.

	*/
char a[7][100] = {{"picture\\stand.bmp"}, {"picture\\bottom left.bmp"}, {"picture\\bottom right.bmp"}, {"picture\\right corner.bmp"}, {"picture\\left corner.bmp"}, {"picture\\top right.bmp"}, {"picture\\up.bmp"}};

char b[5][100] = {{"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}};

bool collisionDetected = false; // Flag to track collision detection
int collisionX = 0, collisionY = 0; // Position of collision

void collision(int sx, int sy, char click)
{
    if ((sx >= 300 && sx <= 430) && (sy >= 350 && sy <= 410) && click == 'w') // Example collision condition
    {
        collisionDetected = true; // Set flag to true
        iSetColor(255, 255, 255);
        iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
        score++;
        sprintf(point, "Score: %d", score);
    }
	else if ((sx >= 430 && sx <= 770) && (sy >= 350 && sy <= 410) && click == 'a') // Example collision condition
    {
        collisionDetected = true; // Set flag to true
        collisionX = sx;          // Capture collision position
        collisionY = sy;
        iSetColor(255, 255, 255);
        iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
        score++;
        sprintf(point, "Score: %d", score);
    }
	else if ((sx >= 430 && sx <= 5000) && (sy >= 400 && sy <= 530) && click == 's') // Example collision condition
    {
        collisionDetected = true; // Set flag to true
        collisionX = sx;          // Capture collision position
        collisionY = sy;
        iSetColor(255, 255, 255);
        iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
        score++;
        sprintf(point, "Score: %d", score);
    }
	else if ((sx >= 300 && sx <= 430) && (sy >= 420 && sy <= 530) && click == 'e') // Example collision condition
    {
        collisionDetected = true; // Set flag to true
        collisionX = sx;          // Capture collision position
        collisionY = sy;
        iSetColor(255, 255, 255);
        iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
        score++;
        sprintf(point, "Score: %d", score);
    }
	else if ((sx >= 430 && sx <= 770) && (sy >= 420 && sy <= 530) && click == 'd') // Example collision condition
    {
        collisionDetected = true; // Set flag to true
        collisionX = sx;          // Capture collision position
        collisionY = sy;
        iSetColor(255, 255, 255);
        iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
        score++;
        sprintf(point, "Score: %d", score);
    }
}

void iDraw()
{
    iClear();
    if (bg == 1)
    {
        ballstate = 0;
        by = 95;
        bx = 470;
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
    else if (scoreapage == 1)
    {
        drawscorepage();
    }

    // Check if a collision occurred and render a visual effect
    if (collisionDetected)
    {
        iSetColor(255, 0, 0); // Set color for collision visualization
        iFilledCircle(collisionX, collisionY, 20); // Draw a circle at the collision position
        iSetColor(255, 255, 255);
        iText(collisionX - 50, collisionY + 30, "Collision!", GLUT_BITMAP_HELVETICA_18);
    }

    if (ballstate == 1 && ax >= 252 && ax <= 755 && ay >= 345 && ay <= 534)
    {
        for (int i = 0; i < 5; i++)
        {
            if (ballx >= 252 && ballx <= 755 && bally >= 95 && bally <= 534)
            {
                iShowBMP2(bx, by, b[i], 0);
                by += (ballspeed * (bally - 95) / (sqrt((bally - 95) * (bally - 95) + (ballx - 470) * (ballx - 470))));
                bx += ballspeed * (ballx - 470) / (sqrt((bally - 95) * (bally - 95) + (ballx - 470) * (ballx - 470)));
                if ((bx < ballx + 100 && by < 100 + bally && bx > ballx - 100 && by > bally - 100) || (bx < 100 || by < 30 || bx > iScreenWidth - 100 || by > iScreenHeight - 100))
                {
                    ballstate = 0;
                    by = 95;
                    bx = 470;
                    break;
                }
            }
            else
            {
                iShowBMP2(bx, by, b[i], 0);
                break;
            }
        }
    }
    else
    {
        ballstate = 0;
    }
	iSetColor(255, 255, 255); // Set text color (white)
    iText(80, 520, point, GLUT_BITMAP_TIMES_ROMAN_24);
}

void resetCollision()
{
    collisionDetected = false; // Reset the flag
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
		if (startpg == 1)
		{
			ballstate = 1;
			ballx = mx;
			bally = my;
			ax = mx;
			ay = my;
		}
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
		else if (bg == 1 || aboutbutton == 1 || instructionpg == 1 || startpg == 1 || scoreapage == 1)
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
	 if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Capture mouse coordinates
        mouseX = mx;
        mouseY = my;

        // Trigger collision function with the current mouse coordinates and last pressed key
        collision(mouseX, mouseY, lastKey);
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
		state = 1;
		click=key;

	}
	if (key == 'a')
	{
		state = 2;
		click=key;
	}
	if (key == 'd')
	{
		state = 3;
		click=key;
	}
	if (key == 'e')
	{
		state = 4;
		click=key;
	}
	if (key == 'v')
	{
		state = 5;
		click=key;
	}
	if (key == 's')
	{
		state = 6;
		click=key;
	}
	if (key == 'f')
	{
		state = 0;
		click=key;
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
	 lastKey = key;

    // Example: You can also trigger collision here if needed
    collision(mouseX, mouseY, lastKey);
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
	// iShowBMP2(470, 320, "picture\\stand.bmp", 0);
	// iShowBMP2(470, 95, "picture\\ball.bmp", 0);
	iShowBMP2(250, 515, "picture\\target.bmp", 0);
	iShowBMP2(480, 520, "picture\\target.bmp", 0);
	iShowBMP2(740, 515, "picture\\target.bmp", 0);
	iShowBMP2(240, 340, "picture\\target.bmp", 0);
	iShowBMP2(750, 340, "picture\\target.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
	iShowBMP2(x, y, a[state], 0);
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
	iSetTimer(20, iDraw);
	iSetTimer(2000, resetCollision); // Reset collision after 2 seconds
	iInitialize(1000, 600, "2D PENALTY SAVING GAME");
	return 0;
}
