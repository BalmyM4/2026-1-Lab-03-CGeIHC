
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <random>
#include <ctime>
#include <sstream>
#include <fstream>
#include <iomanip> 

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

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"
#include "keyframes.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;



// =================================================================== //
//																	   //
//					Variables para animación						   //
//																	   //
// =================================================================== //


// Puerta
float bajadaPuerta = 0.0f;
float rotacionPuerta = 0.0f;

// Hollow Knight
GLfloat HK_movimiento = 0.0f;
GLfloat hk_x = 0.0f;
GLfloat hk_z = 0.0f;
GLfloat hk_pos = 0.0f;
GLboolean hk_direccion = true;
float step;

// Cartel
float toffsetcartelu = 0.0f;
float toffsetcartelv = 0.0f;
float tiempoAcumulado = 0.0f;

// Fuego
float toffsetfuegou = 0.0f;
float toffsetfuegov = 0.0f;
float tiempoAcumuladoFuego = 0.0f;

// Luciernagas
float Lu_aXZ = 10.0f;
float Lu_aY = 5.0f;
float Lu_frecAng = 2.0f;
float Lu_phi = 0.0f;
float Lu_mov = 0.0f;

float Lu_x = 0.0f;
float Lu_y = 0.0f;
float Lu_z = 0.0f;

float Lu_alaAbajo = 0.0f;
float Lu_rot_ala = 0.0f;

// Iselda 
float movCabeza;
float rotxManoDer = 0.0f;
float rotyManoDer = 0.0f;
float rotzManoDer = 0.0f;

bool subexManoDer = true;
bool subeyManoDer = true;
bool subezManoDer = true;

float movIselda = 0.0f;

// Wumpa
GLfloat rotWumpa = 0.0f;
GLfloat wumpaTime = 0.0f;

// TNT de Crash Bandicoot
float toffsettntu = 0.0f;
float toffsettntv = 1.0f;
float toffsetexpu = 0.0f;
float toffsetexpv = 1.0f;
float tiempoAcumuladoTnt = 0.0f;
float tiempoAcumuladoExpTnt = 0.0f;
bool condandoTnt = true;
bool explotadoTnt = false;
bool portalTnt = false;
bool portalAbriendose = true;
bool caidaPortal = false;
bool portalCerrando = false;
bool resetPortal = false;
GLfloat sizeTnt = 3.0f;
GLfloat sizePortal = 0.0f;
float delayPortal = 0.0f;
GLfloat tntY = 0.0f;
float rotarPortal = 0.0f;

// Abrir megacaja
float toffsetrotcaja = 1.0f;
float rotcaja = 0.0f;

// Rotación alas aguila
float ag_rot_ala = 0.0f;
bool ag_alaAbajo = false;

// =================================================================== //


Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;


// =================================================================== //
//																	   //
//					Variables para texturas							   //
//																	   //
// =================================================================== //

// Texturas básicas
Texture plainTexture;
Texture pisoTexture;
Texture cespedTexture;

// Para el cartel de la puerta
Texture hk_font_Proyecto_GCEIHC;

// Para el fuego
Texture es_fuego;

// Para las rejas
Texture hk_rejas;

// Para la explosión de la TNT
Texture cb_explosion;


// =================================================================== //
//																	   //
//					Variables para Modelos							   //
//																	   //
// =================================================================== //

// Crash Bandicoot (Avatar)
Model cb_cuerpo;
Model cb_pierna_der_0;
Model cb_pierna_der_1;
Model cb_pierna_izq_0;
Model cb_pierna_izq_1;
Model cb_brazo_der_0;
Model cb_brazo_der_1;
Model cb_brazo_izq_0;
Model cb_brazo_izq_1;


// Puerta reja
Model Puerta_reja_arco;
Model Puerta_reja_derecha;
Model Puerta_reja_central;
Model Puerta_reja_piso;
Model Puerta_reja_puerta_izquierda;
Model Puerta_reja_puerta_derecha;

// Banco Hollow Knight
Model hk_Banco;

// Lampara Hollow Knight
Model hk_Lampara;

// Luciernaga Hollow Knight
Model hk_Luciernaga_cuerpo;
Model hk_Luciernaga_ala;
Model hk_Luciernaga_ala_izq;

// Ring
Model Ring;

// Rocas
Model Roca;
Model RocaPequenia;

// Iselda Hollow Knight
Model hk_mesa_iselda;
Model hk_body_iselda;
Model hk_head_iselda;
Model hk_arm_right0_iselda;
Model hk_arm_right1_iselda;
Model hk_arm_left0_iselda;
Model hk_arm_left1_iselda;

// Antorcha
Model es_Antorcha;

// Hollow Knight
Model hk_hollow_knight;
Model hk_dash;

// Wumpa de Crash Bandicoot
Model cb_Wumpa;

// TNT de Crash Bandicoot
Model cb_tnt;
Model rm_portal;

// Gradas
Model grada;

// Brawl stars
Model megacaja1;
Model megacaja2;

// El primo
Model elprimo;

// Dr Cortex
Model cb_dr_cortex;

// Piramide
Model es_piramide;

// Aguila
Model es_aguila;
Model es_aguila_ala_der;
Model es_aguila_ala_izq;

// =================================================================== //

// Skybox
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
SpotLight spotLights2[MAX_SPOT_LIGHTS];


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
		// Cara frontal
		0, 1, 2,
		0, 2, 3,
		// Cara trasera
		4, 5, 6,
		4, 6, 7,
		// Cara izquierda
		8, 9, 10,
		8, 10, 11,
		// Cara derecha
		12, 13, 14,
		12, 14, 15
	};

	GLfloat vegetacionVertices[] = {
		// ----- Frente (z = +0.5)
		-0.5f, -0.5f,  0.5f,   0.0f, 0.666f,   0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   0.25f, 0.666f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,   0.25f, 0.999f,    0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   0.0f, 0.999f,     0.0f, 0.0f, 1.0f,

		// ----- Atrás (z = -0.5)
		 0.5f, -0.5f, -0.5f,   0.0f, 0.666f,   0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,   0.25f, 0.666f,  0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,   0.25f, 0.999f,    0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,   0.0f, 0.999f,     0.0f, 0.0f, -1.0f,

		 // ----- Izquierda (x = -0.5)
		 -0.5f, -0.5f, -0.5f,   0.0f, 0.666f,  -1.0f, 0.0f, 0.0f,
		 -0.5f, -0.5f,  0.5f,   0.25f, 0.666f, -1.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,   0.25f, 0.999f,   -1.0f, 0.0f, 0.0f,
		 -0.5f,  0.5f, -0.5f,   0.0f, 0.999f,    -1.0f, 0.0f, 0.0f,

		 // ----- Derecha (x = +0.5)
		  0.5f, -0.5f,  0.5f,   0.0f, 0.666f,   1.0f, 0.0f, 0.0f,
		  0.5f, -0.5f, -0.5f,   0.25f, 0.666f,  1.0f, 0.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,   0.25f, 0.999f,    1.0f, 0.0f, 0.0f,
		  0.5f,  0.5f,  0.5f,   0.0f, 0.999f,     1.0f, 0.0f, 0.0f,
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

	unsigned int cruzIndices[] = {
		// Plano XY
		0, 1, 2,
		0, 2, 3,

		// Plano ZY
		4, 5, 6,
		4, 6, 7
	};
	GLfloat cruzVertices[] = {
		// ----- Plano XY (z = 0)
		-0.5f, -0.5f,  0.0f,   0.0f,  0.5f,   0.0f, 0.0f, 1.0f,  // abajo izq
		 0.5f, -0.5f,  0.0f,   0.25f, 0.5f,   0.0f, 0.0f, 1.0f,  // abajo der
		 0.5f,  0.5f,  0.0f,   0.25f, 1.0f,   0.0f, 0.0f, 1.0f,  // arriba der
		-0.5f,  0.5f,  0.0f,   0.0f,  1.0f,   0.0f, 0.0f, 1.0f,  // arriba izq

		// ----- Plano ZY (x = 0)
		 0.0f, -0.5f, -0.5f,   0.0f,  0.5f,   1.0f, 0.0f, 0.0f,  // abajo atrás
		 0.0f, -0.5f,  0.5f,   0.25f, 0.5f,   1.0f, 0.0f, 0.0f,  // abajo frente
		 0.0f,  0.5f,  0.5f,   0.25f, 1.0f,   1.0f, 0.0f, 0.0f,  // arriba frente
		 0.0f,  0.5f, -0.5f,   0.0f,  1.0f,   1.0f, 0.0f, 0.0f   // arriba atrás
	};

	unsigned int planoXZ_Indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat planoXZ_Vertices[] = {
		// ----- Plano XZ (y = 0)
		-0.5f, 0.0f, -0.5f,   0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // esquina inferior izq
		 0.5f, 0.0f, -0.5f,   0.75f, 0.0f,   0.0f, 1.0f, 0.0f, // esquina inferior der
		 0.5f, 0.0f,  0.5f,   0.75f, 0.5f,   0.0f, 1.0f, 0.0f, // esquina superior der
		-0.5f, 0.0f,  0.5f,   0.5f, 0.5f,   0.0f, 1.0f, 0.0f  // esquina superior izq
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
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 256, 48);
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

	Mesh* obj9 = new Mesh();
	obj9->CreateMesh(cruzVertices, cruzIndices, 64, 12);
	meshList.push_back(obj9);

	Mesh* obj10 = new Mesh();
	obj10->CreateMesh(planoXZ_Vertices, planoXZ_Indices, 32, 6);
	meshList.push_back(obj10);
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


// =================================================================== //
//																	   //
//								KEY FRAMES							   //
//																	   //
// =================================================================== //

FRAME KeyFrameAguila[MAX_FRAMES];
int FrameIndexAguila = 0;
int playIndexAguila = 0;
int i_max_stepsAguila = 100;
int i_curr_stepsAguila = 0;

//NEW// Keyframes
float posXaguila = 0.0f, posYaguila = 150.0f, posZaguila = 0.0f;
float movAguila_x = 0.0f, movAguila_y = 0.0f, movAguila_z = 0.0f;
float giroAguila = 0.0f;




int main()
{
	// Ventana principal
	mainWindow = Window(1280, 1024); 
	mainWindow.Initialise();

	// Crear objetos y shaders
	CreateObjects();
	CreateShaders();

	// Camera
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);


	// =================================================================== //
	//																	   //
	//						Importar texturas				       		   //
	//																	   //
	// =================================================================== //

	// Texturas básicas
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/Escenario/4_Piso.png");
	pisoTexture.LoadTextureA();
	cespedTexture = Texture("Textures/Escenario/cesped-verde.png");
	cespedTexture.LoadTextureA();


	// Skybox Textures (Day)
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	// Skybox Textures (Night)
	std::vector<std::string> skyboxFaces2;
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_rt.tga");
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_lf.tga");
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_dn.tga");
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_up.tga");
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_bk.tga");
	skyboxFaces2.push_back("Textures/Skybox/cupertin-lake-night_ft.tga");

	//Creación del skybox
	skybox = Skybox(skyboxFaces, skyboxFaces2);

	// Materiales
	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	// Textura del cartel de la puerta
	hk_font_Proyecto_GCEIHC = Texture("Textures/Hollow_knight/hk_font_Proyecto_GCEIHC.png");
	hk_font_Proyecto_GCEIHC.LoadTextureA();

	// Textura del fuego
	es_fuego = Texture("Textures/Escenario/es_fuego.png");
	es_fuego.LoadTextureA();

	// Textura de las rejas
	hk_rejas = Texture("Textures/Hollow_knight/hk_rejas.png");
	hk_rejas.LoadTextureA();

	// Textura de la explosión de la TNT
	cb_explosion = Texture("Textures/Crash_bandicoot/cb_explosion.png");
	cb_explosion.LoadTextureA();


	// =================================================================== //
	//																	   //
	//						Importar Modelos				       		   //
	//																	   //
	// =================================================================== //
	
	// Puerta reja
	Puerta_reja_arco = Model();
	Puerta_reja_arco.LoadModel("Models/Hollow_knight/hk_Puerta_reja_arco.obj");
	Puerta_reja_derecha = Model();
	Puerta_reja_derecha.LoadModel("Models/Hollow_knight/hk_Puerta_reja_derecha.obj");
	Puerta_reja_central = Model();
	Puerta_reja_central.LoadModel("Models/Hollow_knight/hk_Puerta_reja_puerta_central.obj");
	Puerta_reja_piso = Model();
	Puerta_reja_piso.LoadModel("Models/Hollow_knight/hk_Puerta_reja_piso.obj");
	Puerta_reja_puerta_izquierda = Model();
	Puerta_reja_puerta_izquierda.LoadModel("Models/Hollow_knight/hk_Puerta_reja_puerta_izquierda.obj");
	Puerta_reja_puerta_derecha = Model();
	Puerta_reja_puerta_derecha.LoadModel("Models/Hollow_knight/hk_Puerta_reja_puerta_derecha.obj");

	// Crash Bandicoot (Avatar)
	cb_cuerpo = Model();
	cb_cuerpo.LoadModel("Models/Crash_bandicoot/cb_cuerpo.obj");
	cb_pierna_der_0 = Model();
	cb_pierna_der_0.LoadModel("Models/Crash_bandicoot/cb_pierna_der_0.obj");
	cb_pierna_der_1 = Model();
	cb_pierna_der_1.LoadModel("Models/Crash_bandicoot/cb_pierna_der_1.obj");
	cb_brazo_der_0 = Model();
	cb_brazo_der_0.LoadModel("Models/Crash_bandicoot/cb_brazo_der_0.obj");
	cb_brazo_der_1 = Model();
	cb_brazo_der_1.LoadModel("Models/Crash_bandicoot/cb_brazo_der_1.obj");
	cb_pierna_izq_0 = Model();
	cb_pierna_izq_0.LoadModel("Models/Crash_bandicoot/cb_pierna_izq_0.obj");
	cb_pierna_izq_1 = Model();
	cb_pierna_izq_1.LoadModel("Models/Crash_bandicoot/cb_pierna_izq_1.obj");
	cb_brazo_izq_0 = Model();
	cb_brazo_izq_0.LoadModel("Models/Crash_bandicoot/cb_brazo_izq_0.obj");
	cb_brazo_izq_1 = Model();
	cb_brazo_izq_1.LoadModel("Models/Crash_bandicoot/cb_brazo_izq_1.obj");


	// Banco Hollow Knight
	hk_Banco = Model();
	hk_Banco.LoadModel("Models/Hollow_knight/hk_Banco.obj");

	// Lampara Hollow Knight
	hk_Lampara = Model();
	hk_Lampara.LoadModel("Models/Hollow_knight/hk_Lampara.obj");

	// Luciernaga Hollow Knight
	hk_Luciernaga_cuerpo = Model();
	hk_Luciernaga_cuerpo.LoadModel("Models/Hollow_knight/hk_Luciernaga_cuerpo.obj");
	hk_Luciernaga_ala = Model();
	hk_Luciernaga_ala.LoadModel("Models/Hollow_knight/hk_Luciernaga_ala.obj");
	hk_Luciernaga_ala_izq = Model();
	hk_Luciernaga_ala_izq.LoadModel("Models/Hollow_knight/hk_Luciernaga_ala_izq.obj");

	// Ring
	Ring = Model();
	Ring.LoadModel("Models/Escenario/es_Ring.obj");

	// Rocas
	Roca = Model();
	Roca.LoadModel("Models/Escenario/es_Roca_canasta.obj");
	RocaPequenia = Model();
	RocaPequenia.LoadModel("Models/Escenario/es_Roca_canasta_pequenia.obj");

	// Iselda Hollow Knight
	hk_mesa_iselda = Model();
	hk_mesa_iselda.LoadModel("Models/Hollow_knight/hk_mesa_iselda.obj");
	hk_body_iselda = Model();
	hk_body_iselda.LoadModel("Models/Hollow_knight/hk_body_iselda.obj");
	hk_head_iselda = Model();
	hk_head_iselda.LoadModel("Models/Hollow_knight/hk_head_iselda.obj");
	hk_arm_right0_iselda = Model();
	hk_arm_right0_iselda.LoadModel("Models/Hollow_knight/hk_arm_right0_iselda.obj");
	hk_arm_right1_iselda = Model();
	hk_arm_right1_iselda.LoadModel("Models/Hollow_knight/hk_arm_right1_iselda.obj");
	hk_arm_left0_iselda = Model();
	hk_arm_left0_iselda.LoadModel("Models/Hollow_knight/hk_arm_left0_iselda.obj");
	hk_arm_left1_iselda = Model();
	hk_arm_left1_iselda.LoadModel("Models/Hollow_knight/hk_arm_left1_iselda.obj");

	// Antorcha
	es_Antorcha = Model();
	es_Antorcha.LoadModel("Models/Escenario/es_antorcha.obj");

	// Hollow Knight
	hk_hollow_knight = Model();
	hk_hollow_knight.LoadModel("Models/Hollow_knight/hk_hollow_knight.obj");
	hk_dash = Model();
	hk_dash.LoadModel("Models/Hollow_knight/hk_dash.obj");

	// Wumpa de Crash Bandicoot
	cb_Wumpa = Model();
	cb_Wumpa.LoadModel("Models/Crash_bandicoot/cb_Wumpa.obj");

	// tnt de Crash Bandicoot
	cb_tnt = Model();
	cb_tnt.LoadModel("Models/Crash_bandicoot/cb_tnt.obj");

	// portal de rick y morty
	rm_portal = Model();
	rm_portal.LoadModel("Models/Rick_and_morty/rm_Portal.obj");


	//Grada
	grada = Model();
	grada.LoadModel("Models/Escenario/es_grada.obj");

	//Mega caja 
	megacaja1 = Model();
	megacaja1.LoadModel("Models/Brawl_stars/bs_megacaja_arriba.obj");

	megacaja2 = Model();
	megacaja2.LoadModel("Models/Brawl_stars/bs_megacaja_abajo.obj");

	// El primo
	elprimo = Model();
	elprimo.LoadModel("Models/Brawl_stars/bs_primoulti.obj");

	/*elprimo = Model();
	elprimo.LoadModel("Models/Brawl_stars/Mobile - Brawl Stars - El Primo.fbx");*/

	// Dr Cortex
	cb_dr_cortex = Model();
	cb_dr_cortex.LoadModel("Models/Crash_bandicoot/cb_dr_cortex.obj");

	// Piramide
	es_piramide = Model();
	es_piramide.LoadModel("Models/Escenario/es_pyramid.obj");

	// Aguila
	es_aguila = Model();
	es_aguila.LoadModel("Models/Escenario/es_aguila.obj");
	es_aguila_ala_izq = Model();
	es_aguila_ala_izq.LoadModel("Models/Escenario/es_aguila_ala_izq.obj");
	es_aguila_ala_der = Model();
	es_aguila_ala_der.LoadModel("Models/Escenario/es_aguila_ala_der.obj");

	
	// =================================================================== //
	//																	   //
	//						Definir luces					       		   //
	//																	   //
	// =================================================================== //

	
	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, -1.0f, 0.0f);


	// Luces puntuales ----------------------------------------------------

	unsigned int pointLightCount = 0; // Contador de luces puntuales

	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	// Luces spot ---------------------------------------------------------

	unsigned int spotLightCount = 0; // Contador de luces spot

	// Linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	// Lampara hollow knight 1
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	glm::vec3 baseLightPosHK_1(-0.732f, 4.2f, 0.0f);

	// Lampara hollow knight 2
	spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;
	glm::vec3 baseLightPosHK_2(-0.732f, 4.2f, 0.0f);

	// Segundo arreglo
	spotLights2[0] = spotLights[0];
	spotLights2[1] = spotLights[2];
	spotLights2[2] = spotLights[1];

	
	// =================================================================== //
	//																	   //
	//							Key Frames					       		   //
	//																	   //
	// =================================================================== //

	CargarKeyframesDesdeArchivo("keyframes_aguila.txt" , movAguila_x, movAguila_y, movAguila_z, giroAguila, KeyFrameAguila, FrameIndexAguila);

	printf("\n=== TECLAS PARA USO DE KEYFRAMES Y MOVIMIENTO ===\n");
	printf("1.- Barra espaciadora: Reproducir animación\n");
	printf("2.- Tecla 0: Habilitar nuevamente la reproducción de la animación\n");
	printf("3.- Tecla L: Guardar frame actual\n");
	printf("4.- Tecla P: Habilitar guardar un nuevo frame\n\n");

	printf("=== MOVIMIENTO MANUAL DEL HELICÓPTERO ===\n");
	printf("EJE X:\n");
	printf("   Tecla 1: Mover en X positivo (+X)\n");
	printf("   Tecla 2: Mover en X negativo (-X)\n");
	printf("   Tecla 3: Desbloquear eje X para volver a mover\n\n");

	printf("EJE Y:\n");
	printf("   Tecla 4: Mover en Y positivo (+Y)\n");
	printf("   Tecla 5: Mover en Y negativo (-Y)\n");
	printf("   Tecla 6: Desbloquear eje Y para volver a mover\n\n");

	printf("EJE Z:\n");
	printf("   Tecla 7: Mover en Z positivo (+Z)\n");
	printf("   Tecla 8: Mover en Z negativo (-Z)\n");
	printf("   Tecla 9: Desbloquear eje Z para volver a mover\n\n");

	printf("ROTACION EN EJE Y:\n");
	printf("   Tecla Q: Rotar a la izquierda (−Y)\n");
	printf("   Tecla E: Rotar a la derecha (+Y)\n");
	printf("   Tecla R: Habilitar nuevamente la rotacion\n\n");

	// =================================================================== //

	//Duración ciclo dia/noche
	float ciclo = 10.0f;
	float t;
	float a;

	// Variables
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset=0;
	GLuint uniformColor = 0;

	// Matriz de proyección
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	// Para la lampara
	glm::vec3 lowerLight(0.0f,0.0f,0.0f);

	// Variables auxiliares
	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 ringCentro(1.0);
	glm::mat4 luciernagaPos(1.0);
	glm::mat4 iseldaPos(1.0);
	glm::mat4 crashAux(1.0);
	glm::mat4 crashExtrAux(1.0);

	// Para la piramide
	glm::mat4 aguilaAux(1.0);
	glm::vec3 aguilaPos(0.0f, 0.0f, 0.0f);


	// Color blanco por defecto
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	// Offset de textura
	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

	// Para el fuego
	float xtorch, ztorch;

	// Para los wumpas
	float localTime;
	float tw;
	glm::vec3 posW;

	// Para la tnt
	glm::vec3 posTNT;

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		// Calculo del tiempo entre frames
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//dia/noche
		t = fmod(glfwGetTime(), ciclo) / ciclo;
		a = 0.5f * (1.0f - cos(2.0f * 3.14159265f * t));

		skybox.setFactor(a);
		//skybox.setFactor(0.0f);
		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// =================================================================== //
		//																	   //
		//							Key Frames					       		   //
		//																	   //
		// =================================================================== //

		inputKeyframes(KeyFrameAguila, mainWindow.getsKeys(), movAguila_x, movAguila_y, movAguila_z, giroAguila);
		animate(KeyFrameAguila, playIndexAguila, i_curr_stepsAguila, i_max_stepsAguila, FrameIndexAguila, movAguila_x, movAguila_y, movAguila_z, giroAguila);


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
		spotLights2[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);


		//Reinicializando variables cada ciclo de reloj
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		// Piso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -150.0f));
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 20.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		// Piso cesped
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -150.0f));
		model = glm::scale(model, glm::vec3(100.0f, 1.0f, 100.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		cespedTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();



		// ================================================================================ //
		//																					//
		//							Crash Bandicoot (avatar)								//
		//																					//
		// ================================================================================ //

		// Cuerpo -------------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = glm::translate(model, glm::vec3(0.0f + mainWindow.getmovex_cb(), 6.2f, 0.0f + mainWindow.getmovez_cb()));
		model = glm::rotate(model, mainWindow.getrotz_cb() * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		crashAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_cuerpo.RenderModel();

		// Pierna derecha 0 ---------------------------------------------------
		model = crashAux;
		model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0f));
		crashExtrAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_pierna_der_0.RenderModel();

		// Pierna derecha 1 ---------------------------------------------------
		model = crashExtrAux;
		model = glm::translate(model, glm::vec3(0.5f, -2.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_pierna_der_1.RenderModel();

		// Pierna izquierda 0 ---------------------------------------------------
		model = crashAux;
		model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0f));
		crashExtrAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_pierna_izq_0.RenderModel();

		// Pierna izquierda 1 ---------------------------------------------------
		model = crashExtrAux;
		model = glm::translate(model, glm::vec3(-0.5f, -2.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_pierna_izq_1.RenderModel();

		// Brazo derecho 0 ---------------------------------------------------
		model = crashAux;
		model = glm::translate(model, glm::vec3(2.2f, 5.08f, 0.97f));
		crashExtrAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_brazo_der_0.RenderModel();

		// Brazo derecho 1 ---------------------------------------------------
		model = crashExtrAux;
		model = glm::translate(model, glm::vec3(1.5f, -3.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_brazo_der_1.RenderModel();

		// Brazo izquierdo 0 ---------------------------------------------------
		model = crashAux;
		model = glm::translate(model, glm::vec3(-2.5f, 4.8f, 1.1f));
		crashExtrAux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_brazo_izq_0.RenderModel();

		// Brazo izquierdo 1 ---------------------------------------------------
		model = crashExtrAux;
		model = glm::translate(model, glm::vec3(-1.5f, -3.0f, -0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_brazo_izq_1.RenderModel();


		
		// ================================================================================ //
		//																					//
		//									Ring											//
		//																					//
		// ================================================================================ //


		model = glm::mat4(1.0);

		// Posicionamiento global
		model = glm::translate(model, glm::vec3(0.0f, 0.01f, -150.0f));
		ringCentro = model;
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Ring.RenderModel();



		// ================================================================================ //
		//																					//
		//									Rocas											//
		//																					//
		// ================================================================================ //


		// Roca grande ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-30.0f, 55.0f, 10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Roca.RenderModel();

		// Roca pequeña ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(30.0f, 55.0f, -10.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		RocaPequenia.RenderModel();


		// ================================================================================ //
		//																					//
		//					Bancas_HK, Lamparas_HK y Luciernagas_HK							//
		//																					//
		// ================================================================================ //

		// Para prender y apagar las luces de las lamparas -------------------------

		if (mainWindow.getPrendida1() && mainWindow.getPrendida2())
		{
			shaderList[0].SetSpotLights(spotLights, spotLightCount);
		}
		else if (mainWindow.getPrendida1() && !mainWindow.getPrendida2())
		{
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 1);
		}
		else if (!mainWindow.getPrendida1() && mainWindow.getPrendida2())
		{
			shaderList[0].SetSpotLights(spotLights2, spotLightCount - 1);
		}
		else
		{
			shaderList[0].SetSpotLights(spotLights, spotLightCount - 2);
		}



		// Animación de las luciernagas --------------------------------------------

		Lu_mov += deltaTime * 0.01;

		// Alas angulo
		if (Lu_alaAbajo)
		{
			if (Lu_rot_ala > -65.0f)
			{
				Lu_rot_ala -= 4.0f * deltaTime;
			}
			else
			{
				Lu_alaAbajo = !Lu_alaAbajo;
			}
		}
		else
		{
			if (Lu_rot_ala < 35.0f)
			{
				Lu_rot_ala += 4.0f * deltaTime;
			}
			else
			{
				Lu_alaAbajo = !Lu_alaAbajo;
			}
		}


		// Banca del fondo ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, -80.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Banco.RenderModel();

		// Lampara asociada a la banca del fondo ---------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(15.0f, -4.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		spotLights[1].SetPos(glm::vec3(model * glm::vec4(baseLightPosHK_1, 1.0f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Lampara.RenderModel();

		// Luciernagas asociadas a la lampara de la banca del fondo ---------------

		Lu_x = Lu_aXZ * cos(Lu_mov);
		Lu_z = Lu_aXZ * sin(Lu_mov);
		Lu_y = Lu_aY * sin(Lu_frecAng * Lu_mov);

		// Cuerpo [0]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f + Lu_x, 15.0f + Lu_y, 0.0f + Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [0]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [0]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();

		Lu_x = (Lu_aXZ * cos(Lu_mov)) / (1 + pow(sin(Lu_mov), 2));
		Lu_z = (Lu_aXZ * sin(Lu_mov) * cos(Lu_mov)) / (1 + pow(sin(Lu_mov), 2));
		Lu_y = Lu_aY * sin(Lu_frecAng * Lu_mov + Lu_phi);

		// Cuerpo [1]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f - Lu_x, 15.0f - Lu_y, 0.0f - Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [1]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [1]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();

		Lu_x = 2.0f * sin(Lu_mov) * (exp(cos(Lu_mov)) - 2 * cos(4 * Lu_mov) - pow(sin(Lu_mov / 12), 5));
		Lu_z = 2.0f * cos(Lu_mov) * (exp(cos(Lu_mov)) - 2 * cos(4 * Lu_mov) - pow(sin(Lu_mov / 12), 5));
		Lu_y = 2.0f * sin(0.5f * Lu_mov) + 0.5f * sin(5.0f * Lu_mov);

		Lu_x += 0.3f * (sin(3.1f * Lu_mov));
		Lu_z += 0.3f * (cos(2.7f * Lu_mov));

		// Cuerpo [2]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f + Lu_x, 10.0f + Lu_y, 0.0f + Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [2]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [2]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();


		// Banca de adelante ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(0.0f, 4.0f, 80.0f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Banco.RenderModel();

		// Lampara asociada a la banca de adelante -------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(-15.0f, -4.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		spotLights[2].SetPos(glm::vec3(model* glm::vec4(baseLightPosHK_2, 1.0f)));
		spotLights2[1].SetPos(glm::vec3(model* glm::vec4(baseLightPosHK_2, 1.0f)));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Lampara.RenderModel();

		// Luciernagas asociadas a la banca de adelante --------------------------

		Lu_x = Lu_aXZ * cos(Lu_mov);
		Lu_z = Lu_aXZ * sin(Lu_mov);
		Lu_y = Lu_aY * sin(Lu_frecAng * Lu_mov);

		// Cuerpo [0]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f + Lu_x, 15.0f + Lu_y, 0.0f + Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [0]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [0]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();

		Lu_x = (Lu_aXZ * cos(Lu_mov)) / (1 + pow(sin(Lu_mov), 2));
		Lu_z = (Lu_aXZ * sin(Lu_mov) * cos(Lu_mov)) / (1 + pow(sin(Lu_mov), 2));
		Lu_y = Lu_aY * sin(Lu_frecAng * Lu_mov + Lu_phi);

		// Cuerpo [1]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f - Lu_x, 15.0f - Lu_y, 0.0f - Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [1]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [1]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();

		Lu_x = 2.0f * sin(Lu_mov) * (exp(cos(Lu_mov)) - 2 * cos(4 * Lu_mov) - pow(sin(Lu_mov / 12), 5));
		Lu_z = 2.0f * cos(Lu_mov) * (exp(cos(Lu_mov)) - 2 * cos(4 * Lu_mov) - pow(sin(Lu_mov / 12), 5));
		Lu_y = 2.0f * sin(0.5f * Lu_mov) + 0.5f * sin(5.0f * Lu_mov);

		Lu_x += 0.3f * (sin(3.1f * Lu_mov));
		Lu_z += 0.3f * (cos(2.7f * Lu_mov));

		// Cuerpo [2]
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f + Lu_x, 10.0f + Lu_y, 0.0f + Lu_z));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		luciernagaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_cuerpo.RenderModel();

		// Ala derecha [2]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(-0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala.RenderModel();

		// Ala izquierda [2]
		model = luciernagaPos;
		model = glm::translate(model, glm::vec3(0.3f, 0.0f, 0.0f));
		model = glm::rotate(model, -1 * Lu_rot_ala * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_Luciernaga_ala_izq.RenderModel();


		// ================================================================================ //
		//																					//
		//									Gradas											//
		//																					//
		// ================================================================================ //
	
		// Grada 1
		model = ringCentro;
		model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		model = glm::translate(model, glm::vec3(0.0f, -0.65f, -47.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		grada.RenderModel();


		// ================================================================================ //
		//																					//
		//									Primo											//
		//																					//
		// ================================================================================ //

		// Primo
		model = ringCentro;
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		model = glm::translate(model, glm::vec3(0.0f, 15.0f, 0.0f));
		//model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		elprimo.RenderModel();


		// ================================================================================ //
		//																					//
		//									brawl stars										//
		//																					//
		// ================================================================================ //
		

		if (mainWindow.getMegacaja() ) {
			if (rotcaja < 60.0f) {
				rotcaja += toffsetrotcaja * deltaTime;
			}
		}
		else {
			if (rotcaja > 0.0f) {
				rotcaja -= toffsetrotcaja * deltaTime;
			}
		}
		
		
		// Megacaja 1 --------------------------------------------------------------------
		model = ringCentro;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(-30.0f, 0.9, 0.0));
		model = glm::rotate(model, rotcaja * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		megacaja1.RenderModel();

		model = ringCentro;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(-28.85f, 0.22f, 0.0));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		megacaja2.RenderModel();


		// Megacaja 2 --------------------------------------------------------------------
		model = ringCentro;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(30.0f, 0.9, 0.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotcaja * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		megacaja1.RenderModel();

		model = ringCentro;
		model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
		model = glm::translate(model, glm::vec3(28.85f, 0.22f, 0.0));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		megacaja2.RenderModel();



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
		model = ringCentro;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 140.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

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

		// Reset cords uv ------------------------------
		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));


		// ================================================================================ //
		//																					//
		//									Iselda											//
		//																					//
		// ================================================================================ //

		// Variable de tiempo acumulado
		movIselda += deltaTime * 0.015;

		// Movimiento senoidal cabeza
		movCabeza = sin(movIselda * 2.5f) * 0.03f;

		// Movimiento mano
		if (subexManoDer)
		{
			if (rotxManoDer <= 20.4411)
				rotxManoDer += deltaTime * 0.5;
			else
				subexManoDer = !subexManoDer;
		}
		else
		{
			if (rotxManoDer >= -20.4411)
				rotxManoDer -= deltaTime * 0.5;
			else
				subexManoDer = !subexManoDer;
		}


		// Mesa Iselda -----------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(80.0f, 0.0f, 80.0f));
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		iseldaPos = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_mesa_iselda.RenderModel();

		// Cuerpo Iselda ---------------------------------------------------------
		model = iseldaPos;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_body_iselda.RenderModel();

		// Cabeza Iselda ---------------------------------------------------------
		model = iseldaPos;
		model = glm::translate(model, glm::vec3(0.0f, movCabeza, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_head_iselda.RenderModel();

		// Brazo derecho Iselda --------------------------------------------------
		model = iseldaPos;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_arm_right0_iselda.RenderModel();

		// Mano derecha Iselda ---------------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.29f, 1.32f, -0.54f));
		model = glm::rotate(model, (rotxManoDer)*toRadians, glm::vec3(1, 0, 0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_arm_right1_iselda.RenderModel();

		// Brazo izquierdo Iselda ------------------------------------------------
		model = iseldaPos;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_arm_left0_iselda.RenderModel();

		// Mano izquierdo Iselda -------------------------------------------------
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		hk_arm_left1_iselda.RenderModel();



		// ================================================================================ //
		//																					//
		//								Hollow Knight										//
		//																					//
		// ================================================================================ //

		// Hollow Knight --------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-20.0f, 12.0f, 20.0f));


		if (mainWindow.getHK_Dash())
		{
			if (HK_movimiento <= 40.0f)
			{
				HK_movimiento += 2.0f * deltaTime;

				step = 2.0f * deltaTime;
				if (!std::isfinite(step)) step = 0.0f;

				if (hk_direccion)
				{
					hk_x += step;
					hk_z -= step;
				}
				else
				{
					hk_x -= step;
					hk_z += step;
				}
			}
			else
			{
				HK_movimiento = 0.0f;
				mainWindow.setHK_Dash();

				// cambia la dirección al terminar
				hk_direccion = !hk_direccion;
				hk_pos = hk_direccion ? 0.0f : 1.0f;
			}

			model = glm::translate(model, glm::vec3(hk_x, 4.0f, hk_z));
			model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));

			if (hk_direccion)
				model = glm::rotate(model, 135.0f * toRadians, glm::vec3(0, 1, 0));
			else
				model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0, 1, 0));

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_dash.RenderModel();
		}
		else
		{
			if (hk_pos == 1.0f)
			{
				model = glm::translate(model, glm::vec3(hk_x, 0.0f, hk_z));
				model = glm::rotate(model, 135.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else if (hk_pos == 0.0f)
			{
				model = glm::translate(model, glm::vec3(hk_x, 0.0f, hk_z));
				model = glm::rotate(model, -45.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
			}

			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_hollow_knight.RenderModel();
		}

		if (!std::isfinite(hk_x) || !std::isfinite(hk_z)) {
			hk_x = hk_z = 0.0f;
			std::cout << "[WARN] HK posición inválida reseteada.\n";
		}


		// ================================================================================ //
		//																					//
		//							Wumpas Crash Bandicoot									//
		//																					//
		// ================================================================================ //


		// Animación de rotación
		rotWumpa += 5.0f * deltaTime;
		if (rotWumpa > 360.0f)
			rotWumpa -= 360.0f;

		// Animación de traslación
		wumpaTime += 0.1f * deltaTime;
		if (wumpaTime > 480.0f)
			wumpaTime -= 480.0f;

		// Primer trio de wumpas
		for (int i = 0; i < 3; i++) {

			localTime = wumpaTime - i * 5.0f;
			if (localTime < 0.0f)
				localTime += 480.0f;

			tw = fmod(localTime, 480.0f);

			if (tw < 120.0f) {
				posW = glm::vec3(60.0f - tw, 4.0f, 60.0f); // lado 1
			}
			else if (tw < 2 * 120.0f) {
				posW = glm::vec3(-60.0f, 4.0f, 60.0f - (tw - 120.0f)); // lado 2
			}
			else if (tw < 3 * 120.0f) {
				posW = glm::vec3(-60.0f + (tw - 2 * 120.0f), 4.0f, -60.0f); // lado 3
			}
			else {
				posW = glm::vec3(60.0f, 4.0f, -60.0f + (tw - 3 * 120.0f)); // lado 4
			}

			// Sube y baja
			posW.y += sin((wumpaTime * 0.5f) + (i * 1.0f)) * 1.5f;

			model = glm::mat4(1.0f);
			model = ringCentro;
			model = glm::translate(model, posW);
			model = glm::rotate(model, rotWumpa * toRadians, glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			cb_Wumpa.RenderModel();
		}

		// Segundo trio de wumpas
		for (int i = 0; i < 3; i++) {

			localTime = wumpaTime - i * 5.0f;
			if (localTime < 0.0f)
				localTime += 520.0f; // 4 * 130

			tw = fmod(localTime, 520.0f);

			if (tw < 130.0f) {
				posW = glm::vec3(65.0f - tw, 4.0f, 65.0f);
			}
			else if (tw < 260.0f) {
				posW = glm::vec3(-65.0f, 4.0f, 65.0f - (tw - 130.0f));
			}
			else if (tw < 390.0f) {
				posW = glm::vec3(-65.0f + (tw - 260.0f), 4.0f, -65.0f);
			}
			else {
				posW = glm::vec3(65.0f, 4.0f, -65.0f + (tw - 390.0f));
			}

			// Sube y baja
			posW.y += sin((wumpaTime * 0.5f) + (i * 1.0f)) * 1.5f;

			model = glm::mat4(1.0f);
			model = ringCentro;
			model = glm::translate(model, posW);
			model = glm::rotate(model, -rotWumpa * toRadians, glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.8f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			cb_Wumpa.RenderModel();
		}

		// Tercer trío (espejo del primero)
		for (int i = 0; i < 3; i++) {

			localTime = wumpaTime - i * 5.0f;
			if (localTime < 0.0f)
				localTime += 480.0f;

			tw = fmod(localTime, 480.0f);

			if (tw < 120.0f) {
				posW = glm::vec3(-(60.0f - tw), 4.0f, -(60.0f)); // invertido en XZ
			}
			else if (tw < 240.0f) {
				posW = glm::vec3(60.0f, 4.0f, -(60.0f - (tw - 120.0f)));
			}
			else if (tw < 360.0f) {
				posW = glm::vec3(60.0f - (tw - 240.0f), 4.0f, 60.0f);
			}
			else {
				posW = glm::vec3(-60.0f, 4.0f, 60.0f - (tw - 360.0f));
			}

			posW.y += sin((wumpaTime * 0.5f) + (i * 1.0f)) * 1.5f;

			model = glm::mat4(1.0f);
			model = ringCentro;
			model = glm::translate(model, posW);
			model = glm::rotate(model, -rotWumpa * toRadians, glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.8f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			cb_Wumpa.RenderModel();
		}

		// Cuarto trío (espejo del segundo)
		for (int i = 0; i < 3; i++) {

			localTime = wumpaTime - i * 5.0f;
			if (localTime < 0.0f)
				localTime += 520.0f;

			tw = fmod(localTime, 520.0f);

			if (tw < 130.0f) {
				posW = glm::vec3(-(65.0f - tw), 4.0f, -(65.0f));
			}
			else if (tw < 260.0f) {
				posW = glm::vec3(65.0f, 4.0f, -(65.0f - (tw - 130.0f)));
			}
			else if (tw < 390.0f) {
				posW = glm::vec3(65.0f - (tw - 260.0f), 4.0f, 65.0f);
			}
			else {
				posW = glm::vec3(-65.0f, 4.0f, 65.0f - (tw - 390.0f));
			}

			posW.y += sin((wumpaTime * 0.5f) + (i * 1.0f)) * 1.5f;

			model = glm::mat4(1.0f);
			model = ringCentro;
			model = glm::translate(model, posW);
			model = glm::rotate(model, rotWumpa * toRadians, glm::vec3(0, 1, 0));
			model = glm::scale(model, glm::vec3(0.8f));
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			cb_Wumpa.RenderModel();
		}


		// ================================================================================ //
		//																					//
		//							Wumpas Crash Bandicoot									//
		//																					//
		// ================================================================================ //


		// Dr Cortex --------------------------------------------------------
		model = glm::mat4(1.0f);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(100.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_dr_cortex.RenderModel();


		// ================================================================================ //
		//																					//
		//									Piramide										//
		//																					//
		// ================================================================================ //

		if (!ag_alaAbajo)
		{
			ag_rot_ala += 3.0 * deltaTime;
			if (ag_rot_ala >= 60.0f)
			{
				ag_rot_ala = 60.0f;
				ag_alaAbajo = true;
			}
				
		}	
		else if (ag_alaAbajo)
		{
			ag_rot_ala -= 3.0 * deltaTime;
			if (ag_rot_ala <= -60.0f)
			{
				ag_rot_ala = -60.0f;
				ag_alaAbajo = false;
			}
		}

		// Piramide --------------------------------------------------------
		model = glm::mat4(1.0f);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-350.0f, 0.0f, -350.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_piramide.RenderModel();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Aguila -----------------------------------------------------------


		// Traslación
		aguilaPos = glm::vec3(posXaguila + movAguila_x, posYaguila + movAguila_y, posZaguila + movAguila_z);
		model = glm::translate(model, aguilaPos);

		// Escalado
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));

		// Rotación
		model = glm::rotate(model, giroAguila * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

		aguilaAux = model;

		// Render
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_aguila.RenderModel();

		// Ala derecha -------------------------------------------------------
		model = aguilaAux;
		model = glm::translate(model, glm::vec3(10.0f, 25.0f, -20.0f));
		model = glm::rotate(model, ag_rot_ala * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_aguila_ala_der.RenderModel();

		// Ala izquierda ------------------------------------------------------
		model = aguilaAux;
		model = glm::translate(model, glm::vec3(-10.0f, 25.0f, -20.0f));
		model = glm::rotate(model, -1 * ag_rot_ala * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_aguila_ala_izq.RenderModel();

		glDisable(GL_BLEND);


		// ================================================================================ //
		//																					//
		//								Antorchas VA AL FINAL								//
		//																					//
		// ================================================================================ //

		
		// Para el posicionamiento de las antorchas y fuegos
		xtorch = 40.0f;
		ztorch = 40.0f;

		// Antorcha 1 ---------------------------------------------------------
		model = glm::mat4(1.0);
		modelaux = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-1 * xtorch, 0.0f, ztorch));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_Antorcha.RenderModel();

		// Antorcha 2 ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(xtorch, 0.0f, ztorch));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_Antorcha.RenderModel();

		// Antorcha 3 ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-1 * xtorch, 0.0f, -1 * ztorch));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_Antorcha.RenderModel();

		// Antorcha 4 ---------------------------------------------------------
		model = glm::mat4(1.0);

		// Posicionamiento global
		model = ringCentro;
		model = glm::translate(model, glm::vec3(xtorch, 0.0f, -1 * ztorch));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_Antorcha.RenderModel();
		

		// Animación del fuego ------------------------------------------------
		tiempoAcumuladoFuego += deltaTime;

		if (tiempoAcumuladoFuego >= 5.0f)
		{
			toffsetfuegou += 0.25;

			if (toffsetfuegou >= 1.0)
			{
				toffsetfuegou = 0.0;
				toffsetfuegov -= 0.333f;

				if (toffsetfuegov <= 0.0f)
				{
					toffsetfuegov = 0.999f;
				}
			}

			tiempoAcumuladoFuego = 0.0f;
		}

		// Fuego 1 ------------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-1 * xtorch, 13.5f, ztorch));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.0f));
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		toffset = glm::vec2(toffsetfuegou, toffsetfuegov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_fuego.UseTexture();
		meshList[3]->RenderMesh();

		// Fuego 2 ------------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, glm::vec3(xtorch, 13.5f, ztorch));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.0f));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		toffset = glm::vec2(toffsetfuegou, toffsetfuegov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_fuego.UseTexture();
		meshList[3]->RenderMesh();

		// Fuego 3 ------------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, glm::vec3(-1 * xtorch, 13.5f, -1 * ztorch));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.0f));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		toffset = glm::vec2(toffsetfuegou, toffsetfuegov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_fuego.UseTexture();
		meshList[3]->RenderMesh();

		// Fuego 4 ------------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, glm::vec3(xtorch, 13.5f, -1 * ztorch));
		model = glm::scale(model, glm::vec3(2.0f, 4.0f, 2.0f));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		toffset = glm::vec2(toffsetfuegou, toffsetfuegov);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		es_fuego.UseTexture();
		meshList[3]->RenderMesh();


		// Reset cords uv ------------------------------
		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glDisable(GL_BLEND);


		// ================================================================================ //
		//																					//
		//							Rejas borde VA AL FINAL									//
		//																					//
		// ================================================================================ //

		// Atrás
		for (int i = 0; i < 27; i++)
		{
			model = ringCentro;
			model = glm::translate(model, glm::vec3(-130.0f + (10 * i), 10.0f, -140.0f));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_rejas.UseTexture();
			meshList[4]->RenderMesh();
		}

		// Izquierda
		for (int i = 0; i < 27; i++)
		{
			model = ringCentro;
			model = glm::translate(model, glm::vec3(-140.0f, 10.0f, -130.0f + (10 * i)));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_rejas.UseTexture();
			meshList[4]->RenderMesh();
		}

		// Derecha
		for (int i = 0; i < 27; i++)
		{
			model = ringCentro;
			model = glm::translate(model, glm::vec3(140.0f, 10.0f, -130.0f + (10 * i)));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_rejas.UseTexture();
			meshList[4]->RenderMesh();
		}

		// En frente derecha
		for (int i = 0; i < 10; i++)
		{
			model = ringCentro;
			model = glm::translate(model, glm::vec3(40.0f + (10 * i), 10.0f, 140.0f));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_rejas.UseTexture();
			meshList[4]->RenderMesh();
		}

		// En frente izquierda
		for (int i = 0; i < 10; i++)
		{
			model = ringCentro;
			model = glm::translate(model, glm::vec3(-40.0f - (10 * i), 10.0f, 140.0f));
			model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
			model = glm::rotate(model, 90.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
			hk_rejas.UseTexture();
			meshList[4]->RenderMesh();
		}


		// ================================================================================ //
		//																					//
		//								TNT Crash Bandicoot									//
		//																					//
		// ================================================================================ //

		posTNT = glm::vec3(-100.0f, 0.0f, 100.0f);

		// Animación de la TNT
		if (!mainWindow.getTNT_Normal())
		{
			if (condandoTnt)
			{
				tiempoAcumuladoTnt += 0.1f + deltaTime;
				if (tiempoAcumuladoTnt >= 50.0f)
				{
					toffsettntv -= 0.20f;
					if (toffsettntv <= 0.40f)
					{
						toffsettntv = 0.8f;
						condandoTnt = false;
						explotadoTnt = true;
					}
					tiempoAcumuladoTnt = 0.0f;
				}
			}

			if (explotadoTnt)
			{
				sizeTnt = 0.0f;

				tiempoAcumuladoExpTnt += 0.1f + deltaTime;
				if (tiempoAcumuladoExpTnt >= 5.0f)
				{
					toffsetexpu += 0.25f;
					if (toffsetexpu >= 1.0f)
					{
						toffsetexpu = 0.0f;
						toffsetexpv -= 0.5f;

						if (toffsetexpv <= 0.0f)
						{
							toffsetexpv = 1.0f;
							explotadoTnt = false;
						}
					}
					tiempoAcumuladoExpTnt = 0.0f;
				}


				model = ringCentro;
				model = glm::translate(model, posTNT + glm::vec3(0.0f, 5.0f, 0.0f));
				model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				toffset = glm::vec2(toffsetexpu, toffsetexpv);
				glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				cb_explosion.UseTexture();
				meshList[8]->RenderMesh();
				glDisable(GL_BLEND);

			}

			delayPortal += 0.1f * deltaTime;
			if (delayPortal >= 30.0f)
			{
				portalTnt = true;
				delayPortal = 0.0f;
			}


			if (portalTnt)
			{
				toffsettntu = 0.0f;
				toffsettntv = 1.0f;

				// Animación portal
				rotarPortal += 1.0f * deltaTime;
				if (rotarPortal >= 360.0f)
					rotarPortal = 0.0f;

				if (portalAbriendose)
				{
					sizePortal += 0.25f * deltaTime;
					if (sizePortal >= 25.0f)
					{
						sizePortal = 25.0f;
						portalAbriendose = false;
					}
				}

				delayPortal += 0.25f * deltaTime;
				if (delayPortal >= 30.0f && !portalAbriendose && !caidaPortal && !portalCerrando)
				{
					delayPortal = 0.0f;
					caidaPortal = true;
					tntY = 36.0f;
				}

				if (caidaPortal)
				{
					sizeTnt += 0.1f * deltaTime;
					if (sizeTnt >= 3.0f)
						sizeTnt = 3.0f;

					tntY -= 0.5f * deltaTime;
					if (tntY <= 0.0f)
					{
						tntY = 0.0f;
						caidaPortal = false;
						portalCerrando = true;
					}
				}

				if (portalCerrando)
				{
					sizePortal -= 0.5f * deltaTime;
					if (sizePortal <= 0.0f)
					{
						sizePortal = 0.0f;
						portalCerrando = false;
						portalTnt = false;
						resetPortal = true;
					}
				}


				model = ringCentro;
				model = glm::translate(model, posTNT + glm::vec3(0.0f, 35.0f, 0.0f));
				model = glm::rotate(model, rotarPortal * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
				model = glm::scale(model, glm::vec3(sizePortal, sizePortal, sizePortal));
				glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
				rm_portal.RenderModel();

			}

			if (resetPortal)
			{
				sizePortal = 0.0f;
				toffsettntu = 0.0f;
				toffsettntv = 1.0f;
				tiempoAcumuladoTnt = 0.0f;
				tiempoAcumuladoExpTnt = 0.0f;
				toffsetexpu = 0.0f;
				toffsetexpv = 1.0f;
				condandoTnt = true;
				resetPortal = false;
				portalAbriendose = true;
				mainWindow.setTNT_Normal();
				delayPortal = 0.0f;
			}

		}


		// TNT ------------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, posTNT + glm::vec3(0.0f, tntY, 0.0f));
		model = glm::scale(model, glm::vec3(sizeTnt, sizeTnt, sizeTnt));
		toffset = glm::vec2(toffsettntu, toffsettntv);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_tnt.RenderModel();

		// Polvo TNT --------------------------------------------------------
		model = ringCentro;
		model = glm::translate(model, posTNT);
		model = glm::scale(model, glm::vec3(6.0f, 6.0f, 6.0f));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		toffset = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cb_explosion.UseTexture();
		meshList[9]->RenderMesh();
		glDisable(GL_BLEND);


		// ================================================================================ //

		

		glDisable(GL_BLEND);
		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}

