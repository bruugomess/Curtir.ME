#include "Postagem.h"
#include <cstring>
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
void Postagem::Setconteudo(string conteudo){
    strcpy(this->conteudo, conteudo.c_str());
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
