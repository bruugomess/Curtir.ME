#ifndef MANIPULADORDEUSUARIO_H
#define MANIPULADORDEUSUARIO_H

#include "Arquivo.h"
#include "Usuario.h"
#include <string>     // std::string, std::to_string
#include <iostream>
#include <list>


/**
*Está Classe é responsável por Manipular todos os documentos nescessários para o funcionamento dos usuários, e processos de arquivo relacionados a classe usuário, sendo seguir, cadastrar,e etc. Para isto nela são implemantados métodos importantes para a aplicação.
*/

using namespace std;
Usuario usuarioAtual;

class manipuladorDeUsuario {
public:
    Usuario procuraUsuarioId(int id);
    Usuario procuraUsuarioNome(char nome[]);
    void cadastrarUsuario(char nome[], char senha[]);
    bool autenticarUsuario(char nome[], char senha[]);
    int numeroDeUsuarios();
    void criaArquivosNescessarios();
    bool seguir(int idSeguidor, int idSeguido);
    bool seguir(int idSeguidor, char* nomeSeguidor);
    bool retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro);
    bool deixarDeSeguir(int idSeguidor, int idSeguido);
    bool deixarDeSeguir(int idSeguidor, char nomeSeguido[]);
    bool segue(int idSeguidor, int idSeguido);
    bool salvarUsuario(Usuario usuario);
    bool aumentarNumeroDeUsuarios();

private:

};



#endif // MANIPULADORDEUSUARIO_H

