#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <iostream>
#include <sstream>
#include <bitset>
#include<stdbool.h>
using std::string;
using std::stringstream;
using namespace std;
#include <math.h>

string CamadaDeAplicacaoTransmissora (string mensagem) {
  	string binary_output;
  	int i=0;
  	//converter a mensagem para binario
  	while(mensagem[i] != '\0'){
	  	bitset<8> b(mensagem.c_str()[i]); // cada caracter tem 8 bits 
	    binary_output+= b.to_string(); //cada 8 bits(cada caracter) coloca na string
	    i++; //atualiza posicao
  	}
	string quadro = binary_output;//trabalhar com bits!!!
	//chama a proxima camada 
    return quadro;
}//fim do metodo CamadaDeAplicacaoTransmissora

int numde1s_pn(int posicao_pn, string quadro){
	int cont,pos, pula_prox_conjunto_pn;
	pula_prox_conjunto_pn = posicao_pn;//atualiza primeiro conjunto n
	while(pula_prox_conjunto_pn<=quadro.size()){
		pos = pula_prox_conjunto_pn; //atualiza onde inicia cada conjunto n-n
		//conta numero de uns do conjunto n 
		for(int i=0;i<posicao_pn;i++){
			//nao pode passa do tamanho da string e nao pode conta o bit do Pn 
			if(quadro[pos-1] == '1' && pos <= quadro.size() && pos != posicao_pn){
				cont++;
			}	
			pos++; //atualiza proximo bit
		}
		pula_prox_conjunto_pn += 2*posicao_pn;
	}
	return cont;		
};




int main() {

	int numberOf1;
	int posicaoP = 0 ;
	int posicaoQuadro = 0;
	int i;
	string quadroFinal;
	string quadro;
	int tamanhoQuadroFinal;
	
	int numeroBitsParidade;
	
	quadro = CamadaDeAplicacaoTransmissora("oi");
	
	cout << quadro << endl;
	
	
	numeroBitsParidade = ceil(log2(quadro.size()+1)) ;
	
	cout << quadro.size() << "\n" << ceil(log2(quadro.size()+1)) << endl;
	
	
	tamanhoQuadroFinal = quadro.size() + numeroBitsParidade;
	
	for(i=1; i<=tamanhoQuadroFinal; i++){
	    
	    if(i==pow(2,posicaoP)){
	        quadroFinal += '0';
	        posicaoP++;
	    } else { 
	        quadroFinal+=quadro[posicaoQuadro];
	        posicaoQuadro++;
	    }
	}
	
	cout << quadroFinal << endl;
	
	posicaoP = 0;
	for(int n=0;n < numeroBitsParidade - 1;n++){
		numberOf1 =  numde1s_pn(pow(2,posicaoP), quadroFinal);
		((numberOf1 % 2) != 0) ? quadroFinal[pow(2,posicaoP) - 1] = '1' : quadroFinal[pow(2,posicaoP) - 1] = '0';
		posicaoP++;
	}
	
	cout << quadroFinal;

}
