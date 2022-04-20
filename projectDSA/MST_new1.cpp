#include <bits/stdc++.h>
using namespace std;

template<typename E>
class AdjListNode
{
    public:
        E dest;
        int weight;
        AdjList<E>* next;
        
        //fns
        AdjListNode<E>* newAdjListNode(E dest, int weight);    
    
};

template<typename E>
AdjListNode<E>* AdjListNode<E> :: newAdjListNode(E dest, int weight)
{
    AdjListNode* newNode = new AdjListNode;
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

template<typename E>
class AdjList
{
    public:
        AdjListNode<E>* head;
};

template<typename E>
class Graph
{
    public:

        int V;
        AdjList<E>* array[V];

        Graph(int V);
        void addEdge(E src, E dest, int weight);
        vector<vector<E>> convertToAdjMatrix();
};

template<typename E>
Graph<E> :: Graph(int v)
{
	//Graph<E>* graph = new Graph();
	V = v;

	// Create an array of adjacency lists. Size of this array will be V.
	array = new AdjList();

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < V; i++)
		array[i]->head = NULL;

}

template<typename E>
void Graph<E> :: addEdge(E src, E dest, int weight)
{
	// Add an edge from src to dest. 
    //A new node is added to the adjacency list of src.
	//The node is added at the beginning
	AdjListNode<E>* newNode = newAdjListNode(dest, weight);
	next = array[src].head;
	array[src].head = newNode;


	// Since graph is undirected, add an edge from dest to src also i.e. 
    //every time ,add the edge both ways.
	newNode = newAdjListNode<E>(src, weight);
	newNode->next = graph->array[dest].head;
	array[dest].head = newNode;
}

template<typename E>
vector<vector<E>> Graph<E> :: convertToAdjMatrix()
{
    int v =V;
    vector<v ,vector<E, v>> AdjMatrix;
    for (int i = 0; i < v; i++)
    {
        AdjListNode* p = array[i]->head;
        while(p!= NULL)
        {
            E p1 = p->dest;
            int w = p->weight;
            AdjMatrix[i][p1] = w;
            p=p->next;
        }
    }

    return AdjMatrix;
}


// Class to represent a MinHeap
template<typename E>
class MinHeap
{
    public:
        vector<E> arr;
        int size;
    
        MinHeap();
        MinHeap(int V);
        int left(int i);
        int right(int i);
        int parent(int i);
        void addToMinHeap(E x);
        void minHeapify(int i);
        E extractMin();
        void decreaseKey(int i, E x);
        bool isEmpty();
        bool isInMinHeap(E x);

};

// Default Constructor
// Initializes size of MinHeap as 0
template<typename E>
MinHeap<E> :: MinHeap()
{
    size = 0;
}

// Function to return index of left child of a given node
template<typename E>
int MinHeap<E>::left(int i)
{
    return (2*i + 1);
}

// Function to return index of right child of a given node
template<typename E>
int MinHeap<E>::right(int i)
{
    return (2*i + 2);
}

// Function to return index of parent node of a given node
template<typename E>
int MinHeap<E>::parent(int i)
{
    return (i-1)/2;
}

// Function to add a node to MinHeap 
template<typename E>
void MinHeap<E>::addToMinHeap(E x)
{
    size++;
    arr[size-1] = x;
    for(int i = size-1; i!=0 && arr[parent(i)] > arr[i])
    {
        // Swapping arr[i] and parent(i)
        E temp4 = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp4;

        i = parent(i);
    } 
}

// Function to implement minHeapify operation 
template<typename E>
void MinHeap<E>::minHeapify(int i)
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
        E temp1 = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp1;
        
        minHeapify(smallest);
    }    
}

// Function to implement Extract Minimum operation
template<typename E>
E MinHeap<E>::extractMin()
{
    if(isEmpty())
        return;
    
    if(size == 1)
    {
        size--;
        return arr[0];
    } 

    // swapping arr[0] and arr[size-1]
    E temp2 = arr[0];
    arr[0] = arr[size -1];
    arr[size - 1] = temp2;
    
    size--;
    minHeapify(0);
    return arr[size];
}

// Function to implement the Decrease Key Operation
template<typename E>
void MinHeap<E>::decreaseKey(int i, E x)
{
    arr[i] = x;
    while(i!=0 && arr[parent(i)] > arr[i])
    {
        // swapping arr[i] and arr[parent(i)]
        E temp3 = arr[i];
        arr[i] = arr[parent(i)];
        arr[parent(i)] = temp3;
     
        i = parent(i);
    }
}

// Function to check if the MinHeap is empty or not
template<typename E>
bool MinHeap<E>::isEmpty()
{
    if(size == 0)
        return true;
    else 
        return false;
}

template<typename E>
bool MinHeap<E>::isInMinHeap(E )
{
    for(int j = 0; j < arr.size(); j++)
    {
        if()
    }
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

template <typename E>
void PrimMST(Graph<E> graph)
{
    vector<vector<E>> cost = graph.convertToAdjMatrix();
    vector<bool> inMST(V, false);
 
    // Include first vertex in MST
    inMST[0] = true;
 
    // Keep adding edges while number of included
    // edges does not become V-1.
    int edge_count = 0, mincost = 0;
    while (edge_count < V - 1) {
 
        // Find minimum weight valid edge. 
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {              
                if (cost[i][j] < min) {
                    if (isValidEdge(i, j, inMST)) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }
        if (a != -1 && b != -1) {
            printf("Edge %d:(%d, %d) cost: %d \n",
                         edge_count++, a, b, min);
            mincost = mincost + min;
            inMST[b] = inMST[a] = true;
        }
    }
    printf("\n Minimum cost= %d \n", mincost);

	printArr(parent, V);
	
}
 
void printArr(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
		cout << arr[i] << " - " << i << endl;
}

// Driver program to test all the above functions
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