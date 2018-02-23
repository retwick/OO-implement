#include <bits/stdc++.h>
using namespace std;

class Package {
public:
	string name;
	long long int cost;
	Package(string pack, int cost){
		name = pack;
		this->cost = cost;
	};
};

long long int minCost = 0;

static bool comparator(class Package obj){
	if(obj.cost > minCost) return true;
	else	return false;
}

class Destination {
public:
	vector<Package> packages;
	long long int tourism_quotient, opCost;
	string minPackages;
	bool done;
	void setQuotient(long q){
		tourism_quotient = q;
		opCost = -1;
		done = false;
	}
	void setPackage(string pack, long cost){
		class Package P(pack,cost);
		packages.push_back(P);
	};
};



void setCost(vector <Destination> &D){
	vector <long> packageIndex(D.size(), -1);
	vector <long long int> price(D.size(), -1);

	auto it_package = find_if(D[0].packages.begin(), D[0].packages.end(), comparator);

	D[0].opCost = (*it_package).cost;
	D[0].minPackages = (*it_package).name;

	for (long i = 0; i < D.size()-1; ++i)
	{
		//cout<<"loop i:"<<i<<" prev:"<<prev;
		if(D[i].tourism_quotient < D[i+1].tourism_quotient){
			//price[i] = D[i].packages[packageIndex[i]];
			minCost = D[i].opCost;
			it_package = find_if(D[i+1].packages.begin(), D[i+1].packages.end(), comparator);

			if(it_package - D[i+1].packages.begin() == D[i+1].packages.size()){				
				cout<<"-1";
				return;
			}
			
			D[i+1].opCost = (*it_package).cost;
			D[i+1].minPackages = (*it_package).name;

		}
		else if(D[i].tourism_quotient >= D[i+1].tourism_quotient && D[i+1].tourism_quotient <= D[i+2].tourism_quotient){
			minCost = 0;
			it_package = find_if(D[i+1].packages.begin(), D[i+1].packages.end(), comparator);
			if(it_package - D[i+1].packages.begin() == D[i+1].packages.size()){				
				cout<<"-1";
				return;
			}
			D[i+1].opCost = (*it_package).cost;
			D[i+1].minPackages = (*it_package).name;
		}
		//cout<<"coeff"<<D[i].tourism_quotient<<" . "<<endl;;
	}

	
	if(D[D.size()-2].tourism_quotient < D[D.size()-1].tourism_quotient){
		minCost = D[D.size()-2].opCost;
	}
	else{
		minCost = 0;
	}
	it_package = find_if(D[D.size()-1].packages.begin(), D[D.size()-1].packages.end(), comparator);
	
	if(it_package - D[D.size()-1].packages.begin() == D[D.size()-1].packages.size()){				
		cout<<"-1";
		return;
	}
	D[D.size()-1].opCost = (*it_package).cost;
	D[D.size()-1].minPackages = (*it_package).name;


	for (long long int i = D.size()-2; i >= 0; --i)
	{			

		if((D[i].tourism_quotient > D[i+1].tourism_quotient) ){
			if(D[i].opCost <= D[i+1].opCost){
				minCost = D[i+1].opCost;
				it_package = find_if(D[i].packages.begin(), D[i].packages.end(), comparator);
				if(it_package == D[i].packages.end()){				
					cout<<"-1";
					return;
				}
				D[i].opCost = (*it_package).cost;
				D[i].minPackages = (*it_package).name;
			}
		}
		//cout<<"coeff"<<D[i].tourism_quotient<<" . ";
	}
	//cout<<endl;


	long long int sum = 0;
	//print the sequence of optimal packages
	for(long long int i = 0 ; i < D.size() ; i++){
		sum+= D[i].opCost;
		//cout<<i;
	}
	cout<<sum<<"\n";

	//print the sequence of optimal packages
	for(long long int i = 0 ; i < D.size() ; i++){
		cout<<D[i].minPackages<<" ";
		//cout<<i;
	}


/*
	for(long i=0; i<D.size()-1; ++i){
		cout<<D[i].tourism_quotient<<"__"<< packageIndex[i]<<" . ";
		if(packageIndex[i] != -1){
			price[i] = D[i].packages[packageIndex[i]].cost;
			sum += price[i];
		}
		else{			
			flag = false;
		}
	}
	//cout<<endl;
	if(flag){
		cout<<sum<<endl;
	}
	if(!flag){
		cout<<"-1"<<endl;
		return ;
	}
	for(long i=0; i<D.size(); ++i){
		cout<<D[i].packages[packageIndex[i]].name<<" ";
	}
*/
}
void printInput(vector <Destination> &D){
	
	for(long i=0; i<D.size(); ++i){
		cout<<"q: "<<D[i].tourism_quotient<<endl;
		for(long j=0; j<D[i].packages.size(); ++j){
			cout<<D[i].packages[j].name<<":"<<D[i].packages[j].cost<<" ";
		}
		cout<<endl;
	}
}
int main(int argc, char const *argv[])
{
	long n,x;
	cin>>n;
	vector <Destination> D(n);
	long long int cost;
	long i = 0;
	while(i < n){
		cin>>x;
		D[i].setQuotient(x);
		++i;
	}
	string l;
	getline(cin,l);
	i = 0;
	while(i < n){
		string line,pack;
		long cost;
		
		getline(cin,line);
		stringstream stream(line);
		while(1){
			stream>>pack>>cost;
			if(!stream){
				break;
			}			
			D[i].setPackage(pack,cost);
		}
		
		++i;
	}
	//printInput(D);
	//cout<<endl;
	setCost(D);
	return 0;
}