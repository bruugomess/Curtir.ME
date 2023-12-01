#include "testes_comentarios.h"

testes_comentarios::testes_comentarios()
{
    //ctor
}

void testes_comentarios::executaTestes(){
    Comentario coment(2,"usuarioTeste", 1, 1,"comentarioTeste");
    CHECK(coment.existe() == true);
    CHECK(coment.GetIDusuario() == 2);
    CHECK(coment.GetIDpostagem() == 1);
    CHECK(coment.GetnumeroComentario() == 1);
    CHECK(strcmp(coment.Getconteudo(), "comentarioTeste") == 0);
    CHECK(strcmp(coment.GetnomeUsuario(), "usuarioTeste") == 0);
}
