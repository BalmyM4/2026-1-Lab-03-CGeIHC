#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	dir1 = 1.0f;
	dir3 = 1.0f;
	dir = 1.0f;
	dir2 = 1.0f;
	dir4 = 1.0f;
	dir5 = -1.0f;
	dir6 = 1.0f;
	dir7 = -1.0;
	dir8 = 1.0f;
	dir9 = -1.0;
	dir10 = 1.0f;
	dir11 = -1.0;
	dir12 = 1.0f;
	dir13 = -1.0;

	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;
	articulacion5 = 0.0f;
	articulacion6 = 0.0f;
	articulacion7 = 0.0f;
	articulacion8 = 0.0f;
	articulacion9 = 0.0f;
	articulacion10 = 0.0f;
	articulacion11 = 0.0f;
	articulacion12 = 0.0f;
	articulacion13 = 0.0f;
	articulacion14 = 0.0f;

	articulacion15 = 0.0f;
	articulacion16 = 0.0f;
	articulacion17 = 0.0f;
	articulacion18 = 0.0f;

	articulacion19 = 0.0f;
	articulacion20 = 0.0f;
	articulacion21 = 0.0f;
	articulacion22 = 0.0f;
	
	
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la práctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_F or key == GLFW_KEY_V)
	{
		theWindow->articulacion1 += 2.5 * theWindow->dir1;

		if (theWindow->articulacion1 == 45)
			theWindow->dir1 *= -1.0f;
		else if (theWindow->articulacion1 == -45)
			theWindow->dir1 *= -1.0f;
	}

	if (key == GLFW_KEY_G)
	{
		theWindow->articulacion2 += 5.0 * theWindow->dir3;

		if (theWindow->articulacion2 == 35)
			theWindow->dir3 *= -1.0f;
		else if (theWindow->articulacion2 == -35)
			theWindow->dir3 *= -1.0f;
	}
	if (key == GLFW_KEY_Y or key == GLFW_KEY_V)
	{
		theWindow->articulacion3 += 2.5 * theWindow->dir4;

		if (theWindow->articulacion3 == 30)
			theWindow->dir4 *= -1.0f;
		else if (theWindow->articulacion3 == -40)
			theWindow->dir4 *= -1.0f;
	}
	if (key == GLFW_KEY_U or key == GLFW_KEY_V)
	{
		theWindow->articulacion4 += 2.5 * theWindow->dir5;

		if (theWindow->articulacion4 == 30)
			theWindow->dir5 *= -1.0f;
		else if (theWindow->articulacion4 == -40)
			theWindow->dir5 *= -1.0f;
	}
	if (key == GLFW_KEY_H or key == GLFW_KEY_V)
	{
		theWindow->articulacion5 += 2.5 * theWindow->dir6;

		if (theWindow->articulacion5 == 30)
			theWindow->dir6 *= -1.0f;
		else if (theWindow->articulacion5 == -40)
			theWindow->dir6 *= -1.0f;

	}
	if (key == GLFW_KEY_J or key == GLFW_KEY_V)
	{
		theWindow->articulacion6 += 2.5 * theWindow->dir7;

		if (theWindow->articulacion6 == 30)
			theWindow->dir7 *= -1.0f;
		else if (theWindow->articulacion6 == -40)
			theWindow->dir7 *= -1.0f;
	}
	if (key == GLFW_KEY_B or key == GLFW_KEY_V)
	{
		theWindow->articulacion12 += 2.5 * theWindow->dir8;

		if (theWindow->articulacion12 == 30)
			theWindow->dir8 *= -1.0f;
		else if (theWindow->articulacion12 == -40)
			theWindow->dir8 *= -1.0f;

	}
	if (key == GLFW_KEY_N or key == GLFW_KEY_V)
	{
		theWindow->articulacion13 += 2.5 * theWindow->dir9;

		if (theWindow->articulacion13 == 30)
			theWindow->dir9 *= -1.0f;
		else if (theWindow->articulacion13 == -40)
			theWindow->dir9 *= -1.0f;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->articulacion7 += 2.5 * theWindow->dir;
		theWindow->articulacion8 += 2.5 * theWindow->dir2;

		if (theWindow->articulacion7 == 35)
			theWindow->dir *= -1.0f;
		else if (theWindow->articulacion7 == -15)
			theWindow->dir *= -1.0f;

		if (theWindow->articulacion8 == 25)
			theWindow->dir2 *= -1.0f;
		else if (theWindow->articulacion8 == -25)
			theWindow->dir2 *= -1.0f;
	}
	if (key == GLFW_KEY_P or key == GLFW_KEY_V)
	{
		theWindow->articulacion8 += 2.5f * theWindow->dir2;

		if (theWindow->articulacion8 == 25)
			theWindow->dir2 *= -1.0f;
		else if (theWindow->articulacion8 == -25)
			theWindow->dir2 *= -1.0f;
	}
	if (key == GLFW_KEY_K or key == GLFW_KEY_V)
	{
		theWindow->articulacion9 += 5.0f * theWindow->dir10;

		if (theWindow->articulacion9 == 90)
			theWindow->dir10 *= -1.0f;
		else if (theWindow->articulacion9 == -25)
			theWindow->dir10 *= -1.0f;

	}
	if (key == GLFW_KEY_L or key == GLFW_KEY_V)
	{
		theWindow->articulacion10 += 5.0f * theWindow->dir11;

		if (theWindow->articulacion10 == 90)
			theWindow->dir11 *= -1.0f;
		else if (theWindow->articulacion10 == -25)
			theWindow->dir11 *= -1.0f;
	}
	if (key == GLFW_KEY_M or key == GLFW_KEY_V)
	{
		theWindow->articulacion11 += 2.5f * theWindow->dir12;
		
		if (theWindow->articulacion11 == 35)
			theWindow->dir12 *= -1.0f;
		else if (theWindow->articulacion11 == -35)
			theWindow->dir12 *= -1.0f;
	}
	if (key == 44 or key == GLFW_KEY_V)
	{
		theWindow->articulacion14 += 2.5f * theWindow->dir13;

		if (theWindow->articulacion14 == 35)
			theWindow->dir13 *= -1.0f;
		else if (theWindow->articulacion14 == -35)
			theWindow->dir13 *= -1.0f;
	}


	if (key == GLFW_KEY_Q)
	{
		theWindow->articulacion15 += 10.0;
	}

	if (key == GLFW_KEY_E)
	{
		theWindow->articulacion16 += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->articulacion17 += 10.0;
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->articulacion18 += 10.0;
	}

	if (key == GLFW_KEY_Z)
	{
		theWindow->articulacion19 += 10.0;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->articulacion20 += 10.0;
	}
	if (key == GLFW_KEY_C)
	{
		theWindow->articulacion21 += 10.0;
	}
	if (key == GLFW_KEY_V)
	{
		theWindow->articulacion22 += 10.0;
	}



	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
