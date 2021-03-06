// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "common/shader.hpp"
#include "common/controls.hpp"

#include <vector>
#include "common/objloader.hpp"
#include "common/text2D.hpp"


/*glm::mat4 getMVPMatrix() {



	//int FoV = 45;
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), // The vertical Field of View, usually between 90�(extra wide) and 30�(quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window.
		0.1f, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f // Far clipping plane. Keep as little as possible.
	);

	glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, -3), // Camera is at (4,3,-3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside - down)
		);

	glm::mat4 Model = glm::mat4(1.0f); // keep an identity matrix so the geometry stays where it was placed originally

		// Our ModelViewProjection : multiplication of our 3 matrices*/

glm::mat4 getMVPMatrix(glm::mat4 ModelMatrix) {
	int FoV = 45;
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), // The vertical Field of View, usually between 90�(extra wide) and 30�(quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window.
		0.1f, // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f // Far clipping plane. Keep as little as possible.
	);
	glm::mat4 View = glm::lookAt(
		glm::vec3(0, 20, -25), // Camera is at (4,3,-3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside - down)
	);
	glm::mat4 Model = ModelMatrix;
	glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around

	return mvp;

}

//}

int width = 1024;
int height = 768;
int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( width, height, "Donut Collector", NULL, NULL);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(window, width / 2, height / 2);

	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; //Needed for core profile

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Initialise Vertex Array Object
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("map.obj", vertices, normals);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices1;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals1; // Won't be used at the moment.
	bool res1 = loadOBJ("player.obj", vertices1, normals1);

	GLuint vertexbuffer1;
	glGenBuffers(1, &vertexbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
	glBufferData(GL_ARRAY_BUFFER, vertices1.size() * sizeof(glm::vec3), &vertices1[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices2;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals2; // Won't be used at the moment.
	bool res2 = loadOBJ("donut.obj", vertices2, normals2);

	GLuint vertexbuffer2;
	glGenBuffers(1, &vertexbuffer2);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
	glBufferData(GL_ARRAY_BUFFER, vertices2.size() * sizeof(glm::vec3), &vertices2[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices3;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals3; // Won't be used at the moment.
	bool res3 = loadOBJ("donut.obj", vertices3, normals3);

	GLuint vertexbuffer3;
	glGenBuffers(1, &vertexbuffer3);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
	glBufferData(GL_ARRAY_BUFFER, vertices3.size() * sizeof(glm::vec3), &vertices3[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices4;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals4; // Won't be used at the moment.
	bool res4 = loadOBJ("donut.obj", vertices4, normals4);

	GLuint vertexbuffer4;
	glGenBuffers(1, &vertexbuffer4);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
	glBufferData(GL_ARRAY_BUFFER, vertices4.size() * sizeof(glm::vec3), &vertices4[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices5;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals5; // Won't be used at the moment.
	bool res5 = loadOBJ("donut.obj", vertices5, normals5);

	GLuint vertexbuffer5;
	glGenBuffers(1, &vertexbuffer5);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
	glBufferData(GL_ARRAY_BUFFER, vertices5.size() * sizeof(glm::vec3), &vertices5[0], GL_STATIC_DRAW);

	std::vector<glm::vec3> vertices6;
	//std::vector<glm::vec2> uvs; // Won't be used at the moment.
	std::vector<glm::vec3> normals6; // Won't be used at the moment.
	bool res6 = loadOBJ("donut.obj", vertices6, normals6);

	GLuint vertexbuffer6;
	glGenBuffers(1, &vertexbuffer6);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
	glBufferData(GL_ARRAY_BUFFER, vertices6.size() * sizeof(glm::vec3), &vertices6[0], GL_STATIC_DRAW);



	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//static const GLfloat g_vertex_buffer_data[] = {
		/*-1.0f,-1.0f,-1.0f, 
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 
		1.0f, 1.0f,-1.0f, 
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, 
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f*/
		// Read our .obj file

	//};

	GLuint programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");

	// One color for each vertex.
	/*static const GLfloat g_color_buffer_data[] = {
		1.0f,  1.0f,  0.0f, //RGB
		1.0f,  1.0f,  0.0f,
		1.0f,  1.0f,  0.0f,

		1.0f,  1.0f,  0.0f, //RGB
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
	};

	static const GLfloat g_color_buffer_data1[] = {
		0.0f,  1.0f,  0.0f, //RGB
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,

		0.0f,  1.0f,  0.0f, //RGB
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
	};*/
	/*GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);*/

	/*GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GLuint colorbuffer1;
	glGenBuffers(1, &colorbuffer1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data1), g_color_buffer_data1, GL_STATIC_DRAW);*/

	GLuint MatrixID1 = glGetUniformLocation(programID, "MVP");
	vec3 playerSpawnLocation = vec3(0.0, 0.0, 0.0);
	vec3 donutSpawnLocation = vec3(-1.5, 0.0, -10.0);
	vec3 donutSpawnLocation2 = vec3(-10.0, 0.0, 10.0);
	vec3 donutSpawnLocation3 = vec3(8, 0.0, -10.0);
	vec3 donutSpawnLocation4 = vec3(-10.0, 0.0, -10.0);
	vec3 donutSpawnLocation5 = vec3(8, 0.0, 10.0);
	do{
		// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
		glClear( GL_COLOR_BUFFER_BIT );

		computeMatricesFromInputs(width, height);



		/*glm::mat4 mvp1 = getMVPMatrix(
			getProjectionMatrix(),
			getViewMatrix(),
			glm::mat4(1.0f));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1[0][0]);*/

		glm::mat4 mvp1 = getMVPMatrix(
			glm::mat4(1.0));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1[0][0]);
		
		// Use our shader
		glUseProgram(programID);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(res));


		glm::mat4 mvp2;
		
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
		{
			
			playerSpawnLocation = playerSpawnLocation + vec3(0.0, 0.0, 0.05);
			mvp2 = getMVPMatrix(glm::translate(playerSpawnLocation));
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			playerSpawnLocation = playerSpawnLocation + vec3(0.05, 0.0, 0.0);
			mvp2 = getMVPMatrix(glm::translate(playerSpawnLocation));
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			playerSpawnLocation = playerSpawnLocation + vec3(0.0, 0.0, -0.05);
			mvp2 = getMVPMatrix(glm::translate(playerSpawnLocation));
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			playerSpawnLocation = playerSpawnLocation + vec3(-0.05, 0.0, 0.0);
			mvp2 = getMVPMatrix(glm::translate(playerSpawnLocation));
		}
		else 
		{
			mvp2 = getMVPMatrix(glm::translate(playerSpawnLocation));
		}

		// 2nd attribute buffer : colors
		/*glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
		glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);*/
				
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp2[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer1);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices1.size() * sizeof(res1));


		glm::mat4 mvp3 = getMVPMatrix(glm::translate(donutSpawnLocation));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp3[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer2);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices2.size() * sizeof(res2));

		glm::mat4 mvp4 = getMVPMatrix(glm::translate(donutSpawnLocation2));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp4[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer3);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices3.size() * sizeof(res3));

		glm::mat4 mvp5 = getMVPMatrix(glm::translate(donutSpawnLocation3));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp5[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer4);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices4.size() * sizeof(res4));

		glm::mat4 mvp6 = getMVPMatrix(glm::translate(donutSpawnLocation4));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp6[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer5);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices5.size() * sizeof(res5));

		glm::mat4 mvp7 = getMVPMatrix(glm::translate(donutSpawnLocation5));
		glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp7[0][0]);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer6);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset

		);

		glDrawArrays(GL_TRIANGLES, 0, vertices6.size() * sizeof(res6));

		// 2nd attribute buffer : colors
		/*glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer1);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);*/

		// Draw the triangles
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(glm::vec3));
		glDisableVertexAttribArray(0);



		// The following code draws a triangle using the function void glDrawArrays(     GLenum mode,      GLint first,      GLsizei count);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glDrawArrays(GL_TRIANGLES, 0, 36); // first vertex: 0, count: 1 triangle is drawn. 1 triangle x 3 vertices = 3

		//glDisableVertexAttribArray(0);

		//glDisableVertexAttribArray(1);

		// Draw nothing, see you in tutorial 2 !

		
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();



	} // Check if the ESC key was pressed or the window was closed

	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader

	glDeleteBuffers(1, &vertexbuffer);

	glDeleteProgram(programID);

	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

