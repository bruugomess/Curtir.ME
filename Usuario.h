#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>

#define tamanhoNome 50 //Tamanho da string que guarda os nomes de usuário
#define tamanhoSenha 50

/**
*Esta classe é responsável por guardar informações de usuário da aplicação, e também pelos métodos de alterações destas (getters e setters), ela é manipulada pelo manipuladoDeUsuário
*/
class Usuario {
public:
    int getId() const;
    char* getSenha() const;
    char* getNome() const;
    void setNome(char nome[]);
    void setSenha(char senha[]);
    void setId(int novoId);
    void limpaUsuario(); // Limpa todas as informações do usuario
    bool existe(); // Retorna se o objeto usuario está vazio ou não

    Usuario();

    int numeroSeguidores = 0;
    int numeroSeguindo = 0;
private:
    int id;
    char nome[tamanhoNome];
    char senha[tamanhoSenha];
};

#endif // USUARIO_H
