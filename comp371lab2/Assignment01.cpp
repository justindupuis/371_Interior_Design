/**
 * Assignment 1
 * Justin Dupuis - 29690352
 */

#include "stdafx.h"
#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm.hpp>
#include <matrix_transform.hpp>
#include <type_ptr.hpp>

using namespace std;

/**
 * Globals
 */

 // GUI Components
GLFWwindow* window;

//Create objects
GLuint VAO, VBO_Spinner, VBO_Rotator;

//Vertex Shader
GLuint vertexShader;
string vertex_shader_path;
string VertexShaderCode;
char const * VertexSourcePointer;

//Fragment Shader
GLuint fragmentShader;
char const * fragmentSourcePointer;
string fragment_shader_path;
string fragmentShaderCode;

//Shader Program
GLuint shaderProgram;

//Error attributes
GLint success;
GLchar infoLog[512];

// Window Dimensions
const GLuint INT_WIDTH = 800;
const GLuint INT_HEIGHT = 800;

//Rendering Settings
int intRenderMode;			//NOTE: Primitives for rendering mode = GL_POINTS, GL_TRIANGLES, GL_LINE_STRIP
GLclampf clrRed;
GLclampf clrGreen;
GLclampf clrBlue;
GLclampf clrAlpha;

//Transformations
glm::mat4 objectTransformation;
GLfloat spinnerScale[] = {1.0f, 1.0f , 1.0f};
GLfloat sizeStep;			//The increment by which size should be multiplied or divided
GLfloat rotateStep;
GLfloat rotateOffset;

//General Orientation
glm::vec3 orientationUp;


//Camera Positioning
glm::vec3 cameraPosition;
glm::vec3 cameraTarget;
glm::vec3 cameraDirection;
glm::vec3 cameraRight;
glm::vec3 cameraUp;
glm::mat4 cameraView;
glm::mat4 cameraProjection;

//Camera Rotation
GLfloat cameraRadius;
GLfloat cameraX;
GLfloat cameraZ;

//Camera Zoom
bool bolZoomEnabled;
int intCameraCurrentZoomLevel;

int intCameraZoom;
int intCameraRotation;
int intCameraPositionXOffset;
int intCameraPositionZOffset;

//Track if zooming or rotating camera
bool bolRotateCam;
bool bolZoomCam;

//Track object rotation
GLfloat fltObjectPositionX;

//track if resizing spinner
int intSpinnerIncrement = 0;
int intSpinnerShrinkMagnitude = 0;

/*Objects
 * Corodinates; (x,y,z,-,-,-) - (L/R,U/D,F/B)
 * Color: (-,-,-,R,G,B) - Alpha handled at the shader level across the entire object
 */

//SPINNER
GLfloat spinnerVertices[] = {
	//SPINNER
	-0.4f,-0.4f,-0.4f,	0.4f, 0.0f, 0.0f,	//Triangle 1
	-0.4f,-0.4f, 0.4f,	0.4f, 0.0f, 0.0f,
	-0.4f, 0.4f, 0.4f,	0.4f, 0.0f, 0.0f,

	0.4f, 0.4f,-0.4f,	0.95f, 0.0f, 0.0f,	//Triangle 2
	-0.4f,-0.4f,-0.4f,	0.95f, 0.0f, 0.0f,
	-0.4f, 0.4f,-0.4f,	0.95f, 0.0f, 0.0f,

	0.4f,-0.4f, 0.4f,	0.90f, 0.0f, 0.0f,	//Triangle 3
	-0.4f,-0.4f,-0.4f,	0.90f, 0.0f, 0.0f,
	0.4f,-0.4f,-0.4f,	0.90f, 0.0f, 0.0f,

	0.4f, 0.4f,-0.4f,	0.85f, 0.0f, 0.0f,	//Triangle 4
	0.4f,-0.4f,-0.4f,	0.85f, 0.0f, 0.0f,
	-0.4f,-0.4f,-0.4f,	0.85f, 0.0f, 0.0f,

	-0.4f,-0.4f,-0.4f,	0.8f, 0.0f, 0.0f,	//Triangle 5
	-0.4f, 0.4f, 0.4f,	0.8f, 0.0f, 0.0f,
	-0.4f, 0.4f,-0.4f,	0.8f, 0.0f, 0.0f,

	0.4f,-0.4f, 0.4f,	0.75f, 0.0f, 0.0f,	//Triangle 6
	-0.4f,-0.4f, 0.4f,	0.75f, 0.0f, 0.0f,
	-0.4f,-0.4f,-0.4f,	0.75f, 0.0f, 0.0f,

	-0.4f, 0.4f, 0.4f,	0.7f, 0.0f, 0.0f,	//Triangle 7
	-0.4f,-0.4f, 0.4f,	0.7f, 0.0f, 0.0f,
	0.4f,-0.4f, 0.4f,	0.7f, 0.0f, 0.0f,

	0.4f, 0.4f, 0.4f,	0.65f, 0.0f, 0.0f,	//Triangle 8
	0.4f,-0.4f,-0.4f,	0.65f, 0.0f, 0.0f,
	0.4f, 0.4f,-0.4f,	0.65f, 0.0f, 0.0f,

	0.4f,-0.4f,-0.4f,	0.6f, 0.0f, 0.0f,	//Triangle 9
	0.4f, 0.4f, 0.4f,	0.6f, 0.0f, 0.0f,
	0.4f,-0.4f, 0.4f,	0.6f, 0.0f, 0.0f,

	0.4f, 0.4f, 0.4f,	0.55f, 0.0f, 0.0f,	//Triangle 10
	0.4f, 0.4f,-0.4f,	0.55f, 0.0f, 0.0f,
	-0.4f, 0.4f,-0.4f,	0.55f, 0.0f, 0.0f,

	0.4f, 0.4f, 0.4f,	0.5f, 0.0f, 0.0f,	//Triangle 11
	-0.4f, 0.4f,-0.4f,	0.5f, 0.0f, 0.0f,
	-0.4f, 0.4f, 0.4f,	0.5f, 0.0f, 0.0f,

	0.4f, 0.4f, 0.4f,	0.45f, 0.0f, 0.0f,	//Triangle 12
	-0.4f, 0.4f, 0.4f,	0.45f, 0.0f, 0.0f,
	0.4f,-0.4f, 0.4f,	0.45f, 0.0f, 0.0f,

	//ROTATOR
	1.6f,-0.2f,-0.2f,	0.0f, 0.1f, 0.0f,	//Triangle 1
	1.6f,-0.2f, 0.2f,	0.0f, 0.1f, 0.2f,
	1.6f, 0.2f, 0.2f,	0.0f, 0.1f, 0.2f,

	2.0f, 0.2f,-0.2f,	0.0f, 0.95f, 0.0f,	//Triangle 2
	1.6f,-0.2f,-0.2f,	0.0f, 0.95f, 0.0f,
	1.6f, 0.2f,-0.2f,	0.0f, 0.95f, 0.0f,

	2.0f,-0.2f, 0.2f,	0.0f, 0.90f, 0.0f,	//Triangle 3
	1.6f,-0.2f,-0.2f,	0.0f, 0.90f, 0.0f,
	2.0f,-0.2f,-0.2f,	0.0f, 0.90f, 0.0f,

	2.0f, 0.2f,-0.2f,	0.0f, 0.85f, 0.0f,	//Triangle 4
	2.0f,-0.2f,-0.2f,	0.0f, 0.85f, 0.0f,
	1.6f,-0.2f,-0.2f,	0.0f, 0.85f, 0.0f,

	1.6f,-0.2f,-0.2f,	0.0f, 0.8f, 0.0f,	//Triangle 5
	1.6f, 0.2f, 0.2f,	0.0f, 0.8f, 0.0f,
	1.6f, 0.2f,-0.2f,	0.0f, 0.8f, 0.0f,

	2.0f,-0.2f, 0.2f,	0.0f, 0.75f, 0.0f,	//Triangle 6
	1.6f,-0.2f, 0.2f,	0.0f, 0.75f, 0.0f,
	1.6f,-0.2f,-0.2f,	0.0f, 0.75f, 0.0f,

	1.6f, 0.2f, 0.2f,	0.0f, 0.7f, 0.0f,	//Triangle 7
	1.6f,-0.2f, 0.2f,	0.0f, 0.7f, 0.0f,
	2.0f,-0.2f, 0.2f,	0.0f, 0.7f, 0.0f,

	2.0f, 0.2f, 0.2f,	0.0f, 0.65f, 0.0f,	//Triangle 8
	2.0f,-0.2f,-0.2f,	0.0f, 0.65f, 0.0f,
	2.0f, 0.2f,-0.2f,	0.0f, 0.65f, 0.0f,

	2.0f,-0.2f,-0.2f,	0.0f, 0.6f, 0.0f,	//Triangle 9
	2.0f, 0.2f, 0.2f,	0.0f, 0.6f, 0.0f,
	2.0f,-0.2f, 0.2f,	0.0f, 0.6f, 0.0f,

	2.0f, 0.2f, 0.2f,	0.0f, 0.55f, 0.0f,	//Triangle 10
	2.0f, 0.2f,-0.2f,	0.0f, 0.55f, 0.0f,
	1.6f, 0.2f,-0.2f,	0.0f, 0.55f, 0.0f,

	2.0f, 0.2f, 0.2f,	0.0f, 0.5f, 0.0f,	//Triangle 11
	1.6f, 0.2f,-0.2f,	0.0f, 0.5f, 0.0f,
	1.6f, 0.2f, 0.2f,	0.0f, 0.5f, 0.0f,

	2.0f, 0.2f, 0.2f,	0.0f, 0.25f, 0.0f,	//Triangle 12
	1.6f, 0.2f, 0.2f,	0.0f, 0.25f, 0.0f,
	2.0f,-0.2f, 0.2f,	0.0f, 0.25f, 0.0f
};

//Object positions
glm::vec3 objectPositions[] = {
	glm::vec3(0.0f,0.0f,0.0f)
};


/**
 * Constructor
 */
void init() {
	intRenderMode = GL_TRIANGLES;

	//Specify the default values for the color buffer when glClear is called
	clrRed = 0.1f;
	clrGreen = 0.1f;
	clrBlue = 0.2f;
	clrAlpha = 0.2f;

	//Transformation Defaults
	sizeStep = 0.05f;
	rotateStep = 15.0f;//degrees

	//Orientation
	orientationUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Default camera positioning
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
	cameraRight = glm::normalize(glm::cross(orientationUp,cameraDirection));
	cameraUp = glm::cross(cameraDirection,cameraRight);
	cameraView = glm::lookAt(
				cameraPosition,
				cameraTarget,
				orientationUp
	);

	//Camera Controls
	cameraRadius = 10.0f; //Not setting cameraX and cameraY here, because they will be set on rendering
	intCameraZoom = 10;
	intCameraRotation = 10;

	bolRotateCam = true;
}

/**
 * Change the level of zoom of the camera
 */
void updateCameraPositionZoom() {
	cameraX = intCameraZoom;
	cameraZ = intCameraZoom;
	bolZoomCam = false;
}

/**
 * Change the amount of rotation of the camera
 */
void updateCameraPositionRotate() {
	cameraX = sin(intCameraRotation) * cameraRadius;
	cameraZ = cos(intCameraRotation) * cameraRadius;
	bolRotateCam = false;
}

/**
 * Increase the size of Spinner
 */
void increaseSpinnerScale() {
	std::cout << "Increasing Spinner Size" << std::endl;
	spinnerScale[0] = spinnerScale[0] + sizeStep;
	spinnerScale[1] = spinnerScale[1] + sizeStep;
	spinnerScale[2] = spinnerScale[2] + sizeStep;
}

/**
* Decrease the size of Spinner
*/
void decreaseSpinnerScale() {
	std::cout << "Decreasing Spinner Size" << std::endl;
	spinnerScale[0] = spinnerScale[0] - sizeStep;
	spinnerScale[1] = spinnerScale[1] - sizeStep;
	spinnerScale[2] = spinnerScale[2] - sizeStep;
}

/**
* Change the rotational position of Spinner and the revolution position of Revolver.
* This can be done with the same method because they are supposed to be in sync.
*/
void updateRotation() {
	fltObjectPositionX = fmod(glfwGetTime(), 360);
	if (fltObjectPositionX >= 360) {
		fltObjectPositionX = 0;
	}
}

/**
 * Capture mouse clicks
 */
void mouseButton_callback(GLFWwindow* window, int button, int action, int mods) {
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (action == GLFW_PRESS) {
				bolZoomEnabled = true;
			}
			else if (action == GLFW_RELEASE) {
				bolZoomEnabled = false;
			}
		}
	}
}

/**
* Capture cursor position
*/
void cursorPosition_callback(GLFWwindow* window, double xPosition, double yPosition) {

	if (bolZoomEnabled == true) {
		std::cout << "Y Start: " + std::to_string(intCameraCurrentZoomLevel) + ", Y END:" + std::to_string(yPosition) << std::endl;
		intCameraZoom =  intCameraZoom+((yPosition + 90 - intCameraCurrentZoomLevel) /100);//intCameraCurrentZoomLevel + ((yPosition - intCameraCurrentZoomLevel + 90) / 100);
		cameraRadius = intCameraZoom + 10; //TO-DO: Fix this formula so the object doesn't jump
		if (intCameraZoom < 1) {
			intCameraZoom = 1;
		}

		else if (intCameraZoom > 60) {
			intCameraZoom = 60;
		}
		bolZoomCam = true;
	}
	else {
		intCameraCurrentZoomLevel = yPosition;
	}
}

/**
 * Input handler: Is called whenever a key is pressed/released via GLFW
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifiers)
{
	//detect input
	std::cout << key << std::endl;

	//if key pressed
	if (action == GLFW_PRESS) {

		//Close window on escape
		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		//Increase spinner size on S
		else if (key == GLFW_KEY_S) {
			if (modifiers == GLFW_MOD_SHIFT) {
				//Capital S, increase size of spinner if it hasn't reached maximum size
				if (intSpinnerShrinkMagnitude > 0) {
					increaseSpinnerScale();
					intSpinnerIncrement = 5;
					intSpinnerShrinkMagnitude--;
				}
			}
			else {
				//Small S, decrease size of spinner if it hasn't reache minimum size
				if (intSpinnerShrinkMagnitude < 10) {
					decreaseSpinnerScale();
					intSpinnerIncrement = -5;
					intSpinnerShrinkMagnitude++;
				}
			}
		}

		//Increase revolver size on R
		else if (key == GLFW_KEY_ESCAPE) {
			//TO-DO
		}

		//Decreaser revolver size on r
		else if (key == GLFW_KEY_ESCAPE) {
			//TO-DO
		}

		//Rotate left on left arrow
		else if (key == GLFW_KEY_LEFT) {
			//rotateOffset += rotateStep;

			intCameraRotation -= 5;
			bolRotateCam = true;
			
		}

		//Rotate right on right arrow
		else if (key == GLFW_KEY_RIGHT) {
			//rotateOffset -= rotateStep;

			intCameraRotation += 5;
			bolRotateCam = true;
			
		}

		//Rotate up on up arrow
		else if (key == GLFW_KEY_DOWN) {
			//TO-DO
		}

		//Rotate down on down arrow
		else if (key == GLFW_KEY_UP) {
			//TO-DO
		}

		//Change rendering to Points on P
		else if (key == GLFW_KEY_P) {
			intRenderMode = GL_POINTS;
		}

		//Change rendering to Lines on W
		else if (key == GLFW_KEY_W) {
			intRenderMode = GL_LINES;
		}

		//Change rendering to Triangles on T
		else if (key == GLFW_KEY_T) {
			intRenderMode = GL_TRIANGLES;
		}
	}
}


/**
 * Display initialization message on startup 
 */
void printWelcomeMessage() {
	//Display instructions in cmd
	std::cout << "Launching Assignment 1 - Justin Dupuis" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "The following controls have been implemented:" << std::endl;
	std::cout << "- Rendering Mode:" << std::endl;
	std::cout << "P for points" << std::endl;
	std::cout << "W for lines" << std::endl;
	std::cout << "T for Triangles" << std::endl;
	std::cout << "- Spinner Size:" << std::endl;
	std::cout << "S to increase" << std::endl;
	std::cout << "s to decrease" << std::endl;
	std::cout << "- Camera:" << std::endl;
	std::cout << "L-Arrow to rotate left" << std::endl;
	std::cout << "R-Arrow to rotate right" << std::endl;
	std::cout << "L-click + drag forward or backward to zoom" << std::endl;
}


/**
 * Initialize the framework
 */
void initializeGLFW() {
	// Initialize  GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}


/**
 * Create a window to display
 */
int initializeEnvironment() {
	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(INT_WIDTH, INT_HEIGHT, "Assignment 01", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Set the window to the current context
	glfwMakeContextCurrent(window);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
}


/**
 * Setup requirements to capture input
 */
void initializeInput() {
	//Set the required callback functions
	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouseButton_callback);
	glfwSetCursorPosCallback(window, cursorPosition_callback);
}


/**
 * Setup the vertex shader
 */
void initializeVertexShader() {
	// Read the Vertex Shader code from the file
	vertex_shader_path = "vertex.shader";
	VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, ios::in);

	if (VertexShaderStream.is_open()) {
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);
}


/**
* Setup the fragment shader
*/
void initializeFragmentShader() {
	// Read the Fragment Shader code from the file
	fragment_shader_path = "fragment.shader"; 
	std:: string fsc;
	fragmentShaderCode = fsc;

	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);

	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			fragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", fragment_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentSourcePointer = fragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &fragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);
}


/**
 * Check for compile time errors
 */
void checkInitializationErrors() {
	// Check for compile time errors


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

/**
 * Link vertex and fragment shaders
 */
void initializeShaderProgram() {
	// Link shaders
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);


	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//free up memory
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glUseProgram(shaderProgram);
}

void initializeVBO(GLuint VBO, GLfloat vertices[], int intArraySize) {

	std::cout << vertices << std::endl;

	glGenBuffers(1, &VBO);		//first parameter is the number of VBO names to generate
	/**
	* START: SPINNER INITIALIZATION
	*/
	//Bind the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Create and initialize the buffer objects data store
	glBufferData(
		GL_ARRAY_BUFFER,			//Target to push the data store
		intArraySize,	//Size in bytes of the data store
		vertices,			//Data store
		GL_STATIC_DRAW				//Expected usage pattern of the data store. 
									/* Frequency:
									STREAM: The data store contents will be modified once and used at most a few times.
									STATIC: The data store contents will be modified once and used many times.
									DYNAMIC: The data store contents will be modified repeatedly and used many times.
									Nature:
									DRAW: The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
									READ: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
									COPY: The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.
									*/
	);

	/***** SET VERTEX SHADER ATTRIBUTES BASED ON INPUT MATRIX *****/

	//Set the position attribute
	glVertexAttribPointer(
		0,								//Which vertex shader attribute to config: 0 = position
		3,								//Size of the vertex attribute
		GL_FLOAT,						//attribute datatype
		GL_FALSE,						//Whether data should be normalized if values aren't between -1 and 1
		6 * sizeof(GLfloat),			//Stride: The space between consecutive vertex attribute sets. Can set to 0 to force OpenGL to decide
		(GLvoid*)0						//Offset of where the position data begins. Casts 0 to GLvoid datatype
	);
	glEnableVertexAttribArray(0);

	//Set the color attribute
	glVertexAttribPointer(
		1,								//Which vertex shader attribute to config: 1 = color
		3,								//Size of the vertex attribute
		GL_FLOAT,						//attribute datatype
		GL_FALSE,						//Whether data should be normalized if values aren't between -1 and 1
		6 * sizeof(GLfloat),			//Stride: The space between consecutive vertex attribute sets. Can set to 0 to force OpenGL to decide
		(GLvoid*)(3 * sizeof(GLfloat))	//Offset of where the color data begins. Casts to GLvoid datatype
	);
	glEnableVertexAttribArray(1);

	// The call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object, so unbind it
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}

/**
 * MAIN FUNCTION
 */
int main()
{
	// Setup application
	init();
	printWelcomeMessage();
	initializeGLFW();
	initializeEnvironment();
	initializeInput();
	initializeVertexShader();
	initializeFragmentShader();
	checkInitializationErrors();
	initializeShaderProgram();
	


	//Generate vertex array & buffer objects
	glGenVertexArrays(1, &VAO);	//first parameter is the number of VAO names to generate
	glGenBuffers(1, &VBO_Rotator);		//first parameter is the number of VBO names to generate

										// Bind the Vertex Array Object
	glBindVertexArray(VAO);


	initializeVBO(VBO_Spinner, spinnerVertices, sizeof(spinnerVertices));

	// Unbind VAO (best practice = unbind buffers/arrays to prevent bugs), Note: do NOT unbind the EBO, keep it bound to this VAO
	glBindVertexArray(0);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check for events (ex: key pressed), call corresponding response functions
		glfwPollEvents();

		// Set RGB/ALpha values used when glClear is called.
		glClearColor(clrRed, clrGreen, clrBlue, clrAlpha);
		glScalef(10.5, 10.5, 10.5);

		// Clear the colorbuffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Control spinner resize
		if (intSpinnerIncrement > 1) {
			intSpinnerIncrement--;
		}
		else if (intSpinnerIncrement == 1) {
			decreaseSpinnerScale();
			intSpinnerIncrement--;
		}
		else if (intSpinnerIncrement < -1) {
			intSpinnerIncrement++;
		}
		else if (intSpinnerIncrement == -1) {
			increaseSpinnerScale();
			intSpinnerIncrement++;
		}

		//Calculate transformation to Scale
		objectTransformation = glm::scale(objectTransformation, glm::vec3(spinnerScale[0], spinnerScale[1], spinnerScale[2]));

		//Rotate Spinner
		updateRotation();
		glRotatef(fltObjectPositionX, 0.0f, 1.0f, 0.0f);

		//Get the transformation uniform location
		GLuint uniformTransform = glGetUniformLocation(shaderProgram, "transform");

		//Pass transform info to shader
		glUniformMatrix4fv(
			uniformTransform,
			1,
			GL_FALSE,
			glm::value_ptr(objectTransformation)
		);


		// Recalculate where the camera should be positioned

		if (bolZoomCam) {
			updateCameraPositionZoom();
		}


		if (bolRotateCam) {
			updateCameraPositionRotate();
		}
		//set the camera view
		cameraView = glm::lookAt(
						glm::vec3(
							cameraX, 
							0.0f, 
							cameraZ
						), //camera position
						cameraTarget, 
						orientationUp
		);

		// Set the camera projection 
		cameraProjection =	glm::perspective(
								45.0f, 
								(GLfloat)INT_WIDTH / (GLfloat) INT_HEIGHT, 
								0.1f, 
								100.0f
							);

		// Get the uniform locations
		GLint uniformModel = glGetUniformLocation(shaderProgram, "model");
		GLint uniformView = glGetUniformLocation(shaderProgram, "view");
		GLint uniformProjection = glGetUniformLocation(shaderProgram, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(
			uniformView, 
			1, 
			GL_FALSE, 
			glm::value_ptr(cameraView)
		);

		glUniformMatrix4fv(
			uniformProjection, 
			1, 
			GL_FALSE, 
			glm::value_ptr(cameraProjection)
		);

		//Bind the VAO
		glBindVertexArray(VAO);

		//Calculate and pass the model matrix for each object prior to rendering
		glm::mat4 model;
		GLfloat angle;

		//iterate on all objects
		for (GLuint i = 0; i < 1; i++)
		{			
			model = glm::translate(model, objectPositions[i]);
			model = glm::rotate(model, fltObjectPositionX, orientationUp);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

			glDrawArrays(intRenderMode, 0, sizeof(spinnerVertices) / 6);
		}

		//Unbind the VAO
		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_Spinner);
	glDeleteBuffers(1, &VBO_Rotator);

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
