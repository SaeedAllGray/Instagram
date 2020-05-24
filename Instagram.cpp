#include <iostream>
#include<string>
#include "FUNCTIONS.h"
#include "POST.h"
using namespace std;
int main() 
{
	clock_t time=clock()/1000;
	Account A;
	Post P;
	int respond;
	cout<<"1.Sign up\n2.Sign in\n";
	cin>>respond;
	string nameInput,usernameInput,passInput;
	if(respond==1)
	{
		cout<<"What is your name? ";
		cin>>nameInput;
		cout<<"Take a username: ";
		cin>>usernameInput;
		cout<<"Enter passcode. (must becontain at last a cpital and small character and a digit with 8 to 15 length\n";
		cin>>passInput;
		cout<<"1.public  2.private\n";
		int publicOrPrivate;
		cin>>publicOrPrivate;
		if(publicOrPrivate==1) 
		{
			Account account(usernameInput,passInput,nameInput,0);
			A=account;
			account.SignUp();
		}
		else
		{
			Account account(usernameInput,passInput,nameInput,1);
			A=account;
			account.SignUp();

		}
	}
	else if(respond==2)
	{
		Account account;
		cout<<"Enter your username: ";
		cin>>usernameInput;
		cout<<"Enter your passcode.\n";
		cin>>passInput;
		if(account.SignIn(usernameInput,passInput)==-1)
		{
			cout<<"You should sign up first.\n";
		}
		else if(account.SignIn(usernameInput,passInput)==0)
		{
			cout<<"Username or password is incorrect.\n";
		}
		else if(account.SignIn(usernameInput,passInput)==1)
		{
			cout<<"Welcome. \n";
			A=account;
		}
	}
	bool launch=1;
	while(launch)
	{
		cout<<"1.Post Somthing  2.Edit a Post  3.Feed  4.Followers & Following  5.Fast Search  6.Setting \n";
		cin>>respond;
		if(respond==1)
		{
			cout<<"Enter the content.\n";
			string contentInput;
			cin>>contentInput;
			clock_t ExtraTime=clock()/1000;
			A.PostAText(contentInput,ExtraTime);
		}
		if(respond==3)
		{
			
			string textIn;
			string text;
			cout<<"username: ";
			cin>>textIn;
			cout<<"which Post ";
			int n;
			cin>>n;
			cout<<A.SeenAPost(textIn,n);
			Post post(A);
			cout<<"\n1.like  2.comment 3.like and comment";
			cin>>respond;
			if(respond==1)
			{
				post.IncreaseLikes();
			}
			else if(respond==2)
			{
				cout<<"Comment: ";
				cin>>text;
				post.Comment(text);
			}
			else if(respond==3)
			{
				post.IncreaseLikes();
				cout<<"Comment: ";
				cin>>text;
				post.Comment(text);
			}
		}
		if(respond==4)
		{
			cout<<"1.follow   2.your followers   ";
			cin>>respond;
			if(respond==1)
			{
				string usernameInput;
				cout<<"enter the user you want to follow!!\n";
				cin>>usernameInput;
				Account accountInput(usernameInput);
				accountInput.BeFollowedBy(A);
			}
			else if(respond==2)
				A.GetFollowers();
		}
		if(respond==5)
		{
		
			string profile;
			cout<<"Enter a profile name\n";
			cin>>profile;
			if(FastSearchAccounts(profile))
				cout<<"Found!!!";
			else 
				cout<<"Sorry!!!!";
		}
		if(respond==6)
		{
			cout<<"1.change password. 2.delete account\n";
			cin>>respond;
			if(respond==1)
			{
				string newPass;
				cout<<"Enter New password\n";
				cin>>newPass;
				A.ChangePassword(newPass);
			}
			if(respond==2)
			{
				A.Delete();
				launch=false;
			}
		}
		else 
			return 0;
	}
}
