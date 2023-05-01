#include<iostream>
#include<vector>
#include<queue> 
#include<utility>
#include<map>
const int WIN_SCORE = 100;
const int LOSS_SCORE = -100;
const int DRAW_SCORE = 0;
const int BLOCK_SCORE = 50;
const int WIN_SCORE = 20;
const int CENTER_SCORE = 10;
const int CORNER_SCORE = 5;
const int EDGE_SCORE = 3;
int PLACES_OCCUPIED=0;
map<pair<int,int>,int> mp;
/*mp[{0,0}]=5;
mp[{0,2}]=5;
mp[{2,0}]=5;
mp[{2,2}]=5;
mp[{1,1}]=10;
mp[{0,1}]=3;
mp[{1,0}]=3;
mp[{1,2}]=3;
mp[{2,1}]=3; */
using namespace std;
// an global array which is our board 
vector<vector<char>> board(3,vector<char>(3,'E'));
// a priority queue that holds a pair of cost of each move alongwith co-ordinates where we will place 
priority_queue<pair<int,pair<int,int>>>pq;
void printBoard()
{
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
bool isFull(){
    return PLACES_OCCUPIED==9;
}
int getWinner()
{
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
   if(isFull){
      return 0;
   }
   else{
    return 3;
   }
}
// Function to check if a move creates a threat
bool isWin(int row, int col)
{
    char computer = 'O';

    // Check rows
    if ((board[row][0] == computer && board[row][1] == computer && board[row][2] == 'E') ||
    (board[row][0] == computer && board[row][1] == 'E' && board[row][2] == computer) ||
    (board[row][0] == 'E' && board[row][1] == computer && board[row][2] == computer))
    {
        return true;
    }
    

    // Check columns
    if ((board[0][col] == computer && board[1][col] == computer && board[2][col] == 'E') ||
    (board[0][col] == computer && board[1][col] == 'E' && board[2][col] == computer) || 
    (board[0][col] == 'E' && board[1][col] == computer && board[2][col] == computer))
    {
        return true;
    }
    

    // Check diagonals
    if (row == col)
    {
        if ((board[0][0] == computer && board[1][1] == computer && board[2][2] == 'E') ||
        (board[0][0] == computer && board[1][1] == 'E' && board[2][2] == computer) ||
        (board[0][0] == 'E' && board[1][1] == computer && board[2][2] == computer))
        {
            return true;
        }
    }

    if (row + col == 2)
    {
        if ((board[0][2] == computer && board[1][1] == computer && board[2][0] == 'E') ||
        (board[0][2] == computer && board[1][1] == 'E' && board[2][0] == computer) ||
        (board[0][2] == 'E' && board[1][1] == computer && board[2][0] == computer))
        {
            return true;
        }
    }

    return false;
}


// Function to check if a move creates an immediate threat
bool needToBlock(int row, int col)
{
    char user = 'X';
    // Check rows
    if ((board[row][0] == user && board[row][1] == user && board[row][2] == 'E') ||
    (board[row][0] == user && board[row][1] == 'E' && board[row][2] == user) ||
    (board[row][0] == 'E' && board[row][1] == user && board[row][2] == user))
    {
        return true;
    }

    // Check columns
    if ((board[0][col] == user && board[1][col] == user && board[2][col] == 'E') ||
    (board[0][col] == user && board[1][col] == 'E' && board[2][col] == user) ||
    (board[0][col] == 'E' && board[1][col] == user && board[2][col] == user))
    {
        return true;
    }

    // Check diagonals
    if (row == col)
    {
        if ((board[0][0] == user && board[1][1] == user && board[2][2] == 'E') ||
        (board[0][0] == user && board[1][1] == 'E' && board[2][2] == user) ||
        (board[0][0] == 'E' && board[1][1] == user && board[2][2] == user))
        {
            return true;
        }
    }

    // if (row + col == 2)
    // {
    //     if ((board[0][2] == user && board[1][1] == user && board[2][0] == 'E') ||
    //     (board[0][2] == user && board[1][1] == 'E' && board[2][0] == user) ||
    //     (board[0][2] == 'E' && board[1][1] == user && board[2][0] == user))
    //     {
    //         return true;
    //     }
    // }

    return false;
}
bool isFarThreat()
{
    if((board[0][0] == 'X' && board[0][1] == 'E' && board[0][2] == 'E' && board[1][0] == 'E' && board[1][1] == 'O' && board[1][2] == 'E' && board[2][0] == 'E' && board[2][1] == 'E' && board[2][2] == 'X') ||
    board[0][0] == 'E' && board[0][1] == 'E' && board[0][2] == 'X' && board[1][0] == 'E' && board[1][1] == 'O' && board[1][2] == 'E' && board[2][0] == 'X' && board[2][1] == 'E' && board[2][2] == 'E')
    {
        return true;
    }
    return false;
}
int getCostforPlace(int i,int j){
   int Cost=0;
   if(isFarThreat()){
    Cost+=BLOCK_SCORE+20;
   }
  else if(needToBlock(i,j)){
    Cost+=BLOCK_SCORE;
   }
 else if(isWin(i,j)){
    Cost+=WIN_SCORE;
 }
 

}
void placeMarkbyCode(){
       PLACES_OCCUPIED++;
       for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                int cost=getCostforPlace(i,j);
                auto p=make_pair(i,j);
                auto q=make_pair(cost,p);
                pq.push(q);
            }
       }
       pair<int,pair<int,int>> t=pq.top();
       int r=t.second.first;
       int c=t.second.second;
       board[r][c]='O';
       while(!pq.empty()){
        pq.pop();
       }
}
void placeMarkbyPlayer(){
    int r,c;
    cout<<"ROW COLUMN: "<<endl;  //1 based indexing
    cin>>r>>c;
    r--,c--;
    if(board[r][c]=='E'){
        board[r][c]='X';
        PLACES_OCCUPIED++;
    }
    else{
        cout<<"The place is already occupied please make another move!"<<endl;
    }
    
}
int main()
{
    board={{'X','E','E'},
          {'E','O','E'},
          {'E','E','X'} };
    //  int winner=getWinner();
    //  if(winner==1){
    //     cout<<"X Wins"<<endl;
    //  }
    //  else if(winner==-1){
    //     cout<<"O wins"<<endl;
    //  }
    // else{
    //     cout<<"Draw"<<endl;
    // }
  while(getWinner()==3){
    while(!isFull()){
        placeMarkbyCode();
        printBoard();
        placeMarkbyPlayer();
        printBoard();
        if(getWinner()!=3)
        {
            break;
        }
    }
   


  }

    return 0;
}