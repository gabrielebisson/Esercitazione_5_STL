#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

namespace PolygonalLibrary {
    //importazione mesh
    bool ImportaMesh(const string& percorso_file,const string& nomefile0D,const string& nomefile1D,const string& nomefile2D,PolygonalMesh& mesh);

    bool ImportaCelle0D(const string &nomefile,PolygonalMesh& mesh);

    bool ImportaCelle1D(const string &nomefile,PolygonalMesh& mesh);

    bool ImportaCelle2D(const string &nomefile,PolygonalMesh& mesh);

    //test sulla mesh
    void TestLati(const PolygonalMesh& mesh,const double& tol);

    void TestAree(const PolygonalMesh& mesh,const double& tol);

    void TestMarker(const PolygonalMesh& mesh);
}
