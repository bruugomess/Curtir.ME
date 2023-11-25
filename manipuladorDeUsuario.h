#ifndef MANIPULADORDEUSUARIO_H
#define MANIPULADORDEUSUARIO_H

#include "Arquivo.h"
#include <string>     // std::string, std::to_string
#include <iostream>
#include <list>

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
    bool seguir(int idSeguidor, int idSeguido);
    bool seguir(int idSeguidor, char* nomeSeguidor);
    bool retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro);
    bool deixarDeSeguir(int idSeguidor, int idSeguido);
    bool deixarDeSeguir(int idSeguidor, char nomeSeguido[]);
    bool segue(int idSeguidor, int idSeguido);
    bool salvarUsuario(Usuario usuario);

private:

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe manipuladorDeUsuario                            */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Função que cria todos os documentos nescessarios para o funcionamento da aplicação
void manipuladorDeUsuario::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDeUsuariosCadastrados.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de usuários.");
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
            geraExcecao("Erro ao criar o arquivo de usuários.");
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
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);
    usuario.setId(this->numeroDeUsuarios()+1);

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    const char* idUsuario = to_string(usuario.getId()).c_str();
    //Cria arquivo de seguidores para o novo usuario

    char parte1[] = "Arquivos/Seguidores/Seguidores#";
    char parte2[] = ".bin";
    char *nomeArquivo = strcat(strcat(parte1,idUsuario),parte2);

    ifstream ifs(nomeArquivo);
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo(nomeArquivo, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidores.");
            return;
        }

        cout << "Arquivo de seguidores criado.\n";
        arquivo.close();
    }



    char parte1b[] = "Arquivos/Seguidores/Segue#";
    char *nomeArquivo2 = strcat(strcat(parte1b,idUsuario),parte2);
    ifstream ifs2(nomeArquivo2);
    if (!ifs2) { //Verifica se Existe o Arquivo
        arquivo.open(nomeArquivo2, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidos.");
            return;
        }

        system("pause");

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
        geraExcecao("Erro ao abrir o arquivo de usuários.");
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
        geraExcecao("Erro ao abrir o arquivo de numero de usuários.");
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
        geraExcecao("Erro ao abrir o arquivo de numero de usuários.");
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
        geraExcecao("Erro ao abrir o arquivo de usuários.");
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
        geraExcecao("Erro ao abrir o arquivo de usuários.");
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

/*Parte de Seguidores*/


bool manipuladorDeUsuario::seguir(int idSeguidor, int idSeguido){
    if(this->segue(idSeguidor, idSeguido)){
        cout << "Você já segue este usuario\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ofstream arquivo(nomeArquivoSeguidor, ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguidor));
        return false;
    }

    arquivo.write((char*)&idSeguido, sizeof(int));
    arquivo.close();

    //Adiciona no arquivo "Seguidor"
    arquivo.open(nomeArquivoSeguido, ios::binary | ios::app);
    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguido));
        return false;
    }

    arquivo.write((char*)&idSeguidor, sizeof(int));
    arquivo.close();

    return true;
}

bool manipuladorDeUsuario::seguir(int idSeguidor, char* nomeSeguidor){
    if(this->procuraUsuarioNome(nomeSeguidor).existe()){
        return this->seguir(idSeguidor, this->procuraUsuarioNome(nomeSeguidor).getId());
    }else{
        cout << "O usuário com este nome não existe\n\n";
    }

    return false;
}

/*Retira um numero inteiro de algum arquivo utilizado para guardar inteiros*/
bool manipuladorDeUsuario::retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro){
    bool encontrado = false;
    fstream arquivo(nomeArquivo, ios::binary | std::ios::in | std::ios::out); //Abre arquivo
    ofstream arquivoAux("Arquivos/aux.bin", ios::binary | ios::app); //Abre arquivo auxiliar
    limparArquivoBinario("Arquivos/aux.bin");

    int valorAtual;

    if (!arquivoAux.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", "aux.bin"));
        return false;
    }

    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivo));
        return false;
    }else{
            while (arquivo.read((char*)&valorAtual, sizeof(int))) {

                if (inteiro == valorAtual) {
                    cout << "Encontrado!" << endl;
                    encontrado = true;
                    break;
                }
                arquivoAux.write((char*)&valorAtual, sizeof(int));
            }

            if(!encontrado){
                geraExcecao(strcat("Inteiro não encontrado no arquivo", nomeArquivo));
                return false;
            }else{
                copiarArquivo(nomeArquivo, "Arquivos/aux.bin");

            }

    }

    arquivoAux.close();
    arquivo.close();
    return true;
}


bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, int idSeguido){
    if(!this->segue(idSeguidor, idSeguido)){
        cout << "Você não segue este usuario.\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Retira do arquivo "Segue"

    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguidor, idSeguido)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }
    //Retira do arquivo "Seguidor"
    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguido, idSeguidor)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }

    if(this->segue(idSeguidor, idSeguido)){
        geraExcecao("Erro ao deixar de seguir!\n");
        return false;
    }

    return true;
}

bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, char nomeSeguido[]){
    if(this->procuraUsuarioNome(nomeSeguido).existe()){
        return this->deixarDeSeguir(idSeguidor, this->procuraUsuarioNome(nomeSeguido).getId());
    }else{
        geraExcecao("O usuário com este nome não existe\n\n");
    }

    return false;
}

bool manipuladorDeUsuario::segue(int idSeguidor, int idSeguido){
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);


    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    Usuario seguidor = this->procuraUsuarioId(idSeguidor);

    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ifstream arquivo(nomeArquivoSeguidor, ios::binary);
    int id;
    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguidor));
        return false;
    }else{

        while (arquivo.read((char*)&id, sizeof(int))) {

            if (id == idSeguido) {
                arquivo.close();
                return true;
            }
        }
    }

    return false;
}

bool manipuladorDeUsuario::salvarUsuario(Usuario usuario){
    fstream arquivo("Arquivos/usuarios.bin", ios::binary | std::ios::in | std::ios::out);
    Usuario userAux;
    int i = 0;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return false;
    }else{

        while (arquivo.read((char*)&userAux, sizeof(Usuario))) {
            if (userAux.getId() == usuario.getId()) {
                break;
            }
            i++;
        }

    }

    arquivo.seekg(i*sizeof(Usuario), ios_base::beg);
    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    return true;
}
/*Parte de Usuarios*/


#endif // MANIPULADORDEUSUARIO_H

