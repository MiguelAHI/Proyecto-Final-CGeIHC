/*
COMPUTACIÓN GRÁFICA E INTERACCIÓN HUMANO-COMPUTADORA
PROYECTO FINAL: FERIA DE PUEBLO
mayo 2019
*/
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_access.hpp>
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh_texturizado.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"

// Iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Material.h"

#include"Model.h"
#include "Skybox.h"
#include"SpotLight.h"

// Sonido
#include<iostream>
#include<stdio.h>
#include<irrKlang.h>
using namespace irrklang;

const float toRadians = 3.14159265f / 180.0f;
float movCoche;
float movOffset;
bool avanza,patoadelante;
float giraRueda;
//float posXDelfin = 0.0f, posYDelfin = 0.0f, posZDelfin = 0.0f;
//float movDelfin_x = 0.05f, movDelfin_z = 0.05f, movDelfin_y = 0.05f;
//bool play = false;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

float reproduciranimacion,habilitaranimacion, guardoFrame,reinicioFrame,ciclo,ciclo2,contador=0;

Texture dirtTexture;
Texture plainTexture;
Texture dadoTexture;
Texture pisoTexture;
//Texturas para la casa del terror
Texture fachada;
Texture cuadro1;
Texture cuadro2;
Texture cuadro3;
Texture cuadro4;
Texture cuadro5;
Texture roca;
Texture marmolTexture;
Texture metal1;
Texture metal5;
Texture metal6;
Texture metal7; 
Texture metal8;

// Materiales
Material Material_brillante;
Material Material_opaco;

// Luz direccional
DirectionalLight mainLight;

// Declaración de varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

//movimiento de la cabina del kilauea
float mov_cabina=-2.0;
bool arriba=1, abajo=0;

bool gameCameraFlag = false;
float horseMovementOne = 0.2f;
float horseMovementTwo = 0.25f;
float horseMovementThree = 0.3f;
float horseMovementFour = 0.35f;
bool horseMovOneFlag = true;
bool horseMovTwoFlag = true;
bool horseMovThreeFlag = true;
bool horseMovFourFlag = true;

Model Barandal;
Model Rueda;
Model EjeRueda;
Model Estructura;
Model Escalera;
Model Medusa;
Model Pat;
Model Can;
Model Cal;
Model Rot;
Model Arbol;
Model Banca;
Model Caballo;
Model Elefante;
Model Barda;
Model CarruselBase;
Model BaseGiratoriaCarrusel;
Model ToldoCarrusel;
Model MetalPipe;
Model Cajon;
Model Puesto;
Model Mesa;
Model Pato;
Model Coca;
//Model Pistola;
Model Rifle;
Model fig1;
Model Botella;
Model Peluches;
Model Peluches2;
Model chango;
Model base_chan;
Model souvenirs; 
Model guanteIZQ;
Model guanteDER;
Model cajon_v;
Model mountain;
Model puestoComida;
Model Carro;
Model Kilauea;
Model Cabinas;
//Casa terror modelos
Model Casa;
Model Skeleto;
Model Skeleto2;
Model Cerca;
Model Tumba;

Model Aqua;
Model Agua;
Model estDelfin;
Model delfin;

Model chocones;
Model bumper;

//Skybox skybox;

Skybox skybox, skybox1, skybox2, skybox3, skybox4, skybox5, skybox6, skybox7, skybox8, skybox9, skybox10, skybox11,skybox12, skybox13;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

//Casa terror variables
float movSkeleto = 0.0f;
int controlSkeleto = 0;

float giroSkeleto = 0.0f;
int controlGiro = 0;

//void my_input(GLFWwindow *window);
void inputKeyframes(bool* keys);

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";

void CreateObjects() 
{
	unsigned int indices[] = {		
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2 //12
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
		1, 2, 3 //18
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
		4, 5, 6,
		4, 6, 7 //30
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

	unsigned int casaIndices[] = {
		0, 2, 1,
		1, 2, 3 //36
	};

	GLfloat casaVertices[] = {
		-1.0f, 0.0f, -1.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, -1.0f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 1.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f
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

	Mesh *obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh *casa = new Mesh();
	casa->CreateMesh(casaVertices, casaIndices, 32, 6);
	meshList.push_back(casa);

}

void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// bottom
		16, 17, 18,
		18, 19, 16,

		// top
		20, 21, 22,
		22, 23, 20,
		
		// left
		12, 13, 14,
		14, 15, 12,
		
		// right
		4, 5, 6,
		6, 7, 4,
	
		// back
		8, 9, 10,
		10, 11, 8,
		
		// front
		0, 1, 2,
		2, 3, 0,
	};
	
	// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.47f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.47f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.5f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.75f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.75f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.50f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.75f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.9999f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.9999f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.75f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.01f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.24f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.24f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.01f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.5f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.75f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.75f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.5f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.5f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.75f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.75f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.5f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};

	unsigned int cubo2_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	
	GLfloat cubo2_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.27f,  0.35f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		0.48f,	0.35f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		0.48f,	0.64f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.27f,	0.64f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.52f,  0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	0.73f,	0.35f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	0.73f,	0.64f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.52f,	0.64f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	0.77f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.98f,	0.35f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.98f,	0.64f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	0.77f,	0.64f,		0.0f,	0.0f,	1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	0.0f,	0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.23f,  0.35f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.23f,	0.64f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	0.0f,	0.64f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	0.27f,	0.02f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.48f,  0.02f,		0.0f,	1.0f,	0.0f,
		 0.5f,  -0.5f,  -0.5f,	0.48f,	0.31f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	0.27f,	0.31f,		0.0f,	1.0f,	0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.27f,	0.68f,		0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	0.48f,  0.68f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	0.48f,	0.98f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.27f,	0.98f,		0.0f,	-1.0f,	0.0f,

	};

	//base casa terror
	Mesh *base = new Mesh();
	base->CreateMesh(cubo2_vertices, cubo2_indices, 160, 30);
	meshList.push_back(base);

	
	Mesh *cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(cubo);
}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

///////////////////////////////KEYFRAMES/////////////////////

bool animacion = false;

//NEW// Keyframes
float posXPato = 0.12, posYPato = 0.75, posZPato = 2.0;
float	movPato_x = 0.0f, movPato_y = 0.0f, movPato_z = 0.0f;
float giroPato = 0;
float caidaPato = 0, patoChico = 1.0;

#define MAX_FRAMES 14
int i_max_steps = 90;  //PARA SUAVISAR TRANSICIONES ENTRE CUADROS. 
int i_curr_steps = 5;  //
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movPato_x;		//Variable para PosicionX
	float movPato_y;		//Variable para PosicionY
	float movPato_z;
	float movPato_xInc;		//Variable para IncrementoX
	float movPato_yInc;		//Variable para IncrementoY, SIEMPRE DEBE EXISTIR EL INCREMENTO PUES ESTA VA A GUARDAR, LA DIFERENCIA 
	float movPato_zInc;
	float giroPato;			//ENTRE EL ANTERIOR Y EL SIGUIENTE PARA HACER LA INTERPOLACI�N.
	float giroPatoInc;
	float caidaPato;
	float caidaPatoInc;
	float patoChico;
	float patoChicoInc;

	//float movDelfin_x;		
	//float movDelfin_xInc;
	//float movDelfin_y;
	//float movDelfin_yInc;
	//float movDelfin_z;
	//float movDelfin_zInc;
}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 14;			//introducir datos
bool play = false;			
int playIndex = 0;

void saveFrame(void) //GUARDA EL FRAME CON L
{

	printf("frameindex %d\n", FrameIndex);


	KeyFrame[FrameIndex].movPato_x = movPato_x;
	KeyFrame[FrameIndex].movPato_y = movPato_y;
	KeyFrame[FrameIndex].movPato_z = movPato_z;
	KeyFrame[FrameIndex].giroPato = giroPato;
	KeyFrame[FrameIndex].caidaPato = caidaPato;
	KeyFrame[FrameIndex].patoChico = patoChico;

	FrameIndex++;
}

void resetElements(void)
{
	
	movPato_x = KeyFrame[0].movPato_x;
	movPato_y = KeyFrame[0].movPato_y;
	movPato_z = KeyFrame[0].movPato_z;
	giroPato= KeyFrame[0].giroPato;
	caidaPato = KeyFrame[0].caidaPato;
	patoChico = KeyFrame[0].patoChico;
}

void interpolation(void)
{
	//LA ANIMACIÓN SE HACE POR TRANSFORMACIONES
	KeyFrame[playIndex].movPato_xInc = (KeyFrame[playIndex + 1].movPato_x - KeyFrame[playIndex].movPato_x) / i_max_steps;
	KeyFrame[playIndex].movPato_yInc = (KeyFrame[playIndex + 1].movPato_y - KeyFrame[playIndex].movPato_y) / i_max_steps;
	KeyFrame[playIndex].movPato_zInc = (KeyFrame[playIndex + 1].movPato_z - KeyFrame[playIndex].movPato_z) / i_max_steps;
	KeyFrame[playIndex].giroPatoInc  = (KeyFrame[playIndex + 1].giroPato - KeyFrame[playIndex].giroPato) / i_max_steps;
	KeyFrame[playIndex].caidaPatoInc = (KeyFrame[playIndex + 1].caidaPato - KeyFrame[playIndex].caidaPato) / i_max_steps;
	KeyFrame[playIndex].patoChicoInc = (KeyFrame[playIndex + 1].patoChico - KeyFrame[playIndex].patoChico) / i_max_steps;

}

void animate(void)
{
	//Movimiento del objeto
	if (play)
	{	
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("playindex : %d\n", playIndex);
			if (playIndex > FrameIndex - 2)	//end of total animation
			{
				printf("Frame index= %d\n", FrameIndex);
				printf("termina anim\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			movPato_x += KeyFrame[playIndex].movPato_xInc;
			movPato_y += KeyFrame[playIndex].movPato_yInc;
			movPato_z += KeyFrame[playIndex].movPato_zInc;
			giroPato += KeyFrame[playIndex].giroPatoInc;
			caidaPato += KeyFrame[playIndex].caidaPatoInc;
			patoChico += KeyFrame[playIndex].patoChicoInc;
			i_curr_steps++;
		}
	}
}

/* FIN KEYFRAMES*/

int main() 
{
	/******************** Para auidio en 2D ****************/
	ISoundEngine* audio = createIrrKlangDevice();

	//audio->play2D("audio/SpongeBob Production Music Stadium Rave A.mp3", true);

	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CrearCubo();
	CreateShaders();
	
	// Initial value of default camera
	camera = Camera(glm::vec3(42.0f, 0.0f, 60.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);

	dirtTexture = Texture("Textures/metal.tga");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/fondoBdw.tga");
	plainTexture.LoadTextureA();
	dadoTexture = Texture("Textures/dado6.tga");
	dadoTexture.LoadTextureA();
	fachada = Texture("Textures/casa.tga");
	fachada.LoadTextureA();
	cuadro1 = Texture("Textures/cuadro1.jpg");
	cuadro1.LoadTexture();
	cuadro2 = Texture("Textures/cuadro2.jpg");
	cuadro2.LoadTexture();
	cuadro3 = Texture("Textures/cuadro3.jpg");
	cuadro3.LoadTexture();
	cuadro4 = Texture("Textures/cuadro4.jpg");
	cuadro4.LoadTexture();
	cuadro5 = Texture("Textures/cuadro5.jpg");
	cuadro5.LoadTexture();
	roca = Texture("Textures/roca.png");
	roca.LoadTexture();
	marmolTexture = Texture("Textures/marmol.jpg");
	marmolTexture.LoadTexture();
	metal1 = Texture("Textures/METAL1.jpg");
	metal1.LoadTexture();
	metal5 = Texture("Textures/METAL5.jpg");
	metal5.LoadTexture();
	metal6 = Texture("Textures/METAL6.jpg");
	metal6.LoadTexture();
	metal7 = Texture("Textures/METAL7.jpg");
	metal7.LoadTexture();
	metal8 = Texture("Textures/METAL8.jpg");
	metal8.LoadTexture();

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);

	Barandal = Model();
	Barandal.LoadModel("Models/Barriere Balcon SH3D.obj");
	Rueda = Model();
	Rueda.LoadModel("Models/CircleSquareTruss_150cm_3ds.3DS");
	EjeRueda = Model();
	EjeRueda.LoadModel("Models/Senza Titolo 2.obj");
	Estructura = Model();
	Estructura.LoadModel("Models/SquareTrussStraightSegment_21_Stl.STL");
	Escalera = Model();
	Escalera.LoadModel("Models/objStairs.obj");
	Medusa = Model();
	Medusa.LoadModel("Models/Jellyfish.obj");
	Pat = Model();
	Pat.LoadModel("Models/Patrick.obj");
	Can = Model();
	Can.LoadModel("Models/cangrebur.FBX");

	Rot = Model();
	Rot.LoadModel("Models/untitled.obj");
	Arbol = Model();
	Arbol.LoadModel("Models/Tree.obj");
	Banca = Model();
	Banca.LoadModel("Models/ConcreteBench-L3.obj");
	Caballo = Model();
	Caballo.LoadModel("Models/10026_Horse_v01-it2.obj");
	Elefante = Model();
	Elefante.LoadModel("Models/elefante.obj");
	Barda = Model();
	Barda.LoadModel("Models/barda.obj");
	CarruselBase = Model();
	CarruselBase.LoadModel("Models/carruselBase.obj");
	BaseGiratoriaCarrusel = Model();
	BaseGiratoriaCarrusel.LoadModel("Models/baseGiro.obj");
	ToldoCarrusel = Model();
	ToldoCarrusel.LoadModel("Models/toldoCarrusel.obj");
	MetalPipe = Model();
	MetalPipe.LoadModel("Models/metalPipe.obj");
	Cajon = Model();
	Cajon.LoadModel("Models/cajon_figuras.obj");
	Puesto = Model();
	Puesto.LoadModel("Models/PUESTO.obj");
	Mesa = Model();
	Mesa.LoadModel("Models/MESA.obj");
	Pato = Model();
	Pato.LoadModel("Models/Pato.obj");

	fig1 = Model();
	fig1.LoadModel("Models/fig1.obj");
	Botella = Model();
	Botella.LoadModel("Models/botella.obj");
	Peluches = Model();
	Peluches.LoadModel("Models/Peluches1.obj");
	Peluches2 = Model();
	Peluches2.LoadModel("Models/Peluches2.obj");
	chango = Model();
	chango.LoadModel("Models/chango.obj");
	base_chan = Model();
	base_chan.LoadModel("Models/base.obj");
	souvenirs = Model();
	souvenirs.LoadModel("Models/tienda.obj");
	cajon_v = Model();
	cajon_v.LoadModel("Models/cajon_v.obj");
	guanteDER = Model();
	guanteDER.LoadModel("Models/guanteDER.obj");
	guanteIZQ = Model();
	guanteIZQ.LoadModel("Models/guanteIZQ.obj");
	mountain = Model();
	mountain.LoadModel("Models/MOUNTAIN2.obj");
	puestoComida = Model();
	puestoComida.LoadModel("Models/city_stall.obj");
	Coca = Model();
	Coca.LoadModel("Models/cup OBJ.obj");
	Kilauea = Model();
	Kilauea.LoadModel("Models/basek.obj");
	Cabinas = Model();
	Cabinas.LoadModel("Models/cabina.obj");

	Casa = Model();
	Casa.LoadModel("Models/OBJ_Church.obj");
	Skeleto = Model();
	Skeleto.LoadModel("Models/skeleton.obj");
	Skeleto2 = Model();
	Skeleto2.LoadModel("Models/Obj_Sculptris.obj");
	Cerca = Model();
	Cerca.LoadModel("Models/Old Fence.obj");
	Tumba = Model();
	Tumba.LoadModel("Models/ObjTomb.obj");
	//
	Aqua = Model();
	Aqua.LoadModel("Models/aqua.obj");
	Agua = Model();
	Agua.LoadModel("Models/agua.obj");
	estDelfin = Model();
	estDelfin.LoadModel("Models/estDelfin.obj");
	delfin = Model();
	delfin.LoadModel("Models/DOLPHIN.obj");

	chocones = Model();
	chocones.LoadModel("Models/chocones.obj");
	bumper= Model();
	bumper.LoadModel("Models/bumper.obj");

	int dia = 0;
	
	// Luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.0f, 0.0f, -1.0f);
	
	// Contador de luces puntuales
	unsigned int pointLightCount = 0;
	
	// Declaración de luz puntual
	pointLights[0] = PointLight();
	pointLightCount++;

	pointLights[1] = PointLight();
	pointLightCount++;

	pointLights[2] = PointLight();
	pointLightCount++;
	
	unsigned int spotLightCount = 0;
	//linterna
	/*spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f);
	spotLightCount++;*/

	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		46.0f, 5.0f, 2.0f,
		0.0f, -4.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		40.0f);
	spotLightCount++;

		spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		46.0f, 6.5f, 5.0f,
		0.0f, -4.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		30.0f);
	spotLightCount++;



	glm::vec3 posPatote = glm::vec3(2.0f, 0.0f, 0.0f);

	std::vector<std::string> skyboxFaces1;
		skyboxFaces1.push_back("Textures/Skybox/1right.tga");
		skyboxFaces1.push_back("Textures/Skybox/1left.tga");
		skyboxFaces1.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces1.push_back("Textures/Skybox/1up.tga");
		skyboxFaces1.push_back("Textures/Skybox/1back.tga");
		skyboxFaces1.push_back("Textures/Skybox/1front.tga");
		skybox1 = Skybox(skyboxFaces1);
		
		std::vector<std::string> skyboxFaces2;
		skyboxFaces2.push_back("Textures/Skybox/2rt.tga");
		skyboxFaces2.push_back("Textures/Skybox/2left.tga");
		skyboxFaces2.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces2.push_back("Textures/Skybox/2up.tga");
		skyboxFaces2.push_back("Textures/Skybox/2back.tga");
		skyboxFaces2.push_back("Textures/Skybox/2ft.tga");
		skybox2 = Skybox(skyboxFaces2);
	
		std::vector<std::string> skyboxFaces3;
		skyboxFaces3.push_back("Textures/Skybox/3rt.tga");
		skyboxFaces3.push_back("Textures/Skybox/3lf.tga");
		skyboxFaces3.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces3.push_back("Textures/Skybox/3up.tga");
		skyboxFaces3.push_back("Textures/Skybox/3bk.tga");
		skyboxFaces3.push_back("Textures/Skybox/3ft.tga");
		skybox3 = Skybox(skyboxFaces3);		
	
		std::vector<std::string> skyboxFaces4;
		skyboxFaces4.push_back("Textures/Skybox/4rt.tga");
		skyboxFaces4.push_back("Textures/Skybox/4lf.tga");
		skyboxFaces4.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces4.push_back("Textures/Skybox/4up.tga");
		skyboxFaces4.push_back("Textures/Skybox/4bk.tga");
		skyboxFaces4.push_back("Textures/Skybox/4ft.tga");
		skybox4 = Skybox(skyboxFaces4);
	
		std::vector<std::string> skyboxFaces5;
		skyboxFaces5.push_back("Textures/Skybox/5rt.tga");
		skyboxFaces5.push_back("Textures/Skybox/5lf.tga");
		skyboxFaces5.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces5.push_back("Textures/Skybox/5up.tga");
		skyboxFaces5.push_back("Textures/Skybox/5bk.tga");
		skyboxFaces5.push_back("Textures/Skybox/5ft.tga");
		skybox5 = Skybox(skyboxFaces5);
	
		std::vector<std::string> skyboxFaces6;
		skyboxFaces6.push_back("Textures/Skybox/7rt.tga");
		skyboxFaces6.push_back("Textures/Skybox/7lt.tga");
		skyboxFaces6.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces6.push_back("Textures/Skybox/7up.tga");
		skyboxFaces6.push_back("Textures/Skybox/7bk.tga");
		skyboxFaces6.push_back("Textures/Skybox/7ft.tga");
		skybox6 = Skybox(skyboxFaces6);

		std::vector<std::string> skyboxFaces7;
		skyboxFaces7.push_back("Textures/Skybox/fondoBrt.tga");
		skyboxFaces7.push_back("Textures/Skybox/fondoBlf.tga");
		skyboxFaces7.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces7.push_back("Textures/Skybox/fondoBup.tga");
		skyboxFaces7.push_back("Textures/Skybox/fondoBbk.tga");
		skyboxFaces7.push_back("Textures/Skybox/fondoBft.tga");
		skybox7 = Skybox(skyboxFaces7);
	
		std::vector<std::string> skyboxFaces8;
		skyboxFaces8.push_back("Textures/Skybox/9rt.tga");
		skyboxFaces8.push_back("Textures/Skybox/9lt.tga");
		skyboxFaces8.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces8.push_back("Textures/Skybox/9up.tga");
		skyboxFaces8.push_back("Textures/Skybox/9bk.tga");
		skyboxFaces8.push_back("Textures/Skybox/9ft.tga");
		skybox8 = Skybox(skyboxFaces8);
		
		std::vector<std::string> skyboxFaces9;
		skyboxFaces9.push_back("Textures/Skybox/10rt.tga");
		skyboxFaces9.push_back("Textures/Skybox/10lt.tga");
		skyboxFaces9.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces9.push_back("Textures/Skybox/10up.tga");
		skyboxFaces9.push_back("Textures/Skybox/10bc.tga");
		skyboxFaces9.push_back("Textures/Skybox/10ft.tga");
		skybox9 = Skybox(skyboxFaces9);
	
		std::vector<std::string> skyboxFaces10;
		skyboxFaces10.push_back("Textures/Skybox/11rt.tga");
		skyboxFaces10.push_back("Textures/Skybox/11lt.tga");
		skyboxFaces10.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces10.push_back("Textures/Skybox/11up.tga");
		skyboxFaces10.push_back("Textures/Skybox/11bk.tga");
		skyboxFaces10.push_back("Textures/Skybox/11ft.tga");
		skybox10 = Skybox(skyboxFaces10);
	
		std::vector<std::string> skyboxFaces11;
		skyboxFaces11.push_back("Textures/Skybox/12rt.tga");
		skyboxFaces11.push_back("Textures/Skybox/12lt.tga");
		skyboxFaces11.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces11.push_back("Textures/Skybox/12up.tga");
		skyboxFaces11.push_back("Textures/Skybox/12bk.tga");
		skyboxFaces11.push_back("Textures/Skybox/12ft.tga");
		skybox11 = Skybox(skyboxFaces11);
		
		std::vector<std::string> skyboxFaces12;
		skyboxFaces12.push_back("Textures/Skybox/13rt.tga");
		skyboxFaces12.push_back("Textures/Skybox/13lt.tga");
		skyboxFaces12.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces12.push_back("Textures/Skybox/13up.tga");
		skyboxFaces12.push_back("Textures/Skybox/13bk.tga");
		skyboxFaces12.push_back("Textures/Skybox/13ft.tga");
		skybox12 = Skybox(skyboxFaces12);
		
		std::vector<std::string> skyboxFaces13;
		skyboxFaces13.push_back("Textures/Skybox/14rt.tga");
		skyboxFaces13.push_back("Textures/Skybox/14lt.tga");
		skyboxFaces13.push_back("Textures/Skybox/fondoBdw.tga");
		skyboxFaces13.push_back("Textures/Skybox/14up.tga");
		skyboxFaces13.push_back("Textures/Skybox/14bk.tga");
		skyboxFaces13.push_back("Textures/Skybox/14ft.tga");
		skybox13 = Skybox(skyboxFaces13);

	//skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformOffTex = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 300.0f);
	
	movCoche = 0.0f;
	movOffset = 1.0f;
	avanza = 0;
	giraRueda = 1;

	int bandera = 0;
	int bandera2 = 0;
	int bandera3 = 0;

	float fpx = -2.0f;

	float fc1 = 1.5f;
	float fc2 = 0.4f;
	float fc3 = -0.6f;
	float fc4 = -1.7f;
	float fc5 = -2.7f;

	float fb1 = 2.0f;
	float fb2 = 1.0f;
	float fb3 = 0.0f;
	float fb4 = -1.0f;
	float fb5 = -2.0f;


	//KEYFRAMES DECLARADOS INICIALES
	KeyFrame[0].movPato_x = 0.0f;
	KeyFrame[0].movPato_y = 0.0f;
	KeyFrame[0].movPato_z = 0.0f;
	KeyFrame[0].giroPato = 0;
	KeyFrame[0].caidaPato = 0;
	KeyFrame[0].patoChico = 1.0;

	KeyFrame[1].movPato_x = 0.0f;
	KeyFrame[1].movPato_y = 0.02f;
	KeyFrame[1].movPato_z = -0.5f;
	KeyFrame[1].giroPato = 0;
	KeyFrame[1].caidaPato = 0;
	KeyFrame[1].patoChico = 1.0;

	KeyFrame[2].movPato_x = 0.0f;
	KeyFrame[2].movPato_y = -0.02f;
	KeyFrame[2].movPato_z = -1.0f;
	KeyFrame[2].giroPato = 0;
	KeyFrame[2].caidaPato = 0;
	KeyFrame[2].patoChico = 1.0;

	KeyFrame[3].movPato_x = 0.0f;
	KeyFrame[3].movPato_y = 0.02f;
	KeyFrame[3].movPato_z = -1.5;
	KeyFrame[3].giroPato = 0;
	KeyFrame[3].caidaPato = 0;
	KeyFrame[3].patoChico = 1.0;

	KeyFrame[4].movPato_x = 0.0f;
	KeyFrame[4].movPato_y = -0.02f;
	KeyFrame[4].movPato_z = -2.0f;
	KeyFrame[4].giroPato = 0.0f;
	KeyFrame[4].caidaPato = 0;
	KeyFrame[4].patoChico = 1.0;
	
	KeyFrame[5].movPato_x = 0.0f;
	KeyFrame[5].movPato_y = 0.02f;
	KeyFrame[5].movPato_z = -2.5f;
	KeyFrame[5].giroPato = 0.0f;
	KeyFrame[5].caidaPato = 0;
	KeyFrame[5].patoChico = 1.0;

	KeyFrame[6].movPato_x = 0.0f;
	KeyFrame[6].movPato_y = -0.02f;
	KeyFrame[6].movPato_z = -3.0f;
	KeyFrame[6].giroPato = 0.0f;
	KeyFrame[6].caidaPato = 0;
	KeyFrame[6].patoChico = 1.0;	

	KeyFrame[7].movPato_x = 0.0f;
	KeyFrame[7].movPato_y = 0.02f;
	KeyFrame[7].movPato_z = -3.5f;
	KeyFrame[7].giroPato = 0.0f;
	KeyFrame[7].caidaPato = 0;
	KeyFrame[7].patoChico = 1.0;	

	KeyFrame[8].movPato_x = 0.0f;
	KeyFrame[8].movPato_y = -0.02f;
	KeyFrame[8].movPato_z = -4.0f;
	KeyFrame[8].giroPato = 0.0f;
	KeyFrame[8].caidaPato = 0;
	KeyFrame[8].patoChico = 1.0;	

	KeyFrame[9].movPato_x = 0.0f;
	KeyFrame[9].movPato_y = -0.02f;
	KeyFrame[9].movPato_z = -4.0f;
	KeyFrame[9].giroPato = 180.0f;
	KeyFrame[9].caidaPato = 0;
	KeyFrame[9].patoChico = 1.0;	

	KeyFrame[10].movPato_x = 0.0f;
	KeyFrame[10].movPato_y = 0.0f;
	KeyFrame[10].movPato_z = 0.0f;
	KeyFrame[10].giroPato = 180.0f;
	KeyFrame[10].caidaPato = 0;
	KeyFrame[10].patoChico = 1.0;	

	KeyFrame[11].movPato_x = 0.0f;
	KeyFrame[11].movPato_y = 0.0f;
	KeyFrame[11].movPato_z = 0.0f;
	KeyFrame[11].giroPato = 0.0f;
	KeyFrame[11].caidaPato = 0;
	KeyFrame[11].patoChico = 1.0;

	KeyFrame[12].movPato_x = -0.05;
	KeyFrame[12].movPato_y = 0.1f;
	KeyFrame[12].movPato_z = 0.0f;
	KeyFrame[12].giroPato = 0.0f;
	KeyFrame[12].caidaPato = -90;
	KeyFrame[12].patoChico = 0.3;

	KeyFrame[13].movPato_x = -0.2;
	KeyFrame[13].movPato_y = -0.3f;
	KeyFrame[13].movPato_z = 0.0f;
	KeyFrame[13].giroPato = 0.0f;	
	KeyFrame[13].caidaPato = -180;
	KeyFrame[13].patoChico = 0.5;

	//mov agua
	int render = 0, ola = 0;
	float incOla = 0.0f;
	float offsTex = 0.0f;
	
	ISound* track3D = audio->play3D("audio/aqua.mp3", vec3df(0, 0, 0), true, false, true);
	if (track3D)
		track3D->setMinDistance(15.0f);

	ISound* exor = audio->play3D("audio/exorcista.mp3", vec3df(0, 0, 0), true, false, true);
	if (exor)
		exor->setMinDistance(2.0f);

	ISound* scream = audio->play3D("audio/scream.mp3", vec3df(0, 0, 0), true, false, true);
	if (scream)
		scream->setMinDistance(3.0f);

	ISound* audioDelfin = audio->play3D("audio/delfin.mp3", vec3df(0, 0, 0), true, false, true);
	if (audioDelfin)
		audioDelfin->setMinDistance(3.0f);

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		audio->setListenerPosition(vec3df(camera.getCameraPosition()[0], camera.getCameraPosition()[1], camera.getCameraPosition()[2]), vec3df(0, 0, 1));
		track3D->setPosition(vec3df(76, -2, -5));
		exor->setPosition(vec3df(-15, 3, 25));
		scream->setPosition(vec3df(-15, 3, 27));
		audioDelfin->setPosition(vec3df(76, -2, -5));
		audio->setSoundVolume(0.7);
		track3D->setVolume(1);
		
		pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f,
			51.0f, mainWindow.p, 46.0f,
			0.3f, 0.2f, 0.1f);

		pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
			0.0f, 1.0f,
			0.6f, mainWindow.p, 3.0f,
			0.3f, 0.2f, 0.1f);

		pointLights[2] = PointLight(0.0f, 0.0f, 1.0f,
			0.0f, 1.0f,
			33.4f, mainWindow.p, 45.0f,
			0.3f, 0.2f, 0.1f);

		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// ANIMACIÓN DE SKYBOX
		if (dia>2100||dia <= 500) {
			skybox = skybox1;
			dia += 1;
			if (dia == 2400) {
				dia = 0;
			}
		}
		if (dia <= 600 && dia > 500) {
			skybox = skybox2;
			dia += 1;
		}
		if (dia<=700&&dia>600) {
			skybox = skybox3;
			dia += 1;
		}
		if (dia <=800 &&dia > 700) {
			skybox = skybox4;
			dia += 1;
		}
		if (dia <= 1000&&dia > 800) {
			skybox = skybox5;
			dia += 1;
		}
		if ( dia<=1200 &&dia > 1000) {
			skybox = skybox6;
			dia += 1;
		}
		if (dia <=1500 &&dia > 1200) {
			skybox = skybox7;
			dia += 1;
		}
		if (dia <=1600 &&dia > 1500) {
			skybox = skybox8;
			dia += 1;
		}
		if (dia <=1700 &&dia > 1600) {
			skybox = skybox9;
			dia += 1;
		}
		if ( dia <= 1800 &&dia > 1700) {
			skybox = skybox10;
			dia += 1;
		}
		if ( dia<=1900 &&dia > 1800) {
			skybox = skybox11;
			dia += 1;
		}
		if (dia <=2000 && dia > 1900) {
			skybox = skybox12;
			dia += 1;
		}
		if (dia <=2100 &&dia > 2000) {
			skybox = skybox13;
			dia += 1;
		}
		if (avanza>-360)
		{
			giraRueda -= 0.04 + deltaTime;
		}
		else {
			break;
		}

		// ANIMACIÓN DE ANIMALES DEL CARRUSEL
		// Caballo 1
		if (horseMovOneFlag)	// si TRUE -> desplazamiento hacia arriba
		{
			if (horseMovementOne < 0.4f) 
				horseMovementOne += 0.005f;
			else 
				horseMovOneFlag = false;
		}
		else					// si FALSE -> desplazamiento hacia abajo
		{
			if (horseMovementOne > 0.2f)
				horseMovementOne -= 0.005f;
			else
				horseMovOneFlag = true;
		}

		// Caballo 2
		if (horseMovTwoFlag)	// si TRUE -> desplazamiento hacia arriba
		{
			if (horseMovementTwo < 0.4f)
				horseMovementTwo += 0.005f;
			else
				horseMovTwoFlag = false;
		}
		else					// si FALSE -> desplazamiento hacia abajo
		{
			if (horseMovementTwo > 0.2f)
				horseMovementTwo -= 0.005f;
			else
				horseMovTwoFlag = true;
		}

		// Caballo 3
		if (horseMovThreeFlag)	// si TRUE -> desplazamiento hacia arriba
		{
			if (horseMovementThree < 0.4f)
				horseMovementThree += 0.005f;
			else
				horseMovThreeFlag = false;
		}
		else					// si FALSE -> desplazamiento hacia abajo
		{
			if (horseMovementThree > 0.2f)
				horseMovementThree -= 0.005f;
			else
				horseMovThreeFlag = true;
		}

		// Caballo 4
		if (horseMovFourFlag)	// si TRUE -> desplazamiento hacia arriba
		{
			if (horseMovementFour < 0.4f)
				horseMovementFour += 0.005f;
			else
				horseMovFourFlag = false;
		}
		else					// si FALSE -> desplazamiento hacia abajo
		{
			if (horseMovementFour > 0.2f)
				horseMovementFour -= 0.005f;
			else
				horseMovFourFlag = true;
		}


		//Movimiento_botellas
		if (bandera3 == 0) {
			if (fb1 < 2.5f && fb2 < 1.2f && fb3 < 0.5f && fb4 < -0.5f && fb5 < -1.5) {
				fb1 += 0.009f;
				fb2 += 0.009f;
				fb3 += 0.009f;
				fb4 += 0.009f;
				fb5 += 0.009f;
			}
			else {
				bandera3 = 1;
			}
		}
		else if (bandera3 == 1) {
			if (fb1 > 2.0f && fb2 > 1.0f && fb3 > 0.0f && fb4 > -1.0f && fb5 > -2.0f) {
				fb1 -= 0.009f;
				fb2 -= 0.009f;
				fb3 -= 0.009f;
				fb4 -= 0.009f;
				fb5 -= 0.009f;
			}
			else {
				bandera3 = 0;
			}
		}

		//mov cabina kilauea
		if (arriba == 1) {
			mov_cabina += 0.2f;
			if (mov_cabina > 14.0f) { abajo = 1; arriba = 0; }
		}
		else {
			mov_cabina -= 0.2f;
			if (mov_cabina < -2.0f) { abajo = 0; arriba = 1; }
		}

		//Mover skeleto1
		if (giroSkeleto <= 0)
		{
			controlGiro = 0;
		}

		if (giroSkeleto >= 20)
		{
			controlGiro = 1;
		}

		if (controlGiro == 0)
		{
			giroSkeleto += 0.1f;
		}

		if (controlSkeleto == 1)
		{
			giroSkeleto -= 0.1f;
		}

		//Mover skeleto2
		if (movSkeleto <= 0)
		{
			controlSkeleto = 0;

		}

		if (movSkeleto >= 2)
		{
			controlSkeleto = 1;

		}

		if (controlSkeleto == 0)
		{
			movSkeleto += 0.01f;
		}

		if (controlSkeleto == 1)
		{
			movSkeleto -= 0.01f;
		}

		// Recibir eventos del usuario
		glfwPollEvents();

		camera.changeCamera(mainWindow.getsKeys());
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();
		
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		//mov agua
		uniformOffTex = shaderList[0].GetOffTexLocation();

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// Matrices que almacenan la posici�n
		glm::mat4 model(1.0);
		glm::mat4 modelt(1.0);
		glm::vec3 camara(1.0);
		glm::mat4 model1(1.0);
		glm::mat4 ejeCan(1.0);
		glm::mat4 model2(1.0);
		glm::mat4 model3(1.0);
		glm::mat4 model4(1.0);
		glm::mat4 model5(1.0);
		glm::mat4 model6(1.0);
		glm::mat4 model7(1.0);
		glm::mat4 model8(1.0);
		glm::mat4 model9(1.0);
		glm::mat4 modelc(1.0);
		glm::mat4 modelBaseCarrusel(1.0);

		//mov agua
		glm::vec2 tex = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformOffTex, 1, glm::value_ptr(tex));

		//OKELA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoTexture.UseTexture();
		plainTexture.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//// DECORACIONES EXTRAS
		// Las garnachas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-25.0f, -1.9f, 0.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puestoComida.RenderModel();		

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.0f, -1.9f, -22.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puestoComida.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.0f, -1.9f, -12.0f));
		model = glm::scale(model, glm::vec3(0.04f, 0.04f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		puestoComida.RenderModel();

		// CANGRE
		// Charola 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -10.0f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -10.0f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -10.5f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -10.5f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		// Charola 2 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -11.2f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -11.2f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -11.7f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -11.7f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		// Charola 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -12.4f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -12.4f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -12.9f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -12.9f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		// Charola 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -13.6f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -13.6f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.05f, -14.1f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.05f, -14.1f));
		model = glm::scale(model, glm::vec3(0.003f, 0.003f, 0.003f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Can.RenderModel();

		//// Botellas de puesto
		// Charola 1
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -19.85f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -19.85f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -20.4f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -20.4f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		// Charola 2
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -21.05f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -21.05f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -21.6f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -21.6f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		// Charola 3
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -22.25f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -22.25f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -22.8f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -22.8f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		// Charola 4
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -23.45f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -23.45f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(41.25f, 0.25f, -24.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.75f, 0.25f, -24.0f));
		model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Coca.RenderModel();

		// Árboles
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-27.0f, -1.975f, -25.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(19.0f, -1.975f, -25.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(33.0f, -1.975f, -25.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(47.0f, -1.975f, 15.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(47.0f, -1.975f, 29.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(61.0f, -1.975f, 40.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(76.0f, -1.975f, 40.0f));
		model = glm::scale(model, glm::vec3(0.90f, 1.0f, 0.90f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Arbol.RenderModel();

		// Bancas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(47.0f, -2.0f, 22.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Banca.RenderModel();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(40.0f, 1.0f, -25.0f));
		//model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//Carro.RenderModel();


		// Bardas 
		//Barda_contraria a la de la entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel(); 

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(42.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(58.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(74.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, -2.0f, -30.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		//Barda a la derecha de la entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));		
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(96.0f, -2.0f, 40.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		//Barda a la izquierda de la entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, -25.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 14.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 27.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-30.0f, -2.0f, 40.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.04f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		//Barda de la entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-22.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-6.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(58.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(74.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(90.0f, -2.0f, 45.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.03f, 0.025f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barda.RenderModel();

		//// CARRUSEL DE CABALLOS Y ELEFANTES
		// Base del Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.65f, -18.5f));
		model = glm::scale(model, glm::vec3(5.0f, 3.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CarruselBase.RenderModel();

		// Base Giratoria del Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.075f, -18.5f));
		model = glm::scale(model, glm::vec3(5.0f, 3.0f, 5.0f));
		modelBaseCarrusel = model = glm::rotate(model, giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BaseGiratoriaCarrusel.RenderModel();

		// Base Toldo del Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 2.5f, -18.5f));
		model = glm::scale(model, glm::vec3(5.0f, 2.0f, 5.0f));
		model = glm::rotate(model, giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		CarruselBase.RenderModel();

		// Base Giratoria del Toldo Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 2.1f, -18.5f));
		model = glm::scale(model, glm::vec3(5.0f, 3.0f, 5.0f));
		model = glm::rotate(model, giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		BaseGiratoriaCarrusel.RenderModel();

		// Toldo del Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, 5.8f, -18.5f));
		model = glm::scale(model, glm::vec3(5.0f, 3.0f, 5.0f));
		model = glm::rotate(model, giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		ToldoCarrusel.RenderModel();

		//Escaleras de ascenso al carrusel
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-5.0f, -1.60f, -12.5f));
		model = glm::scale(model, glm::vec3(0.7f, 0.35f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Escalera.RenderModel();

		// Base Carrusel
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.0f, 0.2f, 0.0f));
		model = glm::scale(model, glm::vec3(0.05f, 0.5f, 0.05f));
		/*model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));*/
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		// Caballos
		//caballo1
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.0f, horseMovementOne, -0.8f));
		model = glm::scale(model, glm::vec3(0.00035f, 0.00035f, 0.00035f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo.RenderModel();
		//base caballo1
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.0f, 0.5f, -0.8f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//caballo2
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.0f, horseMovementTwo, 0.8f));
		model = glm::scale(model, glm::vec3(0.00035f, 0.00035f, 0.00035f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo.RenderModel();
		//base caballo2
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.0f, 0.5f, 0.8f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//caballo3
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.8f, horseMovementThree, 0.0f));
		model = glm::scale(model, glm::vec3(0.00035f, 0.00035f, 0.00035f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo.RenderModel();
		//base caballo3
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.8f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//caballo4
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.8f, horseMovementFour, 0.0f));
		model = glm::scale(model, glm::vec3(0.00035f, 0.00035f, 0.00035f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Caballo.RenderModel();
		//base caballo4
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.8f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		// Elefantes
		//elefante1
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.60f, horseMovementOne + 0.2f, 0.60f));		
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Elefante.RenderModel();
		//base elefante1
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.55f, 0.5f, 0.60f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//elefante2
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.60f, horseMovementTwo + 0.2f, -0.60f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		model = glm::rotate(model, 135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Elefante.RenderModel();
		//base elefante2
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.55f, 0.5f, -0.60f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//elefante3
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.60f, horseMovementThree + 0.2f, 0.60f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Elefante.RenderModel();
		//base elefante3
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(-0.55f, 0.5f, 0.60f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//elefante4
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.60f, horseMovementFour + 0.2f, -0.60f));
		model = glm::scale(model, glm::vec3(0.07f, 0.07f, 0.07f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Elefante.RenderModel();
		//base elefante4
		model = glm::mat4(1.0);
		model = glm::translate(modelBaseCarrusel, glm::vec3(0.55f, 0.5f, -0.60f));
		model = glm::scale(model, glm::vec3(0.01f, 0.30f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		MetalPipe.RenderModel();

		//Barandales
		//front
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -2.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.50f, -2.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.25f, -2.0f, -12.0f));
		model = glm::scale(model, glm::vec3(0.0025f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		//left
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.25f, -2.0f, -15.75f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.25f, -2.0f, -23.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		//back
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-7.0f, -2.0f, -26.60f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.50f, -2.0f, -26.60f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-11.25f, -2.0f, -26.60f));
		model = glm::scale(model, glm::vec3(0.0025f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		//right-entrada
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.85f, -2.0f, -15.75f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(2.85f, -2.0f, -23.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.5f, -2.0f, -10.0f));
		model = glm::scale(model, glm::vec3(0.0020f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.25f, -2.0f, -13.65f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.25f, -2.0f, -20.90f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.5f, -2.0f, -26.60f));
		model = glm::scale(model, glm::vec3(0.0020f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.95f, -2.0f, -26.60f));
		model = glm::scale(model, glm::vec3(0.0020f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.75f, -2.0f, -15.75f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.75f, -2.0f, -23.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(5.75f, -2.0f, -11.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.02f, 0.0030f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();


		//RUEDA DE LA FORTUNA
		//Barandales
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.4f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.4f, -2.0f, 7.4f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.4f, -2.0f, 8.4f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.4f, -2.0f, 9.4f));
		model = glm::scale(model, glm::vec3(0.009f, 0.02f, 0.01f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.7f, -2.0f, 8.2f));
		model = glm::scale(model, glm::vec3(0.01f, 0.02f, 0.0025f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.7f, -2.0f, 8.4f));
		model = glm::scale(model, glm::vec3(0.01f, 0.02f, 0.0027f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.7f, -2.0f, 3.7f));
		model = glm::scale(model, glm::vec3(0.01f, 0.02f, 0.01f));
		model = glm::rotate(model, 90* toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.7f, -2.0f, 3.7f));
		model = glm::scale(model, glm::vec3(0.01f, 0.02f, 0.01f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Barandal.RenderModel();


		//Escalera
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 5.7f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Escalera.RenderModel();

		//kilauea
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -2.0f, -2.4f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Kilauea.RenderModel();
		//Cabinas Kilauea
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, mov_cabina, -2.4f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cabinas.RenderModel();

		//Escenario show acuático
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(76.0f, -2.0f , -5.4f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Aqua.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(75.2f, -2.0f, 17.4f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.45f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		marmolTexture.UseTexture();
		estDelfin.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(80.5f, -2.0f, 17.4f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.45f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		marmolTexture.UseTexture();
		estDelfin.RenderModel();


		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(76.0f, 0.0f, -5.4f));
		model = glm::scale(model, glm::vec3(0.021f, 0.021f, 0.021f));
		model = glm::rotate(model, -giraRueda*(17.0f) * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		delfin.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(73.0f, 0.0f, -10.0f + movSkeleto*2.0f));
		model = glm::scale(model, glm::vec3(0.021f, 0.021f, 0.021f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		delfin.RenderModel();

		//Persona
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(9.0f, 0.85f, 10.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-12.0f, 5.85f, 16.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.7f, 12.85f, -6.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		//Persona
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 9.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, 5.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, -0.85f, 5.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, 20.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(23.0f, 7.85f, 10.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -0.85f, 30.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(17.0f, 3.85f, 17.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(13.0f, 8.85f, 7.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-13.0f, -0.85f, 10.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -0.85f, -30.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-18.0f, -0.85f, -10.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(26.0f, 10.85f, 7.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, 7.85f, 20.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(18.0f, 2.85f, -18.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(20.0f, -0.85f, -20.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(10.0f, -0.85f, -10.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-17.0f, -0.85f, 18.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(28.0f, 12.85f, -1.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, 0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(8.0f, -0.85f, 9.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Medusa.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.95f, 10.1f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Pat.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(3.0f, 0.95f, 10.1f));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Cal.RenderModel();



		//Ruedatalcual
		model = glm::mat4(1.0);
		model = modelt = glm::translate(model, glm::vec3(0.0f, 9.1f, 3.5f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));
		model1 = model = glm::rotate(model, giraRueda * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dirtTexture.UseTexture();
		Rueda.RenderModel();

		//Estructura
		model = glm::mat4(1.0);
		model = glm::translate(modelt, glm::vec3(0.0f, -5.25f, -2.25f));
		model = glm::scale(model, glm::vec3(0.05f, 0.1f, 0.05f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		dirtTexture.UseTexture();
		Estructura.RenderModel();

		//Control
		model = glm::mat4(1.0);
		model = glm::translate(modelt, glm::vec3(0.0f, 0.0f, -2.25f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(modelt, glm::vec3(0.0f, -9.3f, -2.25f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Eje rueda
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f, -15.0f, 10.65f));
		model = glm::scale(model, glm::vec3(1.3f, 32.0f, 1.3f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(12.5f, 1.0f, -13.65f));
		model = glm::scale(model, glm::vec3(32.0f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f, 05.0f, -13.65f));
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 16.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		//Ejederotaciondecanasta
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f, -92.7f, 13.65f));
		model = glm::scale(model, glm::vec3(1.3f, 10.0f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f, -92.7f, -16.65f));
		model = glm::scale(model, glm::vec3(1.3f, 10.0f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(-2.0f, -102.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		//Canasta
		model = glm::mat4(1.0);
		model = model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model2, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelc = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		camara = glm::column(modelc, 3);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//eje
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f, 85.0f, 13.65f));
		model = glm::scale(model, glm::vec3(1.3f, 10.0f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-3.5f,85.0f, -16.65f));
		model = glm::scale(model, glm::vec3(1.3f, 10.0f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(-2.0f, 104.0f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model3 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		//canasta 2
		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model3, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		
		//canasta 3
		//eje
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(93.5f, 05.0f, 13.65f));
		model = glm::scale(model, glm::vec3(10.0f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(93.5f, 05.0f, -16.65f));
		model = glm::scale(model, glm::vec3(10.0f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();


		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(103.0f, 7.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model4 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		//canasta
		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model4, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//canasta 4
		//eje
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-83.5f, 05.0f, 13.65f));
		model = glm::scale(model, glm::vec3(10.0f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-83.5f, 05.0f, -16.65f));
		model = glm::scale(model, glm::vec3(10.0f, 1.3f, 1.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(-103.0f, 7.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model5 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model5, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//Canasta 5
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(55.0f, -75.0f, 13.65f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(55.0f, -75.0f, -16.65f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(63.5f, -79.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model6 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model6, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//Canasta 6
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-60.0f, 60.0f, 13.65f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-60.0f, 60.0f, -16.65f));
		model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(-72.5f, 75.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model7 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model7, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//canasta 7
		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-66.0f, -66.0f, 13.65f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(-66.0f, -66.0f, -16.65f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(-72.5f, -74.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model8 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model8, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();

		//Canasta8

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(60.0f, 60.0f, 13.65f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model1, glm::vec3(60.0f, 60.0f, -16.65f));
		model = glm::rotate(model, -45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.3f, 10.3f, 1.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		ejeCan = model = glm::translate(model1, glm::vec3(74.5f, 72.5f, -5.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 10.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model9 = glm::rotate(model, -giraRueda * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Rot.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(ejeCan, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::translate(model9, glm::vec3(3.5f, 0.5f, 23.5f));
		model = glm::scale(model, glm::vec3(49.1f, 2.1f, 49.1f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dadoTexture.UseTexture();
		meshList[5]->RenderMesh();


		/////////////////PUESTO_JUEGO_DESTREZA/////////////////
		glm::mat4 Puesto_m(1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(48.0f, -2.0f, 5.0f));		
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));		
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Puesto_m = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Puesto.RenderModel();		

		glm::mat4 Cajon_m(1.0);				
		Cajon_m = glm::translate(Puesto_m, glm::vec3(0.0f, 2.0f, -0.1f));	
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		Cajon_m = glm::rotate(Cajon_m, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Cajon_m));
		Cajon.RenderModel();

		glm::mat4 Cajon_m2(1.0);
		Cajon_m2 = glm::translate(Puesto_m, glm::vec3(-3.3f, 0.0f, -0.55f));
		Cajon_m2 = glm::scale(Cajon_m2, glm::vec3(0.8f, 0.8f, 0.9f));
		Cajon_m2 = glm::rotate(Cajon_m2, 60 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Cajon_m2));
		cajon_v.RenderModel();

		glm::mat4 Guante_DER1(1.0);
		Guante_DER1 = glm::translate(Cajon_m2, glm::vec3(0.2f, 2.6f, -0.35f));
		Guante_DER1 = glm::scale(Guante_DER1, glm::vec3(0.25f, 0.25f, 0.25f));
		Guante_DER1 = glm::rotate(Guante_DER1, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Guante_DER1));
		guanteDER.RenderModel();

		glm::mat4 Guante_IZQ1(1.0);
		Guante_IZQ1 = glm::translate(Cajon_m2, glm::vec3(0.2f, 0.3f, 0.35f));
		Guante_IZQ1 = glm::scale(Guante_IZQ1, glm::vec3(0.25f, 0.25f, 0.25f));
		Guante_IZQ1 = glm::rotate(Guante_IZQ1, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Guante_IZQ1));
		guanteIZQ.RenderModel();			
		
		
		glm::mat4 Cajon_m3(1.0);
		Cajon_m3 = glm::translate(Puesto_m, glm::vec3(3.3f, 0.0f, -0.55f));
		Cajon_m3 = glm::scale(Cajon_m3, glm::vec3(0.8f, 0.8f, 0.9f));
		Cajon_m3 = glm::rotate(Cajon_m3, 120 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Cajon_m3));
		cajon_v.RenderModel();

		glm::mat4 Guante_DER2(1.0);
		Guante_DER2 = glm::translate(Cajon_m3, glm::vec3(0.2f, 0.3f, -0.35f));
		Guante_DER2 = glm::scale(Guante_DER2, glm::vec3(0.25f, 0.25f, 0.25f));
		Guante_DER2 = glm::rotate(Guante_DER2, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Guante_DER2));
		guanteDER.RenderModel();

		glm::mat4 Guante_IZQ2(1.0);
		Guante_IZQ2 = glm::translate(Cajon_m3, glm::vec3(0.2f, 2.6f, 0.35f));
		Guante_IZQ2 = glm::scale(Guante_IZQ2, glm::vec3(0.25f, 0.25f, 0.25f));
		Guante_IZQ2 = glm::rotate(Guante_IZQ2, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Guante_IZQ2));
		guanteIZQ.RenderModel();

		glm::mat4 Mesa_m(1.0);
		Mesa_m = glm::translate(Puesto_m, glm::vec3(0.0F, 0.0f, -3.8f));
		//model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		Mesa_m = glm::rotate(Mesa_m , 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Mesa_m));
		Mesa.RenderModel();	
		
		glm::mat4 Figuras_m (1.0);
		Figuras_m = glm::translate(Cajon_m, glm::vec3(-0.53f, -0.35f, 1.5f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Figuras_m));
		fig1.RenderModel();

		glm::mat4 Figuras_m1(1.0);
		Figuras_m1 = glm::translate(Cajon_m, glm::vec3(-0.53f, -0.35f, 0.4f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Figuras_m1));
		fig1.RenderModel();

		glm::mat4 Figuras_m2(1.0);
		Figuras_m2 = glm::translate(Cajon_m, glm::vec3(-0.53f, -0.35f, -0.6f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Figuras_m2));
		fig1.RenderModel();

		glm::mat4 Figuras_m3(1.0);
		Figuras_m3 = glm::translate(Cajon_m, glm::vec3(-0.53f, -0.35f, -1.7f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Figuras_m3));
		fig1.RenderModel();

		glm::mat4 Figuras_m4(1.0);
		Figuras_m4 = glm::translate(Cajon_m, glm::vec3(-0.53f, -0.35f, -2.7f));		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Figuras_m4));
		fig1.RenderModel();
		
		glm::mat4 Botellas_m1(1.0);		
		Botellas_m1 = glm::translate(Cajon_m, glm::vec3(0.1f, 0.09f, fb1));
		Botellas_m1 = glm::scale(Botellas_m1, glm::vec3(0.36f, 0.36f, 0.36f));
		Botellas_m1 = glm::rotate(Botellas_m1, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Botellas_m1));
		Botella.RenderModel();

		glm::mat4 Botellas_m2(1.0);
		Botellas_m2 = glm::translate(Cajon_m, glm::vec3(0.1f, 0.09f, fb2));
		Botellas_m2 = glm::scale(Botellas_m2, glm::vec3(0.36f, 0.36f, 0.36f));
		Botellas_m2 = glm::rotate(Botellas_m2, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Botellas_m2));
		Botella.RenderModel();

		glm::mat4 Botellas_m3(1.0);
		Botellas_m3 = glm::translate(Cajon_m, glm::vec3(0.1f, 0.09f, fb3));
		Botellas_m3 = glm::scale(Botellas_m3, glm::vec3(0.36f, 0.36f, 0.36f));
		Botellas_m3 = glm::rotate(Botellas_m3, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Botellas_m3));
		Botella.RenderModel();

		glm::mat4 Botellas_m4(1.0);
		Botellas_m4 = glm::translate(Cajon_m, glm::vec3(0.1f, 0.09f, fb4));
		Botellas_m4 = glm::scale(Botellas_m4, glm::vec3(0.36f, 0.36f, 0.36f));
		Botellas_m4 = glm::rotate(Botellas_m4, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Botellas_m4));
		Botella.RenderModel();

		glm::mat4 Botellas_m5(1.0);
		Botellas_m5 = glm::translate(Cajon_m, glm::vec3(0.1f, 0.09f, fb5));
		Botellas_m5 = glm::scale(Botellas_m5, glm::vec3(0.36f, 0.36f, 0.36f));
		Botellas_m5 = glm::rotate(Botellas_m5, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Botellas_m5));
		Botella.RenderModel();			

		/*glm::mat4 Pato_m(1.0);
		Pato_m = glm::translate(Cajon_m, glm::vec3(0.12, 0.75f, 0.0f));
		Pato_m = glm::rotate(Pato_m, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Pato_m));
		Pato.RenderModel();*/

		glm::mat4 Pato_m(1.0);
		posPatote = glm::vec3(posXPato + movPato_x, posYPato + movPato_y, posZPato + movPato_z);
		//Pato_m = glm::translate(Cajon_m, glm::vec3(0.12f,0.75f,0.0f));
		Pato_m = glm::translate(Cajon_m, posPatote);
		Pato_m = glm::scale(Pato_m, glm::vec3(patoChico, patoChico, patoChico));
		Pato_m = glm::rotate(Pato_m, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Pato_m = glm::rotate(Pato_m, giroPato * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		Pato_m = glm::rotate(Pato_m, caidaPato * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Pato_m));
		Pato.RenderModel();

		glm::mat4 Peluches_m(1.0);
		Peluches_m = glm::translate(Puesto_m, glm::vec3(-4.0f, 3.5f, -0.4f));
		Peluches_m = glm::scale(Peluches_m, glm::vec3(0.8f, 0.8f, 0.8f));
		Peluches_m = glm::rotate(Peluches_m, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Peluches_m = glm::rotate(Peluches_m, -70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Peluches_m));
		Peluches.RenderModel();
				
		glm::mat4 Peluches_m2(1.0);
		Peluches_m2 = glm::translate(Puesto_m, glm::vec3(4.0f, 3.5f, -0.4f));
		Peluches_m2 = glm::scale(Peluches_m2, glm::vec3(0.8f, 0.8f, 0.8f));
		Peluches_m2 = glm::rotate(Peluches_m2, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Peluches_m2 = glm::rotate(Peluches_m2, 70 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Peluches_m2));
		Peluches.RenderModel();

		glm::mat4 Peluches_m3;
		Peluches_m3 = glm::translate(Puesto_m, glm::vec3(1.2F, 2.4f, -0.15f));
		//model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		Peluches_m3 = glm::rotate(Peluches_m3, 180 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		Peluches_m3 = glm::rotate(Peluches_m3, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(Peluches_m3));
		Peluches2.RenderModel();



		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(mainWindow.rx, mainWindow.ry, mainWindow.rz));
		model = glm::scale(model, glm::vec3(48.0f, -2.0f, 5.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Rifle.RenderModel();*/

		/////TIENDA_SOUVENIRS//////
		glm::mat4 base_m(1.0);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(70.0f, 2.2f, 40.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		base_m = model;	
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		base_chan.RenderModel();

		glm::mat4 chango_mueve(1.0);
		chango_mueve = glm::mat4(1.0);
		chango_mueve = glm::translate(base_m, glm::vec3(0.0f, 1.0f, 0.0f));
		chango_mueve = glm::rotate(chango_mueve, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(chango_mueve));
		chango.RenderModel();

		glm::mat4 tienda_m(1.0);
		tienda_m = glm::mat4(1.0);
		tienda_m = glm::translate(base_m, glm::vec3(0.0f, -5.4f, 0.0f));
		tienda_m = glm::rotate(tienda_m, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		tienda_m = glm::scale(tienda_m, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(tienda_m));
		souvenirs.RenderModel();	

		//////// MONTAÑA RUSA		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(25.0f, -2.0f, 20.0f));
		model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		mountain.RenderModel();
		
		//Casa terror
		glm::mat4 modelCasa(1.0);

		//Casa terror
		//Base casa
		model = glm::mat4(1.0);
		modelCasa=model = glm::translate(model, glm::vec3(-15.0f, 3.2f, 25.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(20.0f, 20.0f, 10.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//roca.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh(); 

		//Skeleto
		model = glm::translate(modelCasa, glm::vec3(7.0f, -2.0f, -8.5f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -giroSkeleto * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Skeleto.RenderModel();

		//Skeleto2
		model = glm::translate(modelCasa, glm::vec3(0.0f, -1.2f, 4.5f + movSkeleto));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Skeleto2.RenderModel();

		//Piso
		model = glm::translate(modelCasa, glm::vec3(0.0f, -5.1f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		roca.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh(); 

		//Centro
		model = glm::translate(modelCasa, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		roca.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh(); 

		//Cuadros
		model = glm::translate(modelCasa, glm::vec3(9.99f, -1.0f, 2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuadro1.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh(); 

		model = glm::translate(modelCasa, glm::vec3(5.01f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuadro2.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh(); 

		model = glm::translate(modelCasa, glm::vec3(-9.99f, -1.0f, 2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuadro3.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh(); 

		model = glm::translate(modelCasa, glm::vec3(-5.01f, -1.0f, 1.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuadro4.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		//Tumbas
		model = glm::translate(modelCasa, glm::vec3(-5.0f, -4.0f, 13.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Tumba.RenderModel();

		//Fachada
		model = glm::translate(modelCasa, glm::vec3(0.0f, 1.8f, 10.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 1.0f, 8.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		fachada.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh(); 
		glDisable(GL_BLEND);

		// Chocones
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-23.0f, -2.0f, -13.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.7, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		chocones.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-23.0f, -1.0f, -13.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		metal6.UseTexture();
		bumper.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -1.0f, -17.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, 30 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		metal8.UseTexture();
		bumper.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-19.5f, -1.0f, -9.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, -135 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.025f, 0.025f, 0.025f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		metal7.UseTexture();
		bumper.RenderModel();



		// Detección de teclas para cambio de camaras
		gameCameraFlag = mainWindow.changeGameCamera();			// Método de detección de cámara de recorrido del juego

		if (gameCameraFlag) {
			camera = Camera(camara, camara , 90.0f, 0.0f, 5.0f, 0.5f);
		}
			   		 	  	  	
		glDisable(GL_BLEND);

		model = glm::mat4(1.0);
		//mov agua
		offsTex += 0.001f;
		if (offsTex >= 10.0f)
			offsTex = 0.0f;
		tex = glm::vec2(offsTex, offsTex);
		model = glm::translate(model, glm::vec3(76.0f, -2.0f, -5.4f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//mov agua
		glUniform2fv(uniformOffTex, 1, glm::value_ptr(tex));
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Agua.RenderModel();
		//mov agua
		tex = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformOffTex, 1, glm::value_ptr(tex));

		glUseProgram(0);

		mainWindow.swapBuffers();
	}


	audio->drop();
	return 0;

}

void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if(reproduciranimacion<1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("presiona 0 para habilitar reproducir de nuevo la animaci�n'\n");
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
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}
	
	//if (keys[GLFW_KEY_L])
	//{
	//	if (guardoFrame < 1)
	//	{
	//		saveFrame();
	//		printf("movAvion_x es: %f\n", movPato_x);
	//		//printf("movAvion_y es: %f\n", movAvion_y);
	//		printf("presiona P para habilitar guardar otro frame'\n");
	//		guardoFrame++;
	//		reinicioFrame = 0;
	//	}
	//}
	//if (keys[GLFW_KEY_P])
	//{
	//	if (reinicioFrame < 1)
	//	{
	//		guardoFrame=0;
	//	}
	//}
	//
	//
	//if (keys[GLFW_KEY_1])
	//{
	//	if (ciclo < 1)
	//	{
	//		//printf("movAvion_x es: %f\n", movAvion_x);
	//		movPato_x += 1.0f;
	//		printf("movAvion_x es: %f\n", movPato_x);
	//		ciclo++;
	//		ciclo2 = 0;
	//		printf("reinicia con 2\n");
	//	}
	//	
	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	if(ciclo2<1)
	//	{
	//	ciclo = 0;
	//	}
	//}

	//if (keys[GLFW_KEY_3])
	//{
	//	if (ciclo < 1)
	//	{
	//		//printf("movAvion_x es: %f\n", movAvion_x);
	//		movPato_x -= 1.0f;
	//		printf("movAvion_x es: %f\n", movPato_x);
	//		ciclo++;
	//		ciclo2 = 0;
	//		printf("reinicia con 2\n");
	//	}

	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	if (ciclo2 < 1)
	//	{
	//		ciclo = 0;
	//	}
	//}

	//if (keys[GLFW_KEY_4])
	//{
	//	if (ciclo < 1)
	//	{
	//		//printf("movAvion_x es: %f\n", movAvion_x);
	//		giroPato = 180.0f;
	//		printf("giroAvion es: %f\n", giroPato);
	//		ciclo++;
	//		ciclo2 = 0;
	//		printf("reinicia con 2\n");
	//	}

	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	if (ciclo2 < 1)
	//	{
	//		ciclo = 0;
	//	}
	//}

	//if (keys[GLFW_KEY_5])
	//{
	//	if (ciclo < 1)
	//	{
	//		//printf("movAvion_x es: %f\n", movAvion_x);
	//		giroPato = 0.0f;
	//		printf("giroAvion es: %f\n", giroPato);
	//		ciclo++;
	//		ciclo2 = 0;
	//		printf("reinicia con 2\n");
	//	}

	//}
	//if (keys[GLFW_KEY_2])
	//{
	//	if (ciclo2 < 1)
	//	{
	//		ciclo = 0;
	//	}
	//}
}
