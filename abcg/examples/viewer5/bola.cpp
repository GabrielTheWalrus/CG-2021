#include "bola.hpp"
#include <glm/gtc/matrix_inverse.hpp>

void Bola::initializeGL(GLuint program, std::string assetsPath) {

  m_program = program;

  modelMatrixLoc = glGetUniformLocation(m_program, "modelMatrix");
  viewMatrixLoc = glGetUniformLocation(m_program, "viewMatrix");
  normalMatrixLoc = glGetUniformLocation(m_program, "normalMatrix");
  shininessLoc = glGetUniformLocation(m_program, "shininess");
  mappingModeLoc = glGetUniformLocation(m_program, "mappingMode");
  
  KaLoc = glGetUniformLocation(m_program, "Ka");
  KdLoc = glGetUniformLocation(m_program, "Kd");
  KsLoc = glGetUniformLocation(m_program, "Ks");

  loadModel(assetsPath);
  //m_mappingMode = 2;  // "From mesh" option

}

void Bola::paintGL(glm::mat4 viewMatrix) {

  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, &m_modelMatrix[0][0]);

  auto modelViewMatrix{glm::mat3(viewMatrix * m_modelMatrix)};
  glm::mat3 normalMatrix{glm::inverseTranspose(modelViewMatrix)};
  glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, &normalMatrix[0][0]);
  
  glUniform1i(mappingModeLoc, m_mappingMode);
  glUniform1f(shininessLoc, m_shininess);
  glUniform4fv(KaLoc, 1, &m_Ka.x);
  glUniform4fv(KdLoc, 1, &m_Kd.x);
  glUniform4fv(KsLoc, 1, &m_Ks.x);

  m_model.render(m_trianglesToDraw);
}

void Bola::loadModel(std::string path) {

  m_model.loadDiffuseTexture(path + "maps/jabulani.jpg");
  m_model.loadFromFile(path + "bola.obj");
  m_model.setupVAO(m_program);
  m_trianglesToDraw = m_model.getNumTriangles();
  

  // Use material properties from the loaded model
  m_Ka = m_model.getKa();
  m_Kd = m_model.getKd();
  m_Ks = m_model.getKs();
  m_shininess = m_model.getShininess();
}