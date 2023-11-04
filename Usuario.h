#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>

#define tamanhoNome 50
#define tamanhoSenha 50

class Usuario {
public:
    int getId() const;
    char* getSenha() const;
    char* getNome() const;
    void setNome(char nome[]);
    void setSenha(char senha[]);
    void setId(int novoId);
    void limpaUsuario();
    bool existe();

    Usuario();
private:
    int id;
    char nome[tamanhoNome];
    char senha[tamanhoSenha];
};

int Usuario::getId() const {
    return id;
}

char* Usuario::getSenha() const {
    int tamanho = strlen(senha);
    char* copia = new char[tamanho + 1];
    strcpy(copia, senha);
    return copia;
}

char* Usuario::getNome() const {
    int tamanho = strlen(nome);
    char* copia = new char[tamanho + 1];
    strcpy(copia, nome);
    return copia;
}

void Usuario::setNome(char nome[]) {
    strcpy(this->nome, nome);
}

void Usuario::setSenha(char senha[]) {
    strcpy(this->senha, senha);
}

void Usuario::setId(int novoId){
    this->id = novoId;
}
Usuario::Usuario(){
    strcpy(this->nome, "");
    strcpy(this->senha, "");
}

bool Usuario::existe()
{
    return strcmp(this->getNome(), "") == 0 || strcmp(this->getSenha(), "") == 0 ?  false : true;
}

void Usuario::limpaUsuario()
{
    this->id = 0;
    strcpy(this->nome, "");
    strcpy(this->senha, "");
}

#endif // USUARIO_H
