# Sistema de Gerenciamento de Biblioteca

Sistema desenvolvido em linguagem C para gerenciamento de uma biblioteca, permitindo o controle de livros, usuários, empréstimos, devoluções e geração de relatórios.

## Funcionalidades

### Livros
- Cadastro de livros;
- Listagem do acervo;
- Busca por código;
- Atualização de informações;
- Remoção de livros;
- Controle de quantidade disponível.

### Usuários
- Cadastro de usuários;
- Listagem de usuários;
- Busca por matrícula ou nome;
- Atualização de dados;
- Remoção de usuários.

### Empréstimos
- Realização de empréstimos;
- Controle de datas;
- Limite de empréstimos ativos por usuário;
- Histórico de empréstimos.

### Devoluções
- Registro de devolução;
- Atualização automática do estoque;
- Verificação de empréstimos atrasados.

### Relatórios
O sistema gera relatórios em arquivos `.txt`:

- Livros mais emprestados;
- Usuários com atraso;
- Acervo disponível;
- Histórico de usuários.

---

# Tecnologias utilizadas

- Linguagem C
- Biblioteca padrão C
- Manipulação de arquivos
- Structs
- Ponteiros
- Alocação dinâmica de memória

---

# Estrutura do projeto

```
SistemaBiblioteca/

├── src/
│   ├── main.c
│   ├── arquivos.c
│   ├── devolucao.c
│   ├── emprestimos.c
│   ├── livros.c
│   ├── relatorio.c
│   ├── usuarios.c
│   └── util.c
│
├── include/
│   ├── arquivos.h
│   ├── devolucao.h
│   ├── emprestimos.h
│   ├── livros.h
│   ├── relatorio.h
│   ├── usuarios.h
│   └── util.h
│
├── data/
│   ├── livros.dat
│   ├── usuarios.dat
│   └── emprestimos.dat
│
└── reports/
    ├── livros_mais_emprestados.txt
    ├── usuarios_atrasados.txt
    ├── acervo_disponivel.txt
    └── historico_usuario.txt
```

---

# Compilação

É necessário possuir o compilador GCC instalado.

Na pasta do projeto execute:

```bash
gcc src/*.c -Iinclude -o biblioteca.exe
```

---

# Execução

No Windows:

```powershell
.\biblioteca.exe
```

No Linux:

```bash
./biblioteca
```

---

# Armazenamento de dados

O sistema utiliza arquivos binários para salvar os dados:

```
data/livros.dat
data/usuarios.dat
data/emprestimos.dat
```

Os dados são carregados automaticamente ao iniciar o programa.

---

# Conceitos utilizados

- Modularização em arquivos `.c` e `.h`;
- Estruturas (`struct`);
- Vetores dinâmicos;
- `malloc`, `realloc` e `free`;
- Leitura e escrita de arquivos (`fread` e `fwrite`);
- Algoritmos de busca e ordenação.

---

# Autores

Projeto desenvolvido para disciplina de programação em linguagem C.
