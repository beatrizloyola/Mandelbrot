#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

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

int escrever_pgm(int *buffer, int largura, int altura, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: falha ao criar arquivo de saída\n");
        return 1;
    }

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            fprintf(arquivo, "%d", buffer[y * largura + x]);
            if (x < largura - 1)
                fprintf(arquivo, " ");
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);
    return 0;
}

int escrever_tempo(const char *rotulo, double tempo){
    FILE *log_tempo = fopen("times.txt", "a");
    if (log_tempo == NULL) {
        fprintf(stderr, "Erro: falha ao criar arquivo de tempos\n");
        return -1;
    }

    fprintf(log_tempo, "%s: %.6f segundos\n", rotulo, tempo);
    fclose(log_tempo);
    return 0;
}

int executar_serial(int largura, int altura, int max_iteracoes){
    int x, y;
    struct timespec inicio, fim;
    int *buffer = malloc(largura * altura * sizeof(int));

    if (buffer == NULL){
        fprintf(stderr, "Erro na alocação de memória\n");
        return -1;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (y = 0; y < altura; y++){
        for (x = 0; x < largura; x++){
            double real, imag;
            pixel_para_complexo(x, y, largura, altura, &real, &imag);
            int num_iteracoes = iterar(real, imag, max_iteracoes);
            int intensidade = normalizar(num_iteracoes, max_iteracoes);
            buffer[y * largura + x] = intensidade;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    if (escrever_pgm(buffer, largura, altura, "mandelbrot_blgv_serial.pgm") != 0){
        free(buffer);
        return -1;
    }

    if(escrever_tempo("Serial", tempo) != 0){
        free(buffer);
        return -1;
    }

    free(buffer);
    return 0;
}

int executar_openmp(int largura, int altura, int max_iteracoes, int num_threads){
    int x, y;
    struct timespec inicio, fim;
    int *buffer = malloc(largura * altura * sizeof(int));

    if (buffer == NULL){
        fprintf(stderr, "Erro na alocação de memória\n");
        return -1;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    #pragma omp parallel for num_threads(num_threads)
    for (y = 0; y < altura; y++) {
        for (x = 0; x < largura; x++) {
            double real, imag;
            pixel_para_complexo(x, y, largura, altura, &real, &imag);
            int num_iteracoes = iterar(real, imag, max_iteracoes);
            int intensidade = normalizar(num_iteracoes, max_iteracoes);
            buffer[y * largura + x] = intensidade;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);

    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;
    if (escrever_pgm(buffer, largura, altura, "mandelbrot_blgv_openmp.pgm") != 0){
        free(buffer);
        return -1;
    }

    if(escrever_tempo("OpenMP", tempo) != 0){
        free(buffer);
        return -1;
    }

    free(buffer);
    return 0;

}