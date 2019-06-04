#include "Window.h"

float Window::x=0.0f;
float Window::y=0.0f;
float Window::z=0.0f;
float Window::x1 = 0.0f;
float Window::y1 = 0.0f;
float Window::z1 = 0.0f;
float Window::p;
float Window::a;
float Window::LX1;
float Window::LY1;
float Window::LZ1;
float Window::LX2;
float Window::LY2;
float Window::LZ2;
float Window::rx;
float Window::ry;
float Window::rz;

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
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	////para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "CGEIHC, PROYECTO FINAL", NULL, NULL);

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

	//Captura del Mouse
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 

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

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		printf("se presiono la tecla: %s\n", key_name);
	}

	if (key == GLFW_KEY_J &&  (action == GLFW_PRESS || action == GLFW_REPEAT))

	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_J, 0);
		printf("se presiono la tecla: %s\n", key_name);
		x += 1.0f;
	}

	if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_L, 0);
		printf("se presiono la tecla: %s\n", key_name);
		x -= 1.0f;
	}

	if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_I, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y += 1.0f;
	}

	if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_K, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y -= 1.0f;
	}

	if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_U, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z += 1.0f;
	}

	if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_O, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z -= 1.0f;
	}


	if (key == GLFW_KEY_G && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_G, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y1 += 1.0f;
	}

	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_B, 0);
		printf("se presiono la tecla: %s\n", key_name);
		y1 -= 1.0f;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_F, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z1 += 1.0f;
	}

	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_H, 0);
		printf("se presiono la tecla: %s\n", key_name);
		z1-= 1.0f;
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
			printf("se solto la tecla %d'\n", key);
		}
	}

	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		LX1 = +1.0f;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		LX1 = -1.0f;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		LY1 = +1.0f;
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		LY1 = -1.0f;
	}
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		LZ1 = +1.0f;
	}
	if (key == GLFW_KEY_I && action == GLFW_PRESS) {
		LZ1 = -1.0f;
	}

	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		LX2 = +1.0f;
	}
	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		LX2 = -1.0f;
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		LY2 = +1.0f;
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		LY2 = -1.0f;
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		LZ2 = +1.0f;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		LZ2 = -1.0f;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS) {
		rx = rx + 1.0f;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		rx = rx - 1.0f;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		ry = ry + 1.0f;
	}
	if (key == GLFW_KEY_V && action == GLFW_PRESS) {
		ry = ry - 1.0f;
	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		rz = rz + 1.0f;
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		rz = rz - 1.0f;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		p = p - 100.0f;
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		p = p + 100.0f;
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
