/*
    Practica #6. Carga de modelos   |   Echevarria Aguilar Luis Angel
    Fecha de entrega: 15/03/2026    |   No. Cuenta: 320236235
*/


// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );


// Camera
Camera camera(glm::vec3(0.0f, 1.5f, 1.5f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;



int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "P6 - Echevarria Aguilar Luis Angel", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model dog((char*)"Models/RedDog.obj");
    Model butaca((char*)"Models/butaca.obj");
    Model lentes((char*)"Models/3dGlass.obj");
    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 2000.0f );
    
  

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // --- 1. Dibujar al Perrito Principal (En primera fila) ---
        glm::mat4 modelDog = glm::mat4(1.0f);
        // Lo movemos a la butaca central: X=0.0 (centro), Y=-0.5 (arriba del asiento), Z=-2.8 (apoyado en el respaldo)
        modelDog = glm::translate(modelDog, glm::vec3(-0.15f, 0.8f, -1.5f));

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelDog));
        dog.Draw(shader);

        //Lentes del perro

       // --- 5. Lentes 3D (Ajuste Final de Precisión) ---
        glm::mat4 modelLentes = glm::mat4(1.0f);

        // 1. POSICIÓN:
        // X: Cambiamos -1.28f a -0.9f (para mover a la derecha y centrar)
        // Y: Cambiamos 0.75f a 0.55f (para bajarlos a la altura de los ojos)
        // Z: Mantenemos 0.15f (o ajusta si se hunden en la cara)
        modelLentes = glm::translate(modelLentes, glm::vec3(-0.95f, 0.3f, 0.4f));

        // 2. ESCALA: (La que ya te funcionó)
        modelLentes = glm::scale(modelLentes, glm::vec3(0.05f, 0.05f, 0.05f));

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelLentes));
        lentes.Draw(shader);

        // --- 2. Dibujar las filas de Butacas ---
        for (int fila = 0; fila < 3; fila++) {
            for (int asiento = 0; asiento < 5; asiento++) {

                glm::mat4 modelButaca = glm::mat4(1.0f);

                // Aumentamos la separación lateral a 2.0f para que no se asfixien
                float separacionX = (asiento - 2) * 2.0f;
                // Aumentamos la separación hacia atrás a -3.0f para dar profundidad (-3, -6, -9)
                float separacionZ = (fila * -3.0f) - 3.0f;

                // El suelo de las butacas será Y = -2.0f
                modelButaca = glm::translate(modelButaca, glm::vec3(separacionX, -2.0f, separacionZ));

                glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(modelButaca));
                butaca.Draw(shader);
            }
        }
        

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }

 

 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

