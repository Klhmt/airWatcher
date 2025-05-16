#include <iostream>
#include <string>

using namespace std;    


class PrivateOwner
{   
    private:
        string userName;
        int points;


    public:

    PrivateOwner(string name, int pts);

    ~PrivateOwner();

};