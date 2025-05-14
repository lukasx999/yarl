#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <yarl.h>
#include <backend/ppm.h>

#define ARRAY_LEN(xs) (sizeof((xs)) / sizeof(*(xs)))



void callback_resize(GLFWwindow* window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
}

void callback_error(int error_code, const char* description) {
    (void) error_code;
    printf("%s\n", description);
}

static const char *vert_src =
    "#version 330\n"
    "in vec2 pos;\n"
    "uniform vec2 scale;\n"
    "void main() {\n"
    // "float s = 1.0;\n"
    // "vec2 p = vec2(pos.x + s, pos.y - s);\n"
    // "vec2 origin = vec2(-1.0, 1.0);\n"
    "gl_Position = vec4(pos*scale, 0., 1.);\n"
    "}\n";

static const char *frag_src =
    "#version 330\n"
    "out vec4 fragment;\n"
    "uniform vec4 color;\n"
    "void main() {\n"
    "fragment = color;\n"
    "}\n";

typedef struct {
    float x, y;
} V2;

int main(void) {

    // int size = 100;
    // Yarl yarl = yarl_init(size, size);
    // int yarl_height = yarl_get_height(yarl);
    // int yarl_width = yarl_get_width(yarl);
    // yarl_fill(yarl, YARL_GREY);
    // yarl_draw_rect(yarl, 1, 1, yarl_width-1, yarl_height-1, YARL_RED);
    // yarl_draw_rect(
    //     yarl,
    //     yarl_width/4,
    //     yarl_height/4,
    //     yarl_width - yarl_width/4,
    //     yarl_height - yarl_height/4,
    //     YARL_DARK_RED
    // );
    // yarl_draw_point(yarl, (yarl_width+1)/2, (yarl_height+1)/2, YARL_BLUE);

    V2 vertices[] = {
        {  1.0f,  1.0f }, // top right
        {  1.0f, -1.0f }, // bottom right
        { -1.0f, -1.0f }, // bottom left
        { -1.0f,  1.0f }, // top left 
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glfwInit();
    glfwSetErrorCallback(callback_error);

    GLFWwindow *window = glfwCreateWindow(500, 500, "yarl", NULL, NULL);

    glfwSetFramebufferSizeCallback(window, callback_resize);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

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
    glDeleteShader(vert);
    glDeleteShader(frag);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint pos = glGetAttribLocation(prog, "pos");
    glVertexAttribPointer(pos, 2, GL_FLOAT, false, sizeof(V2), 0);
    glEnableVertexAttribArray(pos);

    int w, h;
    glfwGetWindowSize(window, &w, &h);
    GLuint u_scale = glGetUniformLocation(prog, "scale");
    float scale = 0.1;
    glUniform2f(u_scale, scale, scale);

    GLuint u_offset = glGetUniformLocation(prog, "offset");
    GLuint u_color = glGetUniformLocation(prog, "color");


    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(prog);
        glBindVertexArray(vao);



        int n = 5;
        for (int i=0; i < n; ++i) {

            glUniform4f(u_color, 1, 0, 0, 1.);

            float x = (float) i / n; // 0..1
            assert(x >= 0 && x <= 1);
            V2 offset = { 0.0, 0.0 };

            glUniform2f(u_offset, offset.x, offset.y);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }







        // int height = yarl_get_height(yarl);
        // int width = yarl_get_width(yarl);
        // for (int y=0; y <= height; ++y) {
        //     for (int x=0; x <= width; ++x) {
        //         YarlColor color = yarl_get_pixel(yarl, x, y);
        //
        //         float r = YARL_COLOR_R(color) / 255.;
        //         float g = YARL_COLOR_G(color) / 255.;
        //         float b = YARL_COLOR_B(color) / 255.;
        //         glUniform4f(u_color, r, g, b, 1.);
        //         float xn = ((float) x / width)  * 2 - 1; // -1..1
        //         float yn = ((float) y / height) * 2 - 1; // -1..1
        //         glUniform2f(u_offset, xn/2, yn/2);
        //
        //         glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //     }
        // }


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
