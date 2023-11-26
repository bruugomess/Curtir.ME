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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe Postagem                                        */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*@brief Retorna uma copia do IDusuario do objeto do tipo Postagem
*@return inteiro
*/
int Postagem::GetIDusuario() {
    return IDusuario;
}

/**
*@brief Altera o Idusuario do objeto
*@param val inteiro
*/
void Postagem::SetIDusuario(int val) {
    IDusuario = val;
}

/**
*@brief Retorna uma copia do numeroPostagem do objeto do tipo Postagem
*@return inteiro
*/
int Postagem::GetnumeroPostagem() {
    return numeroPostagem;
}

/**
*@brief Altera o numeroPostagem do objeto
*@param val inteiro
*/
void Postagem::SetnumeroPostagem(int val) {
    numeroPostagem = val;
}

/**
*@brief Retorna uma copia do numero de curtidas do objeto do tipo Postagem
*@return inteiro
*/
int Postagem::Getcurtidas() {
    return curtidas;
}

/**
*@brief Altera o numero de curtidas do objeto
*@param val inteiro
*/
void Postagem::Setcurtidas(int val) {
    curtidas = val;
}

/**
*@brief retorna o valor de apagada do objeto
*@return booleano
*/
bool Postagem::Getapagada() {
    return apagada;
}

/**
*@brief Altera o valor apagada do objeto
*@param val booleano
*/
void Postagem::Setapagada(bool val) {
    apagada = val;
}

/**
*@brief retorna o valor do conteudo do objeto
*@return ponteiro do tipo caractere
*/
char* Postagem::Getconteudo(){
        char * copia = new char[tamanhoTextoPostagens];
        strcpy(copia, this->conteudo);
        return copia;
}

/**
*@brief Altera o valor DO conteudo do objeto
*/
void Postagem::Setconteudo(char conteudo[]){
    strcpy(this->conteudo, conteudo);
}

/**
*@brief Contrutor do objeto
*Este construtor inicia o objeto setando os valores de ID, numeroPostagem e conteudo
*@param ID inteiro
*@param numeroP inteiro
*@param conteudo vetor de caracteres
*/
Postagem::Postagem(int ID, int numeroP, char conteudo[]){
    this->SetIDusuario(ID);
    this->SetnumeroPostagem(numeroP);
    this->Setconteudo(conteudo);
}

/**
*@brief Contrutor vazio do objeto
*Este construtor inicia o objeto totalmente zerado
*/
Postagem::Postagem(){
    this->Setconteudo("");
    this->SetIDusuario(0);
    this->SetnumeroPostagem(0);
}

/**
*@brief Este método verifica se o objeto Postagem esta vazio
*Este método verifica se o conteudo e numeroPostagem estão vazios se sim retorna false se não true
*@return true se existe e false se não
*/
bool Postagem::existe(){
    if(strcmp(this->Getconteudo(),"") == 0 && this->GetnumeroPostagem() == 0){
        return false;
    }
    return true;
}
#endif // POSTAGEM_H
