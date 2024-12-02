#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include <fstream>
#include <climits>
#include <unordered_map>

std::tuple<std::vector<int>,std::vector<int>> parseInput(std::string);
std::string reedFile(std::string);
int exercise1(std::vector<int>, std::vector<int>);
int exercise2(std::vector<int>,std::vector<int>);
int main(int argc, char* argv[]){
    std::vector<int> values1, values2;

    tie(values1, values2) = parseInput(argv[1]);
    
    std::cout<<exercise2(values1,values2)<<std::endl;
    

    return 0;
}
int exercise1(std::vector<int> values1, std::vector<int> values2){
    int distance=0;
    while(!values1.empty()){
        int index1,index2,min1,min2;
        min1=values1.at(0)+1;
        min2=values2.at(0)+1;
        for(int i=0;i<values1.size();i++){
            if(values1.at(i) < min1){
                min1=values1.at(i);
                index1=i;
            }
            if(values2.at(i) < min2){
                min2=values2.at(i);
                index2=i;
            }
        }
        distance+= std::abs(min2-min1);
        values1.erase(values1.begin()+index1);
        values2.erase(values2.begin()+index2);

    }
    return distance;
}

int exercise2(std::vector<int> values1, std::vector<int> values2){
    int total=0;
    std::unordered_map<int,int> umap;
    for(int i=0; i<values1.size(); i++){
        int frequency=0;
        if(umap.contains(values1.at(i))){
            frequency=umap.at(values1.at(i));
        }
        else{
            for(int j=0; j<values2.size();j++){
                if(values2.at(j)==values1.at(i)){
                    frequency+=1;
                }
            }
            umap[values1.at(i)]=frequency;
        }
        total+=values1.at(i)*frequency;
    }

    return total;
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
std::tuple<std::vector<int>, std::vector<int>> parseInput(std::string fileName){

    std::vector<int> values1, values2;
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
        del = "   ";
        pos = lines.at(x).find(del);
        int num1 = std::stoi(lines.at(x).substr(0,pos));
        int num2 = std::stoi(lines.at(x).substr(pos+del.length()));
        values1.push_back(num1);
        values2.push_back(num2);
    }
    return std::make_tuple(values1, values2);
}

