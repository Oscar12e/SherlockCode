#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <omp.h>
#include "Files.h"


#define LINES_TO_COMPARE_AGAINST 0
#define LINES_TO_COMPARE 0

#define VARIABLES_WEIGHT 0
#define MAGIC_NUMBERS_WEIGHT 0
#define EXCEPTION_WEIGHT 0
#define REPEATED_CODE_WEIGHT 0


typedef struct Population Population, *ptrPopulation;

int getFileLines(char* filename);

char* removeElementsFromArray(char* pText);
char** splitCodeLines(char* pText, int pLines);
int countApparition(const char * pText, const char* pSearchWord);


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
    int linesAmount = countApparition(pCode, "\n"); //O(n)
    char **codeLines = splitCodeLines(strdup(pCode),linesAmount);      //O(n)


    int linesToBeCompare = (int) linesAmount/2;
    int linesToBeCompareAgainst = (int) linesAmount/3;


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
        textBackup = pText + position+1; 								//The pointer is moved so it can read other apparition
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

char** splitCodeLines(char* pText, int pLines){
    char** textResult = (char **) malloc(sizeof(char*) * pLines);
    char * word = (char*) malloc(sizeof(char));
    word = strtok (pText, "\n");

    int wordsCount = 0;

    while (word != NULL){
        word = strtok (NULL, "\n");
        *(textResult + wordsCount) = strdup(word);
        wordsCount++;
    }

    free(word);
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
	printf("\n\n Fin de paralelos \n\n");

    printf("\nTarea Corta 2-10%\nSherlock\tAlgoritmos geneticos y paralelismo");
    printf("\nOscar Cortes Cordero\t20116136191");
    printf("\nLeyendo codigos dentro de la carpeta Code...\n");
    char** fileNames = (char**) malloc(sizeof(char*) * 10);
	fileNames = loadFilesNamesList(); //The program files from Code/ are called

    char** listCodeString = loadFilesList(fileNames);

    printf("\n\nLos codigos encontrados son:\n");
    int currentFile = 0;

    while ( *(fileNames + currentFile) != NULL) {
        printf("\n");
        //printf(*(fileNames + currentFile));
        currentFile++;
    }
	
	char ** blackList = loadBlackList();
	
    printf("\n---+++---+++---+++---+++---+++---+++---\n");
    
    int variablesSum = 0;
    int magicNumbersSum = 0;
    int exceptionSum = 0;
    int repeatedCodeSum = 0;

	int executionIndex = 0;
    //Part to make this paralelo(?
	/*Parallel part starts here*/
	char * fileString;
	
	printf("Iteracion equals %d", currentFile);
	
	#pragma omp parallel firstprivate(executionIndex)
	{
		for (executionIndex = 0; executionIndex < currentFile-1; executionIndex++) {
			
			//#pragma omp task 
			#pragma omp single 
			{
			fileString =  listCodeString[executionIndex];
			//fileString =  fileToString( "Codes/J-ArrayList.jar" ); //Dejar afuera
			
			variablesSum += findVariablesTraces(fileString, blackList);
			printf("\n\nNumber of blacklist variables: %d.", findVariablesTraces(fileString, blackList));
			
			exceptionSum += findExceptionTraces(fileString);
			printf("\nPublic with no throw: %d.", findExceptionTraces(fileString));
			
			magicNumbersSum += findMagicNumberTraces(fileString);
			printf("\nNagicNumbers found: %d.", findMagicNumberTraces(fileString));
			printf("\nArchivo %s ", fileNames[executionIndex]);
			printf("%d\n", omp_get_thread_num());
		
			}
			#pragma omp taskwait
			
		}

	}
	
	printf("\nResultados finales");
	printf("\n%d", variablesSum);
	printf("\n%d", magicNumbersSum);
	printf("\n%d", exceptionSum);
	
	/*
	
    char * const fileString = (char * const) fileToString("Codes/J-ArrayList.jar");


    printf("\nNumber of blacklist variables: %d.",findVariablesTraces(fileString, blackList));
    printf("\nPublic with no throw: %d.", findExceptionTraces(fileString));
    printf("\nNagicNumbers found: %d.", findMagicNumberTraces(fileString));
    //printf("\nRepeated code lines found: %d.", findRepeatedCodeTraces(fileString));
*/
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
