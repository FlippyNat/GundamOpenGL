#include <Windows.h>
#include <gl/GL.h>
#include <gl/Glu.h>
#include <math.h>
#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "OpenGL Window"

// Projection: Ortographics | Perspective
bool isOrtho = true;
float Ry = 180, Tx = 0, Rangle = 0;
float rVSpeed = 1.5, tSpeed = 0.1;

float eyeX = 0, eyeY = 0, eyeZ = -0.1;
float lookAtX = 0, lookAtY = 0, lookAtZ = 0;
float upX = 0, upY = 1, upZ = 0;

float rotateRobotX = 0;
float rotateRobotY = 0;
float zoomIn = 0;

// Lighting
bool isLightOn = false; // Default = No Light
float lightSpeed = 1;
float diffuseLight[] = { 1,1,1,1 }; // Sunlight
float ambientLight[] = { 0,0,0,1 };
float specLight[] = { 1,1,1,1 };
float emissionLight[] = { 0,0,0,1 };

float defaultAmbient[] = { 0.2, 0.2, 0.2, 1 };
float defaultDiffuse[4] = { 0.8, 0.8, 0.8, 1 };
float positionLightTop[] = { 1.0, 1.0, 1.0, 0.0 };
float positionLightCenter[] = { 5.0, 10.0, 2.0, 1.0 };

float white[] = { 0.8710, 0.9330, 0.8710 ,1 };
float blue[] = { 0, 0.5920, 0.8390, 1 };
float red[] = { 0.9060, 0.1760, 0.1060,1 };
float yellow[] = { 0.9730, 0.7180, 0,1 };
float grey[] = { 0.3410, 0.3530, 0.4120, 1 };
float darkGrey[] = { 0.1920, 0.1920, 0.1960, 1 };
float lightBlue[] = { 0.2550, 0.4780, 0.7450 , 1 };
float black[] = { 0,0,0,1 };

// Texture
//Step 1: Variable declaration
int textureMode = 1; // Default = 1
int worldMode = 1;

// Mode 1
GLuint whiteSteel;
GLuint greySteel;
GLuint yellowSteel;
GLuint redSteel;
GLuint blueSteel;
GLuint darkgraySteel;

// Mode 2
GLuint copper;
GLuint darkgrey;
GLuint darkgreen1;

// Mode 3
GLuint matteBlack;

// World Mode
GLuint sky;
GLuint night;
GLuint space;

boolean extend = false;
boolean leftHand = false;
boolean rightHand = false;
boolean leftLeg = false;
boolean rightLeg = false;
boolean headAni = false;
boolean bodyAni = false;
boolean drawSaber1 = false;
boolean drawSaber2 = false;
boolean getSaber = false;
boolean walking1 = false;
boolean leftLegFront = false;
boolean rightLegFront = false;
boolean abc = false;
boolean running1 = false;
boolean jumping1 = false;
boolean jumping2 = false;
boolean jumping3 = false;
boolean jumping4 = false;

boolean attack = false;
boolean attack1 = false;

boolean aniMode = false;
float length = 0.2;


float leftShoulderAngle = 0;
float leftElbowAngle = 0;
float leftWristX = 0;
float leftWristY = 0;
float leftWristZ = 0;

float rightShoulderAngle = 0;
float rightElbowAngle = 0;
float rightWristX = 0;
float rightWristY = 0;
float rightWristZ = 0;


float leftHeel = 0;
float leftKnee = 0;
float leftThigh = 0;
float leftHipFront = 0;
float leftHipBack = 0;

float rightHeel = 0;
float rightKnee = 0;
float rightThigh = 0;
float rightHipFront = 0;
float rightHipBack = 0;

float headX = 0;
float headY = 0;

float hipAngle = 0;

float jumpHeight = 0;

float walkingZ = 0;

float bodyY = 0;
float bodyMoveY = 0;
BITMAP BMP;			 //bitmap structure
HBITMAP hBMP = NULL; //bitmap handle


LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		else if (wParam == 'O') {
			isOrtho = true;
			eyeZ = -0.1;
			Ry = 180;
			Rangle = 0;
			Tx = 0;
			rotateRobotY = 0;

		}
		else if (wParam == 'P') {
			// If Perspective
			isOrtho = false;
			eyeZ = -1.2;
			Ry = 0;
			Rangle = 0;
			Tx = 0;
			rotateRobotY = 180;
			zoomIn = 0;
		}
		else if (wParam == '1') {
			isLightOn = !isLightOn;
		}
		else if (wParam == '2') {
			positionLightTop[0] -= lightSpeed;
			positionLightCenter[0] -= lightSpeed;
		}
		else if (wParam == '3') {
			positionLightTop[0] += lightSpeed;
			positionLightCenter[0] += lightSpeed;
		}
		else if (wParam == '4') {
			positionLightTop[1] -= lightSpeed;
			positionLightCenter[1] -= lightSpeed;
		}
		else if (wParam == '5') {
			positionLightTop[1] += lightSpeed;
			positionLightCenter[1] += lightSpeed;
		}
		else if (wParam == '6') {
			positionLightTop[2] -= lightSpeed;
			positionLightCenter[2] -= lightSpeed;
		}
		else if (wParam == '7') {
			positionLightTop[2] += lightSpeed;
			positionLightCenter[2] += lightSpeed;
		}
		else if (wParam == VK_SHIFT) {
			if (textureMode == 1) {
				textureMode = 2;
			}
			else if (textureMode == 2) {
				textureMode = 3;
			}
			else if (textureMode == 3) {
				textureMode = 4;
			}
			else if (textureMode == 4) {
				textureMode = 1;
			}
		}
		else if (wParam == VK_CONTROL) {
			if (worldMode == 1) {
				worldMode = 2;
			}
			else if (worldMode == 2) {
				worldMode = 3;
			}
			else if (worldMode == 3) {
				worldMode = 4;
			}
			else if (worldMode == 4) {
				worldMode = 1;
			}
		}
		else if (wParam == 'A') {
			if (isOrtho) {
				Tx -= tSpeed;
				eyeX -= 0.1;
			}
		}
		else if (wParam == 'D') {
			Tx += tSpeed;
			eyeX += 0.1;
		}
		else if (wParam == 'W') {
			Rangle += rVSpeed;
		}
		else if (wParam == 'S') {
			Rangle -= rVSpeed;
		}
		else if (wParam == VK_LEFT) {
			Ry -= rVSpeed;
		}
		else if (wParam == VK_RIGHT) {
			Ry += rVSpeed;
		}
		else if (wParam == 'Q') {
			zoomIn += 0.3;
		}
		else if (wParam == 'E') {
			zoomIn -= 0.3;
		}
		else if (wParam == 'Z') {
			rotateRobotY += 1.0;
		}
		else if (wParam == 'X') {
			rotateRobotY -= 1.0;
		}
		else if (wParam == 'T') {
		rotateRobotX += 1.0;
}
		else if (wParam == 'Y') {
		rotateRobotX -= 1.0;
		}
		else if (wParam == 'E') {
			if (extend == true)
				extend = false;
			else if (extend == false)
				extend = true;
		}
		else if (wParam == 'C') {
			if (leftHand == true) {
				leftHand = false;
			}
			else if (leftHand == false) {
				leftLeg = false;
				rightLeg = false;
				rightHand = false;
				leftHand = true;
				headAni = false;
				bodyAni = false;

			}
		}   //control left arm
		else if (wParam == 'V') {
			if (rightHand == true) {
				rightHand = false;
			}
			else if (rightHand == false) {
				leftLeg = false;
				rightLeg = false;
				rightHand = true;
				leftHand = false;
				headAni = false;
				bodyAni = false;

			}
		}   //control right arm
		else if (wParam == 'B') {
			if (leftLeg == true) {
				leftLeg = false;
			}
			else if (leftLeg == false) {
				leftLeg = true;
				rightLeg = false;
				rightHand = false;
				leftHand = false;
				headAni = false;
				bodyAni = false;

			}
		}   //control left leg
		else if (wParam == 'N') {
			if (rightLeg == true) {
				rightLeg = false;
			}
			else if (rightLeg == false) {
				leftLeg = false;
				rightLeg = true;
				rightHand = false;
				leftHand = false;
				headAni = false;
				bodyAni = false;

			}
		}
		else if (wParam == 'M') {
			if (headAni == true) {
				headAni = false;
			}
			else if (headAni == false) {
				leftLeg = false;
				rightLeg = false;
				rightHand = false;
				leftHand = false;
				headAni = true;
				bodyAni = false;
			}
		}
		else if (wParam == 'F') {
		if (bodyAni == true) {
			bodyAni = false;
		}
		else if (bodyAni == false) {
			leftLeg = false;
			rightLeg = false;
			rightHand = false;
			leftHand = false;
			headAni = false;
			bodyAni = true;
		}
		}
		else if (wParam == 'G') {
		if (walking1 == true) {
			walking1 = false;
		}
		else if (walking1 == false) {
			walking1 = true;
		}
}
		else if (wParam == 'R') {
			if (extend == true) {
				extend = false;
			}
			else if (extend == false) {
				extend = true;
			}
		}
		else if (wParam == '8') {
			if (drawSaber1 == true) {

				drawSaber1 = false;
			}
			else if (drawSaber1 == false) {
				drawSaber1 = true;
				drawSaber2 = false;
			}

		}
		else if (wParam == '9') {
		if (drawSaber2 == true) {
			
			drawSaber2 = false;
		}
		else if (drawSaber2 == false) {
			drawSaber2 = true;
			drawSaber1 = false;
		}

		}
		else if (wParam == 'H') {
		if (running1 == true) {
			running1 = false;
		}
		else if (running1 == false) {
			running1 = true;
		}
		}
		else if (wParam == 'J') {
		if (jumping1 == true) {
			jumping1 = false;
			jumping2 = false;
			jumping3 = false;
			jumping4 = false;
		}
		else if (jumping1 == false) {
			jumping1 = true;
		}
		}
		else if (wParam == 'K') {
		if (attack == false) {
			attack = true;
		}
		else if (attack == true) {
			attack = false;
		}
		}
		else if (wParam == 'L') {
		if (aniMode == false) {
			aniMode = true;
		}
		else if (aniMode == true) {
			aniMode = false;
		}
		}	
		else if (wParam == VK_NUMPAD0) {
			if (leftHand == true) {
				if (leftShoulderAngle <= 170)
					leftShoulderAngle += 2;
			}
			else if (rightHand == true) {
				if (rightShoulderAngle <= 170)
					rightShoulderAngle += 2;
			}
			else if (leftLeg == true) {
				if (leftThigh <= 90) {
					leftThigh += 2;
				}
				if (leftThigh >= 0) {
					if (leftHipFront <= 90)
						leftHipFront += 2;
				}
				if (leftHipBack <= 0) {
					leftHipBack += 2;
				}
			}
			else if (rightLeg == true) {
				if (rightThigh <= 90) {
					rightThigh += 2;
				}
				if (rightThigh >= 0) {
					if (rightHipFront <= 90)
						rightHipFront += 2;
				}
				if (rightHipBack <= 0) {
					rightHipBack += 2;
				}
			}
			else if (headAni == true) {
				if (headX <= 25) {
					headX += 2;
				}
			}
			else if (bodyAni == true) {
				if (bodyY <= 25) {
					bodyY += 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD1) {
			if (leftHand == true) {
				if (leftShoulderAngle >= -20)
					leftShoulderAngle -= 2;
			}
			else if (rightHand == true) {
				if (rightShoulderAngle >= -20)
					rightShoulderAngle -= 2;
			}
			else if (leftLeg == true) {
				if (leftThigh >= -90) {
					leftThigh -= 2;
				}
				if (leftHipFront >= 0) {
					leftHipFront -= 2;
				}
				if (leftThigh < 0) {
					if (leftHipBack >= -90)
						leftHipBack -= 2;
				}
			}
			else if (rightLeg == true) {
				if (rightThigh >= -90) {
					rightThigh -= 2;
				}
				if (rightHipFront >= 0) {
					rightHipFront -= 2;
				}
				if (rightThigh < 0) {
					if (rightHipBack >= -90)
						rightHipBack -= 2;
				}
			}
			else if (headAni == true) {
				if (headX >= -25) {
					headX -= 2;
				}
			}
			else if (bodyAni == true) {
				if (bodyY >= -25) {
					bodyY -= 2;
				}
			}

		}
		else if (wParam == VK_NUMPAD2) {
			if (leftHand == true) {
				if (leftElbowAngle <= 90) {
					leftElbowAngle += 2;
				}
			}
			else if (rightHand == true) {
				if (rightElbowAngle <= 90) {
					rightElbowAngle += 2;
				}
			}
			else if (leftLeg == true) {
				if (leftKnee < 0) {
					leftKnee += 2;
				}
			}
			else if (rightLeg == true) {
				if (rightKnee < 0) {
					rightKnee += 2;
				}
			}
			else if (headAni == true) {
				if (headY <= 25) {
					headY += 2;
				}
			}

		}
		else if (wParam == VK_NUMPAD3) {
			if (leftHand == true) {
				if (leftElbowAngle >= 0) {
					leftElbowAngle -= 2;
				}
			}
			else if (rightHand == true) {
				if (rightElbowAngle >= 0) {
					rightElbowAngle -= 2;
				}
			}
			else if (leftLeg == true) {
				if (leftKnee >= -150) {
					leftKnee -= 2;
				}
			}
			else if (rightLeg == true) {
				if (rightKnee >= -150) {
					rightKnee -= 2;
				}
			}
			else if (headAni == true) {
				if (headY >= -25) {
					headY -= 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD4) {
			if (leftHand == true) {
				if (leftWristX <= 45) {
					leftWristX += 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristX <= 45) {
					rightWristX += 2;
				}
			}
			else if (leftLeg == true) {
				if (leftHeel <= 25) {
					leftHeel += 2;
				}
			}
			else if (rightLeg == true) {
				if (rightHeel <= 25) {
					rightHeel += 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD5) {
			if (leftHand == true) {
				if (leftWristX >= -45) {
					leftWristX -= 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristX >= -45) {
					rightWristX -= 2;
				}
			}
			else if (leftLeg == true) {
				if (leftHeel >= -25) {
					leftHeel -= 2;
				}
			}
			else if (rightLeg == true) {
				if (rightHeel >= -25) {
					rightHeel -= 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD6) {
			if (leftHand == true) {
				if (leftWristY <= 45) {
					leftWristY += 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristY <= 45) {
					rightWristY += 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD7) {
			if (leftHand == true) {
				if (leftWristY >= -45) {
					leftWristY -= 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristY >= -45) {
					rightWristY -= 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD8) {
			if (leftHand == true) {
				if (leftWristZ <= 45) {
					leftWristZ += 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristZ <= 45) {
					rightWristZ += 2;
				}
			}
		}
		else if (wParam == VK_NUMPAD9) {
			if (leftHand == true) {
				if (leftWristZ >= -45) {
					leftWristZ -= 2;
				}
			}
			else if (rightHand == true) {
				if (rightWristZ >= -45) {
					rightWristZ -= 2;
				}
			}
		}
		else if (wParam == VK_SPACE) {
		// Projection Reset
		isOrtho = true;
		Ry = 180, Tx = 0, Rangle = 0;
		rVSpeed = 1.5, tSpeed = 0.1;

		eyeX = 0, eyeY = 0, eyeZ = -0.1;
		lookAtX = 0, lookAtY = 0, lookAtZ = 0;
		upX = 0, upY = 1, upZ = 0;

		rotateRobotX = 0;
		rotateRobotY = 0;
		zoomIn = 0;

		// Texture Reset
		textureMode = 1;
		worldMode = 1;


		// Lighting Reset
		isLightOn = false;
		positionLightTop[0] = 1.0;
		positionLightTop[1] = 1.0;
		positionLightTop[2] = 1.0;
		positionLightTop[3] = 0.0;
		positionLightCenter[0] = 5.0;
		positionLightCenter[1] = 10.0;
		positionLightCenter[2] = 2.0;
		positionLightCenter[3] = 1.0;

		  extend = false;
		  leftHand = false;
		  rightHand = false;
		  leftLeg = false;
		  rightLeg = false;
		  headAni = false;
		  bodyAni = false;
		  drawSaber1 = false;
		  drawSaber2 = false;
		  getSaber = false;
		  walking1 = false;
		  leftLegFront = false;
		  rightLegFront = false;
		  abc = false;
		  running1 = false;
		  jumping1 = false;
		  jumping2 = false;
		  jumping3 = false;
		  jumping4 = false;

		  attack = false;
		  attack1 = false;

		  aniMode = false;
		  length = 0.2;


		  leftShoulderAngle = 0;
		  leftElbowAngle = 0;
		  leftWristX = 0;
		  leftWristY = 0;
		  leftWristZ = 0;

		  rightShoulderAngle = 0;
		  rightElbowAngle = 0;
		  rightWristX = 0;
		  rightWristY = 0;
		  rightWristZ = 0;


		  leftHeel = 0;
		  leftKnee = 0;
		  leftThigh = 0;
		  leftHipFront = 0;
		  leftHipBack = 0;

		  rightHeel = 0;
		  rightKnee = 0;
		  rightThigh = 0;
		  rightHipFront = 0;
		  rightHipBack = 0;

		  headX = 0;
		  headY = 0;

		  hipAngle = 0;

		  jumpHeight = 0;

		 walkingZ = 0;

		 bodyY = 0;
		 bodyMoveY = 0;
		}


		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void lightingSetup() {

	if (isLightOn) {
		glEnable(GL_LIGHTING);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_NORMALIZE);
	}
	else {
		glDisable(GL_LIGHTING);
		glDisable(GL_NORMALIZE);
	}

	glLightfv(GL_LIGHT1, GL_POSITION, positionLightTop);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specLight);

	glLightfv(GL_LIGHT2, GL_POSITION, positionLightCenter);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specLight);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, defaultAmbient);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
}

void projectionSetup() {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glRotatef(Ry, 0.0, 1.0, 0.0);	//rotate for view not object
	glTranslatef(Tx, 0.0, 0);
	glRotatef(Rangle, 1.0, 0.0, 0.0);	//rotate for view not object

	gluLookAt(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, upX, upY, upZ);


	if (isOrtho) {
		glOrtho(-1, 1, -1, 1, -1, 2);
	}
	else {
		glTranslatef(0, 0, zoomIn);
		gluPerspective(16.0, 1, -1.0, 1.0);
		glFrustum(-8.0, 8.0, -8.0, 8.0, 1.0, 17.0);
	}

}

GLUquadricObj* cylinder = NULL;

void skybox() {

	glPushMatrix();

	if (worldMode != 1) {
		glColor3f(1, 1, 1);
	}

	if (worldMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3f(0.5294, 0.8078, 0.9216);
	}
	else if (worldMode == 2) {
		glBindTexture(GL_TEXTURE_2D, sky);
	}
	else if (worldMode == 3) {
		glBindTexture(GL_TEXTURE_2D, night);
	}
	else if (worldMode == 4) {
		glBindTexture(GL_TEXTURE_2D, space);
	}

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, 1.8);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, -1.8);
	glTexCoord2f(1, 1);
	glVertex3f(2, 2, -1.8);
	glTexCoord2f(0, 1);
	glVertex3f(2, 2, 1.8);

	glTexCoord2f(0, 0);
	glVertex3f(-2, -2, 1.8);
	glTexCoord2f(1, 0);
	glVertex3f(-2, -2, -1.8);
	glTexCoord2f(1, 1);
	glVertex3f(2, -2, -1.8);
	glTexCoord2f(0, 1);
	glVertex3f(2, -2, 1.8);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, 1.8);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, 1.8);
	glTexCoord2f(1, 1);
	glVertex3f(2, -2, 1.8);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -2, 1.8);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, -1.8);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, -1.8);
	glTexCoord2f(1, 1);
	glVertex3f(2, -2, -1.8);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -2, -1.8);

	glTexCoord2f(0, 0);
	glVertex3f(-2, 2, -1.8);
	glTexCoord2f(1, 0);
	glVertex3f(-2, 2, 1.8);
	glTexCoord2f(1, 1);
	glVertex3f(-2, -2, 1.8);
	glTexCoord2f(0, 1);
	glVertex3f(-2, -2, -1.8);

	glTexCoord2f(0, 0);
	glVertex3f(2, 2, -1.8);
	glTexCoord2f(1, 0);
	glVertex3f(2, 2, 1.8);
	glTexCoord2f(1, 1);
	glVertex3f(2, -2, 1.8);
	glTexCoord2f(0, 1);
	glVertex3f(2, -2, -1.8);
	glEnd();
	glPopMatrix();
}

void head(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float yellowR, float yellowG, float yellowB, float redR, float redG, float redB) {


	if (cylinder == NULL)
		cylinder = gluNewQuadric();
	glPushMatrix();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
	}



	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0, 0.525, 0);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.05, 10, 10);
	glPopMatrix();

	//helmet left piece
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);

	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.55, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.55, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, 0.64, 0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.55, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, 0.06);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.64, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.04);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.55, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.55, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.55, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.55, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.55, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.64, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.55, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, 0.06);
	glEnd();
	glPopMatrix();

	//helmet back piece
	glPushMatrix();
	glColor3f(whiteR, whiteG, whiteB);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}

	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.64, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(-0.035, 0.56, -0.059);
	glTexCoord2f(1, 1);
	glVertex3f(0.035, 0.56, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, 0.64, -0.059);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, -0.039);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.55, -0.039);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, -0.039);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.039);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.64, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(-0.035, 0.56, -0.059);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.55, -0.039);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.039);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.035, 0.64, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(0.035, 0.56, -0.059);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, -0.039);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.039);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.64, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(0.035, 0.64, -0.059);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, -0.039);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.039);

	//bottom 
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.56, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(0.035, 0.56, -0.059);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, -0.039);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.55, -0.039);
	glEnd();
	glPopMatrix();

	//helmet top piece
	glPushMatrix();
	glColor3f(whiteR, whiteG, whiteB);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}

	glBegin(GL_QUADS);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.035, 0.67, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.035, 0.67, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, 0.67, -0.02);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.04);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.035, 0.67, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.035, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.035, 0.67, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.035, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.65, -0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, 0.67, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, 0.67, 0.04);
	glEnd();
	glPopMatrix();

	//helmet right piece
	glPushMatrix();
	glColor3f(whiteR, whiteG, whiteB);

	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}

	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.55, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.55, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, 0.64, 0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.65, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.55, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, 0.06);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.64, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.04);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.075, 0.55, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.55, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.55, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.075, 0.64, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.55, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, -0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.075, 0.64, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.55, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.55, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.65, 0.06);
	glEnd();
	glPopMatrix();

	//helmet front
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0, 0);
	glVertex3f(0., 0.65, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.63, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.62, 0.09);

	glTexCoord2f(0, 0);
	glVertex3f(-0., 0.65, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.63, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0, 0.62, 0.09);

	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.63, 0.07);

	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(0., 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.63, 0.07);

	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.65, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0., 0.63, 0.07);

	glEnd();

	//helmet faceplate
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}

	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.6, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.55, 0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, 0.58, 0.07);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.6, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.55, 0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, 0.58, 0.07);
	glEnd();
	glPopMatrix();

	//face shield
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.59, 0.055);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.55, 0.055);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.55, 0.075);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.6, 0.075);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.59, 0.055);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.55, 0.055);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.55, 0.075);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.6, 0.075);
	glEnd();
	glPopMatrix();

	//eye frame 
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}
	glColor3f(redR, redG, redB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.65, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.56, 0.055);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.58, 0.075);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.65, 0.05);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.65, 0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.56, 0.055);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.58, 0.075);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0.65, 0.05);

	glEnd();
	glPopMatrix();

	//eye
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(yellowR, yellowG, yellowB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.625, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, 0.61, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, 0.61, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(-0.005, 0.62, 0.065);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.625, 0.06);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, 0.61, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.61, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(0.005, 0.62, 0.065);
	glEnd();
	glPopMatrix();

	//chin
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}

	glColor3f(redR, redG, redB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.01, 0.565, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.01, 0.545, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.01, 0.54, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.01, 0.56, 0.085);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.01, 0.565, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.01, 0.55, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.01, 0.545, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.01, 0.56, 0.085);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.01, 0.54, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.01, 0.56, 0.085);
	glTexCoord2f(1, 1);
	glVertex3f(0.01, 0.56, 0.085);
	glTexCoord2f(0, 1);
	glVertex3f(0.01, 0.54, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.01, 0.565, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.01, 0.56, 0.085);
	glTexCoord2f(1, 1);
	glVertex3f(0.01, 0.56, 0.085);
	glTexCoord2f(0, 1);
	glVertex3f(0.01, 0.565, 0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.01, 0.545, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.01, 0.54, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.01, 0.545, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.01, 0.55, 0.07);
	glEnd();
	glPopMatrix();

	//mohawk
	glPushMatrix();
	glColor3f(redR, redG, redB);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}

	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, 0.67, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.7, 0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.67, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.7, 0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.67, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.7, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.7, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.67, 0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.67, -0.02);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.7, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.7, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.7, -0.02);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(redR, redG, redB);
	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.7, -0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.67, -0.02);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.64, -0.059);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.67, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.67, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.64, -0.059);

	//left
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, 0.64, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.67, -0.06);

	//right
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.64, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.67, -0.06);

	//top
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.7, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.7, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.67, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.67, -0.06);

	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.67, -0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.67, -0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.64, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.7, -0.02);
	glEnd();
	glPopMatrix();

	//helmet up armor
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.085, 0.56, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.085, 0.62, 0.02);

	//top left
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.62, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.62, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, 0.64, -0.04);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.56, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.56, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.56, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, 0.56, -0.04);

	//back left
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.56, -0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, 0.65, -0.07);

	//back left top
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, 0.65, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.64, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.64, -0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.65, -0.07);

	//back left bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, 0.56, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.56, -0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.56, -0.07);

	//front left
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.56, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.085, 0.62, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.075, 0.62, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, 0.56, 0.02);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.04, 0.65, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, 0.56, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.56, -0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, 0.65, -0.07);

	//back top
	glTexCoord2f(0, 0);
	glVertex3f(0.04, 0.65, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, 0.65, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.65, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, 0.65, -0.059);

	//back bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.04, 0.56, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, 0.56, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.56, -0.059);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, 0.56, -0.059);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.085, 0.56, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.085, 0.62, 0.02);

	//top right
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.62, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.62, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, 0.64, -0.04);

	//bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.56, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.56, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.56, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, 0.56, -0.04);

	//back right
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.64, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, 0.56, -0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, 0.65, -0.07);

	//back right top
	glTexCoord2f(0, 0);
	glVertex3f(0.04, 0.65, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.64, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.64, -0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.65, -0.07);

	//back right bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.04, 0.56, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.56, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.56, -0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.56, -0.07);

	//front right
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.56, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.085, 0.62, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.62, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.075, 0.56, 0.02);

	glEnd();
	glPopMatrix();

	//front head v shape
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}

	glColor3f(redR, redG, redB);
	glBegin(GL_POLYGON);

	//front
	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.015, 0.66, 0.07);
	glVertex3f(0.015, 0.66, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.64, 0.08);
	glVertex3f(0, 0.63, 0.09);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.64, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.015, 0.66, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.015, 0.66, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.015, 0.66, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.015, 0.66, 0.05);

	//top left
	glTexCoord2f(0, 0);
	glVertex3f(-0.015, 0.66, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.64, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, 0.64, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.015, 0.66, 0.05);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(-0.02, 0.64, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.63, 0.09);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.63, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, 0.64, 0.05);

	//top right
	glTexCoord2f(0, 0);
	glVertex3f(0.015, 0.66, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.64, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, 0.64, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.015, 0.66, 0.05);

	//bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0.02, 0.64, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0, 0.63, 0.09);
	glTexCoord2f(1, 1);
	glVertex3f(0, 0.63, 0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, 0.64, 0.05);
	glEnd();

	//v left
	glBegin(GL_TRIANGLES);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.7, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.015, 0.64, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.015, 0.65, 0.08);

	//top
	glVertex3f(-0.085, 0.7, 0.07);
	glVertex3f(-0.015, 0.66, 0.06);
	glVertex3f(-0.015, 0.65, 0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.085, 0.7, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.015, 0.66, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.015, 0.64, 0.06);
	glEnd();

	//v right
	glBegin(GL_TRIANGLES);
	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.7, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.015, 0.64, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.015, 0.65, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.7, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.015, 0.66, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.015, 0.65, 0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.085, 0.7, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.015, 0.66, 0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.015, 0.64, 0.06);
	glEnd();
	glPopMatrix();


	glPopMatrix();
}

void backpack(float dGreyR, float dGreyG, float dGreyB, float greyR, float greyG, float greyB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		dGreyR = 1.0, dGreyG = 1.0, dGreyB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
	}

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glBegin(GL_POLYGON);
	//left

	glColor3f(dGreyR, dGreyG, dGreyB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.5, -0.2);
	glVertex3f(-0.15, 0.35, -0.2);
	glTexCoord2f(1, 0);

	glVertex3f(-0.15, 0.3, -0.18);
	glVertex3f(-0.15, 0.27, -0.15);
	glTexCoord2f(0, 1);

	glVertex3f(-0.15, 0.27, -0.12);
	glVertex3f(-0.15, 0.5, -0.12);
	glEnd();

	glBegin(GL_POLYGON);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.5, -0.2);
	glVertex3f(0.15, 0.35, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.3, -0.18);
	glVertex3f(0.15, 0.27, -0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, -0.12);
	glVertex3f(0.15, 0.5, -0.12);
	glEnd();

	glBegin(GL_QUADS);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.5, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.35, -0.2);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.2);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.5, -0.2);

	//back 1
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.35, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.3, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.35, -0.2);

	//back 2
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.3, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.27, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.27, -0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.3, -0.18);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.5, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.5, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, -0.12);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.5, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.5, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.5, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.5, -0.2);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.5, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.5, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, -0.12);
	glEnd();

	//left sword holder
	glBegin(GL_QUADS);
	glColor3f(dGreyR, dGreyG, dGreyB);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.48, -0.14);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.19, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.19, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.48, -0.14);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.19, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.35, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.48, -0.18);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.48, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.19, 0.35, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.48, -0.14);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.48, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.48, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.48, -0.18);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.35, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.35, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.19, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.19, 0.35, -0.18);

	// left support
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.35, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.35, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.35, -0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.18, 0.35, -0.17);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.3, -0.165);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, 0.3, -0.165);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.35, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(-0.16, 0.3, -0.155);
	glTexCoord2f(0, 1);
	glVertex3f(-0.18, 0.35, -0.15);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.3, -0.165);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.35, -0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.35, -0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.3, -0.165);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.35, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.35, -0.17);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.35, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.35, -0.15);
	glEnd();

	//right sword holder
	glBegin(GL_QUADS);
	glColor3f(dGreyR, dGreyG, dGreyB);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.48, -0.14);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.19, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.19, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.48, -0.14);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.19, 0.35, -0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.48, -0.18);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.48, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.19, 0.35, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.48, -0.14);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.48, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.48, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.48, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.48, -0.18);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.35, -0.18);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.35, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.19, 0.35, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.19, 0.35, -0.18);

	// left support
	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.35, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.35, -0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.18, 0.35, -0.17);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.16, 0.3, -0.165);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.3, -0.165);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.35, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.3, -0.155);
	glTexCoord2f(0, 1);
	glVertex3f(0.18, 0.35, -0.15);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.3, -0.165);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, 0.35, -0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.35, -0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.3, -0.165);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.35, -0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.35, -0.17);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.35, -0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.3, -0.165);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.3, -0.165);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.35, -0.15);
	glEnd();

	//left jet 
	//left
	glBegin(GL_POLYGON);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(-0.12, 0.27, -0.155);
	glVertex3f(-0.12, 0.27, -0.125);

	glEnd();

	//right
	glBegin(GL_POLYGON);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.055, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.055, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.27, -0.155);
	glVertex3f(-0.055, 0.27, -0.125);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.35, -0.205);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.37, -0.2);

	//middle
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.35, -0.205);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.3, -0.185);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.35, -0.205);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.3, -0.185);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.27, -0.155);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.27, -0.155);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.3, -0.185);

	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.27, -0.155);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.27, -0.125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.055, 0.27, -0.125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.055, 0.27, -0.155);
	glEnd();

	//right jet
	//left
	glBegin(GL_POLYGON);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(0.12, 0.27, -0.155);
	glVertex3f(0.12, 0.27, -0.125);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(0.055, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.055, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.27, -0.155);
	glVertex3f(0.055, 0.27, -0.125);
	glEnd();

	glBegin(GL_QUADS);
	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.37, -0.2);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.35, -0.205);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.35, -0.205);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.37, -0.2);

	//middle
	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.35, -0.205);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.3, -0.185);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.3, -0.185);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.35, -0.205);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.3, -0.185);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.27, -0.155);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.27, -0.155);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.3, -0.185);

	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.27, -0.155);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, 0.27, -0.125);
	glTexCoord2f(1, 1);
	glVertex3f(0.055, 0.27, -0.125);
	glTexCoord2f(0, 1);
	glVertex3f(0.055, 0.27, -0.155);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.09, 0.25, -0.2);
	glRotatef(-60, 1, 0, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.04, 0.01, 0.1, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.09, 0.25, -0.2);
	glRotatef(-60, 1, 0, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.04, 0.01, 0.1, 10, 10);
	glPopMatrix();
}

void body(float yellowR, float yellowG, float yellowB, float redR, float redG, float redB, float blueR, float blueG, float blueB, float lBlueR, float lBlueG, float lBlueB) {
	//neck

	if (textureMode != 1) {
		blueR = 1.0, blueG = 1.0, blueB = 1.0;
		lBlueR = 1.0, lBlueG = 1.0, lBlueB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
	}
	glPushMatrix();

	glPushMatrix();

	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}

	glBegin(GL_QUADS);

	glColor3f(yellowR, yellowG, yellowB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.07, 0.501, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.075, 0.501, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.075, 0.501, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, 0.501, -0.12);

	glTexCoord2f(0, 0);
	glVertex3f(-0.075, 0.501, 0.11);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.501, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.446, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.446, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glLineWidth(5.0f);
	glBegin(GL_LINE_STRIP);
	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.07, 0.505, -0.12);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.075, 0.505, 0.11);

	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.445, 0.15);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.445, 0.15);

	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.075, 0.505, 0.11);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.07, 0.505, -0.12);

	glVertex3f(-0.07, 0.505, -0.12);
	glEnd();

	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, copper);
	}
	//lower body red 1
	glPushMatrix();
	glColor3f(redR, redG, redB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.16, 0.2, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.27, 0.07);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.15, 0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.2, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, 0.07);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.2, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, -0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.2, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.2, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, 0.07);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.27, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.27, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.27, -0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.2, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.2, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.2, -0.07);
	glEnd();
	glPopMatrix();

	// lower body red 2
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, copper);
	}
	glColor3f(redR, redG, redB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.27, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.34, -0.09);
	glTexCoord2f(1, 1);
	glVertex3f(-0.17, 0.34, 0.09);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, 0.27, 0.08);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.16, 0.27, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, 0.34, -0.09);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0.34, 0.09);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.27, 0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.27, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.34, -0.09);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0.34, -0.09);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.27, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.27, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, 0.34, 0.09);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, 0.34, 0.09);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.27, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.27, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.27, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.27, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.27, -0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, 0.34, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.34, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, 0.34, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, 0.34, -0.08);
	glEnd();
	glPopMatrix();

	//upper body left and right
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, blueSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glColor3f(blueR, blueG, blueB);
	//left
	glBegin(GL_POLYGON);

	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.5, -0.12);
	glVertex3f(-0.2, 0.34, -0.12);
	glTexCoord2f(1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.34, 0.1);
	glVertex3f(-0.2, 0.43, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.5, 0.11);
	glVertex3f(-0.2, 0.5, -0.12);
	glEnd();

	//right
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.5, -0.12);
	glVertex3f(0.2, 0.34, -0.12);
	glTexCoord2f(1, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.34, 0.1);
	glVertex3f(0.2, 0.43, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.5, 0.11);
	glVertex3f(0.2, 0.5, -0.12);
	glEnd();

	//upper body 
	//back
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.5, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.34, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.34, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.5, -0.12);

	//front bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.34, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.43, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.43, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.34, 0.1);

	//front top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.42, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.5, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.5, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.43, 0.15);

	//top
	glColor3f(blueR, blueG, blueB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.5, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.5, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.5, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.5, -0.12);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.34, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.34, -0.12);
	glEnd();
	glPopMatrix();

	//middle
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, blueSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	else if (textureMode == 4) {

	}
	glColor3f(blueR, blueG, blueB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.028, 0.43, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.028, 0.21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, 0.21, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.38, 0.18);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.028, 0.43, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.028, 0.21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.21, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.38, 0.18);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.028, 0.43, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.38, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.38, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.028, 0.43, 0.15);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.028, 0.21, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.21, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.21, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.028, 0.21, 0);

	//front
	glColor3f(lBlueR, lBlueG, lBlueB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.21, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.38, 0.18);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.38, 0.18);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.21, 0.1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.028, 0.43, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.028, 0.21, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.028, 0.21, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.028, 0.43, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}
	glColor3f(yellowR, yellowG, yellowB);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.343, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, 0.42, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.42, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, 0.343, 0.1);

	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.343, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, 0.42, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, 0.42, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, 0.343, 0.1);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void armLeft(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float dGreyR, float dGreyG, float dGreyB, float greenR, float greenG, float greenB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	glPushMatrix();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
		dGreyR = 1.0, dGreyG = 1.0, dGreyB = 1.0;
		greenR = 1.0, greenG = 1.0, greenB = 1.0;
	}

	//elbow
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(greyR, greyG, greyB);
	gluQuadricTexture(cylinder, true);
	glTranslatef(-0.235, 0.26, 0);
	glRotatef(-90, 0, 1, 0);

	gluCylinder(cylinder, 0.025, 0.025, 0.1, 10, 10);
	glPopMatrix();

	//elbow decoration
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.31, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.31, 0.24, -0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.27, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.27, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.24, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.27, 0.17, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.24, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.17, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.17, -0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.24, -0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.17, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.17, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.17, -0.05);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.31, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.31, 0.28, -0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.27, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.27, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, 0.28, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.27, 0.24, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.28, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.28, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.3, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.27, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.28, -0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.28, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.28, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.28, -0.08);

	// bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.27, 0.24, -0.08);

	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.235, 0.26, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.025, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.335, 0.26, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.025, 10, 1);
	glPopMatrix();

	//lower arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.32, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.33, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.32, 0.24, 0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.25, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.24, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 0.24, 0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.32, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.15, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 0.24, -0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.32, 0.24, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.25, 0.24, 0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.32, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(-0.32, 0.24, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, 0.24, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(-0.32, 0.24, -0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.32, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.32, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.25, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.32, 0.15, -0.045);
	glEnd();
	glPopMatrix();


	//lower arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.33, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.33, 0.15, 0.045);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.24, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.24, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.15, 0.045);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.03, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.15, -0.045);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.15, 0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.03, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.15, 0.045);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.15, -0.045);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.03, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.03, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.03, -0.045);
	glEnd();
	glPopMatrix();



	glPopMatrix();
}

void armLeft1(float whiteR, float whiteG, float whiteB) {

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}
	glPushMatrix();
	//shoulder
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}


	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.34, 0.4, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.34, 0.4, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.36, 0.55, 0.07);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.201, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.201, 0.39, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.201, 0.39, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.201, 0.55, 0.07);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.34, 0.4, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.39, -0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.55, -0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.34, 0.4, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, 0.55, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.39, 0.07);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.36, 0.55, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.55, -0.07);

	////bottom
	//glTexCoord2f(0, 0);
	//glVertex3f(-0.34, 0.4, -0.07);
	//glTexCoord2f(1, 0);
	//glVertex3f(-0.34, 0.4, 0.07);
	//glTexCoord2f(1, 1);
	//glVertex3f(-0.201, 0.39, 0.07);
	//glTexCoord2f(0, 1);
	//glVertex3f(-0.201, 0.39, -0.07);
	glEnd();
	glPopMatrix();


	//upper arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.33, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.33, 0.45, 0.045);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.24, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.24, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.45, 0.045);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.27, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.45, -0.045);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.45, 0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.29, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.45, 0.045);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.45, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.45, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.45, -0.045);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.33, 0.27, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(-0.33, 0.29, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(-0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(-0.24, 0.27, -0.045);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void handLeft(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float dGreyR, float dGreyG, float dGreyB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
		dGreyR = 1.0, dGreyG = 1.0, dGreyB = 1.0;
	}
	glPushMatrix();
	//wrist
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glTranslatef(-0.285, 0.03, 0);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.025, 10, 10);
	glPopMatrix();

	//hand
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.31, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.31, 0.01, 0.03);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.28, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.28, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.050065, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, 0.01, 0.03);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.05, -0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, 0.01, -0.03);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.01, 0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, -0.05, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, 0.01, 0.03);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, 0.01, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, 0.01, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, 0.01, -0.03);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.31, -0.05, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(-0.31, -0.05, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(-0.28, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(-0.28, -0.05, -0.03);
	glEnd();
	glPopMatrix();

	//hand part 1 cylinder
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.295, -0.06, -0.025);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.0075, 0.0075, 0.05, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.295, -0.06, -0.025);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.0075, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.295, -0.06, 0.025);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.0075, 10, 1);
	glPopMatrix();

	// index finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0525, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0675, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2575, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2575, -0.0675, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, 0.013);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.06, 0.019);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0535, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0535, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0385, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2525, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.013);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.0310, 0.01);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0235, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0235, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0385, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.013);
	glEnd();

	//middle finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front

	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0525, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0675, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0675, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, 0.0005);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.06, 0.0065);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0535, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0535, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0385, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2525, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0.0005);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.0310, 0.0065);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0235, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0235, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0385, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0.0005);
	glEnd();

	//ring finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0525, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0675, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0675, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, -0.0120);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.06, -0.006);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0535, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0535, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0385, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2525, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, -0.0120);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.0310, -0.006);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0235, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0235, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0385, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0385, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, -0.0120);
	glEnd();

	//little finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0675, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0525, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0525, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0675, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0675, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0675, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0675, -0.025);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.06, -0.0185);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0535, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0535, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0385, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0535, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2525, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2525, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2525, -0.0535, -0.025);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.26, -0.0310, -0.0185);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0235, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0235, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0385, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2875, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2875, -0.0235, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.2675, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2675, -0.0235, -0.025);
	glEnd();

	//thumb
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(-0.27, 0, 0.02);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.01, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.26, 0.005, 0.01);
	glRotatef(-50, 0, 0, 1);
	glTranslatef(0.26, -0.005, -0.01);

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.26, 0.01, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.23, 0.01, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(-0.23, -0.01, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.26, -0.01, 0.02);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void armRight(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float dGreyR, float dGreyG, float dGreyB, float greenR, float greenG, float greenB) {
	glPushMatrix();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
		dGreyR = 1.0, dGreyG = 1.0, dGreyB = 1.0;
		greenR = 1.0, greenG = 1.0, greenB = 1.0;
	}
	//elbow
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.235, 0.26, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.025, 0.025, 0.1, 10, 10);
	glPopMatrix();

	//elbow left
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.235, 0.26, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.025, 10, 1);
	glPopMatrix();

	//elbow right
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.335, 0.26, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.025, 10, 1);
	glPopMatrix();

	//elbow decoration
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.31, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.31, 0.24, -0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.27, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.27, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.24, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.17, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.27, 0.17, -0.05);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.24, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.17, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.17, -0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.24, -0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.17, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.17, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.17, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.17, -0.05);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.31, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.31, 0.28, -0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.27, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.27, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, 0.28, -0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.27, 0.24, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.28, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.28, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.3, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.27, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.28, -0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.28, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.28, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.28, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.28, -0.08);

	// bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.3, 0.24, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.24, -0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.26, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.27, 0.24, -0.08);

	glEnd();

	glPopMatrix();

	//lower arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.32, 0.24, -0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.33, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.33, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.32, 0.24, 0.04);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.25, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.24, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.24, 0.04);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.32, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.15, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.15, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.24, -0.04);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.32, 0.24, 0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.25, 0.24, 0.04);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.32, 0.24, -0.04);
	glTexCoord2f(1, 0);
	glVertex3f(0.32, 0.24, 0.04);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, 0.24, 0.04);
	glTexCoord2f(0, 1);
	glVertex3f(0.32, 0.24, -0.04);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.32, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.32, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.25, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.32, 0.15, -0.045);
	glEnd();
	glPopMatrix();


	//lower arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.33, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.33, 0.15, 0.045);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.24, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.24, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.15, 0.045);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.03, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.03, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.15, -0.045);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.15, 0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.03, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.15, 0.045);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.15, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.15, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.15, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.15, -0.045);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.03, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.03, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.03, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.03, -0.045);
	glEnd();
	glPopMatrix();

	//wrist
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glTranslatef(0.285, 0.03, 0);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.025, 10, 10);
	glPopMatrix();

	glPopMatrix();
}

void armRight1(float whiteR, float whiteG, float whiteB) {

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}
	glPushMatrix();
	//shoulder
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.34, 0.4, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.34, 0.4, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.36, 0.55, 0.07);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.201, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.201, 0.39, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.201, 0.39, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.201, 0.55, 0.07);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.34, 0.4, -0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.39, -0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.55, -0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.34, 0.4, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, 0.55, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.39, 0.07);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.36, 0.55, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.36, 0.55, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.55, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.55, -0.07);

	////bottom
	//glTexCoord2f(0, 0);
	//glVertex3f(-0.34, 0.4, -0.07);
	//glTexCoord2f(1, 0);
	//glVertex3f(-0.34, 0.4, 0.07);
	//glTexCoord2f(1, 1);
	//glVertex3f(-0.201, 0.39, 0.07);
	//glTexCoord2f(0, 1);
	//glVertex3f(-0.201, 0.39, -0.07);
	glEnd();
	glPopMatrix();


	//upper arm
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.33, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.33, 0.45, 0.045);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.24, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.24, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.45, 0.045);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.27, -0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.27, -0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.45, -0.045);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.45, 0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.29, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.45, 0.045);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.45, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.45, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.45, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.45, -0.045);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.33, 0.27, -0.045);
	glTexCoord2f(1, 0);
	glVertex3f(0.33, 0.29, 0.045);
	glTexCoord2f(1, 1);
	glVertex3f(0.24, 0.29, 0.045);
	glTexCoord2f(0, 1);
	glVertex3f(0.24, 0.27, -0.045);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void handRight(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float dGreyR, float dGreyG, float dGreyB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
		dGreyR = 1.0, dGreyG = 1.0, dGreyB = 1.0;
	}

	//hand
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.31, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.31, 0.01, 0.03);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.28, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.28, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.050065, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, 0.01, 0.03);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, -0.05, -0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.05, -0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, 0.01, -0.03);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.01, 0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, -0.05, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, 0.01, 0.03);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.31, 0.01, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, 0.01, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, 0.01, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, 0.01, -0.03);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.31, -0.05, -0.03);
	glTexCoord2f(1, 0);
	glVertex3f(0.31, -0.05, 0.03);
	glTexCoord2f(1, 1);
	glVertex3f(0.28, -0.05, 0.03);
	glTexCoord2f(0, 1);
	glVertex3f(0.28, -0.05, -0.03);
	glEnd();
	glPopMatrix();

	//hand part 1 cylinder
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.295, -0.06, -0.025);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.0075, 0.0075, 0.05, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.295, -0.06, -0.025);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.0075, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.295, -0.06, 0.025);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.0075, 10, 1);
	glPopMatrix();

	// index finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0525, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0675, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2575, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2575, -0.0675, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0525, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0525, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, 0.013);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.06, 0.019);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0535, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0535, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0385, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2525, -0.0535, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.013);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.0310, 0.01);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.025);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.013);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.013);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.013);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0235, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0235, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, 0.013);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0385, 0.013);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, 0.013);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0235, 0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.013);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.013);
	glEnd();

	//middle finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front

	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0525, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0675, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0675, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0525, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0525, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, 0.0005);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.06, 0.0065);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0535, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0535, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0385, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2525, -0.0535, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0.0005);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.0310, 0.0065);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.0005);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.0005);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.0005);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0235, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0235, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, 0.0005);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0385, 0.0005);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, 0.0005);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0235, 0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0.0005);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0.0005);
	glEnd();

	//ring finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0525, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0675, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0675, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0525, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0525, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, -0.0120);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.06, -0.006);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0535, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0535, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0385, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2525, -0.0535, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, -0.0120);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.0310, -0.006);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, -0.0120);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, -0.0120);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, -0.0120);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0235, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0235, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, -0.0120);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0385, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0385, -0.0120);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, -0.0120);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0235, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.0120);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, -0.0120);
	glEnd();

	//little finger
	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0675, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0525, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0525, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0675, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0675, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0675, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0675, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0525, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0525, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0675, -0.025);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.06, -0.0185);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0535, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0535, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0385, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0535, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2525, -0.0535, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2525, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2525, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2525, -0.0535, -0.025);
	glEnd();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.26, -0.0310, -0.0185);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.0075, 10, 10);
	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, -0.0125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, -0.025);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, -0.025);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, -0.025);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0235, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0235, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, -0.025);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0385, -0.025);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.2875, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2875, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2875, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2875, -0.0235, -0.025);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.2675, -0.0235, -0.0125);
	glTexCoord2f(1, 0);
	glVertex3f(0.2675, -0.0385, -0.0125);
	glTexCoord2f(1, 1);
	glVertex3f(0.2675, -0.0385, -0.025);
	glTexCoord2f(0, 1);
	glVertex3f(0.2675, -0.0235, -0.025);
	glEnd();

	//thumb
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	}	glColor3f(dGreyR, dGreyG, dGreyB);
	glTranslatef(0.27, 0, 0.02);
	gluQuadricTexture(cylinder, true);
	gluSphere(cylinder, 0.01, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.26, 0.005, 0.01);
	glRotatef(50, 0, 0, 1);
	glTranslatef(-0.26, -0.005, -0.01);

	glBegin(GL_QUADS);
	glColor3f(greyR, greyG, greyB);
	glTexCoord2f(0, 0);
	glVertex3f(0.26, 0.01, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.23, 0.01, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.23, -0.01, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.26, -0.01, 0.02);
	glEnd();
	glPopMatrix();
}

void hip(float whiteR, float whiteG, float whiteB, float redR, float redG, float redB, float yellowR, float yellowG, float yellowB) {
	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
	}
	//hip
	glPushMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	//left
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.2, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.2, 0.025, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.2, 0.025, 0.1);
	glEnd();

	//top
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.2, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, 0.2, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.2, 0.1);
	glEnd();

	//right right
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.2, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.2, 0.025, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.2, 0.025, 0.1);
	glEnd();


	//right top
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.2, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.2, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, 0.1);
	glEnd();


	// hip middle
	glBegin(GL_QUADS);
	//front
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, 0.2, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, -0.025, 0.1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, -0.13);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, 0.2, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, -0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, -0.025, -0.13);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.2, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, -0.025, -0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, -0.025, 0.1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.025, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, 0.2, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, -0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.025, 0.1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.2, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.2, -0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, 0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, -0.025, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, -0.025, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, -0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.025, 0.15);
	glEnd();

	// 红色装饰品
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, copper);
	}

	glBegin(GL_QUADS);
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.021, 0.19, 0.101);
	glTexCoord2f(1, 0);
	glVertex3f(-0.021, 0.1, 0.101);
	glTexCoord2f(1, 1);
	glVertex3f(0.021, 0.1, 0.101);
	glTexCoord2f(0, 1);
	glVertex3f(0.021, 0.19, 0.101);
	glEnd();
	glPopMatrix();

	//front buldge
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.1, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, -0.025, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, -0.025, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.08, 0.16);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.025, 0.1, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, -0.025, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.08, 0.16);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, -0.025, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.08, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.08, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.025, 0.15);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.1, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.08, 0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.08, 0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.1, 0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, -0.025, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, -0.025, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.025, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.025, 0.1);
	glEnd();
	glPopMatrix();

	//back buldge
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, -0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, -0.025, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, 0, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.2, -0.14);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.025, 0.2, -0.13);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, -0.025, -0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, -0.14);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0, -0.16);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.2, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.2, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0, -0.16);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.2, -0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0.2, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0.2, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, -0.13);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, -0.025, -0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, 0, -0.16);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0, -0.16);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.025, -0.13);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void hipMovingLeftFront(float whiteR, float whiteG, float whiteB, float yellowR, float yellowG, float yellowB) {
	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
	}

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	// Front
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.025, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, 0, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.2, 0.1);
	glEnd();
	glPopMatrix();

	//yellow decoration left
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(yellowR, yellowG, yellowB);
	glBegin(GL_QUADS);
	//left

	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, 0.05, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.175, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.175, 0.175, 0.13);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.05, 0.05, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.175, 0.13);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.05, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, 0.175, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.175, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.05, 0.13);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.05, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, 0.175, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.175, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.05, 0.1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, 0.175, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.175, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.175, 0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.05, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, 0.05, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, 0.05, 0.1);
	glEnd();
	glPopMatrix();

}

void hipMovingLeftBack(float whiteR, float whiteG, float whiteB) {
	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;

	}
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	// back
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.2, 0.2, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.2, 0.025, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, 0, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.2, -0.1);
	glEnd();
	glPopMatrix();
}

void hipMovingRightBack(float whiteR, float whiteG, float whiteB) {
	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	// right back
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.2, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.025, -0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, -0.1);
	glEnd();
	glPopMatrix();
}

void hipMovingRightFront(float whiteR, float whiteG, float whiteB, float yellowR, float yellowG, float yellowB) {
	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
	}

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	// right front
	glBegin(GL_POLYGON);
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.2, 0.2, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.2, 0.025, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, 0, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.2, 0.1);
	glEnd();

	//yellow decoration right
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(yellowR, yellowG, yellowB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, 0.05, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.175, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.175, 0.175, 0.13);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.05, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.05, 0.05, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.175, 0.13);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.05, 0.13);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, 0.175, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.175, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.05, 0.13);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.05, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, 0.175, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.175, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.05, 0.1);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.175, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, 0.175, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.175, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.175, 0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.05, 0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, 0.05, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, 0.05, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, 0.05, 0.1);
	glEnd();

	glPopMatrix();

}

void legLeft(float whiteR, float whiteG, float whiteB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}

	glPushMatrix();
	glColor3f(whiteR, whiteG, whiteB);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glTranslatef(-0, 0.1, 0);
	glRotatef(-90, 0, 1, 0);
	gluCylinder(cylinder, 0.05, 0.05, 0.15, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glTranslatef(-0.15, 0.1, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.05, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glTranslatef(-0.15, 0.1, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.05, 10, 1);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glColor3f(whiteR, whiteG, whiteB);
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.16, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(-0.175, 0.1, 0.08);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.025, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.1, 0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.2, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.1, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.1, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.23, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.1, 0.08);

	//top
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, 0.1, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, 0.1, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, 0.1, -0.08);

	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.2, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.23, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(-0.16, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, -0.2, -0.08);
	glEnd();
	glPopMatrix();
}

void legLeft1(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
	}

	//knee
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.03, 0.13, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.17, -0.24, 0);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	//knee guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.1, -0.44, 0.07);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0, 0.06, 0.1, 4, 4);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.14, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, -0.27, 0.125);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.06, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.34, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.27, 0.125);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.27, 0.125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.27, 0.125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.34, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.34, 0.07);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.14, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, -0.27, 0.125);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.06, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.2, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.125);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.2, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.125);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.27, 0.125);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.27, 0.125);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.27, 0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.2, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.2, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.2, 0.07);
	glEnd();
	glPopMatrix();

	//calf
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.155, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.165, -0.27, 0.08);

	////right
	glTexCoord2f(0, 0);
	glVertex3f(-0.035, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(-0.045, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.035, -0.27, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(-0.165, -0.27, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.035, -0.27, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.035, -0.27, -0.09);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.155, -0.45, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.4, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.045, -0.45, -0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.45, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.035, -0.27, -0.09);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.155, -0.4, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.165, -0.27, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.035, -0.27, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.045, -0.4, 0.08);
	glEnd();
	glPopMatrix();

	//lower leg
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glBegin(GL_QUADS);

	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.155, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.14, -0.27, 0.07);

	//right
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.06, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.045, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.27, 0.07);

	//back
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.6, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.27, -0.07);
	//front
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.6, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.27, 0.07);

	//top
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, -0.27, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(-0.06, -0.27, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(-0.06, -0.27, -0.07);

	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.155, -0.6, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.155, -0.6, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.045, -0.6, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.045, -0.6, 0.08);
	glEnd();
	glPopMatrix();
}

void feetLeft(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float redR, float redG, float redB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
	}

	//heel joint
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(-90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.03, 0.15, 10, 10);
	glPopMatrix();

	//heel joint left cover
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.175, -0.63, -0.02);
	glRotatef(-90, 0, 1, 0);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	//heel joint right cover
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(-90, 0, 1, 0);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();//heel guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.6, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.175, -0.67, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.175, -0.67, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.16, -0.57, 0.13);

	////right
	glTexCoord2f(0, 0);
	glVertex3f(-0.04, -0.6, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(-0.025, -0.67, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(-0.025, -0.67, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.57, 0.13);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.175, -0.67, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.57, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.57, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(-0.025, -0.67, 0.15);
	glEnd();
	glPopMatrix();

	//upper feet
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}

	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(-0.16, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.6, -0.06);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.04, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.6, -0.06);

	////back
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.7, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.6, -0.1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.7, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.6, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.6, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.7, -0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.6, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.6, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.6, -0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.16, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.16, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.04, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.04, -0.7, -0.12);
	glEnd();
	glPopMatrix();

	//below heel guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}

	glBegin(GL_QUADS);

	//left
	glColor3f(whiteR, whiteG, whiteB);

	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.17, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, -0.6, 0.1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.05, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.7, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.6, 0.1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.65, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, -0.7, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.6, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.6, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.7, 0.15);
	glEnd();
	glPopMatrix();

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, -0.6, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(-0.05, -0.6, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.05, -0.65, -0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, -0.7, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.7, -0.08);

	//bottom feet
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}	glBegin(GL_QUADS);
	glColor3f(redR, redG, redB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.18, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.17, -0.7, 0.15);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.03, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.7, 0.15);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, -0.73, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.7, -0.12);

	////front
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, -0.73, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, -0.73, 0.17);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(-0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(-0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(-0.03, -0.7, -0.12);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, -0.73, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, -0.73, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(-0.02, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(-0.02, -0.73, -0.14);

	glEnd();
	glPopMatrix();
}

void legRight(float whiteR, float whiteG, float whiteB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}


	//upper leg
	glPushMatrix();
	glColor3f(whiteR, whiteG, whiteB);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glTranslatef(0, 0.1, 0);
	glRotatef(90, 0, 1, 0);
	gluCylinder(cylinder, 0.05, 0.05, 0.15, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glColor3f(whiteR, whiteG, whiteB);
	glTranslatef(0.15, 0.1, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.05, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}

	glColor3f(whiteR, whiteG, whiteB);
	glTranslatef(0.15, 0.1, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.05, 10, 1);
	glPopMatrix();

	//upper leg
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glBegin(GL_QUADS);

	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(0.175, 0.1, 0.08);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.025, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.1, 0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.2, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.2, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.1, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.1, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.23, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.1, 0.08);

	//top
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.175, 0.1, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, 0.1, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, 0.1, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, 0.1, -0.08);

	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.2, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.04, -0.23, 0.065);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, -0.23, 0.065);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, -0.2, -0.08);
	glEnd();
	glPopMatrix();
}

void legRight1(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
	}

	//knee
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.035, -0.24, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.03, 0.13, 10, 10);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.035, -0.24, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.17, -0.24, 0);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	//knee guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}

	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.1, -0.44, 0.07);
	glRotatef(-90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0, 0.06, 0.1, 4, 4);
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.14, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, -0.27, 0.125);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.06, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.34, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.34, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.125);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.27, 0.125);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.27, 0.125);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.27, 0.125);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.34, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.34, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.34, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.34, 0.07);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.14, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, -0.27, 0.125);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.06, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.125);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.2, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.2, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.07);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.125);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.2, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.125);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.27, 0.125);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.27, 0.125);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.27, 0.07);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.2, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.2, 0.11);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.2, 0.11);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.2, 0.07);
	glEnd();
	glPopMatrix();

	//calf
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.155, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.165, -0.27, 0.08);

	////right
	glTexCoord2f(0, 0);
	glVertex3f(0.035, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(0.045, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, -0.27, 0.08);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(0.165, -0.27, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.035, -0.27, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, -0.27, -0.09);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.155, -0.45, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.4, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.4, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.045, -0.45, -0.08);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.165, -0.27, -0.09);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.45, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.45, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.035, -0.27, -0.09);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.155, -0.4, 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.165, -0.27, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.035, -0.27, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.045, -0.4, 0.08);
	glEnd();
	glPopMatrix();

	//lower leg
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, matteBlack);
	}
	glBegin(GL_QUADS);

	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.155, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.14, -0.27, 0.07);

	//right
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.06, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.045, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.27, 0.07);

	//back
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.6, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.6, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.27, -0.07);
	//front
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.27, 0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.6, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.6, 0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.27, 0.07);

	//top
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.14, -0.27, -0.07);
	glTexCoord2f(1, 0);
	glVertex3f(0.14, -0.27, 0.07);
	glTexCoord2f(1, 1);
	glVertex3f(0.06, -0.27, 0.07);
	glTexCoord2f(0, 1);
	glVertex3f(0.06, -0.27, -0.07);

	//bottom
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.155, -0.6, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.155, -0.6, 0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.045, -0.6, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.045, -0.6, 0.08);
	glEnd();
	glPopMatrix();
}

void feetRight(float whiteR, float whiteG, float whiteB, float greyR, float greyG, float greyB, float redR, float redG, float redB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
		greyR = 1.0, greyG = 1.0, greyB = 1.0;
	}

	//heel joint
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.025, -0.63, -0.02);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.03, 0.03, 0.15, 10, 10);
	glPopMatrix();

	//heel joint left
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.175, -0.63, -0.02);
	glRotatef(90, 0, 1, 0);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	//heel joint right
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glColor3f(greyR, greyG, greyB);
	glTranslatef(0.025, -0.63, -0.02);
	glRotatef(90, 0, 1, 0);
	gluDisk(cylinder, 0, 0.03, 10, 1);
	glPopMatrix();

	//heel guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	glColor3f(whiteR, whiteG, whiteB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.6, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.175, -0.67, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.175, -0.67, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.16, -0.57, 0.13);

	////right
	glTexCoord2f(0, 0);
	glVertex3f(0.04, -0.6, -0.05);
	glTexCoord2f(1, 0);
	glVertex3f(0.025, -0.67, -0.05);
	glTexCoord2f(1, 1);
	glVertex3f(0.025, -0.67, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.57, 0.13);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.175, -0.67, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.57, 0.13);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.57, 0.13);
	glTexCoord2f(0, 1);
	glVertex3f(0.025, -0.67, 0.15);
	glEnd();
	glPopMatrix();

	//upper feet
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.16, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.6, -0.06);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.6, -0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.6, -0.06);

	////back
	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.7, -0.12);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.7, -0.12);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.6, -0.1);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.7, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.6, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.6, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.7, -0.08);

	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.6, -0.1);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.6, -0.06);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.6, -0.06);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.6, -0.1);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.16, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(0.16, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.04, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.04, -0.7, -0.12);
	glEnd();
	glPopMatrix();

	//below heel guard
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2) {
		glBindTexture(GL_TEXTURE_2D, greySteel);
	}
	else if (textureMode == 3) {
		glBindTexture(GL_TEXTURE_2D, darkgreen1);
	}
	else if (textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}

	glBegin(GL_QUADS);

	//left
	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.17, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, -0.6, 0.1);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.05, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.03, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.6, 0.1);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, -0.7, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.65, -0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.17, -0.7, 0.15);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.6, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.6, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.7, 0.15);
	glEnd();
	glPopMatrix();

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.15, -0.65, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.15, -0.6, 0.1);
	glTexCoord2f(1, 1);
	glVertex3f(0.05, -0.6, 0.1);
	glTexCoord2f(0, 1);
	glVertex3f(0.05, -0.65, -0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.17, -0.7, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.7, -0.08);

	//bottom feet
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}

	glBegin(GL_QUADS);
	glColor3f(redR, redG, redB);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.18, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.17, -0.7, 0.15);

	////right
	glTexCoord2f(0, 0);
	glVertex3f(0.03, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.7, 0.15);

	////back
	glTexCoord2f(0, 0);
	glVertex3f(0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.73, -0.14);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, -0.73, -0.14);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.7, -0.12);

	////front
	glTexCoord2f(0, 0);
	glVertex3f(0.18, -0.73, 0.17);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, -0.73, 0.17);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.17, -0.7, -0.12);
	glTexCoord2f(1, 0);
	glVertex3f(0.17, -0.7, 0.15);
	glTexCoord2f(1, 1);
	glVertex3f(0.03, -0.7, 0.15);
	glTexCoord2f(0, 1);
	glVertex3f(0.03, -0.7, -0.12);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.18, -0.73, -0.14);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, -0.73, 0.17);
	glTexCoord2f(1, 1);
	glVertex3f(0.02, -0.73, 0.17);
	glTexCoord2f(0, 1);
	glVertex3f(0.02, -0.73, -0.14);
	glEnd();
	glPopMatrix();

	glPopMatrix();
}

void shield(float whiteR, float whiteG, float whiteB, float redR, float redG, float redB, float yellowR, float yellowG, float yellowB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
		redR = 1.0, redG = 1.0, redB = 1.0;
		yellowR = 1.0, yellowG = 1.0, yellowB = 1.0;
	}

	glPushMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, redSteel);
	}	glBegin(GL_QUADS);

	//inner top part
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.11, 0.45, 0.012);
	glTexCoord2f(1, 0);
	glVertex3f(-0.14, 0.2, 0.027);
	glTexCoord2f(1, 1);
	glVertex3f(0.14, 0.2, 0.027);
	glTexCoord2f(0, 1);
	glVertex3f(0.11, 0.45, 0.012);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.105, 0.5, 0.01);
	glTexCoord2f(1, 0);
	glVertex3f(-0.11, 0.45, 0.012);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, 0.45, 0.012);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, 0.5, 0.01);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.105, 0.5, 0.01);
	glTexCoord2f(1, 0);
	glVertex3f(0.11, 0.45, 0.012);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, 0.45, 0.012);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, 0.5, 0.01);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, 0.55, 0.01);
	glTexCoord2f(1, 0);
	glVertex3f(-0.105, 0.5, 0.012);
	glTexCoord2f(1, 1);
	glVertex3f(0.105, 0.5, 0.012);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, 0.55, 0.01);

	//inner top left
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.135, 0.55, -0.003);
	glTexCoord2f(1, 0);
	glVertex3f(-0.18, 0.2, 0.007);
	glTexCoord2f(1, 1);
	glVertex3f(-0.14, 0.2, 0.027);
	glTexCoord2f(0, 1);
	glVertex3f(-0.10, 0.55, 0.007);

	//inner top right
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(0.135, 0.55, -0.003);
	glTexCoord2f(1, 0);
	glVertex3f(0.18, 0.2, 0.007);
	glTexCoord2f(1, 1);
	glVertex3f(0.14, 0.2, 0.027);
	glTexCoord2f(0, 1);
	glVertex3f(0.10, 0.55, 0.007);

	//inner bottom part
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, 0.2, 0.027);
	glTexCoord2f(1, 0);
	glVertex3f(-0.115, -0.4, 0.007);
	glTexCoord2f(1, 1);
	glVertex3f(0.115, -0.4, 0.007);
	glTexCoord2f(0, 1);
	glVertex3f(0.14, 0.2, 0.027);

	//inner bottom left
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.18, 0.2, 0.007);
	glTexCoord2f(1, 0);
	glVertex3f(-0.125, -0.4, 0.004);
	glTexCoord2f(1, 1);
	glVertex3f(-0.115, -0.4, 0.007);
	glTexCoord2f(0, 1);
	glVertex3f(-0.14, 0.2, 0.027);

	//inner bottom right
	glColor3f(redR, redG, redB);
	glTexCoord2f(0, 0);
	glVertex3f(0.18, 0.2, 0.007);
	glTexCoord2f(1, 0);
	glVertex3f(0.125, -0.4, 0.004);
	glTexCoord2f(1, 1);
	glVertex3f(0.115, -0.4, 0.007);
	glTexCoord2f(0, 1);
	glVertex3f(0.14, 0.2, 0.027);
	glEnd();
	glPopMatrix();

	//outer top part
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}	glBegin(GL_QUADS);


	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glVertex3f(-0.125, 0.45, 0.008);
	glTexCoord2f(1, 0);
	glVertex3f(-0.15, 0.2, 0.02);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.2, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.125, 0.45, 0.008);

	//left 
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, 0.5, 0.00);
	glTexCoord2f(1, 0);
	glVertex3f(-0.125, 0.45, 0.008);
	glTexCoord2f(1, 1);
	glVertex3f(-0.08, 0.45, 0.008);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, 0.5, 0.0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.12, 0.5, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(0.125, 0.45, 0.008);
	glTexCoord2f(1, 1);
	glVertex3f(0.08, 0.45, 0.008);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, 0.5, 0.0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.115, 0.57, 0.0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, 0.5, 0.001);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, 0.5, 0.001);
	glTexCoord2f(0, 1);
	glVertex3f(0.115, 0.57, 0.0);

	//outer top left
	glTexCoord2f(0, 0);
	glVertex3f(-0.145, 0.57, -0.01);
	glTexCoord2f(1, 0);
	glVertex3f(-0.19, 0.2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.15, 0.2, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(-0.11, 0.57, 0);

	//outer top right
	glTexCoord2f(0, 0);
	glVertex3f(0.145, 0.57, -0.01);
	glTexCoord2f(1, 0);
	glVertex3f(0.19, 0.2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.15, 0.2, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0.11, 0.57, 0);

	//outer bottom part
	glTexCoord2f(0, 0);
	glVertex3f(-0.15, 0.2, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.125, -0.45, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.125, -0.45, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.2, 0.02);

	//outer bottom left
	glTexCoord2f(0, 0);
	glVertex3f(-0.19, 0.2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.135, -0.45, -0.01);
	glTexCoord2f(1, 1);
	glVertex3f(-0.125, -0.45, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.15, 0.2, 0.02);

	//outer bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0.19, 0.2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.135, -0.45, -0.01);
	glTexCoord2f(1, 1);
	glVertex3f(0.125, -0.45, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.15, 0.2, 0.02);
	glEnd();
	glPopMatrix();

	//star
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, yellowSteel);
	}
	//top left
	glColor3f(yellowR, yellowG, yellowB);
	glColor3f(1, 0.9, 0);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.2, 0.027);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//top right
	glTexCoord2f(0, 0);
	glVertex3f(0, 0.2, 0.027);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//left top
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, 0, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, 0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//left bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.14, 0, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//bottom left
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.41, 0.007);
	glTexCoord2f(1, 0);
	glVertex3f(-0.02, -0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//bottom right
	glTexCoord2f(0, 0);
	glVertex3f(0, -0.41, 0.007);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//left top
	glTexCoord2f(0, 0);
	glVertex3f(0.14, 0, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, 0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);

	//left bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.14, 0, 0.02);
	glTexCoord2f(1, 0);
	glVertex3f(0.02, -0.02, 0.02);
	glTexCoord2f(0, 1);
	glVertex3f(0, 0, 0.05);
	glEnd();
	glPopMatrix();

	//handle left 
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glBegin(GL_QUADS);

	//left
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.06, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.12, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.12, -0.02, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(-0.1, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.1, -0.06, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.02, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.02, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.02, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.02, 0. - 0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.06, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.06, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.06, 0. - 0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.06, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.02, 0);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.02, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.06, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(-0.12, -0.06, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(-0.12, -0.02, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(-0.1, -0.02, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(-0.1, -0.06, -0.08);
	glEnd();
	glPopMatrix();

	//handle right
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glBegin(GL_QUADS);

	//left 
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.06, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.12, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.12, -0.02, 0);

	//right
	glTexCoord2f(0, 0);
	glVertex3f(0.1, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.1, -0.06, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.02, 0);

	//top
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.02, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.02, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.02, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.02, 0. - 0.08);

	//bottom
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.06, 0. - 0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.06, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.06, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.06, 0. - 0.08);

	//front
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.06, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.02, 0);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.02, 0);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.06, 0);

	//back
	glTexCoord2f(0, 0);
	glVertex3f(0.12, -0.06, -0.08);
	glTexCoord2f(1, 0);
	glVertex3f(0.12, -0.02, -0.08);
	glTexCoord2f(1, 1);
	glVertex3f(0.1, -0.02, -0.08);
	glTexCoord2f(0, 1);
	glVertex3f(0.1, -0.06, -0.08);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}
	glLineWidth(5.0f);
	glBegin(GL_LINE_STRIP);

	glColor3f(whiteR, whiteG, whiteB);
	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.08, 0.45, 0.012);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, 0.5, 0.01);

	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(-0.08, 0.5, 0.012);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(0.08, 0.5, 0.012);

	glTexCoord2f(0, 0);
	glTexCoord2f(1, 0);
	glVertex3f(0.08, 0.45, 0.013);
	glTexCoord2f(1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-0.08, 0.45, 0.013);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}	glTranslatef(-0.1, -0.04, -0.08);
	glRotatef(90, 0, 1, 0);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.015, 0.015, 0.2, 10, 10);

	glPopMatrix();
	glPopMatrix();
}

void saber(float whiteR, float whiteG, float whiteB) {
	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (textureMode != 1) {
		whiteR = 1.0, whiteG = 1.0, whiteB = 1.0;
	}


	//handle
	glPushMatrix();
	if (textureMode == 1) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (textureMode == 2 || textureMode == 3 || textureMode == 4) {
		glBindTexture(GL_TEXTURE_2D, whiteSteel);
	}	glColor3f(whiteR, whiteG, whiteB);
	//glTranslatef(-0.27, -0.04, -0.05);
	gluQuadricTexture(cylinder, true);
	gluCylinder(cylinder, 0.015, 0.015, 0.2, 10, 10);
	glPopMatrix();

	//bottom cover
	glPushMatrix();
	glTranslatef(0, 0, 0.2);
	gluDisk(cylinder, 0, 0.015, 10, 1);
	glPopMatrix();

	//top cover
	glPushMatrix();
	glTranslatef(0, 0, 0);
	gluDisk(cylinder, 0, 0.015, 10, 1);
	glPopMatrix();

	//guard
	glPushMatrix();
	glTranslatef(0, 0, 0.17);
	gluCylinder(cylinder, 0.02, 0.02, 0.02, 10, 10);
	glPopMatrix();

	//guard bottom cover
	glPushMatrix();
	glTranslatef(0, 0, 0.19);
	gluDisk(cylinder, 0, 0.02, 10, 1);
	glPopMatrix();

	//guard top cover
	glPushMatrix();
	glTranslatef(0, 0, 0.17);
	gluDisk(cylinder, 0, 0.02, 10, 1);
	glPopMatrix();

}

void saberExtend() {

	if (cylinder == NULL)
		cylinder = gluNewQuadric();

	if (extend == true) {
		if (length <= 0.9)
			length += 0.001;
	}
	else {
		if (length >= 0)
			length -= 0.001;
	}

	glPushMatrix();
	glColor3f(1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPushMatrix();
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, length);
	gluDisk(cylinder, 0, 0.013, 10, 1);
	glPopMatrix();
	gluCylinder(cylinder, 0.013, 0.013, length, 10, 10);


	glPopMatrix();
	glPopMatrix();



}

void handAnimation() {

	glPushMatrix();
	glTranslatef(-0.201, 0.47, 0);
	glRotatef(-leftShoulderAngle, 1, 0, 0);
	glTranslatef(0.201, -0.47, 0);
	armLeft1(0.8710, 0.9330, 0.8710);


	glPushMatrix();
	glTranslatef(-0.235, 0.26, 0);

	glRotatef(-leftElbowAngle, 1, 0, 0);

	glTranslatef(0.235, -0.26, 0);
	armLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960, 0.5530, 0.6820, 0.5450);

	glPushMatrix();
	glTranslatef(-0.285, 0.03, 0);

	glRotatef(-leftWristZ, 0, 0, 1);
	glRotatef(-leftWristY, 0, 1, 0);
	glRotatef(-leftWristX, 1, 0, 0);
	glTranslatef(0.285, -0.03, 0);
	handLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960);
	glPushMatrix();
	if (getSaber == true) {
		glTranslatef(-0.27, -0.02, -0.1);
		//glRotatef(90, 1, 0, 0);
		saberExtend();
	}
	glPopMatrix();
	//glPushMatrix();
	//glTranslatef(-0.27, -0.02, -0.1);
	////glRotatef(90, 1, 0, 0);
	//saberExtend();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.201, 0.47, 0);
	glRotatef(-rightShoulderAngle, 1, 0, 0);
	glTranslatef(-0.201, -0.47, 0);
	armRight1(0.8710, 0.9330, 0.8710);

	glPushMatrix();
	glTranslatef(0.235, 0.26, 0);
	glRotatef(-rightElbowAngle, 1, 0, 0);
	glTranslatef(-0.235, -0.26, 0);
	armRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960, 0.5530, 0.6820, 0.5450);

	glPushMatrix();
	glTranslatef(0.285, 0.03, 0);
	
	glRotatef(-rightWristY, 0, 1, 0);
	glRotatef(-rightWristX, 1, 0, 0);
	glRotatef(-rightWristZ, 0, 0, 1);
	glTranslatef(-0.285, -0.03, 0);
	handRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960);

	glPushMatrix();
	glTranslatef(0.35, 0.015, 0);
	glRotatef(90, 0, 1, 0);
	shield(0.8710, 0.9330, 0.8710, 0.9060, 0.1760, 0.1060, 0.9730, 0.7180, 0);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();






}

void legAnimation() {
	hip(0.8710, 0.9330, 0.8710, 0.9060, 0.1760, 0.1060, 0.9730, 0.7180, 0);

	glPushMatrix();
	glTranslatef(0.1125, 0.2, 0.1);
	glRotatef(-leftHipFront, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, -0.1);
	hipMovingLeftFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, -0.1);
	glRotatef(-leftHipBack, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, 0.1);
	hipMovingLeftBack(0.8710, 0.9330, 0.8710);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.01675, 0.1, 0);
	glRotatef(-leftThigh, 1, 0, 0);
	glTranslatef(0.01675, -0.1, 0);
	legLeft(0.8710, 0.9330, 0.8710);

	glPushMatrix();
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-leftKnee, 1, 0, 0);
	glTranslatef(0.035, 0.24, 0);
	legLeft1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);

	glPushMatrix();
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(leftHeel, 1, 0, 0);
	glTranslatef(0.025, 0.63, 0.02);
	feetLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, 0.1);
	glRotatef(-rightHipFront, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, -0.1);
	hipMovingRightFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, -0.1);
	glRotatef(-rightHipBack, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, 0.1);
	hipMovingRightBack(0.8710, 0.9330, 0.8710);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.01675, 0.1, 0);
	glRotatef(-rightThigh, 1, 0, 0);
	glTranslatef(0.01675, -0.1, 0);
	legRight(0.8710, 0.9330, 0.8710);

	glPushMatrix();
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-rightKnee, 1, 0, 0);
	glTranslatef(0.035, 0.24, 0);
	legRight1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);

	glPushMatrix();
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(rightHeel, 1, 0, 0);
	glTranslatef(0.025, 0.63, 0.02);
	feetRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

}

void jumpingLegAnimation() {


	glPushMatrix();
	glTranslatef(-0.01675, 0.1, 0);
	glRotatef(-leftThigh, 1, 0, 0);
	glTranslatef(0.01675, -0.1, 0);
	legLeft(0.8710, 0.9330, 0.8710);

	glPushMatrix();
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-leftKnee, 1, 0, 0);
	glTranslatef(0.035, 0.24, 0);
	legLeft1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);

	glPushMatrix();
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(leftHeel, 1, 0, 0);
	glTranslatef(0.025, 0.63, 0.02);
	feetLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.01675, 0.1, 0);
	glRotatef(-rightThigh, 1, 0, 0);
	glTranslatef(0.01675, -0.1, 0);
	legRight(0.8710, 0.9330, 0.8710);

	glPushMatrix();
	glTranslatef(-0.035, -0.24, 0);
	glRotatef(-rightKnee, 1, 0, 0);
	glTranslatef(0.035, 0.24, 0);
	legRight1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);

	glPushMatrix();
	glTranslatef(-0.025, -0.63, -0.02);
	glRotatef(rightHeel, 1, 0, 0);
	glTranslatef(0.025, 0.63, 0.02);
	feetRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void headAnimation() {
	glPushMatrix();
	glTranslatef(0, 0.525, 0);
	glRotatef(-headY, 0, 1, 0);
	glRotatef(-headX, 1, 0, 0);
	glTranslatef(0, -0.525, 0);
	head(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9730, 0.7180, 0, 0.9060, 0.1760, 0.1060);
	glPopMatrix();
}

void bodyAnimation() {
	glPushMatrix();

	glPushMatrix();
	legAnimation();
	glPopMatrix();

	glPushMatrix();
	glRotatef(bodyY, 0, 1, 0);
	glTranslatef(0, bodyMoveY, 0);
	body(0.9730, 0.7180, 0, 0.9060, 0.1760, 0.1060, 0, 0.5920, 0.8390, 0.2550, 0.4780, 0.7450);
	handAnimation();
	backpack(0.1920, 0.1920, 0.1960, 0.3410, 0.3530, 0.4120);
	headAnimation();
	glPopMatrix();

	glPopMatrix();
}

void defStance() {

	glPushMatrix();
	glPushMatrix();
	glTranslatef(0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();
	bodyAnimation();
	glPopMatrix();
}

void fightStance() {
	glPushMatrix();
	glTranslatef(0.35, 0.015, 0);
	glRotatef(90, 0, 1, 0);
	shield(0.8710, 0.9330, 0.8710, 0.9060, 0.1760, 0.1060, 0.9730, 0.7180, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.27, -0.02, -0.1);
	//glRotatef(90, 0, 1, 0);
	saberExtend();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();

	legLeft(0.8710, 0.9330, 0.8710);
	legLeft1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);
	feetLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	legRight(0.8710, 0.9330, 0.8710);
	legRight1(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120);
	feetRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9060, 0.1760, 0.1060);
	hip(0.8710, 0.9330, 0.8710, 0.9060, 0.1760, 0.1060, 0.9730, 0.7180, 0);
	hipMovingLeftBack(0.8710, 0.9330, 0.8710);
	hipMovingLeftFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	hipMovingRightBack(0.8710, 0.9330, 0.8710);
	hipMovingRightFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	body(0.9730, 0.7180, 0, 0.9060, 0.1760, 0.1060, 0, 0.5920, 0.8390, 0.2550, 0.4780, 0.7450);
	armLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960, 0.5530, 0.6820, 0.5450);
	armLeft1(0.8710, 0.9330, 0.8710);
	armRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960, 0.5530, 0.6820, 0.5450);
	armRight1(0.8710, 0.9330, 0.8710);
	backpack(0.1920, 0.1920, 0.1960, 0.3410, 0.3530, 0.4120);
	head(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.9730, 0.7180, 0, 0.9060, 0.1760, 0.1060);
	handLeft(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960);
	handRight(0.8710, 0.9330, 0.8710, 0.3410, 0.3530, 0.4120, 0.1920, 0.1920, 0.1960);

}

void drawSaber() {

	glPushMatrix();
	if (getSaber == false) {
		glTranslatef(-0.175, 0.68, -0.16);
		glRotatef(90, 1, 0, 0);
		saber(0.8710, 0.9330, 0.8710);
	}
	glPopMatrix();

	if (drawSaber1 == true) {
		if (getSaber == false) {
			if (leftShoulderAngle <= 170) {
				leftShoulderAngle += 0.1;
			}
			if (leftElbowAngle <= 90) {
				leftElbowAngle += 0.1;
			}
			if (leftWristZ >= -45) {
				leftWristZ -= 0.1;
			}
			if (rightWristY <= 70) {
				rightWristY += 0.1;
			}
			if (rightWristZ <= 20) {
				rightWristZ += 0.1;
			}
			if (rightElbowAngle <= 10) {
				rightElbowAngle += 0.1;
			}
			if (leftShoulderAngle >= 170) {
				getSaber = true;

			}
		}
		else if (getSaber == true) {

			if (leftShoulderAngle >= 0) {
				leftShoulderAngle -= 0.1;

			}
			if (leftElbowAngle >= 0) {
				leftElbowAngle -= 0.1;
			}
			if (leftWristZ <= 0) {
				leftWristZ += 0.1;
			}
			/*if (leftShoulderAngle <= 0) {
				getSaber = false;
			}*/

		}

	}
	if (drawSaber2 == true) {

		if (getSaber == true) {
			if (leftShoulderAngle <= 170) {
				leftShoulderAngle += 0.1;
			}
			if (leftElbowAngle <= 90) {
				leftElbowAngle += 0.1;
			}
			if (leftWristZ >= -45) {
				leftWristZ -= 0.1;
			}
			if (rightWristY >= 0) {
				rightWristY -= 0.1;
			}
			if (rightWristZ >= 0) {
				rightWristZ -= 0.1;
			}
			if (rightElbowAngle >= 0) {
				rightElbowAngle -= 0.1;
			}
			if (leftShoulderAngle >= 169.9) {
				getSaber = false;
				

			}
		}
		if (getSaber == false) {
			if (leftShoulderAngle >= 0) {
				leftShoulderAngle -= 0.1;

			}
			if (leftElbowAngle >= 0) {
				leftElbowAngle -= 0.1;
			}
			if (leftWristZ <= 0) {
				leftWristZ += 0.1;
			}
		}
	}

}

void walking() {
	if (walking1 == true) {
		if (walkingZ <= 1) {
			walkingZ += 0.0001;
		}
		if (walkingZ >= 1) {
			walkingZ = -1;
		}
		if (leftLegFront == false) {
			if (leftThigh >= 0) {
				if (leftHipFront <= 20)
					leftHipFront += 0.01;
			}
			if (leftHipBack <= 0) {
				leftHipBack += 0.01;
			}
			if (leftThigh <= 20) {
				leftThigh += 0.01;
			}
			if (leftKnee <= 0) {
				leftKnee += 0.01;
			}

			if (leftHeel <= 20) {
				leftHeel += 0.02;
			}
			if (leftShoulderAngle >= -20) {
				leftShoulderAngle -= 0.01;
			}
			if (leftElbowAngle >= 0) {
				leftElbowAngle -= 0.01;
			}

			if (leftThigh >= 20) {
				leftLegFront = true;
			}
			if (rightHipFront >= 0) {
				rightHipFront -= 0.01;
			}
			if (rightThigh < 0) {
				if (rightHipBack >= -20)
					rightHipBack -= 0.01;
			}
			if (rightThigh >= -20) {
				rightThigh -= 0.01;
			}
			if (rightKnee >= -30) {
				rightKnee -= 0.01;
			}
			if (rightHeel >= -10) {
				rightHeel -= 0.02;
			}
			if (rightShoulderAngle <= 20) {
				rightShoulderAngle += 0.01;
			}
			if (rightElbowAngle <= 20) {
				rightElbowAngle += 0.01;
			}

		}


		if (leftLegFront == true) {
			if (leftHipFront >= 0) {
				leftHipFront -= 0.01;
			}
			if (leftThigh < 0) {
				if (leftHipBack >= -20)
					leftHipBack -= 0.01;
			}
			if (leftThigh >= -20) {
				leftThigh -= 0.01;
			}
			if (leftKnee >= -30) {
				leftKnee -= 0.01;
			}
			if (leftHeel >= -10) {
				leftHeel -= 0.02;
			}
			if (leftThigh <= -20) {
				leftLegFront = false;
			}
			if (leftShoulderAngle <= 20) {
				leftShoulderAngle += 0.01;
			}
			if (leftElbowAngle <= 20) {
				leftElbowAngle += 0.01;
			}
			if (rightThigh >= 0) {
				if (rightHipFront <= 20)
					rightHipFront += 0.01;
			}
			if (rightHipBack <= 0) {
				rightHipBack += 0.01;
			}
			if (rightThigh <= 20) {
				rightThigh += 0.01;
			}
			if (rightKnee <= 0) {
				rightKnee += 0.01;
			}
			if (rightHeel <= 20) {
				rightHeel += 0.02;
			}
			if (rightShoulderAngle >= -20) {
				rightShoulderAngle -= 0.01;
			}
			if (rightElbowAngle >= 0) {
				rightElbowAngle -= 0.01;
			}

		}
	}
	glPushMatrix();
	
	glTranslatef(0,0,walkingZ);
	glPushMatrix();
	glTranslatef(-0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();
	defStance();
	glPopMatrix();
}

void running() {
	if (running1 == true) {
		if (walkingZ <= 1) {
			walkingZ += 0.001;
		}
		if (walkingZ >= 1) {
			walkingZ = -1;
		}
		if (leftLegFront == false) {
			if (leftThigh >= 0) {
				if (leftHipFront <= 45)
					leftHipFront += 0.1;
			}
			if (leftHipBack <= 0) {
				leftHipBack += 0.1;
			}
			if (leftThigh <= 45) {
				leftThigh += 0.1;
			}
			if (leftKnee <= 0) {
				leftKnee += 0.1;
			}
			if (leftHeel <= 45)
				if (leftHeel <= 45) {
					leftHeel += 0.3;
				}
			if (leftShoulderAngle >= -45) {
				leftShoulderAngle -= 0.1;
			}
			/*if (leftElbowAngle >= 0) {
				leftElbowAngle -= 0.1;
			}*/

			if (leftThigh >= 45) {
				leftLegFront = true;
			}
			if (rightHipFront >= 0) {
				rightHipFront -= 0.1;
			}
			if (rightThigh < 0) {
				if (rightHipBack >= -45)
					rightHipBack -= 0.1;
			}
			if (rightThigh >= -45) {
				rightThigh -= 0.1;
			}
			if (rightKnee >= -60) {
				rightKnee -= 0.1;
			}
			if (rightHeel >= -20) {
				rightHeel -= 0.2;
			}
			if (rightShoulderAngle <= 45) {
				rightShoulderAngle += 0.1;
			}
			if (rightElbowAngle <= 60) {
				rightElbowAngle += 0.1;
			}

		}


		if (leftLegFront == true) {
			if (leftHipFront >= 0) {
				leftHipFront -= 0.1;
			}
			if (leftThigh < 0) {
				if (leftHipBack >= -45)
					leftHipBack -= 0.1;
			}
			if (leftThigh >= -45) {
				leftThigh -= 0.1;
			}
			if (leftKnee >= -60) {
				leftKnee -= 0.1;
			}
			if (leftHeel >= -20) {
				leftHeel -= 0.2;
			}
			if (leftThigh <= -45) {
				leftLegFront = false;
			}
			if (leftShoulderAngle <= 45) {
				leftShoulderAngle += 0.1;
			}
			if (leftElbowAngle <= 60) {
				leftElbowAngle += 0.1;
			}
			if (rightThigh >= 0) {
				if (rightHipFront <= 45)
					rightHipFront += 0.1;
			}
			if (rightHipBack <= 0) {
				rightHipBack += 0.1;
			}
			if (rightThigh <= 45) {
				rightThigh += 0.1;
			}
			if (rightKnee <= 0) {
				rightKnee += 0.1;
			}
			if (rightHeel <= 45) {
				rightHeel += 0.3;
			}
			if (rightShoulderAngle >= -45) {
				rightShoulderAngle -= 0.1;
			}
			/*if (rightElbowAngle >= 0) {
				rightElbowAngle -= 0.1;
			}*/

		}
	}
	glPushMatrix();

	

	glTranslatef(0, 0, walkingZ);
	glPushMatrix();
	glTranslatef(-0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();
	defStance();
	glPopMatrix();
}

void jumping() {
	if (jumping1 == true) {
		if (jumping2 == false) {
			if (hipAngle <= 45) {
				hipAngle += 0.05;
			}
			if (leftThigh <= 45) {
				leftThigh += 0.05;
			}
			if (leftKnee >= -45) {
				leftKnee -= 0.05;
			}
			if (leftThigh >= 0) {
				if (leftHipFront <= 90)
					leftHipFront += 0.1;
			}
			if (leftElbowAngle <= 90) {
				leftElbowAngle += 0.1;
			}
			if (leftShoulderAngle >= -45) {
				leftShoulderAngle -= 0.05;
			}

			if (rightThigh <= 45) {
				rightThigh += 0.05;
			}
			if (rightKnee >= -45) {
				rightKnee -= 0.05;
			}
			if (rightThigh >= 0) {
				if (rightHipFront <= 90)
					rightHipFront += 0.1;
			}
			if (rightElbowAngle <= 90) {
				rightElbowAngle += 0.1;
			}
			if (rightShoulderAngle >= -45) {
				rightShoulderAngle -= 0.05;
			}
			if (hipAngle >= 45) {
				jumping2 = true;
			}
		}
		if (jumping2 == true) {
			if (jumping3 == false) {


				if (hipAngle >= 0) {
					hipAngle -= 0.1;
				}
				if (leftThigh >= 0) {
					leftThigh -= 0.1;
				}
				if (leftKnee <= 0) {
					leftKnee += 0.1;
				}
				if (leftHipFront >= 0) {
					leftHipFront -= 0.1;
				}
				if (leftElbowAngle >= 0) {
					leftElbowAngle -= 0.2;
				}
				if (leftShoulderAngle <= 170) {
					leftShoulderAngle += 0.5;
				}
				if (rightThigh >= 0) {
					rightThigh -= 0.1;
				}
				if (rightKnee <= 0) {
					rightKnee += 0.1;
				}
				if (rightHipFront >= 0) {
					rightHipFront -= 0.1;
				}
				if (rightElbowAngle >= 0) {
					rightElbowAngle -= 0.2;
				}
				if (rightShoulderAngle <= 170) {
					rightShoulderAngle += 0.5;
				}
				if (jumpHeight <= 0.5) {
					jumpHeight += 0.0005;
				}
				if (jumpHeight >= 0.5) {
					jumping3 = true;
				}
			}
			
			if (jumping3 == true) {
				if (jumpHeight >= 0) {
					jumpHeight -= 0.0005;
				}
				if (jumpHeight <= 0) {
					if(jumping4==false){
					if (hipAngle <= 25) {
						hipAngle += 0.05;
					}
					if (leftThigh <= 25) {
						leftThigh += 0.05;
					}
					if (leftKnee >= -25) {
						leftKnee -= 0.05;
					}
					if (leftThigh >= 0) {
						if (leftHipFront <= 45)
							leftHipFront += 0.1;
					}
					if (leftElbowAngle <= 45) {
						leftElbowAngle += 0.1;
					}
					if (leftShoulderAngle >= -25) {
						leftShoulderAngle -= 0.5;
					}

					if (rightThigh <= 25) {
						rightThigh += 0.05;
					}
					if (rightKnee >= -25) {
						rightKnee -= 0.05;
					}
					if (rightThigh >= 0) {
						if (rightHipFront <= 45)
							rightHipFront += 0.1;
					}
					if (rightElbowAngle <= 45) {
						rightElbowAngle += 0.1;
					}
					if (rightShoulderAngle >= -25) {
						rightShoulderAngle -= 0.5;
					}
					if (rightShoulderAngle <= -25) {
						jumping4 = true;
					}
				}
					if (jumping4 == true) {
						if (hipAngle >= 0) {
							hipAngle -= 0.01;
						}
						if (leftThigh >= 0) {
							leftThigh -= 0.01;
						}
						if (leftKnee <= 0) {
							leftKnee += 0.01;
						}
						if (leftHipFront >= 0) {
							leftHipFront -= 0.01;
						}
						if (leftElbowAngle >= 0) {
							leftElbowAngle -= 0.02;
						}
						if (leftShoulderAngle <= 0) {
							leftShoulderAngle += 0.05;
						}
						if (rightThigh >= 0) {
							rightThigh -= 0.01;
						}
						if (rightKnee <= 0) {
							rightKnee += 0.01;
						}
						if (rightHipFront >= 0) {
							rightHipFront -= 0.01;
						}
						if (rightElbowAngle >= 0) {
							rightElbowAngle -= 0.02;
						}
						if (rightShoulderAngle <= 0) {
							rightShoulderAngle += 0.05;
						}
					}
				}
			}

		}
		
	}

	glPushMatrix();
	glPushMatrix();
	glTranslatef(0, jumpHeight, 0);
	jumpingLegAnimation();
	glPushMatrix();
	glTranslatef(0, jumpHeight, 0);
	glRotatef(hipAngle, 1, 0, 0);
	glPushMatrix();
	glTranslatef(-0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.175, 0.68, -0.16);
	glRotatef(90, 1, 0, 0);
	saber(0.8710, 0.9330, 0.8710);
	glPopMatrix();
	backpack(0.1920, 0.1920, 0.1960, 0.3410, 0.3530, 0.4120);
	body(0.9730, 0.7180, 0, 0.9060, 0.1760, 0.1060, 0, 0.5920, 0.8390, 0.2550, 0.4780, 0.7450);
	hip(0.8710, 0.9330, 0.8710, 0.9060, 0.1760, 0.1060, 0.9730, 0.7180, 0);
	handAnimation();
	headAnimation();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, 0.1);
	glRotatef(-leftHipFront, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, -0.1);
	hipMovingLeftFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, -0.1);
	glRotatef(-leftHipBack, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, 0.1);
	hipMovingLeftBack(0.8710, 0.9330, 0.8710);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, 0.1);
	glRotatef(-rightHipFront, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, -0.1);
	hipMovingRightFront(0.8710, 0.9330, 0.8710, 0.9730, 0.7180, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.1125, 0.2, -0.1);
	glRotatef(-rightHipBack, 1, 0, 0);
	glTranslatef(-0.1125, -0.2, 0.1);
	hipMovingRightBack(0.8710, 0.9330, 0.8710);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void attacking() {
	if (attack == true) {
		

		
			if (getSaber == false) {
				if (leftShoulderAngle <= 170) {
					leftShoulderAngle += 0.1;
				}
				if (leftElbowAngle <= 90) {
					leftElbowAngle += 0.1;
				}
				if (leftWristZ >= -45) {
					leftWristZ -= 0.1;
				}
				if (rightWristY <= 70) {
					rightWristY += 0.1;
				}
				if (rightWristZ <= 20) {
					rightWristZ += 0.1;
				}
				if (rightElbowAngle <= 10) {
					rightElbowAngle += 0.1;
				}
				if (leftShoulderAngle >= 170) {
					getSaber = true;

				}
			}
			else if (getSaber == true) {

				if (attack1 == false) {
					if (leftShoulderAngle <= 90) {
						leftShoulderAngle += 0.1;
					}
					if (leftElbowAngle <= 45) {
						leftElbowAngle += 0.1;
					}
					if (leftShoulderAngle >= 90) {
						attack1 = true;
					}
				}
				else if (attack1 == true) {
					if (leftShoulderAngle >= 45) {
						leftShoulderAngle -= 0.1;
					}
					if (leftElbowAngle >= 0) {
						leftElbowAngle -= 0.1;
					}

					if (leftShoulderAngle <= 45) {
						attack1 = false;
					}
				}

			}

	
		if (rightShoulderAngle <= 50) {
			rightShoulderAngle += 0.1;
		}
		if (rightElbowAngle <= 45) {
			rightElbowAngle += 0.1;
		}
		if (rightWristY <= 90) {
			rightWristY += 0.2;
		}
		if (rightWristZ <= 90) {
			rightWristZ += 0.2;
		}

		if(walkingZ <= 1) {
			walkingZ += 0.001;
		}
		if (walkingZ >= 1) {
			walkingZ = -1;
		}
		if (leftLegFront == false) {
			if (leftThigh >= 0) {
				if (leftHipFront <= 45)
					leftHipFront += 0.1;
			}
			if (leftHipBack <= 0) {
				leftHipBack += 0.1;
			}
			if (leftThigh <= 45) {
				leftThigh += 0.1;
			}
			if (leftKnee <= 0) {
				leftKnee += 0.1;
			}
			if (leftHeel <= 45)
				if (leftHeel <= 45) {
					leftHeel += 0.3;
				}

			if (leftThigh >= 45) {
				leftLegFront = true;
			}
			if (rightHipFront >= 0) {
				rightHipFront -= 0.1;
			}
			if (rightThigh < 0) {
				if (rightHipBack >= -45)
					rightHipBack -= 0.1;
			}
			if (rightThigh >= -45) {
				rightThigh -= 0.1;
			}
			if (rightKnee >= -60) {
				rightKnee -= 0.1;
			}
			if (rightHeel >= -20) {
				rightHeel -= 0.2;
			}


		}


		if (leftLegFront == true) {
			if (leftHipFront >= 0) {
				leftHipFront -= 0.1;
			}
			if (leftThigh < 0) {
				if (leftHipBack >= -45)
					leftHipBack -= 0.1;
			}
			if (leftThigh >= -45) {
				leftThigh -= 0.1;
			}
			if (leftKnee >= -60) {
				leftKnee -= 0.1;
			}
			if (leftHeel >= -20) {
				leftHeel -= 0.2;
			}
			if (leftThigh <= -45) {
				leftLegFront = false;
			}
			//if (leftShoulderAngle <= 45) {
			//	leftShoulderAngle += 0.1;
			//}
			//if (leftElbowAngle <= 60) {
			//	leftElbowAngle += 0.1;
			//}
			if (rightThigh >= 0) {
				if (rightHipFront <= 45)
					rightHipFront += 0.1;
			}
			if (rightHipBack <= 0) {
				rightHipBack += 0.1;
			}
			if (rightThigh <= 45) {
				rightThigh += 0.1;
			}
			if (rightKnee <= 0) {
				rightKnee += 0.1;
			}
			if (rightHeel <= 45) {
				rightHeel += 0.3;
			}
			//if (rightShoulderAngle >= -45) {
			//	rightShoulderAngle -= 0.1;
			//}
			/*if (rightElbowAngle >= 0) {
				rightElbowAngle -= 0.1;
			}*/

		}
		
		
		glPushMatrix();
		glTranslatef(0, 0, walkingZ);
		defStance();
		
		if (getSaber == false) {
			glTranslatef(-0.175, 0.68, -0.16);
			glRotatef(90, 1, 0, 0);
			saber(0.8710, 0.9330, 0.8710);
		}
		glPopMatrix();
		
	}
	


}

void display()
{
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.1216, 0.2588, 0.4667, 1);
	glLoadIdentity();
	lightingSetup();
	projectionSetup();


	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	skybox();

	glPushMatrix();
	glRotatef(rotateRobotY, 0, 1, 0);
	glRotatef(rotateRobotX, 1, 0, 0);

	// Add the Robot Here

	if (aniMode == true) {
		if (running1 == true) {
			running();
		}
		else if (walking1 == true) {
			walking();
		}
		else if (jumping1 == true) {
			jumping();
		}
		else if (attack == true) {
			attacking();
		}
		else {
			glPushMatrix();
			glTranslatef(-0.175, 0.68, -0.16);
			glRotatef(90, 1, 0, 0);
			saber(0.8710, 0.9330, 0.8710);
			glPopMatrix();
			defStance();
		}

		
	}
	else {
		defStance();
		drawSaber();
	}

	glPopMatrix();

	glPopMatrix();
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
}

//--------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);
	glEnable(GL_DEPTH_TEST);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"metalic-white.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &whiteSteel);
	glBindTexture(GL_TEXTURE_2D, whiteSteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"red-steel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &redSteel);
	glBindTexture(GL_TEXTURE_2D, redSteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"metalic-grey.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &greySteel);
	glBindTexture(GL_TEXTURE_2D, greySteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"darkgray-steel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &darkgraySteel);
	glBindTexture(GL_TEXTURE_2D, darkgraySteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"metalic-blue.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &blueSteel);
	glBindTexture(GL_TEXTURE_2D, blueSteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"metalic-yellow.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &yellowSteel);
	glBindTexture(GL_TEXTURE_2D, yellowSteel);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// Mode 2
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"green-steel.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &darkgreen1);
	glBindTexture(GL_TEXTURE_2D, darkgreen1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"copper.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &copper);
	glBindTexture(GL_TEXTURE_2D, copper);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// Mode 3
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"black.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &matteBlack);
	glBindTexture(GL_TEXTURE_2D, matteBlack);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	// World Mode
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"sky.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &sky);
	glBindTexture(GL_TEXTURE_2D, sky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"starry-night.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &night);
	glBindTexture(GL_TEXTURE_2D, night);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL),
		"gundam-space.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION |
		LR_LOADFROMFILE);

	GetObject(hBMP, sizeof(BMP), &BMP);

	glGenTextures(1, &space);
	glBindTexture(GL_TEXTURE_2D, space);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------