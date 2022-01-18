#include "Shader.h"

Shader::Shader() : programId(glCreateProgram()), vertexId(0), fragmentId(0) {
}

Shader::~Shader() {
    glUseProgram(0);
    if (programId != 0) {
        glDeleteProgram(programId);
    }
}

void Shader::start() const {
    glUseProgram(programId);
}

void Shader::stop() const {
    glUseProgram(0);
}

void Shader::link() const {
    glLinkProgram(programId);

    GLint success;

    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(programId, 1024, nullptr, infoLog);
        BOOST_LOG_TRIVIAL(error) << "Error linking Shader code: " << infoLog;
    }

    if (vertexId != 0) {
        glDetachShader(programId, vertexId);
    }
    if (fragmentId != 0) {
        glDetachShader(programId, fragmentId);
    }

    glValidateProgram(programId);
    glGetProgramiv(programId, GL_VALIDATE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(programId, 1024, nullptr, infoLog);
        BOOST_LOG_TRIVIAL(warning) << "Warning validating Shader code: " << infoLog;
    }
}

void Shader::createVertexShader(const std::filesystem::path& path) {
    vertexId = createShader(readFile(path), GL_VERTEX_SHADER);
}

void Shader::createFragmentShader(const std::filesystem::path& path) {
    fragmentId = createShader(readFile(path), GL_FRAGMENT_SHADER);
}

GLuint Shader::createShader(const std::string& shaderCode, GLuint shaderType) const {
    GLuint shaderId = glCreateShader(shaderType);
    if (shaderId == 0) {
        BOOST_LOG_TRIVIAL(error) << "Error creating shader. Type: " << (shaderType == GL_FRAGMENT_SHADER ? "FRAGMENT" : "VERTEX");
        return 0;
    }

    const GLchar* code = shaderCode.c_str();
    glShaderSource(shaderId, 1, &code, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
        BOOST_LOG_TRIVIAL(error) << "Error compiling Shader code: " << infoLog;
        return 0;
    }

    glAttachShader(programId, shaderId);

    return shaderId;
}

void Shader::setUniform(const std::string& name, int value) const {
    glUniform1i(uniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, float value) const {
    glUniform1f(uniforms.at(name), value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value) const {
    glUniform3f(uniforms.at(name), value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const glm::vec4& value) const {
    glUniform4f(uniforms.at(name), value.x, value.y, value.z, value.w);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value) const {
    glUniformMatrix4fv(uniforms.at(name), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const std::string& name, const glm::mat4& value, int count) const {
    glUniformMatrix4fv(uniforms.at(name), count, GL_FALSE, glm::value_ptr(value));
}

void Shader::createUniform(const std::string& name) {
    GLint uniformLocation = glGetUniformLocation(programId, name.c_str());
    if (uniformLocation < 0) {
        BOOST_LOG_TRIVIAL(error) << "Could not find uniform: " << name;
        return;
    }
    uniforms.emplace(name, uniformLocation);
}

std::string Shader::readFile(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (file) {
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        return stream.str();
    } else {
        std::abort();
    }
}