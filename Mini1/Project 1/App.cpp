
#include "App.h"
#include "Rect.h"

std::vector<Rect*> rectPtr;

float r = 1.0f, g = 1.0f, b = 1.0f;

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;

	Rect rects;
	
	float step = 0.0f;
	for (int i = 0; i < 4; i++)
	{
		rects.x = -0.60f + step;
		//std::cout << "X: "<< rects.x << std::endl;
		rects.y = 0.75f;
		rects.width = 0.25f;
		rects.height = 0.25f;
		rectPtr.push_back(new Rect(rects.x, rects.y, rects.width, rects.height, rects.r, rects.b, rects.g));
		step += 0.3f;
	}

	
	//std::cout << rectPtr.at(0)->x << std::endl;
	//std::cout << rectPtr.at(1)->x << std::endl;
	//std::cout << rectPtr.at(2)->x << std::endl;
	//std::cout << rectPtr.at(3)->x << std::endl;
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set Color
    glColor3d(r, g, b);
    
    // Draw some points
   /* glBegin(GL_POINTS);
    
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    
    glEnd();
    
    // Draw a yellow cross
    glColor3d(1.0, 1.0, 0.0);
    
    glBegin(GL_LINES);
    
    glVertex2f(mx - 0.05f, my);
    glVertex2f(mx + 0.05f, my);
    
    glVertex2f(mx, my - 0.05f);
    glVertex2f(mx, my + 0.05f);
    
    glEnd();*/

	glBegin(GL_QUADS);
	
	for (int i = 0; i < rectPtr.size(); i++)
	{
		glColor3f(rectPtr[i]->r, rectPtr[i]->g, rectPtr[i]->b);
		glVertex2f(rectPtr.at(i)->x, rectPtr.at(i)->y);
		glVertex2f(rectPtr.at(i)->x + rectPtr.at(i)->width, rectPtr.at(i)->y);
		glVertex2f(rectPtr.at(i)->x + rectPtr.at(i)->width, rectPtr.at(i)->y - rectPtr.at(i)->height);
		glVertex2f(rectPtr.at(i)->x, rectPtr.at(i)->y - rectPtr.at(i)->height);
	}

	glEnd();
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
	Rect r;
	r.retrieve(rectPtr);

	if (r.contains(mx, my))
	{
		for (int j = 0; j < rectPtr.size(); j++)
		{
			rectPtr[j]->r = 1.0f;
			rectPtr[j]->g = 1.0f;
			rectPtr[j]->b = 1.0f;
		}

		for (int i = 0; i < rectPtr.size(); i++)
		{
			if (mx >= rectPtr.at(i)->x && mx < rectPtr.at(i)->x + rectPtr.at(i)->width)
			{
				//std::cout << "IN " << rectPtr.at(i)->g << std::endl;
				rectPtr.at(i)->g = 0.0f;
				rectPtr.at(i)->b = 0.0f;
				//g = 0.0f;
				//b = 0.0f;
				//std::cout << "G: " << rectPtr.at(i)->g << std::endl;
			}
		}
	}
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
}
