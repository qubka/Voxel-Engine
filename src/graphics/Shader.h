#ifndef VOX_SHADER_H
#define VOX_SHADER_H

class Shader {
private:
    GLuint vertexId;
    GLuint fragmentId;
    std::map<std::string, GLint> uniforms;

    GLuint createShader(const std::string& shaderCode, GLuint shaderType) const;
    std::string readFile(const std::filesystem::path& path);
public:
    GLuint programId;

    Shader();
    ~Shader();

    void setUniform(const std::string& name, int value) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, const glm::vec3& value) const;
    void setUniform(const std::string& name, const glm::vec4& value) const;
    void setUniform(const std::string& name, const glm::mat4& value) const;
    void setUniform(const std::string& name, const glm::mat4& value, int count) const;

    template<typename ... Args>
    void createAllUniform(Args&& ... args){
        for (const auto p : {args...}) {
            createUniform(p);
        }
    }
    void createUniform(const std::string& name);
    void createVertexShader(const std::filesystem::path& path);
    void createFragmentShader(const std::filesystem::path& path);

    void link() const;
    void start() const;
    void stop() const;
};

#endif //VOX_SHADER_H
