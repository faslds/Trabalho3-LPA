#include<stdio.h>
#include<stdlib.h>

struct linha
{
	int numero;
	int coluna;
	struct linha *prox;
};

struct coluna
{
	int linha;
	struct linha *line;
	struct coluna *prox;
};

int removenum(struct coluna *raiz, int m, int n)
{
	struct linha *a = NULL;
	struct linha *b = NULL;
	struct linha *c = NULL;
	struct coluna *pont = raiz;
	while(pont->linha != m)
	{
		pont = pont->prox;
	}
	//printf("AQUI");
	a = pont->line;
	b = pont;
	//b = pont->line;
	
	//if testar se existe alguma coisa na linha
	
	while(a->coluna > n)
	{
		if(a->prox != NULL)
		{
			b = a;
			a = a->prox;
		}
		else
		{
			return 0;
		}
	}
	//printf("AQUI2");
	//	printf("O numero %d ", a->numero);
	if(a->coluna == n)
	{
		//printf("\nAQUI 2,5\n");
		b->prox = a->prox;
		//printf("AQUI3");
		printf("O numero %d foi removido com sucesso!", a->numero);
		//printf("AQUI4");
		free(a);
		//printf("AQUI5");
		return 1;
	}
	else
	{
		//printf("caiu no else");
		return 0;
	}
}

void insert(int k, int m, int n, struct coluna *raiz)
{
	struct linha *a = NULL;
	struct linha *b = NULL;
	struct coluna *pont = raiz;
	int i = 0; 
	
	while(pont->linha != m)
	{
		pont = pont->prox;
	}
	if (pont->line == NULL)
	{
		a = (struct linha*) malloc(sizeof(struct linha));
		a->numero = k;
		a->coluna = n; 
		a->prox = NULL;
		pont->line = a;
	}
	else 
	{
		a = pont->line;
		if (a->coluna > n)
		{
			b = (struct linha*) malloc(sizeof(struct linha));
			b->numero = k;
			b->coluna = n;
			b->prox = a;
			pont->line = b;
		}
		else
		{
			while(a->prox != NULL && a->coluna < n)
			{
				a = a->prox;
				//i++;
			}
			b = (struct linha*) malloc(sizeof(struct linha));
			b->numero = k;
			b->coluna = n;
			b->prox = a->prox;
			a->prox = b;
		}
	}
}

int consulta(struct coluna *raiz, int m, int n)
{
	struct coluna *pont = raiz;
	struct linha *a = NULL;
	while(pont->linha != m)
	{
		pont = pont->prox;
	}
	if(pont->line == NULL)
	{
		return 0;
	}
	a = pont->line;
	while(a->coluna < n)
	{
		a = a->prox;
	}
	if(a->coluna == n)
	{
		return(a->numero);
	}
	else if(a->coluna != n)
	{
		return 0;
	}
}

int sumlinha(struct coluna *raiz, int k)
{
	struct coluna *pont = raiz;
	struct linha *a = NULL;
	int soma = 0;
	while(pont->linha != k)
	{
		pont = pont->prox;
	}
	if (pont->line == NULL)
	{
		return 0;
	}
	a = pont->line;
	while(a != NULL)
	{
		soma = soma + a->numero;
		a = a->prox;
	}
	return (soma);
}

int sumcoluna(struct coluna *raiz, int k)
{
	struct coluna *pont = raiz;
	struct linha *a = pont->line;
	int soma = 0;
	while (pont != NULL)
	{
		a = pont->line;
		if(a != NULL)
		{ 
			while(a->coluna < k && a != NULL)
			{
				a = a->prox;
			}
			if(a->coluna == k)
			{
				soma = soma + a->numero;
			}
		}
		pont = pont->prox;
	}
	return (soma);
	
}

int main ()
{
	int a, b, c, m, n, i, j, escolha, quantidade, count = 0;
	printf("Qual o tamanho da sua matriz? \nDigite na seguinte ordem: numero de linhas, ENTER, numero de colunas, ENTER\n");
	//printf("Linhas: ");
	scanf("%d%d", &m, &n);
	while (m < 1)
	{
		printf("Favor entrar com um numero maior do que 0 para as linhas");
		//scanf("%d", &m);
		scanf("%d%d", &m, &n);
	}
	//printf("\nColunas: ");
	//scanf("&d", &n);
	
	while (n < 1)
	{
		printf("Favor entrar com um numero maior do que 0 para as colunas");
		//scanf("%d", &n);
		scanf("%d%d", &m, &n);
	}
	struct coluna *raiz = (struct coluna *)malloc(sizeof(struct coluna));
	struct coluna *pont = raiz;
	raiz->prox = NULL;
	raiz->line = NULL;
	raiz->linha = 0;
	for (i = 1; i < m; i++)
	{
		pont->prox = (struct coluna *)malloc(sizeof(struct coluna));
		pont = pont->prox;
		pont->line = NULL;
		pont->prox = NULL;
		pont->linha = i;
	}
	while (escolha != 6)
	{
		printf("\n\nO que voce deseja fazer? Digite o numero correspondente!\n");
		printf("1 - Adicionar numeros\n2 - Excluir numeros\n3 - Consultar um valor na posicao ij\n");
		printf("4 - Soma dos valores de uma linha\n5 - Soma dos valores de uma coluna\n6 - Sair\n\n");
		scanf("%d", &escolha);
		if (escolha != 1 && count == 0)
		{
			printf("\nNao existe nenhum numero na sua matriz, favor adicionar numeros.\nEscolha a opcao 1 e aperte 'Enter'");
			//scanf("%d", &escolha);
		}
		else if (escolha < 1 || escolha > 6)
		{
			printf("Favor entrar com uma das opcoes do menu");
		}
		else
		{
			switch(escolha)
			{
				case 1:
					printf("\nQuantos numeros voce quer inserir na sua matriz?\n");
					scanf("%d", &quantidade);
					while (quantidade < 1)
					{
						printf("Favor entrar com uma quantidade maior do que 0");
						scanf("%d", &quantidade);
					}
					count++;
					printf("\nDigite seus numeros, seguido de sua posicao:\n");
					printf("(Digite na seguinte ordem: 'numero' 'ENTER' 'numero da linha' 'ENTER' 'numero da coluna' 'ENTER')");
					for (j = 1; j <= quantidade; j++)
					{
						printf("\nNumero %d: ", j);
						//printf("AQUI");
						scanf("%d%d%d", &a, &b, &c);
						//scanf("&d", &a);
						//scanf("&d", &b);
						//scanf("&d", &c);
						//printf("AQUI 2");
						insert(a, b, c, raiz);
					}
					break;
				
				case 2:
					printf("Digite o numero da linha e o numero da coluna do numero que voce deseja excluir, separados por 'ENTER':\n");
					scanf("%d%d", &a, &b);
					c = removenum(raiz, a, b);
					if(c == 0)
					{
						printf("O numero escolhido era 0, entao nada foi feito");
					}
					break;
				
				case 3:
					printf("Digite os valores i e j (a linha e a coluna do numero a ser consultado,\nrespectivamente. Separe-os com um 'Enter')\n");
					scanf("%d%d", &a, &b);
					if(a >= m || b>= n)
					{
						printf("\nFavor digitar uma posicao que pertenca a matriz.\nLembrar que as linhas e colunas sao numeradas com inicio em 0,\nentao uma matriz de 3 colunas tem numeracao 0, 1, 2.");
					break;	
					}
					printf("\nO numero na posicao %dx%d eh %d.", a, b, consulta(raiz, a, b));
					break;
				
				case 4:
					printf("\nDigite o numero da linha que deseja somar.\nLembrar que as linhas e sao numeradas com inicio em 0,\nentao uma matriz de 3 linhas tem numeracao 0, 1, 2.\n");
					scanf("%d", &a);
					if(a >= m )
					{
						printf("\nFavor digitar uma posicao que pertenca a matriz.\n");
					break;	
					}
					printf("\nA soma dos numeros da linha %d eh %d", a, sumlinha(raiz, a));
			}
		}
	}
}
