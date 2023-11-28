#ifndef MANIPULADORDEPOSTAGEM_H
#define MANIPULADORDEPOSTAGEM_H

#include "../ClassesPrincipais/Postagem.h"
#include "manipuladorDeArquivo.h"
#include "manipuladorDeUsuario.h"
#include "manipuladorDeComentario.h"

/**
*Está Classe é responsável por Manipular todos os documentos nescessários para o funcionamento das postagens e processos de arquivo relacionados a classe Postagem, para isto nela são implemantados métodos importantes para a aplicação.
*/

class manipuladorDePostagem : public manipuladorDeArquivo
{
    public:
        void criaArquivosNescessarios();
        void mostrarFeed();
        void mostrarFeedDosSeguidos(int idUsuarioAtual);
        void mostrarFeedPorHashtag(char hashtag[]);
        bool adicionaAoArquivo(Postagem post);
        bool aumentarNumeroDePostagens();
        bool ehMinhaPostagem(int idUsuario, int numeroPostagem);
        bool apagarPostagem(int numeroPostagem);
        int numeroDePostagens();
        bool salvaPostagem(Postagem post);
        Postagem buscaPostagem(int numeroPostagem);
        bool adicionaCurtida(Postagem post);
        void detalhar(int numeroPostagem);

    private:
};


#endif // MANIPULADORDEPOSTAGEM_H
