#include <stdio.h>
#include <stdlib.h>

#include <map>

#include "map_sample_method.hpp"

class MapSample
{
public:
    MapSample();
    ~MapSample(){};

    int PurseData(uint16_t &data_id, int data);

private:
    std::map<uint16_t, void*> parse_methods;

};