#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

typedef struct
{
    int dia;
    int mes;
    int ano;

} Data;

typedef struct
{
    int codigo;
    int matriculaUsuario;
    int codigoLivro;

    Data retirada;
    Data prevista;
    Data devolucao;

    int devolvido;

} Emprestimo;

extern Emprestimo *emprestimos;
extern int totalEmprestimos;
extern int proximoEmprestimo;

Data pegarData();
Data calcularDataPrevista();

int encontrarEmprestimo(int matricula,int codigo);
void realizarEmprestimo();
void listarEmprestimosUsuario(int matricula);
void menuEmprestimos();

#endif