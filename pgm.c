/*Processamento de Imagem em C
Discentes: Daniel Rothmund,Mario Henrique, Wictor Hugo.
Docente: Beatriz Trinchão
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Cabeçalho de funções//
char* substring(char str[], int start, int end) {
    int i, j;
    char *sub;

    sub = (char *) malloc(sizeof(char) * (end - start + 1));

    for(i = start, j = 0; i < end; i++, j++) {
        sub[j] = str[i];
    }

    sub[j] = '\0';

    return sub;
}
void imprimir_arquivo(char* nome_arquivo, int matriz[512][512]){
    FILE *output;
    output = fopen(nome_arquivo,"w");

    fprintf(output, "P2\n");
    fprintf(output, "# MINHA IMAGEM PGM\n");
    fprintf(output, "512 512\n");
    fprintf(output, "255\n");
    
    for(int i=0;i<512;i++){
        for(int j=0;j<512;j++){
            if(j == 0){
                fprintf(output, "%d", matriz[i][j]);
            }
            else{
                fprintf(output, " %d", matriz[i][j]);
            }
        }
        fprintf(output, "\n");
    }
    fclose(output);
}
void carregar_arquivo(char* nome_arquivo, int matriz[512][512]){

    char line[1000];
    int cont = 0;
    char type[3];
    int size_line = 0, size_column = 0, max_level = 0, value;
    char *s_size_line, *s_size_column, *s_max_level;
    FILE* input = fopen(nome_arquivo, "r"); //Abrimos o arquivo.

    while(cont != 3){
        fgets(line, sizeof line, input);
        if(line[0] == '#'){
            continue;
        }
        if(cont == 0){
            strcpy(type, line);
            strtok(type, "\n");
        }
        if(cont == 1){
            s_size_line = substring(line, 0, 3);
            s_size_column = substring(line, 4, 7);
            size_line = atoi(s_size_line);
            size_column = atoi(s_size_column);
        }
        if(cont == 2){
            s_max_level = substring(line, 0, 3);
            max_level = atoi(s_max_level);
        }
        cont++;
    }

    for(int i=0;i<512;i++){
        for(int j=0;j<512;j++){
            fscanf(input, "%d", &value);
            matriz[i][j] = value;
        }
    }
    fclose(input);
}
void preencher_listas(int entrada[512][512]){ 
  int linhas,colunas;
  int cor=0;
  int cont=0;
  for(linhas=0;linhas<512;linhas++){
    for(colunas=0;colunas<512;colunas++){
      if(cor==0){
        entrada[linhas][colunas]=0;
      }if(cor==1){
        entrada[linhas][colunas]=255;
      }
      cont++;
      if(cont==64){
        cor=0;
      }if(cont==128){
        cor=1;
        cont=0;
      }
    }
  }
}
void preencher_aleatoriamente(int entrada [512][512]){ 
  srand(time(NULL));
  int linhas,colunas;
  for(linhas=0;linhas<512;linhas++){
    for(colunas=0;colunas<512;colunas++){
      entrada[linhas][colunas]=rand()%255;
    }
  }
}
void limiarizar(int entrada[512][512], int saida[512][512], int limiar){
   int linhas, colunas;
   for(linhas=0;linhas<512;linhas++){
      for(colunas=0;colunas<512;colunas++){
        if(entrada[linhas][colunas] > limiar){ 
			 saida[linhas][colunas] = 255;
        }else{
			 saida[linhas][colunas] = 0;
	      }
      }
    }
}
void alterar_brilho(int entrada[512][512], int saida[512][512], float fator){
	int linhas,colunas;
  float alterando_brilho;
	for(linhas=0;linhas<512;linhas++){
	 for(colunas=0;colunas<512;colunas++){
     alterando_brilho = entrada[linhas][colunas] * fator;
     if(alterando_brilho < 0){
      alterando_brilho = 0;  
     }
     if(alterando_brilho > 255){
       alterando_brilho = 255;
      }
    saida[linhas][colunas] = alterando_brilho;
	  }
	}
}
void filtro_media(int entrada[512][512], int saida[512][512]){
  int linhas,linha_x,colunas,coluna_y;
  int somatorio,cont;
   for(linhas=0;linhas<512;linhas++){
     for(colunas=0;colunas<512;colunas++){
      somatorio=0;
      cont=0;
       for(linha_x=linhas-1;linha_x<linhas+1;linha_x++){
         for(coluna_y=colunas-1;coluna_y<colunas+1;coluna_y++){
           if(linha_x>=0 && linha_x<512 && coluna_y>=0 && coluna_y<512 ){
             somatorio+=entrada[linha_x][coluna_y];
             cont++;
            } 
          }
        }
      saida[linhas][colunas] = somatorio/cont;
      }
    }
}
int main(){
 int matriz [512][512];
 int saida[512][512];
 int menu,vald_menu;
 printf("\nOla, Usuario. \n\n"
        "O programa a seguir entrega um pouco da manipulacao de imagem,sendo ela do tipo \"pgm\".\n"
        "Sendo assim, lembre-se na hora de salvar o nome do seu arquivo de sempre terminar com \".pgm\".\n\n"
        "Para continuar, pressione \"1\".\n"
        "Para sair, pressione \"2\".\n");
 scanf("%d", &vald_menu);
 if(vald_menu==1){
   system("clear");
   printf(
        "      Processamento de Imagem    \n\n"
        "Opcao 1 - Carregar matriz de entrada.\n"
        "Opcao 2 - Salvar matriz de saida.\n"
        "Opcao 3 - Preencher com listras. \n"
        "Opcao 4 - Preencher aleatoriamente. \n"
        "Opcao 5 - Limiarizar com valor.\n"
        "Opcao 6 - Alterar brilho com valor.\n"
        "Opcao 7 - Filtro de media.\n"
        "Opcao 8 - Sair do programa.\n"
        "Opcao 9 - Leia um pouco mais\n\n"
        "**Por Favor,insera uma opcao para continuar.**\n");
 scanf("%d",&menu);
	switch(menu){
		case 1:
       system("clear");
		   printf("Carregando matriz de entrada...\n");
		   char nome[180];
		   printf("Insira o nome do arquivo de entrada: ");
		   scanf("%s", nome);
		   printf("Otimo, sua matriz foi salva!\n");
		   carregar_arquivo(nome, matriz);
		   return main();
       system("clear");
	   case 2:
       system("clear");
		   printf("Salvando matriz de saida...\n");
		   char nome_saida[180];
		   printf("Insira o nome do arquivo de saida: ");
		   scanf("%s", nome_saida);
		   printf("Otimo, sua matriz foi salva!\n");
		   carregar_arquivo(nome_saida,matriz);
		   return main(menu);
       system("clear");
	   case 3:
       system("clear");
		   printf("Preenchendo matriz de entrada com listras...\n");
		   char nome1[180];
		   printf("Insira o nome do arquivo: ");
		   scanf("%s", nome1);
       carregar_arquivo(nome1,matriz);
       printf("Conseguimos, seu arquivo esta pronto para ser utilizado!\n\n");
       printf("Para continuar, insira o nome do arquivo para salvar: ");
		   scanf("%s", nome1);
		   preencher_listas(saida);
		   imprimir_arquivo(nome1,saida);
       printf("Verifique o seu arquivo!\n");
		   return main(menu);
       printf("Pronto, agora basta verificar o seu arquivo!\n");
       system("clear");
	   case 4:
       system("clear");
	     printf("Prennchendo matriz de entrada aleatoriamente...\n");
	     char nome2[180];
		   printf("Insira o nome do arquivo: ");
		   scanf("%s", nome);
       carregar_arquivo(nome2,matriz);
		   printf("Conseguimos, seu arquivo esta pronto para ser utilizado!\n\n");
       printf("Para continuar, insira o nome do arquivo para salvar: ");
       scanf("%s", nome2);
		   preencher_aleatoriamente(matriz);
		   imprimir_arquivo(nome2, matriz);
       printf("Pronto, agora basta verificar o seu arquivo!\n");
		   return main(menu);
       system("clear");
	  case 5:
       system("clear");
	     printf("Limiarizacao com seu valor definido...\n");
	     char nome3[180];
	     int v_limiar = 0;
		   printf("Insira o nome do arquivo: ");
		   scanf("%s", nome3);
		   printf("Seu arquivo esta pronto para ser usado!\n\n");
       carregar_arquivo(nome3,matriz);
		   printf("Insira o valor para a limiarizacao: ");
		   scanf("%d", &v_limiar);
       printf("Insira o nome do arquivo para salvar: ");
       scanf("%s",nome3);
		   limiarizar(matriz, saida, v_limiar);
		   imprimir_arquivo(nome3,saida);
       printf("Pronto, agora basta verificar o seu arquivo!\n");
		   return main(menu);
       system("clear");
	  case 6:
       system("clear");
	     printf("Alterando brilho com valor fornecido...\n");
       char nome4[180];
	     float fator;
		   printf("Insira o nome do arquivo: ");
		   scanf("%s", nome4);
		   printf("Seu arquivo esta pronto para ser usado!\n\n");
		   printf("Insira o fator para a alterar o brilho: ");
       scanf("%f", &fator);
       carregar_arquivo(nome4,matriz);
		   alterar_brilho(matriz,saida,fator);
       printf("\nInsira o nome do arquivo para salvar: ");
		   scanf("%s", nome4);
		   imprimir_arquivo(nome4 , saida);
       printf("Pronto, agora basta verificar o seu arquivo!\n");
		   return main(menu);
       system("clear");
	  case 7:
      system("clear");
	    printf("Carregando filtro de media...\n");
      char nome5[180];
      printf("Insira o nome do arquivo: ");
      scanf("%s", nome5);
      printf("Seu arquivo esta pronto para ser usado!\n");
      carregar_arquivo(nome5,matriz);
      filtro_media(matriz,saida);
      printf("Insira o nome do arquivo para salvar: ");
      scanf("%s", nome5);
		  imprimir_arquivo(nome5, saida);
      printf("Pronto, agora basta verificar o seu arquivo!\n");
		  return main(menu);
      system("clear");
	  case 8:
       system("clear");
	     printf("Saindo do programa...\n\n");
		   printf("Pressione \"enter\" para sair");
		   exit(1);
		   break;
	  default:
        system("clear");
	      while(1){
		      if(menu==9){
			     printf("\nLink para o texto: https://drive.google.com/file/d/1zqy2Ck6Q-z8BfHuxlyEhRKDWJZwQrY4h/view?usp=sharing\n");  
			     break;
			  }else{ 
				  return main(menu);
          system("clear");
		      }
		   }
       break;
      }
  }else if(vald_menu==2){
   system("clear");
   printf("Sainda do programa!\n");
   exit(1);
  }else{
    return main(vald_menu);
    system("clear");
  }
  return 0;
}