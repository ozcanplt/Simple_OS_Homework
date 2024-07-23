#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Struct of the file
typedef struct
{
    int ID;
    char name[10];
    char file_path[50];
    int number_of_read;
    int number_of_write;
    bool is_read;
    bool is_written;
} file;

// Struct of the program
typedef struct
{
    int ID;
    char name[10];
    int read_file_id;
    int write_file_id;
}program;

void create_new_file(int fileID, char *fileName, char *filePath, file **allFiles, int *fileCount, int *maxFiles);
void create_new_program(int programID, char *programName, program **allPrograms, int *programCount, int *maxPrograms);
void read_file(int fileID, int programID, file **allFiles, program **allPrograms, int fileCount, int programCount);
int find_file_index(int fileID, file *allFiles, int fileCount);
int find_program_index(int programID, program *allPrograms, int programCount);
void write_to_file(int fileID, int programID, file **allFiles, program **allPrograms, int fileCount, int programCount);
void close_all_files_for_program(int programID, file **allFiles, program **allPrograms, int fileCount, int programCount);
void display_all_files(file *allFiles, int fileCount);
void display_all_programs(program *allPrograms, int programCount);


void create_new_file(int fileID, char *fileName, char *filePath, file **allFiles, int *fileCount, int *maxFiles)
{
    if (*fileCount == *maxFiles)
    {
        *maxFiles *= 2;
        file *temp = (file*)realloc(*allFiles, sizeof(file)*(*maxFiles));
        if (temp == NULL)
        {
            printf("Memory allocation failed!");
            return;
        }
        *allFiles = temp;
    }

    for(int i = 0; i<*fileCount; i++)
    {
        if(fileID == (*allFiles)[i].ID)
        {
            printf("File ID already exists");
            return;
        }
    }
        (*allFiles)[*fileCount].ID = fileID;
        strncpy((*allFiles)[*fileCount].name, fileName, sizeof((*allFiles)[*fileCount].name) - 1);
        (*allFiles)[*fileCount].name[sizeof((*allFiles)[*fileCount].name) - 1] = '\0';
        strncpy((*allFiles)[*fileCount].file_path, filePath, sizeof((*allFiles)[*fileCount].file_path) - 1);
        (*allFiles)[*fileCount].file_path[sizeof((*allFiles)[*fileCount].file_path) - 1] = '\0';

        (*allFiles)[*fileCount].number_of_read = 0;
        (*allFiles)[*fileCount].number_of_write = 0;
        (*allFiles)[*fileCount].is_read = false;
        (*allFiles)[*fileCount].is_written = false;

        (*fileCount)++;
        printf("File with ID %d created successfully\n", fileID);
}

void create_new_program(int programID, char *programName, program **allPrograms, int *programCount, int *maxPrograms)
{
    if (*programCount == *maxPrograms)
    {
        *maxPrograms *= 2;
        program *temp = (program*)realloc(*allPrograms, sizeof(file)*(*maxPrograms));
        if (temp == NULL)
        {
            printf("Memory allocation failed!");
            return;
        }
        *allPrograms = temp;
    }

    for(int i = 0; i<*programCount; i++)
    {
        if(programID == (*allPrograms)[i].ID)
        {
            printf("Program ID already exists");
            return;
        }
    }

    (*allPrograms)[*programCount].ID = programID;
    strncpy((*allPrograms)[*programCount].name, programName, sizeof((*allPrograms)[*programCount].name) - 1);
    (*allPrograms)[*programCount].name[sizeof((*allPrograms)[*programCount].name) - 1] = '\0';
    (*allPrograms)[*programCount].read_file_id = -1;
    (*allPrograms)[*programCount].write_file_id = -1;

    (*programCount)++;
    printf("Program with ID %d created successfully\n", programID);
}

void read_file(int fileID, int programID, file **allFiles, program **allPrograms, int fileCount, int programCount)
{
    int indexP = find_program_index(programID, *allPrograms, programCount);
    int indexF = find_file_index(fileID, *allFiles, fileCount);
    if ((indexP == -1)||(indexF == -1))
    {
        printf("No such a program or file exists!\n");
        return;
    }

    if ((*allFiles)[indexF].is_written == true)
    {
        printf("The file is currently being written\n");
        return;
    }

    if ((*allFiles)[indexF].number_of_read >= 2)
    {
        printf("The file reached maximum number of reads\n");
        return;
    }

    
    (*allFiles)[indexF].number_of_read++;
    (*allFiles)[indexF].is_read = true;
    (*allPrograms)[indexP].read_file_id = fileID;

    printf("Program ID %d is reading File with ID %d\n", programID, fileID);
}

void write_to_file(int fileID, int programID, file **allFiles, program **allPrograms, int fileCount, int programCount)
{
    int indexP = find_program_index(programID, *allPrograms, programCount);
    int indexF = find_file_index(fileID, *allFiles, fileCount);
    if ((indexP == -1)||(indexF == -1))
    {
        printf("No such a program or file exists!\n");
        return;
    }

    if ((*allFiles)[indexF].is_read == true)
    {
        printf("The file is currently being read\n");
        return;
    }

    if ((*allFiles)[indexF].number_of_write >= 1)
    {
        printf("The file has reached maximum number of writes\n");
        return;
    }

    (*allFiles)[indexF].number_of_write++;
    (*allFiles)[indexF].is_written = true;
    (*allPrograms)[indexP].write_file_id = fileID;

    printf("Program ID %d is writing to File with ID %d\n", programID, fileID);
}

void release_reading_file(int programID, file **allFiles, program **allPrograms, int fileCount, int programCount)
{
    int indexP = find_program_index(programID, *allPrograms, programCount);
    if (indexP == -1)
    {
        printf("ERROR: No program found!\n");
        return;
    }

    int read_file_id = (*allPrograms)[indexP].read_file_id;

    if (read_file_id == -1)
    {
        printf("Program isnt reading any file at the moment!\n");
        return;
    }

    int indexF = find_file_index(read_file_id, *allFiles, fileCount);

    if (indexF == -1)
    {
        printf("ERROR: No file to READ!\n");
        return;
    }

    (*allFiles)[indexF].number_of_read--;
    if ((*allFiles)[indexF].number_of_read == 0)
    {
        (*allFiles)[indexF].is_read = false;
    }
    (*allPrograms)[indexP].read_file_id = -1;

    printf("File with ID %d is released from program with ID %d(READ)\n",read_file_id, programID);
}

void release_writing_file(int programID, file **allFiles, program **allPrograms, int fileCount, int programCount)
{
    int indexP = find_program_index(programID, *allPrograms, programCount);
    if (indexP == -1)
    {
        printf("ERROR: No program found!\n");
        return;
    }

    int write_file_id = (*allPrograms)[indexP].write_file_id;

    if (write_file_id == -1)
    {
        printf("Program isnt writing to any file at the moment!\n");
        return;
    }

    int indexF = find_file_index(write_file_id, *allFiles, fileCount);

    if (indexF == -1)
    {
        printf("ERROR: No file to WRITE!\n");
        return;
    }

    (*allFiles)[indexF].number_of_write--;
    if ((*allFiles)[indexF].number_of_write == 0)
    {
        (*allFiles)[indexF].is_written = false;
    }
    (*allPrograms)[indexP].write_file_id = -1;

    printf("File with ID %d is released from program with ID %d (WRITE)\n",write_file_id, programID);
}

void close_all_files_for_program(int programID, file **allFiles, program **allPrograms, int fileCount, int programCount)
{
    int indexP = find_program_index(programID, *allPrograms, programCount);
    if (indexP == -1)
    {
        printf("ERROR: No program found!\n");
        return;
    }

    bool released_read = false;
    bool released_write = false;

    if ((*allPrograms)[indexP].read_file_id != -1)
    {
        release_reading_file(programID, allFiles, allPrograms,  fileCount,  programCount);
        released_read = true;
    }

    if ((*allPrograms)[indexP].write_file_id != -1)
    {
        release_writing_file(programID, allFiles, allPrograms,  fileCount,  programCount);
        released_write = true;
    }

    if (released_read||released_write)
    {
        printf("All files have been released for program with ID %d",programID);
    }
    else
    {
        printf("No files have been found to release for program with ID %d",programID);
    }
}

void display_all_files(file *allFiles, int fileCount)
{
    if (fileCount == 0)
    {
        printf("No files in the system.\n");
        return;
    }

    printf("All Files in the System:\n");
    printf("------------------------\n");
    
    for(int i = 0; i < fileCount; i++)
    {
        printf("File ID: %d\n", allFiles[i].ID);
        printf("Name: %s\n", allFiles[i].name);
        printf("Path: %s\n", allFiles[i].file_path);
        printf("Number of reads: %d\n", allFiles[i].number_of_read);
        printf("Number of writes: %d\n", allFiles[i].number_of_write);
        printf("Is being read: %s\n", allFiles[i].is_read ? "Yes" : "No");
        printf("Is being written: %s\n", allFiles[i].is_written ? "Yes" : "No");
        printf("------------------------\n");
    }
}

void display_all_programs(program *allPrograms, int programCount)
{
    if (programCount == 0)
    {
        printf("No programs in the system.\n");
        return;
    }

    printf("All Files in the System:\n");
    printf("------------------------\n");

    for(int i = 0; i < programCount; i++)
    {
        printf("File ID: %d\n", allPrograms[i].ID);
        printf("Name: %s\n", allPrograms[i].name);
        printf("Read file ID: %d\n", allPrograms[i].read_file_id);
        printf("Write file ID: %d\n", allPrograms[i].write_file_id);
    }
}

int find_program_index(int programID, program *allPrograms, int programCount)
{
    for (int i = 0; i < programCount; i++)
    {
        if ((allPrograms)[i].ID == programID)
        {
            return i;
        }
    }
    return -1;
}

int find_file_index(int fileID, file *allFiles, int fileCount)
{
    for (int i = 0; i < fileCount; i++)
    {
        if ((allFiles)[i].ID == fileID)
        {
            return i;
        }
    }
    return -1;
}

int main() 
{
    file *allFiles = malloc(sizeof(file) * 4);  
    int fileCount = 0;
    int maxFiles = 4;

    program *allPrograms = malloc(sizeof(program) * 4);  
    int programCount = 0;
    int maxPrograms = 4;

    create_new_file(1, "file1.txt", "/path/to/file1", &allFiles, &fileCount, &maxFiles);
    create_new_program(12205,"game.exe",&allPrograms, &programCount, &maxPrograms);

    read_file(1, 12205, &allFiles, &allPrograms, fileCount, programCount);
    write_to_file(1, 12205, &allFiles, &allPrograms, fileCount, programCount);

    display_all_files(allFiles,fileCount);

    printf("%s",allFiles[1].ID);

    free(allFiles);
    return 0;
}
