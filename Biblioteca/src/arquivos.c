#include <stdio.h>
#include <stdlib.h>


#include "../include/arquivos.h"
#include "../include/livros.h"
#include "../include/usuarios.h"
#include "../include/emprestimos.h"


void salvarLivros()
{

    FILE *arquivo;
    arquivo = fopen(
    "data/livros.dat",
    "wb"
    );

    if (arquivo == NULL){
    printf("Erro ao salvar livros.\n");
    return;
}

    fwrite(
    &totalLivros,
    sizeof(int),
    1,
    arquivo
    );

    fwrite(
    livros,
    sizeof(Livro),
    totalLivros,
    arquivo
    );

    fclose(arquivo);

}


void carregarLivros()
{

    FILE *arquivo;
    arquivo=fopen(
    "data/livros.dat",
    "rb"
    );


    if(arquivo == NULL)
        return;


    fread(
    &totalLivros,
    sizeof(int),
    1,
    arquivo
    );


    livros = malloc(
    totalLivros * sizeof(Livro)
    );

    fread(
    livros,
    sizeof(Livro),
    totalLivros,
    arquivo
    );

    fclose(arquivo);


}



void salvarUsuarios()
{


    FILE *arquivo;
    arquivo=fopen(
    "data/usuarios.dat",
    "wb"
    );

    if (arquivo == NULL){
    printf("Erro ao salvar usuarios.\n");
    return;
}

    fwrite(
    &totalUsuarios,
    sizeof(int),
    1,
    arquivo
    );

    fwrite(
    usuarios,
    sizeof(Usuario),
    totalUsuarios,
    arquivo
    );

    fclose(arquivo);

}


void carregarUsuarios()
{

    FILE *arquivo;
    arquivo=fopen(
    "data/usuarios.dat",
    "rb"
    );


    if (arquivo == NULL){
    printf("Erro ao carregar usuarios.\n");
    return;
}

    fread(
    &totalUsuarios,
    sizeof(int),
    1,
    arquivo
    );


    usuarios = malloc(
    totalUsuarios*sizeof(Usuario)
    );

    fread(
    usuarios,
    sizeof(Usuario),
    totalUsuarios,
    arquivo
    );

    fclose(arquivo);

}


void salvarEmprestimos()
{

    FILE *arquivo;
    arquivo=fopen(
    "data/emprestimos.dat",
    "wb"
    );

    if (arquivo == NULL){
    printf("Erro ao salvar emprestimos.\n");
    return;
}

    fwrite(
    &totalEmprestimos,
    sizeof(int),
    1,
    arquivo
    );

    fwrite(
    emprestimos,
    sizeof(Emprestimo),
    totalEmprestimos,
    arquivo
    );

    fclose(arquivo);


}


void carregarEmprestimos()
{

    FILE *arquivo;
    arquivo=fopen(
    "data/emprestimos.dat",
    "rb"
    );


    if (arquivo == NULL){
    printf("Erro ao carregar emprestimos.\n");
    return;
}

    fread(
    &totalEmprestimos,
    sizeof(int),
    1,
    arquivo
    );


    emprestimos = malloc(
    totalEmprestimos*sizeof(Emprestimo)
    );


    fread(
    emprestimos,
    sizeof(Emprestimo),
    totalEmprestimos,
    arquivo
    );

    fclose(arquivo);


}