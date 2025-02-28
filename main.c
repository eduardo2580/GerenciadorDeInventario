#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define a estrutura de dados para armazenar informa��es de cada item do invent�rio
// Cada item possui um identificador �nico, nome, quantidade em estoque, pre�o unit�rio,
// data de validade e categoria do produto
typedef struct {
    int id;
    char nome[100];        // Nome do produto com at� 100 caracteres
    int quantidade;        // Quantidade dispon�vel em estoque
    float preco;          // Pre�o unit�rio do produto
    char dataDeValidade[11]; // Data de validade no formato dd/mm/aaaa
    char categoria[50];    // Categoria do produto com at� 50 caracteres
} Item;

// Fun��o respons�vel por adicionar um novo item ao invent�rio
// Par�metros:
// - itens: ponteiro para o array de itens
// - contador: n�mero atual de itens no invent�rio
// - capacidade: capacidade m�xima atual do array
void adicionarItem(Item **itens, int *contador, int *capacidade) {
    // Verifica se � necess�rio aumentar a capacidade do array
    if (*contador == *capacidade) {
        *capacidade *= 2;  // Dobra a capacidade do array
        *itens = (Item*)realloc(*itens, *capacidade * sizeof(Item));
        if (*itens == NULL) {
            printf("Erro ao alocar memoria!\n");
            exit(1);
        }
    }

    // Solicita e valida o ID do novo item
    printf("Digite o ID: ");
    while (scanf("%d", &(*itens)[*contador].id) != 1) {
        printf("Entrada invalida. Digite o ID novamente: ");
        while (getchar() != '\n');
    }

    // Solicita o nome do item
    printf("Digite o Nome: ");
    scanf(" %[^\n]", (*itens)[*contador].nome);

    // Solicita e valida a quantidade
    printf("Digite a Quantidade: ");
    while (scanf("%d", &(*itens)[*contador].quantidade) != 1) {
        printf("Entrada invalida. Digite a Quantidade novamente: ");
        while (getchar() != '\n');
    }

    // Solicita e valida o pre�o
    printf("Digite o Preco: ");
    while (scanf("%f", &(*itens)[*contador].preco) != 1) {
        printf("Entrada invalida. Digite o Preco novamente: ");
        while (getchar() != '\n');
    }

    // Solicita a data de validade
    printf("Digite a Data de Validade (dd/mm/aaaa): ");
    scanf(" %[^\n]", (*itens)[*contador].dataDeValidade);

    // Solicita a categoria
    printf("Digite a Categoria: ");
    scanf(" %[^\n]", (*itens)[*contador].categoria);

    // Incrementa o contador de itens e exibe mensagem de sucesso
    (*contador)++;
    printf("Item adicionado com sucesso!\n");
}

// Fun��o para exibir todos os itens cadastrados no invent�rio
// Par�metros:
// - itens: array de itens
// - contador: n�mero atual de itens no invent�rio
void listarItens(Item *itens, int contador) {
    if (contador == 0) {
        printf("\nNenhum item registrado.\n");
    } else {
        // Exibe cabe�alho da tabela
        printf("\n%-5s %-30s %-10s %-10s %-12s %-20s\n", "ID", "Nome", "Quantidade", "Preco", "Validade", "Categoria");
        printf("-------------------------------------------------------------------------------------\n");
        // Lista todos os itens formatados em tabela
        for (int i = 0; i < contador; i++) {
            printf("%-5d %-30s %-10d %-10.2f %-12s %-20s\n",
                itens[i].id, itens[i].nome, itens[i].quantidade, itens[i].preco, itens[i].dataDeValidade, itens[i].categoria);
        }
    }
}

// Fun��o para editar um item existente no invent�rio
// Par�metros:
// - itens: array de itens
// - contador: n�mero atual de itens
// - id: identificador do item a ser editado
void editarItem(Item *itens, int contador, int id) {
    // Procura o item pelo ID
    for (int i = 0; i < contador; i++) {
        if (itens[i].id == id) {
            // Solicita novos dados para o item
            printf("Digite o novo Nome: ");
            scanf(" %[^\n]", itens[i].nome);

            printf("Digite a nova Quantidade: ");
            while (scanf("%d", &itens[i].quantidade) != 1) {
                printf("Entrada invalida. Digite a nova Quantidade novamente: ");
                while (getchar() != '\n');
            }

            printf("Digite o novo Preco: ");
            while (scanf("%f", &itens[i].preco) != 1) {
                printf("Entrada invalida. Digite o novo Pre�o novamente: ");
                while (getchar() != '\n');
            }

            printf("Digite a nova Data de Validade (dd/mm/aaaa): ");
            scanf(" %[^\n]", itens[i].dataDeValidade);

            printf("Digite a nova Categoria: ");
            scanf(" %[^\n]", itens[i].categoria);

            printf("Item atualizado com sucesso!\n");
            return;
        }
    }
    printf("Item com ID %d nao encontrado.\n", id);
}

// Fun��o para excluir um item do invent�rio
// Par�metros:
// - itens: array de itens
// - contador: ponteiro para o n�mero atual de itens
// - id: identificador do item a ser exclu�do
void excluirItem(Item *itens, int *contador, int id) {
    int i;
    // Procura o item pelo ID
    for (i = 0; i < *contador; i++) {
        if (itens[i].id == id) {
            break;
        }
    }

    // Se encontrou o item, realiza a exclus�o
    if (i < *contador) {
        // Move todos os itens posteriores uma posi��o para tr�s
        for (int j = i; j < *contador - 1; j++) {
            itens[j] = itens[j + 1];
        }
        (*contador)--;
        printf("Item excluido com sucesso.\n");
    } else {
        printf("Item com ID %d nao encontrado.\n", id);
    }
}

// Fun��o para salvar os dados do invent�rio em arquivo bin�rio
// Par�metros:
// - itens: array de itens
// - contador: n�mero atual de itens
void salvarDados(Item *itens, int contador) {
    FILE *arquivo = fopen("inventario.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }
    // Salva o contador e todos os itens no arquivo
    fwrite(&contador, sizeof(int), 1, arquivo);
    fwrite(itens, sizeof(Item), contador, arquivo);
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// Fun��o para carregar os dados do invent�rio do arquivo bin�rio
// Par�metros:
// - itens: ponteiro para o array de itens
// - contador: ponteiro para o n�mero de itens
// - capacidade: ponteiro para a capacidade do array
void carregarDados(Item **itens, int *contador, int *capacidade) {
    FILE *arquivo = fopen("inventario.bin", "rb");
    if (arquivo == NULL) {
        printf("Nenhum dado para carregar ou erro ao abrir o arquivo!\n");
        return;
    }
    // L� o contador do arquivo
    fread(contador, sizeof(int), 1, arquivo);
    // Aloca mem�ria necess�ria
    *capacidade = *contador > 0 ? *contador : 100;
    *itens = (Item*)malloc(*capacidade * sizeof(Item));
    if (*itens == NULL) {
        printf("Erro ao alocar memoria!\n");
        fclose(arquivo);
        exit(1);
    }
    // L� todos os itens do arquivo
    fread(*itens, sizeof(Item), *contador, arquivo);
    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}

// Fun��o para exibir o cabe�alho do programa
void exibirCabecalho() {
    printf("\n==================================\n");
    printf("   SISTEMA DE GESTAO DE ESTOQUE   \n");
    printf("==================================\n");
}

// Fun��o para exibir o menu principal com as opera��es dispon�veis
void exibirMenu() {
    printf("\nOPERACOES DISPONIVEIS:\n");
    printf("------------------------\n");
    printf("[A] Adicionar novo item\n");
    printf("[L] Listar todos os itens\n");
    printf("[E] Editar item existente\n");
    printf("[R] Remover item do estoque\n");
    printf("[S] Salvar e encerrar\n");
    printf("------------------------\n");
    printf("Digite a letra da operacao desejada: ");
}

// Fun��o para obter e normalizar a escolha do usu�rio
char obterEscolha() {
    char escolha;
    scanf(" %c", &escolha);
    return toupper(escolha);
}

// Fun��o principal do programa
int main() {
    // Inicializa��o das vari�veis principais
    int capacidade = 100;  // Capacidade inicial do array
    Item *itens = NULL;    // Array din�mico de itens
    int contador = 0;      // Contador de itens atual

    // Carrega dados salvos anteriormente
    carregarDados(&itens, &contador, &capacidade);

    // Loop principal do programa
    char escolha;
    do {
        exibirCabecalho();
        exibirMenu();
        escolha = obterEscolha();

        // Processa a escolha do usu�rio
        switch(escolha) {
            case 'A':
                printf("\n--- ADICIONANDO NOVO ITEM ---\n");
                adicionarItem(&itens, &contador, &capacidade);
                break;
            case 'L':
                printf("\n--- LISTAGEM DE ITENS ---\n");
                listarItens(itens, contador);
                break;
            case 'E': {
                int id;
                printf("\n--- EDITANDO ITEM ---\n");
                printf("Informe o ID do item a ser editado: ");
                while (scanf("%d", &id) != 1) {
                    printf("Entrada invalida. Informe o ID novamente: ");
                    while (getchar() != '\n');
                }
                editarItem(itens, contador, id);
                break;
            }
            case 'R': {
                int id;
                printf("\n--- REMOVENDO ITEM ---\n");
                printf("Informe o ID do item a ser removido: ");
                while (scanf("%d", &id) != 1) {
                    printf("Entrada invalida. Informe o ID novamente: ");
                    while (getchar() != '\n');
                }
                excluirItem(itens, &contador, id);
                break;
            }
            case 'S':
                printf("\nSalvando dados e encerrando o programa...\n");
                salvarDados(itens, contador);
                break;
            default:
                printf("\nOpcao invalida! Por favor, escolha uma operacao valida.\n");
        }

        // Pausa para o usu�rio ler as mensagens
        if (escolha != 'S') {
            printf("\nPressione Enter para continuar...");
            while (getchar() != '\n');
            getchar();
        }

    } while(escolha != 'S');

    // Libera a mem�ria alocada antes de encerrar
    free(itens);
    return 0;
}
