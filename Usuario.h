#ifndef USUARIO_H
#define USUARIO_H
#define tamanhoNome 50
#define tamanhoSenha 50
#include "Postagem.h"


class Usuario {
    public:
        int id;
        char nome[tamanhoNome];
        char senha[tamanhoSenha];
        Usuario(){
        }
};


#endif
