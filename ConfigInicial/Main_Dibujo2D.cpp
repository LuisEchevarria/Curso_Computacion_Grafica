/*
	Luis Angel Echevarria Aguilar   No. Cuenta: 320236235
	Practica #2. Dibujo de primitivas en 2D   Fecha de entrega: 15/02/2026
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "P2. Echevarria Aguilar Luis Angel", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers
	/*float vertices[] = {
		0.5f,  0.5f, 0.0f,    1.0f,0.0f,0.0f,  // top right
		0.5f, -0.5f, 0.0f,    1.0f,1.0f,0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f,0.0f,1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f,1.0f,0.0f, // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		3,2,1,// second Triangle
		0,1,3,
		
	};*/


	float vertices[] = {
		// X,      Y,      Z,        R,    G,    B         // Referencia Hoja
		-0.1f,   0.9f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 1
		 0.3f,   0.8f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 2
		 0.5f,   0.6f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 3
		 0.55f,  0.5f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 4
		 0.53f,  0.1f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 5
		 0.7f,  -0.55f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 6
		 0.65f, -0.6f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 7
		 0.4f,  -0.6f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 8
		 0.45f, -0.75f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 9
		 0.35f, -0.8f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 10
		 0.1f,  -0.75f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 11
		-0.3f,  -0.9f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 12
		-0.55f, -0.85f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 13
		-0.55f, -0.75f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 14
		-0.45f, -0.65f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 15
		-0.4f,  -0.5f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 16
		-0.5f,  -0.45f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 17
		-0.8f,  -0.25f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 18
		-0.75f,  0.05f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 19
		-0.65f,  0.35f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 20
		-0.55f,  0.45f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 21
		-0.4f,   0.7f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 22
		-0.3f,   0.65f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 23
		-0.4f,   0.35f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 24
		-0.1f,   0.4f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 25
		 0.1f,   0.25f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 26
		 0.25f, -0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 27
		 0.6f,  -0.5f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 28
		-0.4f,  -0.55f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 29
		-0.35f, -0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 30
		-0.42f, -0.29f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 31
		-0.48f, -0.28f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 32
		-0.52f, -0.27f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 33
		-0.58f, -0.26f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 34
		-0.62f, -0.25f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 35
		-0.68f, -0.24f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 36
		-0.72f, -0.23f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 37
		-0.67f, -0.1f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 38
		-0.57f,  0.02f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 39
		-0.57f,  0.05f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 40
		-0.5f,   0.13f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 41
		-0.55f,  0.2f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 42
		-0.53f,  0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 43
		-0.55f,  0.4f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 44
		-0.47f,  0.32f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 45
		-0.4f,   0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 46
		-0.45f,  0.2f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 47
		-0.4f,   0.2f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 48
		-0.47f,  0.1f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 49
		-0.47f,  0.0f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 50
		-0.53f,  0.01f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 51
		-0.25f,  0.12f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 52
		 0.0f,   0.1f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 53
		-0.1f,   0.25f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 54
		-0.3f,   0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 55
		-0.35f,  0.3f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 56
		-0.4f,  -0.15f,  0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 57
		-0.43f, -0.1f,   0.0f,     1.0f, 1.0f, 1.0f,    // Vértice 58
		-0.46f, -0.05f,  0.0f,     1.0f, 1.0f, 1.0f     // Vértice 59
	};

	unsigned int indices[] = {
		// Conexiones alrededor del punto 25 (centro arriba) y 26
		0,22,   // 1 conecta con 23 (índice 22)
		22,23,  // 23 conecta con 24 (índice 23)
		23,24,  // 24 conecta con 25 (índice 24)
		24,25,  // 25 conecta con 26 (índice 25)
		25,53,  // 26 conecta con 54 (índice 53)
		53,52,  // 54 conecta con 53 (índice 52)
		52,26,  // 53 conecta con 27 (índice 26)
		26,27,  // 27 conecta con 28 (índice 27)
		25,3,   // 26 conecta con 4 (índice 3)
		26,5,   // 27 conecta con 6 (índice 5)

		// Conexiones cruzadas en la frente
		23,54,  // 24 conecta con 55 (índice 54)
		54,24,  // 55 conecta con 25 (índice 24)

		// 2. ZONA DEL OJO (Izquierda arriba)
		// El ojo es un ciclo complejo entre 41-48 y sus vecinos
		19,42,  // 20 conecta con 43 (índice 42)
		42,43,  // 43 conecta con 44
		43,20,  // 44 conecta con 21
		20,21,  // 21 conecta con 22
		21,44,  // 22 conecta con 45
		44,45,  // 45 conecta con 46
		45,46,  // 46 conecta con 47
		46,55,  // 47 conecta con 56
		55,54,  // 56 conecta con 55

		// Detalles internos del ojo
		41,42,  // 42 conecta con 43
		40,41,  // 41 conecta con 42
		39,40,  // 40 conecta con 41
		38,39,  // 39 conecta con 40
		18,37,  // 19 conecta con 38
		40,47,  // 41 conecta con 48
		47,48,  // 48 conecta con 49
		48,49,  // 49 conecta con 50
		49,50,  // 50 conecta con 51
		39,50,  // 40 conecta con 51
		46,47,  // 47 conecta con 48
		48,51,  // 49 conecta con 52
		51,52,  // 52 conecta con 53

		// 3. LA REJILLA DE LA BOCA (Abajo izquierda)
		// Línea superior de la rejilla (conectando con la nariz)
		37,58,  // 38 conecta con 59
		36,58,  // 37 conecta con 59
		35,58,  // 36 conecta con 59
		34,57,  // 35 conecta con 58
		33,57,  // 34 conecta con 58
		32,57,  // 33 conecta con 58
		31,56,  // 32 conecta con 57
		30,56,  // 31 conecta con 57
		29,56,  // 30 conecta con 57

		// Línea horizontal que une la rejilla por arriba
		58,57,  // 59 conecta con 58
		57,56,  // 58 conecta con 57
		56,50,  // 57 conecta con 51

		// Línea inferior de la boca (los dientes de abajo)
		17,36,  // 18 conecta con 37
		36,35,  // 37 conecta con 36
		35,34,  // 36 conecta con 35
		34,33,  // 35 conecta con 34
		33,32,  // 34 conecta con 33
		32,31,  // 33 conecta con 32
		31,30,  // 32 conecta con 31
		30,29,  // 31 conecta con 30
		29,16,  // 30 conecta con 17

		// 4. ESTRUCTURA LATERAL Y CUELLO (Derecha abajo)
		26,7,   // 27 conecta con 8
		26,8,   // 27 conecta con 9
		26,10,  // 27 conecta con 11
		26,11,  // 27 conecta con 12
		27,28,  // 28 conecta con 29
		28,10,  // 29 conecta con 11
		28,11,  // 29 conecta con 12
		28,12,  // 29 conecta con 13
		28,15,  // 29 conecta con 16
		28,16,  // 29 conecta con 17
		15,29,  // 16 conecta con 30
		29,30   // 30 conecta con 31
	};

	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


        //glPointSize(10);
        //glDrawArrays(GL_POINTS,0,4);
		//glDrawArrays(GL_TRIANGLES,0,3);
		//glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT,0);
        //glDrawArrays(GL_LINES,0,4);

		// Dibuja los vértices 1 al 22 (índices 0-21) cerrando el ciclo.
		glDrawArrays(GL_LINE_LOOP, 0, 22);
        
		// Dibuja las líneas internas definidas en el arreglo indices[]
		// El segundo argumento es la cantidad de índices en el arreglo.
		glDrawElements(GL_LINES, 100, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}