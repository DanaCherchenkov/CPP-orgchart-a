#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "OrgChart.hpp"

using namespace std;

namespace ariel{
    OrgChart::OrgChart(){}

    OrgChart OrgChart::add_root(string root){
        return *this;
    }

    OrgChart OrgChart::add_sub(string son1, string son2){
        return *this;
    }

    vector<string>::iterator OrgChart::end(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::begin(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::begin_level_order(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::end_level_order(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::begin_reverse_order(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::reverse_order(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::begin_preorder(){
        vector<string>::iterator it;
        return it;
    }

    vector<string>::iterator OrgChart::end_preorder(){
        vector<string>::iterator it;
        return it;
    }

    ostream& operator<<(ostream& out, const OrgChart& chart){return out;}
}