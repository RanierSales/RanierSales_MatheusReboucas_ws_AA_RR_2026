# Guia de Contribuição: Experimento VerificaAlgo

Obrigado por seu interesse em colaborar com o experimento **VerificaAlgo**! Este projeto foca na análise empírica de complexidade de algoritmos (como o `verificaAlgo` e `linearSearch`) e na geração de dados estatísticos rigorosos.

Siga as etapas abaixo para colaborar com nossas análises.

## 🧾 O que está neste repositório?

* **`/src`**: Implementações dos algoritmos em C e scripts de automação.
* **`/data`**: Geradores de dados (Box-Muller) e instâncias de teste.
* **`/results`**: Scripts de plotagem (Python/Matplotlib) e registros de performance.
* **`/docs`**: Documentação teórica e slides sobre os resultados.

---

## 📌 Requisitos para contribuir

Antes de enviar contribuições, certifique-se de:

* Ter um compilador C (`gcc` ou `clang`) instalado.
* Ter Python 3.x e a biblioteca `pandas` e `matplotlib` para os scripts de análise.
* Compreender o fluxo de trabalho **Gitflow** (trabalhamos com branches de `feature/` e `hotfix/`).

---

## 🚀 Etapas para contribuir

1. **Faça um fork do repositório**
   * Clique em "Fork" no topo da página do projeto.

2. **Clone o seu fork**
   ```bash
   git clone https://github.com/RanierSales/RanierSales_MatheusReboucas_ws_AA_RR_2026.git
   cd RanierSales_MatheusReboucas_ws_AA_RR_2026
   ```

3. **Crie uma nova branch**
   Use o padrão do Gitflow para nomear sua branch:
   ```bash
   git checkout -b feature/melhoria-algoritmo-x
   ```

4. **Implemente suas alterações**
   * Se alterar algoritmos, certifique-se de manter a estrutura da `struct Metrics`.
   * Se alterar geradores de dados, garanta que a saída seja compatível com a leitura binária atual.
   * Mantenha o código limpo e comentado.

5. **Faça commit das suas alterações**
   Use commits semânticos:
   ```bash
   git add .
   git commit -m "feat: adiciona algoritmo de busca binária para comparação"
   ```

6. **Envie sua branch para o GitHub**
   ```bash
   git push origin feature/melhoria-algoritmo-x
   ```

7. **Abra um Pull Request**
   * Direcione o seu PR para a branch **`develop`** do repositório original.
   * Descreva os impactos na complexidade de tempo/espaço da sua alteração.

---

## ✅ Boas práticas

* **Não envie arquivos binários gigantes**: Certifique-se de que arquivos `.bin` ou `.csv` grandes não sejam commitados (use o `.gitignore`).
* **Estabilidade**: Antes de enviar, rode o experimento para garantir que não ocorram *segfaults* ou *memory leaks*.
* **Reprodutibilidade**: Se alterar o `plot_results.py`, verifique se ele ainda consegue ler os CSVs gerados pelo código C.

---

## 🛠 Sugestões de contribuição

* Implementação de novos algoritmos de busca para comparação.
* Otimização dos geradores de dados (performance na geração de entropia).
* Melhorias nos scripts de visualização (novos tipos de gráficos).
* Refatoração do código C para melhor portabilidade entre SOs.

---

## 📫 Dúvidas?

Abra uma [issue](https://github.com/RanierSales/RanierSales_MatheusReboucas_ws_AA_RR_2026/issues) para relatar comportamentos inesperados ou sugerir novos cenários de teste.

---

Agradecemos por colaborar com esta análise científica! 📊
