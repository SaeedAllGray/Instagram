#ifndef SIGNATURES
#define SIGNATURES

#include <iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
class AlreadyExists{};
class UnsecurePassword{};
class Post;
class Account
{
public:
	Account(){}
	Account(string usernameInput){ username=usernameInput; }
	Account(Account&);
	Account(string usernameInput,string passwordInput,string nameInput,bool useruserPrefrenceForPrivate);
	string GetUsername(){ return username; }
	int GetNumberOfPosts(){ return numberOfPosts; }
	bool GetStatus(){ return isPrivate; }
	Account& operator=(Account &A)
	{
		username=A.GetUsername();
		return *this;
	}
	bool operator==(Account &A)const
	{
		return username==A.GetUsername() && encryptedPassword.find(A.Encryption());
	}

//	void IncNumberOfPosts(){ numberOfPosts++; }

	void SignUp();
	int SignIn(string usernameInput,string passInput);
	bool PasswordApproval();
	bool CapitalAlphabet();
	bool SmallAlphabet();
	bool Numeric();
	string Encryption();
	bool Exists(string profile);
	
	string SeenAPost(string usernameInput,int number);
	Post PostAText(string contentInput,int timePosted);
	void LikeAPost(Post post);
	void BeFollowedBy(Account a);
	void GetFollowers();
	void ChangePassword(string newPassword);
	void Delete();
	
	friend bool FastSearchAccounts(string profile);

	private:
	string username;
	string password;
	string name;
	bool isPrivate;
	string encryptedPassword;
	
	vector<Post> posts;
	vector<Account> followers;
	int numberOfPosts;
};
class Post
{
public:
	Post(){}
	Post(Account &A){ account=&A; }
	Post(string contentInput,int timePosted,Account* accountInput);
	void IncreaseLikes();
	string GetContent(int number);
	void Comment(string comment);
	
	friend bool FastSearchPosts();
protected:
	string content;
	vector<string> comments;
	int timeP;
	int likes;
	Account* account;
};

#endif
