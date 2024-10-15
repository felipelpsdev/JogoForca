#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define TOTAL_DE_PALAVRAS 20
#define TAM_PALAVRA 15
#define TAM_DICA 100


//Feito por Igor Ryan e Luiz Felipe - ADS II

typedef struct {
    char palavras[TOTAL_DE_PALAVRAS][TAM_PALAVRA];  // Array de palavras
    char dicas[TOTAL_DE_PALAVRAS][TAM_DICA];        // Array de dicas
    char palavra_s[TAM_PALAVRA];                    // Palavra selecionada para o jogo
    char dica[TAM_DICA];                            // Dica associada à palavra selecionada
} BancoPalavras;

typedef struct {
    char jogador_nome[25];
    int vitorias;
    int derrotas;
    int n_rodadas;
} Jogador;

void menu(Jogador *vjogador, BancoPalavras *vbancopalavras);
void iniciar_jogo(Jogador *vjogador, BancoPalavras *vbancopalavras);
void historico(Jogador *vjogador);
void armazenar_palavras(BancoPalavras *vbancopalavras);
void desenhoForca(int erros);

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    Jogador vjogador = {0};
    BancoPalavras vbancopalavras;
	printf("Digite seu nome: ");
	scanf("%s", vjogador.jogador_nome);

    menu(&vjogador, &vbancopalavras);

    return 0;
}

void menu(Jogador *vjogador, BancoPalavras *vbancopalavras) {
    int escolha;
    while (1) {
        system("cls");
        printf("\n---------------------");
        printf("\n|                   |");
        printf("\n|                   0");
        printf("\n|                  /|\\");
        printf("\n|                  / \\   ");
        printf("\n|");
        printf("\n|    Trabalho de Programação II");
        printf("\n|");
        printf("\n==");
        printf("\n");
        printf("\n===== JOGO DA FORCA =====\n");
        printf("\n1. Iniciar Jogo\n");
        printf("2. Histórico\n");
        printf("3. Sair\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                system("cls");
                armazenar_palavras(vbancopalavras);
                iniciar_jogo(vjogador, vbancopalavras);
                break;
            case 2:
                system("cls");
                historico(vjogador);
                break;
            case 3:
                system("cls");
                printf("Até logo 0/ \n");
                return;
            default:
                printf("Opção inválida!\n");
                break;
        }
    }
}

void iniciar_jogo(Jogador *vjogador, BancoPalavras *vbancopalavras) {
    printf("Número de rodadas: ");
    scanf("%d", &vjogador->n_rodadas);

    int rodada;
    int tam_palavra;
    tam_palavra = 0;
    for (rodada = 0; rodada < vjogador->n_rodadas; rodada++) {
    	srand(time(NULL));
        int random = rand() % TOTAL_DE_PALAVRAS;
        strcpy(vbancopalavras->palavra_s, vbancopalavras->palavras[random]);
        tam_palavra = strlen(vbancopalavras->palavra_s);
        strcpy(vbancopalavras->dica, vbancopalavras->dicas[random]);

        char palavra_oculta[TAM_PALAVRA] = {0};
        int i;
        for (i = 0; i < tam_palavra; i++) {
            palavra_oculta[i] = '_';
        }

        int n_tentativas = 6;
        int erros = 0;
        int acertos = 0;

        while (erros < n_tentativas && acertos < tam_palavra) {
            desenhoForca(erros);

            printf("\nRodada %d de %d \n", rodada + 1, vjogador->n_rodadas);
			printf("\nDica: %s\n", vbancopalavras->dica);
            printf("\nPalavra: %s\n", palavra_oculta);
            printf("Tentativas restantes: %d\n", n_tentativas - erros);
			char letra;
			printf("Digite uma letra: ");
            scanf(" %c", &letra);


			int acerto = 0;
            for (i = 0; i < tam_palavra; i++) {
                if (vbancopalavras->palavra_s[i] == letra && palavra_oculta[i] == '_') {
                    palavra_oculta[i] = letra;
                    acerto = 1;
                    acertos++;
                }
            }

            if (!acerto) {
                erros++;
            }

            if (acertos == tam_palavra) {
                vjogador->vitorias++;
                break;
            }

            if (erros == n_tentativas) {
                desenhoForca(erros);
                printf("\nVocê perdeu esta rodada! A palavra era: %s\n", vbancopalavras->palavra_s);
                vjogador->derrotas++;
                system("pause");
                break;

            }
        }


    }

    if(vjogador->vitorias > vjogador->derrotas){
		system("cls");
		printf("Jogador vitorioso\n");
	}else if(vjogador->vitorias < vjogador->derrotas){
		system("cls");
		printf("\n O jogador perdeu \n");
	}else if(vjogador->vitorias = vjogador->derrotas){
		system("cls");
		printf("\n O jogo deu empate! Inicie novas rodadas no menu \n");
	}
	printf("\nTodas as rodadas foram concluídas.\n");
    system("pause");

}



void historico(Jogador *vjogador) {
    int totalJogos = vjogador->vitorias + vjogador->derrotas;
    int percVitorias = 0;
    int percDerrotas = 0;

    if (totalJogos > 0) {
        percVitorias = (vjogador->vitorias * 100) / totalJogos;
        percDerrotas = (vjogador->derrotas * 100) / totalJogos;
    }

		printf("\n---------------------");
        printf("\n|                   |");
        printf("\n|                   0");
        printf("\n|                  /|\\");
        printf("\n|                  / \\  ");
        printf("\n|");
        printf("\n==");
        printf("\n");
        printf("\n===== JOGO DA FORCA =====\n");

    printf("\nHistórico de %s:\n", vjogador->jogador_nome);
	printf("Vitórias: %d (%d%%)\n", vjogador->vitorias, percVitorias);
    printf("Derrotas: %d (%d%%)\n", vjogador->derrotas, percDerrotas);
    system("pause");
}


void armazenar_palavras(BancoPalavras *vbancopalavras) {
    strcpy(vbancopalavras->palavras[0], "xadrez");
    strcpy(vbancopalavras->dicas[0], "Jogo com peças como rei, bispo e torre.");

    strcpy(vbancopalavras->palavras[1], "samuel");
    strcpy(vbancopalavras->dicas[1], "TÉCNICO DE AUTOMAÇÃO DO IFMA CN");

    strcpy(vbancopalavras->palavras[2], "mario");
    strcpy(vbancopalavras->dicas[2], "Famoso encanador dos videogames da Nintendo.");

    strcpy(vbancopalavras->palavras[3], "algoritmo");
    strcpy(vbancopalavras->dicas[3], "Conjunto de instruções para resolver um problema.");

    strcpy(vbancopalavras->palavras[4], "sonic");
    strcpy(vbancopalavras->dicas[4], "mascote da SEGA.");

    strcpy(vbancopalavras->palavras[5], "variavel");
    strcpy(vbancopalavras->dicas[5], "Elemento que pode mudar seu valor.");

    strcpy(vbancopalavras->palavras[6], "computador");
    strcpy(vbancopalavras->dicas[6], "Maquina que faz calculos e executa programas.");

    strcpy(vbancopalavras->palavras[7], "internet");
    strcpy(vbancopalavras->dicas[7], "Rede mundial de computadores interconectados.");

    strcpy(vbancopalavras->palavras[8], "programador");
    strcpy(vbancopalavras->dicas[8], "Profissional que escreve códigos de software.");

    strcpy(vbancopalavras->palavras[9], "teclado");
    strcpy(vbancopalavras->dicas[9], "Dispositivo de entrada com teclas para digitar.");

    strcpy(vbancopalavras->palavras[10], "software");
    strcpy(vbancopalavras->dicas[10], "Conjunto de programas e dados em um computador.");

    strcpy(vbancopalavras->palavras[11], "hardware");
    strcpy(vbancopalavras->dicas[11], "Componentes físicos de um computador.");

    strcpy(vbancopalavras->palavras[12], "banco");
    strcpy(vbancopalavras->dicas[12], "Local onde se guarda dinheiro ou dados.");

    strcpy(vbancopalavras->palavras[13], "processador");
    strcpy(vbancopalavras->dicas[13], "Componente do computador que realiza cálculos.");

    strcpy(vbancopalavras->palavras[14], "memoria");
    strcpy(vbancopalavras->dicas[14], "Armazenamento temporário ou permanente de dados.");

    strcpy(vbancopalavras->palavras[15], "rede");
    strcpy(vbancopalavras->dicas[15], "Conjunto de dispositivos interconectados.");

    strcpy(vbancopalavras->palavras[16], "algoritmo");
    strcpy(vbancopalavras->dicas[16], "Conjunto de regras ou instruções para resolver um problema.");

    strcpy(vbancopalavras->palavras[17], "codigo");
    strcpy(vbancopalavras->dicas[17], "Conjunto de símbolos e regras para criar programas.");

    strcpy(vbancopalavras->palavras[18], "byte");
    strcpy(vbancopalavras->dicas[18], "Unidade de informação digital que equivale a 8 bits.");

    strcpy(vbancopalavras->palavras[19], "monitor");
    strcpy(vbancopalavras->dicas[19], " dispositivo de saida, cuja funcao é transmitir informacao.");
}

void desenhoForca(int erros) {
    system("cls");

    if(erros == 0){
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|");
		printf("\n|");
	   	printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");
	}else if(erros == 1){
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|                 ");
	   	printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");
	}else if(erros == 2){
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|                |");
	   	printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");

	}else if(erros == 3){
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|               /|");
	   	printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");

	}else if(erros == 4){
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|               /|\\");
	   	printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");

	}else if(erros == 5)
	{
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|               /|\\");
	   	printf("\n|               /   ");
		printf("\n|");
		printf("\n|");
		printf("\n|");
		printf("\n_");
	}else if(erros == 6)
	{
		printf("\n------------------");
		printf("\n|                |");
		printf("\n|                0");
		printf("\n|               /|\\");
	   	printf("\n|               / \\   ");
		printf("\n|");
		printf("\n|    Ta morto !");
		printf("\n|");
		printf("\n_");
	}

}

//Feito por Igor Ryan e Luiz Felipe - ADS II