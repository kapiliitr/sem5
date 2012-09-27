/*
 * Given an array of N nonnegative integers (representing a person's emotional value on each 
 *
 * day), the happiness in an interval is the sum of the values in that interval multiplied by the 
 *
 * smallest integer in that interval. Design an O(N log N) divide-and-conquer algorithm to find 
 *
 * the happiest interval. 
 */

/*
 * Author : Mohit Bakshi
 */

#include<iostream>
using namespace std;

class Node{
public:
  int start;
  int end;
  int value;
  Node(int st,int en,int val){
    start = st;
    end = en;
    value = val;
  }

  void print(){
    cout << "Start index : " << start << endl;
    cout << "End index : " << end << endl;
    cout << "Happyness value : " << value << endl;
  }
};

Node crossInterval(int* a,int low,int mid,int high){
  int temp_min = a[mid],min = a[mid];
  int temp = a[mid];
  int val = temp;
  int i=mid-1,j=mid+1;
  int left_ind=mid,right_ind=mid;
  while(i>=low || j<=high){
    if((j==high+1 && i>=low) || ((i>=low && j<=high) && (a[i] >= a[j]))){
      temp += a[i];
      if(a[i] < temp_min)
	temp_min = a[i];
      if(temp_min*temp > val*min){
	min = temp_min;
	val = temp;
	left_ind = i;
      }
      i--;
    }
    else if((i==low-1 && j<=high) || ((i>=low && j<=high) && (a[j] >= a[i]))){
      temp += a[j];
      if(a[j] < temp_min)
	temp_min = a[j];
      if(temp_min*temp > val*min){
	min = temp_min;
	val = temp;
	right_ind = j;
      }
      j++;
    }
  }
  Node b(left_ind,right_ind,val*min);
  return b;
}

Node happyInterval(int* a,int low,int high){
  if(low == high || high < low){
    Node b(low,low,a[low]);
    return b;
  }
  else{
    int mid = (low + high)/2;
    Node left = happyInterval(a,low,mid-1);             
    Node right = happyInterval(a,mid+1,high);
    Node cross = crossInterval(a,low,mid,high);
    if((left.value >= right.value) && (left.value >= cross.value))
      return left;
    else if((right.value >= left.value) && (right.value >= cross.value))
      return right;
    else
      return cross;
  }
}

int main(){
  int n;
  cin >> n;
  int a[n];
  for(int i=0; i<n;i++)
    cin >> a[i];
  Node ans = happyInterval(a,0,n-1);
  ans.print();
  return 0;
}
