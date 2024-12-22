
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#include "format_reader.hpp"

using namespace specified_format_reader;

/**
 * @brief Function to create command options.
 * @details [-f argument] file path
 *          [-x argument] print data size 
 *          [-h] show usage
 * 
 * @param argc 
 * @param argv 
 * @param x [out]
 * @param file_name [out]
 * @return true 
 * @return false 
 */
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

    while((opt = getopt(argc, argv, "f:x:h")) != -1)
    {
        switch (opt){
            case 'f':
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
    else{
        printf("Usage: %s [-d abs_data_file_path] [-x num_to_print] [-h help]\n", argv[0]);
    }

    return(ret);
}


int main(int argc, char* argv[])
{
    std::vector<StructDataFormat> db;
    std::vector<StructDataFormat*> sorted_db;
    std::string file_name;
    int x;

    if(!CheckOption(argc, argv, x, file_name))
    {
        return(-1);
    }

    int error_count = file_importer::ImportDataFromFile(file_name, db);
    printf("Input Data Size:%d\n",(int)db.size());
    if(error_count > 0)
    {
        //std::cerr<<error_count<<" lines of "<<file_name<<" have different format!!"<<std::endl;
        printf("%d lines of %s have different format!!\n", error_count, file_name.c_str());
    }
    else if(error_count == -1)
    {
        return(-1);
    }

    heap_sorter::CreateHeapNodeList(db, sorted_db);
    heap_sorter::HeapSort(sorted_db);

    //heap_sorter::PrintHeapNodes(sorted_db);

    printf("Requested Size:%d\n", x);
    printf("Database Size:%d\n", (int)db.size());
    int print_size = x;
    if(x>(int)db.size())
    {
        printf("Selected print size is too big for this database!!\n");
        print_size = db.size();
    }
    
    printf("---------------------------------------\n");

    for(int i=0; i<print_size; i++)
    {
        printf("\t%d: %ld %d\n", i, sorted_db[i]->timestamp, sorted_db[i]->x_data);
    }
    printf("---------------------------------------\n");

    return(0);
}
