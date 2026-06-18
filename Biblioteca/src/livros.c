#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/livros.h"
#include "../include/util.h"
#include "../include/usuarios.h"
#include "../include/emprestimos.h"

Livro *livros = NULL;
int totalLivros = 0;
int proximoCodigo = 1;

int buscarCodigoLivro(int codigo)
{
    for(int i = 0; i < totalLivros; i++)
    {
        if(livros[i].codigo == codigo)
        {
            return i;
        }
    }

    return -1;
}

void cadastrarLivro()
{
    Livro novo;

    novo.codigo = proximoCodigo++;

    getchar();

    printf("Titulo: ");
    lerTitulo(novo.titulo, 100);

    printf("Autor: ");
    lerTexto(novo.autor, 100);

    printf("Ano: ");
    novo.ano = lerNumero();

    printf("Genero: ");
    lerTexto(novo.genero, 50);

    printf("Quantidade total: ");
    novo.qtd_total = lerNumero();

    novo.qtd_disponivel = novo.qtd_total;
    novo.total_emprestimos = 0;

    Livro *temp = realloc(
        livros,
        (totalLivros + 1) * sizeof(Livro)
    );

    if(temp == NULL)
    {
        printf("Erro de memoria\n");
        pausar();
        return;
    }

    livros = temp;
    livros[totalLivros] = novo;
    totalLivros++;

    printf("\nLivro cadastrado com sucesso!\n");

    pausar();
}

void listarLivros()
{
    if(totalLivros == 0)
    {
        printf("\nNenhum livro cadastrado.\n");
        pausar();
        return;
    }

    printf("\n===== ACERVO =====\n");

    for(int i = 0; i < totalLivros; i++)
    {
        printf("\nCodigo: %d\n", livros[i].codigo);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Ano: %d\n", livros[i].ano);
        printf("Genero: %s\n", livros[i].genero);
        printf("Disponiveis: %d/%d\n",
               livros[i].qtd_disponivel,
               livros[i].qtd_total);

        printf("--------------------------\n");
    }

    pausar();
}

void mostrarUsuariosLivro(int codigo)
{
    int achou = 0;

    printf("\n===== USUARIOS COM ESTE LIVRO =====\n");

    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(
            emprestimos[i].codigoLivro == codigo &&
            emprestimos[i].devolvido == 0
        )
        {
            int pos = buscarMatricula(
                emprestimos[i].matriculaUsuario
            );

            if(pos != -1)
            {
                printf("\nMatricula: %d\n",
                       usuarios[pos].matricula);

                printf("Nome: %s\n",
                       usuarios[pos].nome);

                printf("Curso: %s\n",
                       usuarios[pos].curso);

                achou = 1;
            }
        }
    }

    if(!achou)
    {
        printf("Nenhum usuario possui esse livro emprestado.\n");
    }
}

void buscarLivro(int codigo)
{
    int pos = buscarCodigoLivro(codigo);

    if(pos == -1)
    {
        printf("Livro nao encontrado.\n");
        pausar();
        return;
    }

    printf("\n===== LIVRO =====\n");

    printf("Codigo: %d\n",
           livros[pos].codigo);

    printf("Titulo: %s\n",
           livros[pos].titulo);

    printf("Autor: %s\n",
           livros[pos].autor);

    printf("Ano: %d\n",
           livros[pos].ano);

    printf("Genero: %s\n",
           livros[pos].genero);

    printf("Disponiveis: %d/%d\n",
           livros[pos].qtd_disponivel,
           livros[pos].qtd_total);

    mostrarUsuariosLivro(
        livros[pos].codigo
    );

    pausar();
}

void atualizarLivro()
{
    int codigo;

    printf("Codigo do livro: ");
    codigo = lerNumero();

    int pos = buscarCodigoLivro(codigo);

    if(pos == -1)
    {
        printf("Livro nao encontrado.\n");
        pausar();
        return;
    }

    getchar();

    printf("Novo titulo: ");
    lerTitulo(
        livros[pos].titulo,
        100
    );

    printf("Novo autor: ");
    lerTexto(
        livros[pos].autor,
        100
    );

    printf("Novo ano: ");
    livros[pos].ano = lerNumero();

    printf("Novo genero: ");
    lerTexto(
        livros[pos].genero,
        50
    );

    printf("Nova quantidade total: ");
    livros[pos].qtd_total = lerNumero();

    printf("Nova quantidade disponivel: ");
    livros[pos].qtd_disponivel = lerNumero();

    printf("\nLivro atualizado!\n");

    pausar();
}

void removerLivro()
{
    int codigo;

    printf("Codigo do livro: ");
    codigo = lerNumero();

    int pos = buscarCodigoLivro(codigo);

    if(pos == -1)
    {
        printf("Livro nao encontrado.\n");
        pausar();
        return;
    }

    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(
            emprestimos[i].codigoLivro == codigo &&
            emprestimos[i].devolvido == 0
        )
        {
            printf(
                "Nao e possivel remover.\n"
                "Existem emprestimos em aberto.\n"
            );

            pausar();
            return;
        }
    }

    for(int i = pos; i < totalLivros - 1; i++)
    {
        livros[i] = livros[i + 1];
    }

    totalLivros--;

    if(totalLivros == 0)
    {
        free(livros);
        livros = NULL;
    }
    else
    {
        Livro *temp = realloc(
            livros,
            totalLivros * sizeof(Livro)
        );

        if(temp != NULL)
        {
            livros = temp;
        }
    }

    printf("Livro removido com sucesso!\n");

    pausar();
}

void menuLivros()
{
    int op;

    do
    {
        printf("\n===== LIVROS =====\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Atualizar\n");
        printf("5 - Remover\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        op = lerNumero();

        switch(op)
        {
            case 1:
                cadastrarLivro();
                break;

            case 2:
                listarLivros();
                break;

            case 3:
            {
                int codigo;

                printf("Codigo do livro: ");
                codigo = lerNumero();

                buscarLivro(codigo);
                break;
            }

            case 4:
                atualizarLivro();
                break;

            case 5:
                removerLivro();
                break;
        }

    } while(op != 0);
}