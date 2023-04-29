#include<bits/stdc++.h>
using namespace std;

// Brute Force: O(n2)
// total inversion count: n*(n-1)/2
void countInversion(int n){
  int arr[n];
  cout<<"Enter array elements:"<<endl;
  for(int i=0;i<n;i++)
    cin>>arr[i];

  int inversioncount = 0;

  for(int i=0;i<n;i++)
    for(int j=i+1;j<n;j++)
      if(arr[i] > arr[j]){
        cout<<"("<<arr[i]<<" "<<arr[j]<<")"<<endl;
        inversioncount++;
      }  

  cout<<"Inversion Count: "<<inversioncount<<endl;        
}


int main(){

  int n;
  cout<<"Enter number of elements:"<<endl;
  cin>>n;
  countInversion(n);

  return 0;
}