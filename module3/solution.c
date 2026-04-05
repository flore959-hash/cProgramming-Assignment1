#include <stdio.h>
#include <string.h>

#define SEATS 48
#define NAMELEN 20

struct seat {
    int id;
    int assigned;
    char last[NAMELEN];
    char first[NAMELEN];
};

void initialize_seats(struct seat flight[], int size);
void main_menu(struct seat outbound[], struct seat inbound[], int size);
void flight_menu(struct seat flight[], int size, const char flight_name[]);

int count_empty(struct seat flight[], int size);
void show_empty_seats(struct seat flight[], int size);
void show_alphabetical(struct seat flight[], int size);
void assign_seat(struct seat flight[], int size);
void delete_seat(struct seat flight[], int size);

int main(void)
{
    struct seat outbound[SEATS];
    struct seat inbound[SEATS];

    /* set both flights so all seats start empty */
    initialize_seats(outbound, SEATS);
    initialize_seats(inbound, SEATS);

    /* start the main menu */
    main_menu(outbound, inbound, SEATS);

    printf("Program ended.\n");
    return 0;
}

void initialize_seats(struct seat flight[], int size)
{
    int i;

    /* give each seat an id and mark it empty */
    for (i = 0; i < size; i++)
    {
        flight[i].id = i + 1;
        flight[i].assigned = 0;
        strcpy(flight[i].last, "");
        strcpy(flight[i].first, "");
    }
}

void main_menu(struct seat outbound[], struct seat inbound[], int size)
{
    char choice;

    do
    {
        printf("\nFirst Level Menu\n");
        printf("a. Outbound Flight\n");
        printf("b. Inbound Flight\n");
        printf("c. Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case 'a':
                flight_menu(outbound, size, "Outbound Flight");
                break;
            case 'b':
                flight_menu(inbound, size, "Inbound Flight");
                break;
            case 'c':
                printf("Quitting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 'c');
}

void flight_menu(struct seat flight[], int size, const char flight_name[])
{
    char choice;

    do
    {
        printf("\n%s Menu\n", flight_name);
        printf("a. Show number of empty seats\n");
        printf("b. Show list of empty seats\n");
        printf("c. Show alphabetical list of seats\n");
        printf("d. Assign a customer to a seat assignment\n");
        printf("e. Delete a seat assignment\n");
        printf("f. Return to Main menu\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
            case 'a':
                printf("Number of empty seats: %d\n", count_empty(flight, size));
                break;
            case 'b':
                show_empty_seats(flight, size);
                break;
            case 'c':
                show_alphabetical(flight, size);
                break;
            case 'd':
                assign_seat(flight, size);
                break;
            case 'e':
                delete_seat(flight, size);
                break;
            case 'f':
                printf("Returning to Main menu...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 'f');
}

int count_empty(struct seat flight[], int size)
{
    int i;
    int count = 0;

    for (i = 0; i < size; i++)
    {
        if (flight[i].assigned == 0)
            count++;
    }

    return count;
}

void show_empty_seats(struct seat flight[], int size)
{
    int i;

    printf("Empty seats:\n");
    for (i = 0; i < size; i++)
    {
        if (flight[i].assigned == 0)
            printf("Seat %d\n", flight[i].id);
    }
}

void show_alphabetical(struct seat flight[], int size)
{
    struct seat temp[SEATS];
    struct seat swap;
    int i, j;
    int count = 0;

    /* copy only assigned seats into temp array */
    for (i = 0; i < size; i++)
    {
        if (flight[i].assigned == 1)
        {
            temp[count] = flight[i];
            count++;
        }
    }

    if (count == 0)
    {
        printf("No seats are currently assigned.\n");
        return;
    }

    /* sort by last name, then first name if needed */
    for (i = 0; i < count - 1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(temp[i].last, temp[j].last) > 0)
            {
                swap = temp[i];
                temp[i] = temp[j];
                temp[j] = swap;
            }
            else if (strcmp(temp[i].last, temp[j].last) == 0)
            {
                if (strcmp(temp[i].first, temp[j].first) > 0)
                {
                    swap = temp[i];
                    temp[i] = temp[j];
                    temp[j] = swap;
                }
            }
        }
    }

    printf("Assigned seats in alphabetical order:\n");
    for (i = 0; i < count; i++)
    {
        printf("Seat %d: %s, %s\n",
               temp[i].id,
               temp[i].last,
               temp[i].first);
    }
}

void assign_seat(struct seat flight[], int size)
{
    int seat_num;

    printf("Enter seat number to assign (1-48, 0 to cancel): ");
    scanf("%d", &seat_num);

    if (seat_num == 0)
    {
        printf("Assignment cancelled.\n");
        return;
    }

    if (seat_num < 1 || seat_num > size)
    {
        printf("Invalid seat number.\n");
        return;
    }

    /* do not let user assign an already taken seat */
    if (flight[seat_num - 1].assigned == 1)
    {
        printf("That seat is already assigned.\n");
        return;
    }

    printf("Enter last name: ");
    scanf("%19s", flight[seat_num - 1].last);

    printf("Enter first name: ");
    scanf("%19s", flight[seat_num - 1].first);

    flight[seat_num - 1].assigned = 1;

    printf("Seat %d assigned to %s %s.\n",
           seat_num,
           flight[seat_num - 1].first,
           flight[seat_num - 1].last);
}

void delete_seat(struct seat flight[], int size)
{
    int seat_num;

    printf("Enter seat number to delete (1-48, 0 to cancel): ");
    scanf("%d", &seat_num);

    if (seat_num == 0)
    {
        printf("Delete cancelled.\n");
        return;
    }

    if (seat_num < 1 || seat_num > size)
    {
        printf("Invalid seat number.\n");
        return;
    }

    if (flight[seat_num - 1].assigned == 0)
    {
        printf("That seat is already empty.\n");
        return;
    }

    flight[seat_num - 1].assigned = 0;

    /* clear the old name out too */
    strcpy(flight[seat_num - 1].last, "");
    strcpy(flight[seat_num - 1].first, "");

    printf("Seat %d assignment deleted.\n", seat_num);
}