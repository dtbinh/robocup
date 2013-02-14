#include "linedetector.h"
#include "boost/foreach.hpp"
#include "Tools/Math/LSFittedLine.h"

LineDetector::LineDetector() {}

LineDetector::~LineDetector() {}

vector<LSFittedLine> LineDetector::mergeColinear(vector<LSFittedLine> lines, double angle_threshold, double distance_threshold) const
{
    //O(l^2)  -  l=number of lines
    // Compares all lines and merges based on the angle between and the average distance between

    vector<LSFittedLine> finals; // this vector contains lines that have been merged or did not need to be.
    LSFittedLine current; // line currently being compared with the rest.

    while(!lines.empty()) {
        //get next line
        current = lines.back();
        lines.pop_back();

        vector<LSFittedLine>::iterator it = lines.begin();
        //go through all lines and find any that should be merged - merge them
        while(it < lines.end()) {
            if(current.getAngleBetween(*it) <= angle_threshold && current.averageDistanceBetween(*it) <= distance_threshold) {
                current.joinLine(*it);  //join the other line to current
                it = lines.erase(it);   //remove the other line
            }
            else {
                it++;
            }
        }
        //Now current should have been merged with any valid lines
        //push current to finals
        finals.push_back(current);
    }

    return finals;
}
