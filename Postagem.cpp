#include "Postagem.h"

class Postagem
{
    public:
        Postagem();



    private:
        int IDusuario;
        int numeroPostagem;
        char conteudo[200];
        int curtidas;
        bool apagada=false;
};

Postagem::Postagem()
{
    //ctor
}
