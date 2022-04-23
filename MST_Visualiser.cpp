// DATA STRUCTURES AND ALGORITHMS PROJECT
//***************************TEAM DETAILS******************************************
// LUV GHILOTHIA - 2020A7PS1700H
// AMOGH MOSES   - 2020A7PS1199H
// ABHIRATH N B  - 2020A7PS0260H

// MST VISUALISER BY PRIM'S MST ALGORITHM IN C++
// USING MINIMUM HEAP IMPLEMENTATION

//***************************START OF THE PROGRAM***********************************
#include <bits/stdc++.h>

//#include <limits.h>
//#include <stdio.h>
//#include <stdlib.h>

using namespace std;


// Structure to represent a node in the adjacency list
// It has the destination vertex of the graph,
// its weight between the source and destination vertices.
// Also ,it has the pointer to the next node of the Adjacency List
// so that further more nodes can be joined to make a full list.

struct NodeofAdjacencyList {
	int destinationNode;
	int weightOfEdge;
	struct NodeofAdjacencyList* nextNode;
};


// Structure to represent an Adjacency list
// It has the pointer to the head node of the Adjacency List,
// i.e. it is the starting point of the adjacency list.

struct Adjacency_List {
	struct NodeofAdjacencyList* HeadOfTheList;
};


// Structur to represent a graph
// A Graph is represented as an array of adjacency lists here.
// Size of array will be V.
//where V = (total number of vertices in graph)

struct MainGraph {
	int V;
	struct Adjacency_List* ArrayOfLists;
	//struct Hash h1;
};



// Function which createsa new node for the adjaceny list
// This function returns the pointer to the "NodeofAdjacencyList" type ,
// that is made from the given destination node and weight of the edge parameters.
// Also,initially the pointer to the next node is NULL.

struct NodeofAdjacencyList* newAdjListNode(int destinationNode, int weightOfEdge)
{
	struct NodeofAdjacencyList* newN =  new struct NodeofAdjacencyList;

	//allocating the value of destination node
	newN->destinationNode = destinationNode;

	//allocating the weight of the edge
	newN->weightOfEdge = weightOfEdge;

	//allocating the next pointer
	newN->nextNode = NULL;

	//return the pointer to the new node created
	return newN;
}



// Function that creates a graph of V vertices
// here, V is taken as input.

// Time complexity of this function is O(V)
struct MainGraph* createTheMainGraph(int V)
{
	struct MainGraph* G = new struct MainGraph;

	//allocating the number of vertices we want in the graph
	G->V = V;

	// Create an array of adjacency lists.
	//Size of this array will be V.
	G->ArrayOfLists = new struct Adjacency_List[V * sizeof(struct Adjacency_List)];

	// Initialize each adjacency list as empty by making their head as NULL
	for (int i = 0; i < V; i++)
		G->ArrayOfLists[i].HeadOfTheList = NULL;

	// return the pointer to the new graph created
	return G;
}


// Function which adds an edge to the undirected graph that we have made
// It takes input the graph in which the edge is to be added, and
// also it takes input the weight of the edge ,
// and the src and destinationNode vertices of it.

// Time complexity of this function is O(1) (constant time)
void addGraphEdge(struct MainGraph* G, int sourceNode, int destinationNode, int weightOfEdge)
{

	// Add an edge from src to destinationNode.
    //A new node is added to the adjacency list of src.
	//The node is added at the beginning

	struct NodeofAdjacencyList* newN = newAdjListNode(destinationNode, weightOfEdge);
	newN->nextNode = G->ArrayOfLists[sourceNode].HeadOfTheList;
	G->ArrayOfLists[sourceNode].HeadOfTheList = newN;


	// Since graph is undirected, add an edge from destinationNode to src also i.e.
    //every time ,add the edge both ways.

	newN = newAdjListNode(sourceNode, weightOfEdge);
	newN->nextNode = G->ArrayOfLists[destinationNode].HeadOfTheList;
	G->ArrayOfLists[destinationNode].HeadOfTheList = newN;
}



// Structure to represent a MinHeap Node
// It has the value of the vertex, and a key related to it which
// is actually the weight ,that will be updated later as and when we encounter their src vertex.

struct NodeOfMinHeap {
	int v;
	int KeyValue;
};


// Structure to represent a MinHeap
// size - Number of heap nodes present currently.
// capacity - Capacity of min heap.
// "lambda" pointer is needed for decreaseKey() function later.

struct MinimumHeap {
	int size;
	int capacity;

	//position array
	int* lambda;

	struct NodeOfMinHeap** Array;
};


// Function which creates a new minHeap Node
// Its return type is the pointer to the 'NodeOfMinHeap' type.

// Time complexity of this function is O(1) (constant time)
struct NodeOfMinHeap* newMinHeapNode(int v, int KeyValue)
{
	struct NodeOfMinHeap* mHeapN = new struct NodeOfMinHeap;

	// allocating value of that vertex
	mHeapN->v = v;

	// allocating the key value of that vertex
	mHeapN->KeyValue = KeyValue;

	// return the pointer to the min heap node created
	return mHeapN;
}



// Function which creates a MinHeap
// Its return type is pointer to the 'MinimumHeap' type.

// Time complexity of this function is O(1) (constant time)
struct MinimumHeap* createTheMinimumHeap(int capacity)
{
	struct MinimumHeap* mHeap = new struct MinimumHeap;

	//creating the position array
	mHeap->lambda = new int[capacity*(sizeof(int))];

	//allocating the size to 0
	mHeap->size = 0;

	//allocating the capacity
	mHeap->capacity = capacity;

    //creating the array of lists
	mHeap->Array = new struct NodeOfMinHeap*[capacity * sizeof(struct NodeOfMinHeap*)];

	//return the pointer to the min heap created
	return mHeap;
}

// Functions which swaps two nodes of a minHeap
//(It takes input of those two nodes).
// Needed for MinHeapify

// Time complexity of this function is O(1)
void swapTwoMinimumHeapNodes(struct NodeOfMinHeap** firstNode, struct NodeOfMinHeap** secondNode)
{
    //uses a temporary node to swap the two nodes
	struct NodeOfMinHeap* tempNode = *firstNode;
	*firstNode = *secondNode;
	*secondNode = tempNode;
}



// Function which performs the minHeapfify operation
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey() function.
// here, take input of "index" to know from where to start heapifying in the min heap

// Time complexity of the below function is O(log(n))
void minHeapify(struct MinimumHeap* mHeap, int index)
{

	int smallest, left, right;
	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;

    //compare the left child first
	if (left < mHeap->size and mHeap->Array[left]->KeyValue < mHeap->Array[smallest]->KeyValue)
		smallest = left;

    //then compare the right child
	if (right < mHeap->size and mHeap->Array[right]->KeyValue < mHeap->Array[smallest]->KeyValue)
		smallest = right;

    //base case for the recursive call to heapify function
	if (smallest != index) {

		// The nodes to be swapped in the min heap
		NodeOfMinHeap* smallestNode = mHeap->Array[smallest];
		NodeOfMinHeap* indexNode = mHeap->Array[index];

		// Swap positions
		mHeap->lambda[smallestNode->v] = index;
		mHeap->lambda[indexNode->v] = smallest;

		// Swap nodes
		swapTwoMinimumHeapNodes(&mHeap->Array[smallest], &mHeap->Array[index]);

       //make a recursive call to the function
		minHeapify(mHeap, smallest);
	}
}


// Function which checks if the minHeap is empty or not
// Time complexity of this function is O(1)
int isEmpty(struct MinimumHeap* mHeap)
{
	return mHeap->size == 0;
}


// Function which extracts minimum node from the heap

// Time complexity of this function is O(1) (constant time)
struct NodeOfMinHeap* extractMin(struct MinimumHeap* mHeap)
{
    //check if heap is empty or not
	if (isEmpty(mHeap))
		return NULL;

	// Store the root node
	struct NodeOfMinHeap* root = mHeap->Array[0];

	// Replace root node with last node
	struct NodeOfMinHeap* lastNode = mHeap->Array[mHeap->size - 1];
	mHeap->Array[0] = lastNode;

	// Update position of last node
	mHeap->lambda[root->v] = mHeap->size - 1;
	mHeap->lambda[lastNode->v] = 0;

	// Reduce heap size and heapify from the root node
	--mHeap->size;
	minHeapify(mHeap, 0);

    //It returns the min value node from the minheap.
	return root;
}



// Function that implements the decrease key operation
// This function uses lambda[] of min heap
// to get the current index of node in min heap.

// Time complexity of this function is O(logV)
void decreaseKey(struct MinimumHeap* mHeap, int v, int KeyValue)
{
	// Get the index of v in heap Array
	int index = mHeap->lambda[v];

	// Get the node and update its key value
	mHeap->Array[index]->KeyValue = KeyValue;

	// Travel up while the complete tree is not heapified.

	while (index!=0 and mHeap->Array[index]->KeyValue < mHeap->Array[(index - 1) / 2]->KeyValue) //Comparing with Parent
	{
		// Swap this node with its parent
		mHeap->lambda[mHeap->Array[index]->v] = (index - 1) / 2;
		mHeap->lambda[mHeap->Array[(index - 1) / 2]->v] = index;
		swapTwoMinimumHeapNodes(&mHeap->Array[index], &mHeap->Array[(index - 1) / 2]);

		// move to parent index
		index = (index - 1) / 2;
	}
}


// Function that checks if a given vertex 'v'
// is in MinHeap or not

// Time complexity of this function is O(1) (constant time)
bool isInMinHeap(struct MinimumHeap* mHeap, int v)
{
	if (mHeap->lambda[v] < mHeap->size)
		return true;
	return false;
}


// // A function which prints the edges included in the MST - From the MinHeap

// // Time complexity of this function is O(V)
void printTheSteps(int array[], int n, unordered_map<int, string> StringMap)
{
	cout << "Displaying the Minimum Spanning Tree below:"<< endl;
	for (int i = 1; i < n; i++){
	    //printing the information of the edge included
		cout<< StringMap[array[i]] <<" --- "<<StringMap[i]<<endl;
	}
}


// The function which constructs the Minimum Spanning Tree(MST)
// Using Prim's Algorithm
// It takes the input of the graph to be evaluated.

// Time complexity of this function is O((E+V)*log(V)) i.e. O(E*log(V))
void MainPrimMSTFunction(struct MainGraph* graph, unordered_map<int, string> StringMap)
{
    // Get the number of vertices in graph
	int V = graph->V;

    // Array to store constructed MST
	int parent[V];

    // Key values used to pick minimum weight edge in cut
	int KeyValue[V];

	// minHeap represents set E
	struct MinimumHeap* mHeap = createTheMinimumHeap(V);


    // Initialize min heap with all vertices.
	for (int itr = 1; itr < V; itr++) {

	    //initialising the parent array to -1
		parent[itr] = -1;

		// Key value of all vertices (except 0th vertex) is initially infinite
		KeyValue[itr] = INT_MAX;
		mHeap->Array[itr] = newMinHeapNode(itr, KeyValue[itr]);
		mHeap->lambda[itr] = itr;

	}

	// Make key value of 0th vertex as 0
	// so that it is extracted first
	KeyValue[0] = 0;
	mHeap->Array[0] = newMinHeapNode(0, KeyValue[0]);
	mHeap->lambda[0] = 0;


	// Initially size of min heap is equal to V
	mHeap->size = V;

    //FOR STORING THE FINAL MINIMUM COST AS ANSWER.
    int ansMinCost=0;


	// In the following loop,
    // min heap contains all nodes not yet added to MST.
    while (!isEmpty(mHeap)) {

		// Extract the vertex with minimum key value
		struct NodeOfMinHeap* minHeapNode = extractMin(mHeap);

        // Store the extracted vertex number
		int vertexNumber = minHeapNode->v;

        //incrementing the cost of our answer
        int weightSelected=minHeapNode->KeyValue;
		// if(vertexNumber!=0)
		// {
		// 	cout<<"CHOOSING THE EDGE WITH THE WEIGHT "<<weightSelected<<endl;
		// }
			
        ansMinCost = ansMinCost + weightSelected;


		// Traverse through all adjacent vertices of vertexNumber (the extracted vertex)
		// and update their key values
		struct NodeofAdjacencyList* ALA = graph->ArrayOfLists[vertexNumber].HeadOfTheList;


		while (ALA != NULL) {
			int vNode = ALA->destinationNode;

			// If v is not yet included in MST and weight of u-v is
			// less than key value of v, then update key value and
			// parent of v

			if (isInMinHeap(mHeap, vNode) and ALA->weightOfEdge < KeyValue[vNode]) {
				KeyValue[vNode] = ALA->weightOfEdge;
				parent[vNode] = vertexNumber;
				decreaseKey(mHeap, vNode, KeyValue[vNode]);
			}

            //increment to the next node
			ALA = ALA->nextNode;
		}
	}

    //printing the answer of minimum cost
    cout<<"Hence, the minimum cost of the MST of this graph is: "<<ansMinCost<<endl;

	// // print edges of MST
	 printTheSteps(parent, V, StringMap);

}


// Driver program to test above functions
int main()
{
	//implementing the file input handling for our code
	ifstream fin;
	string line;
	fin.open("i7.txt"); //may change the input file name here
	
	getline(fin, line);
	int V = stoi(line);

	//cout << V << endl;
	// Creating a Graph using Adjacency List Representation
	struct MainGraph* graph = createTheMainGraph(V);

	//will store strings from the system then implements indices into Graph and MainPrimMSTFunction
	//********NOTE THAT YOU NEED TO ADD SPACE AFTER EVERY NUMBER, INCLUDING LAST******
	
	//All the values in the file are shown here
	//int V = 9;

	// addGraphEdge(graph, 0, 1, 4);
	// addGraphEdge(graph, 0, 7, 8);
	// addGraphEdge(graph, 1, 2, 8);
	// addGraphEdge(graph, 1, 7, 11);
	// addGraphEdge(graph, 2, 3, 7);
	// addGraphEdge(graph, 2, 8, 2);
	// addGraphEdge(graph, 2, 5, 4);
	// addGraphEdge(graph, 3, 4, 9);
	// addGraphEdge(graph, 3, 5, 14);
	// addGraphEdge(graph, 4, 5, 10);
	// addGraphEdge(graph, 5, 6, 2);
	// addGraphEdge(graph, 6, 7, 1);
	// addGraphEdge(graph, 6, 8, 6);
	// addGraphEdge(graph, 7, 8, 7);
	
	unordered_map<int, string> StringMap;
	
	int indexInMap = 0;
	//Time complexity for insertion of values into graph is O(V)
	while (fin)
	{
		getline(fin, line);
		string arr[3];

		//temp var
		int k = 0;
		int flag = 0;

		//to add into map
		string word = "";
		//splitting string int 3 parts : string1, string2 and number
		for(auto x : line)
		{
			if (x == ' ')
			{
				arr[k] = word;
				k++;
				word = "";
			}
			else
			{
				word = word + x;
			}
		}
		//arr[k] = word;
		
		int arr0, arr1;
		for (auto x : StringMap)
		{
			if (x.second == arr[0])
			{	
				flag = 1;
				arr0 = x.first;
				break;
			}
		}
		if (flag == 0)
		{
			StringMap[indexInMap] = arr[0];
			arr0 = indexInMap;
			indexInMap++;
		}

		flag = 0;
		for (auto x : StringMap)
		{
			if (x.second == arr[1])
			{	
				flag = 1;
				arr1 = x.first;
				break;
			}
		}
		if (flag == 0)
		{
			StringMap[indexInMap] = arr[1];
			arr1 = indexInMap;
			indexInMap++;
		}
		
		int number;
		number = stoi(arr[2]);

		addGraphEdge(graph, arr0, arr1, number);
		
	}
	fin.close();

    //calling our main Prim's MST function
	MainPrimMSTFunction(graph, StringMap);

	return 0;
}

// ABOUT THE FINAL TIME COMPLEXITY OF THE PROGRAM:
//The time complexity of the above program seems/looks O(V^2) as there are two nested while loops.
//But we must observe that the statements in inner loop are executed O(V+E) times just like it is done in BFS.
//The inner loop has decreaseKey() operation which takes O(LogV) time.
//So overall time complexity is O(E+V)*O(logV) which is O((E+V)*logV) = O(E*logV).
//We know that for a connected graph, V = O(E).

//******************************END OF THE PROGRAM******************************