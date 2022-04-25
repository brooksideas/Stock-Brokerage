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
    }
    // read everything from the given CSV file and parse and insert here
    priorityQ(vector<Type> value)
    {
        this->size = 0;
        this->capacity = 10;
        cout << "Exchange " << endl;

        // Insert Start of day Exchange read
        for (double i : value)
            insert(i);
        cout << endl;
        printHeap();
        cout << endl;
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
            ensureExtraCapacity();
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
    // For testing purpose only 
    void printHeap()
    {
        for (int i = 0; i < this->size; i++)
        {

            cout << this->heapArray[i] << "  ";
        }
        cout << endl;
    } 
private:
    int capacity;
    int size;
    double heapArray[10];
 
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

    // Input the following from the user
    int capacity = 10;
    int numberOfDays = 10;
    double totalBalance = 500.00;
    std::string simulateFile = "NYSE.csv";

    /* Enter the stock exchange file to initialize */
    std::ifstream stockFile("Stocks.csv");
    std::string stockLine;
    std::string oneStock;
    string stockValue;
    vector<string> stocksVector;
    vector<string> stocksNameVector;

    std::stringstream stockStream(stockLine);
    std::string stockName;
    double stockDividened = 0.0;
    double remainingBalance = totalBalance;
    double totalProfit = 0.0;
    std::unordered_map<string, double> stocksMap;
    std::unordered_map<string, int> timesMap;
    vector<double> stockStartVector;
    vector<double> stockEndVector;

    std::cout << "STOCKS" << endl;

    while (std::getline(stockFile, stockValue))
    {
        std::cout << "STOX => " << stockValue << endl;
        stocksVector.push_back(stockValue);
    }

    // insert the values into the stocks unordered map
    for (string str : stocksVector)
    {

        // construct a stream from the string
        std::regex regex("\\,");

        std::vector<std::string> stock(
            std::sregex_token_iterator(str.begin(), str.end(), regex, -1),
            std::sregex_token_iterator());
        stocksNameVector.push_back(stock[0]);
        stocksMap.insert({stock[0], stod(stock[1])});
        timesMap.insert({stock[0], 0}); // initialize the times a stock is bought to zero
    }

    /* TEST:: Traversing an unordered map*/
    std::cout << "STOCKS MAP******" << endl;

    for (auto x : timesMap)
        std::cout << x.first << " " << x.second << endl;
    std::cout << "STOCKS MAP******END***" << endl;

    /* Enter the exchange parsed file */
    std::ifstream infile(simulateFile);
    std::string line;
    std::string stockValueString;
    double oneStockValue;

    int currentDay = 2; // strats from first day

    /* SIMULATION */
    // loop through the number of days to simulate until it is reached
    // If 10 days simulated we will loop until 20 (10 * 2)
    while (numberOfDays * 2 >= currentDay)
    {

        int currentDateToFetch = currentDay; // starting from one so 2 is for one day (Start and End fetched)
        int fetchLines = 0;

        // build the start and end values of the stocks to calculate
        while (fetchLines < currentDateToFetch && getline(infile, line))
        {
            std::cout << " Line " << line << "\n";

            // Read as stream
            std::stringstream fetchStartLine(line);
            // Insert as double the last two lines on fetch i.e (start and end stock values )
            if (fetchLines == currentDateToFetch - 2)
            {
                while (getline(fetchStartLine, stockValueString, ','))
                {
                    oneStockValue = strtod(stockValueString.c_str(), NULL);
                    stockStartVector.push_back(oneStockValue);
                    std::cout << "START VEC => " << oneStockValue << "\n";
                }
            }
            if (fetchLines == currentDateToFetch - 1)
            {
                while (getline(fetchStartLine, stockValueString, ','))
                {
                    oneStockValue = strtod(stockValueString.c_str(), NULL);
                    stockEndVector.push_back(oneStockValue);
                    std::cout << "END VEC => " << oneStockValue << "\n";
                }
            }

            fetchLines++;
        };
        // Seek back to the start of the file
        infile.seekg(0);
        // Build the Priority Queue
        priorityQ<double> p(stockStartVector);

        // calculate gains for the current day
        while (remainingBalance > 0)
        {
            // Perform as long as the next stock purchase would not max out our remaining balance
            if (remainingBalance - p.getPriority() > 0)
            {
                std::string nameOfStock = "";
                // find the index of the priority in the start stock vector
                std::vector<double>::iterator itr = std::find(stockStartVector.begin(), stockStartVector.end(), p.getPriority());
                int nameOfStockIndex = std::distance(stockStartVector.begin(), itr);
                std::cout << "GET NAME OF the Stock Index ->" << nameOfStockIndex << endl;

                // get the name of the stock purchased using the index fetched
                nameOfStock = stocksNameVector[nameOfStockIndex];

                // add to the number of times map when a specific stock is purchased
                try
                {
                    timesMap.at(nameOfStock) += 1;
                }
                catch (const std::exception &e)
                {
                    std::cerr << e.what() << '\n';
                }

                // get the profits made by calculating the buy on start date to value at End of day
                totalProfit = totalProfit + (stockEndVector[nameOfStockIndex] - stockStartVector[nameOfStockIndex]);
                std::cout << "Purchased stock name ->" << nameOfStock << " valued at " << stockStartVector[nameOfStockIndex] << " per share" << endl;

                // subtract the purchased amount from the total available funds
                remainingBalance = remainingBalance - p.getPriority();

                // adjust priority queue
                p.deletePriority();

                std::cout << "GET remainingBalance ->" << remainingBalance << endl;
            }
            else
            {
                // calculate the total balance made include todays purchase
                totalBalance = totalBalance + totalProfit;
                // exit out the loop by maxing out the remaining balance
                remainingBalance = 0;
            }
        }
        // profits made today
        std::cout << "Profit made today ->" << totalProfit << endl;

        // total balance currently
        std::cout << "Day " << ((currentDay + 2) / 2) << " Current balance -> " << totalBalance << endl;

        // Set the remaining balance to the total balance to continue trading in the stock market
        remainingBalance = totalBalance;

        // Reset the start and end vectors and total profit of the day by the end of day
        stockStartVector.clear();
        stockEndVector.clear();
        totalProfit = 0.0;

        // increase by two to go to the next date to be fetched
        currentDay = currentDay + 2;
    }
    std::cout << "**********Simulation End******" << endl;

    for (int i = 0; i < 25; i++)
    {
        // get the dividened per stock from stockMap and the multiply it with the number of times stock was purchased
        double oneStockDividened = stocksMap.at(stocksNameVector[i]) * timesMap.at(stocksNameVector[i]);
        stockDividened = stockDividened + oneStockDividened;
    }
    std::cout << "Balance after 10 days $ " << totalBalance << endl;
    std::cout << "Amount in dividends " << stockDividened << endl;
    return 0;
}