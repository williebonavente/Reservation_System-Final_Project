#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MX_PSNGRS 20
#define MX_ROWS 5
#define MX_COLS 4

struct Psg
{
    char x[50];
    int y;
    char z[100];
    char seat[3];
};

void mm();
void ds();
void adpst();
void ets();
void clrsv();
void dlp();
void daps();
void inrsv(struct Psg psg[], int *psn, bool sts[MX_ROWS][MX_COLS]);
void ets(struct Psg psg[], int psn, bool sts[MX_ROWS][MX_COLS]);
void clrsv(struct Psg psg[], int *psn, bool sts[MX_ROWS][MX_COLS]);

void saveData(struct Psg psg[], int psn);
int readData(struct Psg psg[], bool sts[MX_ROWS][MX_COLS]);

int main()
{
    char psd[20] = "ches123";
    char p[20];

    printf("Enter password: ");
    scanf("%s", p);

    if (strcmp(p, psd) != 0)
    {
        printf("Invalid password. Exiting...\n");
        return 0;
    }

    struct Psg psg[MX_PSNGRS];
    int psn = 0;
    bool sts[MX_ROWS][MX_COLS] = {false};

    // Read data from the file
    psn = readData(psg, sts);
    int ch;
    do
    {
        mm();
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1:
            ds(sts); // Display seat map
            break;
        case 2:
            adpst(psg, &psn, sts);
            saveData(psg, psn); // Save data after adding passenger
            break;
        case 3:
            ets(psg, psn, sts);
            saveData(psg, psn); // Save data after editing seat
            break;
        case 4:
            clrsv(psg, &psn, sts);
            saveData(psg, psn); // Save data after canceling reservation
            break;
        case 5:
            dlp(psg, psn);
            break;
        case 6:
            printf("Exiting...\n");
            saveData(psg, psn); // Save data before exiting
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (ch != 6);

    return 0;
}

void mm()
{
    printf("\n\tMain Menu\n");
    printf("1. Display the Available Seats\n");
    printf("2. Add Passenger\n");
    printf("3. Edit Seat Number\n");
    printf("4. Cancel Reservation\n");
    printf("5. Display the List of Passengers\n");
    printf("6. Exit\n");
}

void ds(bool sts[MX_ROWS][MX_COLS])
{
    printf("Seat Map\n\n");
    printf("   A  B  C  D\n");

    for (int i = 0; i < MX_ROWS; i++)
    {
        printf("%d", i + 1);
        for (int j = 0; j < MX_COLS; j++)
        {
            printf("  %c", sts[i][j] ? 'X' : 'A' + j);
        }
        printf("\n");
    }
}

void adpst(struct Psg psg[], int *psn, bool sts[MX_ROWS][MX_COLS])
{
    if (*psn >= MX_PSNGRS)
    {
        printf("No more seats available. Reservation is full.\n");
        return;
    }

    struct Psg np;
    printf("Enter name: ");
    scanf(" %[^\n]", np.x);
    printf("Enter age: ");
    scanf("%d", &np.y);
    printf("Enter address: ");
    scanf(" %[^\n]", np.z);

    ds(sts);
    printf("Enter the seat number (e.g., 1A): ");
    scanf("%s", np.seat);

    int r = np.seat[0] - '1';
    int c = np.seat[1] - 'A';

    if (r < 0 || r >= MX_ROWS || c < 0 || c >= MX_COLS || sts[r][c])
    {
        printf("Invalid seat or seat already occupied.\n");
        return;
    }

    sts[r][c] = true;
    psg[*psn] = np;
    (*psn)++;

    printf("Passenger added successfully!\n");
}

void ets(struct Psg psg[], int psn, bool sts[MX_ROWS][MX_COLS])
{
    char n[50];
    printf("Enter name: ");
    scanf(" %[^\n]", n);

    int pi = -1;
    for (int i = 0; i < psn; i++)
    {
        if (strcmp(n, psg[i].x) == 0)
        {
            pi = i;
            break;
        }
    }

    if (pi == -1)
    {
        printf("Passenger not found.\n");
        return;
    }

    printf("Current seat: %s\n", psg[pi].seat);
    printf("Enter the new seat number (e.g., 1A): ");
    scanf("%s", psg[pi].seat);

    int r = psg[pi].seat[0] - '1';
    int c = psg[pi].seat[1] - 'A';

    if (r < 0 || r >= MX_ROWS || c < 0 || c >= MX_COLS || sts[r][c])
    {
        printf("Invalid seat or seat already occupied.\n");
        return;
    }

    int pr = psg[pi].seat[0] - '1';
    int pc = psg[pi].seat[1] - 'A';
    sts[pr][pc] = false;

    sts[r][c] = true;
    printf("Seat updated successfully!\n");
}

void clrsv(struct Psg psg[], int *psn, bool sts[MX_ROWS][MX_COLS])
{
    char n[50];
    printf("Enter name: ");
    scanf(" %[^\n]", n);

    int pi = -1;
    for (int i = 0; i < *psn; i++)
    {
        if (strcmp(n, psg[i].x) == 0)
        {
            pi = i;
            break;
        }
    }

    if (pi == -1)
    {
        printf("Passenger not found.\n");
        return;
    }

    int r = psg[pi].seat[0] - '1';
    int c = psg[pi].seat[1] - 'A';
    sts[r][c] = false;

    for (int i = pi; i < (*psn - 1); i++)
    {
        psg[i] = psg[i + 1];
    }

    (*psn)--;
    printf("Reservation canceled successfully!\n");
}

void dlp(struct Psg psg[], int psn)
{
    printf("\n\tList of Passengers\n");
    printf("Passenger Name\tAge\tAddress\t\tSeat No.\n");

    for (int i = 0; i < psn; i++)
    {
        printf("%s\t\t%d\t%s\t\t%s\n",
               psg[i].x, psg[i].y, psg[i].z, psg[i].seat);
    }
}

int readData(struct Psg psg[], bool sts[MX_ROWS][MX_COLS])
{
    FILE *file = fopen("data.txt", "r");
    if (file == NULL)
    {
        return 0;
    }

    int count = 0;
    while (count < MX_PSNGRS && fscanf(file, " %[^\n]\n%d\n%[^\n]\n%s\n", psg[count].x, &psg[count].y, psg[count].z, psg[count].seat) == 4)
    {
        int r = psg[count].seat[0] - '1';
        int c = psg[count].seat[1] - 'A';
        if (r >= 0 && r < MX_ROWS && c >= 0 && c < MX_COLS)
        {
            sts[r][c] = true;
        }
        count++;
    }

    fclose(file);
    return count;
}

void saveData(struct Psg psg[], int psn)
{
    FILE *file = fopen("data.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < psn; i++)
    {
        fprintf(file, "%s\t%d\t%s\t%s\n", psg[i].x, psg[i].y, psg[i].z, psg[i].seat);
    }

    fclose(file);
}
