#include <iostream>
#include <vector>
#include "DNest4.h"
#include "MyModel.h"

using namespace GPDemo;

int main(int argc, char** argv)
{
    MyModel::set_data();
    DNest4::start<MyModel>(argc, argv);
    return 0;
}

