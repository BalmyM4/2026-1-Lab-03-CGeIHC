#include "Keyframes.h"
#include "Shader_light.h" 

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
int i_max_steps = 100;
int i_curr_steps = 0;
bool play = false;
int playIndex = 0;

float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

void AgregarKeyframeEnArchivo(const char* fileLocation, float x, float y, float z, float giro)
{
	std::ofstream fileStream(fileLocation, std::ios::app);

	if (!fileStream.is_open()) {
		printf("Error: No se pudo abrir el archivo %s para agregar un keyframe.\n", fileLocation);
		return;
	}

	// Escribe los valores
	fileStream << std::fixed << std::setprecision(1)
		<< x << " " << y << " " << z << " " << giro << "\n";

	fileStream.close();
	printf("Keyframe agregado al archivo: (%.1f, %.1f, %.1f, %.1f)\n", x, y, z, giro);
}

void saveFrame(FRAME* KeyFrame, int& FrameIndex, float& mov_x, float& mov_y, float& mov_z, float& giro) //tecla L
{
	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].mov_x = mov_x;
	KeyFrame[FrameIndex].mov_y = mov_y;
	KeyFrame[FrameIndex].mov_z = mov_z;
	KeyFrame[FrameIndex].giro = giro;

	// Guardar en el archivo de texto
	AgregarKeyframeEnArchivo("keyframes_.txt", mov_x, mov_y, mov_z, giro);

	FrameIndex++;
}

void resetElements(FRAME* KeyFrame, float& mov_x, float& mov_y, float& mov_z, float& giro) //Tecla 0
{
	mov_x = KeyFrame[0].mov_x;
	mov_y = KeyFrame[0].mov_y;
	mov_z = KeyFrame[0].mov_z;
	giro = KeyFrame[0].giro;
}

void interpolation(FRAME* KeyFrame, int playIndex, int i_max_steps)
{
	KeyFrame[playIndex].mov_xInc = (KeyFrame[playIndex + 1].mov_x - KeyFrame[playIndex].mov_x) / i_max_steps;
	KeyFrame[playIndex].mov_yInc = (KeyFrame[playIndex + 1].mov_y - KeyFrame[playIndex].mov_y) / i_max_steps;
	KeyFrame[playIndex].mov_zInc = (KeyFrame[playIndex + 1].mov_z - KeyFrame[playIndex].mov_z) / i_max_steps;
	KeyFrame[playIndex].giroInc = (KeyFrame[playIndex + 1].giro - KeyFrame[playIndex].giro) / i_max_steps;
}

/*
void animate(void)
{
	//Movimiento del objeto con barra espaciadora
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //fin de animación entre frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//Fin de toda la animación con último frame?
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termino la animacion\n");
				playIndex = 0;
				//play = false;
			}
			else Interpolación del próximo cuadro
			{

				i_curr_steps = 0; //Resetea contador
				//Interpolar
				interpolation();
			}
		}
		else
		{
			//Dibujar Animación
			mov_x += KeyFrame[playIndex].mov_xInc;
			mov_y += KeyFrame[playIndex].mov_yInc;
			mov_z += KeyFrame[playIndex].mov_zInc;
			giro += KeyFrame[playIndex].giroInc;
			i_curr_steps++;
		}

	}
}*/

void animate(FRAME* KeyFrame, int& playIndex, int& i_curr_steps, int i_max_steps, int FrameIndex, float& mov_x, float& mov_y, float& mov_z, float& giro)
{
	if (play)
	{
		if (i_curr_steps >= i_max_steps) // fin de animación entre frames
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	// llegó al último frame
			{
				playIndex = 0; // reinicia desde el primer keyframe
			}

			i_curr_steps = 0; // resetea contador
			interpolation(KeyFrame, playIndex, i_max_steps);  // calcula incrementos del nuevo tramo
		}
		else
		{
			// interpolar movimiento
			mov_x += KeyFrame[playIndex].mov_xInc;
			mov_y += KeyFrame[playIndex].mov_yInc;
			mov_z += KeyFrame[playIndex].mov_zInc;
			giro += KeyFrame[playIndex].giroInc;
			i_curr_steps++;
		}
	}
}

void CargarKeyframesDesdeArchivo(const char* fileLocation, float& mov_x, float& mov_y, float& mov_z, float& giro, FRAME* KeyFrame, int& FrameIndex)
{
	Shader shader;
	std::string data = shader.ReadFile(fileLocation);

	if (data.empty()) {
		printf("No se pudieron cargar los keyframes desde %s\n", fileLocation);
		return;
	}

	std::istringstream stream(data);
	std::string line;
	int frameCount = 0;

	// Leer línea por línea
	while (std::getline(stream, line))
	{
		// Saltar encabezado
		if (line.empty() || line[0] == '#') continue;
		if (line.find("movAvion") != std::string::npos) continue;

		std::istringstream linestream(line);
		float x, y, z, giro;

		if (linestream >> x >> y >> z >> giro)
		{
			KeyFrame[frameCount].mov_x = x;
			KeyFrame[frameCount].mov_y = y;
			KeyFrame[frameCount].mov_z = z;
			KeyFrame[frameCount].giro = giro;
			frameCount++;
		}
	}

	FrameIndex = frameCount;
	printf("Se cargaron %d keyframes desde %s\n", frameCount, fileLocation);

	if (FrameIndex > 1) {
		resetElements(KeyFrame, mov_x, mov_y, mov_z, giro);
		interpolation(KeyFrame, playIndex, i_max_steps);
		play = true;
		playIndex = 0;
		i_curr_steps = 0;
	}
}

void inputKeyframes(FRAME* KeyFrame, bool* keys, float& mov_x, float& mov_y, float& mov_z, float& giro)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements(KeyFrame, mov_x, mov_y, mov_z, giro);
				//First Interpolation				
				interpolation(KeyFrame, playIndex, i_max_steps);
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("\n presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;
			}
			else
			{
				play = false;

			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1 && reproduciranimacion>0)
		{
			printf("Ya puedes reproducir de nuevo la animación con la tecla de barra espaciadora'\n");
			reproduciranimacion = 0;

		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame(KeyFrame, FrameIndex, mov_x, mov_y, mov_z, giro);
			printf("mov_x es: %f\n", mov_x);
			printf("mov_y es: %f\n", mov_y);
			printf("mov_z es: %f\n", mov_z);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
			reinicioFrame = 1;
			printf("Ya puedes guardar otro frame presionando la tecla L'\n");
		}
	}

	// Para Movimiento X (tecla 1 y 2 mueve, tecla 2 habilita)
	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("mov_x es: %f\n", mov_x);
			mov_x += 10.0f;
			printf("\n mov_x es: %f\n", mov_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}
	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo < 1)
		{
			//printf("mov_x es: %f\n", mov_x);
			mov_x -= 10.0f;
			printf("\n mov_x es: %f\n", mov_x);
			ciclo++;
			ciclo2 = 0;
			printf("\n Presiona la tecla 2 para poder habilitar la variable\n");
		}

	}
	if (keys[GLFW_KEY_3])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
			ciclo2++;
			printf("\n Ya puedes modificar tu variable presionando la tecla 1\n");
		}
	}

	// ================= MOVIMIENTO EN Y =================
	static bool cy1 = false, cy2 = false;
	if (keys[GLFW_KEY_4]) // Mover +Y
	{
		if (!cy1)
		{
			mov_y += 10.0f;
			printf("\nmov_y: %.2f (+Y)\n", mov_y);
			cy1 = true; cy2 = false;
			printf("Presiona 6 para desbloquear el eje Y\n");
		}
	}
	if (keys[GLFW_KEY_5]) // Mover -Y
	{
		if (!cy1)
		{
			mov_y -= 10.0f;
			printf("\nmov_y: %.2f (-Y)\n", mov_y);
			cy1 = true; cy2 = false;
			printf("Presiona 6 para desbloquear el eje Y\n");
		}
	}
	if (keys[GLFW_KEY_6]) // Desbloquear eje Y
	{
		if (!cy2)
		{
			cy1 = false; cy2 = true;
			printf("Eje Y desbloqueado, puedes volver a mover con 4 (+Y) o 5 (-Y)\n");
		}
	}

	// ================= MOVIMIENTO EN Z =================
	static bool cz1 = false, cz2 = false;
	if (keys[GLFW_KEY_7]) // Mover +Z
	{
		if (!cz1)
		{
			mov_z += 10.0f;
			printf("\nmov_z: %.2f (+Z)\n", mov_z);
			cz1 = true; cz2 = false;
			printf("Presiona 9 para desbloquear el eje Z\n");
		}
	}
	if (keys[GLFW_KEY_8]) // Mover -Z
	{
		if (!cz1)
		{
			mov_z -= 10.0f;
			printf("\nmov_z: %.2f (-Z)\n", mov_z);
			cz1 = true; cz2 = false;
			printf("Presiona 9 para desbloquear el eje Z\n");
		}
	}
	if (keys[GLFW_KEY_9]) // Desbloquear eje Z
	{
		if (!cz2)
		{
			cz1 = false; cz2 = true;
			printf("Eje Z desbloqueado, puedes volver a mover con 7 (+Z) o 8 (-Z)\n");
		}
	}


	// ================= ROTACIÓN EN EJE Y =================
	static bool giroBloqueado = false;
	float pasoRotacion = 20.0f; // grados por paso

	// Rotar a la izquierda (Q)
	if (keys[GLFW_KEY_Q])
	{
		if (!giroBloqueado)
		{
			giro -= pasoRotacion;
			if (giro < 0.0f) giro += 360.0f;
			printf("\nGiro: %.2f grados (rotacion -Y)\n", giro);
			giroBloqueado = true;
			printf("Rotacion bloqueada. Presiona R para volver a habilitar.\n");
		}
	}

	// Rotar a la derecha (E)
	if (keys[GLFW_KEY_E])
	{
		if (!giroBloqueado)
		{
			giro += pasoRotacion;
			if (giro > 360.0f) giro -= 360.0f;
			printf("\nGiro: %.2f grados (rotacion +Y)\n", giro);
			giroBloqueado = true;
			printf("Rotacion bloqueada. Presiona R para volver a habilitar.\n");
		}
	}

	// Rehabilitar rotación (R)
	if (keys[GLFW_KEY_R])
	{
		if (giroBloqueado)
		{
			giroBloqueado = false;
			printf("Rotacion habilitada nuevamente. Puedes usar Q o E.\n");
		}
	}

}