/*
  bin2header
  Turns a binary file into a C header for embedding inside exectuables.

  it’s a quick and dirty implementation of “xxd -i”

  Usage
  bin2header <input_file> > myheader.h

  prints result to stdout, ready to be redirected onto a file
*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_FILENAME_LENGTH 512 // I made this up, should probably use the real macro's OS offer

void PrintHelp(void);
int  StringReplaceChar(char *String, char Replace, char Replacement);

int main(int argc, char **argv)
{
    FILE *InputFile = NULL;
    char *Filename = NULL;
    long int FileSize = 0;

    // Parse Arguments
    if(argc == 1)
    {
        PrintHelp();
        return 0;
    }
    if(strncmp(argv[1], "--help", MAX_FILENAME_LENGTH) == 0 ||
       strncmp(argv[1], "-h", MAX_FILENAME_LENGTH) == 0)
    {
        PrintHelp();
        return 0;
    }

    // Open file, extract the filename, replace the last . with _
    InputFile = fopen(argv[1], "rb");

#if _WIN32
    Filename = strrchr(argv[1], '\\');
    if(Filename == NULL)
    {
        Filename = argv[1];
    }
#elif __linux__
    Filename = strrchr(argv[1], '/');
    if(Filename == NULL)
    {
        Filename = argv[1];
    }
#endif

    StringReplaceChar(Filename, '.', '_');

    if(InputFile == NULL)
    {
        printf("Something went wrong opening the input file: %s\n", argv[1]);
        return 1;
    }

    // Get file size
    fseek(InputFile, 0, SEEK_END);
    FileSize = ftell (InputFile);
    rewind(InputFile);

    // Output to stdout
    printf("long int _Size_%s = %ld;\n", Filename, FileSize);
    printf("unsigned char _%s[] = {\n\t", Filename);
    for(long int i = 1; i <= FileSize; i++)
    {
        char Buff = fgetc(InputFile);
        printf("0x%02hhX, ", Buff);
        if(i % 8 == 0)
        {
            printf("\n\t");
        }
    }
    printf("\n};");

    return 0;
}

inline void PrintHelp(void)
{
    printf("\n");
    printf("Usage:\n");
    printf("\tbin2header <input_file> > my_header.h\n\n");
    printf("\t--help\tPrints this dialog.\n");
    printf("\t-h\tPrints this dialog.\n");
}

int StringReplaceChar(char *String, char Replace, char Replacement)
{
    int Count = 0;

    while(*String != '\0')
    {
        if(*String == Replace)
        {
            *String = Replacement;
            Count++;
        }

        String++;
    }

    return (Count);
}
