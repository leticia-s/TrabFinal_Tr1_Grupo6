/*************************************************************
* 		****----CAMADA ENLACE------****
Grupo 6:
	(Supervisora) Leticia de Souza Soares, 15/0015178
	Thiaggo Ferreira Bispo de Souza, 17/0157024
	David Potolski Lafeta, 15/0122969 
	Filipi Teles da Silva, 12/0117754
	Christian Braga de Almeida Pires, 12/0028379
*********************************************************** */
 #include "SimuladorCamadaFisica.cpp"  // inclusao das funcoes da camada fisica
 
 //declaracao de funcoes   --- Nao e para fazer o de Enquadramento

void CamadaEnlaceDadosTransmissora (string quadro);
void CamadaEnlaceDadosTransmissoraControleDeErro (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro);
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro );
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro );
void MeioDeComunicacao (string fluxoBrutoDeBits );
void CamadaEnlaceDadosReceptora (string quadro);
void CamadaEnlaceDadosReceptoraControleDeErro (string quadro );
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string quadro );
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar (string quadro );
void CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) ;
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro );
 

/* **********************************************************************
*******************Controle de Erro - Transmissão************************
************************************************************************/


void CamadaEnlaceDadosTransmissora (string quadro ) {
	CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
	//chama proxima camada
	CamadaFisicaTransmissora(quadro);
}//fim do metodo CamadaEnlaceDadosTransmissora


/* **********************************************************************
*******************Controle de Erro - Transmissão************************
************************************************************************/


void CamadaEnlaceDadosTransmissoraControleDeErro (string quadro ) {
	int tipoDeControleDeErro = 0; //alterar de acordo com o teste
	switch (tipoDeControleDeErro) {
	case 0 : //bit de paridade par
	//codigo
	break;
	case 1 : //bit de paridade impar
	//codigo
	break;
	case 2 : //CRC
	//codigo
	case 3 : //codigo de Hamming
	//codigo
	break;
	}//fim do switch/case
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Transmissão************************
************************************************************************/

void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar (string quadro ) {
 //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadePar
void CamadaEnlaceDadosTransmissoraControleDeErroBitParidadeImpar (string quadro)
{
 //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroBitParidadeImpar
void CamadaEnlaceDadosTransmissoraControleDeErroCRC (string quadro ) {
 //implementacao do algoritmo
 //usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosTransmissoraControledeErroCRC
void CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo
}//fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCodigoDehamming


/* **********************************************************************
*****************Meio de Comunicação****OBS.: PROVOCAR O ERRO!***********
************************************************************************/

void MeioDeComunicacao (string fluxoBrutoDeBits ) {
 //OBS: trabalhar com BITS e nao com BYTES!!!
	int erro, porcentagemDeErros;
	string fluxoBrutoDeBitsPontoA , fluxoBrutoDeBitsPontoB ;
	porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%  <-------
	fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits; //<-------
	while (fluxoBrutoDeBitsPontoB.lenght!=fluxoBrutoDeBitsPontoA) {
		if ((rand()%100)== ... ) //fazer a probabilidade do erro <-------
		 	fluxoBrutoBitsPontoB += fluxoBrutoBitsPontoA; //BITS!!!   
		else //ERRO! INVERTER (usa condicao ternaria)
		 	fluxoBrutoBitsPontoB==0) ?
		 	fluxoBrutoBitsPontoA=fluxoBrutoBitsPontoB++ :
		 	fluxoBrutoBitsPontoA=fluxoBrutoBitsPontoB--;
	}//fim do while
}//fim do metodo MeioDeTransmissao

/* **********************************************************************
*******************Controle de Erro - Recepção***************************
************************************************************************/

void CamadaEnlaceDadosReceptora (string quadro) {
	 CamadaDeEnlaceTransmissoraControleDeErro(quadro);
	 //chama proxima camada
	 CamadaDeAplicacaoReceptora(quadro);
}//fim do metodo CamadaEnlaceDadosReceptora

/* **********************************************************************
*******************Controle de Erro - Recepção***************************
************************************************************************/

void CamadaEnlaceDadosReceptoraControleDeErro (string quadro ) {
	 int tipoDeControleDeErro = 0; //alterar de acordo com o teste
	 switch (tipoDeControleDeErro) {
	 case 0 : //bit de paridade par
	 //codigo
	 break;
	 case 1 : //bit de paridade impar
	 //codigo
	 break;
	 case 2 : //CRC
	 //codigo
	 case 3 : //codigo de hamming
	 //codigo
	 break;
	 }//fim do switch/case
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErro


/* **********************************************************************
*******************Controle de Erro - Recepção***************************
************************************************************************/


void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar
void CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadeImpar
void CamadaEnlaceDadosReceptoraControleDeErroCRC (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
 //usar polinomio CRC-32(IEEE 802)
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC
void CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming (string quadro ) {
 //implementacao do algoritmo para VERIFICAR SE HOUVE ERRO
}//fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming
