#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

typedef struct {
	int dia;
	int mes;
	int ano;
} Nascimento;

typedef struct {
	char nome[256];
	char CPF[12];
	char address[256];
	Nascimento nascimento;
} Pessoa;

void exibirMenu(int size, Pessoa *pessoa);
void cadastrarUsuarios(int size, Pessoa *pessoa);
void exibirDados(int size, Pessoa *pessoa);
void alterarDados(int size, Pessoa *pessoa, int index);
void deletarUsuario(int *size, Pessoa *pessoa, int index);
void cadastrarNovoUsuario(int *size, Pessoa *pessoa);
void voltarAoMenu(int size, Pessoa *pessoa);
void exibirOpcoes(int size, Pessoa *pessoa);
int calcularIdade(int dia, int mes, int ano);
void encerrarPrograma();
void limparTela();

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	system("color 0A");
	system("title Sistema Cadastro de Us�ario");
	
	printf("--------Sistema Cadastro de Us�ario-------\n\n");

	int size;
	
	printf("Digite a quantidade de pessoas que voc� deseja cadastrar: ");

	while(scanf("%d", &size) != 1) {
		fflush(stdin);

        printf("Quantidade inv�lida. Por favor, digite um n�mero inteiro positivo: ");
    }

	while(size < 1 || size > 100) {
		printf("Quantidade inv�lida, tente novamente (1-100): ");
		scanf("%d", &size);
	}
	
	Pessoa *pessoa = (Pessoa *)malloc(size * sizeof(Pessoa));

	if(pessoa == NULL) {
		limparTela();
		
		printf("Erro ao alocar mem�ria. Encerrando o programa...\n\n");
		exit(1);
	}
	
	cadastrarUsuarios(size, pessoa);
	exibirMenu(size, pessoa);
	
	return 0;
}

void exibirMenu(int size, Pessoa *pessoa) {
	printf("--------Sistema Cadastro de Us�ario-------\n\n");

	int input;
	
	printf("1. Exibir os dados\n2. Alterar dados cadastrados de um usu�rio\n3. Deletar usu�rio cadastrado\n4. Cadastrar novo usu�rio\n5. Sair do programa\n\n");
	printf("Escolha uma op��o: ");
	scanf("%d", &input);

	while(input < 1 || input > 5) {
		printf("Op��o inv�lida, tente novamente: ");
		scanf("%d", &input);
	}

	switch(input) {
		case 1: {
			exibirDados(size, pessoa);
			exibirOpcoes(size, pessoa);
			break;
		}
		case 2: {
			int input;

			exibirDados(size, pessoa);
			
			printf("Qual usu�rio voc� deseja alterar: ");
			scanf("%d", &input);
			
			while(input < 0 || input > size) {
				printf("Usu�rio inv�lido, tente novamente (Digite 0 para voltar ao menu): ");
				scanf("%d", &input);

				if (input == 0) {
					voltarAoMenu(size, pessoa);
				}
			}

			printf("\n");
			
			alterarDados(size, pessoa, input);
			break;
		}
		case 3: {
			int input;

			exibirDados(size, pessoa);
			
			printf("Qual usu�rio voc� deseja deletar: ");
			scanf("%d", &input);
			
			while(input < 0 || input > size) {
				printf("Usu�rio inv�lido, tente novamente (Digite 0 para voltar ao menu): ");
				scanf("%d", &input);

				if (input == 0) {
					voltarAoMenu(size, pessoa);
				}
			}
			
			deletarUsuario(&size, pessoa, input);
			break;
		}
		case 4: {
			cadastrarNovoUsuario(&size, pessoa);
			break;
		}
		case 5: {
			encerrarPrograma();
			break;
		}
	}
}

void exibirOpcoes(int size, Pessoa *pessoa) {
	int input;

	printf("1. Voltar ao menu\n2. Encerrar o programa\n\n");
	printf("Escolha uma op��o: ");
	scanf("%d", &input);

	while(input < 1 || input > 2) {
		printf("Op��o inv�lida, tente novamente: ");
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

void cadastrarUsuarios(int size, Pessoa *pessoa) {
	for(int i = 0; i < size; i++) {
		printf("\n");
		
		// Nome: 
		printf("Digite o nome do %d� usu�rio: ", i + 1);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].nome);
		
		// Data de nascimento: 
		printf("Digite a data de nascimento de %s (DD/MM/AAAA): ", pessoa[i].nome);
		scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);

		while(pessoa[i].nascimento.dia < 1 || pessoa[i].nascimento.dia > 31 || pessoa[i].nascimento.mes < 1 || pessoa[i].nascimento.mes > 12 || pessoa[i].nascimento.ano < 1900 || pessoa[i].nascimento.ano > 2024) {
			printf("Data de nascimento inv�lida, tente novamente: ");
			scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);
		}
		
		// CPF:
		printf("Digite o CPF de %s (Apenas n�meros): ", pessoa[i].nome);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].CPF);

		while(strlen(pessoa[i].CPF) != 11) {
			printf("CPF inv�lido, tente novamente: ");
			fflush(stdin);
			scanf("%[^\n]s", &pessoa[i].CPF);
		}
		
		// Endere�o:
		printf("Digite o endere�o de %s: ", pessoa[i].nome);
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].address);
	}
	
	voltarAoMenu(size, pessoa);
}

void cadastrarNovoUsuario(int *size, Pessoa *pessoa) {
	*size += 1;
	
	Pessoa *temp = (Pessoa *)malloc(*size * sizeof(Pessoa));

	if(temp == NULL) {
		limparTela();

		printf("Erro ao alocar mem�ria. Encerrando o programa...\n\n");
		exit(1);
	}
	
	for(int i = 0, j = 0; i < *size - 1; i++) {
		temp[j++] = pessoa[i];
	}
	
	free(pessoa);

	printf("\n");
	
	// Nome: 
	printf("Digite o nome do novo usu�rio: ", size);
	fflush(stdin);
	scanf("%[^\n]s", &temp[*size - 1].nome);
	
	// Data de nascimento: 
	printf("Digite a data de nascimento de %s (DD/MM/AAAA): ", temp[*size - 1].nome);
	scanf("%d/%d/%d", &temp[*size - 1].nascimento.dia, &temp[*size - 1].nascimento.mes, &temp[*size - 1].nascimento.ano);

	while(pessoa[*size - 1].nascimento.dia < 1 || pessoa[*size - 1].nascimento.dia > 31 || pessoa[*size - 1].nascimento.mes < 1 || pessoa[*size - 1].nascimento.mes > 12 || pessoa[*size - 1].nascimento.ano < 1900 || pessoa[*size - 1].nascimento.ano > 2024) {
		printf("Data de nascimento inv�lida, tente novamente: ");
		scanf("%d/%d/%d", &pessoa[*size - 1].nascimento.dia, &pessoa[*size - 1].nascimento.mes, &pessoa[*size - 1].nascimento.ano);
	}
	
	// CPF:
	printf("Digite o CPF de %s (Apenas n�meros): ", temp[*size - 1].nome);
	fflush(stdin);
	scanf("%[^\n]s", &temp[*size - 1].CPF);
	
	// Endere�o:
	printf("Digite o endere�o de %s: ", temp[*size - 1].nome);
	fflush(stdin);
	scanf("%[^\n]s", &temp[*size - 1].address);


	printf("\nNovo usu�rio cadastrado com sucesso!\n\n");

	exibirOpcoes(*size, temp);
}

void exibirDados(int size, Pessoa *pessoa) {
	limparTela();

	if(size == 0) {
		printf("Nenhum usu�rio cadastrado.\n\n");
	} else {
		for(int i = 0; i < size; i++) {
			printf("USU�RIO %d:\n\n", i + 1);
			printf("Nome: %s\n", pessoa[i].nome); 
			printf("Idade: %d (%d/%d/%d)\n", calcularIdade(pessoa[i].nascimento.dia, pessoa[i].nascimento.mes, pessoa[i].nascimento.ano), pessoa[i].nascimento.dia, pessoa[i].nascimento.mes ,pessoa[i].nascimento.ano);
			printf("CPF: %s\n", pessoa[i].CPF);
			printf("Endere�o: %s\n", pessoa[i].address);
		
			printf("\n");
		}
	}
}

void deletarUsuario(int *size, Pessoa *pessoa, int index) {
	*size -= 1;

	Pessoa *temp = (Pessoa *)malloc(*size * sizeof(Pessoa));

	if(temp == NULL) {
		limparTela();
		
		printf("Erro ao alocar mem�ria. Encerrando o programa...\n\n");
		exit(1);
	}
	
	for(int i = 0, j = 0; i < *size + 1; i++) {
		if (i != index - 1) {
			temp[j++] = pessoa[i];
		}
	}
	
	free(pessoa);

	printf("\nUsu�rio %d deletado com sucesso!\n\n", index);

	exibirOpcoes(*size, temp);
}

void alterarDados(int size, Pessoa *pessoa, int index) {
	int i = index - 1;
	
	// Nome: 
	printf("Digite o novo nome do usu�rio %d: ", index);
	fflush(stdin);
	scanf("%[^\n]s", &pessoa[i].nome);
		
	// Data de nascimento: 
	printf("Digite a data de nascimento de %s (DD/MM/AAAA): ", pessoa[i].nome);
	scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);

	while(pessoa[i].nascimento.dia < 1 || pessoa[i].nascimento.dia > 31 || pessoa[i].nascimento.mes < 1 || pessoa[i].nascimento.mes > 12 || pessoa[i].nascimento.ano < 1900 || pessoa[i].nascimento.ano > 2024) {
		printf("Data de nascimento inv�lida, tente novamente: ");
		scanf("%d/%d/%d", &pessoa[i].nascimento.dia, &pessoa[i].nascimento.mes, &pessoa[i].nascimento.ano);
	}
		
	// CPF:
	printf("Digite o CPF de %s (Apenas n�meros): ", pessoa[i].nome);
	fflush(stdin);
	scanf("%[^\n]s", &pessoa[i].CPF);

	while(strlen(pessoa[i].CPF) != 11) {
		printf("CPF inv�lido, tente novamente: ");
		fflush(stdin);
		scanf("%[^\n]s", &pessoa[i].CPF);
	}
		
	// Endere�o:
	printf("Digite o endere�o de %s: ", pessoa[i].nome);
	fflush(stdin);
	scanf("%[^\n]s", &pessoa[i].address);

	printf("\nDados de usu�rio %d atualizados com sucesso!\n\n", index);
	
	exibirOpcoes(size, pessoa);
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

// https://petbcc.ufscar.br/time/
int calcularIdade(int dia, int mes, int ano) {
    time_t now;
    time(&now);
    struct tm *dataAtual = localtime(&now);

	int anoAtual= dataAtual->tm_year + 1900;
	int mesAtual = dataAtual->tm_mon + 1;
	int diaAtual = dataAtual->tm_mday;
	int idade = anoAtual - ano;

    if (mesAtual < mes || (mesAtual == mes && diaAtual < dia)) idade--;

    return idade;
}
