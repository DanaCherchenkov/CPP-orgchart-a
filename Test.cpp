#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "doctest.h"
#include "sources/OrgChart.hpp"

using namespace std;
using namespace ariel;

TEST_CASE("Good test for add_root & add_sub"){
    OrgChart organization;
    CHECK_NOTHROW(organization.add_root("Maor"));
    CHECK_NOTHROW(organization.add_root("Regina"));
    CHECK_NOTHROW(organization.add_root("Dana"));
    CHECK_NOTHROW(organization.add_root("Michal"));
    CHECK_NOTHROW(organization.add_root("Mama"));
    CHECK_NOTHROW(organization.add_root("Papa"));
    CHECK_NOTHROW(organization.add_sub("Papa", "Maor1"));
    CHECK_NOTHROW(organization.add_sub("Maor1", "Maor2"));
    CHECK_NOTHROW(organization.add_sub("Maor2", "Maor3"));
    CHECK_NOTHROW(organization.add_sub("Michal", "Maor4"));
    CHECK_NOTHROW(organization.add_sub("Mama", "Maor5"));
}

TEST_CASE("Good test for correct hierarchy"){
    OrgChart organization;
    organization.add_root("Mor")
        .add_sub("Mor", "Michal")
        .add_sub("Michal", "Orel")
        .add_sub("Orel", "Linoy")
        .add_sub("Linoy", "Shani")
        .add_sub("Shani", "Amit")
        .add_sub("Amit", "Gil");     

    vector<string> level_order = {"dad", "son", "son1", "son2", "son3", "son4", "son5"};

    size_t i = 0;
    for(auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        level_order[i] = *(it);
        i++;
    }
    CHECK(level_order[0] == "Mor");
    CHECK(level_order[1] == "Michal");
    CHECK(level_order[2] == "Orel");
    CHECK(level_order[3] == "Linoy");
    CHECK(level_order[4] == "Shani");
    CHECK(level_order[5] == "Amit");
    CHECK(level_order[6] == "Gil");
    

    organization.add_root("Dana")
        .add_sub("Dana", "Regina")
        .add_sub("Dana", "Roni")
        .add_sub("Dana", "Gal")
        .add_sub("Dana", "Linoy")

        .add_sub("Linoy", "Noa");

    vector<string> level_order1 = {"dad", "son", "son", "son", "son", "son1"};
    size_t j = 0;
    for(auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        level_order[i] = *(it);
        j++;
    }
    CHECK(level_order1[0] == "Dana");
    CHECK(level_order1[1] == "Regina");
    CHECK(level_order1[2] == "Roni");
    CHECK(level_order1[3] == "Gal");
    CHECK(level_order1[4] == "Linoy");

    vector<string> reverse_level_order = {"son1", "son", "son", "son", "son", "dad"};
    size_t s = 0;
    for(auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        level_order[i] = *(it);
        s++;
    }
    CHECK(reverse_level_order[4] == "Dana");
    CHECK(reverse_level_order[3] == "Regina");
    CHECK(reverse_level_order[2] == "Roni");
    CHECK(reverse_level_order[1] == "Gal");
    CHECK(reverse_level_order[0] == "Linoy");
}

TEST_CASE("Good test for preorder iterator"){
    OrgChart organization;
    organization.add_root("A");
    organization.add_sub("A", "AB");
    organization.add_sub("AB", "ABC");
    organization.add_sub("AB", "ABD");
    organization.add_sub("ABC", "ABCD");
    organization.add_sub("ABC", "ABCDE");
    organization.add_sub("A", "AC");
    organization.add_sub("AC", "ACE");
    organization.add_sub("AC", "ACF");
    organization.add_sub("AC", "ACG");
    vector<string> ans = {"A", "AB", "AC", "ABC", "ABD", "ACE", "ACF", "ACG", "ABCD", "ABCDE"};
    size_t count = 0;
    for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it){
        CHECK(ans[count].compare((*it)));
        count++;
    }
}

TEST_CASE("Bad test for correct hierarchy"){
    OrgChart organization;
    organization.add_root("Mor")
        .add_sub("Mor", "Michal")
        .add_sub("Michal", "Orel")
        .add_sub("Orel", "Linoy")
        .add_sub("Linoy", "Shani")
        .add_sub("Shani", "Amit")
        .add_sub("Amit", "Gil");     

    vector<string> level_order = {"dad", "son", "son1", "son2", "son3", "son4", "son5"};

    size_t i = 0;
    for(auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        level_order[i] = *(it);
        i++;
    }
    CHECK_NE(level_order[6], "Mor");
    CHECK_NE(level_order[5], "Michal");
    CHECK_NE(level_order[4], "Orel");
    CHECK_NE(level_order[0], "Linoy");
    CHECK_NE(level_order[1], "Shani");
    CHECK_NE(level_order[2], "Amit");
    CHECK_NE(level_order[3], "Gil");

    organization.add_root("Dana")
        .add_sub("Dana", "Regina")
        .add_sub("Dana", "Roni")
        .add_sub("Dana", "Gal")
        .add_sub("Dana", "Linoy")
        .add_sub("Linoy", "Noa");

    vector<string> reverse_level_order = {"son1", "son", "son", "son", "son", "dad"};
    size_t s = 0;
    for(auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it){
        level_order[i] = *(it);
        s++;
    }
    CHECK_NE(reverse_level_order[0], "Dana");
    CHECK_NE(reverse_level_order[1], "Regina");
    CHECK_NE(reverse_level_order[3], "Roni");
    CHECK_NE(reverse_level_order[2], "Gal");
    CHECK_NE(reverse_level_order[4], "Linoy");
}

TEST_CASE("Bad test for get a tree without a root"){
    OrgChart organization;
    CHECK_THROWS(organization.add_sub("Dana", "Regina"));
    CHECK_THROWS(organization.add_sub("Dana", "Michal"));
    CHECK_THROWS(organization.add_sub("Michal", "Orel"));
}

TEST_CASE("Bad test for checking ranks in an organization"){
    OrgChart organization;
    organization.add_root("Dana");
    CHECK_NOTHROW(organization.add_sub("Dana", "Gal"));
    CHECK_NOTHROW(organization.add_sub("Dana", "Maor"));
    CHECK_NOTHROW(organization.add_sub("Dana", "Roni"));
    CHECK_THROWS(organization.add_sub("Roni", "Dana")); //Can not determine that the father will be the grandson of the child.
    CHECK_THROWS(organization.add_sub("Gal", "Dana")); //Can not determine that the father will be the grandson of the child.
    CHECK_THROWS(organization.add_sub("Maor", "Dana")); //Can not determine that the father will be the grandson of the child.
    CHECK_THROWS(organization.add_sub("Dana", "Dana")); //Can not be tha same name of the root and sub_root.
}

TEST_CASE("Bad test for determine a root that does not exist"){
    OrgChart organization;
    organization.add_root("Dana");
    CHECK_NOTHROW(organization.add_sub("Dana", "Gal"));
    CHECK_NOTHROW(organization.add_sub("Dana", "Maor"));
    CHECK_THROWS(organization.add_sub("Michael", "Roni"));
}



