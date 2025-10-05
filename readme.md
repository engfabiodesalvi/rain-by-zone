### [English version](#Versão-em-português)

# 🌧️ Rain by Zone

Projeto em **C** para registrar e analisar dados pluviométricos por bairro/região ao longo dos dias.  
O sistema permite tanto **registrar** novas intensidades de chuva quanto **visualizar** os dados em forma de **Heatmap** colorido no terminal.

---

## 🛠️ Tecnologias e Conceitos Utilizados

- 💻 **Linguagem C**
- 📂 Manipulação de arquivos (`fopen`, `fscanf`, `fprintf`, `fclose`)
- 🔀 Estruturas condicionais (`if`, `else`, `switch`)
- 🔁 Estruturas de repetição (`for`, `while`, `do-while`)
- 🧱 Estruturas de dados (`struct`)
- 📊 Matrizes bidimensionais (15 dias × 10 bairros)
- 📌 Ponteiros e passagem por referência
- ⌨️ Entrada e saída formatada (`printf`, `scanf`, `fgets`, `wprintf`)
- 🔤 Manipulação de strings (`strcpy`, `strcmp`, `strchr`, `wcscpy`, `wcslen`)
- 🌐 Suporte a UTF-8 e caracteres acentuados (`setlocale`, `wchar_t`)
- 🎲 Geração de números aleatórios (`rand`, `srand`, `time`)
- 🎨 Códigos ANSI RGB para cores no terminal
- 🪟 Funções específicas de Windows (`SetConsoleOutputCP`)
- 📝 Código modular, comentado e organizado

---

## 📂 Estrutura do Projeto

- 📜 `rain_by_zone.c` → código-fonte principal  
- 🎨 `ANSI-color-codes.h` → cabeçalho auxiliar para cores no terminal  
- 📄 `word/Atividade3_ChuvasPorBairro_FabioToledoBonemerDeSalvi.pdf` → relatório acadêmico  

---

## 🎓 Visão Acadêmica

- 🎯 **Objetivo**: armazenar e manipular dados pluviométricos em matriz (15 × 10) e exibir em Heatmap.  
- ✅ **Requisitos atendidos**: loops, condicionais, menu interativo, validação de entradas.  
- 🌈 **Visualização**: azul (baixo), laranja (médio), vermelho (alto).  
- ⚙️ **Funcionalidades**: registrar bairros, editar nomes, inserir dados, gerar dados aleatórios, exibir Heatmap.  
- 🖥️ **Ambiente**: VS Code + GCC (MinGW-w64) + Windows (UTF-8).  

---

## ⚙️ Compilação

```bash
gcc rain_by_zone.c -o rain_by_zone
```
---
### [Versão em português](#English-version)

# 🌧️ Rain by Zone

Project in **C** to register and analyze rainfall data by neighborhood/region over multiple days.  
The system allows both **registering** new rainfall intensities and **visualizing** them as a **Heatmap** in the terminal.

---

## 🛠️ Technologies and Concepts Used

- 💻 **C Language**
- 📂 File manipulation (`fopen`, `fscanf`, `fprintf`, `fclose`)
- 🔀 Conditional structures (`if`, `else`, `switch`)
- 🔁 Loop structures (`for`, `while`, `do-while`)
- 🧱 Data structures (`struct`)
- 📊 Two-dimensional matrices (15 days × 10 neighborhoods)
- 📌 Pointers and pass-by-reference
- ⌨️ Formatted input/output (`printf`, `scanf`, `fgets`, `wprintf`)
- 🔤 String handling (`strcpy`, `strcmp`, `strchr`, `wcscpy`, `wcslen`)
- 🌐 UTF-8 and accented character support (`setlocale`, `wchar_t`)
- 🎲 Random number generation (`rand`, `srand`, `time`)
- 🎨 ANSI RGB color codes for heatmap rendering
- 🪟 Windows-specific functions (`SetConsoleOutputCP`)
- 📝 Modular, well-commented, and organized code

---

## 📂 Project Structure

- 📜 `rain_by_zone.c` → main source code  
- 🎨 `ANSI-color-codes.h` → header file for terminal colors  
- 📄 `word/Atividade3_ChuvasPorBairro_FabioToledoBonemerDeSalvi.pdf` → academic report  

---

## 🎓 Academic Perspective

- 🎯 **Goal**: store and manipulate rainfall data in a 15 × 10 matrix and visualize it as a Heatmap.  
- ✅ **Requirements met**: loops, conditionals, interactive menu, input validation.  
- 🌈 **Visualization**: blue (low), orange (medium), red (high).  
- ⚙️ **Features**: register neighborhoods, rename them, insert data, generate random data, display Heatmap.  
- 🖥️ **Environment**: VS Code + GCC (MinGW-w64) + Windows (UTF-8).  

---

## ⚙️ Compilation

```bash
gcc rain_by_zone.c -o rain_by_zone
```