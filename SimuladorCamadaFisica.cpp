/*************************************************************
* 		****----Simulador da Camada Fisica - TR1 ------****
Grupo 6:
	(Supervisora) Leticia de Souza Soares, 15/0015178
	Thiaggo Ferreira Bispo de Souza, 17/0157024
	David Potolski Lafeta, 15/0122969 
	Filipi Teles da Silva, 12/0117754
	Christian Braga de Almeida Pires, 12/0028379
	
	link repositorio do Github: https://github.com/leticia-s/TrabFinal_Tr1_Grupo6
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
string lerStringArquivo(string mensagem);
void AplicacaoTransmissora ();
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

//variavel global para o tipo de codificacao
int tipo_de_codific;

string lerStringArquivo(string mensagem){
	char caracter;
	FILE *ptr;
	//ler Arquivo txt << tudo no arquivo txt sera somente uma unica string
	ptr = fopen("text_string.txt","rt"); //colocar nome do arquivo .txt para ser lido
	if (ptr == NULL){
    	printf("Problemas na abertura do arquivo\n");
    	exit(0);
	}
	
	while (fread(&caracter,sizeof(char),1,ptr)){    	// ler caracter por caracter
			mensagem += caracter; // adiciona caracter na string
	}
    fclose(ptr);
    return mensagem;
};//fim do metodo lerStringArquivo


void CamadaFisicaTransmissora (string quadro) {
	int tipoDeCodificacao = tipo_de_codific; //alterar de acordo o teste
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
	 cout << "Mensagem codificada em bits:\n"  << quadro << endl;
    return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria


string CamadaFisicaTransmissoraCodificacaoManchester (string quadro) {
	
	string codificada;
	int t = 0; //tempo do clock iniciando com 0
	unsigned int indice = 0;

	while(quadro[indice] != '\0'){
		//cada bit do quadro compara com 2 tempos de clock
		for(t=0;t!=2;t++){
		// um XOR do dos bits do quadro com o tempo do clock
			if (quadro[indice] == '1' && t== 0) codificada += '1';
			if (quadro[indice] == '1' && t== 1) codificada += '0';
			if (quadro[indice] == '0' && t== 1) codificada += '1';
			if (quadro[indice] == '0' && t== 0) codificada += '0';
           
		}
		indice += 1; // vai pro proximo bit do quadro
	}
cout << "Mensagem codificada (Manchester):\n" << codificada << endl;

return codificada;

}//fim do metodo CamadaFisicaTransmissoraCodificacaoManchester


string CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(string quadro) {
	
	string codificada;
	unsigned int indice = 0; 
    //se primeiro bit do quadro for 0
	if (quadro[indice] == '1'){ 
		codificada += '1';
		codificada += '0';
	}
    //se primeiro bit do quadro for 1
	if (quadro[indice] == '0'){ 
		codificada += '0';
		codificada += '1';
	}
	indice++;
    //proximos bits
	while(quadro[indice] != '\0'){
            // se bit do quadro igual ao ultimo bit codificado
			if (quadro[indice] == codificada[(indice*2)-1]){
				codificada += '1';
				codificada += '0';
			} 
			//se bit do quadro diferente do ultimo bit codificado
			if (quadro[indice] != codificada[(indice*2)-1]){
				codificada += '0';
				codificada += '1';
			}
		indice += 1;
	}
cout << "Mensagem codificada (Manchester Diferencial):\n"  << codificada << endl;

return codificada;

	
}//fim do CamadaFisicaTransmissoraCodificacaoManchesterDiferencial



string CamadaFisicaReceptoraDecodificacaoBinaria (string quadro) {

	return quadro;
	
}//fim do metodo CamadaFisicaReceptoraDecodificacaoBinaria


string CamadaFisicaReceptoraDecodificacaoManchester (string quadro) {
	
	string decodificada;
	unsigned int indice = 0;

	while(quadro[indice] != '\0'){
			//verifica os bits nas posicoes pares (0...2...4...) do quadro
			if (quadro[indice] == '1' ) decodificada += '1';
			if (quadro[indice] == '0' ) decodificada += '0';
			indice+=2;
		}
		// Nao usei clock para fazer o decodifica pq caso o quadro[Clock] seja 1 o decodifica[Clock2] e 1 tambem
		// Como o codigo de Manchester possui a logica de a cada ciclo de clock 1 bit tranmitido sera codificado para 2 sempre 01 ou 10
		// Caso seja 10 o bit da mensagem original sera 1 e caso seja 01 o bit da mensagem original sera 0
		// Isso porque eu tomei como base para o codifica que o clock comeca em 0 e vai pra 1 
		cout << "Mensagem decodificada (Manchester):\n" << decodificada << endl;
return decodificada;

	
}//fim do metodo CamadaFisicaReceptoraDecodificacaoManchester


string CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(string quadro){
	
	string decodificada;
	unsigned int indice = 0;
		//se primeiro bit o quadro for igual a 1
		if (quadro[indice] == '1' ){
				decodificada += '1';;
		} 
		//se primeiro bit o quadro for igual a 0
		if (quadro[indice] == '0'){
			decodificada += '0';
			;
		}
	indice+=2; // proxima posicao 2 do quadro
	
    // verifica restantes dos bits do quadro nas posicoes pares (0,2,4,6...) 
	while(quadro[indice] != '\0'){
		    //se posicao par do quadro atual for igual a posicao par anterior do quadro
			if (quadro[indice] ==  quadro[indice-2]){
				decodificada += '0';
			} 
		    //se posicao par do quadro atual for diferente a posicao par anterior do quadro
			if (quadro[indice] != quadro[indice-2]){
				decodificada += '1';
			} 
			indice+=2; 
		}
		cout << "Mensagem decodificada (Manchester Diferencial):\n" << decodificada << endl;
return decodificada;
	
}//fim do CamadaFisicaReceptoraDecodificacaoManchesterDiferencial


void CamadaDeAplicacaoReceptora (string quadro) {
	string mensagem;
	unsigned int posCaracter = 0; 
	//tem que pegar a cada 8 bits sera um caracter
	while(quadro[posCaracter] != '\0'){
		bitset<8> b(quadro.substr(posCaracter,8));// pega 8 bits de um caracter
		mensagem += b.to_ulong(); //transforma os 8 bits para um inteiro ulong e depois pra caracter
		posCaracter += 8;// a cada posicao multiplo de 8 sera um caracter
	}
	//chama proxima camada
	AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora


void AplicacaoReceptora (string mensagem) {
	cout << "A mensagem recebida foi:\n" << mensagem << endl;
}//fim do metodo AplicacaoReceptora
