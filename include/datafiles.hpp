#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <string>
#include <vector>

#include "utils.hpp"
#include "defines.hpp"
#include "types.hpp"

namespace Engine
{
    struct DataFile
    {
        DataFile( std::string path, std::string header )
        {
            this->inputStream{ path };

            // Verify header
            for ( uint i = 0; i < header.length(); i++ )
            {
                char c; this->inputStream >> c;
                if ( c != header[i] ) throw std::invalid_argument{ "Invalid " + header + " file provided" };
            }
        }

        std::ifstream& getInputStream()
        {
            return this->inputStream;
        }

        private:
            std::ifstream inputStream;
    };
}