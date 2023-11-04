#ifndef MANIPULADORDEUSUARIO_H
#define MANIPULADORDEUSUARIO_H

using namespace std;
Usuario usuarioAtual;

class manipuladorDeUsuario {
public:
    void cadastrarUsuario(char nome[], char senha[]);
    bool autenticarUsuario(char nome[], char senha[]);
    int numeroDeUsuarios();
    int aumentarNumeroDeUsuarios();
    void criaArquivosNescessarios();
    int limparArquivoBinario(char nome[]);
private:

};

//Função que cria todos os documentos nescessarios para o funcionamento da aplicação
void manipuladorDeUsuario::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDeUsuariosCadastrados.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de numero de usuários." << endl;
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
            cout << "Erro ao criar o arquivo de usuários." << endl;
            return;
        }
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }
    //Arquivo de Postagens
    ifstream ifs3("Arquivos/postagens.bin");
    if (!ifs3) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/postagens.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            cout << "Erro ao criar o arquivo de postagens." << endl;
            return;
        }
        cout << "Arquivo de Postagens criado\n";
        arquivo.close();
    }
}


/*Parte de Usuarios*/

void manipuladorDeUsuario::cadastrarUsuario(char nome[], char senha[]) {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);
    usuario.setId(this->numeroDeUsuarios());

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();

    cout << "Usuário cadastrado com sucesso." << endl;
    this->aumentarNumeroDeUsuarios();
}

bool manipuladorDeUsuario::autenticarUsuario(char nome[], char senha[]) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de usuários." << endl;
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

int manipuladorDeUsuario::numeroDeUsuarios(){
    ifstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de numero de usuários." << endl;
        return 0;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
        arquivo.close();
        return numero;
    }
}

int manipuladorDeUsuario::aumentarNumeroDeUsuarios(){
    int numero = numeroDeUsuarios()+1;
    this->limparArquivoBinario("Arquivos/numeroDeUsuariosCadastrados.bin");
    //Aumenta numero de usuarios cadastrados
    ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de numero de usuários." << endl;
        return 1;
    }

    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return 0;
}

int manipuladorDeUsuario::limparArquivoBinario(char nome[]){
        ofstream arquivo(nome,std::ofstream::out | std::ofstream::trunc);
        if (!arquivo.is_open()) {
            cout << "Erro ao limpar o arquivo!" << endl;
            return 1;
        }
        cout << "Arquivo Limpo com Sucesso!" << endl;
        arquivo.close();
        return 0;
}


/*Parte de Usuarios*/


#endif // MANIPULADORDEUSUARIO_H

