#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <stdio.h>

#include "ClassesPrincipais/Usuario.cpp"
#include "ClassesPrincipais/Usuario.h"
#include "ClassesPrincipais/Postagem.cpp"
#include "ClassesPrincipais/Postagem.h"
#include "ClassesPrincipais/Comentario.cpp"
#include "ClassesPrincipais/Comentario.h"
#include "ClassesPrincipais/Hashtag.cpp"
#include "ClassesPrincipais/Hashtag.h"

#include "Manipuladores/manipuladorDeUsuario.cpp"
#include "Manipuladores/manipuladorDeUsuario.h"
#include "Manipuladores/manipuladorDePostagem.cpp"
#include "Manipuladores/manipuladorDePostagem.h"
#include "Manipuladores/manipuladorDeComentario.cpp"
#include "Manipuladores/manipuladorDeComentario.h"

#define sucesso 0

/*Cria��o dos manipuladores utilizados*/

manipuladorDeUsuario manipuladorUsuarios;
manipuladorDePostagem manipuladorPostagens;
manipuladorDeComentario manipuladorComentarios;
Hashtag manipuladorHashtag;

/*Cria��o dos manipuladores utilizados*/

/*Declara��o das Fun��es*/

void printaMenuLogin(); // Mostra na tela o menu de login
void printaMenu(); // Mostra na tela o menu normal
void limpaEntrada(); // Limpa os buffers depois de uma leitura
void printaMenuPostagens(); // Mostra o menu de Postagens, ap�s o usuario escolher a parte de postagens
void printaMenuFeed(); // Exibe o menu com op��es de feed
void printaMenuFeedPostagens(); // Mostra o menu de intere��o com o feed, que � exibido ap�s serem mostradas postagens
void Curtir_ME(); // Respons�vel por todas intera��es com o usu�rio

/*Declara��o das Fun��es*/

int main() {

    setlocale(LC_ALL, "Portuguese"); //Deixa a sa�da com os caracteres da lingua portuguesa

    /*Cria os arquivos nescess�rios no inicio se n�o existir*/

    try{

        manipuladorUsuarios.criaArquivosNescessarios();
        manipuladorPostagens.criaArquivosNescessarios();
        manipuladorComentarios.criaArquivosNescessarios();
        manipuladorHashtag.criaArquivosNescessarios();

    }catch(const char* msg){
        cout << "ERRO: " << msg;
        return 0;
    }

    Curtir_ME();

    return sucesso;
}


void Curtir_ME(){

    try{ // Mostra quantidade de usuarios e postagens

        cout << "  Numero de usuarios: " << manipuladorUsuarios.numeroDeUsuarios() << endl;
        cout << " Numero de postagens: " << manipuladorPostagens.numeroDePostagens() << endl;

    }catch(const char* msg){
            cout << "ERRO: " << msg;
    }

    system("pause");

    int opcao;

    do {
        if(!usuarioAtual.existe()){  //Se n�o existe um usuario
            printaMenuLogin();

            cin >> opcao;
            char nome[tamanhoNome], senha[tamanhoSenha];
            switch (opcao) {
            case 1: //Cadastrar Usuario

                cout << "   Digite o nome do usu�rio: ";
                limpaEntrada();
                fgets(nome, tamanhoNome, stdin);

                cout << "   Digite a senha do usu�rio: ";
                fgets(senha, tamanhoSenha, stdin);

                try{
                    if(manipuladorUsuarios.procuraUsuarioNome(nome).existe() == true){
                        cout << "\n\nEste nome de usu�rio j� existe no sistema, tente outro nome!\n\n\n\n";
                        system("pause");
                    }else{
                            manipuladorUsuarios.cadastrarUsuario(nome,senha);

                    }
                }catch(const char* msg){
                        cout << "ERRO: " << msg;
                        cout << "N�o foi possivel cadastrar o usu�rio!" << endl;
                }

                break;

            case 2: //Entrar com usuario e senha
                cout << "   Nome: ";
                limpaEntrada();
                fgets(nome, tamanhoNome,stdin);
                cout << "   Senha: ";
                fgets(senha, tamanhoSenha, stdin);

                try{

                    if (manipuladorUsuarios.autenticarUsuario(nome,senha)) {
                        cout << "   Autentica��o bem-sucedida.\n";
                    }else{
                        cout << "   Usuario ou senha incorretos.\n";
                    }

                }catch(const char* msg){
                    cout << "ERRO: " << msg;
                    cout << "N�o foi possivel entrar com o usu�rio!";
                }

                system("pause");
                break;
            case 0:
                return;
            }
        }else{ //Se existe um usuario
            printaMenu();
            cin >> opcao;

            switch(opcao){
                case 3:// Seguir ou n�o seguir outro usu�rio

                        int opcaoSeguir;
                        cout << "   (1)Seguir (2) Deixar de seguir: ";
                        cin >> opcaoSeguir;
                        limpaEntrada();

                        if(opcaoSeguir == 1){ //Seguir

                            cout << "    (1) Seguir por id (2) Seguir por nome: ";
                            cin >> opcaoSeguir;
                            limpaEntrada();

                            try{
                                if(opcaoSeguir == 1){ //Seguir por Id
                                    int id;
                                    cout << "       Digite o Id que dejesa seguir: ";
                                    cin >> id;
                                    limpaEntrada();
                                    if(id == usuarioAtual.getId()){ //Se for voc� mesmo

                                        cout << "Voc� n�o pode seguir a si mesmo" << endl;

                                    }else if(manipuladorUsuarios.seguir(usuarioAtual.getId(), id)){
                                        Usuario seguido = manipuladorUsuarios.procuraUsuarioId(id);

                                        seguido.numeroSeguidores++;
                                        usuarioAtual.numeroSeguindo++;

                                        manipuladorUsuarios.salvarUsuario(seguido);
                                        manipuladorUsuarios.salvarUsuario(usuarioAtual);

                                        cout << "Seguido com sucesso \n";
                                    }else{
                                        cout << "Falha ao seguir \n";
                                    }
                                }else if(opcaoSeguir == 2){ //Seguir por nome
                                    char nomeDoSeguido[tamanhoNome];
                                    cout << "    Digite o nome de quem dejesa seguir: ";
                                    fgets(nomeDoSeguido, tamanhoNome, stdin);

                                    if (strcmp(nomeDoSeguido, usuarioAtual.getNome()) == 0){ //Se for voc� mesmo

                                        cout << "Voc� n�o pode seguir a si mesmo" << endl;

                                    }else if(manipuladorUsuarios.seguir(usuarioAtual.getId(), nomeDoSeguido)){
                                        Usuario seguido = manipuladorUsuarios.procuraUsuarioNome(nomeDoSeguido);

                                        seguido.numeroSeguidores++;
                                        usuarioAtual.numeroSeguindo++;

                                        manipuladorUsuarios.salvarUsuario(seguido);
                                        manipuladorUsuarios.salvarUsuario(usuarioAtual);

                                        cout << "Seguido com sucesso \n";
                                    }else{
                                        cout << "Falha ao seguir \n";
                                    }
                                }else{
                                    cout << "Digite uma op��o v�lida!\n";
                                }
                            }catch(const char* msg){
                                cout << "ERRO: " << msg;
                            }

                        }else if(opcaoSeguir == 2){ //Deixar de seguir


                                cout << "    (1) Deixar de seguir por id (2) Deixar de seguir por nome: ";
                                    cin >> opcaoSeguir;
                                    limpaEntrada();

                                    if(opcaoSeguir == 1){ //Deixar de seguir por Id
                                        int id;
                                        cout << "       Digite o Id que dejesa deixar de seguir: ";
                                        cin >> id;
                                        limpaEntrada();
                                        try{

                                            manipuladorUsuarios.deixarDeSeguir(usuarioAtual.getId(), id);
                                            Usuario seguido = manipuladorUsuarios.procuraUsuarioId(id);

                                            seguido.numeroSeguidores--;
                                            usuarioAtual.numeroSeguindo--;

                                            manipuladorUsuarios.salvarUsuario(seguido);
                                            manipuladorUsuarios.salvarUsuario(usuarioAtual);

                                            cout << "Deixado de Seguir com sucesso \n";

                                        }catch(const char* msg){
                                            cout << "ERRO: " << msg;
                                            cout << "Falha ao deixar de seguir \n";
                                        }

                                    }else if(opcaoSeguir == 2){ //Deixar de seguir por nome
                                        char nomeDoSeguido[tamanhoNome];
                                        cout << "    Digite o nome de quem dejesa deixar de seguir: ";
                                        fgets(nomeDoSeguido, tamanhoNome, stdin);

                                        try{
                                            manipuladorUsuarios.deixarDeSeguir(usuarioAtual.getId(), nomeDoSeguido);
                                            Usuario seguido = manipuladorUsuarios.procuraUsuarioNome(nomeDoSeguido);

                                            seguido.numeroSeguidores--;
                                            usuarioAtual.numeroSeguindo--;

                                            manipuladorUsuarios.salvarUsuario(seguido);
                                            manipuladorUsuarios.salvarUsuario(usuarioAtual);

                                            cout << "Deixado de Seguir com sucesso \n";

                                        }catch(const char* msg){
                                                cout << "ERRO: " << msg;
                                                cout << "Falha ao seguir \n";
                                        }

                                    }else{
                                        cout << "Digite uma op��o v�lida!\n";
                                    }

                            }else{
                                cout << "Digite uma op��o v�lida!\n";

                            }

                        system("pause");

                    break;
                case 2: // Adiciona uma postagem
                    goto postagemStop; // Vai para a esta��o de postagens
                    break;
                case 1: // Exibe o feed
                    printaMenuFeed();
                    break;
                case 0:
                    usuarioAtual.limpaUsuario();
                    break;
            }


            postagemStop:
                if(opcao == 2){
                    while(1){
                        printaMenuPostagens();
                        int opcaoPostagens;
                        cin >> opcaoPostagens;
                        limpaEntrada();

                        if(opcaoPostagens == 1){ //Adicionar Postagens
                                char texto[tamanhoTextoPostagens];
                                cout << "Digite o conteudo da postagem:\n";
                                fgets(texto, tamanhoTextoPostagens, stdin);

                                Postagem novaPostagem(usuarioAtual.getId(), 0,texto);

                                cout << "Dejesa adicionar uma Hashtag (1) Sim (Outro numero) N�o: \n";
                                cin >> opcaoPostagens;
                                limpaEntrada();

                                if(opcaoPostagens == 1){ //Adiciona hashtag
                                    char hashtag[tamanhoTextoPostagens];
                                    while(1){
                                        cout << "Digite a Hashtag:\n";
                                        fgets(hashtag, tamanhoHashtag, stdin);
                                        if(novaPostagem.hashtag.verificaFormato(hashtag)){
                                            break;
                                        }
                                        cout << "Digite uma Hashtag que comece com #\n";
                                    }

                                    novaPostagem.hashtag.Sethashtag(hashtag);
                                    novaPostagem.hashtag.Setexiste(true);
                                    try{

                                        manipuladorHashtag.adicionaHashtagArquivo(novaPostagem.hashtag);

                                    }catch(const char* msg){
                                        cout << "ERRO: " << msg;
                                        break;
                                    }

                                }

                                try{
                                    manipuladorPostagens.adicionaAoArquivo(novaPostagem); //Adiciona a nova postagem ao arquivo
                                }catch(const char* msg){
                                    cout << "ERRO: " << msg;
                                    cout << "N�o foi possivel adicionar a postagem" << endl;
                                    break;
                                }

                                system("pause");
                        }else if(opcaoPostagens == 2){ // Alterar uma postagem
                                while(1){
                                    int numeroPostagem;
                                    cout << "Qual postagem deseja alterar (0 para voltar) : \n";
                                    cin >> numeroPostagem;

                                    limpaEntrada();

                                    if(numeroPostagem == 0){
                                        goto postagemStop;
                                    }

                                    try{
                                        if( manipuladorPostagens.ehMinhaPostagem(usuarioAtual.getId(),numeroPostagem)){

                                            char texto[tamanhoTextoPostagens];
                                            cout << "Digite o conteudo da postagem:\n";
                                            fgets(texto, tamanhoTextoPostagens, stdin);
                                            Postagem postAlterado(usuarioAtual.getId(), numeroPostagem, texto);

                                            manipuladorPostagens.salvaPostagem(postAlterado);


                                            break;
                                        }else{
                                            cout << "Voc� n�o t�m esta postagem.\n\n";
                                            system("pause");

                                        }
                                    }catch(const char* msg){
                                        cout << "ERRO: " << msg;
                                        cout << "N�o foi possivel alterar!" << endl;
                                    }

                                }

                        }else if(opcaoPostagens == 3){
                            while(1){
                                int numeroPostagem;
                                cout << "Qual postagem deseja apagar (0 para voltar) : \n";
                                cin >> numeroPostagem;

                                limpaEntrada();

                                if(numeroPostagem == 0){
                                    goto postagemStop;
                                }

                                try{
                                    if( manipuladorPostagens.ehMinhaPostagem(usuarioAtual.getId(),numeroPostagem)){

                                        if(manipuladorPostagens.apagarPostagem(numeroPostagem)){
                                            cout << "Apagada com sucesso!" << endl;
                                        }else{
                                            cout << "N�o foi possivel apagar a postagem\n" << endl;
                                        }

                                        break;
                                    }else{
                                        cout << "Voc� n�o t�m esta postagem.\n\n";

                                    }
                                }catch(const char* msg){
                                    cout << "ERRO: " << msg;
                                    cout << "N�o foi possivel apagar!" << endl;
                                }

                            }
                            system("pause");
                            break;
                        }else if(opcaoPostagens == 0){
                            break;
                        }else{
                            cout << "Digite uma op��o v�lida.\n";
                        }
                    }
                }

        }
    } while (1);

}

void printaMenuLogin(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                            Login                                  .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";

        cout <<"    1 - Cadastrar usu�rio\n";
        cout <<"    2 - Entrar\n";
        cout <<"    0 - Fechar\n";
        cout <<"    Digite a op��o: ";
}

void printaMenu(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                             Menu                                  .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";


        printf("\n\n    ID: %d Perfil: %s",usuarioAtual.getId(),usuarioAtual.getNome());
        printf("    Seguidores: %d Seguindo: %d\n\n",usuarioAtual.numeroSeguidores,usuarioAtual.numeroSeguindo);

        cout <<"    1 - Feed\n";
        cout <<"    2 - Postagens\n";
        cout <<"    3 - Seguir / N�o seguir\n";
        cout <<"    0 - Sair\n";
        cout <<"    Digite a op��o: ";
}

void printaMenuPostagens(){
        system("cls");
        cout <<"    .....................................................................\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .                            Postagens                              .\n";
        cout <<"    .                                                                   .\n";
        cout <<"    .....................................................................\n";


        printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

        cout <<"    1 - Adicionar uma Postagem\n";
        cout <<"    2 - Mudar postagem\n";
        cout <<"    3 - Apagar postagem\n";
        cout <<"    0 - Voltar\n";
        cout <<"    Digite a op��o: ";
}

void printaMenuFeedPostagens(){
        int opcao;
        int idPostagem;
        char textoComentario[tamanhoTextoComentarios];
        int IDpostagem;
        Comentario comentario;

        while(1){
            printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

            cout <<"    1 - Curtir uma Postagem\n";
            cout <<"    2 - Comentar uma postagem\n";
            cout <<"    3 - Detalhar uma postagem (Mostrar postagem e todos os seus coment�rios)\n";
            cout <<"    0 - Voltar\n";
            cout <<"    Digite a op��o: ";
            cin >> opcao;

            switch(opcao){
                case 1: //Adiciona uma curtida a uma postagem escolhida
                    cout << "   Digite o Id da postagem: ";
                    cin >> idPostagem;

                    try{

                        if(manipuladorPostagens.buscaPostagem(idPostagem).existe()){
                            manipuladorPostagens.adicionaCurtida(manipuladorPostagens.buscaPostagem(idPostagem));
                        }else{
                            cout << "\n\n  Esta postagem n�o existe!\n";
                        }

                    }catch(const char* msg){
                        cout << "ERRO: " << msg;
                        cout << "N�o foi possivel curtir" << endl;
                    }

                    break;
                case 2: // Adiciona um coment�rio a uma postagem escolhida
                        cout << "Qual o Id da postagem que voc� deseja comentar: ";
                        scanf("%d", &IDpostagem);
                        limpaEntrada();
                        cout << "Digite o coment�rio: " << endl;
                        fgets(textoComentario, tamanhoTextoComentarios, stdin);

                        comentario.SetIDusuario(usuarioAtual.getId());
                        comentario.Setconteudo(textoComentario);
                        comentario.SetIDpostagem(IDpostagem);
                        comentario.SetnomeUsuario(usuarioAtual.getNome());
                        comentario.SetnumeroComentario(0);

                        try{
                            manipuladorComentarios.adicionaAoArquivo(comentario);
                        }catch(const char* msg){
                            cout << "ERRO: " << msg;
                            cout << "N�o foi possivel adicionar o coment�rio" << endl;
                        }

                    break;
                case 3: // Mostra uma postagem com seus coment�rios
                        cout << "Qual o Id da postagem que voc� deseja detalhar: ";
                        scanf("%d", &IDpostagem);
                        limpaEntrada();

                        try{
                            manipuladorPostagens.detalhar(IDpostagem);
                        }catch(const char* msg){
                            cout << "ERRO: " << msg;
                        }

                    break;
                case 0:
                    return;

            }
        }
}

void printaMenuFeed(){
        int opcao;
        int idPostagem;
        char textoComentario[tamanhoTextoComentarios];
        int IDpostagem;
        Comentario comentario;


        while(1){
            system("cls");
            cout <<"    .....................................................................\n";
            cout <<"    .                                                                   .\n";
            cout <<"    .                            Feed                                   .\n";
            cout <<"    .                                                                   .\n";
            cout <<"    .....................................................................\n";



            printf("\n\n    ID: %d Perfil: %s\n",usuarioAtual.getId(),usuarioAtual.getNome());

            cout <<"    1 - Meu Feed\n";
            cout <<"    2 - Feed Global\n";
            cout <<"    3 - Mostrar postagens por Hashtag\n";
            cout <<"    0 - Voltar\n";
            cout <<"    Digite a op��o: ";
            cin >> opcao;
            limpaEntrada();

            switch(opcao){
                case 1: //Mostra feed pelas pessoas que voc� segue

                    try{
                        manipuladorPostagens.mostrarFeedDosSeguidos(usuarioAtual.getId());
                        printaMenuFeedPostagens();
                    }catch(const char* msg){
                        cout << "ERRO: " << msg;
                        cout << "N�o � possivel mostrar o feed" << endl;
                    }

                    break;
                case 2: // Mostra o Feed total

                    try{
                        manipuladorPostagens.mostrarFeed();
                        printaMenuFeedPostagens();
                    }catch(const char* msg){
                        cout << "ERRO: " << msg;
                        cout << "N�o � possivel mostrar o feed" << endl;
                    }

                    break;
                case 3: // Mostra feed por hashtag
                    char hashtag[tamanhoHashtag];
                    cout << "Digite a hashtag procurada:";
                    fgets(hashtag, tamanhoHashtag, stdin);

                    try{
                        manipuladorPostagens.mostrarFeedPorHashtag(hashtag);
                        printaMenuFeedPostagens();
                    }catch(const char* msg){
                        cout << "ERRO: " << msg;
                        cout << "N�o � possivel mostrar o feed por hashtag" << endl;
                    }

                    break;
                case 0:
                    return;

            }
        }
}

void limpaEntrada(){
    getchar();
}
