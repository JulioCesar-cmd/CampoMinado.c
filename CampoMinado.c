#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void TamanhoCampo (char *Opcao, int *Tamanho); 
int **CriarCampoMinado(int Tamanho);
void The_Bomb_Has_Been_Planted(int **CampoMinado,int Tamanho,int *QuantidadeBombas);
void CordenadasAxuliares(int **CampoMinado,int Tamanho);
char **MascaraCampoMinado(int Tamanho);
void VamosJogarUmJogo(int **CampoMinado, char **Interface,int *QuantidadeBombas,int Tamanho);
void ImprimeCampo(int **CampoMinado,int Tamanho);
void ImprimeInterface(char **Interface,int Tamanho);
void Desalocar_Memoria_CampoMinado(int **CampoMinado, int Tamanho);
void Desalocar_Memoria_Interface(char **Interface, int Tamanho);
void Letreiro_Inicial (int Tamanho);
void Letreiro_Final(int Tamanho);
void TentarDenovo(int *JogarNovamente);


int main(void){
	
char Dificuldade [8];
int Tamanho;
int QuantidadeBombas;
int **CampoMinado;
char **Interface;
 int JogarNovamente;
	
    do
    {

    printf("\n");

    printf("Escolha a Dificildade : facil [10x10], medio[20x20], dificil[30x30]: ");
	
    scanf("%100s",Dificuldade);
	
    TamanhoCampo(Dificuldade,&Tamanho);
	
    CampoMinado = CriarCampoMinado(Tamanho);
	
    The_Bomb_Has_Been_Planted(CampoMinado,Tamanho,&QuantidadeBombas);
	
    CordenadasAxuliares(CampoMinado,Tamanho);
	
    Interface = MascaraCampoMinado(Tamanho);
    
    ImprimeInterface (Interface,Tamanho);
	
    VamosJogarUmJogo(CampoMinado,Interface,&QuantidadeBombas,Tamanho);
	   
    Desalocar_Memoria_CampoMinado(CampoMinado,Tamanho);

    Desalocar_Memoria_Interface(Interface,Tamanho);

    printf("\nGostaria de Jogar Novamente ? Digite s/n.");
    
    TentarDenovo(&JogarNovamente);

    } while (JogarNovamente);

    printf("\nFIM !\n");
	

    return 0;
}




void TamanhoCampo (char *Opcao, int *Tamanho){
	
	int TamanhoMatriz;
	
	if (strcmp(Opcao,"facil") == 0){
		*Tamanho = 10;
	}else if(strcmp(Opcao,"medio") == 0){
		*Tamanho = 20;
	}else if(strcmp(Opcao,"dificil") == 0){
		*Tamanho = 30;

	}else{
		printf("Entrada invalida.\n");
		printf("\nEscolha a Dificildade : facil [10x10], medio[20x20], dificil[30x30]: ");
		scanf("%s",Opcao);
		TamanhoCampo(Opcao,Tamanho);
	}
	
}

int **CriarCampoMinado(int Tamanho){
	
	int Linha,Coluna,contador;
	
	int **alocacao = malloc(Tamanho * Tamanho * sizeof(int*));
	
	if (alocacao == NULL){
		printf("\nMemoria Insuficiente.\n");
		exit(1);
	}
	
	for (contador = 0; contador < Tamanho; contador++){
		alocacao[contador] = malloc(Tamanho * sizeof(int));
		if (alocacao[contador] == NULL){
			printf("Memoria Insuficiente.\n");
			exit(1);
		}
	}
	
	for (Linha = 0; Linha < Tamanho; Linha++){
		for (Coluna = 0; Coluna < Tamanho; Coluna++){
			alocacao[Linha][Coluna] = 0;
		}
	}
	
	return alocacao;	
}

void The_Bomb_Has_Been_Planted(int **CampoMinado,int Tamanho,int *QuantidadeBombas){
	
	int CordenadaX;
	int CordenadaY;
	int contador;
	
	srand(time(NULL));
	
	if(Tamanho == 10){
		*QuantidadeBombas = 3;
	}else if(Tamanho == 20){
		*QuantidadeBombas = 6;
	}else if(Tamanho == 30){
		*QuantidadeBombas = 9;
	}
	
	contador = 0;
	
	while(contador < *QuantidadeBombas){
		CordenadaX = rand() % (Tamanho-1);
		CordenadaY = rand() % (Tamanho-1);
		if (CampoMinado[CordenadaX][CordenadaY] != -1){
			CampoMinado[CordenadaX][CordenadaY] = -1;
			contador++;
		}
	}
	
}

void CordenadasAxuliares(int **CampoMinado,int Tamanho){
	
	int Linha,Coluna,contador,X,Y,Z,Casas;
	
	for (Linha = 0; Linha < Tamanho; Linha++){
		for(Coluna = 0; Coluna < Tamanho; Coluna++){
			if (CampoMinado[Linha][Coluna] == -1){
				X = Linha - 1;
				Y = (Coluna - 1);
				for (contador = 0; contador < 3; contador++){
					if (X >= 0 && Y >= 0 && X <= (Tamanho - 1) && Y <= (Tamanho - 1) && CampoMinado[X][Y] != -1){
						CampoMinado[X][Y] += 1; 
					}
					Y++;
				}
				X = Linha + 1;
				Y = Coluna - 1;
				for (contador = 0; contador < 3; contador++){
					if (X >= 0 && Y >= 0 && X <= (Tamanho - 1) && Y <= (Tamanho - 1) && CampoMinado[X][Y] != -1){
						CampoMinado[X][Y] += 1; 
					}
					Y++;
				}
				X = Linha;
				Y = Coluna - 1;
				for (contador = 0; contador < 2;contador++){
					// Condição para Verificar se a Coordenada esta dentro dos limites da Matriz e se estiver nao substituir uma Bomba;
					// X,Y sao as Casas Laterais a Bomba;
					if (X >= 0 && Y >= 0 && X <= (Tamanho - 1) && Y <= (Tamanho - 1) && CampoMinado[X][Y] != -1){
						CampoMinado[X][Y] += 1;
					}
					Y += 2;
				}
			}
		}
	}
}

char **MascaraCampoMinado(int Tamanho){
	
	int Linha,Coluna,contador;
	
	char **alocacao = malloc(Tamanho * Tamanho * sizeof(char*));
	
	if (alocacao == NULL){
		printf("Memoria Insuficiente.\n");
		exit(1);
	}
	
	for (contador = 0; contador < Tamanho; contador++){
		alocacao[contador] = malloc(Tamanho * sizeof(char));
		if (alocacao[contador] == NULL){
			printf("Memoria Insuficiente.\n");
			exit(1);
		}
	}
	
	for (Linha = 0; Linha < Tamanho; Linha++){
		for (Coluna = 0; Coluna < Tamanho; Coluna++){
			alocacao[Linha][Coluna] = 'X';
		}
	}
	
	return alocacao;	
}

void VamosJogarUmJogo(int **CampoMinado, char **Interface,int *QuantidadeBombas,int Tamanho){
	
	int Finalizar,BOOM,EntradaX,EntradaY,CasasSeguras,Acertos;
	
	CasasSeguras = (Tamanho * Tamanho) - *QuantidadeBombas;
	Acertos = 0;
		
	Finalizar = 1;
	BOOM = 0;
	
	while(Finalizar){
		printf("\nDigite as coordenadas com x,y: ");

        scanf("%d,%d",&EntradaX,&EntradaY);

		while (EntradaX < 1 || EntradaY < 1 || EntradaX > Tamanho || EntradaY > Tamanho){
			printf("\nCoordenadas Invalidas.\nDigite as coordenadas com x,y: \n");
            while (getchar () != '\n');
			scanf("%d,%d",&EntradaX,&EntradaY);
		}

        EntradaX --;
	    EntradaY --;
		
		if (CampoMinado[EntradaX][EntradaY] == -1){
			Finalizar = 0;
			BOOM  = 1;
		}else if (Interface[EntradaX][EntradaY] != 'X'){
			printf("\nCoordenada Repetida !!!\n");			
		}		
		else{
			Interface[EntradaX][EntradaY] = CampoMinado[EntradaX][EntradaY] + '0';
			Acertos++;
			ImprimeInterface(Interface,Tamanho);
		}
		
		if (Acertos == CasasSeguras){
			Finalizar = 0;
		}
				
	}
	
	if (BOOM == 1){
		printf("\n   Game Over. (╥︣﹏᷅╥)\n");
	}else{
    
		printf("\n   Parabéns, você eh fera.  (•◡•) /\n");
	}
	
	ImprimeCampo(CampoMinado,Tamanho);
	
}

void Letreiro_Inicial (int Tamanho){
   
    printf("  ");   
    if (Tamanho == 10){
        printf("|-----------CAMPO-MINADO---------|\n");   
    }else if (Tamanho == 20){
        printf("|------------------------------CAMPO-MINADO------------------------------|\n");
    }else if (Tamanho == 30){
        printf("|----------------------------------------------------CAMPO-MINADO------------------------------------------------|\n");
    }

}

void Letreiro_Final(int Tamanho){
    
    printf("  ");   
    if (Tamanho == 10){     
        printf("|--------------------------------|\n");   
    }else if (Tamanho == 20){
        printf("|------------------------------------------------------------------------|\n");
    }else if (Tamanho == 30){
        printf("|----------------------------------------------------------------------------------------------------------------|\n");
    }

}

void ImprimeCampo(int **CampoMinado,int Tamanho){
	
	int Linha,Coluna,contador;

      printf("\n");

    Letreiro_Inicial (Tamanho);

    printf ("  |  1");
	for (contador = 1; contador < Tamanho; contador++){
        printf("| %d",contador + 1);
    }
    printf(" |\n");

	for (Linha = 0; Linha < Tamanho; Linha++){
        if (Linha + 1 >= 10 ){
            printf("%d|",Linha + 1);
        }else{
            printf(" %d|",Linha  + 1);
        }
		for (Coluna = 0; Coluna < Tamanho; Coluna++){
            if (Coluna + 1 >= 10){
               printf("   %d",CampoMinado[Linha][Coluna]);
            }else{
               printf("  %d",CampoMinado[Linha][Coluna]);
            }
		}
		printf(" |\n");
	}
    
    Letreiro_Final(Tamanho);
	
}

void ImprimeInterface(char **Interface,int Tamanho){
	
	int Linha,Coluna,contador;

    printf("\n");

    Letreiro_Inicial (Tamanho);

    printf ("  |  1");
	for (contador = 1; contador < Tamanho; contador++){
        printf("| %d",contador + 1);
    }
    printf(" |\n");

	for (Linha = 0; Linha < Tamanho; Linha++){
        if (Linha + 1 >= 10 ){
            printf("%d|",Linha + 1);
        }else{
            printf(" %d|",Linha  + 1);
        }
		for (Coluna = 0; Coluna < Tamanho; Coluna++){
            if (Coluna + 1 >= 10){
               printf("   %c",Interface[Linha][Coluna]);
            }else{
               printf("  %c",Interface[Linha][Coluna]);
            }
		}
		printf(" |\n");
	}

    Letreiro_Final(Tamanho);
	
}
    
     

void Desalocar_Memoria_CampoMinado(int **CampoMinado, int Tamanho){

    int contador;

    for (contador = 0; contador < Tamanho; contador++){
        free (CampoMinado[contador]);
    }
    
    free (CampoMinado);
}

void Desalocar_Memoria_Interface(char **Interface, int Tamanho){

    int contador;

    for (contador = 0; contador < Tamanho; contador++){
        free (Interface[contador]);
    }
    
    free (Interface);
}

void TentarDenovo(int *JogarNovamente){

    char Entrada;

    while (getchar() != '\n');

    scanf("%c",&Entrada);
    if (Entrada == 's'){
        *JogarNovamente = 1;
    }else if (Entrada == 'n'){
        *JogarNovamente = 0;    
    }else{
        printf("\nOpcao Invalida.\nDigite s/n: ");
        TentarDenovo(JogarNovamente);      
    }
}
