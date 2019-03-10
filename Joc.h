#ifndef JOC_H
#define JOC_H

class Cautator; //am nevoie de forward declaration pentru clasa Cautator

class Joc
{
    public:
        Joc(int d);  //constructor cu parametru pentru dimensiunea hartii
        bool IsOver ();  //verific daca jocul s-a incheiat
        int Runda (int d);  //desfasurarea unei runde
        void Joc_Total();  //gestionarea jocului
        void Afisare_Runda();  //afisarea unei runde
        virtual ~Joc();

    protected:

    private:
        int **Harta;
        int Numar_Comori_Gasite;
        int Dimensiune_Harta;
        int *Playing;
        Cautator *C[4];
        int indice_castigator;
        friend class Cautator;  //clasa Cautator este friend deoarece in constructorul acestuia doresc sa modific membrul Playing al jocului, care este privat
        friend class Cautator_Tip1;  //clasele tipurilor de cautatori sunt friend deoarece
        friend class Cautator_Tip2;  //in functiile de deplasare ale acestora am nevoie sa verific daca pozitia de pe harta
        friend class Cautator_Tip3;  //pe care vreau sa-i mut este libera, iar harta este un membru private al jocului
        friend class Cautator_Tip4;

};

#endif // JOC_H
