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
void delete_contact();
int compare(const void *a, const void *b);

int c = 0;

void main()
{
    int choice;

    while (1)
    {
        printf("\t\t\t\t ======= contacts =======\n");
        printf("\n\t\t\t\t  1:add contacts");
        printf("\n\t\t\t\t  2:show all contacts");
        printf("\n\t\t\t\t  3:search contacts");
        printf("\n\t\t\t\t  4:delete contacts");
        printf("\n\t\t\t\t  5:Exit\n");
        printf("\t\t\t        __________________________\n");
        printf("\t\t\t\t\n");
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
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
            printf("Exiting program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

void add_contact()
{
    char another;
    FILE *fp;
    int n, i;
    struct contacts info;
    do
    {
        printf("\n\t\t\t\t===== Add Contacts ====\n\n\n");
        printf("Enter first name  : ");
        scanf("%s", info.first_name);
        printf("Enter second name  : ");
        scanf("%s", info.last_name);
        printf("\nEnter the phoneno : ");
        scanf("%ld", &info.phoneno);

        fp = fopen("contacts.txt", "a");
        if (fp == NULL)
        {
            fprintf(stderr, "\t\t\t Can't open files\n");
            return;
        }

        fwrite(&info, sizeof(struct contacts), 1, fp);
        fclose(fp);

        printf("\t\t\t\tContact stored successfully\n");
        printf("\t\t\tDo you want to add another record ?(y/n) :");
        scanf("%s", &another);

    } while (another == 'y' || another == 'Y');
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

    printf("\n\t\t\t\t===== Contacts ====\n\n\n");

    for (int i = 0; i < c; i++)
    {
        printf("\n\t\t\t\t %d) Name : %s %s\n", i + 1, contactArray[i].first_name, contactArray[i].last_name);
        printf("\t\t\t\t    Phone no : %ld\n", contactArray[i].phoneno);
        printf("\t\t\t\t-------------------------\n");
    }
}
void search_contact()
{
    FILE *fp;
    struct contacts info;
    char name[30];
    int found = 0;

    printf("Enter the name : ");
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

    printf("\t\t\t===== Search Result =====\n\n\n");

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
            printf("Name: %s %s\n", info.first_name, info.last_name);
            printf("Phone Number: %ld\n", info.phoneno);
            printf("____________________________\n");
            found = 1;
        }
    }
    if (!found)
    {
        printf("\n\t\t\tNo contacts founds by that name\n");
    }
    fclose(fp);
}
