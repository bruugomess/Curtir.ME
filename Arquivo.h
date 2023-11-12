#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <fstream>
using namespace std;

void geraExcecao(char excecao[]){
    cout << excecao << endl;
}

bool limparArquivoBinario(char nome[]){
        ofstream arquivo(nome,std::ofstream::out | std::ofstream::trunc);
        if (!arquivo.is_open()) {
            cout << "Erro ao limpar o arquivo!" << endl;
            return false;
        }
        cout << "Arquivo Limpo com Sucesso!" << endl;
        arquivo.close();
        return true;
}

bool copiarArquivo(char destino[], char origem[]){
    limparArquivoBinario(destino);
    ifstream arquivoOrigem(origem, ios::binary);
    ofstream arquivoDestino(destino, ios::binary | ios::app);
    if (!arquivoDestino.is_open() || !arquivoOrigem.is_open()) {
        geraExcecao("Não foi possível abrir os arquivos.");
        return false;
    }
    char c;
    while (arquivoOrigem.read((char*)&c, sizeof(char))) {
            arquivoDestino.write((char*)&c, sizeof(char));
    }
    cout << "Arquivo copiado com sucesso." << endl;

    arquivoDestino.close();
    arquivoOrigem.close();
    return true;

}

#endif // ARQUIVO_H
