#include "ANSI-color-codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h> // SetConsoleOutputCP()
#include <math.h> // Required for round() and pow()
#include <time.h> // For time() function
#include <limits.h>
#include <float.h> // FLT_MAX
#include <locale.h>
#include <wchar.h>

// Three-Color Scale
// Define Start, Midpoint and End Colors
// Definindo a estrutura com as três cores bases do Heatmap
struct CoresHeatmap {
    int rgbBaixo[3]; // Cor do valor baixo
    int rgbMedio[3]; // Cor do valor médio
    int rgbAlto[3];  // Cor do valor alto
};

// Define estrutura com valores máximo e mínimo das medidades de intensidade de chuva
struct Limites {
    float valorMin;
    float valorMax;
};

// Define estrutura com os dados a serem impressos e com as configurações do gráfico
struct ConjuntoDados {
    // Valores máximo e mínimo das intensidades de chuva inseridas pelo usuario
    struct Limites limites;
    // Valores máximo e mínimo das intensidades de chuva dos valores aleatórios
    struct Limites limitesAleatorio;
    // Three-Color Scale
    // Escala de três cores
    // Variável com as três cores do Heatmap
    struct CoresHeatmap coresHeatmap;
    // Matriz nome dos bairros
    //char bairros[10][21];
    wchar_t bairros[10][21];
    // Matriz nome dos bairros padrão
    //char bairrosPadrao[10][21];    
    wchar_t bairrosPadrao[10][21];    
    // Matriz dados de intensidade de chuva por dia e bairro
    float medidaPluviometricaDiaBairro[15][10];
    // Matriz dados aleatórios de intensidade de chuva por dia e bairro
    float medidaPluviometricaDiaBairroAleatorio[15][10];
};

// Define estrutura com as opções de manipulacao do menu
struct Menu {
    // Definindo as variáveis de manipulação dos menus
    int menu;
    int returnMenu;
    int sairMenu;
    // Definindo as variáveis de manipulação das opções do menu    
    int opcao;
    int returnOpcao;
    // Faixa de opções do menu
    int opcaoMinMax[2]; 
    // Opção selecinada pelo usuário
    // Dados aleatorios - 1 / Dados inseridos pelo usuario - 2
    int tipoDado;
    // Bairro selecionado
    int bairro;
    // novo bairro
    //char novoBairro[21];
    wchar_t novoBairro[21];
    // Array para armazenar o retorno da função fgets() 
    // [Erro -> NULL | Success -> aponta para a variável utilizada como buffer]    
    char *returnNovoCaracteres;
    // Indice para determinar o dia durante entrada de dados de intensidade pluviométrica
    int indiceDia;
    // novo valor com máximo de 6 dígitos - o útimo caracter é o '\n'
    char novoValor[7];
    // numero de valores inseridos na variavel novoValor
    int returnNovoValor;
    // nova Intensidade pluviométrica
    float novaIntensidadePluviometrica;
};

// Protótipo das funções
void apresentacaoSistema();
void menuInicio();
void menuPrincipal();
void menuVisualizarIntensidadePluviometrica(struct Menu *menu, struct ConjuntoDados *conjuntoDados);
void menuRegistrarIntensidadePluviometrica(struct Menu *menu, struct ConjuntoDados *conjuntoDados);
void menuFim();
void defineCoresHeatmap(struct CoresHeatmap *coresHeatmap);
void inicializaMatriz(float medidaPluviometricaDiaBairro[15][10], struct Limites *limites);
void defineLimites(float medidaPluviometricaDiaBairro[15][10], struct Limites *limites);
//void imprimirHeatmap(char bairros[10][21], float medidaPluviometricaDiaBairro[15][10], struct Limites *limites, struct CoresHeatmap *coresHeatmap);
void imprimirHeatmap(wchar_t bairros[10][21], float medidaPluviometricaDiaBairro[15][10], struct Limites *limites, struct CoresHeatmap *coresHeatmap);
void mensagemEncerramento();
int validaOpcaoMenu(struct Menu *menu);
int validaEntradaNumerica(struct Menu *menu);
int validaEntradaCaracters(struct Menu *menu);

// Número máximo de dias
const int MAX_DIAS = 15;
// Número máximo de bairros
const int MAX_BAIRROS = 10;
// Número máximo de caracteres no nome do bairro
const int MAX_BAIRRO_CARACTERES = 21;

// Heatmap de intencidade pluviométrica

int main() {
    //  Mostrar caracteres acentuados
    //SetConsoleOutputCP( CP_UTF8 ); 
    
    // habilita UTF-8 no terminal
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8"); 
    // Set the locale for numeric formatting
    // setlocale(LC_NUMERIC, "C");

    // Declarando a estrutura de manipulação do menu
    struct Menu menu;

    // Definindo as variáveis de manipulação dos menus
    menu.menu = 0;
    menu.returnMenu = 0;
    menu.sairMenu = 0;

    // Definindo as variáveis de manipulação das opções do menu    
    menu.opcao = 0;
    menu.returnOpcao = 0;
    // Faixa de opções do menu
    menu.opcaoMinMax[0] = 0; 
    menu.opcaoMinMax[1] = 0; 

    // Declarando a estrutura do conjunto de dados
    // Inicializando os dados com valores nulos
    struct ConjuntoDados conjuntoDados = {0};

    // Definindo as cores de transição do Heatmap
    defineCoresHeatmap(&conjuntoDados.coresHeatmap);


    // Matriz dias e bairros
    // Matriz medidaPluviometricaBairro aleatoria
    // Definindo valores nulos
    // i - dias / j - bairros
    for (int i; i < MAX_DIAS; i++) {
        for (int j; j < MAX_BAIRROS; j++){
            conjuntoDados.medidaPluviometricaDiaBairro[i][j] = 0.0;
            conjuntoDados.medidaPluviometricaDiaBairroAleatorio[i][j] = 0.0;
        }
    }

    // Valores máximo e mínimo das intensidades de chuva inseridas pelo susuário
    conjuntoDados.limites.valorMin = 0;
    conjuntoDados.limites.valorMax = 0;

    // Valores máximo e mínimo das intensidades de chuva dos valores aleatórios
    conjuntoDados.limitesAleatorio.valorMin = 0;
    conjuntoDados.limitesAleatorio.valorMax = 0;

    // Matriz nome dos bairros
    //char bairros[10][21] = {
    //     "Bairro/Região  1", "Bairro/Região  2", "Bairro/Regiao  3", "Bairro/Região  4", "Bairro/Região  5",
    //     "Bairro/Região  6", "Bairro/Região  7", "Bairro/Região  8", "Bairro/Região  9", "Bairro/Região 10"
    // };

    // Largura lógica de caracteres
    wchar_t bairros[10][21] = {
        L"Bairro/Região  1", L"Bairro/Região  2", L"Bairro/Regiao  3", L"Bairro/Região  4", L"Bairro/Região  5",
        L"Bairro/Região  6", L"Bairro/Região  7", L"Bairro/Região  8", L"Bairro/Região  9", L"Bairro/Região 10"
    };


    // Definindo os nome iniciais para os bairros
    for (int i; i < MAX_BAIRROS; i++) {        
        //strcpy(conjuntoDados.bairros[i], bairros[i]);
        //strcpy(conjuntoDados.bairrosPadrao[i], bairros[i]);
        wcscpy(conjuntoDados.bairros[i], bairros[i]);
        wcscpy(conjuntoDados.bairrosPadrao[i], bairros[i]);
    }        

    // Mensagem inicial
    apresentacaoSistema();

    // Menu 0 - Menu principal
    menu.menu = 0;
    menu.sairMenu = 0;

    // Loop dos menus
    do {

        if (menu.menu == 0) {
            // Menu para a opção 0

            // Primeiro menu:
            // Menu principal - "Menu de serviços"
            // Loop que garente uma entrada numérica válida
            do {
                // Menu principal -> "Menu de serviços" 
                menuInicio();
                menuPrincipal();

                // Opção selecionada pelo usuario
                printf("Digite a opção desejada: ");
                menu.returnOpcao = scanf("%d", &menu.opcao);
                menuFim();

                // Opções do menu
                menu.opcaoMinMax[0] = 1;
                menu.opcaoMinMax[1] = 3;            
                
                // Limpando o buffer de entrada!!!!
                while(getchar() != '\n');

            } while (!validaOpcaoMenu(&menu));

            // Analisa a opção selecionada
            if (menu.opcao >= 1 && menu.opcao <= 2) {
                menu.menu = menu.opcao;
            } else {
                // Sair do programa
                menu.sairMenu = 1;
            }        
        } else if (menu.menu == 1) {
            // Menu 1 - Selecionar entre visualizar dados aleatórios ou visualizar dados registrados pelo usuário

            // Menu para a opção 1

            // Passos para chegar a este menu:
            // "Serviços disponíveis" -> "1 - Visualizar os registros da intensidade de chuva"

            // Loop que garante uma entrada numérica válida
            do {                                
                // Menu "Visualizar os registros da intensidade de chuva"
                // O usuário deve escolher entre visualizar os dados leatórios ou visualizar dados registrados pelo usuário
                menuInicio();
                menu.tipoDado = 0;
                menuVisualizarIntensidadePluviometrica(&menu, &conjuntoDados);

                // Opcao selecionada pelo usuario
                printf("Entre com a opção: ");                
                menu.returnOpcao = scanf("%d", &menu.opcao);
                menuFim();

                // Opções do menu
                menu.opcaoMinMax[0] = 1;
                menu.opcaoMinMax[1] = 3;

                // Limpando o buffer de entrada!!!!
                while(getchar() != '\n');

            // Valida a entrada numerica antes de prosseguir
            } while (!validaOpcaoMenu(&menu));                

            // Verifica qual opção de conjunto de dados foi escolhida
            if (menu.opcao >= 1 && menu.opcao <= 2) {
                    // Registros aleatórios - 1 / Registros inseridos pelo usuário - 2
                    menu.tipoDado = menu.opcao;
                    // Primeiro dígito (1) - "Visualizar os registros da intensidade de chuva"
                    // Segundo dígito (opcao) - Identifica se os dados são aleatórios ou são dados inseridos pelo usuário
                    menu.menu = menu.opcao + 10;
            } else {
                    // Opcao 3 - Voltar
                    // Volta para o menu principal
                    menu.menu = 0;
            }            
        } else if (menu.menu >= 11 && menu.menu <= 12) {
            // Visualizar dados aleatórios ou visualizar dados inseridos pelo usuário

            // Menu 11 e 12 para as opções 1 e 2

            // Passos para chegar a este menu:
            // "Serviços disponíveis" -> "1 - Visualizar os registros da intensidade de chuva"
            
            // "Selecione um conjunto de registros para visualizar:" -> "1 - Registros aleatórios
            // ou
            // "Selecione um conjunto de registros para visualizar:" -> "2 - Registros inseridos pelo usuário

            // Loop que garante uma entrada numérica válida
            do {                                
                // Menu 11 "Utilizando dados aleatórios"
                //ou
                // Menu 12 "Utilizando dados inseridos pelo usuário"

                // O usuário deve escolher entre visualizar os dados leatórios ou visualizar dados registrados pelo usuário
                menuInicio();
                menuVisualizarIntensidadePluviometrica(&menu, &conjuntoDados);

                // Opcao selecionada pelo usuario
                printf("Entre com a opção: ");                
                menu.returnOpcao = scanf("%d", &menu.opcao);
                menuFim();

                // Opções do menu
                menu.opcaoMinMax[0] = 1;
                menu.opcaoMinMax[1] = 1;

                // Limpando o buffer de entrada!!!!
                while(getchar() != '\n');

            // Valida a entrada numerica antes de prosseguir
            } while (!validaOpcaoMenu(&menu));                

            // Verifica qual opção de conjunto de dados foi escolhida
            if (menu.opcao == 1) {
                    // Opcao 1 - Voltar
                    // Volta para o menu anterior
                    menu.menu = 1;
            }      
        } else if (menu.menu == 2) {
            // Menu 2 - Selecionar uma categoria para editar o nome e inserir as
            // informações de intensidade de chuva

            // Menu para a opção 2
            // Passos para chegar a este menu:
            // "Serviços disponíveis" -> "2 - Registrar a intensidade pluviométrica"
            // "Selecione um bairro para inserir os dados:" -> "1 - Bairro 1" ao "10 - Bairro 10"

            // Loop que garante uma entrada numérica válida
            do {                                
                // Menu "Registrar a intensidade pluviométrica"
                // O usuário deve escolher um bairro para adicinar os dados de intensidade pluviométrica
                menuInicio();
                menu.bairro = 0;
                menuRegistrarIntensidadePluviometrica(&menu, &conjuntoDados);

                // Opção selecionada pelo usuario
                printf("Entre com a opção: ");                
                menu.returnOpcao = scanf("%d", &menu.opcao);
                menuFim();

                // Opções do menu
                menu.opcaoMinMax[0] = 1;
                menu.opcaoMinMax[1] = MAX_BAIRROS + 1;

                // Limpando o buffer de entrada!!!!
                while(getchar() != '\n');

            // Valida a entrada numerica antes de prosseguir
            } while (!validaOpcaoMenu(&menu));                

            // Verifica qual opção de conjunto de dados foi escolhida
            if (menu.opcao >= 1 && menu.opcao <= MAX_BAIRROS) {
                    // Bairro 1 - [1] / Bairro MAX_BAIRROS - [MAX_BAIRROS]
                    menu.bairro = menu.opcao;
                    // Primeiro dígito (2) - "Registrar a intensidade pluviométrica"
                    // Segundo dígito (opcao) - Número do bairro selecionado
                    menu.menu = menu.opcao + 200;
            } else {
                    // Opcao 11 - Voltar
                    // Volta para o menu principal
                    menu.menu = 0;
            }        

        } else if (menu.menu >= 201 && menu.menu <=210){
            // Menu para editar o nome da categoria
            // Menus 201 a 210
            // Opções 1 a 10

            // Menu para as opções 1 a 10
            // Passos para chegar a este menu:
            // "Serviços disponíveis" -> "2 - Registrar a intensidade pluviométrica"
            // "Selecione um bairro para inserir os dados:" -> "1 - Bairro 1" ao "10 - Bairro 10"                

            // Menu "Editar nome do bairro"  

            menuInicio();
            menuRegistrarIntensidadePluviometrica(&menu, & conjuntoDados);
            printf("Digite um novo nome para o bairro/região ou tecle \"Enter\": ");

            // Nome do bairro digitado
            // A função fgets foi utilizada para obter strings com espaços.
            //menu.returnNovoCaracteres = fgets(menu.novoBairro, 21, stdin);

            // Verifica se fgets() leu todos os caracteres da entrada
            // Se retornar NULL significa que ainda restam caracteres a serem lidos
            if (fgetws(menu.novoBairro, 21, stdin) != NULL) {            
                // Verifica se o carater de fim de linha foi lido
                //  retorno NULL da função strchr() significa que o caracter não esta presente no vetor
                if (wcschr(menu.novoBairro, '\n') == NULL ) {
                    // Termina de ler os caracters não lidos!
                    // Um valor igual a EOF significa que o fim do buffer foi alcançado.
                    char c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
            }

            menuFim();

            // Eliminando '\n' da string
            //menu.novoBairro[strcspn(menu.novoBairro, "\n")] = 0;

            size_t len = wcslen(menu.novoBairro);
            if (len > 0 && menu.novoBairro[len - 1] == L'\n') menu.novoBairro[len - 1] = L'\0';
            
            // Verifica se a entrada de caracteres é válida  

            // Verifica se foi digitado o nome de um novo bairro
            if (wcslen(menu.novoBairro) > 0) {
                // Renomeia o bairro
                wcscpy(conjuntoDados.bairros[menu.bairro-1], menu.novoBairro);
                // Imprime uma mensagem confirmando os dados modificados
                printf("\n -> Bairro/região renomeado(a)!\n");
                wprintf(L" [Novo nome para o bairro/região: %ls]\n", conjuntoDados.bairros[menu.bairro - 1]);                
            }
            // Ir para o menu para inserir os dados de intensidade pluviométrica
            // Inicia a captura de dados pelo dia 1
            menu.indiceDia = 1;
            menu.menu = menu.menu * 100 + menu.indiceDia;                          

        } else if (menu.menu >= 20101 && menu.menu <= 21016) {
            // Menu para inserir as informações de intensidade de chuva medidas em mm/h
            // Menus 201.01 a 210.16
            // Opções 1 a 15

            // Menu para os dias 1 a 15
            // Menu para a opção 16 -> menu com a opção voltar
            // Passos para chegar a este menu:
            // "Serviços disponíveis" -> "2 - Registrar a intensidade pluviométrica"
            // "Selecione um bairro para inserir os dados:" -> "1 - Bairro 1" ao "10 - Bairro 10"         
            // "Inserir dados diários de intensidade de chuva" -> "Dia 1" a "Dia 15"      
            
            do {
                // Menu "Inserir dados de intensidade pluviometrica"  

                menuInicio();
                menuRegistrarIntensidadePluviometrica(&menu, & conjuntoDados);

                if (menu.indiceDia <= MAX_DIAS) {
                    printf("Digite um novo valor em [mm/h] ou tecle \"Enter\" : ");
                    
                    // Limpa a variável novoValor
                    strcpy(menu.novoValor, "");
                    // Define como valor padrão o valor atual                    
                    menu.novaIntensidadePluviometrica = conjuntoDados.medidaPluviometricaDiaBairro[menu.indiceDia-1][menu.bairro - 1]; 

                    // A função fgets foi utilizada para obter strings com espaços.   

                    // Verifica se fgets() leu todos os caracteres da entrada
                    // Se retornar NULL significa que ainda restam caracteres a serem lidos                   
                    if (fgets(menu.novoValor, 7, stdin) != NULL) {            
                        // Verifica se o carater de fim de linha foi lido
                        //  retorno NULL da função strchr() significa que o caracter não esta presente no vetor
                        if (strchr(menu.novoValor, '\n') == NULL ) {
                            // Termina de ler os caracters não lidos!
                            // Um valor igual a EOF significa que o fim do buffer foi alcançado.
                            char c;
                            while ((c = getchar()) != '\n' && c != EOF);
                        }
                    }
            
                } else {
                    // Opção selecionada pelo usuario
                    printf("Entre com a opção: ");                
                    menu.returnOpcao = scanf("%d", &menu.opcao);

                    // Opções do menu
                    menu.opcaoMinMax[0] = 1;
                    menu.opcaoMinMax[1] = 1;                    
                }

                menuFim();

            // Valida a opcao do menu apenas se os valores de intensidade de chuva de todos os dias tiverem sido atualizados
            } while (
                (!validaOpcaoMenu(&menu) && (menu.indiceDia > MAX_DIAS)) ||
                (!validaEntradaNumerica(&menu) && (menu.indiceDia <= MAX_DIAS))
            );  

            // if (menu.indiceDia <= MAX_DIAS) {

            // }

            // Verifica o indice do dia
            if (menu.indiceDia >= 1 && menu.indiceDia <= MAX_DIAS) {
                // // Define como valor padrão o valor atual
                // menu.novaIntensidadePluviometrica = conjuntoDados.medidaPluviometricaDiaBairro[menu.indiceDia-1][menu.bairro - 1];

                if (menu.returnNovoValor)
                    conjuntoDados.medidaPluviometricaDiaBairro[menu.indiceDia-1][menu.bairro - 1] = menu.novaIntensidadePluviometrica;
                
                // Aponta para o menu do próximo dia
                menu.indiceDia++;                
                menu.menu = (menu.bairro + 200) * 100 + menu.indiceDia; 
            } else {
                // Opcao voltar
                // Menu de seleção de bairros
                menu.menu = 2;
            }                                     
        } else {
            // Menu principal
            menu.menu = 0;
        } 

    // Sair - sairMenu igual a 1 encerra o sistema! 
    } while (!menu.sairMenu);

    mensagemEncerramento();

    return 0;
}

void apresentacaoSistema() {
    // Apresnetação do sistema
    printf("\n");
    printf("####################################################################\n");
    printf("###### Sistema de Registro de Intensidade Pluviométrica v1.0 #######\n");
    printf("####################################################################\n");
    printf("* Sobre:\n");
    printf("-> Desenvolvido por Fabio Toledo Bonemer De Salvi\n");
    printf("\n");
    printf("* Visualize os registros de intensidade pluviométrica!\n");
    printf("-> Os registros são apresentados em um gráfico comparando os\n");
    printf("  bairros, ou regiões, ao longo dos dias!\n");
    printf("-> As intensidade pluviométricas são apresentadadas por meio de um\n");
    printf("  gráfico de intensidade de cores no estilo \"Heatmap\"!\n");
    printf("-> Os menores valores são representados pela cor azul, os valores\n");
    printf("  médios pela cor laranja e os valores maiores pela cor vermelha!\n");
    printf("\n");
    printf("* Registre os dados da intensidade pluviométrica!\n");
    printf("-> Entre com o nome do bairro e com os valores da intensidade\n");
    printf("  pluviométrica!\n");
    printf("-> Limitado a 10 bairros e a 15 dias de dados por bairro!\n");   
    printf("####################################################################\n"); 
}

void menuInicio() {
    printf("\n");
    printf("####################################################################\n");
    printf("###### Sistema de Registro de Intensidade Pluviométrica v1.0 #######\n");
    printf("####################################################################\n");
}

void menuPrincipal() {
    // Menu 0 - Menu principal
    // Menu inicial    
    printf("\n");
    printf(">> Serviços disponíveis:\n");
    printf("1 - Visualizar os registros de intensidade pluviométrica\n");
    printf("2 - Registrar uma intensidade pluviométrica\n");            
    printf("3 - Sair\n");    
}

void menuVisualizarIntensidadePluviometrica(struct Menu *menu, struct ConjuntoDados *conjuntoDados) {
    switch(menu->menu) {
        case 11:
            // Menu 11 - Menu Visualizar os registros da intensidade pluviométrica com dados aleatórios       
            printf("======= Visualizar os registros da intensidade pluviométrica =======\n\n");
            printf(">> Gráfico \"Heatmap\" para os dados aleatórios:\n\n");
          
            // Inicializar dados aleatórios de intensidade pluviométrica na matriz
            inicializaMatriz(
                conjuntoDados->medidaPluviometricaDiaBairroAleatorio, 
                &conjuntoDados->limitesAleatorio);

            // Imprimir os valores aleatrios da matriz da intensidade pluviométrica no estilo Heatmap
            imprimirHeatmap(
                conjuntoDados->bairrosPadrao, 
                conjuntoDados->medidaPluviometricaDiaBairroAleatorio, 
                &conjuntoDados->limitesAleatorio, 
                &conjuntoDados->coresHeatmap
            );

            printf("\n1 - Voltar\n");         
            break;

        case 12:
            // Menu 12 - Menu Visualizar os registros da intensidade pluviométrica com dados inseridos pelo usuário       
            printf("======= Visualizar os registros da intensidade pluviométrica =======\n\n");
            printf(">> Gráfico \"Heatmap\" para os dados inseridos pelo usuário:\n\n");

            // Imprimir os valores inseridos pelo usuário na matriz de intensidade pluviométrica no estilo Heatmap
            imprimirHeatmap(
                conjuntoDados->bairros, 
                conjuntoDados->medidaPluviometricaDiaBairro, 
                &conjuntoDados->limites, 
                &conjuntoDados->coresHeatmap
            );

            printf("\n1 - Voltar\n");         
            break;        

        case 1:
        default:
            // Menu 1 - Menu Visualizar os registros da intensidade pluviométrica       
            printf("======= Visualizar os registros da intensidade pluviométrica =======\n\n");
            printf(">> Selecione um conjunto de registros para visualizar:\n");
            printf("1 - Registros aleatórios\n");
            printf("2 - Registros inseridos pelo usuário\n");            
            printf("3 - Voltar\n");    
            break;
    }

}

void menuRegistrarIntensidadePluviometrica(struct Menu *menu, struct ConjuntoDados *conjuntoDados) {

    if(menu->menu >= 201 && menu->menu <= 210) {

        // Menu 201 a 210 - Menu 
        printf("=============== Registrar a intensidade pluviométrica ==============\n\n");
        // Imprime o bairro selecinado
        wprintf(L">> Bairro/região selecionado(a): %ls\n", conjuntoDados->bairros[menu->bairro-1]);  

    }else if(menu->menu >= 20101 && menu->menu <= 21016) {

        // Menu 20101 a 21015 - Menu 
        printf("=============== Registrar a intensidade pluviométrica ==============\n\n");
        // Imprime o bairro selecinado
        wprintf(L">> Bairro/região selecionado(a): %ls\n", conjuntoDados->bairros[menu->bairro-1]); 
        printf(">> Registros de intensidade pluviométrica:\n") ;
        // Imprime os dias
        printf("  %-5s", "Dia");
        for(int i = 0; i < MAX_DIAS; i++)
            printf("| %4d |", i + 1);
        printf("\n");
        // Imprime os dados de intensidade pluviométrica
        printf("  %-5s", "mm/h");
        for(int i = 0; i < MAX_DIAS; i++)
            printf("|%6.1f|", conjuntoDados->medidaPluviometricaDiaBairro[i][menu->bairro-1]);
        printf("\n\n");
        // Verifica se o indiceDia é menor que o numero total de dias
        if (menu->indiceDia <= MAX_DIAS) {
            printf(">> Dia: %d de %d.\n>> Intensidade pluviométrica: %6.1f [mm/h]\n",
                menu->indiceDia,
                MAX_DIAS,
                conjuntoDados->medidaPluviometricaDiaBairro[menu->indiceDia - 1][menu->bairro-1]
            );
        } else {
            printf(">> Selecione uma opção:\n");
            printf("1 - Voltar\n");
        }

    } else {

        // Menu 2 - Menu Registrar a intensidade pluviométrica       
        printf("=============== Registrar a intensidade pluviométrica ==============\n\n");
        printf(">> Selecione um bairro/região para inserir os dados:\n");            
        for (int indiceBairro = 0; indiceBairro < MAX_BAIRROS; indiceBairro++) {
            wprintf(L"%2d - %ls\n", indiceBairro + 1, conjuntoDados->bairros[indiceBairro]);
        }          
        printf("11 - Voltar\n");  

    }
}

void menuFim() {
    printf("####################################################################\n");
}

void mensagemEncerramento() {
    // Mensagem de encerramento
    printf("\n");
    printf("####################################################################\n");
    printf("###### Sistema de Registro de Intensidade Pluviometrica  v1.0 ######\n");
    printf("####################################################################\n");
    printf("Obrigado por utilizar nosso sistema!\n\n");  
    printf("Volte sempre!\n");  
    printf("####################################################################\n");    
}

// Define as cores de transição do Heatmap
void defineCoresHeatmap(struct CoresHeatmap *coresHeatmap) {
    // Definindo as cores de transição do HeatMap
    // light blue
    coresHeatmap->rgbBaixo[0] = 173;
    coresHeatmap->rgbBaixo[1] = 216; 
    coresHeatmap->rgbBaixo[2] = 230; 

    // orange
    coresHeatmap->rgbMedio[0] = 255;
    coresHeatmap->rgbMedio[1] = 165;
    coresHeatmap->rgbMedio[2] = 0;

    // yellow
    // coresHeatmap->rgbMedio[0] = 255;
    // coresHeatmap->rgbMedio[1] = 255;
    // coresHeatmap->rgbMedio[2] = 0;    
    
    // red
    coresHeatmap->rgbAlto[0] = 255;
    coresHeatmap->rgbAlto[1] = 0;
    coresHeatmap->rgbAlto[2] = 0;
}

// Inicializa a matriz com valores aleatório de intensidade de chuva 
void inicializaMatriz(float medidaPluviometricaDiaBairro[15][10], struct Limites *limites) {
    // Inicia matriz com valores randomicos
    srand(time(NULL));

    // Define a variável que receberá os valores aleatórios dentro do laço de repetição
    float random_in_range;

    // Define o valor máximo com um valor mínimo
    limites->valorMax = 0.0;
    // Define o valor mínimo com um valór máximo
    limites->valorMin = FLT_MAX;

    //printf("{\n");
    for (int j = 0; j < MAX_BAIRROS; j++) {    
        //printf("{ ");
        for (int i = 0; i < MAX_DIAS; i++){
            // Generate a random number between 1 and 100
            random_in_range =  (float) ((rand() % 1000) + 1) / 10.0;
            medidaPluviometricaDiaBairro[i][j] = random_in_range;
            if (random_in_range > limites->valorMax)
                limites->valorMax = random_in_range;   
            if (random_in_range < limites->valorMin)
                limites->valorMin = random_in_range;                                            
            //printf("%3d%s ", medidaPluviometricaDiaBairro[i][j], (i == MAX_DIAS - 1) ? "" : ",");
        }
        //printf("}%s\n", (j == MAX_BAIRROS - 1) ? "" : ",");    
    }
    //printf("}\n");
}

void defineLimites(float medidaPluviometricaDiaBairro[15][10], struct Limites *limites) {
    // Inicia matriz com valores randomicos
    srand(time(NULL));

    // Define a variável que receberá os valores aleatórios dentro do laço de repetição
    float medidaIntensidadePluviometrica;

    // Define o valor máximo com um valor mínimo
    limites->valorMax = 0.0;
    // Define o valor mínimo com um valór máximo
    limites->valorMin = FLT_MAX;

    //printf("{\n");
    for (int j = 0; j < MAX_BAIRROS; j++) {    
        //printf("{ ");
        for (int i = 0; i < MAX_DIAS; i++){
            medidaIntensidadePluviometrica = medidaPluviometricaDiaBairro[i][j];
            if (medidaIntensidadePluviometrica > limites->valorMax)
                limites->valorMax = medidaIntensidadePluviometrica;   
            if (medidaIntensidadePluviometrica < limites->valorMin)
                limites->valorMin = medidaIntensidadePluviometrica;                                            
            //printf("%3d%s ", medidaPluviometricaDiaBairro[i][j], (i == MAX_DIAS - 1) ? "" : ",");
        }
        //printf("}%s\n", (j == MAX_BAIRROS - 1) ? "" : ",");    
    }
    //printf("}\n");
}

void imprimirHeatmap(wchar_t bairros[10][21], float medidaPluviometricaDiaBairro[15][10], struct Limites *limites, struct CoresHeatmap *coresHeatmap) {
    
    // Cor final do Heatmap
    int rgbItem[3];
    int rgbTexto[3] = {0, 0, 0};
    
    // Para os dados normalizados calculados dentro do laço
    float norm_val = 0.0;
    // Limite inferior normalizado
    float norm_val_lower;
    // Limite superior normalizado
    float norm_val_upper;    

    // Determina os limites dos valores de intensidade de chuva
    defineLimites(medidaPluviometricaDiaBairro, limites);

    // Imprime os valores do gráfico Heatmap
    // Laço que percorre os bairros
    for (int i = 0; i < MAX_BAIRROS; i++){        
        // Imprime o nome do bairo na referida linha de dados
        wprintf(L"%-20ls-", bairros[i]);
        // Laço que percorre os dias
        for (int j = 0; j < MAX_DIAS; j++) {
            // Imprime dados utilizando a escala de duas cores
            // rgbItem[0] = (int) coresHeatmap->rgbBaixo[0] + (coresHeatmap->rgbAlto[0] - coresHeatmap->rgbBaixo[0]) * norm_val;
            // rgbItem[1] = (int) coresHeatmap->rgbBaixo[1] + (coresHeatmap->rgbAlto[1] - coresHeatmap->rgbBaixo[1]) * norm_val;
            // rgbItem[2] = (int) coresHeatmap->rgbBaixo[2] + (coresHeatmap->rgbAlto[2] - coresHeatmap->rgbBaixo[2]) * norm_val;                                
            
            // Verifica a diferença entre o limite maximo e  limite mínimo
            if (limites->valorMax - limites->valorMin) {
                // Fórmula básica para normalizar os dados entre o menor e  maior
                norm_val = (float) (medidaPluviometricaDiaBairro[j][i] - limites->valorMin) / (limites->valorMax - limites->valorMin);
                
                // Garante que os valores normalizados estejam entre 0.0 e 1.0
                if (norm_val < 0)
                    norm_val = 0;
                else if (norm_val > 1)
                    norm_val = 1;

            } else {
                norm_val = 0.0;
            }


            // Imprime os dados considerando uma transição entre três cores
            // Seleciona entre a metade inferior ou supeior para realizar a transição de cores
            // A cor supeior equivale ao valor 1
            // A cor central equivale ao valor 0.5
            // A cor inferior equivale a valor 0                
            if (norm_val <= 0.5) {
                // Transição entre as cores rgbBaixo e rgbMedio
                // Renormaliza o valor para estar entre 0.0 e 1.0 com um décimo de presição 
                norm_val_lower = round(norm_val / 0.5 * 10) / 10;            
                rgbItem[0] = (int) coresHeatmap->rgbBaixo[0] + (coresHeatmap->rgbMedio[0] - coresHeatmap->rgbBaixo[0]) * norm_val_lower;
                rgbItem[1] = (int) coresHeatmap->rgbBaixo[1] + (coresHeatmap->rgbMedio[1] - coresHeatmap->rgbBaixo[1]) * norm_val_lower;
                rgbItem[2] = (int) coresHeatmap->rgbBaixo[2] + (coresHeatmap->rgbMedio[2] - coresHeatmap->rgbBaixo[2]) * norm_val_lower;    

                // Imprime os valores de intensidade de chuva que correspondem às cores da metade inferior  
                printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%6.1f \e[0m",
                    rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], medidaPluviometricaDiaBairro[j][i]);  
                // Imprime os valores normalizados que correspondem às cores da metade inferior      
                //  printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%6.2f \e[0m",
                //     rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], norm_val_lower);                   
            } else {       
                // Transição entre as cores rgbMedio e rgbAlta       
                // Renormaliza o valor para estar entre 0.0 e 1.0 com um décimo de presição            
                norm_val_upper = round((norm_val - 0.5) * 10) / (0.5 * 10);
                rgbItem[0] = (int) coresHeatmap->rgbMedio[0] + (coresHeatmap->rgbAlto[0] - coresHeatmap->rgbMedio[0]) * norm_val_upper;
                rgbItem[1] = (int) coresHeatmap->rgbMedio[1] + (coresHeatmap->rgbAlto[1] - coresHeatmap->rgbMedio[1]) * norm_val_upper;
                rgbItem[2] = (int) coresHeatmap->rgbMedio[2] + (coresHeatmap->rgbAlto[2] - coresHeatmap->rgbMedio[2]) * norm_val_upper;
                // Imprime os valores de intensidade de chuva que correspondem às cores da metade superior    
                printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%6.1f \e[0m",
                    rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], medidaPluviometricaDiaBairro[j][i]);         
                // Imprime os valores normalizados que correspondem às cores da metade superior 
                // printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%6.2f \e[0m",
                //     rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], norm_val_upper);        
            }
            
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm (%d, %d, %d) \e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2]);
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%4d\e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], "");                            
                  
        }
        printf("\n");        
    }   

    // Imprime a linha referente aos dias
    printf("%-20s-", "Dia      ");
    for(int i = 0; i < MAX_DIAS; i++)
        printf("| %3d |", i + 1);
    
    printf("\n\n");

    // Imprime a barra de cores e os limites da escala
    // Imprime o valor inferior da escala de cores
    printf(" %.1f [mm/h] ", limites->valorMin);
    // printf(" %.1f [mm/m\u00B2] ", limites->valorMin);
    for (float norm_val = 0.0; norm_val < 1.0; norm_val += 0.05) {
        // Imprime os dados para a transição entre duas cores
        // rgbItem[0] = (int) coresHeatmap->rgbBaixo[0] + (coresHeatmap->rgbAlto[0] - coresHeatmap->rgbBaixo[0]) * norm_val;
        // rgbItem[1] = (int) coresHeatmap->rgbBaixo[1] + (coresHeatmap->rgbAlto[1] - coresHeatmap->rgbBaixo[1]) * norm_val;
        // rgbItem[2] = (int) coresHeatmap->rgbBaixo[2] + (coresHeatmap->rgbAlto[2] - coresHeatmap->rgbBaixo[2]) * norm_val;

        // Imprime os dados considerando uma transição entre três cores
        // Seleciona entre a metade inferior ou supeior para realizar a transição de cores
        // A cor supeior equivale ao valor 1
        // A cor central equivale ao valor 0.5
        // A cor inferior equivale a valor 0
        if (norm_val <= 0.5 || !(limites->valorMax - limites->valorMin)) {
            // Transição entre as cores rgbBaixo e rgbMedio
            // Verifica a deferença entre o limite máximo é mair do que limite mínimo
            if (limites->valorMax - limites->valorMin) {
                // Renormaliza o valor para estar entre 0.0 e 1.0 com um décimo de presição
                norm_val_lower = round(norm_val * 10) / (0.5 * 10);                
            } else {
                norm_val_lower = 0.0;
            }
            rgbItem[0] = (int) coresHeatmap->rgbBaixo[0] + (coresHeatmap->rgbMedio[0] - coresHeatmap->rgbBaixo[0]) * norm_val_lower;
            rgbItem[1] = (int) coresHeatmap->rgbBaixo[1] + (coresHeatmap->rgbMedio[1] - coresHeatmap->rgbBaixo[1]) * norm_val_lower;
            rgbItem[2] = (int) coresHeatmap->rgbBaixo[2] + (coresHeatmap->rgbMedio[2] - coresHeatmap->rgbBaixo[2]) * norm_val_lower;  
            // Imprime os valores normalizados que correspondem às cores da metade inferior 
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm% 4.2f \e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], norm_val_lower);
        } else {      
            // Transição entre as cores rgbMedio e rgbAlta    
            // Verifica a deferença entre o limite máximo é mair do que limite mínimo
            if (limites->valorMax - limites->valorMin) {
                // Renormaliza o valor para estar entre 0.0 e 1.0 com um décimo de presição   
                norm_val_upper = round((norm_val - 0.5)*10) / (0.5 * 10);
            } else {            
                norm_val_lower = 0.0;                
            }
            rgbItem[0] = (int) coresHeatmap->rgbMedio[0] + (coresHeatmap->rgbAlto[0] - coresHeatmap->rgbMedio[0]) * norm_val_upper;
            rgbItem[1] = (int) coresHeatmap->rgbMedio[1] + (coresHeatmap->rgbAlto[1] - coresHeatmap->rgbMedio[1]) * norm_val_upper;
            rgbItem[2] = (int) coresHeatmap->rgbMedio[2] + (coresHeatmap->rgbAlto[2] - coresHeatmap->rgbMedio[2]) * norm_val_upper;       
            // Imprime os valores normalizados que correspondem às cores da metade superior 
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm% 4.2f \e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], norm_val_upper);
        }
        
        // Imprime a cor RGB
        //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm (%d, %d, %d) \e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], rgbItem[0], rgbItem[1], rgbItem[2]);

        // Imprime espaços em branco com cor de fundo        
        printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%4s\e[0m", rgbTexto[0], rgbTexto[1], rgbTexto[2], rgbItem[0], rgbItem[1], rgbItem[2], "");
      
    }
    // Imprime  valor superior da escala de cores
    printf(" %.1f [mm/h]\n", limites->valorMax);
    // printf(" %.1f [mm/m\u00B2]\n", limites->valorMax);

}

int validaOpcaoMenu(struct Menu *menu) {
    // Verifica se apenas um valor inteiro foi digitado
    if (menu->returnOpcao != 1) {
        printf("\nValor inválido!\n");
        return 0; // Entrada inválida
    }
    
    // Verifica se a opção digitada esta disponível no menu
    if (menu->opcao < menu->opcaoMinMax[0] || menu->opcao > menu->opcaoMinMax[1]) {
        printf("\nOpção inválida!\n");
        return 0; // Opção inválida
    }                

    return 1; // Entrada numérica Ok    
}

int validaEntradaNumerica(struct Menu *menu) {
        
    
    if (menu->menu >= 20101 && menu->menu <= 21015) {
        // Extrai o valor de intensidade pluviometrica da variável novoValor
        // e armazena na variável novaIntensidadePluviometrica
        menu->returnNovoValor = sscanf(
            menu->novoValor,
            "%f", &menu->novaIntensidadePluviometrica
        );         
        if (menu->returnNovoValor) {
            if (menu->novaIntensidadePluviometrica < 0.0 || menu->novaIntensidadePluviometrica > 10000) {
                printf("\nValor %6.1f inválido! Digite um valor entre 0,0 e 9999,9!\n", menu->novaIntensidadePluviometrica);
                return 0; // Entrada inválida
            }   
        } else {
            printf("\nUtilizar valor padrão!\n");
            return 2; // Utilizar Valor Padrão
        }
    }  else {
        // Verifica se apenas um valor inteiro foi digitado
        if (menu->returnNovoValor != 1) {     
            printf("\nValor inválido!\n");
            return 0; // Entrada inválida
        }  
    }      

    return 1; // Entrada numérica Ok    
}

int validaEntradaCaracters(struct Menu *menu) {
 
    // Verifica se huve problemas ao ler a entrada de caracteres
    if (menu->returnNovoCaracteres == NULL) {
        printf("\nEntrada inválida!\n");
        return 0; // Entrada inválida
    }             

    return 1; // Entrada caracteres Ok    

}
// run into prompt:
// $ prompt $G
// $ exemplo{number}.exe
// $ echo %errorlevel%