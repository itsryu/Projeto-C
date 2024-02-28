#include <stdio.h>
#include <stdlib.h>
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
void exibirMenu(int size, Pessoa *pessoa);
void alterarDados(int size, Pessoa *pessoa, int index);
void deletarUsuario(int *size, Pessoa **pessoa, int index);
void voltarAoMenu(int size, Pessoa *pessoa);
void encerrarPrograma();
void limparTela();

int main(void)	{
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Sistema Cadastro de Usúario");
	
	printf("--------Sistema Cadastro de Usúario-------\n\n");

	int size;
	
	printf("Digite a quantidade de pessoas que você deseja cadastrar: ");
	scanf("%d", &size);
	
	Pessoa *pessoa = (Pessoa *)malloc(size * sizeof(Pessoa));
	
	cadastrarUsuarios(size, pessoa);
	exibirMenu(size, pessoa);
	
	return 0;
}

void exibirMenu(int size, Pessoa *pessoa) {
	printf("--------Sistema Cadastro de Usúario-------\n\n");

	int input;
	
	printf("1. Exibir os dados\n2. Alterar dados cadastrados de um usuário\n3. Deletar usuário cadastrado\n4. Sair do programa\n\n");
	printf("Escolha uma opção: ");
	scanf("%d", &input);

	while(input < 1 || input > 4) {
		printf("Opção inválida, tente novamente: ");
		scanf("%d", &input);
	}

	switch(input) {
		case 1: {
			exibirDados(size, pessoa);
			break;
		}
		case 2: {
			int input;
			
			printf("Qual usuário você deseja alterar: ");
			scanf("%d", &input);
			
			while(input <= 0 || input > size) {
				printf("Usuário inválido, tente novamente: ");
				scanf("%d", &input);
			}
			
			alterarDados(size, pessoa, input);
			break;
		}
		case 3: {
			int input;
			
			printf("Qual usuário você deseja deletar: ");
			scanf("%d", &input);
			
			while(input <= 0 || input > size) {
				printf("Usuário inválido, tente novamente: ");
				scanf("%d", &input);
			}
			
			deletarUsuario(&size, &pessoa, input);
			break;
		}
		case 4: {
			encerrarPrograma();
			break;
		}
	}
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
	
	printf("\n");
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
	
	int input;

	printf("\n");
	printf("1. Voltar ao menu\n2. Encerrar o programa\n\n");
	printf("Escolha uma opção: ");
	scanf("%d", &input);

	while(input < 1 || input > 2) {
		printf("Opção inválida, tente novamente: ");
		scanf("%d", &input);
	}

	switch(input) {
		case 1: {
			voltarAoMenu(size, pessoa);
			break;
		}
		case 2: {
			encerrarPrograma();
			break;
		}
	}
}

void deletarUsuario(int *size, Pessoa **pessoa, int index) {
	*size -= 1;

	Pessoa *temp = (Pessoa *)malloc(*size * sizeof(Pessoa));
	
	for(int i = 0, j = 0; i < *size + 1; i++) {
		if (i != index - 1) {
			temp[j++] = (*pessoa)[i];
		}
	}
	
	free(*pessoa);

	int input;

	printf("\n");
	printf("Usuário deletado com sucesso!\n");
	printf("1. Voltar ao menu\n2. Encerrar o programa\n\n");
	printf("Escolha uma opção: ");
	scanf("%d", &input);

	while(input < 1 || input > 2) {
		printf("Opção inválida, tente novamente: ");
		scanf("%d", &input);
	}

	switch(input) {
		case 1: {
			voltarAoMenu(*size, temp);
			break;
		}
		case 2: {
			encerrarPrograma();
			break;
		}
	}
}

void alterarDados(int size, Pessoa *pessoa, int index) {
	int i = index - 1;
	
	// Nome: 
	printf("Digite o novo nome do usuário %d: ", index);
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
	
	int input;

	printf("\n");
	printf("1. Voltar ao menu\n2. Encerrar o programa\n\n");
	printf("Escolha uma opção: ");
	scanf("%d", &input);

	while(input < 1 || input > 2) {
		printf("Opção inválida, tente novamente: ");
		scanf("%d", &input);
	}

	switch(input) {
		case 1: {
			voltarAoMenu(size, pessoa);
			break;
		}
		case 2: {
			encerrarPrograma();
			break;
		}
	}
}

void limparTela() {
	system("cls");
}

void voltarAoMenu(int size, Pessoa *pessoa) {
	limparTela();
	exibirMenu(size, pessoa);
}

void encerrarPrograma() {
	system("pause");
	exit(0);
}
