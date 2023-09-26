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
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"

//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
    const struct Appointment* appoint,
    int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
            appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) 
{
    int i;
    int done = 0;
    if (fmt == FMT_TABLE) {

        displayPatientTableHeader();
    }
    for (i = 0; i < max; i++) 
    {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            done = 1;
        }
    }
    if (done == 0) 
    {
        printf("*** No records found ***");
    }

    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) 
{
    int selection;

    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1) 
        {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (selection == 2) 
        {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (selection);
}


// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) 
{
    int i = 0;
    int index = -1;

    for (i = 0; i < max; i++) 
    {
        if (patient[i].patientNumber == 0) 
        {
            index = i;
            if (max > index) 
            {
                patient[index].patientNumber = nextPatientNumber(patient, max);
                inputPatient(patient + index);
                printf("*** New patient record added ***\n\n");

            }
            //br
            i = max;
        }
    }

    if (index == -1) 
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) 
{
    int patientNum, indexFound;

    printf("Enter the patient number: ");
    scanf("%d", &patientNum);
    printf("\n");

    indexFound = findPatientIndexByPatientNum(patientNum, patient, max);
    if (indexFound != -1) 
    {
        menuPatientEdit(patient + indexFound);
    }
    else 
    {
        printf("ERROR: Patient record not found!\n");
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)

void removePatient(struct Patient patient[], int max) 
{
    int patientNum, indexFound;
    char selection;

    printf("Enter the patient number: ");
    scanf("%d", &patientNum);
    clearInputBuffer();
    printf("\n");

    indexFound = findPatientIndexByPatientNum(patientNum, patient, max);

    if (indexFound != -1)
    {

        displayPatientData(&patient[indexFound], FMT_FORM);
        printf("\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");
        selection = inputCharOption("yn");
        
        if (selection == 'n') 
        {
            printf("Operation aborted.\n\n");
            
        }
        else 
        {
            patient[indexFound].patientNumber = 0;
            strcpy(patient[indexFound].phone.number, "");
            printf("Patient record has been removed!\n\n");
            
        }
    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
        
    }

}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:

void viewAllAppointments(struct ClinicData* data) 
{
    int i, j;

    bubblesortbyDate(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(NULL, 1); //null

    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientnumber && data->patients[j].patientNumber) {
                if (data->appointments[i].patientnumber == data->patients[j].patientNumber) {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }
    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) 
{
    int maxDay, i, j;
    
    struct Date date;

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);
    
    maxDay = findMaxDayoftheMonth(date);
    printf("Day (1-%d)  : ", maxDay);

    date.day = inputIntRange(1, maxDay);
    printf("\n");

    bubblesortbyDate(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++) 
    {
        for (j = 0; j < data->maxPatient; j++) 
        {
            if (data->appointments[i].patientnumber && data->patients[j].patientNumber) 
            {
                if (data->appointments[i].patientnumber == data->patients[j].patientNumber) 
                {
                    if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day) 
                    {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    printf("\n");

}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appoint, int maxAppointments, struct Patient* patients, int maxPatients) 
{
    struct Date date;
    struct Time time;
  
    int maxDay;
    int patientNumber, indexFound, available = 1;

    printf("Patient Number: ");
    patientNumber = inputIntPositive();

    indexFound = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);

    if (indexFound >= 0) 
    {
        while (available)
        {
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            maxDay = findMaxDayoftheMonth(date);

            printf("Day (1-%d)  : ", maxDay);
            date.day = inputIntRange(1, maxDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            
            if (availableTime(date, time, appoint, maxAppointments)) 
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else 
            {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.min > 0) || (time.min % MINUTE_INTERVAL != 0)) 
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);

                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                available = 0;
            }
        }

        
        indexFound = emptyIndexAppointment(appoint, maxAppointments);
        appoint[indexFound].date = date;
        appoint[indexFound].time = time;
        appoint[indexFound].patientnumber = patientNumber;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else 
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
    return;
}
// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* patients, int maxPatients) 
{
    struct Date date;
    int indexFound, patientNumber, maxDay, appointIndex;

   
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    indexFound = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);

    if (indexFound >= 0) 
    {
        printf("Year        : ");
        date.year = inputIntPositive();

        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        maxDay = findMaxDayoftheMonth(date);
        
        printf("Day (1-%d)  : ",maxDay);
        
        date.day = inputIntRange(1, maxDay);

        appointIndex = appointmentExist(patientNumber, date, app, maxAppointments);

        if (appointIndex >= 0) 
        {
            printf("\n");

            displayPatientData(&patients[indexFound], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') 
            {
                app[appointIndex].patientnumber = 0;

                printf("\nAppointment record has been removed!\n\n");
            }

            else 
            {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else 
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) 
{
    int patientNum;
    int indexFound;
    printf("Search by patient number: ");

    patientNum = inputIntPositive();

    indexFound = findPatientIndexByPatientNum(patientNum, patient, max);
    printf("\n");
    if (indexFound != -1) 
    {
        displayPatientData(&patient[indexFound], FMT_FORM);

    }

    else 
    {
        printf("*** No records found ***\n");
    }
    printf("\n");

}


// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) 
{
    char numInput[PHONE_LEN + 1];
    int i, result;
    int done = 0;
    printf("Search by phone number: ");
    inputCString(numInput, PHONE_LEN, PHONE_LEN);
    printf("\n");

    displayPatientTableHeader();

    for (i = 0; i < max; i++) 
    {
        result = strcmp(patient[i].phone.number, numInput);
        if (result == 0) {

            displayPatientData(&patient[i], FMT_TABLE);
            done = 1;
        }
    }
    if (!done)
    {
        printf("\n*** No records found ***\n");
    }

    printf("\n");
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) 
{
    int nextNum, maxNum = patient[0].patientNumber, i;

    for (i = 0; i < max; i++) 
    {
        if (patient[i].patientNumber > maxNum) 
        {
            maxNum = patient[i].patientNumber;
        }
    }
    nextNum = maxNum + 1;
    return nextNum;
}


// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber,
    const struct Patient patient[], int max) 
    {
    int i;
    for (i = 0; i < max; i++) 
    {
        if (patient[i].patientNumber == patientNumber) 
        {
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) 
{
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    printf("\n");
    inputPhoneData(&patient->phone);
}


// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) 
{
    int selection;

    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");

    selection = inputIntRange(1, 4);
    putchar('\n');


    if (selection == 4)

    {
       strcpy(phone->description, "TBD");
       //strcpy
       *phone->number = 0;
    }

    else if (selection == 1 || selection == 2 || selection == 3)

    {
       if (selection == 1)
       {

        strcpy(phone->description, "CELL");
        printf("Contact: %s", phone->description);

       }
       else if (selection == 2)
       {
        strcpy(phone->description, "HOME");
        printf("Contact: %s", phone->description);

       }
    else if (selection == 3)
    {
        strcpy(phone->description, "WORK");
        printf("Contact: %s", phone->description);
    }

       printf("\n");

       printf("Number : ");
       scanf("%s", phone->number);

       while (strlen(phone->number) != 10)
       {
        if (strlen(phone->number) != 10)
            {
                printf("Invalid 10-digit number! ");
                printf("Number: ");
                scanf("%s", phone->number);
            }
       }

       clearInputBuffer();
       printf("\n");

    }

}


//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:

int importPatients(const char* datafile, struct Patient patients[], int max) 
{
    int i = 0;
    FILE* fp = fopen(datafile, "r");

    if (fp != NULL) 
    {

        while (i < max && fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number)!=EOF) 
        {
            i++;

        }

        fclose(fp);
    }
    else 
    {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:

int importAppointments(const char* datafile, struct Appointment appoints[], int max) 
{
    int i = 0;
    FILE* fp = fopen(datafile, "r");

    if (fp != NULL) {
        
        while (i < max && fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[i].patientnumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min)!=EOF) 
        {
            i++;
            
        }

        fclose(fp);
    }
    else 
    {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

void bubblesortbyDate(struct Appointment appoint[], int maxItemCount)
{
    int i, j;
    struct Appointment temp;

    for (i = maxItemCount - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoint[j].date.year > appoint[j+1].date.year || 
                (appoint[j].date.year == appoint[j+1].date.year && appoint[j].date.month > appoint[j+1].date.month) || 
                (appoint[j].date.year == appoint[j+1].date.year && appoint[j].date.month == appoint[j+1].date.month && appoint[j].date.day > appoint[j+1].date.day))
            {
                temp = appoint[j];
                appoint[j] = appoint[j + 1];
                appoint[j + 1] = temp;
            }        
        }    
    }
    
    for (i = maxItemCount - 1; i > 0; i--)
    {
        for (j = 0; j < i; j++)
        {
            if (appoint[j].date.year == appoint[j + 1].date.year &&
                appoint[j].date.month == appoint[j + 1].date.month &&
                appoint[j].date.day == appoint[j + 1].date.day &&
                (appoint[j].time.hour > appoint[j + 1].time.hour ||
                (appoint[j].time.hour == appoint[j + 1].time.hour && 
                appoint[j].time.min > appoint[j + 1].time.min)))
            {
                temp = appoint[j];
                appoint[j] = appoint[j + 1];
                appoint[j + 1] = temp;
            }
        }
    }
    
}

int availableTime(struct Date date, struct Time time, struct Appointment* appoint, int maxAppointments) 
{
    int i, available = 0;

    for (i = 0; i < maxAppointments; i++) 
    {
        if (date.year == appoint[i].date.year && date.month == appoint[i].date.month && date.day == appoint[i].date.day && time.hour == appoint[i].time.hour && time.min == appoint[i].time.min) 
        {
            available = 1;
        }
    }

    return available;
}

int emptyIndexAppointment(struct Appointment* appoint, int maxAppointments) 
{
    int i = 0, availableApp = 0;

    while (availableApp == 0 && i < maxAppointments) 
    {
        if (appoint[i].patientnumber < 1) 
        {
            availableApp = 1;
        }
        i++;
    }
    return i;
}

int appointmentExist(int patientNumber, struct Date date, struct Appointment* appoint, int maxAppointments) 
{
    int i = 0, validApp = 0;

    while (validApp == 0 && i < maxAppointments)
    {
        if ((appoint[i].patientnumber == patientNumber) && (appoint[i].date.day == date.day) && (appoint[i].date.month == date.month) && (appoint[i].date.year == date.year)) 
        {
            validApp = 1;
        }
        i++;
    }
    return i - 1 ;
}

int findMaxDayoftheMonth(struct Date date)
{
    int maxDay = 31;

    if (date.month == 4 || date.month == 9 || date.month == 11 || date.month == 6) 
    {
        maxDay = 30;
    }
    if (date.month == 2) 
    {
        maxDay = 28;
    }
    if (date.year % 4 == 0 && date.month == 2) 
    {
        maxDay = 29;
    }
    

    return maxDay;
}