/*****************************************************************************
 * Este programa é baseado no exemplo "Hello-Triangle" disponível 
 * em 
 *     https://learnopengl.com/Getting-started/Hello-Triangle
 * 
 *     A principal diferença entre este programa e o exemplo acima é que neste
 * os vertex e fragment shaders são carregados a partir de arquivos externos, 
 * ao inves de estarem hard coded no código fonte. 
 *     Isso da mais flexibilidade para se fazerem experimentos com os shaders, 
 * pois nao e necessario se recompilar o programa a cada vez que os shaders forem
 * alterados.
 ****************************************************************************/
#include "main.h"

#define IMAGE_WIDTH 512  // Largura da janela OpenGL em pixels.
#define IMAGE_HEIGHT 512 // Altura da janela OpenGL em pixels.

using namespace std;

// Array contendo as coordenadas X,Y e Z de tres vertices (um trianglulo).
float vertices[] = {-0.25f, -0.5f, -0.1f, 0.75f, 0.0f, 0.0f, // red triangle (closer)
                    0.25f, 0.5f, -0.1f, 0.75f, 0.0f, 0.0f,
                    0.75f, -0.5f, -0.1f, 0.75f, 0.0f, 0.0f,
                    -0.75f, -0.5f, -0.4f, 0.0f, 0.0f, 0.75f, // blue triangle (farther)
                    -0.25f, 0.5f, -0.4f, 0.0f, 0.0f, 0.75f,
                    0.25f, -0.5f, -0.4f, 0.0f, 0.0f, 0.75f};

char *frag_shader_source = NULL;
char *vertex_shader_source = NULL;
unsigned int shader_program;
unsigned int vbo; // Vertex buffer object ID
unsigned int vao; // Vertex array object ID

float module(float a, float b, float c)
{
    return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
}

void vetorial(float *vector1, float *vector2, float *vectorReturn)
{
    vectorReturn[0] = vector1[1] * vector2[2] - vector1[2] * vector2[1];
    vectorReturn[1] = vector1[2] * vector2[0] - vector1[0] * vector2[2];
    vectorReturn[2] = vector1[0] * vector2[1] - vector1[1] * vector2[0];
}

void calculate_zc(float *vector, float *vectorReturn)
{
    vectorReturn[0] = -1 * vector[0] / module(vector[0], vector[1], vector[2]);
    vectorReturn[1] = -1 * vector[1] / module(vector[0], vector[1], vector[2]);
    vectorReturn[2] = -1 * vector[2] / module(vector[0], vector[1], vector[2]);
}

void calculate_xc(float *vector1, float *vector2, float *vectorReturn)
{
    float v[3];

    vetorial(vector1, vector2, v);

    vectorReturn[0] = v[0] / module(v[0], v[1], v[2]);
    vectorReturn[1] = v[1] / module(v[0], v[1], v[2]);
    vectorReturn[2] = v[2] / module(v[0], v[1], v[2]);
}

void create_matrix_bt(float *vector1, float *vector2, float *b_t)
{
    float zc[3], xc[3], yc[3];

    calculate_zc(vector1, zc);
    calculate_xc(vector2, zc, xc);
    calculate_xc(zc, xc, yc);

    float bt[16] = {xc[0], yc[0], zc[0], 0.0f,
                    xc[1], yc[1], zc[1], 0.0f,
                    xc[2], yc[2], zc[2], 0.0f,
                    0.00f, 0.00f, 0.0f, 1.0f};

    int l;
    for (l = 0; l < 16; l++)
        b_t[l] = bt[l];
}

// void calculateMatrix()

//********************************************************************************************************************
// A função LoadShader() é baseada em https://stackoverflow.com/a/174552/6107321
void LoadShader(char *file_name, char **shader_source)
{
    long length;
    FILE *f = fopen(file_name, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        (*shader_source) = (char *)malloc(length + 1);
        if ((*shader_source))
        {
            fread((*shader_source), 1, length, f);
            (*shader_source)[length] = '\0';
        }

        fclose(f);
    }
    else
    {
        printf("Could not load the shader file %s\nExiting...", file_name);
        exit(EXIT_FAILURE);
    }
}

//********************************************************************************************************************
void Display(void)
{
    // Limpa a tela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Define a posição da Viewport dentro da janela OpenGL
    glViewport(0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);

    // Seleciona o Shader Program a ser utilizado.
    glUseProgram(shader_program);

    // Matriz Model ///////////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises
    float model_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat = glm::make_mat4(model_array);

    // 1/3 3/2 1
    float model_array1[16] = {0.33f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.50f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat1 = glm::make_mat4(model_array1);

    // 1 0 0
    float model_array2[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat2 = glm::make_mat4(model_array2);

    float model_array3[16] = {-1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat3 = glm::make_mat4(model_array3);

    float model_array4[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, -1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 model_mat4 = glm::make_mat4(model_array4);

    // Matriz View ////////////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises
    float view_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};

    glm::mat4 view_mat = glm::make_mat4(view_array);

    float b_array[16];
    float p[3]{-0.1f, 0.1f, 0.1f};
    float d[3]{0.1f, -0.1f, -1.1f};
    float u[3]{0.0f, 1.0f, 0.0f};

    create_matrix_bt(d, u, b_array);

    glm::mat4 b_t = glm::make_mat4(b_array);

    float b_array2[16];
    float p2[3]{1.0f, 0.9f, 2.5f};
    float d2[3]{0.0f, 0.1f, -2.5f};
    float u2[3]{0.0f, 1.0f, 0.0f};

    create_matrix_bt(d2, u2, b_array2);

    glm::mat4 b_t2 = glm::make_mat4(b_array2);

    float b_array3[16];
    float p3[3]{0.5f, 0.5f, 1.5f};
    float d3[3]{0.5f, -0.5f, -1.5f};
    float u3[3]{0.0f, 1.0f, 0.0f};

    create_matrix_bt(d3, u3, b_array3);

    glm::mat4 b_t3 = glm::make_mat4(b_array3);

    float t_array[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                         0.00f, 1.00f, 0.00f, 0.00f,
                         0.00f, 0.00f, 1.00f, 0.00f,
                         -p[0], -p[1], -p[2], 1.00f};

    glm::mat4 t = glm::make_mat4(t_array);

    float t_array2[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                          0.00f, 1.00f, 0.00f, 0.00f,
                          0.00f, 0.00f, 1.00f, 0.00f,
                          -p2[0], -p2[1], -p2[2], 1.00f};

    glm::mat4 t2 = glm::make_mat4(t_array2);

    float t_array3[16] = {1.00f, 0.00f, 0.00f, 0.00f,
                          0.00f, 1.00f, 0.00f, 0.00f,
                          0.00f, 0.00f, 1.00f, 0.00f,
                          -p3[0], -p3[1], -p3[2], 1.00f};

    glm::mat4 t3 = glm::make_mat4(t_array3);

    // Matriz Projection //////////////////////////////////////////////////////
    // You will have to change the contents of this matrix for the exercises
    float proj_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f, 0.0f,
                            0.0f, 0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f};
    // afasd
    glm::mat4 proj_mat = glm::make_mat4(proj_array);

    float proj_array2[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, -8.0f,
                             0.0f, 0.0f, 0.125f, 0.0f};

    glm::mat4 proj_mat2 = glm::make_mat4(proj_array2);

    float proj_array3[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f, 0.0f,
                             0.0f, 0.0f, 1.0f, -1.2f,
                             0.0f, 0.0f, 0.83f, 0.0f};

    glm::mat4 proj_mat3 = glm::make_mat4(proj_array3);

    // Thr NDC is a left handed system, so we flip along the Z axis.
    // IMPORTANT: Do not change the contents of this matrix!!!!!!
    float flip_z_array[16] = {1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, -1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f};
    glm::mat4 flip_z_mat = glm::make_mat4(flip_z_array);

    // Matriz ModelViewProjection /////////////////////////////////////////////
    glm::mat4 model_view_proj_mat = flip_z_mat * proj_mat * view_mat * model_mat;

    glm::mat4 model_view_proj_mat1 = flip_z_mat * proj_mat * view_mat * model_mat1; // Questao 1.

    glm::mat4 model_view_proj_mat2 = flip_z_mat * proj_mat * view_mat * model_mat2; // Questao 2.

    glm::mat4 model_view_proj_mat3 = flip_z_mat * proj_mat2 * view_mat * model_mat; // Questao 3.

    glm::mat4 model_view_proj_mat4 = flip_z_mat * proj_mat2 * (b_t * t) * model_mat; // Questao 3.

    glm::mat4 model_view_proj_mat5 = flip_z_mat * proj_mat3 * (b_t2 * t2) * model_mat3; // Questao 3.

    glm::mat4 model_view_proj_mat6 = flip_z_mat * proj_mat3 * (b_t3 * t3) * model_mat4; // Questao 3.

    unsigned int transformLoc;
    GL_CHECK(transformLoc = glGetUniformLocation(shader_program, "transform"));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat1));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat2));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat3));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat4));
    // glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat5));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model_view_proj_mat6));

    // Ativa o Vertex Array Object selecionado.
    glBindVertexArray(vao);

    // Desenha as tres primeiras primitivias, comecando pela de indice 0.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glFlush();           //
    glutSwapBuffers();   //
    glutPostRedisplay(); //
}

//********************************************************************************************************************
void ExitProg(void)
{
    if (vertex_shader_source)
    {
        free(vertex_shader_source);
        vertex_shader_source = NULL;
    }

    if (frag_shader_source)
    {
        free(frag_shader_source);
        frag_shader_source = NULL;
    }

    printf("Exiting...\n");
}

//********************************************************************************************************************
int main(int argc, char **argv)
{
    // Inicializa a GLUT
    glutInit(&argc, argv);

    // Cria um color buffer onde cada pixel é representado por 4 bytes (RGBA)
    // Cria um depth buffer (para resolver a oclusão)
    // Cria dois color buffers para reduzir o flickering
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // Define as dimensões do color buffer (ou a área útil do OpenGL na janela)
    glutInitWindowSize(IMAGE_WIDTH, IMAGE_HEIGHT);

    // Posição do canto superior esquerdo da janela OpenGL em relação a tela do computador.
    glutInitWindowPosition(100, 100);

    // Título da janela
    glutCreateWindow("Modern OpenGL: Assignment 3");

    // Load the OpenGL extensions
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    // Carrega o codigo fonte do Vertex shader
    LoadShader("vertex_shader.glsl", &vertex_shader_source);

    printf("%s\n", vertex_shader_source);

    unsigned int vertex_shader;

    // Cria um identificador para o Vertex Shader
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    // Vincula o código fonte do Vertex Shader ao seu identificador
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);

    // Compila dinamicamente (em tempo de execucao) o Vertex Shader
    glCompileShader(vertex_shader);

    // Imprime eventuais mensagens de erro de compilacao do Vertex Shader
    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
    }

    // Carrega o codigo fonte do Fragment shader
    LoadShader("fragment_shader.glsl", &frag_shader_source);

    printf("%s\n", frag_shader_source);

    unsigned int fragment_shader;

    // Cria um identificador para o Fragment Shader
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Vincula o código fonte do Fragment Shader ao seu identificador
    glShaderSource(fragment_shader, 1, &frag_shader_source, NULL);

    // Compila dinamicamente (em tempo de execucao) o Fragment Shader
    glCompileShader(fragment_shader);

    // Imprime eventuais mensagens de erro de compilacao do Fragment Shader
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", info_log);
    }

    // Cria um identificador para um Shader program (vertex + fragment shader)
    shader_program = glCreateProgram();

    // Vincula os Fragment e Vertex Shaders ao Program Shader
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);

    // Linka o Fragment e Vertex Shader para formarem o Program Shader
    glLinkProgram(shader_program);

    // Imprime eventuais mensagens de erro de linkagem do Program Shader
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
    }

    // Deleta os Fragment e Vertex Shaders, já que eles já foram incorporados
    // ao Program Shader e não são mais necessários.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Ativa o Vertex Array Object (VAO)
    glBindVertexArray(vao);

    // Cria um novo identificador de buffer
    glGenBuffers(1, &vbo);

    // Vincula o buffer criado a um Vertex Buffer Object (VBO)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Carrega as propriedades (coordenadas + cores) dos vértices no VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Atributo 'posição' do vértice
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Atributo 'cor' do vértice
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define a cor a ser utilizada para limpar o color buffer a cada novo frame
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita o teste de profundidade (oclusão).
    GL_CHECK(glEnable(GL_DEPTH_TEST));

    atexit(ExitProg);         // deifne o callback de saída do programa
    glutDisplayFunc(Display); // define o callback que renderizará cada frame

    // Framebuffer scan loop.
    glutMainLoop();

    return EXIT_SUCCESS;
}
