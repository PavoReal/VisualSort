#pragma once

#include <string>
#include "Elements.hpp"

class ISort
{
public:
    ISort() { _name = ""; }
    ISort(std::string name_) : _name(name_) {}

    virtual void
    Run(Elements&, size_t, size_t) = 0; 

    inline void
    SetName(std::string s) { _name = s; }
        
    inline std::string 
    GetName() { return _name; }

protected:
    std::string _name;
};

