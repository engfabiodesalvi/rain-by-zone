# Rain by Zone

Projeto em **C** para registrar e visualizar dados de intensidade pluviométrica separados por bairros ou regiões ao longo dos dias.

## Tecnologias e conceitos utilizados

- **Linguagem C**
- Manipulação de arquivos (`fopen`, `fscanf`, `fprintf`, `fclose`)
- Estruturas condicionais (`if`, `else`)
- Estruturas de repetição (`for`, `while`)
- Estruturas de dados com `struct`
- Arrays para armazenamento de registros
- Ponteiros e passagem por referência
- Entrada e saída formatada (`printf`, `scanf`)
- Tratamento de strings (`strcpy`, `strcmp`, `strchr`)
- Códigos ANSI para cores no terminal (via `ANSI-color-codes.h`)

## Estrutura do projeto

- `rain_by_zone.c` → código-fonte principal
- `ANSI-color-codes.h` → cabeçalho auxiliar para saída colorida no terminal
- Arquivos de dados externos (ex: `dados_chuva.txt`)

## Compilação

```bash
gcc rain_by_zone.c -o rain_by_zone