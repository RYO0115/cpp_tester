
#include "map_sample_class.hpp"

MapSample::MapSample()
{
    // Error
    //parse_methods[sample_methods::data_id_1] = sample_methods::Return1Plus;
    //parse_methods[sample_methods::data_id_2] = sample_methods::Return2Plus;
    //parse_methods[sample_methods::data_id_3] = sample_methods::Return3Plus;
    //parse_methods[sample_methods::data_id_4] = sample_methods::Return4Plus;

    // Error 2
    //parse_methods{
    //    {sample_methods::data_id_1, sample_methods::Return1Plus},
    //    {sample_methods::data_id_2, sample_methods::Return2Plus},
    //    {sample_methods::data_id_3, sample_methods::Return3Plus},
    //    {sample_methods::data_id_4, sample_methods::Return4Plus}
    //};
    parse_methods.insert(std::pair<uint16_t, >(sample_methods::data_id_1, sample_methods::Return1Plus));
    parse_methods.insert(std::pair<uint16_t, >(sample_methods::data_id_2, sample_methods::Return2Plus));
    parse_methods.insert(std::pair<uint16_t, >(sample_methods::data_id_3, sample_methods::Return3Plus));
    parse_methods.insert(std::pair<uint16_t, >(sample_methods::data_id_4, sample_methods::Return4Plus));
}

int MapSample::PurseData(uint16_t &data_id, int data)
{
    return(parse_methods[data_id](data));
}