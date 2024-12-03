#pragma once

#include <string>
#include <unordered_map>
#include <glad/gl.h>

namespace GH::renderer::internal {
    class texture {
    private:
        GladGLContext* m_GL;
        unsigned int m_ID;
        int m_width, m_height, m_channels;
        std::string m_data;
        unsigned char* m_rawData;

    public:
        texture();
        texture(GladGLContext* GL, const std::string& data);
        ~texture();

        texture(const texture&) = delete;
        texture& operator=(const texture&) = delete;

        std::string getData() const;
        unsigned char* const getRawData() const;
        const GladGLContext* const getGL() const;
        unsigned int getID() const;
        int getWidth() const;
        int getHeight() const;
    };

    class textureManager {
    private:
        GladGLContext* m_GL;
        std::unordered_map<std::string, texture*> m_textures;

    public:
        textureManager() = default;
        ~textureManager();
        textureManager(const textureManager&) = delete;
        textureManager& operator=(const textureManager&) = delete;

        bool loaded(const std::string& alias);
        texture* loadTexture(const std::string& alias, const std::string& data);
        void unloadTexture(const std::string& alias);
        void setGL(GladGLContext* GL);

        const GladGLContext* const getGL() const;
        texture* getTexture(const std::string& alias) const;
        std::string getData(const std::string& alias) const;
        unsigned char* const getRawData(const std::string& alias) const;
        unsigned int getID(const std::string& alias) const;
        int getWidth(const std::string& alias) const;
        int getHeight(const std::string& alias) const;
    };
}