#include "Files.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



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
        //free(currentVariable);
        wordsCount++;
    }

    *(blackList + wordsCount) = NULL;
    free(word);
    return blackList;
}


char** loadFilesList(char** pFileNames){
	
    char* fileName;
    char** filesResult = (char**) malloc(sizeof(char*));

    int nameIndex = 0;

    while ( *(pFileNames + nameIndex ) != NULL){
        //Por el largo de Codes/ + el largo del nombre + NULL
        fileName = (char*) malloc(sizeof(char) * 7 + strlen(*(pFileNames + nameIndex )));
        strcpy(fileName, "Codes/");
        //printf(strdup(*(pFileNames + nameIndex )));  //Memory leak(? pendign to be fixed -- Print is avaible meanwhile
        strcat(fileName, strdup(*(pFileNames + nameIndex )));
        *(filesResult + nameIndex) = fileToString(fileName);

        nameIndex++;
    }

    return filesResult;
}

char** loadFilesNamesList(){
    DIR *dir;
    struct dirent *ent;
    char** fileNames = NULL;
    int fileAmount = 0;
	int i = 0;

    if ((dir = opendir ("Codes")) != NULL) { // print all the files and directories within directory
        while ((ent = readdir (dir)) != NULL){
			
			char* string = strstr(ent->d_name, ".jar");
            if (string != NULL) { //Cualquier file más largo que .jar se toma en cuenta
				fileNames = realloc(fileNames, sizeof(char*) * ++fileAmount);
                fileNames[i++] = strdup(ent->d_name);
            }

        }
        closedir (dir);  //Close
        free(dir);
    } else {
      /* could not open directory */
      return NULL;
    }
    *(fileNames + fileAmount) = NULL;

    return fileNames;
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
    free(filePointer);
    return body;
}
