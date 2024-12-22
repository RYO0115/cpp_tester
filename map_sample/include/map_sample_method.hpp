
#include <stdio.h>
#include <stdlib.h>

namespace sample_methods
{
    int Return1Plus(int var){return(var+1);}
    int Return2Plus(int var){return(var+2);}
    int Return3Plus(int var){return(var+3);}
    int Return4Plus(int var){return(var+4);}

    typedef enum{
        data_id_1=0x0001,
        data_id_2=0x0010,
        data_id_3=0x0100,
        data_id_4=0x1000
    }DataID;

}