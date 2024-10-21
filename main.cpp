#include <iostream>
#include <string>
#include "biblioteca.hpp"

using namespace std;

void limparTerminal() {
    system("clear");
}

void esperarTecla() {
    cout << "Pressione enter para continuar...";
    cin.get();
    limparTerminal();
}

void exibirMenuPrincipal() {
    cout << "Menu Principal:" << endl;
    cout << "1. Menu de Livros" << endl;
    cout << "2. Menu de Revistas" << endl;
    cout << "3. Menu de Usuários" << endl;
    cout << "4. Menu de Relatórios" << endl;
    cout << "5. Menu de Locações" << endl;
    cout << "0. Sair" << endl;
}

void exibirMenuLivros() {
    cout << "Menu de Livros:" << endl;
    cout << "1. Cadastrar Livro" << endl;
    cout << "2. Alterar Livro" << endl;
    cout << "3. Remover Livro" << endl;
    cout << "4. Pesquisar Livro" << endl;
    cout << "0. Voltar" << endl;
}

void exibirMenuRevistas() {
    cout << "Menu de Revistas:" << endl;
    cout << "1. Cadastrar Revista" << endl;
    cout << "2. Alterar Revista" << endl;
    cout << "3. Remover Revista" << endl;
    cout << "4. Pesquisar Revista" << endl;
    cout << "0. Voltar" << endl;
}

void exibirMenuUsuarios() {
    cout << "Menu de Usuários:" << endl;
    cout << "1. Cadastrar Usuário" << endl;
    cout << "2. Alterar Usuário" << endl;
    cout << "3. Remover Usuário" << endl;
    cout << "4. Listar Usuários" << endl;
    cout << "0. Voltar" << endl;
}

void exibirMenuRelatorios() {
    cout << "Menu de Relatórios:" << endl;
    cout << "1. Listar Livros/Revistas por Autor/Editora" << endl;
    cout << "2. Listar Livros/Revistas por Assunto" << endl;
    cout << "3. Listar Livros/Revistas em Atraso" << endl;
    cout << "4. Histórico de Retiradas de um Usuário" << endl;
    cout << "0. Voltar" << endl;
}

void exibirMenuLocacoes() {
    cout << "Menu de Locações:" << endl;
    cout << "1. Alugar Livro" << endl;
    cout << "2. Alugar Revista" << endl;
    cout << "3. Devolver Livro" << endl;
    cout << "4. Devolver Revista" << endl;
    cout << "0. Voltar" << endl;
}

int main() {
    LivroHash<HashLivro> livroHash;
    RevistaHash<HashRevista> revistaHash;
    UsuarioHash<HashUsuario> usuarioHash;
    AluguelLivrosHash<hashAluguelLivros> aluguelLivrosHash;
    AluguelRevistasHash<hashAluguelRevistas> aluguelRevistasHash;

    inicializarLivroLDE(livroHash);
    inicializarRevistaLDE(revistaHash);
    inicializarUsuarioLDE(usuarioHash);
    inicializarAluguelLivrosLDE(aluguelLivrosHash);
    inicializarAluguelRevistasLDE(aluguelRevistasHash);

    int opcaoPrincipal;
    do {
        exibirMenuPrincipal();
        cout << "Escolha uma opção: ";
        cin >> opcaoPrincipal;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        limparTerminal();
        
        switch (opcaoPrincipal) {
            case 1: {  // Menu de Livros
                int opcaoLivro;
                do {
                    exibirMenuLivros();
                    cout << "Escolha uma opção: ";
                    cin >> opcaoLivro;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    limparTerminal();
                    
                    switch (opcaoLivro) {
                        case 1: {  // Cadastrar Livro
                            int matricula;
                            string titulo, autor[3], editora, assunto;
                            cout << "Matrícula: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!validarMatricula(matricula)) {
                                cout << "Matricula inválida. Permitido até 4 dígitos." << endl;
                                break;
                            }

                            cout << "Título: ";
                            getline(cin, titulo);
                            for (int i = 0; i < 3; i++) {
                                cout << "Autor " << i + 1 << ": ";
                                getline(cin, autor[i]);
                            }
                            cout << "Editora: ";
                            getline(cin, editora);
                            cout << "Assunto: ";
                            getline(cin, assunto);

                            inserirLivro(livroHash, matricula, titulo, autor, editora, assunto);
                            esperarTecla();
                            break;
                        }
                        case 2: {  // Alterar Livro
                            int matricula;
                            string titulo, autor[3], editora, assunto;
                            cout << "Matrícula do Livro a Alterar: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (pesquisarLivro(livroHash, matricula) == nullptr) {
                                cout << "Livro não encontrado." << endl;
                                esperarTecla();
                                break;
                            }

                            cout << "Novo Título: ";
                            getline(cin, titulo);
                            for (int i = 0; i < 3; i++) {
                                cout << "Novo Autor " << i + 1 << ": ";
                                getline(cin, autor[i]);
                            }
                            cout << "Nova Editora: ";
                            getline(cin, editora);
                            cout << "Novo Assunto: ";
                            getline(cin, assunto);

                            editarLivro(livroHash, matricula, titulo, autor, editora, assunto);
                            esperarTecla();
                            break;
                        }
                        case 3: {  // Remover Livro
                            int matricula;
                            cout << "Matrícula do Livro a Remover: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!retirarLivro(livroHash, matricula)) {
                                cout << "Livro não encontrado." << endl;
                                esperarTecla();
                                break;
                            }
                            cout << "Livro removido com sucesso." << endl;
                            esperarTecla();
                            break;
                        }
                        case 4: {  // Pesquisar Livro
                            int matricula;
                            cout << "Matrícula do Livro a Pesquisar: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            pesquisarLivroPorMatricula(livroHash, matricula);
                            esperarTecla();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                            break;
                    }
                } while (opcaoLivro != 0);
                break;
            }
            case 2: {  // Menu de Revistas
                int opcaoRevista;
                do {
                    exibirMenuRevistas();
                    cout << "Escolha uma opção: ";
                    cin >> opcaoRevista;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    limparTerminal();
                    
                    switch (opcaoRevista) {
                        case 1: {  // Cadastrar Revista
                            int matricula;
                            string titulo, editora, assunto;
                            cout << "Matrícula: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!validarMatricula(matricula)) {
                                cout << "Matricula inválida. Permitido até 4 dígitos." << endl;
                                break;
                            }

                            cout << "Título: ";
                            getline(cin, titulo);
                            cout << "Editora: ";
                            getline(cin, editora);
                            cout << "Assunto: ";
                            getline(cin, assunto);

                            inserirRevista(revistaHash, matricula, titulo, editora, assunto);
                            esperarTecla();
                            break;
                        }
                        case 2: {  // Alterar Revista
                            int matricula;
                            string titulo, editora, assunto;
                            cout << "Matrícula da Revista a Alterar: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Novo Título: ";
                            getline(cin, titulo);
                            cout << "Nova Editora: ";
                            getline(cin, editora);
                            cout << "Novo Assunto: ";
                            getline(cin, assunto);

                            editarRevista(revistaHash, matricula, titulo, editora, assunto);
                            esperarTecla();
                            break;
                        }
                        case 3: {  // Remover Revista
                            int matricula;
                            cout << "Matrícula da Revista a Remover: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!retirarRevista(revistaHash, matricula)) {
                                cout << "Revista não encontrada." << endl;
                                esperarTecla();
                                break;
                            }
                            cout << "Revista removida com sucesso." << endl;
                            esperarTecla();
                            break;
                        }
                        case 4: {  // Pesquisar Revista
                            int matricula;
                            cout << "Matrícula da Revista a Pesquisar: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            pesquisarRevistaPorMatricula(revistaHash, matricula);
                            esperarTecla();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                            break;
                    }
                } while (opcaoRevista != 0);
                break;
            }
            case 3: {  // Menu de Usuários
                int opcaoUsuario;
                do {
                    exibirMenuUsuarios();
                    cout << "Escolha uma opção: ";
                    cin >> opcaoUsuario;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    limparTerminal();
                    
                    switch (opcaoUsuario) {
                        case 1: {  // Cadastrar Usuário
                            int matricula;
                            string nome, email, telefone;
                            cout << "Matrícula: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Nome: ";
                            getline(cin, nome);
                            cout << "Email: ";
                            getline(cin, email);
                            cout << "Telefone: ";
                            getline(cin, telefone);

                            inserirUsuario(usuarioHash, matricula, nome, email, telefone);
                            esperarTecla();
                            break;
                        }
                        case 2: {  // Alterar Usuário
                            int matricula;
                            string nome, email, telefone;
                            cout << "Matrícula do Usuário a Alterar: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Novo Nome: ";
                            getline(cin, nome);
                            cout << "Novo Email: ";
                            getline(cin, email);
                            cout << "Novo Telefone: ";
                            getline(cin, telefone);

                            retirarUsuario(usuarioHash, matricula);
                            inserirUsuario(usuarioHash, matricula, nome, email, telefone);
                            esperarTecla();
                            break;
                        }
                        case 3: {  // Remover Usuário
                            int matricula;
                            cout << "Matrícula do Usuário a Remover: ";
                            cin >> matricula;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!retirarUsuario(usuarioHash, matricula)) {
                                cout << "Usuário não encontrado." << endl;
                                esperarTecla();
                                break;
                            }
                            cout << "Usuário removido com sucesso." << endl;
                            esperarTecla();
                            break;
                        }
                        case 4: {  // Listar Usuários
                            mostrarUsuarios(usuarioHash);
                            esperarTecla();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                            break;
                    }
                } while (opcaoUsuario != 0);
                break;
            }
            case 4: {  // Menu de Relatórios
                int opcaoRelatorio;
                do {
                    exibirMenuRelatorios();
                    cout << "Escolha uma opção: ";
                    cin >> opcaoRelatorio;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    limparTerminal();
                    
                    switch (opcaoRelatorio) {
                        case 1: {  // Livros/Revistas por Autor/Editora
                            string termo;
                            cout << "Digite o Autor ou Editora: ";
                            getline(cin, termo);
                            pesquisarPorAutorOuEditora(livroHash, revistaHash, termo);
                            esperarTecla();
                            break;
                        }
                        case 2: {  // Livros/Revistas por Assunto
                            string assunto;
                            cout << "Digite o Assunto: ";
                            getline(cin, assunto);
                            pesquisarPorAssunto(livroHash, revistaHash, assunto);
                            esperarTecla();
                            break;
                        }
                        case 3: {  // Livros/Revistas em Atraso
                            livrosRevistasAtraso(aluguelLivrosHash, aluguelRevistasHash, livroHash, revistaHash);
                            esperarTecla();
                            break;
                        }
                        case 4: {  // Histórico de Retiradas de um Usuário
                            int matriculaUsuario;
                            cout << "Matrícula do Usuário: ";
                            cin >> matriculaUsuario;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Livros locados: " << endl;
                            pesquisarAluguelLivroPorUsuario(aluguelLivrosHash, matriculaUsuario);
                            cout << "Revistas locadas: " << endl;
                            pesquisarAluguelRevistaPorUsuario(aluguelRevistasHash, matriculaUsuario);

                            esperarTecla();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                            break;
                    }
                } while (opcaoRelatorio != 0);
                break;
            }
            case 5: {  // Menu de Locações
                int opcaoLocacao;
                do {
                    exibirMenuLocacoes();
                    cout << "Escolha uma opção: ";
                    cin >> opcaoLocacao;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    limparTerminal();
                    
                    switch (opcaoLocacao) {
                        case 1: {  // Alugar Livro
                            int id, matriculaUsuario, matriculaLivro;
                            string dataEmprestimo, dataDevolucao;

                            cout << "ID do Aluguel: ";
                            cin >> id;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Matrícula do Usuário: ";
                            cin >> matriculaUsuario;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Matrícula do Livro: ";
                            cin >> matriculaLivro;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Data de Empréstimo (AAAA-MM-DD): ";
                            getline(cin, dataEmprestimo);

                            cout << "Data de Devolução (AAAA-MM-DD): ";
                            getline(cin, dataDevolucao);

                            locarLivro(aluguelLivrosHash, id, matriculaUsuario, matriculaLivro, dataEmprestimo, dataDevolucao);
                            esperarTecla();
                            break;
                        }
                        case 2: {  // Alugar Revista
                            int id, matriculaUsuario, matriculaRevista;
                            string dataEmprestimo, dataDevolucao;

                            cout << "ID do Aluguel: ";
                            cin >> id;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Matrícula do Usuário: ";
                            cin >> matriculaUsuario;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Matrícula da Revista: ";
                            cin >> matriculaRevista;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            cout << "Data de Empréstimo (AAAA-MM-DD): ";
                            getline(cin, dataEmprestimo);

                            cout << "Data de Devolução (AAAA-MM-DD): ";
                            getline(cin, dataDevolucao);

                            locarRevista(aluguelRevistasHash, id, matriculaUsuario, matriculaRevista, dataEmprestimo, dataDevolucao);
                            esperarTecla();
                            break;
                        }
                        case 3: {  // Devolver Livro
                            int id;
                            cout << "ID do Aluguel do Livro a Devolver: ";
                            cin >> id;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!devolverLivro(aluguelLivrosHash, id)) {
                                cout << "Aluguel não encontrado." << endl;
                            } else {
                                cout << "Livro devolvido com sucesso." << endl;
                            }
                            esperarTecla();
                            break;
                        }
                        case 4: {  // Devolver Revista
                            int id;
                            cout << "ID do Aluguel da Revista a Devolver: ";
                            cin >> id;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');

                            if (!devolverRevista(aluguelRevistasHash, id)) {
                                cout << "Aluguel não encontrado." << endl;
                            } else {
                                cout << "Revista devolvida com sucesso." << endl;
                            }
                            esperarTecla();
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Opção inválida!" << endl;
                            break;
                    }
                } while (opcaoLocacao != 0);
                break;
            }
            case 0:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
                break;
        }
    } while (opcaoPrincipal != 0);

    return 0;
}
