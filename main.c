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

    "in vec2 a_pos;\n"
    "in vec2 a_uv;\n"
    "out vec2 uv;\n"

    "void main() {\n"
        "uv = a_uv;\n"
        "gl_Position = vec4(a_pos*0.5, 0.0, 1.0);\n"
    "}\n";

static const char *frag_src =
    "#version 330\n"

    "out vec4 fragment;\n"
    "uniform vec4 color;\n"
    "in vec2 uv;\n"
    "uniform sampler2D tex;\n"

    "void main() {\n"
        "fragment = texture(tex, uv);\n"
    "}\n";

typedef struct {
    float x, y;
} V2;

typedef struct {
    V2 pos;
    V2 uv;
} Vertex;

int main(void) {

    int size = 1000;
    Yarl yarl = yarl_init(size, size);
    int yarl_height = yarl_get_height(yarl);
    int yarl_width = yarl_get_width(yarl);
    yarl_fill(yarl, YARL_GREY);
    yarl_draw_rect(yarl, 1, 1, yarl_width-1, yarl_height-1, YARL_RED);
    yarl_draw_rect(
        yarl,
        yarl_width/4,
        yarl_height/4,
        yarl_width - yarl_width/4,
        yarl_height - yarl_height/4,
        YARL_DARK_RED
    );
    yarl_draw_point(yarl, (yarl_width+1)/2, (yarl_height+1)/2, YARL_BLUE);

    Vertex vertices[] = {
        { { 1.0f,  1.0f }, { 1.0, 1.0 } }, // top right
        { { 1.0f, -1.0f }, { 1.0, 0.0 } }, // bottom right
        { {-1.0f, -1.0f }, { 0.0, 0.0 } }, // bottom left
        { {-1.0f,  1.0f }, { 0.0, 1.0 } }, // top left 
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

    GLuint pos = glGetAttribLocation(prog, "a_pos");
    glVertexAttribPointer(pos, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(pos);

    GLuint uv = glGetAttribLocation(prog, "a_uv");
    glVertexAttribPointer(uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, uv));
    glEnableVertexAttribArray(uv);

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // glTexImage2D(
    //     GL_TEXTURE_2D,
    //     0,
    //     GL_RGBA,
    //     yarl_width+1,
    //     yarl_height+1,
    //     0,
    //     GL_RGBA,
    //     GL_UNSIGNED_BYTE,
    //     c
    // );

    glGenerateMipmap(tex);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        glUseProgram(prog);
        glBindVertexArray(vao);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwDestroyWindow(window);
    glfwTerminate();
    yarl_destroy(yarl);

    return 0;
}
