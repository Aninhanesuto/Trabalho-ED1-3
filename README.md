# Estrutura de Dados I – Trabalho Prático  
**Tema: Jogos Vorazes**

**Prazo para envio: 16/09/2024, 23:59 – via [AVA](https://ava.ufes.br)**

---

## 1. Descrição do Problema

Todos os anos, o Capitólio de Panem obriga os 12 distritos a enviarem dois tributos (um menino e uma menina) para os **Jogos Vorazes**. Este ano, cada tributo será colocado em **um labirinto separado**, com **um ou mais bestantes**.

- A arena terá **24 labirintos**, um para cada tributo.
- O tributo deve **escapar do labirinto** e alcançar **um quadrado limítrofe**, sem dividir um quadrado com um bestante.
- O tributo e os bestantes se movimentam **simultaneamente a cada rodada**.
- O programa deve simular a situação e verificar se a sobrevivência do tributo é possível.

### Entrada:
- Primeira linha: dois inteiros `n` e `m` (dimensões do labirinto), com `1 ≤ n, m ≤ 1000`
- Depois, `n` linhas com `m` caracteres:
  - `.` → chão
  - `#` → parede
  - `A` → tributo
  - `M` → bestante
- Há exatamente **um 'A'** na entrada.

### Saída:
- “**YES**” se o tributo puder escapar, seguido do número de passos e o caminho usando:
  - `L` = esquerda
  - `R` = direita
  - `U` = cima
  - `D` = baixo
- “**NO**” caso não haja escapatória.
