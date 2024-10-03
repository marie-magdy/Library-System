#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int month;
    int year;
} date;

typedef struct
{
    char ISBN[14];
    char name[50];
    char authorname[30];
    int quantity;
    float price;
    date publish;
} book;

book b[100];
int count=0;
char month[12][20]= {"January","February","March","April","May","June","July","August","September","October","November","December"};

void load()
{
    FILE *f2=fopen("books.txt","r");
    while(!feof(f2))
    {
        fscanf(f2,"%[^,],%[^,],%[^,],%d,%f,%d-%d\n",b[count].ISBN,b[count].name,b[count].authorname,&b[count].quantity,&b[count].price,&b[count].publish.month,&b[count].publish.year);
        count++;
    }
    fclose(f2);

}

void search ()//salma//
{
    char str[13];
    int i,m,flag=0;
    printf("enter ISBN number: ");
    scanf("%s",str);
    printf("\n");
    for(i=0; i<count; i++)
    {
        if (strcmp(b[i].ISBN,str)==0)
        {
            m= b[i].publish.month;
            printf("ISBN: %s\n",b[i].ISBN);
            printf("Title: %s\n",b[i].name);
            printf("Author: %s\n",b[i].authorname);
            printf("Quantity: %d\n",b[i].quantity);
            printf("Price: %.2f$\n",b[i].price);
            printf("Published: %s %d\n\n",month[m-1],b[i].publish.year);
            flag=1;
            break;
        }
    }
    if(flag==0)
        printf("The book is not found \n");
}

void sortByPrice()//salma//
{
    int pass,j;
    book temp;
    for(pass=1; pass<count; pass++)
    {
        for (j=0; j<count-pass; j++)
        {
            if( b[j].price > b[j+1].price)
            {
                temp=b[j];
                b[j]=b[j+1];
                b[j+1]=temp;
            }
        }
    }
}
void sortByTitle()//salma//
{
    int pass,i;
    book temp;
    for(pass=1; pass<count; pass++)
    {
        for(i=0; i<count-pass; i++)
        {
            if(  strcasecmp((b[i].name),(b[i+1].name))>0) //betcompare elcharacters bs malhahsh da3wa bel capital w elsmall//
            {
                temp=b[i];
                b[i]=b[i+1];
                b[i+1]=temp;
            }
        }
    }

}
void sortByDate()//salma//
{
    int pass,i;
    book temp;
    for(pass=1; pass<count; pass++)
    {
        for(i=0; i<count-pass; i++)
        {
            if( b[i].publish.year< b[i+1].publish.year)
            {
                temp=b[i];
                b[i]=b[i+1];
                b[i+1]=temp;
            }
            else if (b[i].publish.year== b[i+1].publish.year&& b[i].publish.month<b[i+1].publish.month)
            {
                temp=b[i];
                b[i]=b[i+1];
                b[i+1]=temp;
            }
        }
    }

}
void print()//salma//
{
    int n,i,flag=1;
    printf("Do you want to sort by:\n 1.Title\n 2.Price\n 3.Date\n");
    printf("choose number of desired sort: ");
    scanf("%d",&n);
    printf("\n");
    switch(n)
    {
    case 1:
        sortByTitle();
        break;
    case 2:
        sortByPrice();
        break;
    case 3:
        sortByDate();
        break;
    default:
        printf("Error wrong input\n");
        flag=0;
    }
    if(flag)
    {
        for(i=0; i<count; i++)
        {
            printf("ISBN: %s\n",b[i].ISBN);
            printf("Title: %s\n",b[i].name);
            printf("Author: %s\n",b[i].authorname);
            printf("Quantity: %d\n",b[i].quantity);
            printf("price: %.2f$\n",b[i].price);
            printf("Published:%s %d\n\n",month[b[i].publish.month-1],b[i].publish.year);
        }


    }
}

int  validate(char s[14])
{
    int i;
    for(i=0; i<13; i++)
    {
        if(isdigit(s[i])==0)
        {
            printf("Invalid ISBN\n");
            return 0;
        }
    }
    if(strlen(s)!=13)
    {
        printf("Invalid ISBN\n");
        return 0;
    }
    return 1;
}

int isvalidM(char m[20])
{
    int i;
    for (i=0; i<strlen(m); i++)
    {
        if(!isdigit(m[i]))
            return 0;
    }
    int x=atoi(m);
    if(x>=1 && x<=12)
        return 1;
    else
        return 0;
}
int isvalidY(char y[20])
{
    int i;
    for (i=0; i<strlen(y); i++)
    {
        if(!isdigit(y[i]))
            return 0;
    }
    int x=atoi(y);
    if(x>=1900 && x<=2023)
        return 1;
    else
        return 0;
}

void add() //sara//
{

    char s[14];
    char m[20];
    char y[20];
    do
    {
        printf("Enter ISBN of the book:");
        scanf("%s",s);
    }
    while(!validate(s));
    strcpy( b[count].ISBN,s);
    printf("Enter name of the book:");
    getchar();
    gets(b[count].name);

    printf("Enter name of the author:");
    gets(b[count].authorname);

    printf("Enter price of the book:");
    scanf("%f",&b[count].price);

    printf("Enter quantity of the book:");
    scanf("%d",&b[count].quantity);

    printf("Enter year of publish:");
    getchar();
    gets(y);
    while(!isvalidY(y))
    {
        printf(" Error\n");
        printf("Enter year of publish:");
        gets(y);
    }
    b[count].publish.year=atoi(y);
    printf("Enter month of publish:");
    gets(m);
    while(!isvalidM(m))
    {
        printf(" Error\n");
        printf("Enter month of publish:");
        gets(m);
    }
    b[count].publish.month=atoi(m);
    count++;

}
void Delete() //sara//
{
    int i,flag=0,pos;

    char target[14];
    printf("Enter ISBN:");
    scanf("%s",target);

    for(i=0; i<count; i++)
    {
        if(strcmp(target,b[i].ISBN)==0)
        {
            pos=i;
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        for(i=pos; i<count; i++)
        {
            b[i]=b[i+1];

        }
        count--;
        printf("\nBook deleted successfuly\n\n");
    }
    else
        printf("Not found!\n");
}
void save() //marie//
{
    int i;
    FILE *f ;
    f=fopen("books.txt","w");
    for(i=0 ; i<count ; i++)
    {
        if(i==count-1)
        {
            fprintf(f,"%s,%s,%s",b[i].ISBN,b[i].name,b[i].authorname);
            fprintf(f,",%d,%.2f,%d-%d",b[i].quantity,b[i].price,b[i].publish.month,b[i].publish.year);
        }
        else
        {
            fprintf(f,"%s,%s,%s",b[i].ISBN,b[i].name,b[i].authorname);
            fprintf(f,",%d,%.2f,%d-%d\n",b[i].quantity,b[i].price,b[i].publish.month,b[i].publish.year);
        }
    }
    fclose (f);
}
void advanc()
{
    int i,flag=0;
    char target[30];
    printf("enter key word: ");
    getchar();
    gets(target);
    for(i=0; i<count; i++)
    {
        char*x=strstr(b[i].name,target);
        if(x!=NULL)
        {
            flag=1;
            printf("Search results:\n");
            printf("ISBN: %s\n",b[i].ISBN);
            printf("Title: %s\n",b[i].name);
            printf("Author: %s\n",b[i].authorname);
            printf("Quantity: %d\n",b[i].quantity);
            printf("price: %.2f$\n",b[i].price);
            printf("Published:%s %d\n\n",month[b[i].publish.month-1],b[i].publish.year);

        }
    }
    if(flag==0)
        printf("No matches found\n");


}

void modify() //marie//
{
    char target[14];
    char m[20];
    char y[20];
    int i=0,choice,flag=0;
    do
    {
        printf("Enter ISBN of the book:");
        scanf("%s",target);

    }
    while(!validate(target));
    for (i=0; i<count; i++ )
    {
        if(strcmp(target,b[i].ISBN) == 0)
        {
            flag = 1;
            break;
        }
    }
    if(flag)
    {
        printf("You want to modify:\n");
        printf("1.the title \n");
        printf("2.the author\n");
        printf("3.the quantity\n");
        printf("4.the price\n");
        printf("5.the month of publishment \n");
        printf("6.the year of publishment\n");
        printf("Enter choice :");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("Enter the new title:");
            getchar();
            gets(b[i].name);
            break;
        case 2:
            printf("Enter the new author:");
            getchar();
            gets(b[i].authorname);
            break;

        case 3:
            printf("Enter the new quantity:");
            scanf("%d",&b[i].quantity);
            break;

        case 4:
            printf("Enter the new price:");
            scanf("%f",&b[i].price);
            break;

        case 5:
            printf("Enter month of publish:");
            getchar();
            gets(m);
            while(!isvalidM(m))
            {
                printf("Error\n");
                printf("Enter month of publish:");
                gets(m);
            }
            b[i].publish.month=atoi(m);
            break;
        case 6:
            printf("Enter year of publish:");
            getchar();
            gets(y);
            while(!isvalidY(y))
            {
                printf("Error\n");
                printf("Enter year of publish:");
                gets(y);
            }
            b[i].publish.year=atoi(y);
            break;
        default:
            printf("Invalid choice \n");
        }
    }
    else
        printf("ISBN is not found!\n");
}



void menu()
{
    load();
    int choice=0;
    while(choice!=8)
    {
        printf(" 1.Add\n 2.Delete\n 3.Modify\n 4.Search\n 5.Advanced Search\n 6.Print\n 7.Save\n 8.Quit\n");
        printf("choose number of desired operation: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            add();
            break;
        case 2:
            Delete();
            break;
        case 3:
            modify();
            break;
        case 4:
            search();
            break;
        case 5:
            advanc();
            break;
        case 6:
            print();
            break;
        case 7:
            save();
            break;
        case 8:
            quit();
            break;
        default:
            printf("Invalid choice!\n");

        }
    }

}

int checkcredentials (char x[],int n,char y[],int m)
{
    FILE *f1=fopen("credentials.txt","r");
    char s1[30],s2[10];
    fscanf(f1,"%s%s",s1,s2);
    if(strcmp(s1,x) == 0 && strcmp(s2,y)== 0)
    {
        printf("Login successful\n");
        return 1;
    }
    else  if(strcmp(s1,x)!=0 && strcmp(s2,y)!=0)
    {
        printf("Incorrect username and password\n");
        return 0;
    }

    else if(strcmp(s2,y)!=0)
    {
        printf("Incorrect password\n");
        return 0;
    }
    else
    {
        printf("Incorrect username\n");
        return 0;
    }
    fclose(f1);
}

void quit()
{
    int c;
    printf(" Are you sure you want to quit? all your changes will be discarded\n");
    do
    {
    printf("1.save 2.quit\n");
    scanf("%d",&c);
        if(c==1)
            save();
        else if(c==2)
            exit(0);
        else
            printf("Invalid Choice!\n");
    }
        while(c!=1&&c!=2);

}

int main()
{
    char x[30],y[10];
    int a,choice;
    while(1)
    {
        printf(" 1.Login 2.Quit\n");
        printf("choose number of desired operation: ");
        scanf("%d",&choice);
        if(choice == 1)
        {
            printf("Enter the username: ");
            scanf("%s",x);
            printf("Enter the password: ");
            scanf("%s",y);
            a=checkcredentials(x,30,y,10);
            if(a==1)
            {
                menu();
                break;
            }

            else
                continue;
        }
        else if(choice==2)
            return (0);
        else
            printf("Invalid option\n");
    }
    return 0;

}
