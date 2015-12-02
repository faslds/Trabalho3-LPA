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
		return 0;
	}
	else
	{
		return -1;
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

int main ()
{
	int a, b, c, m, n, i, j, escolha, quantidade, count = 0;
	printf("Qual o tamanho da sua matriz? \nDigite na seguinte ordem: numero de linhas, ENTER, numero de colunas, ENTER\n");
	printf("Linhas: ");
	scanf("%d", &m);
	while (m < 1)
	{
		printf("Favor entrar com um numero maior do que 0");
		scanf("%d", &m);
	}
	printf("\nColunas: ");
	scanf("&d", &n);
	
	while (n < 1)
	{
		printf("Favor entrar com um numero maior do que 0");
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
	while (escolha != 6)
	{
		printf("\n\nO que voce deseja fazer? Digite o numero correspondente!\n");
		printf("1 - Adicionar numeros\n2 - Excluir numeros\n3 - Consultar um valor na posicao ij\n");
		printf("\n4 - Soma dos valores de uma linha\n5 - Soma dos valores de uma coluna\n6 - Sair\n");
		scanf("%d", &escolha);
		if (escolha != 1 && count == 0)
		{
			printf("Nao existe nenhum numero na sua matriz, favor adicionar numeros. Escolha a opcao 1 e aperte 'Enter'");
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
						scanf("&d", &a);
						scanf("&d", &b);
						scanf("&d", &c);
						insert(a, b, c, raiz);
					}
			}
		}
	}
}
