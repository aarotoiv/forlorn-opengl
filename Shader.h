#ifndef Shader_h
#define Shader_h

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

class Shader {
    public:
        Shader();
        void CreateFromString(const char* vertexCode, const char* fragmentCode);
        void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

        std::string ReadFile(const char* fileLocation);
        GLuint GetProjectionLocation();
        GLuint GetModelLocation();
        GLuint GetViewLocation();
        GLuint GetColorLocation();
        GLuint GetAlphaLocation();
        
        void UseShader();
        void ClearShader();

        ~Shader();

    private:
        GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformColor, uniformAlpha;

        void CompileShader(const char* vertexCode, const char* fragmentCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

#endif