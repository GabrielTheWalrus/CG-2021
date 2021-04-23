#ifndef BOLA_HPP_
#define BOLA_HPP_

#include "abcg.hpp"
#include "model.hpp"

class Bola : public abcg::OpenGLWindow{

    public:
        void initializeGL(GLuint program);
        void paintGL();
        void terminateGL();
        void loadModel(std::string_view path);

        Model m_model;
        int m_trianglesToDraw{};
        glm::vec4 m_Ka{};
        glm::vec4 m_Kd{};
        glm::vec4 m_Ks{};
        float m_shininess{};
        GLuint m_program{};
        int m_mappingMode;

};

#endif
