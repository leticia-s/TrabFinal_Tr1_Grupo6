/*************************************************************
* 		****----NAO ESQUECER DOS COMENTARIOS!------****
Grupo 6:
	(Supervisora) Leticia de Souza Soares, 15/0015178
	Thiaggo Ferreira Bispo de Souza, 17/0157024
	David Potolski Lafeta, 15/0122969 
	Filipi Teles da Silva, 12/0117754
	Christian Braga de Almeida Pires, 12/0028379
*********************************************************** */

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

//declaracao de funcoes

void AplicacaoTransmissora (void);
void CamadaDeAplicacaoTransmissora (string mensagem);
void CamadaFisicaTransmissora (string quadro);
string CamadaFisicaTransmissoraCodificacaoBinaria (string quadro );
string CamadaFisicaTransmissoraCodificacaoManchester (string quadro );
string CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(string quadro );
void MeioDeComunicacao (string fluxoBrutoDeBits );
void CamadaFisicaReceptora (string quadro);
string CamadaFisicaReceptoraDecodificacaoBinaria (string quadro );
string CamadaFisicaReceptoraDecodificacaoManchester (string quadro );
string CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(string quadro);
void CamadaDeAplicacaoReceptora (string quadro );
void AplicacaoReceptora(string mensagem);



int main () {
AplicacaoTransmissora();
}//fim do metodo main


void AplicacaoTransmissora (void) {
	string mensagem;
	cout << "Digite uma mensagem:" << endl;
    getline(cin, mensagem); // cin sozinho nao pega espacos
	//chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo AplicacaoTransmissora


void CamadaDeAplicacaoTransmissora (string mensagem) {
  	string binary_output;
  	//converter a mensagem para binario
  	for (size_t i = 0; i < mensagem.size(); ++i){
	  	bitset<8> b(mensagem.c_str()[i]); // cada caracter tem 8 bits => 4 bytes
	    binary_output+= b.to_string(); //cada 8 bits(cada caracter) coloca na string
  	}
	string quadro = binary_output;//trabalhar com bits!!!
	//chama a proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaDeAplicacaoTransmissora


void CamadaFisicaTransmissora (string quadro) {
	int tipoDeCodificacao = 2; //alterar de acordo o teste
	string fluxoBrutoDeBits; //ATENCAO: trabalhar com BITS!!!
	switch (tipoDeCodificacao) {
		case 0 : //codificao binaria
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
		break;
		case 1 : //codificacao manchester
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoManchester(quadro);
		break;
		case 2 : //codificacao manchester diferencial
			fluxoBrutoDeBits =
			CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);
		break;
	}//fim do switch/case
	MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


// *******************OBSERVACAO IMPORTANTE*********************
//   QUANDO FOR TESTAR TEM QUE ALTERAR OPCAO DE TESTE NAS DUAS 
//FUN�OES TANTO CAMADAFISICATRANSMISSORA QUANTO NA RECEPTORA


string CamadaFisicaTransmissoraCodificacaoBinaria (string quadro) {
	 
    return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria


string CamadaFisicaTransmissoraCodificacaoManchester (string quadro) {
	
	string codificada;
	int t = 0;
	unsigned int Clock = 0;

	while(quadro[Clock] != '\0'){

		for(int i=0;i!=2;i++){
			if (quadro[Clock] == '1' && t== 0) codificada += '1';
			if (quadro[Clock] == '1' && t== 1) codificada += '0';
			if (quadro[Clock] == '0' && t== 1) codificada += '1';
			if (quadro[Clock] == '0' && t== 0) codificada += '0';
			t++;
		}
		t = 0;
		Clock += 1;
	}
return codificada;

}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester


string CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(string quadro) {
	
	string codificada;
	unsigned int Clock = 0;

	if (quadro[Clock] == '1'){ 
		codificada += '1';
		codificada += '0';
	}

	if (quadro[Clock] == '0'){ 
		codificada += '0';
		codificada += '1';
	}
	Clock++;
	while(quadro[Clock] != '\0'){

			if (quadro[Clock] == '1' && codificada[(Clock*2)-1] == '1'){
				codificada += '1';
				codificada += '0';
			} 
			if (quadro[Clock] == '1' && codificada[(Clock*2)-1] == '0'){
				codificada += '0';
				codificada += '1';
			} 
			if (quadro[Clock] == '0' && codificada[(Clock*2)-1] == '1'){
				codificada += '0';
				codificada += '1';
			} 
			if (quadro[Clock] == '0' && codificada[(Clock*2)-1] == '0'){
				codificada += '1';
				codificada += '0';
			} 

		Clock += 1;
	}
	cout << codificada << endl;
return codificada;

	
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial
/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA (transmissor) para um
* ponto B (receptor)
*/

/////////////////////////////////////////////////////////////////////////////////////

void MeioDeComunicacao (string fluxoBrutoDeBits) {
	//OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
	string fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
	unsigned int FluxoBitABit; 
	while ((unsigned) fluxoBrutoDeBitsPontoB.size()!= (unsigned) fluxoBrutoDeBitsPontoA.size()) {
		FluxoBitABit =  fluxoBrutoDeBitsPontoB.size(); //tamanho de B, sera exatamente a posicao do bit em A que tem que ser transferido para B
		fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA[FluxoBitABit];  //BITS! Sendo transferidos
	}//fim do while
	//chama proxima camada
	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao


void CamadaFisicaReceptora (string quadro) {
	int tipoDeDecodificacao = 1; //alterar de acordo o teste
	string fluxoBrutoDeBits; //ATENCAO: trabalhar com BITS!!!
	switch (tipoDeDecodificacao) {
		case 0 : //codificao binaria
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
		break;
		case 1 : //codificacao manchester
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
		break;
		case 2 : //codificacao manchester diferencial
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
		break;
	}//fim do switch/case
//chama proxima camada
	
	//	cout << "tesets : "<< fluxoBrutoDeBits << endl;
	CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora


//
//            FUNÇÔES PARA SEREM FEITAS
//

string CamadaFisicaReceptoraDecodificacaoBinaria (string quadro) {
	
	return quadro;
	
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria


string CamadaFisicaReceptoraDecodificacaoManchester (string quadro) {
	
	string decodificada;
	unsigned int Clock = 0;

	while(quadro[Clock] < quadro.length()){
			if (quadro[Clock] == '1' ) decodificada += '1';
			if (quadro[Clock] == '0' ) decodificada += '0';
			Clock+=2;
		}
		// Não usei clock para fazer o decodifica pq caso o quadro[Clock] seja 1 o decodifica[Clock2] é 1 tmb 
		// Como o código de Manchester possui a lógica de a cada ciclo de clock 1 bit tranmitido será codificado para 2 sempre 01 ou 10
		// Caso seja 10 o bit da mensagem original é 1 e caso seja 01 o bit da mensagem original é 0
		// Isso porque eu tomei como base para o codifica que o clock começa em 0 e vai pra 1 
		
return decodificada;

	
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester


string CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(string quadro){
	//implementacao do algoritmo para DECODIFICAR
	
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial


//////////////////////////////////////////////////////////////////////////////

void CamadaDeAplicacaoReceptora (string quadro) {
	string mensagem;
	unsigned int posCaracter = 0; 
	//tem que pegar a cada 8 bits sera um caracter
	while(quadro[posCaracter] != '\0'){
		bitset<8> b(quadro.substr(posCaracter,8));
		mensagem += b.to_ulong(); //estava trabalhando com bits
		posCaracter += 8;
	}
	//chama proxima camada
	AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora


void AplicacaoReceptora (string mensagem) {
	cout << "A mensagem recebida foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora
