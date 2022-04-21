#include<iostream>
#include<string>
#include<queue>
using namespace std;
struct stockType
{
std:: string name;
int timesPurchased;
double dividend;
double price;
bool operator<( const stockType& rhs)
{
}
};
template <class Type >
class priorityQ
{
public:
priorityQ(int = 10);
1
priorityQ(vector <Type >);
priorityQ(const priorityQ <Type >&);
~priorityQ ();
const priorityQ <Type >& operator =(const priorityQ <Type >&);
void insert(Type);
void deletePriority ();
Type getPriority () const;
bool isEmpty () const;
void bubbleUp(int);
void bubbleDown(int);
int getSize () const;
private:
int_t capacity;
int_t size;
Type * heapArray;
};