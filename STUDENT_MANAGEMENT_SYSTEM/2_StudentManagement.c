#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int Roll_Number;
    char Name[50];
    float cgpa;
    char course[50];
    int phonenumber;
} student;

void display_menu()
{
    printf("\n=========STUDENT RECORD MANAGEMENT SYSTEM=========\n");
    printf("1. Add Student\n");
    printf("2. Display\n");
    printf("3. Search\n");
    printf("4. Update\n");
    printf("5. Delete\n");
    printf("6. Exit\n");
}

int studentexists(int id)
{
    FILE *fp;
    fp = fopen("D:/Data.txt","rb");
    if (fp == NULL)
    {
        return 0;
    }
    student temp;
    while (fread(&temp, sizeof(student), 1, fp) == 1)
    {
        if (temp.Roll_Number == id)
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
void sortStudentsFile();

void clearinputbuffer()
{
    while (getchar() != '\n')
        ;
}

void delete_record()
{
    FILE *fp;
    FILE *fp1;
    FILE *fp2;
    int found = 0;
    fp = fopen("D:/Data.txt", "rb");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    fp1 = fopen("D:/temp.txt", "wb");
    if (fp1 == NULL)
    {
        printf("Unable to open the file.\n");
        fclose(fp);
        return;
    }
    fp2 = fopen("D:/bin.txt", "ab");
    if (fp2 == NULL)
    {
        printf("Unable to open the file.\n");
        fclose(fp);
        fclose(fp1);
        return;
    }
    student temp;
    int id;
    printf("Enter the Roll Number which you have to delete: ");
    scanf("%d", &id);
    clearinputbuffer();
    char choice;

    printf("Are you sure you want to delete? (y/n): ");
    scanf(" %c", &choice);

    if (choice != 'y' && choice != 'Y')
    {
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        return;
    }
    else
    {
        while (fread(&temp, sizeof(student), 1, fp) == 1)
        {
            if (temp.Roll_Number == id)
            {
                found = 1;
                fwrite(&temp, sizeof(student), 1, fp2);
            }
            else
            {
                fwrite(&temp, sizeof(student), 1, fp1);
            }
        }

        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        if (!found)
        {
            printf("Record not found.\n");
            remove("D:/temp.txt");
            return;
        }
        else
        {
            remove("D:/Data.txt");
            if (rename("D:/temp.txt", "D:/Data.txt") != 0)
            {
                printf("Error replacing file.\n");
                return;
            }
            printf("Record deleted successfully.\n");
            sortStudentsFile();
        }
    }
}

void Add_student()
{
    FILE *fp;
    student s;
    printf("Enter the Roll Number of the Student: ");
    scanf("%d", &s.Roll_Number);
    clearinputbuffer();
    // check if any duplicate id exists because we cannot allow multiple students with the same roll number.
    if (studentexists(s.Roll_Number))
    {
        printf("\nThere is already a Student registerred with the Roll Number the User has given.\n");
        return;
    }
    else
    {
        printf("Enter the name of the Student: ");
        fgets(s.Name, sizeof(s.Name), stdin); // This fgets function is used to get input from the user and it is used to take input in form of strings.
        // For the function to work we have to provide the place where we have to input and the size of string and the place from where input is taken.
        // Here stdin means taken from keyboard.
        s.Name[strcspn(s.Name, "\n")] = '\0'; // Here i have used the string complement span function.
        // It detects the new line added by the fgets function and then replaces it with a null character thus the new line is removed.

        printf("Enter the Cgpa of the Student: ");
        scanf("%f", &s.cgpa);
        clearinputbuffer();

        printf("Enter the Phone Number of the Student: ");
        scanf("%d", &s.phonenumber);
        clearinputbuffer();

        printf("Enter Course: ");
        fgets(s.course, sizeof(s.course), stdin);
        s.course[strcspn(s.course, "\n")] = '\0';

        fp = fopen("D:/Data.txt", "ab");
        if (fp == NULL)
        {
            printf("The system was not able to open the file.\n");
            return;
        }
        fwrite(&s, sizeof(s), 1, fp);

        fclose(fp);

        printf("\nStudent added successfully.\n");

        // This function is used to sort files and record of the students.
        sortStudentsFile();
    }
}

/*
The below function is used to display records of the students which are stored in the binary file that the user entered.
*/
void displayrecord()
{
    FILE *fp;
    student s;
    int count = 0;
    fp = fopen("D:/Data.txt", "rb");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }
    printf("\n--------STUDENT RECORDS--------\n");
    while (fread(&s, sizeof(student), 1, fp) == 1)
    {
        printf("Record = %d\n", ++count);
        printf("Roll Number = %d\n", s.Roll_Number);
        printf("Name = %s\n", s.Name);
        printf("Course = %s\n", s.course);
        printf("Phone number = %d\n", s.phonenumber);
        printf("Cgpa = %.2f\n", s.cgpa);
        printf("-----------------------------\n");
    }

    if (count == 0)
    {
        printf("No records available.\n");
    }
    fclose(fp);
}

/*
The code written below is used to find the students by their college id and here first we have to supply the program,
with the college id of the student we have to search for and then after passing the id, we again use the same fread loop.
It is used to read the whole file in binary and then we have to just use an if statement to check if the roll number matches,
Then we can print the details of the student if we get the right match and break the loop.


*/
void searchByID()
{
    FILE *fp;
    student s;

    int id;
    int found = 0;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &id);
    clearinputbuffer();

    fp = fopen("D:/Data.txt", "rb");

    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    while (fread(&s, sizeof(student), 1, fp) == 1)
    {
        if (s.Roll_Number == id)
        {
            printf("\nStudent Found:\n");
            printf("Roll Number = %d\n", s.Roll_Number);
            printf("Name = %s\n", s.Name);
            printf("Course = %s\n", s.course);
            printf("Phone number = %d\n", s.phonenumber);
            printf("Cgpa = %.2f\n", s.cgpa);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nStudent with Roll Number %d not found.\n", id);
    }

    fclose(fp);
}

void sortStudentsFile()
{
    FILE *fp;
    student *arr;
    student temp;

    int n = 0, i, j;

    fp = fopen("D:/Data.txt", "rb");

    if (fp == NULL)
    {
        printf("The system was not able to open the file.\n");
        return;
    }
    /* count records */
    while (fread(&temp, sizeof(student), 1, fp) == 1)
    {
        n++;
    }

    if (n == 0)
    {
        fclose(fp);
        return;
    }

    arr = (student *)malloc(n * sizeof(student));

    rewind(fp);

    /* read all records into array */
    fread(arr, sizeof(student), n, fp);

    fclose(fp);

    /*bubble sort*/
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j].Roll_Number > arr[j + 1].Roll_Number)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    /* rewrite file */
    fp = fopen("D:/Data.txt", "wb");

    if (fp == NULL)
    {
        printf("The system was not able to open the file.\n");
        return;
    }
    fwrite(arr, sizeof(student), n, fp);

    fclose(fp);

    free(arr);
}

void update_student()
{
    FILE *fp;
    student s;
    char choice;
    int option;
    int id;
    int found = 0;
    printf("Enter the Roll Number of the student for whom you have to update the record: ");
    scanf("%d", &id);
    clearinputbuffer();

    fp = fopen("D:/Data.txt", "rb+");
    if (fp == NULL)
    {
        printf("The system was not able to open the file.\n");
        return;
    }

    while (fread(&s, sizeof(student), 1, fp) == 1)
    {
        if (s.Roll_Number == id)
        {
            found = 1;
            fseek(fp, -sizeof(student), SEEK_CUR);
            printf("Current Record:\n");
            printf("Roll: %d\n", s.Roll_Number);
            printf("Name: %s\n", s.Name);
            printf("CGPA: %.2f\n", s.cgpa);
            printf("Course: %s\n", s.course);

            printf("Enter the field you want to update: \n");
            printf("1) Roll Number\n 2) Name\n 3) Course\n 4) Cgpa\n 5) Phone Number\n");
            scanf("%d", &option);
            clearinputbuffer();

            switch (option)
            {
            case 1:
            {
                int new_roll;

                while (1)
                {
                    printf("Enter new Roll Number: ");
                    scanf("%d", &new_roll);
                    clearinputbuffer();

                    if (new_roll == s.Roll_Number)
                    {
                        printf("Same as old Roll Number. No change.\n");
                        break;
                    }

                    else if (studentexists(new_roll))
                    {
                        printf("Roll Number already exists. Try again.\n");
                    }
                    else
                    {
                        s.Roll_Number = new_roll;
                        break;
                    }
                }
            }
            break;

            case 2:
                printf("Enter Updated Name: ");
                fgets(s.Name, sizeof(s.Name), stdin);
                s.Name[strcspn(s.Name, "\n")] = '\0';
                break;

            case 3:
                printf("Enter Updated Course: ");
                fgets(s.course, sizeof(s.course), stdin);
                s.course[strcspn(s.course, "\n")] = '\0';
                break;

            case 4:
                printf("Enter the Updated Cgpa of the Student: ");
                scanf("%f", &s.cgpa);
                clearinputbuffer();
                break;

            case 5:
                printf("Enter the Updated Phone Number: ");
                scanf("%d", &s.phonenumber);
                clearinputbuffer();
                break;

            default:
                printf("Invalid option\n");
            }
            fwrite(&s, sizeof(student), 1, fp);
            printf("Record updated successfully.\n");
            break;
        }
    }
    if (!found)
    {
        printf("Record not found\n");
        printf("Do you want to add the student: ");
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y')
        {
            Add_student();
        }
    }
    sortStudentsFile();
    fclose(fp);
}

int main()
{
    int choice;

    while (1)
    {
        display_menu();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearinputbuffer();

        switch (choice)
        {
        case 1:
            Add_student();
            break;

        case 2:
            displayrecord();
            break;

        case 3:
            searchByID();
            break;

        case 4:
            update_student();
            break;

        case 5:
            delete_record(); // next function
            break;

        case 6:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}