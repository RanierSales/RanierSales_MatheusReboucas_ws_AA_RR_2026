# Experimento VerificaAlgo: Análise de Complexidade e Performance

Este repositório contém o experimento prático e a análise teórica do algoritmo **VerificaAlgo**, desenvolvido para a disciplina **DCC606 - Análise de Algoritmos** (UFRR). O objetivo é validar a complexidade assintótica teórica através de experimentos empíricos, comparando-os com um baseline de Busca Linear.

## 📊 O Experimento

O algoritmo analisado possui quatro laços de repetição aninhados. Enquanto o laço mais externo possui uma constante fixa de 10.000 iterações, os laços internos dependem do tamanho da entrada $n$, gerando um comportamento de custo elevado.

### Algoritmos Comparados
1.  **VerificaAlgo**: Algoritmo alvo da análise (Complexidade teórica $O(n^2)$).
2.  **LinearSearch**: Algoritmo de busca linear utilizado como baseline de performance ($O(n)$).

### Metodologia
* **Tamanhos de entrada ($n$):** 100, 300, 500, 700, 1000, 1500 e 2000.
* **Cenários de Dados:** Aleatórios, Ordenados Crescentes e Ordenados Decrescentes (Gerados via Transformada de Box-Muller para distribuição normal).
* **Repetições:** 13 execuções para cada cenário para extração de média e redução de ruído de hardware.

## 🧮 Análise Teórica (Resumo)

Conforme os cálculos detalhados em `docs/EquationSolution.pdf`, a função de custo encontrada foi:
$$T(n) = 10.000n^2 - 50.000n$$
Para valores de $n \ge 6$. Embora a complexidade assintótica seja **$O(n^2)$**, a constante massiva de 10.000 faz com que, em intervalos práticos, o algoritmo apresente uma inclinação de crescimento que se assemelha a funções de ordem superior em escalas log-log.

## 🚀 Como Rodar

### Pré-requisitos
* Compilador C (`gcc`)
* Python 3.10+
* Ambiente Virtual Python (recomendado)

### 1. Preparação do Ambiente
```bash
# Criar e ativar ambiente virtual
python -m venv venv
source venv/bin/activate  # Linux/Mac
# ou: venv\Scripts\activate  # Windows

# Instalar dependências
pip install pandas matplotlib numpy
```

### 2. Geração de Dados e Execução
Como os scripts foram desenhados para rodar na raiz:
```bash
# 1. Compilar os geradores e o experimento
gcc src/random_generator.c -o random_gen -lm
gcc src/sorted_generator.c -o sorted_gen -lm
gcc src/verificaAlgo.c -o experimento -lm

# 2. Gerar os dados binários (Exemplo para n=100)
./random_gen 100
./sorted_gen 100 asc
./sorted_gen 100 desc
# (Repetir para os demais tamanhos de n ou usar um script de automação)

# 3. Rodar o experimento
./experimento
```

### 3. Visualização dos Resultados
Após a geração do arquivo `experiment_results.csv`, rode o script de plotagem:
```bash
python src/plot_results.py
```

## 📂 Estrutura do Repositório
* `/src`: Códigos fonte em C e scripts Python.
* `/data`: Arquivos binários gerados para os testes.
* `/results`: Gráficos gerados e o CSV de resultados.
* `/docs`: Slides da apresentação e PDF com a dedução matemática dos cálculos.

---

## 👥 Autores
* **Ranier Veras**
* **Matheus Lima**
