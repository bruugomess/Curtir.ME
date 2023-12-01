#include "manipuladorDeComentario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe manipuladorDeComentario                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
*@brief Método que cria todos os documentos nescessarios para o funcionamento da classe manipuladorDeComentario
*Está função têm como objetivo abrir o arquivo binários (comentarios.bin) importante para a aplicação.
*/
void manipuladorDeComentario::criaArquivosNescessarios(){

    //Arquivos de comentarios
    ifstream ifs2("Arquivos/comentarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de comentários.");

            return;
        }
        cout << "Arquivo de comentários criado\n";
        arquivo.close();
    }
}

/**@brief Método que adiciona um comentário no arquivo binário comentarios.bin
*Este método recebe um comentário, abre o arquivo de comentarios e adiciona o comentário recebido na ultima posição do arquivo
*@param coment recebe um objeto do tipo Comentario
*@return Valor booleano, retorna true caso tenha sido adicionado com sucesso e false se não
*/
bool manipuladorDeComentario::adicionaAoArquivo(Comentario coment){
    ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de comentarios.");
        return false;
    }

    arquivo.write((char*)&coment, sizeof(Comentario));
    arquivo.close();

    cout << "Comentário adicionado." << endl;

    return true;
}

/**@brief Método que exibe comentários por id de uma postagem
*Este método recebe um id, abre o arquivo de comentários e percorre verificando se os id's de postagens batem, se sim ele exibe os comentários sem ultrapassar o limite do argumento quantidade,
*caso a quantidade seja -1 ele mostra todos os comentários
*@param idPost valor inteiro
*@param quantidade valor inteiro
*/
void manipuladorDeComentario::exibirComentariosPorId(int idPost, int quantidade){
    int i = 0;
    ifstream arquivo("Arquivos/comentarios.bin", ios::binary);
    Comentario coment;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de comentários.");
    }else{

        while (arquivo.read((char*)&coment, sizeof(Comentario))) {
            if(quantidade != mostrarTodos){
                if(coment.GetIDpostagem() == idPost && i < quantidade){
                    this->printaComentario(coment);
                    i++;
                }
            }else{
                if(coment.GetIDpostagem() == idPost){
                    this->printaComentario(coment);
                    i++;
                }
            }

        }
    }

    if(i == 0){
        cout << "\n                 Nenhum comentário!\n" << endl;
    }

}

/**@brief Método que exibe um comentário
*Este método recebe um comentário, e exibe ele em um formato especial
*@param coment recebe um objeto do tipo Comentario
*/
void manipuladorDeComentario::printaComentario(Comentario coment){

        cout <<   "\n\n             | - ";
        cout << coment.Getconteudo() << endl;
        cout << "\n               Comentado por "<<  coment.GetnomeUsuario() << endl;
        cout <<   "\n             L \n";
}

 manipuladorDeComentario::manipuladorDeComentario(){
 }
