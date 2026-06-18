#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/usuarios.h"
#include "../include/emprestimos.h"
#include "../include/util.h"

Usuario *usuarios = NULL;
int totalUsuarios = 0;
int proximaMatricula = 1;

int buscarMatricula(int matricula)
{
    for(int i = 0; i < totalUsuarios; i++)
    {
        if(usuarios[i].matricula == matricula)
        {
            return i;
        }
    }

    return -1;
}

int buscarNome(char nome[])
{
    for(int i = 0; i < totalUsuarios; i++)
    {
        if(strcmp(usuarios[i].nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

void cadastrarUsuario()
{
    Usuario novo;

    novo.matricula = proximaMatricula++;

    getchar();

    printf("Nome: ");
    lerTexto(novo.nome, 100);

    printf("Curso: ");
    lerTexto(novo.curso, 100);

    novo.qtd_emprestimos_ativos = 0;

    Usuario *temp = realloc(
        usuarios,
        (totalUsuarios + 1) * sizeof(Usuario)
    );

    if(temp == NULL)
    {
        printf("Erro de memoria.\n");
        pausar();
        return;
    }

    usuarios = temp;
    usuarios[totalUsuarios] = novo;

    totalUsuarios++;

    printf("\nUsuario cadastrado!\n");
    printf("Matricula: %d\n", novo.matricula);

    pausar();
}

void listarUsuarios()
{
    if(totalUsuarios == 0)
    {
        printf("\nNenhum usuario cadastrado.\n");
        pausar();
        return;
    }

    printf("\n===== USUARIOS =====\n");

    for(int i = 0; i < totalUsuarios; i++)
    {
        printf("\nMatricula: %d\n",
               usuarios[i].matricula);

        printf("Nome: %s\n",
               usuarios[i].nome);

        printf("Curso: %s\n",
               usuarios[i].curso);

        printf("Emprestimos ativos: %d\n",
               usuarios[i].qtd_emprestimos_ativos);

        printf("-------------------------\n");
    }

    pausar();
}

void buscarUsuario()
{
    int opcao;

    printf("\n1 - Buscar por matricula\n");
    printf("2 - Buscar por nome\n");
    printf("Opcao: ");

    opcao = lerNumero();

    if(opcao == 1)
    {
        int mat;

        printf("Matricula: ");
        mat = lerNumero();

        int pos = buscarMatricula(mat);

        if(pos == -1)
        {
            printf("Usuario nao encontrado.\n");
        }
        else
        {
            printf("\n===== USUARIO =====\n");

            printf("Matricula: %d\n",
                   usuarios[pos].matricula);

            printf("Nome: %s\n",
                   usuarios[pos].nome);

            printf("Curso: %s\n",
                   usuarios[pos].curso);

            printf("Emprestimos ativos: %d\n",
                   usuarios[pos].qtd_emprestimos_ativos);

            printf("\nLivros emprestados:\n");

            listarEmprestimosUsuario(
                usuarios[pos].matricula
            );
        }
    }
    else if(opcao == 2)
    {
        char nome[100];

        getchar();

        printf("Nome: ");
        lerTexto(nome, 100);

        int pos = buscarNome(nome);

        if(pos == -1)
        {
            printf("Usuario nao encontrado.\n");
        }
        else
        {
            printf("\n===== USUARIO =====\n");

            printf("Matricula: %d\n",
                   usuarios[pos].matricula);

            printf("Nome: %s\n",
                   usuarios[pos].nome);

            printf("Curso: %s\n",
                   usuarios[pos].curso);

            printf("Emprestimos ativos: %d\n",
                   usuarios[pos].qtd_emprestimos_ativos);

            printf("\nLivros emprestados:\n");

            listarEmprestimosUsuario(
                usuarios[pos].matricula
            );
        }
    }
    else
    {
        printf("Opcao invalida.\n");
    }

    pausar();
}

void atualizarUsuario()
{
    int matricula;

    printf("Matricula: ");
    matricula = lerNumero();

    int pos = buscarMatricula(matricula);

    if(pos == -1)
    {
        printf("Usuario nao encontrado.\n");
        pausar();
        return;
    }

    getchar();

    printf("Novo nome: ");
    lerTexto(
        usuarios[pos].nome,
        100
    );

    printf("Novo curso: ");
    lerTexto(
        usuarios[pos].curso,
        100
    );

    printf("\nUsuario atualizado!\n");

    pausar();
}

void removerUsuario()
{
    int matricula;

    printf("Matricula: ");
    matricula = lerNumero();

    int pos = buscarMatricula(matricula);

    if(pos == -1)
    {
        printf("Usuario nao encontrado.\n");
        pausar();
        return;
    }

    if(
        usuarios[pos].qtd_emprestimos_ativos > 0
    )
    {
        printf(
            "Nao e possivel remover.\n"
            "Usuario possui emprestimos ativos.\n"
        );

        pausar();
        return;
    }

    for(int i = pos; i < totalUsuarios - 1; i++)
    {
        usuarios[i] = usuarios[i + 1];
    }

    totalUsuarios--;

    if(totalUsuarios == 0)
    {
        free(usuarios);
        usuarios = NULL;
    }
    else
    {
        Usuario *temp = realloc(
            usuarios,
            totalUsuarios * sizeof(Usuario)
        );

        if(temp != NULL)
        {
            usuarios = temp;
        }
    }

    printf("Usuario removido com sucesso!\n");

    pausar();
}

void menuUsuarios()
{
    int op;

    do
    {
        printf("\n===== USUARIOS =====\n");
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
                cadastrarUsuario();
                break;

            case 2:
                listarUsuarios();
                break;

            case 3:
                buscarUsuario();
                break;

            case 4:
                atualizarUsuario();
                break;

            case 5:
                removerUsuario();
                break;
        }

    } while(op != 0);
}