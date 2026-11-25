/* =====================================================================
   SISTEMA DE PEDIDOS - HAMOOD SHAWARMARIA
   ---------------------------------------------------------------------
   Como o programa funciona, em resumo:
   - O cliente monta um carrinho (menu 1), pode remover itens (menu 2)
     e finaliza o pedido (menu 3).
   - O admin (menu 5, senha 12345) gerencia produtos, estoque,
     departamentos e ve as vendas.
   - Tudo e salvo no arquivo dados.txt para nao perder nada ao fechar.

   IDEIA PRINCIPAL: "vetores paralelos".
   Varios vetores usam o MESMO indice para falar do mesmo objeto.
   Ex.: produtos[2], tipos[2] e precos[2] sao todos do produto 2.
   ===================================================================== */

#include <stdio.h>   // printf, scanf, fopen, fprintf, fscanf
#include <string.h>  // strcmp, strcpy
#include <stdlib.h>  // system("clear")
#include <unistd.h>  // sleep()

// ---------------------------------------------------------------------
// CORES: codigos ANSI. Quando voce imprime um desses textos, o terminal
// muda a cor de tudo que vier depois, ate aparecer outra cor ou o RESET.
// Os "38;5;N" usam a paleta de 256 cores do terminal.
// ---------------------------------------------------------------------
#define VERMELHO "\033[31m"
#define VERMELHO_ESCURO "\033[38;5;88m"

#define AZUL "\033[34m"
#define AZUL_ESCURO "\033[38;5;18m"
#define AZUL_MARINHO "\033[38;5;17m"

#define AMARELO "\033[33m"
#define AMARELO_LIMAO "\033[38;5;190m"

#define VERDE "\033[32m"
#define VERDE_VIBRANTE "\033[38;5;46m"

#define RESET "\033[0m"   // volta para a cor padrao do terminal

// =====================================================================
// VARIAVEIS GLOBAIS
// Ficam fora de qualquer funcao para que todas as funcoes e o main
// consigam ler e alterar.
// =====================================================================

int senha[2];            // senha[0] = senha correta (12345); senha[1] = a que o usuario digita
int numero[1000];        // numero[pedido]: 1 = entrega, 0 = buscar/comer no local
int numero_casa[1000];   // NAO e usada (quem guarda o numero da casa e o nurua)

// Lista de bairros para entrega. O ultimo ("N/A") e usado quando
// o pedido NAO e entrega (por isso o codigo usa bairro[36]).
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
char bairroc[1000][30];   // bairroc[pedido]: bairro escolhido em CADA pedido
char rua[1000][1][40];    // rua[pedido][0]: rua do pedido (o [1] do meio e so um "encaixe")
char nome[1000][100];     // nome[pedido]: nome do cliente de cada pedido

int quantidade[10];       // quantidade[0]: quantas unidades o cliente quer adicionar (case 1)
int i[10];                // variaveis auxiliares de menu, cada posicao tem um uso:
                          //   i[1] = confirma sair      i[2] = item do carrinho a remover
                          //   i[3] = 1 se ja pediu dados de entrega desse pedido
                          //   i[4] = confirmar/voltar/cancelar pedido
                          //   i[6] = bairro escolhido
int menu[20] = { 0 };     // variaveis de menu, cada posicao tem um uso:
                          //   menu[0] = menu principal      menu[1] = produto escolhido
                          //   menu[4] = menu do admin       menu[5] = departamento do novo produto
                          //   menu[6] = item a remover      menu[7] = confirmacao de remocao
                          //   menu[8] = menu do estoque     menu[9] = item/unidade do estoque
                          //   menu[10] = submenu "adicionar produtos"
                          //   menu[11] = produto cujo gasto sera alterado
                          //   menu[12] = item de estoque cujo gasto sera alterado

// Departamentos (categorias do cardapio). A quantidade atual fica em qtd[1].
char departamento[1000][30] = {
	"doce",
	"salgado",
	"bebida"
};
char novodep[30];         // nome do departamento novo que o admin digita

// ---------------- PRODUTOS (o que o cliente compra) ----------------
// produtos[k], tipos[k] e precos[k] sao do mesmo produto k.
char produtos[1000][50] = {
	"Shawarma misto",
	"Shawarma carne",
	"Shawarma frango",
	"Shawarma habib",
	"Coca Cola 2L",
	"Suco fruta 2L",
	"Agua com gas"
};
// tipos[k] = em qual DEPARTAMENTO o produto k esta (precisa ser igual ao nome do departamento)
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

// ---------------- ESTOQUE (os ingredientes e itens) ----------------
// estoque[e], quantosst[e] e tipoe[e] sao do mesmo item e.
char estoque[1000][40] = {           // nome do item
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

int quantosst[1000] = {              // quanto TEM de cada item agora
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

// Unidade de cada item: "un" (unidade), "g" (gramas) ou "ml".
// Tamanho 3 porque cabe 2 letras + o '\0' que termina a string.
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
char novoprod[50];       // nome do produto novo digitado pelo admin
char novoitem[40];       // nome do item de estoque novo digitado pelo admin
float novopreco;         // preco do produto novo
int novaqtd;             // quantidade digitada (estoque ou gasto)
int dst[1000][1000];     // NAO e usada
int qtdst[5] = { 11 };   // qtdst[0] = quantos itens existem no estoque (comeca com 11)
int qtd1[1000];          // qtd1[pedido] = quantos itens tem no carrinho daquele pedido
float total[2][1000];    // total[0][pedido] = valor total do pedido
// qtd[0] = quantos produtos existem (comeca com 7)
// qtd[1] = quantos departamentos existem (comeca com 3)
// qtd[2] = numero de pedidos ja FINALIZADOS. Tambem e o indice do pedido
//          ABERTO no momento (por isso aparece em carrinho[qtd[2]] etc.)
// qtd[3] = NAO e usada
int qtd[4] = {7, 3, 0, 0};
int qtd2[4];             // qtd2[0] guarda uma copia de qtd[2]; o resto nao e usado
char carrinho[1000][1000][50];   // carrinho[pedido][item] = NOME do produto no carrinho
float cprecos[1000][1000];       // cprecos[pedido][item] = preco daquele item no carrinho
int nurua[1000];                 // nurua[pedido] = numero da casa para entrega

// Cancela o pedido aberto: zera o total e esvazia o carrinho.
// (os nomes continuam na memoria, mas qtd1 = 0 faz o programa ignorar)
void cancelapdd() {
	total[0][qtd[2]] = 0.00;
	qtd1[qtd[2]] = 0;
}
char outro[1][1000];     // buffer usado so para "pressione qualquer tecla" no admin
int selec;               // NAO e usada
int qtdf = 1;            // NAO e usada

// ---------------- RECEITAS ----------------
// gasto[p][e] = quanto do item de estoque "e" o produto "p" consome
// POR UNIDADE vendida. Linha = produto, coluna = item de estoque.
// Exemplo: gasto[0][1] = 50 -> o Shawarma misto gasta 50g de carne bovina.
// Zero significa que o produto nao usa aquele item.
int gasto[1000][1000];
int faltou;              // guarda o indice do item que faltou (para mostrar o nome na mensagem)
int carregou = 0;        // vira 1 se o dados.txt existia e foi carregado

// Preenche as receitas iniciais. So e chamada quando NAO existe dados.txt
// (primeira vez que o programa roda). Depois disso, as receitas vem do arquivo.
void iniciargasto() {
	// Shawarma misto (produto 0)
	gasto[0][0] = 1;      // 1 pao arabe
	gasto[0][1] = 50;     // 50g carne bovina
	gasto[0][2] = 50;     // 50g carne de frango
	gasto[0][3] = 20;     // 20g salada
	gasto[0][10] = 1;     // 1 guardanapo

	// Shawarma carne (produto 1)
	gasto[1][0] = 1;
	gasto[1][1] = 100;
	gasto[1][3] = 20;
	gasto[1][10] = 1;

	// Shawarma frango (produto 2)
	gasto[2][0] = 1;
	gasto[2][2] = 100;
	gasto[2][3] = 20;
	gasto[2][10] = 1;

	// Shawarma habib (produto 3): sem pao, e carne + batata + molho
	gasto[3][1] = 125;
	gasto[3][3] = 20;
	gasto[3][4] = 40;
	gasto[3][5] = 10;

	// Bebidas: cada uma consome 1 unidade do item de estoque correspondente
	gasto[4][7] = 1;      // Coca Cola 2L -> "Coca cola 2l"
	gasto[5][8] = 1;      // Suco fruta 2L -> "Suco fruta 2l"
	gasto[6][9] = 1;      // Agua com gas -> "Agua com gas"
}

// Mostra na tela a receita do produto p (so os itens com gasto maior que 0).
// Usada no menu admin ao alterar o gasto de um produto.
void mostrargasto(int p) {
	int achou = 0;        // vira 1 se encontrar pelo menos um item na receita
	printf(AZUL"%s\n", produtos[p]);
	for (int e = 0; e < qtdst[0]; e++) {
		if (gasto[p][e] > 0) {
			// %-20s = texto alinhado a esquerda com 20 espacos de largura
			printf(VERDE"   %-20s %d %s\n", estoque[e], gasto[p][e], tipoe[e]);
			achou = 1;
		}
	}
	if (achou == 0) {
		printf(AMARELO"   (sem gasto cadastrado)\n");
	}
}

/* ====================== CONTROLE DE ESTOQUE ====================== */
/* Regra do sistema:
   - Ao ADICIONAR no carrinho: so VERIFICA se tem estoque (nao desconta).
   - Ao CONFIRMAR o pedido: DESCONTA tudo de uma vez.
   Assim, remover item ou cancelar pedido nao precisa devolver estoque. */

// necessario[e] = quanto do item de estoque "e" o carrinho inteiro vai gastar
int necessario[1000];

// Soma o gasto de TODOS os produtos que estao no carrinho do pedido.
// O resultado fica no vetor necessario[].
void calculanecessario(int pedido) {
	// 1) zera o vetor para nao somar em cima de valores antigos
	for (int e = 0; e < qtdst[0]; e++) {
		necessario[e] = 0;
	}
	// 2) para cada item do carrinho...
	for (int o = 0; o < qtd1[pedido]; o++) {
		// ...descobre qual e o produto (o carrinho guarda so o NOME, entao
		// comparamos o nome com a lista de produtos usando strcmp)
		for (int p = 0; p < qtd[0]; p++) {
			if (strcmp(produtos[p], carrinho[pedido][o]) == 0) {
				// achou o produto: soma a receita dele em necessario[]
				for (int e = 0; e < qtdst[0]; e++) {
					necessario[e] += gasto[p][e];
				}
				break;   // ja achou, nao precisa continuar procurando
			}
		}
	}
}

// So VERIFICA (nao desconta): cabe mais q unidades do produto p no carrinho?
// Retorna 1 se cabe e 0 se nao cabe (e guarda em "faltou" o item que acabou).
int cabeNoEstoque(int pedido, int p, int q) {
	calculanecessario(pedido);   // o que o carrinho ja gasta
	for (int e = 0; e < qtdst[0]; e++) {
		// o que o carrinho ja gasta + o que as novas q unidades gastariam
		// nao pode passar do que existe no estoque
		if (necessario[e] + gasto[p][e] * q > quantosst[e]) {
			faltou = e;
			return 0;
		}
	}
	return 1;
}

// DESCONTA o carrinho inteiro do estoque. E "tudo ou nada":
// primeiro verifica tudo, e so depois desconta.
// Retorna 1 se descontou e 0 se faltou algo (nesse caso nao desconta NADA).
int baixaestoque(int pedido) {
	calculanecessario(pedido);
	// ETAPA 1: verificar (sem alterar nada)
	for (int e = 0; e < qtdst[0]; e++) {
		if (necessario[e] > quantosst[e]) {
			faltou = e;
			return 0;
		}
	}
	// ETAPA 2: descontar (so chega aqui se tudo estava disponivel)
	for (int e = 0; e < qtdst[0]; e++) {
		quantosst[e] -= necessario[e];
	}
	return 1;
}

/* ======================================================================= */

// Funcao vazia (o for nao faz nada). Sobrou de uma ideia nao terminada.
void addproduto(int a) {
	for (int k = 0; k < qtdst[0]; k++) {
	}
}

// =====================================================================
// SALVAR / CARREGAR
// O arquivo dados.txt e escrito um valor por linha, numa ORDEM FIXA.
// salvarpdd() e carregarpdd() precisam seguir exatamente a mesma ordem.
// Se mudar a ordem de um, tem que mudar no outro.
// =====================================================================
void salvarpdd() {
	FILE *f;
	f = fopen("dados.txt", "w");   // "w" = cria/apaga e escreve do zero
	if (f == NULL) {
		return;                    // nao conseguiu abrir: sai sem salvar
	}

	// contadores gerais
	for (int k = 0; k < 4; k++) {
		fprintf(f, "%d\n", qtd[k]);
	}
	for (int k = 0; k < 4; k++) {
		fprintf(f, "%d\n", qtd2[k]);
	}
	fprintf(f, "%d\n", qtdst[0]);   // quantos itens de estoque
	fprintf(f, "%d\n", i[3]);       // se o pedido aberto ja tinha dados de entrega

	// departamentos
	for (int k = 0; k < qtd[1]; k++) {
		fprintf(f, "%s\n", departamento[k]);
	}

	// produtos: nome, departamento e preco
	for (int k = 0; k < qtd[0]; k++) {
		fprintf(f, "%s\n", produtos[k]);
		fprintf(f, "%s\n", tipos[k]);
		fprintf(f, "%.2f\n", precos[k]);   // %.2f = 2 casas decimais
	}

	// estoque: nome, quantidade e unidade
	for (int k = 0; k < qtdst[0]; k++) {
		fprintf(f, "%s\n", estoque[k]);
		fprintf(f, "%d\n", quantosst[k]);
		fprintf(f, "%s\n", tipoe[k]);
	}

	// receitas (tabela gasto, produto por produto)
	for (int p = 0; p < qtd[0]; p++) {
		for (int e = 0; e < qtdst[0]; e++) {
			fprintf(f, "%d\n", gasto[p][e]);
		}
	}

	// pedidos (inclui o pedido aberto, por isso <= qtd[2])
	for (int p = 0; p <= qtd[2]; p++) {
		fprintf(f, "%d\n", numero[p]);
		fprintf(f, "%d\n", nurua[p]);
		fprintf(f, "%.2f\n", total[0][p]);
		fprintf(f, "%s\n", nome[p]);
		fprintf(f, "%s\n", bairroc[p]);
		fprintf(f, "%s\n", rua[p][0]);
		fprintf(f, "%d\n", qtd1[p]);
		// itens do carrinho desse pedido
		for (int o = 0; o < qtd1[p]; o++) {
			fprintf(f, "%s\n", carrinho[p][o]);
			fprintf(f, "%.2f\n", cprecos[p][o]);
		}
	}

	fclose(f);   // fecha o arquivo (garante que tudo foi gravado)
}

// Le o dados.txt na MESMA ordem em que salvarpdd() escreveu.
// Detalhes de leitura:
//   %d%*c          le um numero e descarta 1 caractere (o '\n' do fim da linha)
//   %49[^\n]       le texto (com espacos) ate a quebra de linha, no maximo 49 letras
//   fscanf("%*c")  descarta o '\n' que sobrou depois do texto
// Antes de ler cada texto, o primeiro caractere e zerado ('\0') para que,
// se a leitura falhar, a string fique vazia em vez de lixo.
void carregarpdd() {
	FILE *f;
	f = fopen("dados.txt", "r");   // "r" = so leitura
	if (f == NULL) {
		return;                    // arquivo nao existe: usa os dados iniciais do codigo
	}
	carregou = 1;                  // avisa o main que carregou (para nao rodar iniciargasto)

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
		fscanf(f, "%2[^\n]", tipoe[k]);   // unidade: no maximo 2 letras (un, g, ml)
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

// Desenha o logo "HAMOOD SHAWARMARIA" em letras grandes (arte ASCII).
// Cada printf e uma linha do desenho.
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

// Limpa a tela do terminal (comando "clear" do Linux/Mac).
// No Windows seria system("cls").
void lptela() {
	system("clear");
}

// =====================================================================
// MAIN: o programa comeca aqui
// =====================================================================
int main() {
	senha[0] = 12345;   // senha do admin
	i[3] = 0;           // comeca sem dados de entrega preenchidos

	carregarpdd();              // tenta carregar o dados.txt
	if (carregou == 0) {
		iniciargasto();         // primeira vez: cria as receitas iniciais
	}
	qtd2[0] = qtd[2];

	// Loop do menu principal. Repete enquanto menu[0] == 0.
	// Quando o usuario escolhe "Sair" (4 + confirmar), menu[0] fica 4
	// e o loop termina.
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
		// FAZER PEDIDO: mostra o cardapio e adiciona produtos ao carrinho
		case 1:
			lptela();
			printf(VERDE"\n\n-------------------------------------------------------------"VERDE_VIBRANTE "CARDÁPIO" VERDE "-------------------------------------------------------------\n\n");

			// Mostra o cardapio agrupado por departamento:
			// para cada departamento, lista os produtos cujo "tipos" for igual ao nome dele
			for (int d = 0; d < qtd[1]; d++) {
				printf(VERDE"\n=============== %s ===============\n", departamento[d]);

				for (int k = 0; k < qtd[0]; k++) {
					if (strcmp(tipos[k], departamento[d]) == 0) {
						// k + 1 porque o cliente ve numeros a partir de 1 (o vetor comeca em 0)
						printf(VERDE"[%-3d] |" AZUL " %-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |\n", k + 1, produtos[k], precos[k]);

					}
				}

			}
			scanf("%d", &menu[1]);   // numero do produto escolhido

			// valida: precisa estar entre 1 e o total de produtos
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
				// limite de 6 unidades por vez
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
				// So VERIFICA o estoque (nao desconta). O desconto so acontece
				// quando o pedido for confirmado (case 3).
				// menu[1] - 1 = indice real do produto no vetor.
				else if (cabeNoEstoque(qtd[2], menu[1] - 1, quantidade[0]) == 0) {
					lptela();
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					printf(VERMELHO"%s fora de estoque para essa quantidade.", estoque[faltou]);
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					sleep(3);
				}
				else {
					lptela();
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					printf(VERDE_VIBRANTE"%d "AZUL" %s " AMARELO_LIMAO "Adicionado(s) ao carrinho\n", quantidade[0], produtos[menu[1] - 1]);
					printf(VERDE"----------------------------------------------------------------------------------\n");
					// Adiciona uma linha no carrinho para CADA unidade.
					// qtd[2] = pedido aberto; qtd1[qtd[2]] = proxima posicao livre do carrinho.
					for (int k = 0; k < quantidade[0]; k++) {
						strcpy(carrinho[qtd[2]][qtd1[qtd[2]]], produtos[menu[1] - 1]);
						cprecos[qtd[2]][qtd1[qtd[2]]] = precos[menu[1] - 1];
						qtd1[qtd[2]]++;   // carrinho ganhou 1 item
					}
					sleep(2);
				}
			}
			menu[0] = 0;   // 0 = volta para o menu principal
			break;

		/* ============================== CASE 2 ============================== */
		// GERENCIAR PEDIDO: lista o carrinho e permite remover um item
		case 2:
			// carrinho vazio: nao tem o que mostrar, volta direto
			if (qtd1[qtd[2]] == 0) {
				menu[0] = 0;
				break;
			}
			lptela();
			printf(VERDE_VIBRANTE"------------------------------------------------------------------------------------------------------\n");
			printf(AMARELO_LIMAO"                  Produtos que deseja remover(0 ou negativo para voltar)                                   ");
			printf(VERDE_VIBRANTE"\n------------------------------------------------------------------------------------------------------\n");

			// lista cada item do carrinho
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
				// numero maior que a quantidade de itens do carrinho
				lptela();
				printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
				printf(VERMELHO"Opção inexistente seu imbecil");
				printf(VERDE"\n----------------------------------------------------------------------------------\n");
				sleep(2);
			}
			else {
				int j = i[2] - 1;   // posicao real do item no vetor
				lptela();
				printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
				printf(AZUL"%s" AMARELO " Removido do carrinho", carrinho[qtd[2]][j]);
				printf(VERDE"\n----------------------------------------------------------------------------------\n");
				sleep(2);
				// Remove "puxando" todos os itens seguintes uma posicao para tras,
				// cobrindo o item removido.
				for (int o = j; o < qtd1[qtd[2]] - 1; o++) {
					strcpy(carrinho[qtd[2]][o], carrinho[qtd[2]][o + 1]);
					cprecos[qtd[2]][o] = cprecos[qtd[2]][o + 1];
				}
				qtd1[qtd[2]]--;   // carrinho ficou com 1 item a menos
			}
			menu[0] = 0;
			break;

		/* ============================== CASE 3 ============================== */
		// FINALIZAR: pede dados, mostra a nota fiscal e confirma o pedido
		case 3:
			lptela();
			// nao deixa finalizar com carrinho vazio
			if (qtd1[qtd[2]] == 0) {
				printf(VERMELHO"\n\nCarrinho vazio.\n");
				sleep(2);
				menu[0] = 0;
				break;
			}
				lptela();
				printf("\nInforma seu nome: ");

				// " %99[^\n]" : o espaco no inicio ignora enter/espacos sobrando,
				// e le ate 99 letras (com espacos) ate o enter
				scanf(" %99[^\n]", nome[qtd[2]]);
				printf("\n\n----------------------------------------------------------------------------------\n");
				printf("%s é seu nome", nome[qtd[2]]);
				printf("\n\n----------------------------------------------------------------------------------\n");

            lptela();
			// i[3] == 0 significa que ainda NAO perguntamos entrega/endereco
			// desse pedido. Depois de perguntar, vira 1 para nao repetir.
			if (i[3] == 0) {
				// Pergunta se e entrega (1) ou retirada (0). O for permite
				// repetir a pergunta se a pessoa digitar um valor invalido.
				for (int o = 0; o <= 1; o++) {
					lptela();
					printf(VERDE"\n\n------------------------------------------------------------------------------\n");
					printf(VERDE_VIBRANTE"1 para entrega e 0 para buscar/comer aqui");
					printf(VERDE"\n------------------------------------------------------------------------------\n");
					strcpy(bairroc[qtd[2]], bairro[36]);   // padrao: "N/A" (sem entrega)
					rua[qtd[2]][0][0] = '\0';              // rua vazia
					scanf("%d", &numero[qtd[2]]);
					if (numero[qtd[2]] > 1 || numero[qtd[2]] < 0) {
						printf(VERMELHO"\ninexistente\n");
						sleep(1);
						o--;   // "desconta" a volta para repetir a pergunta
					}
					else {
						break;   // valor valido: sai do for
					}
				}


				// Se for entrega, pede bairro, rua e numero da casa
				if (numero[qtd[2]] == 1) {
					lptela();
					printf(VERDE_VIBRANTE"\nINFORME SEU BAIRRO\n");
					for (int k = 0; k < 36; k++) {
						printf(VERDE"[%-3d] | %-30s\n", k + 1, bairro[k]);
					}
					sleep(2);
					scanf("%d", &i[6]);
					i[6]--;   // converte para indice do vetor (comeca em 0)
					if (i[6] < 0 || i[6] > 35) {
						lptela();
						printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
						printf(VERMELHO"Opção inexistente seu imbecil");
						printf(VERDE"\n----------------------------------------------------------------------------------\n");
						sleep(2);
						menu[0] = 0;
						break;   // bairro invalido: volta ao menu principal
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
				i[3] = 1;   // marca: dados de entrega ja preenchidos
			}

			// ---- Nota fiscal ----
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
			total[0][qtd[2]] = 0.00;   // zera o total para recalcular
			for (int o = 0; o < qtd1[qtd[2]]; o++) {
				printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
				printf(VERDE"| " AZUL "%-30s" VERDE " | " VERMELHO "%-3.2f" VERDE " |", carrinho[qtd[2]][o], cprecos[qtd[2]][o]);
				total[0][qtd[2]] += cprecos[qtd[2]][o];   // soma o preco de cada item
			}
			printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
			printf(VERDE_VIBRANTE"TOTAL : " VERMELHO "%-4.2f", total[0][qtd[2]]);
			printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
			printf(AMARELO_LIMAO"Digite 1 para confirmar o pedido, 0 para voltar ao menu ou qualquer outro para cancelar");
			scanf("%d", &i[4]);
			switch (i[4]) {
			case 1:
				// CONFIRMAR: aqui e o UNICO lugar onde o estoque e descontado de verdade.
				// Se faltar algo, avisa e NAO fecha o pedido (o break sai antes do qtd[2]++),
				// entao o carrinho continua aberto para o cliente ajustar.
				if (baixaestoque(qtd[2]) == 0) {
					lptela();
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					printf(VERMELHO"Pedido não confirmado: %s fora de estoque.\n", estoque[faltou]);
					printf(AMARELO"Remova itens do carrinho (opção 2) e tente finalizar novamente.");
					printf(VERDE"\n----------------------------------------------------------------------------------\n");
					sleep(4);
					break;
				}

				qtd[2]++;   // pedido finalizado: o proximo pedido sera um novo carrinho vazio
				i[3] = 0;   // o proximo pedido vai precisar perguntar a entrega de novo

				// mensagem "VOLTE SEMPRE" em arte ASCII
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
				// voltar ao menu sem confirmar (o carrinho continua como esta)
				lptela();
				total[0][qtd[2]] = 0.00;
				printf("\n\nVoltando");
				sleep(1);
				break;

			default:
				// qualquer outro numero: cancela o pedido e esvazia o carrinho
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
		// SAIR: pede confirmacao antes de encerrar
		case 4:
			lptela();
			printf(VERDE"\n\n\n-------------------------------------------------------------------------------\n");
			printf(VERMELHO"CERTEZA QUE DESEJA SAIR?(1 sim, qualquer não)");
			printf(VERDE"\n-------------------------------------------------------------------------------\n");
			scanf("%d", &i[1]);
			switch (i[1]) {
			case 1:
				break;   // menu[0] continua 4, entao o loop principal termina

			default:
				menu[0] = 0;   // nao quis sair: volta ao menu
				printf(VERDE_VIBRANTE"\n\n\nVoltando...\n");
				sleep(2);
				break;
			}
			break;

		/* ============================== CASE 5 ============================== */
		// ADMINISTRACAO: pede senha e abre o menu do admin
		case 5:
			lptela();
			printf(AMARELO_LIMAO"0 Para voltar.\nDigite a senha: ");
			scanf("%d", &senha[1]);
			if ( senha[1] == 0) {
			    printf(VERDE_VIBRANTE"Voltando...\n\n");
			    menu[0] = 0;
			    break;
			}
			menu[0] = 1;   // 1 = continua dentro do loop do admin
			// Loop do admin: repete enquanto menu[0] == 1.
			// Cada opcao termina com "menu[0] = 1" para continuar no admin;
			// a opcao 7 (ou invalida) usa "menu[0] = 0" para sair.
			do {
				lptela();
				// o switch compara a senha digitada com a senha correta
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
							// ALTERAR GASTO (receita) de um produto existente.
							// Dois loops: o de fora escolhe o produto, o de dentro
							// escolhe o item de estoque. 0 volta um nivel.
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
										mostrargasto(menu[11] - 1);   // mostra a receita atual
										printf(VERDE"\n----------------------------------------------------------------------------------\n");
										// lista todos os itens de estoque para escolher
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
												// grava na tabela: linha = produto, coluna = item
												gasto[menu[11] - 1][menu[12] - 1] = novaqtd;
												printf(VERDE_VIBRANTE"\nGasto atualizado!\n");
												sleep(1);
											}
										}
										else if (menu[12] != 0) {
											printf(VERMELHO"\nItem inexistente.\n");
											sleep(2);
										}
									} while (menu[12] != 0);   // repete ate digitar 0
								}
								else if (menu[11] != 0) {
									printf(VERMELHO"\nProduto inexistente.\n");
									sleep(2);
								}
							} while (menu[11] != 0);           // repete ate digitar 0
						}
						else if (menu[10] == 2) {
							// NOVO PRODUTO: escolhe departamento, nome e preco
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

								// confere se ja existe um produto com esse nome
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
										// grava o produto novo na primeira posicao livre (qtd[0])
										strcpy(produtos[qtd[0]], novoprod);
										strcpy(tipos[qtd[0]], departamento[menu[5] - 1]);
										precos[qtd[0]] = novopreco;
										qtd[0]++;   // agora existe 1 produto a mais
										printf(VERDE_VIBRANTE"\n%s adicionado em %s!\n", novoprod, tipos[qtd[0] - 1]);
										sleep(2);
									}
								}
							}
						}
						menu[0] = 1;   // continua no admin
						break;

					/* ---------- VER VENDAS ---------- */
					case 2:
						lptela();
						printf(VERDE_VIBRANTE"------------------------------------------------=Vendas=------------------------------------------------");

						// mostra todos os pedidos FINALIZADOS (de 0 ate qtd[2] - 1)
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
							// itens do pedido k
							for (int o = 0; o < qtd1[k]; o++) {
								printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
								printf(VERDE"| " AZUL "%-30s" VERDE " | " VERMELHO "%-3.2f" VERDE " |", carrinho[k][o], cprecos[k][o]);
							}
							printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
							printf("Total: %.2f", total[0][k]);
						}
						printf(AMARELO_LIMAO"\n\nPressione qualquer para voltar...");
                        scanf("%s", outro[0]);   // espera o usuario digitar algo + enter
						menu[0] = 1;
						break;

					/* ---------- GERENCIAR ESTOQUE ---------- */
					case 3:
						do {
							lptela();
							printf(VERDE_VIBRANTE"-------------------------------------------=Estoque=-------------------------------------------\n\n");
							// lista todos os itens com a quantidade atual
							for (int k = 0; k < qtdst[0]; k++) {
								printf(VERDE"[%-3d] | " AZUL "%-20s" VERDE " | " AMARELO_LIMAO "%6d %s\n", k + 1, estoque[k], quantosst[k], tipoe[k]);
							}
							printf(AMARELO_LIMAO"\n[1] Adicionar quantidade a um item\n");
							printf("[2] Cadastrar item novo\n");
							printf("[3] Remover item\n");
							printf("[0] Voltar\n");
							scanf("%d", &menu[8]);

							/* ----- [3] REMOVER ITEM DO ESTOQUE ----- */
							if (menu[8] == 3) {
								printf("Numero do item que deseja remover (0 para voltar): ");
								scanf("%d", &menu[9]);

								if (menu[9] == 0) {
									printf(VERDE_VIBRANTE"\nVoltando...\n");
									sleep(1);
								}
								else if (menu[9] < 0 || menu[9] > qtdst[0]) {
									printf(VERMELHO"\nItem inexistente.\n");
									sleep(2);
								}
								else {
									int j = menu[9] - 1;   // indice real do item
									int usado = 0;         // 1 se alguma receita usa esse item
									for (int p = 0; p < qtd[0]; p++) {
										if (gasto[p][j] > 0) {
											usado = 1;
										}
									}
									if (usado == 1) {
										printf(AMARELO"\nAtencao: esse item faz parte da receita de algum produto e sera retirado dela.\n");
									}
									printf(AMARELO"Remover %s? (1 sim, qualquer outro cancela): ", estoque[j]);
									scanf("%d", &menu[7]);
									if (menu[7] == 1) {
										printf(VERDE_VIBRANTE"\n%s removido!\n", estoque[j]);
										// Todo mundo depois do item removido "anda" uma casa
										// para tras: nome, quantidade, unidade E a coluna da
										// tabela gasto (para TODOS os produtos). Se a coluna
										// nao andasse junto, as receitas apontariam para os
										// itens errados.
										for (int o = j; o < qtdst[0] - 1; o++) {
											strcpy(estoque[o], estoque[o + 1]);
											quantosst[o] = quantosst[o + 1];
											strcpy(tipoe[o], tipoe[o + 1]);
											for (int p = 0; p < qtd[0]; p++) {
												gasto[p][o] = gasto[p][o + 1];
											}
										}
										// limpa a ultima posicao (que ficou duplicada)
										for (int p = 0; p < qtd[0]; p++) {
											gasto[p][qtdst[0] - 1] = 0;
										}
										estoque[qtdst[0] - 1][0] = '\0';
										quantosst[qtdst[0] - 1] = 0;
										tipoe[qtdst[0] - 1][0] = '\0';
										qtdst[0]--;   // agora existe 1 item a menos
									}
									else {
										printf(VERMELHO"\nCancelado.\n");
									}
									sleep(2);
								}
							}

							/* ----- [1] ADICIONAR QUANTIDADE A UM ITEM ----- */
							if (menu[8] == 1) {
								printf("Numero do item: ");
								scanf("%d", &menu[9]);

								if (menu[9] < 1 || menu[9] > qtdst[0]) {
									printf(VERMELHO"\nItem inexistente.\n");
									sleep(2);
								}
								else {
									// limite por vez: 1000 para "un" e 10000 para g/ml
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
										quantosst[menu[9] - 1] += novaqtd;   // soma ao que ja tinha
										printf(VERDE_VIBRANTE"\n%d %s adicionado(s) em %s!\n", novaqtd, tipoe[menu[9] - 1], estoque[menu[9] - 1]);
										sleep(2);
									}
								}
							}
							/* ----- [2] CADASTRAR ITEM NOVO ----- */
							else if (menu[8] == 2) {
								printf("Nome do novo item: ");
								scanf(" %39[^\n]", novoitem);

								// confere se ja existe item com esse nome
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

									// aceita 1, 2 ou 3
									if (menu[9] < 1 || menu[9] > 3) {
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
											// grava o item novo na primeira posicao livre (qtdst[0])
											strcpy(estoque[qtdst[0]], novoitem);
											quantosst[qtdst[0]] = novaqtd;
											// traduz a opcao numerica para o texto da unidade
											if (menu[9] == 1) {
												strcpy(tipoe[qtdst[0]], "un");
											}
											else if ( menu[9] == 2 ) {
												strcpy(tipoe[qtdst[0]], "g");
											}
											else if ( menu[9] == 3 ) {
											    strcpy(tipoe[qtdst[0]], "ml");
											    
											}
											qtdst[0]++;   // agora existe 1 item a mais
											printf(VERDE_VIBRANTE"\n%s cadastrado!\n", novoitem);
											sleep(2);
										}
									}
								}
							}
							salvarpdd();   // salva a cada volta, para nao perder alteracoes
						} while (menu[8] == 1 || menu[8] == 2 || menu[8] == 3);   // 0 (ou outro) sai
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

						// aqui o "0" e lido como TEXTO, por isso usa strcmp
						if (strcmp(novodep, "0") == 0) {
							printf(VERDE_VIBRANTE"\nVoltando...\n");
							sleep(1);
						}
						else if (qtd[1] >= 1000) {
							printf(VERMELHO"\nLimite de departamentos atingido.\n");
							sleep(2);
						}
						else {
							// confere se ja existe departamento com esse nome
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
								qtd[1]++;   // agora existe 1 departamento a mais
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
						// lista os produtos agrupados por departamento
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
								int j = menu[6] - 1;   // indice real do produto
								printf(VERDE_VIBRANTE"\n%s removido!\n", produtos[j]);
								// Todo mundo depois do produto removido anda uma casa para
								// tras: nome, departamento, preco E a linha da tabela gasto
								// (a receita anda junto com o produto).
								for (int o = j; o < qtd[0] - 1; o++) {
									strcpy(produtos[o], produtos[o + 1]);
									strcpy(tipos[o], tipos[o + 1]);
									precos[o] = precos[o + 1];
									for (int e = 0; e < qtdst[0]; e++) {
										gasto[o][e] = gasto[o + 1][e];
									}
								}
								// limpa a receita da ultima posicao (que ficou duplicada)
								for (int e = 0; e < qtdst[0]; e++) {
									gasto[qtd[0] - 1][e] = 0;
								}
								qtd[0]--;   // agora existe 1 produto a menos
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
							// so deixa remover se nenhum produto estiver nesse departamento
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
									// puxa os departamentos seguintes uma casa para tras
									for (int o = j; o < qtd[1] - 1; o++) {
										strcpy(departamento[o], departamento[o + 1]);
									}
									qtd[1]--;   // agora existe 1 departamento a menos
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
						// opcao 7 (Sair) ou qualquer numero invalido: sai do admin
						menu[0] = 0;
						break;
					}
					break;

				default:
					// senha errada: espera 2 segundos e volta ao menu principal
					sleep(2);
					menu[0] = 0;
					break;
				}
				salvarpdd();   // salva depois de cada acao do admin
			} while (menu[0] == 1);   // continua no admin enquanto menu[0] for 1
			menu[0] = 0;   // saiu do admin: volta ao menu principal
			break;

		/* ============================== DEFAULT ============================== */
		// qualquer opcao que nao seja 1 a 5 no menu principal
		default:
			lptela();
			printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
			printf(VERMELHO"Opção inexistente seu imbecil");
			printf(VERDE"\n----------------------------------------------------------------------------------\n");
			sleep(2);
			menu[0] = 0;
			break;
		}

		salvarpdd();   // salva depois de cada volta do menu principal

	} while (menu[0] == 0);   // repete ate o usuario escolher sair

	return 0;   // fim do programa
}
