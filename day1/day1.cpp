#include <vector>
#include <iostream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy


// Code to solve advent of code day 1
#include <iostream>
#include <algorithm>


int main()
{
    std::ifstream is("data.txt");
    std::istream_iterator<double> start(is), end;
    std::vector<double> measurements(start, end);

    std::cout << measurements.size() << std::endl;
    std::copy(measurements.begin(), measurements.end(), std::ostream_iterator<double>(std::cout, " "));

    int last = measurements.front(); 
    int counter = 0;
    // count how many measurements are larger than the previous measurement
    for(const auto& measurement: measurements) // range based for loop 
    {
        if(measurement > last)
        {
            counter ++;    
        }
        last = measurement;
    }
    std::cout << counter << " measurements were larger than the previous measurement" << std::endl; 


    // Part 2
    int sum = 0;
    int lastSum = measurements[0] + measurements[1] + measurements[2];
    counter = 0;
    for(int i = 1; i < measurements.size() - 2; i++)
    {
        if (i == measurements.size() - 3)
        {
            std::cout << i <<std::endl;
        }

        sum = measurements[i] + measurements[i+1] + measurements[i+2];

        if(sum > lastSum)
        {
            counter ++;
        }
        lastSum = sum;

    }
    std::cout << counter << " sums of moving window of 3 measurements were larger than the previous window" << std::endl;



}
