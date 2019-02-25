#include <iostream>
#include "TableClass.h"

using namespace std;

int main()
{
    int N;
    cin>>N;
    TableClass table(N);
    table.Build();
    return 0;
}
