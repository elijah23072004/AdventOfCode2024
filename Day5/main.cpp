#include<iostream>
#include<vector>
#include<tuple>
#include<string>
#include <fstream>
#include <climits>
#include <unordered_map>
#include <array>

struct data{
    std::vector<std::array<int,2>> rules;
    std::vector<std::vector<int>> pageOrderings;
};

void printVec(std::vector<int>);
data parseInput(std::string);
std::string readFile(std::string);
int exercise1(data);
int exercise2(data);

int main(int argc, char* argv[]){

    data values = parseInput(argv[1]);
    std::cout<<exercise1(values)<<std::endl;
    std::cout<<exercise2(values)<<std::endl;
    return 0;
}
void printVec(std::vector<int> values){
    for(int j=0;j<values.size();j++){
        std::cout<<values.at(j)<<" ";
    }
    std::cout<<std::endl;
}

std::unordered_map<int, std::vector<int>> convertRulesToMap(std::vector<std::array<int,2>> rules){
    std::unordered_map<int, std::vector<int>> umap; 
    for(int i=0; i<rules.size();i++){
        std::array<int,2> rule = rules.at(i);
        if(umap.contains(rule[1])){
            umap.at(rule[1]).push_back(rule[0]);
        }
        else{
            std::vector<int> nums = {rule[0]};
            umap[rule[1]] = nums;
        }
    }
    return umap;        
}
int find(std::vector<int> nums, int value){
    int index =-1;
    
    for(int i=0;i<nums.size();i++){
        if(nums.at(i) ==value){
            return i;
        }
    }

    return index;
}

bool isValidPageOrdering(std::vector<int> pageOrder, std::unordered_map<int, std::vector<int>> umap){
    for(int j=0; j<pageOrder.size(); j++){
        if(umap.contains(pageOrder.at(j))){
            std::vector<int> nums = umap[pageOrder.at(j)];
            for(int k=pageOrder.size()-1; k>j;k--){
                int index = find(nums, pageOrder.at(k));
                if( index!=-1){
                    //std::cout<<"rule broken was "<<nums.at(index)<< "|" << pageOrder.at(j)<<std::endl;
                    return false; 
                    //}
                }
            }
        }
    }
    return true;
}

int exercise1(data data){
    std::unordered_map<int, std::vector<int>> umap = convertRulesToMap(data.rules); 
    int sum = 0;
    for(int i=0; i<data.pageOrderings.size();i++){
        std::vector<int> pageOrder = data.pageOrderings.at(i);
        //printVec(pageOrder);
        if(isValidPageOrdering(pageOrder, umap)){
            sum+=pageOrder.at((pageOrder.size()/2));
            //std::cout<<pageOrder.at((pageOrder.size()/2))<<std::endl;
        }

    }

    return sum;
}


bool isValidPageOrderingPart2(std::vector<int>& pageOrder, std::unordered_map<int, std::vector<int>> umap){
    bool valid = true;
    for(int j=0; j<pageOrder.size(); j++){
        if(umap.contains(pageOrder.at(j))){
            std::vector<int> nums = umap[pageOrder.at(j)];
            for(int k=pageOrder.size()-1; k>j;k--){
                int index = find(nums, pageOrder.at(k));
                if( index!=-1){

                    //std::cout<<"rule broken was "<<nums.at(index)<< "|" << pageOrder.at(j)<<std::endl;
                    valid=false;
                    
                    //swap both values so rule is valid 
                    int temp = pageOrder.at(j);
                    pageOrder.at(j) = pageOrder.at(k);
                    pageOrder.at(k) = temp;

                    //-1 since next loop will add 1 setting j to 0
                    j=-1;
                    break;
                }
            }
        }
    }
    return valid;
}

int exercise2(data data){
    std::unordered_map<int, std::vector<int>> umap = convertRulesToMap(data.rules); 
    int sum = 0;
    for(int i=0; i<data.pageOrderings.size();i++){
        std::vector<int> pageOrder = data.pageOrderings.at(i);
        if(!isValidPageOrderingPart2(pageOrder, umap)){
            sum+=pageOrder.at((pageOrder.size()/2));
        }
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

data parseInput(std::string fileName){

    
    std::vector<std::vector<int>> pages;
    std::vector<std::array<int,2>> rules;

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
    del = '|';
    int x;
    for(x=0; x<lines.size();x++){
        std::string line = lines.at(x);
        std::array<int,2> rule; 
        
        pos = line.find(del);
        
        if(line==""){
            x++;
            break;
        }

        rule[0] = std::stoi(line.substr(0,pos));
        rule[1] = std::stoi(line.substr(pos+1, line.length()));
        rules.push_back(rule);

    }

    del = ',';
    while(x<lines.size()){
        std::string line = lines.at(x);
        pos = line.find(del);
        std::vector<int> pageList; 
        while(pos != std::string::npos){
            pageList.push_back(std::stoi(line.substr(0,pos)));
            line.erase(0,pos+1);
            pos=line.find(del);
        }
        pageList.push_back(std::stoi(line));
        pages.push_back(pageList);
        x++;
    }

    return data{rules, pages};
}

