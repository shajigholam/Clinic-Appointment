/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  :Samaneh Hajigholam
Student ID#:119751220
Email      :shajigholam@myseneca.ca
Section    :NGG

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

#include <string.h>
//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
//
int inputInt(void)
{
    char newline = 'x';
    int value;
    do
    {
        scanf("%d%c", &value, &newline);
        if (newline != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
        
    } while (newline != '\n');
    
    return value;
}

int inputIntPositive(void)
{
    int value;
    do
    {
        value = inputInt();
        if (value <= 0)
        {
            
            printf("ERROR! Value must be > 0: ");
        }
    } while (value <= 0);

    return value;
}

int inputIntRange(int lowerBound, int upperBound)
{
    int value;

    do
    {
        value = inputInt();
        if (value < lowerBound || value > upperBound)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
        }
  
    } while (value < lowerBound || value > upperBound);

    return value;
}

char inputCharOption(const char validCharacters[])
{
    char character;
    int i, done = 0;

    do{
        scanf(" %c", &character);

        if (getchar() != '\n')
        {
            printf("ERROR: Character must be one of [%s]: ", validCharacters);
            clearInputBuffer();
        }
        
        else
        {
            for (i = 0; validCharacters[i] != '\0'; i++)
            {
                if (validCharacters[i] == character)
                {
                    done = 1;
                }      
            }
        }
    }while(done == 0);
    
    return character;
}

void inputCString(char* string, int minValueInput, int maxValueInput)
{
    int length = 0;
    char stringInput[100] = {"\0"};

    int done = 0;
    
    while (done == 0)
    {
        scanf("%100[^\n]", stringInput);
        clearInputBuffer();
        length = 0;

        length = strlen(stringInput);

        if (length >= minValueInput && length <= maxValueInput)
        {
            done = 1;
            
            strcpy(string, stringInput);
  
        }
        else if (length < minValueInput || length > maxValueInput)
        {

            if (minValueInput == maxValueInput)
            {
                
                printf("ERROR: String length must be exactly %d chars: ", maxValueInput);
            }
            
            else if (length > maxValueInput)
            {
            
                printf("ERROR: String length must be no more than %d chars: ", maxValueInput);
            }
            else if (length < minValueInput)
            {
            
                printf("ERROR: String length must be between %d and %d chars: ", minValueInput, maxValueInput);
            }
        }
        
    }
    
}

void displayFormattedPhone(const char* ptrPhoneNum)
{
    int i;
    int done = 0;

    if (ptrPhoneNum == NULL)
    {
        printf("(___)___-____");
    }
    else
    {
        for (i = 0; ptrPhoneNum[i] != '\0' && done == 0; i++)
        {
            if (ptrPhoneNum[i] == '0' || ptrPhoneNum[i] == '1' || ptrPhoneNum[i] == '2' || ptrPhoneNum[i] == '3' || ptrPhoneNum[i] == '4' || ptrPhoneNum[i] == '5' || ptrPhoneNum[i] == '6' || ptrPhoneNum[i] == '7' || ptrPhoneNum[i] == '8' || ptrPhoneNum[i] == '9')
            {
                
            }
            else
            {
                done = 1;
            }
            
        }
        if (done == 0 && i == 10)
        {
            printf("(%c%c%c)%c%c%c-%c%c%c%c", ptrPhoneNum[0], ptrPhoneNum[1], ptrPhoneNum[2], ptrPhoneNum[3], ptrPhoneNum[4], ptrPhoneNum[5], ptrPhoneNum[6], ptrPhoneNum[7], ptrPhoneNum[8], ptrPhoneNum[9]);
        }
        else
        {
            printf("(___)___-____");
        }        
        
    }
    
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

