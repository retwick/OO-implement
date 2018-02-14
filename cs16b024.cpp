#include <bits/stdc++.h>
using namespace std;

class Student
{
	string rollNum;
	float score;
	int sumASCII;

public:
	Student(string roll, float s){
		rollNum = roll;
		score = s;
		sumASCII = 0;
		getSumASCII();
	};

	bool operator ==(const Student &s2) const {
		if(s2.rollNum.compare(this->rollNum) == 0){
			return true;
		}
		return false;
	}

	//function to get sum of ascii values
	int getSumASCII();

	void updateScore(float newScore){ score = (score + newScore)/2;}
	string getRoll() { return rollNum;}
	float getMark()	{ return score;}
};

struct CompareStudent{
	//order according to the question
	bool operator () (Student&s1, Student &s2) const {
		if( s1.getMark() == s2.getMark()){
			if(s1.getSumASCII() == s2.getSumASCII()){
				return ((s1.getRoll()).compare(s2.getRoll()) < 0);
			}
			else{
				return (s1.getSumASCII() < s2.getSumASCII());
			}
		}
		else{
			return (s1.getMark() > s2.getMark());
		}
	};
};

class DB
{
	vector<Student> v;
	int S;
public:

	void sortList();
	
	void insert(string rollNum, float marks){
		CompareStudent comp;				
		Student SObj(rollNum,marks);
		if(S == 0){
			//cout<<"empty list\n";
			v.push_back(SObj);						
		}
		else{
			//cout<<"non empty\n";
			//cout<<"roll for find: "<<rollNum<<endl;
			
			if(find(v.begin(), v.end(), SObj) == v.end()){
				//new entry 
				//cout<<"new entry\n";
				//insert S in right position
				v.push_back(SObj);				
				sort(v.begin(), v.end(), comp);
			}
			else{
				//cout<<"old entry\n";

				auto it = find(v.begin(), v.end(), SObj);
				it->updateScore(marks);
				//cout<<it->getRoll()<<":"<<it->getMark()<<endl;
				sort(v.begin(), v.end(), comp);
				//insert S in position
				//copy S to temp, delete S, insert temp
			}
		}
		++S;	
	};

	void IsAdmit(int M, int N){
		if(S<10){cout<<"NO\n"; return ;}
		float topMark = v[0].getMark();
		float cutOff = topMark*N/100.0;

		int c = count_if(v.begin(), v.end(), [cutOff](Student S){ return (S.getMark()>= cutOff); });
		//cout<<"count_if "<<c<<" cutOff "<<cutOff;
		if(c >= (int)M*S/100){
			cout<<"YES\n";
			Admit(S/10);
			DeleteApp(S/10);		
		}
		else{
			cout<<"NO\n";
		}
	}
	void Admit(int selected){
		for (int i = 0; i < selected; ++i){
			cout<<v[i].getRoll()<<" "<<v[i].getMark()<<endl;
		}
	}
	void DeleteApp(int selected){
		for (int i = 0; i < selected; ++i){
			v.erase(v.begin());
		}
	}
	void PRINT(){
		for (int i = 0; i < S; ++i)
		{
			cout<<v[i].getRoll()<<" "<<v[i].getMark()<<endl;
		}
	}
	void PRINT(int start, int end){
		for (int i = start-1; i < end-1 ; ++i)
		{
			cout<<v[i].getRoll()<<" "<<v[i].getMark()<<endl;
		}
	}
	DB(){ S = 0;}
};


int Student::getSumASCII(){	
	for(int i=0; i < rollNum.length(); ++i){
		sumASCII += rollNum[i];
	}
	return sumASCII;
}

int main(int argc, char const *argv[])
{
	int p,q,m,n;
	class DB data;
	cin>>p;
	while(p--){
		string roll;
		float score;
		cin>>roll>>score;		
		data.insert(roll,score);

	}
	//data.PRINT();	
	cin>>q;
	while(q-- >= 0){
		//cout<<q<<endl;
		string command,roll,line;
		float marks;
		int n1, n2 ;
		getline(cin, line);
		stringstream stream(line);
		stream>>command;
		//cout<<"comm "<<command;
		//cin>>command;
		if(!command.compare("IS_ADMIT")){
			stream>>n1>>n2;
			//cout<<"n1 "<<n1<<"n2 "<<n2;
			data.IsAdmit(n1,n2);

		}
		else if(!command.compare("PRINT")){
			if(!line.compare("PRINT")){
				//no arg
				data.PRINT();
				//cout<<"no arg\n";

			}
			stream>>n1>>n2;
			data.PRINT(n1,n2);
			//cout<<"n1 "<<n1<<"n2 "<<n2;	
		}
		else if(!command.compare("INSERT")){
			stream>>roll>>marks;
			//cout<<"n1 "<<roll<<"n2 "<<marks;	
		}
		
	}
	return 0;
}