#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else  //In any other OS
#define CLEAR "clear"
#endif

void pausar(void);
void limpar(void);
int verificarFim(int *ponteiro);
int verificarJogada(int *ponteiro, int movimento[2]);
void escolha01(int *ponteiro, char *nome1, char *nome2);
void escolha02(void);
void printarTabuleiro(int *ponteiro);
void limparTabuleiro(int *ponteiro);
int main(void);

void pausar(void) {
    char pause;

    fflush(stdin);
    printf("\n\nAperte qualquer tecla pra continuar...");
    scanf("%c", &pause);
    fflush(stdin);
}

void limpar(void) {
    system(CLEAR);
}

int verificarFim(int *ponteiro) {
    int i = 0, velha = 0;

    if ((ponteiro[0] == 1 && ponteiro[1] == 1 && ponteiro[2] == 1) ||
        (ponteiro[6] == 1 && ponteiro[7] == 1 && ponteiro[8] == 1) ||
        (ponteiro[2] == 1 && ponteiro[5] == 1 && ponteiro[8] == 1) ||
        (ponteiro[0] == 1 && ponteiro[3] == 1 && ponteiro[6] == 1) ||
        (ponteiro[0] == 1 && ponteiro[4] == 1 && ponteiro[8] == 1) ||
        (ponteiro[2] == 1 && ponteiro[4] == 1 && ponteiro[6] == 1) ||
        (ponteiro[3] == 1 && ponteiro[4] == 1 && ponteiro[5] == 1) ||
        (ponteiro[1] == 1 && ponteiro[4] == 1 && ponteiro[7] == 1)) {
        return 1;
    } else if ((ponteiro[0] == 2 && ponteiro[1] == 2 && ponteiro[2] == 2) ||
               (ponteiro[6] == 2 && ponteiro[7] == 2 && ponteiro[8] == 2) ||
               (ponteiro[2] == 2 && ponteiro[5] == 2 && ponteiro[8] == 2) ||
               (ponteiro[0] == 2 && ponteiro[3] == 2 && ponteiro[6] == 2) ||
               (ponteiro[0] == 2 && ponteiro[4] == 2 && ponteiro[8] == 2) ||
               (ponteiro[2] == 2 && ponteiro[4] == 2 && ponteiro[6] == 2) ||
               (ponteiro[3] == 2 && ponteiro[4] == 2 && ponteiro[5] == 2) ||
               (ponteiro[1] == 2 && ponteiro[4] == 2 && ponteiro[7] == 2)) {
        return 1;
    } else {
        for (i = 0; i < 9; i++) {
            velha += ponteiro[i];
        }

        if (velha == 13) {
            return 2;
        } else {
            return 0;
        }
    }
}

int verificarJogada(int *ponteiro, int movimento[2]) {
    if ((ponteiro[(3 * movimento[0]) + movimento[1]] == 1) || (ponteiro[(3 * movimento[0]) + movimento[1]] == 2)) {
        return 1;
    } else if (movimento[0] > 2 || movimento[0] < 0 || movimento[1] < 0 || movimento[1] > 2) {
        return 1;
    } else {
        return 0;
    }
}

void escolha01(int *ponteiro, char *nome1, char *nome2) {
    int parar = 0, trocarNome = 1, jogada = 0, movimento[2], i;

    limpar();

    printf("\t\tNome dos jogadores");
    printf("\n\n\nJogador 01 - X: ");
    scanf("%s", nome1);

    printf("Jogador 02 - 0: ");
    scanf("%s", nome2);

    do {
        limpar();

        do {
            if (trocarNome) {
                printf("\t\tVez de %s - X\n", nome1);
            } else {
                printf("\t\tVez de %s - 0\n", nome2);
            }

            printarTabuleiro(ponteiro);
            printf("Linha: ");
            scanf("%d", &movimento[0]);
            printf("Coluna: ");
            scanf("%d", &movimento[1]);

            movimento[0] -= 1;
            movimento[1] -= 1;

            jogada = verificarJogada(ponteiro, movimento);

            if (jogada) {
                printf("\n\nMovimento invalido... Tente novamente\n\n");
                pausar();
                limpar();
            } else {
                if (trocarNome) {
                    ponteiro[(3 * movimento[0]) + movimento[1]] = 1;
                } else {
                    ponteiro[(3 * movimento[0]) + movimento[1]] = 2;
                }
            }

        } while (jogada);

        parar = verificarFim(ponteiro);

        if (parar == 1) {
            limpar();

            if (trocarNome) {
                printf("\t\tVENCEDOR - %s - X\n", nome1);

                printarTabuleiro(ponteiro);

                for (i = 0; i < 20; i++) {
                    system("color a0");
                    system("color 0a");
                }
            } else {
                printf("\t\tVENCEDOR - %s - 0\n", nome2);

                printarTabuleiro(ponteiro);

                for (i = 0; i < 20; i++) {
                    system("color a0");
                    system("color 0a");
                }
            }
        } else if (parar == 2) {
            limpar();

            printf("\t\tVELHA!!!\n");

            printarTabuleiro(ponteiro);

            for (i = 0; i < 20; i++) {
                system("color 4a");
                system("color 0a");
            }
        }

        if (trocarNome) {
            trocarNome = 0;
        } else {
            trocarNome = 1;
        }

    } while (parar == 0);
}

void escolha02(void) {
    printf("\nEm desenvolvimento...");
}

int menu(void) {
    int escolha;

    limpar();

    do {
        printf("\t\tJOGO DOIDAO\n\n\n");

        printf("1 - Jogador x Jogador\n");
        printf("2 - Jogador x Computador\n");
        printf("3 - Sair\n\n");

        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha < 1 || escolha > 3) {
            printf("\nOpcao invalida!!! Escolha outra...\n\n");
            pausar();
            limpar();
        }

    } while (escolha < 1 || escolha > 3);

    return escolha;
}

void printarTabuleiro(int *ponteiro) {
    int i, j;

    printf("\n    1   2   3 ");
    for (i = 1; i <= 3; i++) {
        printf("\n");
        printf("%d ", i);
        for (j = 0; j < 3; j++) {
            if (ponteiro[(i - 1) * 3 + j] == 0) {
                printf(" { }");
            } else if (ponteiro[(i - 1) * 3 + j] == 1) {
                printf(" {X}");
            } else {
                printf(" {0}");
            }
        }
    }
    printf("\n\n");
}

void limparTabuleiro(int *ponteiro) {
    int i, j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            ponteiro[3 * i + j] = 0;
        }
    }
}

int main(void) {
    system("color 0a");

    int tabuleiro[3][3];
    int escolha;
    char nome1[50], nome2[50];

    while (1) {
        escolha = menu();

        if (escolha == 1) {
            limparTabuleiro(tabuleiro[3]);
            escolha01(tabuleiro[3], nome1, nome2);
            pausar();
        } else if (escolha == 2) {
            limparTabuleiro(tabuleiro[3]);
            escolha02();
            pausar();
        } else if (escolha == 3) {
            exit(1);
        }
    }

    return 0;
}