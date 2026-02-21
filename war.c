#include <stdio.h>   // Biblioteca para entrada e saída (printf e scanf)
#include <string.h>  // Biblioteca para manipulação de strings

// Definição da struct Territorio
struct Territorio {
    char nome[30];   // Nome do território (até 29 caracteres + '\0')
    char cor[10];    // Cor do exército (até 9 caracteres + '\0')
    int tropas;      // Quantidade de tropas
};

int main() {

    // Declaração de um vetor para armazenar 5 territórios
    struct Territorio territorios[5];

    // Laço para cadastrar os 5 territórios
    for (int i = 0; i < 5; i++) {

        printf("\n=== Cadastro do Territorio %d ===\n", i + 1);

        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n\n=== Territorios Cadastrados ===\n");

    for (int i = 0; i < 5; i++) {

        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exercito: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }

    return 0; // Indica que o programa terminou corretamente
}