#ifndef MANIPULADORDEUSUARIO_H
#define MANIPULADORDEUSUARIO_H

#include "manipuladorDeArquivo.h"
#include "../ClassesPrincipais/Usuario.h"
#include <string>     // std::string, std::to_string
#include <iostream>
#include <list>


/**
*Est� Classe � respons�vel por Manipular todos os documentos nescess�rios para o funcionamento dos usu�rios, e processos de arquivo relacionados a classe usu�rio, sendo seguir, cadastrar,e etc. Para isto nela s�o implemantados m�todos importantes para a aplica��o.
*/

using namespace std;
Usuario usuarioAtual;

class manipuladorDeUsuario : public manipuladorDeArquivo{
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

