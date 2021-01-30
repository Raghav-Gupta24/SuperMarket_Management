/*
PROJECT
Develped By: Raghav Gupta
Class	   : XII-K
*/
#include<iostream.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<fstream.h>

struct Date
{
	int day, month, year;
};
class ITEM
{
	int Ino, qty;
	float Price;
	char Name[20], categ;    //category
	public:
	void input()
	{
	  cout<<"Ino:";  cin>>Ino;
	  cout<<"Price:";  cin>>Price;
	  cout<<"Name:";  gets(Name);
	  cout<<"Quantity:";  cin>>qty;
	  cout<<"Category:";  cin>>categ;
	}
	 void Edit()
	{
	  int ch;
	  cout<<"1. Price 2. Name 3. Quantity 4. Category 5. edit all\n";
	  cin>>ch;
	  if(ch==1)
	 {
	  cout<<"Price:";  cin>>Price;
	 }
	   else
	   if(ch==2)
	  {
	   cout<<"Name:";  gets(Name);
	  }
	  else
	  if(ch==3)
	  {
	   cout<<"Quantity:";  cin>>qty;
	  }
	  else
	  if(ch==4)
	  {
	   cout<<"Category:";  cin>>categ;
	  }
	  else
	   if(ch==5)
	  input();
	}
	void IQty(int i){qty+=i;}
	int Rino(){return Ino;}
	char RCateg(){return categ;}
	float Rprice(){return Price;}
	int Rqty(){return qty;}
	char *Rname(){return Name;}
	void Disp()
	{
	  cout<<"Item number:"<<Ino;
	  cout<<"\n Name:";  puts(Name);
	  cout<<"Price:"<<Price;
	  cout<<endl;
	}
};

class Transact
{
	int ino, qty;
	Date dat;
       char CustName[20];
	char Iname[40];
	float price, amount;
	public:
	float RAmount(){return amount;}
	void EDate()
	{
	  cout<<"Day:";  cin>>dat.day;
	  cout<<"Month:";  cin>>dat.month;
	  cout<<"Year:";  cin>>dat.year;
	}
	void AssignData( ITEM T)
	{
	 ino=T.Rino();
	 price=T.Rprice();
	 qty=T.Rqty();
	 strcpy(Iname,T.Rname());
	 amount=price*qty;
	 }
	void GetDetail()
	{
	  cout<<"Enter name :";
	  gets(CustName);
	  cout<<"Enter date:\n:";
	  EDate();
	}
	char *Rname(){return Iname;}
	void DisplayCust()
	{
	  puts(CustName);
	  cout<<"\t"<<dat.day<<"/"<<dat.month<<"/"<<dat.year<<endl;
	}
	void DisplayDetails()
	{
	cout<<ino<<"  "<<Iname<<"  "<<qty<<"  "<<price<<"  "<<amount;
	}
};
void Admin();    //
void Customer();   //
void Update();  //
void AddItem();     //
void ChangePass();    //
int CheckPass(char []); //
void Billing(ITEM ,int);     //
void DisplayItem();   //
void BuyItem();       //
void DeleteItem();    //
void Supply();     //
void PrintBill();               //
void main()
{
  clrscr();
  char c;
  do
  {
    cout<<"Good Morning..\n";
    cout<<"[A] Admin   [C] Customer   [E] Exit";
    cin>>c;
    c=toupper(c);
    if(c=='A')
     Admin();
    else if(c=='C')
     Customer();
  }while(c!='E');
  cout<<"Have a nice day..\n";
  getch();
}
void Admin()
{
  char pass[20];
  cout<<"Enter Password:";
  char ch,c;
  int i=0;
  do
  {
    ch=getch();
    pass[i++]=ch;
    cout<<"*";
  }
    while(ch!=13);

    pass[i-1]='\0';

  if(CheckPass(pass)==1)
  {
   do
   {
     cout<<"\n[A]Add Item [U] Update [D] Delete Item";
     cout<<"  [C] Change Password  \n[N] New Supplies ";
     cout<<" [R] Display [M]Main menu\n";
     cin>>c;
     c=toupper(c);
     switch(c)
     {
       case 'A': AddItem();
		break;
      case 'U': Update();
		break;
       case 'D': DeleteItem();
		break;
       case 'N':  Supply();
		break;
       case 'R':  DisplayItem();
		break;
       case 'M': cout<<"Going Back..\n";
		break;
     }
   }while(c!='M');
  }
  else
   cout<<"Wrong password";
}
void Update()
{
   fstream fil;
  fil.open("Items.dat",ios::in|ios::out|ios::binary);
   ITEM A;
   int INO;
   cout<<"Enter the Item number to be updated: ";
    cin>>INO;
  int ctr=0;
  while(ctr==0&& fil.read((char*)&A, sizeof(A)))
 {
  if(INO==A.Rino())
  {
   A.Edit();
   fil.seekg(fil.tellg()-sizeof(A));
   fil.write((char*)&A, sizeof(A));
   ctr++;
   }
  }
  if(!ctr)
  cout<<"Could not find a matching item\n";
  else
  cout<<"Record updated sucessfully\n";

  fil.close();
}

void Customer()
{
  char c;
  ITEM A;
  do
  {
    cout<<"[B] Search & Buy  [D] Display Item  [M] Main Menu";
    cin>>c;
    c=toupper(c);
    switch(c)
    {
	case 'B': BuyItem(); A.Disp();
		   break;
	case 'D': DisplayItem();
			break;
       case 'M':cout<<" going back\n";
    }
  }while(c!='M');   //HOW DO I EXIT THE PROGRAMME ONCE I'M HERE
  //THERE'S SOMETHING WRONG IN THIS STATEMENT
}
int CheckPass(char A[])
{
  fstream fil;
  fil.open("Password.txt",ios::in);
  char Pass[15];

  fil.getline(Pass,15);
  fil.close();
  if(strcmp(A,Pass)==0)
     return 1;
  else
     return 0;
}
void ChangePass()
{
  int i=0;
  char A[15];
  do
  {
   cout<<"Enter new password:";
   gets(A);
   cout<<"Confirm new password:";
   char B[15];
   gets(B);
   if(strcmp(A,B)==0)
     i++;
   else
     cout<<"Re-enter\n";
  }while(i==0);
  fstream fil;
  fil.open("Password.txt",ios::out);
  fil<<A<<endl;
  fil.close();
}
void AddItem()
{
  char c;
  fstream fil;
  fil.open("Items.dat",ios::app|ios::binary);
  ITEM A;
  do
  {
   A.input();
   fil.write((char*)&A, sizeof(A));
   cout<<"More?(y/n)";
   cin>>c;

  }while(tolower(c)!='n');
  fil.close();
}
void BuyItem()
{
  fstream fil;
  fil.open("Items.dat",ios::in|ios::out |ios::binary);
  ITEM A;
  int flag=0, flag2=0,rec=0;
  int num,Qty;
  DisplayItem();
  while(!flag && fil.read((char*)&A, sizeof(A)))
  {
    cout<<"Item number:";
    cin>>num;
     rec++;
    if(num==A.Rino())
    {
     flag++;
     cout<<"enter quatity to buy\n";
     cin>>Qty;
     if(Qty< A.Rqty())
     { cout<<"transaction possible";flag2++;
       A.IQty(-1*Qty);
       fil.seekg(fil.tellg()-sizeof(A));
       fil.write((char*)&A, sizeof(A));
     }
     else
      cout<<"not enough quatity\n";
     }
   }
   fil.close();
   if(flag2)
    Billing(A,Qty);
 }

void DisplayItem()
{
  cout<<"Which category of items do you want to display?";
  cout<<"\n [F] Food [S] Stationary  [E] Electronics ";
		//food clothing books stationary elsectronics
  char c;
  cin>>c;
  fstream fil;
  fil.open("Items.dat", ios::in|ios::binary);
  ITEM A;
while(    fil.read((char*)&A,sizeof(A)))
  {
    char a=A.RCateg();
    if(a==tolower(c)||a==toupper(c))
      A.Disp();
  }
  fil.close();
}
void DeleteItem()
{
  fstream fil,temp;
  fil.open("Items.dat",ios::binary|ios::in);
  temp.open("Temp.dat", ios::binary|ios::out);
  ITEM A;
  int Del=0, ino;
  cout<<"Enter the item number you want to delete:";
  cin>>ino;
  while(fil.read((char*)&A,sizeof(A)))
  {
    if(A.Rino()==ino)
      Del=1;
    else
      temp.write((char*)&A,sizeof(A));
  }
 fil.close();
 temp.close();
 if(Del==1)
  {
    remove("Items.dat");
    rename("temp.dat","Items.dat");
  }
  else
    cout<<"Item not found\n";
}
void Supply()
{
  char name[15];
  int i,ino;
  ITEM A;
  cout<<"Supplies of which item have come?";
  cin>>ino;
  //A=SearchItem();

  cout<<"Enter the quantity supplied:";
  cin>>i;
  A.IQty(i);
}
void Billing(ITEM A, int Qty)
{
  //float Tprice=0;
  int i;
  char reply;
  ITEM A1;
  Transact T;
  T.GetDetail();
  fstream fil, F;
  fil.open("Bill.dat",ios::binary|ios::app);
  T.AssignData(A);
  fil.write((char*)&T,sizeof(T));
  fil.close();
  cout<<"Want to buy any other item :\n";
  cin>>reply;
  if(reply=='y')
   BuyItem();
 else
 PrintBill();
 }
 void PrintBill()
 {
  fstream fil;
  fil.open("Bill.dat",ios::binary|ios::in);
  float Total=0;
  Transact T;
  T.GetDetail();
  T.DisplayCust();
  while(fil.read((char*)&T,sizeof(T)))
  {
   Total+=T.RAmount();
   T.DisplayDetails();
  }
  cout<<"total amount to be paid:"<<Total<<endl;
  }


