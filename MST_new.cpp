#include <bits/stdc++.h>
using namespace std;

//Hashing for any datatype
template<typename E>
class Hash
{
    public:
        vector<E> keys;
        //vector<int> values;

        int returnPos(E x);
        E returnValue(int x);
        bool isPresent(E x);
        void enterValue(E x);

};

template<typename E>
int Hash<E> :: returnPos(E x)
{
    for (int i = 0; i < keys.size();i++)
        if(keys[i] == x)
            return i;
    return -1;
}

template<typename E>
E Hash<E> :: returnValue(int x)
{
    for (int i = 0; i < keys.size();i++)
        if(keys[i] == x)
            return keys[i];
    return;
}

template<typename E>
bool Hash<E> :: isPresent(E x)
{
    for (int i = 0; i < keys.size();i++)
        if(keys[i] == x)
            return true;
    return false;
}

template<typename E>
void Hash<E> :: enterValue(E x)
{
    keys.push_back(x);
}


// A STRUCTURE TO REPRESENT A NODE IN ADJACENCY LIST
//It has the destination vertex of the graph,
//its weight between the source and destination vertices.
//Also ,it has the pointer to the next node of the Adjacency List.

class AdjListNode
{
    public:
        int dest;
        int weight;
        AdjListNode* next;

        AdjListNode* newAdjListNode(int dest, int weight); 
};


AdjListNode* AdjListNode :: newAdjListNode(int dest, int weight)
{
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// A STRUCTURE TO REPRESENT AN ADJACENCY LIST
//It has the pointer to the head node of the Adjacency List.
class AdjList
{
    public:
	    AdjListNode* head; 
};


// A STRUCTURE TO REPRESENT A GRAPH.
// A Graph is represented as an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
//HASHING IS IMPLEMENTED HERE THE POSITIONS OF EACH DATATYPE IS STORED IN ARRAY
//AND HASHER STORES RESPECTIVE DATATYPE(OPEN HASHING)
template<typename E>
class Graph
{
    public:

        int V;
        Hash<E> hasher;
        AdjList* array;

        Graph(int V);
        void addEdge(E src, E dest, int weight);
        
};

template<typename E>
Graph<E> :: Graph(int v)
{
	V = v;
	// Create an array of adjacency lists. Size of this array will be V.
	array = new AdjList();

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < V; i++)
		array[i].head = NULL;

}

// THIS FUNCTION ADDS AN EDGE TO AN UNDIRECTED GRAPH
//It takes input the graph in which the edge is to be added, and 
//also it takes input the weight of the edge and the src and dest vertices of it.
template<typename E>
void Graph<E> :: addEdge(E oldsrc, E olddest, int weight)
{
	// Add an edge from src to dest. 
    //A new node is added to the adjacency list of src.
	//The node is added at the beginning
	int src, dest;
    if(hasher.isPresent(oldsrc))
    {
        src=hasher.returnPos(oldsrc);
    }    
    else
    {
        hasher.enterValue(oldsrc);
        src=hasher.returnPos(oldsrc);
    }

    if(hasher.isPresent(olddest))
    {
        dest=hasher.returnPos(olddest);
    }    
    else
    {
        hasher.enterValue(olddest);
        dest=hasher.returnPos(olddest);
    }

    AdjListNode* newNode = newNode->newAdjListNode(dest, weight);
	newNode->next = array[src].head;
	array[src].head = newNode;


	// Since graph is undirected, add an edge from dest to src also i.e. 
    //every time ,add the edge both ways.
	newNode = newNode->newAdjListNode(src, weight);
	newNode->next = array[dest].head;
	array[dest].head = newNode;
}



// A STRUCTURE TO REPRESENT A MIN HEAP NODE
//It has the value of the vertex, and a key related to it which 
//is actually the weight ,that will be updated later as and when we encounter their src vertex.
/*template <typename E>*/
class MinHeap
{
    public:
        vector<int> arr;
        int size;
    
        MinHeap();
        int left(int i);
        int right(int i);
        int parent(int i);
        void addToMinHeap(int x);
        void minHeapify(int i);
        int extractMin();
        void decreaseKey(int i, int x);
        bool isEmpty();
        bool isInMinHeap(int x);

};



// STRUCTURE TO REPRESENT A MIN HEAP
//size - Number of heap nodes present currently.
//capacity - Capacity of min heap.
//"pos" pointer is needed for decreaseKey() function later.
MinHeap :: MinHeap()
{
    size = 0;
}
// Function to return index of left child of a given node
int MinHeap::left(int i)
{
    return (2*i + 1);
}
// Function to return index of right child of a given node
int MinHeap::right(int i)
{
    return (2*i + 2);
}
// Function to return index of parent node of a given node
int MinHeap::parent(int i)
{
    return (i-1)/2;
}


void MinHeap::addToMinHeap(int x)
{
    size++;
    arr.push_back(x);
    for(int i = size-1; i!=0 && arr[parent(i)] > arr[i];)
    {
        // Swapping arr[i] and parent(i)
        int temp4 = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp4;

        i = parent(i);
    }
}

//to check if given minheap is a min heap or not
bool MinHeap :: isInMinHeap( int v)
{
	if (v < size)
		return true;
	return false;
}

//minheapify
void MinHeap :: minHeapify(int i)
{
    int lt = left(i);
    int rt = right(i);

    int smallest = i;
    
    if(lt < size && arr[lt] < arr[smallest])
        smallest = lt;

    if(rt < size && arr[rt] < arr[smallest])
        smallest = rt;

    if(smallest != i)
    {
        // swapping arr[i] and arr[smallest]
        int temp1 = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp1;
        
        minHeapify(smallest);
    }    
}

// Function to implement Extract Minimum operation
int MinHeap::extractMin()
{
    if(isEmpty()) 
    {
        return -1;
    }
    if(size == 1)
    {
        size--;
        return arr[0];
    } 

    // swapping arr[0] and arr[size-1]
    int temp2 = arr[0];
    arr[0] = arr[size -1];
    arr[size - 1] = temp2;
    
    size--;
    minHeapify(0);
    return arr[size];
}



// Function to implement the Decrease Key Operation
void MinHeap::decreaseKey(int i, int x)
{
    arr[i] = x;
    while(i!=0 && arr[parent(i)] > arr[i])
    {
        // swapping arr[i] and arr[parent(i)]
        int temp3 = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp3;
     
        i = parent(i);
    }
}




// A UTILITY FUNCTION TO CHECK IF THE GIVEN MIN HEAP IS EMPTY OR NOT
bool MinHeap :: isEmpty()
{
    if(size == 0)
        return true;
    else 
        return false;
}

// Function which constructs Minumum Spanning Tree(MST)
// Using Prim's Algorithm
bool isValidEdge(int u, int v, vector<bool> inMST)
{
   if (u == v)
       return false;
   if (inMST[u] == false && inMST[v] == false)
        return false;
   else if (inMST[u] == true && inMST[v] == true)
        return false;
   return true;
}



template<typename E>
void PrimMST(Graph<E> graph)
{
    int V = graph.V; 
    
    vector<bool> inMST(V, false);
    inMST[0] = true;
    // Array to store constructed MST
	int parent[V]; 

    // Key values used to pick minimum weight edge in cut
	int key[V]; 

	// minHeap represents set E
	MinHeap minHeap;

	// Initialize min heap with all vertices.
    // Key value of all vertices (except 0th vertex) is initially infinite
	for (int v = 1; v < V; ++v) 
    {
		minHeap.addToMinHeap(graph.array[v].head->weight);
	}

	// Make key value of 0th vertex as 0 so that it
	// is extracted first
	key[0] = 0;
	minHeap.addToMinHeap(graph.array[0].head->weight);
	//minHeap.pos[0] = 0;

	// Initially size of min heap is equal to V
	minHeap.size = V;

	// In the following loop,
    // min heap contains all nodes not yet added to MST.

	while (!minHeap.isEmpty()) {

		// Extract the vertex with minimum key value
		int u = minHeap.extractMin();

        // Store the extracted vertex number
		//int u = minHeapNode.v; 

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their key values
		AdjListNode* pCrawl = graph.array[u].head;

		while (pCrawl != NULL) {
			int v = pCrawl->dest;

			// If v is not yet included in MST and weight of u-v is
			// less than key value of v, then update key value and
			// parent of v

			if (isInMinHeap(v) && pCrawl->weight < key[v]) {
				key[v] = pCrawl->weight;
				parent[v] = u;
				decreaseKey(v, key[v]);
			}

			pCrawl = pCrawl->next;
		}
	}

	// print edges of MST
	printArr(graph<E>, parent, V);
	
}


// A UTILITY FUNCTION USED TO PRINT THE CONSTRUCTED MST.
template<typename E>
void printArr(Graph<E> graph, int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << graph.hasher.returnValue(arr[i]) << " - " << graph.hasher.returnValue(i) << endl;
    }
}



// void printArr(int arr[], int n)
// {
//     for (int i = 1; i < n; ++i)
// 		cout << arr[i] << " - " << hasher.returnValue(i) << endl;
// }



// A UTILITY FUNCTION USED TO PRINT THE CONSTRUCTED MST.


// THE MAIN FUNCTION THAT CONSTRUCTS MINIMUM SPANNING TREE (MST)
// USING PRIM'S ALGORITHM



// Driver program to test above functions
int main()
{
	// Creating a Sample Graph
	int V = 9;
	class Graph<int> graph(V);
	graph.addEdge( 0, 1, 4);
	graph.addEdge( 0, 7, 8);
	graph.addEdge( 1, 2, 8);
	graph.addEdge( 1, 7, 11);
	graph.addEdge( 2, 3, 7);
	graph.addEdge( 2, 8, 2);
	graph.addEdge( 2, 5, 4);
	graph.addEdge( 3, 4, 9);
	graph.addEdge( 3, 5, 14);
	graph.addEdge( 4, 5, 10);
	graph.addEdge( 5, 6, 2);
	graph.addEdge( 6, 7, 1);
	graph.addEdge( 6, 8, 6);
	graph.addEdge( 7, 8, 7);

	PrimMST<int>(graph);

	return 0;

}
