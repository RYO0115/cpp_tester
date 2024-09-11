
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "format_reader.hpp"

using namespace specified_format_reader;

bool CheckOption(int argc
                , char* argv[]
                , int &x
                , std::string &file_name)
{
    int i, opt;
    opterr = 0;
    std::string s;

    // Init
    file_name = "";
    x = 0;

    bool ret = false;

    while((opt = getopt(argc, argv, "d:x:h")) != -1)
    {
        switch (opt){
            case 'd':
                file_name = optarg;
                break;
            case 'x':
                s = optarg;
                x = stoi(s);
                break;
            case 'h':
                printf("Usage: %s [-d abs_data_file_path] [-x num_to_print] [-h help]\n", argv[0]);
                break;
            default:
                printf("Usage: %s [-d abs_data_file_path] [-x num_to_print] [-h help] ...\n", argv[0]);
                break;
                
        }
    }

    if(file_name.size()!=0 && x!=0)
    {
        ret = true;
    }

    return(ret);
}


int main(int argc, char* argv[])
{
    std::vector<StructDataFormat> db;
    std::vector<StructDataFormat*> sorted_db;
    std::string file_name;
    int x;
    //std::string file_name = "../test/data/test1.txt";

    if(!CheckOption(argc, argv, x, file_name))
    {
        return(-1);
    }

    int error_count = file_importer::ImportDataFromFile(file_name, db);
    if(error_count >= 0)
    {
        std::cerr<<error_count<<" lines of "<<file_name<<" have different format!!"<<std::endl;
    }
    else{
        return(-1);
    }

    heap_sorter::CreateHeapNodeList(db, sorted_db);
    heap_sorter::HeapSort(sorted_db);

    //heap_sorter::PrintHeapNodes(sorted_db);

    printf("Requested Size:%d\n", x);
    printf("---------------------------------------\n");
    for(int i=0; i<x; i++)
    {
        printf("\t%ld %d\n", sorted_db[i]->timestamp, sorted_db[i]->x_data);
    }
    printf("---------------------------------------\n");

    return(0);
}
