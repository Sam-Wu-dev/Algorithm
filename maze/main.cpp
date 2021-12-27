#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

int start_dir=0;
unordered_map<int,pair<int,int>> direction={
    {0,make_pair(-1,0)},
    {1,make_pair(-1,1)},
    {2,make_pair(0,1)},
    {3,make_pair(1,1)},
    {4,make_pair(1,0)},
    {5,make_pair(1,-1)},
    {6,make_pair(0,-1)},
    {7,make_pair(-1,-1)},
};
vector<vector<int>> maze={
    {0,1,0,0,1},
    {1,0,1,1,0},
    {1,1,1,1,0},
    {1,0,1,1,0},
    {1,1,0,0,0},
};
int n=maze.size();
stack<pair<pair<int,int>,int>> path;
pair<int,int> start_point(0,0);
pair<int,int> end_point(4,4);

bool inrange(pair<int,int> location){
    return location.first>=0 && location.second>=0 && location.first<n && location.second<n;
}

void print(pair<pair<int,int>,int> info){
    cout<<"("<<info.first.first<<","<<info.first.second<<")"<<endl;
}

pair<int,int> operator+(pair<int,int> a,pair<int,int>b){
    return make_pair(a.first+b.first,a.second+b.second);
}

int get_direction(pair<int,int> location){
    for(int d=0;d<8;d++){
        pair<int,int> dir=direction[(d+start_dir)%8]+location;
        if(inrange(dir) && maze[dir.first][dir.second]==0){
            return (d+start_dir)%8;
        }
    }
    return -1;
}
void go_through_maze(){
    path.push(make_pair(start_point,0));
    while(path.top().first!=end_point){
        print(path.top());
        pair<int,int> location=path.top().first;
        maze[location.first][location.second]=1;
        int shift=get_direction(location);
        while(shift==-1){
            if(path.empty()){
                return;
            }
            path.pop();
            location=path.top().first;
            shift=get_direction(location);
        }
        pair<int,int> offset=direction[shift];
        path.push(make_pair(make_pair(location.first+offset.first,location.second+offset.second),shift));
    }
    print(path.top());
}

int main()
{
    go_through_maze();
}