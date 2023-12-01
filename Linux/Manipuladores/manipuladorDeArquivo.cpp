#include "manipuladorDeArquivo.h"

/**
*@brief Metódo que gera uma exceção com um texto recebido
*/
void manipuladorDeArquivo::geraExcecao(string problema){
    throw problema;
    //cout << problema << endl;
}

/**
*@brief Metódo que limpa um arquivo binário
*Esta função recebe um nome de arquivo, nisto ela abre o arquivo de modo trunc para deixa-lo limpo
*@see geraExcecao(char problema[])
*@return true caso tenha sido limpo com sucesso e false se não foi limpo
*/
bool manipuladorDeArquivo::limparArquivoBinario(string nome){
        ofstream arquivo(nome,std::ofstream::out | std::ofstream::trunc);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao limpar o arquivo!");
            return false;
        }
        arquivo.close();
        return true;
}

/**
*@brief Metódo que copia um arquivo binário em outro
*Esta Metódo recebe dois nomes de arquivos, nisto ela limpar o arquivo de origem, depois abre os arquivos sendo o de origem como leitura e o de destino como escrito, nisto ela copia cada caractere da de origem para a de destino
*@see limparArquivoBinario(char nome[])
*@see geraExcecao(char problema[])
*@return true caso tenha sido copiado com sucesso e false se não foi
*/
bool manipuladorDeArquivo::copiarArquivo(string destino, string origem){
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

    arquivoDestino.close();
    arquivoOrigem.close();
    return true;

}
/**
*@brief Metódo que zera um arquivo binário
*Esta Metódo recebe um nome de arquivo, nisto ela limpar o arquivo, depois adiciona o valor zero no arquivo
*@see limparArquivoBinario(char nome[])
*@see geraExcecao(char problema[])
*@return true caso tenha sido zerado com sucesso e false se não foi
*/
bool manipuladorDeArquivo::zeraArquivo(string nome){
    limparArquivoBinario(nome);
    // Abrir o arquivo binário em modo de leitura e escrita
    fstream arquivo(nome, std::ios::binary | std::ios::in | std::ios::out);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo.");
        return false;
    }

    // Posicionar no final do arquivo
    arquivo.seekg(0, std::ios::end);

    // Adicionar zero ao final do arquivo
    arquivo.put(0);
    arquivo.put(0);

    // Fechar o arquivo
    arquivo.close();

    return true;
}
