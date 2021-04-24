#ifndef BOLA_HPP_
#define BOLA_HPP_

#include "abcg.hpp"
#include "model.hpp"

class OpenGLWindow;

class Bola{

    public:
        void initializeGL(GLuint program, std::string path);
        void paintGL(glm::mat4 viewMatrix);
        void terminateGL();
        void loadModel(std::string path);

        Model m_model;
        int m_trianglesToDraw{};
        float m_shininess{};
        GLuint m_program{};
        int m_mappingMode = 2;
        friend OpenGLWindow;

        GLuint modelMatrixLoc;
        GLuint viewMatrixLoc;
        GLuint mappingModeLoc;
        GLuint normalMatrixLoc;
        GLuint shininessLoc;
        GLuint KaLoc;
        GLuint KdLoc;
        GLuint KsLoc;

        glm::mat4 m_modelMatrix = glm::mat4(1.0f);

        glm::vec4 m_Ka{};
        glm::vec4 m_Kd{};
        glm::vec4 m_Ks{};

};

#endif
