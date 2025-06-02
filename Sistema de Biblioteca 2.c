#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

#define MAX_LIVROS 100
#define MAX_TITULO 50
#define MAX_AUTOR 50

typedef struct {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int disponivel;
    int codigo;
} Livro;

Livro biblioteca[MAX_LIVROS];
int totalLivros = 0;

void pausar() {
    printf("\nPressione Enter para continuar...");
    getchar();
    getchar();
}

void limparTela() {
    system(CLEAR);
}

void exibirMenu() {
    printf("============================================\n");
    printf("|         SISTEMA DE BIBLIOTECA            |\n");
    printf("|------------------------------------------|\n");
    printf("|   Opção    |        Descrição            |\n");
    printf("|------------|-----------------------------|\n");
    printf("|     1      | Cadastrar livro             |\n");
    printf("|------------|-----------------------------|\n");
    printf("|     2      | Listar livros               |\n");
    printf("|------------|-----------------------------|\n");
    printf("|     3      | Emprestar livro             |\n");
    printf("|------------|-----------------------------|\n");
    printf("|     4      | Devolver livro              |\n");
    printf("|------------|-----------------------------|\n");
    printf("|     0      | Sair                        |\n");
    printf("|==========================================|\n");
}

void cadastrarLivro() {
    printf("============================================\n");
    printf("|          CADASTRAR NOVO LIVRO            |\n");
    printf("============================================\n");

    if (totalLivros >= MAX_LIVROS) {
        printf("Biblioteca cheia!\n");
        return;
    }

    Livro novoLivro;
    printf("Digite o título do livro: ");
    scanf(" %[^\n]", novoLivro.titulo);
    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", novoLivro.autor);
    
    novoLivro.disponivel = 1;
    novoLivro.codigo = totalLivros + 1;
    
    biblioteca[totalLivros] = novoLivro;
    totalLivros++;
    
    printf("Livro cadastrado com sucesso!\n");
}

void listarLivros() {
	int i;
    printf("============================================\n");
    printf("|            LISTA DE LIVROS               |\n");
    printf("============================================\n");

    if (totalLivros == 0) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    printf("| Código |          Título        | Status |\n");
    printf("|--------|------------------------|--------|\n");

    for (i = 0; i < totalLivros; i++) {
        printf("|  %3d   | %-22s | %-6s |\n", biblioteca[i].codigo, biblioteca[i].titulo,
               biblioteca[i].disponivel ? "Disp." : "Emprest.");
    }
}

void listarDisponibilidade() {
	int i;
    printf("============================================\n");
    printf("|         LIVROS DISPONÍVEIS               |\n");
    printf("============================================\n");
    int encontrados = 0;
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            printf("| Código: %d | Título: %s | Autor: %s |\n", biblioteca[i].codigo, biblioteca[i].titulo, biblioteca[i].autor);
            encontrados = 1;
        }
    }
    if (!encontrados) {
        printf("Nenhum livro disponível.\n");
    }

    printf("\n=============================================\n");
    printf("|         LIVROS INDISPONÍVEIS              |\n");
    printf("=============================================\n");
    encontrados = 0;
    for (i = 0; i < totalLivros; i++) {
        if (!biblioteca[i].disponivel) {
            printf("| Código: %d | Título: %s | Autor: %s |\n", biblioteca[i].codigo, biblioteca[i].titulo, biblioteca[i].autor);
            encontrados = 1;
        }
    }
    if (!encontrados) {
        printf("Nenhum livro emprestado.\n");
    }
}

void emprestarLivro() {
    printf("============================================\n");
    printf("|           EMPRÉSTIMO DE LIVRO            |\n");
    printf("============================================\n");

    if (totalLivros == 0) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    listarDisponibilidade();

    int codigo;
    printf("\nDigite o código do livro para emprestar: ");
    scanf("%d", &codigo);
    
    if (codigo < 1 || codigo > totalLivros) {
        printf("Código inválido!\n");
        return;
    }
    
    int index = codigo - 1;
    if (!biblioteca[index].disponivel) {
        printf("Livro já está emprestado!\n");
        return;
    }
    
    biblioteca[index].disponivel = 0;
    printf("Livro emprestado com sucesso!\n");
}

void devolverLivro() {
    printf("============================================\n");
    printf("|            DEVOLUÇÃO DE LIVRO            |\n");
    printf("============================================\n");

    if (totalLivros == 0) {
        printf("Não há livros cadastrados.\n");
        return;
    }

    int codigo;
    printf("Digite o código do livro: ");
    scanf("%d", &codigo);
    
    if (codigo < 1 || codigo > totalLivros) {
        printf("Código inválido!\n");
        return;
    }
    
    int index = codigo - 1;
    if (biblioteca[index].disponivel) {
        printf("Livro não está emprestado!\n");
        return;
    }
    
    biblioteca[index].disponivel = 1;
    printf("Livro devolvido com sucesso!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int opcao;
    
    do {
        limparTela();
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        limparTela();

        switch (opcao) {
            case 1:
                cadastrarLivro();
                pausar();
                break;
            case 2:
                listarLivros();
                pausar();
                break;
            case 3:
                emprestarLivro();
                pausar();
                break;
            case 4:
                devolverLivro();
                pausar();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                pausar();
        }
    } while (opcao != 0);
    
    return 0;
}