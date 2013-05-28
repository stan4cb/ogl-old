#include "renderer.h"
#include "game.h"
#include <iostream>

Camera* Renderer::cam;
Program* Renderer::prog;
int Renderer::win_w,Renderer::win_h;
vector<Geometry*> Renderer::drawList;

Renderer::Renderer(Geometry *obj)
{
    Reg(obj);
}
void Renderer::Render()
{
    prog->SetUniform("cameraMatrix",cam->GetMatrix());

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int edges = 0;
    GLenum type = GL_TRIANGLES;
    string lastDrawName = "null";
    for(Geometry* gmo : drawList)
    {
        /* Find a better wat to do it */
        if(gmo == Game::ins->editor.GetOnEdit())
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        prog->SetUniform("modelMatrix",gmo->GetModelMatrix());
        prog->SetUniform("color",gmo->GetColor());
        prog->Use(true);
        if(lastDrawName != gmo->gPtr->idString)
        {
            glBindVertexArray(gmo->gPtr->GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,gmo->gPtr->GetEBO());
            edges = gmo->gPtr->GetEdges();
            type = gmo->gPtr->GetType();
            lastDrawName = gmo->gPtr->idString;
        }
        glDrawElements(type,edges,GL_UNSIGNED_INT,0);
    }
    prog->Use(false);
    glBindVertexArray(0);

    glfwSwapBuffers();
}

bool Renderer::Setup(int w,int h , int screenState)
{
    glfwInit();
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(!glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 0, screenState) )
    {
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE,0);
        if(!glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 0, screenState))
        {
            throw runtime_error("glfwOpenWindow() Fail 2x!");
            return false;
        }
        cerr << "GLFW_OPENGL_PROFILE -> 0" << endl;

    }
    glfwSetWindowTitle("openGL 3.2 -PRE.ALPHA");
    glfwSwapInterval(1);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        throw runtime_error("glewInit() Fail!");
        return false;
    }
    if(!GLEW_VERSION_3_2)
    {
        throw runtime_error("OpenGL 3.2 API is not available.");
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    win_w = w;
    win_h = h;
    cam = new Camera(win_w,win_h);
    prog = new Program();
    return true;
}
void Renderer::Reg(Geometry *obj)
{
    drawList.push_back(obj);
}
void Renderer::UnReg(Geometry *obj)
{
    for(unsigned int i = 0;i < drawList.size();i++)
    {
        if(drawList[i] == obj)
        {
            drawList.erase(drawList.begin() + i);
        }
    }
}
