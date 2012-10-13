#include"sub.h"
#include<iostream>
#include <set>
#include<math.h>
#define x1 0//Д,С,В используемые в вычислениях, по умолчанию
#define x2 1
#define oper + //Значение элементарного оператора (X1+X2,X1-X2,X1*X2,X1/X2)
inline double miniCalc(double a, char s, double b);

input::input(){
  std::cout<<"\nВведите кол-во значений в событии: ";
  std::cin>>number;
  std::cout<<"\nВведите значения события: ";
  for (int i=0;i<number;++i){
    double a;
    std::cin>>a;
    Values.push_back(a);
  }
   std::cout<<"\nВведите возможность значения события: ";
  for (int i=0;i<number;++i){
    double a,b;
    char s;
    std::cin>>a>>s>>b;
    if(miniCalc(a,s,b)!=-1)Possibility.push_back(miniCalc(a,s,b));
  }
}


head::head(){
  std::cout<<"\nВведите кол-во событий: ";
  std::cin>>SumTables;
  Tables=new input[SumTables];
    for(int i=0;i<SumTables;++i){
    PrintTable(Tables[i]);
  }
  //Resultat
  output Z;
  //По умолчанию Z=X1+X2
  //По умолчанию x1=0,x2=1; Объявлены в define
  //Values Z
  for(int i=0;i<Tables[x2].GetNumber();++i){
    for(int j=0;j<Tables[x1].GetNumber();++j){
      Z.AddElemValues(Tables[x1].GetValues(j) oper Tables[x2].GetValues(i));
    }
  }
  //Possibility Z
  for(int i=0;i<Tables[x2].GetNumber();++i){
    for(int j=0;j<Tables[x1].GetNumber();++j){
      Z.AddElemPoss(Tables[x1].GetPossible(j)*Tables[x2].GetPossible(i));
    }
  }  
  //NoFormat Z
    std::cout<<"\n\n\tX2/X1:\t";
  for(int i=0;i<Z.GetNumber();++i){
    std::cout<<" "<<Z.GetValues(i)<<"\t";
    if((i+1)%Tables[x1].GetNumber()==0 )std::cout<<"\n\t\t";
  }
  std::vector<double> AllValuesZ;
  for (int i=0;i<Z.GetNumber();++i){
    AllValuesZ.push_back(Z.GetValues(i));
  }
  
for(int i=0;i<Z.GetNumber();++i){
    for(int j=0;j<Z.GetNumber();++j){
      if(Z.GetValues(i)==Z.GetValues(j) && i!=j){
	Z.SetPossible(i,Z.GetPossible(i)+Z.GetPossible(j));
	Z.DelPoss(j); Z.DelValues(j);
	i=0;j=0;
    }
  }
}
for(int i=0;i<Tables[x2].GetNumber();++i){
  int s=0;int ind;
   double tmp=0;
    for(int j=0;j<Z.GetNumber();++j){
      for(int k=i*Tables[x1].GetNumber();k<i*Tables[x1].GetNumber()+Tables[x1].GetNumber();++k){
	if (k%Tables[x1].GetNumber()==0){
			if (k< Tables[x1].GetNumber()){
			ind=k;
			}else{
					ind=Tables[x1].GetNumber();}
	}else{
			 ind=k%Tables[x1].GetNumber();
	}
	
	if(ind>=Tables[x1].GetNumber())ind-=Tables[x1].GetNumber() ;
	if(AllValuesZ[k]==Z.GetValues(j)){
			s++;
			tmp=s*Tables[x2].GetPossible(i)*Tables[x1].GetPossible(ind);
	}
		  }
	   Z.AddDoublePoss(tmp);
      s=0;
      tmp=0;
    }
      s=0;
  }
//По умолчанию x1=0;x2=1;
  std::cout<<"\n";
  PrintTable(Z);
  for(int i=0;i<SumTables;++i){
    std::cout<<"\nHX"<<i+1<<"="<<intropy(Tables[i]);
  }
  std::cout<<"\nHZ"<<"="<<intropy(Z);
  std::cout<<"\nH(x2,z)= "<<Z.DblIntropy();
  std::cout<<"\nI(x2,z)= "<<Shennon(Tables[x2], Z);
}


double output::DblIntropy(){
  double sum=0;
    for(int i=0;i<GetNumDblPoss();++i){
      if(DoublePoss[i]!=0)sum+=DoublePoss[i]*log(DoublePoss[i])/log(2);
    }
    sum*=-1;
    return sum;
}




double head::intropy(input &a){
  double sum=0;
  for(int i=0;i<a.GetNumber();++i){
    sum+=a.GetPossible(i)*log(a.GetPossible(i))/log(2);
  }
  sum*=-1;
  return sum;
}
double head::intropy(output &a){
    double sum=0;
  for(int i=0;i<a.GetNumber();++i){
    sum+=a.GetPossible(i)*log(a.GetPossible(i))/log(2);
  }
  sum*=-1;
  return sum;
}


void head::PrintTable(input &a){
  std::cout<<"\n\n\tX:\t";
  for(int i=0;i<a.GetNumber();++i){
    std::cout<<" "<<a.GetValues(i)<<"\t";
  }
 std::cout<<"\n\tP(x):\t";
  for(int i=0;i<a.GetNumber();++i){
    std::cout<<a.GetPossible(i)<<"\t";
  }
  
}

void head::PrintTable(output &a){
  std::cout<<"\n\n\tZ:\t";
  for(int i=0;i<a.GetNumber();++i){
    std::cout<<" "<<a.GetValues(i)<<"\t";
  }
 std::cout<<"\n\tP(z):\t";
  for(int i=0;i<a.GetNumber();++i){
    std::cout<<a.GetPossible(i)<<"\t";
  }
  std::cout<<"\n\n\tP(i,j):\t";
  for(int i=0;i<a.GetNumDblPoss();++i){
    std::cout<<a.GetDoublePoss(i)<<"\t";
    if((i+1)%a.GetNumber()==0 )std::cout<<"\n\t\t";
  }
  
}

double head::Shennon(input &b,output &a){
  double sum=intropy(b)+intropy(a)-a.DblIntropy();
  return sum;
}

int input::GetNumber(){
  return number;
}
  

double input::GetValues(int i){
  return Values[i];
}
  
double input::GetPossible(int i){
  return Possibility[i];
}

void input::SetValues(int i,double a){
    Values[i]=a;
}
void input::SetPossible(int i,double a){
  Possibility[i]=a;
}
 
 
 
 void output::AddElemValues(double a){
  Values.push_back(a);
}
  
void output::AddElemPoss(double a){
  Possibility.push_back(a);
}
    
double output::GetValues(int i){
  return Values[i];
}
  
double output::GetPossible(int i){
  return Possibility[i];
}

void output::SetValues(int i,double a){
    Values[i]=a;
}
void output::SetPossible(int i,double a){
  Possibility[i]=a;
}

int output::GetNumber(){
  return Values.size();
}

void output::DelPoss(int i){
 Possibility.erase(Possibility.begin() + i);
}
void output::DelValues(int i){
   Values.erase(Values.begin() + i);
}

void output::AddDoublePoss(double a){
  DoublePoss.push_back(a);
}

void output::SetDoublePoss(int i,double a){
 DoublePoss[i]=a; 
}
double output::GetDoublePoss(int i){
  return DoublePoss.at(i);
}
int output::GetNumDblPoss(){
  return DoublePoss.size();
}

void output::SetSizeDblPoss(int a, int b){
  DoublePoss.resize(a*b);
}


head::~head(){
  std::cout<<"\n";
delete[] Tables;
  
}

double miniCalc(double a, char s, double b){
  switch(s){
    case '/':return a/b;break;
    case '+':return a+b;break;
    case '-':return a-b;break;
    case '*': return a*b;break;
    default: return -1;
  }
}
  
