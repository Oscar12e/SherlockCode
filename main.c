#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct Population Population, *ptrPopulation;


#define _GNU_SOURCE
int getFileLines(char* filename);
char* fileToString(char* filename);
int getFileLines2(char* filename);

int findVariablesTraces();
int findRepeatedCodeTraces();
int findExceptionTraces();
int findMagicNumberTraces();

int findVariablesTraces(){
    const char * blackListVaribles[] = {"temp", "i", "j", "x"};
    FILE* f;
    char singleLine[300];

    f = fopen("Codes/J-ArrayList.jar", "r");

    if (f == NULL){
        printf("No funco");
    }

    while (!feof(f)){
        fgets(singleLine, 300, f);
        ///puts(singleLine);
    }
    fclose(f);

    char months[] = "JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC";
    char s[2] = ",";
    char* token = strtok(months, s);
    printf("f");

    while( token != NULL ) {
      printf(token);

      token = strtok(NULL, s);
   }
   //Buscar las palabras reservadas en paralelo, tomar el más corto y luego hacer split
   char str[] = "sdfad abc GGGGGGGGG";
   char* result = strstr(str, "abc");
   int position = result - str;
   int substringLength = strlen(str) - position;

   puts(result);
}

int findRepeatedCodeTraces(){

}

int findExceptionTraces(){

}

int findMagicNumberTraces(){

}

/**
    Returns the number of lines contain in the file.

    @param filename: the name of the file thats going to be used.
    @return the number of lines.
*/

int getFileLines(char * const pSringText){
    int lines = 0;
    size_t stringLenght = strlen(pSringText);

    if (stringLenght != 0){
        lines++;
        for (int currentChar = 0; currentChar < stringLenght; currentChar++) {
          if(pSringText[currentChar] == '\n')
            lines++;

        }
    }

    //14693
    return lines;
}



int getFileLines2(char* filename){
    FILE *fp = fopen(filename,"r");
    int ch = 0;
    int lines = 0;

    if (fp == NULL)
        return 0;

    lines++;
    while(!feof(fp)){
      if(fgetc(fp) == '\n')
        lines++;
    }

    fclose(fp);
    return lines;
}

char* fileToString(char* filename){
    FILE *filePointer = fopen(filename, "r");

    if (filePointer == NULL){
        printf("No funco");
        return NULL;
    }

    fseek (filePointer, 0, SEEK_END);
    long fileLenght =  ftell(filePointer);

    fseek (filePointer, 0, SEEK_SET);
    char* body = malloc(fileLenght);
    fread(body, 1, fileLenght, filePointer);

    return body;
}


int main(){
    printf("Tarea Corta 2-10%\tGeneticos y paralelos\n");
    printf("Oscar Cortes Cordero\t20116136191\n\n");


    Population* testPopulation = population_new();
    addSubject(testPopulation, 1);
    //End

    char * const fileString = (char * const) fileToString("Codes/J-ArrayList.jar");
    puts("The hell:");

    puts("Amount2: ");
    printf("%d", strlen(fileString) );


    int linesAmount = getFileLines(fileString); //O(n)
    puts("Counter done\n");
    printf("Lines: %d", linesAmount);

    printf("\nEnd");

    printf("%d", getFileLines2("Codes/J-ArrayList.jar"));
    return 0;
}


//Testing C awesomeness
    /*
    unsigned short short1 = 32;
    unsigned short short2 = 128;
    unsigned short short3 = short1 | short2;
    printf("a: %hu\n", short3);
    */
