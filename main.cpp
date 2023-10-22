/*
 * The program reads dictionary file and produces
 * output in the form of network ie node and its 
 * connected nodes.
 *
 * input -> 
 * ti transaction inquiry    
 * tm transaction maintenance   
 *
 * output ->
 * transaction ti tm
 * inquiry ti
 * maintenance tm
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef vector<string> SVector;
typedef unordered_map <string,SVector> Dict;

int main (int argc, char** argv){
  if(argc<2){
    cout << "give filename." << endl;
  }
  ifstream in(argv[1]);
  string line;
  string word;
  vector <string> words;
  Dict dict;
  while(getline(in,line)){
    istringstream ss(line);
    while(getline(ss,word,' ')){
      words.push_back(word);
    }
    
    for(int i=0;i<words.size();i++){
      if(dict.find(words[i])==dict.end()){
        dict.insert(make_pair(words[i],SVector()));
        dict[words[i]].push_back(words[0]);
      } else {
        if(find(dict[words[i]].begin(),
              dict[words[i]].end(),words[0])==
            dict[words[i]].end()){
          dict[words[i]].push_back(words[0]);
        }
      }
    }
    words.clear();
  }


  ofstream out("mdict.txt");
  Dict::iterator itr=dict.begin();
  while(itr!=dict.end()){
    cout << itr->first << ":";
    out << itr->first << ":";
    for(int i=0;i<(itr->second).size();i++){
      cout << (itr->second)[i] << ",";
      out << (itr->second)[i] << ",";
    }
    out << endl;
    cout << endl;
    itr++;
  }

  in.close();
  out.close();
  return 1;
}
