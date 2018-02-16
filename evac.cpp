#include <cstdlib>
#include "evac.h"
#include "EvacRunner.h"

using namespace std;

void Evac::insertionSort(int numRoads, int *Roads)// to sort ID's based on capacity
{
   int key;
   int i = 1;
   while(i < numRoads)
   {
       key = Roads[i];
       int j = i-1;
       while (j >= 0)
       {
         if(roads[Roads[j]].capacity < roads[key].capacity)
         {
           Roads[j+1] = Roads[j];
           j = j-1;
         }
         else
          break;
       }
       Roads[j+1] = key;
       i++;
   }
}
Evac::Evac(City *citie, int numCitie, int numRoad) :numRoads(numRoad), numCities(numCitie)
{
  for(int i = 0; i < numCitie; i++)
  {
    cities[citie[i].ID].numRoads = citie[i].roadCount;
    cities[citie[i].ID].population = citie[i].population;
    cities[citie[i].ID].ID = citie[i].ID;
    cities[citie[i].ID].numEvacuees = 0;
  	cities[citie[i].ID].numEvacueted = 0;
  	cities[citie[i].ID].notEvacCity = true;
  	cities[citie[i].ID].visited = false;
    cities[citie[i].ID].roadIDs = new int[citie[i].roadCount];

    for(int j = 0; j < citie[i].roadCount; j++)
    {
      cities[citie[i].ID].roadIDs[j] = citie[i].roads[j].ID;
      roads[citie[i].roads[j].ID].ID =  citie[i].roads[j].ID;
      roads[citie[i].roads[j].ID].capacity =  citie[i].roads[j].peoplePerHour;
      roads[citie[i].roads[j].ID].currentCapacity = citie[i].roads[j].peoplePerHour;
      roads[citie[i].roads[j].ID].destination = citie[i].roads[j].destinationCityID;
    }

    insertionSort(cities[citie[i].ID].numRoads, cities[citie[i].ID].roadIDs);
  }
} // Evac()


void Evac::evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes,
    int &routeCount)
{
  routeCount = 0;
  evacID = new int[numEvacs];
  bool left = true;
  Stack stack(numCities);
  Queue usedRoads(numRoads * 5);

  for(int i = 0; i < numEvacs; i++)
  {
    evacID[i] = evacIDs[i];
	  cities[evacID[i]].notEvacCity = false;
  }

  while(left)
  {
  	left = false;

  	for(int i = 0; i < numEvacs; i++)
  	{
  		if(cities[evacID[i]].numEvacueted < cities[evacID[i]].population)
  		{
  			left = true;
  		}
  	}

    for(int i = 0; i < numEvacs; i++)// per city
    {
      count = 0;
      int needed = cities[evacID[i]].population - cities[evacID[i]].numEvacueted;
      stack.push(evacID[i]);
      cities[evacID[i]].visited = true;
      targetedCity = evacID[i];
      int temp = dfs(evacID[i], needed, 0, stack, usedRoads);
      while(stack.notEmpty())
      {
        cities[stack.topAndPop()].visited = false;
      }
      stack.count = 0;
    }

    for(int i = 0; i < usedRoads.count; i++)// store roads and reset vars
    {
      evacRoutes[routeCount].numPeople = roads[usedRoads.findAt(i)].capacity - roads[usedRoads.findAt(i)].currentCapacity;
      roads[usedRoads.findAt(i)].currentCapacity = roads[usedRoads.findAt(i)].capacity;
      cities[roads[usedRoads.findAt(i)].destination].visited = 0;
      evacRoutes[routeCount].roadID = usedRoads.findAt(i);
      evacRoutes[routeCount++].time = time;
    }// order based on looks cuz we real Gs

    usedRoads.makeEmpty();
    time++;
  }
} // evacuate

int Evac::dfs(int cityID , int needed, int sourceCityID, Stack& stack, Queue& usedRoads)
{
  int total = 0;
  // base case breaks the cycle
  if(count > 0)
  {
    if(!cities[cityID].visited)
    {
      cities[cityID].visited = true;
     stack.push(cityID);
    }
    else
      return 0;

    if(cities[cityID].notEvacCity)
    {
      if(needed > cities[cityID].population - cities[cityID].numEvacuees)// if no space in city
      {
        total = cities[cityID].population - cities[cityID].numEvacuees;
        cities[cityID].numEvacuees = cities[cityID].population;
      }
      else //if space in city
      {
        cities[cityID].numEvacuees += needed;
        return needed;
      }
    }
  }

  int i = 0;
  while(i < cities[cityID].numRoads)
  {
    if(total < needed)
    {
      if(roads[cities[cityID].roadIDs[i]].destination == sourceCityID && count > 0)
      {
          i++;
      }
      else
      {
        count++;
    	  int flow = roads[cities[cityID].roadIDs[i]].currentCapacity;
        if(flow > needed - total)
          flow = needed - total;
        flow = dfs(roads[cities[cityID].roadIDs[i]].destination, flow, cityID, stack, usedRoads);
        if(roads[cities[cityID].roadIDs[i]].currentCapacity - flow < 0)
        {
          roads[cities[cityID].roadIDs[i]].currentCapacity = 0;
        }
        else
        {
          	roads[cities[cityID].roadIDs[i]].currentCapacity -= flow;
        }
        total += flow;
        if(flow > 0)
          usedRoads.enque(cities[cityID].roadIDs[i]);
        i++;
      }
    }
    else
    {
      break;
    }
  }
  if(cityID == targetedCity)// pure gold
    count = 0;
  if(count == 0)
  {
    cities[cityID].numEvacueted += total;
  }
  return total;
}
