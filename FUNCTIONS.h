#include "SIGNATURES.h"
#include "PASSWORDPROCESSING.h"
#include <time.h>

Account::Account(string usernameInput,string passwordInput,string nameInput,bool userPrefrenceForPrivate)
	:username(usernameInput),password(passwordInput),name(nameInput),encryptedPassword(""),numberOfPosts(1),isPrivate(userPrefrenceForPrivate){}
void Account::SignUp()
{
	srand(time(NULL));
	string profile=username;
	profile+=".txt";
	try{
		if(Exists(profile))
			throw AlreadyExists();
		if(!PasswordApproval())
			throw UnsecurePassword();

	}catch(AlreadyExists alreadyExists)
	{
		profile=profile.substr(0,profile.find(".txt"));
		char randomChar=rand()%26+65;
		char randomChar2=rand()%26+65;
		int randomInt=rand()%100+1920;
		username+=randomChar;
		username+=randomChar2;
		username+=to_string(randomInt);
		profile=username;
		profile+=".txt";
	}catch(UnsecurePassword unsecurePassword)
	{
		int randomInt=rand()%10000;
		if(password.size()<8)
		{
			password+="CYpl";
			password+=to_string(randomInt);
		}
	}
	Encryption();
	ofstream info(profile);
	isPrivate?info<<"Private\n":info<<"Public\n";
	info<<"username: "<<username<<"\nname: "<<name<<"\npassword: "<<encryptedPassword;
}
Account::Account(Account& user)
{
	isPrivate=user.GetStatus();
	username=user.GetUsername();
	encryptedPassword=user.Encryption();
}
int Account::SignIn(string usernameInput,string passInput)
{
	string profile=usernameInput;
	profile+=".txt";
	if(!Exists(profile))
		return -1;
	string profilePassword;
	username=usernameInput;
	Account account(usernameInput,passInput,name,isPrivate);
	ifstream info(profile);
	while(!info.eof())
	{
		getline(info,encryptedPassword);
	}
	if(account==*this)
		return 1;
	return 0;
	
}
bool Account::Exists(string profile)
{
	fstream file;
	file.open(profile.c_str());
	if(file)
		return true;
	return false;
}

void Account::LikeAPost(Post post)
{
	post.IncreaseLikes();
}
Post Account::PostAText(string contentInput,int timePosted)
{
	Post post(contentInput,timePosted,this);
	posts.push_back(post);
	numberOfPosts++;
	return post;
}
/*void Account::SeenAPost(Post post,int number)
{
	//post.GetContent(number);
}*/
void Account::BeFollowedBy(Account account)
{
	string profile=username;
	profile+=".folowers.txt";
	ofstream input(profile.c_str(),ios::app);
		input<<account.GetUsername()<<endl;
}
void Account::GetFollowers()
{
	string profile=username;
	profile+=".folowers.txt";
	ifstream out(profile);
	string followersName;
	while(!out.eof())
	{
		getline(out,followersName);
		cout<<followersName<< endl;
	}
}
void Account::Delete()
{
	string profile=username;
	profile+=".txt";
	string folowersProfile=username;
	folowersProfile+=".followers.txt";
	string postProfile=username;
	postProfile+=".post.txt";
	ofstream erase(profile.c_str());
	ofstream eraseF(folowersProfile.c_str());
	ofstream eraseP(postProfile.c_str());
	erase<<"Deleted. ";
	eraseF<<"Deleted. ";
	eraseP<<"Deleted. ";
}

void Account::ChangePassword(string newPassword)
{
	password=newPassword;
	string profile=username;
	profile+=".txt";
	Encryption();
	ofstream info(profile.c_str());
	isPrivate?info<<"Private\n":info<<"Public\n";
	info<<"username: "<<username<<"\nname: "<<name<<"\npassword: "<<encryptedPassword;
}
string Account::SeenAPost(string usernameInput,int number)
{
	Account anyAccount(usernameInput);
	Post post(anyAccount);
	string profile=usernameInput;
	profile+=".post.txt";
	return post.GetContent(number);
}
bool FastSearchAccounts(string profile)
{
	profile+=".txt";
	fstream file;
	file.open(profile.c_str());
	if(file)
		return true;
	return false;
}
