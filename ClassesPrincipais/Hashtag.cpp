#include "Hashtag.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe Hashtag                                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Métodos para manipulação de arquivos*/

/**
*@brief Método que cria todos os documentos nescessarios para o funcionamento da classe Hashtags
*Está função têm como objetivo abrir o arquivo binário (hashtags.bin) importante para a aplicação.
*@return Valor booleano, retorna true caso tenha sido criado com sucesso e false se não
*/
bool Hashtag::criaArquivosNescessarios(){
    ifstream ifs("Arquivos/hashtags.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de hashtags.");
            return false;
        }
        cout << "Arquivo de  hashtags criado\n";
        arquivo.close();
    }
    return true;
}

/**
*@brief Método que adiciona uma hashtag no sistema, guardando suas informações no arquivo hashtags.bin
*Este método recebe uma hashtag e adiciona no arquivo
*@param hashtag Objeto do tipo Hashtag
*@return Valor booleano, retorna true caso tenha sido adicionado com sucesso e false se não
*/
bool Hashtag::adicionaHashtagArquivo(Hashtag hashtag){
        ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao abrir o arquivo de hashtags.");
            return false;
        }
        arquivo.write((char*)&hashtag, sizeof(Hashtag));
        arquivo.close();
        return true;
}

/**
*@brief Método que verifica a existencia de uma hashtag no sistema
*Este método recebe uma hashtag e percorre o arquivo a procura de uma hashtag com o mesmo conteúdo se encontrado retorna true e senão false
*@param hashtag Objeto do tipo Hashtag
*@return Valor booleano, retorna true caso tenha sido encontrado com sucesso e false se não
*/
bool Hashtag::verificaExistencia(Hashtag hashtag){
    ifstream arquivo("Arquivos/hashtags.bin", ios::binary);
    Hashtag aux;
    bool encontrado = false;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de hashtags.");
    }else{
        while (arquivo.read((char*)&aux, sizeof(Hashtag))) {
            if(strcmp(aux.Gethashtag(), hashtag.Gethashtag()) == 0){
                cout << "encontrado";
                encontrado = true;
            }
        }
    }
    return encontrado;
}
/*Métodos para manipulação de arquivos*/



/*Métodos para manipulação da hashtag*/

/**
*@brief Método que verifica o formato de uma hashtag
*Este método recebe um texto e verifica se está em um formato válido de hashtag, sendo que deve começar com '#'
*@param hashtag vetor de caracteres
*@return Valor booleano, retorna true caso tenha sido verificado com sucesso e false se não
*/
bool Hashtag::verificaFormato(char hashtag[]){
    if(hashtag[0] == '#'){
        return true;
    }
    return false;
}

/**
*@brief Altera o valor DO conteudo da hashtag
*@param Hashtag ponteiro do tipo char
*/
void Hashtag::Sethashtag(char* Hashtag){
    strcpy( this->hashtag, Hashtag);
}

/**
*@brief retorna o valor do conteudo da hashtag
*@return ponteiro do tipo caractere
*/
char* Hashtag::Gethashtag(){
    return this->hashtag;
}

/**
*@brief Muda o valor de existe da hashtag
*@param valor booleano
*/
void Hashtag::Setexiste(bool valor){
    this->existe = valor;
}

/**
*@brief Este método retorna o valor de existe do objeto
*Este método retorna o valor de existe da hashtag
*@return true se existe e false se não
*/
bool Hashtag::Getexiste(){
    return this->existe;
}

Hashtag::Hashtag()
{
}

/**
*@brief Contrutor do objeto
*Este construtor inicia o objeto já setando o valor da hashtag
*@param hashtag vetor de caracteres
*/
Hashtag::Hashtag(char hashtag[])
{
    this->Sethashtag(hashtag);
    this->Setexiste(true);
}
/*Métodos para manipulação da hashtag*/
