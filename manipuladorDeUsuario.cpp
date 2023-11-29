#include "manipuladorDeUsuario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe manipuladorDeUsuario                            */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*@brief Método que cria todos os documentos nescessários para o funcionamento dos usuários
*Este método têm como objetivo abrir 2 arquivos binários importantes para a aplicação sendo eles o arquivo numeroDeUsuariosCadastrados.bin (Detém o numero de usuarios da aplicação)
* e o outro sendo usuarios.bin (Guarda os usuarios da aplicação).
*/
void manipuladorDeUsuario::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDeUsuariosCadastrados.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de usuários.");
            return;
        }

        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }

    //Arquivos de usuarios
    ifstream ifs2("Arquivos/usuarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de usuários.");
            return;
        }
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }
}


/*Parte de Usuarios*/

/**
*@brief Método que cadastra um usuário no sistema, guardando suas informações no arquivo usuários.bin
*Este método recebe um nome e uma senha, cria um objeto de usuário, adiciona as informações no objeto e salva no arquivo
*@param nome Vetor de char's, recebe um nome de usuario
*@param senha Vetor de char's, recebe uma senha de usuario
*/
void manipuladorDeUsuario::cadastrarUsuario(char nome[], char senha[]) {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);
    usuario.setId(this->numeroDeUsuarios()+1); //Seta o id sendo o numero de usuarios mais 1

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    const char* idUsuario = to_string(usuario.getId()).c_str();
    //Cria arquivo de seguidores para o novo usuario

    char parte1[] = "Arquivos/Seguidores/Seguidores#";
    char parte2[] = ".bin";
    char *nomeArquivo = strcat(strcat(parte1,idUsuario),parte2);

    ifstream ifs(nomeArquivo);
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo(nomeArquivo, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidores.");
            return;
        }

        cout << "Arquivo de seguidores criado.\n";
        arquivo.close();
    }



    char parte1b[] = "Arquivos/Seguidores/Segue#";
    char *nomeArquivo2 = strcat(strcat(parte1b,idUsuario),parte2);
    ifstream ifs2(nomeArquivo2);
    if (!ifs2) { //Verifica se Existe o Arquivo
        arquivo.open(nomeArquivo2, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidos.");
            return;
        }

        system("pause");

        cout << "Arquivo de seguidores criado.\n";
        arquivo.close();
    }


    cout << "Usuário cadastrado com sucesso." << endl;
    this->aumentarNumeroDeUsuarios();
}

/**
*@brief Método que autentica se um usuário e senha batem no sistema
*Este método recebe um nome e uma senha, verifica no arquivo de usuários se existe um usuário que bate com o nome e a senha
*@param nome Vetor de char's, recebe um nome de usuario
*@param senha Vetor de char's, recebe uma senha de usuario
*@return se o usuário foi autenticado ou não, true para sim e false para não
*/
bool manipuladorDeUsuario::autenticarUsuario(char nome[], char senha[]) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return false;
    }else{
        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0 && strcmp(usuario.getSenha(),senha) == 0) {
                usuarioAtual = usuario;
                arquivo.close();
                return true;
            }
        }
    }
    arquivo.close();

    return false;
}

/**@brief Método que retorna o numero de usuários
*Este método abre o arquivo numeroDeUsuariosCadastrados.bin faz a leitura e retorna o numero de usuários no sistema
*@return rwtorna um valor Int com o numero de usuários no arquivo
*/
int manipuladorDeUsuario::numeroDeUsuarios(){
    ifstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de numero de usuários.");
        return 0;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
        arquivo.close();
        return numero;
    }
}

/**@brief Método que aumenta o numero de usuários no sistema
*Este método abre o arquivo numeroDeUsuariosCadastrados.bin faz a leitura soma mais um e substitui no arquivo
*@see numeroDeUsuarios()
*@return valor int, true se foi adicionado com sucesso e false se não foi
*/
bool manipuladorDeUsuario::aumentarNumeroDeUsuarios(){
    int numero = numeroDeUsuarios()+1;
    limparArquivoBinario("Arquivos/numeroDeUsuariosCadastrados.bin");
    //Aumenta numero de usuarios cadastrados
    ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de numero de usuários.");
        return false;
    }

    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return true;
}

/**@brief Método que recebe um id de usuario e retorna o usuario contido no arquivo
*Este método recebe um id de usuario, percorre o arquivo de usuários procurando algum usuário que tenha o id recebido como argumento se encontrado retorna o usuário
*@param id int numero de postagem
*@return O usuário procurado
*/
Usuario manipuladorDeUsuario::procuraUsuarioId(int id) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (usuario.getId() == id) {
                arquivo.close();

                return usuario;
            }
        }
    }

    arquivo.close();


    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}

/**@brief Método que recebe um nome de usuário e retorna o usuário contido no arquivo
*Este método recebe um nome de usuario, percorre o arquivo de usuários procurando algum usuário que tenha o nome recebido como argumento se encontrado retorna o usuário
*@param nome vetor de caracteres
*@return O usuário procurado
*/
Usuario manipuladorDeUsuario::procuraUsuarioNome(char nome[]){
    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0) {
                arquivo.close();

                return usuario;
            }
        }
    }


    arquivo.close();

    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}

/*Parte de Seguidores*/

/**@brief Método para um usuário seguir outro usuário por id
*Este método verifica se os usuários já se seguem, senão recebe dois id's, sendo um do seguidor e outro do seguido, acessa os documentos de seguidores e seguidos dos respectivos usuários
*e adiciona os id's dos respectivos usuários.
*@see segue(int idSeguidor, int idSeguido)
*@param idSeguidor um argumento inteiro
*@param idSeguido um argumento inteiro
*@return True se foi seguido com sucesso e False se não
*/
bool manipuladorDeUsuario::seguir(int idSeguidor, int idSeguido){
    if(this->segue(idSeguidor, idSeguido)){
        cout << "Você já segue este usuario\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ofstream arquivo(nomeArquivoSeguidor, ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguidor));
        return false;
    }

    arquivo.write((char*)&idSeguido, sizeof(int));
    arquivo.close();

    //Adiciona no arquivo "Seguidor"
    arquivo.open(nomeArquivoSeguido, ios::binary | ios::app);
    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguido));
        return false;
    }

    arquivo.write((char*)&idSeguidor, sizeof(int));
    arquivo.close();

    return true;
}

/**@brief Método para um usuário seguir outro usuário por nome
*Este método verifica se os usuários já se seguem, senão recebe um id e um nome, procura o id do nome e chama o método seguir
*@see seguir(int idSeguidor, int idSeguido)
*@see existe()
*@param idSeguidor um argumento inteiro
*@param  nomeSeguidor um argumento vetor de caracteres
*@return True se foi seguido com sucesso e False se não
*/
bool manipuladorDeUsuario::seguir(int idSeguidor, char* nomeSeguidor){
    if(this->procuraUsuarioNome(nomeSeguidor).existe()){
        return this->seguir(idSeguidor, this->procuraUsuarioNome(nomeSeguidor).getId());
    }else{
        cout << "O usuário com este nome não existe\n\n";
    }

    return false;
}

/**@brief Retira um numero inteiro de algum arquivo utilizado para guardar inteiros
*Este método recebe um nome de arquivo e um inteiro, o arquivo deve ter somente inteiros, o método procura o inteiro recebido como argumento e retira no arquivo.
*@param nomeArquivo um argumento vetor de caracteres
*@param  inteiro um argumento inteiro
*@return True se foi retirado com sucesso e False se não
*/
bool manipuladorDeUsuario::retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro){
    bool encontrado = false;
    fstream arquivo(nomeArquivo, ios::binary | std::ios::in | std::ios::out); //Abre arquivo
    ofstream arquivoAux("Arquivos/aux.bin", ios::binary | ios::app); //Abre arquivo auxiliar
    limparArquivoBinario("Arquivos/aux.bin");

    int valorAtual;

    if (!arquivoAux.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", "aux.bin"));
        return false;
    }

    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivo));
        return false;
    }else{
            while (arquivo.read((char*)&valorAtual, sizeof(int))) {

                if (inteiro == valorAtual) {
                    encontrado = true;
                    break;
                }
                arquivoAux.write((char*)&valorAtual, sizeof(int));
            }

            if(!encontrado){
                geraExcecao(strcat("Inteiro não encontrado no arquivo", nomeArquivo));
                return false;
            }else{
                copiarArquivo(nomeArquivo, "Arquivos/aux.bin");

            }

    }

    arquivoAux.close();
    arquivo.close();
    return true;
}

/**@brief Este método é utilizado para um usuário deixar de seguir outro usuário por id
*Este método recebe dois id's sendo um o id do seguidor e outro do seguido, ele verifica se um id segue o outro, se sim, ele retira os id's respectivos nos arquivos de seguidos e de seguidos respectivos aos id's
*@param  idSeguidor um argumento inteiro
*@param  idSeguido um argumento inteiro
**@see existe()
*@see retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro)
*@return True se foi deixado de seguir com sucesso e False se não
*/
bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, int idSeguido){
    if(!this->segue(idSeguidor, idSeguido)){
        cout << "Você não segue este usuario.\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Retira do arquivo "Segue"

    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguidor, idSeguido)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }
    //Retira do arquivo "Seguidor"
    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguido, idSeguidor)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }

    if(this->segue(idSeguidor, idSeguido)){
        geraExcecao("Erro ao deixar de seguir!\n");
        return false;
    }

    return true;
}

/**@brief Este método é utilizado para um usuário deixar de seguir outro usuário por nome
*Este método recebe um id e um nome, procura o id do respctivo nome e chama o método deixarDeSeguir() passando como parametro os id's
*@param  idSeguidor um argumento inteiro
*@param  nomeSeguido um argumento vetor de caracteres
*@see deixarDeSeguir(int idSeguidor, int idSeguido)
*@return True se foi deixado de seguir com sucesso e False se não
*/
bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, char nomeSeguido[]){
    if(this->procuraUsuarioNome(nomeSeguido).existe()){
        return this->deixarDeSeguir(idSeguidor, this->procuraUsuarioNome(nomeSeguido).getId());
    }else{
        geraExcecao("O usuário com este nome não existe\n\n");
    }

    return false;
}

/**@brief Este método é utilizado para verificar se um usuário segue outro
*Este método recebe dois id's sendo um o id do seguidor e outro do seguido, ele verifica se um id segue o outro, verificando os arquivos de seguidores e seguidos respectivos
*@param  idSeguidor um argumento inteiro
*@see existe()
*@param  idSeguido um argumento inteiro
*@return True se segue e False se não
*/
bool manipuladorDeUsuario::segue(int idSeguidor, int idSeguido){
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);


    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    Usuario seguidor = this->procuraUsuarioId(idSeguidor);

    if(!seguido.existe()){
        geraExcecao("Usuario não existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ifstream arquivo(nomeArquivoSeguidor, ios::binary);
    int id;
    if (!arquivo.is_open()) {
        geraExcecao(strcat("Erro ao abrir o arquivo ", nomeArquivoSeguidor));
        return false;
    }else{

        while (arquivo.read((char*)&id, sizeof(int))) {

            if (id == idSeguido) {
                arquivo.close();
                return true;
            }
        }
    }

    return false;
}

/**@brief Método que salva um usuario com alterações no arquivo
*Este método têm como objetivo salvar um usuario já existente, mas que foi alterado no funcionamento da aplicação, ela recebe um objeto do tipo Usuario
*Porcura um objeto com o mesmo id e substitui ele no arquivo.
*@param post do tipo Usuario
*@return valor booleano, true se foi substituido com sucesso e false se não foi
*/
bool manipuladorDeUsuario::salvarUsuario(Usuario usuario){
    fstream arquivo("Arquivos/usuarios.bin", ios::binary | std::ios::in | std::ios::out);
    Usuario userAux;
    int i = 0;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usuários.");
        return false;
    }else{

        while (arquivo.read((char*)&userAux, sizeof(Usuario))) {
            if (userAux.getId() == usuario.getId()) {
                break;
            }
            i++;
        }

    }

    arquivo.seekg(i*sizeof(Usuario), ios_base::beg);
    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    return true;
}
/*Parte de Usuarios*/
