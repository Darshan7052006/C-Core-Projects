#include <stdio.h>
#include <string.h>
#include <time.h>

char filename[50];
void menu()
{
    printf("\n========MENU========\n");
    printf("1). Compress File.\n");
    printf("2). Display Compressed File.\n");
    printf("3). Decompress File.\n");
    printf("4). Display Decompressed File.\n");
    printf("5)  Integrity Verification.\n");
    printf("6). View History.\n");
    printf("7). Exit.\n");

    printf("Enter your choice : ");
}
void compressfile()
{
    printf("Enter the Name of the File you want to compress: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    FILE *fp;
    FILE *fp1;
    FILE *fp2;
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }
    fp1 = fopen("Compressed.bin", "wb");
    if (fp1 == NULL)
    {
        printf("Unable to open file.\n");
        fclose(fp);
        return;
    }
    fp2 = fopen("History.txt", "a");
    if (fp2 == NULL)
    {
        printf("Warning : History Unavailable\n");
    }
    unsigned char current;
    unsigned char previous;
    unsigned char count = 1;
    if (fread(&previous, 1, 1, fp) != 1)
    {
        printf("File is empty.\n");
        fclose(fp);
        fclose(fp1);
        if (fp2 != NULL)
        {
            fclose(fp2);
        }
        return;
    }
    while (fread(&current, 1, 1, fp) == 1)
    {
        if (current == previous && count < 255)
        {
            count++;
        }
        else
        {
            fwrite(&count, 1, 1, fp1);
            fwrite(&previous, 1, 1, fp1);
            previous = current;
            count = 1;
        }
    }
    fwrite(&count, 1, 1, fp1);
    fwrite(&previous, 1, 1, fp1);
    printf("File Compressed Successfully\n");
    fflush(fp1);
    fseek(fp, 0, SEEK_END);
    long originalsize = ftell(fp);
    if (originalsize == 0)
    {
        printf("Invalid compressed file.\n");
        fclose(fp);
        fclose(fp1);
        if (fp2 != NULL)
        {
            fclose(fp2);
        }

        return;
    }
    fseek(fp1, 0, SEEK_END);
    long compressedsize = ftell(fp1);
    long bytessaved = originalsize - compressedsize;
    if (compressedsize == 0)
    {
        printf("Invalid compressed file.\n");
        fclose(fp);
        fclose(fp1);
        if (fp2 != NULL)
        {
            fclose(fp2);
        }

        return;
    }
    float compressionpercentage = (((float)(originalsize - compressedsize) / (originalsize)) * 100);
    float compressionratio = (float)originalsize / compressedsize;
    printf("File Size : %ld Bytes\n", originalsize);
    printf("Compressed File Size : %ld Bytes\n", compressedsize);
    printf("Total Bytes saved: %ld Bytes\n", bytessaved);
    printf("Compression ratio : %.2f\n", compressionratio);
    printf("Compression percentage : %.2f%% \n", compressionpercentage);
    fclose(fp);
    fclose(fp1);
    if (fp2 != NULL)
    {
        time_t t;
        time(&t);
        fprintf(fp2, "HISTORY\n");
        fprintf(fp2, "=======================\n");
        fprintf(fp2, "Date : %s", ctime(&t));
        fprintf(fp2, "File name : %s\n", filename);
        fprintf(fp2, "File Size : %ld Bytes\n", originalsize);
        fprintf(fp2, "Compressed File Size : %ld Bytes\n", compressedsize);
        fprintf(fp2, "Total Bytes saved: %ld Bytes\n", bytessaved);
        fprintf(fp2, "Compression ratio : %.2f\n", compressionratio);
        fprintf(fp2, "Compression percentage : %.2f%% \n", compressionpercentage);
        fprintf(fp2, "=======================\n");
        fclose(fp2);
    }
}
void displaycompressedfile()
{
    FILE *fp;
    fp = fopen("Compressed.bin", "rb");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    unsigned char ch;
    while (fread(&ch, 1, 1, fp) == 1)
    {
        printf("%02X", ch);
    }
    printf("\n");
    fclose(fp);
}
void decompressfile()
{
    FILE *fp;
    FILE *fp1;

    char filename[50];
    printf("Enter the Name of the file you want to decompress: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0';
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    fp1 = fopen("Decompressed.txt", "wb");
    if (fp1 == NULL)
    {
        printf("Unable to create the decompressed file.\n");
        fclose(fp);
        return;
    }
    unsigned char ch;
    unsigned char digit;
    while (fread(&digit, 1, 1, fp) == 1 && fread(&ch, 1, 1, fp))
    {
        int count = digit;
        int i = 0;
        for (i = 0; i < count; i++)
        {
            fwrite(&ch, 1, 1, fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    printf("Decompression of File is successfull.\n");
}
void displaydecompressedfile()
{
    FILE *fp;
    fp = fopen("Decompressed.txt", "rb");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    unsigned char ch;
    while (fread(&ch, 1, 1, fp) == 1)
    {
        printf("%c", ch);
    }
    printf("\n");
    fclose(fp);
}
void integrityverification()
{
    FILE *fp;
    FILE *fp1;
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    fp1 = fopen("Decompressed.txt", "rb");
    if (fp1 == NULL)
    {
        printf("Unable to open the file.\n");
        fclose(fp);
        return;
    }
    unsigned char ch1;
    unsigned char ch2;
    while (fread(&ch1, 1, 1, fp) == 1 && fread(&ch2, 1, 1, fp1) == 1)
    {
        if (ch1 != ch2)
        {
            printf("Verification Failed\n");
            fclose(fp);
            fclose(fp1);
            return;
        }
    }
    if (fread(&ch1, 1, 1, fp) != 1 && fread(&ch2, 1, 1, fp1) != 1)
    {
        printf("Verification successfull.\n");
        printf("Both the original file and Decompressed file are identical.\n");
    }
    else
    {
        printf("Verification failed.\n");
    }
    fclose(fp);
    fclose(fp1);
}

void viewhistory()
{
    FILE *fp;
    fp = fopen("History.txt", "r");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }
    fclose(fp);
}

int main()
{
    char response;
    int choice;
    do
    {
        menu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            compressfile();
            break;

        case 2:
            displaycompressedfile();
            break;

        case 3:
            decompressfile();
            break;

        case 4:
            displaydecompressedfile();
            break;

        case 5:
            integrityverification();
            break;

        case 6:
            viewhistory();
            break;

        case 7:
            printf("Thanks for using compression tool.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
            break;
        }
        printf("Do you want to continue: ");
        scanf(" %c", &response);
    } while (response == 'y' || response == 'Y');
}