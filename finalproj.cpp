#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>  /* to use exit */
using namespace std;

// FALL22-SPR23 
// Update this file for HW2 FWDC (Yoshii)
// Read the main() first and write down all the functions it calls!
// Then, look for *** using control-S and add code. 
// ** always marks where you need to change!
//--------------------------------------------------
// YOUR NAME: Alfonso De La Cruz
// Tested on Empress using g++  
//--------------------------------------------------

// State description class.
// Could have used struct.
// Items here is a string of L or R for FWDC 
//    e.g. RRRR for the initial state
class state
{
public:
  string items;  // made up of L and R going from RRRR to LLLL 
  string camefrom; // the parent on the solution path
  int g;   // cost so far
  int h;   // estimated cost to the goal
  int f;   // g+h
};

// Major data structures:
vector<state> frontier;  // Frontier nodes - will pick one of these to expand
vector<state> beenThere; // already expanded nodes

// ========== Utility Functions ===================

// utility to add x to the beenthere
void addtoBeenThere(state x)
{  beenThere.push_back(x); }

// utility to add x to the frontier
void addtoFrontier(state x)
{  frontier.push_back(x); }

// to remove state x from the frontier when it has been expanded
void removefromFrontier(state x)
{  
  vector<state> newfrontier;
  for (int k = 0; k < frontier.size(); k++)
    if (frontier[k].items != x.items)
      newfrontier.push_back(frontier[k]);

  frontier = newfrontier;
}

//============= At the Very End ====================

// Trace and display the solution path from goal to initial.
// Note that camefrom of each state should be used. (called from generate)
void tracePath(state goal)
{
  state newS;
  if(goal.items =="RRRR")
    {

      exit(0);
    }
  cout << "came from" << endl;

  for(int i = 0; i<beenThere.size(); i++)
    if(goal.camefrom == beenThere[i].items)
      newS = beenThere[i];
  cout << newS.items << endl;
  tracePath(newS);
}// end of tracePath  

//======= For Generating a new state to add to Frontier  =============

// Check to see if next's items is already in frontier and return true or false.
//   If it is already in frontier, 
//   and if the next's f is better, 
//   update the frontier node to next.  (called from generate)
bool inFrontier(state next)
{
  bool there = false;

  for(int i = 0; i<frontier.size(); i++)
    if(next.items == frontier[i].items)
      {
	cout << endl << "Already in frontier" << endl;
	if (next.f < frontier[i].f)
	  {
	  
	    frontier[i] = next;
	    cout << "f is better" << endl;
	  }
	else
	  cout << "f not better" << endl;

	there = true;
      }

  // the same frontier node with next if f is better.
  // Please cout a message in that case.
  // Return true or false.
  return there;
}// end of inFrontier


// Try to add next to frontier but stop if LLLL (called from generateAll)
void generate(state next)
{ 
  cout << "Trying to add: " << next.items; 

  if (next.items  == "LLLL")  // the goal is reached
    { cout << endl <<  ">> Reached Goal: " << next.items << endl;
      tracePath(next);  // display the solution path
      exit(0); }//done
  bool been = false;
  // if been there before, do not add to frontier.
  for(int i = 0; i<beenThere.size(); i++)
    if(next.items == beenThere[i].items)
      been = true;
  if(been==true)
    {
      cout << " been there already" << endl;
      return;
    }
  // You may write a utility function check been-there and call it

  // if unsafe, do not add to frontier.
  bool safe = true;
  if(next.items == "LRRR" || next.items == "LLRR" || next.items == "RLLL" || next.items == "RRLL" || next.items == "RLLR" || next.items == "LRRL")
    safe = false;
  if (safe == false)
    {
    cout << " unsafe!" << endl;
    return;
    }
  else
    cout << " safe!";
  // You may write a function to check unsafe and call it

  // else compute h and then f for next
  int h = 0;// start point for h; g is already set
  // update h and then f
  for (int i = 1; i<4; i++)
    if(next.items[i] == 'R')
      h++;
  next.f= next.g + h;
  next.h = h;
  //next.f = f;
  if (!inFrontier(next))
    {
      cout << endl << "Not in frontier yet" << endl;
      addtoFrontier(next); // add next to Frontier 
    }
  

}// end of generate   



// Generate all new states from current (called from main)
//  This calls generate for each new state
void generateAll(state current)
{
  state next;  // a generated one

  // each next will be modified from current for ease
  current.g = current.g + 1; // to update g to be used for next
  // storing the parent so that we can produce the solution path
  current.camefrom = current.items; 

  // check all possibilities as follows..

  // move F alone to L
  next = current;  // starting point of next is current
  if (current.items[2] == 'S')
    { next.items[0]='S'; generate(next);};

  next = current; // starting point of next
  // move F alone to R
  if (current.items[0] == 'L')
    { next.items[0]='R'; generate(next);};

  next = current; // starting point of next
  // move FW to L
  if (current.items[0] == 'R' && current.items[1] == 'R')
    { next.items[0]='L'; next.items[1] = 'L'; generate(next);};  

  next = current; // starting point of next
  // move FW to R
  if (current.items[0] == 'L' && current.items[1] == 'L')
    { next.items[0]='R'; next.items[1] = 'R'; generate(next);};  
  
  next = current; // starting point of next
  // move FD to L
  if (current.items[0] == 'R' && current.items[2] == 'R')
    { next.items[0]='L'; next.items[2] = 'L'; generate(next);};  

  next = current; // starting point of next
  // move FD to R
  if (current.items[0] == 'L' && current.items[2] == 'L')
    { next.items[0]='R'; next.items[2] = 'R'; generate(next);};  

  next = current; // starting point of next
  // move FC to L
  if (current.items[0] == 'R' && current.items[3] == 'R')
    { next.items[0]='L'; next.items[3] = 'L'; generate(next);};  

  next = current; // starting point of next
  // move FC to R 
  if (current.items[0] == 'L' && current.items[3] == 'L')
    { next.items[0] = 'R'; next.items[3] = 'R'; generate(next); };  

}// end of generateAll


// Find the best f state out of the frontier and return it (called from main)
state bestofFrontier()
{ 
  state j = frontier[0];
  for(int k = 0; k< frontier.size(); k++)
    if(frontier[k].f < j.f)
      j = frontier[k];//j hold the state with the best f
  
  return j;
}//end of bestofFrontier

// Display the states in the frontier  (called from main)
void displayFrontier()
{
  for (int k = 0; k < frontier.size(); k++)
    { cout << frontier[k].items << " ";  
      cout << "g = " <<frontier[k].g << " ";
      cout << "h = " <<frontier[k].h << " ";
      cout << "f = " <<frontier[k].f << endl; 
    }
}// end of displayFrontier

//================= Main ===========================

int main() 
{

  state  current = {"RRRR","", 0, 3, 3};  // initial
  addtoFrontier(current);

  char ans;
  while ( ans != 'n')
    { 
      removefromFrontier(current);      
      addtoBeenThere(current);

      cout << ">>>Expand:" << current.items << endl; 
      generateAll(current);  // new states are added to frontier

      cout << "Frontier is:" << endl;
      displayFrontier();

      current = bestofFrontier(); // pick the best state out of frontier
      cout << "Best is: " << current.items << endl;
      cin >> ans;

    }// end while

}//end of main

