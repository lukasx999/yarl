#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "examples.c"

#define GLAD_GL_IMPLEMENTATION
#include "lib/glad/gl.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <yarl.h>

#define ARRAY_LEN(xs) (sizeof((xs)) / sizeof(*(xs)))

#define CANVAS_HEIGHT 500
#define CANVAS_WIDTH 500

void handle_inputs(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS
        || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void resize_callback(GLFWwindow* window, int width, int height) {
    (void) window;
    glViewport(0, 0, width, height);
}

static const char *vert_src =
    "#version 330\n"

    "in vec2 a_pos;\n"
    "in vec2 a_uv;\n"
    "out vec2 uv;\n"

    "void main() {\n"
        "uv = a_uv;\n"
        "gl_Position = vec4(a_pos*0.75, 0.0, 1.0);\n"
    "}\n";

static const char *frag_src =
    "#version 330\n"

    "out vec4 fragment;\n"
    "uniform vec4 color;\n"
    "in vec2 uv;\n"
    "uniform sampler2D tex;\n"

    "void main() {\n"
        "fragment = texture(tex, vec2(uv.x, 1.0 - uv.y));\n"
        // texture must be y-flipped        ^^^^^^^^^^
    "}\n";

typedef struct {
    float x, y;
} Vec2;

typedef struct {
    Vec2 pos;
    Vec2 uv;
} Vertex;

int main(void) {

    Yarl *yarl = yarl_init(CANVAS_WIDTH, CANVAS_HEIGHT);
    assert(yarl != NULL);
    triangles(yarl);

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

    assert(glfwInit());
    GLFWwindow *window = glfwCreateWindow(1600, 900, "yarl", NULL, NULL);
    assert(window != NULL);

    glfwSetFramebufferSizeCallback(window, resize_callback);
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

    GLuint loc_pos = glGetAttribLocation(prog, "a_pos");
    glVertexAttribPointer(loc_pos, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(loc_pos);

    GLuint loc_uv = glGetAttribLocation(prog, "a_uv");
    glVertexAttribPointer(loc_uv, 2, GL_FLOAT, false, sizeof(Vertex), (void*) offsetof(Vertex, uv));
    glEnableVertexAttribArray(loc_uv);

    GLuint tex_canvas;
    glGenTextures(1, &tex_canvas);
    glBindTexture(GL_TEXTURE_2D, tex_canvas);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    YarlColor *canvas = yarl_get_canvas(yarl);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CANVAS_WIDTH, CANVAS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas);
    glGenerateMipmap(tex_canvas);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex_canvas);

        glUseProgram(prog);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        handle_inputs(window);
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(prog);
    glDeleteTextures(1, &tex_canvas);
    glfwDestroyWindow(window);
    glfwTerminate();
    yarl_destroy(yarl);

    return 0;
}
