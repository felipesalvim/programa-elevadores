#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// Definindo constantes para os tamanhos máximos
#define MAX_CLIENTES 100
#define TAM_NOME 100
#define TAM_ENDERECO 100
#define TAM_TELEFONE 100
#define TAM_EMAIL 100
#define TAM_VALOR 100

// Estrutura para armazenar informações de um cliente
typedef struct
{
    char nome[TAM_NOME];
    char endereco[TAM_ENDERECO];
    char telefone[TAM_TELEFONE];
    char email[TAM_EMAIL];
    char valor[TAM_VALOR];
} Cliente;

// Array para armazenar os clientes e uma variável para contar o total de clientes
Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

// Função para remover o caractere de nova linha após a entrada do usuário
void removerNovaLinha(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

// Função para salvar os dados dos clientes em um arquivo
void salvarDados()
{
    FILE *file = fopen("./clientes.dat", "wb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    fwrite(&totalClientes, sizeof(int), 1, file);
    fwrite(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

// Função para carregar os dados dos clientes de um arquivo
void carregarDados()
{
    FILE *file = fopen("./clientes.dat", "rb");
    if (file == NULL)
    {
        if (errno == ENOENT)
        {
            printf("Nenhum dado encontrado.\n");
        }
        else
        {
            printf("Erro ao abrir o arquivo para leitura.\n");
        }
        return;
    }
    fread(&totalClientes, sizeof(int), 1, file);
    fread(clientes, sizeof(Cliente), totalClientes, file);
    fclose(file);
}

// Função para validar o email
int validarEmail(char *email)
{
    int at = 0, dot = 0;
    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
            at++;
        if (email[i] == '.')
            dot++;
    }
    return (at == 1 && dot >= 1);
}

// Função para adicionar um novo cliente
void adicionarCliente()
{
    if (totalClientes >= MAX_CLIENTES)
    {
        printf("Limite de clientes atingido.\n\n");
        return;
    }
    Cliente novoCliente;
    printf("\n");
    printf("Nome: ");
    fgets(novoCliente.nome, TAM_NOME, stdin);
    removerNovaLinha(novoCliente.nome); // Remover '\n'

    printf("Endereco: ");
    fgets(novoCliente.endereco, TAM_ENDERECO, stdin);
    removerNovaLinha(novoCliente.endereco); // Remover '\n'

    printf("Telefone: ");
    fgets(novoCliente.telefone, TAM_TELEFONE, stdin);
    removerNovaLinha(novoCliente.telefone); // Remover '\n'

    do
    {
        printf("Email: ");
        fgets(novoCliente.email, TAM_EMAIL, stdin);
        removerNovaLinha(novoCliente.email); // Remover '\n'
        if (!validarEmail(novoCliente.email))
        {
            printf("Email invalido. Tente novamente.\n\n");
        }
    } while (!validarEmail(novoCliente.email));

    printf("Valor da manutencao mensal: ");
    fgets(novoCliente.valor, TAM_VALOR, stdin);
    removerNovaLinha(novoCliente.valor); // Remover '\n'

    clientes[totalClientes++] = novoCliente;
    salvarDados();
    printf("Cliente adicionado com sucesso!\n\n");
}

// Função para listar todos os clientes
void listarClientes()
{
    for (int i = 0; i < totalClientes; i++)
    {
        printf("Cliente %d:\n\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Endereco: %s\n", clientes[i].endereco);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Email: %s\n", clientes[i].email);
        printf("Valor manutencao mensal: %s\n\n", clientes[i].valor);
    }
}

// Função para buscar um cliente pelo nome
void buscarCliente()
{
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja buscar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    removerNovaLinha(nomeBusca); // Remover '\n'

    for (int i = 0; i < totalClientes; i++)
    {
        if (strstr(clientes[i].nome, nomeBusca) != NULL)
        {
            printf("\n");
            printf("Cliente encontrado:\n\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereco: %s\n", clientes[i].endereco);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("Email: %s\n", clientes[i].email);
            printf("Valor manutencao mensal: %s\n", clientes[i].valor);
            printf("\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n\n");
}

// Função para atualizar as informações de um cliente
void atualizarCliente()
{
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja atualizar: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    removerNovaLinha(nomeBusca); // Remover '\n'

    for (int i = 0; i < totalClientes; i++)
    {
        if (strstr(clientes[i].nome, nomeBusca) != NULL)
        {
            printf("Atualizando informacoes do cliente %s\n\n", clientes[i].nome);
            printf("Novo Endereco: ");
            fgets(clientes[i].endereco, TAM_ENDERECO, stdin);
            removerNovaLinha(clientes[i].endereco); // Remover '\n'

            printf("Novo Telefone: ");
            fgets(clientes[i].telefone, TAM_TELEFONE, stdin);
            removerNovaLinha(clientes[i].telefone); // Remover '\n'

            do
            {
                printf("Novo Email: ");
                fgets(clientes[i].email, TAM_EMAIL, stdin);
                removerNovaLinha(clientes[i].email); // Remover '\n'
                if (!validarEmail(clientes[i].email))
                {
                    printf("Email invalido. Tente novamente.\n");
                }
            } while (!validarEmail(clientes[i].email));
            salvarDados();
            printf("Informacoes atualizadas com sucesso!\n\n");
            return;
        }
    }
    printf("Cliente nao encontrado.\n\n");
}

// Função para excluir um cliente
void excluirCliente()
{
    char nomeBusca[TAM_NOME];
    printf("Digite o nome do cliente que deseja excluir: ");
    fgets(nomeBusca, TAM_NOME, stdin);
    removerNovaLinha(nomeBusca); // Remover '\n'

    for (int i = 0; i < totalClientes; i++)
    {
        if (strstr(clientes[i].nome, nomeBusca) != NULL)
        {
            for (int j = i; j < totalClientes - 1; j++)
            {
                clientes[j] = clientes[j + 1];
            }
            totalClientes--;
            salvarDados();
            printf("Cliente excluido com sucesso!\n\n");

            return;
        }
    }
    printf("Cliente nao encontrado.\n\n");
}

// Função para ordenar os clientes por nome
void ordenarClientes()
{
    Cliente temp;
    for (int i = 0; i < totalClientes - 1; i++)
    {
        for (int j = i + 1; j < totalClientes; j++)
        {
            if (strcmp(clientes[i].nome, clientes[j].nome) > 0)
            {
                temp = clientes[i];
                clientes[i] = clientes[j];
                clientes[j] = temp;
            }
        }
    }
    printf("Clientes ordenados pelo nome.\n");
    printf("Caso deseje verificar, selecione a opcao 2 (Listar Clientes), para conferir. \n\n");
}

// Função principal que exibe o menu e chama as funções apropriadas
int main()
{
    carregarDados();
    int opcao;
    do
    {
        printf("\n");
        printf("//////////////////////////////////////////\n");
        printf("==== SEJA BEM-VINDO AO SISTEMA ELEVA ====\n");
        printf("////////////////////////////////////////// \n\n");
        printf("Selecione uma das opcoes abaixo, basta digitar o numero correspondente: \n");
        
        printf("1. Adicionar Cliente\n");
        printf("2. Listar Clientes\n");
        printf("3. Buscar Cliente\n");
        printf("4. Atualizar Cliente\n");
        printf("5. Excluir Cliente\n");
        printf("6. Ordenar Clientes por Nome\n");
        printf("7. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao)
        {
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
            printf("Encerrando o programa. Te aguardo em breve.\n");
            break;
        default:
            printf("Opcao invalida.\n");
        }
    } while (opcao != 7);

    return 0;
}
