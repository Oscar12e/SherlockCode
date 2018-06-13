#ifndef FILES_H_INCLUDED
#define FILES_H_INCLUDED

extern char* fileToString(char* filename);
extern char** loadFilesNamesList();
extern char** loadBlackList();
extern char** loadFilesList(char** pFileNames);

#endif // FILES_H_INCLUDED
