/*============================================================================*/
/* CSF13 - 2023-1 - TRABALHO 1                                                */
/*----------------------------------------------------------------------------*/
/* Joao Guilherme Menegassi Silva - joaosilva.2005@alunos.utfpr.edu.br        */
/*============================================================================*/
/* Implementação das funções do projeto. */
/*============================================================================*/

#include"trabalho1.h"

//Declaração da função codifica.
void codificaStreamImagem (int n_bits);

//Funções Auxiliares.
unsigned int pegaProximoPixel ();
void enviaByteRBD (unsigned char byte);

void codificaStreamImagem (int n_bits)
{

    // Declaração das variaveis
    int i;
    int contador = 8 - n_bits;
    unsigned int byte;
    unsigned char aux = 0;

    // Armazena o primeiro byte;
    byte = pegaProximoPixel();

    // Loop até o ultimo pixel.
    while(byte != 0xFFFFFFFF)
    {

        // Loop para pegar apenas os n_bits mais significativos de cada byte e somar em aux.
        for(i = 0; i < 8 / n_bits ; i++)
        {
            byte =  byte >> 8 - n_bits;
            byte = byte << contador;

            //soma os n_bits significativos.
            aux = byte | aux;

            //Diminui a variável "contador" em n_bits para que a proxima soma seja correta.
            contador -= n_bits;

            byte = pegaProximoPixel();

        }
        // Envia a soma dos bits mais significativos de cada byte.
        enviaByteRBD(aux);

        //Reseta o contador e o aux para que não ocorra problemas na próxima soma.
        aux = 0;
        contador = 8 - n_bits;

    }
}

//Declaração da função decodifica.
void decodificaStreamRBD (int n_bits, int preenche);

//Funções Auxiliares.
unsigned int pegaProximoByteRBD ();
void enviaPixel (unsigned char pixel);

void decodificaStreamRBD (int n_bits, int preenche)
{
    // Declaração das variaveis.
    int byte, aux;
    int i, moveBits = 8 - n_bits;

    // Armazena o primeiro byte.
    byte = pegaProximoByteRBD();

    while (byte != 0xFFFFFFFF)
    {
        /* O loop irá rodar até o 0, pois iremos usar o 0 na conta, vendo que no ultimo conjunto de n_bits
        o byte não deveria mover nenhuma casa para a direita, usei a variável i para essa função.*/
        for (i = 8 / n_bits - 1; i >= 0 ; i--)
        {
            // Move para a direita até i = 0;
            aux = byte >> n_bits * i;
            aux = aux << moveBits;
            enviaPixel(aux);
        }
        byte = pegaProximoByteRBD();
    }
}