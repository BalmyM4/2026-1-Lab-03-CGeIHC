//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>		
#include <string.h>
#include<cmath>			// funciones matemáticas como cos, sin, etc.
#include<vector>		// para vectores dinámicos
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>		// Para usar las matrices
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>		// Para variables uniform
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

// Vertex Shader ======================================================================

// Para las formas
static const char* vShaderRed = "shaders/shaderRed.vert";
static const char* fShaderRed = "shaders/shaderRed.frag";

static const char* vShaderGreen = "shaders/shaderGreen.vert";
static const char* fShaderGreen = "shaders/shaderGreen.frag";

static const char* vShaderBlue = "shaders/shaderBlue.vert";
static const char* fShaderBlue = "shaders/shaderBlue.frag";

static const char* vShaderBrown = "shaders/shaderBrown.vert";
static const char* fShaderBrown = "shaders/shaderBrown.frag";

static const char* vShaderDarkGreen = "shaders/shaderDarkGreen.vert";
static const char* fShaderDarkGreen = "shaders/shaderDarkGreen.frag";

// Para las figuras
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";



float angulo = 0.0f;

//color café en RGB : 0.478f, 0.255f, 0.067f

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0, 2, 3,
		1, 2, 3,
		0, 2, 4,
		0, 3, 4,
		1, 2, 4,
		1, 3, 4,
		
	};
	GLfloat vertices[] = {
		-0.5f,	0.0f,	-0.5f,	// 0
		0.5f,	0.0f,	0.5f,	// 1
		0.5f,	0.0f,	-0.5f,	// 2
		-0.5f,	0.0f,	0.5f,	// 3
		0.0f,	1.0f,	0.0f,	// 4

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 16, 24);
	meshList.push_back(obj1);
}


//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}


void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {	
			//X			Y			Z			R		G		B

			//  Para G

			-0.4f, 0.4f, 0.0f,   			1.0f,	1.0f,	0.0f,
			-0.4f, 0.2f, 0.0f,   			1.0f,	1.0f,	0.0f,
			-0.8f, 0.2f, 0.0f,   			1.0f,	1.0f,	0.0f,
											
			-0.4f, 0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,
			-1.0f, 0.1f, 0.0f,  			1.0f,	1.0f,	0.0f,
			-1.0f, 0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,
											
			-0.8f, 0.2f, 0.0f,   			1.0f,	1.0f,	0.0f,
			-1.0f, 0.1f, 0.0f,   			1.0f,	1.0f,	0.0f,
			-0.8f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,
											
			-1.0f, 0.1f, 0.0f,   			1.0f,	1.0f,	0.0f,
			-0.8f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,
			-1.0f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,
											
			-0.8f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// F
			-1.0f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// G
			-1.0f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// H
											
			-0.8f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// F
			-1.0f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// H
			-0.8f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// I
											
			-0.8f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// I
			-0.8f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// J
			-0.4f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// L
											
			-0.8f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// I
			-0.4f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// L
			-0.4f, -0.6f, 0.0f,  			1.0f,	1.0f,	0.0f,// K
											
			-0.4f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// L
			-0.6f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// M
			-0.6f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// P
											
			-0.4f, -0.4f, 0.0f,  			1.0f,	1.0f,	0.0f,// L
			-0.6f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// M
			-0.4f, -0.0f, 0.0f,  			1.0f,	1.0f,	0.0f,// O
											
			-0.6f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// M
			-0.4f, -0.0f, 0.0f,  			1.0f,	1.0f,	0.0f,// O
			-0.8f, -0.2f, 0.0f,  			1.0f,	1.0f,	0.0f,// F


			//  Para B

			0.22f, 0.4f, 0.0f,   			0.0f,	1.0f,	1.0f,// A
			0.3f,  0.32f, 0.0f,  			0.0f,	1.0f,	1.0f,// B
			0.1f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// C
															
			0.3f,  0.32f, 0.0f,  			0.0f,	1.0f,	1.0f,// B
			0.1f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// C
			0.3f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// D
															
			0.22f, 0.4f, 0.0f,   			0.0f,	1.0f,	1.0f,// A
			0.1f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// C
			-0.3f, 0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// E
															
			0.22f, 0.4f, 0.0f,   			0.0f,	1.0f,	1.0f,// A
			-0.3f, 0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// E
			-0.3f, 0.4f,  0.0f,  			0.0f,	1.0f,	1.0f,// F
															
			-0.3f, 0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// E
			-0.1f, 0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// G
			-0.3f, -0.1f, 0.0f,  			0.0f,	1.0f,	1.0f,// H
															
			-0.3f, -0.1f, 0.0f,  			0.0f,	1.0f,	1.0f,// H
			-0.1f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// I
			-0.3f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// J
															
			-0.3f, -0.1f, 0.0f,  			0.0f,	1.0f,	1.0f,// H
			-0.1f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// I
			-0.18f, 0.08f, 0.0f, 			0.0f,	1.0f,	1.0f,// K
															
			-0.1f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// I
			-0.18f, 0.08f, 0.0f, 			0.0f,	1.0f,	1.0f,// K
			-0.1f,  0.2f,  0.0f, 			0.0f,	1.0f,	1.0f,// G
															
			0.22f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// L
			0.3f,  -0.52f, 0.0f, 			0.0f,	1.0f,	1.0f,// M
			-0.1f, -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// N
															
			-0.1f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// I
			0.22f, -0.6f, 0.0f,  			0.0f,	1.0f,	1.0f,// L
			-0.1f, -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// N
															
			0.3f,  -0.52f, 0.0f, 			0.0f,	1.0f,	1.0f,// M
			-0.1f, -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// N
			0.3f,  -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// O
															
			0.3f,  -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// O
			0.3f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// P
			0.1f,  -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// Q
															
			0.3f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// P
			0.1f,  -0.4f, 0.0f,  			0.0f,	1.0f,	1.0f,// Q
			0.1f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// R
															
			0.1f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// C
			0.3f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// D
			0.3f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// S
															
			0.3f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// S
			0.1f,  0.2f,  0.0f,  			0.0f,	1.0f,	1.0f,// C
			0.1f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// T
															
			0.3f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// P
			0.1f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// R
			0.24f, -0.09f, 0.0f, 			0.0f,	1.0f,	1.0f,// U
															
			0.3f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// S
			0.1f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// T
			0.24f, -0.09f, 0.0f, 			0.0f,	1.0f,	1.0f,// U
															
			0.1f,  -0.16f, 0.0f, 			0.0f,	1.0f,	1.0f,// R
			0.24f, -0.09f, 0.0f, 			0.0f,	1.0f,	1.0f,// U
			0.1f,  -0.04f, 0.0f, 			0.0f,	1.0f,	1.0f,// T
															
			-0.1f, -0.2f, 0.0f,  			0.0f,	1.0f,	1.0f,// V
			0.1f,  -0.2f, 0.0f,  			0.0f,	1.0f,	1.0f,// W
			0.1f,   0.0f, 0.0f,  			0.0f,	1.0f,	1.0f,// Z



			// Para F

			1.0f, 0.35f, 0.0f,   			1.0f,	0.0f,	1.0f,// A
			0.95f, 0.4f, 0.0f,   			1.0f,	0.0f,	1.0f,// B
			0.4f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// C
											
			1.0f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// D
			1.0f, 0.35f, 0.0f,   			1.0f,	0.0f,	1.0f,// A
			0.4f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// C
											
			0.4f, 0.4f, 0.0f,    			1.0f,	0.0f,	1.0f,// E
			0.95f, 0.4f, 0.0f,   			1.0f,	0.0f,	1.0f,// B
			0.4f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// C
											
			0.4f, -0.55f, 0.0f,  			1.0f,	0.0f,	1.0f,// F
			0.5f, -0.6f, 0.0f,   			1.0f,	0.0f,	1.0f,// G
			0.4f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// C
											
			0.6f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// H
			0.5f, -0.6f, 0.0f,   			1.0f,	0.0f,	1.0f,// G
			0.4f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// C
											
			0.6f, -0.6f, 0.0f,   			1.0f,	0.0f,	1.0f,// I
			0.6f, 0.2f, 0.0f,    			1.0f,	0.0f,	1.0f,// H
			0.5f, -0.6f, 0.0f,   			1.0f,	0.0f,	1.0f,// G
											
			0.6f, 0.0f, 0.0f,    			1.0f,	0.0f,	1.0f,// J
			0.8f, -0.1f, 0.0f,   			1.0f,	0.0f,	1.0f,// K
			0.6f, -0.2f, 0.0f,   			1.0f,	0.0f,	1.0f,// L
											
			0.75f, 0.0f, 0.0f,   			1.0f,	0.0f,	1.0f,// M
			0.6f, 0.0f, 0.0f,    			1.0f,	0.0f,	1.0f,// J
			0.8f, -0.1f, 0.0f,   			1.0f,	0.0f,	1.0f,// K
											
			0.75f, -0.2f, 0.0f,  			1.0f,	0.0f,	1.0f,// N
			0.8f, -0.1f, 0.0f,   			1.0f,	0.0f,	1.0f,// K
			0.6f, -0.2f, 0.0f,   			1.0f,	0.0f,	1.0f,// L
			
	};
	MeshColor *letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,710);
	meshColorList.push_back(letras);
}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShaderRed, fShaderRed);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader3->CreateFromFiles(vShaderGreen, fShaderGreen);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader4->CreateFromFiles(vShaderBlue, fShaderBlue);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader5->CreateFromFiles(vShaderBrown, fShaderBrown);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader6->CreateFromFiles(vShaderDarkGreen, fShaderDarkGreen);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;

	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		/*										*
		*										*
		*			PARA LAS LETRAS				*
		*										*
		*										*/


		/*
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		// Para las letras
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		//
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();*/


		/*										*
		*										*
		*			PARA LAS CASA				*
		*										*
		*										*/


		//angulo += 0.01;

		// Cubo Rojo
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		// Cubo Verde derecha
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.2f, 0.2f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		// Cubo Verde izqierda
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.2f, 0.2f, -2.6f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		// Cubo Verde abajo
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.3385f, -2.7f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		// Piramide Azul
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		// Cubo Cafe izquierda
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, -0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// Piramide Verde obscuro izquierda
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.5f, -0.4f, -2.95f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		// Cubo Cafe Derecha
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.5f, -0.5f, -3.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		// Piramide Verde obscuro Derecho
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.5f, -0.4f, -2.95f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/