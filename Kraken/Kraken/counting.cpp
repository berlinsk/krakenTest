//
//  counting.cpp
//  Kraken
//
//  Created by Берлинский Ярослав Владленович on 01.03.2021.
//

#include "counting.hpp"

/// Getting a name of team from line

string nameOfTeam(string line, int length, int &index){
    string result = "";
    index = 0;
    while ( line[index] != ',' ) {
        result = result + line[index];
        index++;
    }
    return result;
}

void delLines(vector<string> &line, string *Del, int *n, int size){
    int col;
    for (int i = 0; i<*n; i++){
        for (int j = 0; j<size; j++){
        if(nameOfTeam(line[i], line[i].size(), col)==Del[j]){
            line.erase(line.begin()+i);
            (*n)--;
        }
    }
}
}

/// comparising Goals and Cancels
int scoreComparising(int scoredGoals, int canceledGoals){
    if (scoredGoals>canceledGoals) {
        return 3;
    }
    else return (scoredGoals<canceledGoals)? 0 : 1;
}

void getScore(vector<string> line, int *numberOfLines, string *teams, int *GoalsArray, int *differenceArray, int *CancelsArray, int *ResultedScoreArray, string *Del, int dsize){
    
    delLines(line, Del, numberOfLines, dsize);
    
    int row = 0;              // for moving through the lines
    int col = 0;              // for moving through the columns
    int goals = 0;            // num goals for each team
    int cancels = 0;          // num canceled goals for each team
    
    for (int i = 0; i<*numberOfLines; i++){
        
        teams[i] = nameOfTeam(line[i], line[i].size(), col);   // getting a name of each team
        ResultedScoreArray[i] = 0;          // initially on each line a number of points must be equal to 0
        GoalsArray[i] = 0;                  // number of goals for each team must be equal to 0 initially
        CancelsArray[i] = 0;                // the same is for Cancels
        differenceArray[i] = 0;             // and for differences
        
        for (int j = col; j < line[i].size(); j++){
            if (line[i][j-1] ==',' && line[i][j+1] == ':'){  // goals're stayin btw ',' and ':'
                goals = int(line[i][j] - 48);  // cause '48' in ASCII is a zero
                GoalsArray[i] = GoalsArray[i] + goals; // filling an arr with goals
            }
            if (line[i][j-1] ==':' && (line[i][j+1] == ',' || j+1==line[i].size())){
                cancels = int(line[i][j] - 48);
                CancelsArray[i] = CancelsArray[i] + cancels; // filling an arr with cancels
                ResultedScoreArray[i] = ResultedScoreArray[i] + scoreComparising(goals, cancels);//adding points
            }
        }
        differenceArray[i] = GoalsArray[i] - CancelsArray[i];
        row++;
        col=0;  // before moving to another line an index of column must be annuled
    }
}
