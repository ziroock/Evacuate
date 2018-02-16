#ifndef evacH
#define evacH

#include "EvacRunner.h"


// simple queue
class Queue{

  public:
		int size,
        count,
        front,
        back,
        *storage;

    Queue(int num) :
        size(num),count(0), front(0), back(0)
    {
        storage = new int[size];
    }

    void enque(int city)
    {
        storage[back] = city;
        back++;
        count++;
    }

    int findAt(int i)
    {
      return storage[i];
    }
		bool notEmpty()
		{
				if (count == 0)
					return true;
				return false;
		}

  	void deque()
  		{
      	front++;
				count--;
  		}
    void makeEmpty()
    {
      front = count = back = 0;
    }

  	int seekFront()
  	{
      if (count > 0)
          return storage[front];
      return NULL;
  	}

  ~Queue()
  {
      delete storage;
  }
};
// simple stack
class Stack {

public:
	int count,
      *storage;

	Stack(int num)
	{
		count = 0;
		storage = new int[num];
	}

	void push(int city)
	{
		storage[count++] = city;
	}

	bool notEmpty()
	{
		if (count >= 0)
			return true;
		return false;
	}

	void pop()
	{
		--count;
	}

	int top()
	{
		return storage[count];
	}

	int topAndPop()
	{
		return storage[--count];
	}

	~Stack()
	{
		delete storage;
	}
};

class myCity
{
public:
  int ID,
      population,
      numEvacuees,
      numEvacueted,
      numRoads,
      *roadIDs;
  bool visited,
       notEvacCity;
  myCity() {}
};



class myRoad
{
public:
  int ID,
      destination,
      currentCapacity,
      capacity;
  myRoad() {}
};

class Evac
{
  int numCities,
      numRoads,
      targetedCity,// for dfs
      count, // for dfs
      time = 1,
      *evacID;

  myCity *cities = new myCity[numCities];
  myRoad *roads = new myRoad[numRoads * 3];


  int dfs(int cityID , int needed, int sourceCityID, Stack& stack, Queue& usedRoads);
	void insertionSort(int numRoads, int *Roads);

public:
  Evac(City *cities, int numCities, int numRoad);
  void evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes,
    int &routeCount); // student sets evacRoutes and routeCount
}; // class Evac
#endif
