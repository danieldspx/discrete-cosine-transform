/*********************************************************************
// Canvas para desenho, criada sobre a API OpenGL. Nao eh necessario conhecimentos de OpenGL para usar.
//  Autor: Cesar Tadeu Pozzer
//         05/2020
//
//  Pode ser utilizada para fazer desenhos, animacoes, e jogos simples.
//  Tem tratamento de mouse e teclado
//  Estude o OpenGL antes de tentar compreender o arquivo gl_canvas.cpp
//
//  Versao 2.0
//
//  Instru��es:
//	  Para alterar a animacao, digite numeros entre 1 e 3
// *********************************************************************/

#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include "gl_canvas2d.h"

#include "Bola.h"
#include "Relogio.h"
#include "Botao.h"

int screenWidth = 800, screenHeight = 800; //largura e altura inicial da tela . Alteram com o redimensionamento de tela.
int mouseX, mouseY; //variaveis globais do mouse para poder exibir dentro da render().

void plotWaveform(std::vector<float>& data, int x, int y, int w, int h) {
    float maxElement = *std::max_element(data.begin(), data.end(), [](float a, float b){return std::abs(a) < std::abs(b);});
    // Compute the vertical scaling factor based on the maximum absolute value in the data array
    float scaleFactorY = h / (2 * std::abs(maxElement));

    // Compute the horizontal scaling factor
    float scaleFactorX = (float)w / data.size();

    // Draw the waveform
    for (int i = 0; i < data.size() - 1; i++) {
        float x0 = x + i * scaleFactorX;
        float y0 = y + (scaleFactorY * data[i]);
        float x1 = x + (i + 1) * scaleFactorX;
        float y1 = y + (scaleFactorY * data[i + 1]);
        // draw a line segment between (x0, y0) and (x1, y1)
        CV::line((int)x0, (int)y0, (int)x1, (int)y1);
    }
}

std::vector<float> fdct(std::vector<float> v) {
    int N = v.size();
    std::vector<float> transformed(N);

    for (int u = 0; u < N; u++) {
        float sum = 0;
        for (int x = 0; x < N; x++) {
            // The same as ((2*x + 1) * u * PI)/(2*N)
            sum += v[x] * std::cos(M_PI / N * (x + 0.5) * u);
        }

        if (u == 0) {
            transformed[u] = sum / std::sqrt(N); // Same as multiply std::sqrt(2.0 / N) * std::sqrt(1 / N) * sum
        } else {
            transformed[u] = std::sqrt(2.0 / N) * sum;
        }
    }

    return transformed;
}

//funcao chamada continuamente. Deve-se controlar o que desenhar por meio de variaveis globais
//Todos os comandos para desenho na canvas devem ser chamados dentro da render().
//Deve-se manter essa fun��o com poucas linhas de codigo.
std::vector<float> v{6, 18, 4, 200, 123, 65, 11, 241, 54, 154, 190, 2, 251, 201, 55, 143, 133, 102, 99, 201, 55, 21, 66, 65, 77, 1, 211, 87, 95, 103, 66, 137, 63, 98, 220, 102, 100, 9, 76, 32, 21, 144, 29, 1, 102, 198, 201, 11, 87, 21, 85, 230, 241, 21, 54, 94, 103, 191, 9, 32, 105, 43, 91, 102};
auto r = fdct(v);

void render() {
    CV::clear(0, 0, 0);

    CV::color(1, 0, 0);
    plotWaveform(v, 100, 100, 300, 80);
}

//funcao chamada toda vez que uma tecla for pressionada.
void keyboard(int key)
{
    printf("\nTecla: %d" , key);
}

//funcao chamada toda vez que uma tecla for liberada
void keyboardUp(int key)
{
    printf("\nLiberou: %d" , key);
}

//funcao para tratamento de mouse: cliques, movimentos e arrastos
void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    mouseX = x; //guarda as coordenadas do mouse para exibir dentro da render()
    mouseY = y;

//    printf("\nmouse %d %d %d %d %d %d", button, state, wheel, direction,  x, y);
}


int main(void)
{
    // std::vector<float> v{16,  11,  10,  16,  24,  40,  51,  61 };
    // auto r = fdct(v);
    // for (int i = 0; i < r.size(); i++) {
    //     printf("%f\n", r[i]);
    // }
   CV::init(&screenWidth, &screenHeight, "Discrete Cousine Transform");
   CV::run();
}
