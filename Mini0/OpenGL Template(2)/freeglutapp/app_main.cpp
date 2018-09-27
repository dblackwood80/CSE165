#include <iostream>
#include <deque>
#include <string>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;

// Some global variables to maintain state

// A square data structure
struct Square {
	// The coordinates of the square (top-left)
	float x;
	float y;

	// The color of the square
	float r;
	float g;
	float b;

	//Variables of square
	float squareWidth;
	float point2X, point2Y;
	float point3X, point3Y;
	float point4X, point4Y;

	bool marked;

	// A constructor for square
	Square(float x, float y, float r, float g, float b, float squareWidth) {
		this->x = x;
		this->y = y;
		this->r = r;
		this->g = g;
		this->b = b;
		this->squareWidth = squareWidth;

		point2X = x + squareWidth;
		point2Y = y;

		point3X = point2X;
		point3Y = y - squareWidth;

		point4X = x;
		point4Y = y - squareWidth;
	}
};

// A "Double Ended QUEue" to store points 
deque<Square> squares;
deque<Square> undos;
deque<Square> deletes;

// Variables to store current color, initialize to black
float red = 0.0, green = 0.0, blue = 0.0;
float currentWidth = 0.1f;
string widthString = to_string(currentWidth);
unsigned char m_Test[10];
bool triger = false;

// Store the width and height of the window
int width = 640, height = 640;

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	strcpy((char*)m_Test, widthString.c_str());

	// Set background color to white
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the color to the current values of the global vars
	glColor3f(red, green, blue);

	// // Set point size
	glPointSize(6);

	// Draw a point at the bottom-right
	glBegin(GL_POINTS);

	glVertex2f(-0.8, -0.8);

	glEnd();

	glRasterPos2f(-0.8f, -0.9f);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)"WIDTH: ");
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char *)m_Test);

	// Draw all the points stored in the double-ended queue
	for (int i = 0; i < squares.size(); i++) {

		// Set the vertex color to be whatever we stored in the point
		glColor3f(squares[i].r, squares[i].g, squares[i].b);
		glLineWidth(squares[i].squareWidth);
		glBegin(GL_QUADS);

		// Draw the vertex in the right position
		glVertex2f(squares[i].x, squares[i].y);
		glVertex2f(squares[i].point2X, squares[i].point2Y);
		glVertex2f(squares[i].point3X, squares[i].point3Y);
		glVertex2f(squares[i].point4X, squares[i].point4Y);

		glEnd();
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
void windowToScene(float& x, float& y) {
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
	else {
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
	// Convert from Window to Scene coordinates
	y = y + 8; 
	float mx = (float)x;
	float my = (float)y;
	bool clicked = false;

	windowToScene(mx, my);

	cout << mx << ", " << my << "\n" << x << ", " << y << endl;

	for (int k = 0; k < squares.size(); k++)
	{
		if (mx >= squares[k].x && mx <= squares[k].point2X)
		{
			if (my >= squares[k].point3Y && my <= squares[k].y)
			{
				if (b == GLUT_RIGHT_BUTTON && s == GLUT_UP)
				{
					undos.push_back(squares[k]);
					squares.erase(squares.begin() + k);
				}
				else if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
				{
					clicked = true;
				}
			}
		}
	}

	// Add a point with with coordinates matching the
	// current mouse position, and the current color values
	// only if the left button is pressed

	if (b == GLUT_LEFT_BUTTON && s == GLUT_UP && clicked == false) 
	{
		squares.push_front(Square(mx, my, red, green, blue, currentWidth));
	}

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
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

	// Similar behavior to click handler. This function
	// allows us to paint free hand with the mouse.

	if (GLUT_LEFT_BUTTON || GLUT_UP || GLUT_DOWN)
	{
		squares.push_front(Square(mx, my, red, green, blue, currentWidth));
	}
	
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
		// Space was pressed. Erase all points
	case ' ':
		squares.clear();
		break;

		// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;

		// The "r" key was pressed. Set global color to red
	case 'r':
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "g" key was pressed. Set global color to green
	case 'g':
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;

		// The "b" key was pressed. Set global color to blue
	case 'b':
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;

		// The "k" key was pressed. Set global color to black
	case 'k':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "w" key was pressed. Set global color to white
	case 'w':
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		break;

		// "Ctrl-z" was pressed. Undo last drawn square
	case 26:
		if (!squares.empty())
		{
			undos.push_front(squares.front());
			squares.pop_front();
		}
		break;

		// "Ctrl-y" was pressed. Redo last deleted square
	case 25:
		if (!undos.empty())
		{
			squares.push_front(undos.front());
			undos.pop_front();
		}
		break;

		// The "+" was pressed. Increase width by 0.05f if < than 0.5f limit.
	case '+':
		if (currentWidth >= 0.5f)
		{
			currentWidth = 0.5f;
		}
		else if (currentWidth < 0.5f)
		{
			currentWidth += 0.05f;
		}
		widthString = to_string(currentWidth);
		break;

		// The "-" was pressed. Decrease width by 0.05f if > than 0.1f limit.
	case '-':
		if (currentWidth < 0.15f) {
			currentWidth = 0.1f;
		}
		else if (currentWidth >= 0.1f)
		{
			currentWidth -= 0.05f;
		}
		widthString = to_string(currentWidth);
		break;
	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}
 

int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// Start the main loop
	glutMainLoop();
}