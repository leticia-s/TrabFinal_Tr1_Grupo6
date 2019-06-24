/*************************************************************
* 		****----Simulador da Camada Enlace - TR1 ------****
Grupo 6:
	(Supervisora) Leticia de Souza Soares, 15/0015178
	Thiaggo Ferreira Bispo de Souza, 17/0157024
	David Potolski Lafeta, 15/0122969 
	Filipi Teles da Silva, 12/0117754
	Christian Braga de Almeida Pires, 12/0028379
*********************************************************** */
#include "SimuladorCamadaFisica.cpp" // inclusao das funcoes da camada fisica
#include <math.h>					 //necessaria para usar as funcoes matematicas pow, ceil, log
#include <time.h>					 //para srand
 //declaracao de funcoes   --- Nao e para fazer o de Enquadramento
/* indice de funcoes desse arquivo "SimuladorCamadaEnlace.cpp"
   OBS: todas funcoes do arquivo da camada fisica que foram alteradas para chamar camada de enlace estao neste arquivo*/
void AplicacaoTransmissora (); // alterado para add enlace
void CamadaDeAplicacaoTransmissora (string mensagem);  //alterado chamar a camada de enlace transmissora
//void MeioDeComunicacao (string fluxoBrutoDeBits ); alterado para add porcentagens, ja declado arquivo fisica
void CamadaFisicaReceptora (string quadro); // alterado para chamar a camada de enlace enlace

void CamadaEnlaceDadosTransmissora(string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErro(string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErroCRC(string quadro);
string CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(string quadro);
void MeioDeComunicacao(string fluxoBrutoDeBits);
void CamadaEnlaceDadosReceptora(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErro(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroCRC(string quadro);
string CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(string quadro);
int numde1s_pn(int posicao_pn, string quadro);

int tipoDeControleDeErro;

int main()
{
	AplicacaoTransmissora();
} //fim do metodo main

void AplicacaoTransmissora()
{
	srand(time(NULL)); //sempre que executar vai mudar os valores gerados aleatoriamente
	string mensagem;
	tipo_de_codific = -1;
	tipoDeControleDeErro = -1; //valor inicial pra condicao while
	//while para selecionar o tipo de codificacao
	while (tipo_de_codific != 0 && tipo_de_codific != 1 && tipo_de_codific != 2)
	{
		cout << "Digite o tipo de codificacao:\n    0- Binaria\n    1- Manchester\n    2- Manchester Diferencial\n>>";
		cin >> tipo_de_codific;
		cin.ignore(); // limpar \n do buffer
		if (tipo_de_codific != 0 && tipo_de_codific != 1 && tipo_de_codific != 2)
			cout << "tipo de codificacao invalida!" << endl;
	}
	//while para selecionar o tipo de controle de erro
	while (tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2 && tipoDeControleDeErro != 3)
	{
		cout << "Insira o tipo de controle de erro:\n    0- Bit de Paridade Par\n    1- Bit de Paridade Impar\n    2- CRC\n    3- Codigo de Hamming\n>>";
		cin >> tipoDeControleDeErro;
		cin.ignore(); // limpar \n do buffer
		if (tipoDeControleDeErro != 0 && tipoDeControleDeErro != 1 && tipoDeControleDeErro != 2 && tipoDeControleDeErro != 3)
			cout << "tipo de codificacao invalida!" << endl;
	}

	//ler de um arquivo
	cout << "lendo mensagem do arquivo 'text_string.txt'...\n";
	mensagem = lerStringArquivo(mensagem);
	//cout << "Digite uma mensagem:" << endl;
	//getline(cin, mensagem); // cin sozinho nao pega espacos
	//chama a proxima camada
	CamadaDeAplicacaoTransmissora(mensagem); //em um exemplo mais realistico, aqui seria dado um SEND do SOCKET
} //fim do metodo AplicacaoTransmissora

void CamadaDeAplicacaoTransmissora(string mensagem)
{
	string binary_output;
	int i = 0;
	//converter a mensagem para binario
	while (mensagem[i] != '\0')
	{
		bitset<8> b(mensagem.c_str()[i]); // cada caracter tem 8 bits
		binary_output += b.to_string();   //cada 8 bits(cada caracter) coloca na string
		i++;							  //atualiza posicao
	}
	string quadro = binary_output; //trabalhar com bits!!!
	//chama a proxima camada
	CamadaEnlaceDadosTransmissora(quadro);
} //fim do metodo CamadaDeAplicacaoTransmissora

/* **********************************************************************
*******************Controle de Erro - Transmissao************************
************************************************************************/

void CamadaEnlaceDadosTransmissora(string quadro)
{   
	cout << "Mensagem para fazer enlace de Dados:\n"<< quadro << endl<< endl;
	quadro = CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
} //fim do metodo CamadaEnlaceDadosTransmissora

/* Este metodo simula a transmissao da informacao no meio de
* comunicacao, passando de um pontoA fisico (transmissor) para um
* ponto B fisico (receptor)
*/
/* **********************************************************************
*****************Meio de Comunicacao****OBS.: PROVOCAR O ERRO!***********
************************************************************************/

void MeioDeComunicacao(string fluxoBrutoDeBits)
{
	//OBS: trabalhar com BITS e nao com BYTES!!!
	int erro, porcentagemDeErros, BitABit;
	string fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

	porcentagemDeErros = 0;				   //10%, 20%, 30%, 40%, ..., 100%  <-------
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits; //<-------
	while (fluxoBrutoDeBitsPontoB.length() != fluxoBrutoDeBitsPontoA.length())
	{
		BitABit = fluxoBrutoDeBitsPontoB.length();
		erro = 1 + rand() % (100);									   //1 ate 100
		if (erro > porcentagemDeErros)								   //sempre que for maior que % nao tem erro
			fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA[BitABit]; //BITS!!!
		else														   //ERRO! INVERTER (usa condicao ternaria)
			(fluxoBrutoDeBitsPontoA[BitABit] == '0') ? fluxoBrutoDeBitsPontoB += '1' : fluxoBrutoDeBitsPontoB += '0';

	} //fim do while
	cout << "\nTransferencia do fluxo de bits para receptora:\n"
		 << fluxoBrutoDeBitsPontoB << endl<< endl;
	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
} //fim do metodo MeioDeTransmissao

void CamadaFisicaReceptora(string quadro)
{
	int tipoDeDecodificacao = tipo_de_codific; //alterar de acordo o teste
	string fluxoBrutoDeBits;				   //ATENCAO: trabalhar com BITS!!!
	switch (tipoDeDecodificacao)
	{
	case 0: //codificao binaria
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
		break;
	case 1: //codificacao manchester
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
		break;
	case 2: //codificacao manchester diferencial
		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
		break;
	} //fim do switch/case
	  //chama proxima camada - camada de enlace
	CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
} //fim do metodo CamadaFisicaTransmissora

/* **********************************************************************
*******************Controle de Erro - Transmissao************************
************************************************************************/

string CamadaEnlaceDadosTransmissoraControleDeErro(string quadro)
{
	switch (tipoDeControleDeErro)
	{
	case 0: //bit de paridade par
		quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
		break;
	case 1: //bit de paridade impar
		quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(quadro);
		break;
	case 2: //CRC
		quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
		break;
	case 3: //codigo de Hamming
		quadro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
		break;
	} //fim do switch/case
	return quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

/* **********************************************************************
*******************Controle de Erro - Transmissao************************
************************************************************************/

string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(string quadro)
{
	int count = 0;
	char bitParidade;

	for (int i = 0; i < quadro.size(); i++)
	{ //Caminha pelo quadro
		if (quadro[i] == '1')
		{
			count++; //Conta o numero de 1's
		}
	}
	((count % 2) != 0) ? quadro += '1' : quadro += '0'; //Se o numero de 1s for par, o bit de paridade e 0, se nao for par o bit de paridade e 1

	cout << "Enlace Transmissora (Bit de paridade par):\n"
		 << quadro << endl;

	return quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar

string CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar(string quadro)
{
	int count = 0;

	for (int i = 0; i < quadro.size(); i++)
	{//Caminha pelo quadro
		if (quadro[i] == '1')
		{
			count++; //conta numero de 1's 
		}
	}
	((count % 2) != 0) ? quadro += '0' : quadro += '1'; //Se o numero de 1s for impar, o bit de paridade e 0, se nao for par o bit de paridade e 1

	cout << "Enlace Transmissora (Bit de paridade impar):\n"
		 << quadro << endl;

	return quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar

string CamadaEnlaceDadosTransmissoraControleDeErroCRC(string quadro)
{
	//Utilizado a parte teorica do livro do tanenbaum 5 edicao pag 132 a 134 e estrategia para o calculo de https://pt.wikipedia.org/wiki/CRC
	//Passos: 	Seja r o grau de G(x), o polinomio gerador (CRC-32), e m o numero de bits do quadro (M(x)) adicionar r zeros ao final do quadro de forma que tenha m+r bits para que o quadro sempre seja divisivel pelo gerador
	//			Dividir as strings correspondentes aos indices dos polinomios usando operacoes modulo 2 (mesma coisa que o XOR)
	//			Adicionar o resto, que sempre tem r ou menos bits, na string do quadro original
	//			retornar o quadro			

 
	string geradorcrc = "100000100110000010001110110110111"; //usar polinomio CRC-32(IEEE 802)
	string quadroresultado = quadro; //quadro usado para armazenar o resultado de cada iteracao
	string quadroresto; //quadro usado para armazenar o resto da divisao polinomial
	int contador, indice, i, j, k;	//i, j, k sao indices de loop, os outros dois sao explicados abaixo

	//Loop para adicionar zeros ao final do quadro
	for (i = 0; i < geradorcrc.size()-1; i++) {
		quadroresultado += '0';
	}

	//Loop para adicionar zeros ao final do quadro
	for (i = 0; i < geradorcrc.size()-1; i++) {
		quadro += '0';
	}
	

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
	
	cout << "Resto (CRC): " << quadroresto << endl;
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
	cout << "Enlace Transmissora (CRC): \n" << quadro << endl << endl;

	return quadro;

} //fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC

string CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(string quadro)
{
	//implementacao do algoritmo
	int numberOf1, i, tamanhoQuadroFinal, numeroBitsParidade;
	int indiceP = 0;
	int posicaoQuadro = 0;
	string quadroFinal;
	//numero de bis de paridade
	numeroBitsParidade = ceil(log2(quadro.size() + 1));
	//numero total de bits = bits do quadro + bits de paridade
	tamanhoQuadroFinal = quadro.size() + numeroBitsParidade;
	//
	for (i = 1; i <= tamanhoQuadroFinal; i++)
	{
		//se for a posicao de bit de paridade coloca 0 no quadroFinal, caso contrario coloca o bit do quadro
		if (i == pow(2, indiceP)) //2 elevado ao indice
		{
			//zera a posicao com os bits de paridade, pois ainda vao ser calculados
			quadroFinal += '0';
			indiceP++;
		}
		else
		{
			quadroFinal += quadro[posicaoQuadro];
			posicaoQuadro++;
		}
	}

	indiceP = 0; //atualiza indice dos pn (bits de paridade)
	cout << "Bits de paridade da mensagem:" << " \n";
	//pega cada posicao Pn(paridade) muda para 1 se for impar
	while (indiceP < numeroBitsParidade)
	{
		numberOf1 = numde1s_pn(pow(2, indiceP), quadroFinal); //funcao retorna numero de 1s de uma posicao Pn
		//se for impar muda para 1, pois todos pn estao com zeros
		if ((numberOf1 % 2) != 0) //usamos paridade par
			quadroFinal[pow(2, indiceP) - 1] = '1';
		//imprimi cada bit de paridade
		cout << "P" << pow(2, indiceP) << ": " << quadroFinal[pow(2, indiceP) - 1]<< " | ";
		
		indiceP++; // atualiza proximo pn -> (bit de paridade)
	}cout <<endl;
	cout << "Enlace Transmissora (Codigo De Hamming):" << " \n"
		 << quadroFinal << endl << endl;
	return quadroFinal;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming

/* **********************************************************************
*******************Controle de Erro - Recepcao***************************
************************************************************************/

void CamadaEnlaceDadosReceptora(string quadro)
{
	quadro = CamadaEnlaceDadosReceptoraControleDeErro(quadro);
	//chama proxima camada
	CamadaDeAplicacaoReceptora(quadro);
} //fim do metodo CamadaEnlaceDadosReceptora

/* **********************************************************************
*******************Controle de Erro - Recepcao***************************
************************************************************************/

string CamadaEnlaceDadosReceptoraControleDeErro(string quadro)
{
	switch (tipoDeControleDeErro)
	{
	case 0: //bit de paridade par
		quadro = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
		break;
	case 1: //bit de paridade impar
		quadro = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(quadro);
		break;
	case 2: //CRC
		quadro = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
		break;
	case 3: //codigo de hamming
		quadro = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
		break;
	} //fim do switch/case
	return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErro

/* **********************************************************************
*******************Controle de Erro - Recepcao***************************
************************************************************************/

string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(string quadro)
{
	int count = 0, Par;

	for (int bitPos = 0; bitPos < quadro.size(); bitPos++)
	{
		if (quadro[bitPos] == '1')
		{
			count++; //conta numero de 1's
		}
	}
	//verifica a paridade
	((count % 2) == 0) ? Par = 1 : Par = 0;
	if (Par != 1) 
	{
		cout << "Foi detectado um erro!!!" << endl;
		exit(1);
	}
	//tira o ultimo bit de paridade
	quadro = quadro.substr(0, quadro.size() - 1);
	cout << "Mensagem(quadro) apos enlace Receptora (Bit De Paridade Par): \n" << quadro << endl;
	return quadro;

} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
string CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar(string quadro)
{
	int count = 0, Impar;

	for (int bitPos = 0; bitPos < quadro.size(); bitPos++)
	{
		if (quadro[bitPos] == '1')
		{
			count++; //conta numero de 1's
		}
	}
    //verifica a paridade
	((count % 2) == 0) ? Impar = 0 : Impar = 1;
	if (Impar != 1)
	{
		cout << "Foi detectado um erro!!!" << endl;
		exit(1);
	}
	//tira o ultimo bit de paridade
	quadro = quadro.substr(0, quadro.size() - 1);
	cout << "Mensagem(quadro) apos enlace Receptora (Bit De Paridade Impar) \n" << quadro << endl;
	return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
string CamadaEnlaceDadosReceptoraControleDeErroCRC(string quadro)
{
	//Utilizado a parte teorica do livro do tanenbaum 5 edicao pag 132 a 134 e estrategia para o calculo de https://pt.wikipedia.org/wiki/CRC
	//Passos: 	Seja r o grau de G(x), o polinomio gerador (CRC-32), e m o numero de bits do quadro (M(x)) adicionar r zeros ao final do quadro de forma que tenha m+r bits para que o quadro sempre seja divisivel pelo gerador
	//			Dividir as strings correspondentes aos indices dos polinomios usando operacoes modulo 2 (mesma coisa que o XOR)
	//			Adicionar o resto, que sempre tem r ou menos bits, na string do quadro original
	//			retornar o quadro			


	string geradorcrc = "100000100110000010001110110110111"; //usar polinomio CRC-32(IEEE 802)
	string quadroresultado = quadro; //quadro usado para armazenar o resultado de cada iteracao
	string quadroresto; //quadro usado para armazenar o resto da divisao polinomial
	int contador, indice, i, j, k;	//i, j, k sao indices de loop, os outros dois sao explicados abaixo

	//Loop para adicionar zeros ao final do quadro
	for (i = 0; i < geradorcrc.size()-1; i++) {
		quadroresultado += '0';
	}
	

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
	//Remover os comentarios abaixo para testar a recepcao do quadro
	
	if(quadroresto[0] == '\0') {
		cout << "Resto zero, quadro sem erros" << endl;
	}
	else if (quadroresto[0] == '0') {
		for (i=0; quadroresto[i] != '\0'; i++) {
			if (quadroresto[i] != '0') {
				cout << "Resto diferente de zero, quadro com erros" << endl << endl;
				exit(1);
			}
		}
	}
	else {
		cout << "Resto diferente de zero, quadro com erros" << endl << endl;
		exit(1);
	} 
	cout << "Resto (CRC): " << quadroresto << endl << endl;

	int tamanhoquadro = quadro.size();

	quadro[tamanhoquadro - (geradorcrc.size()-1)] = '\0';
	
    quadro = quadro.substr(0, tamanhoquadro - (geradorcrc.size()-1));
    
    cout << "Mensagem(quadro) apos enlace Receptora (CRC) \n" << quadro << endl;
    
	return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
string CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(string quadro)
{
	int BitsParidade = 0, i = 0, numberOf1 = 0;
	bool Erro = false;
	string QuadroFinal, QuadroP;
	cout << "Bits de paridade da mensagem recebida:"<< "\n";
	
	for (i = 0; i < quadro.size(); i++)
	{
		//se for um bit de paridade de paridade - //2 elevado ao bitParidade
		if (i == pow(2, BitsParidade) - 1){ 
			cout << "P" << i + 1 << ": " << quadro[i] << " | ";
			QuadroP += quadro[i]; //quadro com bits de paridade
			BitsParidade++;  //quantidade de bits de paridade
		}
		else{
			QuadroFinal += quadro[i]; // adiciona somente o quadro sem os bits de paridade
		}
	
	}	cout << endl;
    //verificar cada paridade para ver se tem erro
	for (i = 0; i < BitsParidade; i++)
	{
		numberOf1 = numde1s_pn(pow(2, i), quadro); //funcao retorna numero de 1s de uma posicao Pn
		// se o numero de 1s de Pn + bit de paridade Pn for igual a 1, ou seja for impar, entao tem erro
		if ((numberOf1 + QuadroP[i]) % 2 == 1) // se a (paridade Pn + bit de paridade Pn) for 
		{
			cout << "Mensagem com erro!!!" << endl;
			exit(1); //encerra programa
		}
	}
	cout << "Mensagem(quadro) apos enlace Receptora (Hamming):\n" << QuadroFinal << endl;
	return QuadroFinal;
	
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming

/* **********************************************************************
*******************Funcao para CodigoDeHamming***************************
************************************************************************/

//funcao retorna numero de 1s de um "Pn" (p1,p2,p4,p8,p16...)
int numde1s_pn(int posicao_pn, string quadro)
{
	int cont, pos, pula_prox_conjunto_pn;
	pula_prox_conjunto_pn = posicao_pn; //atualiza primeiro conjunto n
	while (pula_prox_conjunto_pn <= quadro.size())
	{
		pos = pula_prox_conjunto_pn; //atualiza onde inicia cada conjunto n-n
		//conta numero de uns do conjunto n
		for (int i = 0; i < posicao_pn; i++)
		{
			//nao pode passa do tamanho da string e nao pode conta o bit do Pn
			if (quadro[pos - 1] == '1' && pos <= quadro.size() && pos != posicao_pn)
			{
				cont++;
			}
			pos++; //atualiza proximo bit
		}
		pula_prox_conjunto_pn += 2 * posicao_pn;
	}
	return cont;
};
