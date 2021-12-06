#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <bitset> 
#include <string>
#include <algorithm>
#include <tuple>
#include <set>

// TODO: Wie kann ich numBitsPerLine nicht hardcoden und trotzdem später als const verwenden? -> bitset möchte das im type haben
const std::string fileName{"day3_input.txt"}; 
const std::size_t numBitsPerLine = 12; 

// FUNCTION: sReturns the most common bit for a vector of bitsets at a specific index
int mostCommonBit(std::vector<std::bitset<numBitsPerLine>> vectorOfBitsets, int bitInd)
{
    int bitSum{0};
    for (auto it =std::begin(vectorOfBitsets); it != std::end(vectorOfBitsets); ++it) 
    {
        bitSum +=  static_cast<int>((*it)[bitInd]); // NOTE: Index 0 of a Bitsets is the most right, or in other words the least significant bit
    } 
    if(bitSum >= vectorOfBitsets.size()/2.0)
    return 1; 
    else 
    return 0;
}

// FUNCTION: sReturns the most common bit for a vector of bitsets at a specific index
int mostCommonBitBinaryIndices(std::vector<std::bitset<numBitsPerLine>> vectorOfBitsets, std::set<int> binaryIndices, int bitInd)
{
    int bitSum{0};
    for(auto binaryInd: binaryIndices)
    {
        bitSum += vectorOfBitsets[binaryInd][bitInd];
    }
    
    if(bitSum >= binaryIndices.size()/2.0)
    return 1; 
    else 
    return 0;
}

// FUNCTION sequence of most common bits 
std::tuple< std::bitset<numBitsPerLine>, std::bitset<numBitsPerLine> > gammaEpsilonRate(std::vector<std::bitset<numBitsPerLine>> vectorOfBitsets)
{
    std::bitset<numBitsPerLine> gammaRate;
    std::bitset<numBitsPerLine> epsilonRate;
    // NOTE: Index 0 of a Bitsets is the most right, or in other words the least significant bit
    for(int bitInd = 0; bitInd < numBitsPerLine; bitInd++)
    {
        gammaRate[bitInd] = mostCommonBit(vectorOfBitsets, bitInd);
        epsilonRate[bitInd] = 1 - gammaRate[bitInd];
    }
    return std::make_tuple(gammaRate, epsilonRate);
}

// FUNCTION -> Not needed anymore 
void eraseBinaries(std::vector<std::bitset< numBitsPerLine >> &binaryVector, int mostCommon, int ind)
{
    auto i = std::begin(binaryVector);//pointer on first element
        while (i != std::end(binaryVector))
        {
            if((*i)[ind] != mostCommon)
            {
                i = binaryVector.erase(i);
            }
            else{
                i++;
            }
        }
}

// FUNCTION
void eraseBinaryIndices(std::vector<std::bitset< numBitsPerLine >> &binaryVector, int mostCommon, int ind, std::set<int> &indices)
{
    std::set<int> indicesToErase;
    std::set<int> result;
    std::set<int>::iterator it = indices.begin();
    while (it != indices.end())
    {   
        if(binaryVector[(*it)][ind] != mostCommon)
            {
                // save all elements that are subtracted from the set later
                indicesToErase.insert(*it);
            }
        it++;
        
    }
    // erase indices using set difference TODO: better way? seems messy..
    std::set_difference(indices.begin(), indices.end(), indicesToErase.begin(), indicesToErase.end(),
    std::inserter(result, result.end()));
    indices = result;
}

void computeRating(std::vector<std::bitset< numBitsPerLine >> binaries, std::set<int> &indices, bool mostcommon)
{
    int mostOrLeastBit;
    int bitInd = numBitsPerLine - 1; 
    while(indices.size() > 1 )
    {
        // find most commond bit at position bitInd 
        if(mostcommon)
        mostOrLeastBit = mostCommonBitBinaryIndices(binaries, indices, bitInd);  
        else
        mostOrLeastBit = 1 - mostCommonBitBinaryIndices(binaries, indices, bitInd);  

        // Discard all binary indices that do not share most common bit at position bitInd
        eraseBinaryIndices(binaries, mostOrLeastBit, bitInd, indices); 
        
        bitInd--;
    }
}


int main()
{
    std::string stringvalue; 

    std::string line;
    std::ifstream filestream(fileName);
    
    int numLinesTextFile = 0;
    std::bitset<numBitsPerLine> bs;
    std::vector<std::bitset< numBitsPerLine >> binaries; // for binary data 

    // Loop thorugh text file and save lines as a vector of bitsets
    if (filestream.is_open()) 
    {
        while (std::getline(filestream, line)) 
        {
            std::istringstream linestream(line);
            while (linestream >> stringvalue) 
            {
                numLinesTextFile++;
                bs  = std::bitset<numBitsPerLine>(std::string(stringvalue));
                binaries.push_back(bs);
            }
        }
    filestream.close();
    } 
    std::bitset< numBitsPerLine> gammaRate; 
    std::bitset< numBitsPerLine> epsilonRate;

    std::tie(gammaRate,epsilonRate) = gammaEpsilonRate(binaries);
 
    std:: cout << "Result Part 1: gammarate * epsilonrate " << gammaRate.to_ulong()*epsilonRate.to_ulong() << std::endl; 
    // test: 22 * 9 = 198
    // regular: 2250414

    // Part 2 
    std::set<int> binindicesoxy;
    for (int i=0; i<numLinesTextFile; i++) binindicesoxy.insert(i);
    std::set<int> binindicesoco2 = binindicesoxy;

    computeRating(binaries, binindicesoxy, true); // True for most significant -> Oxygen Rating
    computeRating(binaries, binindicesoco2, false); // False for least significant -> Co2 Rating

    std::cout << "oxygen rating  = "  << binaries[*binindicesoxy.cbegin()].to_ulong() << std::endl; 
    std::cout << "co 2 rating  = "  << binaries[*binindicesoco2.cbegin()].to_ulong() << std::endl; 
    std::cout << "Result Part 2: (oxygen generator rating * CO2 scrubber rating) = "  << binaries[*binindicesoxy.cbegin()].to_ulong() * binaries[*binindicesoco2.cbegin()].to_ulong() << std::endl; 
    // test: 23*10 = 230, regular 6085575

    return 0;
}