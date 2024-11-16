#include <stdio.h>
#include <string.h>
#define MAX_NAME 100
#define TOTAL_INDIVIDUALS 1000
#define TOTAL_FAMILIES 100
#define TOTAL_EXPENSES 48000
#define MAX_EXPENSES_BY_INDIVIDUAL 600
// date should be in format ddmm as integer
// one user can be a part of many families as in the question it is specified that the user should be a part of ATLEAST one family

int user_count = 0;
int family_count = 0;
int expense_count = 0;
struct individual
{
    int user_ID;
    char user_name[MAX_NAME];
    float income;
} total_individuals[TOTAL_INDIVIDUALS];

struct family
{
    int family_ID;
    char family_name[MAX_NAME];
    int user_ID_of_individuals_in_family[4];
    float family_income;
    float total_expense;
} total_families[TOTAL_FAMILIES];

struct expense
{
    int expense_ID;
    int user_ID_for_expense;
    char category[5][15];
    float expense;
    int date_of_expense;
} total_expenses[TOTAL_EXPENSES];

void initialise_database()
{
    int i;
    for (i = 0; i < TOTAL_INDIVIDUALS; i++)
    {
        total_individuals[i].user_ID = 0;
        total_individuals[i].user_name[0] = '\0';
        total_individuals[i].income = 0.00;
    }

    for (i = 0; i < TOTAL_FAMILIES; i++)
    {
        total_families[i].family_ID = 0;
        total_families[i].family_name[0] = '\0';
        total_families[i].family_income = 0.00;
        total_families[i].total_expense = 0.00;
    }
    for (i = 0; i < TOTAL_EXPENSES; i++)
    {
        total_expenses[i].expense_ID = 0;

        strcpy(total_expenses[i].category[0], "rent");
        strcpy(total_expenses[i].category[1], "utility");
        strcpy(total_expenses[i].category[2], "grocery");
        strcpy(total_expenses[i].category[3], "stationery");
        strcpy(total_expenses[i].category[4], "leisure");
        total_expenses[i].date_of_expense = 0;
        total_expenses[i].expense = 0.00;
    }
}

void insertion_sort_individuals()
{
    int i = 0, j;
    struct individual x = total_individuals[user_count - 1];
    while (total_individuals[user_count - 1].user_ID > total_individuals[i].user_ID && total_individuals[i].user_ID != 0)
    {
        i++;
    }
    for (j = user_count - 1; j > i; j--)
    {
        total_individuals[j] = total_individuals[j - 1];
    }
    total_individuals[j] = x;
}
void insertion_sort_family_members(int arr[])
{
    for (int i = 1; i < 4; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
void insertion_sort_family()
{
    int i = 0, j, k;
    struct family x = total_families[user_count - 1];
    while (total_families[family_count - 1].family_ID > total_families[i].family_ID && total_families[i].family_ID != 0)
    {
        i++;
    }
    for (j = family_count - 1; j > i; j--)
    {
        total_families[j] = total_families[j - 1];
    }
    total_families[j] = x;
    insertion_sort_family_members(total_families[family_count].user_ID_of_individuals_in_family);
}
void insertion_sort_expense()
{
    int i = 0, j;
    struct expense x = total_expenses[expense_count - 1];
    while (total_expenses[expense_count - 1].user_ID_for_expense > total_expenses[i].user_ID_for_expense && total_expenses[expense_count - 1].expense_ID > total_expenses[i].expense_ID && total_expenses[i].user_ID_for_expense != 0)
    {
        i++;
    }
    for (j = expense_count - 1; j > i; j--)
    {
        total_expenses[j] = total_expenses[j - 1];
    }
    total_expenses[j] = x;
}

int find_user_ID_in_array(int user_ID)
{
    int flag = 0, i;
    int user_index_is = 0;

    for (i = 0; i < user_count && flag == 0; i++)
    {
        if (user_ID == total_individuals[i].user_ID)
        {
            flag = 1;
            user_index_is = i;
        }
    }
    if (flag == 0)
    {
        user_index_is = user_count;
    }
    return user_index_is;
}
int find_family_ID_in_array(int family_ID)
{
    int flag = 0, i;
    int family_index_is = 0;

    for (i = 1; i < family_count && flag == 0; i++)
    {
        if (family_ID == total_families[i].family_ID)
        {
            flag = 1;
            family_index_is = i;
        }
    }
    if (flag == 0)
    {
        family_index_is = family_count;
    }

    return family_index_is;
}

void find_expenses_by_user_ID_in_expense_array(int user_ID, int expenseID_of_expense_by_the_user_ID[MAX_EXPENSES_BY_INDIVIDUAL])
{
    int i, k = 0;
    for (i = 0; i < expense_count; i++)
    {
        if (user_ID == total_expenses[i].user_ID_for_expense)
        {
            expenseID_of_expense_by_the_user_ID[k] = total_expenses[i].expense_ID;
            k++;
        }
    }
}

void add_user(int input_user_ID, int family_ID)
{
    int i = 0, flag = 0, j, k;
    i = find_user_ID_in_array(input_user_ID);

    j = find_family_ID_in_array(family_ID);

    if (i < user_count)
    {
        printf("user already exists\n");
    }

    else
    {
        user_count++;
        total_individuals[i].user_ID = input_user_ID;
        printf("enter individual's name\n");
        scanf("%s", total_individuals[i].user_name);
        printf("enter the income of individual\n");
        scanf(" %f", &total_individuals[i].income);
        for (k = 0; k < 4 && flag == 0; k++)
        {
            if (total_families[j].user_ID_of_individuals_in_family[k] == 0)
            {
                total_families[j].user_ID_of_individuals_in_family[k] = input_user_ID;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("no more family members can be added in family \n");
        }

        printf("user added\n");
    }

    insertion_sort_individuals();
}

void add_family(int family_ID)
{
    int i = 0, number_of_members, member_ID;
    i = find_family_ID_in_array(family_ID);

    if (i >= family_count)
    {
        family_count++;
        printf("enter family name\n");
        char familyname[MAX_NAME]; // surname
        scanf("%s", familyname);
        strcpy(familyname, total_families[i].family_name);
        printf("enter number of people in the family\n");
        scanf("%d", &number_of_members);
        for (int j = 0; j < number_of_members; j++)
        {
            {
                printf("enter user ID of the member in the family\n"); // add a unique one
                scanf("%d", &member_ID);
                int member_ID_index = find_user_ID_in_array(member_ID);
                if (member_ID_index < user_count)
                {
                    total_families[i].user_ID_of_individuals_in_family[j] = total_individuals[member_ID_index].user_ID;
                }
                else
                {
                    add_user(member_ID, family_ID);
                    printf("new user added\n");
                }
            }
        }
    }
    else
    {
        printf("family already exists\n");
    }
    insertion_sort_family();
}
int find_expense_index(int user_ID_of_expense)
{
    int i = 0, flag = 0;
    int expense_index_is = 0;
    for (i = 0; i < expense_count && flag == 0; i++)
    {
        flag = 1;
        expense_index_is = i;
    }
    if (flag == 0)
    {
        expense_index_is = expense_count;
    }
    return expense_index_is;
}
void add_expense(int input_user_ID, int input_date_of_Expense, char input_category[], float input_expense)
{
    int i, flag = 0, category_is = 0;

    int k = find_family_ID_in_array(input_user_ID); // add users which already exists

    i = find_expense_index(input_user_ID);
    expense_count++;
    total_expenses[i].expense_ID = expense_count;
    total_expenses[i].user_ID_for_expense = total_individuals[k].user_ID;
    total_expenses[i].date_of_expense = input_date_of_Expense;
    for (int j = 0; j < 5; j++)
    {
        if (strcmp(total_expenses[i].category[j], input_category) == 0 && flag == 0)
        {
            category_is = j;
            total_expenses[i].expense = input_expense;
            flag = 1;
        }
    }

    insertion_sort_expense();
}

void delete_user(int user_ID)
{
    int i = 0, j;
    i = find_user_ID_in_array(user_ID);
    for (j = i; j < user_count; j++)
    {
        total_individuals[j - 1] = total_individuals[j];
    }
    total_individuals[user_count - 1].user_ID = 0;
    total_individuals[user_count - 1].user_name[0] = '\0';
    total_individuals[user_count].income = 0;
    user_count--;
    if (user_count < 0)
    {
        user_count = 0;
    }
}

void update_or_delete_individual_or_family_details(char status[])
{
    char choice[20];
    int user_ID, family_ID, flag = 0, i = 0, j, k;
    int user_ID_of_family_member;

    if (strcmp(status, "delete") == 0)
    {
        printf("do you want to delete user or family\n");
        scanf("%s", choice);
        if (strcmp(choice, "individual") == 0)
        {
            printf("enter the userID to be deleted\n");
            scanf("%d", &user_ID);
            delete_user(user_ID);

            for (j = 0; j < family_count && flag == 0; j++)
            {
                for (int k = 0; k < 4; k++)
                {
                    if (total_families[j].user_ID_of_individuals_in_family[k] == user_ID)
                    {
                        total_families[j].user_ID_of_individuals_in_family[k] = 0;
                        flag = 1;
                    }
                }
            }
        }

        if (strcmp(choice, "family") == 0)
        {
            printf("enter the familyID of the family to be deleted\n");
            scanf("%d", &family_ID);
            for (i = 0; i < family_count && flag == 0; i++)
            {
                if (total_families[i].family_ID == family_ID)
                {
                    for (j = 0; j < 4; j++)
                    {
                        user_ID_of_family_member = total_families[i].user_ID_of_individuals_in_family[j];
                        delete_user(user_ID_of_family_member);
                    }
                    flag = 1;
                }
            }
            for (j = i; j < user_count; j++)
            {
                total_families[j - 1] = total_families[j];
            }
            total_families[family_count].family_ID = 0;
            total_families[family_count].family_name[0] = '\0';
            total_families[family_count].family_income = 0.00;
            total_families[family_count].total_expense = 0.00;
            for (j - 0; j < 4; j++)
            {
                total_families[family_count].user_ID_of_individuals_in_family[j] = 0;
            }
            family_count--;
        }
    }
    if (strcmp(status, "update") == 0)
    {
        printf("do you want to update the individual details or family details\n");
        scanf("%s", choice);
        if (strcmp(choice, "individual"))
        {
            printf("enter the user_ID of individual to be updated\n");
            scanf("%d", &user_ID);
            for (i = 0; i < user_count && flag == 0; i++)
            {
                if (total_individuals[i].user_ID == user_ID)
                {
                    flag = 1;
                }
            }
            printf("enter what you want to update username or income\n");
            scanf("%s", choice);
            if (strcmp(choice, "username") == 0)
            {
                printf("enter the changed username\n");
                scanf("%S", &total_individuals[i - 1].user_name);
            }
            if (strcmp(choice, "income") == 0)
            {
                printf("enter the changed income\n");
                scanf("%d", &total_individuals[i - 1].income);
            }
        }
        if (strcmp(choice, "family") == 0)
        {
            printf("enter the family_ID of family details to be updated\n");
            scanf("%d", &family_ID);
            for (i = 0; i < user_count && flag == 0; i++)
            {
                if (total_individuals[i].user_ID == user_ID)
                {
                    flag = 1;
                }
            }
            printf("enter what you want to update familyname or individuals belonging to family(individual)\n");
            scanf("%s", choice);
            if (strcmp(choice, "familyname") == 0)
            {
                printf("enter the new family name\n");
                scanf("%s", &total_families[i].family_name);
            }
            if (strcmp(choice, "individual") == 0)
            {
                printf("do you want to add or delete individual from family\n");
                scanf("%s", choice);
                printf("enter user_ID of individual\n");
                scanf("%d", user_ID);
                if (strcmp(choice, "add") == 0)
                {
                    int flag = 0;
                    k = find_family_ID_in_array(family_ID);
                    for (j = 0; j < 4 && flag == 0; j++)
                    {

                        if (total_families[k].user_ID_of_individuals_in_family[j] == 0)
                        {
                            total_families[k].user_ID_of_individuals_in_family[j] = user_ID;
                            flag = 1;
                        }
                    }
                    if (flag == 0)
                    {
                        printf("no more members can be added to family\n");
                    }
                }
                if (strcmp(choice, "delete") == 0)
                {
                    for (j = 0; j < 4; j++)
                    {
                        if (total_families[i].user_ID_of_individuals_in_family[j] == user_ID)
                        {
                            total_families[i].user_ID_of_individuals_in_family[j] = 0;
                        }
                    }
                }
            }
        }
    }
}
void update_or_delete_expense(int expense_ID)
{
    int i;
    char choice[12], change[12];
    printf("do you want to delete or update the expense\n");
    scanf("%s", choice);
    if (strcmp(choice, "update") == 0)
    {
        printf("do you want to change the amount or the category of the expense\n");
        scanf("%s", choice);
        if (strcmp(choice, "amount") == 0)
        {
            printf("enter the amount to be updated\n");
            scanf("%d", &total_expenses[expense_ID - 1].expense);
        }
        if (strcmp(choice, "category") == 0)
        {
            printf("enter the category expense should be changed from to the category it should be changed to\n");
            scanf("%s,%s", &choice, &change);
            for (i = 0; i < 5; i++)
            {
                if (strcmp(change, total_expenses[expense_ID - 1].category[i]) == 0)
                {
                    strcpy(change, total_expenses[expense_ID - 1].category[i]);
                }
            }
            printf("updated category is %s ", total_expenses[expense_ID - 1].category[i]); // line not working
        }
    }
    if (strcmp(choice, "delete") == 0)
    {
        for (i = expense_ID; i < expense_count; i++)
        {
            total_expenses[i] = total_expenses[i + 1];
        }
        total_expenses[expense_count].expense_ID = 0;
        total_expenses[expense_count].user_ID_for_expense = 0;
        total_expenses[expense_count].date_of_expense = 0;
        total_expenses[expense_count].expense = 0.00;
        expense_count--;
    }
    insertion_sort_expense();
}

float get_total_expense(int family_ID, int date, float target_of_month)
{
    int i = 0, j = 0, flag = 0, k;
    float total_family_expense = 0;
    int month = date % 100;
    int family_index_is;

    for (i = 0; i < family_count && flag == 0; i++)
    {
        if (family_ID == total_families[i].family_ID)
        {
            flag = 1;
            family_index_is = i;
        }
    }
    for (j = 0; j < 4; j++)
    {
        for (k = 0; k < expense_count; k++)
        {
            if (total_families[i].user_ID_of_individuals_in_family[j] == total_expenses[k].user_ID_for_expense)
            {
                if (month = total_expenses[i].date_of_expense % 100)
                {
                    total_family_expense = total_family_expense + total_expenses[k].expense;
                }
            }
        }
    }
    if (target_of_month < total_family_expense)
    {
        float diff = total_family_expense - target_of_month;
        printf("The expense exceeds by %f \n", diff);
    }
    else
    {
        printf("does not exceed the budget of the month\n");
    }

    return total_family_expense;
}
int get_highest_expense_day(int family_ID)
{
    int i, j, k, flag = 0, max = 0, required_day;
    float expense_for_a_day;
    i = find_family_ID_in_array(family_ID);
    for (int day = 1; day <= 10; day++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < expense_count; k++)
            {
                if (total_families[i].user_ID_of_individuals_in_family[j] == total_expenses[k].user_ID_for_expense)
                {

                    if (day == total_expenses[k].date_of_expense / 100)
                    {
                        expense_for_a_day = expense_for_a_day + total_expenses[k].expense;
                    }
                }
            }
        }
        if (expense_for_a_day > max)
        {
            max = expense_for_a_day;
            required_day = day;
        }
    }
    return required_day;
}
float get_individual_expense(int user_ID, int month)
{
    int i;
    int j;
    float total_expense_for_individual;
    char category_wise[5][15] = {"rent", "utility", "grocery", "stationery", "leisure"};
    float category_expense[5] = {0};
    for (i = 0; i < expense_count; i++)
    {
        if (total_expenses[i].user_ID_for_expense == user_ID && month == total_expenses[i].date_of_expense % 100)
        {
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(total_expenses[i].category[j], category_wise[j]) == 0)
                {
                    category_expense[j] = category_expense[j] + total_expenses[i].expense;
                }
            }
        }
    }

    // Sort the categories and expenses in descending order by expense
    for (i = 0; i < 5 - 1; i++) // Sorting using Bubble Sort (descending order)
    {
        for (j = 0; j < 4 - i; j++)
        {
            if (category_expense[j] < category_expense[j + 1])
            {
                // Swap expenses
                float temp_expense = category_expense[j];
                category_expense[j] = category_expense[j + 1];
                category_expense[j + 1] = temp_expense;

                // Swap corresponding categories
                char temp_category[15];
                strcpy(temp_category, category_wise[j]);
                strcpy(category_wise[j], category_wise[j + 1]);
                strcpy(category_wise[j + 1], temp_category);
            }
        }
    }

    //  Print the total individual expense and category-wise expenses
    printf("Total expense for user ID %d in month %d: %f\n", user_ID, month, total_expense_for_individual);
    printf("Category-wise expenses in descending order:\n");
    for (i = 0; i < 5; i++)
    {
        if (category_expense[i] > 0)
        {
            printf("%s: %f\n", category_wise[i], category_expense[i]);
        }
    }
    return total_expense_for_individual;
}
float get_categorial_expense(char category[], int family_ID, int month)
{
    int i, j, k, flag = 0;
    float individual_expense[4];
    float total_family_expense;
    i = find_family_ID_in_array(family_ID);
    int user_expense_id[4] = {0};
    for (j = 0; j < 4; j++)
    {
        for (k = 0; k < expense_count; k++)
        {
            if (total_families[i].user_ID_of_individuals_in_family[j] == total_expenses[k].user_ID_for_expense)
            {
                for (int l = 0; l < 5; l++)
                {
                    if (strcmp(category, total_expenses[k].category[l]) && month == total_expenses[k].date_of_expense % 100)
                    {
                        individual_expense[j] = individual_expense[j] + total_expenses[k].expense;
                    }
                }
            }
        }
        total_family_expense = total_family_expense + individual_expense[j];
        user_expense_id[j] = total_families[i].user_ID_of_individuals_in_family[j];
    }
    // printing individual contribution of each individual of particular category
    // Sort the individual contributions in descending order
    for (j = 0; j < 4 - 1; j++)
    {
        for (k = j + 1; k < 4; k++)
        {
            if (individual_expense[j] < individual_expense[k])
            {
                // Swap the expenses
                float temp_expense = individual_expense[j];
                individual_expense[j] = individual_expense[k];
                individual_expense[k] = temp_expense;

                // Swap the corresponding user IDs
                int temp_user = user_expense_id[j];
                user_expense_id[j] = user_expense_id[k];
                user_expense_id[k] = temp_user;
            }
        }
    }

    // Print the total family expense for the given category
    printf("Total family expense for category '%s' in month %d: %f\n", category, month, total_family_expense);

    // Print the individual contributions in descending order
    printf("Individual contributions (sorted):\n");
    for (j = 0; j < 4; j++)
    {
        if (individual_expense[j] > 0)
        { // Only print if there was an expense
            printf("User %d spent %f\n", user_expense_id[j], individual_expense[j]);
        }
    }

    return total_family_expense;
}

int main()
{
    initialise_database();
    // giving values to data base

    add_user(7, 6);
    add_user(3, 3);
    add_user(15, 7);
    add_user(12, 1);
    add_user(25, 5);
    add_user(18, 9);
    add_user(9, 7);
    add_user(2, 4);
    add_user(24, 5);
    add_user(11, 8);
    add_user(8, 3);
    add_user(1, 4);
    add_user(22, 7);
    add_user(21, 6);
    add_user(17, 9);
    add_user(19, 2);
    add_user(23, 8);
    add_user(13, 5);
    add_user(10, 1);
    add_user(14, 5);
    add_user(16, 8);
    add_user(4, 2);
    add_user(6, 6);
    add_user(5, 2);
    add_user(20, 3);

    add_family(7);
    add_family(2);
    add_family(9);
    add_family(5);
    add_family(1);
    add_family(4);
    add_family(3);
    add_family(8);
    add_family(6);
    add_family(11);
    add_family(12);
    add_family(15);
    add_family(17);
    add_family(13);
    add_family(16);
    add_family(14);
    add_family(20);
    add_family(21);
    add_family(18);
    add_family(19);
    add_family(23);
    add_family(22);
    add_family(10);
    add_family(25);
    add_family(24);

    add_expense(7, 1209, "rent", 5000.00);
    add_expense(18, 1309, "grocery", 1500.00);
    add_expense(3, 1111, "utility", 1000.00);
    add_expense(12, 1010, "leisure", 8000.00);
    add_expense(2, 1110, "stationery", 2500.00);
    add_expense(19, 1210, "rent", 4000.00);
    add_expense(13, 0210, "grocery", 3000.00);
    add_expense(8, 910, "utility", 1200.00);
    add_expense(16, 1509, "stationery", 4500.00);
    add_expense(10, 1809, "leisure", 7000.00);
    add_expense(24, 1909, "grocery", 2000.00);
    add_expense(5, 1210, "utility", 1500.00);
    add_expense(21, 609, "rent", 3000.00);
    add_expense(1, 1210, "grocery", 5000.00);
    add_expense(4, 2209, "stationery", 2500.00);
    add_expense(11, 1410, "utility", 3000.00);
    add_expense(23, 2909, "leisure", 4000.00);
    add_expense(20, 0110, "rent", 2500.00);
    add_expense(9, 0310, "stationery", 3500.00);
    add_expense(14, 910, "utility", 2000.00);
    add_expense(15, 0110, "grocery", 4500.00);
    add_expense(25, 2509, "leisure", 3000.00);
    add_expense(22, 1709, "utility", 1700.00);
    add_expense(6, 1409, "rent", 1000.00);
    add_expense(17, 1010, "stationery", 5500.00);

    printf("welcome to expense tracker system\n");
    // add users
    int userid;
    int familyid;

    printf("what do you want to do?enter choice\n");
    int choice;
    printf(" 1.Add a user\n 2.Add expense\n 3.Create family\n 4.Update or detlete individual or family details \n5.Update or delete an expense\n 6.Get total expense of a family for a month\n 7.get categorical expense for a category\n8.Get highest expense day\n9.Get a particular indivdual expense\n");
    scanf("%d", &choice);

    char status[15];

    switch (choice)
    {
    case 1:
    {

        printf("enter user id\n");
        scanf("%d", &userid);
        printf("enter family id\n");
        scanf("%d", &familyid);

        add_user(userid, familyid);
        break;
    }

    case 2:
    {
        int userid;
        int dateofexpense;
        char category[15];
        float expense;
        printf("enter user id\n");
        scanf("%d", &userid);
        printf(" date of expense\n");
        scanf("%d", &dateofexpense);
        printf("category of expense\n");
        scanf("%s", category);
        printf("enter expense\n");
        scanf("%f", &expense);

        add_expense(userid, dateofexpense, category, expense);
        break;
    }

    case 3:
    {
        int familyid;
        printf("enter family id\n");
        scanf("%d", &familyid);
        add_family(familyid);
        break;
    }

    case 4:
    {
        printf("whether you want to delete or update\n");
        scanf("%s", status);
        update_or_delete_individual_or_family_details(status);
        break;
    }
    case 5:
    {

        int expenseid;
        printf("enter expense id\n");
        scanf("%d", &expenseid);
        update_or_delete_expense(expenseid);
        break;
    }
    case 6:
    {

        printf("enter family id\n");
        scanf("%d", &familyid);

        // calculating expense of the month
        int date;
        float target;
        printf("print any date of the month of which you need the expense\n");
        scanf("%d", &date);
        printf("what is your budget of the month?\n");
        scanf("%f", &target);
        float totalofmonth = get_total_expense(familyid, date, target);
        printf("total expense for the month is %f ", totalofmonth);
        break;
    }
    case 7:
    {
        printf("enter family id\n");
        scanf("%d", &familyid);

        int month;
        printf("enter the month so that we can calculate the highest expense day \n");
        scanf("%d", &month);
        char particularcategory[15];
        printf("enter the category for which you want to calculate the expense \n");
        scanf("%s", particularcategory);
        float e = get_categorial_expense(particularcategory, familyid, month);
        printf("expense of the category %s is %f ", particularcategory, e);
        break;
    }
    case 8:
    {

        printf("enter family id\n");
        scanf("%d", &familyid);

        int day = get_highest_expense_day(familyid);
        printf("The date with highest expense is %d \n", day);
        break;
    }
    case 9:
    {
        printf("enter the user id :");
        scanf("%d", &userid);

        int month;
        printf("enter the month for which you want to calculate individual expenses\n");
        scanf("%d", &month);

        int s = get_individual_expense(userid, month);
        printf("the total expense for the individual for the month is %f ", s);
        break;
    }
    default:
    {
        printf("enter a valid choice:");
    }
    }

    return 0;
}