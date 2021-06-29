#include <iostream>
#include <fstream>

using namespace std;

struct tInvestimento{
  float montInicial;
  float juroAno;
  float periodoAno;
};

//Criação do Nó
struct tNo{
  tInvestimento info;
  tNo* proximo;
};

tNo* criaNo (tInvestimento item){
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

void incluirNoFim(tLista* pLista, tInvestimento info){
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
    tInvestimento informacao = pLista -> marcador -> info;

    cout << "Montante Investido: " << informacao.montInicial << endl;
    cout << "Juro ao ano: " << informacao.juroAno << endl;
    cout << "Periodo em anos: " << informacao.periodoAno << endl;

    pLista->marcador = pLista->marcador->proximo;
  }
}

void gravarArquivo(tLista* pLista){
  ofstream file;
  pLista -> marcador = pLista -> primeiro;

  file.open("investimentos.txt", ios::out);

  while(!finalLista(pLista)){
    tInvestimento informacao = pLista -> marcador -> info;

    file << "Montante Investido: " << informacao.montInicial << endl;
    file << "Juro ao ano: " << informacao.juroAno << endl;
    file << "Periodo em anos: " << informacao.periodoAno << endl;

    pLista->marcador = pLista->marcador->proximo;
  }
  
}

int main() {
  tLista* investimento = new tLista;
  tInvestimento invest;
  int tamanho;

  cout << "Digite a quantidade de informacoes que ira digitar: " << endl;
  cin >> tamanho;

  for (int i = 0; i < tamanho; i++){
    cout << "\nMontante Inicial: ";
    cin >> invest.montInicial;
    cout << "Juro ao Ano: ";
    cin >> invest.juroAno;
    cout << "Periodo ao Ano: ";
    cin >> invest.periodoAno;
    incluirNoFim(investimento, invest);
  }
  
  cout << "\nTamanho lista: " << obterTamanho(investimento) << endl;

  gravarArquivo(investimento);


}