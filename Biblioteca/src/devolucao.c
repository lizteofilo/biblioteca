#include <stdio.h>
#include <time.h>

#include "../include/devolucao.h"
#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/util.h"

void registrarDevolucao()
{
    int matricula;
    int codigo;

    printf("\nMatricula do usuario: ");
    matricula = lerNumero();

    printf("Codigo do livro: ");
    codigo = lerNumero();

    int pos = encontrarEmprestimo(
        matricula,
        codigo
    );

    if(pos == -1)
    {
        printf(
            "Esse usuario nao possui esse livro emprestado.\n"
        );

        pausar();
        return;
    }

    int livro =
        buscarCodigoLivro(codigo);

    int usuario =
        buscarMatricula(matricula);

    emprestimos[pos].devolvido = 1;

    emprestimos[pos].devolucao =
        pegarData();

    livros[livro].qtd_disponivel++;

    usuarios[usuario].qtd_emprestimos_ativos--;

    printf(
        "\nDevolucao registrada com sucesso!\n"
    );

    pausar();
}

void listarAtrasados()
{
    time_t agora = time(NULL);

    struct tm *hoje =
        localtime(&agora);

    int encontrou = 0;

    printf(
        "\n===== EMPRESTIMOS ATRASADOS =====\n"
    );

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
                data.ano == hoje->tm_year + 1900 &&
                data.mes < hoje->tm_mon + 1
            )
            {
                atrasado = 1;
            }
            else if(
                data.ano == hoje->tm_year + 1900 &&
                data.mes == hoje->tm_mon + 1 &&
                data.dia < hoje->tm_mday
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
                    printf(
                        "\nUsuario: %s\n",
                        usuarios[u].nome
                    );

                    printf(
                        "Livro: %s\n",
                        livros[l].titulo
                    );

                    printf(
                        "Data prevista: %02d/%02d/%d\n",
                        data.dia,
                        data.mes,
                        data.ano
                    );

                    encontrou = 1;
                }
            }
        }
    }

    if(!encontrou)
    {
        printf(
            "Nenhum emprestimo atrasado.\n"
        );
    }

    pausar();
}

void menuDevolucao()
{
    int op;

    do
    {
        printf(
            "\n===== DEVOLUCAO =====\n"
        );

        printf(
            "1 - Registrar devolucao\n"
        );

        printf(
            "2 - Listar atrasados\n"
        );

        printf(
            "0 - Voltar\n"
        );

        printf("Opcao: ");

        op = lerNumero();

        switch(op)
        {
            case 1:
                registrarDevolucao();
                break;

            case 2:
                listarAtrasados();
                break;
        }

    } while(op != 0);
}