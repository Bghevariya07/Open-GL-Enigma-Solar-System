
/************************************************************************************

	File: 			Assignment02.c

	Description:	A complete OpenGL program to animate a solar system with planets,
					moons, orbits, stars, a spaceship and their visibility options.

	Author:			Bhavya Ghevariya

*************************************************************************************/


// include the library header files
#include <stdlib.h>
#include <stdio.h>
#include <freeglut.h>
#include <math.h>

// declaration of required variables
static twoPI = 2 * 3.14;

// declaration of variables to change controls
GLfloat rVisibility = 0.0;
GLfloat cVisibility = 0.0;
GLfloat sVisibility = 0.0;
GLfloat eVisibility = 0.0;
GLfloat rotationCounter = 0.0;

// planet rotation axis
GLfloat xTheta = 0;
GLfloat zTheta = 0;

// window hight and width
GLint windowWidth = 1400;
GLint windowHeight = 600;

// special key function array keys
GLfloat upArrow = 0.0;
GLfloat leftArrow = 0.0;
GLfloat rightArrow = 0.0;
GLfloat downArrow = 0.0;
GLfloat pageUpArrow = 0.0;
GLfloat pageDownArrow = 0.0;

// special key function array keys
GLfloat xAxis = 0.0;
GLfloat yAxis = 0.0;
GLfloat zAxis = 0.0;

// current camera position
GLfloat cameraPosition[] = { 0, 5, 35 };

// colors of the planets
GLfloat colors[][3] = { {1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
						{0.0,0.0,1.0}, {1.0,0.0,1.0}, {0.0,1.0,1.0},
						{0.5,0.0,1.0}, {1.0,0.5,0.0}, {0.5,0.5,0.5} };

// radius of planets
GLfloat planetRadius[] = { 0.3, 0.4, 0.6, 0.4, 0.3, 0.2, 0.5 };

// radius of orbits
GLfloat orbitRadius[] = { 3, 5, 8, 10, 13, 15, 17 };

// colors of planet - numbers
GLfloat planetColor[] = { 3, 4, 1, 5, 0, 6, 2, 7, 8 };

// moon count for planets
GLfloat moonCount[] = { 0, 0, 3, 2, 0, 1, 2 };

// speed dividers of the planets
GLint planetSpeed[] = { 80, 120, 100, 80, 90, 110, 100 };


/************************************************************************

	Function:		planet

	Description:	generates a planet with or without moons and the radius.

*************************************************************************/
void planet(float pRadius, int color, float oRadius, int moons, int speed)
{
	// create an angle variable
	float angle;

	// set the line width to 0.5
	glLineWidth(0.5);

	// set the visibility and color of the ring
	glColor4f(1.0, 1.0, 1.0, rVisibility);

	// create lines to create a ring around the sun as an orbit
	glBegin(GL_LINES);

	// use for loop to create orbital path
	for (int i = 0; i < (360 * rVisibility); i++)
	{
		// draw a vertex at the position theta angle
		angle = i * twoPI;
		glVertex3f(oRadius * cos(angle), 0.0, oRadius * sin(angle));
	}
	glEnd();

	// set the planet color
	glColor3fv(colors[color]);

	// trnaslate the model matrix to the orbital path
	glTranslatef(oRadius * cos(xTheta / speed), 0, oRadius * sin(zTheta / speed));

	// create a solid sphere for a planet
	glutSolidSphere(pRadius, 30, 36);

	// if the moon count is not 0 then create its moons
	while (moons > 0)
	{
		// use recursion to create moons and reduce the moon count by 1
		moons--;
		planet(pRadius / 3, moons, pRadius + 0.2, moons, speed - 25);
	}

	// translate back the model matrix
	glTranslatef(-(oRadius * cos(xTheta / speed)), 0, -(oRadius * sin(zTheta / speed)));
}



/************************************************************************

	Function:		drawElipticalPlanet

	Description:	generates a planet with or without moons and the radius
					and elliptical orbit.

*************************************************************************/
drawEllipticalPlanet(int tilt, float pRadius, int color, float oRadius, int moons, int speed, float shiftX, float shiftY)
{
	// create an angle variable
	float angle;

	// set the line width to 0.5
	glLineWidth(0.5);

	// translate the planet
	glTranslatef(shiftX, shiftY, 0.0);

	// set the visibility and color of the ring
	glColor4f(1.0, 1.0, 1.0, rVisibility);

	// create lines to create a ring around the sun as an orbit
	glBegin(GL_LINES);

	// use for loop to create orbital path
	for (int i = 0; i < (360 * rVisibility); i++)
	{
		// draw a vertex at the position theta angle
		angle = i * twoPI;
		glVertex3f(oRadius * cos(angle) / tilt, oRadius * cos(angle), oRadius * sin(angle));
	}
	glEnd();

	// set the color of the planet
	glColor3fv(colors[color]);

	// move the model matrix to the radius strating point
	glTranslatef(oRadius * cos(xTheta / speed) / tilt, oRadius * cos(zTheta / speed), oRadius * sin(zTheta / speed));

	// create a solid sphere with the given radius
	glutSolidSphere(pRadius, 30, 36);

	// if the moon count is not 0 then create its moons
	while (moons > 0)
	{
		// use recursion to create moons and reduce the moon count by 1
		moons--;
		planet(pRadius / 3, moons, pRadius + 0.2, moons, speed - 25);
	}

	// translate back the model matrix
	glTranslatef(-(oRadius * cos(xTheta / speed) / tilt), -(oRadius * cos(zTheta / speed)), -(oRadius * sin(zTheta / speed)));
	glTranslatef(-shiftX, -shiftY, 0.0);
}


/************************************************************************

	Function:		drawPlanets

	Description:	generates all the planets in the solarsystem with
					orbits and moons.

*************************************************************************/
void drawPlanets()
{
	// use a for loop to take values from the array and create planets
	for (int i = 0; i < 7; i++)
	{
		// call planet method to create a planet
		planet(planetRadius[i], planetColor[i], orbitRadius[i], moonCount[i], planetSpeed[i] / 10);
	}

	// draw an elliptical planet with certain angle to it
	drawEllipticalPlanet(1.5, 0.9, planetColor[8], 12, 2, 180 / 10, 5, 5);
	drawEllipticalPlanet(3.0, 0.5, planetColor[3], 15, 1, 200 / 10, -1.5, -5);
}



/************************************************************************

	Function:		drawStars

	Description:	generates stars at different locations behind the solar system.

*************************************************************************/
void drawStars()
{
	// move the stars in the background of the solar system
	glTranslatef(-100, -50, -50);

	// increase the size of the star space area
	glScalef(40, 40, 0);

	// increase the star size to 1.5 to make it more visible
	glPointSize(1.5);

	// use a for loop to generate random stars with  random colors
	for (int i = 0; i < 500; i++)
	{
		// use points to create points with random colors at random positions
		glBegin(GL_POINTS);
		glColor4f(rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0), rand() / (RAND_MAX + 1.0), sVisibility);
		glVertex3f(10 * rand() / (RAND_MAX + 1.0), 10 * rand() / (RAND_MAX + 1.0), 10 * rand() / (RAND_MAX + 1.0));
		glEnd();
	}

	// scale back the star space
	glScalef(-40, -40, 0);

	// move the model matrix back
	glTranslatef(100, 50, 50);
}


/************************************************************************

	Function:		drawSun

	Description:	generates a sun with option to change the visibility of corona.

*************************************************************************/
void drawSun()
{
	// set the color to red for the core of the sun
	glColor3fv(colors[0]);

	// create a solid sphere for the sun in the center of the system
	glutSolidSphere(1.0, 30, 36);

	// Use a for loop to create sun rays around the sun
	for (int i = 0; i < 360; i++)
	{
		// an angle to measure the theta for sine cosine values
		float angle = i * twoPI;

		// draw line stripes to create rays with multiple colors
		glBegin(GL_LINE_STRIP);
		glColor4f(1.0, 0.2, 0.0, cVisibility);
		glVertex3f(1.0 * cos(angle), (1.0 * sin(angle)), 0.0);
		glColor4f(1.0, 1.0, 0.0, cVisibility);
		glVertex3f(1.5 * cos(angle), (1.5 * sin(angle)), 0.0);
		glColor4f(0.0, 0.0, 0.0, cVisibility);
		glVertex3f(1.9 * cos(angle), (1.9 * sin(angle)), 0.0);
		glEnd();
	}
}


/************************************************************************

	Function:		drawSunEnergy

	Description:	generates sun energy coming out of the sun like a supernova.

*************************************************************************/
void drawSunEnergy()
{
	// draw sun energy rays
	for (int i = 0; i < 360; i++)
	{
		// angle to create a theta for the ray positions
		float angle = i * twoPI;

		// create line stripes to create lines of the rays and add visibility option
		glBegin(GL_LINE_STRIP);
		glColor4f(1.0, 0.2, 0.0, eVisibility);
		glVertex3f(0.0 * cos(angle), (0.0 * tan(angle)), (0.0 * sin(angle)));
		glColor4f(1.0, 1.0, 0.0, eVisibility);
		glVertex3f(1.9 * cos(angle), (1.9 * tan(angle)), (1.9 * sin(angle)));
		glColor4f(0.0, 0.0, 0.0, eVisibility);
		glVertex3f(3.0 * cos(angle), (3.0 * tan(angle)), (3.0 * sin(angle)));
		glEnd();
	}
}


/************************************************************************

	Function:		drawStarship

	Description:	generates a spaceship at the camera position.

*************************************************************************/
void drawStarship()
{
	// set the array counter to 1
	int counter = 1;

	// open the enterprise.txt file into fp FILE pointer
	FILE* fp;
	errno_t err = fopen_s(&fp, "enterprise.txt", "r");

	// if the file is NULL return from the method
	if (err)
	{
		return;
	}

	// create three arrays for vertices co ordinates
	GLfloat xShip[1202], yShip[1202], zShip[1202];

	// create three integers for triangle face values
	int tria = 0, trib = 0, tric = 0;

	// create a character for the type of values in the file
	char type = "";

	// translate the model matrix
	glTranslatef(0 + xAxis, 4 + yAxis, 31 + zAxis);

	// take values from the enterprise.txt file and store them into variables
	while (fscanf_s(fp, "%c", &type) != EOF)
	{
		// if the char value is v then store them as vertices
		if (type == 'v')
		{
			// take the vertex values and store them into xShip, yShip and zShip
			fscanf_s(fp, "%f", &xShip[counter]);
			fscanf_s(fp, "%f", &yShip[counter]);
			fscanf_s(fp, "%f", &zShip[counter]);
			counter++;
		}

		// if the char value is c then store them as faces
		if (type == 'f')
		{
			// take the face values and store them into tria, trib and tric
			fscanf_s(fp, "%d", &tria);
			fscanf_s(fp, "%d", &trib);
			fscanf_s(fp, "%d", &tric);
			counter++;

			// draw triangles using the face values which calls the vertices
			glBegin(GL_TRIANGLES);
			glColor3f(0.5-xShip[tria], 0.5-yShip[tria], 0.5-zShip[tria]);
			glVertex3f(xShip[tria], yShip[tria], zShip[tria]);
			glVertex3f(xShip[trib], yShip[trib], zShip[trib]);
			glVertex3f(xShip[tric], yShip[tric], zShip[tric]);
			glEnd();
		}
	}

	// close the enterprise.txt file pointer
	fclose(fp);

	// translate back the model matrix
	glTranslatef(0 - xAxis, -4 - yAxis , -31 - zAxis);
}



void printInfo()
{
	// print all the statements to show the modifications that can be made
	printf("Scene Controls");
	printf("\n-------------------------------");
	printf("\nr:	toggle rings");
	printf("\ns:	toggle stars");
	printf("\nc:	toggle the sun's corona");
	printf("\ne:	toggle the sun's energy\n");
	printf("\nCamera Controls");
	printf("\n-------------------------------");
	printf("\nUp	Arrow:    move up");
	printf("\nDown	Arrow:    move down");
	printf("\nRight	Arrow:    move right");
	printf("\nLeft	Arrow:    move left");
	printf("\nPAGE	UP   :    forward");
	printf("\nPAGE	DOWN :    backward\n");
}



/************************************************************************

	Function:		myDisplay

	Description:	Display callback, clears frame buffer and depth buffer,
					positions the camera and draws the solar system.

*************************************************************************/
void myDisplay(void)
{
	// clear the screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load an identity matrix
	glLoadIdentity();

	// set the position of the camers
	gluLookAt(cameraPosition[0] + xAxis, cameraPosition[1] + yAxis, cameraPosition[2] + zAxis, 0, 0, -150, 0, 1, 0);

	// turn on transparency blending
	glEnable(GL_BLEND);

	// set the blending mode to be controlled by ALPHA
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable line smoothening
	glEnable(GL_LINE_SMOOTH);

	// set the line width to 0.5
	glLineWidth(0.5);

	// draw all the planets
	drawPlanets();

	// draw the sun
	drawSun();

	//draw the sun enery like supernova
	drawSunEnergy();

	//draw the starship
	drawStarship();

	// draw twinkling star
	drawStars();

	// swap the drawing buffers
	glutSwapBuffers();
}


/************************************************************************

	Function:		myIdle

	Description:	Updates the animation when idle.

*************************************************************************/
void myIdle()
{
	// change the value of angle as rotation counter changes
	xTheta = rotationCounter * twoPI;
	zTheta = rotationCounter * twoPI;

	// reset the rotation counter as it reaches 360
	if (rotationCounter != 360)
	{
		// increase the rotation counter by 0.01
		rotationCounter += 0.01;
	}
	else
	{
		// set the rotation counter to 0
		rotationCounter = 0;
	}

	// redraw the new state
	glutPostRedisplay();
}


/************************************************************************

	Function:		myKey

	Description:	Updates the visibility of corresponding objects
					based on the key input

*************************************************************************/
void myKey(unsigned char key, int x, int y)
{
	//if r key is pressed change the visibility of the radius
	if (key == 'r' || key == 'R')
	{
		// if the value is 0 or 1 set it to 1 or 0 respectively
		if (rVisibility == 0.0)
		{
			rVisibility = 1.0;
		}
		else
		{
			rVisibility = 0.0;
		}
	}

	//if c key is pressed change the visibility of the sun's corona
	if (key == 'c' || key == 'C')
	{
		// if the value is 0 or 1 set it to 1 or 0 respectively
		if (cVisibility == 0.0)
		{
			cVisibility = 1.0;
		}
		else
		{
			cVisibility = 0.0;
		}
	}

	//if s key is pressed change the visibility of the stars
	if (key == 's' || key == 'S')
	{
		// if the value is 0 or 1 set it to 1 or 0 respectively
		if (sVisibility == 0.0)
		{
			sVisibility = 1.0;
		}
		else
		{
			sVisibility = 0.0;
		}
	}

	//if e key is pressed change the visibility of the sun's energy
	if (key == 'e' || key == 'E')
	{
		// if the value is 0 or 1 set it to 1 or 0 respectively
		if (eVisibility == 0.0)
		{
			eVisibility = 1.0;
		}
		else
		{
			eVisibility = 0.0;
		}
	}

	// redraw the new state
	glutPostRedisplay();
}


/************************************************************************

	Function:		specialKey

	Description:	Updates the movement of the camera based on the key input

*************************************************************************/
void specialKey(unsigned char key, int x, int y)
{
	// if page up key is pressed move the starship forward
	if (key == GLUT_KEY_PAGE_UP) {
		zAxis -= 0.1;
	}

	// if page down key is pressed move the starship backward
	if (key == GLUT_KEY_PAGE_DOWN) {
		zAxis += 0.1;
	}

	// if up arrow key is pressed move the starship up
	if (key == GLUT_KEY_UP) {
		yAxis += 0.1;
	}

	// if down arrow key is pressed move the starship down
	if (key == GLUT_KEY_DOWN) {
		yAxis -= 0.1;
	}

	// if right arrow key is pressed move the starship right
	if (key == GLUT_KEY_RIGHT) {
		xAxis += 0.1;
	}

	// if left arrow key is pressed move the starship left
	if (key == GLUT_KEY_LEFT) {
		xAxis -= 0.1;
	}

	//redraw the new state
	glutPostRedisplay();
}


/************************************************************************

	Function:		initializeGL

	Description:	Initializes the OpenGL rendering context for display.

*************************************************************************/
void initializeGL(void)
{
	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);

	// change into model-view mode so that we can change the camera positions and perspective
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// set the perspective parameters
	gluPerspective(45, (float)windowWidth / (float)windowHeight, 1, 150);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}




/************************************************************************

	Function:		main

	Description:	Sets up the openGL rendering context and the windowing
					system, then begins the display loop.

*************************************************************************/
void main(int argc, char** argv)
{
	// initialize the toolkit
	glutInit(&argc, argv);

	// set display mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// set window size
	glutInitWindowSize(windowWidth, windowHeight);

	// set window position on screen
	glutInitWindowPosition(100, 150);

	// open the screen window
	glutCreateWindow("Enigma - Solar System");

	// register redraw function
	glutDisplayFunc(myDisplay);

	// register the idle function
	glutIdleFunc(myIdle);

	// register the keyboard function
	glutKeyboardFunc(myKey);

	// register the special key function
	glutSpecialFunc(specialKey);

	// print all the statements
	printInfo();

	// initialize the rendering context
	initializeGL();

	// go into a perpetual loop
	glutMainLoop();
}
