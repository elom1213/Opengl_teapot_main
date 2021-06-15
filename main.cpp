// 1652025 ¹ÚÁöÈÆ
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "teapot_loader.h"
#include "myShader.h"
#include "myTexture.h"
#include "myCamera.h"

void processInput(GLFWwindow*);
void framebuffersizeCallback(GLFWwindow*, int width, int height);
void mousepositionCallback(GLFWwindow*, double new_xpos, double new_ypos);

using namespace std;

const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

myCamera myCam{};
bool is_firstmouse = true;
float lastx = SCR_WIDTH/2;
float lasty = SCR_HEIGHT/2;

float deltaTime = 0.0f;
float lastTime = 0.0f;

bool quantize_option = false;

glm::vec3 lightPos{1.5f, 0.4f, 1.0f };
glm::vec3 lightPos2{ -1.5f, 0.3f, -0.5f };

int main()
{
    float currentTime = glfwGetTime();
    deltaTime = lastTime - currentTime;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "1652025 park ji hun", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffersizeCallback);
    glfwSetCursorPosCallback(window, mousepositionCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // compile shader and link to shader program
    Shader teapotShader("shader/teapotShader.vs", "shader/teapotShader.fs");
    Shader lightCubeShader("shader/lightCube.vs", "shader/lightCube.fs");

    // cube vertices
    float vertices_cube[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    //bind teapot vao, vbo
    vector<float> vertice_teapot;
    Teapot teapot("teapot.vbo", vertice_teapot, 8);

    unsigned int teapotVBO, teapotVAO;

    glGenVertexArrays(1, &teapotVAO);
    glGenBuffers(1, &teapotVBO);

    glBindVertexArray(teapotVAO);

    glBindBuffer(GL_ARRAY_BUFFER, teapotVBO);
    glBufferData(GL_ARRAY_BUFFER, teapot.nVertNum*teapot.nVertFloats*sizeof(float), vertice_teapot.data(), GL_STATIC_DRAW);

    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, teapot.nVertFloats*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //texture coordinate
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, teapot.nVertFloats*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    //normal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, teapot.nVertFloats*sizeof(float), (void*)(5*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // bind light vao, vbo
    unsigned int lightVBO, lightVAO;

    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);

    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

// set texture
    Texture mytex("../texture/block.jpg", GL_RGB);
    teapotShader.setInt("mytex", 0);

// rendering loop
#if 1
    float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        teapotShader.use();
        
        //set properties
        teapotShader.setBool("is_quantized", false);
        teapotShader.setBool("is_textured", false);
        
        teapotShader.setVec3("eyePos", myCam.Position);

        glm::mat4 view = myCam.getViewMatrix();
        teapotShader.setMat4("view", view);

        glm::mat4 projection = glm::perspective(glm::radians(myCam.Zoom), aspect, 0.1f, 100.0f);
        teapotShader.setMat4("projection", projection);

        //draw teapot 1
        //set light property
        teapotShader.setBool("set_light2", true);
        glm::vec3 lightColor = glm::vec3(1.0f);
        glm::vec3 diffuse_light = glm::vec3(0.7f);
        glm::vec3 diffuse_light2 = 0.7f * glm::vec3(0.1f, 0.3f, 1.0f);
        glm::vec3 ambient = glm::vec3(0.0f);
        teapotShader.setVec3("light.position", lightPos);
        teapotShader.setVec3("light.position2", lightPos2);
        teapotShader.setVec3("light.diffuse", diffuse_light);
        teapotShader.setVec3("light.diffuse2",diffuse_light2);
        teapotShader.setVec3("light.specular", glm::vec3(1.0f));
        teapotShader.setVec3("light.ambient", ambient);

        //set material property
        glm::vec3 diffuse_material = glm::vec3(1.0f, 0.2f, 0.1f);
        teapotShader.setVec3("material.diffuse", diffuse_material);
        teapotShader.setVec3("material.specular", glm::vec3(0.5f));
        teapotShader.setVec3("material.ambient", diffuse_material);
        teapotShader.setFloat("material.shininess", 50.0f);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);

        //draw teapot 2
        teapotShader.setBool("set_light2", false);
        ambient = glm::vec3(0.2f);
        teapotShader.setVec3("light.ambient", ambient);
        teapotShader.setFloat("material.shininess", 5.0f);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);

        //draw teapot 3
        diffuse_light = lightColor * glm::vec3(1.0f);
        teapotShader.setVec3("light.diffuse", diffuse_light);

        teapotShader.setVec3("material.ambient", glm::vec3(0.7f, 0.5f, 0.2f));
        teapotShader.setFloat("material.shininess", 50.0f);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, -0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);
        
        //draw teapot 4
        teapotShader.setBool("is_quantized", true);

        teapotShader.setVec3("material.ambient", ambient);
        teapotShader.setVec3("meterial.specular", glm::vec3(0.0f));

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);

        //draw teapot 5
        mytex.Bind();
        teapotShader.setBool("is_quantized", false);
        teapotShader.setBool("is_textured", true);
        teapotShader.setVec3("material.diffuse", lightColor);
        teapotShader.setVec3("material.specular", glm::vec3(0.5f));
       
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);

        //draw teapot 6
        teapotShader.setBool("is_textured", false);
        float sinwave = 0.5f + sin(glm::radians(50*glfwGetTime()))/2;
        diffuse_material = glm::vec3(sinwave, 0.2f, -sinwave+1);
        teapotShader.setVec3("material.diffuse", diffuse_material);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.5f, 0.0f));
        model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        teapotShader.setMat4("model", model);

        glBindVertexArray(teapotVAO);
        glDrawArrays(GL_TRIANGLES, 0, teapot.nVertNum);

        glBindVertexArray(0);

        // draw light cube
        lightCubeShader.use();

        lightCubeShader.setVec3("lightColor", lightColor);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // light cube 2
        lightCubeShader.setVec3("lightColor", diffuse_light2);
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos2);
        model = glm::scale(model, glm::vec3(0.15f));
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
#endif

    glDeleteVertexArrays(1, &teapotVAO);
    glDeleteBuffers(1, &teapotVBO);
    
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        myCam.processkeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        myCam.processkeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        myCam.processkeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        myCam.processkeyboard(RIGHT, deltaTime);
}

void framebuffersizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mousepositionCallback(GLFWwindow *window, double new_xpos, double new_ypos)
{
    if (is_firstmouse)
    {
        lastx = new_xpos;
        lasty = new_ypos;
        is_firstmouse = false;
    }

    float xoffset = lastx - new_xpos;
    float yoffset = new_ypos - lasty;

    lastx = new_xpos;
    lasty = new_ypos;

    myCam.processMouseMovement(xoffset, yoffset);
}