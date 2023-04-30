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

// T:O(nlogn) S:O(n)
int countInversion2(int arr[],int temp[],int left,int mid,int right){
    int i = left,j = mid,k = left,count = 0;

    while((i<=mid) && (j<=right)){
      if(arr[i] <= arr[j])
        temp[k++] = arr[i++];
      else{
        temp[k++] = arr[j++];
        count = count + (mid - i);
      }
    }

    while(i <= mid - 1)
      temp[k++] = arr[i++];

    while(j<= right)
      temp[k++] = arr[j++];  
    
    for(int i=left;i<=right;i++)
      arr[i] = temp[i];

    return count;  

}

int getInversion(int arr[],int low,int high,int temp[]){
    int mid = 0,count = 0;

    if(high > low){

      mid =( low + (high - low)/2);

      count += getInversion(arr,low,mid,temp);
      count += getInversion(arr,mid+1,high,temp);

      count += countInversion2(arr,temp,low,mid+1,high);
    }

    return count;
}


int main(){

  int n;
  cout<<"Enter number of elements:"<<endl;
  cin>>n;
  // countInversion(n);

  int arr[n];
  int temp[n];
  cout<<"Enter array elements:"<<endl;
  for(int i=0;i<n;i++)
    cin>>arr[i];

  int totalinversion = getInversion(arr,0,n-1,temp);
  cout<<"Number of Inversion: "<<totalinversion<<endl;
  return 0;
}