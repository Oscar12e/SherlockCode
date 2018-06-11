#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
//#include "parallel.h"

#define LINES_TO_COMPARE_AGAINST 0
#define LINES_TO_COMPARE 0

#define VARIABLES_WEIGHT 0
#define MAGIC_NUMBERS_WEIGHT 0
#define EXCEPTION_WEIGHT 0
#define REPEATED_CODE_WEIGHT 0


typedef struct Population Population, *ptrPopulation;

int getFileLines(char* filename);
char* fileToString(char* filename);
char** loadFilesNamesList();
char** loadBlackList();
char* removeElementsFromArray(char* pText);
char** splitText(char* pText, char* pDelimeters);

int findVariablesTraces(const char * pCode, char** pBlackList);
int findRepeatedCodeTraces();
int findExceptionTraces(const char * pCode);
int findMagicNumberTraces(const char * pCode);


/**
    The function search every variable name, contained in the blacklist. Counts
    every variable so it can return the amount of bad variable names found in the code.

    @param pCode: The code to be examined as a pointer to constant char
    @param pBlackList: List of variable names that aren´t accepted
*/
int findVariablesTraces(const char * pCode, char** pBlackList){
    int tracesFound = 0;
    int currentVarIndex = 0;
    char* currentVariable = *(pBlackList + currentVarIndex);
                                            //Reading all variable names in the black list
    while ( currentVariable != NULL  ) {    //O(c) if we make a little cheating saying that there are k names, k as connstan
        const char *codeBackup = pCode;     //Back up for the code, strstr modify the pointer

        if (strstr( codeBackup, currentVariable ) != NULL){            //O(n) if we take the len of pCode as our n
            //Lines to  check position and variable found
            //printf( "\nPosition: %d\n", (int)(strstr( codeBackup, currentVariable )-pCode));
            //printf("\n%s", currentVariable);
            ++tracesFound;
        }
        currentVarIndex++;
        currentVariable = *(pBlackList + currentVarIndex);
    }

    return tracesFound;
}

int findRepeatedCodeTraces(const char * pCode){
    int repeatedLines = 0;
    char **codeLines = splitText(pCode, "\n");      //O(n)
    int linesAmount = countApparition(pCode, "\n"); //O(n)

    int linesToBeCompare = (int) linesAmount/2;
    int linesToBeCompareAgainst = (int) linesAmount/3;

    for (int linesCompared = 0; linesCompared < linesToBeCompare; linesCompared++){

    }

    return 0;
}

/**
    The function finds all the 'public' words in the code as all the 'Throw' words,
    then it just.. ahm.. makes a 'resta' to tell the difference between the two words
    found result.

    @param pCode: The code to be examined as a pointer to constant char
*/

int findExceptionTraces(const char * pCode){

    //Public 'methods' found
    int publicFound = countApparition(pCode, " public ");

    //Control except found in the code
    int exceptControlFound = countApparition(pCode, "throw new") + countApparition(pCode, "catch");

    int result = publicFound - exceptControlFound;

    /*
    printf("\n%d", publicFound);
    printf("\n%d", exceptControlFound);
    printf("\n");
    */

    if (result > 0)
        return result;
    else return 0;
}

int countApparition(const char * pText, const char* pSearchWord){
    const char *textBackup = pText;
    int apparitionFound = 0;
    //Pendiente: Revisar porque while(codeBackup) != NULL No funciona

    while (strstr( textBackup, pSearchWord ) != NULL){
        int position = (int) (strstr( textBackup, pSearchWord )-pText);
        apparitionFound++;
        textBackup = pText + position+1;
    }

    return apparitionFound;
}

int findMagicNumberTraces(const char * pCode){
    char * tokensToMagicNumbers[] = {"<", ">", "==", "<=", ">=", "!=", "+", "-", "*", "/", "%", NULL};  //Se buscan los que esten a la derecha
    pCode = removeElementsFromArray(strdup(pCode));

    int tokenLenght;
    int currentTokenIndex = 0;
    int counter = 0;
    char* currentToken = *(tokensToMagicNumbers + currentTokenIndex);

    while ( currentToken != NULL){
        tokenLenght = strlen(currentToken);

        const char *textBackup = pCode;                     //Set the backup so it can be readable and modifiable
        while (strstr( textBackup, currentToken ) != NULL){
            int position = (int) (strstr( textBackup, currentToken )-pCode);
            textBackup = pCode + position;                  //Set the backup at the token start

            if (isdigit(*(textBackup - 1)) )            //Checks the character before token
                counter++;
            if (isdigit(*(textBackup + tokenLenght)) )  //Checks the character after token
                counter++;

            textBackup++;   //Moves the pointer so we can read the next occurrence
        }


        currentTokenIndex++;
        currentToken = *(tokensToMagicNumbers + currentTokenIndex);
    }

    return counter;
}



/**
    Returns the number of lines contain in the file.

    @param
    @return the number of lines.
*/

int getFileLines(char * const pSringText){
    return countApparition(pSringText, "\n") + 1;
}


char* fileToString(char* filename){
    FILE *filePointer = fopen(filename, "r");

    if (filePointer == NULL){
        printf("No se pudo abrir el archivo ");
        printf(filename);
        printf("\n");
        return NULL;
    }

    fseek (filePointer, 0, SEEK_END);
    long fileLenght =  ftell(filePointer);

    fseek (filePointer, 0, SEEK_SET);
    char* body = malloc(fileLenght);
    fread(body, 1, fileLenght, filePointer);

    fclose(filePointer);
    return body;
}

char** loadFilesNamesList(){
    DIR *dir;
    struct dirent *ent;
    char** fileNames = (char **) malloc(sizeof(char*));
    int fileAmount = 0;

    if ((dir = opendir ("Codes")) != NULL) { // print all the files and directories within directory
        while ((ent = readdir (dir)) != NULL){

            if (ent->d_namlen > 4){ //Cualquier file más largo que .jar se toma en cuenta
                *(fileNames + fileAmount) = strdup(ent->d_name);
                fileAmount++;
            }

        }
        closedir (dir);  //Close conections
    } else {
      /* could not open directory */
      return NULL;
    }
    *(fileNames + fileAmount) = NULL;

    return fileNames;
}

char** loadFilesList(char** pFileNames){
    char* fileName = (char*) malloc(sizeof(char));
    char** filesResult = (char**) malloc(sizeof(char*));

    int nameIndex = 0;

    while (*(pFileNames +nameIndex)!= NULL){
        nameIndex++;
    }

    return NULL;
}

char** loadBlackList(){
    char * blackListTXT =  fileToString("BlackList.txt");
    char * word = (char*) malloc(sizeof(char));
    word = strtok (blackListTXT,"\n ,.;\0");

    char ** blackList = (char **) malloc(sizeof(char*));
    int wordsCount = 0;
    while (word != NULL){
        *(blackList + wordsCount) = (char*) malloc(sizeof(char));
        const char * currentVariable = (char*) malloc(sizeof(char));

        currentVariable = (const char *) strdup(word);
        //*(blackList + wordsCount) = strdup(word);
        strcpy(*(blackList + wordsCount), " ");
        strcat(*(blackList + wordsCount), currentVariable);
        strcat(*(blackList + wordsCount), " ");
        //printf ("\n%s",word);

        word = strtok (NULL, "\n ,.;\0");
        free(currentVariable);
        wordsCount++;
    }

    *(blackList + wordsCount) = NULL;
    free(word);
    return blackList;
}

char** splitText(char* pText, char* pDelimeters){
    char** textResult = (char **) malloc(sizeof(char*));
    char * word = (char*) malloc(sizeof(char));
    word = strtok (pText, pDelimeters);

    int wordsCount = 0;
    while (word != NULL){
        word = strtok (NULL, pDelimeters);

        *(textResult + wordsCount) = (const char *) strdup(word);
        wordsCount++;
    }

    *(textResult + wordsCount) = NULL;
    return textResult;
}

char* removeElementsFromArray(char* pText){
    char *write = pText, *read = pText;

    do {
    if (*read != ' ')
       *write++ = *read;
    } while (*read++);

    return pText;
}


int main(){
    printf("Tarea Corta 2-10%\nSherlock\tAlgoritmos geneticos y paralelismo");
    printf("\nOscar Cortes Cordero\t20116136191");
    printf("\nLeyendo codigos dentro de la carpeta Code...\n");
    char** fileNames = loadFilesNamesList(); //The program files from Code/ are called
    char** listCodeString = (char** const) malloc(sizeof(char * const));

    printf("\n\nLos codigos encontrados son:\n");
    int currentFile = 0;

    while ( *(fileNames + currentFile) != NULL) {
        printf("\n");
        printf(*(fileNames + currentFile));
        currentFile++;
    }

    listCodeString = loadFilesList(fileNames);

    printf("\n---+++---+++---+++---+++---+++---+++---\n");
    char ** blackList = loadBlackList();
    int variablesSum = 0;
    int magicNumbersSum = 0;
    int exceptionSum = 0;
    int repeatedCodeSum = 0;

    //Part to make this paralelo(?

    char * const fileString = (char * const) fileToString("Codes/J-ArrayList.jar");

    printf("\nNumber of blacklist variables: %d.",findVariablesTraces(fileString, blackList));
    printf("\nPublic with no throw: %d.", findExceptionTraces(fileString));
    printf("\nNagicNumbers found: %d.", findMagicNumberTraces(fileString));
    printf("\nRepeated code lines found: %d.", findRepeatedCodeTraces(fileString));

    printf("\n\n\nEnd");

    return 0;
}


//Testing C awesomeness
/*
    unsigned short short1 = 32;
    unsigned short short2 = 128;
    unsigned short short3 = short1 | short2;
    printf("a: %hu\n", short3);

    Population* testPopulation = population_new();
    addSubject(testPopulation, 1);
    //End
*/
