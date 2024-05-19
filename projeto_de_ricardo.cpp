#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

struct  lista_de_inscritos
{
    string nome;
    string email;
    int numero_de_inscricao;
    lista_de_inscritos *ant;
    lista_de_inscritos *prox;
};

struct descritor_de_lista_de_inscritos
{
    lista_de_inscritos *ini;
    lista_de_inscritos *fim;
    int tam;
};

descritor_de_lista_de_inscritos *criar_lista_de_inscritos(){
    descritor_de_lista_de_inscritos *novo=new descritor_de_lista_de_inscritos;
    novo->ini=NULL;
    novo->fim=NULL;
    novo->tam=0;
    return novo;
}

struct lista_de_atividades
{
    string nome_da_atividade;
    string tipo_da_ativida;
    float hora_da_atividade;
    int dia_da_atividade;
    lista_de_atividades *ant;
    lista_de_atividades *prox;
};

struct descritor_da_lista_de_atividade
{
    lista_de_atividades *ini;
    lista_de_atividades *fim;
    int tam;
};

descritor_da_lista_de_atividade *criar_lista_de_atividades(){
    descritor_da_lista_de_atividade *novo=new descritor_da_lista_de_atividade;
    novo->ini=NULL;
    novo->fim=NULL;
    novo->tam=0;
    return novo;
}

void adicionar_inscritos(descritor_de_lista_de_inscritos *lista_dos_inscritos,string nome,string email,int numero_de_inscrisao){
    lista_de_inscritos *novo=new lista_de_inscritos;
    novo->nome=nome;
    novo->email=email;
    novo->numero_de_inscricao=numero_de_inscrisao;
    novo->ant=NULL;
    novo->prox=NULL;
    if (lista_dos_inscritos->ini==NULL)
    {
        lista_dos_inscritos->ini=novo;
        lista_dos_inscritos->fim=novo;
        lista_dos_inscritos->tam=1;
    }
    else{
        lista_dos_inscritos->fim->prox=novo;
        novo->ant=lista_dos_inscritos->fim;
        lista_dos_inscritos->fim=novo;
        lista_dos_inscritos->tam++;
    }
}

void adicionar_atividades(descritor_da_lista_de_atividade *listas_das_atividades,string atividade,string tipo,float hora_da_atividade,int dia_da_atividade){
    lista_de_atividades *novo=new lista_de_atividades;
    novo->nome_da_atividade=atividade;
    novo->tipo_da_ativida=tipo;
    novo->hora_da_atividade=hora_da_atividade;
    novo->dia_da_atividade=dia_da_atividade;
    novo->ant=NULL;
    novo->prox=NULL;
    if (listas_das_atividades->ini==NULL)
    {
        listas_das_atividades->ini=novo;
        listas_das_atividades->fim=novo;
        listas_das_atividades->tam=1;
    }
    else{
        listas_das_atividades->fim->prox=novo;
        novo->ant=listas_das_atividades->fim;
        listas_das_atividades->fim=novo;
        listas_das_atividades->tam++;
    }
}

bool **criar_matriz(descritor_de_lista_de_inscritos *lista_dos_inscritos,descritor_da_lista_de_atividade *lista_das_atividades){
    bool **matriz=new bool*[lista_dos_inscritos->tam];
    for (int i = 0; i < lista_dos_inscritos->tam; i++)
    {
        matriz[i]=new bool[lista_das_atividades->tam];
    }
    return matriz;
}

void adicionar_presenca(bool **matriz,descritor_de_lista_de_inscritos *lista_dos_inscritos,descritor_da_lista_de_atividade *lista_das_atividas){
    int linhas=lista_dos_inscritos->tam,linha=0;
    string pergunta;
    lista_de_inscritos *aux_de_incritos=lista_dos_inscritos->ini;
    while (linha<linhas)
    {   lista_de_atividades *aux_das_atividas=lista_das_atividas->ini;
        int colunas=lista_das_atividas->tam,coluna=0;
        while (coluna<colunas)
        {
            cout<<"digite sim se "<<aux_de_incritos->nome<<" esteve presente na atividade"<<aux_das_atividas->nome_da_atividade<<"\ndigite não se "<<aux_de_incritos->nome<<" nao esteve presente na atividade "<<aux_das_atividas->nome_da_atividade<<"\n"<<aux_de_incritos->nome<<"esteve presente na atividade "<<aux_das_atividas->nome_da_atividade<<" no dia "<<aux_das_atividas->dia_da_atividade<<": ";
            cin>>pergunta;
            if (pergunta=="sim"||pergunta=="SIM"||pergunta=="nao"||pergunta=="NAO")
            {
                if (pergunta=="SIM"||pergunta=="sim")
                {
                    matriz[linha][coluna]=true;
                }
                else{
                    matriz[linha][coluna]=false;
                }
                coluna++;
                aux_das_atividas=aux_das_atividas->prox;
            }
            else{
                cout<<"codigo não cadastrado porafavor digite de novo"<<endl;
            }
        }
        linha++;
        aux_de_incritos=aux_de_incritos->prox;
    }
}

descritor_de_lista_de_inscritos  *porcetagem_de_preseca(bool **matiz,descritor_de_lista_de_inscritos *lista_dos_inscritos,descritor_da_lista_de_atividade *lista_das_atividades){
    descritor_de_lista_de_inscritos *lista_dos_inscritos_participantes_do_sorteio=criar_lista_de_inscritos();
    lista_de_inscritos *aux_de_inscritos=lista_dos_inscritos->ini;
    int linhas=lista_dos_inscritos->tam,linha=0;
    float porcentagem_de_presenca;
    while (linha<linhas)
    {
        int colunas=lista_das_atividades->tam,coluna=0,verificador_de_presenca=0;
        while (coluna<colunas)
        {   
            if (matiz[linha][coluna]==true)
            {
                verificador_de_presenca++;
            }
            coluna++;
        }
        porcentagem_de_presenca=(verificador_de_presenca*100)/colunas;
        if (porcentagem_de_presenca>=75)
        {
            adicionar_inscritos(lista_dos_inscritos_participantes_do_sorteio,aux_de_inscritos->nome,aux_de_inscritos->email,aux_de_inscritos->numero_de_inscricao);
        }
        aux_de_inscritos=aux_de_inscritos->prox;
        linha++;
    }
    return lista_dos_inscritos_participantes_do_sorteio;
}

bool verificar(int num,descritor_de_lista_de_inscritos *listas_dos_participantes_do_sorteio,descritor_de_lista_de_inscritos *sortados){
    lista_de_inscritos *aux=listas_dos_participantes_do_sorteio->ini;
    int cont=1;
    while (cont<num)
    {
        cont++;
        aux=aux->prox;
    }
    lista_de_inscritos *aux2=sortados->ini;
    while (aux2!=NULL)
    {
        if (aux2->nome==aux->nome)
        {
            return false;
        }
        aux2=aux2->prox;
    }
    return true;
}

lista_de_inscritos *sorteado(int num,descritor_de_lista_de_inscritos *lista_dos_participantes_do_sorteio){
    lista_de_inscritos *aux=lista_dos_participantes_do_sorteio->ini;
    int cont=1;    
    while (cont<num)
    {   cont++;
        aux=aux->prox;
    }
    return aux;
}

descritor_de_lista_de_inscritos *listas_dos_sorteados(descritor_de_lista_de_inscritos *lista_dos_participantes_do_sorteio){
    srand(time(NULL));
    descritor_de_lista_de_inscritos *premiados=criar_lista_de_inscritos();
    if (lista_dos_participantes_do_sorteio->tam==1||lista_dos_participantes_do_sorteio->tam==2)
    {
        return premiados;
    }
    else{
        int cont,c=0;
        while (c<4)
        {
            cont=rand()%lista_dos_participantes_do_sorteio->tam;
            if (verificar(cont,lista_dos_participantes_do_sorteio,premiados)==true)
            {
                lista_de_inscritos *aux=sorteado(cont,lista_dos_participantes_do_sorteio);
                adicionar_inscritos(premiados,aux->nome,aux->email,aux->numero_de_inscricao);
                c++;
            }
        } 
    }
    return premiados;
}

void mostrar(descritor_de_lista_de_inscritos *listas){
    lista_de_inscritos *aux=listas->ini;
    while (aux!=NULL)
    {
        cout<<aux->nome;
        aux=aux->prox;
    }
    cout<<endl;
}

int main(){
    descritor_de_lista_de_inscritos *listas_dos_inscritos=criar_lista_de_inscritos();
    string nome;
    string email;
    int numero_da_incrisao=0;
    while (nome!="fim")
    {
        cout<<"digite seu nome caso deseja parar de inseriri nomes digite fim\ndigite seu nome: ";
        cin>>nome;
        if (nome!="fim")
        {
            cout<<"digite seu email: ";
            cin>>email;
            numero_da_incrisao+=1;
            adicionar_inscritos(listas_dos_inscritos,nome,email,numero_da_incrisao);
        }
    }

    descritor_da_lista_de_atividade *lista_das_atividades=criar_lista_de_atividades();
    string atividade;
    string tipo_da_ativida;
    float hora_da_atividade;
    int dia_da_atividade;
    while (atividade!="fim")
    {
        cout<<"digite o nome da atividade caso deseja parar de inseriri nomes de atividades digite fim\ndigite o nome da atividade: ";
        cin>>atividade;
        if (atividade!="fim")
        {
            cout<<"digite o tipo da atividade "<<atividade<<": ";
            cin>>tipo_da_ativida;
            cout<<"caso a hora tenha minutos coloque um (.) para dividir os minutos das horas\ndigite a hora que inicia a atividade "<<atividade<<": ";
            cin>>hora_da_atividade;
            cout<<"digite o dia que ira ocorrer a atividade"<<atividade<<": ";
            cin>>dia_da_atividade;
            adicionar_atividades(lista_das_atividades,atividade,tipo_da_ativida,hora_da_atividade,dia_da_atividade);
        }
    }
    bool **matriz=criar_matriz(listas_dos_inscritos,lista_das_atividades);
    adicionar_presenca(matriz,listas_dos_inscritos,lista_das_atividades);
    descritor_de_lista_de_inscritos *listas_dos_participantes_do_sorteio=porcetagem_de_preseca(matriz,listas_dos_inscritos,lista_das_atividades);
    descritor_de_lista_de_inscritos *lista_dos_premiados=listas_dos_sorteados(listas_dos_participantes_do_sorteio);
    mostrar(lista_dos_premiados);
    
    return 0;
}