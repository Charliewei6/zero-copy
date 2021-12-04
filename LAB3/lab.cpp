
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include<omp.h>

using namespace std;

int main()
{
    omp_set_dynamic(0);
    omp_set_num_threads(omp_get_num_procs()*2);
   //clock_t start = clock();
       ifstream inFile;

    string city;
    string line;
    cout << "Enter file size";
    int size;
    cin >> size;
    string** array = new string * [size];
#pragma omp parallel for
    for (int x = 0; x < size; x++)
    {
        array[x] = new string[12];
    }
    inFile.open("file.csv");

    if (inFile.is_open())
    {
        cout << "File has been opened" << endl;
    }
    else
    {
        cout << "NO FILE HAS BEEN OPENED" << endl;
    }
    int x = 0, y = 0;

    if (inFile.is_open())
    {
        getline(inFile, line);
        for ( x = 0; x < size; x++)
        {
            getline(inFile, line);
            std::stringstream ss(line);

            for ( y = 0; y < 12; y++)
            {
                getline(ss, array[x][y], ',');
            }

        }



    }
    
    inFile.close();
    cout << "Enter 1 for id, 2 for name, 3 for mesonet, 4 for lat, 5 for lon, 6 for elevation, 7 for agl, 8 for cit, 9 for state, 10 for country, 11 for active";
    int selection;
    cin >> selection;
    cin.ignore();
    cout << "Enter data to search::" ;
    string search;
clock_t start = clock();


    getline(cin, search);
#pragma omp parallel for
    for (int x = 0; x < size; x++)
    {
        if (array[x][selection - 1] == search)
        {
            cout << "Found at index =" << x << endl;
        }
    }
    double time = (double)(clock() - start);

    cout << "Manipulation on data" << endl;
    start = clock();
    int count = 0;
    x = 0;
#pragma omp parallel for firstprivate(x) reduction(+:count) 
    for (x = 0; x < size; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            int len = array[x][y].length();
            for (int z = 0; z < len; z++)
            {
                if (array[x][y][z] == 'a')
                    count++;
            }
        }
    }
    cout << "A times = " << count << endl;
    time += (double)(clock() - start);
    cout << endl << "Time in milli second= " << time << endl;

    system("pause");
    return 0;





}
