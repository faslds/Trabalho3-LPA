#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define R 100

/* A struct linha armazenara as linhas da matriz
e representarão linhas encadeadas "horizontais" */
struct linha
{
	int numero;
	int coluna;
	struct linha *prox;
};

/* A struct coluna sera a lista base, sera uma lista encadeada 
"vertical" para apontar para as listas "horizontais" */
struct coluna
{
	int linha;
	struct linha *line;
	struct coluna *prox;
};

/* A funcao para remover numeros funciona como uma remocao de 
um item de uma lista encadeada. O antecessor do item a ser removido
passa a apontar para seu sucessor, e a memoria do item removido
eh liberada. */
int removenum(struct coluna *raiz, int m, int n)
{
	struct linha *a = NULL;
	struct linha *b = NULL;
	struct linha *c = NULL;
	struct coluna *pont = raiz;
	while(pont->linha != m)//chega na linha desejada
	{
		pont = pont->prox;
	}
	a = pont->line;
	b = pont;	
	if(a == NULL)//se nada existir nessa posicao, sai da funcao
	{
		return 0;
	}
	else
	{
		while(a->coluna > n)//chega no numero desejado
		{
			if(a->prox != NULL)
			{
				b = a;
				a = a->prox;
			}
			else //caso o numero nao exista
			{
				return 0;
			}
		}
		if(a->coluna == n) //remove o numero
		{
			b->prox = a->prox;
			printf("O numero %d foi removido com sucesso!", a->numero);
			free(a);//libera a memoria
			return 1;
		}
		else //se o numero nao existir
		{
			return 0;
		}
	}
}

/* A funcao de insercao funciona como a insecao em uma lista
encadeada. Ela mantem a ordenacao de acordo com o numero da coluna
de cada item. Isso facilita o processo da resolucao dos demais
itens do trabalho. */
void insert(int k, int m, int n, struct coluna *raiz)
{
	struct linha *a = NULL;
	struct linha *b = NULL;
	struct coluna *pont = raiz;
	int i = 0; 
	while(pont->linha != m) // chega na linha desejada
	{
		pont = pont->prox;
	}
	if (pont->line == NULL) //se nao houver nada na linha, ja aloca o espaco para o novo item
	{
		a = (struct linha*) malloc(sizeof(struct linha)); //aloca a memoria
		a->numero = k;
		a->coluna = n; 
		a->prox = NULL; // aterra o ponteiro 
		pont->line = a;
	}
	else //caso ja haja algo na linha
	{
		a = pont->line;
		if (a->coluna > n) //matem a ordenacao
		{
			b = (struct linha*) malloc(sizeof(struct linha));
			b->numero = k;
			b->coluna = n;
			b->prox = a;
			pont->line = b;
		}
		else
		{
			while(a->prox != NULL && a->coluna < n) //chega na posicao desejada
			{
				a = a->prox;
			}
			b = (struct linha*) malloc(sizeof(struct linha));
			b->numero = k;
			b->coluna = n;
			b->prox = a->prox; //mantem a ordenacao
			a->prox = b;
		}
	}
}

/* A funcao de consulta funciona de maneira simples, ela chega ate a linha
desejada, depois checa se a coluna existe ou nao. Como as listas das linhas
estao ordenadas, basta percorrer ate que o numero da coluna seja maior do que
o numero da coluna do numero que se deseja achar. */
int consulta(struct coluna *raiz, int m, int n)
{
	struct coluna *pont = raiz;
	struct linha *a = NULL;
	while(pont->linha != m) //chega na linha desejada
	{
		pont = pont->prox;
	}
	if(pont->line == NULL) 
	{
		return 0; //nao existe o numero
	}
	a = pont->line;
	while(a->coluna < n) //procura a coluna desejada
	{
		a = a->prox;
	}
	if(a->coluna == n)
	{
		return(a->numero); //acha o numero e retorna ele
	}
	else if(a->coluna != n)
	{
		return 0; //nao existe o numero
	}
}

/* A soma de uma determinada linha eh feita de maneira simples, basta 
chegar na linha desejada e somar cada um de seus elementos. Como os 
elementos nao existentes sao zero, eles nao vao influenciar na soma. */
int sumlinha(struct coluna *raiz, int k)
{
	struct coluna *pont = raiz;
	struct linha *a = NULL;
	int soma = 0;
	while(pont->linha != k) //chega na linha desejada
	{
		pont = pont->prox;
	}
	if (pont->line == NULL)
	{
		return 0;//se nao existe nada na linha, sua soma eh zero
	}
	a = pont->line;
	while(a != NULL) //percorre a linha somando seus elementos
	{
		soma = soma + a->numero;
		a = a->prox;
	}
	return (soma); //retorna o valor da soma
}

/* A funcao para somar os valores de uma coluna funciona de maneira 
um pouco mais complexa. Ela percorre cada linha da matriz para achar 
o elemento da coluna desejada. Ao encontra-lo, ela faz a soma e parte 
para a proxima linha, e faz a busca e a soma novamente. */
int sumcoluna(struct coluna *raiz, int k)
{
	struct coluna *pont = raiz;
	struct linha *a = pont->line;
	int soma = 0;
	while (pont != NULL)//percorre todas as linhas (da lista base) ate chegar em NULL (fim da lista) 
	{
		a = pont->line;
		if(a != NULL)//se a linha nao for nula, procura a coluna desejada
		{ 
			while(a->coluna < k && a != NULL)//percorre o item desejado 
			{
				a = a->prox;
			}
			if(a->coluna == k) //caso seja o item desejado, faz a soma
			{
				soma = soma + a->numero;
			}
		}
		pont = pont->prox;
	}
	return (soma); //retorna o valor da soma
}

/* Essa funcao faz parte da solucao por Gauss-Seidel. Ela testa se a funcao
eh realmente diagonal dominante, para que o programa pare caso a matriz nao seja, 
pois nesse caso a solucao por Gauss-Seidel nao funcionara. */
int check(struct coluna *raiz, int n)
{
	struct coluna *pont = raiz;
	struct linha *a = NULL;
	int c = 0;
	while (pont != NULL)
	{
		a = pont->line;
		while(a != NULL) //percorre a linha toda
		{
			if(pont->linha == a->coluna)//se for um elemento da diagonal, subtrai seu valor absoluto
			{
				c = c - abs(a->numero);
			}
			else if(pont->linha != a->coluna && a->coluna != n-1) //para outros elementos, soma o valor absoluto
			{
				c = c + abs(a->numero);
			}
			a = a->prox;
		}
		if(c > 0) //nesse caso, se c for positivo em qualquer uma das linhas, a matriz nao eh diagonal dominante
		{
			printf("\nA matriz nao eh diagonal dominante, entao esse metodo de solucao nao ira convergir para o resultado correto.\n");
			return 0;
		}
		pont = pont->prox;
	}
	if(c <= 0)
	{
		return(1);
	}
}

/* A funcao calc calcula o valor de uma das variaveis, isolando ela e obtendo
o valor das demais variaveis a partir do vetor vet, usado para armazena-las.
Esta funcao retorna o valor obtido para a variavel. Ao chama-la varias vezes, 
atualiza-se o conteudo do vetor com as novas variaveis obtidas. */
float calc(struct coluna *raiz, float *vet, int k, int m, int n)
{
	float c = consulta(raiz, k, n-1); /* A funcao consulta, ja citada anteriormente, 
	ira retornar o valor de um item numa dada posicao. Ela pode ser usada para facilitar
	a realizacao dos calculos nessa funcao calc. */
	float b = 0;
	int i;
	struct linha *a = raiz->line;
	for(i = 0; i<n -1; i++) //percorre o vetor vet que contem as variaveis
	{
		if(a->coluna != k && i == a->coluna)//faz a multiplicacao de cada elemento da matriz pelas variaveis de vet 
		{
			b = b + (a->numero)*vet[i];
		}
		a = a->prox; 
	}
	b = c - b; 
	b = b/consulta(raiz, k, k);// calcula o valor final de b para retornar
	return(b);
}

/* A funcao gauss realiza o algoritmo do metodo de solucao de Gauss-Seidel. Um vetor vet de floats
para as variaveis eh criado e zerado. Em cada linha da matriz se isola uma das variaveis e eh feito 
o calculo do seu novo valor. O processo eh realizado "R" vezes. Quanto mais vezes for realizado, mais 
os valores convergem para o resultado correto. O valor de R pode ser alterado no inicio do programa 
usando o #define. */
void gauss(struct coluna *raiz, int m, int n)
{
	int i, j;
	float vet[m]; //declarado o vetor
	struct coluna *pont = raiz;
	for(i = 0; i < m; i++)// zera o vetor
	{
		vet[i] = 0;
	}
	for(j = 0; j <= R; j++) //repete o processo R vezes
	{
		pont = raiz;
		for(i = 0; i < m; i++)// faz o processo para o vetor inteiro, para todas as linhas da matriz
		{
			vet[i] = calc(pont, vet, i, m, n); //chama a funcao calc para realizar as contas
			pont = pont->prox; //parte para a proxima linha
		}
	}
	printf("\nA solucao do seu sistema eh:\n");
	for(i = 0; i < m; i++) //imprime a solucao do sistema
	{
		printf("\nX%d: %.3f", i, vet[i]);// trunca o resultado para 3 casas decimais
	}
}

/* Funcao main */
int main()
{
	int a, b, c, m, n, i, j, escolha, quantidade, count = 0;
	printf("Ola! Este programa ira criar uma matriz esparsa.\n");
	printf("Qual o tamanho da sua matriz? \nDigite na seguinte ordem: numero de linhas, ENTER, numero de colunas, ENTER.\n");
	scanf("%d%d", &m, &n);
	while (m < 1) //caso sejam digitados valores menores que zero para linhas ou colunas
	{
		printf("Favor entrar com um numero maior do que 0 para as linhas");
		scanf("%d%d", &m, &n);
	}
	while (n < 1)
	{
		printf("Favor entrar com um numero maior do que 0 para as colunas");
		scanf("%d%d", &m, &n);
	}
	struct coluna *raiz = (struct coluna *)malloc(sizeof(struct coluna));// cria a raiz
	struct coluna *pont = raiz;
	raiz->prox = NULL;
	raiz->line = NULL;
	raiz->linha = 0;
	for (i = 1; i < m; i++)// cria todos os elementos da lista base
	{
		pont->prox = (struct coluna *)malloc(sizeof(struct coluna));
		pont = pont->prox;
		pont->line = NULL;
		pont->prox = NULL;
		pont->linha = i; // marca o numero da linha
	}
	while (escolha != 7) // repete o menu ate que seja escolhida a opcao "sair"
	{
		printf("\n\nO que voce deseja fazer? Digite o numero correspondente!\n");
		printf("1 - Adicionar numeros\n2 - Excluir numeros\n3 - Consultar um valor na posicao ij\n");
		printf("4 - Soma dos valores de uma linha\n5 - Soma dos valores de uma coluna\n6 - Resolucao do sistema por Gauss-Seidel\n7 - Sair\n");
		printf("OBS: Para a resolucao por Guass-Seidel, a matriz precisa ter um formato n x n+1, representando um sistema de equacoes linerares\n\n");
		scanf("%d", &escolha);
		if (escolha != 1 && count == 0)// nao se pode escolher outra opcao sem antes preencher a matriz
		{
			printf("\nNao existe nenhum numero na sua matriz, favor adicionar numeros.\nEscolha a opcao 1 e aperte 'Enter'");
		}
		else if (escolha < 1 || escolha > 6)// que nao seja escolhida uma opcao fora do menu
		{
			printf("Favor entrar com uma das opcoes do menu");
		}
		else
		{
			switch(escolha) // o menu foi feito usando "switch"
			{
				case 1:
					printf("\nQuantos numeros voce quer inserir na sua matriz?\n");
					scanf("%d", &quantidade);
					while (quantidade < 1)
					{
						printf("Favor entrar com uma quantidade maior do que 0");
						scanf("%d", &quantidade);
					}
					count++; // para marcar que ja foram inseridos numeros
					printf("\nDigite seus numeros, seguido de sua posicao:\n");
					printf("(Digite na seguinte ordem: 'numero' 'ENTER' 'numero da linha' 'ENTER' 'numero da coluna' 'ENTER')");
					for (j = 1; j <= quantidade; j++)//chama a funcao n vezes para inserir os n numeros
					{
						printf("\nNumero %d: ", j);
						scanf("%d%d%d", &a, &b, &c);
						insert(a, b, c, raiz);
					}
					break;
				
				case 2:
					printf("Digite o numero da linha e o numero da coluna do numero que voce deseja excluir, separados por 'ENTER':\n");
					scanf("%d%d", &a, &b);
					c = removenum(raiz, a, b);
					if(c == 0)
					{
						printf("O numero escolhido era 0, entao nada foi feito");//caso o numero ja nao existisse na matriz
					}
					break;
				
				case 3:
					printf("Digite os valores i e j (a linha e a coluna do numero a ser consultado,\nrespectivamente. Separe-os com um 'Enter')\n");
					scanf("%d%d", &a, &b);
					if(a >= m || b>= n) //caso os numeros estejam fora da matriz
					{
						printf("\nFavor digitar uma posicao que pertenca a matriz.\nLembrar que as linhas e colunas sao numeradas com inicio em 0,\nentao uma matriz de 3 colunas tem numeracao 0, 1, 2.");
					break;	
					}
					printf("\nO numero na posicao %dx%d eh %d.", a, b, consulta(raiz, a, b));
					break;
				
				case 4:
					printf("\nDigite o numero da linha que deseja somar.\nLembrar que as linhas sao numeradas com inicio em 0,\nentao uma matriz de 3 linhas tem numeracao 0, 1, 2.\n");
					scanf("%d", &a);
					if(a >= m )//caso os numeros estejam fora da matriz
					{
						printf("\nFavor digitar uma posicao que pertenca a matriz.\n");
					break;	
					}
					printf("\nA soma dos numeros da linha %d eh %d", a, sumlinha(raiz, a));
					break;
				
				case 5:
					printf("\nDigite o numero da linha que deseja somar.\nLembrar que as colunas sao numeradas com inicio em 0,\nentao uma matriz de 3 colunas tem numeracao 0, 1, 2.\n");
					scanf("%d", &b);
					if(b >= n )//caso os numeros estejam fora da matriz
					{
						printf("\nFavor digitar uma posicao que pertenca a matriz.\n");
					break;	
					}
					printf("\nA soma dos numeros da coluna %d eh %d", b, sumcoluna(raiz, b));
					break;
					
				case 6:
					if(n != m+1) //caso a matriz nao tenha o formato correto de um sistema de equacoes lineares.
					{
						printf("A matriz nao tem formato n x n+1, favor entrar novamente com a matriz");
						break;
					}
					if(check(raiz, n) == 0)
					{
						break;
					}
					gauss(raiz, m, n);
					break;
			}
		}
	}
}
