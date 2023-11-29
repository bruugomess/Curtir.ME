#ifndef MANIPULADORDEARQUIVO_H
#define MANIPULADORDEARQUIVO_H

#include <fstream>
using namespace std;

/**
*Esta interface contém alguns metódos importantes para o funcionamento dos manipuladores de arquivos
*/

class manipuladorDeArquivo{
    public:
    bool limparArquivoBinario(char nome[]);
    void geraExcecao(char problema[]);
    bool copiarArquivo(char destino[], char origem[]);

    private:
};
#include "manipuladorDeArquivo.cpp"

#endif // MANIPULADORDEARQUIVO_H
