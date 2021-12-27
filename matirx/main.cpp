#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>

using namespace std;

void print(vector<vector<int>> matrix){
    int n=matrix.size();
    int line=0;
    cout<<"/ ";
    for(int j=0;j<n;j++){
        cout<<setw(2)<<j<<" ";
    }
    cout<<endl;
    for(auto v:matrix){
        cout<<line++<<" ";
        for(auto i:v){
            cout<<setw(2)<<i<<" ";
        }
        cout<<endl;
    }
}
bool valid(int i,int j,int n){
    return i<n && j<n && i>=0 && j>=0;
}
int value_1(int n,int a,int b,int i,int j){
    if(j<=i){
        return (2*n+j-i-a)*(j-i+a-1)/2+j+1;
    } else{
        return (2*n-a+1)*a/2+(2*n-j+i)*(j-i-1)/2+i+1;
    }
}
int value_2(int n,int a,int b,int i,int j){
    if(i==j){
        return i+(a-1)*(2*n-a)/2;
    }
    else if(i>j){
        return j+(2*n-a+j-i)*(a+j-i-1)/2;
    }
    else{
        int k=j-i;
        return (n+(n-a+1))*a/2+((n-1)+(n-k-1))*(k-1)/2+i;
    }
}
int value_3(int n,int a,int b,int i,int j){
    int ans=0;
    for(int k=1;k<=j-i+a-1;k++){
            if(k-a<0){
                ans+=n+k-a;
            }
            else{
                ans+=n-k+a;
            }
        }
    if(j<=i){
        ans+=j+1;
    }
    else{
        ans+=i+1;
    }
    return ans;
}

int main()
{
    int n=10;
    int a=3;
    int b=3;
    cout<<value_2(n,a,b,7,8)<<endl;
    vector<vector<int>> matrix;
    for(int i=0;i<n;i++){
        vector<int> temp(n,0);
        matrix.push_back(temp);
    }
    for(int i=0;i<n;i++){
        int j=i;
        for(int k=0;k<b;k++){
            if(valid(i+k,j,n)){
                matrix[i+k][j]=1;
            }
        }
        for(int k=0;k<a;k++){
            if(valid(i-k,j,n)){
                matrix[i-k][j]=1;
            }
        }
    }
    int counter=1;
    for(int i=n-1;i>=0;i--){
        int temp=i;
        int j=0;
        while(valid(i,j,n)&&matrix[i][j]!=0){
            matrix[i][j]=counter;
            i++;
            j++;
            counter++;
        }
        i=temp;
    }
    for(int j=1;j<n;j++){
        int temp=j;
        int i=0;
        while(valid(i,j,n)&&matrix[i][j]!=0){
            matrix[i][j]=counter;
            i++;
            j++;
            counter++;
        }
        j=temp;
    }
    print(matrix);
}