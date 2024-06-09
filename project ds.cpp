#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<string>
#include<string.h>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<windows.h>
#include "Check.h"
using namespace std;

bool AlphabatSmall(char);
void PrintFormat(string);
void printHead();
int getChoice();
void printLoadScr();
void printAll(string, string, string, string, string, string, string, string, string);

//Using to manipulate cursor for output
void gotoxy(int x, int y)
{
  static HANDLE h = NULL;
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c;
  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition(h,c);
}
bool checkEmpty(string st){
	if(st.length()>=0 && st.length()<=2){
		return true;
	}
	return false;
}
string redString(string st, int x, int y){
	if(!checkEmpty(st)){
		st = st.substr(x, y);
		return st;
	}
	return st;
}

const int TABLE_SIZE = 10;
class Title{
public:
	int key;
	string data_value;
	Title *next;

	Title(int key,string data)
	{
		this->key = key;
		data_value = data;
		next = NULL;
	}
};

class TitleMap{
public:
	Title **htable;
	TitleMap()
	{
		htable = new Title*[TABLE_SIZE];
		for(int i=0;i<TABLE_SIZE;i++)
		{
			htable[i] = NULL;
		}
	}

	int Titlefun(int key)
	{
		return key%TABLE_SIZE;
	}

	void InsertInTable(int key,string data)
	{
		int index = Titlefun(key);
		Title* prev = NULL;
		Title* root = htable[index];

		while(root!=NULL)
		{
			prev = root;
			root = root->next;
		}

		if(root == NULL)
		{
			root = new Title(key,data);
			if(prev == NULL)
			{
				htable[index] = root;
			}
			else
			{
				prev->next = root;
			}
		}
		else
		{
			root->data_value = data;
		}
	}
	//If user enters symptom(s)
	void searchIfSymptom(string name){
		int T_count=0;
		int character = 0;
		int count = 0,count1=0;
		int c = 0;
		int k = Titlefun(1);
		int countArr[5] = {-1};
		string sympArr[5] = {""};
		string disName[5] = {""};
		Title *temp = htable[k];
		while(temp!=NULL){
			if(temp->key==k){
				count=0;
				count1=0;
				string word;
				string tempName = temp->data_value;
				string T,M;
				stringstream X(name);
				while(getline(X, T, ' ')) {
					count+=1;
					stringstream S(tempName);
					while(getline(S,M,' '))
					{
						if(T==M)
						{
							count1+=1;
							break;
						}
					}
				}
				if(count==count1)
				{
					if(c<5){
					sympArr[c] = tempName;
					countArr[c] = T_count;
					c+=1;
					}
				}
			}
			T_count+=1;
			temp = temp->next;
		}
		for(int i=0;i<5;i++){
			if(countArr[i]>0){
				disName[i] = searchDisease(countArr[i]);
			}
		}
		int choice = askUser(disName);
		string dis = disName[choice-1];
		string symp = sympArr[choice-1];
		symp = redString(sympArr[choice-1], 2, sympArr[choice-1].length()-2);
		string cau = searchCauses(countArr[choice-1]);
		cau = redString(cau, 2, cau.length()-3);
		string rf = searchRiskFactor(countArr[choice-1]);
		rf = redString(rf, 2, rf.length()-3);
		string ovr = searchOverview(countArr[choice-1]);
		ovr = redString(ovr, 2, ovr.length()-2);
		string tr = searchTreatment(countArr[choice-1]);
		tr = redString(tr, 2, tr.length()-2);
		string md = searchMedication(countArr[choice-1]);
		md = redString(md, 2, md.length()-2);
		string cost = searchCost(countArr[choice-1]);
		string hr = searchHomeRem(countArr[choice-1]);
		hr = redString(hr, 2, md.length()-2);
		printLoadScr();
		printAll(dis, symp, cau, rf, ovr, tr, md, hr, cost);
	}
	//If user enters a Disease
	void searchIfDisease(string name){
		int character=0;
		string nameArr[5] = {""};
		int countArr[5] = {0};
		int count=0;
		int c=0;
		int k =Titlefun(0);
		Title *temp = htable[k];
		while(temp!=NULL){
			if(temp->key==k){
				character=0;
				string s = temp->data_value;
				for(int i=0;i<name.length();i++){
					if(name[i]==s[i]){
						character+=1;
					}
					else{
						break;
					}
				}
				if(character==name.length()){
					nameArr[c] = s;
					countArr[c] = count;
					c+=1;
				}
			}
			count+=1;
			temp = temp->next;
		}
		int choice = askUser(nameArr);
		string dis = nameArr[choice-1];
		string symp = searchSymptom(countArr[choice-1]);
		symp = redString(symp, 2, symp.length()-3);
		string cau = searchCauses(countArr[choice-1]);
		cau = redString(cau, 3, cau.length()-3);
		string rf = searchRiskFactor(countArr[choice-1]);
		rf = redString(rf, 2, rf.length()-3);
		string ovr = searchOverview(countArr[choice-1]);
		ovr = redString(ovr, 2, ovr.length()-2);
		string tr = searchTreatment(countArr[choice-1]);
		tr = redString(tr, 2, tr.length()-2);
		string md = searchMedication(countArr[choice-1]);
		md = redString(md, 2, md.length()-2);
		string cost = searchCost(countArr[choice-1]);
		string hr = searchHomeRem(countArr[choice-1]);
		hr = redString(hr, 2, hr.length()-2);
		printLoadScr();
		printAll(dis, symp, cau, rf, ovr, tr, md, hr, cost);
	}
	string searchDisease(int index){
		int k = Titlefun(0);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchCost(int index){
		int k = Titlefun(8);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchHomeRem(int index){
		int k = Titlefun(7);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchMedication(int index){
		int k = Titlefun(6);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchTreatment(int index){
		int k = Titlefun(5);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchRiskFactor(int index){
		int k = Titlefun(3);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchCauses(int index){
		int k = Titlefun(2);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchOverview(int index){
		int k = Titlefun(4);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	string searchSymptom(int index){
		int k = Titlefun(1);
		Title *temp = htable[k];
		for(int i=0;i<index && temp!=NULL;i++){
			temp = temp->next;
		}
		return temp->data_value;
	}
	int askUser(string nameArr[]){
		int choice, counter = 0;
		int x = 45, y = 13;
		printHead();
		gotoxy(x, y);
		cout << "Which Disease Would You Like to Know More About?";
		y+=2;
		for(int i=0;i<5;i++){
			if(nameArr[i]!=""){

				gotoxy(x, y);
				nameArr[i] = nameArr[i].substr(0, nameArr[i].length()-2);
				cout << " " << i+1 << ") " << nameArr[i];
				counter+=1;
				y+=1;
			}
		}
		gotoxy(x, y+2);
		cout << "Enter Your Choice: ";
		cin >> choice;

		while(choice < 0 || choice>counter){
			y+=1;
			gotoxy(x, y);
			cout << " Invalid Choice.....";
			y+=1;
			gotoxy(x, y);
			cout << " Enter Your Choice: ";
			cin >> choice;
		}
		return choice;
	}
	~TitleMap()
	{
		for (int i = 0; i < TABLE_SIZE; ++i)
		{
		Title* root = htable[i];
			while (root != NULL)
			{
				Title* prev = root;
				root = root->next;
				delete prev;
			}
		}
            delete[] htable;
	}
};

int main()
{
	TitleMap obj;
	string s;
	fstream database;
	database.open("extra2.csv",ios::in);
	while(!database.eof())
	{
		getline(database,s);
		int i=0;
		while(!Alphabat(s[i]))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
			string fine="";
			int j=0;
			while(s[i]!='[')
			{
				fine.push_back(s[i]);
				i++;
			}
			obj.InsertInTable(0,fine);
		}
	}
	database.close();
	//Now Symptom insertion
	fstream database2;
	database2.open("extra2.csv",ios::in);
	while(!database2.eof())
	{
		getline(database2,s);
		int i=0;
		while(Bracket(s[i]))
		{
			i++;
		}
		if(INDEX(s[0])){
			string fine2 = "";
			int j=0;
			while(s[i]!=']')
			{
				fine2.push_back(s[i]);
				i++;
			}
			fine2.push_back(']');
			obj.InsertInTable(1,fine2);
		}
	}
	database2.close();

	//NOW Causes Insertion
	fstream database3;
	database3.open("extra2.csv",ios::in);
	while(!database3.eof())
	{
		string fine3="";
		getline(database3,s);
		int i=0;
		while(Causebracket(s[i]))
		{
			i++;
		}
		i=i+3;
		if(s[0]>='0' && s[0]<='9'){
			string fine3 = "";
			while(s[i]!=']')
			{
				fine3.push_back(s[i]);
				i++;
			}
			obj.InsertInTable(2,fine3);
		}
	}
	database3.close();

	//	Now Risk Factor insertion
	fstream database4;
	database4.open("extra2.csv",ios::in);
	while(!database4.eof())
	{
		getline(database4,s);
		int i=0;
		int count=0;
		while(Riskbracket(s[i],count))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
				string fine4="";
			int j=0;
			while(s[i]!=']')
			{
				fine4.push_back(s[i]);;
				i++;
			}
			obj.InsertInTable(3,fine4);
		}
	}
	database4.close();

	//Now OverView Factor insertion
	fstream database5;
	database5.open("extra2.csv",ios::in);
	while(!database5.eof())
	{
		getline(database5,s);
		int i=0;
		int count=0;
		while(overview(s[i],count))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
			string fine5="";
			int j=0;
			while(s[i]!=']')
			{
				fine5.push_back(s[i]);;
				i++;
			}
			obj.InsertInTable(4,fine5);
		}
	}
	database5.close();

	//	Now treatment insertion
	fstream database6;
	database6.open("extra2.csv",ios::in);
	while(!database6.eof())
	{
		getline(database6,s);
		int i=0;
		int count=0;
		while(treatment(s[i],count))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
			string fine6="";
			int j=0;
			while(s[i]!=']')
			{
				fine6.push_back(s[i]);;
				i++;
			}
			obj.InsertInTable(5,fine6);
		}
	}
	database6.close();

	// Now medication insertion
	fstream database7;
	database7.open("extra2.csv",ios::in);
	while(!database7.eof())
	{
		getline(database7,s);
		int i=0;
		int count=0;
		while(medication(s[i],count))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
			string fine7="";
			int j=0;
			while(s[i]!=']')
			{
				fine7.push_back(s[i]);
				i++;
			}
			obj.InsertInTable(6,fine7);
		}
	}
	database7.close();

	//	Now Medical remendies
	fstream database8;
	database8.open("extra2.csv",ios::in);
	while(!database8.eof())
	{
		getline(database8,s);
		int i=0;
		int count=0;
		while(medicalRemendies(s[i],count))
		{
			i++;
		}
		if(s[0]>='0' && s[0]<='9'){
			string fine8="";
			int j=0;
			while(s[i]!=']')
			{
			fine8.push_back(s[i]);
				i++;
			}
			obj.InsertInTable(7,fine8);
		}
	}
	database8.close();

	// Cost Insertion
	fstream database9;
	database9.open("extra2.csv",ios::in);
	while(!database9.eof())
	{
		getline(database9,s);
		int i=0;
		while(Cost(s[i],s[i+1],s[i+2]))
		{
			i++;
		}
		if(INDEX(s[0])){
			string fine9="";
			int j=0;
			while(s[i]!='.')
			{
				fine9.push_back(s[i]);
				i++;
			}
			obj.InsertInTable(8,fine9);
		}
	}
	database9.close();


	//Main Program
  while(1){
		int choice = getChoice();
		string sear;
		system("cls");
		system("color 71");
		switch(choice){
			case 1:
				printHead();
				gotoxy(45, 12);
				cout << "Enter the Name of the Disease: ";
				fflush(stdin);
				getline(cin, sear);
				if(sear[0]>='a' && sear[0]<='z'){
					sear[0]-=32;
				}
				printLoadScr();
				obj.searchIfDisease(sear);
			    cout<<"Press <enter> key to continue"<<endl;
			    system("pause");
			    system("cls");
				break;
			case 2:
				printHead();
				gotoxy(45, 12);
				cout << "Please Enter a Symptom: ";
				fflush(stdin);
				getline(cin, sear);
				if(sear[0]>='A' && sear[0]<='Z'){
					sear[0]+=32;
				}
				printLoadScr();
				obj.searchIfSymptom(sear);
		    	cout<<"Press <enter> key to continue"<<endl;
		    	system("pause");
		    	system("cls");
				break;    
			case 3:
			    gotoxy(37, 12);
			    cout << "Thankyou for Using Our Seacrh Engine!";
			    gotoxy(37, 14);
			    cout << "Hope you have had a significant addition in your Knowledge";
			    exit(0);
			default:
				gotoxy(45, 12);
				cout << "Invalid Choice..........";
				for(int i=0;i<1000000000;i++){}
				break;
		}
	}
	return 0;
}

void printLoadScr(){
	int i;
	char a = 219;
	system("cls");
	printHead();
	gotoxy(50, 10);
	cout << "Searching........";
	gotoxy(50, 11);
	for(i=0;i<30;i++){
		cout << a;
	    system("color 71");
	}
	for(i=0;i<1000000000;i++);
	system("cls");
}

void printHead(){
	system("color 71");
	gotoxy(40, 5);
	cout << "=========================================";
	gotoxy(40, 6);
	cout << "||";
	gotoxy(44, 6);
	cout << "\t Medical Search Engine\t       ||";
	gotoxy(40, 7);
	cout << "=========================================";
}

int getChoice(){
	int choice;
	printHead();
	gotoxy(36, 12);
	cout << "What Would you Like to Search? Press 3 to exit Program" ;
	gotoxy(47, 14);
	cout << "1) Disease\t2) Symptoms";
	gotoxy(49, 16);
	cout << "Enter your Choice: ";
	cin >> choice;
return choice;
}

void printAll(string dis, string symp, string cau, string rf, string ovr, string tr, string md, string hr, string cost){
	system("color 71");
	if(!checkEmpty(dis)){
		cout << "||Disease Name||\n\n";
		cout << dis << "\t" << "(Est. Treatment Cost :- " << cost << ")" << endl;
		if(!checkEmpty(ovr)){
			cout << "\n\n||Overview||\n";
			cout << "____________\n";
			cout << "\n";
			PrintFormat(ovr);
			cout << endl;
		}
		if(!checkEmpty(symp)){
			cout << "\n\n||Symptoms||\n";
			cout << "____________\n";
			cout << "\n";
			PrintFormat(symp);
			cout << endl;
		}
		if(!checkEmpty(cau)){
			cout << "\n\n||Causes||\n";
			cout << "__________\n";
			cout << "\n";
			PrintFormat(cau);
			cout << endl;
		}
		if(!checkEmpty(rf)){
			cout << "\n\n||Risk Factor||\n";
			cout << "_______________\n";
			PrintFormat(rf);
			cout << endl;
		}
		if(!checkEmpty(tr)){
			cout << "\n\n||Treatment||\n";
			cout << "_____________\n";
			cout << "\n";
			PrintFormat(tr);
			cout << endl;
		}
		if(!checkEmpty(md)){
			cout << "\n\n||Medications||\n";
			cout << "_______________\n";
			cout << "\n";
			PrintFormat(md);
			cout << endl;
		}
		if(!checkEmpty(hr)){
			cout << "\n\n||Home Remedies||\n";
			cout << "_________________\n";
			cout << "\n";
			PrintFormat(hr);
			cout << endl;
		}
	}
}
bool AlphabatSmall(char s)
{
	if(s>='a' && s<='z')
	{
		return true;
	}
	return false;
}

void PrintFormat(string s)
{
	cout << " ";
	for(int i=0;i<s.length();i++)
	{
		cout << s[i];
		if(s[i]=='.')
		{
			cout << endl << "=>";
			int j=0;
			while(1)
			{
				if(Alphabat(s[i]) || INDEX(s[i]) || AlphabatSmall(s[i]))
				{
					i = i-1;
					break;
				}
				else
				{
					i++;
				}
			}
		}
	}
}
