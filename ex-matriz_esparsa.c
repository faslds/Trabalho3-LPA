#include<stdio.h>
#include<stdlib.h>

struct linha
{
	int numero;
	int coluna
	struct linha *prox;
}

struct coluna
{
	int linha;
	struct linha *line;
	struct coluna *prox;
}

void remove (struct coluna *raiz, int m, int n)
{
	struct linha *a = NULL;
	struct linha *b = NULL;
	struct linha *c = NULL;
	struct coluna *pont = raiz;
	while(pont->linha != m)
	{
		pont = pont->prox;
	}
	a = pont->line;
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
			return -1;
		}
	}
	if(a->coluna == n)
	{
		b->prox = a->prox;
		printf("O número %d foi removido com sucesso!", a->numero);
		free(a);
	}
	else
	{
		return -1;
	}
	
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

int main ()
{
	int m, n, i, escolha;
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
	raiz->linha = 0;
	for (i = 1; i < m; i++)
	{
		pont->prox = (struct coluna *)malloc(sizeof(struct coluna));
		pont = pont->prox;
		pont->line = NULL;
		pont->prox = NULL;
		pont->linha = i;
	}
	while (escolha != )
	{
		printf("\n\nO que voce deseja fazer? Digite o numero correspondente!\n");
		printf("")
	}
}
