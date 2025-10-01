#include "ANSI-color-codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h> // SetConsoleOutputCP()
#include <math.h> // Required for round() and pow()
#include <time.h> // For time() function

// Heatmap de intencidade pluviométrica

int main() {
    //  Mostrar caracteres acentuados
    SetConsoleOutputCP( CP_UTF8 ); 

    // Three-Color Scale

    // Define Start, Midpoint and End Colors

    int r2 = 255, g2 = 0, b2 = 0; // red
    int r_mid = 255, g_mid = 165, b_mid = 0; // orange
    //int r_mid = 255, g_mid = 255, b_mid = 0; // yellow
    int r1 = 173, g1 = 216, b1 = 230; // light blue

    // int r1 = 255, g1 = 0, b1 = 0; // red
    // int r_mid = 255, g_mid = 165, b_mid = 0; // orange
    // int r2 = 0, g2 = 0, b2 = 255; // blue

    // int r1 = 156, g1 = 0, b1 = 6; // dark red
    // int r_mid = 255, g_mid = 235, b_mid = 235; // white/ light gray
    // int r2 = 255, g2 = 199, b2 = 206; // lighter red    

    // int r1 = 255, g1 = 0, b1 = 0; //  red
    // int r_mid = 128, g_mid = 128, b_mid = 128; // white/ gray
    // int r2 = 0, g2 = 0, b2 = 255; //  blue  


    // Matriz dias e bairros
    int intencidadeDiaBairro[7][10] = {0};

    // Inicia matriz com valores randomicos
    srand(time(NULL));

    int random_in_range = (rand() % 100) + 1;
    int maxValue = 0;
    printf("{\n");
    for (int i = 0; i < 7; i++){
        printf("{ ");
        for (int j = 0; j < 10; j++) {
            random_in_range = (rand() % 100) + 1;
            intencidadeDiaBairro[i][j] = random_in_range;
            if (random_in_range > maxValue)
                maxValue = random_in_range;                            
            printf("%3d%s ", intencidadeDiaBairro[i][j], (j == 9) ? "" : ",");
        }
        printf("}%s\n", (i == 6) ? "" : ",");    
    }
    printf("}\n");

    // Generate a random number between 1 and 100
    random_in_range = (rand() % 100) + 1;

    int r, g, b;
    float norm_val_lower, norm_val_upper;

    // Normalize Data
    float norm_val = 0.0;

    for (int i = 0; i < 7; i++){
        for (int j = 0; j < 10; j++) {
            // r = (int) r1 + (r2 - r1) * norm_val;
            // g = (int) g1 + (g2 - g1) * norm_val;
            // b = (int) b1 + (b2 - b1) * norm_val;        
            
            norm_val = (float) intencidadeDiaBairro[i][j] / maxValue;

            if (norm_val <= 0.5) {
                norm_val_lower = round(norm_val / 0.5 * 10) / 10;            
                r = (int) r1 + (r_mid - r1) * norm_val_lower;
                g = (int) g1 + (g_mid - g1) * norm_val_lower;
                b = (int) b1 + (b_mid - b1) * norm_val_lower;     
                printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm %5d \e[0m", r, g, b, r, g, b, intencidadeDiaBairro[i][j]);       
            } else {             
                norm_val_upper = round((norm_val - 0.5) * 10) / (0.5 * 10);
                r = (int) r_mid + (r2 - r_mid) * norm_val_upper;
                g = (int) g_mid + (g2 - g_mid) * norm_val_upper;
                b = (int) b_mid + (b2 - b_mid) * norm_val_upper;   
                printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm %5d \e[0m", r, g, b, r, g, b, intencidadeDiaBairro[i][j]);                 
            }
            
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm (%d, %d, %d) \e[0m", 1, 1, 1, r, g, b, r, g, b);
            //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%4d\e[0m", 1, 1, 1, r, g, b, "");                            
                  
        }
        printf("\n");
    }   


    // int count = 1;
    // for (float norm_val = 0.0; norm_val < 0.99; norm_val += 0.01) {
    //     // r = (int) r1 + (r2 - r1) * norm_val;
    //     // g = (int) g1 + (g2 - g1) * norm_val;
    //     // b = (int) b1 + (b2 - b1) * norm_val;        

    //     if (norm_val <= 0.5) {
    //         norm_val_lower = round(norm_val / 0.5 * 10) / 10;            
    //         r = (int) r1 + (r_mid - r1) * norm_val_lower;
    //         g = (int) g1 + (g_mid - g1) * norm_val_lower;
    //         b = (int) b1 + (b_mid - b1) * norm_val_lower;     
    //         printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%.2f\e[0m", 1, 1, 1, r, g, b, norm_val_lower);       
    //     } else {             
    //         norm_val_upper = round((norm_val - 0.5) * 10) / (0.5 * 10);
    //         r = (int) r_mid + (r2 - r_mid) * norm_val_upper;
    //         g = (int) g_mid + (g2 - g_mid) * norm_val_upper;
    //         b = (int) b_mid + (b2 - b_mid) * norm_val_upper;   
    //         printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%.2f\e[0m", 1, 1, 1, r, g, b, norm_val_upper);                 
    //     }
        
    //     //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm (%d, %d, %d) \e[0m", 1, 1, 1, r, g, b, r, g, b);
    //     //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%4d\e[0m", 1, 1, 1, r, g, b, "");
        
    //     if (count < 10) {
    //         count++;
    //     } else {
    //         count = 1;
    //         printf("\n");
    //     }        
    // }

    printf("\n");

    printf("0 [mm/m\u00B2] ");
    for (float norm_val = 0.0; norm_val < 0.9; norm_val += 0.05) {
        // r = (int) r1 + (r2 - r1) * norm_val;
        // g = (int) g1 + (g2 - g1) * norm_val;
        // b = (int) b1 + (b2 - b1) * norm_val;

        if (norm_val <= 0.5) {
            norm_val_lower = norm_val / 0.5;
            r = (int) r1 + (r_mid - r1) * norm_val_lower;
            g = (int) g1 + (g_mid - g1) * norm_val_lower;
            b = (int) b1 + (b_mid - b1) * norm_val_lower;            
        } else {             
            norm_val_upper = (norm_val - 0.5) / 0.5;
            r = (int) r_mid + (r2 - r_mid) * norm_val_upper;
            g = (int) g_mid + (g2 - g_mid) * norm_val_upper;
            b = (int) b_mid + (b2 - b_mid) * norm_val_upper;             
        }
        
        //printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm (%d, %d, %d) \e[0m", 1, 1, 1, r, g, b, r, g, b);
        printf("\e[0m\e[38;2;%d;%d;%dm\e[48;2;%d;%d;%dm%4s\e[0m", 1, 1, 1, r, g, b, "");
      
    }
    printf(" %d [mm/m\u00B2]", maxValue);

    // Define some 256-color codes (you can find full lists online)
    // int foreground_color_code = 57; // Pink
    // int background_color_code = 57;  // Light blue

    // Print text with custom foreground and background colors
    // printf("\033[38;5;%d;48;5;%dmHello, ANSI Colors!\033[0m\n", 
    //        foreground_color_code, background_color_code);
    // printf("\033[48;5;%dmHello, ANSI Colors!\033[0m\n", 
    //        background_color_code);

    return 0;

}

// int main(void)
// {
//     int row, col, n;

//     for (row = 0; row < 11; row++) {
//         for (col = 0; col < 10; col++) {
//             n = 10 * row + col;
//             if (n > 109) break;
//             printf("\033[%dm %3d \033[m", n, n);
//         }
//         printf("\n");
//     }
//     return 0;
// }


// run into prompt:
// $ prompt $G
// $ exemplo{number}.exe
// $ echo %errorlevel%