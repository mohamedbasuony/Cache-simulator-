#include "Direct_Mapping.h"

Direct_Mapping::Direct_Mapping()
{
    NumberOfBlocks = cacheSize / lineSize;
    NumberOfBits = log(lineSize) - 2;   // used for word offset
    Index_Bits = log2(NumberOfBlocks);    //used  for determining how many bits for the index field we need
    mask = pow(2, NumberOfBits + 2) - 1;
    
    Construct() ;
}

void Direct_Mapping::Construct()
{
    b = new store[NumberOfBlocks];
    
    Initialize() ;
    
}

void Direct_Mapping::Initialize()
{
    for (int i = 0; i < NumberOfBlocks; i++)
    {
        b[i].valid = false ;
        b[i].tag = -1;

        for (int i = 0; i < lineSize / 4; i++)
            for (int j = 0; j < 4; j++)
                b[i].check[i][j] = false;
    }
}

bool Direct_Mapping::Check_Cache(int Address ) // This function check the cache array. If valid is false, then the cache  block is empty and the function returns false. Otherwise, it checks if the tag of the address is the same as the one in the cache array. If that is the case, the function returns true.
{
    index = (Address >> (NumberOfBits + 2)) % NumberOfBlocks;
    Temp_B = Address & 3;
    Temp_W = (Address >> 2) & mask;
    
    if (b[index].valid == false)
        return false;
    else
    {
        temp_Tag = (Address >> (NumberOfBits + 2 + Index_Bits));
        if (b[index].tag == temp_Tag) {
            int poffset = (Address & mask);
            if (b[index].check[Temp_B][Temp_W] == true)
                return true;
            else
                return false;
        }
        else
            return false;
    }
}

void Direct_Mapping::Add_To_Cache(int Address)
// This function adds the address's tag and set the valid in the cache block. Thus function is instantiated if the cache block is empty. 
{
    for (int i = 0; i < lineSize; i++)
    {
        b[index].valid = true;
        b[index].tag = temp_Tag;
        b[index].check[Temp_W][Temp_B] = true;
        Address++;
    }
}

int Direct_Mapping::log(int a)
{
    int Counter = 0 ;
    
    while ( a > 1 )
    {
        Counter++ ;
        a = a / 2 ;
    }
    return Counter ;
}

Direct_Mapping::~Direct_Mapping()
{
    delete[] b;
}






/*int temp_Tag = (Address >> (NumberOfBits + 2 + Index_Bits));
int Offset_B = Address & 3;
int Offset_W = (Address >> 2) & mask;*/
