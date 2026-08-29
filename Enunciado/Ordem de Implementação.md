# Ordem de Implementação — Conjunto de Mandelbrot

Backlog incremental. Cada fase constrói sobre a anterior. Marcar `[X]` ao concluir.

## 🧱 Fase 1 — Esqueleto e parsing de argumentos
- [X] Estrutura do projeto: `src/`, `Makefile`, `.gitignore`
- [X] Parsing de `argc/argv`: `mandelbrot [largura] [altura] [max_iteracoes] [num_threads]`
- [X] Validação: número correto de argumentos (senão erro + saída)
- [X] Validação: largura, altura, max_iteracoes, num_threads > 0 e numéricos
- [X] Mensagens de erro coerentes via stderr, programa não imprime nada em stdout no fluxo normal

## 🧮 Fase 2 — Núcleo matemático do Mandelbrot
- [X] Função de mapeamento pixel → ponto complexo c (região real [-2.0,1.0], imaginária [-1.5,1.5])
- [X] Função de iteração: z0=0, z_novo = z² + c, critério de escape (|z|>2) até max_iteracoes
- [X] Normalização do nº de iterações para intensidade 0–255
- [X] Teste isolado: comparar saída da função para poucos pontos calculados à mão

## 🖼️ Fase 3 — Implementação Serial + escrita do arquivo
- [X] Implementação serial completa (duplo loop sobre largura x altura)
- [X] Escrita do arquivo `.pgm` sem cabeçalho: 1 valor por pixel, separados por espaço, 1 linha por linha da imagem
- [X] Medição de tempo de execução do cálculo (ex: `clock_gettime`)
- [X] Gravar tempo em `times.txt`
- [X] Nomeação correta: `mandelbrot_<login>_serial.pgm`

## 🚀 Fase 4 — Implementação OpenMP
- [X] Paralelizar o loop de cálculo dos pontos com `#pragma omp parallel for`
- [X] Garantir que só o trecho de CPU-intensivo (cálculo) está paralelizado
- [X] Medir tempo e gravar em `times.txt`
- [X] Gerar `mandelbrot_<login>_openmp.pgm` e conferir que é idêntico ao serial

## 🧵 Fase 5 — Pthreads 1 (divisão estática por blocos)
- [X] Dividir a imagem em blocos contíguos de linhas, um bloco por thread (`num_threads`)
- [X] Criar/join das threads, cada thread calcula seu bloco e escreve no buffer compartilhado
- [X] Medir tempo e gravar em `times.txt`
- [X] Gerar `mandelbrot_<login>_pthreads1.pgm` e conferir identidade com serial

## 🧵 Fase 6 — Pthreads 2 (estratégia distinta de divisão)
- [X] Escolher estratégia diferente da Fase 5 (ex: round-robin de linhas, ou fila dinâmica de trabalho/work-stealing)
- [X] Implementar sincronização necessária (mutex se houver fila compartilhada)
- [X] Medir tempo e gravar em `times.txt`
- [X] Gerar `mandelbrot_<login>_pthreads2.pgm` e conferir identidade com serial

## 📄 Fase 7 — Consolidação do times.txt
- [X] Garantir que `times.txt` contém os 4 tempos (serial, openmp, pthreads1, pthreads2) num formato único e claro
- [X] Conferir que nenhuma implementação escreve nada em stdout

## 🛡️ Fase 8 — Revisão de erros e robustez
- [X] Erro: número incorreto de argumentos
- [X] Erro: parâmetros inválidos (largura/altura/max_iteracoes/num_threads)
- [X] Erro: falha na criação do arquivo de saída
- [X] Erro: falha na alocação de memória
- [X] Erro: falha na criação de threads
- [X] Testar com casos extremos (threads=1, imagem 1x1, max_iteracoes=0, etc.)

## ✅ Fase 9 — Verificação de consistência entre implementações
- [X] Script/comando para comparar os 4 `.pgm` byte a byte (`diff`)
- [X] Rodar com diferentes tamanhos e num_threads, confirmar sempre idênticos
- [X] Registrar evidências (prints/logs) para o relatório

## 📦 Fase 10 — Empacotamento e entrega
- [X] Makefile (build + clean)
- [X] Commits atômicos no Github, link incluído no relatório
- [ ] Relatório em PDF seguindo o Guia de Relatórios da disciplina (dificuldades, limitações, evidências de teste)
- [ ] Diretório e .tar nomeados corretamente com o login (iniciais do e-mail)
- [ ] Conferir nomes: `login.pdf`, `login.tar`, diretório `login/`
