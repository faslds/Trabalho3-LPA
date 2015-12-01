#include<stdio.h>
#include<stdlib.h>

struct coluna
{
	int linha;
	struct linha *line;
	struct coluna *prox;
}

struct linha
{
	int numero;
	int coluna
	struct linha *prox;
}

void insert(int k, int m, int n, struct coluna *raiz)
{
	struct linha *a = NULL;
	struct linha *b = NULL
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

int main ()
{
	int m, n, i;
	printf("Qual o tamanho da sua matriz? Digite na seguinte ordem: ´numero de linhas´ ´ENTER´ ´numero de colunas´ ´ENTER´");
	scanf("%d", &m);
	while (m < 1)
	{
		printf("Favor entrar com um número maior do que 0");
		scanf("%d", &m);
		
	}
	scanf("&d", &n);
	while (n < 1)
	{
		printf("Favor entrar com um número maior do que 0");
		scanf("%d", &n);
	}
	struct coluna *raiz = (struct coluna *)malloc(sizeof(struct coluna));
	struct coluna *pont = raiz;
	raiz->prox = NULL;
	raiz->line = NULL;
	for (i = 0; i < m; m++)
	{
		pont->prox = (struct coluna *)malloc(sizeof(struct coluna));
		pont = pont->prox;
		pont->line = NULL;
		pont->prox = NULL;
	}
	
}
