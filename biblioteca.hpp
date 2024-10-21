#ifndef BIBLIOTECA_HPP
#define BIBLIOTECA_HPP
#include <iostream>
#include <string>
#include "lde.hpp"
#include "biblioteca.hpp"
#include <chrono>
#include <ctime> // Para conversão de chrono::time_point para tm
#include <fstream>
#include <sstream>

#define tamanho 100

using namespace std;
using namespace chrono;

struct Usuario {
    int matricula;
    string nome;
    string email;
    string telefone;
};

struct HashUsuario {
    int info;
    Usuario *usuario;

    bool operator<(const HashUsuario &other) const {
        return this->info < other.info;
    }

    bool operator>(const HashUsuario &other) const {
        return this->info > other.info;
    }
};

template<typename T>
struct UsuarioHash {
    LDE <T> matricula[tamanho];
    LDE <T> nome[tamanho];
    LDE <T> email[tamanho];
    LDE <T> telefone[tamanho];
};

struct Livro {
    int matricula;
    string titulo;
    string autor[3];
    string editora;
    string assunto;
};

struct Revista {
    int matricula;
    string titulo;
    string editora;
    string assunto;
};

struct HashLivro {
    int info;
    Livro *livro;

    bool operator<(const HashLivro &other) const {
        return this->info < other.info;
    }

    bool operator>(const HashLivro &other) const {
        return this->info > other.info;
    }
};

struct HashRevista {
    int info;
    Revista *revista;

    bool operator<(const HashRevista &other) const {
        return this->info < other.info;
    }

    bool operator>(const HashRevista &other) const {
        return this->info > other.info;
    }
};

template<typename T>
struct LivroHash {
    LDE <T> matricula[tamanho];
    LDE <T> titulo[tamanho];
    LDE <T> autor[tamanho*3];
    LDE <T> editora[tamanho];
    LDE <T> assunto[tamanho];
};

template<typename T>
struct RevistaHash {
    LDE <T> matricula[tamanho];
    LDE <T> titulo[tamanho];
    LDE <T> editora[tamanho];
    LDE <T> assunto[tamanho];
};

struct aluguelLivros {
    int id;
    int matriculaUsuario;
    int matriculaLivro;
    string dataEmprestimo;
    string dataDevolucao;
};

struct aluguelRevistas {
    int id;
    int matriculaUsuario;
    int matriculaRevista;
    string dataEmprestimo;
    string dataDevolucao;
};

struct hashAluguelLivros {
    int info;
    aluguelLivros *aluguel;

    bool operator<(const hashAluguelLivros &other) const {
        return this->info < other.info;
    }

    bool operator>(const hashAluguelLivros &other) const {
        return this->info > other.info;
    }
};

struct hashAluguelRevistas {
    int info;
    aluguelRevistas *aluguel;

    bool operator<(const hashAluguelRevistas &other) const {
        return this->info < other.info;
    }

    bool operator>(const hashAluguelRevistas &other) const {
        return this->info > other.info;
    }
};

template<typename T>
struct AluguelLivrosHash {
    LDE <T> id[tamanho]; // Add this line
    LDE <T> matriculaUsuario[tamanho];
    LDE <T> matriculaLivro[tamanho];
    LDE <T> dataEmprestimo[tamanho];
    LDE <T> dataDevolucao[tamanho];
};

template<typename T>
struct AluguelRevistasHash {
    LDE <T> id[tamanho]; // Add this line
    LDE <T> matriculaUsuario[tamanho];
    LDE <T> matriculaRevista[tamanho];
    LDE <T> dataEmprestimo[tamanho];
    LDE <T> dataDevolucao[tamanho];
};

template<typename T>
void salvarUsuarios(UsuarioHash<T> &hash, const string &arquivo) {
    ofstream outFile(arquivo);
    for (int i = 0; i < tamanho; i++) {
        No<T> *aux = hash.matricula[i].comeco;
        while (aux != NULL) {
            Usuario *usuario = aux->info.usuario;
            outFile << usuario->matricula << ';' 
                    << usuario->nome << ';' 
                    << usuario->email << ';' 
                    << usuario->telefone << '\n';
            aux = aux->eloP;
        }
    }
    outFile.close();
}

template<typename T>
void salvarLivros(LivroHash<T> &hash, const string &arquivo) {
    ofstream outFile(arquivo);
    for (int i = 0; i < tamanho; i++) {
        No<T> *aux = hash.matricula[i].comeco;
        while (aux != NULL) {
            Livro *livro = aux->info.livro;
            outFile << livro->matricula << ';' 
                    << livro->titulo << ';' 
                    << livro->autor[0] << ';' 
                    << livro->autor[1] << ';' 
                    << livro->autor[2] << ';' 
                    << livro->editora << ';' 
                    << livro->assunto << '\n';
            aux = aux->eloP;
        }
    }
    outFile.close();
}

template<typename T>
void salvarRevistas(RevistaHash<T> &hash, const string &arquivo) {
    ofstream outFile(arquivo);
    for (int i = 0; i < tamanho; i++) {
        No<T> *aux = hash.matricula[i].comeco;
        while (aux != NULL) {
            Revista *revista = aux->info.revista;
            outFile << revista->matricula << ';' 
                    << revista->titulo << ';' 
                    << revista->editora << ';' 
                    << revista->assunto << '\n';
            aux = aux->eloP;
        }
    }
    outFile.close();
}

template<typename T>
void salvarAluguelLivros(AluguelLivrosHash<T> &hash, const string &arquivo) {
    ofstream outFile(arquivo);
    for (int i = 0; i < tamanho; i++) {
        No<T> *aux = hash.id[i].comeco;
        while (aux != NULL) {
            aluguelLivros *aluguel = aux->info.aluguel;
            outFile << aluguel->id << ';' 
                    << aluguel->matriculaUsuario << ';' 
                    << aluguel->matriculaLivro << ';' 
                    << aluguel->dataEmprestimo << ';' 
                    << aluguel->dataDevolucao << '\n';
            aux = aux->eloP;
        }
    }
    outFile.close();
}

template<typename T>
void excluirUsuarioArquivo(const string &arquivo, int matricula) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) != matricula) {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void excluirLivroArquivo(const string &arquivo, int matricula) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) != matricula) {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void excluirRevistaArquivo(const string &arquivo, int matricula) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) != matricula) {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void excluirAluguelLivroArquivo(const string &arquivo, int id) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) != id) {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void editarUsuarioArquivo(const string &arquivo, int matricula, const Usuario &novoUsuario) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) == matricula) {
            outFile << novoUsuario.matricula << ';' 
                    << novoUsuario.nome << ';' 
                    << novoUsuario.email << ';' 
                    << novoUsuario.telefone << '\n';
        } else {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void editarLivroArquivo(const string &arquivo, int matricula, const Livro &novoLivro) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) == matricula) {
            outFile << novoLivro.matricula << ';' 
                    << novoLivro.titulo << ';' 
                    << novoLivro.autor[0] << ';' 
                    << novoLivro.autor[1] << ';' 
                    << novoLivro.autor[2] << ';' 
                    << novoLivro.editora << ';' 
                    << novoLivro.assunto << '\n';
        } else {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void editarRevistaArquivo(const string &arquivo, int matricula, const Revista &novaRevista) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) == matricula) {
            outFile << novaRevista.matricula << ';' 
                    << novaRevista.titulo << ';' 
                    << novaRevista.editora << ';' 
                    << novaRevista.assunto << '\n';
        } else {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

template<typename T>
void editarAluguelLivroArquivo(const string &arquivo, int id, const aluguelLivros &novoAluguel) {
    ifstream inFile(arquivo);
    ofstream outFile("temp.txt");
    string linha;
    while (getline(inFile, linha)) {
        stringstream ss(linha);
        string campo;
        getline(ss, campo, ';');
        if (stoi(campo) == id) {
            outFile << novoAluguel.id << ';' 
                    << novoAluguel.matriculaUsuario << ';' 
                    << novoAluguel.matriculaLivro << ';' 
                    << novoAluguel.dataEmprestimo << ';' 
                    << novoAluguel.dataDevolucao << '\n';
        } else {
            outFile << linha << '\n';
        }
    }
    inFile.close();
    outFile.close();
    remove(arquivo.c_str());
    rename("temp.txt", arquivo.c_str());
}

// Inicializa as listas duplamente encadeadas de cada campo da struct LivroHash
template<typename T>
void inicializarLivroLDE(LivroHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        inicializarLDE(hash.matricula[i]);
        inicializarLDE(hash.titulo[i]);
        inicializarLDE(hash.editora[i]);
        inicializarLDE(hash.assunto[i]);
    }
    for(int j = 0; j < tamanho * 3; j++){
        inicializarLDE(hash.autor[j]);
    }
};

// Inicializa as listas duplamente encadeadas de cada campo da struct RevistaHash
template<typename T>
void inicializarRevistaLDE(RevistaHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        inicializarLDE(hash.matricula[i]);
        inicializarLDE(hash.titulo[i]);
        inicializarLDE(hash.editora[i]);
        inicializarLDE(hash.assunto[i]);
    }
};

// Inicializa as listas duplamente encadeadas de cada campo da struct UsuarioHash
template<typename T>
void inicializarUsuarioLDE(UsuarioHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        inicializarLDE(hash.matricula[i]);
        inicializarLDE(hash.nome[i]);
        inicializarLDE(hash.email[i]);
        inicializarLDE(hash.telefone[i]);
    }
};

// Inicializa as listas duplamente encadeadas de cada campo da struct AluguelLivrosHash
template<typename T>
void inicializarAluguelLivrosLDE(AluguelLivrosHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        inicializarLDE(hash.matriculaUsuario[i]);
        inicializarLDE(hash.matriculaLivro[i]);
        inicializarLDE(hash.dataEmprestimo[i]);
        inicializarLDE(hash.dataDevolucao[i]);
    }
};

// Inicializa as listas duplamente encadeadas de cada campo da struct AluguelRevistasHash
template<typename T>
void inicializarAluguelRevistasLDE(AluguelRevistasHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        inicializarLDE(hash.matriculaUsuario[i]);
        inicializarLDE(hash.matriculaRevista[i]);
        inicializarLDE(hash.dataEmprestimo[i]);
        inicializarLDE(hash.dataDevolucao[i]);
    }
};

// Verifica o número de cada caractere ASCII de uma string e retorna a soma e retorna o total
int somarCaracteres(string str){
    int soma = 0;
    for(size_t i = 0; i < str.length(); i++){
        soma += (int)str[i];
    }
    return soma;
};

int converterHash(int valor){
    return valor % 100;
}

// Insere um livro e faz a hash de cada campo da struct Livro
template<typename T>
bool inserirLivro(LivroHash<T> &hash, int matricula, string titulo, string autor[3], string editora, string assunto){
    Livro *livro = new Livro;

    livro->matricula = matricula;
    livro->titulo = titulo;
    for(int i = 0; i < 3; i++){
        livro->autor[i] = autor[i];
    }
    livro->editora = editora;
    livro->assunto = assunto;

    HashLivro hashLivro;
    hashLivro.livro = livro;

    hashLivro.info = converterHash(matricula);
    inserirLDE(hash.matricula[converterHash(matricula)], hashLivro);

    hashLivro.info = converterHash(somarCaracteres(titulo));
    inserirLDE(hash.titulo[converterHash(somarCaracteres(titulo))], hashLivro);

    for(int i = 0; i < 3; i++){
        hashLivro.info = converterHash(somarCaracteres(autor[i]));
        inserirLDE(hash.autor[converterHash(somarCaracteres(autor[i]))], hashLivro);
    }

    hashLivro.info = converterHash(somarCaracteres(editora));
    inserirLDE(hash.editora[converterHash(somarCaracteres(editora))], hashLivro);

    hashLivro.info = converterHash(somarCaracteres(assunto));
    inserirLDE(hash.assunto[converterHash(somarCaracteres(assunto))], hashLivro);

    return true;
}

// Insere uma revista e faz a hash de cada campo da struct Revista
template<typename T>
bool inserirRevista(RevistaHash<T> &hash, int matricula, string titulo, string
editora, string assunto){
    Revista *revista = new Revista;

    revista->matricula = matricula;
    revista->titulo = titulo;
    revista->editora = editora;
    revista->assunto = assunto;

    HashRevista hashRevista;
    hashRevista.revista = revista;

    hashRevista.info = converterHash(matricula);
    inserirLDE(hash.matricula[converterHash(matricula)], hashRevista);

    hashRevista.info = converterHash(somarCaracteres(titulo));
    inserirLDE(hash.titulo[converterHash(somarCaracteres(titulo))], hashRevista);

    hashRevista.info = converterHash(somarCaracteres(editora));
    inserirLDE(hash.editora[converterHash(somarCaracteres(editora))], hashRevista);

    hashRevista.info = converterHash(somarCaracteres(assunto));
    inserirLDE(hash.assunto[converterHash(somarCaracteres(assunto))], hashRevista);

    return true;
}

template<typename T>
bool inserirUsuario(UsuarioHash<T> &hash, int matricula, string nome, string email, string telefone){
    Usuario *usuario = new Usuario;

    usuario->matricula = matricula;
    usuario->nome = nome;
    usuario->email = email;
    usuario->telefone = telefone;

    HashUsuario hashUsuario;
    hashUsuario.usuario = usuario;

    hashUsuario.info = converterHash(matricula);
    inserirLDE(hash.matricula[converterHash(matricula)], hashUsuario);

    hashUsuario.info = converterHash(somarCaracteres(nome));
    inserirLDE(hash.nome[converterHash(somarCaracteres(nome))], hashUsuario);

    hashUsuario.info = converterHash(somarCaracteres(email));
    inserirLDE(hash.email[converterHash(somarCaracteres(email))], hashUsuario);

    hashUsuario.info = converterHash(somarCaracteres(telefone));
    inserirLDE(hash.telefone[converterHash(somarCaracteres(telefone))], hashUsuario);

    return true;
}

// Pesquisa um livro pela matrícula
template<typename T>
Livro *pesquisarLivro(LivroHash<T> &hash, int matricula){
    No<T> *aux = procurarLDE(hash.matricula[converterHash(matricula)], converterHash(matricula));
    if(aux == NULL) return NULL;
    return aux->info.livro;
}

void mostrarUsuario(Usuario *usuario){
    cout << "Matrícula: " << usuario->matricula << endl;
    cout << "Nome: " << usuario->nome << endl;
    cout << "Email: " << usuario->email << endl;
    cout << "Telefone: " << usuario->telefone << endl;
}

void mostrarLivro(Livro *livro){
    cout << "Matrícula: " << livro->matricula << endl;
    cout << "Título: " << livro->titulo << endl;
    cout << "Autor: ";
    for(int i = 0; i < 3; i++){
        cout << livro->autor[i] << " ";
    }
    cout << endl;
    cout << "Editora: " << livro->editora << endl;
    cout << "Assunto: " << livro->assunto << endl;
}

void mostrarAluguelLivros(aluguelLivros *aluguel){
    cout << "ID: " << aluguel->id << endl;
    cout << "Matrícula do Usuário: " << aluguel->matriculaUsuario << endl;
    cout << "Matrícula do Livro: " << aluguel->matriculaLivro << endl;
    cout << "Data de Empréstimo: " << aluguel->dataEmprestimo << endl;
    cout << "Data de Devolução: " << aluguel->dataDevolucao << endl;
}

void mostrarRevista(Revista *revista){
    cout << "Matrícula: " << revista->matricula << endl;
    cout << "Título: " << revista->titulo << endl;
    cout << "Editora: " << revista->editora << endl;
    cout << "Assunto: " << revista->assunto << endl;
}

void mostrarAluguelRevistas(aluguelRevistas *aluguel){
    cout << "ID: " << aluguel->id << endl;
    cout << "Matrícula do Usuário: " << aluguel->matriculaUsuario << endl;
    cout << "Matrícula da Revista: " << aluguel->matriculaRevista << endl;
    cout << "Data de Empréstimo: " << aluguel->dataEmprestimo << endl;
    cout << "Data de Devolução: " << aluguel->dataDevolucao << endl;
}

// Buscar livros por matrícula
void pesquisarLivroPorMatricula(LivroHash<HashLivro> &hash, int matricula) {
    No<HashLivro> *aux = hash.matricula[converterHash(matricula)].comeco;
    while (aux != NULL) {
        if (aux->info.livro->matricula == matricula) {
            mostrarLivro(aux->info.livro);
            return;
        }
        aux = aux->eloP;
    }
    cout << "Livro não encontrado." << endl;
}

// Buscar livros por título
void pesquisarLivroPorTitulo(LivroHash<HashLivro> &hash, string titulo) {
    No<HashLivro> *aux = hash.titulo[converterHash(somarCaracteres(titulo))].comeco;
    while (aux != NULL) {
        if (aux->info.livro->titulo == titulo) {
            mostrarLivro(aux->info.livro);
        }
        aux = aux->eloP;
    }
}

// Buscar livros por autor
void pesquisarLivroPorAutor(LivroHash<HashLivro> &hash, string autor) {
    No<HashLivro> *aux = hash.autor[converterHash(somarCaracteres(autor))].comeco;
    while (aux != NULL) {
        if (aux->info.livro->autor[0] == autor || aux->info.livro->autor[1] == autor || aux->info.livro->autor[2] == autor) {
            mostrarLivro(aux->info.livro);
        }
        aux = aux->eloP;
    }
}

// Buscar livros por editora
void pesquisarLivroPorEditora(LivroHash<HashLivro> &hash, string editora) {
    No<HashLivro> *aux = hash.editora[converterHash(somarCaracteres(editora))].comeco;
    while (aux != NULL) {
        if (aux->info.livro->editora == editora) {
            mostrarLivro(aux->info.livro);
        }
        aux = aux->eloP;
    }
}

// Buscar livros por assunto
void pesquisarLivroPorAssunto(LivroHash<HashLivro> &hash, string assunto) {
    No<HashLivro> *aux = hash.assunto[converterHash(somarCaracteres(assunto))].comeco;
    while (aux != NULL) {
        if (aux->info.livro->assunto == assunto) {
            mostrarLivro(aux->info.livro);
        }
        aux = aux->eloP;
    }
}

// Pesquisar revistas por matrícula
void pesquisarRevistaPorMatricula(RevistaHash<HashRevista> &hash, int matricula) {
    No<HashRevista> *aux = hash.matricula[converterHash(matricula)].comeco;
    while (aux != NULL) {
        if (aux->info.revista->matricula == matricula) {
            mostrarRevista(aux->info.revista);
            return;
        }
        aux = aux->eloP;
    }
    cout << "Revista não encontrada." << endl;
};

// Pesquisar revistas por título
void pesquisarRevistaPorTitulo(RevistaHash<HashRevista> &hash, string titulo) {
    No<HashRevista> *aux = hash.titulo[converterHash(somarCaracteres(titulo))].comeco;
    while (aux != NULL) {
        if (aux->info.revista->titulo == titulo) {
            mostrarRevista(aux->info.revista);
        }
        aux = aux->eloP;
    }
};

// Pesquisar revistas por editora
void pesquisarRevistaPorEditora(RevistaHash<HashRevista> &hash, string editora) {
    No<HashRevista> *aux = hash.editora[converterHash(somarCaracteres(editora))].comeco;
    while (aux != NULL) {
        if (aux->info.revista->editora == editora) {
            mostrarRevista(aux->info.revista);
        }
        aux = aux->eloP;
    }
};

// Pesquisar revistas por assunto
void pesquisarRevistaPorAssunto(RevistaHash<HashRevista> &hash, string assunto) {
    No<HashRevista> *aux = hash.assunto[converterHash(somarCaracteres(assunto))].comeco;
    while (aux != NULL) {
        if (aux->info.revista->assunto == assunto) {
            mostrarRevista(aux->info.revista);
        }
        aux = aux->eloP;
    }
};

// Pesquisar todos os Livros e Revistas pelo Autor ou Editora (Mesmo campo)
void pesquisarPorAutorOuEditora(LivroHash<HashLivro> &livroHash, RevistaHash<HashRevista> &revistaHash, string termo) {
    int hashIndex = converterHash(somarCaracteres(termo));

    // Buscar livros por autor
    cout << "Livros encontrados por autor:" << endl;
    No<HashLivro> *auxLivro = livroHash.autor[hashIndex].comeco;
    while (auxLivro != NULL) {
        if (auxLivro->info.livro->autor[0] == termo || auxLivro->info.livro->autor[1] == termo || auxLivro->info.livro->autor[2] == termo) {
            mostrarLivro(auxLivro->info.livro);
        }
        auxLivro = auxLivro->eloP;
    }

    // Buscar livros por editora
    cout << "Livros encontrados por editora:" << endl;
    auxLivro = livroHash.editora[hashIndex].comeco;
    while (auxLivro != NULL) {
        if (auxLivro->info.livro->editora == termo) {
            mostrarLivro(auxLivro->info.livro);
        }
        auxLivro = auxLivro->eloP;
    }

    // Buscar revistas por editora
    cout << "Revistas encontradas por editora:" << endl;
    No<HashRevista> *auxRevista = revistaHash.editora[hashIndex].comeco;
    while (auxRevista != NULL) {
        if (auxRevista->info.revista->editora == termo) {
            mostrarRevista(auxRevista->info.revista);
        }
        auxRevista = auxRevista->eloP;
    }
};

// Pesquisar todos os Livros e Revistas pelo Assunto
void pesquisarPorAssunto(LivroHash<HashLivro> &livroHash, RevistaHash<HashRevista> &revistaHash, string termo) {
    int hashIndex = converterHash(somarCaracteres(termo));

    // Buscar livros por assunto
    cout << "Livros encontrados por assunto:" << endl;
    No<HashLivro> *auxLivro = livroHash.assunto[hashIndex].comeco;
    while (auxLivro != NULL) {
        if (auxLivro->info.livro->assunto == termo) {
            mostrarLivro(auxLivro->info.livro);
        }
        auxLivro = auxLivro->eloP;
    }

    // Buscar revistas por assunto
    cout << "Revistas encontradas por assunto:" << endl;
    No<HashRevista> *auxRevista = revistaHash.assunto[hashIndex].comeco;
    while (auxRevista != NULL) {
        if (auxRevista->info.revista->assunto == termo) {
            mostrarRevista(auxRevista->info.revista);
        }
        auxRevista = auxRevista->eloP;
    }
}

// Função para converter string de data para struct tm
tm stringParaData(const string &data) {
    tm tm = {};
    sscanf(data.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    tm.tm_year -= 1900; // Adjust year
    tm.tm_mon -= 1; // Adjust month
    return tm;
}

// Função para calcular a diferença em dias entre duas datas
int diferencaDias(const tm &data1, const tm &data2) {
    time_t time1 = mktime(const_cast<tm *>(&data1));
    time_t time2 = mktime(const_cast<tm *>(&data2));
    return difftime(time1, time2) / (60 * 60 * 24);
}

void livrosRevistasAtraso(AluguelLivrosHash<hashAluguelLivros> &aluguelLivrosHash, AluguelRevistasHash<hashAluguelRevistas> &aluguelRevistasHash, LivroHash<HashLivro> &livroHash, RevistaHash<HashRevista> &revistaHash) {
    cout << "Livros em atraso de devolução:" << endl;

    for (int i = 0; i < tamanho; i++) {
        No<hashAluguelLivros> *auxAluguel = aluguelLivrosHash.dataDevolucao[i].comeco;

        auto now = system_clock::now();
        time_t timeNow = system_clock::to_time_t(now);
        tm dataAtual = *localtime(&timeNow);

        while (auxAluguel != NULL) {
            tm dataDevolucao = stringParaData(auxAluguel->info.aluguel->dataDevolucao);

            if (diferencaDias(dataAtual, dataDevolucao) > 7) {
                Livro *livro = pesquisarLivro(livroHash, auxAluguel->info.aluguel->matriculaLivro);
                if (livro != NULL) {
                    mostrarLivro(livro);
                }
            }
            auxAluguel = auxAluguel->eloP;
        }
    }

    cout << "Revistas em atraso de devolução:" << endl;
    for (int i = 0; i < tamanho; i++) {
        No<hashAluguelRevistas> *auxAluguel = aluguelRevistasHash.dataDevolucao[i].comeco;

        auto now = system_clock::now();
        time_t timeNow = system_clock::to_time_t(now);
        tm dataAtual = *localtime(&timeNow);

        while (auxAluguel != NULL) {
            tm dataDevolucao = stringParaData(auxAluguel->info.aluguel->dataDevolucao);

            if (diferencaDias(dataAtual, dataDevolucao) > 7) {
                // Corrige a chamada para mostrar diretamente a revista
                pesquisarRevistaPorMatricula(revistaHash, auxAluguel->info.aluguel->matriculaRevista);
            }
            auxAluguel = auxAluguel->eloP;
        }
    }
}


// Função para pesquisar aluguel de livro por usuário e retornar ponteiro
template<typename T>
aluguelLivros* buscarAluguelLivroPorUsuario(AluguelLivrosHash<T> &hash, int matriculaUsuario) {
    No<T> *aux = hash.matriculaUsuario[converterHash(matriculaUsuario)].comeco;
    while (aux != NULL) {
        if (aux->info.aluguel->matriculaUsuario == matriculaUsuario) {
            return aux->info.aluguel;
        }
        aux = aux->eloP;
    }
    return NULL;
}

// Função para pesquisar aluguel de revista por usuário e retornar ponteiro
template<typename T>
aluguelRevistas* buscarAluguelRevistaPorUsuario(AluguelRevistasHash<T> &hash, int matriculaUsuario) {
    No<T> *aux = hash.matriculaUsuario[converterHash(matriculaUsuario)].comeco;
    while (aux != NULL) {
        if (aux->info.aluguel->matriculaUsuario == matriculaUsuario) {
            return aux->info.aluguel;
        }
        aux = aux->eloP;
    }
    return NULL;
}


// Função para pesquisar usuário pela matrícula
template<typename T>
Usuario* pesquisarUsuario(UsuarioHash<T> &hash, int matricula) {
    No<T> *aux = hash.matricula[converterHash(matricula)].comeco;
    while (aux != NULL) {
        if (aux->info.usuario->matricula == matricula) {
            return aux->info.usuario;
        }
        aux = aux->eloP;
    }
    return NULL;
}

// Função para remover um usuário pela matrícula
template<typename T>
bool retirarUsuario(UsuarioHash<T> &hash, int matricula) {
    // Primeiro, pesquisa o usuário para verificar se ele existe
    Usuario *usuarioEncontrado = pesquisarUsuario(hash, matricula);
    if (usuarioEncontrado == NULL) {
        cout << "Usuário não encontrado para remoção." << endl;
        return false; // Usuário não encontrado, nada para remover
    }

    // Remove a entrada da hash de matrícula
    removerLDE(hash.matricula[converterHash(matricula)], matricula);

    // Remove a entrada da hash de nome
    removerLDE(hash.nome[converterHash(somarCaracteres(usuarioEncontrado->nome))], somarCaracteres(usuarioEncontrado->nome));

    // Remove a entrada da hash de e-mail
    removerLDE(hash.email[converterHash(somarCaracteres(usuarioEncontrado->email))], somarCaracteres(usuarioEncontrado->email));

    // Remove a entrada da hash de telefone
    removerLDE(hash.telefone[converterHash(somarCaracteres(usuarioEncontrado->telefone))], somarCaracteres(usuarioEncontrado->telefone));

    // Libera a memória do usuário removido
    delete usuarioEncontrado;

    cout << "Usuário removido com sucesso." << endl;
    return true;
}


// Remove um usuario pela matrícula e exclui a hash de cada campo da struct Usuario
template<typename T>
bool retirarUsuario(UsuarioHash<HashUsuario> &hash, int matricula){
    Usuario *usuarioEncontrado = pesquisarUsuario(hash, matricula);
    if(usuarioEncontrado == NULL) return false;

    removerLDE(hash.matricula[converterHash(matricula)], converterHash(matricula));

    removerLDE(hash.nome[converterHash(somarCaracteres(usuarioEncontrado->nome))], converterHash(somarCaracteres(usuarioEncontrado->nome)));

    removerLDE(hash.email[converterHash(somarCaracteres(usuarioEncontrado->email))], converterHash(somarCaracteres(usuarioEncontrado->email)));

    removerLDE(hash.telefone[converterHash(somarCaracteres(usuarioEncontrado->telefone))], converterHash(somarCaracteres(usuarioEncontrado->telefone)));

    return true;
}

// Remove um livro pela matrícula e exclui a hash de cada campo da struct Livro
template<typename T>
bool retirarLivro(LivroHash<T> &hash, int matricula){
    Livro *livroEncontrado = pesquisarLivro(hash, matricula);
    if(livroEncontrado == NULL) return false;

    removerLDE(hash.matricula[converterHash(matricula)], converterHash(matricula));

    removerLDE(hash.titulo[converterHash(somarCaracteres(livroEncontrado->titulo))], converterHash(somarCaracteres(livroEncontrado->titulo)));

    for(int i = 0; i < 3; i++){
        removerLDE(hash.autor[converterHash(somarCaracteres(livroEncontrado->autor[i]))], converterHash(somarCaracteres(livroEncontrado->autor[i])));
    }

    removerLDE(hash.editora[converterHash(somarCaracteres(livroEncontrado->editora))], converterHash(somarCaracteres(livroEncontrado->editora)));

    removerLDE(hash.assunto[converterHash(somarCaracteres(livroEncontrado->assunto))], converterHash(somarCaracteres(livroEncontrado->assunto)));

    return true;
};

template<typename T>
bool retirarRevista(RevistaHash<T> &hash, int matricula){
    No<T> *aux = hash.matricula[converterHash(matricula)].comeco;
    Revista *revistaEncontrada = NULL;
    while (aux != NULL) {
        if (aux->info.revista->matricula == matricula) {
            revistaEncontrada = aux->info.revista;
            break;
        }
        aux = aux->eloP;
    }
    if(revistaEncontrada == NULL) return false;

    removerLDE(hash.matricula[converterHash(matricula)], converterHash(matricula));

    removerLDE(hash.titulo[converterHash(somarCaracteres(revistaEncontrada->titulo))], converterHash(somarCaracteres(revistaEncontrada->titulo)));

    removerLDE(hash.editora[converterHash(somarCaracteres(revistaEncontrada->editora))], converterHash(somarCaracteres(revistaEncontrada->editora)));

    removerLDE(hash.assunto[converterHash(somarCaracteres(revistaEncontrada->assunto))], converterHash(somarCaracteres(revistaEncontrada->assunto)));

    return true;
};

// Editar um livro e todas as suas hashs pela matrícula
bool editarLivro(LivroHash<HashLivro> &hash, int matricula, string titulo, string autor[3], string editora, string assunto){
    retirarLivro(hash, matricula);
    inserirLivro(hash, matricula, titulo, autor, editora, assunto);

    return true;
};

// Editar uma revista e todas as suas hashs pela matrícula
bool editarRevista(RevistaHash<HashRevista> &hash, int matricula, string titulo, string editora, string assunto){
    Revista *revistaEncontrada = NULL;
    pesquisarRevistaPorMatricula(hash, matricula);
    if(revistaEncontrada == NULL) return false;

    retirarRevista(hash, matricula);

    inserirRevista(hash, matricula, titulo, editora, assunto);

    return true;
};

// mostra todos os usuários
template<typename T>
void mostrarUsuarios(UsuarioHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        No<T> *aux = hash.matricula[i].comeco;
        while(aux != NULL){
            cout << "Matrícula: " << aux->info.usuario->matricula << endl;
            cout << "Nome: " << aux->info.usuario->nome << endl;
            cout << "Email: " << aux->info.usuario->email << endl;
            cout << "Telefone: " << aux->info.usuario->telefone << endl;
            cout << endl;
            aux = aux->eloP;
        }
    }
}

// mostra todos os livros
template<typename T>
void mostrarLivros(LivroHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        No<T> *aux = hash.matricula[i].comeco;
        while(aux != NULL){
            cout << "Matrícula: " << aux->info.livro->matricula << endl;
            cout << "Título: " << aux->info.livro->titulo << endl;
            cout << "Autor: ";
            for(int j = 0; j < 3; j++){
                cout << aux->info.livro->autor[j] << " ";
            }
            cout << endl;
            cout << "Editora: " << aux->info.livro->editora << endl;
            cout << "Assunto: " << aux->info.livro->assunto << endl;
            cout << endl;
            aux = aux->eloP;
        }
    }
}

// mostra todas as revistas
template<typename T>
void mostrarRevistas(RevistaHash<T> &hash){
    for(int i = 0; i < tamanho; i++){
        No<T> *aux = hash.matricula[i].comeco;
        while(aux != NULL){
            cout << "Matrícula: " << aux->info.revista->matricula << endl;
            cout << "Título: " << aux->info.revista->titulo << endl;
            cout << "Editora: " << aux->info.revista->editora << endl;
            cout << "Assunto: " << aux->info.revista->assunto << endl;
            cout << endl;
            aux = aux->eloP;
        }
    }
};

// Locar livros, armazenar em Hash apenas id e matriculas usuario e livro
template<typename T>
bool locarLivro(AluguelLivrosHash<T> &hash, int id, int matriculaUsuario, int matriculaLivro, string dataEmprestimo, string dataDevolucao){
    aluguelLivros *aluguel = new aluguelLivros;

    aluguel->id = id;
    aluguel->matriculaUsuario = matriculaUsuario;
    aluguel->matriculaLivro = matriculaLivro;
    aluguel->dataEmprestimo = dataEmprestimo;
    aluguel->dataDevolucao = dataDevolucao;

    hashAluguelLivros hashAluguel;
    hashAluguel.aluguel = aluguel;

    hashAluguel.info = converterHash(id);
    inserirLDE(hash.id[converterHash(id)], hashAluguel);

    hashAluguel.info = converterHash(matriculaUsuario);
    inserirLDE(hash.matriculaUsuario[converterHash(matriculaUsuario)], hashAluguel);

    hashAluguel.info = converterHash(matriculaLivro);
    inserirLDE(hash.matriculaLivro[converterHash(matriculaLivro)], hashAluguel);

    hashAluguel.info = converterHash(somarCaracteres(dataEmprestimo));
    inserirLDE(hash.dataEmprestimo[converterHash(somarCaracteres(dataEmprestimo))], hashAluguel);

    hashAluguel.info = converterHash(somarCaracteres(dataDevolucao));
    inserirLDE(hash.dataDevolucao[converterHash(somarCaracteres(dataDevolucao))], hashAluguel);

    return true;
};

// Locar revistas, armazenar em Hash apenas id e matriculas usuario e revista
bool locarRevista(AluguelRevistasHash<hashAluguelRevistas> &hash, int id, int matriculaUsuario, int matriculaRevista, string dataEmprestimo, string dataDevolucao){
    aluguelRevistas *aluguel = new aluguelRevistas;

    aluguel->id = id;
    aluguel->matriculaUsuario = matriculaUsuario;
    aluguel->matriculaRevista = matriculaRevista;
    aluguel->dataEmprestimo = dataEmprestimo;
    aluguel->dataDevolucao = dataDevolucao;

    hashAluguelRevistas hashAluguel;
    hashAluguel.aluguel = aluguel;

    hashAluguel.info = converterHash(id);
    inserirLDE(hash.id[converterHash(id)], hashAluguel);

    hashAluguel.info = converterHash(matriculaUsuario);
    inserirLDE(hash.matriculaUsuario[converterHash(matriculaUsuario)], hashAluguel);

    hashAluguel.info = converterHash(matriculaRevista);
    inserirLDE(hash.matriculaRevista[converterHash(matriculaRevista)], hashAluguel);

    hashAluguel.info = converterHash(somarCaracteres(dataEmprestimo));
    inserirLDE(hash.dataEmprestimo[converterHash(somarCaracteres(dataEmprestimo))], hashAluguel);

    hashAluguel.info = converterHash(somarCaracteres(dataDevolucao));
    inserirLDE(hash.dataDevolucao[converterHash(somarCaracteres(dataDevolucao))], hashAluguel);

    return true;
};

// Pesquisar aluguel de livro por id
template<typename T>
aluguelLivros *pesquisarAluguelLivro(AluguelLivrosHash<hashAluguelLivros> &hash, int id){
    No<T> *aux = procurarLDE(hash.id[converterHash(id)], converterHash(id));
    if(aux == NULL) return NULL;
    return aux->info.aluguel;
};

// Pesquisar aluguel de revista por id
aluguelRevistas* pesquisarAluguelRevista(AluguelRevistasHash<hashAluguelRevistas> &hash, int id){
    No<hashAluguelRevistas> *aux = procurarLDE(hash.id[converterHash(id)], converterHash(id));
    if(aux == NULL) return NULL;
    return aux->info.aluguel;
};

// Pesquisar aluguel de livro por usuario
template<typename T>
aluguelLivros *pesquisarAluguelLivroPorUsuario(AluguelLivrosHash<T> &hash, int matriculaUsuario){
    No<T> *aux = procurarLDE(hash.matriculaUsuario[converterHash(matriculaUsuario)], converterHash(matriculaUsuario));
    if(aux == NULL) return NULL;
    return aux->info.aluguel;
};

// Pesquisar aluguel de revista por usuario
template<typename T>
aluguelRevistas *pesquisarAluguelRevistaPorUsuario(AluguelRevistasHash<T> &hash, int matriculaUsuario){
    No<T> *aux = procurarLDE(hash.matriculaUsuario[converterHash(matriculaUsuario)], converterHash(matriculaUsuario));
    if(aux == NULL) return NULL;
    return aux->info.aluguel;
};


// Remover aluguel de livro por id
template<typename T>
bool retirarAluguelLivro(AluguelLivrosHash<T> &hash, int id){
    aluguelLivros *aluguelEncontrado = pesquisarAluguelLivro<hashAluguelLivros>(hash, id);
    if(aluguelEncontrado == NULL) return false;

    removerLDE(hash.id[converterHash(id)], converterHash(id));

    removerLDE(hash.matriculaUsuario[converterHash(aluguelEncontrado->matriculaUsuario)], converterHash(aluguelEncontrado->matriculaUsuario));

    removerLDE(hash.matriculaLivro[converterHash(aluguelEncontrado->matriculaLivro)], converterHash(aluguelEncontrado->matriculaLivro));

    removerLDE(hash.dataEmprestimo[converterHash(somarCaracteres(aluguelEncontrado->dataEmprestimo))], converterHash(somarCaracteres(aluguelEncontrado->dataEmprestimo)));

    removerLDE(hash.dataDevolucao[converterHash(somarCaracteres(aluguelEncontrado->dataDevolucao))], converterHash(somarCaracteres(aluguelEncontrado->dataDevolucao)));

    return true;
};

// Remover aluguel de revista por id
bool retirarAluguelRevista(AluguelRevistasHash<hashAluguelRevistas> &hash, int id){
    aluguelRevistas *aluguelEncontrado = pesquisarAluguelRevista(hash, id);
    if(aluguelEncontrado == NULL) return false;

    removerLDE(hash.id[converterHash(id)], converterHash(id));

    removerLDE(hash.matriculaUsuario[converterHash(aluguelEncontrado->matriculaUsuario)], converterHash(aluguelEncontrado->matriculaUsuario));

    removerLDE(hash.matriculaRevista[converterHash(aluguelEncontrado->matriculaRevista)], converterHash(aluguelEncontrado->matriculaRevista));

    removerLDE(hash.dataEmprestimo[converterHash(somarCaracteres(aluguelEncontrado->dataEmprestimo))], converterHash(somarCaracteres(aluguelEncontrado->dataEmprestimo)));

    removerLDE(hash.dataDevolucao[converterHash(somarCaracteres(aluguelEncontrado->dataDevolucao))], converterHash(somarCaracteres(aluguelEncontrado->dataDevolucao)));

    return true;
};

// Devolver livro
bool devolverLivro(AluguelLivrosHash<hashAluguelLivros> &hash, int id){
    aluguelLivros *aluguelEncontrado = pesquisarAluguelLivro<hashAluguelLivros>(hash, id);
    
    if(aluguelEncontrado == NULL) return false;

    retirarAluguelLivro(hash, id);

    return true;
};

// Devolver revista
bool devolverRevista(AluguelRevistasHash<hashAluguelRevistas> &hash, int id){
    aluguelRevistas *aluguelEncontrado = pesquisarAluguelRevista(hash, id);
    if(aluguelEncontrado == NULL) return false;

    retirarAluguelRevista(hash, id);

    return true;
};

// validar se a matricula do usuario existe, se tem mais de 4 digitos
bool validarMatricula(int matricula){
    if(matricula < 1000) return false;
    return true;
};

// validar matricula do livro
bool validarMatriculaLivro(int matricula){
    if(matricula < 1000) return false;
    return true;
};

// validar matricula da revista
bool validarMatriculaRevista(int matricula){
    if(matricula < 1000) return false;
    return true;
}

// gerar id para aluguel maximo 4 digitos
int gerarId(){
    return rand() % 10000;
}

#endif