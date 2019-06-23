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
#include <math.h>//necess�ria para usar as funcao de pontenciacao pow(variavel, expoente)
#include <time.h> //srand
 //declaracao de funcoes   --- Nao e para fazer o de Enquadramento

void CamadaEnlaceDadosTransmissora (string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErro (string quadro );
string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro );
string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro );
string CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro );
void MeioDeComunicacao (string fluxoBrutoDeBits );
void CamadaEnlaceDadosReceptora(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErro(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string quadro );
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) ;
string CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro );
int numde1s_pn(int posicao_pn, string quadro);

int tipoDeControleDeErro; 

int main () {
AplicacaoTransmissora();
}//fim do metodo main

void AplicacaoTransmissora () {
	srand(time(NULL)); //sempre que executar vai mudar os valores gerados aleatoriamente
	string mensagem;
	tipo_de_codific = -1; tipoDeControleDeErro = -1;//valor inicial pra condicao while
	//while para selecionar o tipo de codificacao
	while(tipo_de_codific != 0 && tipo_de_codific != 1 && tipo_de_codific != 2 ){
		cout << "Digite o tipo de codificacao:\n    0- Binaria\n    1- Manchester\n    2- Manchester Diferencial\n>>";
		cin >> tipo_de_codific; 
	    cin.ignore();// limpar \n do buffer
		if(tipo_de_codific != 0 && tipo_de_codific != 1 && tipo_de_codific != 2 )
			cout << "tipo de codificacao invalida!" << endl;
	}
	//while para selecionar o tipo de controle de erro
	while(tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2 && tipoDeControleDeErro != 3) {
        cout<< "Insira o tipo de controle de erro:\n    0- Bit de Paridade Par\n    1- Bit de Paridade Impar\n    2- CRC\n    3- Codigo de Hamming\n>>";
        cin >> tipoDeControleDeErro;
        cin.ignore();// limpar \n do buffer 
        if (tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2  && tipoDeControleDeErro != 3)
            cout << "tipo de codificacao invalida!" << endl;
    }
    
	//ler de um arquivo
	cout << "lendo string do arquivo txt...\n";
	mensagem = lerStringArquivo(mensagem); 
	//cout << "Digite uma mensagem:" << endl;
    //getline(cin, mensagem); // cin sozinho nao pega espacos
	//chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora (string mensagem) {
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
	CamadaEnlaceDadosTransmissora(quadro); 
}//fim do metodo CamadaDeAplicacaoTransmissora

/* **********************************************************************
*******************Controle de Erro - Transmiss�o************************
************************************************************************/


void CamadaEnlaceDadosTransmissora(string quadro ) {
	quadro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA fisico (transmissor) para um
* ponto B fisico (receptor)
*/
/* **********************************************************************
*****************Meio de Comunicacao****OBS.: PROVOCAR O ERRO!***********
************************************************************************/

void MeioDeComunicacao (string fluxoBrutoDeBits ) {
 //OBS: trabalhar com BITS e nao com BYTES!!!
	int erro, porcentagemDeErros, BitABit;
	string fluxoBrutoDeBitsPontoA , fluxoBrutoDeBitsPontoB ;

	porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%  <-------
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits; //<-------
	while (fluxoBrutoDeBitsPontoB.length() !=fluxoBrutoDeBitsPontoA.length()) {
		BitABit = fluxoBrutoDeBitsPontoB.length();
		erro = 1 + rand() % (100); //1 ate 100
		if (erro > porcentagemDeErros) //sempre que for maior que % n�o tem erro
		 	fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA[BitABit]; //BITS!!!   
		else //ERRO! INVERTER (usa condicao ternaria)
		 	(fluxoBrutoDeBitsPontoA[BitABit]== '0') ?
		 	fluxoBrutoDeBitsPontoB += '1'  :
		 	fluxoBrutoDeBitsPontoB += '0';

	}//fim do while
	cout << "Fluxo de bits para camada fisica Receptora:" <<fluxoBrutoDeBitsPontoB << endl;
    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeTransmissao

void CamadaFisicaReceptora (string quadro) {
	int tipoDeDecodificacao = tipo_de_codific; //alterar de acordo o teste
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
//chama proxima camada - camada de enlace
	CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

/* **********************************************************************
*******************Controle de Erro - Transmissao************************
************************************************************************/


string CamadaEnlaceDadosTransmissoraControleDeErro (string quadro ) {
	switch (tipoDeControleDeErro) {
	case 0 : //bit de paridade par
	quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
	break;
	case 1 : //bit de paridade impar
	quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
	break;
	case 2 : //CRC
	quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
	case 3 : //codigo de Hamming
	quadro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (quadro);
	break;
	}//fim do switch/case
	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Transmissao************************
************************************************************************/

string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro ) {
	int count = 0;
	char bitParidade;
	 
	for(int i = 0; i < quadro.size(); i++){    //Caminha pelo quadro
		 if (quadro[i] == '1'){
			 count++;                           //Conta o número de 1s
		 }
	}
	((count % 2) != 0) ? quadro += '1' : quadro += '0';    //Se o número de 1s for par, o bit de paridade é 1, se não for par o bit de paridade é 0
	
	cout << "Quadro por bit de paridade par:\n" << quadro << endl;
	
	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro){
	int count = 0;
	 
	for(int i = 0; i < quadro.size(); i++){
		 if (quadro[i] == '1'){
			 count++;
		 }
	}
	((count % 2) != 0) ? quadro += '0' : quadro += '1'; 
	
	cout << "Quadro por bit de paridade impar:\n" << quadro << endl;
	
	return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

string CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro ) {
    string gerador = "00000100110000010001110110110111";        //0x 04 C1 1D B7
    string geradorEfetivo;
    int geradorPos = gerador.size() - quadro.size();

    for(int i = 0; i < quadro.size() ; i++){
        geradorEfetivo += gerador[geradorPos];
        geradorPos++;
    }
    cout << "Gerador Efetivo:" << geradorEfetivo << endl;

    //return quadro;
    
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

string CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo
 	
	//return quadro;
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming


/* **********************************************************************
*******************Controle de Erro - Recepcao***************************
************************************************************************/

void CamadaEnlaceDadosReceptora(string quadro) {
	 quadro = CamadaEnlaceDadosReceptoraControleDeErro(quadro);
	 //chama proxima camada
	 CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

/* **********************************************************************
*******************Controle de Erro - Recep��o***************************
************************************************************************/

string CamadaEnlaceDadosReceptoraControleDeErro(string quadro) {
	 switch (tipoDeControleDeErro) {
	 case 0 : //bit de paridade par
	 quadro = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
	 break;
	 case 1 : //bit de paridade impar
	 quadro = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(quadro);
	 break;
	 case 2 : //CRC
	 quadro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
	 case 3 : //codigo de hamming
	 quadro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
	 break;
	 }//fim do switch/case
	 return quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Recep��o***************************
************************************************************************/


string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string quadro ) {
    int count = 0, Par;

    for(int bitPos = 0; bitPos < quadro.size(); bitPos++){
        if(quadro[bitPos] == '1'){
            count++;
        }
    }

    ((count % 2) == 0) ? Par = 1 : Par = 0;
    if (Par != 1) {
        cout << "Foi detectado um erro!!!" << endl;
        exit(1);
    }
    //tira o ultimo bit de paridade
	quadro = quadro.substr(0,quadro.size()-1);
    return quadro;

}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string quadro) {
    int count = 0, Impar;

    for(int bitPos = 0; bitPos < quadro.size(); bitPos++){
        if(quadro[bitPos] == '1'){
            count++;
        }
    }

    ((count % 2) == 0) ? Impar = 0 : Impar = 1;
    if (Impar != 1) {
        cout << "Foi detectado um erro!!!" << endl;
        exit(1);
    }
    //tira o ultimo bit de paridade
    quadro = quadro.substr(0,quadro.size()-1);
    return quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
string CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
 //usar polinomio CRC-32(IEEE 802)
 	//return quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
string CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
 	//return quadro;
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming

/* **********************************************************************
*******************Funcao para CodigoDeHamming***************************
************************************************************************/

//funcao retorna numero de 1s de um "Pn" (p1,p2,p4,p8,p16...) 
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

