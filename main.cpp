#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>

GLuint load_shader(const std::string& path, GLenum shader_type){
    std::cout<< "Loading shader: " << path << std::endl;
    std::ifstream file(path);
    if(!file.is_open()){
        std::cerr << "Faileddd to open file: " << path << " (Error: " << strerror(errno) << ")" << std::endl;
        return 0;
    }
    std::string source = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    const char* source_cstr = source.c_str();

    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source_cstr, NULL);

    glCompileShader(shader);
    GLint status;
    std::cout<< "Compiling shader: " << status << std::endl;
    if(!status){
        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        char* log = new char[log_length];
        glGetShaderInfoLog(shader, log_length, NULL, log);
        std::cerr << "Failed to compile shader: " << path << std::endl;
        std::cerr << log << std::endl;
        delete[] log;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

int main(int, char**){
    std::cout<< "Loading shader: " ;

    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL);

    if(!window){
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    GLuint program = glCreateProgram();
    GLuint vs = load_shader("assets/shaders/simple.vert", GL_VERTEX_SHADER);
    GLuint fs = load_shader("assets/shaders/simple.frag", GL_FRAGMENT_SHADER);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);

    GLuint time_location = glGetUniformLocation(program, "time");
    

    while(glfwWindowShouldClose(window) == GL_FALSE){
        float time = (float)glfwGetTime();
        // glClearColor(std::sin(time) * 0.5f + 0.5f, std::cos(time) * 0.5f + 0.5f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vertex_array);
        glUniform1f(time_location, time);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
