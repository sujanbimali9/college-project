#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define green_colour "\033[1;32m"
#define blue_colour "\033[0;35m"
#define red_colour "\033[0;31m"
#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 30
#define MAX_PHONE_LENGTH 10

struct contacts
{
    char first_name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    long int phoneno;
};

void clrscr();
void add_contact();
void display_contacts();
void search_contact();
void update_contact();
void delete_contact();
int compare(const void *a, const void *b);

int c = 0;

void main()
{
    getchar();
    clrscr();
    printf(blue_colour);
    printf("\t\t\t\t ______    ________    ___     _    _________    ___       ______    _________\n");
    printf("\t\t\t\t|  ____|  |  ____  |  |   \\   | |  |___   ___|  / _ \\     |  ____|  |___   ___|\n");
    printf("\t\t\t\t| |       | |    | |  | |\\ \\  | |      | |     / /_\\ \\    | |           | |  \n");
    printf("\t\t\t\t| |       | |    | |  | | \\ \\ | |      | |    / ____  \\   | |           | | \n");
    printf("\t\t\t\t| |____   | |____| |  | |  \\ \\| |      | |   / /     \\ \\  | |____       | |  \n");
    printf("\t\t\t\t|______|  |________|  |_|   \\___|      |_|  /_/       \\_\\ |______|      |_| \n");

    printf("\n\n\t\t\t\t\t\t\tPress Enter to continue...\n");
    getchar();

    int choice;
    clrscr();
    while (1)
    {
        printf(blue_colour);

        clrscr();
        printf("\t\t\t\t ______    ________    ___     _    _________    ___       ______    _________\n");
        printf("\t\t\t\t|  ____|  |  ____  |  |   \\   | |  |___   ___|  / _ \\     |  ____|  |___   ___|\n");
        printf("\t\t\t\t| |       | |    | |  | |\\ \\  | |      | |     / /_\\ \\    | |           | |  \n");
        printf("\t\t\t\t| |       | |    | |  | | \\ \\ | |      | |    / ____  \\   | |           | | \n");
        printf("\t\t\t\t| |____   | |____| |  | |  \\ \\| |      | |   / /     \\ \\  | |____       | |  \n");
        printf("\t\t\t\t|______|  |________|  |_|   \\___|      |_|  /_/       \\_\\ |______|      |_| \n");

        printf(green_colour);

        // printf("\n\n\t\t\t\t\t============ CONTACTS ============\n");
        printf("\n\t\t\t\t\t\t\t  1:add contacts");
        printf("\n\t\t\t\t\t\t\t  2:show all contacts");
        printf("\n\t\t\t\t\t\t\t  3:search contacts");
        printf("\n\t\t\t\t\t\t\t  4:update contacts");
        printf("\n\t\t\t\t\t\t\t  5:delete contacts");
        printf(red_colour);
        printf("\n\t\t\t\t\t\t\t  6:Exit\n");
        printf(green_colour);
        printf("\t\t\t  \t\t\t      __________________________\n");
        printf("\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        printf("\n\n");
        switch (choice)
        {
        case 1:

            add_contact();
            c++;
            break;
        case 2:
            display_contacts();
            break;
        case 3:
            search_contact();
            break;
        case 4:
            update_contact();
            break;
        case 5:

            delete_contact();
            break;
        case 6:
            printf(red_colour);
            printf("Exiting program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
        printf("\033[1;33m");
    }
}

void clrscr()
{

    // checking the platform

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void add_contact()
{
    clrscr();
    char another;
    FILE *fp;
    int n, i;
    struct contacts info;
    do
    {
        printf("\n\t\t\t\t\t\t===== Add Contacts ====\n\n\n");
        printf("\t\t\t\t\t\tEnter first name  : ");
        scanf("%s", info.first_name);
        printf("\t\t\t\t\t\tEnter second name : ");
        scanf("%s", info.last_name);
        printf("\n\t\t\t\t\t\tEnter the phoneno : ");
        scanf("%ld", &info.phoneno);

        fp = fopen("contacts.txt", "a");
        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\t Can't open files\n");
            return;
        }

        fwrite(&info, sizeof(struct contacts), 1, fp);
        fclose(fp);

        printf("\n\n\t\t\t\t\t\tContact stored successfully\n");
        printf("\t\t\t\t\tDo you want to add another record ?(y/n) :");
        scanf("%s", &another);

    } while (another == 'y' || another == 'Y');
    clrscr();
}

int compare(const void *a, const void *b)
{
    const struct contacts *contactsA = (const struct contacts *)a;
    const struct contacts *contactsB = (const struct contacts *)b;

    int result = strcmp(contactsA->first_name, contactsB->first_name);

    if (result == 0)
    {
        result = strcmp(contactsA->last_name, contactsB->last_name);
    }

    return result;
}

void display_contacts()
{
    clrscr();
    getchar();

    FILE *fp;
    struct contacts contactArray[MAX_CONTACTS];
    struct contacts info;
    int c = 0;

    fp = fopen("contacts.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\t\t Can't open files\n");
        return;
    }

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        contactArray[c++] = info;
    }

    fclose(fp);
    qsort(contactArray, c, sizeof(struct contacts), compare);

    printf("\n\n\t\t\t\t\t\t     ============ CONTACTS ============\n\n");
    for (int i = 0; i < c; i++)
    {
        printf("\n\t\t\t\t\t\t\t %d) Name  : %s %s\n", i + 1, contactArray[i].first_name, contactArray[i].last_name);
        fflush(stdin);
        printf("\t\t\t\t\t\t\t   Phone no : %ld\n", contactArray[i].phoneno);
        printf("\t\t\t\t\t\t\t-------------------------\n");
    }
    printf("\n\t\t\t\t\t\t\tPress Enter to continue...\n");
    getchar();
    clrscr();
}

void search_contact()
{
    clrscr();
    getchar();
    FILE *fp;
    struct contacts info;
    char name[MAX_NAME_LENGTH], lastname[MAX_NAME_LENGTH];
    int found = 0;

    printf("\t\t\t\t\t\t\tEnter the name : ");
    scanf("%s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
    }
    printf("\t\t\t\t\t\t\tEnter the lastname : ");
    scanf("%s", lastname);

    for (int i = 0; lastname[i]; i++)
    {
        lastname[i] = tolower(lastname[i]);
    }

    fp = fopen("contacts.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file.\n");
        return;
    }

    printf("\n\n\n\t\t\t\t\t\t\t===== Search Result =====\n\n\n");

    getchar();

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        char contactFirstName[MAX_NAME_LENGTH], contactLastName[MAX_NAME_LENGTH];
        strcpy(contactFirstName, info.first_name);
        strcpy(contactLastName, info.last_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }

        for (int i = 0; contactLastName[i]; i++)
        {
            contactLastName[i] = tolower(contactLastName[i]);
        }

        if (strcmp(contactFirstName, name) == 0 && strcmp(contactLastName, lastname) == 0)
        {
            printf("\t\t\t\t\t\t\tName: %s %s\n", info.first_name, info.last_name);
            printf("\t\t\t\t\t\t\tPhone Number: %ld\n", info.phoneno);
            printf("\t\t\t\t\t\t\t____________________________\n");
            getchar();

            found = 1;
        }
    }
    if (!found)
    {
        printf("\n\t\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
    }
    fclose(fp);
    clrscr();
}
void update_contact()
{
    FILE *fp, *fp1;
    struct contacts info;
    char name[MAX_NAME_LENGTH], lastname[MAX_NAME_LENGTH];
    int found = 0;

    printf("\t\t\t\t\t\t\tEnter the name to update : ");
    scanf(" %s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
    }
    printf("\t\t\t\t\t\t\tEnter the lastname : ");
    scanf("%s", lastname);

    for (int i = 0; lastname[i]; i++)
    {
        lastname[i] = tolower(lastname[i]);
    }

    fp = fopen("contacts.txt", "r");
    fp1 = fopen("tempContacts.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file.\n");
        return;
    }

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        char contactFirstName[MAX_NAME_LENGTH], contactLastName[MAX_NAME_LENGTH];
        strcpy(contactFirstName, info.first_name);
        strcpy(contactLastName, info.last_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }
        for (int i = 0; contactLastName[i]; i++)
        {
            contactLastName[i] = tolower(contactLastName[i]);
        }

        if (strcmp(contactFirstName, name) == 0 && strcmp(contactLastName, lastname) == 0)
        {
            printf("\n\t\t\t\t\t\t\tEnter new first name  : ");
            scanf("%s", info.first_name);
            printf("\t\t\t\t\t\t\tEnter new second name  : ");
            scanf("%s", info.last_name);
            printf("\t\t\t\t\t\t\tEnter new phoneno : ");
            scanf("%ld", &info.phoneno);
            found = 1;
            printf("\n\n\t\t\t\t\t\t\tcontact updated successfully");
            getchar();
        }
        fwrite(&info, sizeof(struct contacts), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    getchar();

    if (found)
    {
        fp1 = fopen("tempContacts.txt", "r");
        fp = fopen("contacts.txt", "w");

        while (fread(&info, sizeof(struct contacts), 1, fp1))
        {
            fwrite(&info, sizeof(struct contacts), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
        remove("tempContacts.txt");
        clrscr();
    }
    else
    {
        printf("\n\t\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
        clrscr();
    }
}

void delete_contact()
{
    FILE *fp, *fp1;
    struct contacts info;
    char name[MAX_NAME_LENGTH], lastname[MAX_NAME_LENGTH];
    int found = 0;

    printf("\t\t\t\t\t\t\tEnter the name to delete : ");
    scanf("%s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
    }

    printf("\t\t\t\t\t\t\tEnter the lastname : ");
    scanf("%s", lastname);

    for (int i = 0; lastname[i]; i++)
    {
        lastname[i] = tolower(lastname[i]);
    }

    fp = fopen("contacts.txt", "r");
    fp1 = fopen("tempContacts.txt", "w");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file.\n");
        return;
    }

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        char contactFirstName[MAX_NAME_LENGTH], contactLastName[MAX_NAME_LENGTH];
        strcpy(contactFirstName, info.first_name);
        strcpy(contactLastName, info.last_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }
        for (int i = 0; contactLastName[i]; i++)
        {
            contactLastName[i] = tolower(contactLastName[i]);
        }

        if (strcmp(contactFirstName, name) == 0 && strcmp(contactLastName, lastname) == 0)
        {
            found = 1;
            printf("\n\t\t\t\t\t\t\tContact deleted successfully.\n");
            getchar();
        }
        else
            fwrite(&info, sizeof(struct contacts), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);
    getchar();
    if (found)
    {
        fp1 = fopen("tempContacts.txt", "r");
        fp = fopen("contacts.txt", "w");

        while (fread(&info, sizeof(struct contacts), 1, fp1))
        {
            fwrite(&info, sizeof(struct contacts), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
        remove("tempContacts.txt");
        clrscr();
    }
    else
    {
        printf("\n\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
        clrscr();
    }
}
