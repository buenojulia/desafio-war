#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= STRUCT =================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// ================= CADASTRO =================
void cadastrarTerritorios(Territorio* mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n=== Territorio %d ===\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// ================= EXIBIÇÃO =================
void exibirMapa(Territorio* mapa, int quantidade) {
    printf("\n===== MAPA =====\n");
    for (int i = 0; i < quantidade; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// ================= ATAQUE =================
void atacar(Territorio* atacante, Territorio* defensor) {

    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nNao pode atacar territorio da mesma cor!\n");
        return;
    }

    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtacante rolou: %d", dadoA);
    printf("\nDefensor rolou: %d\n", dadoD);

    if (dadoA > dadoD) {
        printf("Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

    } else {
        printf("Defensor venceu! Atacante perde 1 tropa.\n");

        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

// ================= MISSÕES =================
void atribuirMissao(char* destino, char* missoes[], int total) {
    int indice = rand() % total;
    strcpy(destino, missoes[indice]);
}

// ================= VERIFICAÇÃO =================
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    // Condição 1: todos territórios da mesma cor
    int mesmaCor = 1;

    for (int i = 1; i < tamanho; i++) {
        if (strcmp(mapa[0].cor, mapa[i].cor) != 0) {
            mesmaCor = 0;
            break;
        }
    }

    if (mesmaCor) return 1;

    // Condição 2: total de tropas >= 20
    int totalTropas = 0;

    for (int i = 0; i < tamanho; i++) {
        totalTropas += mapa[i].tropas;
    }

    if (totalTropas >= 20) return 1;

    return 0;
}

// ================= LIBERAÇÃO =================
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

// ================= MAIN =================
int main() {

    srand(time(NULL));

    int quantidade;

    printf("Quantos territorios? ");
    scanf("%d", &quantidade);

    // Alocação dinâmica do mapa
    Territorio* mapa = (Territorio*) calloc(quantidade, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, quantidade);

    // ================= MISSÕES =================
    char* missoes[] = {
        "Conquistar todos territorios",
        "Ter 20 tropas no total",
        "Dominar o mapa inteiro",
        "Eliminar inimigos",
        "Expandir territorios"
    };

    // Alocação dinâmica da missão
    char* missaoJogador = (char*) malloc(100 * sizeof(char));

    if (missaoJogador == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, 5);

    printf("\nSua missao: %s\n", missaoJogador);

    int atacante, defensor;
    char continuar;

    // ================= LOOP DO JOGO =================
    do {
        exibirMapa(mapa, quantidade);

        printf("\nEscolha atacante: ");
        scanf("%d", &atacante);

        printf("Escolha defensor: ");
        scanf("%d", &defensor);

        if (atacante >= 0 && atacante < quantidade &&
            defensor >= 0 && defensor < quantidade &&
            atacante != defensor) {

            atacar(&mapa[atacante], &mapa[defensor]);

            // Verifica vitória
            if (verificarMissao(missaoJogador, mapa, quantidade)) {
                printf("\n🏆 MISSÃO CUMPRIDA! VOCE VENCEU!\n");
                break;
            }

        } else {
            printf("Indices invalidos!\n");
        }

        printf("\nDeseja continuar? (s/n): ");
        scanf(" %c", &continuar);

    } while (continuar == 's' || continuar == 'S');

    liberarMemoria(mapa, missaoJogador);

    return 0;
}
