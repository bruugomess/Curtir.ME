#ifndef MANIPULADORDEUSUARIO_H
#define MANIPULADORDEUSUARIO_H

#include "Arquivo.h"
#include <string>     // std::string, std::to_string

using namespace std;
Usuario usuarioAtual;

class manipuladorDeUsuario {
public:
    Usuario procuraUsuarioId(int id);
    Usuario procuraUsuarioNome(char nome[]);
    void cadastrarUsuario(char nome[], char senha[]);
    bool autenticarUsuario(char nome[], char senha[]);
    int numeroDeUsuarios();
    int aumentarNumeroDeUsuarios();
    void criaArquivosNescessarios();
private:

};

//Função que cria todos os documentos nescessarios para o funcionamento da aplicação
void manipuladorDeUsuario::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDeUsuariosCadastrados.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de numero de usuários." << endl;
            return;
        }
        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }

    //Arquivos de usuarios
    ifstream ifs2("Arquivos/usuarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de usuários." << endl;
            return;
        }
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }
}


/*Parte de Usuarios*/

void manipuladorDeUsuario::cadastrarUsuario(char nome[], char senha[]) {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);
    usuario.setId(this->numeroDeUsuarios()+1);

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();

    //Cria arquivo de seguidores para o novo usuario
    char parte1[] = "Arquivos/Seguidores/S#";
    char parte2[] = ".bin";
    char *nomeArquivo = strcat(strcat(parte1,to_string(usuario.getId()).c_str()),parte2);

    ifstream ifs(nomeArquivo);
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo(nomeArquivo, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de numero de usuários." << endl;
            return;
        }
        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        arquivo.write((char*)&numeroInicial, sizeof(int));

        cout << "Arquivo de seguidores criado.\n";
        arquivo.close();
    }


    cout << "Usuário cadastrado com sucesso." << endl;
    this->aumentarNumeroDeUsuarios();
}

bool manipuladorDeUsuario::autenticarUsuario(char nome[], char senha[]) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
        return false;
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0 && strcmp(usuario.getSenha(),senha) == 0) {
                usuarioAtual = usuario;
                arquivo.close();
                return true;
            }
        }
    }

    arquivo.close();

    return false;
}


int manipuladorDeUsuario::numeroDeUsuarios(){
    ifstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de numero de usuários." << endl;
        return 0;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
        arquivo.close();
        return numero;
    }
}

int manipuladorDeUsuario::aumentarNumeroDeUsuarios(){
    int numero = numeroDeUsuarios()+1;
    limparArquivoBinario("Arquivos/numeroDeUsuariosCadastrados.bin");
    //Aumenta numero de usuarios cadastrados
    ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de numero de usuários." << endl;
        return 1;
    }

    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return 0;
}


Usuario manipuladorDeUsuario::procuraUsuarioId(int id) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (usuario.getId() == id) {
                arquivo.close();

                return usuario;
            }
        }
    }

    arquivo.close();


    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}

Usuario manipuladorDeUsuario::procuraUsuarioNome(char nome[]){
    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0) {
                arquivo.close();

                return usuario;
            }
        }
    }


    arquivo.close();

    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}


/*Parte de Usuarios*/


#endif // MANIPULADORDEUSUARIO_H

