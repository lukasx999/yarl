#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include "glad/gl.h"
#include <GLFW/glfw3.h>

#include <yarl.h>



void draw(Yarl yarl) {

    int h = yarl_get_height(yarl);
    int w = yarl_get_width(yarl);

    yarl_fill(yarl, YARL_GREY);
    yarl_draw_triangle(yarl, w/2, 25, 0, h, w, h, YARL_DARK_BLUE);
    yarl_draw_triangle(yarl, w/2, 50, 50, h-50, w-50, h-50, YARL_BLUE);
}


void callback(int error_code, const char* description) {
    (void) error_code;
    printf("%s\n", description);
}


typedef struct {
    float x, y;
} Vertex;

int main(void) {

    Yarl yarl = yarl_init(1000, 1000);
    draw(yarl);

    Vertex data[] = {
        {  0.5,  0.5 },
        {  0.5, -0.5 },
        { -0.5, -0.5 },
        { -0.5,  0.5 },
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glfwSetErrorCallback(callback);

    assert(glfwInit() == true);

    GLFWwindow *window = glfwCreateWindow(500, 500, "yarl", NULL, NULL);
    assert(window != NULL);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    const char *vert_src =
        "#version 330\n"
        "in vec2 pos;\n"
        "void main() {\n"
        "gl_Position = vec4(pos, 0., 1.);\n"
        "}\n";

    const char *frag_src =
        "#version 330\n"
        "out vec4 fragment;\n"
        "void main() {\n"
        "fragment = vec4(1., 1., 1., 1.);\n"
        "}\n";

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vert, 1, &vert_src, NULL);
    glShaderSource(frag, 1, &frag_src, NULL);
    glCompileShader(vert);
    glCompileShader(frag);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vert);
    glAttachShader(prog, frag);
    glLinkProgram(prog);
    glUseProgram(prog);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint pos = glGetAttribLocation(prog, "pos");
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 2, GL_FLOAT, false, sizeof(Vertex), 0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    yarl_destroy(yarl);

    return 0;
}
