# Planejamento — Conjunto de Mandelbrot

Cronograma em blocos de estudo/execução, 3 dias. Cada bloco: conceito + subtarefas técnicas + testes esperados.

## DIA 1 — Fundamentos + Serial
**Hora 1-2 — Conceito**: número complexo, iteração z=z²+c, critério de escape, mapeamento pixel→plano complexo.
- Subtarefas: Fase 1 e 2 da Ordem de Implementação (parsing, validação, núcleo matemático)
- Teste esperado: função de iteração retorna valores corretos para pontos conhecidos (ex: c=0 nunca escapa, c=2 escapa rápido)

**Hora 3-4 — Serial**
- Subtarefas: Fase 3 (loop serial, escrita `.pgm`, medição de tempo)
- Teste esperado: `.pgm` gerado abre corretamente como imagem em escala de cinza; times.txt populado

## DIA 2 — Paralelismo
**Hora 1-2 — OpenMP**
- Subtarefas: Fase 4
- Teste esperado: saída idêntica ao serial; tempo menor com mais threads

**Hora 3-5 — Pthreads (2 estratégias)**
- Subtarefas: Fase 5 e 6
- Teste esperado: ambas saídas idênticas ao serial; comparar tempo entre as duas estratégias de divisão

## DIA 3 — Robustez, consolidação e entrega
**Hora 1-2 — Erros**
- Subtarefas: Fase 8 (todos os casos de erro do enunciado)
- Teste esperado: cada erro dispara mensagem coerente em stderr e encerra sem crash

**Hora 3 — Consistência**
- Subtarefas: Fase 9 (diff entre os 4 arquivos, times.txt consolidado)

**Hora 4-5 — Empacotamento**
- Subtarefas: Fase 10 (Makefile, relatório, commits atômicos, nomeação de entrega)
- Teste esperado: `make` compila limpo, `make clean` remove binários, .tar com nome correto
