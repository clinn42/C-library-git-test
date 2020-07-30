#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[0m"
#define CYAN    "\x1b[36m"


//function prototypes
struct user* newuser();
struct book* newbook();
void saveb();
void saveu();
void loadb();
void loadu();
void display(int opt);
void displayb();
void displayu();
void frame0();
void frame1();
void login();
void issb();
void ret();
void adlogin();
void upbook();
void downbook();
void nusr();
void frame33();
void delusr();
void editusr();
void sendcat(char catchk[]);


struct user
{
    char uname[50];
    char upass[15];
    int uid;
    int currb;
    int listofbooks[4];
    struct user *next;
};
struct user *ustart=NULL;
struct user *ulog=NULL;

struct user* newuser()
{
  struct user *u;
  u=(struct user* )malloc(sizeof(struct user))  ;
  return(u);
}


struct book
{
    int bid;
    int nobks;
    char topic[50];
    char aut[50];
    char bname[85];
    struct book *l;
    struct book *r;
};
struct book *bstart=NULL;

struct book* newbook()
{
  struct book *b;
  b=(struct book* )malloc(sizeof(struct book))  ;
  return(b);
};

struct category
{
    char cname[25];
}cat[20];
int ncat=0;

//ADMIN !!!
char admname[50]="Admin" ;
char admpass[15]="password" ;



void saveb()
{
 //struct book *bs;
 struct book *t;
 FILE *fp;

t=bstart;

while(t!=NULL){

    if(t==bstart)
    {
        if( ( fp=fopen("Book_db.txt","wb+") )==NULL )
  {
      printf("FIle opening error");
      getch();
  }
   fwrite(t,sizeof(struct book),1,fp);
   fclose(fp);
   t=t->r;
 }

 else{

    if( ( fp=fopen("Book_db.txt","rb+") )==NULL )
  {
      printf("FIle opening error");
  }
   fseek(fp, 0, SEEK_END);

  fwrite(t,sizeof(struct book),1,fp);
  fclose(fp);
  t=t->r;

 }
    }
printf("\nSaved Data !");
}




void loadb()
{
 int i;
 long int j;
 struct book *bs;
 struct book* pre = NULL; // to hold previous user from file

 FILE *fp;

   if( ( fp=fopen("Book_db.txt","rb+") )==NULL )
  {
      printf("FIle opening error");
      getch();
  }

  fseek(fp,0,SEEK_END);
  j=ftell(fp);
  j=( j/sizeof(struct book)) ;

   for(i=0;i<j;i++)
   {
    bs=newbook(); // create new user with every iteration
        if (i==0)
            {
                bstart = bs; // set head of list
                fseek(fp, (sizeof(struct book) * i), SEEK_SET);
                fread(bs,sizeof(struct book),1,fp);
                bs->l=NULL;
                bs->l=NULL;
                pre=bs;
                strcpy(cat[0].cname,bs->topic);
                ++ncat;
            }

        else{
        fseek(fp, (sizeof(struct book) * i), SEEK_SET);
        fread(bs,sizeof(struct book),1,fp);
        bs->r = NULL; // set next to NULL for current user
        bs->l=pre;
        pre->r=bs;
        pre = bs;
        sendcat(bs->topic);
        }
   }

   fclose(fp);

}


void displayb()
{
    struct book *t;
    t=bstart;
    int i;
    while(t!=NULL)
    {
        printf("\n\nAuthor:%s\nTitle:%s\nID:%d\nCategory:%s\nAvailable:%d",t->aut,t->bname,t->bid,t->topic,t->nobks);
        t=t->r;
    }

    for(i=0;i<ncat;i++)
    {
        printf("\n%s",cat[i].cname);
    }
    printf("%d",ncat);

    getch();
}

void sendcat(char catchk[])
{
    int i,same=0;
    for(i=0;i<ncat;i++)
    {
        if(strcmp(cat[i].cname,catchk)==0)
        {
            same=1;
            i=ncat;

        }
    }
    if(same==0)
    {
        strcpy(cat[ncat].cname,catchk);
        ++ncat;
    }
}



void saveu()
{
    struct user *ul;
 //struct user *t;
 //int i;
 FILE *fp;

 ul=ustart;

 while(ul!=NULL)
 if(ul==ustart)
 {

   if( ( fp=fopen("User_datab.txt","wb+") )==NULL )
  {
      printf("FIle opening error");
      getch();
  }
   fwrite(ul,sizeof(struct user),1,fp);
   fclose(fp);
   ul=ul->next;
 }
 else
 {
    if( ( fp=fopen("User_datab.txt","rb+") )==NULL )
  {
      printf("FIle opening error");
  }
   fseek(fp, 0, SEEK_END);

  fwrite(ul,sizeof(struct user),1,fp);
  fclose(fp);
  ul=ul->next;
}

}


void loadu()
{
 int i;
 long int j;
 struct user *ul;
 struct user* pre = NULL; // to hold previous user from file

 FILE *fp;

 //ul=newuser();
 //ustart=ul;

   if( ( fp=fopen("User_datab.txt","rb+") )==NULL )
  {
      printf("FIle opening error");
      getch();
  }

  fseek(fp,0,SEEK_END);
  j=ftell(fp);
  j=( j/sizeof(struct user)) ;

   for(i=0;i<j;i++)
   {
    ul=newuser(); // create new user with every iteration
        if (!i)
            ustart = ul; // set head of list

        fseek(fp, (sizeof(struct user) * i), SEEK_SET);
        fread(ul,sizeof(struct user),1,fp);

        ul->next = NULL; // set next to NULL for current user
        if (pre)
            pre->next = ul; // update previous user to point to current one
        pre = ul;
   }

   fclose(fp);

}

void displayu()
{
    struct user *t;
    t=ustart;
    int i;

    while(t!=NULL)
    {
        printf("\nName:%s\nPassword:%s\nID:%d\nNo of Issued:%d",t->uname,t->upass,t->uid,t->currb);
        for(i=0;i<4;i++)
            printf("\n%d",t->listofbooks[i]);

        t=t->next;
    }
    getch();
}


void display(int opt)
{
    int i,lp=1;
    char ch[50];
    struct book *d;


    do{
    system("cls");
    printf("-------CATEGORIES-------\n");
    for(i=0;i<ncat;i++)
    {
        printf( CYAN "\n%d.%s" RESET"\n",i+1,cat[i].cname);
    }

    for(;;)
    {
        printf("\nEnter Category no>>\n ['111'] to Exit::>>");
       scanf("%d",&i);
       i=i-1;
    if( (i>=ncat || i<0) && i!=110 )
    {
        printf("invalid option !!");

    }
    else if(i==110)
    {
        lp=0;
        break;
    }
    else{
        break;
    }
    }

    if(lp)
    {
        strcpy(ch,cat[i].cname);

    system("cls");
    printf("-----CATEGORY: %s-----\n",ch);
    for(d=bstart;d!=NULL;d=d->r)
    {
        if( strcmp(ch,d->topic)==0 )
        {
            if( d->nobks>0 )
            {
                printf( GREEN "\n [%d] Title:%s\nAuthor:%s" RESET  CYAN "\tBook ID:%d" RESET "\n",d->nobks,d->bname,d->aut,d->bid);
            }
            if( d->nobks==0 && opt!=0)
            {
                printf( RED "\n [%d] Title:%s\nAuthor:%s" RESET "\n",d->nobks,d->bname,d->aut);
            }
        }
    }
    if(opt==1)
        {
            printf("\nPress ENTER to go back");
        getch();
        }
        else if(opt==0)
        {
        issb();
        lp=0;
        }
        else if(opt==2)
        {
            downbook();
            lp=0;
        }

      }

    }while(lp);


}


void frame0()
{
    int ch,lp=1;

        do{

         system("cls");
        printf("-----MACROPPLE LIBRARY------");
        printf("\n1.LOGIN\n\n2.VIEW BOOKS\n\n3.ADMIN OPTIONS\n\n4.EXIT\n");
        printf(">>>");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:login();
            break;

            case 2:display(1);
            break;

            case 3:adlogin();
            break;

            case 4:lp=0;
                printf("!!!Exiting Library !!!");
            break;

            case 11:displayu();
            break;

            case 22: displayb();
            break;

            default:printf("invalid option\nPress any key to continue");
            getch();
            break;
        }
        }while(lp);

}


void login()
{
    struct user *t;
    int id,f=0,lp=1;
    char n[50],p[15];

    do{
    system("cls");
    printf("-----USER LOGIN-----");
    fflush(stdin);
    printf("\nEnter Name:");
    gets(n);
    printf("Enter Password:");
    gets(p);
    printf("Enter ID:");
    scanf("%d",&id);

    for(t=ustart;t!=NULL;t=t->next)
    {
        if(t->uid==id)
        {
            if( ( strcmp(t->upass,p) )!=0)
            {
                printf("\nPassword is Incorrect!");
                f=1;
                printf("\nPress any key to continue");
                getch();
                break;
            }
            else
            {
                ulog=t;
                //printf("\nFound!!");
                f=1;
                lp=0;
                break;
            }
        }

    }//for loop break


    if(!f)
    {
        printf("User not Registered!!");
        printf("\nPress any key to continue");
        getch();
    }

    }while(lp);

    printf("\nWelcome :%s !!",ulog->uname);
    printf("\nPress any key to continue");
        getch();
    frame1();

}


void frame1()
{
    int ch,lp=1;

    do{
        system("cls");
        printf("-----USER %s------",ulog->uname);
        printf("\n1.ISSUE BOOKS\n\n2.VIEW ISSUED BOOKS\n  OR RETURN BOOKS\n\n3.BROWSE\n\n4.LOG OUT\n");
        printf(">>>");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:display(0);
            break;

            case 2:ret();
            break;

            case 3:display(1);
            break;

            case 4:lp=0;
                printf(" %s has Logged out",ulog->uname);
                getch();
                ulog=NULL;
            break;

            default:printf("invalid option\nPress any key to continue");
            getch();
            break;
        }

    }while(lp);
}

void issb()
{
    int bch,done=0,th=1,i;
    struct book *t;


    if(ulog->currb==4)
    {
        printf("CANNOT ISSUE MORE THAN 4 BOOKS");
        printf("\nPress any key to continue");
        getch();
    }

    else
    {
        printf("\n>>Enter Book ID>>");
    scanf("%d",&bch);

     for(i=0;i<ulog->currb;i++)
     {
        if(bch==ulog->listofbooks[i])
        {
             printf("\nYou have already issued this book");
          printf("\nPress any key to continue");
            getch();
         th=0;
        }
     }

     if(th)
     {
         for(t=bstart;t!=NULL;t=t->r)
    {
        if( (t->bid==bch) )
        {
            //printf("\t%d ==? %d",t->bid,bch);
            //getch();
            if(t->nobks>0)
            {
            ulog->listofbooks[ulog->currb]=bch;
            ulog->currb=ulog->currb + 1;
            t->nobks=t->nobks - 1;
            done=1;
            break;
            }
        }
    }
    if(!done)
    {
        printf("\nBook not found!");
        printf("\ninvalid option\nPress any key to continue");
        getch();

    }
    else{
        printf("\n%s has issued: %s by %s",ulog->uname,t->bname,t->aut);
        printf("\nPress any key to continue");
            getch();
    }
     }

    }




}


void ret()
{
    int i,bch,th=0,lp=1;
    struct book *b;

    do{
    system("cls");
    printf("----%s 's books-----",ulog->uname);

    for(b=bstart;b!=NULL;b=b->r)
    {
        for(i=0;i<4;i++)
        {
            if(b->bid==ulog->listofbooks[i])
            {
                printf("\n\n%s by %s \nBook ID:%d",b->bname,b->aut,b->bid);
                th=1;
            }
        }
    }

    if(th)
    {
        printf("\nEnter Book Id>>\n or ['999'] to Exit::>>");
       scanf("%d",&bch);

      if(bch==999)
      {
          lp=0;
      }
      else
      {
           for(i=0;i<4;i++)
    {
        if(bch==ulog->listofbooks[i])
        {
            ulog->listofbooks[i]=0;
            --ulog->currb;
            break;
        }
    }

    for(b=bstart;b!=NULL;b=b->r)
    {
        if(b->bid==bch)
        {
            ++b->nobks;
            break;
        }
    }

      }


    }
    else
    {
        printf("\nUser has no Issued books");
        lp=0;
         printf("\nPress any key to continue");
            getch();
    }

    }while(lp);

}

void adlogin()
{
    int lp=1,ch;
    char lad[50],lpass[15];

    for(;;)
    {
        system("cls");
        fflush(stdin);
    printf("Enter Admin name:");
    gets(lad);
    printf("Enter password:");
    gets(lpass);

      if( !strcmp(lad,admname) && !strcmp(lpass,admpass) )
      {
          break;
      }
      else
      {
          printf("\nWrong Admin name or password");
          getch();
      }
    }



    do{

         system("cls");
        printf("------ADMINISTRATOR------");
        printf("\n\n1.NEW BOOK\n\n2.DELETE BOOK\n\n3.ACCESS USER INFO\n\n4.LOG OUT");
        printf("\n\n>>>>");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1: upbook();
            break;

            case 2: display(2);
            break;

            case 3:frame33();
            break;

            case 4:printf("\n\nLOGGED OUT");
            lp=0;
            break;

            default:printf("\nInvalid choice");
            printf("Press any key to continue");
            getch();

        }

    }while(lp);
}

void upbook()
{
    int nid,lp,i;
    char nn[85],naut[50],nct[50];
    struct book *b ;
    struct book *nb;

    system("cls");
    printf("----ADD NEW BOOK TO DATABASE----");
    fflush(stdin);
    printf("\nEnter Book Title:");
    gets(nn);
    printf("Enter Author:");
    gets(naut);

    do{
    printf("\nEnter ID:");
    scanf("%d",&nid);
    lp=0;

    for(b=bstart;b!=NULL;b=b->r)
    {
        if(b->bid==nid)
        {
            printf("\nBook ID already exists !\nEnter different Book ID::");
            lp=1;
        }
    }

    }while(lp);

    printf("\nCategories:");

    for(i=0;i<ncat;i++)
    {
        printf("\n %s",cat[i].cname);
    }

     fflush(stdin);
    printf("\nEnter new category or enter from current topics:");
    gets(nct);
    sendcat(nct);

    b=bstart;
    while(b->r!=NULL)
    {
        b=b->r;
    }

    nb=newbook();
    nb->l=b;
    nb->r=NULL;
    b->r=nb;
    strcpy(nb->aut,naut);
    strcpy(nb->bname,nn);
    strcpy(nb->topic,nct);
    nb->bid=nid;
    nb->nobks=4;

     printf("\n\nAuthor:%s\nTitle:%s\nID:%d\nCategory:%s\nAvailable:%d",nb->aut,nb->bname,nb->bid,nb->topic,nb->nobks);
     getch();

}

void downbook()
{
    int did,done=1;
    struct book *b;
    //struct book *temp;

    printf("\nEnter Book id:");
    scanf("%d",&did);

    for(b=bstart;b!=NULL;b=b->r)
    {
        if(b->bid==did)
        {
           if(b->nobks<=3)
           {
               printf("\nThis book is currently issued please return");
               done=0;
               printf("\nPress any key to cont,");
               getch();
           }
           else
           {
                b->l->r=b->r;
                b->r->l=b->l;
                free(b);
                break;
           }
        }
    }

   if(done)
   {
        printf("\n Book Deleted !!");
        printf("\nPress any key to continue");
        getch();
   }
}

void frame33()
{
    int lp=1,ch;

    do{
        system("cls");
        printf("-----EDIT USER DETAILS-----");
        printf("\n\n1.NEW USER\n\n2.REMOVE USER\n\n3.CHANGE DETAILS\n\n4.EXIT");
        printf("\n>>>");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:nusr();
            break;

            case 2:delusr();
            break;

            case 3: editusr();
            break;

            case 4:lp=0;
            break;

            default:printf("\nInvalid choice\nPress any key to continue");
            getch();
            break;

        }

    }while(lp);
}

void nusr()
{
    int nuid,f,i;
    struct user *u;
    struct user *nu;

    system("cls");
    printf("\n-----NEW USER-----");
    u=ustart;
    while(u->next!=NULL)
    {
        u=u->next;
    }

    nu=newuser();
    u->next=nu;
    nu->next=NULL;

    fflush(stdin);
    printf("\nEnter Name:");
    gets(nu->uname);
    printf("\n Enter password:");
    gets(nu->upass);

    do{
    printf("\nEnter ID:");
    scanf("%d",&nuid);
    f=0;

    for(u=ustart;u!=NULL;u=u->next)
    {
        if(u->uid==nuid)
        {
            printf("\nUser ID already exists !\nEnter different User ID::");
            f=1;
        }
    }

    }while(f);

    nu->uid=nuid;
    nu->currb=0;

    for(i=0;i<4;i++)
    {
        nu->listofbooks[i]=0;
    }

    printf("\nADDED:");
     printf("\nName:%s\nPassword:%s\nID:%d\nNo of Issued:%d",nu->uname,nu->upass,nu->uid,nu->currb);
        for(i=0;i<4;i++)
            {
                printf("\n%d",nu->listofbooks[i]);
            }
    printf("\nPress any key to continue");
    getch();


}

void delusr()
{
    struct user *du;
    struct user *pre;
    int did,done=0;

    system("cls");
    printf("\n-----CURRENT USERS-----");

    for(du=ustart;du!=NULL;du=du->next)
    {
        printf("\n\nName:%s\nID:%d\tNo of Books:%d",du->uname,du->uid,du->currb);
    }

    printf("\nEnter User id:");
    scanf("%d",&did);

    pre=du=ustart;
    while(du!=NULL)
    {
        if(du->uid==did)
        {
           if(du->currb>0)
           {
               printf("\n User has issued books!!\nPress any key to continue");
               getch();
               break;
           }
           else
           {

            if(du==ustart)
            {
                ustart=du->next;
                free(du);
                done=1;
                break;
            }
            else{

                pre->next=du->next;
                free(du);
                done=1;
                break;
            }
           }

        }

        pre=du;
        du=du->next;
    }

   if(done)
   {
        printf("\n User Deleted !!");
        printf("\nPress any key to continue");
        getch();
   }
}

void editusr()
{
    int i,eid,done=0;
    struct user *eu;

    system("cls");
    printf("\n-----CURRENT USERS-----");

    for(eu=ustart;eu!=NULL;eu=eu->next)
    {
        printf("\n\nName:%s\nID:%d",eu->uname,eu->uid);
    }

    printf("\nEnter User id:");
    scanf("%d",&eid);

    for(eu=ustart;eu!=NULL;eu=eu->next)
    {
        if(eu->uid==eid)
        {
            printf("\nEnter new details:");
            fflush(stdin);
            printf("\nName:");
            gets(eu->uname);
            printf("\nPassword:");
            gets(eu->upass);
            printf("\nEnter ID:");
            scanf("%d",&eu->uid);
            done=1;
            break;

        }
    }

    if(done)
    {
        printf("\nChanged details:");
        printf("\n\nName:%s\nPassword:%s\nID:%d\nNo of Issued:%d",eu->uname,eu->upass,eu->uid,eu->currb);
        for(i=0;i<4;i++)
            printf("\n%d",eu->listofbooks[i]);

        getch();
    }
}

int main()
{
   system("cls");
    loadb();
    loadu();
   frame0();

    saveb();
    saveu();

    return 0;
}
