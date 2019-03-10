#ifndef CAUTATOR_H
#define CAUTATOR_H
#include "Joc.h"

struct pozitie{
int linie, coloana;
};

class Cautator
{
    public:
        Cautator(const Joc &J);
        virtual ~Cautator();
        pozitie GetPoz ();  //getter pentru pozitia actuala a cautatorului
        virtual void Deplasare (const Joc &J)=0;  //metoda pentru deplasare - virtuala pura
        bool IsPlaying(const Joc &J);  //metoda pentru a verifica daca cautatorul inca mai este in joc
        bool IsBlocat();  //metoda pentru a verifica daca cautatorul s-a blocat
        int GetIndice();  //getter pentru indice
        void Afisare_Status (const Joc &J);
        void StopPlaying (Joc &J);  //metoda care marcheaza daca jucatorul meu nu mai joaca

    protected:
        pozitie Poz;  //sunt protected deoarece am nevoie de ele si in clasele mostenite
        bool blocat;
        int indice;

    private:
};

class Cautator_Tip1 : public Cautator
{
    public:
        Cautator_Tip1(const Joc &J);
        virtual ~Cautator_Tip1();
        void Deplasare (const Joc &J);  //deplasarea, redefinita pentru cautatorul de tip 1

    protected:

    private:
        int directie;  //folosesc la directia de deplasare
};

class Cautator_Tip2 : public Cautator
{
    public:
        Cautator_Tip2(const Joc &J);
        virtual ~Cautator_Tip2();
        void Deplasare (const Joc &J);  //deplasarea, redefinita pentru cautatorul de tip 2

    protected:

    private:
        int k;  //folosesc la directia de deplasare
};

class Cautator_Tip3 : public Cautator
{
    public:
        Cautator_Tip3(const Joc &J);
        virtual ~Cautator_Tip3();
        void Deplasare (const Joc &J);  //deplasarea, redefinita pentru cautatorul de tip 3

    protected:

    private:
};

class Cautator_Tip4 : public Cautator
{
    public:
        Cautator_Tip4(const Joc &J);
        virtual ~Cautator_Tip4();
        void Deplasare (const Joc &J);  //deplasarea, redefinita pentru cautatorul de tip 4

    protected:

    private:
};


#endif // CAUTATOR_H
