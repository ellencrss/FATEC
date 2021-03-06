#include <stdio.h>
#include<stdlib.h>
#include<string.h>

void invert(FILE *ent,FILE *sai);
void cript(char *senha,FILE *ent,FILE *sai);
void unixdos(FILE *ent,FILE *sai);
void dosunix(FILE *ent,FILE *sai);
void verificar_extensao(char *entrada,char *extensao,int i,int caso);

int main(int argc, char *argv[]){
	int i;
	char entrada[200],saida[200],extensao[10],senha[100],tipo;//pega do argv
	FILE *ent,*sai;
	if(argc>=2){
		strcpy(entrada,argv[1]);//pegar o nome do arquivo
		tipo=argv[2][0];//pegar o tipo de conversao
	}
	else{
		printf("PROGRAMA CANCELADO!");
		return (1);
	}
	ent=fopen(entrada,"rb");
	if(ent==NULL){
		printf("Erro na abertura");
		exit(1);
	}
	strcpy(saida,entrada);	
	for(i=strlen(saida)-1; i!=0 && saida[i]!='.';i--);
	switch(tipo){
		case 'I'://invert
			verificar_extensao(entrada,extensao,i,1);
			strcpy(saida+i,extensao);
			sai=fopen(saida,"wb");
			invert(ent,sai);
			break;
		case 'C'://CRIPT
			strcpy(senha,argv[3]);//pega a chave
			verificar_extensao(entrada,extensao,i,2);
			strcpy(saida+i,extensao);
			sai=fopen(saida,"wb");
			cript(senha,ent,sai);
			break;
		case 'D'://DOS TO UNIX
			strcpy(saida+i,".UNX");
			sai=fopen(saida,"wb");
			dosunix(ent,sai);
			break;
		case 'U'://UNIX TO DOS
			strcpy(saida+i,".DOS");
			sai=fopen(saida,"wb");
			unixdos(ent,sai);
			break;
		default:
			printf("TIPO INVALIDO");
			break;
	}
	return (0);
}

void invert(FILE *ent,FILE *sai){//I
	char ch,x;
	ch=fgetc(ent);
	while(ch!=EOF){
		x=~ch;
		fputc(x,sai);
		ch=fgetc(ent);
	}
	fclose(sai);fclose(ent);
}

void cript(char *senha,FILE *ent,FILE *sai){//C
	char ch,x;
	int cont=0;
	ch=fgetc(ent);
		while(ch!=EOF){
		x=ch^senha[cont];
		fputc(x,sai);
		ch=fgetc(ent);
		if (senha[cont]=='\0')
			cont=0;
		cont++;
	}
	fclose(sai);fclose(ent);
}

void unixdos(FILE *ent,FILE *sai){
	char ch;
	ch=fgetc(ent);
	while(ch!=EOF && ch!=10)//10 é o valor de LF
	{
		fputc(ch,sai);
		ch=fgetc(ent);
	}
	fputc(13,sai);
	fputc(10,sai);
	fclose(sai);fclose(ent);
}

void dosunix(FILE *ent,FILE *sai){//U salvar como .UNIX
	char ch;
	ch=fgetc(ent);
	while(ch!=EOF && ch!=13)//13 é o valor de CR
	{
		fputc(ch,sai);
		ch=fgetc(ent);
	}
	fputc(10,sai);
	fclose(sai);fclose(ent);
}

void verificar_extensao(char *entrada,char *extensao,int i,int caso){
	int c;
	for(c=0;entrada[i+c]!='\0';c++)
		extensao[c]=entrada[i+c];
	switch(caso){
		case 1:
			if(strcmp(extensao,".INV")==0)
				strcpy(extensao,".DNV");
			else
				strcpy(extensao,".INV");
			break;
		case 2:
			if(strcmp(extensao,".CRP")==0)
				strcpy(extensao,".DRP");
			else
				strcpy(extensao,".CRP");
			break;
			
	}
}
