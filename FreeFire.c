#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} item;


typedef struct {
    item itens[MAX_ITENS];
    int quantidade;
} lista;


void iniciarLista(lista* lista);
void inserirItem(lista* mochila, item* item);
void removerItem(lista* mochila, char* nomeItem);
void buscarItem(lista* mochila, char* nomeItem);
void listarItens(lista* mochila);
void limparBufferEntrada();


int main() {
    int escolha;
    char nomeItem[30];
    lista* mochila = malloc(sizeof(lista));
    if(mochila == NULL){
        printf("Erro ao alocar memoria.\n");
        return -1;
    }
    iniciarLista(mochila);

    item* novoItem = malloc(sizeof(item));
    if(novoItem == NULL){
        printf("Erro ao alocar memoria.\n");
        return -1;
    }
    
    while(1){
        // Menu principal com opções:
        printf("Itens na mochila: %d/10\n", mochila->quantidade);
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\t1. Adicionar item a mochila\n");  // 1. Adicionar um item
        printf("\t2. Remover item da mochila\n");   // 2. Remover um item
        printf("\t3. Listar itens na mochila\n");   // 3. Listar todos os itens
        printf("\t4. Buscar item por nome\n");
        printf("\t0. Sair\n");                      // 0. Sair
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        printf("Digite uma das opcoes: ");
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch(escolha){  // A estrutura switch trata cada opção chamando a função correspondente.
            case 1:
                printf("--- Inserindo item ---\n");

                printf("Nome do item: ");
                fgets(novoItem->nome, 30, stdin);

                novoItem->nome[strcspn(novoItem->nome, "\n")] = 0;

                printf("Tipo do item (arma, municao, cura, etc.): ");
                fgets(novoItem->tipo, 20, stdin);

                novoItem->tipo[strcspn(novoItem->tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &novoItem->quantidade);

                inserirItem(mochila, novoItem);
                listarItens(mochila);
                break;
            case 2:
                printf("--- Removendo Item ---\n");

                printf("Digite o nome do item a ser removido: ");
                fgets(nomeItem, 30, stdin);
                nomeItem[strcspn(nomeItem, "\n")] = 0;

                removerItem(mochila, nomeItem);
                listarItens(mochila);
                break;
            case 3:
                listarItens(mochila);
                printf("\n\n\n\n");
                break;
            case 4:
                printf("--- Buscando Item na mochila---\n");

                printf("Digite o nome do item que deseja buscar: ");
                fgets(nomeItem, 30, stdin);
                nomeItem[strcspn(nomeItem, "\n")] = 0;

                buscarItem(mochila, nomeItem);
                break;
            case 0:
                return 0;
        }
    }
    free(mochila);
    free(novoItem);
    return 0;
}


void iniciarLista(lista* lista){
    lista->quantidade = 0;
}


void inserirItem(lista* mochila, item* item){
    if(mochila->quantidade == MAX_ITENS){
        printf("Mochila cheia. Nao e possivel adicionar mais itens.\n");
        return;
    }
    mochila->itens[mochila->quantidade] = *item;
    mochila->quantidade++;
    printf("Item '%s' adicionado com sucesso!\n", item->nome);
}


void removerItem(lista* mochila, char* nomeItem){
    int pos = -1;

    if(mochila->quantidade == 0){
        printf("Ainda nao ha itens na mochila. Nao e possivel remover.\n");
        return;
    }
    for(int i = 0; i < mochila->quantidade; i++){
        if(strcmp(mochila->itens[i].nome, nomeItem) == 0){
            pos = i;
        }
    }

    if(pos == -1){
        printf("Item nao encontrado na lista.\n");
        return;
    }

    for(int i = pos; i < mochila->quantidade-1; i++){
        mochila->itens[i] = mochila->itens[i+1];
    }
    mochila->quantidade--;
    printf("Item '%s' foi removido com sucesso.\n", nomeItem);
}


void buscarItem(lista* mochila, char* nomeItem){
    for(int i = 0; i < mochila->quantidade; i++){
        if(strcmp(mochila->itens[i].nome, nomeItem) == 0){
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila->itens[i].nome);
            printf("Tipo: %s\n", mochila->itens[i].tipo);
            printf("Quantidade: %d\n", mochila->itens[i].quantidade);
            printf("----------------------- \n");
            return;
        }
    }
    printf("Resultado: Item '%s' NAO foi encontrado na mochila.\n", nomeItem);
}


void listarItens(lista* mochila){
    printf("-=-=-=-=-=-=-=-=-=-=Itens na Mochila-=(%2d/10)=-=-=-=-=-=-=\n", mochila->quantidade);
    printf("NOME\t\t|TIPO\t\t|QUANTIDADE\n");
    for(int i = 0; i < mochila->quantidade; i++){
        printf("%s\t\t|%s\t\t|%d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade);
        
    }
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
