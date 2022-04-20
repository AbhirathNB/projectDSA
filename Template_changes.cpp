

#include <bits/stdc++.h>
using namespace std;


// A STRUCTURE TO REPRESENT A NODE IN ADJACENCY LIST
//It has the destination vertex of the graph,
//its weight between the source and destination vertices.
//Also ,it has the pointer to the next node of the Adjacency List.
template <typename E>
struct AdjListNode {
	E dest;
	int weight;
	struct AdjListNode<E>* next;  
};



// A STRUCTURE TO REPRESENT AN ADJACENCY LIST
//It has the pointer to the head node of the Adjacency List.
template <typename E>
struct AdjList {
	struct AdjListNode<E>* head; 
};


// A STRUCTURE TO REPRESENT A GRAPH.
// A Graph is represented as an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
template <typename E>
struct Graph {
	int V;
	struct AdjList<E>* array;
};



// A UTILITY FUNCTION TO CREATE A NEW ADJACENCY LIST NODE
//This function returns the pointer to the AdjListNode type ,
//that is made from the given dest and weight parameters.
//Also,initially the pointer to the next node is NULL.
template <typename E>
struct AdjListNode<E>* newAdjListNode(E dest, int weight)
{
	struct AdjListNode<E>* newNode = (struct AdjListNode<E>*)malloc(sizeof(struct AdjListNode<E>));/////////////////
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}



// A UTILITY FUNCTION THAT CREATES A GRAPH OF V VERTICES(taken as input).
template <typename E>
struct Graph<E>* createGraph(int V)
{
	struct Graph<E>* graph = (struct Graph<E>*)malloc(sizeof(struct Graph<E>));/////////////////
	graph->V = V;

	// Create an array of adjacency lists. Size of this array will be V.
	graph->array = (struct AdjList<E>*)malloc(V * sizeof(struct AdjList<E>));//////////////////

	// Initialize each adjacency list as empty by making head as NULL 
	for (int i = 0; i < V; i++)
		graph->array[i].head = NULL;

	return graph;
}



// THIS FUNCTION ADDS AN EDGE TO AN UNDIRECTED GRAPH
//It takes input the graph in which the edge is to be added, and 
//also it takes input the weight of the edge and the src and dest vertices of it.
template <typename E>
void addEdge(struct Graph<E>* graph, E src, E dest, int weight)
{

	// Add an edge from src to dest. 
    //A new node is added to the adjacency list of src.
	//The node is added at the beginning
	struct AdjListNode<E>* newNode = newAdjListNode(dest, weight);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;


	// Since graph is undirected, add an edge from dest to src also i.e. 
    //every time ,add the edge both ways.
	newNode = newAdjListNode<E>(src, weight);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}



// A STRUCTURE TO REPRESENT A MIN HEAP NODE
//It has the value of the vertex, and a key related to it which 
//is actually the weight ,that will be updated later as and when we encounter their src vertex.
/*template <typename E>*/
struct MinHeapNode {
	int v;
	int key;
};



// STRUCTURE TO REPRESENT A MIN HEAP
//size - Number of heap nodes present currently.
//capacity - Capacity of min heap.
//"pos" pointer is needed for decreaseKey() function later.
struct MinHeap {
	int size;            
	int capacity;        
	int* pos;           
	struct MinHeapNode** array;
};


// A UTILITY FUNCTION TO CREATE A NEW MIN HEAP NODE
//Its return type is the pointer to the MinHeapNode type.
struct MinHeapNode* newMinHeapNode(int v, int key)
{
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));///////////////
	minHeapNode->v = v;
	minHeapNode->key = key;
	return minHeapNode;
}



// A UTILITY FUNCTION TO CREATE A MIN HEAP
//Its return type is pointer to the MinHeap type.
struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));/////////////////
	minHeap->pos = (int*)malloc(capacity * sizeof(int));///////////////
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));///////////
	return minHeap;
}



// A UTILITY FUNCTION TO SWAP TWO NODES OF A MIN HEAP(it takes input of those two nodes). 
//NEEDED FOR MIN HEAPIFY.
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}



// A STANDARD FUNCTION TO HEAPIFY AT GIVEN INDEX.
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey() function.
void minHeapify(struct MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;
 
    //////////////////////////////////////
	if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
		smallest = left;
    
    /////////////////////////////////////
	if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
		smallest = right;

    /////////////////////////////////////
	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode = minHeap->array[smallest];
		MinHeapNode* idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

       ///////////////////////////////
		minHeapify(minHeap, smallest);
	}
}




// A UTILITY FUNCTION TO CHECK IF THE GIVEN MIN HEAP IS EMPTY OR NOT
int isEmpty(struct MinHeap* minHeap)
{
	return minHeap->size == 0;
}


// STANDARD FUCNTION TO EXTRACT MINIMUM NODE FROM HEAP
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
	struct MinHeapNode* root = minHeap->array[0];

	// Replace root node with last node
	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;
	minHeapify(minHeap, 0);
    
    //It returns the min value node from the minheap.
	return root;
}



// FUNCTION TO DECREASE KEY VALUE OF A GIVEN VERTEX v.
// This function uses pos[] of min heap to get the current index of node in min heap.
void decreaseKey(struct MinHeap* minHeap, int v, int key)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its key value
	minHeap->array[i]->key = key;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}



// A UTILITY FUNCTION TO CHECK IF A GIVEN VERTEX
// 'v' IS IN MIN HEAP OR NOT
bool isInMinHeap(struct MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return true;
	return false;
}



// A UTILITY FUNCTION USED TO PRINT THE CONSTRUCTED MST.
/*template <typename E>*/
void printArr(int arr[], int n)
{
	for (int i = 1; i < n; ++i)
		cout << arr[i] << " - " << i << endl;
		//printf("%d - %d\n", arr[i], i);
}


// THE MAIN FUNCTION THAT CONSTRUCTS MINIMUM SPANNING TREE (MST)
// USING PRIM'S ALGORITHM
template <typename E>
void PrimMST(struct Graph<E>* graph)
{
    // Get the number of vertices in graph
	int V = graph->V; 
    
    // Array to store constructed MST
	int parent[V]; 

    // Key values used to pick minimum weight edge in cut
	int key[V]; 

	// minHeap represents set E
	struct MinHeap* minHeap = createMinHeap(V);

	// Initialize min heap with all vertices.
    // Key value of all vertices (except 0th vertex) is initially infinite
	for (int v = 1; v < V; ++v) {
		parent[v] = -1;
		key[v] = INT_MAX;
		minHeap->array[v] = newMinHeapNode(v, key[v]);
		minHeap->pos[v] = v;
	}

	// Make key value of 0th vertex as 0 so that it
	// is extracted first
	key[0] = 0;
	minHeap->array[0] = newMinHeapNode(0, key[0]);
	minHeap->pos[0] = 0;

	// Initially size of min heap is equal to V
	minHeap->size = V;

	// In the following loop,
    // min heap contains all nodes not yet added to MST.

	while (!isEmpty(minHeap)) {

		// Extract the vertex with minimum key value
		struct MinHeapNode* minHeapNode = extractMin(minHeap);

        // Store the extracted vertex number
		int u = minHeapNode->v; 

		// Traverse through all adjacent vertices of u (the extracted
		// vertex) and update their key values
		struct AdjListNode<E>* pCrawl = graph->array[u].head;

		while (pCrawl != NULL) {
			E v = pCrawl->dest;

			// If v is not yet included in MST and weight of u-v is
			// less than key value of v, then update key value and
			// parent of v

			if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) {
				key[v] = pCrawl->weight;
				parent[v] = u;
				decreaseKey(minHeap, v, key[v]);
			}

			pCrawl = pCrawl->next;
		}
	}

	// print edges of MST
	printArr(parent, V);
	
}


// Driver program to test above functions
int main()
{
	// Let us create the graph given in above figure
	int V = 9;
	struct Graph<int>* graph = createGraph<int>(V);
	addEdge(graph, 0, 1, 4);
	addEdge(graph, 0, 7, 8);
	addEdge(graph, 1, 2, 8);
	addEdge(graph, 1, 7, 11);
	addEdge(graph, 2, 3, 7);
	addEdge(graph, 2, 8, 2);
	addEdge(graph, 2, 5, 4);
	addEdge(graph, 3, 4, 9);
	addEdge(graph, 3, 5, 14);
	addEdge(graph, 4, 5, 10);
	addEdge(graph, 5, 6, 2);
	addEdge(graph, 6, 7, 1);
	addEdge(graph, 6, 8, 6);
	addEdge(graph, 7, 8, 7);

	PrimMST<int>(graph);

	return 0;
}
