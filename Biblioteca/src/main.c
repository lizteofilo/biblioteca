#include <stdio.h>
#include <stdlib.h>
#include "../include/livros.h"
#include "../include/emprestimos.h"
#include "../include/usuarios.h"
#include "../include/relatorio.h"
#include "../include/devolucao.h"
#include "../include/util.h"
#include "../include/arquivos.h"



int main(){

carregarLivros();
carregarUsuarios();
carregarEmprestimos();


/* Descobre o próximo código de livro */
proximoCodigo = 1;

for(int i = 0; i < totalLivros; i++)
{
    if(livros[i].codigo >= proximoCodigo)
    {
        proximoCodigo = 
        livros[i].codigo + 1;
    }
}

/* Descobre a próxima matrícula */
proximaMatricula = 1;

for(int i = 0; i < totalUsuarios; i++)
{
    if(usuarios[i].matricula >= proximaMatricula)
    {
        proximaMatricula =
        usuarios[i].matricula + 1;
    }
}

/* Descobre o próximo código de empréstimo */
proximoEmprestimo = 1;

for(int i = 0; i < totalEmprestimos; i++)
{
    if(emprestimos[i].codigo >= proximoEmprestimo)
    {
        proximoEmprestimo =
        emprestimos[i].codigo + 1;
    }
}



int opcao;

do {
    printf("\n=== SISTEMA BIBLIOTECARIO ===\n");
    printf("Bem-Vindo(a) ao Sistema de Gerenciamento de Biblioteca! Leia a seguintes opcoes e suas respectivos numeros: \n");

    printf("1 - Gerenciar Livros\n");
    printf("2 - Gerenciar Usuarios\n");
    printf("3 - Realizar Emprestimo\n");
    printf("4 - Registrar Devolucao\n");
    printf("5 - Relatorios\n");
    printf("0 - Sair\n");

    printf("Digite o numero da sua Opcao: ");
    opcao = lerNumero();

    switch(opcao) {
        case 1:
            menuLivros();
            break;

        case 2:
            menuUsuarios();
            break;

        case 3:
            menuEmprestimos();
            break;

        case 4:
            menuDevolucao();
            break;

        case 5:
            menuRelatorios();
            break;

        case 0:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida!\n");
    }

} while(opcao != 0);

salvarLivros();
salvarUsuarios();
salvarEmprestimos();

atualizarRelatorios();

free(livros);
livros = NULL;

free(usuarios);
usuarios = NULL;

free(emprestimos);
emprestimos = NULL;


return 0;
}