#include <iostream>
#include <queue>
using namespace std;
#define VERTEX 20

class Graph {
public:
    Graph() { vertices = 0; };
    void Read();
    void BreadthSearch(int v0);
    void Display();
    void Visit(int vertex);
private:
    int vertices;
    int graph[VERTEX][VERTEX];
};

void Graph::Display()
{
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++)
            cout << " " << graph[i][j];
        cout << endl;
    }
}
void Graph::Visit(int vertex)
{
    cout << " " << vertex;
}

void Graph::Read(){
    int m, n;
    cin >> m >> n;
    for(int i=0; i<vertices; i++)
        for(int j=0; j<vertices; j++)
            graph[i][j] = 0;
    vertices = m;
    for(int i=0; i<n; i++){
        int a, b;
        cin >> a >> b;
        graph[a][b] = 1; graph[b][a] = 1;
    }
}

void Graph::BreadthSearch(int v0){
    int visited[vertices] = {0};
    queue<int> qq;
    qq.push(v0);
    while(!qq.empty()){
        int cur = qq.front();
        qq.pop();
        visited[cur] = 1;
        for(int i=0; i<vertices; i++){
            if(graph[cur][i] == 1 && visited[i] == 0){
                qq.push(i);
            }
        }
        cout << cur << " ";
    }
    cout << endl;
}

int  main(){
    Graph gh;
    gh.Read();
    gh.BreadthSearch(0);
    gh.BreadthSearch(2);
    return 0;
}
