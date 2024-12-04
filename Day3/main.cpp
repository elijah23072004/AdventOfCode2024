#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include <fstream>
#include <climits>
#include <unordered_map>

std::string parseInput(std::string);
std::string readFile(std::string);
int exercise1(std::string);
int exercise2(std::string);

int main(int argc, char* argv[]){

    std::string input = parseInput(argv[1]);
    
    std::cout<<exercise2(input)<<std::endl;
    return 0;
}
void printVec(std::vector<int> values){
    for(int j=0;j<values.size();j++){
        std::cout<<values.at(j)<<" ";
    }
    std::cout<<std::endl;
}

int exercise1(std::string input){
    int sum =0;
    //shortest possible mul command is 8 characters
    for(int i=0;i<input.length()-8;)
    {
        if(input.substr(i,4) != "mul("){
            i++;
            continue;
        }
        i+=4;
        if(!isdigit(input.at(i))){
            continue;
        }
        int num1 = std::stoi(input.substr(i,3));
        if(num1<10){
            i+=1;
        }
        else if (num1<100){
            i+=2;
        }
        else{
            i+=3;
        }

        if(input.at(i) != ','){
            i++;
            continue;
        }
        i++;
        if(!isdigit(input.at(i))){
            continue;
        }
        int num2 = std::stoi(input.substr(i,3));

        if(num2<10){
            i+=1;
        }
        else if (num2<100){
            i+=2;
        }
        else{
            i+=3;
        }

        if(input.at(i)!=')'){
            continue;
        }
        sum+=num1*num2;
        i++;
        
    }

    return sum;
}



int exercise2(std::string input){
    int sum =0;
    bool enableInstructions= true;
    //shortest possible mul command is 8 characters
    for(int i=0;i<input.length()-8;)
    {
        if(!enableInstructions){
            if(input.substr(i,4)=="do()"){
                enableInstructions=true;
                i+=4;
                continue;
            }
            i++;
            continue;
        }
        if(input.substr(i,4) != "mul("){
            if(input.substr(i,7) == "don't()"){
                enableInstructions=false;
                i+=7;
                continue;
            }
            i++;
            continue;
        }
        i+=4;
        if(!isdigit(input.at(i))){
            continue;
        }
        int num1 = std::stoi(input.substr(i,3));
        if(num1<10){
            i+=1;
        }
        else if (num1<100){
            i+=2;
        }
        else{
            i+=3;
        }

        if(input.at(i) != ','){
            i++;
            continue;
        }
        i++;
        if(!isdigit(input.at(i))){
            continue;
        }
        int num2 = std::stoi(input.substr(i,3));

        if(num2<10){
            i+=1;
        }
        else if (num2<100){
            i+=2;
        }
        else{
            i+=3;
        }

        if(input.at(i)!=')'){
            continue;
        }
        sum+=num1*num2;
        i++;
        
    }

    return sum;
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
std::string parseInput(std::string fileName){

    std::string str = readFile(fileName); 
    return str;
}

