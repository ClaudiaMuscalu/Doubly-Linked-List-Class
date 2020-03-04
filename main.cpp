#include <iostream>
#include<string.h>
#include<new>
using namespace std;

/** Liste circulare dublu inlantuite cu clase generice **/
/** Declararea clasei nod **/

template<class T> class Lista;

template <class T>
class nod
{
private:
    T info;
    nod* prec;
    nod* urm;

public:

    friend class Lista<T>;
    friend class Iterator;

    nod(){}

    nod(T valoare, nod* p, nod* u):info(valoare),prec(p),urm(u){}

    ~nod(){}

    T getdata();

    T& getdat();

    void setdata(T valoare);

    nod* getprec();

    nod* geturm();

    void setprec(nod* p);

    void seturm(nod* u);

    nod(const nod& c);

    nod operator=(const nod& c);
};

template <> nod<char*>::nod(char * s,nod *p, nod * u)
{
    try
    {
        info=new char[strlen((s)+1)];
    }
    catch(bad_alloc xa)
    {
        cout<<"Nu s-a putut aloca memorie pentru cuvantul dat in constructorul specializat din clasa nod.\n";

    }
    strcpy(info,s);
    prec=p;
    urm=u;
}
template <> nod<char*>::~nod()
{
    delete[] info;
}

template <class T> T nod<T>::getdata()
{
    return info;
}

template <class T> T& nod<T>::getdat()
{
    return info;
}

template <class T> void nod<T>::setdata(T valoare)
{
    info=valoare;
}

template <class T> nod<T>* nod<T>::getprec()
{
    return prec;
}

template <class T> nod<T>* nod<T>::geturm()
{
    return urm;
}

template <class T> void nod<T>::setprec(nod* p)
{
    prec=p;

}
template <class T> void nod<T>::seturm(nod* u)
{
    urm=u;
}

template <class T> nod<T>::nod(const nod& c)
{
    info=c.info;
    prec=c.prec;
    urm=c.urm;
}

template <class T> nod<T> nod<T>::operator=(const nod& c)
{
    if(this==&c)
        return *this;
    info=c.info;
    prec=c.prec;
    urm=c.urm;
    return *this;
}
/****************************/
/** Declararea clasei Lista **/
template<class T>
class Lista
{

private:
    nod<T>* prim;
    nod<T>*ultim;

public:

    Lista();

    Lista(int i, T x);

    ~Lista();

    Lista(const Lista& c);

    Lista operator=(const Lista& c);

    nod<T>* cautarepozitie(int poz);

    void push_front(T valoare);

    void push_back(T valoare);

    void sterge_interior(nod<T>* elem);

    T pop_back();

    T pop_front();

    void insert(int i, T valoare);

    void remove(int i);

    void golire_lista();

    int nr_lista()const;

    void afisare();

    T& operator[](int i);

    bool operator!()const;

    operator bool()const;

    operator int()const;

    class Iterator
    {

    public:
        nod<T>* curent;

        Iterator(nod<T>* c):curent(c){}

        void increment(){curent=curent->urm;}

        Iterator operator++(){curent=curent->urm; return *this;}//prefixat

        Iterator operator++(int)

        {Iterator temp(*this);
         operator++();
         return temp;
        }

        const Iterator& operator=(const Iterator& iter)
        {
            curent=iter.curent;
            return (*this);
        }

        bool operator==(const Iterator& iter)
        {
            return curent==iter.curent;
        }

        bool operator!=(const Iterator iter)
        {
            return !((*this)==iter);
        }

        T operator*()const
        {
            return curent->getdata();
        }
        T* operator->()const//nod pointer la informatie
        {
            return &curent->getdat();
        }
    };
        Iterator begin(){return Iterator(prim);}
        Iterator end(){return Iterator(NULL);}


};
template <class T> Lista<T>::Lista()
{
    prim=NULL;
    ultim=prim;
}

template <class T> Lista<T>::Lista(int i, T x)
{
   prim=ultim=NULL;
   while(i!=0)
   {push_back(x);
    i--;
   }
}

template <class T> Lista<T>::~Lista()
{
    golire_lista();
}

template <class T> Lista<T>::Lista(const Lista& c)
{
    nod<T>* p;
    prim=NULL;
    p=c.prim;

    if(p==NULL)
        return;

    while(p->geturm()!=NULL)
    {
        push_back(p->getdata());
        p=p->geturm();
    }
    push_back(p->getdata());
}

template <class T> Lista<T> Lista<T>::operator=(const Lista& c)
{
    if(this==&c)
        return (*this);
    golire_lista();
    nod<T>* p;
    p=c.prim;
     while(p->geturm()!=NULL)
    {
        push_back(p->getdata());
        p=p->geturm();
    }
    push_back(p->getdata());
    return (*this);
}

template <class T> nod<T>* Lista<T>::cautarepozitie(int poz)
{
    int i=0;
    nod<T>* p;
    p=prim;

    while(p!=NULL&&i<poz)
    {
        i++;
        p=p->geturm();
    }
    if(i==poz)
        return p;
    return NULL;
}

template <> nod<char*>* Lista<char*>::cautarepozitie(int poz)
{
    int i=0;
    nod<char *>* p;
    p=prim;

    while(p!=NULL&&i<poz)
    {
        i++;
        p=p->geturm();
    }
    if(i==poz)
        return p;
    return NULL;
}

template <class T> void Lista <T>::push_front(T x)
{
    nod<T>* p;
    try
    {
        p=new nod<T>(x,NULL,prim);
    }
    catch(bad_alloc xa)
    {
        cout<<"Alocare esuata in functia push_front.\n";
    }
    if(prim!=NULL)
        prim->setprec(p);
    prim=p;
}

template <> void Lista <char*>::push_front(char *x)
{
    cout<<"Metoda specializata:\n";
    nod<char *>* p;
    try
    {
        p=new nod<char *>(x,NULL,prim);
    }
    catch(bad_alloc xa)
    {
        cout<<"Alocare esuata in functia push_front metoda specializata.\n";
    }
    if(prim!=NULL)
        prim->setprec(p);
    prim=p;

}

template <class T> void Lista<T>::push_back(T x)
{
    nod<T>* p;

    try
    {
        p=new nod<T>;
    }
    catch(bad_alloc xa)
    {
        cout<<"Alocare esuata in functia push_back.\n";
    }

    p->setdata(x);
    p->setprec(ultim);
    p->seturm(NULL);

    if(prim==NULL)
        {prim=p;
         ultim=prim;
        }
    else
        {
        ultim->seturm(p);
        ultim=p;
        }
}

template <> void Lista <char*>::push_back(char *x)
{
    nod<char *>* p;

    try
    {
        p=new nod<char *>(x,ultim,NULL);

    }
    catch(bad_alloc xa)
    {
        cout<<"Alocarea esuata in fucntia puch_back metoda specializata.\n";
    }
    if(prim==NULL)
        {prim=p;
         ultim=prim;
        }
    else
        {
        ultim->seturm(p);
        ultim=p;
        }
}

template <> Lista<char*>::Lista(int i, char *x)
{
    prim=ultim=NULL;
    while(i!=0)
    {
        push_back(x);
        i--;
    }
}

template <class T> void Lista<T>::sterge_interior(nod<T>* elem)
{
    elem->getprec()->seturm(elem->geturm());
    elem->geturm()->setprec(elem->getprec());
    delete elem;
}

template <class T> T Lista<T>::pop_back()
{
    if(prim==NULL)
    {
        cout<<"Lista este deja vida";
    }

    T val=ultim->getdata();

    if(prim==ultim)
    {
        delete prim;
        prim=ultim=NULL;

    }
    nod<T>* p;
    p=prim;
    while(p->geturm()!=ultim)
        p=p->geturm();

    p->seturm(NULL);
    delete ultim;
    ultim=p;

    return val;
}

template <class T> T Lista<T>::pop_front()
{
    if(prim==NULL)
    {
        cout<<"Lista este deja vida";
    }

    nod<T>* p;
    T v=prim->getdata();
    p=prim;
    if(prim==ultim)
        prim=ultim=NULL;
    else
        prim=prim->geturm();

    delete p;
    return v;
}


template <class T> void Lista<T>::insert(int i, T valoare)
{
    if(i<0||i>nr_lista())
        throw 1;

    int n=nr_lista();
    if(i==0)
    {nod<T>* p=new nod<T>(valoare,NULL,prim);
     if(prim==NULL)
        prim=ultim=p;
     else
        prim->setprec(p);
     prim=p;
    }
    else
       if(i==n)
       push_back(valoare);
    else
    {
        nod<T> *q=cautarepozitie(i);
        nod<T>* r=q->getprec();

        nod<T> *p=new nod<T>(valoare,r,q);
        q->setprec(p);
        r->seturm(p);
    }
}

template <> void Lista <char *>::insert(int i, char *s)
{
    if(i<0||i>nr_lista())
        throw 1;

    int n=nr_lista();
    if(i==0)
    {nod<char *>* p=new nod<char *>(s,NULL,prim);
     if(prim==NULL)
        prim=ultim=p;
     else
        prim->setprec(p);
     prim=p;
    }
    else
       if(i==n)
       push_back(s);
    else
    {
        nod<char *> *q=cautarepozitie(i);
        nod<char *>* r=q->getprec();

        nod<char *> *p=new nod<char *>(s,r,q);
        q->setprec(p);
        r->seturm(p);
    }

}

template <class T> void Lista<T>::remove(int i)
{
    if(i<0||i>nr_lista())
        throw 1;
    if(prim==NULL)
        throw 'a';

    if(i==0)
        {cout<<pop_front();
         return;
        }

    nod<T>* p=cautarepozitie(i);
    sterge_interior(p);

}
template <class T> void Lista<T>::golire_lista()
{
    while(prim!=NULL)
        pop_front();
}

template <class T> int Lista<T>::nr_lista()const
{
    int i=0;
    nod<T>* p;
    p=prim;
    while(p!=NULL)
    {
        i++;
        p=p->geturm();
    }
    return i;
}

template <class T> void Lista<T>::afisare()
{
    if(prim==NULL)
    {
        cout<<"Lista este vida\n";
        return;
    }
    nod<T>* p;
    p=prim;

    while(p!=NULL)
    {
        cout<<p->getdata()<<" ";
        p=p->geturm();
    }
    cout<<"\n";
}

template <class T> T& Lista<T>::operator[](int i)
{
    if(i<0||i>nr_lista())
        throw 1;
    nod<T>* p;
    p=cautarepozitie(i);
    return p->getdat();
}

template <class T> bool Lista<T>::operator!()const
{
    if(nr_lista()!=0)
        return true;
    return false;
}

template <class T> Lista<T>::operator bool()const
{
    if(nr_lista()!=0)
        return true;
    return false;
}

template <class T> Lista<T>::operator int()const
{
    return nr_lista();
}

int main()
{
    unsigned int optiune;
    do
    {
        cout<<"\n\nOptiuni pentru tipul de date ales:\n";
        cout<<"1. int\n";
        cout<<"2. double\n";
        cout<<"3. char\n";
        cout<<"4. char*\n";
        cout<<"5. Exit\n";

        cin>>optiune;

        switch(optiune)
    {

    case 1:
        {
            cout<<"Verificare pentru tipul int:\n";

            Lista<int> l;
            cout<<"\nVerificare functiilor de push:\n";
            l.push_back(5);
            l.push_front(4);
            l.push_back(6);
            l.push_back(7);
            l.push_front(3);
            l.push_back(8);
            cout<<"Lista creata este urmatoarea:\n";
            l.afisare();

            cout<<"\nElementul de la inceputul listei este: "<<l.pop_front()<<"\n";
            l.afisare();
            cout<<"Elementul de la sfarsitul listei este: "<<l.pop_back()<<"\n";
            l.afisare();

            try
            {
            cout<<"Dati o pozitie pentru stergere:\n";
            int x;
            cin>>x;
            l.remove(x);
            cout<<"Lista dupa stergere:\n";
            l.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data este invalida pentru stergere.\n";
            }
            catch(char i)
            {
            cout<<"Lista este deja vida, deci nu se mai poate sterge\n";
            }

            try
            {
            cout<<"Inserarea pe o pozitie data a unei valori date:\n";
            l.insert(1,9);
            l.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data este invalida pentru inserare.\n";
            }

            cout<<"Verificare pentru constructorul cu parametri:\n";
            Lista<int> l1(4,7);

            cout<<"Afisarea listei l1 folosind clasa Iterator:\n";
            for (Lista<int>::Iterator b = l1.begin(); b.curent != l1.end().curent; b.increment())
            {
                cout<<*b<<" ";
            }
            try
            {
            cout<<"\n"<<l1[1]<<"\n";
            cout<<"Dimensiunea listei l1 este:\n";
            cout<<int(l1)<<"\n";
            l1[-1]=100;//
            l1.afisare();

            }
            catch(int i)
            {
                cout<<"Pozitia data pentru operatorul [] este invalida.\n";
            }

        }
    case 2:
        {
            cout<<"Verificare pentru tipul double:\n";

            Lista<double> l2;
            cout<<"\nVerificare functiilor de push:\n";
            l2.push_back(5.9);
            l2.push_front(4.72);
            l2.push_back(6.87);
            l2.push_back(7.0);
            l2.push_front(3);
            l2.push_back(8.78);
            cout<<"Lista creata este urmatoarea:\n";
            l2.afisare();

            cout<<"\nElementul de la inceputul listei este: "<<l2.pop_front()<<"\n";
            l2.afisare();
            cout<<"Elementul de la sfarsitul listei este: "<<l2.pop_back()<<"\n";
            l2.afisare();

            try
            {
            cout<<"Dati o pozitie pentru stergere:\n";
            int x;
            cin>>x;
            l2.remove(x);
            cout<<"\nLista dupa stergere:\n";
            l2.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data pentru stergere este invalida pentru stergere.\n";
            }
            catch(char i)
            {
            cout<<"Lista este deja, deci nu se mai poate sterge vida\n";
            }

            try
            {
            cout<<"Inserarea pe o pozitie data a unei valori date:\n";
            l2.insert(1,9.99);
            l2.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data pentru inserare este invalida.\n";
            }

            cout<<"Verificare pentru constructorul cu parametri:\n";
            Lista<double> l1(4,6.32);

            cout<<"Afisarea listei l1 folosind clasa Iterator:\n";
            for (Lista<double>::Iterator b = l1.begin(); b.curent != l1.end().curent; b.increment())
            {
                cout<<*b<<" ";
            }

            try
            {
            cout<<"\n"<<l1[1]<<"\n";
            cout<<"Dimensiunea listei l1 este:\n";
            cout<<int(l1)<<"\n";
            l1[1]=9.99;
            l1.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data pentru [] este invalida.\n";
            }

        }
    case 3:
        {
            cout<<"Verificare pentru tipul char:\n";

            Lista<char> lc;
            cout<<"\nVerificare functiilor de push:\n";
            lc.push_back('5');
            lc.push_front('a');
            lc.push_back('b');
            lc.push_back('c');
            lc.push_front('d');
            lc.push_back('r');
            cout<<"Lista creata este urmatoarea:\n";
            lc.afisare();

            cout<<"\nElementul de la inceputul listei este: "<<lc.pop_front()<<"\n";
            lc.afisare();
            cout<<"Elementul de la sfarsitul listei este: "<<lc.pop_back()<<"\n";
            lc.afisare();

            try
            {
            cout<<"Dati o pozitie pentru stergere:\n";
            int x;
            cin>>x;
            lc.remove(x);
            cout<<"\nLista dupa stergere:\n";
            lc.afisare();
            }

            catch(int i)
            {
            cout<<"Pozitia data pentru stergere este invalida pentru stergere.\n";
            }
            catch(char i)
            {
            cout<<"Lista este deja vida, deci nu se mai poate sterge\n";
            }

            try
            {
            cout<<"Inserarea pe o pozitie data a unei valori date:\n";
            lc.insert(1,'f');
            lc.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data este invalida pentru inserare.\n";
            }

            cout<<"Verificare pentru constructorul cu parametri:\n";
            Lista<char> l1(4,'M');

            cout<<"Afisarea listei l1 folosind clasa Iterator:\n";
            for (Lista<char>::Iterator b = l1.begin(); b.curent != l1.end().curent; b.increment())
            {
                cout<<*b<<" ";
            }
            try
            {
            cout<<"\n"<<lc[1]<<"\n";
            cout<<"Dimensiunea listei l1 este:\n";
            cout<<int(lc)<<"\n";
            l1[1]='a';
            l1.afisare();
            }
           catch(int i)
           {
                cout<<"Pozitia data pentru [] este invalida.\n";
           }
           break;
        }
    case 4:
        {
            cout<<"Verificare pentru tipul char*:\n";

            Lista<char*> lc;
            cout<<"\nVerificare functiilor de push:\n";
            lc.push_back("Piersica");
            lc.push_front("mar");
            lc.push_back("cireasa");
            lc.push_back("gutuie");
            lc.push_front("strugure");
            lc.push_back("caisa");
            cout<<"Lista creata este urmatoarea:\n";
            lc.afisare();

            try
            {
            cout<<"Dati o pozitie pentru stergere:\n";
            int x;
            cin>>x;
            lc.remove(x);
            cout<<"Lista dupa stergere:\n";
            lc.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data pentru stergere este invalida pentru stergere.\n";
            }
            catch(char i)
            {
            cout<<"Lista este deja vida, deci nu se mai poate sterge\n";
            }

            try
            {
            cout<<"Inserarea pe o pozitie data a unei valori date:\n";
            lc.insert(1,"vopsea");
            lc.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data este invalida pentru inserare.\n";
            }

            cout<<"Verificare pentru constructorul cu parametri:\n";
            Lista<char*> l1(4,"canapea");

            cout<<"Afisarea listei l1 folosind clasa Iterator:\n";
            for (Lista<char*>::Iterator b = l1.begin(); b.curent != l1.end().curent; b.increment())
            {
                cout<<*b<<" ";

            }
            try
            {
            cout<<"\n"<<lc[1]<<"\n";
            cout<<"Dimensiunea listei l1 este:\n";
            cout<<int(lc)<<"\n";
            l1[2]="apa";
            l1.afisare();
            }
            catch(int i)
            {
            cout<<"Pozitia data pentru [] este invalida.\n";
            }
            break;
        }
    }
    }
    while(optiune<5);

    return 0;
}

