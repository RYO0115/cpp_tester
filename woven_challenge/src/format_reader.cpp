
#include "format_reader.hpp"

namespace specified_format_reader
{

    void heap_sorter::CreateHeapNodeList(std::vector<StructDataFormat> &db, std::vector<StructDataFormat*> &heap_tree)
    {
        heap_tree.resize(db.size());

        for(int i=0; i<(int)db.size(); i++)
        {
            heap_tree[i] = &db[i];
        }
    }

    void heap_sorter::PrintHeapNodes(std::vector<StructDataFormat*> &heap_tree)
    {
        printf("\tCurrent Result:\n");
        for(int j=0; j<(int)heap_tree.size(); j++){
            if(heap_tree[j]!=NULL) printf("\t\t%ld, %d\n", heap_tree[j]->timestamp, heap_tree[j]->x_data);
        }
    }

    void heap_sorter::Heapify(std::vector<StructDataFormat*> &heap_tree, int tree_size, int default_largest_id)
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

    void heap_sorter::HeapSort(std::vector<StructDataFormat*> &heap_tree)
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

    }

    int file_importer::CountFileDataSize(const std::string &file_name)
    {
        int ret = -1;
        std::string str;
        std::ifstream line_count_ifs(file_name);
        if( (line_count_ifs.fail())){
            std::cerr<<"Failed to Open File"<<std::endl;
        }
        else{
            int db_size = 0;
            while( getline(line_count_ifs, str))
            {
                db_size++;
            }
            ret = db_size;
        }
        return(ret);
    }

    bool file_importer::ReadData(const std::string &str, long &timestamp, int &data)
    {
        bool ret = false;

        if(sscanf( str.c_str(), "%ld %d", &timestamp, &data) == DATA_COLUMNS)
        {
            ret = true;
        }
        
        return(ret);
    }

    int file_importer::ImportDataFromFile(const std::string &file_name
                                , std::vector<StructDataFormat> &db)
    {
        int db_size = 0;
        std::string str;
        std::ifstream ifs(file_name);
        long timestamp = 0;
        int data = 0;

        db_size = CountFileDataSize(file_name);
        if(db_size<0)
        {
            return(-1);
        }

        db.resize(db_size);

        int line_counter=0;
        int format_error_counter = 0;
        while( getline(ifs, str) )
        {
            if(ReadData(str
                , db[line_counter].timestamp
                , db[line_counter].x_data) )
            {
                line_counter++;
            }
            else{
                /**
                 * @brief If data size is too big or too small, 
                 *          won't be added to database.
                 */
                format_error_counter++;
            }

        }
        db.resize(line_counter);

        return(format_error_counter);
    }

}