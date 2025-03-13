#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

#define MAX_CARTAS 10

typedef struct {
    char estado[50];
    int codigo;
    char cidade[50];
    long populacao;
    float area;
    double pib;
    int pontosTuristicos;
} Carta;

void cadastrarCarta(Carta* c) {
    printf("Digite o estado: ");
    fgets(c->estado, sizeof(c->estado), stdin);
    c->estado[strcspn(c->estado, "\n")] = '\0';

    printf("Digite o codigo da carta: ");
    scanf("%d", &c->codigo);
    getchar();

    printf("Digite o nome da cidade: ");
    fgets(c->cidade, sizeof(c->cidade), stdin);
    c->cidade[strcspn(c->cidade, "\n")] = '\0';

    printf("Digite a populacao: ");
    scanf("%ld", &c->populacao);

    printf("Digite a area (em km²): ");
    scanf("%f", &c->area);

    printf("Digite o PIB: ");
    scanf("%lf", &c->pib);

    printf("Digite o numero de pontos turisticos: ");
    scanf("%d", &c->pontosTuristicos);
    getchar();
}

void exibirCarta(Carta c) {
    printf("Estado: %s\n", c.estado);
    printf("Codigo: %d\n", c.codigo);
    printf("Cidade: %s\n", c.cidade);
    printf("Populacao: %ld\n", c.populacao);
    printf("Area: %.2f km²\n", c.area);
    printf("PIB: %.2lf\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontosTuristicos);
}

double getAttributeValue(Carta c, int atributo) {
    switch (atributo) {
    case 1:
        return (double)c.populacao;
    case 2:
        return (double)c.area;
    case 3:
        return c.pib;
    case 4:
        return (double)c.pontosTuristicos;
    case 5:
        return (c.area != 0) ? ((double)c.populacao / c.area) : 0;
    default:
        return 0;
    }
}

int compareAttribute(double val1, double val2, int reverse) {
    if (val1 == val2)
        return 0;
    if (reverse) {
        return (val1 < val2) ? 1 : 2;
    }
    else {
        return (val1 > val2) ? 1 : 2;
    }
}

int compararCartaNovato(Carta c1, Carta c2, int atributo) {
    int reverse = (atributo == 5) ? 1 : 0;
    double v1 = getAttributeValue(c1, atributo);
    double v2 = getAttributeValue(c2, atributo);
    return compareAttribute(v1, v2, reverse);
}

int compararCartaMestre(Carta c1, Carta c2, int attr1, int attr2) {
    int reverse1 = (attr1 == 5) ? 1 : 0;
    int reverse2 = (attr2 == 5) ? 1 : 0;

    double v1_attr1 = getAttributeValue(c1, attr1);
    double v2_attr1 = getAttributeValue(c2, attr1);
    double v1_attr2 = getAttributeValue(c1, attr2);
    double v2_attr2 = getAttributeValue(c2, attr2);

    int resultado1 = compareAttribute(v1_attr1, v2_attr1, reverse1);
    int resultado2 = compareAttribute(v1_attr2, v2_attr2, reverse2);

    int pontos1 = 0, pontos2 = 0;
    if (resultado1 == 1)
        pontos1++;
    else if (resultado1 == 2)
        pontos2++;

    if (resultado2 == 1)
        pontos1++;
    else if (resultado2 == 2)
        pontos2++;

    if (pontos1 > pontos2)
        return 1;
    else if (pontos2 > pontos1)
        return 2;
    else
        return 0;
}

int main() {
    Carta carta1, carta2;
    int nivel;

    printf("===== Desafio Super Trunfo - Paises =====\n");
    printf("Escolha o nivel de jogo:\n");
    printf("1 - Novato\n");
    printf("2 - Aventureiro\n");
    printf("3 - Mestre\n");
    printf("Opcao: ");
    scanf("%d", &nivel);
    getchar();

    printf("\n--- Cadastro da Carta 1 ---\n");
    cadastrarCarta(&carta1);
    printf("\n--- Cadastro da Carta 2 ---\n");
    cadastrarCarta(&carta2);

    printf("\n--- Dados da Carta 1 ---\n");
    exibirCarta(carta1);
    printf("\n--- Dados da Carta 2 ---\n");
    exibirCarta(carta2);

    int atributo, atributo2;
    int resultado;

    switch (nivel) {
    case 1:
        printf("\nNivel Novato: Comparacao de uma unica propriedade.\n");
        printf("Escolha o atributo para comparacao:\n");
        printf("1 - Populacao\n");
        printf("2 - Area\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor vence)\n");
        printf("Opcao: ");
        scanf("%d", &atributo);
        resultado = compararCartaNovato(carta1, carta2, atributo);
        break;
    case 2:
        printf("\nNivel Aventureiro: Comparacao com menu interativo.\n");
        printf("Escolha o atributo para comparacao:\n");
        printf("1 - Populacao\n");
        printf("2 - Area\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor vence)\n");
        printf("Opcao: ");
        scanf("%d", &atributo);
        switch (atributo) {
        case 1: case 2: case 3: case 4: case 5:
            resultado = compararCartaNovato(carta1, carta2, atributo);
            break;
        default:
            printf("Atributo invalido!\n");
            return 1;
        }
        break;
    case 3:
        printf("\nNivel Mestre: Comparacao com dois atributos.\n");
        printf("Escolha o primeiro atributo para comparacao:\n");
        printf("1 - Populacao\n");
        printf("2 - Area\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor vence)\n");
        printf("Opcao: ");
        scanf("%d", &atributo);
        printf("Escolha o segundo atributo para comparacao:\n");
        printf("1 - Populacao\n");
        printf("2 - Area\n");
        printf("3 - PIB\n");
        printf("4 - Pontos Turisticos\n");
        printf("5 - Densidade Populacional (menor vence)\n");
        printf("Opcao: ");
        scanf("%d", &atributo2);
        resultado = compararCartaMestre(carta1, carta2, atributo, atributo2);
        break;
    default:
        printf("Nivel invalido!\n");
        return 1;
    }

    printf("\n===== Resultado da Comparacao =====\n");
    if (resultado == 1)
        printf("A Carta 1 (%s) venceu!\n", carta1.cidade);
    else if (resultado == 2)
        printf("A Carta 2 (%s) venceu!\n", carta2.cidade);
    else
        printf("Empate!\n");

    return 0;
}
