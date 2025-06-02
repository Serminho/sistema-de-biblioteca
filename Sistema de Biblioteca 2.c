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
    printf("|   Op��o    |        Descri��o            |\n");
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
    printf("Digite o t�tulo do livro: ");
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
        printf("N�o h� livros cadastrados.\n");
        return;
    }

    printf("| C�digo |          T�tulo        | Status |\n");
    printf("|--------|------------------------|--------|\n");

    for (i = 0; i < totalLivros; i++) {
        printf("|  %3d   | %-22s | %-6s |\n", biblioteca[i].codigo, biblioteca[i].titulo,
               biblioteca[i].disponivel ? "Disp." : "Emprest.");
    }
}

void listarDisponibilidade() {
	int i;
    printf("============================================\n");
    printf("|         LIVROS DISPON�VEIS               |\n");
    printf("============================================\n");
    int encontrados = 0;
    for (i = 0; i < totalLivros; i++) {
        if (biblioteca[i].disponivel) {
            printf("| C�digo: %d | T�tulo: %s | Autor: %s |\n", biblioteca[i].codigo, biblioteca[i].titulo, biblioteca[i].autor);
            encontrados = 1;
        }
    }
    if (!encontrados) {
        printf("Nenhum livro dispon�vel.\n");
    }

    printf("\n=============================================\n");
    printf("|         LIVROS INDISPON�VEIS              |\n");
    printf("=============================================\n");
    encontrados = 0;
    for (i = 0; i < totalLivros; i++) {
        if (!biblioteca[i].disponivel) {
            printf("| C�digo: %d | T�tulo: %s | Autor: %s |\n", biblioteca[i].codigo, biblioteca[i].titulo, biblioteca[i].autor);
            encontrados = 1;
        }
    }
    if (!encontrados) {
        printf("Nenhum livro emprestado.\n");
    }
}

void emprestarLivro() {
    printf("============================================\n");
    printf("|           EMPR�STIMO DE LIVRO            |\n");
    printf("============================================\n");

    if (totalLivros == 0) {
        printf("N�o h� livros cadastrados.\n");
        return;
    }

    listarDisponibilidade();

    int codigo;
    printf("\nDigite o c�digo do livro para emprestar: ");
    scanf("%d", &codigo);
    
    if (codigo < 1 || codigo > totalLivros) {
        printf("C�digo inv�lido!\n");
        return;
    }
    
    int index = codigo - 1;
    if (!biblioteca[index].disponivel) {
        printf("Livro j� est� emprestado!\n");
        return;
    }
    
    biblioteca[index].disponivel = 0;
    printf("Livro emprestado com sucesso!\n");
}

void devolverLivro() {
    printf("============================================\n");
    printf("|            DEVOLU��O DE LIVRO            |\n");
    printf("============================================\n");

    if (totalLivros == 0) {
        printf("N�o h� livros cadastrados.\n");
        return;
    }

    int codigo;
    printf("Digite o c�digo do livro: ");
    scanf("%d", &codigo);
    
    if (codigo < 1 || codigo > totalLivros) {
        printf("C�digo inv�lido!\n");
        return;
    }
    
    int index = codigo - 1;
    if (biblioteca[index].disponivel) {
        printf("Livro n�o est� emprestado!\n");
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
        printf("Escolha uma op��o: ");
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
                printf("Op��o inv�lida!\n");
                pausar();
        }
    } while (opcao != 0);
    
    return 0;
}