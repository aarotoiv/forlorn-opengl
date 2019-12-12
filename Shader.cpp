#include "Shader.h"
 
 
Shader::Shader()
{
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}
 
void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}
 
void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation) {
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();
 
    CompileShader(vertexCode, fragmentCode);
}
 
std::string Shader::ReadFile(const char* fileLocation) {
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);
 
    if (!fileStream.is_open()) {
        printf("FAILED TO READ %s! File doesn't exist.", fileLocation);
        return "";
    }
 
    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
 
    fileStream.close();
    return content;
}
 
GLuint Shader::GetProjectionLocation() {
    return uniformProjection;
}
GLuint Shader::GetModelLocation() {
    return uniformModel;
}
GLuint Shader::GetViewLocation() {
    return uniformView;
}
GLuint Shader::GetColorLocation() {
    return glGetUniformLocation(shaderID, "projection");
}
 
void Shader::CompileShader(const char* vertexCode, const char* fragmentCode) {
    shaderID = glCreateProgram();
 
    if (!shaderID) {
        printf("Creation of shader failed.");
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);
 
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
 
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s' \n", eLog);
        return;
    }
 
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s' \n", eLog);
        return;
    }
 
    // get location of uniform variable in shader
    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}
 
void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    //create empty container for the shader
    GLuint theShader = glCreateShader(shaderType);
    //this was weird and i have no idea why this is done
    const GLchar* theCode[1];
    theCode[0] = shaderCode;
    // again no clue why were using an array
    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);
    //shadersource, the shader, 1 shader source, theCode we're using, and the length of the code
    glShaderSource(theShader, 1, theCode, codeLength);
    //compile that shit
    glCompileShader(theShader);
    //error log shit
    GLint result = 0;
    GLchar eLog[1024] = { 0 };
 
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling program the %d shader: '%s' \n", shaderType, eLog);
        return;
    }
    //finally attach the shader to the program
    glAttachShader(theProgram, theShader);
}
 
void Shader::UseShader() {
    glUseProgram(shaderID);
}
 
void Shader::ClearShader() {
    if (!shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }
    uniformModel = 0;
    uniformProjection = 0;
}
 
 
 
Shader::~Shader()
{
    ClearShader();
}