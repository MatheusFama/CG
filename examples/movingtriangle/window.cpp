#include "window.hpp"

void Window::onCreate() {
  auto const *vertexShader{R"gl(#version 300 es
    layout(location = 0) in vec2 inPosition;
    layout(location = 1) in float inTranslation;
    void main() { 
      gl_PointSize = 20.0;
      vec2 newPosition = vec2(inPosition.x,inPosition.y + inTranslation);
      gl_Position = vec4(newPosition, 0, 1);
    }
  )gl"};

  auto const *vertexLineShader{R"gl(#version 300 es
    layout(location = 0) in vec2 inPosition;
    void main() { 
      gl_Position = vec4(inPosition, 0, 1);
    }
  )gl"};

  auto const *fragmentShader{R"gl(#version 300 es
    precision mediump float;

    out vec4 outColor;

    void main() { outColor = vec4(1); }
  )gl"};

  // Create shader program
  m_program = abcg::createOpenGLProgram(
      {{.source = vertexShader, .stage = abcg::ShaderStage::Vertex},
       {.source = fragmentShader, .stage = abcg::ShaderStage::Fragment}});

  m_Lineprogram = abcg::createOpenGLProgram(
      {{.source = vertexLineShader, .stage = abcg::ShaderStage::Vertex},
       {.source = fragmentShader, .stage = abcg::ShaderStage::Fragment}});

  // Clear window
  abcg::glClearColor(0, 0, 0, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  std::array<GLfloat, 2> sizes{};
#if !defined(__EMSCRIPTEN__)
  abcg::glEnable(GL_PROGRAM_POINT_SIZE);
  abcg::glGetFloatv(GL_POINT_SIZE_RANGE, sizes.data());
#else
  abcg::glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, sizes.data());
#endif
  fmt::print("Point size: {:.2f} (min), {:.2f} (max)\n", sizes.at(0),
             sizes.at(1));

  m_P.x = 0.0;
  m_P.y = 0.0;
}

void Window::onPaint() {
  // Create OpenGL buffers for drawing the point at m_P
  m_translation += 0.0001f;

  setupModel();

  // Clear window
  abcg::glClearColor(0, 0, 0, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);

  if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow)) {
    m_P.x = m_P.x - 0.1;
  }

  if (ImGui::IsKeyPressed(ImGuiKey_RightArrow)) {
    m_P.x = m_P.x + 0.1;
  }

  if (ImGui::IsKeyPressed(ImGuiKey_DownArrow)) {
    m_P.y = m_P.y - 0.1;
  }

  if (ImGui::IsKeyPressed(ImGuiKey_UpArrow)) {
    m_P.y = m_P.y + 0.1;
  }

  // Set the viewport
  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);

  // Start using the shader program
  abcg::glUseProgram(m_program);
  // Start using VAO
  abcg::glBindVertexArray(m_VAO);

  // Draw a single point
  abcg::glDrawArrays(GL_POINTS, 0, 1);

  // End using VAO
  abcg::glBindVertexArray(0);
  // End using the shader program
  abcg::glUseProgram(0);
}

void Window::setupModel() {
  // Release previous VBO and VAO
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteBuffers(1, &m_VBOTranslation);
  abcg::glDeleteVertexArrays(1, &m_VAO);

  // Generate a new VBO and get the associated ID
  abcg::glGenBuffers(1, &m_VBOVertices);
  // Bind VBO in order to use it
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  // Upload data to VBO
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(m_P), &m_P, GL_STATIC_DRAW);
  // Unbinding the VBO is allowed (data can be released now)
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate VBO translation
  // fmt::print("translation: {:.2f} \n", m_translation);
  abcg::glGenBuffers(1, &m_VBOTranslation);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOTranslation);
  abcg::glBufferData(GL_ARRAY_BUFFER, sizeof(m_translation), &m_translation,
                     GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};

  auto const translationAttribute{
      abcg::glGetAttribLocation(m_program, "inTranslation")};

  fmt::print("positionAtribbute: {} \n", positionAttribute);
  fmt::print("translationAtribbute: {} \n", translationAttribute);
  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOVertices);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glEnableVertexAttribArray(translationAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOTranslation);
  abcg::glVertexAttribPointer(translationAttribute, 1, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}

void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  // Release shader program, VBO and VAO
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_VBOVertices);
  abcg::glDeleteBuffers(1, &m_VBOTranslation);

  abcg::glDeleteVertexArrays(1, &m_VAO);
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();

  {
    ImGui::SetNextWindowPos(ImVec2(5, 81));
    ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoDecoration);

    if (ImGui::Button("Clear window", ImVec2(150, 30))) {
      abcg::glClear(GL_COLOR_BUFFER_BIT);
    }

    ImGui::End();
  }
}