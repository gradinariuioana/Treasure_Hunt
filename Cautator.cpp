#include "Cautator.h"
#include <iostream>
using namespace std;

Cautator::Cautator(const Joc &J)
{
    //ctor
}

//Verific daca Cautatorul s-a blocat
bool Cautator::IsBlocat()
{
    return blocat;
}

//Getter pentru indicele fiecarui cautator
int Cautator::GetIndice()
{
    return indice;
}

//Getter pentru pozitia actuala a cautatorului
pozitie Cautator::GetPoz()
{
    return Poz;
}

//Afisez statusul fiecarui Cautator (i.e. daca s-a blocat sau daca a gasit vreo comoara)
void Cautator::Afisare_Status(const Joc &J)
{
    if (blocat)
        cout<<"Jucatorul "<<indice<<" s-a blocat!\n";
    else
        if (!IsPlaying(J))
            cout<<"Jucatorul "<<indice<<" a gasit o comoara!\n";
}

bool Cautator::IsPlaying(const Joc &J)
{
    return J.Playing[GetIndice()];
}

void Cautator::StopPlaying(Joc &J)
{
    J.Playing[GetIndice()]=0;
}

Cautator::~Cautator()
{
    //dtor
}

//constructorul cautatorului de tip 1
Cautator_Tip1::Cautator_Tip1(const Joc &J):Cautator(J)
{
    Poz.linie=Poz.coloana=0;  //pozitia initiala a cautatorului
    directie=1;  //folosesc directia pentru a sti cum sa ma deplasez pe harta
    blocat=0;
    indice=1;
}

//functia de deplasare a primului jucator
void Cautator_Tip1::Deplasare(const Joc &J)
{
    if (Poz.linie+directie>=0 and Poz.linie+directie<J.Dimensiune_Harta and J.Harta[Poz.linie+directie][Poz.coloana]%5==0)
        Poz.linie+=directie;  //daca am loc, incerc sa ma misc pe linii, in sus sau jos, in functie de directie (1 sus, -1 jos)
    else
        {
            if (Poz.coloana+1<J.Dimensiune_Harta)  //incerc pozitia de pe coloana uramtoare
                {
                    if (J.Harta[Poz.linie][Poz.coloana+1]%5==0)  //aceeasi linie, coloana urmatoare
                        Poz.coloana+=1, directie*=-1;
                    else
                        if (Poz.linie-directie>=0 && J.Harta[Poz.linie-directie][Poz.coloana+1]%5==0)  //in diagonala
                            Poz.coloana+=1, Poz.linie-=directie, directie*=-1;
                        else
                            blocat=1;  //daca nu am unde sa merg, inseamna ca m-am blocat
                }
        }
}

Cautator_Tip1::~Cautator_Tip1()
{
    //dtor
}

//constructorul cautatorului de tip 2
Cautator_Tip2::Cautator_Tip2(const Joc &J):Cautator(J)
{
    Poz.linie=J.Dimensiune_Harta-1;  //pozitia initiala
    Poz.coloana=0;
    k=0;  //folosesc k pentru deplasare
    blocat=0;
    indice=2;
}

void Cautator_Tip2::Deplasare(const Joc &J)
{
    if (k%2==0 && Poz.linie-1>=0 && J.Harta[Poz.linie-1][Poz.coloana]%5==0)  //incerc sa ma deplasez in sus
        Poz.linie-=1, k++;  //k par inseamna ca merg in sus
    else
        if (k%2==1  && Poz.coloana+1<J.Dimensiune_Harta && J.Harta[Poz.linie][Poz.coloana+1]%5==0)
            Poz.coloana+=1, k++;  //incerc sa ma deplasez la dreapta; k impar inseamna ca merg la dreapta
        else
            {  //incerc sa ma deplasez pe una dintre cele 4 diagomnale
                if (Poz.linie-1>=0 && Poz.coloana+1<J.Dimensiune_Harta && J.Harta[Poz.linie-1][Poz.coloana+1]%5==0)
                    Poz.linie-=1, Poz.coloana+=1;
                else
                    if (Poz.linie-1>=0 && Poz.coloana-1>=0 && J.Harta[Poz.linie-1][Poz.coloana-1]%5==0)
                        Poz.linie-=1, Poz.coloana-=1;
                    else
                        if (Poz.coloana+1<J.Dimensiune_Harta && Poz.linie+1<J.Dimensiune_Harta && J.Harta[Poz.linie+1][Poz.coloana+1]%5==0)
                            Poz.coloana+=1, Poz.linie+=1;
                        else
                            if (Poz.coloana-1>=0 && Poz.linie+1<J.Dimensiune_Harta && J.Harta[Poz.linie+1][Poz.coloana-1]%5==0)
                                Poz.coloana-=1, Poz.linie+=1;
                            else
                                blocat=1;  //daca nu am unde sa ma deplasez, inseamna ca m-am blocat
            }
}

Cautator_Tip2::~Cautator_Tip2()
{
    //dtor
}

//constructorul cautatorului de tip 3
Cautator_Tip3::Cautator_Tip3(const Joc &J):Cautator(J)
{
    Poz.linie=J.Dimensiune_Harta-1;  //pozitia initiala
    Poz.coloana=J.Dimensiune_Harta-1;
    indice=3;
    blocat=0;
}

void Cautator_Tip3::Deplasare(const Joc &J)
{  //cautatorul se deplaseaza in cruce
    if(Poz.coloana-1>=0 && J.Harta[Poz.linie][Poz.coloana-1]%5==0)
        Poz.coloana-=1;  //intai in stanga
    else
        if (Poz.linie+1<J.Dimensiune_Harta && J.Harta[Poz.linie+1][Poz.coloana]%5==0)
            Poz.linie+=1;  //apoi jos
        else
            if(Poz.coloana+1<J.Dimensiune_Harta && J.Harta[Poz.linie][Poz.coloana+1]%5==0)
                Poz.coloana+=1;  //la dreapta
            else
                if (Poz.linie-1>=0 && J.Harta[Poz.linie-1][Poz.coloana]%5==0)
                    Poz.linie-=1;  //sus
                else
                    blocat=1;  //daca nu am unde sa ma deplasez, m-am blocat
}

Cautator_Tip3::~Cautator_Tip3()
{
    //dtor
}

//constructorul cautatorului de tip 4
Cautator_Tip4::Cautator_Tip4(const Joc &J):Cautator(J)
{
    Poz.linie=0;  //pozitie initiala
    Poz.coloana=J.Dimensiune_Harta-1;
    blocat=0;
    indice=4;
}

void Cautator_Tip4::Deplasare(const Joc &J)
{  //Cautatorul 4 se deplaseaza pe diagonale
    if(Poz.coloana-1>=0 && Poz.linie-1>=0 and J.Harta[Poz.linie-1][Poz.coloana-1]%5==0)
        Poz.coloana-=1, Poz.linie-=1;  //intai in stanga sus
    else
        if (Poz.linie+1<J.Dimensiune_Harta and Poz.coloana-1>=0 && J.Harta[Poz.linie+1][Poz.coloana-1]%5==0)
            Poz.linie+=1, Poz.coloana-=1;  //apoi in stanga jos
        else
            if(Poz.coloana+1<J.Dimensiune_Harta and Poz.linie+1<J.Dimensiune_Harta and J.Harta[Poz.linie+1][Poz.coloana+1]%5==0)
                Poz.coloana+=1, Poz.linie+=1;  //dreapta jos
            else
                if (Poz.linie-1>=0 and Poz.coloana+1<J.Dimensiune_Harta and J.Harta[Poz.linie-1][Poz.coloana+1]%5==0)
                    Poz.linie-=1, Poz.coloana+=1;  //dreapta sus
                else
                    blocat=1;  //daca nu am unde sa ma deplasez, m-am blocat
}

Cautator_Tip4::~Cautator_Tip4()
{
    //dtor
}

