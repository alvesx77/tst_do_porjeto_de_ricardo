#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

struct lista_de_participantes{
	string nome;
	string email;
	int numero_de_inscricao;
	lista_de_participantes *ant;
	lista_de_participantes *prox;
};

struct descritor_de_participantes{
		lista_de_participantes *ini;
		lista_de_participantes *fim;
		int tam;
};

descritor_de_participantes *criar_lista_de_participantes(){
	descritor_de_participantes *novo=new descritor_de_participantes;
	novo->ini=NULL;
	novo->fim=NULL;
	novo->tam=0;
	return novo;
}

struct lista_de_atividades{
	string nome_da_atividade;
	string tipo_da_atividade;
	float hora_da_atividade;
	string data_da_atividade;
	lista_de_atividades *ant;
	lista_de_atividades *prox;
};

struct descritor_de_ativades{
	lista_de_atividades *ini;
	lista_de_atividades *fim;
	int tam;
};

descritor_de_ativades *criar_lista_de_atividades(){
	descritor_de_ativades *novo=new descritor_de_ativades;
	novo->ini=NULL;
	novo->fim=NULL;
	novo->tam=0;
	return novo;		
}

void adicionar_inscricao(descritor_de_participantes *lista_de_inscricao,string nome,string email,int num){
	lista_de_participantes *novo=new lista_de_participantes;
	novo->nome=nome;
	novo->email=email;
	novo->numero_de_inscricao=num;
	novo->ant=NULL;
	novo->prox=NULL;
	if(lista_de_inscricao->ini==NULL){
		lista_de_inscricao->ini=novo;
		lista_de_inscricao->fim=novo;
		lista_de_inscricao->tam=1;
	}
	else{
		lista_de_inscricao->fim->prox=novo;
		novo->ant=lista_de_inscricao->fim;
		lista_de_inscricao->fim=novo;
		lista_de_inscricao->tam++;
	}
}

void adicioanr_atividade(descritor_de_ativades *lista_das_atividades,string nome,string tipo,float hora,string data){
	lista_de_atividades *novo=new lista_de_atividades;
	novo->nome_da_atividade=nome;
	novo->tipo_da_atividade=tipo;
	novo->hora_da_atividade=hora;
	novo->data_da_atividade=data;
	novo->ant=NULL;
	novo->prox=NULL;
	if (lista_das_atividades->ini==NULL)
	{
		lista_das_atividades->ini=novo;
		lista_das_atividades->fim=novo;
		lista_das_atividades->tam=1;
	}
	else{
		lista_das_atividades->fim->prox=novo;
		novo->ant=lista_das_atividades->fim;
		lista_das_atividades->fim=novo;
		lista_das_atividades->tam++;
	}
}

bool **criar_matriz(descritor_de_participantes *lista_de_incricao,descritor_de_ativades *lista_das_atividades){
	bool **matriz=new bool*[lista_de_incricao->tam];
	for (int i = 0; i < lista_de_incricao->tam; i++)
	{
		matriz[i]=new bool[lista_das_atividades->tam];
	}
	return matriz;
}

void adicionar_presenca(bool **matiz_de_presenca,descritor_de_participantes *lista_de_incricao,descritor_de_ativades*lista_das_atividades){
	lista_de_participantes *aux_de_inscritos=lista_de_incricao->ini;
	int linha=0,linhas=lista_de_incricao->tam;
	string pergunta;
	while (linha<linhas)
	{
		lista_de_atividades *aux_de_atividade=lista_das_atividades->ini;
		int coluna=0,colunas=lista_das_atividades->tam;
		while (coluna<colunas)
		{
			cout<<"digite sim se "<<aux_de_inscritos->nome<<" esteve presente na atividade"<<aux_de_atividade->nome_da_atividade<<"\ndigite não se "<<aux_de_inscritos->nome<<" nao esteve presente na atividade "<<aux_de_atividade->nome_da_atividade<<"\n"<<aux_de_inscritos->nome<<"esteve presente na atividade "<<aux_de_atividade->nome_da_atividade<<" no dia "<<aux_de_atividade->data_da_atividade<<": ";
            cin>>pergunta;
            if (pergunta=="sim"||pergunta=="SIM"||pergunta=="nao"||pergunta=="NAO")
            {
                if (pergunta=="SIM"||pergunta=="sim")
                {
                    matiz_de_presenca[linha][coluna]=true;
                }
                else{
                    matiz_de_presenca[linha][coluna]=false;
                }
                coluna++;
                aux_de_atividade=aux_de_atividade->prox;
            }
            else{
                cout<<"codigo não cadastrado porafavor digite de novo"<<endl;
            }
		}
		linha++;
		aux_de_inscritos=aux_de_inscritos->prox;
	}
}

descritor_de_participantes *verificar_os_participantes_do_sortei(bool **matriz_de_presenca,descritor_de_participantes *lista_de_inscritos,descritor_de_ativades *lista_das_atividades){
	descritor_de_participantes *lista_dos_participantes_do_sorteio=criar_lista_de_participantes();
	lista_de_participantes *aux_de_participantes=lista_de_inscritos->ini;
	for (int i = 0; i < lista_de_inscritos->tam; i++)
	{	int cont=0;
		for (int j = 0; j < lista_das_atividades->tam; j++)
		{
			if (matriz_de_presenca[i][j]==true)
			{
				cont++;
			}
			
		}
		float presenca=(cont*100)/lista_das_atividades->tam;
		if (presenca>=75)
		{
			adicionar_inscricao(lista_dos_participantes_do_sorteio,aux_de_participantes->nome,aux_de_participantes->email,aux_de_participantes->numero_de_inscricao);
		}
		aux_de_participantes=aux_de_participantes->prox;
	}
	return lista_dos_participantes_do_sorteio;
}

bool validar_o_sorteio(descritor_de_participantes * lista_dos_participantes_do_sorteio){
	if (lista_dos_participantes_do_sorteio->tam==1||lista_dos_participantes_do_sorteio->tam==2||lista_dos_participantes_do_sorteio->tam==0)
	{
		return false;
	}
	return true;
}

bool verificar_sortei(descritor_de_participantes *listas_dos_participantes_do_sorteio,descritor_de_participantes *lista_de_sorteados,int num){
    lista_de_participantes *aux;
	if (num==listas_dos_participantes_do_sorteio->tam)
	{
		aux=listas_dos_participantes_do_sorteio->fim;
	}
	else{ int cont=0;
    	aux=listas_dos_participantes_do_sorteio->ini;
    	while (cont<num)
    	{	cont++;
    		aux=aux->prox;
    	}
	}
    lista_de_participantes *aux2=lista_de_sorteados->ini;
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

lista_de_participantes *pos(descritor_de_participantes *listas_dos_participantes_do_sorteio,int num){
    lista_de_participantes *aux;
	if (listas_dos_participantes_do_sorteio->tam==num)
    {	
		aux=listas_dos_participantes_do_sorteio->fim;
    }
	else{ int cont=0;
		aux=listas_dos_participantes_do_sorteio->ini;
    	while (cont<num)
		{
        	cont++;
    		aux=aux->prox;
		}
	}
	return aux;
}

lista_de_participantes *v(descritor_de_participantes *listas_dos_participantes_do_sorteio,descritor_de_participantes *lista_de_sorteados){
    lista_de_participantes *aux=listas_dos_participantes_do_sorteio->ini;
    while (aux!=NULL)
    {   int cont=0;
        lista_de_participantes*aux2=lista_de_sorteados->ini;
        while (aux2!=NULL)
        {
            if (aux->nome==aux2->nome)
            {
                cont++;
            }
            aux2=aux2->prox;
        }
        if (cont==1)
        {
            aux=aux->prox;
        }
        else{
            return aux;
        }
    }
}

void sorteados(descritor_de_participantes *listas_dos_participantes_do_sorteio,descritor_de_participantes *lista_de_sorteados){
    if (listas_dos_participantes_do_sorteio->tam==3)
    {   srand(time(NULL));
        while (lista_de_sorteados->tam<2)
        {
            int cont=rand()%listas_dos_participantes_do_sorteio->tam;        
            if (verificar_sortei(listas_dos_participantes_do_sorteio,lista_de_sorteados,cont)==true)
            {
            lista_de_participantes *nome=pos(listas_dos_participantes_do_sorteio,cont);
            adicionar_inscricao(lista_de_sorteados,nome->nome,nome->email,nome->numero_de_inscricao);
            }
        }
        lista_de_participantes *p=v(listas_dos_participantes_do_sorteio,lista_de_sorteados);
        adicionar_inscricao(lista_de_sorteados,p->nome,p->email,p->numero_de_inscricao);
    }
    else{
        srand(time(NULL));
        while (lista_de_sorteados->tam<3){
        int count=rand()%listas_dos_participantes_do_sorteio->tam;        
        if (verificar_sortei(listas_dos_participantes_do_sorteio,lista_de_sorteados,count)==true)
        {
            lista_de_participantes *nome=pos(listas_dos_participantes_do_sorteio,count);
            adicionar_inscricao(lista_de_sorteados,nome->nome,nome->email,nome->numero_de_inscricao);
        }
        }  
    }
}

void mostrar(descritor_de_participantes *lista_dos_sorteados){
	lista_de_participantes *aux=lista_dos_sorteados->ini;
	while (aux!=NULL)
	{
		cout<<aux->nome<<endl;
		aux=aux->prox;
	}
}

int main() {
	descritor_de_participantes *lista_de_inscricao=criar_lista_de_participantes();
	string nome;
	string email;
	int numero_de_inscricao=0;
	while(nome!="fim"){
		cout<<"digite seu nome caso deseja parar de inseriri nomes digite fim\ndigite seu nome: ";
		cin>>nome;
		if(nome!="fim"){
			cout<<"digite seu email: ";
			cin>>email;
			numero_de_inscricao+=1;
			adicionar_inscricao(lista_de_inscricao,nome,email,numero_de_inscricao);
		}
	}
	descritor_de_ativades *lista_das_atividades=criar_lista_de_atividades();
	string nome_da_atividade;
	string tipo_da_atividade;
	float hora_da_atividade;
	string data_da_atividade;
	while(nome_da_atividade!="fim"){
		cout<<"digite o nome da atividade caso deseja parar de inseriri nomes de atividades digite fim\ndigite o nome da atividade: ";
        cin>>nome_da_atividade;
        if(nome_da_atividade!="fim"){
        	cout<<"digite o tipo da atividade: ";
        	cin>>tipo_da_atividade;
        	cout<<"caso a hora tenha minutos coloque um (.) para dividir os minutos das horas\ndigite a hora que inicia a atividade "<<nome_da_atividade<<": ";
            cin>>hora_da_atividade;
			cout<<"digite a data da atividade"<<nome_da_atividade<<": ";
			cin>>data_da_atividade;
			adicioanr_atividade(lista_das_atividades,nome_da_atividade,tipo_da_atividade,hora_da_atividade,data_da_atividade);
		}
	}
	bool **matriz_de_presenca=criar_matriz(lista_de_inscricao,lista_das_atividades);
	adicionar_presenca(matriz_de_presenca,lista_de_inscricao,lista_das_atividades);
	descritor_de_participantes *lista_dos_participantes_do_sorteio=verificar_os_participantes_do_sortei(matriz_de_presenca,lista_de_inscricao,lista_das_atividades);
	if (validar_o_sorteio(lista_dos_participantes_do_sorteio)==false)
	{
		cout<<"o sorteio não ocorrerar pois o numero de participantes e insuficiente";
	}
	else{
		descritor_de_participantes *lista_dos_sorteados=criar_lista_de_participantes();
		sorteados(lista_dos_participantes_do_sorteio,lista_dos_sorteados);
		mostrar(lista_dos_sorteados);
	}
	return 0;
}
