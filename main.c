#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>

#define ANS 15
#define ACS 4
COORD coord= {0,0}; // this is global variable
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*declaration of checking functions*/
void c_code(char[]);
int check(char[]);

/*structure declaration*/
typedef struct
{
    char name[ANS],code[ACS];
    int quantity;
    float price;
} rec;
rec item;

/*declaration of main menu functions*/
void bill() ;
void edit();
void add();
void del();
void exit();

/*declaration of display functions*/
void cursor(int);
void dbill();
void d_mainmenu();
void display(rec *,int,int);
void dis_con();
void d_search();
void highlight(int,int);

/*declaration of display submenu functions*/
void d_code();
void d_price();
void d_quan();
void d_all();

/*start of main*/
int main()
{
    d_mainmenu();
    return 0;
}

void d_mainmenu()
{
    int i;
    const char *menu[]= {"   Calculate Bill","   Add Product","   Edit Product","   Display All  ","   Search Product", "   Delete Product","   Exit"};
    system("cls");
    gotoxy(30,10);
    printf("------WERMUT------");
    gotoxy(30,11);
    printf("DEPARTMENTAL STORE");
    gotoxy(33,18);
    printf("MAIN MENU");
    gotoxy(33,20);
    printf("------------------");
    for (i=0; i<=6; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    cursor(7);
}

void d_search()
{
    int i;
    const char *menu[]= {"   By Code","   By Price","   By Quantity","   Back to main menu"};
    system("cls");
    gotoxy(33,18);
    printf("SEARCH MENU");
    for (i=0; i<=3; i++)
    {
        gotoxy(30,22+i+1);
        printf("%s\n\n\n",menu[i]);
    }
    cursor(4);
}

/*function for cursor movement*/
void cursor(int no)
{
    int count=1;
    char ch='0';
    gotoxy(30,23);
    while(1)
    {
        switch(ch)
        {
        case 80:
            count++;
            if (count==no+1) count=1;
            break;
        case 72:
            count--;
            if(count==0) count=no;
            break;
        }
        highlight(no,count);
        ch=getch();
        if(ch=='\r')
        {
            if(no==7)
            {
                if (count==1) bill() ;
                else if(count==2) add();
                else if(count==3) edit();
                else if (count==4) d_all();
                else if (count==5) d_search();
                else if (count==6) del();
                else   exit(0);
            }
            if(no==4)
            {
                if (count==1) d_code();
                else if(count==2)d_price();
                else if (count==3) d_quan();
                else d_mainmenu();
            }
        }
    }
}
void highlight(int no,int count)
{
    if (no==4)
    {

        gotoxy(30,23);
        printf("   By Code          ");
        gotoxy(30,24);
        printf("   By Price         ");
        gotoxy(30,25);
        printf("   By Quantity      ");
        gotoxy(30,26);
        printf("   Back to main menu");
        switch (count)
        {
        case 1:
            gotoxy(30,23);
            printf(" - By Code          ");
            break;
        case 2:
            gotoxy(30,24);
            printf(" - By Price         ");
            break;
        case 3:
            gotoxy(30,25);
            printf(" - By Quantity      ");
            break;
        case 4:
            gotoxy(30,26);
            printf(" - Back to main menu");
            break;
        }
    }
    if(no==7)
    {

        gotoxy (30,23);
        printf("   Calculate Bill ");
        gotoxy (30,24);
        printf("   Add Product      ");
        gotoxy (30,25);
        printf("   Edit Product     ");
        gotoxy (30,26);
        printf("   Display All    ");
        gotoxy (30,27);
        printf("   Search         ");
        gotoxy (30,28);
        printf("   Delete Product   ");
        gotoxy (30,29);
        printf("   Exit           ");

        switch(count)
        {
        case 1:
            gotoxy (30,23);
            printf(" - Calculate Bill ");
            break;
        case 2:
            gotoxy (30,24);
            printf(" - Add Product      ");
            break;
        case 3:
            gotoxy (30,25);
            printf(" - Edit Product     ");
            break;
        case 4:
            gotoxy (30,26);
            printf(" - Display All    ");
            break;
        case 5:
            gotoxy (30,27);
            printf(" - Search         ");
            break;
        case 6:
            gotoxy (30,28);
            printf(" - Delete Product   ");
            break;
        case 7:
            gotoxy (30,29);
            printf(" - Exit           ");
            break;
        }
    }
}
void bill()
{
    char x[4]= {0};
    int j=29,q=0,size=0,i=1;
    float total=0,gtotal=0;
    FILE *file;
    file=fopen("project.txt","r+b");
    rewind(file);
    system("cls");
    dbill();
    gotoxy(26,15);
    printf("Enter  \"end\" to finish input");
    while(1)
    {
        gotoxy(25,18);
        printf("                    ");
        gotoxy(25,19);
        printf("                    ");
        gotoxy(25,18);
        printf("Enter Item Code:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        gotoxy(25,19);
        printf("Enter Quantity:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
                total=item.price*q;
                gotoxy(11,j);
                printf("%4d",i);
                printf("%12s",item.name);
                printf("%10d",q);
                printf("%14.2f",item.price);
                printf("%14.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoxy(30,j+5);
        printf("TOTAL AMOUNT =  %.2f",gtotal);
    }
    fclose(file);
    getch();
    d_mainmenu();
}
/*function to display bill window*/
void dbill()
{
    int i;
    gotoxy(20,10);

    for (i=1; i<=10; i++)
        printf("-");
    printf(" WERMUT ");
    for (i=1; i<=10; i++)
        printf("-");
    printf("\n\n");
    gotoxy(30,11);
    printf("DEPARTMENTAL STORE");
    gotoxy(32,25);
    printf("CUSTOMER'S BILL") ;
    gotoxy(13,27);
    printf("SN.   Item Name     Quantity     Price       Total");

}
/*function to add records*/
void add ()
{
    FILE *file;
    char y[ACS];
    system("cls");

    gotoxy(25,25);
    printf("Enter New Record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("project.txt","ab");
        c_code(y);
        strcpy(item.code,y);
        gotoxy(22,28);
        printf("Enter price of the item:");
        scanf("%f",&item.price);
        gotoxy(22,30);
        printf("Enter Quantity Of The Item:");
        scanf("%d",&item.quantity);
        gotoxy(22,32);
        printf("Enter Name Of The Item:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        gotoxy(22,34);
        printf("Enter New Record(Y/N)?");

    }
    d_mainmenu();
}
/*function to check availability of code*/
void c_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("project.txt","rb");
    while(1)
    {
        system("cls");
        gotoxy(32,18);
        printf(" ADD ARTICLES ")  ;
        flag=1;
        rewind(file);
        gotoxy(22,25);
        printf("Enter New Code Of The Article:");
        scanf(" %[^\n]",y);
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;
                gotoxy(26,30);
                printf("Code Already Exists");
                gotoxy(29,32);
                printf("Enter Again");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
}
/*function for editing*/
void edit()
{
    int flag=0,choice;
    char x[ACS],y[ACS];
    FILE *file;
    int size;
    system("cls");

    gotoxy(35,18);
    printf("EDIT RECORDS");
    ;
    gotoxy(25,23);
    printf("Enter Item Code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file=fopen("project.txt","r+b");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {

                gotoxy(25,27);
                printf("name       = %s",item.name);
                gotoxy(25,28);
                printf("code       = %s",item.code);
                gotoxy(25,29);
                printf("price      = %g",item.price);
                gotoxy(25,30);
                printf("quantity   = %d",item.quantity);
                gotoxy(25,32);;
                printf("Do You Want To Edit This Record?(y/n):");
                fflush(file);
                if(toupper(getche())=='Y')
                {

                    gotoxy(25,34);
                    printf("1- Edit Name ");
                    gotoxy(25,35);
                    printf("2- Edit Code ");
                    gotoxy(25,36);
                    printf("3- Edit Price ");
                    gotoxy(25,37);
                    printf("4- Edit Quantity ");
                    gotoxy(25,39);  ;
                    printf(" Enter Your Choice(1, 2, 3, 4) ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        system("cls");
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" Enter New Name: ");
                        scanf("%s",item.name);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" Enter New Price: ");
                        scanf("%f",&item.price);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" Enter New Quantity: ");
                        scanf("%d",&item.quantity);
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }
                    gotoxy(27,30);
                    printf("--- Item Edited---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoxy(32,30);
        printf("Item Does Not Exist.");
        gotoxy(36,32);
        printf("TRY AGAIN");
    }
    getch();
    fclose(file);
    d_mainmenu();
}
/*function to display all records*/
void d_all()
{
    int i,j=1;
    FILE *file;
    dis_con();
    file=fopen("project.txt","rb");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        display(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoxy(27,47);
            printf("Press Any Key To See More...........");
            getch();
            system("cls");
            dis_con();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(24,30);
        printf("-- No Articles Found --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}
/*function to search by quantity*/
void d_quan()
{
    int i,j=1;
    int a,b;
    FILE *file;
    dis_con();
    file=fopen("project.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("Enter Lower Range: ");
    scanf("%d",&a);
    gotoxy(16,21);
    printf("Enter Upper Range:");
    scanf("%d",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.quantity>=a)&&(item.quantity<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("Press Any Key To See More......");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" No Items Found.");
    }
    getch();
    d_search();
    fclose(file);
}
/*function to search by price*/
void d_price()
{
    int i,j=1;
    float a,b;
    FILE *file;
    dis_con();
    file=fopen("project.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("Enter Lower Range: ");
    scanf("%f",&a);
    gotoxy(16,21);
    printf("Enter Upper Range: ");
    scanf("%f",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.price>=a)&&(item.price<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("Press Any Key To See More...........");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" No Item Found ");
    }
    getch();
    fclose(file);
    d_search();
}

/*function to search by code*/
void d_code()
{
    int i,j=1;
    char x[4]= {0};
    FILE *file;
    dis_con();
    file=fopen("project.txt","rb");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("Enter Item Code: ");
    scanf("%s",x);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((strcmp(item.code,x)==0))
        {
            display(&item,i,j);
            i++;
            j++;
            break;
        }
    }
    if (i==26)
    {
        gotoxy(28,30);
        printf("No Item Found");
    }
    getch();
    fclose(file);
    d_search();
}
/*function to display window for item display*/
void dis_con()
{
    int i;
    system("cls");
    gotoxy(20,10);
    ;
    for (i=1; i<=10; i++)
        printf("-");
    printf(" WERMUT ");
    for (i=1; i<=10; i++)
        printf("-");
    printf("\n\n");
    gotoxy(30,11);
    printf("DEPARTMENTAL STORE");

    gotoxy(32,17);
    printf("RECORDS") ;

    gotoxy(18,23);
    printf ("No   Item Name   Item Code      Price       Quantity");
}
/*function to display in screen*/
void display(rec *item,int i,int j)
{
    gotoxy(16,i);
    printf("%4d",j);
    printf("%9s",item->name);
    printf("%12s",item->code);
    printf("%14.2f",item->price);
    printf("%11d",item->quantity);
}
/*function to delete records*/
void del()
{
    int flag;
    char x[ANS];
    FILE *file,*file1;
    system("cls");

    gotoxy(29,18);
    printf("DELETE ARTICLES");
    gotoxy(27,27);
    printf("Enter Item Code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("project1.txt","ab");/*temporary file for delete*/
        file=fopen("project.txt","rb");/*file to be deleted*/
        rewind(file);
        remove("project.txt");
        rename("project1.txt","project.txt");
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        gotoxy(27,29);
        printf("---Item Deleted---");

    }
    if (flag==1)
    {
        gotoxy(25,29);
        printf("---Item Does Not Exist---");
        gotoxy(30,31);
        printf("TRY AGAIN");
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}
/*function to check validity of code while editing and deleting*/
int check(char x[ANS])
{
    FILE *file;
    int flag=1;
    file=fopen("project.txt","rb");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}
