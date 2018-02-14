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
	//vector<Student>::iterator find(vector <Student> v, string rollNum);
	void insert(string rollNum, float marks){
		CompareStudent comp;				
		Student SObj(rollNum,marks);
		if(S == 0){
			cout<<"empty list\n";
			v.push_back(SObj);						
		}
		else{
			cout<<"non empty\n";
			cout<<"roll for find: "<<rollNum<<endl;
			//if(find(v,rollNum) == v.end()){
			if(find(v.begin(), v.end(), SObj) == v.end()){
				//new entry 
				cout<<"new entry\n";
				//insert S in right position
				v.push_back(SObj);				
				sort(v.begin(), v.end(), comp);
			}
			else{
				cout<<"old entry\n";
				//SObj.updateScore(marks);
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
		float topMark = v[0].getMark();

	}

	int countStudentsMoreMarks(float x){
		//return (S - lower_bound(v.begin(), v.end(), ))
	}

	void PRINT(){
		for (int i = 0; i < S; ++i)
		{
			cout<<v[i].getRoll()<<" "<<v[i].getMark()<<endl;
		}
	}
	DB(){
		S = 0;
	}

	
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
	data.PRINT();	
	cin>>q;
	while(q--){
		string command,roll,line;
		float marks;
		int n1, n2 ;
		getline(cin, line);
		stringstream stream(line);
		stream>>command;
		if(!command.compare("IS_ADMIT")){
			stream>>n1>>n2;
			cout<<"n1 "<<n1<<"n2 "<<n2;
		}
		else if(!command.compare("PRINT")){
			stream>>n1>>n2;
			cout<<"n1 "<<n1<<"n2 "<<n2;	
		}
	}
	return 0;
}