#include <iostream>
#include <deque>
#include <string>
#include "Player.h"
#define _USE_MATH_DEFINES
#define PI 3.14159265
#include <cmath>

using namespace std;

int width = 660, height = 660;

Player player;

enum Menus {Main = 0, Options = 1, Play = 2, Won = 3};

Menus currentMenu = Main;

void drawCircle(double stepX, double stepY)
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 360; i++) {
		double angle = 2 * PI * i / 360;
		double x = stepX + cos(angle);
		double y = stepY + sin(angle);
		glVertex2d(x / 3.1, y / 3.1);
		player.done = false;
	}
	glEnd();
}

void drawCross(float x, float y, float offsetX, float offsetY)
{
	//Offset is only for middle column boxes and middle row boxes. It should be 0.05f for both X and Y offsets

	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_LINES);

	glVertex2f(x, y);
	glVertex2f(x + 0.65f + offsetX, y - 0.65 - offsetY);

	glVertex2f(x + 0.65f + offsetX, y);
	glVertex2f(x, y - 0.65 - offsetY);

	glEnd();
}

void read()
{

		//First row first box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[0][0] == 2)
		{
			drawCircle(-2.1, 2.1);
		}
		else if (player.vec1[0][0] == 1)
		{
			drawCross(-1.0f, 1.0f, 0, 0);
		}

		//First row second box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[0][1] == 2)
		{
			drawCircle(0.0, 2.1);
		}
		else if (player.vec1[0][1] == 1)
		{
			drawCross(-0.35f, 1.0f, 0.05f, 0.00f); // Only need to change X offset for column 2 and change Y for row 2			
		}

		//First row third box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[0][2] == 2)
		{
			drawCircle(2.1, 2.1);
		}
		else if (player.vec1[0][2] == 1)
		{
			drawCross(0.35f, 1.0f, 0.0f, 0.0f);
		}

		//Second row first box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[1][0] == 2)
		{
			drawCircle(-2.1, 0.0);
		}
		else if (player.vec1[1][0] == 1)
		{
			drawCross(-1.0f, 0.35f, 0.0f, 0.05f);
			
		}

		//Second row second box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[1][1] == 2)
		{
			drawCircle(0.0, 0.0);
		}
		else if (player.vec1[1][1] == 1)
		{
			drawCross(-0.35f, 0.35f, 0.05f, 0.05f); //Real special since it's row 2 and column 2 needs offset on both X and Y
		}

		//Second row third box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[1][2] == 2)
		{
			drawCircle(2.1, 0.0);
		}
		else if (player.vec1[1][2] == 1)
		{
			drawCross(0.35f, 0.35f, 0.0f, 0.05f);
		}

		//Third row first box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[2][0] == 2)
		{
			drawCircle(-2.1, -2.1);
		}
		else if (player.vec1[2][0] == 1)
		{
			drawCross(-1.0f, -0.35f, 0.0f, 0.0f);
		}

		//Third row second box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[2][1] == 2)
		{
			drawCircle(0.0, -2.1);
		}
		else if (player.vec1[2][1] == 1)
		{
			drawCross(-0.35f, -0.35f, 0.05f, 0.0f);
		}

		//Third row third box draw logic
//--------------------------------------------------------------------------------------------------------------\\

		if (player.vec1[2][2] == 2)
		{
			drawCircle(2.1, -2.1);
		}
		else if (player.vec1[2][2] == 1)
		{
			drawCross(0.35f, -0.35f, 0.0f, 0.0f);
		}
}

void appDrawScene()
{

	if (currentMenu == Main)
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//cout << currentMenu << endl;
		// Set background color to white
		glClearColor(1.0, 1.0, 1.0, 1.0);

		// Set up the transformations stack
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		

		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(-0.365f, -0.07f);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)"PLAY");

		glRasterPos2f(0.14f, -0.07f);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)"EXIT");

		glColor3f(0.75f, 0.75f, 0.75f);

		glBegin(GL_QUADS);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.4f, 0.0f);
		glVertex2f(0.4f, -0.1f);
		glVertex2f(0.0f, -0.1f);

		glVertex2f(-0.5f, 0.0f);
		glVertex2f(-0.1f, 0.0f);
		glVertex2f(-0.1f, -0.1f);
		glVertex2f(-0.5f, -0.1f);

		glEnd();
	}

	if (currentMenu == Options)
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//cout << currentMenu << endl;
		// Set background color to white
		glClearColor(1.0, 1.0, 1.0, 1.0);

		// Set up the transformations stack
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(-0.48f, -0.07f);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)"ONE PLAYER");

		glRasterPos2f(0.0125f, -0.07f);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)"TWO PLAYER");

		glColor3f(0.75f, 0.75f, 0.75f);

		glBegin(GL_QUADS);

		glVertex2f(0.0f, 0.0f);
		glVertex2f(0.4f, 0.0f);
		glVertex2f(0.4f, -0.1f);
		glVertex2f(0.0f, -0.1f);

		glVertex2f(-0.5f, 0.0f);
		glVertex2f(-0.1f, 0.0f);
		glVertex2f(-0.1f, -0.1f);
		glVertex2f(-0.5f, -0.1f);

		glEnd();
	}
	
	if (currentMenu == Play)
	{
		
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//cout << currentMenu << endl;
		// Set background color to white
		glClearColor(1.0, 1.0, 1.0, 1.0);

		// Set up the transformations stack
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(6);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);

		//Left side down
		glVertex2f(-0.35f, 1.0f);
		glVertex2f(-0.35f, -1.0f);

		//Right side down
		glVertex2f(0.35f, 1.0f);
		glVertex2f(0.35f, -1.0f);

		//Top across
		glVertex2f(-1.0f, 0.35f);
		glVertex2f(1.0f, 0.35f);

		//Bottom across
		glVertex2f(-1.0f, -0.35f);
		glVertex2f(1.0f, -0.35f);

		glEnd();

		read();

		if (player.enableAI)
		{
			player.playerAI(); //For 1 player uncomment this line
		}

		if (!(player.player1Won() == 0 || player.player1Won() == 1 || player.player1Won() == 2))
		{
			read();
		}

		if (player.player1Won() == 0 || player.player1Won() == 1 || player.player1Won() == 2)
		{
			if (player.player1Won() == 1)
			{
				read();
			}

			player.done = true;
			currentMenu = Won;
			player.enableAI = false;
		}
		else
		{
			currentMenu = Play;
		}
	}

	if (currentMenu == Won)
	{
		if (player.player1Won() == 0)
		{
			//cout << "Player 1 has won!" << endl;
			player.keepOnChecking = false;
			player.done = true;
			// Clear the screen
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Set background color to white
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(0.5f, 0.0f, 0.5f);
			// Set up the transformations stack
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-1.0f, 0.0f, -1.0f);
			glScalef(0.0018f, 0.0015f, 1.0f);

			glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)"PLAYER 1 WINS!");
		}
		else if (player.player1Won() == 1)
		{
			//cout << "Player 2 has won!" << endl;
			player.keepOnChecking = false;
			// Clear the screen
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Set background color to white
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(0.5f, 0.0f, 0.5f);
			// Set up the transformations stack
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-1.0f, 0.0f, -1.0f);
			glScalef(0.0018f, 0.0015f, 1.0f);

			glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)"PLAYER 2 WINS!");
		}
		else if (player.player1Won() == 2)
		{
			//cout << "Player 2 has won!" << endl;
			player.keepOnChecking = false;
			// Clear the screen
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Set background color to white
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glColor3f(0.5f, 0.0f, 0.5f);
			// Set up the transformations stack
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(-1.0f, 0.0f, -1.0f);
			glScalef(0.0018f, 0.0015f, 1.0f);

			glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)"  IT'S A TIE! ");
		}
	}
	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) 
{
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else 
	{
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {

	if (s == 1 && b == GLUT_LEFT_BUTTON)
	{
		// Convert from Window to Scene coordinates
		y = y + 8;
		float mx = (float)x;
		float my = (float)y;

		//cout << mx << ", " << my << endl;

		//cout << player.player1Turn << " whose? "  << player.vec1.size() << endl;

		if (currentMenu == Main)
		{
			//cout << x << ", " << y << endl;

			if (x >= 160 && x < 290 && y >= 323 && y < 355)
			{
				currentMenu = Options;
			}

			if (x >= 325 && x < 453 && y >= 323 && y < 355)
			{
				exit(0);
			}
		}
		else if (currentMenu == Options)
		{
			if (x >= 160 && x < 290 && y >= 323 && y < 355)
			{
				currentMenu = Play;
				player.enableAI = true;
			}

			if (x >= 325 && x < 453 && y >= 323 && y < 355)
			{
				currentMenu = Play;
			}
		}
		else if (currentMenu == Play && player.player1Turn)
		{
			player.inBounds(mx, my);
			glutPostRedisplay();
			//currentMenu = Play;
		}
		else if (currentMenu == Play && !player.player1Turn && !player.enableAI)
		{

			player.inBounds(mx, my); //For 1 player remove this line and next
			glutPostRedisplay();
		}
		else if (currentMenu == Won)
		{
			if (s == 1 && b == GLUT_LEFT_BUTTON)
			{
				currentMenu = Main;
				player.reset();

				// Clear the screen
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				// Set background color to white
				glClearColor(1.0, 1.0, 1.0, 1.0);
			}
		}
	
		windowToScene(mx, my);
		// Redraw the scene by calling appDrawScene above
		// so that the point we added above will get painted
		glutPostRedisplay();
	}
	
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	y = y + 8;
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {
		// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;
		
		// After all the state changes, redraw the scene
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("Tic-Tac-Toe");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
	
	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	//glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// Start the main loop
	glutMainLoop();
}