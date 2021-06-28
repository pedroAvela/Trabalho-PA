#include <iostream>

using namespace std;

struct tinvestimento{
  float montInicial;
  float juroAno;
  float periodoAno;
};

//Criação do Nó
struct tNo{
  tinvestimento info;
  tNo* proximo;
};

tNo* criaNo (tinvestimento item){
  tNo* no = new tNo;

  no -> info = item;
  no -> proximo = NULL;

  return no;
}
/////////////////////

struct tLista{
  tNo* primeiro;
  tNo* ultimo;
  tNo* marcador;
  int tamanho = 0;
};

int obterTamanho(tLista* pLista){
  return pLista -> tamanho;
}

bool listaVazia(tLista* pLista){
  return (pLista->tamanho == 0);
}

bool finalLista(tLista* pLista){
  return (pLista->marcador == 0);
}

void incluirNoFim(tLista* pLista, tinvestimento info){
  tNo* no;
  no = criaNo(info);

  if (listaVazia(pLista)){
    pLista -> primeiro = no;
  }else{
    pLista -> ultimo -> proximo = no;
  }

  pLista -> ultimo = no;
  pLista -> marcador = no;
  pLista -> tamanho++;
}

void imprimirLista(tLista* pLista){
  pLista -> marcador = pLista -> primeiro;

  while(!finalLista(pLista)){
    tinvestimento informacao = pLista -> marcador -> info;

    cout << "Montante Investido: " << informacao.montInicial << endl;
    cout << "Juro ao ano: " << informacao.juroAno << endl;
    cout << "Periodo em anos: " << informacao.periodoAno << endl;

    pLista->marcador = pLista->marcador->proximo;
  }
}

int main() {
  tLista* investimento = new tLista;
  tinvestimento invest, invest1, invest2;

  invest.montInicial = invest1.montInicial = 10;
  invest2.montInicial = 15;
  invest.juroAno = invest1.juroAno = 2;
  invest2.juroAno = 5;
  invest.periodoAno = 2;
  invest1.periodoAno = 5;
  invest2.periodoAno = 3;

  incluirNoFim(investimento, invest);
  incluirNoFim(investimento, invest1);
  incluirNoFim(investimento, invest2);

  cout << "Tamanho lista: " << obterTamanho(investimento) << endl;

  imprimirLista(investimento);


}