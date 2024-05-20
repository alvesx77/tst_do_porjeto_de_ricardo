#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct  lista_de_inscritos
{
    string nome,email;
    int num_de_ins;
    lista_de_inscritos *ant;
    lista_de_inscritos *prox;
};

struct  descritor_inscritos
{
    lista_de_inscritos *ini;
    lista_de_inscritos *fim;
    int tam;
};

struct lista_de_atividades
{
    string atividade,tipo;
    float hora;
    int dia;
    lista_de_atividades *ant;
    lista_de_atividades *prox;
};

struct  descritos_atividades
{
    lista_de_atividades *ini;
    lista_de_atividades *fim;
    int tam;
};

descritor_inscritos *criar_lista_de_insc(){
    descritor_inscritos *novo=new descritor_inscritos;
    novo->ini=NULL;
    novo->fim=NULL;
    novo->tam=0;
    return novo;
}
descritos_atividades *criar_lista_de_ativid(){
    descritos_atividades *novo=new descritos_atividades;
    novo->ini=NULL;
    novo->fim=NULL;
    novo->tam=0;
    return novo;
}

void adicionar_inscritos(descritor_inscritos *lista_dos_inscritos,string nome,string email,int numero_de_inscrisao){
    lista_de_inscritos *novo=new lista_de_inscritos;
    novo->nome=nome;
    novo->email=email;
    novo->num_de_ins=numero_de_inscrisao;
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

void adicionar_atividades(descritos_atividades *listas_das_atividades,string atividade,string tipo,float hora_da_atividade,int dia_da_atividade){
    lista_de_atividades *novo=new lista_de_atividades;
    novo->atividade=atividade;
    novo->tipo=tipo;
    novo->hora=hora_da_atividade;
    novo->dia=dia_da_atividade;
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

bool **criar_matriz(descritor_inscritos *lista_dos_inscritos,descritos_atividades *lista_das_atividades){
    bool **matriz=new bool*[lista_dos_inscritos->tam];
    for (int i = 0; i < lista_dos_inscritos->tam; i++)
    {
        matriz[i]=new bool[lista_das_atividades->tam];
    }
    return matriz;
}

void adicionar_presenca(bool **matriz,descritor_inscritos *lista_dos_inscritos,descritos_atividades *lista_das_atividas){
    int linhas=lista_dos_inscritos->tam,linha=0;
    string pergunta;
    lista_de_inscritos *aux_de_incritos=lista_dos_inscritos->ini;
    while (linha<linhas)
    {   lista_de_atividades *aux_das_atividas=lista_das_atividas->ini;
        int colunas=lista_das_atividas->tam,coluna=0;
        while (coluna<colunas)
        {
            cout<<"digite sim se "<<aux_de_incritos->nome<<" esteve presente na atividade"<<aux_das_atividas->atividade<<"\ndigite não se "<<aux_de_incritos->nome<<" nao esteve presente na atividade "<<aux_das_atividas->atividade<<"\n"<<aux_de_incritos->nome<<"esteve presente na atividade "<<aux_das_atividas->atividade<<" no dia "<<aux_das_atividas->dia<<": ";
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

descritor_inscritos  *porcetagem_de_preseca(bool **matiz,descritor_inscritos *lista_dos_inscritos,descritos_atividades *lista_das_atividades){
    descritor_inscritos *lista_dos_inscritos_participantes_do_sorteio=criar_lista_de_insc();
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
            adicionar_inscritos(lista_dos_inscritos_participantes_do_sorteio,aux_de_inscritos->nome,aux_de_inscritos->email,aux_de_inscritos->num_de_ins);
        }
        aux_de_inscritos=aux_de_inscritos->prox;
        linha++;
    }
    return lista_dos_inscritos_participantes_do_sorteio;
}

bool verificar(descritor_inscritos *listas_dos_participantes_do_sorteio,descritor_inscritos *lista_de_sorteados,int num){
    int cont=1;
    lista_de_inscritos *aux=listas_dos_participantes_do_sorteio->ini;
    while (cont<num)
    {   cont++;
        aux=aux->prox;
    }
    lista_de_inscritos *aux2=lista_de_sorteados->ini;
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

lista_de_inscritos *pos(descritor_inscritos *listas_dos_participantes_do_sorteio,int num){
    int cont=1;
    lista_de_inscritos *aux=listas_dos_participantes_do_sorteio->ini;
    while (cont<num)
    {
        cont++;
        aux=aux->prox;
    }
    return aux;
}
void add_sorteados(descritor_inscritos *listas_dos_participantes_do_sorteio,descritor_inscritos *lista_de_sorteados){
    srand(time(0));
   while (lista_de_sorteados->tam<3){
        int cont=rand()%listas_dos_participantes_do_sorteio->tam;        
        if (verificar(listas_dos_participantes_do_sorteio,lista_de_sorteados,cont)==true)
        {
            lista_de_inscritos *nome=pos(listas_dos_participantes_do_sorteio,cont);
            adicionar_inscritos(lista_de_sorteados,nome->nome,nome->email,nome->num_de_ins);
        }
    }   
}


bool verificar_se_averar_sorteio(descritor_inscritos *lista_de_sorteados){
    if (lista_de_sorteados->tam<=3)
    {
        return false;
    }
    return true;
}

void mostrar(descritor_inscritos *lista){
    lista_de_inscritos *aux=lista->ini;
    int pos=1;
    while (aux!=NULL)
    {
        cout<<pos<<"° "<<aux->nome<<endl;
        aux=aux->prox;
        pos++;
    }
    cout<<endl;
}

int main(){
    descritor_inscritos *listas_dos_inscritos=criar_lista_de_insc();
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

    descritos_atividades *lista_das_atividades=criar_lista_de_ativid();
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
    descritor_inscritos *listas_dos_participantes_do_sorteio=porcetagem_de_preseca(matriz,listas_dos_inscritos,lista_das_atividades);
    descritor_inscritos *lista_de_sorteados=criar_lista_de_insc();
    add_sorteados(listas_dos_participantes_do_sorteio,lista_de_sorteados);
    if (verificar_se_averar_sorteio(lista_de_sorteados)==false)
    {
        cout<<"o sorteio não ocorerar pois o numero de pessoas e insuficiente"<<endl;
    }
    else{
        mostrar(lista_de_sorteados);
    }
    return 0;
}
