#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define VILA 15
#define FASE1 20
#define FASE2 20
#define FASE3 40

// Funcoes da vila
char vila[VILA][VILA];
int px, py;
boolean comChave = 0;

// fase 1
char faseUm[FASE1][FASE1];
int px_fase1, py_fase1;

// fase 2-----------------------
char fase2_mapa[FASE2][FASE2];
int fase2_jogadorX, fase2_jogadorY;
int fase2_vidas = 3;
int fase2_chaveColetada = 0;
int fase2_monstroX, fase2_monstroY;

// FASE 3 ----------------------------------
char fase3_mapa[FASE3][FASE3];
int fase3_jogadorX, fase3_jogadorY;
int fase3_vidas = 3;
int fase3_chaveColetada = 0;
int fase3_monstroX, fase3_monstroY;

// Posições dos teletransportes
int tp1_x = 20, tp1_y = 12;
int tp2_x = 30, tp2_y = 5;



// VILA -----------------


void inicializaMapa() {
    for (int i = 0; i < VILA; i++) {
        for (int j = 0; j < VILA; j++) {
            if (i == 0 || j == 0 || i == VILA - 1 || j == VILA - 1)
                vila[i][j] = '*';
            else
                vila[i][j] = ' ';
        }
    }

    vila[5][5] = 'P';    // NPC
    vila[3][8] = '@';    // Chave
    vila[10][10] = 'D';  // Porta fechada
    px = 1; py = 1;
    vila[px][py] = '&';  // Jogador
}

// --------- Impressão do mapa ---------
void imprimeMapa() {
    system("cls");
    for (int i = 0; i < VILA; i++) {
        for (int j = 0; j < VILA; j++) {
            printf("%c ", vila[i][j]);
        }
        printf("\n");
    }
    printf("\nChave coletada? %s\n", comChave ? "SIM" : "NÃO");
    printf("Fale com o NPC\n");

}

// --------- Abrir a porta ---------
void abrirPorta() {
    for (int i = 0; i < VILA; i++) {
        for (int j = 0; j < VILA; j++) {
            if (vila[i][j] == 'D') {
                vila[i][j] = '='; // Porta aberta
            }
        }
    }
    printf("A porta foi aberta!\n");
    getch();
}

// --------- Verificar interações ---------
void interagir() {
    if (vila[px][py] == '@') {
        comChave = 1;
        vila[px][py] = '&';
        printf("Voce pegou a chave!\n");
        abrirPorta();
    } else if (vila[px][py] == 'P') {
        printf("NPC: bem-vindo a masmorra! Seu objetivo e simples: sair vivo.\n Mas nao vai ser fácil... monstros espreitam e espinhos venenosos aguardam cada passo. Boa sorte.\n");
        printf("Pegue a chave (@) e chegue  na porta (=).\n");
        getch();
    }
}

// --------- Movimentação ---------
void moverJogador(char comando) {
    int novoX = px;
    int novoY = py;

    switch (tolower(comando)) {
        case 'w': novoX--; break;
        case 's': novoX++; break;
        case 'a': novoY--; break;
        case 'd': novoY++; break;
        default: return;
    }

    if (vila[novoX][novoY] == '*') return;

    vila[px][py] = ' ';
    px = novoX;
    py = novoY;
    interagir(); // chama função de interação
    vila[px][py] = '&';
}

// --------- Loop principal da vila ---------
boolean vilaPrincipal() {
    inicializaMapa(); // Inicializa o mapa da vila
    char comando;

    while (1) {
        imprimeMapa(); // Exibe o mapa da vila
        comando = getch(); // Captura o comando do jogador

        if (tolower(comando) == 'q') {
            printf("Você saiu do jogo.\n");
            return 1; // Sai do jogo
        }

        moverJogador(comando); // Move o jogador com base no comando

        // Verifica se o jogador está na posição da porta aberta
        if (vila[px][py] == '=') {
            printf("Você entrou na porta e avançou para a fase 1!\n");
            getch();
            return 1; // Avança para a fase 1
        }
    }
}

// FASE 1 -=------------------------



void inicializaFase1() {
    comChave = 1;
    for (int i = 0; i < FASE1; i++) {
        for (int j = 0; j < FASE1; j++) {
            if (i == 0 || j == 0 || i == FASE1 - 1 || j == FASE1 - 1)
                faseUm[i][j] = '*';  // bordas
            else
                faseUm[i][j] = ' ';
        }
    }

    faseUm[10][10] = '@';  // chave
    faseUm[18][18] = 'D';  // porta fechada
    px_fase1 = 1;
    py_fase1 = 1;
    faseUm[px_fase1][py_fase1] = '&';  // jogador
}

// Imprime o mapa na tela
void imprimeFase1() {
    system("cls");
    for (int i = 0; i < FASE1; i++) {
        for (int j = 0; j < FASE1; j++) {
            printf("%c ", faseUm[i][j]);
        }
        printf("\n");
    }

    printf("\nChave coletada? %s\n", comChave ? "SIM" : "NÃO");
    printf("Use W A S D para mover, i para interagir, q para sair.\n");
}

// Abre a porta ao pegar a chave
void abrirPortaFase1() {
    for (int i = 0; i < FASE1; i++) {
        for (int j = 0; j < FASE1; j++) {
            if (faseUm[i][j] == 'D') {
                faseUm[i][j] = '=';  // porta aberta
            }
        }
    }
    printf("A porta foi aberta!\n");
    getch();
}

// Interação do jogador com elementos
void interagirFase1() {
    if (faseUm[px_fase1][py_fase1 ] == '@') {
        comChave = 1;
        faseUm[px_fase1][py_fase1] = '&';
        printf("Você pegou a chave!\n");
        abrirPortaFase1();
    }
}

// Movimenta o jogador
void moverJogadorFase1(char comando) {
    int novoX = px_fase1;
    int novoY = py_fase1;

    switch (tolower(comando)) {
        case 'w': novoX--; break;
        case 's': novoX++; break;
        case 'a': novoY--; break;
        case 'd': novoY++; break;
        default: return;
    }

    if (faseUm[novoX][novoY] == '*') return;

    // Corrigido: Atualiza a posição anterior do jogador na fase 1
    faseUm[px_fase1][py_fase1] = ' ';
    px_fase1 = novoX;
    py_fase1 = novoY;
    interagirFase1(); // Chama a função de interação específica da fase 1
    faseUm[px_fase1][py_fase1] = '&';
}

// Loop da fase 1
void fase1() {
    char comando;
    inicializaFase1();

    while (1) {
        imprimeFase1();
        comando = getch();

        if (tolower(comando) == 'q') break;

        moverJogadorFase1(comando);

        if (faseUm[px_fase1][py_fase1] == '=') {
            printf("Você completou a Fase 1!\n");
            getch();
            break;
        }
    }
}

// FASE 2 -------------------

int fase2_verificaColisao() {
    // Verifica se o jogador está sobre um espinho
    if (fase2_mapa[fase2_jogadorX][fase2_jogadorY] == '#') {
        printf("\nVocê pisou em um espinho! -1 vida\n");
        fase2_vidas--;
        Sleep(1000);
        return 1; // sinaliza que deve reiniciar a fase
    }

    // Verifica se o monstro alcançou o jogador
    if (fase2_jogadorX == fase2_monstroX && fase2_jogadorY == fase2_monstroY) {
        printf("\nO monstro te pegou! -1 vida\n");
        fase2_vidas--;
        Sleep(1000);
        return 1; // sinaliza que deve reiniciar a fase
    }

    return  0;
}


void fase2_moverMonstro() {
    int dir = rand() % 4; // Escolhe uma direção aleatória
    int novoX = fase2_monstroX;
    int novoY = fase2_monstroY;

    // Calcula a nova posição com base na direção
    if (dir == 0) novoX--; // Cima
    if (dir == 1) novoX++; // Baixo
    if (dir == 2) novoY--; // Esquerda
    if (dir == 3) novoY++; // Direita

    // Verifica se a nova posição está dentro dos limites do mapa
    if (novoX < 0 || novoX >= FASE2 || novoY < 0 || novoY >= FASE2) {
        return; // Movimento inválido, não atualiza a posição
    }

    // Verifica se a nova posição é válida (não é uma parede ou outro monstro)
    if (fase2_mapa[novoX][novoY] == ' ' || fase2_mapa[novoX][novoY] == '&') {
        // Atualiza a posição do monstro no mapa
        fase2_mapa[fase2_monstroX][fase2_monstroY] = ' '; // Libera a posição anterior
        fase2_monstroX = novoX;
        fase2_monstroY = novoY;
        fase2_mapa[fase2_monstroX][fase2_monstroY] = 'X'; // Atualiza a nova posição
    }
}


void fase2_inicializaMapa() {
    for (int i = 0; i < FASE2; i++)
        for (int j = 0; j < FASE2; j++)
            fase2_mapa[i][j] = ' ';

    for (int i = 0; i < FASE2; i++) {
        fase2_mapa[0][i] = '*';
        fase2_mapa[FASE2 - 1][i] = '*';
        fase2_mapa[i][0] = '*';
        fase2_mapa[i][FASE2 - 1] = '*';
    }

    fase2_jogadorX = 1;
    fase2_jogadorY = 1;
    fase2_mapa[fase2_jogadorX][fase2_jogadorY] = '&';

    fase2_mapa[5][5] = '#';
    fase2_mapa[8][3] = '#';
    fase2_mapa[12][12] = '#';
    fase2_mapa[6][14] = '#';
    fase2_mapa[15][2] = '#';
    fase2_mapa[8][8] = 'X';  fase2_monstroX = 8;  fase2_monstroY = 8;  // Monstro aleatório


    fase2_mapa[4][4] = '@'; // chave
    fase2_mapa[10][10] = 'D'; // porta fechada
}

void fase2_imprimeMapa() {
    for (int i = 0; i < FASE2; i++) {
        for (int j = 0; j < FASE2; j++) {
            printf("%c ", fase2_mapa[i][j]);
        }
        printf("\n");
    }
    printf("\nVidas restantes: %d\n", fase2_vidas);
}

void fase2_moveJogador(char movimento) {
    int novoX = fase2_jogadorX;
    int novoY = fase2_jogadorY;

    if (movimento == 'w') novoX--;
    if (movimento == 's') novoX++;
    if (movimento == 'a') novoY--;
    if (movimento == 'd') novoY++;

    char destino = fase2_mapa[novoX][novoY];



    if (destino == '*') return;

    if (destino == '#') {
        fase2_vidas--;
        printf("Você tocou em um espinho! -1 vida\n");
        Sleep(500);
        return; // Não move o jogador
    }

    if (destino == '@') {
        fase2_chaveColetada = 1;
        fase2_mapa[4][4] = ' '; // Remove a chave
        fase2_mapa[10][10] = '='; // Porta se abre
        printf("Você pegou a chave! A porta foi aberta.\n");
        Sleep(1000);
    }

    if (destino == 'D') {
        printf("A porta está trancada. Pegue a chave!\n");
        Sleep(1000);
        return;
    }

    if (destino == '=') {
        printf("Você passou pela porta!\n");
        Sleep(1000);
        return; // Aqui você pode chamar fase3()
    }

    fase2_mapa[fase2_jogadorX][fase2_jogadorY] = ' ';
    fase2_jogadorX = novoX;
    fase2_jogadorY = novoY;
    fase2_mapa[fase2_jogadorX][fase2_jogadorY] = '&';
}



void fase2() {
    fase2_vidas = 3; // Inicializa as vidas
    fase2_chaveColetada = 0; // Inicializa a chave como não coletada
    fase2_inicializaMapa(); // Inicializa o mapa da fase 2

    while (fase2_vidas > 0) {
    system("cls");
    fase2_imprimeMapa();

   

    char comando = _getch();
    if (comando == 'w' || comando == 'a' || comando == 's' || comando == 'd') {
        fase2_moveJogador(comando);
    } else if (comando == 'i') {
        // interação (caso use no futuro)
    }

    fase2_moverMonstro();

    // Verifica colisão com monstro ou espinho
    if (fase2_verificaColisao()) {
        if (fase2_vidas > 0) {
            printf("Reiniciando a fase...\n");
            Sleep(1000);
            fase2_inicializaMapa(); // reinicia tudo, inclusive o monstro e o jogador
        }
    }
}
}





int fase3_verificaColisao() {
    if (fase3_mapa[fase3_jogadorX][fase3_jogadorY] == '#') {
        printf("\nVocê pisou em um espinho! -1 vida\n");
        fase3_vidas--;
        Sleep(1000);
        return 1;
    }

    if (fase3_jogadorX == fase3_monstroX && fase3_jogadorY == fase3_monstroY) {
        printf("\nO monstro te pegou! -1 vida\n");
        fase3_vidas--;
        Sleep(1000);
        return 1;
    }

    return  0;
}

void fase3_moverMonstro() {
    int dir = rand() % 4;
    int novoX = fase3_monstroX;
    int novoY = fase3_monstroY;

    if (dir == 0) novoX--;
    if (dir == 1) novoX++;
    if (dir == 2) novoY--;
    if (dir == 3) novoY++;

    if (novoX < 0 || novoX >= FASE3 || novoY < 0 || novoY >= FASE3) return;

    if (fase3_mapa[novoX][novoY] == ' ' || fase3_mapa[novoX][novoY] == '&') {
        fase3_mapa[fase3_monstroX][fase3_monstroY] = ' ';
        fase3_monstroX = novoX;
        fase3_monstroY = novoY;
        fase3_mapa[fase3_monstroX][fase3_monstroY] = 'V';
    }
}

void fase3_inicializaMapa() {
    for (int i = 0; i < FASE3; i++)
        for (int j = 0; j < FASE3; j++)
            fase3_mapa[i][j] = ' ';

    for (int i = 0; i < FASE3; i++) {
        fase3_mapa[0][i] = '*';
        fase3_mapa[FASE3 - 1][i] = '*';
        fase3_mapa[i][0] = '*';
        fase3_mapa[i][FASE3 - 1] = '*';
    }

    fase3_jogadorX = 1;
    fase3_jogadorY = 1;
    fase3_mapa[fase3_jogadorX][fase3_jogadorY] = '&';

    fase3_mapa[15][5] = '#';
    fase3_mapa[13][5] = '#';
    fase3_mapa[11][5] = '#';
    fase3_mapa[10][5] = '#';
    fase3_mapa[17][32] = '#';
    fase3_mapa[16][17] = '#';
    fase3_mapa[32][3] = '#';
    fase3_mapa[16][31] = '#';
    fase3_mapa[27][23] = '#';
    fase3_mapa[32][15] = '#';
    fase3_mapa[32][14] = '#';
    fase3_mapa[22][6] = '#';
    fase3_mapa[22][4] = '#';
    fase3_mapa[5][5] = '#';
    fase3_mapa[8][3] = '#';
    fase3_mapa[12][12] = '#';
    fase3_mapa[6][14] = '#';
    fase3_mapa[15][2] = '#';

    fase3_mapa[30][32] = 'V';
    fase3_monstroX = 30;
    fase3_monstroY = 32;

    fase3_mapa[15][7] = '@';
    fase3_mapa[26][36] = 'D';

    // Adiciona os dois pontos de teletransporte
    fase3_mapa[tp1_x][tp1_y] = '>';
    fase3_mapa[tp2_x][tp2_y] = '>';
}

void fase3_imprimeMapa() {
    for (int i = 0; i < FASE3; i++) {
        for (int j = 0; j < FASE3; j++) {
            printf("%c ", fase3_mapa[i][j]);
        }
        printf("\n");
    }
    printf("\nVidas restantes: %d\n", fase3_vidas);
}

void fase3_moveJogador(char movimento) {
    int novoX = fase3_jogadorX;
    int novoY = fase3_jogadorY;

    if (movimento == 'w') novoX--;
    if (movimento == 's') novoX++;
    if (movimento == 'a') novoY--;
    if (movimento == 'd') novoY++;

    char destino = fase3_mapa[novoX][novoY];

    if (destino == '*') return;

    if (destino == '#') {
        fase3_vidas--;
        printf("Você tocou em um espinho! -1 vida\n");
        Sleep(500);
        return;
    }

    if (destino == '@') {
        fase3_chaveColetada = 1;
        fase3_mapa[4][4] = ' ';
        fase3_mapa[26][36] = '=';
        printf("Você pegou a chave! A porta foi aberta.\n");
        Sleep(1000);
    }

    if (destino == 'D') {
        printf("A porta está trancada. Pegue a chave!\n");
        Sleep(1000);
        return;
    }

    if (destino == '=') {
        printf("Você passou pela porta!\n");
        Sleep(1000);
        return;
    }

    if (destino == '>') {
        printf("Teletransporte ativado!\n");
        Sleep(500);
        fase3_mapa[fase3_jogadorX][fase3_jogadorY] = ' ';

        if (novoX == tp1_x && novoY == tp1_y) {
            fase3_jogadorX = tp2_x;
            fase3_jogadorY = tp2_y;
        } else {
            fase3_jogadorX = tp1_x;
            fase3_jogadorY = tp1_y;
        }

        fase3_mapa[fase3_jogadorX][fase3_jogadorY] = '&';
        return;
    }

    fase3_mapa[fase3_jogadorX][fase3_jogadorY] = ' ';
    fase3_jogadorX = novoX;
    fase3_jogadorY = novoY;
    fase3_mapa[fase3_jogadorX][fase3_jogadorY] = '&';
}

void fase3() {
    fase3_vidas = 3;
    fase3_chaveColetada = 0;
    fase3_inicializaMapa();

    while (fase3_vidas > 0) {
        system("cls");
        fase3_imprimeMapa();

        char comando = _getch();
        if (comando == 'w' || comando == 'a' || comando == 's' || comando == 'd') {
            fase3_moveJogador(comando);
        }

        fase3_moverMonstro();

        if (fase3_verificaColisao()) {
            if (fase3_vidas > 0) {
                printf("Reiniciando a fase...\n");
                Sleep(1000);
                fase3_inicializaMapa();
            }
        }
    }
}

// --------- Funções auxiliares ---------
void mostrarTelaVitoria() { printf("Parabéns! Você venceu o jogo.\n"); }
void mostrarCreditos() { printf("Créditos: Desenvolvido por Gabriel.\n"); }
void sairDoJogo() { printf("\nObrigado por jogar Dungeon Crawler! Até logo.\n\n"); }

// --------- Menu principal ---------
int main() {
    int opcao;

    while (1) {
        printf("Escolha uma opção:\n");
        printf("1 - Jogar\n");
        printf("2 - Créditos\n");
        printf("3 - Sair\n");
        printf("Digite sua opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                vilaPrincipal();
                fase1();
                fase2();
                fase3();
                mostrarTelaVitoria();
                break;
            case 2:
                mostrarCreditos();
                break;
            case 3:
                sairDoJogo();
                return 0;
            default:
                printf("Opção inválida.\n");
                break;
    }
    }
}
