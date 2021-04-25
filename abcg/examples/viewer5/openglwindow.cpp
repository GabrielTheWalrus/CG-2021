#include "openglwindow.hpp"

#include <imgui.h>

#include <cppitertools/itertools.hpp>
#include <glm/gtc/matrix_inverse.hpp>

#include "imfilebrowser.h"

void OpenGLWindow::handleEvent(SDL_Event& event) {
  glm::ivec2 mousePosition;
  SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
  
  
  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_w){      
      m_dollySpeed = 20.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::Up));
    }
    if (event.key.keysym.sym == SDLK_s){
       m_dollySpeed = -20.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::Down));
    }
    if (event.key.keysym.sym == SDLK_a){
      m_truckSpeed = -5.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::UpR));
    }
    if (event.key.keysym.sym == SDLK_d){
      m_truckSpeed = 5.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::DownR));
    }
  }
  if (event.type == SDL_KEYUP) {
    if (event.key.keysym.sym == SDLK_w){      
      m_dollySpeed = 0.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::Up));
    }
    if (event.key.keysym.sym == SDLK_s){
      m_dollySpeed = 0.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::Down));
    }
    if (event.key.keysym.sym == SDLK_a){
      m_truckSpeed = 0.0f;
    }
    if (event.key.keysym.sym == SDLK_d){
      m_truckSpeed = 0.0f;
      //m_gameData.m_input.set(static_cast<size_t>(Input::DownR));
    }
  }
  /*if (event.type == SDL_MOUSEMOTION) {
    
    mouseMove(mousePosition);
    
    if(mousePosition2.x < lastPosition.x){
      lastPosition.x = mousePosition2.x;
      m_dollySpeed = 20.0f;
      //move cameradireita
    }
    if(mousePosition2.x > lastPosition.x){
      lastPosition.x = mousePosition2.x;
      m_dollySpeed = -20.0f;
      //move cameraesquerda
    }
    if(mousePosition2.x == lastPosition.x){
      lastPosition.x = mousePosition2.x;
      m_dollySpeed = 0.0f;
      //move cameraesquerda
    }
    
  }*/

  if (event.type == SDL_MOUSEMOTION) {
    
    //m_lastPosition = mousePosition;
//    m_mouseMove = true;

    m_trackBallModel.mouseMove(mousePosition);
    m_trackBallLight.mouseMove(mousePosition);
  }
  if (event.type == SDL_MOUSEBUTTONDOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_mouseClick = true;
      m_trackBallModel.mousePress(mousePosition);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mousePress(mousePosition);
    }
  }
  if (event.type == SDL_MOUSEBUTTONUP) {
    m_mouseClick = false;
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_trackBallModel.mouseRelease(mousePosition);
    }
    if (event.button.button == SDL_BUTTON_RIGHT) {
      m_trackBallLight.mouseRelease(mousePosition);
    }
  }
  if (event.type == SDL_MOUSEWHEEL) {
    m_zoom += (event.wheel.y > 0 ? 1.0f : -1.0f) / 5.0f;
    m_zoom = glm::clamp(m_zoom, -1.5f, 1.0f);
  }
}
/*
void OpenGLWindow::mouseMove(glm::ivec2 position){
  
  const auto epsilon{std::numeric_limits<float>::epsilon()};

  //if (glm::all(glm::epsilonEqual(static_cast<glm::vec2>(m_lastPosition), position, epsilon)))
  //  return;

  // Rotation axis
  //m_axis = glm::cross(m_lastPosition, position);
  // Rotation angle
  auto angle{glm::length(m_axis)};

  if(m_lastPosition.x != position.x){

    if(position.x - (m_viewportWidth/2) < 0)
      speedX = -5.0f;

    else if(position.x - (m_viewportWidth/2) > 0)
      speedX = 5.0f;

    else if(!m_mouseMove)
      speedX = 0.0f;
  }

  m_axis = glm::normalize(m_axis);

  // Compute an angle velocity that will be used as a constant rotation angle
  // when the mouse is not being tracked.
  //m_velocity = angle / (msecs + epsilon);
  //m_velocity = glm::clamp(m_velocity, 0.0f, m_maxVelocity);

  // Concatenate the rotation: R_old = R_new * R_old
  //m_rotation = glm::rotate(glm::mat4(1.0f), angle, m_axis) * m_rotation;

  m_lastPosition = position;
}*/

void OpenGLWindow::initializeGL() {
  glClearColor(0, 0, 0, 1);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);

  // Create programs
  auto path{getAssetsPath() + "shaders/texture"};
  m_program = createProgramFromFile(path + ".vert", path + ".frag");

  start();

  // Initial trackball spin
  m_trackBallModel.setAxis(glm::normalize(glm::vec3(1, 1, 1)));
  m_trackBallModel.setVelocity(0.0001f);

  // Load cubemap
  m_model.loadCubeTexture(getAssetsPath() + "maps/cube/");

  
}

void OpenGLWindow::start(){

  bola.initializeGL(m_program, getAssetsPath(), glm::vec3(0.22f), glm::vec3(0.0f, 0.5f, 0.0f));
  bola2.initializeGL(m_program, getAssetsPath(), glm::vec3(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  ground.initializeGL(m_program, getAssetsPath(), glm::vec3(100.0f), glm::vec3(0.0f, 0.0f, 0.0f));
  stadium.initializeGL(m_program, getAssetsPath(), glm::vec3(450.0f), glm::vec3(0.0f, 0.40f, 0.12f));
  
  //initializeSkybox();
}

void OpenGLWindow::initializeSkybox() {
  // Create skybox program
  auto path{getAssetsPath() + "shaders/skybox"};
  m_skyProgram = createProgramFromFile(path + ".vert", path + ".frag");

  // Generate VBO
  glGenBuffers(1, &m_skyVBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(m_skyPositions), m_skyPositions.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  GLint positionAttribute{glGetAttribLocation(m_skyProgram, "inPosition")};

  // Create VAO
  glGenVertexArrays(1, &m_skyVAO);

  // Bind vertex attributes to current VAO
  glBindVertexArray(m_skyVAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_skyVBO);
  glEnableVertexAttribArray(positionAttribute);
  glVertexAttribPointer(positionAttribute, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  glBindVertexArray(0);
}

void OpenGLWindow::paintGL() {

  update();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0, 0, m_viewportWidth, m_viewportHeight);

  // Use currently selected program
  //const auto program{m_programs.at(m_currentProgramIndex)};
  glUseProgram(m_program);

  // Get location of uniform variables
  GLint viewMatrixLoc{glGetUniformLocation(m_program, "viewMatrix")};
  GLint projMatrixLoc{glGetUniformLocation(m_program, "projMatrix")};
  GLint lightDirLoc{glGetUniformLocation(m_program, "lightDirWorldSpace")};
  GLint IaLoc{glGetUniformLocation(m_program, "Ia")};
  GLint IdLoc{glGetUniformLocation(m_program, "Id")};
  GLint IsLoc{glGetUniformLocation(m_program, "Is")};
 
  GLint diffuseTexLoc{glGetUniformLocation(m_program, "diffuseTex")};
  //GLint normalTexLoc{glGetUniformLocation(m_program, "normalTex")};
  //GLint cubeTexLoc{glGetUniformLocation(m_skyProgram, "cubeTex")};

  // Set uniform variables used by every scene object
  //glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_viewMatrix[0][0]);
  //glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &m_camera.m_viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_camera.m_projMatrix[0][0]);
  
  glUniform1i(diffuseTexLoc, 0);
  //glUniform1i(cubeTexLoc, 2);
  //glUniform1i(normalTexLoc, 1);
  
  auto lightDirRotated{m_trackBallLight.getRotation() * m_lightDir};
  glUniform4fv(lightDirLoc, 1, &lightDirRotated.x);
  glUniform4fv(IaLoc, 1, &m_Ia.x);
  glUniform4fv(IdLoc, 1, &m_Id.x);
  glUniform4fv(IsLoc, 1, &m_Is.x);

  float deltaTime{static_cast<float>(getDeltaTime())};
  // Set uniform variables of the current object
  bola.paintGL(m_viewMatrix, deltaTime);
  //bola2.paintGL(m_viewMatrix, deltaTime);
  ground.paintGL(m_viewMatrix, deltaTime);
  stadium.paintGL(m_viewMatrix, deltaTime);

  //renderSkybox();

  glUseProgram(0);
  
}

void OpenGLWindow::renderSkybox() {

  glUseProgram(m_skyProgram);

  // Get location of uniform variables
  //GLint skyTexLoc{glGetUniformLocation(m_skyProgram, "skyTex")};

  // Set uniform variables
  /*
  auto viewMatrix{m_trackBallLight.getRotation()};
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, &viewMatrix[0][0]);
  glUniformMatrix4fv(projMatrixLoc, 1, GL_FALSE, &m_projMatrix[0][0]);
  glUniform1i(skyTexLoc, 0);*/

  glBindVertexArray(m_skyVAO);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, m_model.getCubeTexture());

  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
  glDepthFunc(GL_LEQUAL);
  glDrawArrays(GL_TRIANGLES, 0, m_skyPositions.size());
  glDepthFunc(GL_LESS);

  glBindVertexArray(0);
  glUseProgram(0);
}

void OpenGLWindow::paintUI() {
  abcg::OpenGLWindow::paintUI();
}

void OpenGLWindow::resizeGL(int width, int height) {
  m_viewportWidth = width;
  m_viewportHeight = height;

  m_camera.computeProjectionMatrix(width, height);

  m_trackBallModel.resizeViewport(width, height);
  m_trackBallLight.resizeViewport(width, height);
}

void OpenGLWindow::terminateGL() {
  glDeleteProgram(m_program);
  
}

void OpenGLWindow::update() {

  float deltaTime{static_cast<float>(getDeltaTime())};

  m_modelMatrix = m_trackBallModel.getRotation();
  
  //m_viewMatrix = glm::translate(m_viewMatrix, glm::vec3(0.0f, (directionY * deltaTime), (0.0f)));

  glm::ivec2 currentPosition;
  SDL_GetMouseState(&currentPosition.x, &currentPosition.y);

  if(currentPosition.x != m_lastPosition.x){

    if(currentPosition.x > m_lastPosition.x){
      m_panSpeed = 15.0f;
      m_lastPosition.x = m_lastPosition.x + 1;
    }

    else if(currentPosition.x < m_lastPosition.x){
      m_panSpeed = -15.0f;
      m_lastPosition.x = m_lastPosition.x - 1;
    }
    
  }
  else{

    m_panSpeed = 0.0f;
  }

  m_camera.pan(m_panSpeed * deltaTime);
  m_camera.dolly(m_dollySpeed * deltaTime);
  m_camera.truck(m_truckSpeed * deltaTime);

 /*
  m_viewMatrix =
      glm::lookAt(glm::vec3(0.0f + (directionX * 5.0f), 20.0f + (directionY * 5.0f ), 60.0f + m_zoom),
                  glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
*/
  //Peye - posição do olho
  //Par - onde o olho olha
  //Vu
  
}