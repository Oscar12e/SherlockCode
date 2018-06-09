#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>

typedef struct Population Population, *ptrPopulation;

int getFileLines(char* filename);
char* fileToString(char* filename);
char** loadFilesList();
char** loadBlackList();


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
            printf( "\nPosition: %d\n", (int)(strstr( codeBackup, currentVariable )-pCode));
            //printf("\n%s", currentVariable);
            ++tracesFound;
        }
        currentVarIndex++;
        currentVariable = *(pBlackList + currentVarIndex);
    }

    return tracesFound;
}

int findRepeatedCodeTraces(const char * pCode){
    /*
*/
}

/**
    The function finds all the 'public' words in the code as all the 'Throw' words,
    then it just.. ahm.. makes a 'resta' to tell the difference between the two words
    found result.

    @param pCode: The code to be examined as a pointer to constant char
*/

int findExceptionTraces(const char * pCode){
    int publicFound = 0;
    int throwFound = 0;


    //while ( currentVariable != NULL  ) {                    //O(c) if we make a little cheating
    const char *codeBackup = pCode;
    //Pendiente: Revisar porque while(codeBackup) != NULL No funciona

    while (strstr( codeBackup, "public" ) != NULL){
        int position = (int) (strstr( codeBackup, "public" )-pCode);
        publicFound++;
        codeBackup = pCode + position+1;
    }

    codeBackup = pCode; //Backup its made again so the process can be reapeated whith Throw


    while (strstr( codeBackup, "Throw" ) != NULL){
        //printf( "\nPosition: %d\n", (int)(codeBackup-pCode));
        //printf("\n%s", currentVariable);
        codeBackup++;
        throwFound++;
    }
    printf("%d", publicFound);
    printf("\n%d", throwFound);
    return publicFound - throwFound;

}

int findMagicNumberTraces(const char * pCode){
    char * tokensToMagicNumbers[] = {"<", ">", "==", "<=", ">=", "!=", "+", "-", "*", "/", "%"};  //Se buscan los que esten a la derecha
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

char** loadFilesList(){
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
        closedir (dir);
    } else {
      /* could not open directory */
      return NULL;
    }
    *(fileNames + fileAmount) = NULL;

    return fileNames;
}


char** loadBlackList(){
    char * blackListTXT =  fileToString("BlackList.txt");
    char * word = (char*) malloc(sizeof(char));
    word = strtok (blackListTXT,"\n ,.;\0");

    char ** blackList = (char **) malloc(sizeof(char*));
    int wordsCount = 0;
    while (word != NULL){
        *(blackList + wordsCount) = malloc(sizeof(char));
        const char * currentVariable = (const char *) strdup(word);
        //*(blackList + wordsCount) = strdup(word);
        strcpy(*(blackList + wordsCount), " ");
        strcat(*(blackList + wordsCount), currentVariable);
        strcat(*(blackList + wordsCount), " ");
        //printf ("\n%s",word);

        word = strtok (NULL, "\n ,.;\0");
        wordsCount++;
    }

    *(blackList + wordsCount) = NULL;
    return blackList;
}

int main(){
    printf("Tarea Corta 2-10%\tGeneticos y paralelos\n");
    printf("Oscar Cortes Cordero\t20116136191\n\n");
    printf("Los codigos a evaluarse son:\n");

    char** fileNames = loadFilesList(); //The program files from Code/ are called
    int currentFile = 0;
    while (*(fileNames + currentFile) != NULL) {
        printf( *(fileNames + currentFile) );
        printf("\n");
        currentFile++;
    }

    printf("\n---+++---+++---+++---+++---+++---+++---+++---+++---+++---+++\n");


    //char str[] ="- This, a sample string.";
    char ** blackList = loadBlackList();

    int wordsCount = 0;
    while (*(blackList + wordsCount) != NULL) {
        printf("%s", *(blackList + wordsCount) );
        printf("\n");
        wordsCount++;
    }


    //Future fuction to load blacklist

    char * const fileString = (char * const) fileToString("Codes/J-ArrayList.jar");

    findVariablesTraces(fileString, blackList);
    printf("Public with no throw %d", findExceptionTraces(fileString));
    puts("\nThe hell:");

    puts(strstr("Hola", "ola "));
    puts("Amount2: ");
    printf("%d", strlen(fileString) );

    int linesAmount = getFileLines(fileString); //O(n)
    puts("Counter done\n");
    printf("Lines: %d", linesAmount);

    //printf ("%s",fileString);
    printf("\nEnd");

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
