#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Node{
public:
    int index;
    int distance; //for Dij, the distance from the starting point to this point
    int visited;
    Node* predecessor;

    explicit Node(int input_index){
        index=input_index;
        distance=0;
        visited=0;
        predecessor=nullptr;
    }
    ~Node()= default;
};

class Edge{
private:
    typedef pair<Node,Node> EDGE;
    EDGE edge;
    int weight;

};

class Graph{
private:
    typedef pair<Node*,int> ADJACENCY_NODE; //node + weight of edge
    typedef vector<ADJACENCY_NODE> ADJACENCY_LIST;
    typedef vector<ADJACENCY_LIST> VERTICES;
    //ADJACENCY_NODE adj_node;
    //ADJACENCY_LIST adj_list;
    VERTICES vertices;
    int ver_num=0;
    int edge_num=0;
    int start_node=0;
    int end_node=0;
public:
//    Graph(){//file input
//        ifstream file;
//        file.open("input.txt");
//        if(!file) cout<<"open failed"<<endl;
//        file>>ver_num;
//        //VERTICES vertices((unsigned int)ver_num);
//        vertices=VERTICES((unsigned int)ver_num);
//        for(int i=0;i<ver_num;i++) {
//            Node* node=new Node(i);
//            ADJACENCY_NODE adj_node(node,0);
//            vertices[i].insert(vertices[i].begin(),adj_node);
//        }
//
//        file>>start_node;
//        file>>end_node;
//        int start_temp; int end_temp; int weight;
//        while(file>>start_temp>>end_temp>>weight){
//            ADJACENCY_NODE adj_node(vertices[end_temp].begin()->first,weight);
//            vertices[start_temp].push_back(adj_node);
//            edge_num++;
//        }
//        file.close();
//    }

    Graph(){//standard input
        cin >> ver_num;
        //VERTICES vertices((unsigned int)ver_num);
        vertices = *new VERTICES((unsigned int) ver_num);
        for (int i = 0; i < ver_num; i++) {
            Node *node = new Node(i);
            ADJACENCY_NODE adj_node(node, 0);
            vertices[i].insert(vertices[i].begin(), adj_node);
        }

        cin >> start_node;
        cin >> end_node;
        int start_temp;
        int end_temp;
        int weight;
        while (!cin.eof()) {
            cin >> start_temp >> end_temp >> weight;
            ADJACENCY_NODE adj_node(vertices[end_temp].begin()->first, weight);
            vertices[start_temp].push_back(adj_node);
            edge_num++;
        }
    }

    ~Graph(){
        for (int i = 0; i < ver_num; i++) {
            delete(vertices[i].begin()->first);
            //delete(&vertices[i]);
            //cout<<"deleted"<<endl;
        }
        //delete(&vertices);
    }
// ~Graph()= default;

    void Dijkstra(){
        //EFFECT: find the shortest path
        int visited_node=0;
       // auto curr_ver=vertices.begin()+start_node;
        VERTICES::iterator curr_ver;//=vertices.begin();
        for(auto &it:vertices){
            it.begin()->first->distance=2147483647/2;//max value of int
            it.begin()->first->visited=0;
        }
        vertices[start_node].begin()->first->distance=0;
        //vertices[start_node].begin()->first->visited=1;
        for(visited_node=0;visited_node<ver_num;visited_node++){
            curr_ver=nearest_unvisited();//first time will add start node
            if(curr_ver==vertices.end()) continue;
            curr_ver->begin()->first->visited=1;
            for(auto it2=curr_ver->begin()+1;it2!=curr_ver->end();it2++){//改过循环范围
                if(it2->second+curr_ver->begin()->first->distance < it2->first->distance)
                    it2->first->distance=it2->second+curr_ver->begin()->first->distance;
            }
        }
        if(vertices[end_node].begin()->first->distance==2147483647/2)
            cout<<"No path exists!"<<endl;
        else
            cout<<"Shortest path length is "<<vertices[end_node].begin()->first->distance<<endl;
    }

    VERTICES::iterator nearest_unvisited(){
        //EFFECT: find the nearest unvisited node
        auto nearest=vertices.end();
        for(auto it=vertices.begin();it!=vertices.end();++it){
            if(!it->begin()->first->visited){
                if(nearest==vertices.end()) nearest=it;
                else{
                    if(it->begin()->first->distance < nearest->begin()->first->distance)
                        nearest=it;
                }
            }
        }
        return nearest;
    }

    void DAG(){
        queue<ADJACENCY_LIST> Q;
        int in_degree[65536];
        for(int j=0;j<ver_num;j++) in_degree[j]=0;
        for(auto &it: vertices){
            for(auto it2=++it.begin();it2!=it.end();it2++){
                in_degree[it2->first->index]++;
            }
        }
        int sum=0;//record the number of nodes explored
        for(int i=0;i<ver_num;i++){
            if(in_degree[i]==0) Q.push(vertices[i]);
        }
        while(!Q.empty()){
            if (sum>ver_num){
                cout<<"The graph is not a DAG"<<endl;
                break;
            }
            ADJACENCY_LIST curr=Q.front();Q.pop();
            sum++;
            for(auto it3=curr.begin()+1;it3!=curr.end();it3++){
                if(--in_degree[it3->first->index]==0) Q.push(vertices[it3->first->index]);
            }
        }
        if(sum==ver_num) cout<<"The graph is a DAG"<<endl;
        else  cout<<"The graph is not a DAG"<<endl;
    }

//    void MST(){//directed
//        int visited_node=0;
//        int sum=0;
//        int curr_edge=0;
//        // auto curr_ver=vertices.begin()+start_node;
//        auto curr_ver=vertices.begin();
//        for(auto &it:vertices){
//            it.begin()->first->distance=2147483647;//max value of int
//            it.begin()->first->visited=0;
//        }
//        vertices[0].begin()->first->distance=0;
//        vertices[0].begin()->first->visited=0;
//        for(visited_node=0;visited_node<ver_num;visited_node++){
//            curr_ver=nearest_unvisited_MST(curr_ver);//first time will add start node
//            if(curr_ver==vertices.end()) continue;
//            curr_ver->begin()->first->visited=1;
//            sum+=curr_ver->begin()->first->distance;
//            for(auto &it2:*curr_ver) {
//                it2.first->distance = it2.second < it2.first->distance ? it2.second : it2.first->distance;
//            }
//
//            //sum+=curr_edge;
//        }
//        for(auto &it:vertices){
//            if(it.begin()->first->visited==0){
//                cout<<"No MST exists!"<<endl;
//                return;
//            }
//        }
//        cout<<"The total weight of MST is "<<sum<<endl;
//
//    }

    VERTICES::iterator nearest_unvisited_MST(){
        //EFFECT: find the nearest unvisited node
        auto nearest=vertices.end();
        for(auto it=vertices.begin();it!=vertices.end();++it){
            if(!it->begin()->first->visited){
                if(nearest==vertices.end()) nearest=it;
                else{
                    if(it->begin()->first->distance < nearest->begin()->first->distance)
                        nearest=it;
                }
            }
        }
        return nearest;
    }

    void MST_new(){//undirected
        int visited_node=0;
        int sum=0;
        //int curr_edge=0;
        // auto curr_ver=vertices.begin()+start_node;
        VERTICES::iterator curr_ver;//=vertices.begin();
        for(auto &it:vertices){
            it.begin()->first->distance=2147483647;//max value of int
            it.begin()->first->visited=0;
        }
        vertices[0].begin()->first->distance=0;
        vertices[0].begin()->first->visited=0;
        for(visited_node=0;visited_node<ver_num;visited_node++){
            curr_ver=nearest_unvisited_MST();//first time will add start node
            if(curr_ver==vertices.end()) continue;
            curr_ver->begin()->first->visited=1;
            sum+=curr_ver->begin()->first->distance;
//            for(auto &it2:*curr_ver) {
//                it2.first->distance = it2.second < it2.first->distance ? it2.second : it2.first->distance;
//            }
            for(auto &iter1: vertices){
                for(auto &iter2:iter1){
                    if(iter1==*curr_ver)
                        iter2.first->distance=iter2.second < iter2.first->distance ? iter2.second : iter2.first->distance;
                    if(iter2.first->index==curr_ver->begin()->first->index)
                        iter1.begin()->first->distance=iter2.second <iter1.begin()->first->distance ? iter2.second : iter1.begin()->first->distance;
                }
            }
            //sum+=curr_edge;
        }
        for(auto &it:vertices){
            if(it.begin()->first->visited==0){
                cout<<"No MST exists!"<<endl;
                return;
            }
        }
        cout<<"The total weight of MST is "<<sum<<endl;

    }

};



int main() {
//    ifstream file;
//    file.open("input.txt");
//auto g= new Graph();
//g->Dijkstra();
//g->DAG();
//g->MST_new();

    Graph g;
    g.Dijkstra();
    g.DAG();
    g.MST_new();

}