//Project in current state operates on vertices


#include <glad/glad.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shaders.h"
#include "Camera.h"
#include "Board.h"
#include "model.h"
#include "mesh.h"



#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Board &board);
unsigned int loadTexture(const char* path);


// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

// camera
Camera camera(glm::vec3(13.5f, 5.0f, 3.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;



struct press_check {
	bool w = false;
    bool a = false;
    bool s = false;
    bool d = false;
    bool space = false; 
};

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CHESS", NULL, NULL);
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
    Shader Shader_1("shaders/shader.vs", "shaders/shader.fs");
    Shader Shader_2("shaders/shader.vs", "shaders/color_shader.fs");
    Shader Temp_Shader("shaders/model_shader.vs", "shaders/model_shader.fs");
    Model BPawn_Model("models/Black/pawn.obj");
    Model BKnight_Model("models/Black/knight.obj");
    Model BRook_Model("models/Black/rook.obj");
    Model BBishop_Model("models/Black/bishop.obj");
    Model BQueen_Model("models/Black/queen.obj");
    Model BKing_Model("models/Black/king.obj");

    Model WPawn_Model("models/White/Pawn.obj");
    Model WKnight_Model("models/White/Knight.obj");
    Model WRook_Model("models/White/Rook.obj");
    Model WBishop_Model("models/White/Bishop.obj");
    Model WQueen_Model("models/White/Queen.obj");
    Model WKing_Model("models/White/King.obj");



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
         -4.0f, -0.5f, -4.0f,  0.0f, 1.0f,

         
                                            //Select space
        // Front face
    -0.5f, -0.1f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.1f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.1f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.1f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.1f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.1f, -0.5f,  0.0f, 0.0f,

        // Back face
        -0.5f, -0.1f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.1f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.1f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.1f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.1f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.1f,  0.5f,  0.0f, 0.0f,

        // Left face
        -0.5f,  0.1f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.1f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.1f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.1f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.1f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.1f,  0.5f,  1.0f, 0.0f,

        // Right face
         0.5f,  0.1f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.1f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.1f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.1f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.1f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.1f,  0.5f,  1.0f, 0.0f,

        // Top face
        -0.5f,  0.1f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.1f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.1f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.1f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.1f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.1f, -0.5f,  0.0f, 1.0f,

        // Bottom face
        -0.5f, -0.1f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.1f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.1f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.1f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.1f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.1f, -0.5f,  0.0f, 1.0f
    

    };


    // postions of the chessboard
    glm::vec3 chessbordPostion(3.5f, -1.95f, 3.5f);

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


    //// load and create a texture for chessboard
    //// -------------------------
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
    unsigned char* data = stbi_load("textures/Check_board.jpg", &width, &height, &nrChannels, 0);
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
  
    //// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    //// -------------------------------------------------------------------------------------------
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

        //game logic

        board.piece_movement();

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        //configure tranformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 rotation_matrix(1.0f);//matrix of rotation 
        Shader_1.use();
        Shader_1.setMat4("projection", projection);
        Shader_1.setMat4("view", view);
        Shader_1.setMat4("rotation_matrix", rotation_matrix);
        Shader_2.use();
        Shader_2.setMat4("projection", projection);
        Shader_2.setMat4("view", view);
        Shader_2.setMat4("rotation_matrix", rotation_matrix);
        Temp_Shader.use();
        Temp_Shader.setMat4("projection", projection);
        Temp_Shader.setMat4("view", view);
        rotation_matrix = glm::rotate(rotation_matrix, glm::radians(1.0f), glm::normalize(glm::vec3(0, 1, 0))); //rotates the object
        Temp_Shader.setMat4("rotation_matrix", rotation_matrix);

        //Displaying the chessboard
        // activate shader chessboard
        Shader_1.use();
     
        // render big box
        glBindVertexArray(VAO1);
        
        glm::mat4 cube1_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        cube1_model = glm::translate(cube1_model, chessbordPostion);
        Shader_1.setMat4("model", cube1_model);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        //Displaying the highlight box
        // change color to green
        Shader_2.use();
        if (board.turn == 'w')
            Shader_2.setVec4("ourColor", glm::vec4(1.0, 0.992, 0.816, 1.0));
        else  Shader_2.setVec4("ourColor", glm::vec4(0.396, 0.263, 0.129, 1.0));

        // render select space


        glm::mat4 cube2_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        cube2_model = glm::translate(cube2_model, glm::vec3(1.f * board.highlight_box.y, -1.5f, 1.f * board.highlight_box.x));
        Shader_2.setMat4("model", cube2_model);
        glDrawArrays(GL_TRIANGLES, 36, 36);


        //Displaying the move spaces
       // change color to cyan
        
        Shader_2.setVec4("ourColor", glm::vec4(0.0, 0.545, 0.545, 1.0));

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board.chessboard[i][j].state == selected)
                {
                    glm::mat4 cube2_model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                    cube2_model = glm::translate(cube2_model, glm::vec3(1.f * j, -1.5f, 1.f * i));
                    Shader_2.setMat4("model", cube2_model);
                    glDrawArrays(GL_TRIANGLES, 36, 36);
                }
            }
        }


       

        //Displaying the  chess pieces
 
        Temp_Shader.use();

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {

                if (board.chessboard[i][j].color == 'w')
                {
                    if (board.chessboard[i][j].type == 'k')
                    {
						glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i));
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
                        Temp_Shader.setMat4("model", model);
                        WKing_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'p')
                    {

                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); 
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	
                        Temp_Shader.setMat4("model", model);
                        WPawn_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'n')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); 
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	
                        Temp_Shader.setMat4("model", model);

                        WKnight_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'b')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i));
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
                        Temp_Shader.setMat4("model", model);

                        WBishop_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'r')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i));
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	
                        Temp_Shader.setMat4("model", model);

                        WRook_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'q')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); 
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	
                        Temp_Shader.setMat4("model", model);

                        WQueen_Model.Draw(Temp_Shader);
                    }
                }

                if (board.chessboard[i][j].color == 'b')
                {
                    if (board.chessboard[i][j].type == 'k')
                    {
                        
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);
                        BKing_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'p')
                    {

                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);
                        BPawn_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'n')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);

                        BKnight_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'b')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                       model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);

                        BBishop_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'r')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);

                        BRook_Model.Draw(Temp_Shader);
                    }
                    if (board.chessboard[i][j].type == 'q')
                    {
                        glm::mat4 model = glm::mat4(1.0f);
                        model = glm::translate(model, glm::vec3(1.0f * j, -1.45f, 1.0f * i)); // translate it down so it's at the center of the scene
                        model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));	// it's a bit too big for our scene, so scale it down
                        Temp_Shader.setMat4("model", model);

                        BQueen_Model.Draw(Temp_Shader);
                    }

                }
            }
        }


       
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

    
    // Highlight movement
    static press_check check;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && check.w==false )
    {
     board.selection_movement(B_LEFT);
     check.w = true;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && check.s == false)
    {
        board.selection_movement(B_RIGHT);
        check.s = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && check.a == false)
    {
        board.selection_movement(B_DOWN);
        check.a = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && check.d == false)
    {
        board.selection_movement(B_UP);
        check.d = true;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
        check.w = false;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
        check.s = false;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
        check.a = false;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
        check.d = false;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        board.select_piece();
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
		board.move_piece();
	}

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        board.clear_selection();
	}   

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        board.reset();
    }
    
    if(glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
        camera.Default(glm::vec3(13.5f, 5.0f, 3.5f));
	}
    
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

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
