#ifndef POSTAGEM_H
#define POSTAGEM_H

#define tamanhoTextoPostagens 401

#include "Hashtag.h"

/**
*Esta classe é responsável por guardar informações de uma postagem da aplicação, e também pelos métodos de alterações destas (getters e setters), ela é manipulada pelo manipuladorDePostagem
*/

class Postagem
{
    public:

        int GetIDusuario();
        void SetIDusuario(int val);
        char* Getconteudo();
        void Setconteudo(char conteudo[]);
        int GetnumeroPostagem();
        void SetnumeroPostagem(int val);
        int Getcurtidas();
        void Setcurtidas(int val);
        bool Getapagada();
        void Setapagada(bool val);
        Postagem(int ID, int numeroP, char conteudo[]);
        Postagem();
        bool existe();

        Hashtag hashtag;

    private:
        int IDusuario;
        int numeroPostagem;
        char conteudo[tamanhoTextoPostagens];
        int curtidas = 0;
        bool apagada=false;
};


#endif // POSTAGEM_H
