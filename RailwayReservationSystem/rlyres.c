#include<stdio.h>
#include<stdlib.h>
#include"conio2.h"
#include"rlyres.h"
#include<string.h>
#include<ctype.h>
int enterchoice()
{
    int choice,i;
    gotoxy(28,1);
    textcolor(YELLOW);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=0;i<=125;i++)
    {
        printf("-");
    }
    printf("\n");
    printf("select an option\n");
    printf("1- View Trains\n2- Book Ticket\n3- View Ticket\n4- Search Ticket no\n5- View All Bookings\n6- View Train Bookings\n7- Cancel Ticket\n8- Cancel Train\n9- Quit\n\n");
    printf("enter choice: ");
    scanf("%d",&choice);
    return choice;

}


void add_trains()
{

    FILE *fp;
    fp=fopen("d:\\c programs\\MyProject\\alltrains.dat","rb");
    if(fp==NULL)
    {
        Train alltrains[4]=
        {

              {"123","BPL","GWA",2100,1500},
              {"546","BPl","DEl",3500,2240},
              {"345","HBJ","AGR",1560,1135},
              {"896","HBJ","MUM",4500,3360}
        };
        fp=fopen("d:\\c programs\\MyProject\\alltrains.dat","wb");
        fwrite(alltrains,4*sizeof(Train),1,fp);
        printf("file saved successfully\n");
        fclose(fp);

    }
   /* else
    {


        printf("file already present\n");
        fclose(fp);
    }*/
}


void view_trains()
{
    int i;
    clrscr();
    printf("TRAIN NO\tFROM\tTO\tFIRST AC FAIR\tSECOND AC FAIR\n");
    for(i=0;i<=125;i++)
    {
        printf("-");
    }
    FILE *fp;
    fp=fopen("d:\\c programs\\MyProject\\alltrains.dat","rb");
    if(fp==NULL)
    {
        printf("sorry!file can't be open/t");
        exit(0);

    }
    Train t;
    while(fread(&t,sizeof(Train),1,fp)==1)
    {
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",t.train_no,t.from,t.to,t.fac_fare,t.sac_fare);
    }
    fclose(fp);

}


int check_train_no(char *trainno)
{
 FILE* fp;
 fp=fopen("d:\\c programs\\MyProject\\alltrains.dat","rb");
 Train t;
 while(fread(&t,sizeof(Train),1,fp)==1)
 {
     if(strcmp(trainno,t.train_no)==0)
     {
         fclose(fp);
         return 1;
     }

 }
 fclose(fp);
 return 0;

}


void reservationCancellation()
{
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");
    gotoxy(1,25);
    textcolor(LIGHTRED);
    printf("Reservation cancelled!");
    getch();
    textcolor(YELLOW);
}


int check_mob_no(char* p_mob)
{
    if(strlen(p_mob)!=10)
        return 0;
    while(*p_mob!='\0')
    {
        if(isdigit(*p_mob==0))
            return 0;
        p_mob++;

    }
    return 1;
}


Passenger* get_passenger_details()
{
    gotoxy(60,1);
    textcolor(LIGHTGREEN);
    printf("Press 0 to exit");
    gotoxy(1,1);
    textcolor(YELLOW);

    //taking name of passenger.....

    static Passenger psn;
    char* pos;

    printf("Enter Passenger name:");
    fflush(stdin);
    fgets(psn.p_name,20,stdin);
    pos=strchr(psn.p_name,'\n');
    *pos='\0';

    if(strcmp(psn.p_name,"0")==0)
    {
        reservationCancellation();
        return NULL;
    }

    //taking gender of passenger......

    printf("Enter gender(M/F):");

    while(1)
    {
        gotoxy(19,2);
        printf("    \b\b\b\b");
        scanf("%c",&psn.gender);

       if(psn.gender=='0')
       {
        reservationCancellation();
        return NULL;
        }
        else if(psn.gender=='M'||psn.gender=='F')
        {
            break;
        }
        else
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Gender should be (M/F)in upper case");
            textcolor(YELLOW);

        }

    }
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");



    //taking train no ........
    gotoxy(1,3);
    printf("enter train no:");

    while(1)
    {
        gotoxy(16,3);
        printf("    \b\b\b\b");
        fflush(stdin);
        fgets(psn.train_no,20,stdin);
        pos=strchr(psn.train_no,'\n');
        *pos='\0';

        if(strcmp(psn.train_no,"0")==0)
        {
            reservationCancellation();
            return NULL;
        }
       else if(check_train_no(psn.train_no)==1)
       {
           break;
       }
       else
       {
           gotoxy(1,25);
           textcolor(LIGHTRED);
           printf("Error! Invalid train no");
           textcolor(YELLOW);
       }

    }
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");


    //taking travelling class.........

    gotoxy(1,4);
    printf("Enter travelling class(First AC-F,Second AC-S):");

    while(1)
    {
        gotoxy(48,4);
        printf("   \b\b\b");
        fflush(stdin);
        scanf("%c",&psn.p_class);

       if(psn.p_class=='0')
       {
        reservationCancellation();
        return NULL;
        }
        else if(psn.p_class=='S'||psn.p_class=='F')
        {
            break;
        }
        else
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Travelling class should be F or S in upper case");
            textcolor(YELLOW);

        }

    }
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");


    //taking address..........

    gotoxy(1,5);

    printf("Enter address:");
    fflush(stdin);
    fgets(psn.address,40,stdin);
    pos=strchr(psn.address,'\n');
    *pos='\0';

    if(strcmp(psn.address,"0")==0)
    {
        reservationCancellation();
        return NULL;
    }

    //taking age......
    gotoxy(1,6);
    printf("Enter age:");
    fflush(stdin);

    while(1)
    {
        gotoxy(11,6);
        printf("   \b\b\b");
        scanf("%d",&psn.age);

       if(psn.age==0)
       {
        reservationCancellation();
        return NULL;
        }
        else if(psn.age>0&&psn.age<120)
        {
            break;
        }
        else
        {
            gotoxy(1,25);
            textcolor(LIGHTRED);
            printf("Error! Age should be positive!");
            textcolor(YELLOW);

        }

    }
    gotoxy(1,25);
    printf("\t\t\t\t\t\t\t");


    //taking mobile no......


    gotoxy(1,7);
    int valid=0;

    printf("Enter mobile no:");
    do
    {
        fflush(stdin);
        fgets(psn.mob_no,11,stdin);
        pos=strchr(psn.mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';

        if(strcmp(psn.mob_no,"0")==0)
        {
             reservationCancellation();
             return NULL;
        }
        valid=check_mob_no(psn.mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Mobile no:");
            getch();
            gotoxy(17,7);
            printf("\t\t\t\t\t\t");
            gotoxy(17,7);
            textcolor(YELLOW);
        }

      }
    while(valid==0);


    gotoxy(1,25);
    printf("\t\t\t\t\t\t");
    getch();


    return &psn;

}


int get_booked_ticket_count(char *train_no,char tc)
{

    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    int count=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0&& pr.p_class==tc)
            ++count;

    }
    fclose(fp);
    return count;
}


int last_ticket_no()
{

    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    int size=ftell(fp);
    if(size==0)
        return 0;
    Passenger pr;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}


int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==2)
    {
        textcolor(LIGHTRED);
        printf("All seats are full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no= last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","ab");
    if(fp==NULL)
    {
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}


int accept_ticket_no()
{
    printf("Enter ticket no:");
    int valid;
    int ticket_no;
    do
    {
        valid=1;
        scanf("%d",&ticket_no);
        if(ticket_no==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...");
            textcolor(YELLOW);
            return 0;

        }
        if(ticket_no<0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Ticket no should be positive");
            valid=0;
            getch();
            gotoxy(17,1);
            printf("\t\t\t\t\t");
            gotoxy(17,1);
            textcolor(YELLOW);
        }

    }
    while(valid==0);
    gotoxy(1,25);
    printf("\t\t\t\t\t");
    gotoxy(1,2);
    return ticket_no;


}


void view_ticket(int ticket_no)
{
    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return;
    }
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(pr.ticketno==ticket_no)
        {
            printf("\nNAME: %s\nGENDER: %c\nTRAIN NO: %s\nCLASS : %c\nADDRESS: %s\nAGE: %d\nMOBILE NO: %s\nTICKET NO: %d\n",pr.p_name,pr.gender,pr.train_no,pr.p_class,pr.address,pr.age,pr.mob_no,pr.ticketno);
            printf("\n\n");
            found=1;
            break;
        }
    }
    if(!found)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of ticket no %d found!",ticket_no);
    }
    fclose(fp);
}


int cancel_ticket(int ticket_no)
{
    FILE *fp1=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb+");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
    FILE *fp2=fopen("d:\\c programs\\MyProject\\temp.dat","wb");
    Passenger pr;
    int found=0;
    while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
        if(pr.ticketno!=ticket_no)
        {
            fwrite(&pr,sizeof(pr),1,fp2);
        }
        else
        {
            found=1;
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\c programs\\MyProject\\temp.dat");
    }
    else
    {
        remove("d:\\c programs\\MyProject\\allbookings.dat");
        rename("d:\\c programs\\MyProject\\temp.dat","d:\\c programs\\MyProject\\allbookings.dat");
    }
    return found;

}


char * accept_train_no()
{
static char train_no[10];
int valid;
printf("Enter train number:");
            do
            {
            fflush(stdin);
            scanf("%s",train_no);
            if(strcmp(train_no,"0")==0)
            {
                textcolor(LIGHTRED);
                gotoxy(1,25);
                printf("\t\t\t\t\t\t\t");
                gotoxy(1,25);
                printf("Cancelling Input. . .!");
                textcolor(YELLOW);
                return NULL;
            }
            valid=check_train_no(train_no);
            if(valid==0)
            {
            textcolor(LIGHTRED);
            gotoxy(1,25);

            printf("Error! Invalid Train No");
            getch();
            gotoxy(20,1);
            printf("\t\t\t\t\t\t");
            gotoxy(20,1);
            textcolor(YELLOW);

            }
            }while(valid==0);
clrscr();
return train_no;
}


int cancel_train(char *ptrain_no)
{
  FILE *fp1=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb+");
  if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return -1;
    }
  FILE *fp2=fopen("d:\\c programs\\MyProject\\temp.dat","wb+");
  Passenger pr;
  int found=0;
  while(fread(&pr,sizeof(pr),1,fp1)==1)
    {
      if(strcmp(pr.train_no,ptrain_no)!=0)
      {
          fwrite(&pr,sizeof(pr),1,fp2);
      }
      else
      {
          found=1;
      }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("d:\\c programs\\MyProject\\temp.dat");
    }
    else
    {
        remove("d:\\c programs\\MyProject\\allbookings.dat");
        rename("d:\\c programs\\MyProject\\temp.dat","d:\\c programs\\MyProject\\allbookings.dat");

    }

return found;
}


char* accept_mob_no()
{
    static char mob_no[11];
    char *pos;
    int valid;
    printf("Enter mobile number:");
    do
    {
        fflush(stdin);
        fgets(mob_no,11,stdin);
        pos=strchr(mob_no,'\n');
        if(pos!=NULL)
            *pos='\0';
        if(strcmp(mob_no,"0")==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input. . .!");
            getch();
            textcolor(YELLOW);
            return NULL;
        }
        valid=check_mob_no(mob_no);
        if(valid==0)
        {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("Error! Invalid Mobile No");
            getch();
            gotoxy(21,1);
            printf("\t\t\t\t\t\t");
            gotoxy(21,1);
            textcolor(YELLOW);
        }
    }while(valid==0);
    clrscr();
    return mob_no;
}


int* get_ticket_no(char *p_mob_no)
{
   int count=0;
   FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
   if(fp==NULL)
    {
        return NULL;
    }
   Passenger pr;
   while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
            ++count;
    }
    if(count==0)
    {
        fclose(fp);
        return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
      if(strcmp(pr.mob_no,p_mob_no)==0)
      {
          *(p+i)=pr.ticketno;
            i++;
      }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}


void view_all_tickets(char *pmob_no,int *pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("---------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
}


void view_booking(char* train_no)
{
    clrscr();
    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet");
        return;
    }
    Passenger pr;
    int i;
    int found=0;
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=0;i<=125;i++)
    {
        printf("-");
    }
    printf("\n");
    i=4;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        if(strcmp(pr.train_no,train_no)==0)
        {
            printf("%d\t\t%c\t%s",pr.ticketno,pr.p_class,pr.p_name);
            gotoxy(41,i);
            printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
            found=1;
            i++;
        }
    }
    if(found==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("No details of train no %s found",pr.train_no);
    }
    fclose(fp);

}


void view_all_bookings()
{
    clrscr();
    FILE *fp=fopen("d:\\c programs\\MyProject\\allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        return;
    }

    Passenger pr;
    int i,found=0;
    printf("TRAIN NO\tTICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(i=0;i<=125;i++)
    {
        printf("-");
    }
    printf("\n");
    i=4;
    while(fread(&pr,sizeof(pr),1,fp)==1)
    {
        printf("%s\t\t%d\t\t%c\t%s",pr.train_no,pr.ticketno,pr.p_class,pr.p_name);
        gotoxy(57,i);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        i++;
        found=1;
    }
    if(found==0)
    {
        clrscr();
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        textcolor(YELLOW);
    }

    fclose(fp);

}










