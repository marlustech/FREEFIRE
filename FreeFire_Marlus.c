#include <stdio.h>      // Para usar printf, scanf, etc.
#include <string.h>     // Para usar strcmp (comparar textos) e strcpy (copiar textos)
#include <stdlib.h>     // Para usar system("cls") e outras coisas úteis

// 1. CRIANDO O "MOLDE" DO ITEM — A STRUCT
// Isso aqui é como se você estivesse desenhando uma ficha de personagem no RPG
typedef struct {
    char nome[30];      // Nome do item: "AK-47", "Kit Médico", "Mochila Grande"
    char tipo[20];      // Tipo: "arma", "cura", "munição", "ferramenta"
    int quantidade;     // Quantas unidades você tem daquele item
} Item;

// 2. CRIANDO A MOCHILA (o vetor que guarda até 10 itens)
Item mochila[10];       // São 10 "espaços" na mochila (índices de 0 a 9)
int total_itens = 0;    // Começa com zero i1tens dentro

// 3. FUNÇÕES QUE VAMOS USAR (vamos criar uma por uma lá embaixo)
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

// 4. FUNÇÃO PRINCIPAL — É AQUI QUE O JOGO COMEÇA
int main() {
    int opcao;

    do {
        system("cls");  // Limpa a tela (no Windows)
        printf("=== MOCHILA DE SOBREVIVENCIA ===\n");
        printf("Itens na mochila: %d/10\n\n", total_itens);
        printf("1. Coletar item (inserir)\n");
        printf("2. Descartar item (remover)\n");
        printf("3. Ver mochila (listar)\n");
        printf("4. Procurar item (buscar)\n");
        printf("0. Fugir da zona (sair)\n");
        printf("\nO que voce quer fazer? ");
        scanf("%d", &opcao);
        getchar();  // Limpa o "Enter" que fica preso

        switch(opcao) {
            case 1: inserirItem();   break;
            case 2: removerItem();   break;
            case 3: listarItens();   break;
            case 4: buscarItem();    break;
            case 0: printf("Voce fugiu com vida! Boa sorte sobrevivente!\n"); break;
            default: printf("Opcao invalida! Tente de novo.\n");
        }

        if (opcao != 0) {
            printf("\nPressione ENTER para continuar...");
            getchar();  // Espera você apertar Enter
        }

    } while(opcao != 0);

    return 0;
}

// 5. FUNÇÃO PARA COLETAR UM ITEM NOVO
void inserirItem() {
    if (total_itens >= 10) {
        printf("Mochila cheia! Voce nao pode carregar mais nada!\n");
        return;
    }

    printf("\n--- COLETANDO ITEM ---\n");
    printf("Nome do item: ");
    fgets(mochila[total_itens].nome, 30, stdin);
    mochila[total_itens].nome[strcspn(mochila[total_itens].nome, "\n")] = 0; // tira o \n do final

    printf("Tipo (arma, cura, municao, ferramenta): ");
    fgets(mochila[total_itens].tipo, 20, stdin);
    mochila[total_itens].tipo[strcspn(mochila[total_itens].tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &mochila[total_itens].quantidade);
    getchar(); // limpa o Enter que fica

    total_itens++; // aumenta o contador
    printf("\nItem coletado com sucesso!\n");
}

// 6. FUNÇÃO PARA REMOVER UM ITEM
void removerItem() {
    if (total_itens == 0) {
        printf("Sua mochila ja esta vazia!\n");
        return;
    }

    char nome_busca[30];
    printf("\nDigite o nome do item que quer descartar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < total_itens; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            printf("Descartando: %s (%d unidades)\n", mochila[i].nome, mochila[i].quantidade);

            // Move todos os itens seguintes uma posição para trás
            for (int j = i; j < total_itens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            total_itens--;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado na mochila!\n");
    } else {
        printf("Item descartado!\n");
    }
}

// 7. FUNÇÃO PARA MOSTRAR TODOS OS ITENS
void listarItens() {
    system("cls");
    printf("=== SUA MOCHILA ===\n");
    if (total_itens == 0) {
        printf("Mochila vazia... voce precisa coletar itens rapido!\n");
    } else {
        for (int i = 0; i < total_itens; i++) {
            printf("%d. [%s] %s - Quantidade: %d\n", 
                   i+1, mochila[i].tipo, mochila[i].nome, mochila[i].quantidade);
        }
    }
}

// 8. FUNÇÃO PARA BUSCAR UM ITEM PELO NOME
void buscarItem() {
    if (total_itens == 0) {
        printf("Mochila vazia!\n");
        return;
    }

    char nome_busca[30];
    printf("\nDigite o nome do item que quer procurar: ");
    fgets(nome_busca, 30, stdin);
    nome_busca[strcspn(nome_busca, "\n")] = 0;

    int encontrado = 0;
    for (int i = 0; i < total_itens; i++) {
        if (strcmp(mochila[i].nome, nome_busca) == 0) {
            printf("\nITEM ENCONTRADO!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item nao encontrado!\n");
    }
}