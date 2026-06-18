#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/emprestimos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/util.h"

Emprestimo *emprestimos = NULL;
int totalEmprestimos = 0;
int proximoEmprestimo = 1;

Data pegarData()
{
    Data d;

    //Pega o horário atual do computador.
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);

    d.dia = t->tm_mday;
    d.mes = t->tm_mon + 1;
    d.ano = t->tm_year + 1900;

    return d;
}

Data calcularDataPrevista()
{
    Data d;

    time_t agora = time(NULL);
    agora += 14 * 24 * 60 * 60;

    struct tm *t = localtime(&agora);

    d.dia = t->tm_mday;
    d.mes = t->tm_mon + 1;
    d.ano = t->tm_year + 1900;

    return d;
}

int encontrarEmprestimo(int matricula, int codigo)
{
    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(
            emprestimos[i].matriculaUsuario == matricula &&
            emprestimos[i].codigoLivro == codigo &&
            emprestimos[i].devolvido == 0
        )
        {
            return i;
        }
    }

    return -1;
}

void realizarEmprestimo()
{
    int mat;
    int cod;

    printf("Matricula do usuario: ");
    mat = lerNumero();

    int u = buscarMatricula(mat);

    if(u == -1)
    {
        printf("Usuario nao encontrado.\n");
        pausar();
        return;
    }

    printf("Codigo do livro: ");
    cod = lerNumero();

    int l = buscarCodigoLivro(cod);

    if(l == -1)
    {
        printf("Livro nao encontrado.\n");
        pausar();
        return;
    }

    if(livros[l].qtd_disponivel <= 0)
    {
        printf("Nao existem exemplares disponiveis.\n");
        pausar();
        return;
    }

    if(usuarios[u].qtd_emprestimos_ativos >= 3)
    {
        printf("O usuario ja possui 3 emprestimos ativos.\n");
        pausar();
        return;
    }

    if(encontrarEmprestimo(mat, cod) != -1)
    {
        printf("Esse usuario ja possui esse livro emprestado.\n");
        pausar();
        return;
    }

    Emprestimo novo;

    novo.codigo = proximoEmprestimo++;
    novo.matriculaUsuario = mat;
    novo.codigoLivro = cod;

    novo.retirada = pegarData();
    novo.prevista = calcularDataPrevista();

    novo.devolucao.dia = 0;
    novo.devolucao.mes = 0;
    novo.devolucao.ano = 0;

    novo.devolvido = 0;

    Emprestimo *temp = realloc(
        emprestimos,
        (totalEmprestimos + 1) * sizeof(Emprestimo)
    );

    if(temp == NULL)
    {
        printf("Erro de memoria.\n");
        pausar();
        return;
    }

    emprestimos = temp;

    emprestimos[totalEmprestimos] = novo;
    totalEmprestimos++;

    livros[l].qtd_disponivel--;
    livros[l].total_emprestimos++;

    usuarios[u].qtd_emprestimos_ativos++;

    printf("\nEmprestimo realizado com sucesso!\n");

    printf("Data prevista de devolucao: %02d/%02d/%d\n",
           novo.prevista.dia,
           novo.prevista.mes,
           novo.prevista.ano);

    pausar();
}

void listarEmprestimosUsuario(int matricula)
{
    int achou = 0;

    for(int i = 0; i < totalEmprestimos; i++)
    {
        if(
            emprestimos[i].matriculaUsuario == matricula &&
            emprestimos[i].devolvido == 0
        )
        {
            int livro =
                buscarCodigoLivro(
                    emprestimos[i].codigoLivro
                );

            if(livro != -1)
            {
                printf("\nCodigo: %d\n",
                       livros[livro].codigo);

                printf("Titulo: %s\n",
                       livros[livro].titulo);

                printf("Devolver ate: %02d/%02d/%d\n",
                       emprestimos[i].prevista.dia,
                       emprestimos[i].prevista.mes,
                       emprestimos[i].prevista.ano);

                achou = 1;
            }
        }
    }

    if(!achou)
    {
        printf("Nenhum livro emprestado.\n");
    }
}

void menuEmprestimos()
{
    int op;

    do
    {
        printf("\n===== EMPRESTIMOS =====\n");
        printf("1 - Realizar emprestimo\n");
        printf("0 - Voltar\n");

        printf("Opcao: ");
        op = lerNumero();

        switch(op)
        {
            case 1:
                realizarEmprestimo();
                break;
        }

    } while(op != 0);
}