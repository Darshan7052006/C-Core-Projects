#include <stdio.h>

void display_menu()
{
    printf("-------------------\n");
    printf("---MATRIX MASTER---\n");
    printf("-------MENU-------\n");
    printf("1) TRANSPOSE OF MATRIX\n");
    printf("2) DETERMINANT OF MATRIX\n");
    printf("3) INVERSE OF MATRIX\n");
    printf("4) ADDITION OF MATRIX\n");
    printf("5) SUBTRACTION OF MATRIX\n");
    printf("6) MULTIPLICATION OF MATRIX\n");
    printf("7) Show History\n");
    printf("8) Exit\n");

    printf("Choose an option from above\n");
}

void input_matrix(int row, int column, int User[row][column])
{
    int i, j;
    printf("Enter the Matrix elements: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            printf("Enter the element for row %d and column %d: ", i, j);
            scanf("%d", &User[i][j]);
        }
    }
}

void display_matrix(int row, int column, int User[row][column])
{
    int i, j;
    printf(" Matrix: \n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            printf("%5d", User[i][j]);
        }
        printf("\n");
    }
}

void add_matrix(int row, int column, int A[row][column], int B[row][column], int result[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract_matrix(int row, int column, int A[row][column], int B[row][column], int result[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void transpose_matrix(int row, int column, int User[row][column], int result[column][row])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            result[j][i] = User[i][j];
        }
    }
}

void multiply_matrix(int r1, int c1, int r2, int c2, int A[r1][c1], int B[r2][c2], int result[r1][c2])
{
    int i, j, k;
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            result[i][j] = 0;
            for (k = 0; k < c1; k++)
            {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void get_minor(int n, int User[n][n], int minor[n - 1][n - 1], int skip_col)
{
    int i, j;
    int r = 0;
    int c;
    for (i = 1; i < n; i++)
    {
        c = 0;
        for (j = 0; j < n; j++)
        {
            if (j == skip_col)
                continue;
            minor[r][c] = User[i][j];
            c++;
        }
        r++;
    }
}

int determinant(int n, int User[n][n])
{
    if (n == 1)
        return User[0][0];

    else if (n == 2)
        return User[0][0] * User[1][1] - User[0][1] * User[1][0];

    int det = 0;
    int sign = 1;
    for (int j = 0; j < n; j++)
    {
        int minor[n - 1][n - 1];
        get_minor(n, User, minor, j);
        det += sign * User[0][j] * determinant(n - 1, minor);
        sign = -sign;
    }
    return det;
}

void inverse_matrix(int n, int User[n][n], float inverse[n][n])
{
    int det = determinant(n, User);
    if (det == 0)
    {
        printf("Inverse does not exist as determinant is 0.\n");
        return;
    }
    int cofactor[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int minor[n - 1][n - 1];
            int r = 0, c;
            for (int x = 0; x < n; x++)
            {
                if (x == i)
                    continue;
                c = 0;
                for (int y = 0; y < n; y++)
                {
                    if (y == j)
                        continue;
                    minor[r][c] = User[x][y];
                    c++;
                }
                r++;
            }
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            cofactor[i][j] = sign * determinant(n - 1, minor);
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            inverse[j][i] = (float)cofactor[i][j] / det;
        }
    }
}

void append_to_history(int r, int c, float matrix[r][c], char operation[])
{
    FILE *fp = fopen("D:/matrix_history.txt", "a");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    else
    {
        fprintf(fp, "\n=====================\n");
        fprintf(fp, "Operation: %s\n", operation);
        fprintf(fp, "Size: %d x %d\n", r, c);
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                fprintf(fp, "%8.3f", matrix[i][j]);
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void append_determinant(int det)
{
    FILE *fp = fopen("D:/matrix_history.txt", "a");
    if (fp == NULL)
    {
        printf("Unable to open the file.\n");
        return;
    }
    else
    {
        fprintf(fp, "\n=====================\n");
        fprintf(fp, "Operation: Determinant\n");
        fprintf(fp, "Result : %d\n", det);
        fclose(fp);
    }
}

void show_history()
{
    FILE *fp = fopen("D:/matrix_history.txt", "r");
    if (fp == NULL)
    {
        printf("File is empty.\n");
        return;
    }
    else
    {
        char ch;
        while ((ch = fgetc(fp)) != EOF)
        {
            printf("%c", ch);
        }
        fclose(fp);
    }
}

int main()
{
    int choice;
    char repeat;

    do
    {
        display_menu();
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
        {
            int r, c;
            printf("Enter rows and columns: ");
            scanf("%d %d", &r, &c);
            int A[r][c];
            int T[c][r];
            input_matrix(r, c, A);
            transpose_matrix(r, c, A, T);
            printf("\nThe Transpose matrix\n");
            display_matrix(c, r, T);
            char save;
            printf("Save the result of the operation ? (y/n): ");
            scanf(" %c", &save);
            if (save == 'Y' || save == 'y')
            {
                float temp[c][r];
                for (int i = 0; i < c; i++)
                {
                    for (int j = 0; j < r; j++)
                    {
                        temp[i][j] = T[i][j];
                    }
                }
                append_to_history(c, r, temp, "Transpose");
            }
            break;
        }
        case 2:
        {
            int n;
            printf("Enter the size of square matrix: ");
            scanf("%d", &n);
            int matrix[n][n];
            input_matrix(n, n, matrix);
            int det = determinant(n, matrix);
            printf("\nDeterminant = %d\n", det);
            char save;
            printf("Save the result of the operation ? (y/n): ");
            scanf(" %c", &save);
            if (save == 'Y' || save == 'y')
            {
                append_determinant(det);
            }
            break;
        }
        case 3:
        {
            int n;
            printf("Enter the size of square matrix: ");
            scanf("%d", &n);
            int matrix[n][n];
            float inverse[n][n];
            input_matrix(n, n, matrix);
            inverse_matrix(n, matrix, inverse);
            printf("\nInverse Matrix\n");
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    printf("%8.3f", inverse[i][j]);
                }
                printf("\n");
            }
            char save;
            printf("Save the result of the operation ? (y/n): ");
            scanf(" %c", &save);
            if (save == 'Y' || save == 'y')
            {
                append_to_history(n, n, inverse, "Inverse");
            }
            break;
        }
        case 4:
        {
            int r1, c1, r2, c2;
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &r1, &c1);

            printf("Enter rows and columns of matrix B: ");
            scanf("%d %d", &r2, &c2);
            if (r1 == r2 && c1 == c2)
            {
                int A[r1][c1];
                int B[r2][c2];
                int result[r1][c1];
                input_matrix(r1, c1, A);
                input_matrix(r2, c2, B);
                add_matrix(r1, c1, A, B, result);
                printf("\nResult\n");
                display_matrix(r1, c1, result);
                char save;
                printf("Save the result of the operation ? (y/n): ");
                scanf(" %c", &save);
                if (save == 'Y' || save == 'y')
                {
                    float temp[r1][c1];
                    for (int i = 0; i < r1; i++)
                    {
                        for (int j = 0; j < c1; j++)
                        {
                            temp[i][j] = result[i][j];
                        }
                    }
                    append_to_history(r1, c1, temp, "Addition");
                }
            }
            else
            {
                printf("Addition not possible\n");
            }
            break;
        }

        case 5:
        {
            int r1, c1, r2, c2;
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &r1, &c1);

            printf("Enter rows and columns of matrix B: ");
            scanf("%d %d", &r2, &c2);
            if (r1 == r2 && c1 == c2)
            {
                int A[r1][c1];
                int B[r2][c2];
                int result[r1][c1];
                input_matrix(r1, c1, A);
                input_matrix(r2, c2, B);
                subtract_matrix(r1, c1, A, B, result);
                printf("\nResult\n");
                display_matrix(r1, c1, result);
                char save;
                printf("Save the result of the operation ? (y/n): ");
                scanf(" %c", &save);
                if (save == 'Y' || save == 'y')
                {
                    float temp[r1][c1];
                    for (int i = 0; i < r1; i++)
                    {
                        for (int j = 0; j < c1; j++)
                        {
                            temp[i][j] = result[i][j];
                        }
                    }
                    append_to_history(r1, c1, temp, "Subtraction");
                }
            }
            else
            {
                printf("Subtraction not possible\n");
            }
            break;
        }
        case 6:
        {
            int r1, c1, r2, c2;
            printf("Enter rows and columns of matrix A: ");
            scanf("%d %d", &r1, &c1);

            printf("Enter rows and columns of matrix B: ");
            scanf("%d %d", &r2, &c2);
            if (c1 == r2)
            {
                int A[r1][c1];
                int B[r2][c2];
                int result[r1][c2];
                input_matrix(r1, c1, A);
                input_matrix(r2, c2, B);
                multiply_matrix(r1, c1, r2, c2, A, B, result);
                printf("\nResult\n");
                display_matrix(r1, c2, result);
                char save;
                printf("Save the result of the operation ? (y/n): ");
                scanf(" %c", &save);
                if (save == 'Y' || save == 'y')
                {
                    float temp[r1][c2];
                    for (int i = 0; i < r1; i++)
                    {
                        for (int j = 0; j < c2; j++)
                        {
                            temp[i][j] = result[i][j];
                        }
                    }
                    append_to_history(r1, c2, temp, "Multiplication");
                }
            }
            else
            {
                printf("Multiplication not possible\n");
            }
            break;
        }
        case 7:
        {
            show_history();
            break;
        }

        case 8:
        {
            return 0;
        }

        default:
            printf("Invalid choice\n");
        }
        printf("\nDo you want to continue (y/n): ");
        scanf(" %c", &repeat);
    } while (repeat == 'Y' || repeat == 'y');
    return 0;
}