#ifndef HASHTAG_H
#define HASHTAG_H

#define tamanhoHashtag 51

#include "../Manipuladores/manipuladorDeArquivo.h"
#include <fstream>
#include <iostream>

/**
*Esta classe é responsável por guardar informações de uma Hashtag da aplicação, e também pelos métodos de alterações destas (getters e setters)o
*/

class Hashtag : public manipuladorDeArquivo
{
    public:
        Hashtag();
        Hashtag(char hashtag[]);
        bool criaArquivosNescessarios();
        bool adicionaHashtagArquivo(Hashtag hashtag);
        bool verificaExistencia(Hashtag hashtag);

        char* Gethashtag();
        void Sethashtag(char* Hashtag);
        bool verificaFormato(char* Hashtag);
        void Setexiste(bool valor);
        bool Getexiste();

    private:
        char hashtag[tamanhoHashtag];
        bool existe = false; //Fala se têm uma hashtag ou não
};


#endif // HASHTAG_H
