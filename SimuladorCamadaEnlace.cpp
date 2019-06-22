/*************************************************************
* 		****----Simulador da Camada Enlace - TR1 ------****
Grupo 6:
	(Supervisora) Leticia de Souza Soares, 15/0015178
	Thiaggo Ferreira Bispo de Souza, 17/0157024
	David Potolski Lafeta, 15/0122969 
	Filipi Teles da Silva, 12/0117754
	Christian Braga de Almeida Pires, 12/0028379
*********************************************************** */
 #include "SimuladorCamadaFisica.cpp"  // inclusao das funcoes da camada fisica

#include <time.h>
 //declaracao de funcoes   --- Nao e para fazer o de Enquadramento

void CamadaEnlaceDadosTransmissora (string quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro );
void MeioDeComunicacao (string fluxoBrutoDeBits );
void CamadaEnlaceDadosReceptora(string *quadro);
void CamadaEnlaceDadosReceptoraControleDeErro(string *quadro);
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string *quadro );
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string *quadro);
void CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) ;
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro );

int tipoDeControleDeErro = 99999; //alterar de acordo com o teste

int main () {
    srand(time(NULL));
    string q = "10011001";
//AplicacaoTransmissora();

    CamadaEnlaceDadosTransmissora(q);
    return 0;
}//fim do metodo main


/* **********************************************************************
*******************Controle de Erro - Transmiss�o************************
************************************************************************/


void CamadaEnlaceDadosTransmissora (string quadro ) {
	CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora


/* **********************************************************************
*******************Controle de Erro - Transmiss�o************************
************************************************************************/


void CamadaEnlaceDadosTransmissoraControleDeErro (string quadro ) {
    while(tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2 ) {
        cout<< "Insira o tipo de controle:\n    0- Bit de Paridade Par\n    1- Bit de Paridade Impar\n    2- CRC\n    3- Codigo de Hamming\n>>";
        cin >> tipoDeControleDeErro;
        cin.ignore();// se for usar getline tem que limpar \n do buffer
        if (tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2)
            cout << "tipo de codificacao invalida!" << endl;
    }
	switch (tipoDeControleDeErro) {
	case 0 : //bit de paridade par
	CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
	break;
	case 1 : //bit de paridade impar
	CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
	break;
	case 2 : //CRC
	//codigo
	case 3 : //codigo de Hamming
	//codigo
	break;
	}//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Transmiss�o************************
************************************************************************/

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro ) {
 int count = 0;
 char bitParidade;
 
 for(int i = 0; i < quadro.size(); i++){    //Caminha pelo quadro
	 if (quadro[i] == '1'){
		 count++;                           //Conta o número de 1s
	 }
 }
 ((count % 2) != 0) ? quadro += '1' : quadro += '0';    //Se o número de 1s for par, o bit de paridade é 1, se não for par o bit de paridade é 0

cout << "Quadro por bit de paridade par:" << quadro << endl;

MeioDeComunicacao(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro){
int count = 0;
 
 for(int i = 0; i < quadro.size(); i++){
	 if (quadro[i] == '1'){
		 count++;
	 }
 }
 ((count % 2) != 0) ? quadro += '0' : quadro += '1'; 

cout << "Quadro por bit de paridade impar:" << quadro << endl;

MeioDeComunicacao(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

void CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro ) {
    string gerador = "00000100110000010001110110110111";        //0x 04 C1 1D B7
    string geradorEfetivo;
    int geradorPos = gerador.size() - quadro.size();

    for(int i = 0; i < quadro.size() ; i++){
        geradorEfetivo += gerador[geradorPos];
        geradorPos++;
    }
    cout << "Gerador Efetivo:" << geradorEfetivo << endl;


}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming


/* **********************************************************************
*****************Meio de Comunica��o****OBS.: PROVOCAR O ERRO!***********
************************************************************************/

void MeioDeComunicacao (string fluxoBrutoDeBits ) {
 //OBS: trabalhar com BITS e nao com BYTES!!!
	int erro, porcentagemDeErros, BitABit;
	string fluxoBrutoDeBitsPontoA , fluxoBrutoDeBitsPontoB ;

	porcentagemDeErros = 70; //10%, 20%, 30%, 40%, ..., 100%  <-------
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits; //<-------
	while (fluxoBrutoDeBitsPontoB.length() !=fluxoBrutoDeBitsPontoA.length()) {
		BitABit = fluxoBrutoDeBitsPontoB.length();
		erro = (rand() % 101);
		if (erro > porcentagemDeErros) //fazer a probabilidade do erro <-------
		 	fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA[BitABit]; //BITS!!!   
		else //ERRO! INVERTER (usa condicao ternaria)
		 	(fluxoBrutoDeBitsPontoA[BitABit]== '0') ?
		 	fluxoBrutoDeBitsPontoB += '1'  :
		 	fluxoBrutoDeBitsPontoB += '0';

	}//fim do while
	cout << "Fluxo de bits ponto B:" <<fluxoBrutoDeBitsPontoB << endl;
    CamadaEnlaceDadosReceptora(&fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

/* **********************************************************************
*******************Controle de Erro - Recep��o***************************
************************************************************************/

void CamadaEnlaceDadosReceptora(string *quadro) {
	 CamadaEnlaceDadosReceptoraControleDeErro(quadro);
	 //chama proxima camada
	 CamadaDeAplicacaoReceptora(*quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

/* **********************************************************************
*******************Controle de Erro - Recep��o***************************
************************************************************************/

void CamadaEnlaceDadosReceptoraControleDeErro(string *quadro) {
	 string quadro_aux = *quadro;
	 switch (tipoDeControleDeErro) {
	 case 0 : //bit de paridade par
	 CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
	 quadro_aux = *quadro;
	 break;
	 case 1 : //bit de paridade impar
	 CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(quadro);
	 break;
	 case 2 : //CRC
	 //codigo
	 case 3 : //codigo de hamming
	 //codigo
	 break;
	 }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Recep��o***************************
************************************************************************/


void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string *quadro ) {
    int count = 0, Par;
    string quadro_aux = (*quadro);

    for(int bitPos = 0; bitPos < quadro_aux.size(); bitPos++){
        if(quadro_aux[bitPos] == '1'){
            count++;
        }
    }

    ((count % 2) == 0) ? Par = 1 : Par = 0;
    if (Par != 1) {
        cout << "Foi detectado um erro!!!" << endl;
        exit(1);
    }

    *quadro = quadro_aux.substr(0,8);
    quadro_aux = *quadro;

}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string *quadro) {
    int count = 0, Impar;
    string quadro_aux = (*quadro);

    for(int bitPos = 0; bitPos < quadro_aux.size(); bitPos++){
        if(quadro_aux[bitPos] == '1'){
            count++;
        }
    }

    ((count % 2) == 0) ? Impar = 0 : Impar = 1;
    if (Impar != 1) {
        cout << "Foi detectado um erro!!!" << endl;
        exit(1);
    }

    *quadro = quadro_aux.substr(0,8);
    quadro_aux = *quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
void CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
 //usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming


