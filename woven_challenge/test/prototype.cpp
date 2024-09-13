#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>



typedef struct{
    uint64_t timestamp;
    int x_data;
} StructDataFormat;

typedef enum{
    TIMESTAMP = 0,
    X_DATA,
    DATA_COLUMNS,
} DATA_FORMAT;



void SwapNode(StructDataFormat* data1, StructDataFormat* data2)
{
    printf("Swap %d %d --> ", data1, data2);
    StructDataFormat* tmp_data = data1;
    data1 = data2;
    data2 = tmp_data;
    printf("%d %d\n", data1, data2);
}

void CreateHeapNodeList(std::vector<StructDataFormat> &db, std::vector<StructDataFormat*> &heap_tree)
{
    heap_tree.resize(db.size());

    for(int i=0; i<(int)db.size(); i++)
    {
        heap_tree[i] = &db[i];
    }
}

void PrintHeapNodes(std::vector<StructDataFormat*> &heap_tree)
{
    printf("\tCurrent Result:\n");
    for(int j=0; j<(int)heap_tree.size(); j++){
        if(heap_tree[j]!=NULL) printf("\t\t%ld, %d\n", heap_tree[j]->timestamp, heap_tree[j]->x_data);
    }
}

void Heapify(std::vector<StructDataFormat*> &heap_tree, int tree_size, int default_largest_id)
{

    int left    = 2 * default_largest_id + 1;
    int right   = 2 * default_largest_id + 2;

    if(left < tree_size
        && heap_tree[left]->x_data > heap_tree[default_largest_id]->x_data)
    {
        //swap
        StructDataFormat* tmp_data;
        tmp_data = heap_tree[default_largest_id];
        heap_tree[default_largest_id] = heap_tree[left];
        heap_tree[left] = tmp_data;

        Heapify(heap_tree, tree_size, left);
    }

    if(right < tree_size
        && heap_tree[right]->x_data > heap_tree[default_largest_id]->x_data)
    {

        //swap
        StructDataFormat* tmp_data;
        tmp_data = heap_tree[default_largest_id];
        heap_tree[default_largest_id] = heap_tree[right];
        heap_tree[right] = tmp_data;

        Heapify(heap_tree, tree_size, right);
    }

}

void HeapSort(std::vector<StructDataFormat*> &heap_tree)
{
    std::vector<StructDataFormat*> tmp_tree;
    tmp_tree.resize(heap_tree.size());

    for(int i=(int)heap_tree.size()/2; i >= 0; i--)
    {
        Heapify(heap_tree, heap_tree.size(), i);
    }

    int biggest = 0;
    for(int i = (int)heap_tree.size() - 1; i >= 0; i--)
    {
        tmp_tree[biggest] = heap_tree[0];
        heap_tree[0] = heap_tree[i];
        heap_tree[i] = NULL;

        Heapify(heap_tree, i, 0);
        biggest++;
    }

    for(int i=0; i<(int)heap_tree.size(); i++)
    {
        heap_tree[i] = tmp_tree[i];
    }

    //PrintHeapNodes(heap_tree);

}


int main(void)
{
    std::string file_name = "../test/data/test1.txt";
    std::ifstream line_count_ifs(file_name);
    
    std::string str, word;
    long timestamp;
    int data;

    if( (line_count_ifs.fail())){
        std::cerr<<"Failed to Open File"<<std::endl;
        return(-1);
    }

    int db_size = 0;
    while( getline(line_count_ifs, str))
    {
        db_size++;
    }

    std::vector< StructDataFormat > db;
    db.resize(db_size);

    std::ifstream ifs(file_name);
    int line_counter=0;
    int format_error_counter = 0;
    while( getline(ifs, str) )
    {
        if(sscanf( str.c_str(), "%ld %d", &timestamp, &data) == DATA_COLUMNS)
        {
            //printf("%ld, %d\n", timestamp, data);
            db[line_counter].timestamp = timestamp;
            db[line_counter].x_data = data;
            printf("%ld, %d\n", db[line_counter].timestamp, db[line_counter].x_data);
            line_counter++;
        }
        else{
            // If data size is too big or too small, won't be added to database.
            format_error_counter++;
        }
    }

    std::cout<<"Data Size:"<<line_counter<<"(Format Error:"<<format_error_counter<<")"<<std::endl;

    // Searching Algorythms.

    std::vector<StructDataFormat*> sorted_db;
    CreateHeapNodeList(db, sorted_db);
    HeapSort(sorted_db);
    PrintHeapNodes(sorted_db);


    return(0);
}