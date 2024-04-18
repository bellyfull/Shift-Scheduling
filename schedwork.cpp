#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
// bool search(int row, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<int>& shiftCount );

bool search(int row, int slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& shiftCount);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    // if(avail.size() == 0U){
    if (avail.empty() || avail[0].empty()) {
        return false; 
    }
    sched.clear(); // initialize to all 
    // Add your code below

    size_t n = avail.size();
    size_t k = avail[0].size();
    
    sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<int> shiftCount(k,0);


    return search(0,0, avail, dailyNeed, maxShifts, sched, shiftCount);
}

// bool search(int row, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, std::vector<int>& shiftCount ) {

//   size_t n = avail.size();
//   size_t k = avail[0].size();

//      if (row == n) {
//         return true; //success
//     }

//     // unsigned int numWorkers = 0;
//     // for (unsigned int col =0; col< k; ++col) {
//     //   if (avail[row][col] && shiftCount[col]<maxShifts) {
//     //     numWorkers++;
//     //   }
//     // }

//     // if (numWorkers < dailyNeed) {
//     //   return false; // not enough workers for the daily need minimum req
//     // }

//     for (unsigned int col = 0; col < k ; col++ ) { // iterating through all
//         if (avail[row][col] == false || shiftCount[col] >= maxShifts) {
//           continue;
//         }
//         // if ( avail[row][col] == 1 && shiftCount[col] < maxShifts) {   
//         //     for (size_t schedCol = 0; schedCol < dailyNeed; schedCol++) { 
//         //         if (sched[row][schedCol] == INVALID_ID) {
//         //             sched[row][schedCol] = col; // assign worker
//         //             shiftCount[col]++;
                    
//         //             if (search(row+1, avail, dailyNeed, maxShifts, sched, shiftCount)) { // will only search from rows 0~n-1. (the days)
//         //                 return true; // valid. move to next col
//         //             }
//         //             sched[row][schedCol] = INVALID_ID; // backtrack bc this worker for this day in the schedule column doesn't work
//         //             shiftCount[col]--;

//         //         }
//         //     }
//         // }
        
//         for (size_t schedCol = 0; schedCol < dailyNeed; schedCol++) { 
//                 if (sched[row][schedCol] == INVALID_ID) {
//                     sched[row][schedCol] = col; // assign worker
//                     shiftCount[col]++;
                    
//                     if (search(row+1, avail, dailyNeed, maxShifts, sched, shiftCount)) { // will only search from rows 0~n-1. (the days)
//                         return true; // valid. move to next col
//                     }
//                     sched[row][schedCol] = INVALID_ID; // backtrack bc this worker for this day in the schedule column doesn't work
//                     shiftCount[col]--;

//                 }
//         }
//     }
//     return false; //no solution exists
// }



//change to one loop 
//iterate by slot at each recursive call don't try to fill out row at once



bool search(int row, int slot, const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& shiftCount) {
  size_t n = avail.size();
  size_t k = avail[0].size();

  if (row ==n) {
    return true; //success
  }

  if (slot == dailyNeed) { // all slots of dailyneed is filled
    return search(row+1, 0, avail, dailyNeed, maxShifts, sched, shiftCount); // move to next row/day
  }

  for (size_t worker = 0; worker < k; worker++) { // iterating through all workers at current slot
    if (avail[row][worker] && shiftCount[worker] < maxShifts) { // if available, and hasn't worked max amt of shifts
      sched[row][slot] = worker; // if so, schedule the worker for that day's specific slot
      shiftCount[worker]++; // update their shift count

      if (search(row, slot +1, avail, dailyNeed, maxShifts, sched, shiftCount)) { // call on next slot of the day
        return true;
      }

      sched[row][slot] = INVALID_ID; // if at this point, couldn't find a solution. backtrack 
      shiftCount[worker]--; // decrement 
    }
  }
  return false; //no solution exists
}