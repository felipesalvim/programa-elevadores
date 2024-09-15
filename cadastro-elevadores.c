#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definindo constantes para os tamanhos máximos
#define MAX_CLIENTES 100
#define TAM_NOME 100
#define TAM_ENDERECO 100
#define TAM_TELEFONE 100
#define TAM_EMAIL 100

// Estrutura para armazenar informações de um cliente
typedef struct {
    char nome[TAM_NOME];
    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
} Cliente;

// Array para armazenar os clientes e uma variável para contar o total de clientes
Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

// Função para salvar os dados dos clientes em um arquivo
void salvarDados() {
    FILE *file = fopen("./clientes.dat", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&totalClientes, sizeof(int), 1, file);
    fwrite(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

// Função para carregar os dados dos clientes de um arquivo
void carregarDados() {
    FILE *file = fopen("./clientes.dat", "rb");
    if (file == NULL) {
        printf("Nenhum dado encontrado.\n");
        return;
    }
    fread(&totalClientes, sizeof(int), 1, file);
    fread(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

// Função para validar o email
int validarEmail(char *email) {
    int at = 0, dot = 0;
    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') at++;
        if (email[i] == '.') dot++;
    }
    return (at == 1 && dot >= 1);
}

// Função para adicionar um novo cliente
void adicionarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }
    Cliente novoCliente;
    printf("Nome: ");
    fgets(novoCliente.nome, TAM_NOME, stdin);
    printf("Endereco: ");
    fgets(novoCliente.endereco, TAM_ENDERECO, stdin);
    printf("Telefone: ");
    fgets(novoCliente.telefone, TAM_TELEFONE, stdin);
    do {
        printf("Email: ");
        fgets(novoCliente.email, TAM_EMAIL, stdin);
        if (!validarEmail(novoCliente.email)) {
            printf("Email invalido. Tente novamente.\n");
        }
    } while (!validarEmail(novoCliente.email));

    clientes[totalClientes++] = novoCliente;
    salvarDados();
    printf("Cliente adicionado com sucesso!\n");
}

// Função para listar todos os clientes
void listarClientes() {
    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s", clientes[i].nome);
        printf("Endereco: %s", clientes[i].endereco);
        printf("Telefone: %s", clientes[i].telefone);
        printf("Email: %s", clientes[i].email);
        printf("\n");
    }
}

// Função para buscar um cliente pelo nome
void buscarCliente() {
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);

    for (int i = 0; i < totalClientes; i++) {
        if (strstr(clientes[i].nome, nomeBusca) != NULL) {
            printf("Cliente encontrado:\n");
            printf("Nome: %s", clientes[i].nome);
            printf("Endereco: %s", clientes[i].endereco);
            printf("Telefone: %s", clientes[i].telefone);
            printf("Email: %s", clientes[i].email);
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

// Função para atualizar as informações de um cliente
void atualizarCliente() {
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja atualizar: ");
    fgets(nomeBusca, TAM_NOME, stdin);

    for (int i = 0; i < totalClientes; i++) {
        if (strstr(clientes[i].nome, nomeBusca) != NULL) {
            printf("Atualizando informações do cliente %s\n", clientes[i].nome);
            printf("Novo Endereco: ");
            fgets(clientes[i].endereco, TAM_ENDERECO, stdin);
            printf("Novo Telefone: ");
            fgets(clientes[i].telefone, TAM_TELEFONE, stdin);
            do {
                printf("Novo Email: ");
                fgets(clientes[i].email, TAM_EMAIL, stdin);
                if (!validarEmail(clientes[i].email)) {
                    printf("Email invalido. Tente novamente.\n");
                }
            } while (!validarEmail(clientes[i].email));
            salvarDados();
            printf("Informações atualizadas com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

// Função para excluir um cliente
void excluirCliente() {
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja excluir: ");
    fgets(nomeBusca, TAM_NOME, stdin);

    for (int i = 0; i < totalClientes; i++) {
        if (strstr(clientes[i].nome, nomeBusca) != NULL) {
            for (int j = i; j < totalClientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            totalClientes--;
            salvarDados();
            printf("Cliente excluído com sucesso!\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n");
}

// Função para ordenar os clientes por nome
void ordenarClientes() {
    Cliente temp;
    for (int i = 0; i < totalClientes - 1; i++) {
        for (int j = i + 1; j < totalClientes; j++) {
            if (strcmp(clientes[i].nome, clientes[j].nome) > 0) {
                temp = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = temp;
            }
        }
    }
    printf("Clientes ordenados por nome.\n");
}

// Função principal que exibe o menu e chama as funções apropriadas
int main() {
    carregarDados();
    int opcao;
    do {
        printf("1. Adicionar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente\n");
        printf("4. Atualizar Cliente\n");
        printf("5. Excluir Cliente\n");
        printf("6. Ordenar Clientes por Nome\n");
        printf("7. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                adicionarCliente();
                break;
            case 2:
                listarClientes();
                break;
            case 3:
                buscarCliente();
                break;
            case 4:
                atualizarCliente();
                break;
            case 5:
                excluirCliente();
                break;
            case 6:
                ordenarClientes();
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 7);

    return 0;
}
