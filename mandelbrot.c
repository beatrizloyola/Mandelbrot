#include <stdio.h>

void pixel_para_complexo(int x, int y, int largura, int altura, double *real, double *imag) {
    *real = -2.0 + (x / (double)(largura - 1)) * 3.0;
    *imag = -1.5 + (y / (double)(altura - 1)) * 3.0;
}

int iterar(double c_real, double c_imag, int max_iteracoes) {
    double z_real = 0.0;
    double z_imag = 0.0;
    int num_iteracoes;

    for (num_iteracoes = 0; num_iteracoes < max_iteracoes; num_iteracoes++) {
        double z_real2 = z_real * z_real;
        double z_imag2 = z_imag * z_imag;

        if (z_real2 + z_imag2 > 4.0){
            break;
        }

        double novo_real = z_real2 - z_imag2 + c_real;
        double novo_imag = 2.0 * z_real * z_imag + c_imag;

        z_real = novo_real;
        z_imag = novo_imag;
    }

    return num_iteracoes;
}

int normalizar(int num_iteracoes, int max_iteracoes){
    double normalizado = ((double)num_iteracoes / (double)max_iteracoes) * 255;
    return (int)normalizado;
}