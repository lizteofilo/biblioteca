#ifndef USUARIOS_H
#define USUARIOS_H

typedef struct
{
    int matricula;
    char nome[100];
    char curso[100];
    int qtd_emprestimos_ativos;

} Usuario;

extern Usuario *usuarios;
extern int totalUsuarios;
extern int proximaMatricula;

int buscarMatricula(int matricula);
int buscarNome(char nome[]);

void cadastrarUsuario();
void listarUsuarios();
void buscarUsuario();
void atualizarUsuario();
void removerUsuario();

void menuUsuarios();

#endif