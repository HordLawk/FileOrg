#include <stdio.h>
#include <stdlib.h>
#include "funcoesFornecidas.h"
#include <string.h>

char *readLineDynamic(FILE *stream);

void linebreak(FILE *stream);

void writeString(FILE *bin, char* str, int size);

int main(){
    int cmd;
    scanf("%d ", &cmd);
	char* name = readLineDynamic(stdin);
	switch(cmd){
		case 1: {
			FILE* bin = fopen(name, "wb");
			int n;
			scanf("%d", &n);
			linebreak(stdin);
			char* str = malloc(sizeof(char) * 81);
			for(int i = 0; i < 81; i++) str[i] = '$';
			while(n--){
				writeString(bin, str, 51);
				writeString(bin, str, 51);
				writeString(bin, str, 81);
				writeString(bin, str, 51);
				int age;
				scanf("%d", &age);
				linebreak(stdin);
				fwrite(&age, sizeof(int), 1, bin);
			}
			free(str);
			fclose(bin);
			binarioNaTela(name);
			free(name);
		}
		break;
		case 2: {
			FILE* bin = fopen(name, "rb");
			free(name);
			if(!bin){
				printf("Falha no processamento do arquivo\n");
				return 0;
			}
			char* str = malloc(sizeof(char) * 81);
			fread(str, sizeof(char), 51, bin);
			while(!feof(bin)){
				printf("Firstname: %s\n", str);
				fread(str, sizeof(char), 51, bin);
				printf("Lastname: %s\n", str);
				fread(str, sizeof(char), 81, bin);
				printf("Email: %s\n", str);
				fread(str, sizeof(char), 51, bin);
				printf("Nationality: %s\n", str);
				int age;
				fread(&age, sizeof(int), 1, bin);
				printf("Age: %d\n\n", age);
				fread(str, sizeof(char), 51, bin);
			}
			free(str);
			fclose(bin);
		}
		break;
		case 3: {
			FILE* bin = fopen(name, "rb");
			free(name);
			if(!bin){
				printf("Falha no processamento do arquivo\n");
				return 0;
			}
			int n;
			scanf("%d", &n);
			linebreak(stdin);
			char* str = malloc(sizeof(char) * 81);
			fseek(bin, n * 238, SEEK_SET);
			fread(str, sizeof(char), 51, bin);
			printf("Firstname: %s\n", str);
			fread(str, sizeof(char), 51, bin);
			printf("Lastname: %s\n", str);
			fread(str, sizeof(char), 81, bin);
			printf("Email: %s\n", str);
			fread(str, sizeof(char), 51, bin);
			printf("Nationality: %s\n", str);
			free(str);
			int age;
			fread(&age, sizeof(int), 1, bin);
			fclose(bin);
			printf("Age: %d\n\n", age);
		}
		break;
	}
    return 0;
}

char *readLineDynamic(FILE *stream){
    char *line = NULL;
    for(int i = 0; !i || (line[i - 1] != '\0'); i++){
        line = realloc(line, (i + 1) * sizeof(char));
        char tmp = fgetc(stream);
        line[i] = ((tmp == '\n') || feof(stream) || (tmp == '\r')) ? '\0' : tmp;
		if(tmp == '\r') fgetc(stream);
    }
    return line;
}

void linebreak(FILE *stream){
	char crlf = fgetc(stream);
	while((crlf != '\n') && !feof(stream)) crlf = fgetc(stream);
}

void writeString(FILE *bin, char* str, int size){
	readline(str);
	fwrite(str, sizeof(char), size, bin);
	for(int i = 0; i < strlen(str); i++) str[i] = '$';
	str[strlen(str)] = '$';
}