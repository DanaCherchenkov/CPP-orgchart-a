#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

namespace ariel{
    class OrgChart{
        private:
            vector<string> tree;
        public:
            OrgChart();
            OrgChart add_root(string root);
            OrgChart add_sub(string son1, string son2);
            vector<string> ::iterator end();
            vector<string> ::iterator begin();
            vector<string> ::iterator begin_level_order();
            vector<string> ::iterator end_level_order();
            vector<string> ::iterator begin_reverse_order();
            vector<string> ::iterator reverse_order();
            vector<string> ::iterator begin_preorder();
            vector<string> ::iterator end_preorder();
            friend ostream& operator<<(ostream& out, const OrgChart& chart);
    };
}

