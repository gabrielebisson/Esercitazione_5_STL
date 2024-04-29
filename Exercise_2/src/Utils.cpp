#include "Utils.hpp"

using namespace std;

namespace PolygonalLibrary {

bool ImportaMesh(const string& percorso_file,const string& nomefile0D,const string& nomefile1D,const string& nomefile2D,PolygonalMesh& mesh)
{
    bool esito=true;
    if(!ImportaCelle0D(percorso_file+nomefile0D,mesh))
    {
        cerr << "C'e' un errore nell'importazione del file '"<<nomefile0D<<"'"<<endl;
        esito=false;
    }
    if(!ImportaCelle1D(percorso_file+nomefile1D,mesh))
    {
        cerr << "C'e' un errore nell'importazione del file '"<<nomefile1D<<"'"<<endl;
        esito=false;
    }
    if(!ImportaCelle2D(percorso_file+nomefile2D,mesh))
    {
        cerr << "C'e' un errore nell'importazione del file '"<<nomefile2D<<"'"<<endl;
        esito=false;
    }
    return esito;
}

bool ImportaCelle0D(const string& nomefile,PolygonalMesh& mesh) //il nome del file non lo devo modificare, la mesh la prendo per riferimento perchè devo modificarla
{
    //apro il file
    ifstream in_str(nomefile);
    if (in_str.fail())
    {
        cerr << "C'e' un errore nella lettura di '" << nomefile << "'"<< endl;
        return false;
    }

    //memorizzo le righe del file in una lista
    string riga;
    list<string> lista_righe;

    //leggo la prima riga d'intestazione
    in_str >> riga;

    while (!in_str.eof())
    {
        in_str >> riga;
        lista_righe.push_back(riga);
        //cout << riga << endl;
    }
    in_str.close(); //chiudo il file

    //tolgo l'ultima riga
    lista_righe.pop_back();

    //memorizzo il numero di punti
    mesh.NumberCell0D = lista_righe.size();
    //cout << mesh.NumberCell0D<<endl;

    if (mesh.NumberCell0D == 0)
    {
        cerr << "Non ci sono celle 0D" << endl;
        return false;
    }

    //riservo la memoria necessaria per memorizzare i dati
    mesh.Cell0DId.reserve(mesh.NumberCell0D);
    mesh.Cell0DCoordinates.reserve(mesh.NumberCell0D);

    //memorizzo i dati
    //cout << "ID,MAKER,X,Y"<<endl;
    for (string& linea:lista_righe)
    {
        unsigned int id;
        unsigned int marker;
        char sep; //sarebbe il ';'
        array<double,2> coordinate;
        istringstream convertitore(linea);
        convertitore >> id >> sep >> marker >> sep >> coordinate[0] >> sep >> coordinate[1];
        //cout << id <<";"<<marker<<";"<<coordinate[0]<<";"<<coordinate[1]<<endl;
        mesh.Cell0DId.push_back(id);
        mesh.Cell0DCoordinates.push_back(coordinate);
        if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end()) //se non trova il marker come chiave (ossia l'iteratore è arrivato alla fine)...
        {
            mesh.Cell0DMarkers.insert({marker, {id}}); //inserisce il marker come chiave e l'id come argomento
        }
        else
        {
            mesh.Cell0DMarkers[marker].push_back(id); //mette in fondo alla lista dei punti con quel marker il nuovo id
        }
    }
    return true;
}

bool ImportaCelle1D(const string& nomefile,PolygonalMesh& mesh) //il nome del file non lo devo modificare, la mesh la prendo per riferimento perchè devo modificarla
{
    //apro il file
    ifstream in_str(nomefile);
    if (in_str.fail())
    {
        cerr << "C'e' un errore nella lettura di '" << nomefile << "'"<< endl;
        return false;
    }

    //memorizzo le righe del file in una lista
    string riga;
    list<string> lista_righe;

    //leggo la prima riga d'intestazione
    in_str >> riga;

    while (!in_str.eof())
    {
        in_str >> riga;
        lista_righe.push_back(riga);
        //cout << riga << endl;
    }
    in_str.close(); //chiudo il file

    //tolgo l'ultima riga
    lista_righe.pop_back();

    //memorizzo il numero di punti
    mesh.NumberCell1D = lista_righe.size();
    //cout << mesh.NumberCell1D<<endl;

    if (mesh.NumberCell1D == 0)
    {
        cerr << "Non ci sono celle 1D" << endl;
        return false;
    }

    //riservo la memoria necessaria per memorizzare i dati
    mesh.Cell1DId.reserve(mesh.NumberCell1D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell1D);

    //memorizzo i dati
    //cout << "ID,MAKER,INIZIO,FINE"<<endl;
    for (string& linea:lista_righe)
    {
        unsigned int id;
        unsigned int marker;
        char sep; //sarebbe il ';'
        array<unsigned int,2> vettore; //(inizio, fine)'
        istringstream convertitore(linea);
        convertitore >> id >> sep >> marker >> sep >> vettore[0] >> sep >> vettore[1];
        //cout << id <<";"<<marker<<";"<<vettore[0]<<";"<<vettore[1]<<endl;
        mesh.Cell1DId.push_back(id);
        mesh.Cell1DVertices.push_back(vettore);
        if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end()) //se non trova il marker come chiave (ossia l'iteratore è arrivato alla fine)...
        {
            mesh.Cell1DMarkers.insert({marker, {id}}); //inserisce il marker come chiave e l'id come argomento
        }
        else
        {
            mesh.Cell1DMarkers[marker].push_back(id); //mette in fondo alla lista dei segmenti con quel marker il nuovo id
        }
    }
    return true;
}

bool ImportaCelle2D(const string& nomefile,PolygonalMesh& mesh) //il nome del file non lo devo modificare, la mesh la prendo per riferimento perchè devo modificarla
{
    //apro il file
    ifstream in_str(nomefile);
    if (in_str.fail())
    {
        cerr << "C'e' un errore nella lettura di '" << nomefile << "'"<< endl;
        return false;
    }

    //memorizzo le righe del file in una lista
    string riga;
    list<string> lista_righe;

    //leggo la prima riga d'intestazione
    in_str >> riga;

    while (!in_str.eof())
    {
        in_str >> riga;
        lista_righe.push_back(riga);
        //cout << riga << endl;
    }
    in_str.close(); //chiudo il file

    //tolgo l'ultima riga
    lista_righe.pop_back();

    //memorizzo il numero di punti
    mesh.NumberCell2D = lista_righe.size();
    //cout << mesh.NumberCell2D<<endl;

    if (mesh.NumberCell2D == 0)
    {
        cerr << "Non ci sono celle 2D" << endl;
        return false;
    }

    //riservo la memoria necessaria per memorizzare i dati
    mesh.Cell2DId.reserve(mesh.NumberCell2D);
    mesh.Cell1DVertices.reserve(mesh.NumberCell2D);
    mesh.Cell2DEdges.reserve(mesh.NumberCell2D);
    //memorizzo i dati
    //cout << "ID,NUMERO_LATI"<<endl;
    for (string& linea:lista_righe)
    {
        unsigned int id;
        char sep; //sarebbe il ';'
        unsigned int lung_vett;
        istringstream convertitore(linea);
        convertitore >> id >> sep >> lung_vett >> sep >>lung_vett;
        //cout << id <<";"<<lung_vett<<endl;
        vector<unsigned int> v(lung_vett); //inizializzo il vettore dei vertici/lati (n_vertici=n_lati)
        //cout << "---vettore dei vertici---"<< endl;
        for(unsigned int i=0;i<lung_vett;i++) //memorizzo il vettore dei vertici
        {
            convertitore >> sep >> v[i];
            //cout << v[i] << endl;
        }
        mesh.Cell2DId.push_back(id); //salvo l'id
        mesh.Cell2DVertices.push_back(v); //salvo il vettore dei vertici

        convertitore >> sep >> lung_vett; //salto il numero di lati, che è uguale al numero di vertici
        //cout << "---vettore dei vertici---"<< endl;
        for(unsigned int i=0;i<lung_vett;i++)
        {
            convertitore >> sep >> v[i];
            //cout << v[i] << endl;
        }
        mesh.Cell2DEdges.push_back(v); //salvo il vettore dei lati
    }
    return true;
}

void TestLati(const PolygonalMesh& mesh,const double& tol) //verifica che non ci siano lati degeneri, ossia di lunghezza nulla
{
    cout << "------------Test Lati------------"<<endl;
    double tol_eff = max(tol,__DBL_EPSILON__); //la tolleranza impostata dall'utente deve essere maggiore dell'epsilon di macchina
    //cout << tol_eff<<endl;
    bool esito=true;
    unsigned int j=0;
    for (auto& segmento:mesh.Cell1DVertices)
    {
        j++;
        double dist=sqrt(pow(mesh.Cell0DCoordinates[segmento[0]][0]-mesh.Cell0DCoordinates[segmento[1]][0],2)+pow(mesh.Cell0DCoordinates[segmento[0]][1]-mesh.Cell0DCoordinates[segmento[1]][1],2));
        //cout << "la lunghezza del segmento e' "<<dist<<endl;
        if(!(dist/max(dist,1.) >tol_eff))
        {
            cout << "Errore: il segmento "<<j<<" e' degenere per la tolleranza impostata"<<endl;
            esito=false;
        }
    }
    cout <<"Esito:"<<endl;
    if(esito)
    {
        cout << "Il test dei lati e' andato a buon fine: non ci sono lati degeneri per la tolleranza impostata"<<endl;
    }
    else
    {
        cout << "Il test dei lati non e' andato a buon fine: ci sono lati degeneri per la tolleranza impostata"<<endl;
    }
    cout << "---------------------------------"<<endl<<endl;
}

void TestAree(const PolygonalMesh& mesh,const double& tol) //verifica che non ci siano poligoni di area nulla
{
    cout << "------------Test Aree------------"<<endl;
    double tol_eff=max(__DBL_EPSILON__,sqrt(3)/4.*tol*tol); //sqrt(3)/4.*tol*tol è l'area del triangolo equilatero di lato tol
    bool esito=true;
    unsigned int j=0;
    //double areaTOT=0;
    for (auto& vett_vertici:mesh.Cell2DVertices)
    {
        j++;
        double area=0;
        array<double,2> punto_0=mesh.Cell0DCoordinates[vett_vertici[vett_vertici.size()-1]];
        for(unsigned int i=0; i<vett_vertici.size();i++) //area con la formula di Gauss
        {
            array<double,2> punto_1=mesh.Cell0DCoordinates[vett_vertici[i]];
            area+=(punto_1[0]-punto_0[0])*(punto_0[1]+punto_1[1]);
            punto_0=punto_1;
        }
        area=abs(area)*1./2.;
        //areaTOT+=area;
        //cout<<"L'area e' "<<area<<endl;
        if(!(area/max(area,1.) >tol_eff))
        {
            cout << "Errore: l'area del del poligono "<< j <<" e' degenere per la tolleranza impostata"<<endl;
            esito=false;
        }
    }
    cout <<"Esito:"<<endl;
    if(esito)
    {
        cout << "Il test delle aree e' andato a buon fine: non ci sono poligoni degeneri per la tolleranza impostata"<<endl;
    }
    else
    {
        cout << "Il test delle aree non e' andato a buon fine: ci sono poligoni degeneri per la tolleranza impostata"<<endl;
    }
    //cout <<"L'area totale e' "<< areaTOT<<endl;
    cout << "---------------------------------"<<endl<<endl;
}

void TestMarker(const PolygonalMesh& mesh) //permette di controllare che i marker dei segmenti e dei punti siano stati salvati correttamente
{
    cout << "----------Test Marker1D----------"<<endl;
    for(auto& tupla:mesh.Cell1DMarkers)
    {
        unsigned int mar1D =tupla.first;
        cout <<"Dato il marker "<< mar1D <<", i segmenti associati ad esso sono:"<<endl;
        for(const unsigned int& seg:tupla.second)
        {
            cout << seg <<" ";
        }
        cout << endl<<endl;
    }
    cout << "---------------------------------"<<endl<<endl;

    cout << "---------Test Marker0D----------"<<endl<<endl;
    for(auto& tupla:mesh.Cell0DMarkers)
    {
        unsigned int mar0D =tupla.first;
        cout <<"Dato il marker "<< mar0D <<", i punti associati ad esso sono:"<<endl;
        for(const unsigned int& punto:tupla.second)
        {
            cout << punto <<" ";
        }
        cout << endl<<endl;
    }
    cout << "---------------------------------"<<endl<<endl;
}
}
