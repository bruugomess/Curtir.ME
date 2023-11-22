#ifndef COMENTARIO_H
#define COMENTARIO_H

#define tamanhoTextoComentarios 201
#define tamanhoNome 50

class Comentario
{
    public:
        int GetIDusuario();
        void SetIDusuario(int val);
        int GetnumeroComentario();
        void SetnumeroComentario(int val);
        char* Getconteudo();
        void Setconteudo(char conteudo[]);
        void SetnomeUsuario(char nomeUsuario[]);
        char* GetnomeUsuario();
        int GetIDpostagem();
        void SetIDpostagem(int val);
        Comentario(int ID,char nomeUsuario[], int IDpostagem, int numeroC, char conteudo[]);
        Comentario();
        bool existe();

    private:
        int IDusuario;
        char nomeUsuario[tamanhoNome];
        int numeroComentario;
        int IDpostagem;
        char conteudo[tamanhoTextoComentarios];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementação dos Metodos da Classe Comentário                                      */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //Getters e Setters
        int Comentario::GetIDusuario() {
            return IDusuario;
        }

        void Comentario::SetIDusuario(int val) {
            this->IDusuario = val;
        }

        int Comentario::GetnumeroComentario() {
            return numeroComentario;
        }

        void Comentario::SetnumeroComentario(int val) {
            this->numeroComentario = val;
        }

        char* Comentario::Getconteudo(){
            char * copia = new char[tamanhoTextoComentarios];
            strcpy(copia, this->conteudo);
            return copia;
        }

        void Comentario::SetnomeUsuario(char nomeUsuario[]){
            strcpy(this->nomeUsuario, nomeUsuario);
        }

        char* Comentario::GetnomeUsuario(){
            char * copia = new char[tamanhoNome];
            strcpy(copia, this->nomeUsuario);
            return copia;
        }

        void Comentario::Setconteudo(char conteudo[]){
            strcpy(this->conteudo, conteudo);
        }

        int Comentario::GetIDpostagem() {
            return IDpostagem;
        }

        void Comentario::SetIDpostagem(int val) {
            this->IDpostagem = val;
        }
        //Construtores
        Comentario::Comentario(int ID,char nomeUsuario[], int IDpostagem, int numeroC, char conteudo[]){
            this->SetIDusuario(ID);
            this->SetnumeroComentario(numeroC);
            this->Setconteudo(conteudo);
            this->SetIDpostagem(IDpostagem);
            this->SetnomeUsuario(nomeUsuario);
        }

        Comentario::Comentario(){
            this->Setconteudo("");
            this->SetIDusuario(0);
            this->SetnumeroComentario(0);
            this->SetnomeUsuario("");
        }

        //Metodos complementares
        bool Comentario::existe(){
            if(strcmp(this->Getconteudo(),"") == 0 && this->GetnumeroComentario() == 0){
                return false;
            }
            return true;
        }
#endif // COMENTARIO_H
