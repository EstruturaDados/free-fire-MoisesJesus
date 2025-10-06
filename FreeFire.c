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
    int prioridade;
} item;


typedef struct {
    item itens[MAX_ITENS];
    int quantidade;
} lista;


void iniciarLista(lista* lista);
void inserirItem(lista* mochila, item* item);
void removerItem(lista* mochila, char* nomeItem);
int ordenarPorNome(lista* mochila);
int ordenarPorTipo(lista* mochila);
int ordenarPorPrioridade(lista* mochila);
void buscarItem(lista* mochila, char* nomeItem);
int buscaBinaria(lista* mochila, char* nomeItem);
void listarItens(lista* mochila);
void limparBufferEntrada();


int main() {
    int ordenadoPorNome = 0;
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
        printf("\n\nItens na mochila: %d/10\n", mochila->quantidade);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("1. Adicionar Componente\n");                          // 1. Adicionar um item
        printf("2. Remover Componente\n");                            // 2. Remover um item
        printf("3. Listar Componentes (Inventario)\n");               // 3. Listar todos os itens
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA\n");                          // 0. Sair
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        limparBufferEntrada();

        switch(escolha){  // A estrutura switch trata cada opção chamando a função correspondente.
            case 1:
                printf("\n\n--- Coletando Novo Componente ---\n");

                printf("Nome: ");
                fgets(novoItem->nome, 30, stdin);

                novoItem->nome[strcspn(novoItem->nome, "\n")] = 0;

                printf("Tipo (Estrutural, Eletronico, Energia): ");
                fgets(novoItem->tipo, 20, stdin);

                novoItem->tipo[strcspn(novoItem->tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &novoItem->quantidade);
                limparBufferEntrada();

                printf("Priodidade de Montagem (1-5): ");
                scanf("%d", &novoItem->prioridade);
                limparBufferEntrada();

                inserirItem(mochila, novoItem);
                ordenadoPorNome = 0;
                listarItens(mochila);
                break;
            case 2:
                printf("\n\n--- Removendo Item ---\n");

                printf("Digite o nome do item a ser removido: ");
                fgets(nomeItem, 30, stdin);
                nomeItem[strcspn(nomeItem, "\n")] = 0;

                removerItem(mochila, nomeItem);
                listarItens(mochila);
                break;
            case 3:
                listarItens(mochila);
                break;
            case 4:
                printf("\n--- Estrategia de Organizacao ---\n");
                printf("Como deseja ordenar seus componentes?\n");
                printf("1. Por Nome (Ordem alfabetica)\n");
                printf("2. Por Tipo\n");
                printf("3. Por Prioridade de Montagem\n");
                printf("0. Cancelar\n");
                int criterio;
                printf("Escolha o criterio: ");
                scanf("%d", &criterio);
                limparBufferEntrada();
                int n = 0;
                switch (criterio){
                    case 1:
                        n = ordenarPorNome(mochila);
                        ordenadoPorNome = 1;
                        printf("Mochila organizada por NOME.\n");
                        break;
                    case 2:
                        n = ordenarPorTipo(mochila);
                        ordenadoPorNome = 0;
                        printf("Mochila organizada por TIPO.\n");
                        break;
                    case 3:
                        n = ordenarPorPrioridade(mochila);
                        ordenadoPorNome = 0;
                        printf("Mochila organizada por PRIORIDADE.\n");
                        break;
                    default:
                        break;
                }
                if(n != 0){
                    printf("Analise de Desenpenho: Foram Necessarias %d Comparacoes.\n", n);
                    listarItens(mochila);
                }
                break;
            case 5:
                if(!ordenadoPorNome){
                    printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
                    printf("Use a opcao  para organizar a mochila primeiro.\n");
                    break;
                }
                printf("\n\n--- Busca Binaria por Componente-Chave ---\n");

                printf("Nome do componente a buscar: ");
                fgets(nomeItem, 30, stdin);
                nomeItem[strcspn(nomeItem, "\n")] = 0;
                int indice;
                indice = buscaBinaria(mochila, nomeItem);
                if(indice == -1){
                    printf("\nComponente-chave nao encontrado na mochila.\n");
                }
                else{
                    printf("\n--- Componente-Chave Encontrado! ---\n");
                    printf("Nome: %s\n", mochila->itens[indice].nome);
                    printf("Tipo: %s\n", mochila->itens[indice].tipo);
                    printf("Quantidade: %d\n", mochila->itens[indice].quantidade);
                    printf("Prioridade: %d\n", mochila->itens[indice].prioridade);
                    printf("------------------------\n");
                }

                break;
            case 0:
                return 0;
        }
        printf("\n\nPressione Enter para continuar...");
        getchar();
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
        printf("\nMochila cheia. Nao e possivel adicionar mais itens.\n");
        return;
    }
    mochila->itens[mochila->quantidade] = *item;
    mochila->quantidade++;
    printf("\nItem '%s' adicionado com sucesso!\n", item->nome);
}


void removerItem(lista* mochila, char* nomeItem){
    int pos = -1;

    if(mochila->quantidade == 0){
        printf("\nAinda nao ha itens na mochila. Nao e possivel remover.\n");
        return;
    }
    for(int i = 0; i < mochila->quantidade; i++){
        if(strcmp(mochila->itens[i].nome, nomeItem) == 0){
            pos = i;
        }
    }

    if(pos == -1){
        printf("\nItem nao encontrado na lista.\n");
        return;
    }

    for(int i = pos; i < mochila->quantidade-1; i++){
        mochila->itens[i] = mochila->itens[i+1];
    }
    mochila->quantidade--;
    printf("\nItem '%s' foi removido com sucesso.\n", nomeItem);
}


int ordenarPorNome(lista* mochila){
    //ordenação por bubble sort
    int troca = 0;
    int c = 0;
    for(int i = 0; i < mochila->quantidade - 1; i++){
        for(int j = 0; j < mochila->quantidade - i - 1; j++){
            if(strcmp(mochila->itens[j].nome, mochila->itens[j + 1].nome) > 0){
                c++;
                item* temp = malloc(sizeof(item));
                *temp = mochila->itens[j];
                mochila->itens[j] = mochila->itens[j + 1];
                mochila->itens[j + 1] = *temp;
                free(temp);
                troca = 1;
            }
        }
        if(troca == 0){
            break;
        }
    }
    return c;
}


int ordenarPorTipo(lista* mochila){
    //Ordenação por insertion sort
    int c = 0;
    for(int i = 1; i < mochila->quantidade; i++){
        item chave = mochila->itens[i];
        int j = i - 1;

        while(j >= 0 && strcmp(mochila->itens[j].tipo, chave.tipo) > 0){
            c++;
            mochila->itens[j + 1] = mochila->itens[j];
            j--;
        }
        mochila->itens[j + 1] = chave;
    }
    return c;
}


int ordenarPorPrioridade(lista* mochila){
    //Ordenação por selection sort
    int c = 0;
    int maiorIndice = 0;
    for(int i = 0; i < mochila->quantidade-1; i++){
        for(int j = i + 1; j < mochila->quantidade; j++){
            if(mochila->itens[j].prioridade > mochila->itens[maiorIndice].prioridade){
                c++;
                maiorIndice = j;
            }
        }
        if(maiorIndice != i){
            item* temp = malloc(sizeof(item));
            *temp = mochila->itens[i];
            mochila->itens[i] = mochila->itens[maiorIndice];
            mochila->itens[maiorIndice] = *temp;
            free(temp);
        }
    }
    return c;
}


void buscarItem(lista* mochila, char* nomeItem){
    for(int i = 0; i < mochila->quantidade; i++){
        if(strcmp(mochila->itens[i].nome, nomeItem) == 0){
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila->itens[i].nome);
            printf("Tipo: %s\n", mochila->itens[i].tipo);
            printf("Quantidade: %d\n", mochila->itens[i].quantidade);
            printf("Prioridade: %d\n", mochila->itens[i].prioridade);
            printf("------------------------\n");
            return;
        }
    }
    printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n", nomeItem);
}


int buscaBinaria(lista* mochila, char* nomeItem){
    int inicio = 0;
    int fim = mochila->quantidade - 1;
    int meio = (inicio + fim) / 2;
    while(inicio <= fim){
        if(strcmp(mochila->itens[meio].nome, nomeItem) == 0){
            return meio;
        }
        if(strcmp(mochila->itens[meio].nome, nomeItem) > 0){
            fim = meio - 1;
            meio = (inicio + fim) / 2;
        }
        
        else{
            inicio = meio + 1;
            meio = (inicio + fim) / 2;
        }
    }
    return -1;
}


void listarItens(lista* mochila){
    printf("\n\n-=-=-=-=-=-=-=-=-=-=Itens na Mochila-=(%2d/10)=-=-=-=-=-=-=\n", mochila->quantidade);
    printf("NOME\t\t|TIPO\t\t|QUANTIDADE\t|PRIORIDADE\n");
    for(int i = 0; i < mochila->quantidade; i++){
        printf("%s\t|%s\t|%d\t\t|%d\n", mochila->itens[i].nome, mochila->itens[i].tipo, mochila->itens[i].quantidade, mochila->itens[i].prioridade);
        
    }
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}


void limparBufferEntrada(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
