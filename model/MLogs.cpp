#include "MLogs.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <iomanip>

void createLog(const std::string &logs){
    // Get date
    std::time_t timestamp = std::time(nullptr);
    struct tm* timeInfo = std::localtime(&timestamp);
    std::stringstream formattedDate;
    formattedDate << std::put_time(timeInfo, "%Y-%m-%d_%H-%M-%S");

    // Create file
    std::string const fileName("oxo_" + formattedDate.str() + ".log");
    std::ofstream stream(fileName.c_str());

    if(stream){
        // Write to the file
        stream << logs;
    }
    else{
        // Error occurred
        std::cout << "An error occurred while saving the logs" << std::endl;
    }
}

