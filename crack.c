#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings


// Given a target plaintext word, use it to try to find
// a matching hash in the hashFile.
// Get this function working first!
char * tryWord(char * plaintext, char * hashFilename)
{
    int size = 0;
    char ln[HASH_LEN];
    size = strlen(plaintext);
    // Hash the plaintext
    char *hashed = md5(plaintext, size);
    // Open the hash file
    FILE *filer = fopen(hashFilename, "r");
    if (filer == NULL)
    {
        printf("error with hash file\n");
        exit(1);
    }
    // Loop through the hash file, one line at a time.
    while ((fgets(ln, HASH_LEN, filer))!= NULL)
    {
        int length = strlen(ln);
        int i = length - 1;
        if ( ln[i] == '\n')
        {
            ln[i] = '\0';
        }
        
        if ((strstr(ln, hashed)) != NULL)
        {
            return hashed;
        }
    }
    return NULL;
    fclose(filer);
    free(hashed);

    // Attempt to match the hash from the file to the
    // hash of the plaintext.

    // If there is a match, you'll return the hash.
    // If not, return NULL.

    // Before returning, do any needed cleanup:
    //   Close files?
    //   Free memory?
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    
    char dictln[PASS_LEN];
    // Open the dictionary file for reading.
    FILE *dictf = fopen(argv[2], "r");
     if (dictf == NULL)
    {
        printf("error with dict file");
        exit(1);
    }
    int count;
    int size = 0;

    while ((fgets(dictln, PASS_LEN, dictf))!= NULL)
    {
        size = strlen(dictln);
        int z = size - 1;
        if ( dictln[z] == '\n')
        {
            dictln[z] = '\0';
        }

        char *hashstore = (tryWord(dictln, argv[1]));
        if (hashstore != NULL) 
        {
            fputs(hashstore, stdout);
            printf(": %s\n", dictln);
            count++;
            free(hashstore);
        }
    }
    printf("Cracked %d hashes\n", count);

    // For each dictionary word, pass it to tryWord, whichS
    // will attempt to match it against the hashes in the hash_file.
    
    // If we got a match, display the hash and the word. For example:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the dictionary file.
    fclose(dictf);
    // Display the number of hashes that were cracked.
    
    // Free up any malloc'd memory?
}

