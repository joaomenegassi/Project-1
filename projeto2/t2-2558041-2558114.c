/*
===========================================
|            JOÃO MENEGASSI               |
|            MURILO BONTORIN              |
===========================================
*/

#include"trabalho2.h"
#include"wavfile.h"

/// FUNÇÃO 1
void mudaGanho (double* dados, int n_amostras, double ganho)
{
    int i;

    for(i = 0; i < n_amostras ; i++)
    {
        //Cada elemento na posição i do vetor será multiplicado por ganho.
        dados[i] = dados[i] * ganho;

    }
}

/// FUNÇÃO 2
void misturaDados (double* dados1, double* dados2, double* saida, int n_amostras)
{
    int i;

    for(i=0; i<n_amostras; i++)
    {
        //Em cada posição i do vetor de saída será recebido a soma dos vetores dados1 e dados2 na posição i.
        saida[i] = dados1[i] + dados2[i];
    }
}

/// FUNÇÃO 3
void inverteSinal (double* dados, int n_amostras)
{
    int i;
    double aux;
    int troca = n_amostras - 1;

    // A condição deve ser n_amostras/2 pois se for apenas n_amostras o vetor será invertido e desinvertido.
    for(i=0; i<n_amostras/2; i++)
    {
        // Pega o primeiro valor do vetor e troca pelo último e vice-versa, em seguida o segundo pelo penúltimo e assim por diante.
        aux = dados[i];
        dados[i] = dados[troca];
        dados[troca] = aux;
        troca--;
    }
}

/// FUNÇÃO 4
void atrasaSinal (double* dados, int n_amostras, int atraso)
{
    int i,aux ;

    // Atraso negativo.
    // Percore o vetor de frente para trás, já que os primeiros valores podem ser eliminados.
    if (atraso < 0)
    {
        atraso *= -1;

        // Deslocamos os valores para a esquerda.
        for (i = 0; i < n_amostras - atraso ; i++)
        {
            dados[i] = dados[i + atraso];
        }
        // Preenchemos as posições finais com 0.
        for(i=0; i<atraso; i++)
        {
            dados[n_amostras-i-1]=0;
        }
    }

    // Atraso positivo.
    // Percorre o vetor de trás para frente, já que os últimos valores podem ser eliminados.
    else
    {
        // Deslocamos os valores para a direita..
        for (i = n_amostras - 1; i >= atraso; i--)
        {
            dados[i] = dados[i - atraso];
        }

        // Preenchemos as posições do atraso com 0.
        for(i=0; i<atraso; i++)
        {
            dados[i]=0;
        }
    }
}

/// FUNÇÃO 5
void filtroDaMedia (double* dados, int n_amostras, int largura)
{
    int i,j;
    double *vetor_auxiliar,soma=0;

    // Vetor auxiliar para que a média dos valores ocorra corretamente.
    vetor_auxiliar = (double*) malloc (n_amostras*sizeof(double));


    // Verifica se a largura está dentro dos limites.
    if(largura%2==1 && largura >= 3 && largura <= n_amostras)
    {
        // "i" começa no primeiro valor cuja largura não ultrapassa os limites permitidos pelo vetor, e termina no último dessa mesma condição.
        for(i=(largura-1)/2 ; i<n_amostras-(largura-1)/2; i++)
        {
            // Percorre os valores requitados pela largura e soma-os numa variável.
            for(j=i-(largura-1)/2; j <= i+(largura-1)/2; j++)
            {
                soma += (dados[j]);
            }

            // Tira a média que essa posição deve receber.
            vetor_auxiliar[i]=soma/largura;
            soma=0;
        }
        for(i=0; i<n_amostras; i++)
            dados[i] = vetor_auxiliar[i];

    }
    free(vetor_auxiliar);
}


/// FUNÇÃO EXTRA
void ecos (double* dados, int n_amostras, unsigned short n_repeticoes, int atraso, unsigned short abafamento, double decaimento)
{
    int i;
    double *vetor_auxiliar;

    // Um vetor necessário para que seja possível realizar as operações.
    vetor_auxiliar = (double*) malloc (n_amostras*sizeof(double));

    for(i=0; i<n_amostras; i++)
        vetor_auxiliar[i] = dados[i];

    for(i=0; i<n_repeticoes; i++)
    {
        // Atrasa o vetor auxiliar a cada iteração para dar o efeito do sinal "indo e vindo"
        atrasaSinal(vetor_auxiliar,n_amostras,atraso);

        // As duas próximas operaçõses dão um efeito do som se deslocando e consequentemente perdendo a qualidade.
        // Faz o vetor auxiliar ficar com um volume mais baixo a cada iteração.
        mudaGanho(vetor_auxiliar,n_amostras,decaimento);

        // Faz o vetor auxiliar ficar mais abafado a cada iteração.
        filtroDaMedia(vetor_auxiliar,n_amostras,abafamento);

        // Junta o vetor auxiliar, já modificado, com o vetor "dados" original.
        misturaDados(dados,vetor_auxiliar,dados,n_amostras);
    }

    free(vetor_auxiliar);
}
