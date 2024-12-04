#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include <fstream>
#include <climits>
#include <unordered_map>

std::vector<std::string> parseInput(std::string);
std::string readFile(std::string);
int exercise1(std::vector<std::string>);
int exercise2(std::vector<std::string>);

int main(int argc, char* argv[]){

    std::vector<std::string> input = parseInput(argv[1]);
    
    std::cout<<exercise2(input)<<std::endl;
    return 0;
}
void printVec(std::vector<int> values){
    for(int j=0;j<values.size();j++){
        std::cout<<values.at(j)<<" ";
    }
    std::cout<<std::endl;
}

int exercise1(std::vector<std::string> input){
    int count =0;
    
    for(int i=0;i<input.size();i++){
        std::string str = input.at(i);
        for(int j=0; j<str.length();j++){
            //std::cout<<"0";
            if(str.at(j) !='X'){
                continue;
            }
            //make sure not doing out of array indexes
            
            //cardinal directions first 
            //std::cout<<"1"<<std::endl;
            if(j>2){
                if(str.substr(j-3, 4) == "SAMX"){
                    count++;
                }
            }
            if(j< str.size()-3){
                if(str.substr(j,4) =="XMAS"){
                    count++;
                }
            }
            //std::cout<<"a"<<std::endl;
            if(i>2){
                std::string xmas = std::string()+str.at(j) + input.at(i-1).at(j) + 
                    input.at(i-2).at(j) + input.at(i-3).at(j);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<"b"<<std::endl;
            if(i< input.size()-3){
                std::string xmas = std::string()+ str.at(j) + input.at(i+1).at(j) +
                    input.at(i+2).at(j) + input.at(i+3).at(j);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<"c"<<std::endl;
            //left top
            if(j>2 && i>2){
                std::string xmas =  std::string()+ str.at(j) + input.at(i-1).at(j-1) +
                    input.at(i-2).at(j-2) + input.at(i-3).at(j-3);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<"d"<<std::endl;;
            //left bottom
            if(j>2 && i<input.size()-3){
                std::string xmas =  std::string()+str.at(j) + input.at(i+1).at(j-1) + 
                    input.at(i+2).at(j-2) + input.at(i+3).at(j-3);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<"e"<<std::endl;;
            //right top
            if(j<str.size()-3&& i>2){
                std::string xmas =  std::string()+str.at(j) + input.at(i-1).at(j+1) + 
                    input.at(i-2).at(j+2) + input.at(i-3).at(j+3);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<"f"<<std::endl;;
            //right bottom
            if((j<str.size()-3) && (i<input.size()-3)){
                std::string xmas =  std::string()+str.at(j) + input.at(i+1).at(j+1) + 
                    input.at(i+2).at(j+2) + input.at(i+3).at(j+3);
                if(xmas == "XMAS"){
                    count++;
                }
            }
            //std::cout<<std::endl;
        }
    }
    //std::cout<<std::endl;

    return count;
}



int exercise2(std::vector<std::string> input){
    int count =0;
    for(int i=1;i<input.size()-1;i++){
        std::string str = input.at(i);
        for(int j=1; j<str.length()-1;j++){
            if(str.at(j) != 'A'){
                continue;
            }
            char upLeft = input.at(i-1).at(j-1);
            char upRight = input.at(i-1).at(j+1);
            char bottomLeft = input.at(i+1).at(j-1);
            char bottomRight = input.at(i+1).at(j+1);
            int mCount=0;
            int sCount=0;

            if(upLeft == 'M')mCount++;
            if(upLeft =='S')sCount++;
            if(upRight=='M')mCount++;
            if(upRight=='S')sCount++;
            if(bottomLeft == 'M')mCount++;
            if(bottomLeft =='S')sCount++;
            if(bottomRight=='M')mCount++;
            if(bottomRight=='S')sCount++;
            
            if(upLeft==bottomRight){
                continue;
            }
            if(mCount != 2 || sCount != 2) continue;

            count++;
        }
    }
    return count;
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
std::vector<std::string> parseInput(std::string fileName){

    std::string str = readFile(fileName); 
    std::vector<std::string> lines;
    auto pos = str.find("\n");
    
    while(pos != std::string::npos){
        lines.push_back(str.substr(0,pos));
        str.erase(0,pos+1);
        pos=str.find("\n");
    }
    lines.push_back(str);
    return lines;
}

