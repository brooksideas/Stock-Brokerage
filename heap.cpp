#include <iostream>
#include <string>
#include <queue>
#include <array>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <regex>
#include <unordered_map>

using namespace std;
struct stockType
{
    std::string name;
    int timesPurchased;
    double dividend;
    double price;
    bool operator<(const stockType &rhs)
    {
        return true;
    }
};
template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10)
    {

        this->size = 0;
        this->capacity = 10;
        // Insert the element to the priority queue
        // insert(4);
        // insert(2);
        // insert(1);
        // insert(7);
        // insert(8);
        // insert(9);
        // insert(11);
        // insert(13);
        // insert(10);
        // insert(21);
        // insert(30);
        // insert(40);
 
        // printHeap();
        // getPriority();
        // cout << "CON" << getPriority() << endl;
    }
    // read everything from the given CSV file and parse and insert here
    priorityQ(vector<Type> value)
    {
        this->size = 0;
        this->capacity = 10;
        cout << "Exchange " << endl;

        // if the first value is a double then it is a exchange read
        for (double i : value)
            insert(i);
        cout << endl;
        printHeap();

    }
    priorityQ(const priorityQ<Type> &copy)
    {
        int *copied = new int[this->size];
        for (int i = 0; i < this->size; i++)
        {
            copied[i] = copy[i];
        }
        delete[] copy;

        copy = copied;
    }
    // ~priorityQ();
    const priorityQ<Type> &operator=(const priorityQ<Type> &);
    void insert(double p)
    {
        // Make sure there is still space in the heap
        if (this->size == this->capacity)
        {
            // cout << "MIN HEAP FULL!" << endl;
            ensureExtraCapacity();
            // return;
        }

        // Increse the amount of elements in the heap
        this->size++;

        // Insert the new key at the end
        int i = this->size - 1;
        this->heapArray[i] = p;

        // Fix the min this->heapArray property
        // Moves the element up until i >= parent or root
        while (i != 0 && this->heapArray[parent(i)] > this->heapArray[i])
        {
            cout << "HEAP VAL->" << this->heapArray[i] << "parent-> "<< this->heapArray[parent(i)] << endl; 
            swap(this->heapArray[i], this->heapArray[parent(i)]);
            i = parent(i);
        }
    }
    void deletePriority()
    {
        /*
          -> Grab the min item. It is at index 0.
          -> Move the last item in the heap to the "top" of the
          heap at index 0.
          -> Reduce size.
        */
        if (isEmpty())
        {
            cout << "Heap is empty." << endl;
        }
        // Check if there is only 1 element
        else if (this->size == 1)
        {
            this->size--;
            // return this->heapArray[0];
            // Normal extraction
        }
        else
        {
            // Store the root
            int root = this->heapArray[0];

            // Maintain this->heapArray shape and then order
            this->heapArray[0] = this->heapArray[this->size - 1];
            this->size--;
            /*
        Restore / Maintain this->heapArray shape and then order
        by bubbling down the element we swapped up to index 0
      */
            bubbleDown(0);
        }
    }
    Type getPriority() const
    {
        return this->heapArray[0];
    }
    bool isEmpty() const
    {
        return sizeof(this->heapArray) == 0 ? true : false;
    }
    void bubbleUp(int i)
    {
        // Set initial conditions
        int l = left(i);
        int r = right(i);
        int largest = i;

        // Find the largest element of the three
        if ((l < this->size) && (this->heapArray[l] > this->heapArray[largest]))
        {
            largest = l;
        }
        if ((r < this->size) && (this->heapArray[r] > this->heapArray[largest]))
        {
            largest = r;
        }

        // If the largest of l or r, continue bubbleUp
        if (largest != i)
        {
            swap(this->heapArray[i], this->heapArray[largest]);
            bubbleUp(largest);
        }
    }
    void bubbleDown(int i)
    {
        // Set initial conditions
        int l = left(i);
        int r = right(i);
        int smallest = i;

        // Find the smallest element of the three
        if ((l < this->size) && (this->heapArray[l] < this->heapArray[smallest]))
        {
            smallest = l;
        }
        if ((r < this->size) && (this->heapArray[r] < this->heapArray[smallest]))
        {
            smallest = r;
        }

        // If the smallest of l or r, continue bubbleDown
        if (smallest != i)
        {
            swap(this->heapArray[i], this->heapArray[smallest]);
            bubbleDown(smallest);
        }
    }
    int getSize() const
    {
        return this->size;
    }
    void printHeap()
    {
        for (int i = 0; i < this->size; i++)
        {

            cout << this->heapArray[i] << "  ";
        }
        cout << endl;
    } // test
private:
    int capacity;
    int size;
    double heapArray[10];

    /* CREATE Empty Maps for future use */
    // std::unordered_map<string, double> stocksMap;
    // std::unordered_map<string, int> timesMap;

    /**********************************************
  Helpers to access our array easily, perform
  rudimentary operations, and manipulate capacity
    ************************************************/

    // If this->heapArray is full then double capacity
    void ensureExtraCapacity()
    {
        // create a new copy array for temporary storage
        double copyHeapArray[this->size];
        if (this->size == this->capacity)
        {
            // copy the previous heap array
            for (int i = 0; i < this->capacity; i++)
            {
                copyHeapArray[i] = this->heapArray[i];
            }

            // double the size of the heap array
            this->heapArray[this->size * 2];

            for (int j = 0; j < this->capacity; j++)
            {
                this->heapArray[j] = copyHeapArray[j];
            }

            // delete the temporary Array
            // delete[] copyHeapArray;

            // this->heapArray = Arrays.copyOf(this->heapArray, this->capacity * 2);
            this->capacity *= 2;
        }
    }
    // Returns the parent index
    int parent(int i) { return (i - 1) / 2; }
    // Returns the left child
    int left(int i) { return 2 * i + 1; }
    // Returns the right child
    int right(int i) { return 2 * i + 2; }
};

int main()
{

    int capacity = 10;
    int numberOfDays = 10;
    double totalBalance = 500.00;

    // priorityQ<int> p(capacity);
    /* Enter the stock exchange file to initialize */
    std::ifstream stockFile("Stocks.csv");
    std::string stockLine;
    std::string oneStock;
    string stockValue;
    vector<string> stockVector;

    getline(stockFile, stockLine);

    // std::cout << stockLine << "\n";
    std::stringstream stockStream(stockLine);
    std::string stockName;
    double stockDividened = 0.0;
    std::unordered_map<string, double> stocksMap;
    std::unordered_map<string, int> timesMap;

    std::cout << "STOCKS" << endl;
    int isInt;
    const type_info &isIntType = typeid(isInt);

    while (std::getline(stockFile, stockValue))
    {
        stockVector.push_back(stockValue);
    }

    // insert the values into the stocks unordered map
    for (string str : stockVector)
    {

        // construct a stream from the string
        std::regex regex("\\,");

        std::vector<std::string> stock(
            std::sregex_token_iterator(str.begin(), str.end(), regex, -1),
            std::sregex_token_iterator());
        stocksMap.insert({stock[0], stod(stock[1])});
        timesMap.insert({stock[0], 0}); // initialize
    }

    /* TEST:: Traversing an unordered map
    std::cout << "STOCKS MAP******" << endl;

    for (auto x : stocksMap)
        cout << x.first << " " << x.second << endl;
    std::cout << "STOCKS MAP******END***" << endl; */

    /* Enter the exchange parsed file */
    std::ifstream infile("NYSE.csv");
    std::string line;
    std::string pol;
    double exchangeValue;
    vector<double> exchange;

    getline(infile, line);

    // std::cout << line << "\n";
    std::stringstream ss(line);

    while (getline(ss, pol, ','))
    {
        exchangeValue = strtod(pol.c_str(), NULL);
        exchange.push_back(exchangeValue);
        std::cout << exchangeValue << "\n";
    }

    priorityQ<double> p(exchange);
    return 0;
}