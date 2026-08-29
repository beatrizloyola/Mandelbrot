#include <stdio.h>
#include <stdlib.h>
#include "mandelbrot.h"

int main (int argc, char *argv[]){
    if (argc != 5){
        fprintf(stderr, "Quantidade de argumentos inválida\n");
        exit(1);
    }

    char *endptr;

    long largura = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || largura <= 0) {
        fprintf(stderr, "Erro: largura inválida\n");
        exit(1);
    }

    long altura = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || altura <= 0) {
        fprintf(stderr, "Erro: altura inválida\n");
        exit(1);
    }

    long max_iteracoes = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || max_iteracoes <= 0) {
        fprintf(stderr, "Erro: quantidade máxima de iterações inválida\n");
        exit(1);
    }

    long num_threads = strtol(argv[4], &endptr, 10);
    if (*endptr != '\0' || num_threads <= 0) {
        fprintf(stderr, "Erro: quantidade de threads inválida\n");
        exit(1);
    }
    
    int resultado;

    // Teste Serial
    resultado = executar_serial((int)largura, (int)altura, (int)max_iteracoes);
    if (resultado != 0) {
        fprintf(stderr, "Erro na execução serial\n");
        return 1;
    }

    // Teste OpenMP
    resultado = executar_openmp((int)largura, (int)altura, (int)max_iteracoes, (int)num_threads);
    if (resultado != 0) {
        fprintf(stderr, "Erro na execução serial\n");
        return 1;
    }

    return 0;
}