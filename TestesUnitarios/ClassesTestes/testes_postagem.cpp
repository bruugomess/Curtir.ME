#include "testes_postagem.h"

testes_postagem::testes_postagem()
{
    //ctor
}
void testes_postagem::executaTestes(){
    Postagem postTeste(1,1,"Texto teste");
    CHECK(postTeste.existe() == true);
    CHECK(postTeste.GetnumeroPostagem() == 1);
    CHECK(postTeste.GetIDusuario() == 1);
    CHECK(strcmp(postTeste.Getconteudo(), "Texto teste") == 0);
}
