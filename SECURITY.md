# Política de Segurança: Experimento VerificaAlgo

## 🔐 Visão Geral

Este repositório contém experimentos de **Análise de Algoritmos (Complexidade de Tempo e Espaço)**. Embora o objetivo seja puramente acadêmico, levamos a sério a segurança na execução de scripts que manipulam memória e arquivos binários. Esta política descreve como tratamos vulnerabilidades que possam causar instabilidade no sistema do usuário.

---

## 🛡️ Escopo de Segurança

As seguintes situações são consideradas relevantes para a segurança deste experimento:

* **Buffer Overflows**: Vulnerabilidades na leitura de arquivos binários gerados ou na alocação dinâmica via `malloc`.
* **Corrupção de Arquivos**: Erros na geração de arquivos `.bin` (via Box-Muller) que possam causar leituras inválidas de memória.
* **Consumo de Recursos (DoS Local)**: Algoritmos com complexidade excessiva (ex: `verificaAlgo` com laços quadráticos/cúbicos) que não possuem travas de segurança para inputs gigantescos, podendo travar o sistema por consumo de CPU/RAM.
* **Manipulação de Entropia**: Uso inseguro ou bloqueante de `/dev/urandom` em sistemas que não o suportam.
* **Injeção em Relatórios**: Falhas na geração do CSV que permitam injeção de fórmulas (CSV Injection) se aberto em softwares de planilhas.

**Fora de escopo**:
* Bugs de lógica que não afetam a segurança do sistema.
* Erros de plotagem no script Python que não envolvam execução de código arbitrário.

---

## 🧑‍💻 Relatando Vulnerabilidades

Se você identificar um comportamento que coloque em risco o ambiente de execução:

1. **Não abra uma issue pública** imediatamente.
2. Envie um e-mail detalhado para o mantenedor: `mths.academics91@gmail.com`
3. No assunto, utilize: `[SECURITY VULNERABILITY] VerificaAlgo`.

Você receberá um feedback inicial em até **4 dias úteis**.

---

## 🔄 Processo de Mitigação

Seguiremos o rito de correção baseada no **Gitflow**:
1. Identificação do problema em ambiente isolado;
2. Criação de uma branch `hotfix/nome-da-vulnerabilidade`;
3. Correção e merge para `main` e `develop`;
4. Atualização imediata do `README.md` alertando os usuários sobre a versão vulnerável.

---

## 🔐 Recomendações de Execução Segura

Ao rodar este experimento em sua máquina:

* **Limites de N**: Tenha cautela ao aumentar os tamanhos de `n` no arquivo `verificaAlgo.c`, pois o crescimento da carga computacional pode causar aquecimento excessivo ou travamento do SO.
* **Revisão de Binários**: Não execute o script de experimento com arquivos `.bin` baixados de fontes não confiáveis; sempre gere seus próprios dados usando o `random_generator.c`.
* **Ambiente**: Recomendamos o uso de ambientes controlados (contêineres Docker ou VMs) para testes com grandes volumes de dados.

---

## 📄 Licença e Responsabilidade

Conforme definido na Licença MIT deste projeto, o software é fornecido "como está", sem garantias. O uso de técnicas que manipulam ponteiros em C exige revisão cuidadosa por parte do usuário.
