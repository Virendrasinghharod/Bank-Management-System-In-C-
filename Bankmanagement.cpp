#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;



class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();
	void show_account() const;
	void modify();
	void dep(int);
	void draw(int);
	void report() const;
	int retacno() const;
	int retdeposit() const;
	char rettype() const;
};

void account::create_account()
{
	system("CLS");
	cout<<"Enter the Account No. : ";
	cin>>acno;
	cout<<"Enter the Name of the Account holder : \n";
	cin.ignore();
	cin.getline(name,50);
	cout<<"Enter Type of the Account (C/S) : \n";
	cin>>type;
	type=toupper(type);
	cout<<"Enter The Initial amount : \n";
	cin>>deposit;
	cout<<"Account Created..\n";
}

void account::show_account() const
{
	cout<<"\nAccount No. : \n"<<acno;
	cout<<"\nAccount Holder Name : \n";
	cout<<name;
	cout<<"\nType of Account : \n"<<type;
	cout<<"\nBalance amount : \n"<<deposit;
}


void account::modify()
{
	cout<<"\nAccount No. : \n"<<acno;
	cout<<"\nModify Account Holder Name : \n";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : \n";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : \n";
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::draw(int x)
{
	deposit-=x;
}

void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}



void write_account();
void display_sp(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	char ch;
	int num;
	do
	{
	system("CLS");
	cout<<"\n";
	cout<<"BANK MANAGEMENT SYSTEM\n";
	cout<<"\n";

		cout<<"---->MAIN MENU<----\n";
		cout<<"1. CREATE NEW ACCOUNT\n";
		cout<<"2. DEPOSIT AMOUNT IN ACCOUNT\n";
		cout<<"3. WITHDRAW AMOUNT FROM ACCOUNT \n";
		cout<<"4. CHECK BALANCE OF ACCOUNT\n";
		cout<<"5. LIST OF ACCOUNT HOLDER\n";
		cout<<"6. CLOSE AN ACCOUNT\n";
		cout<<"7. MODIFY AN ACCOUNT\n";
		cout<<"8. EXIT\n";
		cout<<"\nPRESS 1 TO CREATE NEW ACCOUNT \n PRESS 2 TO DEPOSIT AMOUNT IN ACCOUNT\n PRESS 3 TO WITHDRAW AMOUNT FROM ACCOUNT \n PRESS 4 TO CHECK BALANCE OF ACCOUNT \n PRESS 5 TO SEE THE LIST OF ACCOUNT HOLDER \n PRESS 6 TO CLOSE AN ACCOUNT \n PRESS 7 TO MODIFY AN ACCOUNT \n PRESS 8 TO EXIT   \n";
		cin>>ch;

		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			system("CLS");
			cout<<"\nEnter The account No. : \n"; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			cout<<"\nEnter The account No. : \n"; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			cout<<"\nEnter The account No. : \n"; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			system("CLS");
			cout<<"\nEnter The account No. : \n"; cin>>num;
			delete_account(num);
			break;
		 case '7':
		 	system("CLS");
			cout<<"Enter The account No. : \n"; cin>>num;
			modify_account(num);
			break;
		 case '8':
		 	system("CLS");
			cout<<"\nBrought To You By code-projects.org\n";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return 0;
}


void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile could not be open !! Press any Key...\n";
		return;
	}
	cout<<"BALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\nAccount number does not exist\n";
}



void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"\nFile could not be open !! Press any Key...\n";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\nEnter The New Details of account\n"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    cout<<"\nRecord Updated\n";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\nRecord Not Found \n";
}



void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat\n",ios::binary);
	if(!inFile)
	{
		cout<<"\nFile could not be open !! Press any Key...\n";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("\naccount.dat\n");
	rename("\nTemp.dat","account.dat\n");
	cout<<"\n\nRecord Deleted ..\n";
}


void display_all()
{
	system("CLS");
	account ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...\n";
		return;
	}
	cout<<"ACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...\n";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\nTO DEPOSITSS AMOUNT\n";
				cout<<"\nEnter The amount to be deposited: \n";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				cout<<"\nTO WITHDRAW AMOUNT\n";
				cout<<"\nEnter The amount to be withdraw: \n ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"\nInsufficience balance\n";
				else
					ac.draw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\nRecord Updated\n";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"\nRecord Not Found \n";
}
