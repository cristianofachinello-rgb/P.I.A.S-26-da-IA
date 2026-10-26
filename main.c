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
char bairroc[300];
char rua[1000][1][40];



int quantidade[10];
int i[10];
int menu[20] = { 0 };
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


float total[2][1000];
int qtd[4] = {7, 0, 0, 0};
int qtd2[4];
char carrinho[1000][1000][50];
float cpreços[1000][1000];
void cancelapdd() {
    total[0][qtd[2]] = 0.00;
    qtd[1] = 0;
    

}
 
void intsalvar() {
    FILE *f = fopen("ints.txt", "w");
    for ( int i = 0; i < 4; i++ ) {
    fprintf( f, "%d %d", qtd[i], qtd2[i]);
    
    }
    for ( int i = 0; i < qtd[2]; i++) {
        fprintf(f, "%f", total[0][i]);
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
void lptela(){
    system("clear");
}


int main() {
    senha[0] = 12345;
    i[3] = 0;
    qtd2[0] = qtd[2];

do {
    intsalvar();
    lptela();
    logo();
    printf(AMARELO_LIMAO"[1] Fazer pedido\n");
    printf("[2] Gerenciar pedido\n");
    printf("[3] Finalizar\n");
    printf("[4] Sair\n");
    printf("[5] Admnistração\n");
    scanf("%d", &menu[0]);
    switch ( menu[0] ) {
    
    case 1:
    lptela();
     printf(VERDE"\n\n-------------------------------------------------------------"VERDE_VIBRANTE "CARDÁPIO" VERDE "-------------------------------------------------------------\n\n");
     printf(VERDE"===============SALGADOS===============\n");
     for (int i = 0; i < qtd[0]; i++) {
         if (strcmp(tipos[i], "salgado") == 0) {
          
         printf(VERDE"[%-3d] |" AZUL " %-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |\n", i+1, produtos[i], precos[i] );
         
         
         }
     
    }
     printf("\n\n===============BEBIDAS================\n");
     for ( int i = 0; i < qtd[0]; i++){
         if ( strcmp(tipos[i], "bebida") == 0) {
             printf(VERDE"[%-3d] |" AZUL " %-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |\n", i+1, produtos[i], precos[i] );
         }
         
         
         
         
         
         
     }
     scanf("%d", &menu[1]);
     for ( int i = 0; i < qtd[0];i++ ) {
         if ( menu[1]-1 == i) {
             lptela();
             printf(AMARELO"\n\n Deseja adicionar quantas unidades de %s?(numeros igual e menor que 0 cancelam o pedido)\n", produtos[menu[1]-1]);
             scanf("%d", &quantidade[0]);
             if ( quantidade[0] > 6) {
                 printf(VERMELHO"\n\nValor alterado para o limite(6).\n");
                 quantidade[0] = 6;
                 sleep(1);
             }
             if ( quantidade[0] <= 0 ) {
                 lptela();
                 printf(VERDE"\n----------------------------------------------------------------------------------\n");
                 printf(VERMELHO"Cancelado");
                 printf(VERDE"\n----------------------------------------------------------------------------------\n");
                 sleep(2);
                 break;
             }
             
             lptela();
             printf(VERDE"\n----------------------------------------------------------------------------------\n");
             printf(VERDE_VIBRANTE"%d "AZUL" %s " AMARELO_LIMAO "Adicionado(s) ao carrinho\n", quantidade[0], produtos[menu[1]-1]);
             printf(VERDE"----------------------------------------------------------------------------------\n");
             for( int i = 0;i < quantidade[0]; i++) {
             strcpy(carrinho[qtd[2]][qtd[1]], produtos[menu[1]-1]);
             cpreços[qtd[2]][qtd[1]] = precos[menu[1]-1];
             qtd[1]++;
             }
             
             sleep(2);
             break;
         }
         if( menu[1]-1 > qtd[0]) {
            lptela();
         printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
         printf(VERMELHO"Opção inexistente seu imbecil");
         printf(VERDE"\n----------------------------------------------------------------------------------\n"); 
         sleep(3);
         break;
        }
        
         
         
     }
     
     
     
     
     
     
     
     
     
    menu[0] = 0;
    break;
    
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@ CASE 2 @!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    case 2:
    if( qtd[1] == 0) {
        menu[0] = 0;
        break;
    }
    lptela();
    printf(VERDE_VIBRANTE"------------------------------------------------------------------------------------------------------\n");
    printf(AMARELO_LIMAO"                  Produtos que deseja remover(0 ou negativo para voltar)                                   ");
    printf(VERDE_VIBRANTE"\n------------------------------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < qtd[1]; i++ ) {
        printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
        printf(VERDE "[%-3d] "VERDE "| " AZUL "%-25s" VERDE " | " VERMELHO "%6.2f" VERDE " |", i+1, carrinho[qtd[2]][i], cpreços[qtd[2]][i] );
    }
    printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
    scanf("%d", &i[2]);
    for( int j = 0; j < qtd[1]; j++) {
    if ( i[2] <= 0 ) {
        lptela();
        printf("Voltando...\n");
        sleep(1);
        menu[0] = 0;
        break;
    }
    if ( i[2]-1 > qtd[1]-1) {
         lptela();
         printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
         printf(VERMELHO"Opção inexistente seu imbecil");
         printf(VERDE"\n----------------------------------------------------------------------------------\n"); 
         sleep(2);
         menu[0] = 0;
         break;
    }
    if ( j == i[2]-1) {
        lptela();
        printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
        printf(AZUL"%s" AMARELO " Removido do carrinho", carrinho[qtd[2]][j]);
        printf(VERDE"\n----------------------------------------------------------------------------------\n");
        sleep(2);
        for (int o = j; o < qtd[1];o++){
        strcpy(carrinho[qtd[2]][j], carrinho[qtd[2]][j+1]);
        
        
        }
        
        qtd[1]--;
        menu[0] = 0;
        break;
    }
    
    }
    break;
    
    
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@ CASE 3 @!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    case 3:
    lptela();
    if ( i[3] == 0) {
    for( int o = 0; o <= 1; o++) {
        lptela();
     
    printf(VERDE"\n\n------------------------------------------------------------------------------\n");
    printf(VERDE_VIBRANTE"1 para entrega e 0 para buscar/comer aqui");
    printf(VERDE"\n------------------------------------------------------------------------------\n");
    bairroc[qtd[2]] = 36;
    scanf("%d", &numero[qtd[2]]);
    if ( numero[qtd[2]] > 1 || numero[qtd[2]] < 0) {
        printf(VERMELHO"\ninexistente\n");
        sleep(1);
        o--;
    }
    else { 
        break;
    }
    }
    if ( numero[qtd[2]] == 1) {
    lptela();
    printf(VERDE_VIBRANTE"\nINFORME SEU BAIRRO\n");
    for(int i = 0; i < 36; i++) {
        printf(VERDE"[%-3d] | %-30s\n", i+1, bairro[i]);
        
    }
    scanf("%s", &bairroc[qtd[2]]);
    bairroc[qtd[2]]--;
    lptela();
    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("%s é o seu bairro.", bairro[bairroc[qtd[2]]]);
    printf("\n----------------------------------------------------------------------------------\n");
    sleep(2);
    lptela();
    printf("\nInforma sua rua:");
    char texto[100];

    scanf(" %[^\n]", rua[qtd[2]][0] );
    printf("\n\n----------------------------------------------------------------------------------\n");
    printf("%s é sua rua", rua[qtd[2]][0]);
    printf("\n\n----------------------------------------------------------------------------------\n");
    sleep(2);
    i[3]++;
    }
    
    }
    
    lptela();
    printf(AMARELO"\n\nEntrega:");
    if ( numero[qtd[2]] == 1) {
        printf(" sim");
    }
    else {
        printf(" não");
    }
    printf("\nbairro: %-40s", bairro[bairroc[qtd[2]]]);
    printf("\nrua: %-40s", rua[qtd[2]][0]);
    printf(VERDE"\n\n===========================================" VERDE_VIBRANTE "NOTA FISCAL" VERDE"===========================================");
    for ( int o = 0; o < qtd[1]; o++){
    printf(VERDE"\n------------------------------------------------------------------------------------------------------\n");
    printf(VERDE"| " AZUL "%-30s" VERDE " | " VERMELHO "%-3.2f" VERDE " |", carrinho[qtd[2]][o], cpreços[qtd[2]][o] );
    total[0][qtd[2]] += cpreços[qtd[2]][o];
    
    }
    printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
    printf(VERDE_VIBRANTE"TOTAL : " VERMELHO "%-4.2f", total[0][qtd[2]]);
    printf(VERDE"\n------------------------------------------------------------------------------------------------------\n\n");
    printf(AMARELO_LIMAO"Digite 1 para confirmar o pedido, 0 para voltar ao menu ou qualquer outro para cancelar");
    scanf("%d", &i[4]);
    switch ( i[4] ) {
        case 1:
        qtd[2]++;
        qtd[1] = 0;
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
        menu[0] = 0;
        break;
        
        case 0:
        lptela();
        total[0][qtd[2]] = 0.00;
        printf("\n\nVoltando");
        menu[0] = 0;
        break;
        
        default:
        
        
    }
    menu[0] = 0;
    break;
    
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@ CASE 4 @!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
    case 4:
    lptela();
    printf(VERDE"\n\n\n-------------------------------------------------------------------------------\n");
    printf(VERMELHO"CERTEZA QUE DESEJA SAIR?(1 sim, qualquer não)");
    printf(VERDE"\n-------------------------------------------------------------------------------\n");
    scanf("%d", &i[1]);
    switch ( i[1] ) {
        case 1:
        
        break;
        
        default:
        menu[0] = 0;
        printf(VERDE_VIBRANTE"\n\n\nVoltando...\n");
        sleep(2);
        break;
    }
    break;
    
    /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@ CASE 5 @!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    case 5:
    do {
    lptela();
    printf(AMARELO_LIMAO"Digite a senha: ");
    scanf("%d", &senha[1]);
    switch ( senha[1] ) {
     
     case 12345:
     logo();
     printf(AMARELO_LIMAO"[1] Adicionar produtos\n");
     printf("[2] Ver vendas\n");
     printf("[3] Gerenciar estoque");
     printf("[4] Sair");
     break;
     
     default:
     menu[0] = 0;
     break;
        
        
        
        
    }


    }
    while ( menu[0] = 1); {

    }
    break;
    
    
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!@ default @!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    default:
     lptela();
     printf(VERDE"\n\n----------------------------------------------------------------------------------\n");
     printf(VERMELHO"Opção inexistente seu imbecil");
     printf(VERDE"\n----------------------------------------------------------------------------------\n"); 
     sleep(2);
     menu[0] = 0;
    break;
    }
    
    
}

while ( menu[0] == 0 ); {

}













   return 0;
}

