#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct contacts
{
    char first_name[30];
    char last_name[30];
    long int phoneno;
};

void add_contact();
void display_contacts();
void search_contact();
void update_contact();
void delete_contact();
int compare(const void *a, const void *b);

int c = 0;

void main()
{
    // system("cls");
    getchar();

    system("clear");

    printf("\t\t\t\t _____\t _____\t _    .\t_______\t   _  \t _____\t_______\t \n");
    printf("\t\t\t\t|     \t|     |\t| \\   |\t   |  \t  / \\  \t|     \t   |  \t\n");
    printf("\t\t\t\t|     \t|     |\t|  \\  |\t   |  \t /___\\ \t|     \t   |  \t \n");
    printf("\t\t\t\t|_____\t|_____|\t|   \\_|    |   \t/     \\\t|_____\t   |   \t \n");
    printf("\n\n\t\t\t\t\t\tPress Enter to continue...\n");
    getchar();

    int choice;
    system("clear");
    while (1)
    {

        printf("\t\t\t\t _____\t _____\t _    .\t_______\t   _  \t _____\t_______\t \n");
        printf("\t\t\t\t|     \t|     |\t| \\   |\t   |  \t  / \\  \t|     \t   |  \t\n");
        printf("\t\t\t\t|     \t|     |\t|  \\  |\t   |  \t /___\\ \t|     \t   |  \t \n");
        printf("\t\t\t\t|_____\t|_____|\t|   \\_|    |   \t/     \\\t|_____\t   |   \t \n");

        // printf("\n\n\t\t\t\t\t============ CONTACTS ============\n");
        printf("\n\t\t\t\t\t\t  1:add contacts");
        printf("\n\t\t\t\t\t\t  2:show all contacts");
        printf("\n\t\t\t\t\t\t  3:search contacts");
        printf("\n\t\t\t\t\t\t  4:update contacts");
        printf("\n\t\t\t\t\t\t  5:delete contacts");
        printf("\n\t\t\t\t\t\t  6:Exit\n");
        printf("\t\t\t  \t\t      __________________________\n");
        printf("\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\tEnter your choice: ");
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
            printf("Exiting program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void add_contact()
{
    // system("cls");
    system("clear");
    char another;
    FILE *fp;
    int n, i;
    struct contacts info;
    do
    {
        printf("\n\t\t\t\t\t===== Add Contacts ====\n\n\n");
        printf("\t\t\t\t\tEnter first name  : ");
        scanf("%s", info.first_name);
        printf("\t\t\t\t\tEnter second name : ");
        scanf("%s", info.last_name);
        printf("\n\t\t\t\t\tEnter the phoneno : ");
        scanf("%ld", &info.phoneno);

        fp = fopen("contacts.txt", "a");
        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\t Can't open files\n");
            return;
        }

        fwrite(&info, sizeof(struct contacts), 1, fp);
        fclose(fp);

        printf("\n\n\t\t\t\t\tContact stored successfully\n");
        printf("\t\t\t\tDo you want to add another record ?(y/n) :");
        scanf("%s", &another);

    } while (another == 'y' || another == 'Y');
    system("clear");
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
    // system("cls");
    system("clear");
    getchar();

    FILE *fp;
    struct contacts contactArray[100];
    struct contacts info;
    int c = 0;

    fp = fopen("contacts.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\t\t\t Can't open files\n");
        return;
    }

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        contactArray[c++] = info;
    }

    fclose(fp);
    qsort(contactArray, c, sizeof(struct contacts), compare);

    printf("\n\n\t\t\t\t\t============ CONTACTS ============\n\n");
    for (int i = 0; i < c; i++)
    {
        printf("\n\t\t\t\t\t\t %d) Name  : %s %s\n", i + 1, contactArray[i].first_name, contactArray[i].last_name);
        printf("\t\t\t\t\t\t   Phone no : %ld\n", contactArray[i].phoneno);
        printf("\t\t\t\t\t\t-------------------------\n");
    }
    printf("\n\t\t\t\t\t\tPress Enter to continue...\n");
    // getch();
    getchar();
    system("clear");
}

void search_contact()
{
    // system("cls");
    system("clear");
    getchar();
    FILE *fp;
    struct contacts info;
    char name[30];
    int found = 0;

    printf("\t\t\t\t\t\tEnter the name : ");
    scanf("%s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
    }

    fp = fopen("contacts.txt", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open file.\n");
        return;
    }

    printf("\n\n\n\t\t\t\t\t\t===== Search Result =====\n\n\n");

    getchar();

    while (fread(&info, sizeof(struct contacts), 1, fp))
    {
        char contactFirstName[30];
        strcpy(contactFirstName, info.first_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }

        if (strcmp(contactFirstName, name) == 0)
        {
            printf("\t\t\t\t\t\tName: %s %s\n", info.first_name, info.last_name);
            printf("\t\t\t\t\t\tPhone Number: %ld\n", info.phoneno);
            printf("\t\t\t\t\t\t____________________________\n");
            getchar();
            found = 1;
        }
    }
    if (!found)
    {
        printf("\n\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
    }
    fclose(fp);
    // getch();
    system("clear");
}
void update_contact()
{
    FILE *fp, *fp1;
    struct contacts info;
    char name[30];
    int found = 0;

    printf("\t\t\t\t\t\tEnter the name to update : ");
    scanf(" %s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
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
        char contactFirstName[30];
        strcpy(contactFirstName, info.first_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }

        if (strcmp(contactFirstName, name) == 0)
        {
            printf("\n\t\t\t\t\t\tEnter new first name  : ");
            scanf("%s", info.first_name);
            printf("\t\t\t\t\t\tEnter new second name  : ");
            scanf("%s", info.last_name);
            printf("\t\t\t\t\t\tEnter new phoneno : ");
            scanf("%ld", &info.phoneno);
            found = 1;
            printf("\n\n\t\t\t\t\t\tcontact updated successfully");
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
        system("clear");
    }
    else
    {
        printf("\n\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
        system("clear");
    }
}

void delete_contact()
{
    FILE *fp, *fp1;
    struct contacts info;
    char name[30];
    int found = 0;

    printf("\t\t\t\t\t\tEnter the name to delete : ");
    scanf("%s", name);
    for (int i = 0; name[i]; i++)
    {
        name[i] = tolower(name[i]);
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
        char contactFirstName[30];
        strcpy(contactFirstName, info.first_name);
        for (int i = 0; contactFirstName[i]; i++)
        {
            contactFirstName[i] = tolower(contactFirstName[i]);
        }

        if (strcmp(contactFirstName, name) == 0)
        {
            found = 1;
            printf("\n\t\t\t\t\t\tContact deleted successfully.\n");
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
        system("clear");
    }
    else
    {
        printf("\n\t\t\t\t\t\tNo contacts founds by that name\n");
        getchar();
        system("clear");
    }
}
