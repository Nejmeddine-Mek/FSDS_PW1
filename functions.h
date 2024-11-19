#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#define MAXLEN 200




typedef struct{
    int nb_Blocks;
    int nb_records;
    int nb_chars;
    int nb_del_chars;
}Header;

typedef struct{
    int key;
    bool eraser;
    char firstName[35];
    char lastName[35];
    char school[64];
}Record;

typedef struct {
    int nb_records;
    int maxKey;
    int minKey;
    char info[MAXLEN];
    bool overlaps;

} TOVS_Block;

typedef struct {
    int nb_records;
    bool overlaps;
    char info[MAXLEN];
} Block;

typedef struct{
   FILE *file;
   Header header;
}TnOVS_file;

typedef struct {
    FILE* file;
    Header header;
}TOVS_file;

extern char typeOfFile[6];
extern char nameOfFile[35];

extern TOVS_file orderedFile;
extern TnOVS_file unorderedFile;


void functionalityTOVS(int k);
void functionalityTnOVS(int k);

int arrow(int pos, int match);
int Menu(char *fileType);
int Integer(const char *input);
bool isValid(char *s);
void substring(char *s,char delimiter,int *beginningIndex, char *output);
Record parse(char *s);
char *sliceString(char *input, int beg, int End);
char *stringify(Record parcel,const char delimiter);


int openTOVSFile(TOVS_file *file, const char *fileName,const char mode);
int closeTOVSFile(TOVS_file file);
int getTOVSHeader(TOVS_file file,int field);
int setTOVSHeader(TOVS_file *file,int field, int value);
void displayTOVSHeader(TOVS_file file, char *fileName);
int bulkLoadingTOVS(TOVS_file *file, TOVS_Block *data,int dataLen,int nbOfRecords, int nbOfChars);
int loadTOVSFile(TOVS_file *file, float loadingFactor);
int writeTOVSBlock(TOVS_file *file, TOVS_Block block, int position);
int readTOVSBlock(TOVS_file file,int position, TOVS_Block *data);
bool searchTOVS(TOVS_file file, int key, int *numberOfBlock, int *beginningPosition);
int deleteTOVS(TOVS_file *file,int key);
void displayOverlappingInformationTOVS(TOVS_file file);
void displayBlockTOVS(TOVS_file file, int numberOfBlock);
void displayAllTOVSFile(TOVS_file file);
int allocateTOVSBlock(TOVS_file *file);
void updateBlockInfo(TOVS_Block *block,char *placeholder);
int writeAndShift(TOVS_file *file,char *infoToInsert, Record data, int blockNumber, TOVS_Block currentBlock);
int insertInTOVSFile(TOVS_file *file, Record data);
//------------------------------------------------------------------------------

int openTnOVSFile(TnOVS_file *file, const char *fileName, const char mode);
int setHeader(TnOVS_file *file,int field,int val);
int getHeader(TnOVS_file file, int field);
int closeTnOVSFile(TnOVS_file file);
int allocateBlock(TnOVS_file *file);
int writeBlock(FILE *file,Block data,int position);
int readBlock(FILE *file,int position, Block *data);
int bulkLoadingTnOVS(TnOVS_file *file, Block *data,int dataLen,int nbOfRecords, int nbOfChars);
int loadTnOVSFile(TnOVS_file *file);
void disPlayHeader(char *fileName, TnOVS_file file);
void displayAllFile(TnOVS_file file);
bool searchTnOVS(TnOVS_file file, int key, int *blockNumber, int *position);
int insertInTnOVSFile(TnOVS_file *file, Record data);
void displayBlock(TnOVS_file file, int numberOfBlock);
int deleteFromTnOVS(TnOVS_file *file,int key);
void displayOverlappingInformation(TnOVS_file file);


int renewTnOVSFile(TnOVS_file file,const char *fileName);
int renewTOVSFile(TOVS_file file,const char *fileName);
void concatenateTwoTnOVSFiles(TnOVS_file file1, TnOVS_file file2);
void concatenateTwoTOVSFiles(TOVS_file file1, TOVS_file file2);
void intersectionOfTwoTOVSFiles(TOVS_file file1, TOVS_file file2);
void intersectionOfTwoTnOVSFiles(TnOVS_file file1, TnOVS_file file2);
#endif // FUNCTIONS_H_INCLUDED
