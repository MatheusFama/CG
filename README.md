# FuturisticMuseum
* Nome: Matheus Fama
* RA: 11040615
  
## Descrição
<p> O FuturisticMuseum proporciona uma visão inovadora ao representar um museu do futuro, onde cada obra do acervo é cuidadosamente disposta em sua própria plataforma, girando e movendo-se verticalmente, em uma simulação de gravidade artificial. Esse design permite que o observador aprecie cada peça de arte sob uma variedade de ângulos, proporcionando uma experiência única e dinâmica.
</p>
<p>  A ideia foi inspirada observando os projetos em aula. Os modelos 3d quando sem textura pareciam estátuas e, para demonstrar os conceitos aprendidos em aula, decidi movimentar os modelos das mais diversas formas dando uma perspectiva futurista para a cena.

Você pode ver o projeto [aqui](https://matheusfama.github.io/CG.github.io/public/futuristicmuseum.html).
</p>

### Museu
<table>
  <tr>
    <td>
      <img src="https://github.com/MatheusFama/CG-Assets/blob/main/futuristcmuseum.gif" width="300">
    </td>
  </tr>
</table>


## Organização do Projeto
O projeto foi separado nas seguintes classes:

* Base: classe que representa a base onde as estátuas estarão.
* Estatue: classe que representa a obra que estará sob as bases.
* Collection: classe que controlará o acervo de obras.
* Ground : classe que representa o terreno.
* Wall: classe que representa as quatro paredes da cena.
* Camera: classe que representa a visão do observador.


### Organização dos arquivos
<pre>
<code>jumpingsquare/
│   base.cpp
│   base.hpp
│   camera.cpp
│   camera.hpp
│   collection.cpp
│   colection.hpp
│   CMakeLists.txt
│   common.hpp
|   estatue.hpp
|   estatue.cpp
|   ground.hpp
|   ground.cpp
|   wall.hpp
|   wall.cpp  
│   main.cpp
│   window.hpp
│   window.cpp
│
└───assets/
    │   futuristicmuseum.frag
    └   futuristicmuseum.vert</code></pre>

### Cenário
O cenário será formado pelos seguintes objetos:
* A plataforma formada por GL_TRIANGLES;
* A estátua formada por GL_TRIANGLES;
* Terreno formado por GL_TRIANGLE_STRIP;
* A parede formado por GL_TRIANGLE_STRIP;
  
*obs: Vale ressaltar que os vértices utilizados para gerar cada modelo bem como a indexação dos mesmos encontram-se em arquivo obj.

### main.hpp
Construção padrão da classe main vista em aula.
<pre>
  <code >
  #include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    window.setOpenGLSettings({.samples = 4});
    window.setWindowSettings({
        .width = 600,
        .height = 600,
        .title = "LookAt Camera",
    });

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}
  </code>
</pre>

### window.hpp
<pre>
  <code>
  #ifndef WINDOW_HPP_
  #define WINDOW_HPP_
  
  #include "abcgOpenGL.hpp"
  
  #include "base.hpp"
  #include "camera.hpp"
  #include "collection.hpp"
  #include "common.hpp"
  #include "estatue.hpp"
  #include "ground.hpp"
  #include "wall.hpp"
  #include <random>
  
  class Window : public abcg::OpenGLWindow {
  protected:
    void onEvent(SDL_Event const &event) override;
    void onCreate() override;
    void onPaint() override;
    void onPaintUI() override;
    void onResize(glm::ivec2 const &size) override;
    void onDestroy() override;
    void onUpdate() override;
  
  private:
    glm::ivec2 m_viewportSize{};
  
    GLuint m_program{};
    GLuint base_program{};
    GLuint groundWall_program{};
  
    GLint m_viewMatrixLocation{};
    GLint m_projMatrixLocation{};
  
    Camera m_camera;
    float m_dollySpeed{};
    float m_truckSpeed{};
    float m_panSpeed{};
  
    Collection m_collection;
    Ground m_ground;
    Wall m_wall;
  
    std::vector<ObjectConfiguration> allConfigs;
    std::vector<glm::vec2> positions;
  
    std::default_random_engine m_randomEngine;
  };

#endif
  </code>
</pre>
  * glm::ivec2 m_viewportSize : indica o tamanaho da view port.
  * GLuint m_program: referência para o programa utilizado na estátuas.
  * GLuint base_program: referência para o programa utilizado na base.
  * GLuint groundWall_program: referência para o programa utilizado no chão/paredes.
  * GLuint m_viewMatrixLocation: referência para a matriz de visão.
  * GLuint m_projMatrixLocation: referência para a matriz de projeção.
  * Camera m_camera: referência para o observador.
  * float m_dollySpeed: variavel responsável por ativar a direção do movimento de trás e frente da camera.
  * float m_truckSpeed: variavel responsável por ativar a direação do movimento lateral da camera.
  * float m_panSpeed: variavel responsável por ativar a direção do giro da camera em seu próprio eixo.
  * Collection m_collection: responsável por gerenciar o acervo do múseu.
  * Ground m_ground: responsável por desenhar o chão.
  * Wall m_wall: responsável por desenhar o chão.
  * std::vector<ObjectConfiguration> allConfigs: Lista de configurações das estátuas.
  * std::vector<glm::vec2> positions: lista de configurações das posições inciais.
  * std::default_random_engine m_randomEngine: Seed para aleatorizar quando será gerado o próximo obstáculo.

 De modo geral, a window.cpp irá criar uma lista aletória de configuralções onde serão selecionados as obras que serão dispostas na tela. As configurações selecionadas serão guardadas em "allConfigs" que será o parametro para 
m_collection. Alguns parametrôs como posição e cores serão definidos de maneira aleatória e outros como escala, altura, etc serão pré-definidos pois eram necessidades dos modelos adotados de se adequarem a cena proposta.

### ObjectConfiguration

Estrutura que define as configurações do modelo
<pre>
  <code>
struct ObjectConfiguration {
  glm::vec2 startPosition;
  float minHigh;
  float maxHigh;
  bool verticalRotate;
  float radiusVerticalRotate;
  float scale;
  std::string path;
  bool choosed;
  float rotationSpeed;
  std::string normalTexturepath;
  std::string difuseTexturepath;
  int mode;
};
</code>
</pre>

* glm::vec2 startPosition : define a posição incial do modelo.
* float minHigh : define a posição minima do eixo y.
* float maxHigh : define a posição máxima do eixo y
* bool verticalRotate : defina se será necessário realizar a rotação em outro eixo para ajustar o modelo. Alguns modelos (cat.obj por exemplo) não vieram na posição adequada e necessitam deste parametro.
* float radiusVerticalRotate : define em quanto o modelo irá rotacionar.
* float scale : define a escala do modelo.
* std::string path : caminho do arquivo obj do modelo. 
* float rotationSpeed : define a velocidade de rotação
* std::string difuseTexturepath; : caminho onde estaão definidas a configuração da textura.

### ground.cpp

Classe que gera o chão. O código em si é idêntico ao visto em aula apenas adicionei uma linha vermelha para simular um tapete.

<pre>
<code>
  #ifndef GROUND_HPP_
  #define GROUND_HPP_
  
  #include "abcgOpenGL.hpp"
  
  class Ground {
  public:
    void create(GLuint program);
    void paint(glm::mat4 viewMatrix, glm::mat4 projMatrix);
    void destroy();
  
  private:
    GLuint m_VAO{};
    GLuint m_VBO{};
  
    GLint m_modelMatrixLoc{};
    GLint m_viewMatrixLoc{};
    GLint m_projMatrixLoc{};
    GLint m_colorLoc{};
  };
  
  #endif
</code>
</pre>

* GLuint m_VAO : guarda a referência do VAO.
* GLuint m_VBO: guarda a referência do VBO.
* GLint m_modelMatrixLoc: guarda a localização da matriz de modelo.
* GLint m_viewMatrixLoc: guarda a localização da matriz de visão.
* GLint m_projMatrixLoc: guarda a localização da matriz de projeção.
* GLint m_colorLoc: guarda a localização da cor.
* void create(GLuint program) : método responsável por criar os vértices, VBO, VBA que serão utilizados.
* void paint() : método responsável por desenhar o grid de quadrados.
* void destroy() : método responsável por destruir VBO e VAO utilizados.


### wall.cpp
Wall é a classe responsável por desenhar as parades da sala. O código foi inspirado no ground.cpp visto em aula apenas transladei para outros planos e rotacionei (no caso das parades traseira e frontal) para se ajustarem ao plano correto pois, inicialmente, o quadrado é iniciado no plano yz.

<pre>
  <code>
  #ifndef WALL_HPP_
  #define WALL_HPP_
  
  #include "abcgOpenGL.hpp"
  
  class Wall {
  public:
    void create(GLuint program);
    void paint(glm::mat4 viewMatrix, glm::mat4 projMatrix);
    void destroy();
  
  private:
    GLuint m_VAO{};
    GLuint m_VBO{};
  
    GLint m_modelMatrixLoc{};  
    GLint m_viewMatrixLoc{};
    GLint m_projMatrixLoc{};
    GLint m_colorLoc{};
  };
  
  #endif
  </code>
</pre>


* GLuint m_VAO : guarda a referência do VAO.
* GLuint m_VBO: guarda a referência do VBO.
* GLint m_modelMatrixLoc: guarda a localização da matriz de modelo.
* GLint m_viewMatrixLoc: guarda a localização da matriz de visão.
* GLint m_projMatrixLoc: guarda a localização da matriz de projeção.
* GLint m_colorLoc: guarda a localização da cor.
* void create(GLuint program) : método responsável por criar os vértices, VBO, VBA que serão utilizados.
* void paint() : método responsável por desenhar o grid de quadrados.
* void destroy() : método responsável por destruir VBO e VAO utilizados.


### base.cpp

Classe responsável por desenhar a base cilindrica que ficará embaixo da estátua.
<pre>
  <code>
  #ifndef BASE_HPP_
#define BASE_HPP_

#include "common.hpp"
class Base {
public:
  void create(GLuint program, std::string_view path, glm::vec2 position,glm::vec4 lightDir);
  void paint(glm::mat4 viewMatrix);
  void destroy();
  void loadObj(std::string_view path);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);

private:
  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_normalMatrixLoc{};
  GLint m_lightDirWorldSpace{};

  GLint m_IaLoc{};
  GLint m_IdLoc{};
  GLint m_IsLoc{};
  GLint m_KaLoc{};
  GLint m_KdLoc{};
  GLint m_KsLoc{};
  GLint m_shininessLoc{};

  GLint m_colorLocation{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;
  glm::vec2 startPosition;
  bool m_hasNormals{false};

  float high{0.15f};

  // Light and material properties
  glm::vec4 m_lightDir{-1.0f, -1.0f, -1.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka{0.1f, 0.1f, 0.1f, 1.0f};
  glm::vec4 m_Kd{0.7f, 0.7f, 0.7f, 1.0f};
  glm::vec4 m_Ks{1.0f};
  float m_shininess{25.0f};
    
  void computeNormals();
  void createBuffers();
};
#endif
  </code>
</pre>

* GLuint m_program : referência do programa utilizado.
* GLuint m_VAO: referência do VAO.
* GLuint m_VBO: referência do VBO.
* GLuint m_EBO: referência do EBO.
* GLint m_viewMatrixLocation: localização da matriz de visão
* GLint m_projMatrixLocation: localização da matriz de projeção
* GLint m_modelMatrixLocation: localização da matriz do modelo
* GLint m_normalMatrixLoc: localização da matriz normal
* GLint m_lightDirWorldSpace: localização da fonte de luz
* GLint m_IaLoc: localização da constante de Ia
* GLint m_IdLoc: localização da constante de Id
* GLint m_IsLoc: localização da constante de Is
* GLint m_KaLoc: localização da constante de Ka
* GLint m_KdLoc: localização da constante de Kd
* GLint m_KsLoc: localização da constante de Ks
* GLint m_shininessLoc: localização da constante de brilho
* glm::vec4 m_lightDir : localização padrão da luz
* glm::vec4 m_Ia : valor padrão da constante Ia
* glm::vec4 m_Id : valor padrão da constante Id 
* glm::vec4 m_Is : valor padrão da constante Is
* glm::vec4 m_Ka : valor padrão da constante Ka 
* glm::vec4 m_Kd : valor padrão da constante Kd
* glm::vec4 m_Ks : valor padrão da constante Ks
* float m_shininess : valor padrão do brilho
* std::vector<Vertex> m_vertices : conjunto de vértices do modelo.
* std::vector<GLuint> m_indices : conjunto de índices do modelo.
* glm::vec2 startPosition : posição inicial.
* float high: altura da base. 
* void loadObj(std::string_view path) : método utilizado para carregar o modelo.
* void create(GLuint program, std::string_view path, glm::vec2 position,glm::vec4 lightDir); : método utilizado para carregar os véticos, criar VBO, VAO, EBO que serão utilizados para gerar o modelo.
* void render(int numTriangles = -1) : método responsável por renderizar o modelo.
* void setupVAO(GLuint program) : método responsável por configurar o VAO.
* void computeNormals() : método responsável por calcular e armazenar o vertices normais.
* void createBuffers() : método responsável por criar os buffers VBO e EBO
* void paint(glm::mat4 viewMatrix) : método responsável por desenhar a base.
* void destroy() : método responsável por destruir os recursos utilizados.


### estatue.cpp
Classe responsável por desenhar a estátua com base nas configurações selecionadas.

<pre>
  <code>
  #ifndef ESTATUE_HPP_
#define ESTATUE_HPP_

#include "common.hpp"

class Estatue {
public:
  void create(GLuint program, ObjectConfiguration configuration);
  void paint(glm::mat4 m_viewMatrix);
  void update(float deltaTime);
  void destroy();

private:
  void loadDiffuseTexture(std::string_view path);
  void loadNormalTexture(std::string_view path);
  void loadObj(std::string_view path);
  void render(int numTriangles = -1) const;
  void setupVAO(GLuint program);

  GLuint m_program{};

  GLuint m_VAO{};
  GLuint m_VBO{};
  GLuint m_EBO{};

  GLint m_viewMatrixLocation{};
  GLint m_projMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_modelNormalMatrixLoc{};
  GLuint m_diffuseTexture{};
  GLuint m_normalTexture{};

  std::vector<Vertex> m_vertices;
  std::vector<GLuint> m_indices;

  bool up{true};
  float high{0.0f};
  float radius{0.0f};

  glm::vec2 startPosition{0, 0};
  float minHigh{0.0f};
  float maxHigh{0.0f};
  bool verticalRotate{false};
  float radiusVerticalRotate{0.0f};
  float scale{0.0f};
  float rotationSpeed{0.0f};
  std::string path{""};
  std::string normalTexturepath{""};
  std::string difuseTexturepath{""};
  bool choosed{false};

  // Light and material properties
  glm::vec4 m_lightDir{0.5f, -1.0f, 0.0f, 0.0f};
  glm::vec4 m_Ia{1.0f};
  glm::vec4 m_Id{1.0f};
  glm::vec4 m_Is{1.0f};
  glm::vec4 m_Ka{};
  glm::vec4 m_Kd{};
  glm::vec4 m_Ks{};

  float m_shininess{};
  bool m_hasNormals{false};
  bool m_hasTexCoords{false};
  int m_mappingMode{3};

  void computeNormals();
  void computeTangents();
  void createBuffers();
};
#endif
  </code>
</pre>

Os campos são os mesmos do objeto ObjectConfiguration.

* void create(GLuint program, ObjectConfiguration configuration) : Configura o modelo com base na configuração recebida por parâmetro.
* void paint() : método responsável por desenhar o modelo.
* void update(float deltaTime) : método responsável por determinar a posição do modelo.
* void destroy() : método responsável por eliminar os recursos utilizados.
* void loadObj(std::string_view path) : método utilizado para carregar o modelo.
* void create(GLuint program, std::string_view path, glm::vec2 position,glm::vec4 lightDir): método utilizado para carregar os véticos, criar VBO, VAO, EBO que serão utilizados para gerar o modelo.
* void render(int numTriangles = -1) : método responsável por renderizar o modelo.
* void setupVAO(GLuint program) : método responsável por configurar o VAO.
* void computeNormals() : método responsável por calcular e armazenar o vertices normais.
* void createBuffers() : método responsável por criar os buffers VBO e EBO
* void paint(glm::mat4 viewMatrix) : método responsável por desenhar a base.
* GLint m_lightDirWorldSpace: localização da fonte de luz
* GLint m_IaLoc: localização da constante de Ia
* GLint m_IdLoc: localização da constante de Id
* GLint m_IsLoc: localização da constante de Is
* GLint m_KaLoc: localização da constante de Ka
* GLint m_KdLoc: localização da constante de Kd
* GLint m_KsLoc: localização da constante de Ks
* GLint m_shininessLoc: localização da constante de brilho
* glm::vec4 m_lightDir : localização padrão da luz
* glm::vec4 m_Ia : valor padrão da constante Ia
* glm::vec4 m_Id : valor padrão da constante Id 
* glm::vec4 m_Is : valor padrão da constante Is
* glm::vec4 m_Ka : valor padrão da constante Ka 
* glm::vec4 m_Kd : valor padrão da constante Kd
* glm::vec4 m_Ks : valor padrão da constante Ks

### collection.cpp
Classe responsável por gerenciar a lista de bases e estátuas.
<pre>
  <code>
  #ifndef COLLECTION_HPP_
  #define COLLECTION_HPP_
  
  #include "abcgOpenGL.hpp"
  
  #include "base.hpp"
  #include "common.hpp"
  #include "estatue.hpp"
  
  class Collection {
  public:
    void create(GLuint program, GLuint base_program,
                std::vector<ObjectConfiguration> configs,
                std::string_view basePath);
    void paint(glm::mat4 m_viewMatrix, glm::mat4 projMatrix);
    void update(float deltaTime);
    void destroy();
  
  private:
    GLuint m_program{};
    GLuint b_program{};
    GLuint m_viewMatrixLocation{};
    GLuint m_projMatrixLocation{};
    GLuint b_viewMatrixLocation{};
    GLuint b_projMatrixLocation{};
  
    std::vector<Base> m_bases;
    std::vector<Estatue> m_estatues;
    std::string_view objBasePath;
  };
  
  #endif
  </code>
</pre>

* GLuint m_program: referência do programa.
* std::vector<Base> m_bases : lista de bases.
* std::vector<Estatue> m_estatues : lista de estátuas.
* std::string_view objBasePath : caminho do arquivo obj da base.
* void create(GLuint program, std::vector<ObjectConfiguration> configs, std::string_view basePath) : método responsável por criar e configurar a lista de bases e estátuas.
* void paint() : método responsável por desenhar a coleção de bases e estátuas.
* void update(float deltaTime): método responsável por atualizar a posição das estátuas.
* void destroy() : método responsável por liberar os recursos utilizados.
