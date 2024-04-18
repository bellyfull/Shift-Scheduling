#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <unordered_map>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
int remaining(const string& str, unsigned int start);
bool combos(std::string& in, unsigned int idx, std::string floating, const set<std::string>& dict, set<std::string>& results);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code herecl
    set<std::string> results;
    std::string input = in;
    combos(input, 0, floating, dict, results);
    return results;
}

int remaining(const string& str, unsigned int start) { // finds num of spaces left '-'
  return count(str.begin() + start, str.end(), '-');
}

// Define any helper functions here

bool combos(std::string& in, unsigned int idx, std::string floating, const set<std::string>& dict, set<std::string>& results) {
    // static unordered_map<string, bool> used;
    if (idx == in.size()) { // if 'floating' is all used and reached the end of the 'in' list
        // cout <<"checking dict for "<< in << endl;
        if (floating.empty() && dict.find(in) != dict.end()) { // if in is a word of the dictionary
            // if not findable in dict, will return the end of the set
            // cout << " found in dict" << endl;
            results.insert(in);
            // cout <<"added: " << in << endl;
            return true;
        }
        return false; // hasn't been found 
    }

    if(in[idx] == '-') { // currently filling one space at a time
        bool found = false;
        int spacesleft = remaining(in, idx);
        // int remaining = count(in.begin()+idx, in.end(),'-');


        if (spacesleft == floating.size()) { // if num of spaces left == number of chars left in floating
          for (unsigned int i=0; i < floating.size(); i++) { // try every letter in 'floating' list
              std::string temp = in;
              temp[idx] = floating[i];
              std::string next = floating.substr(0,i) + floating.substr(i+1); // removing letter from floating string
              // cout << "trying floating letter "<< floating[i] << " at position "<< idx << endl;  
              if (combos(temp, idx + 1, next, dict, results)) { // calls next idx with new floating   
                found = true;
              }
          } 
        }
         else { // try all floating letters
            for (unsigned int i=0; i < floating.size(); i++) { // try every letter in 'floating' list
              std::string temp = in;
              temp[idx] = floating[i];
              std::string next = floating.substr(0,i) + floating.substr(i+1); // removing letter from floating string
              // cout << "trying floating letter "<< floating[i] << " at position "<< idx << endl;
              if (combos(temp, idx + 1, next, dict, results)) { // calls next idx with new floating   
                found = true;
              }
            }
            if (spacesleft>floating.size()) { // if remaining spaces fill w arbitrary chars
              for (char c = 'a'; c<='z'; c++) {
                if (floating.find(c) == string::npos) {
                  // std::string temp = in;
                  // temp[idx] =c;
                  in[idx] =c;
                  if (combos(in, idx + 1, floating, dict, results)) { // calls next idx with new floating   
                    found = true;
                  }
                  in[idx]='-'; // relabel back to '-'
                }
              }
            }
        }
        return found;
    }    // cout << "current in:" << in << " idx: " << idx << " floating: " << floating;
     else { // (in[idx] != '-')  // if this isnt an empty space move to next idx
      return combos(in, idx + 1, floating, dict, results);
    }


    // else { // is an empty space in 'in'
    //     bool found = false;
    //     for (unsigned int i=0; i < floating.size(); i++) { // try every letter in 'floating' list
    //         std::string temp = in;
    //         temp[idx] = floating[i];
    //         std::string next = floating.substr(0,i) + floating.substr(i+1); // removing letter from floating string
    //         combos(temp, idx+1, next, dict, results); // calling on next idx
    //     }

    //     //filling in remaining slots for potential words
    //     for (char c = 'a'; c<='z'; c++) {
    //         if (floating.find(c)!= std::string::npos) continue;
    //         in[idx] = c;

    //         combos(in, idx+1, floating, dict, results);
    //     }
    //     return found;
    // }
    // return false; // no solution
}