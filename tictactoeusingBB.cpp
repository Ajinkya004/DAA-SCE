#include<bits/stdc++.h>
using namespace std;
// an global array which is our board 
vector<vector<char>> board(3,vector<char>(3,'E'));
void printBoard(vector<vector<char>>&board){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool allFull(){
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board.size();j++){
            if(board[i][j]=='E'){
                return false;
            }
        }
    }
    return true;
}
int getWinner(){
    // check rows for winner 
    for(int i=0;i<board.size();i++){
        if(board[i][0]!='E' and board[i][0]==board[i][1] and board[i][1]==board[i][2] and board[i][0]==board[i][2]){
            return  (board[i][0] == 'X' ? 1 : -1);
        }
    }
    // check column for winner
    for(int i=0;i<board.size();i++){
        if(board[0][i]!='E' and board[0][i]==board[1][i] and board[1][i]==board[2][i] and board[0][i]==board[2][i]){
             return  (board[i][0] == 'X' ? 1 : -1);
        }
    }
    // check diagonal for winner 
      if (board[0][0] != 'E' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return (board[0][0] == 'X' ? 1 : -1);
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return (board[0][2] == 'X' ? 1 : -1);
    // if non of the condtion above is true than we return zero which tells us that there is a draw
   if(allFull){
      return 0;
   }
   else{
    return 3;
   }
}
void placeMarkbyCode(){

}
void placeMarkbyPlayer(){
    int r,c;
    cout<<"ROW : "<<endl;
    cin>>r;
    cout<<"COLUMN : "<<endl;
    cin>>c;
    if(board[r][c]!='E'){
        board[r][c]='O';
    }
    else{
        cout<<"The place is already occupied please enter other co-ordinates"<<endl;
    }
    
}
int main(){
    board={{'O','X','X'},
          {'X','O','O'},
          {'X','O','O'} };
     int winner=getWinner();
     if(winner==1){
        cout<<"X Wins"<<endl;
     }
     else if(winner==-1){
        cout<<"O wins"<<endl;
     }
    else{
        cout<<"Draw"<<endl;
    }

}