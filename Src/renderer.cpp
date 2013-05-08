#include "renderer.h"
#include <iostream>

Camera* Renderer::cam;
Program* Renderer::prog;
vector<Geometry*> Renderer::drawList;
int Renderer::win_w,Renderer::win_h;

void Renderer::Render()
{
    prog->SetUniform("cameraMatrix",cam->GetMatrix());

    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    string lastDrawName = "null";
    int edges = 0;
    GLenum type = GL_TRIANGLES;
    for( unsigned int i = 0; i < drawList.size(); i++)
    {
        Geometry *gmo = drawList[i];
        prog->SetUniform("modelMatrix",gmo->GetModelMatrix());
        prog->SetUniform("color",gmo->GetColor());
        prog->Use(true);
        if(lastDrawName != gmo->mName)
        {
            glBindVertexArray(gmo->d->GetVAO());
            edges = gmo->d->GetEdges();
            type = gmo->d->GetType();
            lastDrawName = gmo->mName;
        }
        glDrawArrays( type , 0 , edges );
    }
    prog->Use(false);
    glBindVertexArray(0);

    glfwSwapBuffers();
}
Renderer::Renderer(Geometry *obj)
{
    drawList.push_back(obj);
}
Camera* Renderer::sCamera()
{
    return cam;
}
bool Renderer::Setup(int w,int h , int screenState)
{
    glfwInit();
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    if(!glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 0, screenState) )
    {
        throw runtime_error("glfwOpenWindow() Fail!");
        return false;
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
    std::cout << "Registered 'geometry' : " << obj->mName << std::endl;
    drawList.push_back(obj);
}

/*
Draw wireframe
if((i / 2) == 0)
glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
else
glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
*/