#include <stdio.h>
#include <time.h>

#include "../include/relatorio.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/util.h"

void trocar(Livro *a, Livro *b)
{
    Livro aux = *a;
    *a = *b;
    *b = aux;
}

void ordenarLivros()
{
    for(int i = 0; i < totalLivros - 1; i++)
    {
        for(int j = 0; j < totalLivros - i - 1; j++)
        {
            if(
                livros[j].total_emprestimos <
                livros[j + 1].total_emprestimos
            )
            {
                trocar(
                    &livros[j],
                    &livros[j + 1]
                );
            }
        }
    }
}

void relatorioLivrosMaisEmprestados()
{
    FILE *arq = fopen("reports/livros_mais_emprestados.txt", "w");

    if(arq == NULL)
    {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    if(totalLivros == 0)
    {
        printf("Nenhum livro cadastrado\n");
        fprintf(arq, "Nenhum livro cadastrado\n");
        fclose(arq);
        return;
    }

    // 1. contar apenas livros com empréstimos
    int qtdValidos = 0;

    for(int i = 0; i < totalLivros; i++)
    {
        if(livros[i].total_emprestimos > 0)
        {
            qtdValidos++;
        }
    }

    if(qtdValidos == 0)
    {
        printf("Nenhum livro foi emprestado ainda\n");
        fprintf(arq, "Nenhum livro foi emprestado ainda\n");
        fclose(arq);
        return;
    }

    // 2. calcular limite (metade dos válidos)
    int limite = qtdValidos / 2;

    if(limite < 1)
    {
        limite = 1;
    }

    // 3. ordenar por empréstimos 
    ordenarLivros();

    // 4. imprimir apenas os válidos
    printf("\n===== LIVROS MAIS EMPRESTADOS =====\n");
    fprintf(arq, "\n===== LIVROS MAIS EMPRESTADOS =====\n");

    int contador = 0;

    for(int i = 0; i < totalLivros && contador < limite; i++)
    {
        if(livros[i].total_emprestimos > 0)
        {
            printf("=====================================\n");
            printf("\nCodigo: %d\n", livros[i].codigo);
            printf("Titulo: %s\n", livros[i].titulo);
            printf("Emprestimos: %d\n", livros[i].total_emprestimos);

            fprintf(arq, "=====================================\n");
            fprintf(arq, "\nCodigo: %d\n", livros[i].codigo);
            fprintf(arq, "Titulo: %s\n", livros[i].titulo);
            fprintf(arq, "Emprestimos: %d\n", livros[i].total_emprestimos);

            contador++;
        }
    }

    fclose(arq);
}

void relatorioAcervoDisponivel()
{
    FILE *arq = fopen(
        "reports/acervo_disponivel.txt",
        "w"
    );

    if(arq == NULL)
    {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    int achou = 0;

    printf("\n===== ACERVO DISPONIVEL =====\n");
    fprintf(arq,"\n===== ACERVO DISPONIVEL =====\n");

    for(int i = 0; i < totalLivros; i++)
    {
        if(livros[i].qtd_disponivel > 0)
        {
            printf("\nCodigo: %d\n",
                   livros[i].codigo);

            printf("Titulo: %s\n",
                   livros[i].titulo);

            printf("Disponiveis: %d/%d\n",
                   livros[i].qtd_disponivel,
                   livros[i].qtd_total);

            fprintf(arq,
                    "\nCodigo: %d\n",
                    livros[i].codigo);

            fprintf(arq,
                    "Titulo: %s\n",
                    livros[i].titulo);

            fprintf(arq,
                    "Disponiveis: %d/%d\n",
                    livros[i].qtd_disponivel,
                    livros[i].qtd_total);

            achou = 1;
        }
    }

    if(!achou)
    {
        printf("Nenhum livro disponivel\n");
        fprintf(arq,
                "Nenhum livro disponivel\n");
    }

    fclose(arq);
}

void relatorioAtrasados()
{
    FILE *arq = fopen(
        "reports/usuarios_atrasados.txt",
        "w"
    );

    if(arq == NULL)
    {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    time_t agora = time(NULL);
    struct tm *hoje = localtime(&agora);

    int achou = 0;

    printf("\n===== USUARIOS ATRASADOS =====\n");
    fprintf(arq,
            "\n===== USUARIOS ATRASADOS =====\n");

    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(emprestimos[i].devolvido == 0)
        {
            Data data =
                emprestimos[i].prevista;

            int atrasado = 0;

            if(data.ano < hoje->tm_year + 1900)
            {
                atrasado = 1;
            }
            else if(
                data.ano ==
                hoje->tm_year + 1900 &&
                data.mes <
                hoje->tm_mon + 1
            )
            {
                atrasado = 1;
            }
            else if(
                data.ano ==
                hoje->tm_year + 1900 &&
                data.mes ==
                hoje->tm_mon + 1 &&
                data.dia <
                hoje->tm_mday
            )
            {
                atrasado = 1;
            }

            if(atrasado)
            {
                int u =
                    buscarMatricula(
                        emprestimos[i].matriculaUsuario
                    );

                int l =
                    buscarCodigoLivro(
                        emprestimos[i].codigoLivro
                    );

                if(u != -1 && l != -1)
                {
                    printf("\nUsuario: %s\n",
                           usuarios[u].nome);

                    printf("Livro: %s\n",
                           livros[l].titulo);

                    printf(
                        "Data prevista: %02d/%02d/%d\n",
                        data.dia,
                        data.mes,
                        data.ano
                    );

                    fprintf(arq,
                            "\nUsuario: %s\n",
                            usuarios[u].nome);

                    fprintf(arq,
                            "Livro: %s\n",
                            livros[l].titulo);

                    fprintf(arq,
                            "Data prevista: %02d/%02d/%d\n",
                            data.dia,
                            data.mes,
                            data.ano);

                    achou = 1;
                }
            }
        }
    }

    if(!achou)
    {
        printf("Nenhum usuario atrasado\n");
        fprintf(arq,
                "Nenhum usuario atrasado\n");
    }

    fclose(arq);
}

void relatorioHistoricoUsuario()
{
    FILE *arq = fopen(
        "reports/historico_usuario.txt",
        "w"
    );

    if(arq == NULL)
    {
        printf("Erro ao gerar relatorio.\n");
        return;
    }

    int mat;

    printf("Matricula: ");
    mat = lerNumero();

    int u =
        buscarMatricula(mat);

    if(u == -1)
    {
        printf("Usuario nao encontrado\n");
        fprintf(arq,
                "Usuario nao encontrado\n");
        fclose(arq);
        return;
    }

    printf("\n===== HISTORICO =====\n");
    fprintf(arq,
            "\n===== HISTORICO =====\n");

    printf("Matricula: %d\n",
           usuarios[u].matricula);
        
    printf("Nome: %s\n",
           usuarios[u].nome);

    printf("Curso: %s\n",
           usuarios[u].curso);

    fprintf(arq,
            "Matricula: %d\n",
            usuarios[u].matricula);
    fprintf(arq,
            "Nome: %s\n",
            usuarios[u].nome);

    fprintf(arq,
            "Curso: %s\n",
            usuarios[u].curso);

    int achou = 0;

    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(
            emprestimos[i].matriculaUsuario
            == mat
        )
        {
            int l =
                buscarCodigoLivro(
                    emprestimos[i].codigoLivro
                );

            if(l != -1)
            {
                printf(
                    "\nCodigo livro: %d\n",
                    livros[l].codigo
                );

                printf(
                    "Titulo: %s\n",
                    livros[l].titulo
                );

                printf(
                    "Retirada: %02d/%02d/%d\n",
                    emprestimos[i].retirada.dia,
                    emprestimos[i].retirada.mes,
                    emprestimos[i].retirada.ano
                );

                fprintf(arq,
                        "\nCodigo livro: %d\n",
                        livros[l].codigo);

                fprintf(arq,
                        "Titulo: %s\n",
                        livros[l].titulo);

                fprintf(arq,
                        "Retirada: %02d/%02d/%d\n",
                        emprestimos[i].retirada.dia,
                        emprestimos[i].retirada.mes,
                        emprestimos[i].retirada.ano);

                if(emprestimos[i].devolvido)
                {
                    printf(
                        "Devolucao: %02d/%02d/%d\n",
                        emprestimos[i].devolucao.dia,
                        emprestimos[i].devolucao.mes,
                        emprestimos[i].devolucao.ano
                    );

                    fprintf(arq,
                            "Devolucao: %02d/%02d/%d\n",
                            emprestimos[i].devolucao.dia,
                            emprestimos[i].devolucao.mes,
                            emprestimos[i].devolucao.ano);
                }
                else
                {
                    printf(
                        "Devolucao: ainda nao devolvido\n"
                    );

                    fprintf(arq,
                            "Devolucao: ainda nao devolvido\n");
                }

                achou = 1;
            }
        }
    }

    if(!achou)
    {
        printf("Sem historico\n");
        fprintf(arq,
                "Sem historico\n");
    }

    fclose(arq);
}

void atualizarRelatorios()
{
    FILE *arq;

    arq = fopen(
        "reports/atualizacao.txt",
        "w"
    );

    if(arq == NULL)
        return;

    fprintf(arq,
            "Relatorios atualizados\n");

    fprintf(arq,
            "Livros cadastrados: %d\n",
            totalLivros);

    fprintf(arq,
            "Usuarios cadastrados: %d\n",
            totalUsuarios);

    fprintf(arq,
            "Emprestimos: %d\n",
            totalEmprestimos);

    fclose(arq);
}



void menuRelatorios()
{
    int op;

    do
    {
        printf(
            "\n===== RELATORIOS =====\n"
        );

        printf(
            "1 - Livros mais emprestados\n"
        );

        printf(
            "2 - Usuarios atrasados\n"
        );

        printf(
            "3 - Acervo disponivel\n"
        );

        printf(
            "4 - Historico usuario\n"
        );

        printf(
            "0 - Voltar\n"
        );

        printf("Opcao: ");

        op = lerNumero();

        switch(op)
        {
            case 1:
                relatorioLivrosMaisEmprestados();
                pausar();
                break;

            case 2:
                relatorioAtrasados();
                pausar();
                break;

            case 3:
                relatorioAcervoDisponivel();
                pausar();
                break;

            case 4:
                relatorioHistoricoUsuario();
                pausar();
                break;
        }

    } while(op != 0);
}