#include "Dijsktra.hpp"

 #define max INT_MAX

// N nombre de sommets du graphe 
//c  : matrice des poids du graphe (cij et le poid de l'arrete ij)
// S={1} à l'intialisation
// T=liste des autres sommets
//les sommets sont considérés nommées de 0 à n, 0 étant systématiquement le sommet de départ
// Exemple : cout de l'arrete 01 = c[0][1]

void Dijsktra(int N, double **c, double *l, double *p){
    vector<int> S;
    vector<int> T;
    S.push_back(0); 
    // Initialisation de l et p //
    for(int i=0; i<N; i++){
        l[i]=c[0][i];
        if(i>0 && c[0][i]< max) p[i]=0;
        else  p[i]=-1;

        if(i>0) T.push_back(i); // On rempli T
    }
    // Fin initialisation de l et p //

    while(!T.empty()){ //Tant que liste T n'est pas vide
        // Recherche du point pt de T tel que l[pt] est minimum //
        int min = max; //intialise la mémoire de la recherche
        int pt = 0;
        vector<int>::iterator its=T.begin(); // On parcourt T avec un iterator
        for(; its!= T.end(); its++){ 
            if (l[*its]< min){ // si l[point visité] est inférieur à l[point mémoire]
                min = l[*its]; //on garde ce point visité en mémoire
                pt = *its;
            }
        } 

        S.push_back(pt); //On ajoute le point pt à S
        /// obliger de reparcourir T pour supprimer le point pt choisi : pas optimal ///
        its=T.begin();
        for(; its!= T.end(); its++){ 
            if(*its==pt){
                T.erase(its); // On retir le point pt de T /////////////////////////////////
                break;
            }
        }

        its=T.begin(); // On parcourt T avec un iterator
        for (; its!= T.end();its++){ 
            if( l[*its]>(l[pt]+c[pt][*its])){ //si le cout jusqu'a pt plus le cout de l'arrete pt-its est inférieur au cout minimal
                l[*its] = l[pt]+c[pt][*its]; // nouveau cout minimal pour chemin de 0 à its
                p[*its]= pt; // nouveau prédecesseur pour its : pt
            }
        }
    }
}


int main(){
    double **c= exempleEnonce();
    int N=5;
    double l[N];
    double p[N];
    Dijsktra(N, c, l, p);

    cout<<"l={";
    for(int i=0; i<N; i++){
        cout<<l[i]<<" ";
    }
    cout<<"}"<<endl;
    cout<<"p={";
    for(int i=0; i<N; i++){
        cout<<p[i]<<" ";
    }
    cout<<"}"<<endl;

    return 0;
}

//Exemple de l'énoncé avec 5 points
double ** exempleEnonce(){
    double **c;
    c = new double *[5];
    for(int i = 0; i <5; i++)
    c[i] = new double[5];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            c[i][j] = max;
        }
    }
    c[0][0]=0;
    c[0][1]=15;
    c[0][4]=4;
    c[1][1]=0;
    c[2][1]=3;
    c[2][2]=0;
    c[2][3]=2;
    c[3][0]=10;
    c[3][1]=3;
    c[3][3]=0;
    c[4][2]=7;
    c[4][3]=5;
    c[4][4]=0;
    return reinterpret_cast<double **>(c);
}