#include "testes_ManipuladorDeUsuario.h"



void testes_ManipuladorDeUsuario::executaTestes(){
    manipuladorDeUsuario manipuladorUsuario;
    //Testes de cadastro e autenticação
    manipuladorUsuario.cadastrarUsuario("teste", "teste");
    manipuladorUsuario.cadastrarUsuario("teste2", "teste2");
    CHECK(manipuladorUsuario.autenticarUsuario("teste","teste") == true);
    CHECK(manipuladorUsuario.autenticarUsuario("teste2","teste2") == true);


    //Testes de procura de usuario
    CHECK(manipuladorUsuario.procuraUsuarioNome("teste").getId() == 1);
    CHECK(manipuladorUsuario.procuraUsuarioNome("teste2").getId() == 2);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "teste") == 0);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(2).getNome(), "teste2") == 0);

    //Testes de mudança de informações
    Usuario teste3 = manipuladorUsuario.procuraUsuarioId(1);
    teste3.setNome("teste3");
    manipuladorUsuario.salvarUsuario(teste3);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "teste3") == 0);
    teste3.setNome("teste2");
    manipuladorUsuario.salvarUsuario(teste3);
    CHECK(strcmp(manipuladorUsuario.procuraUsuarioId(1).getNome(), "teste2") == 0);

    //Teste para parte de seguir e deixar de seguir usuarios
    manipuladorUsuario.seguir(1,2);
    CHECK(manipuladorUsuario.segue(1,2) == true);
    manipuladorUsuario.deixarDeSeguir(1,2);
    CHECK(manipuladorUsuario.segue(1,2) == false);

}
