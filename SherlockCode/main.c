#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
typedef struct Population Population, *ptrPopulation;

#define _GNU_SOURCE
char** splitText(char* pText, char pDelimeter);
char** str_split(char* a_str, const char a_delim);

int getFileLines(char* filename);

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


int getFileLines(char* filename){
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




int main(){
    printf("Hello world!\n");
    printf("Tarea Corta 2-10%\tGeneticos y paralelos\n");
    printf("Oscar Cortes Cordero\t20116136191\n\n");


    unsigned short short1 = 32;
    unsigned short short2 = 128;
    unsigned short short3 = short1 | short2;
    printf("a: %hu\n", short3);

    Population* testPopulation = population_new();
    addSubject(testPopulation, 1);

    int linesAmount = getFileLines("Codes/J-ArrayList.jar"); //O(n)
    FILE* f;
    puts("Counter done\n");

    puts("Amount: ");

    printf("%d", linesAmount);

    puts("\n");

    f = fopen("Codes/J-ArrayList.jar", "r");

    if (f == NULL){
        printf("No funco");
    }

    char* body = malloc(sizeof(char*));
    int bodySize = 0;
    char ch = 0;

    while (!feof(f)){
        ch = fgetc(f);
        body[bodySize] = ch;

    }

    char * const * body2 = (char * const * )body;
    printf("%d", strlen(body2) );

    printf("\nEnd");
    return 0;
}



/**
 * Takes the code text and split it by ";", eliminates innecesary spaces as well.
 **/
char ** codeParser(char* pCode){
    return 0;
}


//Internet split
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

char** splitText(char* pText, char pDelimeter){
    char * piece = 0;
    int pieceLenght = 0;
    char ** result;
    int resultLenght = 0;

    printf(pText);
    printf("Really");

    while(*pText){
        printf("in");
        if (*pText == pDelimeter){
            if (pieceLenght != 0){
                printf("Tere");
                *(result + resultLenght) = piece;
                pieceLenght = 0;
                *piece = 0;
                resultLenght++;
                }
        } else {
            printf("Oh boy");
            *(piece + pieceLenght) = *pText;
            pieceLenght++;
        }
        pText++;
   }

   printf("Out");

   *(result + resultLenght) = 0;
   return result;
}



