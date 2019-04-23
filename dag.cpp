#include <iostream>
#include <vector>
#include <algorithm>

#define VISITED true
#define UNVISITED false
#define INFINITE 1<<21

using namespace std;

//MAIN DATA STRUCTURE
vector<vector<pair<int,int>>> g;

vector<int> tSort;
vector<bool> visited;


//recursive function
void topologicalSort(int i)
{
  visited[i]=true;

  for(int j=0;j < g[i].size();j++)
  {
    pair<int,int> v = g[i][j];

    if(visited[v.first]==false)
      topologicalSort(v.first);
  }

  tSort.push_back(i);
}



int main() {
  
  int nV,nA,v,w;

  cout<<"Introduzca cantidad de vertices: ";
  cin>>nV;

  //insert information into a formal data structure
  for(int i=0;i<nV;i++)
  {
    cout<<"Introduzca cantidad de adyacencias para nodo "<<i<<": ";
    cin>>nA;

    //store adjacencies for current node
    vector<pair<int,int>> adj;

    for(int j=0;j<nA;j++)
    {
      cout<<"Introduzca nodo: ";
      cin>>v;

      cout<<"Introduzca costo: ";
      cin>>w;

      adj.push_back({v, w});        
    }

    //insert all the pairs to data structure
    g.push_back({adj});
  }

  //show input
  cout<<"\n\t INPUT";
  for(int i=0;i<g.size();i++)
  {
    cout<<"\n"<<i<<": ";

    for(int j=0;j<g[i].size();j++)
    {
      cout<<" {"<<g[i][j].first<<","<<g[i][j].second<<"} ";
    }
  }

  //TOPOLOGICAL SORTING!

  //set vector visited to false
  vector<bool> f(g.size(),UNVISITED);
  visited.assign(f.begin(),f.end());

  //sort..
  for(int i=0;i<nV;i++)
  {
    if(visited[i] == UNVISITED) topologicalSort(i);
  }

  //sorted output
  cout<<endl<<endl;
  reverse(tSort.begin(),tSort.end());


  for(int i=0;i<nV;i++)
  {
    cout<<tSort[i]<<endl;
  }

  //SSP algorithm
  vector <pair<int,int>> distance;
  
  //set source values
  distance.push_back({0,0});

  //set infinite for the rest
  for(int i=1;i<tSort.size();i++)
  {
    distance.push_back({tSort[i],INFINITE});
  }

  for(int i=0;i<g.size();i++)
  {    
    for(int j=0;j<g[i].size();j++)
    {      
      if(g[distance[i].first].size())
      {
        //find index for adjacency in tSort
        vector<int>::iterator it = std::find(tSort.begin(),tSort.end(), g[distance[i].first][j].first);
        
        //get index
        int index = std::distance(tSort.begin(), it);

        //adjacent of topo sort
        if(distance[i].second+g[distance[i].first][j].second < distance[index].second)
        {
          distance[index].second= g[distance[i].first][j].second;
        }
      }
    }
  }
 
  for(int i=0;i<distance.size();i++)
  {
    cout<<"El menor costo entre [0] y "<<"["<<distance[i].first<<"] es : "<<distance[i].second<<endl;
  }

}
