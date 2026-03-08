/*
	Practica #5. Modelado jerárquico    |    Echevarria Aguilar Luis Angel
	Fecha de entrega: 08/03/2026        |    No. Cuenta: 320236235
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f, codo = 0.0f, muneca = 0.0f, dedo1 = 0.0f, dedo2 = 0.0f, falange1 = 0.0f, falange2 = 0.0f, falange3 = 0.0f;


int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "P5 - Echevarria Aguilar Luis Angel", nullptr, nullptr);

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
	// use with Orthographic Projection


	

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
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
		-0.5f,  0.5f, -0.5f,
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
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp



		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model Antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 0.0, 1.0f)); //codo
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0, 0.0f)); //muñeca
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		////Model Dedo1 A
		//model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));
		//model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0, 1.0f)); //dedo1
		//modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		//color = glm::vec3(0.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//D

		////Model Dedo1 B
		//model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		//model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0, 1.0f)); //dedo2
		//modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		//color = glm::vec3(1.0f, 0.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//glDrawArrays(GL_TRIANGLES, 0, 36);//E

		glm::mat4 modelPalmBase = modelTemp2; // Tomamos el centro de la palma como base

		for (int i = 0; i < 5; i++) {
			// Distribuir las garras en círculo (360 / 5 = 72 grados)
			glm::mat4 modelBaseGarra = glm::rotate(modelPalmBase, glm::radians(i * 72.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			// Mover la base de la garra al borde exterior frontal de la palma
			modelBaseGarra = glm::translate(modelBaseGarra, glm::vec3(0.25f, 0.4f, 0.0f));

			// Falange 1
			glm::mat4 modelF1 = glm::rotate(modelBaseGarra, glm::radians(falange1), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 modelDrawF1 = glm::translate(modelF1, glm::vec3(0.6f, 0.0f, 0.0f)); // Centro del cubo
			modelDrawF1 = glm::scale(modelDrawF1, glm::vec3(1.2f, 0.15f, 0.15f));
			color = glm::vec3(0.0f, 1.0f, 1.0f); // Cyan
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelDrawF1));
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Falange 2
			// Nos movemos al final de la Falange 1 (1.2f en X)
			glm::mat4 modelF2 = glm::translate(modelF1, glm::vec3(1.2f, 0.0f, 0.0f));
			modelF2 = glm::rotate(modelF2, glm::radians(falange2), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 modelDrawF2 = glm::translate(modelF2, glm::vec3(0.5f, 0.0f, 0.0f));
			modelDrawF2 = glm::scale(modelDrawF2, glm::vec3(1.0f, 0.12f, 0.12f));
			color = glm::vec3(1.0f, 0.0f, 1.0f); // Magenta
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelDrawF2));
			glDrawArrays(GL_TRIANGLES, 0, 36);

			// Falange 3
			// Nos movemos al final de la Falange 2 (1.0f en X)
			glm::mat4 modelF3 = glm::translate(modelF2, glm::vec3(1.0f, 0.0f, 0.0f));
			modelF3 = glm::rotate(modelF3, glm::radians(falange3), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 modelDrawF3 = glm::translate(modelF3, glm::vec3(0.4f, 0.0f, 0.0f));
			modelDrawF3 = glm::scale(modelDrawF3, glm::vec3(0.8f, 0.08f, 0.08f));
			color = glm::vec3(1.0f, 1.0f, 0.0f); // Amarillo
			glUniform3fv(uniformColor, 1, glm::value_ptr(color));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelDrawF3));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.008f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.008f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		 codo += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		 codo -= 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 muneca += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 muneca -= 0.18f;

	 // Límites físicos de la garra
	 // 1. Guardamos el estado ANTERIOR de las falanges
	 float prevF1 = falange1;
	 float prevF2 = falange2;
	 float prevF3 = falange3;

	 // 2. Aplicamos el movimiento basándonos en las teclas (con topes naturales de la articulación)
	 // Falange 1
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) falange1 += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) falange1 -= 0.18f;
	 if (falange1 > 45.0f) falange1 = 45.0f;   // Tope al abrir
	 if (falange1 < -90.0f) falange1 = -90.0f; // Tope físico al cerrar

	 // Falange 2
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) falange2 += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) falange2 -= 0.18f;
	 if (falange2 > 15.0f) falange2 = 15.0f;
	 if (falange2 < -90.0f) falange2 = -90.0f;

	 // Falange 3
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) falange3 += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) falange3 -= 0.18f;
	 if (falange3 > 15.0f) falange3 = 15.0f;
	 if (falange3 < -90.0f) falange3 = -90.0f;

	 // 3. Cálculo de colisión geometrica
	 // Sumamos los ángulos acumulados (convertidos a radianes para la trigonometría)
	 float rad1 = glm::radians(falange1);
	 float rad2 = glm::radians(falange1 + falange2);
	 float rad3 = glm::radians(falange1 + falange2 + falange3);

	 // Calculamos la altura (Y) de cada articulación respecto al centro usando el Seno.
	 // Nota: Se empieza en 0.4f porque esa es la distancia desde el centro a la que se dibujo la base.
	 float joint2_Y = 0.4f + (1.2f * sin(rad1));        // Altura del final de la Falange 1
	 float joint3_Y = joint2_Y + (1.0f * sin(rad2));    // Altura del final de la Falange 2
	 float tip_Y = joint3_Y + (0.8f * sin(rad3));       // Altura de la pura punta de la garra

	 // 4. Prevención de traspaso
	 // Verificamos si alguna parte de la garra intentó cruzar el "centro" (Y = 0).
	 if (joint2_Y < 0.08f || joint3_Y < 0.06f || tip_Y < 0.04f) {
		 // Si se detecta una colisión se revierte el movimiento del frame.
		 falange1 = prevF1;
		 falange2 = prevF2;
		 falange3 = prevF3;
	 }
 }


