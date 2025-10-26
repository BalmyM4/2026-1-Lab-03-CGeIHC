#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLboolean getadelante() { return adelante; }


	GLfloat getarticulacion1() { return articulacion1; }

	GLboolean getPrendida() { return luzPrendida; }
	GLboolean getPrendida2() { return luzPrendida2; }

	GLfloat getLucesPuntuales() { return lucesPuntuales; }
	GLfloat getLucesSpotLight() { return lucesSpot; }

	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;

	GLfloat muevex;
	GLboolean adelante;

	GLfloat articulacion1;
	GLfloat dir1;

	GLboolean luzPrendida;
	GLboolean luzPrendida2;
	GLfloat lucesPuntuales;
	GLfloat lucesSpot;

	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

