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
	struct item *prox;
}

void insert(int k, int m, int n, struct coluna *pont)
{
	while(pont->linha != m)
	{
		pont = pont->prox;
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
