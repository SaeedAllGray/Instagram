#include "SIGNATURES.h"

bool Account::PasswordApproval()
{
	if(password.size()>7 && password.size()<16)
		if(CapitalAlphabet() && SmallAlphabet() && Numeric())
			return true;
	return false;
}
string Account::Encryption()
{
	string digit="";
	int smallAlphabet=0,capitalAlphabet=0;
	for(int i=0;i<password.size();i++)
	{
		if(isdigit(password[i]))
			digit+=password[i];
		else
		{
			if(islower(password[i]))
				smallAlphabet+=password[i];
			else
				capitalAlphabet+=password[i];
		}	
	}
	long long int stringToNumber=atoi(digit.c_str())*1024;
	
	while(stringToNumber>0)
	{

		int ten=stringToNumber%100;
		char temp=ten%25+65;
		encryptedPassword+=temp;
		stringToNumber/=100;
	}
	encryptedPassword+=to_string(smallAlphabet*128);
	char temp=capitalAlphabet%25+97;
	encryptedPassword+=temp;
	return encryptedPassword;
}

bool Account::SmallAlphabet()
{
	for(int i=0;i<password.size();i++)
		if(islower(password[i]))
			return true;
	return false;
}
bool Account::CapitalAlphabet()
{
	for(int i=0;i<password.size();i++)
		if(isupper(password[i]))
			return true;
	return false;

}
bool Account::Numeric()
{
	for(int i=0;i<password.size();i++)
		if(isdigit(password[i]))
			return true;
	return false;

}
