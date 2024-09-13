/**
 * @file specified_format_reader.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <vector>

namespace specified_format_reader
{
    typedef struct{
        long timestamp;
        int x_data;
    } StructDataFormat;

    typedef enum{
        TIMESTAMP = 0,
        X_DATA,
        DATA_COLUMNS,
    } ENUM_DATA_FORMAT;
    namespace heap_sorter
    {
        /**
         * @brief Create a Heap Node List object
         * @details Create Heap Node list with pointer of StructDataFormat to save memory.
         * 
         * @param db Input Database
         * @param heap_tree Create binary tree that keeps pointer of database data.
         */
        void CreateHeapNodeList(std::vector<StructDataFormat> &db, std::vector<StructDataFormat*> &heap_tree);

        /**
         * @brief For debug use. Will print binary tree.
         * 
         * @param heap_tree 
         */
        void PrintHeapNodes(std::vector<StructDataFormat*> &heap_tree);

        /**
         * @brief Create Max Heapify
         * 
         * @param heap_tree input target binary tree
         * @param tree_size 
         * @param default_largest_id 
         */
        void Heapify(std::vector<StructDataFormat*> &heap_tree, int tree_size, int default_largest_id);

        /**
         * @brief Sort funtion using heap sort. 
         * @details HeapSort is used to save time.
         * 
         * @param heap_tree input default binary tree. This binary tree will be edited and sorted.
         */
        void HeapSort(std::vector<StructDataFormat*> &heap_tree);
    }

    namespace file_importer
    {
        /**
         * @brief Countup number of data that included in the data file.
         * 
         * @param file_name name of the data file.
         * @return int -1 : File Open Error, >0: data size
         */
        int CountFileDataSize(const std::string &file_name);

        /**
         * @brief Purse string line to [long, int] data
         * 
         * @param str std::string data of single line.
         * @param timestamp 1st data of the line
         * @param data 2nd data of the line
         * @return true Data format is same as expected.
         * @return false Different format.
         */
        bool ReadData(const std::string &str
                    , long &timestamp
                    , int &data);
        /**
         * @brief Read data file and create database.
         * 
         * @param file_name data file path & name
         * @param db [out] created database
         * @return int -1: File Open Error, 
         *              0: Success, 
         *             >0: Success with warnings. \
         *                 Returns number of format error line in data file.
         */
        int ImportDataFromFile(const std::string &file_name
                        , std::vector<StructDataFormat> &db);
    }
}
