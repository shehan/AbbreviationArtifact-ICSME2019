#include <string>
#include <fstream>
#include <iostream>
#include <set>
#include <cctype>
#include <limits>

//CSV contains 3 columns, so assign a number to each one
const unsigned int ORIGINAL_IDENTIFIER_COLUMN = 1;
const unsigned int ABBREV_EXPANSION_COLUMN = 2;
const unsigned int SPLIT_IDENTIFIER_COLUMN = 3;

void ParseGoldSet(std::string filename){
    std::ifstream filestream(filename);
    char currentChar;
    int column = 1; //csv columns are delimited by a ','. This along with the global consts above will help us remember which column we're parsing.
    std::string token;
    filestream.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //remove first line because it's a header line
    std::set<std::string> abbrevs;
    std::set<std::string> abbrevexpansions;
    while(filestream.get(currentChar)){
        switch(currentChar){
            case ',':{
                switch(column){
                    case ORIGINAL_IDENTIFIER_COLUMN:{   
                        std::cout<<"Original Identifier: "<<token<<std::endl;
                        break;
                    }
                    case ABBREV_EXPANSION_COLUMN:{
                        std::string expansion,abbrev;
                        bool seencolon = false;
                        for(char c : token){
                            if(c == ':'){
                                seencolon = true;
                            }
                            if(c == '-'){
                                std::cout<<"Abbrev and Expansion: "<<abbrev +":"+expansion<<std::endl;
                                abbrevs.insert(abbrev);
                                abbrevexpansions.insert(abbrev+expansion);
                                abbrev.clear();
                                expansion.clear();
                                seencolon = false;
                            }
                            if(c == ')'){
                                std::cout<<"Abbrev and Expansion: "<<abbrev +":"+expansion<<std::endl;
                                abbrevs.insert(abbrev);
                                abbrevexpansions.insert(abbrev+expansion);
                                abbrev.clear();
                                expansion.clear();
                                seencolon = false;
                            }
                            if(c != ':' && c != ')' && c != '(' && c != '-'){
                                if((std::isalpha(c) || std::isdigit(c) || ' ') && seencolon){
                                    expansion+=std::tolower(c);
                                }
                                if((std::isalpha(c) || std::isdigit(c) || ' ') && !seencolon){
                                    abbrev+=std::tolower(c);
                                }
                            }
                        }
                        break;
                    }
                    case SPLIT_IDENTIFIER_COLUMN:{
                        std::cout<<"Split Identifier: "<< token<<std::endl;;
                        break;
                    }
                }
                ++column;
                token.clear();
                break;
            }
            case '\n':{
                column = 1;
                token.clear();
                break;
            }
            default:{
                token+=currentChar;
            }
        }

    }
    std::cerr<<"A: "<<abbrevs.size()<<std::endl;
    std::cerr<<"AEX: "<<abbrevexpansions.size()<<std::endl;
}

int main(int argc, char** argv){
  if(argc < 2){ 
    std::cerr<<"Syntax: ./executable [.csv file name]"<<std::endl;
    exit(1);
  }
  ParseGoldSet(argv[1]);
}