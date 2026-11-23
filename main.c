#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define VERMELHO "\033[31m"
#define VERMELHO_ESCURO "\033[38;5;88m"

#define AZUL "\033[34m"
#define AZUL_ESCURO "\033[38;5;18m"
#define AZUL_MARINHO "\033[38;5;17m"

#define AMARELO "\033[33m"
#define AMARELO_LIMAO "\033[38;5;190m"

#define VERDE "\033[32m"
#define VERDE_VIBRANTE "\033[38;5;46m"

#define RESET "\033[0m"

int senha[2];
int numero[1000];
int numero_casa[1000];
char bairro[37][30] = {
	"Centro", "Maracana", "Yolanda",
	"Campos do Iguacu", "Centro Civico", "Polo Centro",
	"Morumbi", "Portal da Foz",
	"Panorama", "Sao Roque",
	"Bourbon", "Porto Meira", "Tres Fronteiras",
	"America", "Monjolo", "Vila Portes",
	"Lancaster", "Tres Bandeiras",
	"Itaipu A", "Itaipu B", "KLP", "Ipe",
	"Cidade Nova", "Itaipu Binacional", "Itaipu C", "Polo Universitario", "Porto Belo",
	"Alvorada", "Nautica", "Tres Lagoas",
	"Carima", "Mata Verde",
	"Cataratas", "Cognopolis", "Lote Grande", "Remanso", "N/A"
};
char bairroc[1000][30];
char rua[1000][1][40];
char nome[1000][100];

int quantidade[10];
int i[10];
int menu[20] = { 0 };


char departamento[1000][30] = {
	"doce",
	"salgado",
	"bebida"
};
char novodep[30];

char produtos[1000][50] = {
	"Shawarma misto",
	"Shawarma carne",
	"Shawarma frango",
	"Shawarma habib",
	"Coca Cola 2L",
	"Suco fruta 2L",
	"Agua com gas"
};
char tipos[1000][50] = {
	"salgado",
	"salgado",
	"salgado",
	"salgado",
	"bebida",
	"bebida",
	"bebida"
};

float precos[1000] = {
	12.99,
	13.99,
	13.99,
	15.99,
	10.00,
	8.00,
	4.00
};

char estoque[1000][40] = {
	"Pao arabe",
	"Carne bovina",
	"Carne de frango",
	"Salada",
	"Batata frita",
	"Molho de pimenta",
	"Sache ketchup",
	"Coca cola 2l",
	"Suco fruta 2l",
	"Agua com gas",
	"Guardanapo"
};

int quantosst[1000] = {
	126,
	10000,
	10000,
	2000,
	9320,
	2000,
	500,
	45,
	50,
	105,
	500
};

char tipoe[1000][3] = {
	"un",
	"g",
	"g",
	"g",
	"g",
	"g",
	"un",
	"un",
	"un",
	"un",
	"un"
};
char novoprod[50];
char novoitem[40];
float novopreco;
int novaqtd;
int dst[1000][1000];
int qtdst[5] = { 11 };
int qtd1[1000];
float total[2][1000];
int qtd[4] = {7, 3, 0, 0};
int qtd2[4];
char carrinho[1000][1000][50];
float cprecos[1000][1000];
int nurua[1000];
void cancelapdd() {
	total[0][qtd[2]] = 0.00;
	qtd1[qtd[2]] = 0;
}
char outro[1][1000];
int selec;
int qtdf = 1;

int gasto[1000][1000];
int faltou;
int carregou = 0;

void iniciargasto() {
	gasto[0][0] = 1;
	gasto[0][1] = 50;
	gasto[0][2] = 50;
	gasto[0][3] = 20;
	gasto[0][10] = 1;

	gasto[1][0] = 1;
	gasto[1][1] = 100;
	gasto[1][3] = 20;
	gasto[1][10] = 1;

	gasto[2][0] = 1;
	gasto[2][2] = 100;
	gasto[2][3] = 20;
	gasto[2][10] = 1;

	gasto[3][1] = 125;
	gasto[3][3] = 20;
	gasto[3][4] = 40;
	gasto[3][5] = 10;

	gasto[4][7] = 1;
	gasto[5][8] = 1;
	gasto[6][9] = 1;
}

void mostrargasto(int p) {
	int achou = 0;
	printf(AZUL"%s\n", produtos[p]);
	for (int e = 0; e < qtdst[0]; e++) {
		if (gasto[p][e] > 0) {
			printf(VERDE"   %-20s %d %s\n", estoque[e], gasto[p][e], tipoe[e]);
			achou = 1;
		}
	}
	if (achou == 0) {
		printf(AMARELO"   (sem gasto cadastrado)\n");
	}
}

int baixaestoque(int p, int q) {
	for (int e = 0; e < qtdst[0]; e++) {
		if (gasto[p][e] * q > quantosst[e]) {
			faltou = e;
			return 0;
		}
	}
	for (int e = 0; e < qtdst[0]; e++) {
		quantosst[e] -= gasto[p][e] * q;
	}
	return 1;
}

void addproduto(int a) {
	for (int k = 0; k < qtdst[0]; k++) {
	}
}

void salvarpdd() {
	FILE *f;
	f = fopen("dados.txt", "w");
	if (f == NULL) {
		return;
	}

	for (int k = 0; k < 4; k++) {
		fprintf(f, "%d\n", qtd[k]);
	}
	for (int k = 0; k < 4; k++) {
		fprintf(f, "%d\n", qtd2[k]);
	}
	fprintf(f, "%d\n", qtdst[0]);
	fprintf(f, "%d\n", i[3]);

	for (int k = 0; k < qtd[1]; k++) {
		fprintf(f, "%s\n", departamento[k]);
	}

	for (int k = 0; k < qtd[0]; k++) {
		fprintf(f, "%s\n", produtos[k]);
		fprintf(f, "%s\n", tipos[k]);
		fprintf(f, "%.2f\n", precos[k]);
	}

	for (int k = 0; k < qtdst[0]; k++) {
		fprintf(f, "%s\n", estoque[k]);
		fprintf(f, "%d\n", quantosst[k]);
		fprintf(f, "%s\n", tipoe[k]);
	}

	for (int p = 0; p < qtd[0]; p++) {
		for (int e = 0; e < qtdst[0]; e++) {
			fprintf(f, "%d\n", gasto[p][e]);
		}
	}

	for (int p = 0; p <= qtd[2]; p++) {
		fprintf(f, "%d\n", numero[p]);
		fprintf(f, "%d\n", nurua[p]);
		fprintf(f, "%.2f\n", total[0][p]);
		fprintf(f, "%s\n", nome[p]);
		fprintf(f, "%s\n", bairroc[p]);
		fprintf(f, "%s\n", rua[p][0]);
		fprintf(f, "%d\n", qtd1[p]);
		for (int o = 0; o < qtd1[p]; o++) {
			fprintf(f, "%s\n", carrinho[p][o]);
			fprintf(f, "%.2f\n", cprecos[p][o]);
		}
	}

	fclose(f);
}

void carregarpdd() {
	FILE *f;
	f = fopen("dados.txt", "r");
	if (f == NULL) {
		return;
	}
	carregou = 1;

	for (int k = 0; k < 4; k++) {
		fscanf(f, "%d%*c", &qtd[k]);
	}
	for (int k = 0; k < 4; k++) {
		fscanf(f, "%d%*c", &qtd2[k]);
	}
	fscanf(f, "%d%*c", &qtdst[0]);
	fscanf(f, "%d%*c", &i[3]);

	for (int k = 0; k < qtd[1]; k++) {
		departamento[k][0] = '\0';
		fscanf(f, "%29[^\n]", departamento[k]);
		fscanf(f, "%*c");
	}

	for (int k = 0; k < qtd[0]; k++) {
		produtos[k][0] = '\0';
		fscanf(f, "%49[^\n]", produtos[k]);
		fscanf(f, "%*c");
		tipos[k][0] = '\0';
		fscanf(f, "%49[^\n]", tipos[k]);
		fscanf(f, "%*c");
		fscanf(f, "%f%*c", &precos[k]);
	}

	for (int k = 0; k < qtdst[0]; k++) {
		estoque[k][0] = '\0';
		fscanf(f, "%39[^\n]", estoque[k]);
		fscanf(f, "%*c");
		fscanf(f, "%d%*c", &quantosst[k]);
		tipoe[k][0] = '\0';
		fscanf(f, "%2[^\n]", tipoe[k]);
		fscanf(f, "%*c");
	}

	for (int p = 0; p < qtd[0]; p++) {
		for (int e = 0; e < qtdst[0]; e++) {
			fscanf(f, "%d%*c", &gasto[p][e]);
		}
	}

	for (int p = 0; p <= qtd[2]; p++) {
		fscanf(f, "%d%*c", &numero[p]);
		fscanf(f, "%d%*c", &nurua[p]);
		fscanf(f, "%f%*c", &total[0][p]);

		nome[p][0] = '\0';
		fscanf(f, "%99[^\n]", nome[p]);
		fscanf(f, "%*c");

		bairroc[p][0] = '\0';
		fscanf(f, "%29[^\n]", bairroc[p]);
		fscanf(f, "%*c");

		rua[p][0][0] = '\0';
		fscanf(f, "%39[^\n]", rua[p][0]);
		fscanf(f, "%*c");

		fscanf(f, "%d%*c", &qtd1[p]);
		for (int o = 0; o < qtd1[p]; o++) {
			carrinho[p][o][0] = '\0';
			fscanf(f, "%49[^\n]", carrinho[p][o]);
			fscanf(f, "%*c");
			fscanf(f, "%f%*c", &cprecos[p][o]);
		}
	}

	fclose(f);
}

void logo() {
	printf(VERDE"\n\n---------------------------------------------------------------------------------------------------------\n\n"RESET);
	printf(RESET"██╗  ██╗ █████╗ ███╗   ███╗ ██████╗  ██████╗ ██████╗ \n");
	printf("██║  ██║██╔══██╗████╗ ████║██╔═══██╗██╔═══██╗██╔══██╗\n");
	printf("███████║███████║██╔████╔██║██║   ██║██║   ██║██║  ██║\n");
	printf("██╔══██║██╔══██║██║╚██╔╝██║██║   ██║██║   ██║██║  ██║\n");
	printf("██║  ██║██║  ██║██║ ╚═╝ ██║╚██████╔╝╚██████╔╝██████╔╝\n");
	printf("╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝ ╚═════╝  ╚═════╝ ╚═════╝ \n");
	printf("\n");
	printf(AMARELO"███████╗██╗  ██╗ █████╗ ██╗    ██╗ █████╗ ██████╗ ███╗   ███╗ █████╗ ██████╗ ██╗ █████╗ \n");
	printf("██╔════╝██║  ██║██╔══██╗██║    ██║██╔══██╗██╔══██╗████╗ ████║██╔══██╗██╔══██╗██║██╔══██╗\n");
	printf("███████╗███████║███████║██║ █╗ ██║███████║██████╔╝██╔████╔██║███████║██████╔╝██║███████║\n");
	printf("╚════██║██╔══██║██╔══██║██║███╗██║██╔══██║██╔══██╗██║╚██╔╝██║██╔══██║██╔══██╗██║██╔══██║\n");
	printf("███████║██║  ██║██║  ██║╚███╔███╔╝██║  ██║██║  ██║██║ ╚═╝ ██║██║  ██║██║  ██║██║██║  ██║\n");
	printf("╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═╝\n"RESET);
	printf(VERDE"\n\n---------------------------------------------------------------------------------------------------------\n\n"RESET);
}

void lptela() {
	system("clear");
}

int main() {
	senha[0] = 12345;
	i[3] = 0;

	carregarpdd();
	if (carregou == 0) {
		iniciargasto();
	}
	qtd2[0] = qtd[2];

	do {
		lptela();
		logo();
		printf(AMARELO_LIMAO"[1] Fazer pedido\n");
		printf("[2] Gerenciar pedido\n");
		printf("[3] Finalizar\n");
		printf("[4] Sair\n");
		printf("[5] Admnistração\n");
		scanf("%d", &menu[0]);

		switch (menu[0]) {

		/* ============================== CASE 1 ============================== */
		case 1:
			lptela();
			printf(VERDE"\n\n-------------------------------------------------------------"VERDE_VIBRANTE "CARDÁPIO" VERDE "-------------------------------------------------------------\n\n");


			for (int d = 0; d < qtd[1]; d++) {
				printf(VERDE"\n=============== %s ===============\n", departamento[d]);

				for (int k = 0; k < qtd[0]; k++) {
					if (strcmp(tipos[k], departamento[d]) == 0) {
						printf(VERDE"[%-3d] |" AZUL " %-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |\n", k + 1, produtos[k], precos[k]);

					}
				}

			}
			scanf("%d", &menu[1]);

			if (menu[1] < 1 || menu[1] > qtd[0]) {
				lptela();
				printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
				printf(VERMELHO"Opção inexistente seu imbecil");
				printf(VERDE"\n----------------------------------------------------------------------------------\n");
				sleep(3);
			}
			else {
				lptela();
				printf(AMARELO"\n\n Deseja adicionar quantas unidades de %s?(numeros igual e menor que 0 cancelam o pedido)\n", produtos[menu[1] - 1]);
				scanf("%d", &quantidade[0]);
				if (quantidade[0] > 6) {
					printf(VERMELHO"\n\nValor alterado para o limite(6).\n");
					quantidade[0] = 6;
					sleep(1);
				}
				if (quantidade[0] <= 0) {
					lptela();
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					printf(VERMELHO"Cancelado");
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					sleep(2);
				}
				else if (baixaestoque(menu[1] - 1, quantidade[0]) == 0) {
					lptela();
					printf(VERMELHO"\nEstoque insuficiente de %s para essa quantidade.\n", estoque[faltou]);
					sleep(2);
				}
				else {
					lptela();
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					printf(VERDE_VIBRANTE"%d "AZUL" %s " AMARELO_LIMAO "Adicionado(s) ao carrinho\n", quantidade[0], produtos[menu[1] - 1]);
					printf(VERDE"----------------------------------------------------------------------------------\n");
					for (int k = 0; k < quantidade[0]; k++) {
						strcpy(carrinho[qtd[2]][qtd1[qtd[2]]], produtos[menu[1] - 1]);
						cprecos[qtd[2]][qtd1[qtd[2]]] = precos[menu[1] - 1];
						qtd1[qtd[2]]++;
					}
					sleep(2);
				}
			}
			menu[0] = 0;
			break;

		/* ============================== CASE 2 ============================== */
		case 2:
			if (qtd1[qtd[2]] == 0) {
				menu[0] = 0;
				break;
			}
			lptela();
			printf(VERDE_VIBRANTE"------------------------------------------------------------------------------------------------------\n");
			printf(AMARELO_LIMAO"                  Produtos que deseja remover(0 ou negativo para voltar)                                   ");
			printf(VERDE_VIBRANTE"\n------------------------------------------------------------------------------------------------------\n");

			for (int k = 0; k < qtd1[qtd[2]]; k++) {
				printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
				printf(VERDE "[%-3d] "VERDE "| " AZUL "%-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |", k + 1, carrinho[qtd[2]][k], cprecos[qtd[2]][k]);
			}
			printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
			scanf("%d", &i[2]);

			if (i[2] <= 0) {
				lptela();
				printf("Voltando...\n");
				sleep(1);
			}
			else if (i[2] > qtd1[qtd[2]]) {
				lptela();
				printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
				printf(VERMELHO"Opção inexistente seu imbecil");
				printf(VERDE"\n----------------------------------------------------------------------------------\n");
				sleep(2);
			}
			else {
				int j = i[2] - 1;
				lptela();
				printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
				printf(AZUL"%s" AMARELO " Removido do carrinho", carrinho[qtd[2]][j]);
				printf(VERDE"\n----------------------------------------------------------------------------------\n");
				sleep(2);
				for (int o = j; o < qtd1[qtd[2]] - 1; o++) {
					strcpy(carrinho[qtd[2]][o], carrinho[qtd[2]][o + 1]);
					cprecos[qtd[2]][o] = cprecos[qtd[2]][o + 1];
				}
				qtd1[qtd[2]]--;
			}
			menu[0] = 0;
			break;

		/* ============================== CASE 3 ============================== */
		case 3:
			lptela();
			if (qtd1[qtd[2]] == 0) {
				printf(VERMELHO"\n\nCarrinho vazio.\n");
				sleep(2);
				menu[0] = 0;
				break;
			}
				lptela();
				printf("\nInforma seu nome: ");

				scanf(" %99[^\n]", nome[qtd[2]]);
				printf("\n\n----------------------------------------------------------------------------------\n");
				printf("%s é seu nome", nome[qtd[2]]);
				printf("\n\n----------------------------------------------------------------------------------\n");

            lptela();
			if (i[3] == 0) {
				for (int o = 0; o <= 1; o++) {
					lptela();
					printf(VERDE"\n\n------------------------------------------------------------------------------\n");
					printf(VERDE_VIBRANTE"1 para entrega e 0 para buscar/comer aqui");
					printf(VERDE"\n------------------------------------------------------------------------------\n");
					strcpy(bairroc[qtd[2]], bairro[36]);
					rua[qtd[2]][0][0] = '\0';
					scanf("%d", &numero[qtd[2]]);
					if (numero[qtd[2]] > 1 || numero[qtd[2]] < 0) {
						printf(VERMELHO"\ninexistente\n");
						sleep(1);
						o--;
					}
					else {
						break;
					}
				}


				if (numero[qtd[2]] == 1) {
					lptela();
					printf(VERDE_VIBRANTE"\nINFORME SEU BAIRRO\n");
					for (int k = 0; k < 36; k++) {
						printf(VERDE"[%-3d] | %-30s\n", k + 1, bairro[k]);
					}
					sleep(2);
					scanf("%d", &i[6]);
					i[6]--;
					if (i[6] < 0 || i[6] > 35) {
						lptela();
						printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
						printf(VERMELHO"Opção inexistente seu imbecil");
						printf(VERDE"\n----------------------------------------------------------------------------------\n");
						sleep(2);
						menu[0] = 0;
						break;
					}

					strcpy(bairroc[qtd[2]], bairro[i[6]]);

					lptela();
					printf("\n\n----------------------------------------------------------------------------------\n");
					printf("seu bairro é %s", bairroc[qtd[2]]);
					printf("\n\n----------------------------------------------------------------------------------\n");
					sleep(2);


					lptela();
					printf("\nInforma sua rua:");

					scanf(" %39[^\n]", rua[qtd[2]][0]);
					printf("\n\n----------------------------------------------------------------------------------\n");
					printf("%s é sua rua", rua[qtd[2]][0]);
					printf("\n\n----------------------------------------------------------------------------------\n");

					sleep(2);
					lptela();
					printf(VERDE"informe o numero de sua casa:\n");
					scanf("%d", &nurua[qtd[2]]);
					printf("\n\n----------------------------------------------------------------------------------\n");
					printf("%d é o numero de sua casa.", nurua[qtd[2]]);
					printf("\n\n----------------------------------------------------------------------------------\n");
					sleep(2);
				}
				i[3] = 1;
			}

			lptela();
			printf(AMARELO"\n\nEntrega:");
			if (numero[qtd[2]] == 1) {
				printf(" sim");
			}
			else {
				printf(" não");
			}
			printf("\nbairro: %s", bairroc[qtd[2]]);
			printf("\nrua: %s", rua[qtd[2]][0]);
			printf("\nnumero casa: %d", nurua[qtd[2]]);
			printf("\nnome: %s", nome[qtd[2]] );
			printf(VERDE"\n\n===========================================" VERDE_VIBRANTE "NOTA FISCAL" VERDE"===========================================");
			total[0][qtd[2]] = 0.00;
			for (int o = 0; o < qtd1[qtd[2]]; o++) {
				printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
				printf(VERDE"| " AZUL "%-30s" VERDE " | " VERMELHO "%-3.2f" VERDE " |", carrinho[qtd[2]][o], cprecos[qtd[2]][o]);
				total[0][qtd[2]] += cprecos[qtd[2]][o];
			}
			printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
			printf(VERDE_VIBRANTE"TOTAL : " VERMELHO "%-4.2f", total[0][qtd[2]]);
			printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
			printf(AMARELO_LIMAO"Digite 1 para confirmar o pedido, 0 para voltar ao menu ou qualquer outro para cancelar");
			scanf("%d", &i[4]);
			switch (i[4]) {
			case 1:
				qtd[2]++;
				i[3] = 0;

				lptela();
				printf("\n\n\n");
				printf(VERDE_VIBRANTE"██╗   ██╗ ██████╗ ██╗  ████████╗███████╗\n");
				printf("██║   ██║██╔═══██╗██║  ╚══██╔══╝██╔════╝\n");
				printf("██║   ██║██║   ██║██║     ██║   █████╗  \n");
				printf("╚██╗ ██╔╝██║   ██║██║     ██║   ██╔══╝  \n");
				printf(" ╚████╔╝ ╚██████╔╝███████╗██║   ███████╗\n");
				printf("  ╚═══╝   ╚═════╝ ╚══════╝╚═╝   ╚══════╝\n");
				printf("\n");
				printf(AZUL"███████╗███████╗███╗   ███╗██████╗ ██████╗ ███████╗\n");
				printf("██╔════╝██╔════╝████╗ ████║██╔══██╗██╔══██╗██╔════╝\n");
				printf("███████╗█████╗  ██╔████╔██║██████╔╝██████╔╝█████╗  \n");
				printf("╚════██║██╔══╝  ██║╚██╔╝██║██╔═══╝ ██╔══██╗██╔══╝  \n");
				printf("███████║███████╗██║ ╚═╝ ██║██║     ██║  ██║███████╗\n");
				printf("╚══════╝╚══════╝╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝╚══════╝\n");
				sleep(3);
				break;

			case 0:
				lptela();
				total[0][qtd[2]] = 0.00;
				printf("\n\nVoltando");
				sleep(1);
				break;

			default:
				cancelapdd();
				i[3] = 0;
				lptela();
				printf(VERMELHO"\n\nPedido cancelado.\n");
				sleep(2);
				break;
			}
			menu[0] = 0;
			break;

		/* ============================== CASE 4 ============================== */
		case 4:
			lptela();
			printf(VERDE"\n\n\n-------------------------------------------------------------------------------\n");
			printf(VERMELHO"CERTEZA QUE DESEJA SAIR?(1 sim, qualquer não)");
			printf(VERDE"\n-------------------------------------------------------------------------------\n");
			scanf("%d", &i[1]);
			switch (i[1]) {
			case 1:
				break;

			default:
				menu[0] = 0;
				printf(VERDE_VIBRANTE"\n\n\nVoltando...\n");
				sleep(2);
				break;
			}
			break;

		/* ============================== CASE 5 ============================== */
		case 5:
			lptela();
			printf(AMARELO_LIMAO"0 Para voltar.\nDigite a senha: ");
			scanf("%d", &senha[1]);
			if ( senha[1] == 0) {
			    printf(VERDE_VIBRANTE"Voltando...\n\n");
			    menu[0] = 0;
			    break;
			}
			menu[0] = 1;
			do {
				lptela();
				switch (senha[1]) {

				case 12345:
					logo();
					printf(AMARELO_LIMAO"[1] Adicionar produtos\n");
					printf("[2] Ver vendas\n");
					printf("[3] Gerenciar estoque\n");
					printf("[4] Adicionar departamento\n");
					printf("[5] Remover produto\n");
					printf("[6] Remover departamento\n");
					printf("[7] Sair\n");
					scanf("%d", &menu[4]);
					switch (menu[4]) {

					/* ---------- ADICIONAR PRODUTOS / ALTERAR GASTO ---------- */
					case 1:
						lptela();
						printf(AMARELO_LIMAO"[1] Alterar gasto de um produto\n");
						printf("[2] Novo produto\n");
						printf("[0] Voltar\n");
						scanf("%d", &menu[10]);

						if (menu[10] == 1) {
							do {
								lptela();
								printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
								printf(AMARELO_LIMAO"Produto que deseja alterar o gasto (0 para voltar):\n");
								for (int k = 0; k < qtd[0]; k++) {
									printf(VERDE"[%-3d] | %s\n", k + 1, produtos[k]);
								}
								scanf("%d", &menu[11]);

								if (menu[11] >= 1 && menu[11] <= qtd[0]) {
									do {
										lptela();
										printf(VERDE_VIBRANTE"Gasto atual:\n\n");
										mostrargasto(menu[11] - 1);
										printf(VERDE"\n----------------------------------------------------------------------------------\n");
										for (int k = 0; k < qtdst[0]; k++) {
											printf(VERDE"[%-3d] | %-20s (%s)\n", k + 1, estoque[k], tipoe[k]);
										}
										printf(AMARELO_LIMAO"\nItem do estoque (0 para voltar): ");
										scanf("%d", &menu[12]);

										if (menu[12] >= 1 && menu[12] <= qtdst[0]) {
											printf("Quanto %s gasta de %s por unidade (0 tira da receita): ", produtos[menu[11] - 1], estoque[menu[12] - 1]);
											scanf("%d", &novaqtd);

											if (novaqtd < 0) {
												printf(VERMELHO"\nValor inválido.\n");
												sleep(2);
											}
											else {
												gasto[menu[11] - 1][menu[12] - 1] = novaqtd;
												printf(VERDE_VIBRANTE"\nGasto atualizado!\n");
												sleep(1);
											}
										}
										else if (menu[12] != 0) {
											printf(VERMELHO"\nItem inexistente.\n");
											sleep(2);
										}
									} while (menu[12] != 0);
								}
								else if (menu[11] != 0) {
									printf(VERMELHO"\nProduto inexistente.\n");
									sleep(2);
								}
							} while (menu[11] != 0);
						}
						else if (menu[10] == 2) {
							lptela();
							printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
							printf(AMARELO_LIMAO"Escolha o departamento (0 para voltar):\n");
							for (int k = 0; k < qtd[1]; k++) {
								printf(VERDE"[%-3d] | %s\n", k + 1, departamento[k]);
							}
							printf(VERDE"----------------------------------------------------------------------------------\n");
							scanf("%d", &menu[5]);

							if (menu[5] == 0) {
								printf(VERDE_VIBRANTE"\nVoltando...\n");
								sleep(1);
							}
							else if (menu[5] < 0 || menu[5] > qtd[1]) {
								printf(VERMELHO"\nDepartamento inexistente.\n");
								sleep(2);
							}
							else {
								printf(AMARELO_LIMAO"\nNome do produto: ");
								scanf(" %49[^\n]", novoprod);

								int existe = 0;
								for (int k = 0; k < qtd[0]; k++) {
									if (strcmp(produtos[k], novoprod) == 0) {
										existe = 1;
									}
								}

								if (existe == 1) {
									printf(VERMELHO"\nEsse produto já existe.\n");
									sleep(2);
								}
								else {
									printf(AMARELO_LIMAO"Preço: ");
									scanf("%f", &novopreco);

									if (novopreco <= 0) {
										printf(VERMELHO"\nPreço inválido.\n");
										sleep(2);
									}
									else {
										strcpy(produtos[qtd[0]], novoprod);
										strcpy(tipos[qtd[0]], departamento[menu[5] - 1]);
										precos[qtd[0]] = novopreco;
										qtd[0]++;
										printf(VERDE_VIBRANTE"\n%s adicionado em %s!\n", novoprod, tipos[qtd[0] - 1]);
										sleep(2);
									}
								}
							}
						}
						menu[0] = 1;
						break;

					case 2:
						lptela();
						printf(VERDE_VIBRANTE"------------------------------------------------=Vendas=------------------------------------------------");

						for (int k = 0; k < qtd[2]; k++) {
							printf(VERDE"\n\n\n================================= Pedido n°: %d =================================\n", k+1);
							printf("Entrega:");
							if (numero[k] == 1) {
								printf(" sim \n");
							}
							else {
								printf(" não \n");
							}

							printf("Bairro: %s\n", bairroc[k]);
							printf("Rua: %s\n", rua[k][0]);
							printf("Numero casa: %d", nurua[k]);
							printf("\nnome: %s", nome[k] );
							for (int o = 0; o < qtd1[k]; o++) {
								printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
								printf(VERDE"| " AZUL "%-30s" VERDE " | " VERMELHO "%-3.2f" VERDE " |", carrinho[k][o], cprecos[k][o]);
							}
							printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
							printf("Total: %.2f", total[0][k]);
						}
						printf(AMARELO_LIMAO"\n\nPressione qualquer para voltar...");
                        scanf("%s", outro[0]);
						menu[0] = 1;
						break;

					/* ---------- GERENCIAR ESTOQUE ---------- */
					case 3:
						do {
							lptela();
							printf(VERDE_VIBRANTE"-------------------------------------------=Estoque=-------------------------------------------\n\n");
							for (int k = 0; k < qtdst[0]; k++) {
								printf(VERDE"[%-3d] | " AZUL "%-20s" VERDE " | " AMARELO_LIMAO "%6d %s\n", k + 1, estoque[k], quantosst[k], tipoe[k]);
							}
							printf(AMARELO_LIMAO"\n[1] Adicionar quantidade a um item\n");
							printf("[2] Cadastrar item novo\n");
							printf("[0] Voltar\n");
							scanf("%d", &menu[8]);

							if (menu[8] == 1) {
								printf("Numero do item: ");
								scanf("%d", &menu[9]);

								if (menu[9] < 1 || menu[9] > qtdst[0]) {
									printf(VERMELHO"\nItem inexistente.\n");
									sleep(2);
								}
								else {
									int limite = 10000;
									if (strcmp(tipoe[menu[9] - 1], "un") == 0) {
										limite = 1000;
									}
									printf("Quanto adicionar de %s (maximo %d %s): ", estoque[menu[9] - 1], limite, tipoe[menu[9] - 1]);
									scanf("%d", &novaqtd);

									if (novaqtd <= 0 || novaqtd > limite) {
										printf(VERMELHO"\nValor inválido.\n");
										sleep(2);
									}
									else {
										quantosst[menu[9] - 1] += novaqtd;
										printf(VERDE_VIBRANTE"\n%d %s adicionado(s) em %s!\n", novaqtd, tipoe[menu[9] - 1], estoque[menu[9] - 1]);
										sleep(2);
									}
								}
							}
							else if (menu[8] == 2) {
								printf("Nome do novo item: ");
								scanf(" %39[^\n]", novoitem);

								int existe = 0;
								for (int k = 0; k < qtdst[0]; k++) {
									if (strcmp(estoque[k], novoitem) == 0) {
										existe = 1;
									}
								}

								if (existe == 1) {
									printf(VERMELHO"\nEsse item já existe.\n");
									sleep(2);
								}
								else {
									printf("Unidade (1: un, 2: g, 3: ml): ");
									scanf("%d", &menu[9]);

									if (menu[9] != 1 && menu[9] != 2 && menu[9] !=3 ) {
										printf(VERMELHO"\nUnidade inválida.\n");
										sleep(2);
									}
									else {
										int limite = 10000;
										if (menu[9] == 1) {
											limite = 1000;
										}
										printf("Quantidade inicial (maximo %d): ", limite);
										scanf("%d", &novaqtd);

										if (novaqtd <= 0 || novaqtd > limite) {
											printf(VERMELHO"\nValor inválido.\n");
											sleep(2);
										}
										else {
											strcpy(estoque[qtdst[0]], novoitem);
											quantosst[qtdst[0]] = novaqtd;
											if (menu[9] == 1) {
												strcpy(tipoe[qtdst[0]], "un");
											}
											else if ( menu[9] == 2 ) {
												strcpy(tipoe[qtdst[0]], "g");
											}
											else if ( menu[9] == 3 ) {
											    strcpy(tipoe[qtdst[0]], "ml");
											    
											}
											qtdst[0]++;
											printf(VERDE_VIBRANTE"\n%s cadastrado!\n", novoitem);
											sleep(2);
										}
									}
								}
							}
							salvarpdd();
						} while (menu[8] == 1 || menu[8] == 2);
						menu[0] = 1;
						break;

					/* ---------- ADICIONAR DEPARTAMENTO ---------- */
					case 4:
						lptela();
						printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
						printf(AMARELO_LIMAO"Departamentos atuais:\n");
						for (int k = 0; k < qtd[1]; k++) {
							printf(VERDE"[%-3d] | %s\n", k + 1, departamento[k]);
						}
						printf(VERDE"----------------------------------------------------------------------------------\n");
						printf(AMARELO_LIMAO"Nome do novo departamento (0 para voltar): ");
						scanf(" %29[^\n]", novodep);

						if (strcmp(novodep, "0") == 0) {
							printf(VERDE_VIBRANTE"\nVoltando...\n");
							sleep(1);
						}
						else if (qtd[1] >= 1000) {
							printf(VERMELHO"\nLimite de departamentos atingido.\n");
							sleep(2);
						}
						else {
							int existe = 0;
							for (int k = 0; k < qtd[1]; k++) {
								if (strcmp(departamento[k], novodep) == 0) {
									existe = 1;
								}
							}
							if (existe == 1) {
								printf(VERMELHO"\nEsse departamento já existe.\n");
								sleep(2);
							}
							else {
								strcpy(departamento[qtd[1]], novodep);
								qtd[1]++;
								printf(VERDE_VIBRANTE"\n%s adicionado com sucesso!\n", novodep);
								sleep(2);
							}
						}
						menu[0] = 1;
						break;

					/* ---------- REMOVER PRODUTO ---------- */
					case 5:
						lptela();
						printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
						printf(AMARELO_LIMAO"Produto que deseja remover (0 para voltar):\n");
						for (int d = 0; d < qtd[1]; d++) {
							printf(VERDE"\n=============== %s ===============\n", departamento[d]);
							for (int k = 0; k < qtd[0]; k++) {
								if (strcmp(tipos[k], departamento[d]) == 0) {
									printf(VERDE"[%-3d] |" AZUL " %-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |\n", k + 1, produtos[k], precos[k]);
								}
							}
						}
						scanf("%d", &menu[6]);

						if (menu[6] == 0) {
							printf(VERDE_VIBRANTE"\nVoltando...\n");
							sleep(1);
						}
						else if (menu[6] < 0 || menu[6] > qtd[0]) {
							printf(VERMELHO"\nProduto inexistente.\n");
							sleep(2);
						}
						else {
							printf(AMARELO"\nRemover %s? (1 sim, qualquer outro cancela): ", produtos[menu[6] - 1]);
							scanf("%d", &menu[7]);
							if (menu[7] == 1) {
								int j = menu[6] - 1;
								printf(VERDE_VIBRANTE"\n%s removido!\n", produtos[j]);
								for (int o = j; o < qtd[0] - 1; o++) {
									strcpy(produtos[o], produtos[o + 1]);
									strcpy(tipos[o], tipos[o + 1]);
									precos[o] = precos[o + 1];
									for (int e = 0; e < qtdst[0]; e++) {
										gasto[o][e] = gasto[o + 1][e];
									}
								}
								for (int e = 0; e < qtdst[0]; e++) {
									gasto[qtd[0] - 1][e] = 0;
								}
								qtd[0]--;
							}
							else {
								printf(VERMELHO"\nCancelado.\n");
							}
							sleep(2);
						}
						menu[0] = 1;
						break;

					/* ---------- REMOVER DEPARTAMENTO ---------- */
					case 6:
						lptela();
						printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
						printf(AMARELO_LIMAO"Departamento que deseja remover (0 para voltar):\n");
						for (int k = 0; k < qtd[1]; k++) {
							printf(VERDE"[%-3d] | %s\n", k + 1, departamento[k]);
						}
						printf(VERDE"----------------------------------------------------------------------------------\n");
						scanf("%d", &menu[6]);

						if (menu[6] == 0) {
							printf(VERDE_VIBRANTE"\nVoltando...\n");
							sleep(1);
						}
						else if (menu[6] < 0 || menu[6] > qtd[1]) {
							printf(VERMELHO"\nDepartamento inexistente.\n");
							sleep(2);
						}
						else {
							int usado = 0;
							for (int k = 0; k < qtd[0]; k++) {
								if (strcmp(tipos[k], departamento[menu[6] - 1]) == 0) {
									usado = 1;
								}
							}
							if (usado == 1) {
								printf(VERMELHO"\nEsse departamento ainda tem produtos. Remova os produtos primeiro.\n");
								sleep(3);
							}
							else {
								printf(AMARELO"\nRemover %s? (1 sim, qualquer outro cancela): ", departamento[menu[6] - 1]);
								scanf("%d", &menu[7]);
								if (menu[7] == 1) {
									int j = menu[6] - 1;
									printf(VERDE_VIBRANTE"\n%s removido!\n", departamento[j]);
									for (int o = j; o < qtd[1] - 1; o++) {
										strcpy(departamento[o], departamento[o + 1]);
									}
									qtd[1]--;
								}
								else {
									printf(VERMELHO"\nCancelado.\n");
								}
								sleep(2);
							}
						}
						menu[0] = 1;
						break;

					default:
						menu[0] = 0;
						break;
					}
					break;

				default:
					sleep(2);
					menu[0] = 0;
					break;
				}
				salvarpdd();
			} while (menu[0] == 1);
			menu[0] = 0;
			break;

		/* ============================== DEFAULT ============================== */
		default:
			lptela();
			printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
			printf(VERMELHO"Opção inexistente seu imbecil");
			printf(VERDE"\n----------------------------------------------------------------------------------\n");
			sleep(2);
			menu[0] = 0;
			break;
		}

		salvarpdd();

	} while (menu[0] == 0);

	return 0;
}
