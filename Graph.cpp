#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
	int v_num;
	int e_num;
	vector<vector<int>> map;
public:
	Graph(): v_num(0), e_num(0) {}
	~Graph(){}
	Graph(int n): v_num(n), e_num(0) {
		map.resize(n);
		for(int i=0; i<n; i++)
			map[i].resize(n);
	}
	void push(int from, int to){
		if(map[from][to] == 1)
			return;
		map[from][to] = 1;
		map[to][from] = 1;
		e_num++;
	}
	void remove(int from, int to){
		if(map[from][to] == 0)
			return;
		map[from][to] = 0;
		map[to][from] = 0;
		e_num--;
	}
	int get_v_num(){ return v_num; }
	int get_e_num() { return e_num; } 
	void print_map() {
		for(int i=0; i<v_num; i++)
		{
			for(int j=0; j<v_num; j++)
				cout << map[i][j] << " ";
			cout << endl;
		}
	}
	void bfs( int start , int* visited){
		queue<int> Q;
		Q.push(start);
		visited[start] = 1;
		while(!Q.empty()){
			int tmp = Q.front();
			Q.pop();
			cout << tmp << " ";
			for(int i=0; i<v_num; i++)
			{
				if(map[tmp][i] == 1 && visited[i] == 0)
				{
					Q.push(i);
					visited[i] = 1;
				}
			}
		}
	}
	void dfs( int start , int* visited ){
		visited[start] = 1;
		cout << start << " ";
		for(int i=0; i<v_num; i++)
		{
			if(map[start][i] == 1 && visited[i] == 0)
			{
				dfs( i , visited);
			}
		}
	}
};


int main(){
	Graph test(10);
	cout << "get_v_num : " << endl;
	cout << test.get_v_num() << endl;
	cout << "get_e_num : " << endl;
	cout << test.get_e_num() << endl;
	cout << "print_map : " << endl;
	test.print_map();
	test.push(1,2);
	test.push(2,3);
	test.push(2,4);
	test.push(1,4);
	test.push(1,5);
	test.push(5,4);
	test.push(4,6);
	cout << "print_map : " << endl;
	test.print_map();
	cout << "get_e_num : " << endl;
	cout << test.get_e_num() << endl;
	cout << "dfs : " << endl;
	int visited[test.get_v_num()] = {0};
	test.dfs(1, visited);
	for(int i=0; i<test.get_v_num(); i++)
		visited[i] = 0;
	cout << endl;
	cout << "bfs : " << endl;
	test.bfs(1, visited);
	for(int i=0; i<test.get_v_num(); i++)
		visited[i] = 0;
	cout << endl;
	return 0;
}