#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

typedef struct
{
    int index ;
    int bookid ;
    int year;
    int month ;
    int day ;

} binfo ;

typedef struct
{
    int bookid;
    char bookname[50];
    int copy;
} books ;

typedef struct
{
    char name[50];
    char nic[20];
    int phone;
    int index;
} person ;

typedef struct
{
    int index ;
    int arr[12];
} payment ;

binfo *binfoptr ;
binfo *dublicatebinfo ;
books *book ;
person *persondata ;
payment *paymentdata;

void nibm();
void authenticate();
void mainMenu();
int personCount();
void registration();
void update_binfo();
int getcountbookinfo();
void readbookinfo();
int getcountbarrowbook();
void abstractFileBinfo();
void BarrowBook();
int DateDifference();
void addFileBinfo();
void handOver();
void PrintBookInfo();
void lordRegDetail();
void getoverDueDetails();

void paymentMenu();
void formatAll();
void lordPaymentData();
void getPayment();
void updatePayamentFile();
void getDetails();


int main()
{
    //mainMenu();

    authenticate();
    return 0;
}

void nibm()
{
    system("CLS");
    printf("                                            ####   ##  ####  ######   ##   ##\n");
    printf("                                            ## ##  ##   ##   ##   ##  ### ###\n");
    printf("                                            ##  ## ##   ##   ######   ## # ##\n");
    printf("                                            ##    ###   ##   ##   ##  ##   ##\n");
    printf("                                            ##     ##  ####  ######   ##   ##\n\n");
    printf("                                                       ~ LIBRARY ~               \n");
    printf("                                                   POWERING GREAT MINDS         \n");
    printf("========================================================================================================================\n");
}

void authenticate()
{
    system("CLS");
    nibm();

    int i = 0;
    char admin[] = "admin123";
    char password[10];

    printf("                                               ENTER ADMIN PASSWORD: ");

    while (i < 10) {
        char pass = _getch(); // here _getch() from conio.h is used to stop from echoing chars in console
                              // and also to use backspace as an eraser
        if (pass == '\r')
        {
            break;    // If Enter is pressed, stop reading
        }
        else if (pass == '\b' && i > 0)
        {
            // Handle backspace by erasing the character
            printf("\b \b");
            i--;
            continue;
        }
        password[i++] = pass;
        printf("*"); // Print '*' for masking
    }
    password[i] = '\0'; //null terminate the password

    if (strcmp(admin, password) == 0)
    {
        printf("\n                                                     LOGGING IN...");
        sleep(3);
        mainMenu();

    }
    else
    {
        system("CLS");
        authenticate();
    }

}

void mainMenu()
{
    system("CLS");
    nibm();
    int choice ;

    printf("    1 - Registration\n");
    printf("    2 - Barrow book\n");
    printf("    3 - Return a book\n");
    printf("    4 - Book Info\n");
    printf("    5 - Delay handover\n");
    printf("    6 - Payment Menu\n");
    printf("    7 - Logout\n\n");

    printf("Enter your choice : ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 1 :
        registration();
        break ;
    case 2 :
        BarrowBook();
        break;
    case 3 :
        handOver();
        break;
    case 4 :
        PrintBookInfo();
        break;
    case 5 :
        getoverDueDetails();
        break;
    case 6 :
        paymentMenu();
        break;
    case 7 :
        system("CLS");
        printf("                                                       ~ LOGING OUT ~\n");
        sleep(2);
        system("CLS");
        printf("                                                       SEE YOU LATER\n");
        sleep(2);
        authenticate();
    default :
        printf("Ooops input error |-_-|..|-_-|..|-_-|..\n");
        sleep(3);

        mainMenu();
    }
}

int personCount()
{
    char ch[100];
    int num;
    int count=0 ;
    FILE* ptr = fopen("registation.txt","r");
    while(fscanf(ptr,"%s",&ch)==1)
    {
        fscanf(ptr , "%s",&ch);
        fscanf(ptr ,"%d",&num);
        fscanf(ptr , "%d", &num);
        count++;

    }
    fclose(ptr);
    return count;
}

void registration()
{
    system("CLS");
    nibm();
    FILE *ptr = fopen("registation.txt","a");
    char name[50] , nic[20] , gnic[20], add[100] ;
    int pno , age ;
    int index = 100 ;

    printf("\tName : ");
    scanf("%s",name);
    if (strcmp(name,"99")== 0)
    {
        mainMenu();
    }

    printf("\tPhone Number : ");
    scanf("%d",&pno);

    if (pno == 99)
    {
        mainMenu();
    }

    printf("\tAge : ");
    scanf("%d",&age);

    if (age == 99)
    {
        mainMenu();
    }

    int count = personCount();
    int pindex = index + count ;

    if (age >= 18)
    {
        printf("\tNIC : ");
        scanf("%s",nic);

        if (strcmp(nic,"99")==0)
        {
            mainMenu();
        }

    }
    else
    {
        printf("\tGUARDIAN NIC : ");
        scanf("%s",gnic);
        if (strcmp(nic,"99")==0)
        {
            mainMenu();
        }

    }

    system("CLS");
    nibm();
    printf("REGISTRATION DETAILS >>>\n\n");
    printf("\tName         : %s\n",name);
    printf("\tPhone Number : %d\n",pno);
    if (age>18)
    {
        printf("\tNIC          : %s\n\n",nic);
    }
    else
    {
        printf("\tNIC          : %s\n\n",gnic);
    }
    int confirm ;
    printf("CONFIRM (1) : ");
    scanf("%d",&confirm);
    if (confirm == 1)
    {
        if (age > 18)
        {
            fprintf(ptr,"%s\n%s\n%d\n%d\n",name,nic,pno,pindex);
        }
        else
        {
            fprintf(ptr,"%s\n%s\n%d\n%d\n",name,gnic,pno,pindex);
        }

    }
    fclose(ptr);

    ptr = fopen("monthlyPayment.txt","a") ;
    fprintf(ptr,"\n%d 0 0 0 0 0 0 0 0 0 0 0 0",pindex) ;
    fclose(ptr);

    system("CLS");
    printf("\t\nREGISTRATION SUCESSFUL.");
    sleep(2);
    registration();


}

int getcountbarrowbook()
{
    int count=0 ;
    int num;

    FILE* ptr = fopen("BarrowBooks.txt","r");

    while(fscanf(ptr,"%d",&num)==1)
    {
        fscanf(ptr,"%d",&num);
        fscanf(ptr,"%d",&num);
        fscanf(ptr,"%d",&num);
        fscanf(ptr,"%d",&num);
        count++;
    }
    //printf("count = %d\n",count);
    return count;
}

void update_binfo()
{
    int bcount = getcountbarrowbook();
    binfoptr = (binfo*)malloc(bcount * sizeof(binfo));

    int i = 0 ;

    FILE *ptr = fopen("BarrowBooks.txt","r");
    while (fscanf(ptr,"%d",&binfoptr[i].index)==1)
    {
        fscanf(ptr,"%d",&binfoptr[i].bookid);
        fscanf(ptr,"%d",&binfoptr[i].year);
        fscanf(ptr,"%d",&binfoptr[i].month);
        fscanf(ptr,"%d",&binfoptr[i].day);
        i++;
    }

    fclose(ptr);
}

void BarrowBook()
{
    system("CLS");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int m2 = tm.tm_mon ;

    FILE* ptr = fopen("BarrowBooks.txt","a");
    nibm();
    update_binfo();
    lordPaymentData();
    int pcount = personCount();
    int bcount = getcountbarrowbook();
    int count=0;
    int bid ;
    int index ;
    int paidStatus = 0 ;
    printf("\t\tINDEX : ");
    scanf("%d",&index);
    if (index == 99)
    {
        mainMenu();
    }

    for (int i = 0 ; i < pcount ; i++ )
    {
        if (paymentdata[i].index == index)
        {
            if (paymentdata[i].arr[m2] == 1)
            {
                paidStatus = 1 ;
            }
        }
    }

    if (paidStatus == 1)
    {
        for (int i = 0 ; i < bcount ; i++ )
        {
            if (binfoptr[i].index==index)
            {
                count++;
            }
        }
        if (count==3)
        {
            printf("\n\n\t\tNOT ELIGIBLE TO BARROW ENY MORE BOOKS.\n");
            sleep(4);
            mainMenu();
        }
        else
        {
            printf("\n\t\tELIGIBLE TO BARROW BOOK.\n\n");
            printf("\t\tBOOKID : ");
            scanf("%d",&bid);
            if (bid == 99)
            {
                mainMenu();
            }

            int bcount = getcountbookinfo ;

            readbookinfo();

            for (int i = 0 ; i< bcount ; i++)
            {
                if (bid == book[i].bookid)
                {
                    if (book[i].copy >=3)
                    {
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);

                        printf("\nREGISTRATION ID : %d\nBOOK ID : %d\n\n",index,bid);
                        fprintf(ptr,"%d\n%d\n",index,bid);
                        fprintf(ptr,"%02d %02d %d\n",tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday);
                        fclose(ptr);
                        abstractFileBinfo(bid);
                        system("CLS");
                        printf("\n\t\tRESERVATION SUCCESSFUL.\n");
                        sleep(2);
                        BarrowBook();

                    }
                    else
                    {
                        system("CLS");
                        printf("\n\t\tTHE BOOK IS NOT AVAILABLE!!!!\n");
                        sleep(2);
                        mainMenu();
                    }
                }
            }

        }
    }
    else
    {
        system("CLS");
        printf("\n\tMONTHLY PAYMENT FAIL OR INVALIED INDEX");
        sleep(4);
        BarrowBook();
    }

}

int getcountbookinfo()
{
    FILE* ptr = fopen("bookinfo.txt","r");
    char ch[50];
    int num;

    int count = 0 ;
    while(fscanf(ptr,"%d",&num)==1)
    {
        fscanf(ptr,"%s",&ch);
        fscanf(ptr,"%d",&num);
        count++ ;
    }

    return count;

}

void readbookinfo()
{
    int bcount = getcountbookinfo() ;
    book = (books*)malloc(bcount * sizeof(books));
    FILE* ptr = fopen("bookinfo.txt","r");
    int i = 0 ;
    while(fscanf(ptr,"%d",&book[i].bookid)==1)
    {
        fscanf(ptr,"%s",&book[i].bookname);
        fscanf(ptr,"%d",&book[i].copy);
        i++ ;
    }

    fclose(ptr);
    /*
    for(int i = 0 ; i < bcount ; i++)
    {
        printf("%d\n%d\n",book[i].bookid,book[i].copy);
    }
    */
}

void abstractFileBinfo(int bookid)
{
    FILE* ptr = fopen("bookinfo.txt","r+");

    readbookinfo();
    int bcount = getcountbookinfo() ;
    for (int i = 0 ; i<bcount ; i++)
    {
        if (book[i].bookid == bookid)
        {
            int copy = book[i].copy ;
            copy = copy - 1 ;
            book[i].copy = copy ;
        }
    }

    for(int i = 0 ; i < bcount ; i++)
    {
        int bid , bcopy ;
        char bname[50];

        bid = book[i].bookid ;
        bcopy = book[i].copy ;
        strcpy(bname,book[i].bookname);
        fprintf(ptr,"%d\n%s\n%d\n",bid,bname,bcopy);
    }

    fclose(ptr);

}

void addFileBinfo(int bookid)
{
    FILE* ptr = fopen("bookinfo.txt","r+");

    readbookinfo();
    int bcount = getcountbookinfo() ;
    for (int i = 0 ; i<bcount ; i++)
    {
        if (book[i].bookid == bookid)
        {
            int copy = book[i].copy ;
            copy = copy + 1 ;
            book[i].copy = copy ;
        }
    }

    for(int i = 0 ; i < bcount ; i++)
    {
        int bid , bcopy ;
        char bname[50];

        bid = book[i].bookid ;
        bcopy = book[i].copy ;
        strcpy(bname,book[i].bookname);
        fprintf(ptr,"%d\n%s\n%d\n",bid,bname,bcopy);
    }

    fclose(ptr);
}

void handOver()
{
    nibm();
    update_binfo();
    int bcount = getcountbarrowbook();
    int dbcount = bcount-1 ;
    dublicatebinfo = (binfo*)malloc(dbcount * sizeof(binfo));
    int index ,bookid ,indexStatus = 0;

    printf("\tINDEX  : ");
    scanf("%d",&index);
    if (index == 99)
    {
        mainMenu();
    }
    printf("\tBOOKID : ");
    scanf("%d",&bookid);
    if (bookid == 99)
    {
        mainMenu();
    }

    for (int i = 0 ; i<bcount ; i++ )
    {
        if (binfoptr[i].index == index && binfoptr[i].bookid==bookid)
        {
            indexStatus = 1 ;
            int year ,month,day ;
            year = binfoptr[i].year ;
            month = binfoptr[i].month ;
            day = binfoptr[i].day ;

            int ddif = DateDifference(year,month,day);
            int duedate = ddif-14 ;
            if (duedate >0)
            {
                int bill = duedate*50;
                int choice ;
                printf("\tLATE %d DAYS!!\n\tFINE PAYMENT = %d.00 (PAID-1) : ",duedate,bill);
                scanf("%d",&choice);
                if (choice != 1)
                {
                    handOver();
                }

            }
            binfoptr[i].index = 0 ;
            binfoptr[i].bookid = 0 ;
            binfoptr[i].year = 0 ;
            binfoptr[i].month = 0 ;
            binfoptr[i].day = 0 ;

            break ;


        }
    }
    if (indexStatus==1)
    {
        int status = 0 ;
        for (int i = 0 ; i < bcount ; i++)
        {
            if (binfoptr[i].index == 0)
            {
                status = 1;
                continue ;
            }
            else
            {
                if (status == 1)
                {
                    dublicatebinfo[i-1].index = binfoptr[i].index ;
                    dublicatebinfo[i-1].bookid = binfoptr[i].bookid ;
                    dublicatebinfo[i-1].year = binfoptr[i].year ;
                    dublicatebinfo[i-1].month = binfoptr[i].month ;
                    dublicatebinfo[i-1].day = binfoptr[i].day ;
                }
                else
                {
                    dublicatebinfo[i].index = binfoptr[i].index ;
                    dublicatebinfo[i].bookid = binfoptr[i].bookid ;
                    dublicatebinfo[i].year = binfoptr[i].year ;
                    dublicatebinfo[i].month = binfoptr[i].month ;
                    dublicatebinfo[i].day = binfoptr[i].day ;
                }

            }
        }
        FILE* ptr = fopen("BarrowBooks.txt","w");

        fclose(ptr);

        ptr = fopen("BarrowBooks.txt","a");
        for (int i = 0 ; i < bcount-1 ; i++)
        {
            int index = dublicatebinfo[i].index ;
            int bookid = dublicatebinfo[i].bookid ;
            int year = dublicatebinfo[i].year ;
            int month = dublicatebinfo[i].month ;
            int day = dublicatebinfo[i].day ;

            fprintf(ptr,"%d\n%d\n%d %d %d\n",index,bookid,year,month,day);
        }
        fclose(ptr);
        addFileBinfo(bookid);
        system("CLS");
        printf("\t\nHANDOVERING SUCCESSFUL\n");
        sleep(2);

        handOver();
    }
    else
    {
        system("CLS");
        printf("\tINVALIED RECORD\n");
        sleep(2);
        handOver();
    }

}

int DateDifference(int y1,int m1,int d1)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int y2 = tm.tm_year + 1900 ;
    int m2 = tm.tm_mon + 1 ;
    int d2 = tm.tm_mday ;

    int leapyearStatus = 0 ;
    int monthdaycount = 0;
    int leapCount = 0 ;
    int loopStatus = 1 ;
    int difd;
    int d;

    if(m2 == m1 && y2 == y1)
    {
        loopStatus = 0 ;
        difd = d2 - d1 ;
    }
    else if(m1==2)
    {
        if(y1%100!=0 && y1%4==0  ||  y1%400==0)
            d=29-d1;
        else
            d=28-d1;
    }
    else if(m1==5 || m1==7 || m1==10 || m1==12)
        d=30-d1;
    else if (m1 != 2)
        d=31-d1;

    if (loopStatus == 1)
    {
        for (int i = m1+1 ; !(y2 == y1 && m2 == i); i++)
        {
            if(y1%100!=0 && y1%4==0  ||  y1%400==0)
            {
                if(i == 2)
                {
                   monthdaycount = monthdaycount +29;

                }
                leapCount++;
            }
            else
            {
                if (i==2)
                {
                    monthdaycount = monthdaycount +28;
                }
            }

            if (i==5 || i==7 || i==10 || i==12)
            {
                monthdaycount = monthdaycount +30;
            }
            else if (i != 2)
            {
                monthdaycount = monthdaycount +31;
            }
            if (i == 12)
            {
                y1++;
                i = 0 ;
            }
        }
        difd=d+d2;
    }

    int dify = y2 - y1 ;

	int yDya = ((dify-leapCount)*365) + (leapCount*366);

	int ddays = yDya+monthdaycount+difd;
	return ddays;


}

void PrintBookInfo()
{
    system("CLS");
    int bcount = getcountbookinfo() ;
    FILE* ptr = fopen("bookinfo.txt","r");
    int i = 0 ;
    readbookinfo();

    printf("                                       |--------------------|----------------------|\n");
    printf("                                       |      BOOK ID       |  AVAILABLE QUANTITY  |\n");
    printf("                                       |--------------------|----------------------|\n");
    printf("                                       |-------------------------------------------|\n");
    for(int i = 0 ; i < bcount ; i++)
    {
        printf("                                       |       %d         |         %d            |\n",book[i].bookid,book[i].copy);
        printf("                                       |-------------------------------------------|\n");
    }
    char choice = _getch();
    if (choice == '\b' || choice == '\r')
    {
        mainMenu();
    }
}

void getoverDueDetails()
{
    system("CLS");
    FILE* ptr = fopen("overDueDetails.txt","w");
    fclose(ptr);
    ptr = fopen("overDueDetails.txt","a");

    fprintf(ptr,"                                            ####   ##  ####  ######   ##   ##\n");
    fprintf(ptr,"                                            ## ##  ##   ##   ##   ##  ### ###\n");
    fprintf(ptr,"                                            ##  ## ##   ##   ######   ## # ##\n");
    fprintf(ptr,"                                            ##    ###   ##   ##   ##  ##   ##\n");
    fprintf(ptr,"                                            ##     ##  ####  ######   ##   ##\n\n");
    fprintf(ptr,"                                                       ~ LIBRARY ~               \n");
    fprintf(ptr,"                                                   POWERING GREAT MINDS         \n");
    fprintf(ptr,"========================================================================================================================\n");

    update_binfo();
    lordRegDetail();
    int pcount = personCount();
    int bcount = getcountbarrowbook();

    for (int i = 0 ; i < pcount ; i++ )
    {
        int year,month,day ;

        year = binfoptr[i].year ;
        month = binfoptr[i].month ;
        day = binfoptr[i].day ;

        int dif = DateDifference(year,month,day);
        int late = dif - 14 ;
        if (late > 0)
        {

            for (int j = 0 ; j < bcount ; j++ )
            {
                if ( binfoptr[i].index == persondata[j].index )
                {
                    char name[50];
                    char nic[20];
                    strcpy(name,persondata[j].name);
                    strcpy(nic,persondata[j].nic);
                    int phone = persondata[j].phone;
                    int index = persondata[j].index;
                    int bookid = binfoptr[i].bookid ;
                    printf("--------------------------------\n");

                    printf("| Name   : %s\n",name);
                    printf("| Index  : %d\n",index);
                    printf("| NIC    : %s\n",nic);
                    printf("| Phone  : %d\n",phone);
                    printf("| BookID : %d\n",bookid);

                    printf("--------------------------------\n");

                    fprintf(ptr,"--------------------------------\n");

                    fprintf(ptr,"| Name   : %s\n",name);
                    fprintf(ptr,"| Index  : %d\n",index);
                    fprintf(ptr,"| NIC    : %s\n",nic);
                    fprintf(ptr,"| Phone  : %d\n",phone);
                    fprintf(ptr,"| BookID : %d\n",bookid);

                    fprintf(ptr,"--------------------------------\n");

                }
            }
        }

    }
    fclose(ptr);
    char choice = _getch();
    if (choice == '\b' || choice == '\r')
    {
        mainMenu();
    }

}

void lordRegDetail()
{
    FILE* ptr = fopen("registation.txt","r");
    int pcount = personCount();
    persondata = (person*)malloc(pcount * sizeof(person));

    int i = 0 ;
    while (fscanf(ptr,"%s",&persondata[i].name)==1)
    {
        fscanf(ptr,"%s",&persondata[i].nic);
        fscanf(ptr,"%d",&persondata[i].phone);
        fscanf(ptr,"%d",&persondata[i].index);
        i++ ;
    }
    fclose(ptr);
}

void paymentMenu()
{
    nibm();
    printf("\n\t1 - GET PAYMENT\n");
    printf("\t2 - GET DETAILS\n");
    printf("\t3 - RESET ALL\n");

    printf("SELECT OPTION : ");

    int choice ;
    scanf("%d",&choice);

    switch (choice)
    {
    case 1 :
        getPayment();
        break;
    case 2 :
        getDetails();
        break ;
    case 3 :
        formatAll();
        break;
    case 99 :
        mainMenu();
        break;
    default :
        printf("\tINPUT ERROR !\n");
        sleep(2);
        paymentMenu();
        break ;
    }

}

void getPayment()
{
    nibm();
    lordPaymentData();
    int pcount = personCount();
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int m2 = tm.tm_mon ;

    int index ;
    printf("\n\tINDEX : ");
    scanf("%d",&index);
    if (index == 99)
    {
        paymentMenu();
    }

    for (int i = 0 ; i<pcount ; i++)
    {
        if (paymentdata[i].index == index)
        {

           if (paymentdata[i].arr[m2]==1)
           {
              printf("\n\tALRADY PAID");
           }
           else
           {
              paymentdata[i].arr[m2] = 1 ;
              updatePayamentFile();
              printf("\n\tPAYMENT SUCCESSFUL\n");
              sleep(2);
              break;
           }

        }
    }

    paymentMenu();



}

void formatAll()
{
    system("CLS");
    int confirm;
    printf("\n\tSURE YOU WANT TO RESET FILE (yes - 1) : ");
    scanf("%d",&confirm);
    if(confirm != 1)
    {
        paymentMenu();
    }
    FILE* ptr = fopen("monthlyPayment.txt","w") ;
    fclose(ptr);
    ptr = fopen("monthlyPayment.txt","a") ;

    lordRegDetail();
    int pcount = personCount();

    for(int i = 0 ; i < pcount ; i++)
    {
        int index = persondata[i].index ;
        fprintf(ptr,"%d 0 0 0 0 0 0 0 0 0 0 0 0\n",index) ;
    }
    fclose(ptr);

    system("CLS");
    printf("\n\tFORMATING SUCCESSFUL");
    sleep(2);
    paymentMenu();

}

void lordPaymentData()
{
    int pcount = personCount();
    paymentdata = (payment*)malloc(pcount * sizeof(payment));
    FILE* ptr = fopen("monthlyPayment.txt","r") ;
    int j = 0 ;
    while (fscanf(ptr,"%d",&paymentdata[j].index)==1)
    {
        for (int i = 0 ; i < 12 ; i++)
        {
           fscanf(ptr,"%d",&paymentdata[j].arr[i]);

        }
        j++;
    }
}

void updatePayamentFile()
{
    FILE* ptr = fopen("monthlyPayment.txt","w") ;
    fclose(ptr);

    ptr = fopen("monthlyPayment.txt","a") ;

    int pcount = personCount();

    for (int i = 0 ; i < pcount ; i++ )
    {
        fprintf(ptr,"\n%d ",paymentdata[i].index) ;
        for (int j=0 ; j<12 ; j++)
        {
            fprintf(ptr,"%d ",paymentdata[i].arr[j]);
        }
    }
    fclose(ptr);

}

void getDetails()
{
    nibm();
    int index;
    printf("\n\tINDEX : ");
    scanf("%d",&index);
    if (index == 99)
    {
        paymentMenu();
    }
    lordPaymentData();
    int pcount = personCount();
    for (int i = 0 ; i < pcount ; i++ )
    {
        if (paymentdata[i].index == index)
        {
            for (int j = 0 ; j <12 ; j++)
            {
                if (paymentdata[i].arr[j] == 1)
                {
                    printf("%2d MONTH        PAID\n",j+1);
                }
                else
                {
                    printf("%2d MONTH        UNPAID\n",j+1);
                }
            }

        }
    }
    char choice = _getch();
    if (choice == '\b' || choice == '\r')
    {
        paymentMenu();
    }
}














