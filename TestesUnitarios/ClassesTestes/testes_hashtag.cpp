#include "testes_hashtag.h"

testes_hashtag::testes_hashtag()
{
    //ctor
}

void testes_hashtag::executaTeste(){
    Hashtag hashtag("#hashtagteste");
    CHECK(hashtag.Getexiste() == true);
    CHECK(strcmp(hashtag.Gethashtag(), "#hashtagteste") == 0);
    CHECK(hashtag.verificaFormato("#teste") == true);
    CHECK(hashtag.verificaFormato("teste") == false);

}
