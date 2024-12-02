#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include <fstream>
#include <climits>
#include <unordered_map>

std::vector<std::vector<int>> parseInput(std::string);
std::string readFile(std::string);
int exercise1(std::vector<std::vector<int>>);
int exercise2(std::vector<std::vector<int>>);

int main(int argc, char* argv[]){

    std::vector<std::vector<int>> values = parseInput(argv[1]);
    
    std::cout<<exercise2(values)<<std::endl;
    return 0;
}
void printVec(std::vector<int> values){
    for(int j=0;j<values.size();j++){
        std::cout<<values.at(j)<<" ";
    }
    std::cout<<std::endl;
}

bool isValidPair(int num1, int num2, bool increasing){
    int diff = num1-num2;
    if((increasing && num2<=num1) || (!increasing && num2>=num1)){
        return false;
    }
    if (std::abs(diff) >3){
        return false;
    }
    return true;
}
bool isValidReport(std::vector<int> values){
    int lastVal;
    if(values.size()<2) return true;
    lastVal = values.at(0);
    bool increasing = values.at(1) > lastVal;
    int mult=-1;
    if(increasing)mult=1;
    
    for(int i=1; i<values.size();i++){
        if(!isValidPair(lastVal,values.at(i),increasing))return false;
        lastVal=values.at(i);
    }
    return true;
}

int exercise1(std::vector<std::vector<int>> values){
    int safeCount=0;
    for(int i=0;i<values.size();i++)
    {
        //check if report is valid
        if(isValidReport(values.at(i))){
            safeCount++;
        }
    }
    return safeCount;
}


bool isValidReportPart2(std::vector<int> values){
    int lastVal;
    if(values.size()<2) return true;
    std::vector<int> val3 = values;
    val3.erase(val3.begin());
    std::vector<int> val4 = values;
    val4.erase(val4.begin()+1);
    lastVal = values.at(0);
    bool increasing = values.at(1) > lastVal;
    int mult=-1;
    if(increasing)mult=1;
    for(int i=1; i<values.size();i++){
        if(!isValidPair(lastVal,values.at(i),increasing)){
            std::vector<int> val1 = values;
            val1.erase(val1.begin()+i);
            std::vector<int> val2=values;
            val2.erase(val2.begin()+i-1);
            return isValidReport(val1) || isValidReport(val2) || isValidReport(val3) || isValidReport(val4);
        
        }
        lastVal=values.at(i);
    }

    return true;
}



int exercise2(std::vector<std::vector<int>> values){
    int safeCount=0;
    for(int i=0;i<values.size();i++){
        if(isValidReportPart2(values.at(i))){
            safeCount++;
        }
    }
    return safeCount;
}

std::string readFile(std::string fileName){
    std::ifstream MyFile(fileName);
    std::string output;
    std::string line;
    while(getline ( MyFile, line)){
       output+=line+"\n"; 
    }
    output = output.substr(0,output.length()-1);
    return output;
}
std::vector<std::vector<int>> parseInput(std::string fileName){

    std::vector<std::vector<int>> values;
    std::string str = readFile(fileName); 
    std::string del = "\n";
    std::vector<std::string> lines;
    auto pos = str.find(del);
    
    while(pos != std::string::npos){
        lines.push_back(str.substr(0,pos));
        str.erase(0,pos+del.length());
        pos=str.find(del);
    }
    lines.push_back(str);
    for(int x=0; x<lines.size();x++){
        std::string line = lines.at(x);
        std::vector<int> report;
        pos = line.find(del);
        while(true){
            for(int i=0;i<line.length();i++){
                pos=-1;
                if(line.at(i)==' '){
                    pos=i;
                    break;
                }
            }
            if(pos==-1)break;
            if(line.length() <1){
                break;
            }
            report.push_back(std::stoi(line.substr(0,pos)));
            line=line.erase(0,pos+del.length());
        }
        report.push_back(std::stoi(line));
        //printVec(report); 
        values.push_back(report);
    }
    return values;
}

