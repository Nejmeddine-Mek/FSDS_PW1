#include "./functions.h"


int main(int argc, char *argv[]){
    system("CLS");
    printf("\033[0;31m IMPORTANT:       \n\n");
    printf("\033[0;31m Please don't delete dataSet.dat file because it is essential for the loading of the file.       \n");
    printf("\033[0;31m it initially has 34 records in it, so the maximum number of records in a file loading is 34\n");
    printf("\033[0;31m There is a two files TOVSFile.dat and TnOVS.dat initially loaded with 20 records if you ever want to use them directly \n");
    printf("\033[0;31m The program is case sensitive, so make sure your inputs match the available options.            \n");
    printf("\033[0;31m The extension of the file must be included within the file name.        \n");
    printf("\033[0;31m Unfortunately, there is only one dataSet thus, for concatenation and intersection, the second file should be created and filled manually. \n");
    printf("\033[0;31m Menu is keyboard controlled.        \n\n\033[0;37m");
    system("PAUSE");
    system("CLS");
    int option = 0;
    do{
        system("CLS");
        printf("enter the file type TOVS/TnOVS (case sensitive): ");
        scanf("%s",typeOfFile);
        if(strcmp(typeOfFile,"TOVS") == 0){
            do{
                option = Menu(typeOfFile);
                printf("\n\n");
                getc(stdin);
                functionalityTOVS(option);
            }while(MessageBox(NULL,"Do you want to do another operation","question", MB_YESNO | MB_ICONQUESTION) == IDYES);
            if(orderedFile.file != NULL){
                closeTOVSFile(orderedFile);
                memset(nameOfFile,0,sizeof(nameOfFile));
            }
        } else if(strcmp(typeOfFile,"TnOVS") == 0){
            do{
                option = Menu(typeOfFile);
                printf("\n\n");
                functionalityTnOVS(option);
            }while(MessageBox(NULL,"Do you want to do another operation","question", MB_YESNO | MB_ICONQUESTION) == IDYES);

            if(unorderedFile.file != NULL){
                closeTnOVSFile(unorderedFile);
                memset(nameOfFile,0,sizeof(nameOfFile));
            }
        }
        else{ MessageBox(NULL,"Invalid type","Warning", MB_OK); }
    }while(MessageBox(NULL,"Do you want to continue","question", MB_YESNO | MB_ICONQUESTION) == IDYES);

    return 0;
}

