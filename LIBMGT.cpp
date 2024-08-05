//A C++ Program for Simple Books Library System
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<conio.h>
#include<dos.h>
#include<fstream.h>
#include<graphics.h>
#include<math.h>
class Menu
{ public:
    void MainMenu(void);
    void Introduction(void);
    void BackGround(void);
  private:
    void EditMenu(void);
    void EditBookMenu(void);
    void EditMemberMenu(void);
    void EnquireMenu(void);
};
class Book
{ public:
    void List(void);
    char *BookName(unsigned long);
  protected:
    void AddNewBook(unsigned long,char[],char[],int,int,int);
    void UpdateCopies(unsigned long,int,int,unsigned long,char);
    void Modify(unsigned long,char[],int);
    int BookFound(unsigned long);
    int BookNameFound(char[]);
    int Available(unsigned long);
    char *AuthorName(unsigned long);
    int BookPrice(unsigned long);
    int NoOfCopies(unsigned long);
    unsigned long BookCodeOf(char[]);
    void Display(unsigned long);
    void DeleteRecord(unsigned long);
    int NumberOfCopiesOfBookIssued(unsigned long);
    void HeadingForListOfAllBooks(void);
  private:
    char BookCode[11];
    //Upto 10 Members can be Issued Copies of a Book
    char M1[11],M2[11],M3[11],M4[11],M5[11],M6[11],M7[11],M8[11],M9[11],M10[11];
    char Name[31],Author[26];
    char Price[6],Copies[6],Avail[6];
};
class Member
{ public:
    void List(void);
  protected:
    void AddMem(unsigned long,char[],char[],char[]);
    void Modify(unsigned long,char[],char[]);
    int MemberFound(unsigned long);
    void UpdateBook(unsigned long,unsigned long,int,int,int,char);
    char *MemberName(unsigned long);
    unsigned long LastMemberCode(void);
    unsigned long Issued(unsigned long);
    int Fine(unsigned long,unsigned long);
    unsigned long MemberCodeOf(char[]);
    int Display(unsigned long);
    void DeleteRecord(unsigned long);
    void HeadingForListOfAllMembers(void);
  private:
    char MemberCode[11];
    char Name[21],Phone[11],Address[31];
    //Upto 5 Books can be Issued to a Member
    char B1[11],B2[11],B3[11],B4[11],B5[11];
    //5 Book Return Dates for 5 Books Issued to a Member
    char DD1[6],MM1[6],YY1[6],DD2[6],MM2[6],YY2[6],DD3[6],MM3[6],YY3[6];
    char DD4[6],MM4[6],YY4[6],DD5[6],MM5[6],YY5[6];
};
class Transaction
{ public:
    void List(void);
  protected:
    char *GetTransactionDate(void);
    void AddTransaction(unsigned long,char[],char[],unsigned long,
			unsigned long,int);
    int TransactionFound(unsigned long);
    int TransactionDateFound(char[]);
    unsigned long LastTransactionCode(void);
    void Display(unsigned long);
    void HeadingForListOfAllTransactions(void);
  private:
    char TransactionCode[11]; char TransactionDate[11],TransactionType[3];
    /* Transaction Types... AB - Append Book, AM - Append Member,
			    IB - Issue Book,  RB - Return Book,
			    MB - Modify Book, MM - Modify Member,
			    DB - Delete Book, DM - Delete Member  */
    char MemberCode[11],BookCode[11]; char Copies[6];
};
class Working : public Book, public Member, public Transaction
{ public:
    void IssueBook(void);
    void ReturnBook(void);
    void AddBook(void);
    void AddMember(void);
    void ModifyBook(void);
    void ModifyMember(void);
    void DeleteBook(void);
    void DeleteMember(void);
    void EnquireBook(void);
    void EnquireMember(void);
    void EnquireTransaction(void);
    int NumericTest(char[]);
};
class Date
{ public:
    void ExtendDate(int,int,int,int);
    int Diff(int,int,int,int,int,int);
    int Day,Mon,Year;
};
//Function to Extend Date by 15 Days
void Date::ExtendDate(int D1,int M1,int Y1,int Days)
{ int i; static int Month[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
  for (i = 1; i <= Days; i++)
  { D1++;
    if ((D1 > Month[M1-1]) || (Y1 % 4 != 0 && M1 == 2 && D1 > 28))
    { D1 = 1; M1++; }
    if (M1 > 12) { M1 = 1; Y1++; }
  }
  Day = D1; Mon = M1; Year = Y1;
}
//Function to Calculate Number of Days Between Two Dates
int Date::Diff(int D1,int M1,int Y1,int D2,int M2,int Y2)
{ int Days = 0; static int Month[] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
  if ((Y2<Y1)||(Y2==Y1 && M2<M1)||(Y2==Y1 && M2==M1 && D2<D1)) return Days;
  while (D1 != D2 || M1 != M2 || Y1 != Y2)
  { Days++; D1++;
    if ((D1 > Month[M1-1]) || (Y1%4 != 0 && M1==2 && D1>28)) { D1 = 1; M1++; };
    if (M1 > 12) { M1 = 1; Y1++; }
  }
  return Days;
}
//Function to Display the Introduction for the Project/System
void Menu::Introduction(void)
{ //Request for Auto Detection of Graphics Driver
  int gdriver = DETECT, gmode, errorcode;
  int x[15], y[15], x_centre, y_centre = 240, radius = 195, i, j, midx;
  char *fname[] = { "L","I","B","R","A","R","Y","S","Y","S","T","E","M" };
  //Initialize Graphics and Local Variables
  initgraph(&gdriver, &gmode, "F:\\tc\\bgi");
  //Read Result of Initialization
  errorcode = graphresult();
  //If an Error Occurs...
  if (errorcode != grOk)
  { printf("Graphics error : %s\n", grapherrormsg(errorcode));
    printf("Press any key to exit ");
    getch(); exit(1); //Terminate with an Error Code
  }
  setbkcolor(YELLOW); setcolor(RED);
  for (x_centre = 195; x_centre <= 445; x_centre += 5)
  { for ( i = 0; i < 15; i++ )
    { x[i] = x_centre + radius * cos((24*i + (x_centre-195)) * 3.14159/180);
      y[i] = y_centre + radius * sin((24*i + (x_centre-195)) * 3.14159/180);
    }
    for ( i = 0; i < 15; i++ )
    for ( j = 0; j < 15; j++ ) { line(x[i], y[i], x[j], y[j]); }
    delay(100); if (x_centre != 445) cleardevice();
  }
  setcolor(RED); settextstyle(10,HORIZ_DIR,2); outtextxy(1,1,"WELCOME TO ...");
  setcolor(GREEN); outtextxy(320,1,"SIMPLE BOOKS");
  for (i = 0; i < 13; i++) //Print Message
  { outtextxy(90+30*(i/7), 40+30*i, *(fname+i)); delay(500); }
  setcolor(BLUE); settextstyle(10, HORIZ_DIR, 1);
  outtextxy(120,440,"\7Press Any Key to Continue "); getch(); setcolor(RED);
  settextstyle(0, HORIZ_DIR, 1); midx = getmaxx()/2; y_centre = getmaxy()/2;
  for (x_centre = 445; x_centre >= midx; x_centre -= 5)
  { for ( i = 0; i < 15; i++ )
    { x[i] = x_centre + radius * cos((24*i + (x_centre-195)) * 3.14159/180);
      y[i] = y_centre + radius * sin((24*i + (x_centre-195)) * 3.14159/180);
    }
    for ( i = 0; i < 15; i++ )
    for ( j = 0; j < 15; j++ ) { line(x[i], y[i], x[j], y[j]); }
    delay(100); if (x_centre != midx) cleardevice();
  }
  for (radius = 240; radius <= 2000; radius += 20)
  { for ( i = 0; i < 15; i++ )
    { x[i] = x_centre + radius * cos((24*i + (x_centre-240)) * 3.14159/180);
      y[i] = y_centre + radius * sin((24*i + (x_centre-240)) * 3.14159/180);
    }
    for ( i = 0; i < 15; i++ )
    for ( j = 0; j < 15; j++ ) { line(x[i],y[i],x[j],y[j]); }
    if (radius == 2000) break; cleardevice();
  }
  gotoxy(27,6);  cout<<"Welcome To The Project...";
  gotoxy(26,8);  cout<<"SIMPLE BOOKS LIBRARY SYSTEM";
  gotoxy(15,11); cout<<"This System has Facility of Maintaining Records of";
  gotoxy(15,12); cout<<"Books and Members.";
  gotoxy(15,14); cout<<"It can Hold More than  10,000 Records of Books and";
  gotoxy(15,15); cout<<"Members.";
  gotoxy(15,17); cout<<"One Member can Issue Maximum 5 Books at a Time. If";
  gotoxy(15,18); cout<<"He / She Does not Return a Book upto 15 Days, then";
  gotoxy(15,19); cout<<"He / She has to Pay a Fine of Rs. 3/- per Day.";
  gotoxy(15,21); cout<<"A Copy of the Book(Title) can be Issued to Maximum";
  gotoxy(15,22); cout<<"10 Members at a Time.";
  gotoxy(27,25); cout<<"\7Press Any Key to Continue "; getch();
  closegraph(); //Close Graphics Mode and Restore CRT Mode
}
//Function to Display Background in Graphics Mode
void Menu::BackGround(void)
{ //Request for Auto Detection of Graphics Driver
  int gdriver = DETECT, gmode, errorcode;
  int x[15], y[15], x_centre, y_centre, radius, i, j;
  //Initialize Graphics and Local Variables
  initgraph(&gdriver, &gmode, "\\tc\\bgi");
  //Read Result of Initialization
  errorcode = graphresult();
  //If an Error Occurs...
  if (errorcode != grOk)
  { printf("Graphics error : %s\n", grapherrormsg(errorcode));
    printf("Press any key to exit ");
    getch(); exit(1); //Terminate with an Error Code
  }
  x_centre = getmaxx()/2; y_centre = getmaxy()/2;
  setbkcolor(YELLOW); setcolor(RED);
  for (radius = 240; radius <= 2000; radius += 20)
  { for ( i = 0; i < 15; i++ )
    { x[i] = x_centre + radius * cos((24*i + (x_centre-240)) * 3.14159/180);
      y[i] = y_centre + radius * sin((24*i + (x_centre-240)) * 3.14159/180);
    }
    for ( i = 0; i < 15; i++ )
    for ( j = 0; j < 15; j++ ) { line(x[i], y[i], x[j], y[j]); }
    if (radius == 2000) break; cleardevice();
  }
}
//Function to Display and Control Main Menu
void Menu::MainMenu(void)
{ char ch;
  while (1)
  { Menu::BackGround(); //Graphics Mode
    gotoxy(22,7);  cout<<"WELCOME TO SIMPLE BOOKS LIBRARY SYSTEM";
    gotoxy(22,8);  cout<<"--------------------------------------";
    gotoxy(19,11); cout<<"1. Append Books to Books Master(B/b)";
    gotoxy(19,12); cout<<"2. Append Members to Members Master(M/m)";
    gotoxy(19,13); cout<<"3. Issue Book to a Member(I/i)";
    gotoxy(19,14); cout<<"4. Return Book from a Member(R/r)";
    gotoxy(19,15); cout<<"5. List Books in the System(L/l)";
    gotoxy(19,16); cout<<"6. List Members in the System(S/s)";
    gotoxy(19,17); cout<<"7. List Transactions in the System(T/t)";
    gotoxy(19,18); cout<<"8. Edit a Book/Member(E/e)";
    gotoxy(19,19); cout<<"9. Enquire a Book/Member/Transaction(N/n)";
    gotoxy(19,20); cout<<"0. Quit from this System(Q/q/Esc)";
    gotoxy(21,23); cout<<"\7Please Enter Your Choice(0..9/Char/Esc) ";
    ch = toupper(getche());
    closegraph(); //Close Graphics Mode and Restore CRT Mode
    if ((ch == '1') || (ch == 'B')) { Working W; W.AddBook(); }
    else if ((ch == '2') || (ch == 'M')) { Working W; W.AddMember(); }
    else if ((ch == '3') || (ch == 'I')) { Working W; W.IssueBook(); }
    else if ((ch == '4') || (ch == 'R')) { Working W; W.ReturnBook(); }
    else if ((ch == '5') || (ch == 'L')) { Book B; B.List(); }
    else if ((ch == '6') || (ch == 'S')) { Member M; M.List(); }
    else if ((ch == '7') || (ch == 'T')) { Transaction T; T.List(); }
    else if ((ch == '8') || (ch == 'E')) EditMenu();
    else if ((ch == '9') || (ch == 'N')) EnquireMenu();
    else if ((ch == '0') || (ch == 'Q') || (ch == 27)) break;
  }
}
//Function to Display and Control Edit Menu
void Menu::EditMenu(void)
{ char ch;
  while (1)
  { Menu::BackGround(); //Graphics Mode
    gotoxy(32,9);  cout<<"EDIT BOOK/MEMBER";
    gotoxy(32,10); cout<<"----------------";
    gotoxy(30,13); cout<<"1. Edit Book(B/b)";
    gotoxy(30,14); cout<<"2. Edit Member(M/m)";
    gotoxy(30,15); cout<<"0. Quit(Q/q/Esc)";
    gotoxy(21,18); cout<<"\7Please Enter Your Choice(0..2/Char/Esc) ";
    ch = toupper(getche());
    closegraph(); //Close Graphics Mode and Restore CRT Mode
    if ((ch == '1') || (ch == 'B')) EditBookMenu();
    else if ((ch == '2') || (ch == 'M')) EditMemberMenu();
    else if ((ch == '0') || (ch == 'Q') || (ch == 27)) break;
  }
}
//Function to Display and Control Edit Menu for Book
void Menu::EditBookMenu(void)
{ char ch;
  while (1)
  { Menu::BackGround(); //Graphics Mode
    gotoxy(36,9);  cout<<"EDIT BOOK";
    gotoxy(36,10); cout<<"---------";
    gotoxy(32,13); cout<<"1. Modify(M/m)";
    gotoxy(32,14); cout<<"2. Delete(D/d)";
    gotoxy(32,15); cout<<"0. Quit(Q/q/Esc)";
    gotoxy(21,18); cout<<"\7Please Enter Your Choice(0..2/Char/Esc) ";
    ch = toupper(getche());
    closegraph(); //Close Graphics Mode and Restore CRT Mode
    if ((ch == '1') || (ch == 'M')) { Working W; W.ModifyBook(); }
    else if ((ch == '2') || (ch == 'D')) { Working W; W.DeleteBook(); }
    else if ((ch == '0') || (ch == 'Q') || (ch == 27)) break;
  }
}
//Function to Display and Control Edit Menu for Member
void Menu::EditMemberMenu(void)
{ char ch;
  while (1)
  { Menu::BackGround(); //Graphics Mode
    gotoxy(35,9);  cout<<"EDIT MEMBER";
    gotoxy(35,10); cout<<"-----------";
    gotoxy(32,13); cout<<"1. Modify(M/m)";
    gotoxy(32,14); cout<<"2. Delete(D/d)";
    gotoxy(32,15); cout<<"0. Quit(Q/q/Esc)";
    gotoxy(21,18); cout<<"\7Please Enter Your Choice(0..2/Char/Esc) ";
    ch = toupper(getche());
    closegraph(); //Close Graphics Mode and Restore CRT Mode
    if ((ch == '1') || (ch == 'M')) { Working W; W.ModifyMember(); }
    else if ((ch == '2') || (ch == 'D')) { Working W; W.DeleteMember(); }
    else if ((ch == '0') || (ch == 'Q') || (ch == 27)) break;
  }
}
//Function to Display and Control Enquire Menu
void Menu::EnquireMenu(void)
{ char ch;
  while (1)
  { Menu::BackGround(); //Graphics Mode
    gotoxy(25,9);  cout<<"ENQUIRE BOOK/MEMBER/TRANSACTION";
    gotoxy(25,10); cout<<"-------------------------------";
    gotoxy(27,13); cout<<"1. Enquire Book(B/b)";
    gotoxy(27,14); cout<<"2. Enquire Member(M/m)";
    gotoxy(27,15); cout<<"3. Enquire Transaction(T/t)";
    gotoxy(27,16); cout<<"0. Quit(Q/q/Esc)";
    gotoxy(21,19); cout<<"\7Please Enter Your Choice(0..2/Char/Esc) ";
    ch = toupper(getche());
    closegraph(); //Close Graphics Mode and Restore CRT Mode
    if ((ch == '1')||(ch == 'B')) { Working W; W.EnquireBook(); }
    else if ((ch == '2')||(ch == 'M')) { Working W; W.EnquireMember(); }
    else if ((ch == '3')||(ch == 'T')) { Working W; W.EnquireTransaction(); }
    else if ((ch == '0') || (ch == 'Q') || (ch == 27)) break;
  }
}
//Function to Return 0, If a Given Book Code is Not Found
int Book::BookFound(unsigned long tCode)
{ int found = 0; char *endptr; unsigned long BookCode1; fstream file;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { found = 1; break; }
  }
  file.close(); return found;
}
//Function to Return 0, If a Given Book Name is Not Found
int Book::BookNameFound(char t1Code[31])
{ int found = 0; fstream file;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  if (!strcmpi(Name,t1Code)) { found = 1; break; }
  file.close(); return found;
}
//Function to Return Available Copies of a Given Book Code
int Book::Available(unsigned long tCode)
{ int tAvail = 0; fstream file; unsigned long BookCode1; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { tAvail = atoi(Avail); break; }
  }
  file.close(); return tAvail;
}
//Function to Return Number of Copies of a Given Book Code
int Book::NoOfCopies(unsigned long tCode)
{ int tCopies = 0; fstream file; unsigned long BookCode1; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { tCopies = atoi(Copies); break; }
  }
  file.close(); return tCopies;
}
//Function to Return Book Name of a Given Book Code
char *Book::BookName(unsigned long tCode)
{ char tName[31],*endptr; fstream file; unsigned long BookCode1;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { strcpy(tName,Name); break; }
  }
  file.close(); return tName;
}
//Function to Return Author Name of a Given Book Code
char *Book::AuthorName(unsigned long tCode)
{ char tAuthor[26],*endptr; fstream file; unsigned long BookCode1;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { strcpy(tAuthor,Author); break; }
  }
  file.close(); return tAuthor;
}
//Function to Return Book Price of a Given Book Code
int Book::BookPrice(unsigned long tCode)
{ int tPrice = 0; fstream file; unsigned long BookCode1; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode) { tPrice = atoi(Price); break; }
  }
  file.close(); return tPrice;
}
//Function to Return Book Code of a Given Book Name
unsigned long Book::BookCodeOf(char t1Code[31])
{ unsigned long tCode = 0; fstream file; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  if (!strcmpi(Name,t1Code)) { tCode = strtoul(BookCode,&endptr,10); break; }
  file.close(); return tCode;
}
//Function to Return Member Code of a Given Member Name
unsigned long Member::MemberCodeOf(char m1Code[21])
{ unsigned long mCode = 0; fstream file; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  if (!strcmpi(Name,m1Code)) { mCode = strtoul(MemberCode,&endptr,10); break; }
  file.close(); return mCode;
}
//Function to Delete Record of a Given Book Code
void Book::DeleteRecord(unsigned long tCode)
{ unsigned long BookCode1; char *endptr; fstream file,temp;
  file.open("BOOKMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Book)); if (file.eof()) break;
    BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 != tCode) temp.write((char *)this,sizeof(Book));
  }
  file.close(); temp.close();
  remove("BOOKMSTR.DAT"); rename("TEMPMSTR.DAT","BOOKMSTR.DAT");
}
//Function to Add a Record in Books Master File
void Book::AddNewBook(unsigned long tCode,char tName[31],char tAuthor[26],
		      int tPrice,int tCopies,int tAvail)
{ int i; fstream file; file.open("BOOKMSTR.DAT",ios::app);
  ultoa(tCode,BookCode,10); strcpy(Author,tAuthor);
  itoa(tPrice,Price,10); itoa(tCopies,Copies,10); itoa(tAvail,Avail,10);
  strcpy(M1,""); strcpy(M2,""); strcpy(M3,""); strcpy(M4,""); strcpy(M5,"");
  strcpy(M6,""); strcpy(M7,""); strcpy(M8,""); strcpy(M9,""); strcpy(M10,"");
  strcpy(Name,tName); file.write((char *)this,sizeof(Book)); file.close();
}
//Function to Update a Record in Books Master File for a Given Book Code
void Book::UpdateCopies(unsigned long tCode,int tCopies,int tAvail,
			unsigned long mCode,char ch)
{ fstream file,temp; int i; char *endptr; char MemberCode2[10];
  unsigned long BookCode1,M11,M21,M31,M41,M51,M61,M71,M81,M91,M101;
  file.open("BOOKMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Book)); if (file.eof()) break;
    BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode)
    { itoa(tCopies,Copies,10); itoa(tAvail,Avail,10);
      if (ch == '3') //Issue
      { for (;;)
	{ if (!strcmpi(M1,"")) { ultoa(mCode,M1,10); break; }
	  if (!strcmpi(M2,"")) { ultoa(mCode,M2,10); break; }
	  if (!strcmpi(M3,"")) { ultoa(mCode,M3,10); break; }
	  if (!strcmpi(M4,"")) { ultoa(mCode,M4,10); break; }
	  if (!strcmpi(M5,"")) { ultoa(mCode,M5,10); break; }
	  if (!strcmpi(M6,"")) { ultoa(mCode,M6,10); break; }
	  if (!strcmpi(M7,"")) { ultoa(mCode,M7,10); break; }
	  if (!strcmpi(M8,"")) { ultoa(mCode,M8,10); break; }
	  if (!strcmpi(M9,"")) { ultoa(mCode,M9,10); break; }
	  if (!strcmpi(M10,"")) { ultoa(mCode,M10,10); break; }
	  break;
	}
      }
      if (ch == '4') //Return
      { for (;;)
	{ M11 = strtoul(M1,&endptr,10); M21 = strtoul(M2,&endptr,10);
	  M31 = strtoul(M3,&endptr,10); M41 = strtoul(M4,&endptr,10);
	  M51 = strtoul(M5,&endptr,10); M61 = strtoul(M6,&endptr,10);
	  M71 = strtoul(M7,&endptr,10); M81 = strtoul(M8,&endptr,10);
	  M91 = strtoul(M9,&endptr,10); M101 = strtoul(M10,&endptr,10);
	  if (M11 == mCode) { strcpy(M1,""); break; }
	  if (M21 == mCode) { strcpy(M2,""); break; }
	  if (M31 == mCode) { strcpy(M3,""); break; }
	  if (M41 == mCode) { strcpy(M4,""); break; }
	  if (M51 == mCode) { strcpy(M5,""); break; }
	  if (M61 == mCode) { strcpy(M6,""); break; }
	  if (M71 == mCode) { strcpy(M7,""); break; }
	  if (M81 == mCode) { strcpy(M8,""); break; }
	  if (M91 == mCode) { strcpy(M9,""); break; }
	  if (M101 == mCode) { strcpy(M10,""); break; }
	  break;
	}
      }
      temp.write((char *)this,sizeof(Book));
    } else temp.write((char *)this,sizeof(Book));
  }
  file.close(); temp.close();
  remove("BOOKMSTR.DAT"); rename("TEMPMSTR.DAT","BOOKMSTR.DAT");
}
//Function to Modify a Record in Books Master File for a Given Book Code
void Book::Modify(unsigned long tCode,char tAuthor[26],int tPrice)
{ fstream file,temp; int i; unsigned long BookCode1; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Book)); if (file.eof()) break;
    BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode)
    { strcpy(Author,tAuthor); itoa(tPrice,Price,10);
      temp.write((char *)this,sizeof(Book));
    } else temp.write((char *)this,sizeof(Book));
  }
  file.close(); temp.close();
  remove("BOOKMSTR.DAT"); rename("TEMPMSTR.DAT","BOOKMSTR.DAT");
}
//Function to Display a Record from Books Master File for a Given Book Code
void Book::Display(unsigned long tCode)
{ fstream file; int i; unsigned long BookCode1,MemberCode1; char *endptr;
  unsigned long M11,M21,M31,M41,M51,M61,M71,M81,M91,M101;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  textbackground(GREEN); textcolor(RED);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode)
    { gotoxy(5,2); cout<<"Book Code   : "<<BookCode1;
      gotoxy(5,3); cout<<"Book Name   : "<<Name;
      gotoxy(5,4); cout<<"Author Name : "<<Author;
      gotoxy(5,5); cout<<"Price(Rs.)  : "<<atoi(Price);
      gotoxy(5,6); cout<<"Number of Copies : "<<atoi(Copies);
      gotoxy(5,7); cout<<"Copies Available : "<<atoi(Avail);
      gotoxy(5,8); cout<<"Copies Issued    : "<<atoi(Copies)-atoi(Avail);
      gotoxy(5,9); cout<<"Copies Issued To Members : "; textcolor(WHITE);
      M11 = strtoul(M1,&endptr,10); M21 = strtoul(M2,&endptr,10);
      M31 = strtoul(M3,&endptr,10); M41 = strtoul(M4,&endptr,10);
      M51 = strtoul(M5,&endptr,10); M61 = strtoul(M6,&endptr,10);
      M71 = strtoul(M7,&endptr,10); M81 = strtoul(M8,&endptr,10);
      M91 = strtoul(M9,&endptr,10); M101 = strtoul(M10,&endptr,10);
      if (strcmpi(M1,"")) { cprintf("%lu,",M11); }
      if (strcmpi(M2,"")) { cprintf("%lu,",M21); }
      if (strcmpi(M3,"")) { cprintf("%lu,",M31); }
      if (strcmpi(M4,"")) { cprintf("%lu,",M41); }
      if (strcmpi(M5,"")) { cprintf("%lu,",M51); }
      if (strcmpi(M6,"")) { cprintf("%lu,",M61); }
      if (strcmpi(M7,"")) { cprintf("%lu,",M71); }
      if (strcmpi(M8,"")) { cprintf("%lu,",M81); }
      if (strcmpi(M9,"")) { cprintf("%lu,",M91); }
      if (strcmpi(M10,"")) { cprintf("%lu",M101); }
      textcolor(RED); break;
    }
  }
  file.close();
}
//Function to Display Number of Copies of a Book Issued for a Given Book Code
int Book::NumberOfCopiesOfBookIssued(unsigned long tCode)
{ fstream file; int i,count = 0; unsigned long BookCode1; char *endptr;
  file.open("BOOKMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { BookCode1 = strtoul(BookCode,&endptr,10);
    if (BookCode1 == tCode)
    { if (strcmpi(M1,"")) { count++; }
      if (strcmpi(M2,"")) { count++; }
      if (strcmpi(M3,"")) { count++; }
      if (strcmpi(M4,"")) { count++; }
      if (strcmpi(M5,"")) { count++; }
      if (strcmpi(M6,"")) { count++; }
      if (strcmpi(M7,"")) { count++; }
      if (strcmpi(M8,"")) { count++; }
      if (strcmpi(M9,"")) { count++; }
      if (strcmpi(M10,"")) { count++; }
      break;
    }
  }
  file.close(); return count;
}
//Function to Display Heading for List of All Books
void Book::HeadingForListOfAllBooks(void)
{ clrscr(); textbackground(GREEN); textcolor(RED);
  gotoxy(34,1); cprintf("LIST OF BOOKS");
  gotoxy(34,2); cprintf("-------------");
  gotoxy(1,3); cprintf("--------------------------------------------------"
		       "------------------------------");
  gotoxy(1,4); cprintf("Book-Code  Book-Name                      Author  "
		       "                  Price Copies");
  gotoxy(1,5); cprintf("--------------------------------------------------"
		       "------------------------------");
}
//Function to Display List of All Books
void Book::List(void)
{ int row = 6,found = 0,flag = 0,i,count; char ch = 0,*endptr; fstream file;
  unsigned long M11,M21,M31,M41,M51,M61,M71,M81,M91,M101;
  HeadingForListOfAllBooks(); file.open("BOOKMSTR.DAT",ios::in);
  file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Book)))
  { flag = 0; found = 1; count = 0;
    gotoxy(1,row);  cout<<BookCode;
    gotoxy(12,row); cout<<Name;
    gotoxy(43,row); cout<<Author;
    gotoxy(69,row); cout<<atoi(Price);
    gotoxy(75,row); cout<<atoi(Copies);
    gotoxy(1,row+1); cprintf("Issued To:"); textcolor(WHITE);
    for (;;)
    { M11 = strtoul(M1,&endptr,10); M21 = strtoul(M2,&endptr,10);
      M31 = strtoul(M3,&endptr,10); M41 = strtoul(M4,&endptr,10);
      M51 = strtoul(M5,&endptr,10); M61 = strtoul(M6,&endptr,10);
      M71 = strtoul(M7,&endptr,10); M81 = strtoul(M8,&endptr,10);
      M91 = strtoul(M9,&endptr,10); M101 = strtoul(M10,&endptr,10);
      if (strcmpi(M1,"")) { cprintf("%lu,",M11); count++; }
      if (strcmpi(M2,"")) { cprintf("%lu,",M21); count++; }
      if (strcmpi(M3,"")) { cprintf("%lu,",M31); count++; }
      if (strcmpi(M4,"")) { cprintf("%lu,",M41); count++; }
      if (strcmpi(M5,"")) { cprintf("%lu,",M51); count++; }
      if (count == 5) { cprintf("..."); break; }
      if (strcmpi(M6,"")) { cprintf("%lu,",M61); count++; }
      if (count == 5) { cprintf("..."); break; }
      if (strcmpi(M7,"")) { cprintf("%lu,",M71); count++; }
      if (count == 5) { cprintf("..."); break; }
      if (strcmpi(M8,"")) { cprintf("%lu,",M81); count++; }
      if (count == 5) { cprintf("..."); break; }
      if (strcmpi(M9,"")) { cprintf("%lu,",M91); count++; }
      if (count == 5) { cprintf("..."); break; }
      if (strcmpi(M10,"")) { cprintf("%lu",M101); count++; }
      break;
    }
    textcolor(RED); gotoxy(70,row+1); cprintf("Avail:"); textcolor(WHITE+BLINK);
    cprintf("%d", atoi(Avail)); textbackground(GREEN); textcolor(RED);
    if (row == 20)
    { gotoxy(1,22); cprintf("---------------------------------------------"
			    "-----------------------------------");
      gotoxy(1,23); textcolor(WHITE);
      cprintf("Five Members to Whom Copies of the Book are Issued "
	      "are Listed. See Enquiry also." );
      textcolor(RED); gotoxy(1,25);
      cprintf("\7Press <Esc> to Quit or Any Other Key to Continue ");
      ch = getch(); if (ch == 27) break;
      HeadingForListOfAllBooks(); flag = 1; row = 6;
    } else row = row + 2;
  }
  file.close(); if (ch == 27) return;
  if (found)
  { gotoxy(1,row); cprintf("---------------------------------------------"
			    "-----------------------------------");
    gotoxy(1,row+1); textcolor(WHITE);
    cprintf("Five Members to Whom Copies of the Book are Issued "
	    "are Listed. See Enquiry also." ); textcolor(RED);
  }
  if (!found) { gotoxy(1,10); cprintf("Books Not Found"); }
  if (!flag)
  { gotoxy(1,25); cprintf("\7Press Any Key to Continue "); getche(); }
}
//Function to Return 0, If a Given Member Code is Not Found
int Member::MemberFound(unsigned long mCode)
{ int found = 0; fstream file; unsigned long MemberCode1; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  { MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode) { found = 1; break; }
  }
  file.close(); return found;
}
//Function to Return 0, If a Member has Not Issued Any Book
unsigned long Member::Issued(unsigned long mCode)
{ unsigned long MemberCode1; int missue = 0,i; fstream file; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  { MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode)
    { if (strcmpi(B1,"")) missue++;
      if (strcmpi(B2,"")) missue++;
      if (strcmpi(B3,"")) missue++;
      if (strcmpi(B4,"")) missue++;
      if (strcmpi(B5,"")) missue++;
      break;
    }
  }
  file.close(); return missue;
}
//Function to Calculate & Return Fine for a Given Member Code
int Member::Fine(unsigned long mCode, unsigned long bCode)
{ Date D; int d1,m1,y1,Days,t_fine,i; fstream file; struct date d;
  unsigned long MemberCode1,B11,B21,B31,B41,B51; char *endptr;
  getdate(&d); d1 = d.da_day; m1 = d.da_mon; y1 = d.da_year;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  { MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode)
    { for (;;)
      { B11 = strtoul(B1,&endptr,10); B21 = strtoul(B2,&endptr,10);
	B31 = strtoul(B3,&endptr,10); B41 = strtoul(B4,&endptr,10);
	B51 = strtoul(B5,&endptr,10);
	if (B11 == bCode) { i = 0; break; }
	if (B21 == bCode) { i = 1; break; }
	if (B31 == bCode) { i = 2; break; }
	if (B41 == bCode) { i = 3; break; }
	if (B51 == bCode) { i = 4; break; }
	break;
      }
      for (;;)
      { if (i==0) { Days=D.Diff(atoi(DD1),atoi(MM1),atoi(YY1),d1,m1,y1);break; }
	if (i==1) { Days=D.Diff(atoi(DD2),atoi(MM2),atoi(YY2),d1,m1,y1);break; }
	if (i==2) { Days=D.Diff(atoi(DD3),atoi(MM3),atoi(YY3),d1,m1,y1);break; }
	if (i==3) { Days=D.Diff(atoi(DD4),atoi(MM4),atoi(YY4),d1,m1,y1);break; }
	if (i==4) { Days=D.Diff(atoi(DD5),atoi(MM5),atoi(YY5),d1,m1,y1);break; }
	break;
      }
      t_fine = Days * 3; break;
    }
  }
  file.close(); return t_fine;
}
//Function to Return Last Member Code
unsigned long Member::LastMemberCode(void)
{ unsigned long mCode = 0; fstream file; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  mCode = strtoul(MemberCode,&endptr,10);
  file.close(); return mCode;
}
//Function to Return Member Name for a Given Member Code
char *Member::MemberName(unsigned long mCode)
{ char mName[21], *endptr; fstream file; unsigned long MemberCode1;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  { MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode) { strcpy(mName,Name); break; }
  }
  file.close(); return mName;
}
//Function to Delete Record of a Given Member Code
void Member::DeleteRecord(unsigned long mCode)
{ fstream file,temp; unsigned long MemberCode1; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Member)); if (file.eof()) break;
    MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 != mCode) temp.write((char *)this,sizeof(Member));
  }
  file.close(); temp.close();
  remove("MEMBMSTR.DAT"); rename("TEMPMSTR.DAT","MEMBMSTR.DAT");
}
//Function to Update Record of a Given Member Code
void Member::UpdateBook(unsigned long mCode,unsigned long tCode,
			int d1,int m1,int y1,char ch)
{ fstream file,temp; int i; char *endptr;
  unsigned long MemberCode1,B11,B21,B31,B41,B51;
  file.open("MEMBMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Member)); if (file.eof()) break;
    MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode)
    { if (ch == '3') //Issue
      { for (;;)
	{ if (!strcmpi(B1,""))
	  { ultoa(tCode,B1,10); itoa(d1,DD1,10); itoa(m1,MM1,10);
	    itoa(y1,YY1,10); break; }
	  if (!strcmpi(B2,""))
	  { ultoa(tCode,B2,10); itoa(d1,DD2,10); itoa(m1,MM2,10);
	    itoa(y1,YY2,10); break; }
	  if (!strcmpi(B3,""))
	  { ultoa(tCode,B3,10); itoa(d1,DD3,10); itoa(m1,MM3,10);
	    itoa(y1,YY3,10); break; }
	  if (!strcmpi(B4,""))
	  { ultoa(tCode,B4,10); itoa(d1,DD4,10); itoa(m1,MM4,10);
	    itoa(y1,YY4,10); break; }
	  if (!strcmpi(B5,""))
	  { ultoa(tCode,B5,10); itoa(d1,DD5,10); itoa(m1,MM5,10);
	    itoa(y1,YY5,10); break; }
	  break;
	}
      }
      if (ch == '4') //Return
      { for (;;)
	{ B11 = strtoul(B1,&endptr,10); B21 = strtoul(B2,&endptr,10);
	  B31 = strtoul(B3,&endptr,10); B41 = strtoul(B4,&endptr,10);
	  B51 = strtoul(B5,&endptr,10);
	  if (B11 == tCode)
	  { strcpy(B1,"");strcpy(DD1,"");strcpy(MM1,"");strcpy(YY1,"");break; }
	  if (B21 == tCode)
	  { strcpy(B2,"");strcpy(DD2,"");strcpy(MM2,"");strcpy(YY2,"");break; }
	  if (B31 == tCode)
	  { strcpy(B3,"");strcpy(DD3,"");strcpy(MM3,"");strcpy(YY3,"");break; }
	  if (B41 == tCode)
	  { strcpy(B4,"");strcpy(DD4,"");strcpy(MM4,"");strcpy(YY4,"");break; }
	  if (B51 == tCode)
	  { strcpy(B5,"");strcpy(DD5,"");strcpy(MM5,"");strcpy(YY5,"");break; }
	  break;
	}
      }
      temp.write((char *)this,sizeof(Member));
    } else temp.write((char *)this,sizeof(Member));
  }
  file.close(); temp.close();
  remove("MEMBMSTR.DAT"); rename("TEMPMSTR.DAT","MEMBMSTR.DAT");
}
//Function to Modify Record of a Given Member Code
void Member::Modify(unsigned long mCode,char mPhone[11],char mAddress[31])
{ fstream file,temp; int i; unsigned long MemberCode1; char *endptr;
  file.open("MEMBMSTR.DAT",ios::in); temp.open("TEMPMSTR.DAT",ios::out);
  file.seekg(0,ios::beg);
  while (!file.eof())
  { file.read((char *)this,sizeof(Member)); if (file.eof()) break;
    MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode)
    { strcpy(Phone,mPhone); strcpy(Address,mAddress);
      temp.write((char *)this,sizeof(Member));
    } else temp.write((char *)this,sizeof(Member));
  }
  file.close(); temp.close();
  remove("MEMBMSTR.DAT"); rename("TEMPMSTR.DAT","MEMBMSTR.DAT");
}
//Function to Add Record in Members Master File for a Given Member Code
void Member::AddMem(unsigned long mCode,char mName[21],char mAddress[31],
		    char mPhone[11])
{ int i; fstream file; file.open("MEMBMSTR.DAT",ios::app);
  ultoa(mCode,MemberCode,10); strcpy(Name,mName);
  strcpy(Address,mAddress); strcpy(Phone,mPhone);
  strcpy(DD1,""); strcpy(MM1,""); strcpy(YY1,"");
  strcpy(DD2,""); strcpy(MM2,""); strcpy(YY2,"");
  strcpy(DD3,""); strcpy(MM3,""); strcpy(YY3,"");
  strcpy(DD4,""); strcpy(MM4,""); strcpy(YY4,"");
  strcpy(DD5,""); strcpy(MM5,""); strcpy(YY5,"");
  strcpy(B1,""); strcpy(B2,""); strcpy(B3,""); strcpy(B4,""); strcpy(B5,"");
  file.write((char *)this,sizeof(Member)); file.close();
}
//Function to Display Record of a Given Member Code
int Member::Display(unsigned long mCode)
{ fstream file; int i,count = 0; char *endptr;
  unsigned long MemberCode1,B11,B21,B31,B41,B51;
  file.open("MEMBMSTR.DAT",ios::in); file.seekg(0,ios::beg);
  textbackground(GREEN); textcolor(RED);
  while (file.read((char *)this,sizeof(Member)))
  { MemberCode1 = strtoul(MemberCode,&endptr,10);
    if (MemberCode1 == mCode)
    { gotoxy(5,5);  cout<<"Member Code #"<<mCode;
      gotoxy(5,6);  cout<<"-----------------------";
      gotoxy(5,8);  cout<<"Name    : "<<Name;
      gotoxy(5,9);  cout<<"Phone   : "<<Phone;
      gotoxy(5,10); cout<<"Address : "<<Address;
      gotoxy(5,11); cout<<"Issued Book Codes : "; textcolor(WHITE);
      B11 = strtoul(B1,&endptr,10); B21 = strtoul(B2,&endptr,10);
      B31 = strtoul(B3,&endptr,10); B41 = strtoul(B4,&endptr,10);
      B51 = strtoul(B5,&endptr,10);
      if (strcmpi(B1,"")) { cprintf("%lu,",B11); count++; }
      if (strcmpi(B2,"")) { cprintf("%lu,",B21); count++; }
      if (strcmpi(B3,"")) { cprintf("%lu,",B31); count++; }
      if (strcmpi(B4,"")) { cprintf("%lu,",B41); count++; }
      if (strcmpi(B5,"")) { cprintf("%lu",B51); count++; }
      textcolor(RED); gotoxy(5,12); cout<<"Dates of Return : ";textcolor(WHITE);
      if (strcmpi(DD1,"")) cprintf("%d/%d/%d,",atoi(DD1),atoi(MM1),atoi(YY1));
      if (strcmpi(DD2,"")) cprintf("%d/%d/%d,",atoi(DD2),atoi(MM2),atoi(YY2));
      if (strcmpi(DD3,"")) cprintf("%d/%d/%d,",atoi(DD3),atoi(MM3),atoi(YY3));
      if (strcmpi(DD4,"")) cprintf("%d/%d/%d,",atoi(DD4),atoi(MM4),atoi(YY4));
      if (strcmpi(DD5,"")) cprintf("%d/%d/%d",atoi(DD5),atoi(MM5),atoi(YY5));
      textcolor(RED); break;
    }
  }
  file.close(); return count;
}
//Function to Display Heading for List of All Members
void Member::HeadingForListOfAllMembers(void)
{ clrscr(); textbackground(GREEN); textcolor(RED);
  gotoxy(34,1); cprintf("LIST OF MEMBERS");
  gotoxy(34,2); cprintf("---------------");
  gotoxy(1,3); cprintf("----------------------------------------------"
		       "----------------------------------");
  gotoxy(1,4); cprintf("Memb-Code    Member-Name            Phone     "
		       "    Address");
  gotoxy(1,5); cprintf("----------------------------------------------"
		       "----------------------------------");
}
//Function to Display List of All Members
void Member::List(void)
{ Book B; int row = 6,found = 0,flag = 0,i; char ch = 0,BookName[31],*endptr;
  unsigned long B11,B21,B31,B41,B51; fstream file;
  HeadingForListOfAllMembers(); file.open("MEMBMSTR.DAT",ios::in);
  file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Member)))
  { flag = 0; found = 1;
    gotoxy(1,row);  cout<<MemberCode;
    gotoxy(14,row); cout<<Name;
    gotoxy(37,row); cout<<Phone;
    gotoxy(51,row); cout<<Address;
    gotoxy(5,row+1); cout<<"Issued Book Codes : "; textcolor(WHITE);
    B11 = strtoul(B1,&endptr,10); B21 = strtoul(B2,&endptr,10);
    B31 = strtoul(B3,&endptr,10); B41 = strtoul(B4,&endptr,10);
    B51 = strtoul(B5,&endptr,10);
    if (strcmpi(B1,"")) { cprintf("%lu,",B11); }
    if (strcmpi(B2,"")) { cprintf("%lu,",B21); }
    if (strcmpi(B3,"")) { cprintf("%lu,",B31); }
    if (strcmpi(B4,"")) { cprintf("%lu,",B41); }
    if (strcmpi(B5,"")) { cprintf("%lu",B51); }
    textcolor(RED);gotoxy(5,row+2);cout<<"Dates of Return : ";textcolor(WHITE);
    if (strcmpi(DD1,"")) cprintf("%d/%d/%d,",atoi(DD1),atoi(MM1),atoi(YY1));
    if (strcmpi(DD2,"")) cprintf("%d/%d/%d,",atoi(DD2),atoi(MM2),atoi(YY2));
    if (strcmpi(DD3,"")) cprintf("%d/%d/%d,",atoi(DD3),atoi(MM3),atoi(YY3));
    if (strcmpi(DD4,"")) cprintf("%d/%d/%d,",atoi(DD4),atoi(MM4),atoi(YY4));
    if (strcmpi(DD5,"")) cprintf("%d/%d/%d",atoi(DD5),atoi(MM5),atoi(YY5));
    textcolor(RED);
    if (row == 21)
    { gotoxy(1,24); cprintf("----------------------------------------------"
			    "----------------------------------");
      gotoxy(1,25);
      cprintf("Press <Esc> to Quit or Any Other Key to Continue ");
      ch = getch(); if (ch == 27) break;
      HeadingForListOfAllMembers(); flag = 1; row = 6;
    } else row = row + 3;
  }
  file.close(); if (ch == 27) return;
  if (found)
  { gotoxy(1,row); cprintf("----------------------------------------------"
			   "----------------------------------");
  }
  if (!found) { gotoxy(1,10); cprintf("\7Members Not Found"); }
  if (!flag) { gotoxy(1,25); cprintf("Press Any Key to Continue "); getche(); }
}
//Function to Return 0, If a Given Transaction Code is Not Found
int Transaction::TransactionFound(unsigned long tCode)
{ int found = 0; unsigned long TransactionCode1; char *endptr; fstream file;
  file.open("TRANSACT.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Transaction)))
  { TransactionCode1 = strtoul(TransactionCode,&endptr,10);
    if (TransactionCode1 == tCode) { found = 1; break; }
  }
  file.close(); return found;
}
//Function to Return 0, If a Transaction Date is Not Found
int Transaction::TransactionDateFound(char t1Date[10])
{ int found = 0; fstream file;
  file.open("TRANSACT.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Transaction)))
  if (!strcmpi(TransactionDate,t1Date)) { found = 1; break; }
  file.close(); return found;
}
//Function to Return Last Transaction Code
unsigned long Transaction::LastTransactionCode(void)
{ unsigned long trCode = 0; char *endptr; fstream file;
  file.open("TRANSACT.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Transaction)))
  trCode = strtoul(TransactionCode,&endptr,10);
  file.close(); return trCode;
}
//Function to Add Record in Transaction File for a Given Transaction Code
void Transaction::AddTransaction(unsigned long trCode,char trDate[11],
	   char trType[3],unsigned long mCode,unsigned long bCode,int tCopies)
{ fstream file; file.open("TRANSACT.DAT",ios::app);
  ultoa(trCode,TransactionCode,10); strcpy(TransactionDate,trDate);
  strcpy(TransactionType,trType); ultoa(mCode,MemberCode,10);
  ultoa(bCode,BookCode,10); itoa(tCopies,Copies,10);
  file.write((char *)this,sizeof(Transaction)); file.close();
}
//Function to Display Record of a Given Transaction Code
void Transaction::Display(unsigned long tCode)
{ fstream file; unsigned long TransactionCode1; char *endptr;
  file.open("TRANSACT.DAT",ios::in); file.seekg(0,ios::beg);
  textbackground(GREEN); textcolor(RED);
  while (file.read((char *)this,sizeof(Transaction)))
  { TransactionCode1 = strtoul(TransactionCode,&endptr,10);
    if (TransactionCode1 == tCode)
    { gotoxy(5,5);  cout<<"Transaction Code # "<<tCode;
      gotoxy(5,6);  cout<<"------------------------";
      gotoxy(5,8);  cout<<"Transaction Date : "<<TransactionDate;
      gotoxy(5,9);  cout<<"Transaction Type : "<<TransactionType;
      gotoxy(5,10); cout<<"Member Code      : "<<MemberCode;
      gotoxy(5,11); cout<<"Book Code        : "<<BookCode;
      gotoxy(5,12); cout<<"Number of Copies : "<<atoi(Copies);
      gotoxy(5,14); cout<<"Description of Transaction Types : ";
      textcolor(WHITE);
      gotoxy(5,16); cprintf("AB-Append Book,AM-Append Member,IB -Issue Book,"
			    "RB -Return Book,");
      gotoxy(5,17); cprintf("MB-Modify Book,MM-Modify Member,DB-Delete Book,"
			    "DM-Delete Member");
      textcolor(RED); break;
    }
  }
  file.close();
}
//Function to Display Heading for List of All Transactions
void Transaction::HeadingForListOfAllTransactions(void)
{ clrscr(); textbackground(GREEN); textcolor(RED);
  gotoxy(31,1); cprintf("LIST OF TRANSACTIONS"); textcolor(WHITE);
  gotoxy(8,2); cprintf("(AB-Append Book,AM-Append Member,IB -Issue Book,"
		       "RB -Return Book,)");
  gotoxy(8,3); cprintf("(MB-Modify Book,MM-Modify Member,DB-Delete Book,"
		       "DM-Delete Member)"); textcolor(RED);
  gotoxy(13,4);
  cprintf("-------------------------------------------------------");
  gotoxy(13,5);
  cprintf("Trans-Code Trans-Date Type Memb-Code  Book-Code  Copies");
  gotoxy(13,6);
  cprintf("-------------------------------------------------------");
}
//Function to Display List of All Transactions
void Transaction::List(void)
{ int row = 7,found = 0,flag = 0; char ch = 0; fstream file;
  HeadingForListOfAllTransactions();
  file.open("TRANSACT.DAT",ios::in); file.seekg(0,ios::beg);
  while (file.read((char *)this,sizeof(Transaction)))
  { flag = 0; found = 1;
    gotoxy(13,row); cout<<TransactionCode;
    gotoxy(24,row); cout<<TransactionDate;
    gotoxy(35,row); cout<<TransactionType;
    gotoxy(40,row); cout<<MemberCode;
    gotoxy(51,row); cout<<BookCode;
    gotoxy(62,row); cout<<atoi(Copies);
    if (row == 23)
    { gotoxy(13,24);
      cprintf("-------------------------------------------------------");
      gotoxy(13,25);
      cprintf("Press <Esc> to Quit or Any Other Key to Continue ");
      ch = getch(); if (ch == 27) break;
      HeadingForListOfAllTransactions(); flag = 1; row = 7;
    } else row = row + 1;
  }
  file.close(); if (ch == 27) return;
  if (found)
  { gotoxy(13,row);
    cprintf("-------------------------------------------------------");
  }
  if (!found) { gotoxy(13,13); cprintf("\7Transactions Not Found"); }
  if (!flag) { gotoxy(13,25); cprintf("Press Any Key to Continue "); getche(); }
}
//Function to Return Transaction Date for a Given Transaction
char *Transaction::GetTransactionDate(void)
{ int d1,m1,y1; char trDate[11],string[10]; struct date d;
  getdate(&d); d1 = d.da_day; m1 = d.da_mon; y1 = d.da_year;
  strcpy(trDate,itoa(d1,string,10)); strcat(trDate,"/");
  strcat(trDate,itoa(m1,string,10)); strcat(trDate,"/");
  strcat(trDate,itoa(y1,string,10)); return trDate;
}
//Function to Test Data of Type char[11] for a Given Numeric Input
int Working::NumericTest(char t[11])
{ int valid,found1,i,j;
  valid = 1;
  if (strlen(t) > 0)
  { for (i = 0; i <= strlen(t) - 1; i++)
    { found1 = 0;
      for (j = '0'; j <= '9'; j++)
      if (t[i] == j) { found1 = 1; break; }
      if (found1 == 0) break;
    }
    if (found1 == 0)
    { valid = 0; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Correctly(Non Numeric Input)..."
	    "Hit Any Key to Continue "; getch();
    }
  }
  return valid;
}
//Function to Give Data for Adding a Record in Books Master File
void Working::AddBook(void)
{ int tCopies,tAvail,tPrice = 0,found = 0,valid = 0,tc;
  static char tName[31],tAuthor[26];
  char ch,ch1,ch2,t[11],t1[6],tType[3],trDate[11],*endptr;
  unsigned long tCode,mCode,trCode; trCode = LastTransactionCode(); trCode++;
  strcpy(trDate,GetTransactionDate());
  do
  { textbackground(GREEN); textcolor(RED);
    clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
    gotoxy(31,3); cout<<"ADDITION OF THE BOOK";
    gotoxy(31,4); cout<<"--------------------";
    do
    { gotoxy(5,25); clreol();
      cout<<"\7Please Enter Code Number(1...4294967295) of Book or Press Enter to Quit";
      gotoxy(5,5); clreol(); cout<<"Code No. : "; fflush(stdin); gets(t);
      valid = NumericTest(t);
    } while (!valid);
    tCode = strtoul(t,&endptr,10); if (tCode == 0) return;
    gotoxy(5,8);  cout<<"Book Name     :";
    gotoxy(5,11); cout<<"Authors Names :";
    gotoxy(5,14); cout<<"Price(Rs.)    :";
    gotoxy(5,17); cout<<"Copies        :";
    if (BookFound(tCode))
    { found = 1;
      strcpy(tName,BookName(tCode)); strcpy(tAuthor,AuthorName(tCode));
      gotoxy(21,8);  cout<<tName;
      gotoxy(21,11); cout<<tAuthor;
      gotoxy(21,14); cout<<BookPrice(tCode);
      gotoxy(21,17); cout<<NoOfCopies(tCode);
    }
    valid = 0;
    while (!valid && !found)
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Name of the Book(Max. 30 Characters)";
      gotoxy(21,8); cout<<"123456789012345678901234567890";
      textcolor(BLUE); gotoxy(21,9); clreol(); fflush(stdin); gets(tName);
      textcolor(RED); strupr(tName); if (tName[0] == '0') return;
      if (strlen(tName) < 1 || strlen(tName) > 30)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...30 Characters)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
    valid = 0;
    while (!valid && !found)
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter the Authors Names(Max. 25 Characters)";
      gotoxy(21,11); cout<<"1234567890123456789012345";
      textcolor(BLUE); gotoxy(21,12); clreol(); fflush(stdin); gets(tAuthor);
      textcolor(RED); strupr(tAuthor); if (tAuthor[0] == '0') return;
      if (strlen(tAuthor) < 1 || strlen(tAuthor) > 25)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...25 Characters)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
    valid = 0;
    while (!valid && !found)
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Price of the Book(Max. Rs. 32766)";
      gotoxy(21,14); cout<<"12345";
      textcolor(BLUE); gotoxy(21,15); clreol(); fflush(stdin); gets(t1);
      textcolor(RED); tPrice = atoi(t1); if (t1[0] == '0') return;
      valid = NumericTest(t1); if (valid == 0) continue;
      if ((tPrice < 1) || (tPrice > 32766))
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...32766)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
    valid = 0;
    while (!valid && !found)
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Number of Copies of the Book to be Added(Max. 100)";
      gotoxy(21,17); cout<<"123";
      textcolor(BLUE); gotoxy(21,18); clreol(); fflush(stdin); gets(t1);
      textcolor(RED); tCopies = tc = atoi(t1); if (t1[0] == '0') return;
      valid = NumericTest(t1); if (valid == 0) continue;
      if (tCopies < 1 || tCopies > 100)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...100)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
    valid = 0;
    while (!valid && found)
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Further Copies of the Book to be Added(Max. 100)";
      gotoxy(5,19); cout<<"Further Copies : 123";
      textcolor(BLUE); gotoxy(22,20); clreol(); fflush(stdin); gets(t1);
      textcolor(RED); tCopies = tc = atoi(t1); if (t1[0] == '0') return;
      valid = NumericTest(t1); if (valid == 0) continue;
      if (tCopies < 1 || tCopies > 100)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...100)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
    if (found)
    { tAvail = Available(tCode) + tCopies;
      tCopies = NoOfCopies(tCode) + tCopies;
    } else tAvail = tCopies;
    gotoxy(5,25); clreol();
    do
    { gotoxy(5,21); clreol(); cout<<"Do You Want to Save ? (Y/N) ";
      ch = toupper(getche());
    } while (ch != 'Y' && ch != 'N');
    if (ch == 'Y')
    if (found)
    { mCode = 0; strcpy(tType,"AB");
      AddTransaction(trCode,trDate,tType,mCode,tCode,tc);
      ch2 = '0'; UpdateCopies(tCode,tCopies,tAvail,mCode,ch2);
    } else
    { mCode = 0; strcpy(tType,"AB");
      AddTransaction(trCode,trDate,tType,mCode,tCode,tc);
      AddNewBook(tCode,tName,tAuthor,tPrice,tCopies,tAvail);
    }
    do
    { gotoxy(5,23); clreol(); cout<<"Do You Want to Add More ? (Y/N) ";
      ch1 = toupper(getche());
    } while (ch1 != 'Y' && ch1 != 'N');
    if ((ch == 'Y') && (ch1 == 'Y')) trCode++;
  } while (ch1 == 'Y');
}
//Function to Give Data for Adding a Record in Members Master File
void Working::AddMember(void)
{ unsigned long mCode,bCode,trCode; int valid = 0,tCopies,i,j,found;
  static char mName[21],mPhone[11],mAddress[31];char ch,ch1,tType[3],trDate[11];
  char *ch2; mCode=LastMemberCode(); mCode++; trCode = LastTransactionCode();
  trCode++; strcpy(trDate, GetTransactionDate());
  do
  { textbackground(GREEN); textcolor(RED);
    clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
    gotoxy(28,3); cout<<"ADDITION OF THE MEMBER";
    gotoxy(28,4); cout<<"----------------------";
    gotoxy(5,7);  cout<<"Member Code #"<<mCode;
    gotoxy(5,8);  cout<<"-----------------";
    gotoxy(5,10); cout<<"Name    :";
    gotoxy(5,13); cout<<"Phone   :";
    gotoxy(5,16); cout<<"Address :";
    do
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Name of the Member(Max. 20 Characters)";
      gotoxy(15,10); cout<<"12345678901234567890";
      textcolor(BLUE); gotoxy(15,11); clreol(); fflush(stdin); gets(mName);
      textcolor(RED); strupr(mName); if (mName[0] == '0') return;
      if (strlen(mName) < 1 || strlen(mName) > 20)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...20 Characters)..."
	      "Hit Any Key to Continue "; getch();
      }
    } while (!valid);
    do
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Pl. Enter Phone Number(Max. 10 Digits,Not Starting with 0)/"
	    "<Enter> for None";
      gotoxy(15,13); cout<<"1234567890";
      textcolor(BLUE); gotoxy(15,14); clreol(); fflush(stdin); gets(mPhone);
      textcolor(RED); if (mPhone[0] == '0') return;
      valid = NumericTest(mPhone); if (valid == 0) continue;
      if ((strlen(mPhone) < 7 && strlen(mPhone) > 0) || (strlen(mPhone) > 10))
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(7 <= Digits) <= 10)..."
	      "Hit Any Key to Continue "; getch();
      }
    } while (!valid);
    if (strlen(mPhone) == 0) strcpy(mPhone,"-");
    gotoxy(5,25); clreol();
    do
    { valid = 1; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Address of the Member(Max. 30 Characters)";
      gotoxy(15,16); cout<<"123456789012345678901234567890";
      textcolor(BLUE); gotoxy(15,17); clreol(); fflush(stdin); gets(mAddress);
      textcolor(RED); strupr(mAddress); if (mAddress[0] == '0') return;
      if (strlen(mAddress) < 1 || strlen(mAddress) > 30)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Range 1...30 Characters)..."
	      "Hit Any Key to Continue "; getch();
      }
    } while (!valid);
    gotoxy(5,25); clreol();
    do
    { gotoxy(5,20); clreol(); cout<<"Do You Want to Save ? (Y/N) ";
      ch = toupper(getche()); if (ch == '0') return;
    } while (ch != 'Y' && ch != 'N');
    if (ch == 'Y')
    { bCode = 0; strcpy(tType,"AM"); tCopies = 0;
      AddTransaction(trCode,trDate,tType,mCode,bCode,tCopies);
      AddMem(mCode,mName,mAddress,mPhone);
    }
    do
    { gotoxy(5,23); clreol(); cout<<"Do You Want to Add More ? (Y/N) ";
      ch1 = toupper(getche()); if (ch1 == '0') return;
    } while (ch1 != 'Y' && ch1 != 'N');
    if ((ch == 'Y') && (ch1 == 'Y')) { trCode++; mCode++; }
  } while (ch1 == 'Y');
}
//Function to Issue a Book
void Working::IssueBook(void)
{ Book B; Member M; Date D; struct date d; unsigned long trCode,tCode=0,mCode=0;
  int valid,d1,m1,y1,tCopies,tAvail,tc = 1,NumIssued,NumberOfCopiesIssued;
  char tType[3],trDate[11],BookName1[31],MemberName1[21],t1Code[31],ch,*endptr;
  trCode=LastTransactionCode(); trCode++; strcpy(trDate,GetTransactionDate());
  getdate(&d); d1 = d.da_day; m1 = d.da_mon; y1 = d.da_year;
  textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,2); cout<<"Date : "<<d1<<"/"<<m1<<"/"<<y1;
      gotoxy(5,5); cout<<"\7Please Enter Code or Name of the Book to be Issued";
      gotoxy(5,6); cout<<" or ";
      gotoxy(5,7); cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) B.List(); else break;
    }
    tCode = strtoul(t1Code,&endptr,10);
    if ((tCode==0 && !BookNameFound(t1Code))||(tCode!=0 && !BookFound(tCode)))
    { valid = 0; gotoxy(5,10); cout<<"\7Book Not Found";
      gotoxy(5,13); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  if (tCode == 0) tCode = BookCodeOf(t1Code);
  strcpy(BookName1,BookName(tCode));
  NumberOfCopiesIssued = NumberOfCopiesOfBookIssued(tCode);
  if (NumberOfCopiesIssued == 10)
  { valid = 0; gotoxy(5,10); cout<<"\7Number Of Copies Of Book Issued = 10";
    gotoxy(5,13); cout<<"More Copies Can't be Issued. Hit Any Key to Continue ";
    getch(); return;
  }
  gotoxy(5,10); cout<<"Book Code : "<<tCode;
  gotoxy(5,11); cout<<"Book Name : "<<BookName1;
  gotoxy(5,14); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
  ch = getch(); if (ch == 27) return;
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,2); cout<<"Date : "<<d1<<"/"<<m1<<"/"<<y1;
      gotoxy(5,5); cout<<"Book Name : "<<BookName1;
      gotoxy(5,7); cout<<"\7Please Enter Code Number of the Member";
      gotoxy(5,8); cout<<" or ";
      gotoxy(5,9); cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) M.List(); else break;
    }
    mCode = strtoul(t1Code,&endptr,10);
    if (mCode == 0)
    { valid = 0; gotoxy(5,25);
      cout<<"\7Please Enter Correctly...Hit Any Key to Continue "; getch();
    }
    if (!MemberFound(mCode) && valid)
    { valid = 0; gotoxy(5,12); cout<<"\7Member Not Found";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
    NumIssued = Issued(mCode);
    if ((NumIssued == 5) && valid)
    { valid = 0; gotoxy(5,12);
      cout<<"\7Sorry!! You Cannot Issue More than Five Books";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  strcpy(MemberName1,MemberName(mCode));
  gotoxy(5,12); cout<<"Member Code : "<<mCode;
  gotoxy(5,13); cout<<"Member Name : "<<MemberName1;
  gotoxy(5,16); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
  ch = getch(); if (ch == 27) return;
  tCopies = NoOfCopies(tCode); ch = '3'; strcpy(MemberName1,MemberName(mCode));
  tAvail = Available(tCode) - 1; UpdateCopies(tCode,tCopies,tAvail,mCode,ch);
  D.ExtendDate(d1,m1,y1,15); d1 = D.Day; m1 = D.Mon; y1 = D.Year;
  UpdateBook(mCode,tCode,d1,m1,y1,ch); strcpy(tType,"IB");
  AddTransaction(trCode,trDate,tType,mCode,tCode,tc);
  gotoxy(5,19); cout<<"\7Book is Issued to : "<<MemberName1;
  gotoxy(5,22); cout<<"Date of Return : "<<d1<<"/"<<m1<<"/"<<y1;
  gotoxy(5,25); cout<<"Hit Any Key to Continue "; getch();
}
//Function to Return a Book
void Working::ReturnBook(void)
{ Member M; Book B; struct date d; unsigned long tCode,mCode=0,trCode;
  char t1Code[31],ch,tType[3],trDate[11],*endptr,BookName1[31],MemberName1[21];
  int valid,d1,m1,y1,tCopies,tAvail,f,tc=1,NumIssued;
  trCode=LastTransactionCode(); trCode++; strcpy(trDate,GetTransactionDate());
  getdate(&d); d1 = d.da_day; m1 = d.da_mon; y1 = d.da_year;
  textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,2); cout<<"Date : "<<d1<<"/"<<m1<<"/"<<y1;
      gotoxy(5,5); cout<<"\7Please Enter Code or Name of the Book to be Returned";
      gotoxy(5,6); cout<<" or ";
      gotoxy(5,7); cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) B.List(); else break;
    }
    tCode = strtoul(t1Code,&endptr,10);
    if ((tCode==0 && !BookNameFound(t1Code))||(tCode!=0 && !BookFound(tCode)))
    { valid = 0; gotoxy(5,10); cout<<"\7Book Not Found";
      gotoxy(5,13); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  if (tCode == 0) tCode = BookCodeOf(t1Code); strcpy(BookName1,BookName(tCode));
  gotoxy(5,10); cout<<"Book Code : "<<tCode;
  gotoxy(5,11); cout<<"Book Name : "<<BookName1;
  gotoxy(5,14); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
  ch = getch(); if (ch == 27) return;
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,2); cout<<"Date : "<<d1<<"/"<<m1<<"/"<<y1;
      gotoxy(5,4); cout<<"Book Name : "<<BookName1;
      gotoxy(5,6);
      cout<<"\7Please Enter Code of the Member who Wants to Return Book";
      gotoxy(5,7); cout<<" or ";
      gotoxy(5,8); cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) M.List(); else break;
    }
    mCode = strtoul(t1Code,&endptr,10);
    if (mCode == 0)
    { valid = 0; gotoxy(5,25);
      cout<<"\7Please Enter Correctly...Hit Any Key to Continue "; getch();
    }
    if (!MemberFound(mCode) && valid)
    { valid = 0; gotoxy(5,11); cout<<"\7Member Not Found";
      gotoxy(5,14); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
    NumIssued = Issued(mCode);
    if ((NumIssued == 0) && valid)
    { valid = 0; gotoxy(5,11); cout<<"\7Member has No Book to Return";
      gotoxy(5,14); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  strcpy(MemberName1,MemberName(mCode));
  gotoxy(5,10); cout<<"Member Code : "<<mCode;
  gotoxy(5,11); cout<<"Member Name : "<<MemberName1;
  gotoxy(5,14); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
  ch = getch(); if (ch == 27) return;
  tCopies = NoOfCopies(tCode); tAvail = Available(tCode)+1;
  f = Fine(mCode,tCode);
  if (f != 0)
  { gotoxy(5,17); cout<<"You Have to Pay a Fine of Rs. "<<f;
    gotoxy(5,19); cout<<"Please Do not Delay the Return of Book Again";
    gotoxy(5,21); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
    ch = getch(); if (ch == 27) return;
  }
  ch = '4'; UpdateCopies(tCode,tCopies,tAvail,mCode,ch);
  UpdateBook(mCode,tCode,0,0,0,ch);
  strcpy(tType,"RB"); AddTransaction(trCode,trDate,tType,mCode,tCode,tc);
  gotoxy(5,23); cout<<"\7Book is Returned from : "<<MemberName1;
  gotoxy(5,25); cout<<"Hit Any Key to Continue "; getch();
}
//Function to Give Data for Modifing a Book Record
void Working::ModifyBook(void)
{ Book B; char t1Code[31],*t1,ch,tType[3],trDate[11],*endptr;
  static char tAuthor[26]; int tPrice=0,valid,tCopies;
  unsigned long tCode=0,mCode,trCode;
  trCode = LastTransactionCode(); trCode++; strcpy(trDate,GetTransactionDate());
  textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5);cout<<"\7Please Enter Code or Name of the Book to be Modified";
      gotoxy(5,6);cout<<" or ";
      gotoxy(5,7);cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) B.List(); else break;
    }
    tCode = strtoul(t1Code,&endptr,10);
    if ((tCode==0 && !BookNameFound(t1Code))||(tCode!=0 && !BookFound(tCode)))
    { valid = 0; gotoxy(5,10); cout<<"\7Book Not Found";
      gotoxy(5,13); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  if (tCode == 0) tCode = BookCodeOf(t1Code);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Book::Display(tCode);
  do
  { gotoxy(5,14); clreol();
    cout<<"Do You Want to Modify this Book ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return;
  gotoxy(5,16); cout<<"Authors Names :";
  gotoxy(5,19); cout<<"Price(Rs.)    :";
  do
  { valid = 1; gotoxy(5,25); clreol();
    cout<<"\7Please Enter the Authors Names(Max. 25 Characters)";
    gotoxy(21,16); cout<<"1234567890123456789012345";
    textcolor(BLUE); gotoxy(21,17); clreol(); fflush(stdin); gets(tAuthor);
    textcolor(RED); strupr(tAuthor); if (tAuthor[0] == '0') return;
    if ((strlen(tAuthor) > 25) || (strlen(tAuthor) == 0))
    { valid = 0; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Correctly(Range 1...25 Characters)..."
	    "Hit Any Key to Continue "; getch();
    }
  } while (!valid);
  do
  { valid = 1; gotoxy(5,25); clreol();
    cout<<"\7Please Enter Price of the Book(Max. 32766)";
    gotoxy(21,19); cout<<"12345";
    textcolor(BLUE); gotoxy(21,20); clreol(); fflush(stdin); gets(t1);
    textcolor(RED); tPrice = atoi(t1); if (t1[0] == '0') return;
    valid = NumericTest(t1); if (valid == 0) continue;
    if ((tPrice < 1 || tPrice > 32766) && (t1[0] != '\0') || (strlen(t1) == 0))
    { valid = 0; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Correctly(Range 1...32766)..."
	    "Hit Any Key to Continue "; getch();
    }
  } while (!valid);
  gotoxy(5,25); clreol();
  do
  { gotoxy(5,22); clreol(); cout<<"Do You Want to Save Changes ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return; Book::Modify(tCode,tAuthor,tPrice);
  mCode = 0; strcpy(tType,"MB"); tCopies = NoOfCopies(tCode);
  AddTransaction(trCode,trDate,tType,mCode,tCode,tCopies);
  gotoxy(5,25); cout<<"\7Book Modified...Hit Any Key to Continue "; getch();
}
//Function to Give Data for Modifing a Member Record
void Working::ModifyMember(void)
{ Member M; char m1Code[11],ch,tType[3],trDate[11],*endptr;
  static char mPhone[11],mAddress[31]; int valid,i,j,found,tCopies;
  unsigned long mCode=0,trCode,tCode; trCode = LastTransactionCode(); trCode++;
  strcpy(trDate,GetTransactionDate()); textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5);cout<<"\7Please Enter Code Number of the Member to be Modified";
      gotoxy(5,6);cout<<" or ";
      gotoxy(5,7);cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(m1Code); mCode = strtoul(m1Code,&endptr,10);
      if (m1Code[0] == '0') return;
      if (strlen(m1Code) == 0) M.List(); else break;
    }
    if (mCode == 0)
    { valid = 0; gotoxy(5,25);
      cout<<"\7Please Enter Correctly...Hit Any Key to Continue "; getch();
    }
    if (valid && !MemberFound(mCode))
    { valid = 0; gotoxy(5,11); cout<<"\7Member Not Found";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
  tCode = Member::Display(mCode);
  do
  { gotoxy(5,14); clreol();
    cout<<"Do You Want to Modify this Member ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return;
  gotoxy(5,16); cout<<"Phone   :";
  gotoxy(5,19); cout<<"Address :";
  do
  { valid = 1; gotoxy(5,25); clreol();
    cout<<"\7Please Enter the Phone Number(Max. 10 Digits, Not Starting with 0)";
    gotoxy(15,16); cout<<"1234567890";
    textcolor(BLUE); gotoxy(15,17); clreol(); fflush(stdin); gets(mPhone);
    textcolor(RED); if (mPhone[0] == '0') return;
    valid = NumericTest(mPhone); if (valid == 0) continue;
    if ((strlen(mPhone) < 7 && strlen(mPhone) > 0) || (strlen(mPhone) > 10)
	|| (strlen(mPhone) == 0))
    { valid = 0; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Correctly(7 <= Digits) <= 10)..."
	    "Hit Any Key to Continue "; getch();
    }
    if (strlen(mPhone) > 0)
    { for (i = 0; i <= strlen(mPhone) - 1; i++)
      { found = 0;
	for (j = '0'; j <= '9'; j++)
	if (mPhone[i] == j) { found = 1; break; }
	if (found == 0) break;
      }
      if (found == 0)
      { valid = 0; gotoxy(5,25); clreol();
	cout<<"\7Please Enter Correctly(Non Numeric Input)..."
	      "Hit Any Key to Continue "; getch();
      }
    }
  } while (!valid);
  do
  { valid = 1; gotoxy(5,25); clreol();
    cout<<"\7Please Enter Address of the Member(Max. 30 Chars)";
    gotoxy(15,19); cout<<"123456789012345678901234567890";
    textcolor(BLUE); gotoxy(15,20); clreol(); fflush(stdin); gets(mAddress);
    textcolor(RED); strupr(mAddress); if (mAddress[0] == '0') return;
    if ((strlen(mAddress) == 0) || (strlen(mAddress) > 30))
    { valid = 0; gotoxy(5,25); clreol();
      cout<<"\7Please Enter Correctly(Range 1...30 Characters)..."
	    "Hit Any Key to Continue "; getch();
    }
  } while (!valid);
  gotoxy(5,25); clreol();
  do
  { gotoxy(5,22); clreol(); cout<<"Do You Want to Save Changes ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return; Member::Modify(mCode,mPhone,mAddress);
  strcpy(tType,"MM"); if (tCode == 0) tCopies = 0; else tCopies = tCode;
  tCode = 0; AddTransaction(trCode,trDate,tType,mCode,tCode,tCopies);
  gotoxy(5,25); cout<<"\7Member Modified...Hit Any Key to Continue "; getch();
}
//Function to Give Book Code for Deleting a Book Record
void Working::DeleteBook(void)
{ Book B; char t1Code[31],tName[31],tAuthor[26],ch,tType[3],trDate[11],*endptr;
  unsigned long tCode = 0,mCode,trCode; int valid,tAvail,tCopies;
  trCode = LastTransactionCode(); trCode++; strcpy(trDate,GetTransactionDate());
  textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5); cout<<"\7Please Enter Code or Name of the Book to be Deleted";
      gotoxy(5,6); cout<<" or ";
      gotoxy(5,7); cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) B.List(); else break;
    }
    tCode = strtoul(t1Code,&endptr,10);
    if ((tCode==0 && !BookNameFound(t1Code))||(tCode!=0 && !BookFound(tCode)))
    { valid = 0; gotoxy(5,10); cout<<"\7Book Not Found";
      gotoxy(5,13); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  if (tCode == 0) tCode = BookCodeOf(t1Code);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Book::Display(tCode);
  do
  { gotoxy(5,14); clreol(); cout<<"Do You Want to Delete this Book ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return;
  tAvail = Available(tCode); tCopies = NoOfCopies(tCode);
  if (tAvail != tCopies)
  { gotoxy(5,16); cout<<"\7Book Cannot be Deleted. This Book is Issued. "
			"Hit Any Key to Continue "; getch();
    return;
  }
  Book::DeleteRecord(tCode); strcpy(tType,"DB"); mCode = 0;
  AddTransaction(trCode,trDate,tType,mCode,tCode,tCopies);
  gotoxy(5,23); cout<<"\7Book Deleted...Hit Any Key to Continue "; getch();
}
//Function to Give Member Code for Deleting a Member Record
void Working::DeleteMember(void)
{ Member M; char m1Code[11],mName[21],mPhone[11],mAddress[31],ch;
  unsigned long mCode = 0,tCode = 0,trCode; int valid,tCopies = 0,NumIssued;
  char tType[3],trDate[11],*endptr; trCode = LastTransactionCode(); trCode++;
  strcpy(trDate,GetTransactionDate()); textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5);cout<<"\7Please Enter Code Number of the Member to be Deleted";
      gotoxy(5,6);cout<<" or ";
      gotoxy(5,7);cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(m1Code); mCode = strtoul(m1Code,&endptr,10);
      if (m1Code[0] == '0') return;
      if (strlen(m1Code) == 0) M.List(); else break;
    }
    if (mCode == 0)
    { valid = 0; gotoxy(5,25);
      cout<<"\7Please Enter Correctly...Hit Any Key to Continue "; getch();
    }
    if (valid && !MemberFound(mCode))
    { valid = 0; gotoxy(5,11); cout<<"\7Member Not Found";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Member::Display(mCode);
  do
  { gotoxy(5,15); clreol(); cout<<"Do You Want to Delete this Member ? (Y/N) ";
    ch = toupper(getche()); if (ch == '0') return;
  } while (ch != 'Y' && ch != 'N');
  if (ch == 'N') return;
  NumIssued = Issued(mCode);
  if (NumIssued != 0)
  { gotoxy(5,18); cprintf("\7Member Cannot be Deleted. Member has %d Book(s). "
			  "Hit Any Key to Continue ",NumIssued);
    getch(); return;
  }
  Member::DeleteRecord(mCode); gotoxy(5,23);
  strcpy(tType,"DM"); AddTransaction(trCode,trDate,tType,mCode,tCode,tCopies);
  cout<<"\7Member Deleted...Hit Any Key to Continue "; getch();
}
//Function to Enquire Data of a Book Record
void Working::EnquireBook(void)
{ Book B; char t1Code[31],tName[31],tAuthor[26],*t1,ch,*endptr;
  unsigned long tCode = 0; int valid; textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5);cout<<"\7Please Enter Code or Name of the Book to be Enquired";
      gotoxy(5,6);cout<<" or ";
      gotoxy(5,7);cout<<"Press <Enter> for Help...";
      fflush(stdin); gets(t1Code); if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) B.List(); else break;
    }
    tCode = strtoul(t1Code,&endptr,10);
    if ((tCode==0 && !BookNameFound(t1Code))||(tCode!=0 && !BookFound(tCode)))
    { valid = 0; gotoxy(5,10); cout<<"\7Book Not Found";
      gotoxy(5,13); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  if (tCode == 0) tCode = BookCodeOf(t1Code);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Book::Display(tCode);
  gotoxy(5,25); cout<<"\7Hit Any Key to Continue "; getch();
}
//Function to Enquire Data of a Member Record
void Working::EnquireMember(void)
{ Member M; char m1Code[21],mName[21],mPhone[11],mAddress[31],ch,*endptr;
  unsigned long mCode = 0; int valid; textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5);cout<<"\7Please Enter Code or Name of the Member to be Enquired";
      gotoxy(5,6);cout<<" or ";
      gotoxy(5,7);cout<<"Press <Enter> for help...";
      fflush(stdin); gets(m1Code); mCode = strtoul(m1Code,&endptr,10);
      if (m1Code[0] == '0') return;
      if (strlen(m1Code) == 0) M.List(); else break;
    }
    if (mCode == 0) mCode = MemberCodeOf(m1Code);
    if (mCode == 0)
    { valid = 0; gotoxy(5,25);
      cout<<"\7Member Not Found. Please Enter Correctly...Hit Any Key to Continue ";
      getch(); continue;
    }
    if (!MemberFound(mCode))
    { valid = 0; gotoxy(5,11); cout<<"\7Member Not Found";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Member::Display(mCode);
  gotoxy(5,25); cout<<"\7Hit Any Key to Continue "; getch();
}
//Function to Enquire Data of a Transaction Record
void Working::EnquireTransaction(void)
{ Transaction T; char t1Code[11],ch,*endptr;
  unsigned long tCode = 0; int valid; textbackground(GREEN); textcolor(RED);
  do
  { valid = 1;
    while (1)
    { clrscr(); gotoxy(72,1); cout<<"<0>=Quit";
      gotoxy(5,5); cout<<"\7Please Enter Code Number of the Transaction "
			 "to be Enquired";
      gotoxy(5,6); cout<<" or ";
      gotoxy(5,7); cout<<"Press <Enter> for help...";
      fflush(stdin); gets(t1Code); tCode = strtoul(t1Code,&endptr,10);
      if (t1Code[0] == '0') return;
      if (strlen(t1Code) == 0) T.List(); else break;
    }
    if (tCode == 0)
    { valid = 0; gotoxy(5,25); cout<<"\7Please Enter Correctly...Hit Any Key to Continue "; getch();
    }
    if (valid && !TransactionFound(tCode))
    { valid = 0; gotoxy(5,11); cout<<"\7Transaction Not Found";
      gotoxy(5,15); cout<<"Press <Esc> to Quit or Any Other Key to Continue ";
      ch = getch(); if (ch == 27) return;
    }
  } while (!valid);
  clrscr(); gotoxy(72,1); cout<<"<0>=Quit"; Transaction::Display(tCode);
  gotoxy(5,25); cout<<"\7Hit Any Key to Continue "; getch();
}
//Main Function to Call Introduction and Main Menu
void main()
{ Menu Menu1;
  Menu1.Introduction();
  Menu1.MainMenu();

}