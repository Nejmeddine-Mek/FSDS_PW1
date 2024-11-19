# include "functions.h"

//                 *********************************************************
//                  WORK DONE BY:
//                      MEKENTICHI Nejem Eddine
//                      ARHAB Yacine
//                      The only function function that was not implemented is the physical deletion of the record
//                     for both TOVS and TnOVS
//---------------------------------------
char typeOfFile[6];
char nameOfFile[35];

TOVS_file orderedFile;
TnOVS_file unorderedFile;
//----------------------------------------
 // this function runs after the menu to select which function to run, works for TOVS type
void functionalityTOVS(int k){
    int key = 0;
    TOVS_file file1, file2;
    char name1[35], name2[35];
    switch (k)
    {
    case 0:
        printf("enter the file Name:  ");
        fgets(nameOfFile,35,stdin);
        nameOfFile[strlen(nameOfFile) - 1] = '\0';
        if(openTOVSFile(&orderedFile,nameOfFile,'o') == 1){
            MessageBox(NULL,"Files opened successfully","Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(NULL,"Something went wrong","Failure", MB_OK | MB_ICONERROR);
        }
        break;
    case 1:
        printf("enter the file Name:  ");
        fgets(nameOfFile,35,stdin);
        nameOfFile[strlen(nameOfFile) - 1] = '\0';
        if(openTOVSFile(&orderedFile,nameOfFile,'n') == 1){
            MessageBox(NULL,"File created successfully","Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(NULL,"Couldn't create the file","Failure", MB_OK | MB_ICONERROR);
        }
        break;
    case 2:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            // the loading factor is set to 0.7 by default
            loadTOVSFile(&orderedFile,0.7);
        }
        break;
    case 3:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            displayTOVSHeader(orderedFile,nameOfFile);
        }
        break;
    case 4:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            Record new;
            new.eraser = 0;
            printf("enter the first name: ");
            fgets(new.firstName,35,stdin);
            new.firstName[strlen(new.firstName) - 1] = '\0';

            printf("enter the last name: ");
            fgets(new.lastName,35,stdin);
            new.lastName[strlen(new.lastName) - 1] = '\0';

            printf("enter the school name: ");
            fgets(new.school,35,stdin);
            new.school[strlen(new.school) - 1] = '\0';

            printf("enter the key: ");
            scanf("%d", &new.key);
            if(insertInTOVSFile(&orderedFile,new) == 0){
                MessageBox(NULL,"Record inserted Successfully!","Success",MB_OK);
            }  else {
                MessageBox(NULL,"Couldn't insert, key repeated","Failure", MB_OK | MB_ICONSTOP);
            }
        }
        break;
    case 5:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            int i = 0; int j = 0;
            printf("Enter key: ");
            scanf("%d",&key);
            if(searchTOVS(orderedFile,key,&i,&j)){
                // read it
                TOVS_Block *buffer = (TOVS_Block *)malloc(sizeof(TOVS_Block));
                char *s = (char *)malloc(sizeof(char) * 2 * MAXLEN);
                char *temp = (char *)malloc(sizeof(char) * 144);
                readTOVSBlock(orderedFile,i,buffer);
                strcpy(s,buffer->info);
                if(buffer->overlaps){
                    int *index = (int *)malloc(sizeof(int));
                    *index = 0;
                    readTOVSBlock(orderedFile,i + 1,buffer);
                    substring(buffer->info,'|',index,temp);
                    strcat(s,temp);
                    free(index);
                    memset(temp,0,sizeof(temp));
                }
                substring(s,'|',&j,temp);
                Record output = parse(temp);
                if(realloc(temp, sizeof(char) * MAXLEN) == NULL){
                    free(temp);
                    temp = (char *)malloc(sizeof(char) * MAXLEN);
                }
                sprintf(temp,"      Key:   %d\n      First Name:   %s\n      Last Name:   %s\n      School:   %s\n",output.key,output.firstName,output.lastName,output.school);
                MessageBox(NULL,temp,"Information",MB_OK | MB_ICONINFORMATION);
                // display
            } else {
                MessageBox(NULL,"Record Not found!","Failure", MB_OK | MB_ICONERROR);
            }
        }
        break;
    case 6:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            printf("enter the key:  ");
            scanf("%d", &key);
            if(deleteTOVS(&orderedFile,key)){
                MessageBox(NULL,"Record deleted successfully","Success",MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(NULL,"Couldn't delete record, or not found","Failure",MB_OK | MB_ICONERROR);
            }
        }
        break;
    case 7:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            displayAllTOVSFile(orderedFile);
        }
        break;
    case 8:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            unsigned int blockIndex = 0;
            printf("enter the number of the block you want to read: ");
            scanf("%u",&blockIndex);
            displayBlockTOVS(orderedFile,(int)(blockIndex - 1));
        }
        break;
    case 9:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            displayOverlappingInformationTOVS(orderedFile);
        }
        break;
    case 10:
        if(orderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            if(getTOVSHeader(orderedFile,3) >= getTOVSHeader(orderedFile,2) * 0.5){
                renewTOVSFile(orderedFile,nameOfFile);
            } else {
                MessageBox(NULL,"No need to renew, deleted characters didn't exceed the 1/2 limit","Information",MB_OK | MB_ICONINFORMATION);
            }
        }
        break;
    case 11:

            printf("enter the name of the first file: ");
            scanf("%s",name1);
            printf("enter the name of the second file: ");
            scanf("%s",name2);
            openTOVSFile(&file1,name1,'o');
            openTOVSFile(&file2,name2,'o');
            concatenateTwoTOVSFiles(file1,file2);
            closeTOVSFile(file1);
            closeTOVSFile(file2);

        break;
    case 12:

            printf("enter the name of the first file: ");
            scanf("%s",name1);
            printf("enter the name of the second file: ");
            scanf("%s",name2);
            openTOVSFile(&file1,name1,'o');
            openTOVSFile(&file2,name2,'o');
            intersectionOfTwoTOVSFiles(file1,file2);
            closeTOVSFile(file1);
            closeTOVSFile(file2);

        break;
    }
}

// same as the previous function works for TnOVS type
void functionalityTnOVS(int k){
    int key = 0;
    TnOVS_file file1, file2;
    char name1[35], name2[35];
    switch (k){
    case 0:
        printf("enter the file name: ");
        fgets(nameOfFile,35,stdin);
        nameOfFile[strlen(nameOfFile) - 1] = '\0';
        if(openTnOVSFile(&unorderedFile,nameOfFile,'o') == 1){
            MessageBox(NULL,"Files opened successfully","Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(NULL,"Something went wrong","Failure", MB_OK | MB_ICONERROR);
        }
        break;
    case 1:
        printf("enter the file name: ");
        fgets(nameOfFile,35,stdin);
        nameOfFile[strlen(nameOfFile) - 1] = '\0';
        if(openTnOVSFile(&unorderedFile,nameOfFile,'n') == 1){
            MessageBox(NULL,"File created successfully","Success", MB_OK | MB_ICONINFORMATION);
        } else {
            MessageBox(NULL,"Couldn't create the file","Failure", MB_OK | MB_ICONERROR);
        }
        break;
    case 2:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            loadTnOVSFile(&unorderedFile);
        }
        break;
    case 3:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            disPlayHeader(nameOfFile,unorderedFile);
        }
        break;
    case 4:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            Record new;
            new.eraser = 0;
            printf("enter the first name: ");
            fgets(new.firstName,35,stdin);
            new.firstName[strlen(new.firstName) - 1] = '\0';

            printf("enter the last name: ");
            fgets(new.lastName,35,stdin);
            new.lastName[strlen(new.lastName) - 1] = '\0';

            printf("enter the school name: ");
            fgets(new.school,35,stdin);
            new.school[strlen(new.school) - 1] = '\0';

            printf("enter the key: ");
            scanf("%d", &new.key);
            if(insertInTnOVSFile(&unorderedFile,new) == 0){
                MessageBox(NULL,"Record inserted Successfully!","Success",MB_OK);
            }  else {
                MessageBox(NULL,"Couldn't insert, key repeated","Failure", MB_OK | MB_ICONSTOP);
            }
        }
        break;
    case 5:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            int block = 0, position = 0;
            printf("enter the key: ");
            scanf("%d",&key);
            if(searchTnOVS(unorderedFile,key,&block,&position)){
                Block *buffer = (Block *)malloc(sizeof(Block));
                char *s = (char *)malloc(sizeof(char) * 2 * MAXLEN);
                char *temp = (char *)malloc(sizeof(char) * 144);
                readBlock(orderedFile.file,block,buffer);
                strcpy(s,buffer->info);
                if(buffer->overlaps){
                    int *index = (int *)malloc(sizeof(int));
                    *index = 0;
                    readBlock(orderedFile.file,block + 1,buffer);
                    substring(buffer->info,'|',index,temp);
                    strcat(s,temp);
                    free(index);
                    memset(temp,0,sizeof(temp));
                }
                substring(s,'|',&position,temp);
                Record output = parse(temp);
                if(realloc(temp, sizeof(char) * MAXLEN) == NULL){
                    free(temp);
                    temp = (char *)malloc(sizeof(char) * MAXLEN);
                }
                sprintf(temp,"      Key:   %d\n      First Name:   %s\n      Last Name:   %s\n      School:   %s\n",output.key,output.firstName,output.lastName,output.school);
                MessageBox(NULL,temp,"Information",MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(NULL,"Record Not found!","Failure", MB_OK | MB_ICONERROR);
            }
        }
        break;
    case 6:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            printf("enter key:  ");
            scanf("%d", &key);
            if(deleteFromTnOVS(&unorderedFile,key)){
                MessageBox(NULL,"Record deleted successfully","Success",MB_OK | MB_ICONINFORMATION);
            } else {
                MessageBox(NULL,"Couldn't delete record, or not found","Failure",MB_OK | MB_ICONERROR);
            }
        }
        break;
    case 7:
        if( unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            displayAllFile(unorderedFile);
        }
        break;
    case 8:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            unsigned int index = 0;
            printf("enter the block Number: ");
            scanf("%u", &index);
            displayBlock(unorderedFile,index - 1);
        }
        break;
    case 9:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            displayOverlappingInformation(unorderedFile);
        }
        break;
    case 10:
        if(unorderedFile.file == NULL){
            MessageBox(NULL,"no file is Opened!","Warning",MB_OK | MB_ICONWARNING);
        } else {
            if(getHeader(unorderedFile,3) >= getHeader(unorderedFile,2) * 0.5 ){
                renewTnOVSFile(unorderedFile,nameOfFile);
            } else {
                MessageBox(NULL,"No need to renew, deleted characters didn't exceed the 1/2 limit","Information",MB_OK | MB_ICONINFORMATION);
            }
        }
        break;
    case 11:

            printf("enter the name of the first file: ");
            scanf("%s",name1);
            printf("enter the name of the second file: ");
            scanf("%s",name2);
            openTnOVSFile(&file1,name1,'o');
            openTnOVSFile(&file2,name2,'o');
            concatenateTwoTnOVSFiles(file1,file2);
            closeTnOVSFile(file1);
            closeTnOVSFile(file2);

        break;
    case 12:
            printf("enter the name of the first file: ");
            scanf("%s",name1);
            printf("enter the name of the second file: ");
            scanf("%s",name2);
            openTnOVSFile(&file1,name1,'o');
            openTnOVSFile(&file2,name2,'o');
            intersectionOfTwoTnOVSFiles(file1,file2);
            closeTnOVSFile(file1);
            closeTnOVSFile(file2);
        break;
    }
}


//--------------------------------------------------------
// this function selects the option in the menu to be highlighted
int arrow(int pos, int match){
    if(pos == match){
        printf("\033[1;34m");
    } else {
        printf("\033[0;37m");
    }
}
// and this one here is the common menu

int Menu(char *fileType){
    int c = 0;
    int position = 0;
    while(c != 13){
    system("CLS");
             printf("\033[0;37m File Type: %s                       \n\n", fileType);
    arrow(0,position); printf("1-Open a file                              \n");
    arrow(1,position); printf("2-Create a new file                          \n");
    arrow(2,position); printf("3-Load new file (only for new files)                            \n");
    arrow(3,position); printf("4-Display Header                             \n");
    arrow(4,position); printf("5-insert in a file                           \n");
    arrow(5,position); printf("6-Search by key                             \n");
    arrow(6,position); printf("7-Delete by key                             \n");
    arrow(7,position); printf("8-Display all the file                         \n");
    arrow(8,position); printf("9-Display one block                           \n");
    arrow(9,position); printf("10-Display overlapping information                    \n");
   arrow(10,position); printf("11-Renew File (if 50% of characters are deleted)                                \n");
   arrow(11,position); printf("12-Concatenate two files                                \n");
   arrow(12,position); printf("13-intersection of two files                                \n");
    c = getch();
    switch (c)
    {
    case 72:
        position--;
        if(position == -1) position = 12;
        break;
    case 80:
        position = (position + 1) % 13;
        break;
    default:
        break;
    }
    }
    return position;
}

// This function converts a given string into an integer, works for signed integers
int Integer(const char *input){
    int power = 0;
    int output = 0;
    int condition = 0;
    int i = strlen(input) - 1;
    bool sign = input[0] == '-' ? true:false; //assign true if negative, or false if positive
    if(sign){
        condition = 1;
    }
    while(i >= condition){  // then do basic conversion from string to integer
        output += (int)(input[i--] - 48) * pow(10,power++);
    }
    if(sign){
        return -output;
    }
    return output;
}

// this function checks if a given string is valid or not, not very efficient, it just checks if the string is longer than 5 chars.
// then checks if the first 4 chars are string representation of digits
bool isValid(char *s){
    if(strlen(s) <= 5){
        return false;
    }
    for(int i = 0; i < 4; i++){
        if( s[i] < '0' || s[i] > '9'){
            return false;
        }
    }
    return true;
}

// this function extracts a substring from a given string (s), based on a given delimiter, returns a sting and an index t continue from s
void substring(char *s,char delimiter,int *beginningIndex, char *output){
    int i = *beginningIndex;
    int j = 0;
    int n = strlen(s);
    while(s[i] != delimiter && i < n){
        output[j++] = s[i++];
    }
    *beginningIndex = i + 1; //because at i we have that delimiter
    output[j] = '\0';
}

// this function parses a string and returns its equivalent record
// it follows a very straightforward approach
Record parse(char *s){
    char temp[64];
    int stringIndex = 0;
    Record data;
    substring(s,'$',&stringIndex,temp);
    data.key = Integer(temp);
    memset(temp, 0, sizeof(temp));

    substring(s,'$',&stringIndex,temp);
    data.eraser = temp[0] == '1';
    memset(temp, 0, sizeof(temp));

   substring(s,'$',&stringIndex,temp);
    sprintf(data.firstName,"%s",temp);
    memset(temp, 0, sizeof(temp));



    substring(s,'$',&stringIndex,temp);
    sprintf(data.lastName,"%s",temp);
    memset(temp, 0, sizeof(temp));

    substring(s,'\0',&stringIndex,temp);
    sprintf(data.school,"%s",temp);
    memset(temp, 0, sizeof(temp));

    return data;
}

// slices a string and returns a substring form index beg to end
char *sliceString(char *input, int beg, int End){
    int size = (End - beg);
    char *output = (char *)malloc(sizeof(char) * size);

    for(int i = 0; beg < End; i++){
        output[i]= input[beg++];
    }
    output[size ] = '\0';
    return output;
}

// this function converts a record into a string to be written in the block (buffer) then the file
char *stringify(Record parcel,const char delimiter){   // we convert our record into a string, separated by some given delimiter (fixed in the whole file)
    char *output = (char *)malloc(sizeof(char) * 144);
    sprintf(output,"%.4d%c%d%c%s%c%s%c%s|",parcel.key,delimiter,parcel.eraser,delimiter,parcel.firstName,delimiter,parcel.lastName,delimiter,parcel.school);
    return output;
}

// FROM NOW ON, WE WILL HAVE ONLY FILE OP. FUNCTIONS

// opens a tovs file
int openTOVSFile(TOVS_file *file, const char *fileName,const char mode){
    if(toupper(mode) == 'N'){           // if new file, we create a file, and we set all the fields of the header to 0
        file->file = fopen(fileName,"wb+");
        file->header.nb_Blocks = 0;
        file->header.nb_chars = 0;
        file->header.nb_del_chars = 0;
        file->header.nb_records = 0;
        return 1;
    } else if(toupper(mode) == 'O'){    // if old, we open the file
        file->file = fopen(fileName,"rb+");
        if(file->file == NULL){
            return -1;          // not found
        }
        if(fread(&(file->header),sizeof(Header),1,file->file) != 1){
            return -2;          // couldn't read header (something went wrong)
        }
        return 1;   // done
    }
    return -2;          // something went wrong, mode isn't valid
}

// closes a tovs file
int closeTOVSFile(TOVS_file file){
    rewind(file.file);
    if(fwrite(&(file.header),sizeof(Header),1,file.file) != 1){
        return -1;  // couldn't write the header
    }
    fclose(file.file);  // closing the file
    return 1;   // done
}

// gets the value of a given field from the header
int getTOVSHeader(TOVS_file file,int field){
    switch (field)
    {
    case 1:
        return file.header.nb_Blocks;           // number of blocks
    case 2:
        return file.header.nb_chars;            // number of written chars.
    case 3:
        return file.header.nb_del_chars;        // number of removed chars (logical deletion)
    case 4:
        return file.header.nb_records;          // number of records
    }
    return -1;  //invalid field
}


// updates the value of a given filed, the idea is a little bit similar to the getters ad setters in other languages like JS
int setTOVSHeader(TOVS_file *file,int field, int value){
    switch (field)
    {
    case 1:
        file->header.nb_Blocks = value;     // update number of blocks
        break;
    case 2:
        file->header.nb_chars = value;      // update number of written chars.
        break;
    case 3:
        file->header.nb_del_chars = value;  // update the number of removed chars
        break;
    case 4:
        file->header.nb_records = value;        // update the number of records
        break;
    default:
        return -1;      // not valid field
    }
    return 0;
}

// display the header of a tovs file
void displayTOVSHeader(TOVS_file file, char *fileName){
    printf("File type:  TOVS\n");
    printf("File name: %s\n", fileName);
    printf("Number of Blocks:  %d\n", getTOVSHeader(file,1));
    printf("Number of characters:  %d\n", getTOVSHeader(file,2));
    printf("Number of deleted characters:  %d\n", getTOVSHeader(file,3));
    printf("Number of records:  %d\n", getTOVSHeader(file,4));
}


// bulk loading function of the tovs file
int bulkLoadingTOVS(TOVS_file *file, TOVS_Block *data,int dataLen,int nbOfRecords, int nbOfChars){
    if(file->file == NULL){     // checking if the file is open or not
        return -1;
    }
    // we insert an array of Blocks  all at once
    fseek(file->file,sizeof(Header),SEEK_SET);
    if(fwrite(data,sizeof(TOVS_Block),dataLen,file->file) != dataLen){
        return 0;   // something went wrong if we couldn't write the data
    }
    // then after writing we update the header
    setTOVSHeader(file,1,dataLen);
    setTOVSHeader(file,2,nbOfChars);
    setTOVSHeader(file,4,nbOfRecords);
    return 1;       // done
}

// this function loads a tovs file
int loadTOVSFile(TOVS_file *file, float loadingFactor){
    printf("Please assign ordered keys to the records, otherwise, the program will encounter problems doing other tasks!\n");
    int lastKey = -1;                   // we begin by a negative key to make sure all our keys are positive >= 0
    int numberOfRecords = 0;                 // we keep track of te number of records we want to insert
    Record data;                             // the following two variables are just placeholders
    char s[100];
    FILE *dataSet = fopen("dataSet.dat","rb+");         // open the data set file
    if(dataSet == NULL){
        return -1;                              // if the file is removed for some reason, we stop here
    }
    printf("how many records do you want to load: ");   // re read the keys to get ordered ones
    scanf("%d", &numberOfRecords);                   // we read the number of records the user wants to add
    getchar();                                  // remove the newline char. from the input stream
    TOVS_Block *arrayOfBlocks = (TOVS_Block *)malloc(sizeof(TOVS_Block) * (numberOfRecords / 3));  //allocate an array of blocks to load
    int j = 0;
    int block_index = 0;    // these variables will be used to keep track of the records in each block
    int charCount = 0;       // and the number of characters t=inserted in the whole file
                    // resetting the first block before we begin using it
            (arrayOfBlocks + block_index)->maxKey = -1; // max to a very small value
            (arrayOfBlocks + block_index)->minKey = 1564894555;  // we set the min to a very big value
            (arrayOfBlocks + block_index)->nb_records = 0;
            (arrayOfBlocks + block_index)->overlaps = 0;

    for(int i = 0; i < numberOfRecords; i++){
        fread(&data,sizeof(Record),1,dataSet);
        printf("enter the key of this record: ");           // we read a record from the dataSet and we reassign a key to it to keep order
        scanf("%d", &data.key);
        while(data.key <= lastKey){
            printf("please maintain the order, enter a bigger key: ");   // we make sure the user maintains the ascending order of the keys
            scanf("%d", &data.key);
        }
        lastKey = data.key;
        strcpy(s,stringify(data,'$'));              // convert the record to a string
        int n = strlen(s);                  // get the length of the string we want to write

        for(int k = 0; k < n; k++){         // we insert our string char. by char. to keep track of our index and prevent going out of bounds
            (arrayOfBlocks + block_index)->info[j++] = s[k];
            ++charCount;                    // keep track of the number of chars. we wrote
        }
        // we update the information of the block, maximum key, minimum key and the number of records
        (arrayOfBlocks + block_index)->maxKey = (arrayOfBlocks + block_index)->maxKey > data.key ? (arrayOfBlocks + block_index)->maxKey:data.key;
        (arrayOfBlocks + block_index)->minKey = (arrayOfBlocks + block_index)->minKey < data.key ? (arrayOfBlocks + block_index)->minKey:data.key;
        (arrayOfBlocks + block_index)->nb_records += 1;
        if(j >= loadingFactor * MAXLEN && i + 1 < numberOfRecords){             // if we exceed the loading factor we move to the next block (next elemnet in the array)

                ++block_index;
                // reset the necessary fields of the next block and we start writing into it

                (arrayOfBlocks + block_index)->maxKey = -1; // max to a very small value
                (arrayOfBlocks + block_index)->minKey = 1564894555;  // we set the min to a very big value
                (arrayOfBlocks + block_index)->nb_records = 0;
                (arrayOfBlocks + block_index)->overlaps = 0;
                j = 0;
        }

    }
    // after we finish writing, we write the whole array into the file, all at once
    bulkLoadingTOVS(file,arrayOfBlocks,block_index+1,numberOfRecords,charCount);
    return 0;
}

// writes a block
// takes the buffer and the index of the block, note that blocks are 0-indexed everywhere in our program
int writeTOVSBlock(TOVS_file *file, TOVS_Block block, int position){
    if(file->file == NULL){
        return -1;              // check if the file is open
    }
    fseek(file->file,sizeof(Header) + sizeof(TOVS_Block) * position, SEEK_SET);
    if(fwrite(&block,sizeof(TOVS_Block),1,file->file) != 1){        // write and return -0 if the op. fails
        return 0;
    }
    return 1;           // and return 1 if all is done successfully
}


//reads a block and loads it into a buffer
int readTOVSBlock(TOVS_file file,int position, TOVS_Block *data){
    if(file.file == NULL){
        return -1;          // check if the file is open
    }
    fseek(file.file,sizeof(Header) + sizeof(TOVS_Block) * position, SEEK_SET);
    if(fread(data,sizeof(TOVS_Block),1,file.file) != 1){
        return 0;               // if reading fails, return 0
    }
    return 1;           // if it succeeds, return 1
}

    // searching into a tovs file
bool searchTOVS(TOVS_file file, int key, int *numberOfBlock, int *beginningPosition){
    if(file.file == NULL){                  // make sure the file is open
        return false;
    }
    int overlapped = 0;
    int low = 0;
    int high = getTOVSHeader(file,1) - 1;
    while(high >= low){

        int middle = (high + low) / 2;
        TOVS_Block data;
        readTOVSBlock(file,middle,&data);       // perform a regular binary search until we find the block we want
        if(data.maxKey < key) low = middle + 1;
        else if(data.minKey > key) high = middle - 1;
        else {
            if(numberOfBlock != NULL){
                *numberOfBlock = middle;        // assign that index to the argument we have if it is not null
            }
                //  read the block, if it overlaps, we read the next block to complete the last string
             char placeholder[2 * MAXLEN];
             strcpy(placeholder,data.info);

             if(data.overlaps){
                    // code for overlapping
                overlapped = 0;
                readTOVSBlock(file,middle + 1,&data);
                char s[100];
                substring(data.info,'|',&overlapped,s);
                strcat(placeholder,s);
             }
            // keep slicing the string and parsing until we either find the record and return true after assigning the position to the argumaent
            // or we return false if we don't find the record
            int n = strlen(placeholder);
            char stringToParse[144];
            int i = 0;
             while (i < n){   // while we're still inbounds of the big string we read
                Record output;
                memset(stringToParse,0,sizeof(stringToParse));
                substring(placeholder,'|',&i,stringToParse);
                if(isValid(stringToParse)){
                    output = parse(stringToParse);
                    if(output.key > key){
                        if(beginningPosition != NULL){
                        *beginningPosition = i - strlen(stringToParse) - 1;
                        }
                        return false;       // not found and return the insert position, we might need it
                    }
                    if(!output.eraser && output.key == key){
                        if(beginningPosition != NULL){
                        *beginningPosition = i - strlen(stringToParse) - 1;
                        }
                        return true;        // return false
                    }
                }
            }

        }
    }
    if(numberOfBlock != NULL){
        *numberOfBlock = (high + low) / 2;      // return the middle value we had if we didn't even find the block, it will be useful when inserting
    }
    return false;
}

 // logical deletion
int deleteTOVS(TOVS_file *file,int key){            // the concept is simple, search for the record, if we find it, we update the eraser field and set it to 1
    int blockNumber = 0, offset = 0;                    // otherwise, we just quit
    if(!searchTOVS(*file,key,&blockNumber,&offset)){
        return -1;      // not found
    }
    TOVS_Block data;
    char placeholder[2 * MAXLEN];
    char stringToParse[144];
    readTOVSBlock(*file,blockNumber,&data);
    strcpy(placeholder,data.info);
        if(data.overlaps){
            // code for overlapping
            TOVS_Block *temp = (TOVS_Block *)malloc(sizeof(TOVS_Block));
            int overlapped = 0;
            readTOVSBlock(*file,blockNumber + 1,temp);
            char s[100];
            substring(temp->info,'|',&overlapped,s);
            strcat(placeholder,s);
            free(temp);
        }
    substring(placeholder,'|',&offset,stringToParse);
    int indexForeRefill = offset - strlen(stringToParse) - 1;

    Record student = parse(stringToParse);
    student.eraser = 1;
    int n = strlen(stringToParse);
    strcpy(stringToParse,stringify(student,'$'));           // don't reduce the number of chars. to be able to renew the file later
    setTOVSHeader(file,3,getTOVSHeader(*file,3) + n);
    setTOVSHeader(file,4,getTOVSHeader(*file,4) -1);
    for(int i  = 0; i < n ; i++ ){
        placeholder[indexForeRefill++] = stringToParse[i];
    }
    offset = 0;
    indexForeRefill = 0;
    n = strlen(placeholder);        // read and slice until we find the string
    while(offset < n){
        data.info[indexForeRefill++] = placeholder[offset++];
        if(indexForeRefill == MAXLEN - 1){
            data.info[indexForeRefill] = '\0';

            writeTOVSBlock(file,data,blockNumber);
            blockNumber += 1;
            readTOVSBlock(*file,blockNumber,&data);
            indexForeRefill = 0;
        }
    }

    writeTOVSBlock(file,data,blockNumber);  // write the modified buffer
    return 1;           // quit after finishing
}

// display the overlapping information
void displayOverlappingInformationTOVS(TOVS_file file){
    TOVS_Block data;
    for(int i = 0; i < getTOVSHeader(file,1); i++){ // go through all the file
        readTOVSBlock(file,i,&data);
        if(data.overlaps){      // if the block overlaps, we complete the string
            int infoIndex = 0;
            char stringToParse[144];
            int n = strlen(data.info);
            while(infoIndex < n){ // find the last string
                substring(data.info,'|',&infoIndex,stringToParse);
            }
            infoIndex = 0;      // parse it then display it
            TOVS_Block *temp = (TOVS_Block *)malloc(sizeof(TOVS_Block));
            readTOVSBlock(file,i + 1,temp);
            char s[144];
            substring(temp->info,'|',&infoIndex,s);
            strcat(stringToParse,s);
            Record student = parse(stringToParse);
            printf("Block Number %3.4d\n",i + 1);
            if(!student.eraser){

                printf("Student with key:  %4d\n",student.key);
                printf("first Name:  %s\n",student.firstName);
                printf("Last Name:  %s\n",student.lastName);
                printf("School:  %s\n\n",student.school);
            } else {
                printf("element deleted\n\n");
            }
            free(temp);  // free memory allocated

        }
    }
}

// display a block

void displayBlockTOVS(TOVS_file file, int numberOfBlock){
    if(numberOfBlock > getTOVSHeader(file,1)){              // read the block, check for overlapping, complete the last string
        return ;                                                 // extract substrings, parse them and display  costs 2 I/O operations in the worst case (overlapping)
    }                                                                 // 1 I/O operation when ther is not overlapping
    TOVS_Block data;
    char placeHolder[2 * MAXLEN];
    readTOVSBlock(file,numberOfBlock,&data);
    if(data.nb_records == 0){
        printf("block empty!\n");
        return;
    }
    strcpy(placeHolder,data.info);
    int i = 0;
    if(data.overlaps){
        readTOVSBlock(file,numberOfBlock + 1,&data);
        char temp[50];
        substring(data.info,'|',&i,temp);
        strcat(placeHolder,temp);
        i = 0;
    }
    int n = strlen(placeHolder);        // we simply read the block, check or overlapping and handle it, then we substring and parse then display each valid string
    char stringToParse[144];
    while (i < n){
        Record output;
        memset(stringToParse,0,sizeof(stringToParse));
        substring(placeHolder,'|',&i,stringToParse);
        if(isValid(stringToParse)){
            output = parse(stringToParse);
            if(!output.eraser){
                printf("Student with key:  %.4d\n",output.key);
                printf("First Name:  %s\n",output.firstName);
                printf("Last Name:  %s\n",output.lastName);
                printf("School:  %s\n\n",output.school);
            }
        }
    }

}

// display all the file

void displayAllTOVSFile(TOVS_file file){
    char placeholder[2 * MAXLEN];               // identical to the unordered file traversal, read each block, check for overlapping
    int overlapped = 0;                             // complete the last record, extract substrings and parse then display,
    TOVS_Block temp;                                    // if half blocks overlap, it would cost 3 / 2 * N I/O operations
    for(int i = 0; i < getTOVSHeader(file,1); i++){         // could be optimized if we keep the next block after reading it in case of overlapping
        readTOVSBlock(file,i,&temp);                           // and it becomes N I/O operations always
        if(temp.nb_records > 0){
            strcpy(placeholder,temp.info);
            int infoIndex = overlapped;
            if(temp.overlaps){
                overlapped = 0;
                readTOVSBlock(file,i + 1,&temp);
                char s[100];
                memset(s,0,sizeof(s));
                substring(temp.info,'|',&overlapped,s);
                strcat(placeholder,s);
            } else {
                overlapped = 0;                 // this variable keeps the index where we begin reading in the next block, so that we make sure all strings are valid
            }

            char stringToParse[144];
            int n = strlen(placeholder);
            while (infoIndex < n){          // display each record after parsing its string
                Record student;
                memset(stringToParse,0,sizeof(stringToParse));
                substring(placeholder,'|',&infoIndex,stringToParse);
                if(isValid(stringToParse)){
                    if(!student.eraser){
                        printf("Student with key: %3.4d\n",student.key);
                        printf("First Name: %s\n",student.firstName);
                        printf("Last Name:  %s\n",student.lastName);
                        printf("School:     %s\n\n\n",student.school);
                    }
                }
                student = parse(stringToParse);


            }
        }
    }

}

// allocate an empty block in the file
int allocateTOVSBlock(TOVS_file *file){
    TOVS_Block temp;
    temp.nb_records = 0;
    temp.overlaps = 0;
    temp.maxKey = -1;
    temp.minKey = 21354866;
    fseek(file->file,sizeof(Header) + sizeof(TOVS_Block) * getTOVSHeader(*file,1),SEEK_SET);
    if(fwrite(&temp,sizeof(Block),1,file->file) != 1){
        return 0;   // could not allocate a block
    }
    setTOVSHeader(file,1,file->header.nb_Blocks + 1);
    return 1;   // task done successfully
}

// updates the block info (maxkey and minKey in particular)
void updateBlockInfo(TOVS_Block *block,char *placeholder){
    char *s = (char *)malloc(sizeof(char) * 144);   // we just go through the block and update the minKey and the maxKey
    int pos = 0;
    int n = strlen(placeholder);
    while(pos < n){
        substring(placeholder,'|',&pos,s);
        if(isValid(s)){
            Record temp = parse(s);
            block->maxKey = block->maxKey > temp.key ? block->maxKey:temp.key;
            block->minKey = block->minKey < temp.key ? block->minKey:temp.key;
        }
    }
    free(s);
}

//writes and shifts to maintain the order and the structure of the file
int writeAndShift(TOVS_file *file,char *infoToInsert, Record data, int blockNumber, TOVS_Block currentBlock){
    bool lastBlock = 0;
    int n = strlen(infoToInsert); // get the length of the string we will be inserting
    int j = 0;
    int i = 0;
    while (i < n){
        currentBlock.info[j++] = infoToInsert[i++];         // we write the string char. by char. to avoid getting out of bounds unintentionally
        if(j == MAXLEN ){                                  // when we're at the end of the string
            currentBlock.info[MAXLEN - 1] = '\0';   // null terminate the string
            if(blockNumber == getTOVSHeader(*file,1) - 1){  // if there is no next block, allocate a new one
                allocateTOVSBlock(file);
                lastBlock = 1;
            }
            currentBlock.overlaps = 1;  // set the overlapping variable of the current block to 1
            updateBlockInfo(&currentBlock,infoToInsert);
            currentBlock.nb_records += 1;           // add a record to our block
            setTOVSHeader(file,4,getTOVSHeader(*file,4) + 1);
            writeTOVSBlock(file,currentBlock,blockNumber);    // write the block
            ++blockNumber;          // increment the block index and reset j then read a new block
            j = 0;
            readTOVSBlock(*file,blockNumber,&currentBlock);
            if(lastBlock){
                memset(currentBlock.info,0,MAXLEN);                                 // if last block we insert right away for two reasons:
                strcpy(currentBlock.info,sliceString(infoToInsert,i-1,n));              //1- if all blocks are full, we won't shift more than 144 and 144 < MAXLEN = 200
                updateBlockInfo(&currentBlock,currentBlock.info);                       //2- there is no extra data to insert so we don't need concatenate anything else
                writeTOVSBlock(file,currentBlock,blockNumber);
                return 0;
            }
            strcpy(infoToInsert,sliceString(infoToInsert,i-1,n));   // keep only the information we didn't insert in the string
            strcat(infoToInsert,currentBlock.info);
                            // concatenate with the information of the read block, and repeat until we write a block which is not 100%full
            i = 0;
            n = strlen(infoToInsert);       // get the new length of the string
        }


    }
    updateBlockInfo(&currentBlock,infoToInsert);
    writeTOVSBlock(file,currentBlock,blockNumber);      // final write of the block that was lastly treated
    return 0;
}

// inserts in a file
int insertInTOVSFile(TOVS_file *file, Record data){
    int blockNumber = 0, insertPosition = 0;   // initialize the block number and the insertion position to zero
    if(searchTOVS(*file,data.key,&blockNumber,&insertPosition)){  // perform a search for that element (Record)
        return 1;   // return 1 if found
    }

    char parsedString[144]; // if not, we declare a string to hold the stringified record
    strcpy(parsedString,stringify(data,'$'));  // we stringify the given record, and we copy it into parsedString

    TOVS_Block block;       // declare a buffer to read blocks
    char placeholder[2 * MAXLEN];       // declare a placeholder to hold the strings stored within blocks
    // if the file is empty we allocate a block and we insert in it then we return 0 operation done successfully
    if(getTOVSHeader(*file,1) == 0){
        allocateTOVSBlock(file);                        // allocation
        readTOVSBlock(*file,blockNumber,&block);    // reading
        strcpy(block.info,parsedString);            // assign the record to the the field of info withing the buffer
        block.nb_records = 1;
        block.overlaps = 0;
        block.maxKey = data.key;
        block.minKey = data.key;
        setTOVSHeader(file,2,getTOVSHeader(*file,2) + strlen(parsedString));
        setTOVSHeader(file,3,0);
        setTOVSHeader(file,4,1);
        writeTOVSBlock(file,block,blockNumber); // re-write the block
        return 0;       // end of the algorithm
    }

    readTOVSBlock(*file,blockNumber,&block);    // we read the block whose index (number) was returned from the search
    int i = 0, j = 0;
    if(data.key > block.maxKey){  // if the record's key we're inserting is greater than all the other keys in the block we do what follows
        j = strlen(block.info);        // keep the length of the information saved already in the block
        int n = strlen(parsedString);
        if(j == MAXLEN - 1){   // if the block is completely filled
                                // we insert at the beginning of the next block
            blockNumber += 1;
            readTOVSBlock(*file,blockNumber,&block);
            char overlappedPart[100];          // we shall truncate the overlapped portion if it exists
            substring(block.info,'|',&i,overlappedPart);

            if(!isValid(overlappedPart)){       // if it's a valid string, then there is no overlapping, so we concatenate
                strcat(overlappedPart,"|");     // our strings right away then we call the writeAndShift function do write the new information
                strcpy(placeholder,overlappedPart);
                strcat(placeholder,parsedString);
                strcat(placeholder,sliceString(block.info,i,strlen(block.info)));
            } else {                                   // if it's not a valid string, we put our string, after the overlapping part, and before the first valid string in the
                strcpy(placeholder,parsedString);   // next block
                strcat(placeholder,block.info);
            }

            writeAndShift(file,placeholder,data,blockNumber,block);
        }
        else if(j + n < MAXLEN){       // if the sum of the length of the information we already have and the new information fits within the bounds
            block.maxKey = data.key;    // of the block, we concatenate and write directly
            block.nb_records += 1;
            strcat(block.info,parsedString);
            setTOVSHeader(file,2,getTOVSHeader(*file,2) + n);
            writeTOVSBlock(file,block,blockNumber);
        } else {           // if we still have some space, but it's not enough, we concatenate, and writeAndShift will do the rest
            strcpy(placeholder,block.info);
            strcat(placeholder,parsedString);
            writeAndShift(file,placeholder,data,blockNumber,block);
        }
    }
    else if(data.key < block.minKey){       // if we have to write at the beginning of a block, it's valid only when inserting in the first block
                                           // we concatenate ( newStr + oldStr ) then writeAndShift does the rest, just like in the previous case
        strcpy(placeholder,parsedString);
        strcat(placeholder,block.info);
        writeAndShift(file,placeholder,data,blockNumber,block);

    } else {
        strcpy(placeholder,sliceString(block.info,0,insertPosition));                    // if we have to insert in the middle of the block, it's even simpler
        strcat(placeholder,parsedString);                                                // the search procedure will return an index to insert at it, we use it to slice the old data, and put
        strcat(placeholder,sliceString(block.info,insertPosition , strlen(block.info))); // the new data in between (dat1|dat2) + (newDat) ==> (dat1|newDat|dat2) then we pass it to writeAndShift
        writeAndShift(file,placeholder,data,blockNumber,block);
    }
    setTOVSHeader(file,2,getTOVSHeader(*file,2) + strlen(parsedString)); // update the number of chars. we wrote
    setTOVSHeader(file,2,getTOVSHeader(*file,4) + 1);
    return 0;
}

//  TnOVS functions
//------------------------------------------------------------------------------------------------------------------
// opens a TnOVS file, identical logic to the openTOVSFile
int openTnOVSFile(TnOVS_file *file, const char *fileName, const char mode){
    if(toupper(mode) == 'N'){
            file->file = fopen(fileName,"wb+");
            file->header.nb_Blocks = 0;
            file->header.nb_chars = 0;
            file->header.nb_del_chars = 0;
            file->header.nb_records = 0;
            return 1;                      //process done successfully
    } else if(toupper(mode) == 'O'){
            file->file = fopen(fileName,"rb+");
            if(file->file == NULL){
                return -1;                //file not found
            }
            fread(&file->header,sizeof(Header),1,file->file);
            return 1;                    //process done successfully
    }
    return -2;              //invalid mode
}

// updates the header of a TnOVS file, similar to the TOVS's setHeader function
int setHeader(TnOVS_file *file,int field,int val){
    switch(field){
    case 1:
        file->header.nb_Blocks = val;
        break;
    case 2:
        file->header.nb_chars = val;
        break;
    case 3:
        file->header.nb_del_chars = val;
        break;
    case 4:
        file->header.nb_records = val;
        break;
    default:
        return -1; // field not valid
    }
    return 1;   // task done
}

// also analogous to the getHeader for the TOVS file
int getHeader(TnOVS_file file, int field){
    switch(field){
    case 1:
        return file.header.nb_Blocks;

    case 2:
        return file.header.nb_chars;

    case 3:
        return file.header.nb_del_chars;

    case 4:
        return file.header.nb_records;

    default:
        return -1; // field not valid
    }
    return -1;
}

// closes a file, identical to TOVS closeFile
int closeTnOVSFile(TnOVS_file file){
    if(file.file == NULL){
        return -1;  //file not found
    }
    rewind(file.file);
    fwrite(&file.header,sizeof(Header),1,file.file);
    return 1;       // done successfully
}

// allocateBlock, similar to the allocateBlock of TOVS file (we have different structs, that's why we have two copies of each function)
int allocateBlock(TnOVS_file *file){
    Block temp;
    temp.nb_records = 0;
    temp.overlaps = 0;
    fseek(file->file,sizeof(Header) + sizeof(Block) * getHeader(*file,1),SEEK_SET);
    if(fwrite(&temp,sizeof(Block),1,file->file) != 1){
        return 0;   // could not allocate a block
    }
    setHeader(file,1,file->header.nb_Blocks + 1);
    return 1;   // task done successfully
}

// writes a block
int writeBlock(FILE *file,Block data,int position){
    if(file == NULL){
        return -1;
    }
    fseek(file,sizeof(Header) + sizeof(Block) * position, SEEK_SET);
    if(fwrite(&data,sizeof(Block),1,file) != 1){
        return 0;
    }
    return 1;
}

// reads a block and loads it into a buffer
int readBlock(FILE *file,int position, Block *data){
    if(file == NULL){
        return -1;
    }
    fseek(file,sizeof(Header) + sizeof(Block) * position, SEEK_SET);
    if(fread(data,sizeof(Block),1,file) != 1){
        return 0;
    }
    return 1;
}

// loads an array of blocks all at once
int bulkLoadingTnOVS(TnOVS_file *file, Block *data,int dataLen,int nbOfRecords, int nbOfChars){
    if(file->file == NULL){
        return -1;
    }
    fseek(file->file,sizeof(Header),SEEK_SET);
    if(fwrite(data,sizeof(Block),dataLen,file->file) != dataLen){
        return 0;
    }
    // update the header
    setHeader(file,1,dataLen);
    setHeader(file,2,nbOfChars);
    setHeader(file,4,nbOfRecords);
    return 1;
}

// loading TnOVS
int loadTnOVSFile(TnOVS_file *file){
    // we don't ask for keys, they are un-ordered by default so we assign right away
    int numberOfRecords = 0;
    Record data;
    char s[100];
    FILE *dataSet = fopen("dataSet.dat","rb+");
    printf("how many records do you want to load: ");
    scanf("%d", &numberOfRecords);
    getchar();
    Block *arrayOfBlocks = (Block *)malloc(sizeof(Block) * (numberOfRecords / 3));
    int j = 0;
    int block_index = 0;
    int charCount = 0;          // keep track of the number of chars.
    // reset the values of the first block before beginning
    (arrayOfBlocks)->nb_records = 0;
    (arrayOfBlocks)->overlaps = 0;
    for(int i = 0; i < numberOfRecords; i++){
        fread(&data,sizeof(Record),1,dataSet);
        strcpy(s,stringify(data,'$'));
        int n = strlen(s);
        (arrayOfBlocks + block_index)->nb_records += 1;
        for(int k = 0; k < n; k++){
            (arrayOfBlocks + block_index)->info[j++] = s[k];
            ++charCount;
            if(j == MAXLEN){        // the loading factor is 100%, so all blocks will overlap except for the last one

                if(k == n - 1){
                    (arrayOfBlocks + block_index)->overlaps = 0;
                } else {
                    (arrayOfBlocks + block_index)->overlaps = 1;
                }
                setHeader(file,2, getHeader(*file,2) + j);
                ++block_index; // we move to the next block
                j = 0;
            }
        }
    }
    setHeader(file,2, getHeader(*file,2) + j);      // update the header
    bulkLoadingTnOVS(file,arrayOfBlocks,block_index+1,numberOfRecords,charCount);   // load the file
    return 0;
}

// displays a header
void disPlayHeader(char *fileName, TnOVS_file file){
    printf("%s header information:  \n", fileName);
    printf("Number of Blocks:  %.4d\n",getHeader(file,1));
    printf("Number of Records:  %.4d\n",getHeader(file,4));
    printf("Number of Characters:  %.4d\n",getHeader(file,2));
    printf("Number of Characters deleted:  %.4d\n",getHeader(file,3));
}

// displays all the file
void displayAllFile(TnOVS_file file){
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    Block temp;
    for(int i = 0; i < getHeader(file,1); i++){     // go through all the file,
        readBlock(file.file,i,&temp);
        if(temp.nb_records >= 0){
            strcpy(placeholder,temp.info);
            int infoIndex = overlapped;
            if(temp.overlaps){      // if there is overlapping we read the next block and we extract the rest of the last record
                overlapped = 0;
                readBlock(file.file,i + 1,&temp);
                char s[100];
                memset(s,0,sizeof(s));
                substring(temp.info,'|',&overlapped,s);
                strcat(placeholder,s);
            } else {
                overlapped = 0;
            }

            char stringToParse[144];        // slice the big string until the end, and parse each substring then display it
            int n = strlen(placeholder);
            while (infoIndex < n){
                Record student;
                memset(stringToParse,0,sizeof(stringToParse));
                substring(placeholder,'|',&infoIndex,stringToParse);
                if(isValid(stringToParse)){
                    if(!student.eraser){        // if the record isn't deleted, we display its content
                        printf("Student with key: %3.4d\n",student.key);
                        printf("First Name: %s\n",student.firstName);
                        printf("Last Name:  %s\n",student.lastName);
                        printf("School:     %s\n\n\n",student.school);
                    }
                }
                student = parse(stringToParse);


            }
        }
    }

}

// searchs a TnOVS file
bool searchTnOVS(TnOVS_file file, int key, int *blockNumber, int *position){
    char placeholder[2 * MAXLEN];  // similar to the display file function, we just compare with a key, and return T/F
    int overlapped = 0;                 // also a blockNumber and a position
    Block temp;
    for(int i = 0; i < getHeader(file,1); i++){   // linear search, always check if there is overlapping, if so, read the rest of the last record
        readBlock(file.file,i,&temp);              // and keep the index to begin from it when reading the next block
        strcpy(placeholder,temp.info);
        int infoIndex = overlapped;
        if(temp.overlaps){
            overlapped = 0;
            readBlock(file.file,i + 1,&temp);
            char s[100];
            substring(temp.info,'|',&overlapped,s);
            strcat(placeholder,s);
        } else {
            overlapped = 0;
        }
        char stringToParse[144];
        int n = strlen(placeholder);
        while (infoIndex < n)
        {
            Record student;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&infoIndex,stringToParse);
            student = parse(stringToParse);
            if(student.key == key && !student.eraser){
                if(blockNumber != NULL){
                    *blockNumber = i;
                }
                if(position != NULL){
                    *position = infoIndex - strlen(stringToParse) - 1;
                }
                return true;
            }

        }
    }
    return false;
}

// inserts in a TnOVS block
int insertInTnOVSFile(TnOVS_file *file, Record data){
    int i = 0, j = 0;       // make sure the key doesn't exist in the file
    if(searchTnOVS(*file,data.key,&i,&j)){
        return 1;
    }
    Block chunk;    // if it doesn't exist, we read the last block and we insert in it
    int charCount = 0;
    char temp[100];
    strcpy(temp,stringify(data,'$'));
    if(getHeader(*file,1) == 0){   // if there is no block we allocate a block and read it, if there are blocks already
        allocateBlock(file);        // we insert at the end of the last block
        readBlock(file->file,0,&chunk);
    }
    else{
        readBlock(file->file,getHeader(*file,1) - 1,&chunk);
    }

    j = strlen(chunk.info);
    int n = strlen(temp);

    chunk.nb_records++;
    while(i < n){
        chunk.info[j++] = temp[i++];
        ++charCount;
        if(j == MAXLEN){
            chunk.overlaps = 1;
            writeBlock(file->file,chunk,getHeader(*file,1) - 1);
            allocateBlock(file);
            readBlock(file->file,getHeader(*file,1) - 1,&chunk);
            j = 0;
        }

    }
    chunk.info[j] = '\0';

    writeBlock(file->file,chunk,getHeader(*file,1) - 1);
    setHeader(file,4,getHeader(*file,4) + 1);
    setHeader(file,2,getHeader(*file,2) + charCount);
    return 0;
}

// display a block
void displayBlock(TnOVS_file file, int numberOfBlock){
    if(numberOfBlock > getHeader(file,1) - 1){
        printf("Out of Bounds!\n");         // check if we're still inbounds
        return;
    }
    Block data;
    char placeHolder[2 * MAXLEN];       // read the block, handle overlapping
    readBlock(file.file,numberOfBlock,&data);
    if(data.nb_records == 0){
        printf("Block Empty!\n");
        return;
    }
    strcpy(placeHolder,data.info);
    int i = 0;
    if(data.overlaps){
        readBlock(file.file,numberOfBlock + 1,&data);
        char temp[50];
        substring(data.info,'|',&i,temp);
        strcat(placeHolder,temp);
        i = 0;
    }
    int n = strlen(placeHolder);
    char stringToParse[144];
    while (i < n){                      // parse and display each record
        Record output;
        memset(stringToParse,0,sizeof(stringToParse));
        substring(placeHolder,'|',&i,stringToParse);
        if(isValid(stringToParse)){
            output = parse(stringToParse);
            if(!output.eraser){
                printf("Student with key:  %.4d\n",output.key);
                printf("First Name:  %s\n",output.firstName);
                printf("Last Name:  %s\n",output.lastName);
                printf("School:  %s\n\n",output.school);
            }
        }
    }

}

// logical deleting
int deleteFromTnOVS(TnOVS_file *file,int key){
    int blockNumber = 0, offset = 0;
    if(!searchTnOVS(*file,key,&blockNumber,&offset)){       // find the record
        printf("not found");
        return -1;
    }
    Block data;
    char placeHolder[144];
    readBlock(file->file,blockNumber,&data);
    substring(data.info,'|',&offset,placeHolder);               // read the block, then get the target string and then parse it

    int indexForeRefill = offset - strlen(placeHolder) - 1;
    if(offset >= MAXLEN){
        Block *temp = (Block *)malloc(sizeof(Block));
        readBlock(file->file,blockNumber + 1,temp);
        char k[100];
        int t = 0;
        substring(temp->info,'|',&t,k);
        strcat(placeHolder,k);
        free(temp);
    }
    Record student = parse(placeHolder);
    student.eraser = 1;
    int n = strlen(placeHolder);
    strcpy(placeHolder,stringify(student,'$'));  // we don't reduce the number of chars so that we can do the renewal later
    setHeader(file,3,getHeader(*file,3) + n);
    setHeader(file,4,getHeader(*file,4) -1);
    offset = 0;
    while(offset < n){                  // after setting the eraser field, we stringify again adn then rewrite
        data.info[indexForeRefill++] = placeHolder[offset++];
        if(indexForeRefill == MAXLEN){
            writeBlock(file->file,data,blockNumber);
            blockNumber += 1;
            readBlock(file->file,blockNumber,&data);
            indexForeRefill = 0;
        }
    }
    writeBlock(file->file,data,blockNumber);   // write the most recently read block after finishing
    return 1;
}

//display overlapping data
void displayOverlappingInformation(TnOVS_file file){        // identical logic to the TOVS version
    Block data;
    for(int i = 0; i < getHeader(file,1); i++){
        readBlock(file.file,i,&data);
        if(data.overlaps){
            int infoIndex = 0;
            char stringToParse[144];
            int n = strlen(data.info);
            while(infoIndex < n){
                substring(data.info,'|',&infoIndex,stringToParse);
            }
            infoIndex = 0;
            Block *temp = (Block *)malloc(sizeof(Block));
            readBlock(file.file,i + 1,temp);
            char s[144];
            substring(temp->info,'|',&infoIndex,s);
            strcat(stringToParse,s);
            Record student = parse(stringToParse);
            printf("Block Number %3.4d\n",i + 1);
            if(!student.eraser){

                printf("Student with key:  %4d\n",student.key);
                printf("first Name:  %s\n",student.firstName);
                printf("Last Name:  %s\n",student.lastName);
                printf("School:  %s\n\n",student.school);
            } else {
                printf("element deleted\n\n");
            }
            free(temp);

        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------
//     BONUS QUESTION, I DIDN'T TEST THEM ENOUGH :/
        // renew a file after deleting 50% of the chars.
int renewTnOVSFile(TnOVS_file file,const char *fileName){
    if(file.file == NULL){
        return -1;
    }
    // read each block and keep only records that aren't deleted in a big buffer (array) , at the end write them in the new file
    char newFileName[70];
    strcpy(newFileName,"new_");   // new file has the name new_${filename}
    strcat(newFileName,fileName);
    TnOVS_file newFile;
    openTnOVSFile(&newFile,newFileName,'n');        // open the new file
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    Block data;

    Block *newBuffer = (Block *)malloc(sizeof(Block) * getHeader(file,1));

    int block_index = 0;
    int infoPosition = 0;

    for(int i = 0; i < getHeader(file,1); i++){     // go through the old file, and read each block
        readBlock(file.file,i,&data);
        strcpy(placeholder,data.info);
        int j = 0;
        if(data.overlaps){
            readBlock(file.file,i + 1,&data);
            char temp[50];
            substring(data.info,'|',&j,temp);
            strcat(placeholder,temp);
            j = 0;
        }
        int n = strlen(placeholder);
        char stringToParse[144];
        while (j < n){      // get un-deleted data and insert it in the new file (I used a bulk loading method)
            Record output;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&j,stringToParse);
            if(isValid(stringToParse)){
                output = parse(stringToParse);
                if(!output.eraser){
                    strcpy(stringToParse,stringify(output,'$'));
                    int k = 0;
                    int infoLen = strlen(stringToParse);
                    newBuffer[block_index].nb_records += 1;
                        printf("%s",stringToParse);
                        getchar();
                    while(k < infoLen){

                        newBuffer[block_index].info[infoPosition++] = stringToParse[k++];

                        if(infoPosition == MAXLEN){
                            if( k == infoLen){
                                newBuffer[block_index].overlaps = 0;
                            }
                            else {
                                newBuffer[block_index].overlaps = 1;
                            }
                            ++block_index;
                            infoPosition = 0;
                        }
                    }
                }
            }
        }
    }
    bulkLoadingTnOVS(&newFile,newBuffer,block_index + 1,getHeader(file,4),getHeader(file,2));
    closeTnOVSFile(newFile);
    return 0;
}

// renews a tovs file, analogous logic to the one right above it
int renewTOVSFile(TOVS_file file,const char *fileName){
    if(file.file == NULL){
        return -1;
    }
    // read each block and keep only records that aren't deleted in a big buffer (array) , at the end write them in the new file
    char newFileName[70];
    strcpy(newFileName,"new_");
    strcat(newFileName,fileName);
    TOVS_file newFile;
    openTOVSFile(&newFile,newFileName,'n');
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    TOVS_Block data;

    TOVS_Block *newBuffer = (TOVS_Block *)malloc(sizeof(TOVS_Block) * getTOVSHeader(file,1));

    int block_index = 0;
    int infoPosition = 0;

    for(int i = 0; i < getTOVSHeader(file,1); i++){
        readTOVSBlock(file,i,&data);
        strcpy(placeholder,data.info);
        int j = 0;
        if(data.overlaps){
            readTOVSBlock(file,i + 1,&data);
            char temp[50];
            substring(data.info,'|',&j,temp);
            strcat(placeholder,temp);
            j = 0;
        }
        int n = strlen(placeholder);
        char stringToParse[144];
        while (j < n){
            Record output;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&j,stringToParse);
            if(isValid(stringToParse)){
                output = parse(stringToParse);
                if(!output.eraser){
                    strcpy(stringToParse,stringify(output,'$'));
                    int k = 0;
                    int infoLen = strlen(stringToParse);
                    newBuffer[block_index].nb_records += 1;
                    while(k < infoLen){

                        newBuffer[block_index].info[infoPosition++] = stringToParse[k++];
                    }
                    if(infoPosition >= 0.7 * MAXLEN){
                            ++block_index;
                            infoPosition = 0;

                    }
                }
            }
        }
    }
    bulkLoadingTOVS(&newFile,newBuffer,block_index + 1,getTOVSHeader(file,4),getTOVSHeader(file,2));
    closeTOVSFile(newFile);
    return 0;
}

// concatenates two tnovs files,
void concatenateTwoTnOVSFiles(TnOVS_file file1, TnOVS_file file2){
    TnOVS_file output;
    Block buffer;
    openTnOVSFile(&output,"ConcatenateTwoTnOVSfiles.dat",'n');  // insert the first file as it is, then try to insert each record from the second file until the end
                                                            // repeated keys won't be inserted
    // update the header of the new file
    setHeader(&output,1,getHeader(file1,1));
    setHeader(&output,2,getHeader(file1,2));
    setHeader(&output,3,getHeader(file1,3));
    setHeader(&output,4,getHeader(file1,4));
        // write all blocks of the first file
    for(int i = 0; i < getHeader(file1,1); i++){
        readBlock(file1.file,i,&buffer);
        writeBlock(output.file,buffer,i);
    }
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    for(int i = 0; i < getHeader(file2,1); i++){        // go through the second file
        readBlock(file2.file,i,&buffer);
        strcpy(placeholder,buffer.info);
        int infoIndex = overlapped;
        if(buffer.overlaps){
            overlapped = 0;
            readBlock(file2.file,i + 1,&buffer);
            char s[100];
            memset(s,0,sizeof(s));
            substring(buffer.info,'|',&overlapped,s);
            strcat(placeholder,s);
        } else {
            overlapped = 0;
        }

        char stringToParse[144];
        int n = strlen(placeholder);
        while (infoIndex < n){      // extract each record, if ont deleted, insert, the return value of the insert doesn't matter
            Record student;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&infoIndex,stringToParse);
            student = parse(stringToParse);
            if(!student.eraser){
                insertInTnOVSFile(&output,student);
            }

        }
    }
    closeTnOVSFile(output);
}

//concatenates two tovs files
// follows the exact same previous logic
void concatenateTwoTOVSFiles(TOVS_file file1, TOVS_file file2){
    TOVS_file output;
    TOVS_Block buffer;
    openTOVSFile(&output,"ConcatenateTwoTOVSfiles.dat",'n');       // write the first file as it is, then insert each record from the second file
    setTOVSHeader(&output,1,getTOVSHeader(file1,1));
    setTOVSHeader(&output,2,getTOVSHeader(file1,2));
    setTOVSHeader(&output,3,getTOVSHeader(file1,3));
    setTOVSHeader(&output,4,getTOVSHeader(file1,4));
    for(int i = 0; i < getTOVSHeader(file1,1); i++){
        readTOVSBlock(file1,i,&buffer);
        writeTOVSBlock(&output,buffer,i);
    }
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    for(int i = 0; i < getTOVSHeader(file2,1); i++){
        readTOVSBlock(file2,i,&buffer);
        strcpy(placeholder,buffer.info);
        int infoIndex = overlapped;
        if(buffer.overlaps){
            overlapped = 0;
            readTOVSBlock(file2,i + 1,&buffer);
            char s[100];
            memset(s,0,sizeof(s));
            substring(buffer.info,'|',&overlapped,s);
            strcat(placeholder,s);
        } else {
            overlapped = 0;
        }

        char stringToParse[144];
        int n = strlen(placeholder);
        while (infoIndex < n)
        {
            Record student;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&infoIndex,stringToParse);
            student = parse(stringToParse);
            if(!student.eraser){
                insertInTOVSFile(&output,student);
            }

        }
    }
    closeTOVSFile(output);
}
// the issue with these functions is that they keep the deleted records from the first file

// intersection of two tovs files
void intersectionOfTwoTOVSFiles(TOVS_file file1, TOVS_file file2){
    if (file1.file == NULL || file2.file == NULL){
        return;     // quit if one of the files is not open
    }
        // traverse the first file, and each time we extract a record, we check if it exists in the second file, if it does, we insert it in the new file
    TOVS_file outputFile;
    TOVS_Block buffer;
    openTOVSFile(&outputFile,"TOVSintersection.dat",'n');
    char placeholder[2 * MAXLEN];
    int overlapped = 0;
    for(int i = 0; i < getTOVSHeader(file1,1); i++){
        readTOVSBlock(file1,i,&buffer);
        strcpy(placeholder,buffer.info);
        int infoIndex = overlapped;
        if(buffer.overlaps){
            overlapped = 0;
            readTOVSBlock(file1,i + 1,&buffer);
            char s[100];
            memset(s,0,sizeof(s));
            substring(buffer.info,'|',&overlapped,s);
            strcat(placeholder,s);
        } else {
            overlapped = 0;
        }

        char stringToParse[144];
        int n = strlen(placeholder);
        while (infoIndex < n)
        {
            Record student;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&infoIndex,stringToParse);
            student = parse(stringToParse);
            if(!student.eraser){
                strcpy(stringToParse,stringify(student,'|'));
                int block = 0, pos = 0;
                if(searchTOVS(file2,student.key,&block,&pos)){
                    insertInTOVSFile(&outputFile,student);
                }
            }
        }
    }
    closeTOVSFile(outputFile);
}

// intersection of two tovs files, same logic
void intersectionOfTwoTnOVSFiles(TnOVS_file file1, TnOVS_file file2){
    if(file1.file == NULL || file2.file == NULL){
        return;
    }
// traverse the first file, and each time we extract a record, we check if it exists in the second file, if it does, we insert it in the new file
    TnOVS_file outputFile;
    Block buffer;
    openTnOVSFile(&outputFile,"TnOVSintersection.dat",'n');
    char placeholder[2 * MAXLEN];
    int overlapped = 0;

    for(int i = 0; i < getHeader(file1,1); i++){
        readBlock(file1.file,i,&buffer);
        strcpy(placeholder,buffer.info);
        int infoIndex = overlapped;
        if(buffer.overlaps){
            overlapped = 0;
            readBlock(file1.file,i + 1,&buffer);
            char s[100];
            memset(s,0,sizeof(s));
            substring(buffer.info,'|',&overlapped,s);
            strcat(placeholder,s);
        } else {
            overlapped = 0;
        }

        char stringToParse[144];
        int n = strlen(placeholder);
        while (infoIndex < n)
        {
            Record student;
            memset(stringToParse,0,sizeof(stringToParse));
            substring(placeholder,'|',&infoIndex,stringToParse);
            student = parse(stringToParse);
            if(!student.eraser){
                int block = 0, position = 0;
                if(searchTnOVS(file2,student.key,&block,&position)){
                    insertInTnOVSFile(&outputFile,student);
                }
            }
        }
    }
    closeTnOVSFile(outputFile);
}
// it would cost a lot if there are a lot of records where they intersect
// the bulk loading method would be better here
