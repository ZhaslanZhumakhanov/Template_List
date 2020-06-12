#include "Tests/Test_ArrayList.hpp"
#include "Tests/Test_LinkedList.hpp"

int main(){
    Test_ArrayList();
    std::cout << "------------------------" << std::endl;
    Test_HardArrayList();
    std::cout << "------------------------" << std::endl;
    Test_LinkedList();
    return 0;
}