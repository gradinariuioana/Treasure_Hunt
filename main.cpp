#include <iostream>
#include "Joc.h"
#include "Cautator.h"

using namespace std;

int main()
{
    int dimensiune;
    cout<<"Introduceti Dimensiunea Hartii: ";
    cin>>dimensiune;
    Joc O(dimensiune);
    O.Joc_Total();
    return 0;
}
