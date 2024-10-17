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


int main(void){
	
	char Dificuldade [8];
	int Tamanho;
	int QuantidadeBombas;
	int **CampoMinado;
	char **Interface;
	
	printf("Escolha a Dificildade : facil, medio, dificil. \n");
	
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
		printf("Escolha a Dificildade : facil, medio, dificil: \n");
		scanf("%s",Opcao);
		TamanhoCampo(Opcao,Tamanho);
	}
	
}

int **CriarCampoMinado(int Tamanho){
	
	int Linha,Coluna,contador;
	
	int **alocacao = malloc(Tamanho * Tamanho * sizeof(int*));
	
	if (alocacao == NULL){
		printf("Memoria Insuficiente.\n");
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
		printf("Digite as coordenadas com x,y: \n");
		scanf("%d,%d",&EntradaX,&EntradaY);
		EntradaX --;
		EntradaY --;
		while (EntradaX < 0 || EntradaY < 0 || EntradaX > (Tamanho - 1) || EntradaY > (Tamanho - 1)){
			printf("Coordenadas Invalidas.\nDigite as coordenadas x,y: \n");
			scanf("%d,%d",&EntradaX,&EntradaY);
            EntradaX --;
	    	EntradaY --;
		}
		
		if (CampoMinado[EntradaX][EntradaY] == -1){
			Finalizar = 0;
			BOOM  = 1;
		}else if (Interface[EntradaX][EntradaY] != 'X'){
			printf("Coordenada Repetetiva Insira outra: \n");			
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
		printf("Game Over. 😵‍💫 🙁\n");
	}else{
		printf("Parabéns, você eh fera. 😁 😎 ");
	}
	
	ImprimeCampo(CampoMinado,Tamanho);
	
}

void Letreiro_Inicial (int Tamanho){

    if (Tamanho == 10){
        printf("|-----------CAMPO-MINADO-----------|\n");   
    }else if (Tamanho == 20){
        printf("|-------------------------------CAMPO-MINADO-------------------------------|\n");
    }else if (Tamanho == 30){
        printf("|--------------------------------------------------CAMPO-MINADO---------------------------------------------------|\n");
    }

}

void ImprimeCampo(int **CampoMinado,int Tamanho){
	
	int Linha,Coluna,contador;

    Letreiro_Inicial (Tamanho);

    printf ("  |  1");
	for (contador = 1; contador < Tamanho; contador++){
        printf("| %d",contador + 1);
    }
    printf("\n");

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
		printf("\n");
	}
	
}

void ImprimeInterface(char **Interface,int Tamanho){
	
	int Linha,Coluna,contador;

    Letreiro_Inicial (Tamanho);

    printf ("  |  1");
	for (contador = 1; contador < Tamanho; contador++){
        printf("| %d",contador + 1);
    }
    printf("\n");

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
		printf("\n");
	}
	
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
