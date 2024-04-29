#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"

using namespace std;
using namespace PolygonalLibrary;

int main()
{
    string percorso_file="PolygonalMesh/";
    string file_punti="Cell0Ds.csv";
    string file_segmenti="Cell1Ds.csv";
    string file_poligoni="Cell2Ds.csv";
    PolygonalMesh mesh;
    double tol=1e-10;
    bool v=ImportaMesh(percorso_file,file_punti,file_segmenti,file_poligoni,mesh);
    if(v)
    {
        cout << "Importazione mesh andata a buon fine"<<endl<<endl;
        TestLati(mesh,tol);
        TestAree(mesh,tol);
        TestMarker(mesh);
    }
    else
    {
        cerr << "Importazione mesh non andata a buon fine, non si può procedere con i test"<<endl;
        return 1;
    }
    return 0;
}
