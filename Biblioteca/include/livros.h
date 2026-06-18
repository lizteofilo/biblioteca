#ifndef LIVROS_H
#define LIVROS_H

typedef struct
{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    char genero[50];
    int qtd_total;
    int qtd_disponivel;
    int total_emprestimos;

} Livro;

extern Livro *livros;
extern int totalLivros;
extern int proximoCodigo;

void cadastrarLivro();
void listarLivros();
int buscarCodigoLivro(int codigo);
void mostrarUsuariosLivro(int codigo);
void buscarLivro(int codigo);
void atualizarLivro();
void removerLivro();

void menuLivros();

#endif