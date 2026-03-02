/*
	Practica #4. Modelado geométrico en OpenGL    |    Echevarria Aguilar Luis Angel
	Fecha de entrega: 01/03/2026                  |    No. Cuenta: 320236235
*/

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "P4 - Echevarria Aguilar Luis Angel", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers

	

	// use with Perspective Projection
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
	//	0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	//	0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	//	0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
	//	-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
	//	-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
	//	
	//    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
	//	 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	//	 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	//	 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	//    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	//    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	//	
	//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	//	 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	//	 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
	//	 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
	//	 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
 //     
	//	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
	//	-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	//	-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
	//	
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
	//	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
	//	0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
	//	-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
	//	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
	//	
	//	-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	//	0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
	//	0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
	//	-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
	//	-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	//};

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};




	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	// Posicion (ahora el 'stride' es de 3 * sizeof(GLfloat))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	////Color
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(1);   // Ya no necesitamos glEnableVertexAttribArray(1)

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer (Fondo Gris)
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint colorLoc = glGetUniformLocation(ourShader.Program, "objectColor");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	
		// --- VARIABLES DE COLOR ---
		float oR = 1.0f, oG = 0.6f, oB = 0.1f; //Naranja
		float cR = 0.95f, cG = 0.9f, cB = 0.6f; //Crema
		float yR = 1.0f, yG = 0.9f, yB = 0.0f; // Amarillo
		float rR = 1.0f, rG = 0.15f, rB = 0.1f; // Rojo
		float eR = 0.1f, eG = 0.7f, eB = 0.7f; // Azul Verdoso
		float wR = 1.0f, wG = 1.0f, wB = 1.0f; // Blanco

		//==========
		//  CABEZA
		//==========
		glUniform3f(colorLoc, oR, oG, oB);

		// Cráneo (Base central)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.1f, 0.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.4f, 1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Domo de la cabeza - Nivel 1 (Primer escalón hacia arriba)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.85f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.3f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Domo de la cabeza - Nivel 2 (Segundo escalón, la punta de la cabeza)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.05f, 0.0f));
		model = glm::scale(model, glm::vec3(0.8f, 0.2f, 0.8f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Nuca (Relieve en la parte de atrás de la cabeza) ---
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.1f, -0.75f));
		model = glm::scale(model, glm::vec3(1.2f, 1.0f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Mejillas (Laterales) ---
		// Mejilla Izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.85f, 1.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Mejilla Derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.85f, 1.0f, 0.1f));
		model = glm::scale(model, glm::vec3(0.2f, 0.8f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Trompa ---

		// 1. Mandíbula inferior
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.85f));
		model = glm::scale(model, glm::vec3(0.8f, 0.2f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2. Hocico principal 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.75f, 0.85f));
		model = glm::scale(model, glm::vec3(1.0f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 3. Puente de la nariz 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.95f, 0.8f));
		model = glm::scale(model, glm::vec3(0.8f, 0.2f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ====================
		// BOCA EN SEMICÍRCULO
		// ====================
		glUniform3f(colorLoc, 0.85f, 0.25f, 0.3f); // Color café muy oscuro/negro

		// Base de la sonrisa (Bloque central horizontal)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.65f, 1.11f));
		model = glm::scale(model, glm::vec3(0.4f, 0.1f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glUniform3f(colorLoc, wR, wG, wB);
		// Colmillo Izquierdo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.60f, 1.12f));
		model = glm::scale(model, glm::vec3(0.08f, 0.15f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Colmillo Derecho
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.60f, 1.12f));
		model = glm::scale(model, glm::vec3(0.08f, 0.15f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ======================
		// TORSO Y PANZA REDONDA
		// ======================
		// Torso
		glUniform3f(colorLoc, oR, oG, oB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -0.1f));
		model = glm::scale(model, glm::vec3(1.4f, 1.6f, 1.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Panza - Nivel 1
		glUniform3f(colorLoc, cR, cG, cB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.65f));
		model = glm::scale(model, glm::vec3(1.2f, 1.4f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Panza - Nivel 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, 0.8f));
		model = glm::scale(model, glm::vec3(0.8f, 1.0f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Panza - Nivel 3 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.45f, 0.9f));
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// =======================
		// BRAZOS (En escalera)
		// =======================
		glUniform3f(colorLoc, oR, oG, oB);

		// --- Brazo Izquierdo ---
		// Hombro izquierdo 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.8f, -0.1f, 0.25f)); // Retrasamos un poco Z para que la mano resalte más
		model = glm::scale(model, glm::vec3(0.45f, 0.6f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Antebrazo / Manita izquierda 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.8f, -0.5f, 0.65f)); 
		model = glm::scale(model, glm::vec3(0.45f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Brazo Derecho ---
		// Hombro derecho 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.8f, -0.1f, 0.25f));
		model = glm::scale(model, glm::vec3(0.45f, 0.6f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Antebrazo / Manita derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.8f, -0.5f, 0.65f)); 
		model = glm::scale(model, glm::vec3(0.45f, 0.4f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//==================================
		// PIERNAS (Simétricas en el eje X)
		//==================================
		glUniform3f(colorLoc, oR, oG, oB);

		// Pierna Izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.45f, -1.3f, 0.1f));
		model = glm::scale(model, glm::vec3(0.6f, 0.5f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pierna Derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.45f, -1.3f, 0.1f));
		model = glm::scale(model, glm::vec3(0.6f, 0.5f, 0.7f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// =========
		//   COLA 
		// =========
		glUniform3f(colorLoc, oR, oG, oB);

		// 1. Raíz de la cola 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -0.9f));
		model = glm::scale(model, glm::vec3(0.8f, 0.5f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 2. Segmento 2 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -1.2f));
		model = glm::scale(model, glm::vec3(0.6f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 3. Segmento 3 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.6f, -1.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.6f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 4. Segmento 4 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -1.7f));
		model = glm::scale(model, glm::vec3(0.4f, 0.5f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// 5. Punta de la cola 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, -1.8f));
		model = glm::scale(model, glm::vec3(0.3f, 0.4f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// ==========
		//   LLAMA 
		// ==========

		// Base de la llama (Roja, ancha, envuelve la punta de la cola)
		glUniform3f(colorLoc, yR, yG, yB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.8f));
		model = glm::scale(model, glm::vec3(0.6f, 0.4f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Centro/Corazón (Amarillo, más alto que la base roja)
		glUniform3f(colorLoc, rR, rG, rB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -1.8f));
		model = glm::scale(model, glm::vec3(0.4f, 0.6f, 0.4f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Corona roja (Anillo superior del fuego)
		glUniform3f(colorLoc, rR, rG, rB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, -1.8f));
		model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Chispa amarilla (Punta central final de la llama)
		glUniform3f(colorLoc, yR, yG, yB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.8f));
		model = glm::scale(model, glm::vec3(0.2f, 0.3f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// =================
		// BRASAS / CHISPAS 
		// =================

		// Brasa 1
		glUniform3f(colorLoc, 1.0f, 0.5f, 0.0f); // Naranja intenso
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.4f, 0.6f, -1.7f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 2
		glUniform3f(colorLoc, yR, yG, yB); 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, 0.85f, -1.85f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 3 
		glUniform3f(colorLoc, 1.0f, 0.5f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 1.1f, -1.75f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 4 
		glUniform3f(colorLoc, rR, rG, rB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -1.45f));
		model = glm::scale(model, glm::vec3(0.15f, 0.15f, 0.15f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 5 
		glUniform3f(colorLoc, 1.0f, 0.5f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, 0.4f, -1.6f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 6 (
		glUniform3f(colorLoc, yR, yG, yB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.05f, 1.25f, -1.8f));
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 7 
		glUniform3f(colorLoc, rR, rG, rB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.45f, 0.35f, -1.55f));
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 8 
		glUniform3f(colorLoc, 1.0f, 0.5f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.45f, 0.65f, -1.7f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 9 
		glUniform3f(colorLoc, 1.0f, 0.5f, 0.0f); // Naranja
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.7f, -2.2f)); 
		model = glm::scale(model, glm::vec3(0.12f, 0.12f, 0.12f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brasa 10 
		glUniform3f(colorLoc, rR, rG, rB); // Rojo
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.45f, -2.2f));
		model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ========
		//   OJOS
		// ========

		// --- Ojo Izquierdo ---
		// Parte Teal (Interior)
		glUniform3f(colorLoc, eR, eG, eB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.35f, 1.35f, 0.76f));
		model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Parte Blanca (Exterior)
		glUniform3f(colorLoc, wR, wG, wB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.55f, 1.35f, 0.76f));
		model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Ojo Derecho ---
		// Parte Teal (Interior)
		glUniform3f(colorLoc, eR, eG, eB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.35f, 1.35f, 0.76f));
		model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Parte Blanca (Exterior)
		glUniform3f(colorLoc, wR, wG, wB);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.55f, 1.35f, 0.76f));
		model = glm::scale(model, glm::vec3(0.2f, 0.7f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//=====================
		// GARRAS DE LOS PIES
		//=====================
		glUniform3f(colorLoc, wR, wG, wB);

		// --- Garras Pie Izquierdo ---
		// Garra exterior izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, -1.45f, 0.5f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Garra interior izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -1.45f, 0.5f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// --- Garras Pie Derecho ---
		// Garra interior derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -1.45f, 0.5f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Garra exterior derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -1.45f, 0.5f));
		model = glm::scale(model, glm::vec3(0.15f, 0.2f, 0.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);

				

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow* window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.0008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.04f;
 }


