

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int Date_Time();
int menu();
int Add_tasks();
int Mark_task_as_completed();
int View_tasks();
int Delete_tasks();

struct check
{
    char task_note[50][50];
    int date[50][20];
    int status, trasfer;
} value;

int Date_Time()
{   
    int SIZE = 256;
    char Time[SIZE];
    time_t curtime;
    struct tm *loctime;

    // Get the current time.
    curtime = time(NULL);

    // Convert it to local time
    // representation.
    loctime = localtime(&curtime);

    // Convert local time into String time format 
    strftime(Time, SIZE, "\nDate :- %d-%b-%Y %I:%M:%S %p\n", loctime);

    // Print out the date and time
    fputs(Time, stdout);
}

int menu()
{
    printf("WELECOME TO MY PROJECT\n");
    printf("1. ADD TASKS\n");
    printf("2. MARK TASK AS COMPLETE\n");
    printf("3. VIEW TASKS\n");
    printf("4. DELETE TASKS\n");
    printf("5. CLEAR THE SCREEN\n");
    printf("6. EXIT\n");
    printf("\nENTER THE OPTION\n");
}

// CREATE A FUNCTION TO ADD TASKS.
int Add_tasks()
{

    char file_name[50] = "hello.txt";
    FILE *Add_tasks_data;
    Add_tasks_data = fopen(file_name, "a");
    printf("HOW MANY TASKS WRITE\n");
    scanf("%d", &value.trasfer);
    if (value.trasfer == 0)
    {
        printf("YOU ARE WRONG ENTRY");
    }

    // TAKEN INPUT BY USER
    for (int i = 0; i < value.trasfer; i++)
    {

        printf("ENTER THE %d TASK DATE.\n", i + 1);
        scanf("%s", &value.date[i]);

        int day, month, year;
        if (sscanf(value.date[i], "%d/%d/%d", &day, &month, &year) != 3)
        {
            printf("YOUR DATE ARE WRONG\n");
            continue;
        }

        printf("ENTER THE %d TASK DETAILS.\n", i + 1);
        scanf("%s", &value.task_note[i]);

        // STORE DATA IN FILE
        fprintf(Add_tasks_data, "DATE :- %s\nTASK DETAILS :- %s\n", value.date[i], value.task_note[i]);
    }

    fclose(Add_tasks_data);
    // getch();
}

// CREATE A FUNCTION TO STUTUS TASKS.
int Mark_task_as_completed()
{
    // char user_file[10] = "hello.txt";
    printf("ENTER THE WHICH DATE WORK WAS COMPLETE.\n");
    scanf("%s", &value.date);

    int day, month, year;
    if (sscanf(value.date, "%d/%d/%d", &day, &month, &year) != 3)
    {
        printf("YOUR DATE ARE WRONG\n");
        return 0;
    }

    FILE *file_name = fopen("hello.txt", "r");
    FILE *temp_file_name = fopen("temp.txt", "w");

    if (file_name == NULL || temp_file_name == NULL) // CHECK BOTH FILE NOT OPEN THEN PRINT.
    {
        printf("FILE NO FOUND THIS TIME.");
    }

    // fgets(value.task_note[0], sizeof(value.task_note), file_name); // READ FILE ONLY ONE LINE.
    while ((fgets(value.task_note[0], sizeof(value.task_note), file_name)) != NULL)
    {

        if (strstr(value.task_note, value.date) != NULL)
        {
            fputs(value.task_note, temp_file_name);
            fgets(value.task_note[0], sizeof(value.task_note), file_name);
            if (strstr(value.task_note[0], "TASK DETAILS :-") != NULL)
            {

                fputs(value.task_note, temp_file_name);
                fgets(value.task_note[0], sizeof(value.task_note), file_name);
                if (strstr(value.task_note, "STATUS :-") != NULL)
                {
                    /* code */
                    // fputs(value.task_note, temp_file_name);
                    printf("ALREADY TASK COMPLETE.\n");
                }

                else
                {
                    fputs("STATUS :- COMPLETE\n", temp_file_name);
                    printf("COMPLETE TASK.");
                }
            }
        }

        fputs(value.task_note, temp_file_name);
    }

    fclose(file_name);
    fclose(temp_file_name);

    remove("hello.txt");
    rename("temp.txt", "hello.txt");

    // remove(file_name);
    // rename(temp_file_name,file_name);
}

// CREATE A FUNCTION TO VIEW TASKS.
int View_tasks()
{
    char file_name[30] = "hello.txt";
    FILE *file_data;
    file_data = fopen("hello.txt", "r");
    printf("\nTHE FILE DATA IS BLEOW.\n\n");
    char ch;
    while ((ch = fgetc(file_data)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(file_data);
    // getch();
}

// CREATE A FUNCTION TO DELETE TASKS.
int Delete_tasks()
{
    char file_name[50] = "hello.txt";
    FILE *file_data, *temp_file;
    char temp_file_name[] = "temp.txt";
    char date_input[20], task_name_input[50];
    int found = 0;

    // Take input for date and task name
    printf("ENTER THE TASK DATE TO DELETE (format: dd/mm/yyyy) \n");
    scanf("%s", date_input);

    int day, month, year; //
    if (sscanf(date_input, "%d/%d/%d", &day, &month, &year) != 3)
    {
        printf("YOUR DATE ARE WRONG\n");
        return 0;
    }

    // Open the original file in read mode and temporary file in write mode
    file_data = fopen(file_name, "r");
    if (file_data == NULL)
    {
        printf("Error opening the file.\n");
        return 0;
    }

    temp_file = fopen(temp_file_name, "w");
    if (temp_file == NULL)
    {
        printf("Error opening the temporary file.\n");
        fclose(file_data);
        return 0;
    }

    char line[100];
    int is_task_to_delete = 0;

    // Read the file and write everything except the matched task to the temp file
    while (fgets(line, sizeof(line), file_data))
    {
        if (strstr(line, "DATE :-") != NULL)
        {
            // If the line starts with "DATE :-", check if it matches the date_input
            if (strstr(line, date_input) != NULL)
            {
                // Check the next line for the task details
                fgets(line, sizeof(line), file_data);
                if (strstr(line, "TASK DETAILS :-") != NULL /*&& strstr(line, task_name_input) != NULL*/)
                {
                    fgets(line, sizeof(line), file_data);
                    // If both date and task details match, skip this task
                    if (strstr(line, "STATUS :-") != NULL)
                    {

                        continue;
                    }
                }
            }
        }

        // If this is not the task to delete, write the line to the temp file
        if (is_task_to_delete == 0)
        {
            fprintf(temp_file, "%s", line);
        }
        else
        {
            is_task_to_delete = 0; // Reset for next task
        }
    }

    // Close both files
    fclose(file_data);
    fclose(temp_file);

    // Replace the original file with the temp file
    remove(file_name);
    rename(temp_file_name, file_name);
    printf("TASK DELETED SUCCESSFULLY.\n");
}

int main()
{
    int option;
    char user_file[50] = "hello.txt";
    while (option != 6)
    {
        Date_Time();
        menu();
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            Add_tasks();
            break;

        case 2:
            Mark_task_as_completed();
            break;

        case 3:
            View_tasks();
            break;
        case 4:
            Delete_tasks();
            break;
        case 5:
            system("CLS");
            break;
        case 6:

            printf("YOU ARE EXIT");
            break;
        default:
            printf("YOU ARE CHOOSE WRONG OPTION.");
            break;
        }
        getch();
    }
    return 0;
}