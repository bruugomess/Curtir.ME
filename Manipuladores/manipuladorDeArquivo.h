#ifndef MANIPULADORDEARQUIVO_H
#define MANIPULADORDEARQUIVO_H

#include <fstream>
using namespace std;

/**
*Esta interface contém alguns metódos importantes para o funcionamento dos manipuladores de arquivos
*/

class manipuladorDeArquivo{
    public:
    bool limparArquivoBinario(string nome);
    void geraExcecao(string problema);
    bool copiarArquivo(string destino, string origem);
    bool zeraArquivo(string nome);

    private:
};



#endif // MANIPULADORDEARQUIVO_H
