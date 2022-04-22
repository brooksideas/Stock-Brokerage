#include <iostream>
#include <string>
#include <queue>

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
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
        insert(4);
        insert(2);
        insert(1);
        insert(7);
        insert(8);
        insert(9);
        insert(11);
        insert(13);
        insert(10);

        printHeap(this->heapArray);
        getPriority();
    }
    // read everything from the given CSV file and parse and insert here
    priorityQ(vector<Type>);
    priorityQ(const priorityQ<Type> &);
    // ~priorityQ();
    const priorityQ<Type> &operator=(const priorityQ<Type> &);
    void insert(int p)
    {
        this->heapArray.push(p);
        this->size++;
    }
    void deletePriority();
    Type getPriority() const
    {
        return this->heapArray.top();
    }
    bool isEmpty() const
    {
        return this->heapArray.size() == 0 ? true : false;
    }
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const
    {
        return this->size;
    }
    void printHeap(priority_queue<int, vector<int>, greater<int>> gq)
    {

        priority_queue<int, vector<int>, greater<int>> g = gq;
        while (!g.empty())
        {
            cout << '\t' << g.top();
            g.pop();
        }
        cout << '\n';
    } // test
private:
    int capacity;
    int size;
    priority_queue<int, vector<int>, greater<int>> heapArray;
};

int main()
{

    int capacity = 10;

    priorityQ<int> p(capacity);

    return 0;
}