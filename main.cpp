//Project in current state operates on vertices
//Model.h is for future version of the project


#include <glad/glad.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Camera.h"
#include "Board.h"



#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Board &board);


// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(3.5f, 3.0f, 14.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{

    Board board;
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader Shader_1("shader.vs", "shader.fs");
    Shader Shader_2("shader.vs", "white_shader.fs");
    Shader Shader_3("shader.vs", "black_shader.fs");
    Shader Shader_4("shader.vs", "select_shader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // vertices include both cubes
    // ------------------------------------------------------------------
    float vertices[] = {

                                            //FLAT CUBE
        // Front face
        -4.0f, -0.5f, -4.0f,  0.0f, 0.0f,
         4.0f, -0.5f, -4.0f,  1.0f, 0.0f,
         4.0f,  0.5f, -4.0f,  1.0f, 1.0f,
         4.0f,  0.5f, -4.0f,  1.0f, 1.0f,
        -4.0f,  0.5f, -4.0f,  0.0f, 1.0f,
        -4.0f, -0.5f, -4.0f,  0.0f, 0.0f,

        // Back face
        -4.0f, -0.5f,  4.0f,  0.0f, 0.0f,
         4.0f, -0.5f,  4.0f,  1.0f, 0.0f,
         4.0f,  0.5f,  4.0f,  1.0f, 1.0f,
         4.0f,  0.5f,  4.0f,  1.0f, 1.0f,
        -4.0f,  0.5f,  4.0f,  0.0f, 1.0f,
        -4.0f, -0.5f,  4.0f,  0.0f, 0.0f,

        // Left face
        -4.0f,  0.5f,  4.0f,  1.0f, 0.0f,
        -4.0f,  0.5f, -4.0f,  1.0f, 1.0f,
        -4.0f, -0.5f, -4.0f,  0.0f, 1.0f,
        -4.0f, -0.5f, -4.0f,  0.0f, 1.0f,
        -4.0f, -0.5f,  4.0f,  0.0f, 0.0f,
        -4.0f,  0.5f,  4.0f,  1.0f, 0.0f,

        // Right face
         4.0f,  0.5f,  4.0f,  1.0f, 0.0f,
         4.0f,  0.5f, -4.0f,  1.0f, 1.0f,
         4.0f, -0.5f, -4.0f,  0.0f, 1.0f,
         4.0f, -0.5f, -4.0f,  0.0f, 1.0f,
         4.0f, -0.5f,  4.0f,  0.0f, 0.0f,
         4.0f,  0.5f,  4.0f,  1.0f, 0.0f,

         // Top face
         -4.0f,  0.5f, -4.0f,  0.0f, 1.0f,
          4.0f,  0.5f, -4.0f,  1.0f, 1.0f,
          4.0f,  0.5f,  4.0f,  1.0f, 0.0f,
          4.0f,  0.5f,  4.0f,  1.0f, 0.0f,
         -4.0f,  0.5f,  4.0f,  0.0f, 0.0f,
         -4.0f,  0.5f, -4.0f,  0.0f, 1.0f,

         // Bottom face
         -4.0f, -0.5f, -4.0f,  0.0f, 1.0f,
          4.0f, -0.5f, -4.0f,  1.0f, 1.0f,
          4.0f, -0.5f,  4.0f,  1.0f, 0.0f,
          4.0f, -0.5f,  4.0f,  1.0f, 0.0f,
         -4.0f, -0.5f,  4.0f,  0.0f, 0.0f,
         -4.0f, -0.5f, -4.0f,  0.0f, 1.0f

                                            //Small CUBE        
                 // Front face
        - 0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
         0.25f, -0.25f, -0.25f,  0.5f, 0.0f,
         0.25f,  0.25f, -0.25f,  0.5f, 0.5f,
         0.25f,  0.25f, -0.25f,  0.5f, 0.5f,
        -0.25f,  0.25f, -0.25f,  0.0f, 0.5f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f,

        // Back face
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
         0.25f, -0.25f,  0.25f,  0.5f, 0.0f,
         0.25f,  0.25f,  0.25f,  0.5f, 0.5f,
         0.25f,  0.25f,  0.25f,  0.5f, 0.5f,
        -0.25f,  0.25f,  0.25f,  0.0f, 0.5f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f,

        // Left face
        -0.25f,  0.25f,  0.25f,  0.5f, 0.0f,
        -0.25f,  0.25f, -0.25f,  0.5f, 0.5f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.5f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.5f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
        -0.25f,  0.25f,  0.25f,  0.5f, 0.0f,

        // Right face
         0.25f,  0.25f,  0.25f,  0.5f, 0.0f,
         0.25f,  0.25f, -0.25f,  0.5f, 0.5f,
         0.25f, -0.25f, -0.25f,  0.0f, 0.5f,
         0.25f, -0.25f, -0.25f,  0.0f, 0.5f,
         0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
         0.25f,  0.25f,  0.25f,  0.5f, 0.0f,

        // Top face
        -0.25f,  0.25f, -0.25f,  0.0f, 0.5f,
         0.25f,  0.25f, -0.25f,  0.5f, 0.5f,
         0.25f,  0.25f,  0.25f,  0.5f, 1.0f,
         0.25f,  0.25f,  0.25f,  0.5f, 1.0f,
        -0.25f,  0.25f,  0.25f,  0.0f, 1.0f,
        -0.25f,  0.25f, -0.25f,  0.0f, 0.5f,

        // Bottom face
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
         0.25f, -0.25f, -0.25f,  0.5f, 0.0f,
         0.25f, -0.25f,  0.25f,  0.5f, 0.5f,
         0.25f, -0.25f,  0.25f,  0.5f, 0.5f,
        -0.25f, -0.25f,  0.25f,  0.0f, 0.5f,
        -0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
                                                
          

    };


    // postions of the chessboard
    glm::vec3 chessbordPostion(3.5f, -2.0f, 3.75f);

    //VAO and VBO for vertices with both cubes

    unsigned int VBO, VAO1;
    glGenVertexArrays(1, &VAO1);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO1);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture for chessboard
    // -------------------------
    unsigned int texture1;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("Check_board.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
  
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    Shader_1.use();
    Shader_1.setInt("texture1", 0);

    

   


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window, board);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        //Displaying the chessboard
        // activate shader chessboard
        Shader_1.use();
     

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        Shader_1.setMat4("projection", projection);
       
        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        Shader_1.setMat4("view", view);
       

        // render big box
        glBindVertexArray(VAO1);
        
        glm::mat4 cube1_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        cube1_model = glm::translate(cube1_model, chessbordPostion);
        Shader_1.setMat4("model", cube1_model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //Displaying the white chess pieces
        // activate shader white
        Shader_2.use();


        // pass projection matrix to shader (note that in this case it could change every frame)
         projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        Shader_2.setMat4("projection", projection);

        // camera/view transformation
         view = camera.GetViewMatrix();
        Shader_2.setMat4("view", view);


        // render small boxes
        
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board.chessboard[i][j].color == 'w')
                {
					glm::mat4 cube2_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					cube2_model = glm::translate(cube2_model, glm::vec3(1.f*j, -1.2f, 1.f * i));
					Shader_2.setMat4("model", cube2_model);
					glDrawArrays(GL_TRIANGLES, 36, 36);
				}
			}
		}

        //Displaying the black chess pieces
        // activate shader black
        Shader_3.use();


        // pass projection matrix to shader (note that in this case it could change every frame)
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        Shader_3.setMat4("projection", projection);

        // camera/view transformation
        view = camera.GetViewMatrix();
        Shader_3.setMat4("view", view);


        // render small boxes


        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board.chessboard[i][j].color == 'b')
                {
                    glm::mat4 cube2_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    cube2_model = glm::translate(cube2_model, glm::vec3( 1.f * j, -1.2f,  1.f * i));
                    Shader_3.setMat4("model", cube2_model);
                    glDrawArrays(GL_TRIANGLES, 36, 36);
                }
            }
        }

        //Displaying the select space 
        // activate select black
        Shader_4.use();


        // pass projection matrix to shader (note that in this case it could change every frame)
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        Shader_4.setMat4("projection", projection);

        // camera/view transformation
        view = camera.GetViewMatrix();
        Shader_4.setMat4("view", view);


        // render select space


        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board.chessboard[i][j].is_selected)
                {
                    std::cout << i << " " << j << std::endl;
                    glm::mat4 cube2_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    cube2_model = glm::translate(cube2_model, glm::vec3(1.f * j, -1.0f, 1.f * i));
                    Shader_4.setMat4("model", cube2_model);
                    glDrawArrays(GL_TRIANGLES, 36, 36);
                }
            }
        }





        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO1);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, Board &board)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

   

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        board.selection_movement(B_UP);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		board.selection_movement(B_DOWN);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        board.selection_movement(B_LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        board.selection_movement(B_RIGHT);
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}



// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}