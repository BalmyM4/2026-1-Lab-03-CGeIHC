/*
Animación:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada)
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <random>
#include <ctime>

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza=true;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;

// Puerta
float bajadaPuerta = 0.0f;
float rotacionPuerta = 0.0f;

// Cartel
float toffsetcartelu = 0.0f;
float toffsetcartelv = 0.0f;
float tiempoAcumulado = 0.0f;

// Dado
float x_rot_dado = 0.0f;
float y_rot_dado = 0.0f;
float z_rot_dado = 0.0f;

float x_tras_dado = 0.0f;
float y_tras_dado = 10.0f;
float z_tras_dado = 0.0f;

float tiempoInicio = 0.0f;
bool dadoCaida = true;
bool dadoGiro = false;
bool dadoNumero = false;
bool resetDado = false;

int numeroDado = 0;
float tiempoNumero = 0.0f;

bool x_dado = false;
bool y_dado = false;
bool z_dado = false;


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;
Texture hk_font_Proyecto_GCEIHC;
Texture dado8Texture;


Model Puerta_reja_arco;
Model Puerta_reja_derecha;
Model Puerta_reja_central;
Model Puerta_reja_piso;
Model Puerta_reja_puerta_izquierda;
Model Puerta_reja_puerta_derecha;

Skybox skybox;


//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};
	

	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};
	
	GLfloat verticesCartel[] = {
		//	x      y      z			u		v			nx	  ny    nz
			-2.5f, -1.0f, 0.0f,		0.0f,	0.875f,		0.0f, 0.0f, -1.0f,
			2.5f,  -1.0f, 0.0f,		0.22f,  0.875f,		0.0f, 0.0f, -1.0f,
			2.5f,  1.0f,  0.0f,		0.22f,	1.0f,		0.0f, 0.0f, -1.0f,
			-2.5f, 1.0f,  0.0f,		0.0f,	1.0f,		0.0f, 0.0f, -1.0f
	};

	unsigned int cartelIndices[] = {
		0, 1, 2,
		0, 3, 2,
	};

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6); // todos los números

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7); // solo un número
	
	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(verticesCartel, cartelIndices, 32, 6);
	meshList.push_back(obj8);

}

void CrearDado8()
{
	unsigned int oct_indices[] = {
		// Up +x+z
		0, 1, 2,

		// Up +x-z
		3, 4, 5,

		// Up -x+z
		6, 7, 8,

		// Up -x-z
		9, 10, 11,

		// Bot +x+z
		12, 13, 14,

		// Bot +x-z
		15, 16, 17,

		// Bot -x+z
		18, 19, 20,

		// Bot -x-z
		21, 22, 23,

	};

	GLfloat oct_vertices[] = {

		// Up +x+z	1
		//x		y		z		S		T			NX		NY		NZ
		0.5f, 0.0f,  0.0f,		0.286f,	0.3f,		0.0f,	0.0f,	-1.0f,	//0
		0.0f, 0.0f,  0.5f,		0.0f,	0.3f,		0.0f,	0.0f,   -1.0f,	//1
		0.0f, 0.5f,  0.0f,		0.143f,	0.548f,		0.0f,	0.0f,	-1.0f,	//2

		// Up +x-z	2
		//x		y		z		S		T
		0.5f, 0.0f,  0.0f,	    0.428f, 0.548f,		-1.0f,	0.0f,	0.0f,  //3
		0.0f, 0.0f,  -0.5f,		0.143f,	0.548f,		-1.0f,	0.0f,	0.0f,
		0.0f,  0.5f,  0.0f,		0.286f,	0.3f,		-1.0f,	0.0f,	0.0f,


		// Up -x+z	4
		-0.5f, 0.0f,  0.0f,		0.286f, 0.3f,		0.0f,	0.0f,	-1.0f,
		0.0f, 0.0f,  0.5f,		0.572f,	0.3f,		0.0f,	0.0f,	-1.0f,
		0.0f, 0.5f,  0.0f,		0.428f,	0.548f,		0.0f,	0.0f,	-1.0f,


		// Up -x-z	3
		//x		y		z		S		T
		-0.5f, 0.0f,  0.0f,		0.428f, 0.548f,		1.0f,	0.0f,	0.0f,
		0.0f, 0.0f,  -0.5f,		0.143f,	0.548f,		1.0f,	0.0f,	0.0f,
		0.0f,  0.5f,  0.0f,		0.286f,	0.796f,		1.0f,	0.0f,	0.0f,


		// Bot +x+z	5
		//x		y		z		S		T			NX		NY		NZ
		0.5f, 0.0f,  0.0f,		0.714f, 0.548f,		0.0f,	0.0f,	-1.0f,	//0
		0.0f, 0.0f,  0.5f,		0.428f,	0.548f,		0.0f,	0.0f,	-1.0f,	//1
		0.0f, -0.5f,  0.0f,		0.572f,	0.3f,		0.0f,	0.0f,	-1.0f,	//2

		// Bot +x-z	6
		//x		y		z		S		T
		0.5f, 0.0f,  0.0f,	    0.858f, 0.3f,		-1.0f,	0.0f,	0.0f,
		0.0f, 0.0f,  -0.5f,		0.572f,	0.3f,		-1.0f,	0.0f,	0.0f,
		0.0f,  -0.5f,  0.0f,	0.714f,	0.548f,		-1.0f,	0.0f,	0.0f,


		// Bot -x+z	7
		-0.5f, 0.0f,  0.0f,		0.714f, 0.548f,		0.0f,	0.0f,	-1.0f,
		0.0f, 0.0f,  0.5f,		1.0f,	0.548f,		0.0f,	0.0f,	-1.0f,
		0.0f, -0.5f,  0.0f,		0.858f,	0.3f,		0.0f,	0.0f,	-1.0f,


		// Bot -x-z	8
		//x		y		z		S		T
		-0.5f, 0.0f,  0.0f,		1.0f,   0.548f,		1.0f,	0.0f,	0.0f,
		0.0f, 0.0f,  -0.5f,		0.714f,	0.548f,		1.0f,	0.0f,	0.0f,
		0.0f,  -0.5f,  0.0f,	0.858f,	0.796f,		1.0f,	0.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(oct_vertices, oct_indices, 300, 50);
	meshList.push_back(dado);

}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}




int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado8();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();

	hk_font_Proyecto_GCEIHC = Texture("Textures/hk_font_Proyecto_GCEIHC.png");
	hk_font_Proyecto_GCEIHC.LoadTextureA();
	dado8Texture = Texture("Textures/dado_8.png");
	dado8Texture.LoadTextureA();

	Puerta_reja_arco = Model();
	Puerta_reja_arco.LoadModel("Models/Puerta_reja_arco.obj");
	Puerta_reja_derecha = Model();
	Puerta_reja_derecha.LoadModel("Models/Puerta_reja_derecha.obj");
	Puerta_reja_central = Model();
	Puerta_reja_central.LoadModel("Models/Puerta_reja_puerta_central.obj");
	Puerta_reja_piso = Model();
	Puerta_reja_piso.LoadModel("Models/Puerta_reja_piso.obj");
	Puerta_reja_puerta_izquierda = Model();
	Puerta_reja_puerta_izquierda.LoadModel("Models/Puerta_reja_puerta_izquierda.obj");
	Puerta_reja_puerta_derecha = Model();
	Puerta_reja_puerta_derecha.LoadModel("Models/Puerta_reja_puerta_derecha.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	
	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	movCoche = 0.0f;
	movOffset = 0.5f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;

	glm::vec3 lowerLight(0.0f,0.0f,0.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

	// Generador de números aleatorios
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 8);


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

	
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation(); // para la textura con movimiento

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		//Reinicializando variables cada ciclo de reloj
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		// ================================================================================ //
		//																					//
		//									Dado 											//
		//																					//
		// ================================================================================ //

		// Animación de la puerta central (para abajo)
		if (mainWindow.getDadoLanzado())
		{
			if (numeroDado == 0)
			{
				numeroDado = dist(gen);
				//numeroDado = 8;
			}

			if ( dadoCaida )
			{
				if ( y_tras_dado >= -0.3f)
				{
					x_tras_dado += 0.035f * deltaTime;	// 0.7 * 0.5 (paso en y) / 10 (distancia de caida)
					y_tras_dado -= 0.5f * deltaTime;
					z_tras_dado += 0.035f * deltaTime;	// 0.7 * 0.5 (paso en y) / 10 (distancia de caida)


					z_rot_dado += 2.25f * deltaTime;   // 45 * 0.5 (paso en y) / 10 (distancia de caida)
				}
				else
				{
					dadoCaida = false;
					dadoGiro = true;
				}
			}
			else if (dadoGiro)
			{
				if ( x_tras_dado <= 10.71f && z_tras_dado >= -10.0f )
				{
					x_tras_dado += 0.08f * deltaTime;
					z_tras_dado -= 0.08f * deltaTime;

					x_rot_dado -= 3.6f * deltaTime;			// Ángulo: 
					z_rot_dado -= 3.6f * deltaTime;
				}
				else
				{
					dadoCaida = false;
					dadoGiro = false;
					dadoNumero = true;
				}
			}
			else if (dadoNumero)
			{
				/*
					Pos inicial:
						x = -449.746735
						y = 0.0
						z= -403.37007
				*/

				if (numeroDado == 1) // Se ve bien
				{
					if (x_rot_dado >= -449.9711f)
					{
						x_rot_dado -= 1.0f * deltaTime;
					}
					else
						x_dado = true;

					if ( y_rot_dado <= 305.0f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						y_rot_dado += 5.0f * deltaTime;
					}
					else
						y_dado = true;

					if ( z_rot_dado >= -403.531158f)
					{
						z_rot_dado -= 1.0f * deltaTime;
					}
					else
						z_dado = true;

					//x_rot_dado = -449.429535f;
					//y_rot_dado = -54.0f;
					//z_rot_dado = -402.97052f;
				}
				else if (numeroDado == 2) // Se ve bien
				{
					if (x_rot_dado <= -449.9711f)
						x_rot_dado += 1.0f * deltaTime;
					else
						x_dado = true;

					if (y_rot_dado <= 235.0f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						y_rot_dado += 5.0f * deltaTime;
					}
					else
						y_dado = true;

					if (z_rot_dado >= -403.531158f)
						z_rot_dado -= 1.0f * deltaTime;
					else
						z_dado = true;

					//x_rot_dado = -449.545654f;
					//y_rot_dado = -125.0f;
					//z_rot_dado = -402.921082f;
				}
				else if (numeroDado == 3) // Se ve bien
				{
					if (x_rot_dado >= -684.532532f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						x_rot_dado -= 5.0f * deltaTime;
					}
					else
						x_dado = true;

					y_dado = true; // no cambia Y en este número

					if (z_rot_dado <= -403.163208f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;

					//x_rot_dado = -324.548035f;
					//z_rot_dado = -403.163208f;
				}
				else if (numeroDado == 4) // Se ve bien
				{
					if (x_rot_dado >= -759.619324f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						x_rot_dado -= 5.0f * deltaTime;
					}
					else
						x_dado = true;

					y_dado = true;

					if (z_rot_dado <= -402.953613f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;

					//x_rot_dado = -394.65f;
					//z_rot_dado = -403.2f;
				}
				else if (numeroDado == 5) // Se ve bien
				{
					if (x_rot_dado >= -506.511292f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						x_rot_dado -= 5.0f * deltaTime;
					}
					else
						x_dado = true;

					y_dado = true;

					if (z_rot_dado <= -402.999268f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;

					//x_rot_dado = -506.511292f;
					//y_rot_dado = 0.0f;
					//z_rot_dado = -402.999268f;
				}
				else if (numeroDado == 6) // Se ve bien
				{
					if (x_rot_dado >= -574.510498f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						x_rot_dado -= 5.0f * deltaTime;
					}
					else
						x_dado = true;

					y_dado = true;

					if (z_rot_dado <= -403.035675f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;

					//x_rot_dado = -574.510498f;
					//z_rot_dado = -403.035675f;
				}
				else if (numeroDado == 7) // Se ve bien
				{
					if (x_rot_dado <= -449.93457f)
						x_rot_dado += 1.0f * deltaTime;
					else
						x_dado = true;

					if (y_rot_dado <= 55.0f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						y_rot_dado += 2.5f * deltaTime;
					}
					else
						y_dado = true;

					if (z_rot_dado <= -403.0507324f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;
					//x_rot_dado = -449.93457f;
					//y_rot_dado = 55.0f;
					//z_rot_dado = -403.0507324f;
				}
				else if (numeroDado == 8)
				{
					if (x_rot_dado <= -449.787201f)
						x_rot_dado += 1.0f * deltaTime;
					else
						x_dado = true;

					if (y_rot_dado <= 125.0f)
					{
						x_tras_dado += 0.08f * deltaTime;
						z_tras_dado -= 0.08f * deltaTime;
						y_rot_dado += 4.0f * deltaTime;
					}
					else
						y_dado = true;

					if (z_rot_dado <= -403.076813f)
						z_rot_dado += 1.0f * deltaTime;
					else
						z_dado = true;
					//x_rot_dado = -449.787201f;
					//y_rot_dado = 125.0f;
					//z_rot_dado = -403.076813f;
				}
				

				/*
				if (x_rot_dado <= -394.65f && z_rot_dado >= -403.2f)
				{
					x_rot_dado += 1.0f * deltaTime;
					z_rot_dado -= 1.0f * deltaTime;
				}*/
				
				/*
				if (x_tras_dado <= 12.71f || z_tras_dado >= -12.0f)
				{
					x_tras_dado += 0.08f * deltaTime;
					z_tras_dado -= 0.08f * deltaTime;


					x_rot_dado += 4.3904f * deltaTime;
					y_rot_dado += 0.0f * deltaTime;
					z_rot_dado += -0.02f * deltaTime;

					if (numeroDado == 1)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 2)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 3)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 4)
					{
						x_rot_dado += -4.4648f * deltaTime;
						y_rot_dado += 0.0f * deltaTime;
						z_rot_dado += -0.0632f * deltaTime;

						//x_rot_dado = -405.0f;
						//y_rot_dado = 34.529f;
						//z_rot_dado = -389.15f;
					}
					else if (numeroDado == 5)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 6)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 7)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}
					else if (numeroDado == 8)
					{
						x_rot_dado -= 0.0f * deltaTime;
						y_rot_dado -= 0.0f * deltaTime;
						z_rot_dado -= 0.0f * deltaTime;
					}

				}*/

				if ( x_dado && y_dado && z_dado )
				{
					tiempoNumero += 0.5f * deltaTime;

					if (tiempoNumero >= 50.0f)
					{
						dadoCaida = false;
						dadoGiro = false;
						dadoNumero = false;
						resetDado = true;
						tiempoNumero = 0.0f;
						x_dado = false;
						y_dado = false;
						z_dado = false;
					}
				}
				
			}
			
			if (resetDado)
			{
				x_tras_dado = 0.0f;
				y_tras_dado = 10.0f;
				z_tras_dado = 0.0f;

				x_rot_dado = 0.0f;
				y_rot_dado = 0.0f;
				z_rot_dado = 0.0f;

				mainWindow.setDadoLanzado();
				resetDado = false;
				dadoCaida = true;
				numeroDado = 0;
			}
		}
		/*
		x_rot_dado += mainWindow.getRotX();
		mainWindow.setRotX();
		printf("Rot X Dado: %f\n", x_rot_dado);
		y_rot_dado += mainWindow.getRotY();
		mainWindow.setRotY();
		printf("Rot Y Dado: %f\n", y_rot_dado);
		z_rot_dado += mainWindow.getRotZ();
		mainWindow.setRotZ();
		printf("Rot Z Dado: %f\n", z_rot_dado);


		printf("Traslacion X Dado: %f\n", x_tras_dado);
		printf("Traslacion Y Dado: %f\n", y_tras_dado);
		printf("Traslacion Z Dado: %f\n", z_tras_dado);
		*/

		// Dado 8 -----------------------------------------------------------------
		model = glm::mat4(1.0);
		toffset = glm::vec2(0.0, 0.0);
		model = glm::translate(model, glm::vec3(x_tras_dado, y_tras_dado, z_tras_dado));
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		model = glm::rotate(model, toRadians * x_rot_dado, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, toRadians * y_rot_dado, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, toRadians * z_rot_dado, glm::vec3(0.0f, 0.0f, 1.0f));

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dado8Texture.UseTexture();
		meshList[8]->RenderMesh();


		// ================================================================================ //
		//																					//
		//									Puerta 											//
		//																					//
		// ================================================================================ //

		// Animación de la puerta
		if (mainWindow.getPuertaAbriendose()) 
		{
			if (mainWindow.getPuertaCerrada())
			{
				if (bajadaPuerta >= -8.17f)
				{
					bajadaPuerta -= 0.1f * deltaTime;
					rotacionPuerta += 1.46879f * deltaTime;
				}
				else
				{
					mainWindow.setPuertaAbriendose();
					mainWindow.setPuertaCerrada();
				}
			}
			else
			{
				if (bajadaPuerta <= 0.0f)
				{
					bajadaPuerta += 0.1f * deltaTime;
					rotacionPuerta -= 1.46879f * deltaTime;
				}
				else
				{
					mainWindow.setPuertaAbriendose();
					mainWindow.setPuertaCerrada();
				}
			}	
		}
		
		// Animación del cartel de la puerta (textura animada)
		tiempoAcumulado += deltaTime;

		if (tiempoAcumulado >= 11.0f) 
		{
			toffsetcartelu += 0.06;

			if (toffsetcartelu >= 1.0)
			{
				toffsetcartelu = 0.0;
			}

			tiempoAcumulado = 0.0f;
		}
		toffsetcartelv = 0.0f;

		// Arco de la puerta ------------------------------------------------------------
		model = glm::mat4(1.0);
		
		// Posicionamiento global
		model = glm::translate(model, glm::vec3(-40.0f, -2.0f, 20.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_arco.RenderModel();


		modelaux = model;

		// Parte derecha de la puerta -----------------------------------------------------
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_derecha.RenderModel();
		
		// Parte izquierda de la puerta ---------------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(-23.4f, 0.0f, 00.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_derecha.RenderModel();
		
		// Parte central de la puerta -----------------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f + bajadaPuerta, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_central.RenderModel();

		// Piso de la puerta --------------------------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.01f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_piso.RenderModel();

		// Parte central derecha de la puerta -------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(8.25f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * rotacionPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_puerta_derecha.RenderModel();

		// Parte central izquierda de la puerta ---------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(-8.35f, 0.0f, 0.0f));
		model = glm::rotate(model, rotacionPuerta * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puerta_reja_puerta_izquierda.RenderModel();
		
		// Para el cartel de la puerta ----------------------------------------------------
		model = modelaux;
		toffset = glm::vec2(toffsetcartelu, toffsetcartelv);

		model = glm::translate(model, glm::vec3(0.0f, 17.19f, 0.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_font_Proyecto_GCEIHC.UseTexture();
		meshList[7]->RenderMesh();


		// ================================================================================ //



		glDisable(GL_BLEND);
		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
