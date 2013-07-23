// Well_Covered.cpp
char input[256]  = "/Users/dimitryvin/Desktop/graphs.txt";
char output[256] = "/Users/dimitryvin/Desktop/sdfsdf.txt";

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>


using std::stringstream;
using std::ifstream;
using std::cout;
using std::endl;
using std::string;
using std::getline;
using std::vector;
using std::copy;
using std::istream_iterator;
using std::back_inserter;
using std::istringstream;
using std::ofstream;
using std::atoi;
using std::cin;
using std::exception;
using std::cerr;

// Graph structure
struct graph{
	vector<string> vertices;
	vector<string> edges;
};

string adj_vtc;

//Reader Functions
string convert_strint_to_strchar(string);
string convert_int_to_strchar(int);
void check_if_vertex_exists(vector<string> &, const string);
void trim(string&);

//Deconstructor Functions
bool descending(int ,int );
bool well_covered(vector<string> ,vector<string> ,string ,string&,string&);
bool check_if_empty(vector<string> );
bool well(string );
int check_same_edges(vector<int> );
void deconstruct(graph , int ,string& );
void delete_adjacent_vetices_and_edges(string ,graph& ,int );
void delete_same_edges(vector<int>& );
void find_adjacent_vertices(string& ,graph ,int );


int main(int argc, char* argv[]) {
    
    //line on the file
    string line;
    
    //get the file
    ifstream inGraphs(input);
    ofstream onGraphs(output);
    
    cout << "Initializing..." << endl << endl;
    //cout << inGraphs.good();
    //if the file is good
    if (inGraphs.good()) {
        
        //are we currently in a graph
        bool inGraph = false;
        
        //which graph are we on
        int onGraph = 0;
        
        //create the convtainers
        vector<string> vertices;
        vector<string> edges;
        string name = "a";
        int liner = -1;
        
        //count num vertices
        int v_count = 0;
        
        //while we haven't hit the bottom and we can still get line contents
        while(!inGraphs.eof()) {
            
            //increment the line
            ++liner;
            
            getline(inGraphs, line);
            
            trim(line);
            
            if (liner == 2){
                name = line;
            }
            //are we at the beginning of a graph?
            if (!inGraph) {
                
                //yes, then increment in indicate that we're in a graph
                onGraph++;
                inGraph = true;
                
                vertices.clear();
                edges.clear();
                
                //are we at the end of the graph?
            } else if (line == "$" && inGraph) {
                
                liner = 0;
                
                inGraph = false;
                
				onGraphs << "Graph " << name << " is ";
				
				string set_1;
				string set_2;
				
				if (well_covered(vertices,edges,name,set_1,set_2)) {
                    
				    onGraphs << "Well Covered" << '\n';
				    onGraphs << set_1 << '\n';
				    onGraphs << set_2 << '\n';
				    
                } else {
                    onGraphs << "Not Well Covered" << '\n';
                    onGraphs << set_1 << '\n';
				    onGraphs << set_2 << '\n';
                    
                }
                
                //Prevents ofstream from 'overflowing'
                onGraphs.flush();
				
                //time to read the data of the graph, line by line
            } else if (line.at(0) == '-') {
                
                v_count++;
                
                //remove the "-" at the beginning
                line.erase(0, 1);
                
                istringstream iss(line);
                
                //split the string at each " "
                vector<string> tokens;
                
                copy(istream_iterator<string>(iss),
                     istream_iterator<string>(),
                     back_inserter<vector<string> >(tokens));
                
                //get the initial vertice
                string main_v = convert_strint_to_strchar(tokens.at(0));
                
                check_if_vertex_exists(vertices, main_v);
                
                //iterate through the items after the main vertice
                for (int i = 0; i < tokens.size(); i++) {
                    
                    //we've reached the end of the graph, so break
                    if (tokens[i] == "0") {
                        
                        v_count = 0;
                        
                        break;
                        
                    }
                    
                    //get the vertice
                    string v = convert_strint_to_strchar(tokens[i]);
                    
                    check_if_vertex_exists(vertices, v);
                    
                    
                    //no loops
                    if (main_v != v)
                        edges.push_back(main_v + v);
                    
                    
                    
                }
                
            }
            
        }
        
        liner = 0;
        
        inGraph = false;
        
		onGraphs << "Graph " << name << " is ";
		
		string set_1;
		string set_2;
        
		if (well_covered(vertices,edges,name,set_1,set_2)) {
            
            onGraphs << "Well Covered" << '\n';
            onGraphs << set_1 << '\n';
            onGraphs << set_2 << '\n';
            
        } else {
            onGraphs << "Not Well Covered" << '\n';
            onGraphs << set_1 << '\n';
            onGraphs << set_2 << '\n';
            
        }
        
        
        //didn't open file
    } else
        cout << "Could not read file.";
    
    //close file stream
    
    inGraphs.close();
    onGraphs.close();
    
    //system("PAUSE");
    
    return EXIT_SUCCESS;
    
}

void check_if_vertex_exists(vector<string> &vertices_vector, const string vertex) {
    
    bool exists = false;
    
    for (int i = 0; i < vertices_vector.size(); i++) {
        if (vertices_vector[i] == vertex)
            exists = true;
    }
    
    if (!exists)
        vertices_vector.push_back(vertex);
    
    
}

//converts a integer string to a letter in the alphabet (ASCII)
string convert_strint_to_strchar(string str) {
    
    stringstream ss;
    
    //conversion done here
    string s;
    
    char char_holder = (char)(64 + atoi(str.c_str()));
    
    ss << char_holder;
    ss >> s;
    
    return s;
}

string convert_int_to_strchar(int num) {
    
    stringstream ss;
    
    //conversion done here
    string s;
    char char_holder = (char)(64 + num);
    
    ss << char_holder;
    ss >> s;
    
    return s;
    
}

void trim(string& str)
{
    string::size_type pos = str.find_last_not_of(' ');
    if(pos != string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        if(pos != string::npos) str.erase(0, pos);
    }
    else str.erase(str.begin(), str.end());
}

//Deconstructor Functions

void find_adjacent_vertices(string& adj_vtc,graph input_graph,int index){
    
	vector<string> strvector = input_graph.edges;
	vector<string> vertices_vector = input_graph.vertices;
	//For each edge, append the vertex adjacent to a given vertex
	for(int j=0; j<strvector.size(); j++){
		string str = strvector[j];
		string vertex = vertices_vector[index];
		if (str[0] == vertex[0]){
			adj_vtc.push_back(str[1]);
		}
		if (str[1] == vertex[0]){
			adj_vtc.push_back(str[0]);
		}
	}
}

//Sort Tool
bool descending(int i,int j) {
	return (i>j);
}

//Removes redundant elements
void delete_same_edges(vector<int>& kill_list) {
	int l = kill_list.size()-1;
	for(int i=0;i<l;i++){
		if (kill_list[i]==kill_list[i+1]){
			kill_list.erase(kill_list.begin()+(i));
			break;
		}
	}
    
}

//Returns number of duplicate elements in sorted set
int check_same_edges(vector<int> kill_list){
	int j = 0;
	int l = kill_list.size()-1;
	for(int i=0;i<l;i++){
		if (kill_list[i]==kill_list[i+1]){
			j++;
		}
	}
	return j;
    
}


//Empty: Return 1
bool check_if_empty(vector<string> vertices){
	if (vertices.size()==0){
		return 1;
	}
	else return 0;
}


//Determines if every element in string is identical
bool well(string s){
    
	for(int i = 0; i < (s.size()-1) ;i++){
		if(s[i] != s[i+1]){
			return 0;
		}
	}
	return 1;
    
}

//Given a vertex, removes all adjacent vertices and edges, itself included.
void delete_adjacent_vetices_and_edges(string adj_vtc,graph& input_graph,int index){
    
	vector<string>& strvector = input_graph.edges;
	vector<string>& vertices_vector = input_graph.vertices;
    
	find_adjacent_vertices(adj_vtc,input_graph,index);
    
	//Create Kill List of edges
	vector<int> kill_list;
	
	//For each adjacent vertex
	for(int k=0;k<adj_vtc.length();k++){
        
	    //For Every Edge
		for(int l=0;l<strvector.size();l++){
            
			string str = strvector[l];
			
			//If either vertex on an edge is adjacent to our original, add the edge to the kill list
			if (str[0]==adj_vtc[k] || str[1]==adj_vtc[k])
                
				kill_list.push_back(l);
		}
	}
	
	//Sorts kill list
	std::sort(kill_list.begin(),kill_list.end());
	
	//Removes duplicate edges from our list
	int s = check_same_edges(kill_list);
	for(int l=0;l<s;l++){
		delete_same_edges(kill_list);
	}
	
	//Sorts kill list
	std::sort(kill_list.begin(),kill_list.end(),descending);
    
	//Delete Edges
	for(int m=0;m<kill_list.size();m++){
		strvector.erase(strvector.begin()+kill_list[m]);
	}
    
	//Create Vector Kill list, append initial vertex, sort
	std::string vectors_to_kill = adj_vtc;
	vectors_to_kill.append(vertices_vector[index]);
	std::sort(vectors_to_kill.begin(),vectors_to_kill.end(),descending);
    
	//Delete vertices
	for(int m=0;m<vectors_to_kill.size();m++){
        
		for(int i=0;i<vertices_vector.size();i++){
            
			if (vectors_to_kill[m]==(vertices_vector[i])[0]){
                
				vertices_vector.erase(vertices_vector.begin()+(i));
			}
		}
	}
    
}

//Recursive function that checks all possible coverings of a graph
void deconstruct(graph input_graph, int iss,string& Isss,string& set_1,string& set_2,string ccs,int& index){
    
    
    
    //If the graph has no more valid vertices, append dominating set size to Isss
	if(check_if_empty(input_graph.vertices)){
        
		Isss.push_back(iss + '0');
		
		//If this was the first covering set
		if(Isss.size()==1){
            //Make our first checking set be the first covering
            set_1 = ccs;
		}
		//If our our current set is not the same as the first one, make it the second set
		int s = Isss.size();
		
        if(Isss[index] != Isss[0]){
            set_2 = ccs;
		}
		//Reset the current string
		ccs = "";
		//Increment index of # of covers
		++index;
	}
    
	//For every remaining vertex, delete that vertex, it's neighbours, then run deconstruct again.
	for(int i = 0; i < input_graph.vertices.size(); i++){
        
		string adj_vtc ="";
		graph new_graph = input_graph;
		delete_adjacent_vetices_and_edges(adj_vtc,new_graph,i);
		string sss = ccs;
		sss.append(input_graph.vertices[i]);
		sss.append(",");
        
		//Increase dominating set size by 1
		int j = iss + 1;
		
		deconstruct(new_graph,j,Isss,set_1,set_2,sss,index);
		
	}
	
}

//Checks if graph is well covered.
bool well_covered(vector<string> vertices,vector<string> edges,string name, string& set_1, string& set_2)
{
	
	graph input_graph;
	input_graph.vertices = vertices;
	input_graph.edges = edges;
	string Isss ="";
	string ccs = "";
	int index = 0;
	
	//Writes independent set sizes to Isss
	deconstruct(input_graph,0,Isss,set_1,set_2,ccs,index);
	
	//Cleanse string of unnecessary comma
	if (!set_1.empty())set_1.erase(set_1.size()-1);
	if (!set_2.empty())set_2.erase(set_2.size()-1);
	
	cout << "Checking Graph " << name << '\n';
	cout << "set 1: " << set_1 << '\n';
	cout << "set 2: " << set_2 << '\n';
    
    
    if (well(Isss)) {
        return 1;
    } else {
        return 0;
    }
}



