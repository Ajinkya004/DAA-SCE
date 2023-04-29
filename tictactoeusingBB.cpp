#include<bits/stdc++.h>
using namespace std;
void printBoard(vector<vector<char>>&board){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main(){
    vector<vector<char>> board(3,vector<char>(3,'E'));
    

}