#include <stdio.h>
#include <locale.h>

typedef struct Nascimento {
	int dia;
	int mes;
	int ano;
} Nascimento;

typedef struct Pessoa {
	char nome[256];
	char CPF[12];
	char address[256];
	Nascimento nascimento;
} Pessoa;

void cadastrarUsuarios(int size, Pessoa *pessoa);
void exibirDados(int size, Pessoa *pessoa);

int main(void )	{
	setlocale(LC_ALL, "");
	
	int size;
	
	printf("Digite a quantidade de pessoas que você deseja cadastrar: ");
	scanf("%d", &size);
	
	Pessoa pessoa[size];
	
	cadastrarUsuarios(size, pessoa);
	exibirDados(size, pessoa);
	
	return 0;
}

void cadastrarUsuarios(int size, Pessoa *pessoa) {
	for(int i = 0; i < size; i++) {
		printf("\n");
		
		// Nome: 
		printf("Digite o nome da %dº pessoa: ", i + 1);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].nome);
		
		// Data de nascimento: 
		printf("Digite a data de nascimento de %s: ", pessoa[i].nome);
		scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);
		
		// CPF:
		printf("Digite o CPF de %s: ", pessoa[i].nome);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].CPF);
		
		// Endereço:
		printf("Digite o endereço de %s: ", pessoa[i].nome);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].address);
	}
}

void exibirDados(int size, Pessoa *pessoa) {
	for(int i = 0; i < size; i++) {
		// Dados:
		
		printf("\n");
		
		printf("USUÁRIO %d:\n", i + 1);
		
		// Nome: 
		printf("Nome: %s\n", pessoa[i].nome);
		
		// Idade: 
		printf("Idade: %d (%d/%d/%d)\n", 2024 - pessoa[i].nascimento.ano, pessoa[i].nascimento.dia, pessoa[i].nascimento.mes ,pessoa[i].nascimento.ano);
		
		// CPF:
		printf("CPF: %s\n", pessoa[i].CPF);
		
		// Endereço:
		printf("Endereço: %s\n", pessoa[i].address);
		
		printf("\n");
	}
}
