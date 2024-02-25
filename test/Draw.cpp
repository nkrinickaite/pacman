#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <vector>
#include "Draw.h"
#include <iostream>

using namespace std;

extern int score;
extern int state;
extern bool gameOver;
int gridX, gridY; //labirinto ribos
short sDirection = RIGHT;

int matrix[40][40] =
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, //Map array
1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,  //0 - food 1 - wall 2 - borders
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,2,0,1,1,1,1,1,1,2,0,1,1,1,1,2,0,1,1,1,1,1,2,0,1,1,1,1,1,1,1,1,2,0,1,1,1,2,0,1,
1,2,0,1,2,2,2,2,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,1,2,2,2,2,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,1,1,1,1,1,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,2,2,2,2,2,2,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,1,1,1,1,1,1,1,2,0,1,1,1,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,1,2,2,2,1,2,0,2,2,2,2,2,2,2,2,2,0,2,2,2,2,0,1,
1,1,1,1,1,1,1,1,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,2,2,2,2,2,2,2,2,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,1,1,1,1,1,1,1,2,0,1,1,1,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,1,2,2,2,1,2,0,2,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,1,1,1,1,1,1,1,1,1,2,2,1,2,0,1,1,1,1,1,2,0,0,0,0,0,0,0,0,1,2,0,1,2,1,2,0,1,
1,2,0,2,2,2,2,2,2,2,2,1,2,2,1,2,0,2,2,2,2,2,2,0,1,1,1,1,1,2,0,1,2,0,1,2,1,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,0,0,0,0,0,0,0,1,2,2,2,1,2,0,1,2,0,1,2,1,2,0,1,
1,1,1,2,0,1,1,1,1,2,0,1,1,1,1,2,0,1,1,1,1,1,2,0,1,2,2,2,1,2,0,1,2,0,1,2,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,2,2,2,2,2,0,2,2,2,2,2,2,0,1,2,2,2,1,2,0,1,2,0,1,2,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,0,1,2,0,1,1,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,1,1,1,1,1,1,1,1,1,1,2,0,1,2,2,2,1,2,0,1,2,0,2,2,2,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,2,2,2,2,2,2,2,2,2,1,2,0,1,2,2,2,1,2,0,1,2,0,0,0,0,0,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,2,2,2,2,2,2,2,2,2,1,2,0,1,1,1,1,1,2,0,1,1,1,2,0,1,1,1,1,
1,2,1,2,0,1,2,2,1,2,0,1,1,1,1,1,1,1,1,1,1,1,2,0,2,2,2,2,2,2,0,1,2,2,2,0,2,2,2,1,
1,2,1,2,0,1,2,2,1,2,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,1,
1,2,1,2,0,1,2,2,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,2,0,1,2,0,1,1,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,1,1,1,2,0,1,1,1,1,1,2,0,1,2,2,2,1,2,0,1,2,0,1,2,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,2,2,2,1,2,0,1,2,0,1,2,1,2,0,1,
1,2,1,2,0,1,2,2,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,1,1,1,1,2,0,1,2,0,1,2,1,2,0,1,
1,1,1,2,0,1,1,1,1,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,2,2,2,2,2,2,0,1,2,0,1,2,1,2,0,1,
1,2,2,2,0,2,2,2,2,2,0,1,2,2,1,2,0,1,2,2,2,1,2,0,0,0,0,0,0,0,0,1,2,0,1,1,1,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,1,1,1,1,1,1,1,2,0,2,2,2,2,0,1,
1,2,0,1,1,1,1,1,1,1,1,1,2,2,1,2,0,1,2,2,2,1,2,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,1,
1,2,0,2,2,2,2,2,2,2,2,1,2,2,1,2,0,1,2,2,2,1,2,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,1,2,2,1,2,0,1,2,2,2,1,2,0,1,1,1,1,1,1,1,1,2,0,1,2,1,2,0,1,
1,2,0,1,1,1,1,1,1,2,0,1,2,2,1,2,0,1,1,1,1,1,2,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,2,2,2,2,2,1,2,0,1,2,2,1,2,0,2,2,2,2,2,2,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,0,0,0,0,0,1,2,0,1,2,2,1,2,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,1,2,0,1,2,1,2,0,1,
1,2,0,1,1,1,2,0,1,2,0,1,1,1,1,2,0,1,1,1,1,1,2,0,1,1,1,1,1,1,1,1,2,0,1,1,1,2,0,1,
1,2,0,2,2,2,2,0,2,2,0,2,2,2,2,2,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,0,2,2,2,2,0,1,
1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
class veikejas
{
protected:
	int triangleAmount = 30;
	double size = 0.75;
public:
	veikejas() : triangleAmount(30), size(0.75) {}
	veikejas(int x, double y) : triangleAmount(x), size(y) {}
	~veikejas() {}
	
};
class ghost :public veikejas
{
private:
	int GposX, GposY;
	double r, g, b;
	short dir;
public:
	ghost() : GposX(0), GposY(0), r(0.0), g(0.0), b(0.0), dir(UP) { }
	ghost(int a, int b) : GposX(a), GposY(b), dir(UP) { }
	~ghost() { }

	void drawghost(double r, double g, double b)
	{
		//random vaiduokliu judejimas
		//priejus siena parenka random krypti, jei ta kryptim nera sienu, juda ta kryptim
		if (dir == UP)
		{
			if (state == 1) {}  //startscreen
			else if (matrix[GposX][GposY + 1] != 1)
				GposY++;
			else
			{
				int randominis = rand() % 2;
				if (randominis == 0)
				{
					if (matrix[GposX + 1][GposY] != 1)
						dir = RIGHT;
					else if (matrix[GposX - 2][GposY] != 1)
						dir = LEFT;
					else
						dir = DOWN;
				}
				else
				{
					if (matrix[GposX - 2][GposY] != 1)
						dir = LEFT;
					else if (matrix[GposX + 1][GposY] != 1)
						dir = RIGHT;
					else
						dir = DOWN;
				}
			}

		}
		if (dir == RIGHT)
		{
			if (matrix[GposX + 1][GposY] != 1)
				GposX++;
			else
			{
				int randominis = rand() % 2;
				if (randominis == 0)
				{
					if (matrix[GposX][GposY + 1] != 1)
						dir = UP;
					else if (matrix[GposX][GposY - 2] != 1)
						dir = DOWN;
					else
						dir = LEFT;
				}
				else
				{
					if (matrix[GposX][GposY - 2] != 1)
						dir = DOWN;
					else if (matrix[GposX][GposY + 1] != 1)
						dir = UP;
					else
						dir = LEFT;
				}
			}

		}
		if (dir == DOWN)
		{
			if (matrix[GposX][GposY - 2] != 1)
				GposY--;
			else
			{
				int randominis = rand() % 2;
				if (randominis == 0)
				{
					if (matrix[GposX + 1][GposY] != 1)
						dir = RIGHT;
					else if (matrix[GposX - 2][GposY] != 1)
						dir = LEFT;
					else
						dir = UP;
				}
				else
				{
					if (matrix[GposX - 2][GposY] != 1)
						dir = LEFT;
					else if (matrix[GposX + 1][GposY] != 1)
						dir = RIGHT;
					else
						dir = UP;
				}
			}

		}
		if (dir == LEFT)
		{
			if (matrix[GposX - 2][GposY] != 1)
				GposX--;
			else
			{
				int randominis = rand() % 2;
				if (randominis == 0)
				{
					if (matrix[GposX][GposY + 1] != 1)
						dir = UP;
					else if (matrix[GposX][GposY - 2] != 1)
						dir = DOWN;
					else
						dir = RIGHT;
				}
				else
				{
					if (matrix[GposX][GposY - 2] != 1)
						dir = DOWN;
					else if (matrix[GposX][GposY + 1] != 1)
						dir = UP;
					else
						dir = RIGHT;
				}
			}

		}
		//piesiu vaiduoklio galva
		glColor3f(r, g, b);
		GLfloat twicePi = 2.0f * 3.14159265359;
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(GposX, GposY);
		for (double i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				GposX + ((size-0.1) * cos(i * twicePi / triangleAmount)),
				GposY + ((size-0.1) * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
		//pesiu vaiduoklio kojas
		glColor3f(r, g, b);
		glBegin(GL_TRIANGLES);
		glVertex2f(GposX + 0.65, GposY);
		glVertex2f(GposX + 0.65, GposY - 0.8);
		glVertex2f(GposX + 0.3, GposY - 0.5);
		glVertex2f(GposX + 0.3, GposY - 0.5);
		glVertex2f(GposX, GposY - 0.8);
		glVertex2f(GposX - 0.3, GposY - 0.5);
		glVertex2f(GposX - 0.65, GposY);
		glVertex2f(GposX - 0.65, GposY - 0.8);
		glVertex2f(GposX - 0.3, GposY - 0.5);
		glEnd();
		//piesiu vaiduoklio desine aki
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2f(GposX + 0.5, GposY);
		glVertex2f(GposX + 0.1, GposY);
		glVertex2f(GposX + 0.2, GposY - 0.3);
		glVertex2f(GposX + 0.4, GposY - 0.3);
		glEnd();
		//piesiu vaiduoklio kaire aki
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_QUADS);
		glVertex2f(GposX - 0.5, GposY);
		glVertex2f(GposX - 0.1, GposY);
		glVertex2f(GposX - 0.2, GposY - 0.3);
		glVertex2f(GposX - 0.4, GposY - 0.3);
		glEnd();
		//pesiu vaiduoklio desini vyzdi
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(GposX + 0.3, GposY - 0.05);
		glVertex2f(GposX + 0.18, GposY);
		glVertex2f(GposX + 0.25, GposY - 0.25);
		glEnd();
		//piesiu vaiduoklio kairyji vyzdi
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(GposX - 0.3, GposY - 0.05);
		glVertex2f(GposX - 0.18, GposY);
		glVertex2f(GposX - 0.25, GposY - 0.25);
		glEnd();
	}
	int get_x()
	{
		return GposX;
	}
	int get_y()
	{
		return GposY;
	}
};
ghost g1(17, 30), g2(19, 30), g3(21, 30), g4(23, 30);
class pac :public veikejas
{
private:
	int posX, posY;
public:
	pac() : posX(17), posY(10) { }
	~pac() { }
	void drawPacman()
	{
		double direction1 = 0, direction2 = 0; //priklausomai nuo krypties, pacmano nesukineju, o kitaip piesiu
		//keyboard ir nepereinamos sienos
		if (sDirection == UP)
		{
			if (matrix[posX][posY + 1] != 1 && matrix[posX][posY + 1] != 2)
			{
				posY++;
				direction1 = 10.5;
				direction2 = 3.6;
			}
			else
			{
				direction1 = 10.5;
				direction2 = 3.6;
			}
		}
		if (sDirection == RIGHT)
		{
			if (matrix[posX + 1][posY] != 1 && matrix[posX + 1][posY] != 2)
			{
				posX++;
				direction1 = 3.0;
				direction2 = 2.8;
			}
			else
			{
				direction1 = 3.0;
				direction2 = 2.8;
			}
		}
		if (sDirection == DOWN)
		{
			if (matrix[posX][posY - 1] != 1 && matrix[posX][posY - 1] != 2)
			{
				posY--;
				direction1 = -6.5;
				direction2 = 2.0;
			}
			else
			{
				direction1 = -6.5;
				direction2 = 2.0;
			}
		}
		if (sDirection == LEFT)
		{
			if (matrix[posX - 1][posY] != 1 && matrix[posX - 1][posY] != 2)
			{
				posX--;
				direction1 = -27.0;
				direction2 = 1.3;
			}
			else
			{
				direction1 = -27.0;
				direction2 = 1.3;
			}
		}
		if (state == 1) { direction1 = 0; direction2 = 3.14159265359; posX = 20; posY = 10; } //startscreen

		if (matrix[posX][posY] == 0)
		{
			matrix[posX][posY] = 3;
			score++;
		}
		//Surinkus visa maista atsiranda dar maisto
		if (score % 416 == 0)
		{
			for (int i = 0; i < 40; i++)
			{
				for (int j = 0; j < 40; j++)
				{
					if (matrix[i][j] == 3)
						matrix[i][j] = 0;
				}
			}
			drawFood();
		}

		//piesiu pati pacmana
		glColor3f(1.0, 1.0, 0.0);
		GLfloat twicePi = 2.0f * direction2;
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(posX, posY);
		for (double i = direction1; i <= triangleAmount; i++) {
			glVertex2f(
				posX + (size * cos(i * twicePi / triangleAmount)),
				posY + (size * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
		//jeigu vaiduoklio koordinates lygios pacmano - gameOver
		if ((posX == g1.get_x() && posY == g1.get_y()) || (posX == g2.get_x() && posY == g2.get_y()) ||
			(posX == g3.get_x() && posY == g3.get_y()) || (posX == g4.get_x() && posY == g4.get_y())) {
			gameOver = true;
		}
	}
};
pac pacman;

class Wall
{
private:
	int locX, locY;
public:
	Wall() : locX(0), locY(0) {}
	~Wall() {}
	void drawWall(int locX, int locY)
	{
		if(state == 2)
		{
			glLineWidth(2.5);
			glColor3f(0.0, 0.0, 0.245);
		}
		else
		{
			glLineWidth(2.5);
			glColor3f(0.0, 0.0, 0.545);
		}
		glBegin(GL_LINE_LOOP);
		glVertex2f(locX, locY);
		glVertex2f(locX + 1, locY);
		glVertex2f(locX + 1, locY + 1);
		glVertex2f(locX, locY + 1);
		glEnd();
	}
};

void initGrid(int x, int y)
{
	//labirinto ir ekrano ribos
	gridX = x;
	gridY = y;
}

void drawGrid()
{
	//piesiamas labirintas is kvadratu
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (matrix[i][j] == 1)
			{
				Wall temp;
				temp.drawWall(i, j);
			}
		}
	}
}

void drawFood()
{
	int foodX, foodY;
	//ten kur nera sienu piesiamas maistas
	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			if (matrix[i][j] == 0)
			{
				foodX = i;
				foodY = j;
				glColor3f(1.0, 1.0, 1.0);
				int triangleAmount = 20;
				GLfloat twicePi = 2.0f * 3.14159265359;
				glBegin(GL_TRIANGLE_FAN);
				glVertex2f(foodX, foodY);
				for (double i = 0; i <= triangleAmount; i++) {
					glVertex2f(
						foodX + (0.15 * cos(i * twicePi / triangleAmount)),
						foodY + (0.15 * sin(i * twicePi / triangleAmount))
					);
				}
				glEnd();
			}
		}
	}
}

void drawPac()
{
	pacman.drawPacman();
}

void drawGhosts()
{
	//piesiu vaiduoklius
	g1.drawghost(0.85, 0.46, 0.7);
	g2.drawghost(0.0, 0.65, 0.65);
	g3.drawghost(0.9, 0.0, 0.0);
	g4.drawghost(0.8, 0.6, 0.0);
}