#include "iGraphics.h"
#include <GL\glut.h>
#include <math.h>

void background();
void about();
void instructionpage();
void startpage();
void drawscorepage();
void aboutbuttonclick();
void instructionbuttonclickhandler();
void startbuttonclickhandler();
void backbuttonclickhandler();
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

int sx, sy;
int score = 0;
static int highestScore = 0;
char point[100];
char highestScoreText[100];
int mouseX = 0, mouseY = 0;
char lastKey = '\0';
bool scoreReset = false;
int miss = 0;

bool ballVisible = true;

char UserScores[10][15] = {};
struct PlayerScore
{
	float pscore;
};
struct PlayerScore HighScores[11];

char a[7][100] = {{"picture\\stand.bmp"}, {"picture\\bottom left.bmp"}, {"picture\\bottom right.bmp"}, {"picture\\right corner.bmp"}, {"picture\\left corner.bmp"}, {"picture\\top right.bmp"}, {"picture\\up.bmp"}};

char b[5][100] = {{"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}, {"picture\\ball.bmp"}};

bool collisionDetected = false;
int collisionX = 0, collisionY = 0;

void collision(int sx, int sy, char click)
{
	if ((sx >= 300 && sx <= 430) && (sy >= 350 && sy <= 410) && click == 'w')
	{
		collisionDetected = true;
		iSetColor(255, 255, 255);
		iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
		score++;

		sprintf(point, "Score: %d", score);

		if (score > highestScore)
		{
			HighScores[10].pscore = score;
			sprintf(highestScoreText, "Highest Score: %d", score);
		}
	}
	else if ((sx >= 430 && sx <= 770) && (sy >= 350 && sy <= 410) && click == 'a')
	{
		collisionDetected = true;
		collisionX = sx;
		collisionY = sy;
		iSetColor(255, 255, 255);
		iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
		score++;
		ballspeed++;
		sprintf(point, "Score: %d", score);

		if (score > highestScore)
		{
			HighScores[10].pscore = score;
			sprintf(highestScoreText, "Highest Score: %d", score);
		}
	}
	else if ((sx >= 430 && sx <= 5000) && (sy >= 400 && sy <= 530) && click == 's')
	{
		collisionDetected = true;
		collisionX = sx;
		collisionY = sy;
		iSetColor(255, 255, 255);
		iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
		score++;
		sprintf(point, "Score: %d", score);
		ballspeed++;

		if (score > highestScore)
		{
			HighScores[10].pscore = score;
			sprintf(highestScoreText, "Highest Score: %d", score);
		}
	}
	else if ((sx >= 300 && sx <= 430) && (sy >= 420 && sy <= 530) && click == 'e')
	{
		collisionDetected = true;
		collisionX = sx;
		collisionY = sy;
		iSetColor(255, 255, 255);
		iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
		score++;
		sprintf(point, "Score: %d", score);
		ballspeed++;

		if (score > highestScore)
		{
			HighScores[10].pscore = score;
			sprintf(highestScoreText, "Highest Score: %d", score);
		}
	}
	else if ((sx >= 430 && sx <= 770) && (sy >= 420 && sy <= 530) && click == 'd')
	{
		collisionDetected = true;
		collisionX = sx;
		collisionY = sy;
		iSetColor(255, 255, 255);
		iText(120, 530, "Score:", GLUT_BITMAP_TIMES_ROMAN_24);
		score++;
		sprintf(point, "Score: %d", score);
		ballspeed++;

		if (score > highestScore)
		{
			HighScores[10].pscore = score;
			sprintf(highestScoreText, "Highest Score: %d", score);
		}
	}
}

void saveHighestScore()
{
	FILE *file = fopen("E:\\term project\\highest_score.txt", "w");
	if (file != NULL)
	{
		fprintf(file, "%d", highestScore);
		fclose(file);
		printf("Highest score saved: %d\n", highestScore);
	}
	else
	{
		printf("Error: Could not open file to save highest score.\n");
	}
}

void loadHighestScore()
{
	FILE *file = fopen("E:\\term project\\highest_score.txt", "r");
	if (file != NULL)
	{
		if (fscanf(file, "%d", &highestScore) == 1)
		{
			printf("Highest score loaded: %d\n", highestScore);
		}
		fclose(file);
	}
	else
	{
		printf("Error: Could not open file to load highest score.\n");
	}
}

void resetScore()
{
	score = 0;
}

void ShowHighScores()
{
	iSetColor(255, 255, 255);
	iText(220, 625, "LEADERBOARD", GLUT_BITMAP_TIMES_ROMAN_24);
	iLine(220, 618, 398, 618);
	iLine(220, 613, 398, 613);
	int i;
	for (int i = 0; i < 10; i++)
	{
		sprintf(UserScores[i], "%g", HighScores[i].pscore);
	}
	for (i = 0; i < 10; i++)
	{
		if (strcmp(UserScores[i], "0") == 0)
			break;
		iSetColor(255, 255, 255);
		iText(390, 530 - 40 * i, UserScores[i], GLUT_BITMAP_HELVETICA_18);
	}
}

void SortScores()
{
	int i, j;
	float temp;
	char name[35] = "";
	FILE *fptr = fopen("highescore.txt", "r");
	for (i = 0; i < 10; i++)
	{
		fscanf(fptr, "%f\n", &HighScores[i].pscore);
	}
	for (i = 0; i < 10; i++)
	{
		for (j = i + 1; j < 11; j++)
		{
			if (HighScores[i].pscore < HighScores[j].pscore)
			{
				temp = HighScores[i].pscore;
				HighScores[i].pscore = HighScores[j].pscore;
				HighScores[j].pscore = temp;
			}
		}
	}
	fclose(fptr);
	fptr = fopen("highscore.txt", "w");
	for (i = 0; i < 10; i++)
	{
		fprintf(fptr, "%g\n", HighScores[i].pscore);
	}
	fclose(fptr);
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

	if (collisionDetected)
	{
		iSetColor(255, 0, 0);
		iFilledCircle(collisionX, collisionY, 20);
		iSetColor(255, 255, 255);
		iText(collisionX - 50, collisionY + 30, "Saved!", GLUT_BITMAP_HELVETICA_18);
	}

	if (ballstate == 1 && ax >= 252 && ax <= 755 && ay >= 345 && ay <= 534 && ballVisible)
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
	iSetColor(255, 255, 255);
	iText(80, 520, point, GLUT_BITMAP_TIMES_ROMAN_24);
}

void resetBall()
{
	ballVisible = true;
	bx = 470;
	by = 95;
	printf("Ball reset!\n");
}

void resetCollision()
{
	collisionDetected = false;
}

void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
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
		if (mx >= bx && mx <= bx + r * 2 && my >= by && my <= by + r * 2)
		{
			ballVisible = false;
			printf("Ball vanished! Mouse clicked at (%d, %d)\n", mx, my);
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		x -= 10;
		y -= 10;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseX = mx;
		mouseY = my;
		collision(mouseX, mouseY, lastKey);
	}
}
void updateHighestScore()
{
	if (score > highestScore)
	{
		highestScore = score;
		saveHighestScore();
	}
}

void iKeyboard(unsigned char key)
{
	if (key == 'u')
	{
		exit(0);
	}
	if (key == 'w')
	{
		state = 1;
		click = key;
	}
	if (key == 'a')
	{
		state = 2;
		click = key;
	}
	if (key == 'd')
	{
		state = 3;
		click = key;
	}
	if (key == 'e')
	{
		state = 4;
		click = key;
	}
	if (key == 'v')
	{
		state = 5;
		click = key;
	}
	if (key == 's')
	{
		state = 6;
		click = key;
	}
	if (key == 'f')
	{
		state = 0;
		click = key;
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

	collision(mouseX, mouseY, lastKey);
}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
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

	iShowBMP2(250, 515, "picture\\target.bmp", 0);
	iShowBMP2(480, 520, "picture\\target.bmp", 0);
	iShowBMP2(740, 515, "picture\\target.bmp", 0);
	iShowBMP2(240, 340, "picture\\target.bmp", 0);
	iShowBMP2(750, 340, "picture\\target.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
	iShowBMP2(x, y, a[state], 0);
}

void drawscorepage()
{
	iFilledRectangle(0, 0, 1000, 600);
	iShowBMP2(50, 0, "picture\\1.bmp", 0);
	iShowBMP2(95, 565, "picture\\back.bmp", 0);
	iSetColor(255, 255, 255);

	SortScores();
	ShowHighScores();
	sprintf(highestScoreText, "Highest Score: %d", highestScore);
	iText(400, 300, highestScoreText, GLUT_BITMAP_TIMES_ROMAN_24);
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

	if (score > highestScore)
	{
		highestScore = score;
		saveHighestScore();
	}

	resetScore();
}

int main()
{
	if (musicOn)
	{
		PlaySound("song.wav", NULL, SND_LOOP | SND_ASYNC);
	}
	loadHighestScore();

	iSetTimer(20, iDraw);
	iSetTimer(2000, resetCollision);
	iInitialize(1000, 600, "2D PENALTY SAVING GAME");
	return 0;
}
