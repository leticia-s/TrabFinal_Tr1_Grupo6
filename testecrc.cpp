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

int main () {
	//Utilizado a parte teorica do livro do tanenbaum 5 edicao pag 132 a 134 e estrategia para o calculo de https://pt.wikipedia.org/wiki/CRC
	//Passos: 	Seja r o grau de G(x), o polinomio gerador (CRC-32), e m o numero de bits do quadro (M(x)) adicionar r zeros ao final do quadro de forma que tenha m+r bits para que o quadro sempre seja divisivel pelo gerador
	//			Dividir as strings correspondentes aos indices dos polinomios usando operacoes modulo 2 (mesma coisa que o XOR)
	//			Adicionar o resto, que sempre tem r ou menos bits, na string do quadro original
	//			retornar o quadro			


	string geradorcrc = "10011";  //usar polinomio CRC-32(IEEE 802)
	//string geradorcrc = "100000100110000010001110110110111";
	string quadro = "1101011111";	//Essa linha vai sumir quando colocar no codigo original pois vem como parametro da funcao
	string quadroresultado = quadro; //quadro usado para armazenar o resultado de cada iteracao
	string quadroresto; //quadro usado para armazenar o resto da divisao polinomial
	int contador, indice, i, j, k;	//i, j, k sao indices de loop, os outros dois sao explicados abaixo

	cout << "Mensagem: " << quadro << endl;

	//Loop para adicionar zeros ao final do quadro
	for (i = 0; i < geradorcrc.size()-1; i++) {
		quadroresultado += '0';
	}

	//Loop para adicionar zeros ao final do quadro
	for (i = 0; i < geradorcrc.size()-1; i++) {
		quadro += '0';
	}
	

	cout << "Mensagem com zeros: " << quadroresultado << endl;

	while (quadroresultado.size() >= geradorcrc.size() ) {	//Loop para verificar se o quadro ainda pode ser dividido pelo polinomio gerador
		contador = 0;	//conta quantos bits foram testados	(vai ser necessario mais a frente)
		indice = 0; 	//marca qual posicao do bit esta sendo testada no quadro
		string quadroresultado2;	//quadro auxiliar para os calculos. Armazena o resultado provisorio do resto de cada iteracao da divisao
		while (geradorcrc[indice] != '\0') {

			if(quadroresultado[indice] == geradorcrc[indice]){	//Se o bit quadro for igual o resultado e zero, caso contrario 1 (XOR)

				
				quadroresultado2 += '0';

				indice++;
				contador++;
			}
			else {
				quadroresultado2 += '1';
				indice++;
				contador++;
			}
		}

		//Loop que conta quantos zeros a esquerda tem no resto para poder contar quantos bits significativos existem no resto 
		//Pois a condicao de divisibilidade é que a quantidade de bits do dividendo (quadro) e do divisor (gerador) deve ser a mesma
		i=0;
		if (quadroresultado2[i] == '0' && quadroresultado2[i] != '\0') {
			while (quadroresultado2[i] == '0') {
				i++;
			}
		}
		k=i;
		string quadroresultado3; //Quadro que armazena o resto concatenado com o restante dos bits ainda nao utilizados do dividendo. 

		//Loop que elinima os zeros a esquerda e coloca o restante no novo quadro
		if (quadroresultado2.size() != k)  {
			for(j=0; j < (quadroresultado2.size() - k) ; j++) {
				quadroresultado3 += quadroresultado2[i];
				i++;
			}
		}
		k = contador;

		//Loop que copia o resto dos bits do quadro original ainda nao utilizados para o quadro que sera utilizado na proxima iteracao
		for(j=0; j < (quadroresultado.size() - k) ; j++) {
			quadroresultado3 += quadroresultado[contador];
			contador++;
		}
		quadroresultado = quadroresultado3;
	}
	quadroresto = quadroresultado;
	cout << "Resto: " << quadroresto << endl;
	i=0;
	j = quadro.size()-1;

	//Loop que calcula a soma do resto com os bits zero adicionados ao quadro (Como a soma e subtracao sao modulo 2 (nao tem 'vai uns' nem emprestimo), é a mesma coisa que fazer um XOR)
	//Loop comeca do final das strings e faz a operacao de soma (pois os zeros iniciais foram adicionados no final do quadro)
	for (k = quadroresto.size() - 1; k >= 0 ; k--) {
		if (quadro[j] == quadroresto[k]) {
			quadro[j] = '0';
			j--;
		}
		else{
			quadro[j] = '1';
			j--;
		}
	}
	cout << "Mensagem Final: " << quadro << endl;
	getchar();
	//return quadro
	return 0;
}
