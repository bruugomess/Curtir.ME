#include <string.h>

//Classes principais
#include "../ClassesPrincipais/Usuario.cpp"
#include "../ClassesPrincipais/Usuario.h"
#include "../ClassesPrincipais/Postagem.cpp"
#include "../ClassesPrincipais/Postagem.h"
#include "../ClassesPrincipais/Comentario.cpp"
#include "../ClassesPrincipais/Comentario.h"
#include "../ClassesPrincipais/Hashtag.cpp"
#include "../ClassesPrincipais/Hashtag.h"

//Classes manipuladoras
#include "../Manipuladores/manipuladorDeUsuario.cpp"
#include "../Manipuladores/manipuladorDeUsuario.h"
#include "../Manipuladores/manipuladorDePostagem.cpp"
#include "../Manipuladores/manipuladorDePostagem.h"
#include "../Manipuladores/manipuladorDeComentario.cpp"
#include "../Manipuladores/manipuladorDeComentario.h"

//Classes de testes
#include "ClassesTestes/testes_usuario.cpp"
#include "ClassesTestes/testes_usuario.h"
#include "ClassesTestes/testes_postagem.cpp"
#include "ClassesTestes/testes_postagem.h"
#include "ClassesTestes/testes_comentario.cpp"
#include "ClassesTestes/testes_comentario.h"
#include "ClassesTestes/testes_hashtag.cpp"
#include "ClassesTestes/testes_hashtag.h"

#include "doctest/parts/doctest.cpp"
#include "doctest/doctest.h"
#include <cassert>

testes_postagem testesPostagens;
testes_usuario testeUsuario;
testes_comentario testeComentario;
testes_hashtag testeHashtag;

TEST_CASE("Testes da classe Usuario"){
    testeUsuario.executaTestes();
}

TEST_CASE("Testes das classe Postagem"){
    testesPostagens.executaTestes();
}

TEST_CASE("Testes da classe Hashtag"){
    testeHashtag.executaTeste();
}

TEST_CASE("Testes da classe Comentario"){
    testeComentario.executaTestes();
}

int main(){
    doctest::Context context;
    return context.run();
}



