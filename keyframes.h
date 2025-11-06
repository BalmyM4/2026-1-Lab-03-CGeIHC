#ifndef KEYFRAMES_H
#define KEYFRAMES_H

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

#include <string>


#define MAX_FRAMES 100

// ===== Estructura de un frame =====
typedef struct _frame {
    float mov_x, mov_y, mov_z;
    float mov_xInc, mov_yInc, mov_zInc;
    float giro, giroInc;
} FRAME;

// ===== Variables globales =====
/*extern FRAME KeyFrame[MAX_FRAMES];
extern int FrameIndex;
extern int i_max_steps;
extern int i_curr_steps;*/
extern bool play;
extern int playIndex;

// ===== Funciones =====
void saveFrame(FRAME* KeyFrame, int& FrameIndex, float& mov_x, float& mov_y, float& mov_z, float& giro);
void resetElements(FRAME* KeyFrame, float& mov_x, float& mov_y, float& mov_z, float& giro);
void interpolation(FRAME* KeyFrame, int playIndex, int i_max_steps);
void animate(FRAME* KeyFrame, int& playIndex, int& i_curr_steps, int i_max_steps, int FrameIndex, float& mov_x, float& mov_y, float& mov_z, float& giro);
void CargarKeyframesDesdeArchivo(const char* fileLocation, float& mov_x, float& mov_y, float& mov_z, float& giro, FRAME* KeyFrame, int& FrameIndex);
void AgregarKeyframeEnArchivo(const char* fileLocation, float x, float y, float z, float giro);
void inputKeyframes(FRAME* KeyFrame, bool* keys, float& mov_x, float& mov_y, float& mov_z, float& giro);

#endif
