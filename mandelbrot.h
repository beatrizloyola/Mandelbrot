#ifndef MANDELBROT_H
#define MANDELBROT_H

void pixel_para_complexo(int x, int y, int largura, int altura, double *real, double *imag);
int iterar(double c_real, double c_imag, int max_iteracoes);
int normalizar(int num_iteracoes, int max_iteracoes);
int escrever_pgm(int *buffer, int largura, int altura, char *nome_arquivo);
int executar_serial(int largura, int altura, int max_iteracoes);

#endif