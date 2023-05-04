#include<iostream>
#include<vector>
#include<queue> 
#include<utility>


const int BLOCK_SCORE = 50;
const int WIN_SCORE = 20;
const int CENTER_SCORE = 10;
const int CORNER_SCORE = 5;
const int EDGE_SCORE = 3;
int PLACES_OCCUPIED=0;

using namespace std;
// an global array which is our board 
vector<vector<char>> board(3,vector<char>(3,' '));
// a priority queue that holds a pair of cost of each move alongwith co-ordinates where we will place 
priority_queue<pair<int,pair<int,int>>>pq;
void printBoard()
{
    printf("\n\n");  
    printf("\t\t\t %c | %c | %c \n", board[0][0],board[0][1], board[0][2]);  
    printf("\t\t\t------------\n");  
    printf("\t\t\t %c | %c | %c \n", board[1][0],board[1][1], board[1][2]);  
    printf("\t\t\t------------\n");  
    printf("\t\t\t %c | %c | %c \n\n", board[2][0],board[2][1], board[2][2]);  
}
bool isFull(){
    return PLACES_OCCUPIED==9;
}
int getWinner()
{
    // check rows for winner 
    for(int i=0;i<board.size();i++){
        if(board[i][0]!=' ' and board[i][0]==board[i][1] and board[i][1]==board[i][2]){
            return  (board[i][0] == 'X' ? 1 : -1);
        }
    }
    // check column for winner
    for(int i=0;i<board.size();i++){
        if(board[0][i]!=' ' and board[0][i]==board[1][i] and board[1][i]==board[2][i] and board[0][i]==board[2][i]){
             return  (board[i][0] == 'X' ? 1 : -1);
        }
    }
    // check diagonal for winner 
      if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
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
    if ((board[row][0] == computer && board[row][1] == computer && board[row][2] == ' ') ||
    (board[row][0] == computer && board[row][1] == ' ' && board[row][2] == computer) ||
    (board[row][0] == ' ' && board[row][1] == computer && board[row][2] == computer))
    {
        return true;
    }
    

    // Check columns
    if ((board[0][col] == computer && board[1][col] == computer && board[2][col] == ' ') ||
    (board[0][col] == computer && board[1][col] == ' ' && board[2][col] == computer) || 
    (board[0][col] == ' ' && board[1][col] == computer && board[2][col] == computer))
    {
        return true;
    }
    

    // Check diagonals
    if (row == col)
    {
        if ((board[0][0] == computer && board[1][1] == computer && board[2][2] == ' ') ||
        (board[0][0] == computer && board[1][1] == ' ' && board[2][2] == computer) ||
        (board[0][0] == ' ' && board[1][1] == computer && board[2][2] == computer))
        {
            return true;
        }
    }

    if (row + col == 2)
    {
        if ((board[0][2] == computer && board[1][1] == computer && board[2][0] == ' ') ||
        (board[0][2] == computer && board[1][1] == ' ' && board[2][0] == computer) ||
        (board[0][2] == ' ' && board[1][1] == computer && board[2][0] == computer))
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
    if ((board[row][0] == user && board[row][1] == user && board[row][2] == ' ') ||
    (board[row][0] == user && board[row][1] == ' ' && board[row][2] == user) ||
    (board[row][0] == ' ' && board[row][1] == user && board[row][2] == user))
    {
        return true;
    }

    // Check columns
    if ((board[0][col] == user && board[1][col] == user && board[2][col] == ' ') ||
    (board[0][col] == user && board[1][col] == ' ' && board[2][col] == user) ||
    (board[0][col] == ' ' && board[1][col] == user && board[2][col] == user))
    {
        return true;
    }

    // Check diagonals
    if (row == col)
    {
        if ((board[0][0] == user && board[1][1] == user && board[2][2] == ' ') ||
        (board[0][0] == user && board[1][1] == ' ' && board[2][2] == user) ||
        (board[0][0] == ' ' && board[1][1] == user && board[2][2] == user))
        {
            return true;
        }
    }

    if (row + col == 2)
    {
        if ((board[0][2] == user && board[1][1] == user && board[2][0] == ' ') ||
        (board[0][2] == user && board[1][1] == ' ' && board[2][0] == user) ||
        (board[0][2] == ' ' && board[1][1] == user && board[2][0] == user))
        {
            return true;
        }
    }

    return false;
}
bool isFarThreat()
{
    if((board[0][0] == 'X' && board[0][1] == ' ' && board[0][2] == ' ' && board[1][0] == ' ' && board[1][1] == 'O' && board[1][2] == ' ' && board[2][0] == ' ' && board[2][1] == ' ' && board[2][2] == 'X') ||
    board[0][0] == ' ' && board[0][1] == ' ' && board[0][2] == 'X' && board[1][0] == ' ' && board[1][1] == 'O' && board[1][2] == ' ' && board[2][0] == 'X' && board[2][1] == ' ' && board[2][2] == ' ')
    {
        return true;
    }
    return false;
}
int getCostforPlace(int i,int j){
   int Cost=0;
   if(i==1 and j==1 and board[i][j]==' ')
   {
      Cost+=CENTER_SCORE+20;
   }
    if((i==0 && j==0) || (i==0 && j==2 ) || (i==2 && j==0) || (i==2 && j==2))
    {
        Cost+=CORNER_SCORE;
    }
    if((i==0 && j ==1) || (i==1 && j==0) || (i==1 && j==2) || (i==2 && j==1))
    {
        Cost+=EDGE_SCORE;
        if(isFarThreat())
        {
            Cost+=20;
        }
    }
   if(needToBlock(i,j))
   {
    Cost+=BLOCK_SCORE;
   }
   if(isWin(i,j))
   {
    Cost+=WIN_SCORE;
   }
   if(board[1][1]==' ')
   {
    Cost+=CENTER_SCORE;
   }
    return Cost;
}
void placeMarkbyCode()
{
       PLACES_OCCUPIED++;
       for(int i=0;i<board.size();i++){
            for(int j=0;j<board[0].size();j++){
                if(board[i][j]==' '){
                int cost=getCostforPlace(i,j);
                auto p=make_pair(i,j);
                auto q=make_pair(cost,p);
                pq.push(q);
                }
                else{
                    continue;
                }
            }
       }
       pair<int,pair<int,int>> t=pq.top();
       int r=t.second.first;
       int c=t.second.second;
       board[r][c]='O';
       cout<<"Computer Played..."<<endl;
       while(!pq.empty()){
        pq.pop();
       }
}
void placeMarkbyPlayer(){
    again:
    int r,c;
    cout<<"ROW COLUMN: "<<endl;  //1 based indexing
    cin>>r>>c;
    r--,c--;
    
    if(board[r][c]==' '){
        board[r][c]='X';
        cout<<endl;
        PLACES_OCCUPIED++;
    }
    else{
        cout<<"The place is already occupied please make another move!"<<endl;
        goto again;
    }
    
}
int main()
{
    board={{' ',' ',' '},
          {' ',' ',' '},
          {' ',' ',' '} };

    char first_move='N';
    cout<<"Do you want to play first? [Y/N]"<<endl;
    cin>>first_move;

    if(first_move=='Y')
    {   
        printBoard();
        while(!isFull())
        {
            placeMarkbyPlayer();
            printBoard();
            if(isFull()){
                break;
            }
            if(getWinner()==1)
            {
                cout<<"You win!!!"<<endl;
                return 0;
            }
            if(getWinner()==-1)
            {
                cout<<"Computer wins!!!"<<endl;
                return 0;
            }
            placeMarkbyCode();
            printBoard();
            if(isFull()){
                break;
            }
            if(getWinner()==1)
            {
                cout<<"You win!!!"<<endl;
                return 0;
            }
            if(getWinner()==-1)
            {
                cout<<"Computer wins!!!"<<endl;
                return 0;
            }
            
        }
        if(getWinner()==1){
            cout<<"You Win!!!!"<<endl;
        }
        else if(getWinner()==-1){
            cout<<"Computer Wins"<<endl;
        }
        else{
            cout<<"It's a draw!!!"<<endl;
        }
        
    }
    else
    {
        while(!isFull())
        {
            placeMarkbyCode();
            printBoard();
            if(isFull()){
                break;
            }
            if(getWinner()==1)
            {
                cout<<"You win!!!"<<endl;
                return 0;
            }
            if(getWinner()==-1)
            {
                cout<<"Computer wins!!!"<<endl;
                return 0;
            }
            placeMarkbyPlayer();
            printBoard();
            if(isFull()){
                break;
            }
            if(getWinner()==1)
            {
                cout<<"You win!!!"<<endl;
                return 0;
            }
            if(getWinner()==-1)
            {
                cout<<"Computer wins!!!"<<endl;
                return 0;
            }
            
        }
      if(getWinner()==1){
            cout<<"You Win !!!!"<<endl;
        }
        else if(getWinner()==-1){
            cout<<"Computer Wins"<<endl;
        }
        else{
            cout<<"It's a draw!!!"<<endl;
        }
    }
    return 0;
}