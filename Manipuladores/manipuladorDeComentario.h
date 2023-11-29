#ifndef MANIPULADORDECOMENTARIO_H
#define MANIPULADORDECOMENTARIO_H

#include "manipuladorDeUsuario.h"
#include "../ClassesPrincipais/Comentario.h"

#define mostrarTodos -1 // Utilizado no metodo exibirComentariosPorId()

/**
*Está Classe é responsável por Manipular todos os documentos nescessários para o funcionamento dos comentários e processos de arquivo relacionados a classe Comentario, sendo adicionar comentário, printaComentario,e etc. Para isto nela são implemantados métodos importantes para a aplicação.
*/

class manipuladorDeComentario : public manipuladorDeArquivo
{
    public:
        manipuladorDeComentario();
        void criaArquivosNescessarios();
        bool adicionaAoArquivo(Comentario coment);
        void printaComentario(Comentario coment);
        void exibirComentariosPorId(int idPost, int quantidade);


    private:
};

#endif // MANIPULADORDECOMENTARIO_H
