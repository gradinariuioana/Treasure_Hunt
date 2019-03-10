#include "Joc.h"
#include <cstdlib>
#include <time.h>
#include <iostream>
#include "Cautator.h"
using namespace std;

Joc::Joc(int d)
{
    //alocarea dinamica a hartii
    Dimensiune_Harta=d;
    Harta=new int*[Dimensiune_Harta];
    for (int i=0; i<Dimensiune_Harta; i++)
        Harta[i]=new int[Dimensiune_Harta];
    for (int i=0; i<Dimensiune_Harta; i++)
        for (int j=0; j<Dimensiune_Harta; j++)
            Harta[i][j]=0;  //fiecare pozitie a hartii va fi initializata cu 0
    //setez pozitia fiecarui cautator in unul dintre cele 4 colturi ale hartii
    Harta[0][0]=1;
    Harta[Dimensiune_Harta-1][Dimensiune_Harta-1]=3;
    Harta[Dimensiune_Harta-1][0]=2;
    Harta[0][Dimensiune_Harta-1]=4;
    Numar_Comori_Gasite=0;
    int i, j, k=0;
    //asez random cele 3 comori pe harta
    while (k<3)
    {
        srand(time(NULL));
        i=rand()%Dimensiune_Harta;
        j=rand()%Dimensiune_Harta;
        if ((i or j) && !(i==0 and j==Dimensiune_Harta-1) && !(i==Dimensiune_Harta-1 and j==Dimensiune_Harta-1) && !(i==Dimensiune_Harta-1 and j==0) && Harta[i][j]==0)
            Harta[i][j]=5, k+=1;
    }
    //marchez toti cei 4 cautatori ca fiind playing
    Playing=new int[5];
    for (int i=1; i<=4; i++)
        Playing[i]=1;
    indice_castigator=0;
    //declararea celor 4 cautatori
    C[0]=new Cautator_Tip1(*this);
    C[1]=new Cautator_Tip2(*this);
    C[2]=new Cautator_Tip3(*this);
    C[3]=new Cautator_Tip4(*this);
}

//Desfasurarea unei runde de joc
int Joc::Runda (int d)
{
    if (d==0)  //d marcheaza daca jocul se mai continua sau nu
       return 0;
    else
    {
        for (int i=0; i<4; i++)
            {
                if (C[i]->IsPlaying(*this))  //verific daca cautatorii mai sunt in joc
                {
                    pozitie *Q=new pozitie;  //retin pozitia initiala a jucatorului
                    *Q=C[i]->GetPoz();
                    C[i]->Deplasare(*this);  //deplasez jucatorul, obtinand astfel pozitia pe care se va muta, daca poate
                    pozitie *P=new pozitie;
                    *P=C[i]->GetPoz();  //retin pozitia de dupa deplasare a jucatorului
                    if (Harta[P->linie][P->coloana]==5)  //verific daca jucatorul a gasit o comoara
                        Numar_Comori_Gasite+=1, C[i]->StopPlaying(*this), Harta[P->linie][P->coloana]=5+(C[i]->GetIndice());
                        //cresc numarul de comori gasite, scot cautatorul in cauza din joc si marchez pe harta acest fapt pe harta cu valoarea 5+indicele jucatorului
                    else
                        Harta[P->linie][P->coloana]=(C[i]->GetIndice());  //altfel, doar marchez deplasarea jucatorului
                    if (!(P->linie==Q->linie && P->coloana==Q->coloana))  //daca pozitia de dinainte de deplare nu este aceeasi cu cea de dupa deplasare (i.e. jucatorul nu s-a blocat), afisez deplasarea
                        cout<<"Jucatorul "<<i+1<<" se deplaseaza de la pozitia ("<<Q->linie<<" , "<<Q->coloana<<") la pozitia ("<<P->linie<<" , "<<P->coloana<<")\n";
                    if ((Harta[P->linie][P->coloana])==(5+(C[i]->GetIndice())))
                        cout<<"Jucatorul "<<i+1<<" va iesi de pe harta\n";  //daca a gasit comoara, anunt ca va iesi de pe harta
                    delete P;
                    delete Q;
                }
            }
        if (Numar_Comori_Gasite==1)
            for (int i=1; i<=4; i++)
                if (!Playing[i])
                    return i;  //metoda returneaza indicele primului cautator care a gasit o comoara
        return 0;
    }
}

//Afisarea unei runde
void Joc::Afisare_Runda()
{
    for (int i=0; i<=Dimensiune_Harta; i++)
        cout<<"--";
    cout<<endl;
            for (int i=0; i<Dimensiune_Harta; i++)
            {
                cout<<"|";
                for (int j=0; j<Dimensiune_Harta; j++)
                    if (Harta[i][j])
                        cout<<Harta[i][j]<<" ";
                    else
                        cout<<"  ";
                cout<<"|"<<endl;
            }
    for (int i=0; i<=Dimensiune_Harta; i++)
        cout<<"--";
    cout<<endl;
}

//verific daca jocul s-a terminat
bool Joc::IsOver()
{
    if (Numar_Comori_Gasite==3)  //daca s-au gasit toate cele 3 comori, s-a terminat
        return 1;
    else
    {
        int i, ok=0;
        for (i=0; i<4; i++)
            if (C[i]->IsBlocat()==1)
                ok++;
        if (ok+Numar_Comori_Gasite==4)  //daca numarul de jucatori blocati si cel de comori gasite dau insumate 4, jocul s-a terminat
            return 1;
    }
    return 0;
}

//Gestionarea intreguului joc
void Joc::Joc_Total()
{
    int k, d;
    //afisarea hartii initiale
    cout<<"Harta Initiala:\n";
    Afisare_Runda();
    //afisarea meniului principal, impreuna cu citirea dorintei de continuare/oprire
    cout<<"To continue, press 1\nTo stop, press 0\n";
    cin>>d;
    while(d)
    {
        k=Runda(d);  //desfasurarea unei runde, k va lua valoarea indicelui jucatorului castigator (daca exista)
        Afisare_Runda();  //afisarea acesteia
        if (k && (Numar_Comori_Gasite==1))
            indice_castigator=k;  //indicele castigator va retine indicele primului jucator care a gasit o comoara
        if (indice_castigator)
            cout<<"Cautatorul "<<indice_castigator<<" a castigat!!!\n";
        for (int i=0; i<4; i++)
            C[i]->Afisare_Status(*this);  //afisarea statusului fiecarui jucator
        if (IsOver())  //afisarea terminarii jocului
            cout<<"Jocul s-a terminat deoarece au fost gasite toate comorile sau toti jucatorii ramasi pe harta s-au blocat\n", d=0;
        if (d)
        {
            cout<<"To continue, press 1\nTo stop, press 0\n";
            cin>>d;
        }
    }
}

Joc::~Joc()
{
    for (int i=0; i<Dimensiune_Harta; i++)  //destructor harta
        delete[] Harta[i];  //dezaloc coloanele
    delete[] Harta;  //dezaloc liniile
    delete[] Playing;  //dezaloc vectorul de playing
}
