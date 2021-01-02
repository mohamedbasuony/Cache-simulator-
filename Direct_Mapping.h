#include "Includes.h"

const int cacheSize = 32 * 1024; // This is cache of size 64 kb
const int lineSize = 16 ;

struct store
{
    bool valid;
    unsigned int tag;
    bool check[lineSize/4][4] ;
};

class Direct_Mapping
{
    
private:
    
    int NumberOfBlocks , NumberOfBits , Index_Bits , mask , index , Temp_B , Temp_W , temp_Tag ;
    store* b;

public:

    Direct_Mapping();
    void Construct() ;
    void Initialize() ;
    bool Check_Cache(int Address);
    void Add_To_Cache(int Address);
    int log(int a);
    ~Direct_Mapping();
};
