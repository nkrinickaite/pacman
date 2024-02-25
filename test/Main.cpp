#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include "draw.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
using namespace std;


#define COLUMS 40
#define ROWS 40
#define FPS 10

extern short sDirection; //pacmano kryptis
bool gameOver = false;
int score = 0;
int state = 1;
int times = 0;
string buffer;
map<string, int> highscoress;

void display_callback();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int, int, int);
void processNormalKeys(unsigned char, int, int);
void highscores();


void init()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	initGrid(COLUMS, ROWS);
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 50);
	glutCreateWindow("PACMAN");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	glutKeyboardFunc(processNormalKeys);
	init();
	glutMainLoop();
	return 0;
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (state == 1) //startscreen
	{
		drawGrid();
		glColor3f(1.0, 1.0, 0.0);
		glRasterPos2f(17, 22.5);
		string strlen = "READY?";
		for (int i = 0; i < strlen.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strlen[i]);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(14.5, 3.7);
		string strlen1 = "Press space to start";
		for (int i = 0; i < strlen1.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, strlen1[i]);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(1.7, 15.7);
		string strlen2 = "Your name:";
		for (int i = 0; i < strlen2.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, strlen2[i]);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(8.7, 15.7);
		for (int i = 0; i < buffer.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
		}
		drawGhosts();
		drawPac();
		glutSwapBuffers();
	}
	else if (state == 0)
	{
		drawGrid(); //labirinto piesimas
		drawFood(); //maisto piesimas
		drawGhosts();
		drawPac();
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(29, 39.1);
		string strlenn = "Your score:";
		stringstream sss;
		sss << score;
		string strr = sss.str();
		string strr2 = strlenn + " " + strr;
		for (int i = 0; i < strr2.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, strr2[i]);
		}
		if (gameOver)
		{
			state = 2;
			display_callback();
		}
		glutSwapBuffers();
	}
	else {
		drawGrid();
		highscores();
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(29, 39.1);
		string strlenn = "Your score:";
		stringstream sss;
		sss << score;
		string strr = sss.str();
		string strr2 = strlenn + " " + strr;
		for (int i = 0; i < strr2.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, strr2[i]);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(14, 27);
		string strlen = "GAME OVER";
		for (int i = 0; i < strlen.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, strlen[i]);
		}
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(14.5, 21.5);
		string strle = "LEADERBOARD:";
		for (int i = 0; i < strle.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, strle[i]);
		}
		glutSwapBuffers();
	}

}
struct comp
{
	template<typename T>
	bool operator()(const T& l, const T& r) const
	{
		if (l.second != r.second) {
			return l.second > r.second;
		}

		return l.first > r.first;
	}
};
void highscores()
{
	set<pair<string, int>, comp> set(highscoress.begin(), highscoress.end());
	map<string, int>::iterator it;
	int i = 20;
	if (times == 0)
	{
		int score2 = score;
		ifstream fd("scores.txt");
		string name;
		int high;
		while (!fd.eof()) {
			{
				fd >> name >> high;
				if (buffer == name) {
					if (score2 > high) { high = score2; }
					else score2 = high;
				}
				highscoress.insert(pair<string, int>(name, high));
			}
		}
		highscoress.insert(pair<string, int>(buffer, score2));
		fd.close();
		ofstream fr("scoress.txt");
		for (it = highscoress.begin(); it != highscoress.end(); it++) {
			fr << (*it).first << " " << (*it).second << endl;
		}
		fr.close();
		if (remove("scores.txt") != 0)
			perror("Error renaming file");
		else
			cout << "File removed successfully" << endl;
		if (rename("scoress.txt", "scores.txt") != 0)
			perror("Error renaming file");
		else
			cout << "File renamed successfully" << endl;
		times++;
	}
	for (auto const& pair : set) {
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(14.5, i);
		stringstream ss;
		ss << pair.second;
		string str = ss.str();
		string str2 = pair.first + " " + str;
		for (int i = 0; i < str2.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str2[i]);
		}
		i--;

	}
}
void reshape_callback(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, COLUMS, 0.0, ROWS, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}
void timer_callback(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000 / FPS, timer_callback, 0);
}

void keyboard_callback(int key, int, int)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		sDirection = UP;
		break;
	case GLUT_KEY_DOWN:
		sDirection = DOWN;
		break;
	case GLUT_KEY_RIGHT:
		sDirection = RIGHT;
		break;
	case GLUT_KEY_LEFT:
		sDirection = LEFT;
		break;
}
}
void processNormalKeys(unsigned char key, int x, int y)
{
	if (key >= 65 && key <= 122)
	{
		buffer.push_back((char)key);
		glutPostRedisplay();
	}
	else if (key == 32)
	{
		state = 0;
	}
	else if (key == 8)
	{
		buffer = "";
	}
}	