#include <iostream>
#include <string>
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
  int cont = 1;

  while(!finalLista(pLista)){
    tInvestimento informacao = pLista -> marcador -> info;

    cout << "Bloco de dados " << cont << ":\n{" << endl;
    cout << "Montante Investido: " << informacao.montInicial << endl;
    cout << "Juro ao ano: " << informacao.juroAno << endl;
    cout << "Periodo em anos: " << informacao.periodoAno << endl;
    cout << "}\n" << endl;

    pLista->marcador = pLista->marcador->proximo;
    cont++;
  }

  cout << "Total de dados carregados: " << (cont - 1) << endl;
}

void clearInput() {
  cin.clear();
  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void gravarLista(tLista* pLista){
  ofstream file;

  file.open("investimentos.txt", ios::out);
  
  pLista -> marcador = pLista -> primeiro;
  while(!finalLista(pLista)){
    tInvestimento informacao = pLista -> marcador -> info;

    file << "Montante(investido): " << informacao.montInicial << endl;
    file << "Juro(ano): " << informacao.juroAno << endl;
    file << "Periodo(anos): " << informacao.periodoAno << endl;

    pLista->marcador = pLista->marcador->proximo;
  }

  file.close();
}

void gravarArquivo(tLista* pLista, tInvestimento invest){
  ofstream file;
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
    incluirNoFim(pLista, invest);
  }
  
  
  gravarLista(pLista);

}

void lerArquivo(tLista* pLista, tInvestimento info){
  ifstream file;
  string text = " ";
  int aux;

  file.open("investimentos.txt", ios::in);
  while(!file.eof()){
    file >> text;
    if (text == "Montante(investido):"){
      file >> text;
      cout << "";
      cout << "";
      info.montInicial = stof(text);
    }else if(text == "Juro(ano):"){
      file >> text;
      info.juroAno = stof(text);
    }else if(text == "Periodo(anos):"){
      file >> text;
      info.periodoAno = stof(text);
    }

    aux++;

    if (aux == 3){
      incluirNoFim(pLista, info);
      aux = 0;
    }
    
  }
  file.close();

  imprimirLista(pLista);
}

int input(){
  int choice;
  cout << "\n******************************************" << endl;
  cout << "\t1. Para gravar um banco de dados" << endl;
  cout << "\t2. Para ler um banco de dados" << endl;
  cout << "\t3. Para  avisos e instruções" << endl;
  cout << "\t4. Para sair do programa" << endl;
  cout << "******************************************" << endl;
  cin >> choice;
  return choice;
}

void instrucoes(){
  cout << "Avisos e instruções:\n" << endl;
  cout << "Ao escolher a opção gravar arquivo, o programa irá criar um arquivo .txt na pasta do programa com o nome de 'investimentos.txt'." << endl;
  cout << "Enquanto escolher a opção gravar no menu, após ter escolhido da primeira vez, o programa irá continuar a coletar os dados" << endl;
  cout << "e colocá-los dentro do arquivo." << endl;
  cout << "\nCaso escolha a opção ler, o programa irá ler o Arquivo e exibir suas informações na tela." << endl;
  cout << "\nIMPORTANTE: Para adicionar novos dados em um arquivo já existente, deve-se ler o arquivo primeiro, antes de gravar, caso" << endl; 
  cout << "o contrário programa irá sobrepor as informações do antigo arquivo, ou seja, apagará os dados que estavama antes e colocara" << endl;
  cout << "novos no lugar." << endl;
}

int main() {
  tLista* investimento = new tLista;
  tInvestimento invest;
  bool is_running = true;
  cout << R"""(
       ______               __                ___    __                
      /\__  _\             /\ \              /\_ \  /\ \               
      \/_/\ \/ _ __    __  \ \ \____     __  \//\ \ \ \ \___     ___   
         \ \ \/\`'__\/'__`\ \ \ '__`\  /'__`\  \ \ \ \ \  _ `\  / __`\ 
          \ \ \ \ \//\ \L\.\_\ \ \L\ \/\ \L\.\_ \_\ \_\ \ \ \ \/\ \L\ \
           \ \_\ \_\\ \__/.\_\\ \_,__/\ \__/.\_\/\____\\ \_\ \_\ \____/
            \/_/\/_/ \/__/\/_/ \/___/  \/__/\/_/\/____/ \/_/\/_/\/___/ 
                                                                      
                                                                      
         ____    ______         
       /\   _`\ /\  _  \        
       \ \ \L\ \\ \ \L\ \       
        \ \ ,__/ \ \  __ \      
         \ \ \/ __\ \ \/\ \  __ 
          \ \_\/\_\\ \_\ \_\/\_\
           \/_/\/_/ \/_/\/_/\/_/
  )""" << endl;

  while (is_running){

    switch (input()){
      case 1: 
        cout << "\033[2J\033[1;1H";
        gravarArquivo(investimento, invest);
        break;
      case 2: 
        cout << "\033[2J\033[1;1H";
        lerArquivo(investimento, invest);
        break;
      case 3: 
        cout << "\033[2J\033[1;1H";
        instrucoes();
        break;
      case 4:
        is_running = false;
        break;
      default:
        cout << "\033[2J\033[1;1H"; 
        cout << "Escolha inválida ou numero digitado incorrentamente tente novamente" << endl;
        clearInput();
        continue;
    }
  }

  return 0;
}