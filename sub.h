#ifndef SUB_H
#define SUB_H
#include<vector>
class input{
  int number;
  std::vector<double> Values;
  std::vector<double> Possibility;
  public:
    int GetNumber();
    input();
    double GetValues(int i);
    double GetPossible(int i);
    void SetValues(int i, double a);
    void SetPossible(int i, double a);    
};
class output{
  std::vector<double> Values;
  std::vector<double> Possibility;
  std::vector<double> DoublePoss;
  public:
    int GetNumber();
    void AddElemValues(double a);
    void AddElemPoss(double a);
    double GetValues(int i);
    double GetPossible(int i);
    void SetValues(int i,double a);
    void SetPossible(int i,double a);    
    void AddDoublePoss(double a); 
    void SetDoublePoss(int i,double a); 
    double GetDoublePoss(int i);
    void SetSizeDblPoss(int a, int b);
    int GetNumDblPoss();
    void DelPoss(int i);
    void DelValues(int i);
	double DblIntropy();
};

struct head{
  int SumTables;
  input *Tables;
  head();
  ~head();
 std::vector<double>  ValPos(input &a, input &b);
 int Intropy(input &a);
 int IntropyDouble(input &a, input &b);
 void PrintTable(input &a);
 void PrintTable(output &a);
 double intropy(input &a);
 double intropy(output &a);
 double Shennon(input &b, output &a); 
};

#endif 
