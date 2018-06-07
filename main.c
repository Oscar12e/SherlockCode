#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <dirent.h>

typedef struct Population Population, *ptrPopulation;

int getFileLines(char* filename);
char* fileToString(char* filename);
char** loadFilesList();
int findVariablesTraces();
int findRepeatedCodeTraces();
int findExceptionTraces();
int findMagicNumberTraces();



int findVariablesTraces(const char * text){

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

    char * const fileString = (char * const) fileToString("Codes/J-ArrayList.jar");
    puts("The hell:");

    puts("Amount2: ");
    printf("%d", strlen(fileString) );

    int linesAmount = getFileLines(fileString); //O(n)
    puts("Counter done\n");
    printf("Lines: %d", linesAmount);

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
