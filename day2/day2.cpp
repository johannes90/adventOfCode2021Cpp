#include <vector>
#include <iostream>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm> // for std::copy
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>

int main() 
{ 
    int y     = 0; // up, down
    int x     = 0; // forward
    int value = 0; // the value of any command
    int aim   = 0;

    std::string command; 
    std::string line;
    const std::string forwardCommand{"forward"};
    const std::string downCommand{"down"};
    const std::string upCommand{"up"};

    std::ifstream filestream("data2.txt");

    if (filestream.is_open()) 
    {

        while (std::getline(filestream, line)) 
        {
        
            std::istringstream linestream(line);
            while (linestream >> command >> value) 
            {
                if(command == forwardCommand)
                {
                    x += value;
                    
                    y += (aim*value);
                }
                else if(command == downCommand)
                {
                    
                    aim   += value;
                }
                else if(command == upCommand)
                {
                    

                    aim   -= value;
                }
            }
        }
        std::cout << "depth (y): " << y << std::endl; 
        std::cout << "horizontal (x): " << x << std::endl; 
        std::cout << "solution (depth*horizontal): " << x * y << std::endl;
    }
    
}