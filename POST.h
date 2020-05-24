#include "SIGNATURES.h"

Post::Post(string contentInput,int timePosted,Account* accountInput)
	:content(contentInput),timeP(timePosted),likes(0),account(accountInput)
{
	string postsArcive=account->GetUsername();
	postsArcive+=".post.txt";
	ofstream input(postsArcive.c_str(),ios::app);
	input<<"##"<<account->GetNumberOfPosts()<<"  #time "<<timeP<<endl<<contentInput<<endl;
	input<<"###\n";
}
void Post::IncreaseLikes()
{
	likes++;
}
string Post::GetContent(int number)
{
	content="";
	string temp="##";
	temp+=to_string(number);
	string profile=account->GetUsername();
	string ssss;
	profile+=".post.txt";
	ifstream file(profile.c_str());
	if(file && content.find("###"))
	{
		while(!file.eof())
		{
			getline(file,ssss);
			content+=ssss;
		}
	file.close();
	}
	content=content.substr(content.find(temp),content.find("###"));
	return content;
}
void Post::Comment(string comment)
{
	comments.push_back(comment);
	string profile=account->GetUsername();
	profile+=".comment.txt";
	ofstream info(profile.c_str(),ios::app);
	info<<comment<<endl;
}
