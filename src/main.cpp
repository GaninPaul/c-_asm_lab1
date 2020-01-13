#include "../imgui/imgui.h"
#include "../lib/glut/imgui_impl_glut.h"
#include "../lib/opengl2/imgui_impl_opengl2.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable : 4505)
#endif

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int sum(int x, int y)
{
    int _sum;
    asm("addl %%ebx, %%eax;"
        : "=a"(_sum)
        : "a"(x), "b"(y));
    return _sum;
}

int sub(int x, int y)
{
    int _sub;
    asm("subl %%ebx, %%eax;"
        : "=a"(_sub)
        : "a"(x), "b"(y));

    return _sub;
}

int mul(int x, int y)
{
    int _mul;
    asm("imull %%ebx, %%eax;"
        : "=a"(_mul)
        : "a"(x), "b"(y));
    return _mul;
}

void my_display_code()
{
    static int Z = 0;
    static int X = 0;
    static int Y = 0;

    ImGui::Begin("Lab 1 asm");
    ImGui::Text("Simple calc");
    ImGui::InputInt("X: ", &X);
    ImGui::InputInt("Y: ", &Y);
    if (ImGui::Button("Addition"))
    {
        Z = sum(X, Y);
    }
    if (ImGui::Button("Multiplication"))
    {
        Z = mul(X, Y);
    }
    if (ImGui::Button("Subtraction"))
    {
        Z = sub(X, Y);
    }
    ImGui::SameLine();
    ImGui::Text("result(X*Y) = %d", Z);
    ImGui::End();
}

void glut_display_func()
{
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();

    my_display_code();

    ImGui::Render();
    ImGuiIO &io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Lab1");
    glutDisplayFunc(glut_display_func);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL2_Init();

    glutMainLoop();

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
