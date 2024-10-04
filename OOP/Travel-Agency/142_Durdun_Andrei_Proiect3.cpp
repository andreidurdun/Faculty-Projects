#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <exception>
#include <set>
#include <list>

using namespace std;

class Plata
{
private:
    string metodaPlata;
    float sumaPlatita;
public:
    Plata();
    Plata(string metodaPlata, float sumaPlatita);
    Plata(const Plata& obj);
    Plata& operator=(const Plata& obj);
    ~Plata()=default;
    friend ostream& operator<<(ostream& out, const Plata& obj);
    friend istream& operator>>(istream& in, Plata& obj);
    void setSumaPlatita(float sumaPlatita);
};
Plata::Plata()
{
    metodaPlata="cash/card";
    sumaPlatita=0;
}
Plata::Plata(string metodaPlata, float sumaPlatita)
{
    this->metodaPlata=metodaPlata;
    this->sumaPlatita=sumaPlatita;
}
Plata::Plata(const Plata& obj)
{
    metodaPlata=obj.metodaPlata;
    sumaPlatita=obj.sumaPlatita;
}
Plata& Plata::operator=(const Plata& obj) //!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
    if(this!=&obj)
    {   
        metodaPlata=obj.metodaPlata;
        sumaPlatita=obj.sumaPlatita;
    }
    return *this;
}
ostream& operator<<(ostream& out, const Plata& obj)
{
    out<<"Suma platita: "<<obj.sumaPlatita<<endl;
    out<<"Metoda plata: "<<obj.metodaPlata<<endl;
    return out;
}
istream& operator>>(istream& in, Plata& obj)
{
    cout<<"Metoda Plata (Cash/Card): ";
    in>>obj.metodaPlata;
    return in;
}
void Plata::setSumaPlatita(float sumaPlatita)
{
    this->sumaPlatita=sumaPlatita;
}


class Client
{
protected:
    Plata plata;
    string nume;
    string prenume;
public:
    Client();
    Client(Plata plata, string nume, string prenume);
    Client(const Client& obj);
    Client& operator=(const Client& obj);
    virtual ~Client()=default;
    virtual ostream& Afisare(ostream& out) const;
    virtual istream& Citire(istream& in);
    friend ostream& operator<<(ostream& out, const Client& obj);
    friend istream& operator>>(istream& in, Client& obj);
    virtual void AfisarePlata();
    void setPlata(Plata plata);
};
Client::Client()
{
    Plata p;
    plata=p;
    nume="anonim";
    prenume="anonim";
}
Client::Client(Plata plata, string nume, string prenume)
{
    this->plata=plata;
    this->nume=nume;
    this->prenume=prenume;
}
Client::Client(const Client& obj)
{
    plata=obj.plata;
    nume=obj.nume;
    prenume=obj.prenume;
}
Client& Client::operator=(const Client& obj)
{
    if(this!=&obj)
    {
        plata=obj.plata;
        nume=obj.nume;
        prenume=obj.prenume;
    }
    return *this;
}
ostream& Client::Afisare(ostream& out) const
{
    out<<"Nume: "<<nume<<endl;
    out<<"Prenume: "<<prenume<<endl;
    out<<plata;
    return out;
}
istream& Client::Citire(istream& in)
{
    cout<<"Nume: ";
    in>>nume;
    cout<<"Prenume: ";
    in>>prenume;
    return in;
}
ostream& operator<<(ostream& out, const Client& obj)
{
    return obj.Afisare(out);
}
istream& operator>>(istream& in, Client& obj)
{
    return obj.Citire(in);
}
void Client::AfisarePlata()
{
    cout<<plata;
}
void Client::setPlata(Plata plata)
{
    this->plata=plata;
}

class ContUtilizator : public Client
{
private:
    string email;
    string nrTelefon;
    string parola;
public:
    ContUtilizator();
    ContUtilizator(Plata plata, string nume, string prenume, string email, string nrTelefon, string parola);
    ContUtilizator(const ContUtilizator& obj);
    ContUtilizator& operator=(const ContUtilizator& obj);
    ~ContUtilizator()=default;
    ostream& Afisare(ostream& out) const;
    istream& Citire(istream& in);
    void AfisarePlata();
};
ContUtilizator::ContUtilizator():Client()
{
    email="nespecificat@gmail.com";
    nrTelefon="0777777777";
    parola="nespecificata";
}
ContUtilizator::ContUtilizator(Plata plata, string nume, string prenume, string email, string nrTelefon, string parola):Client(plata, nume, prenume)
{
    this->email=email;
    this->nrTelefon=nrTelefon;
    this->parola=parola;
}
ContUtilizator::ContUtilizator(const ContUtilizator& obj):Client(obj)
{
    email=obj.email;
    nrTelefon=obj.nrTelefon;
    parola=obj.parola;
}
ContUtilizator& ContUtilizator::operator=(const ContUtilizator& obj) //!!!!!!!!!!!!!
{
    if(this!=&obj)
    {
        Client::operator=(obj);
        email=obj.email;
        nrTelefon=obj.nrTelefon;
        parola=obj.parola;
    }
    return *this;
}
ostream& ContUtilizator::Afisare(ostream& out) const
{
    Client::Afisare(out);
    out<<"Email: "<<email<<endl;
    out<<"Numarul de telefon: "<<nrTelefon<<endl;
    return out;
}
istream& ContUtilizator::Citire(istream& in)
{
    Client::Citire(in);
    cout<<"Email: ";
    in>>email;
    cout<<"Numarul de telefon: ";
    in>>nrTelefon;
    cout<<"Parola: ";
    in>>parola;
    return in;
}
void ContUtilizator::AfisarePlata()
{
    cout<<plata;
}

class Vehicul
{
protected:
    static int CONTOR;
    const int idVehicul;
    string tipVehicul;
public:
    Vehicul();
    Vehicul(string tipVehicul);
    Vehicul(const Vehicul& obj);
    Vehicul& operator=(const Vehicul& obj);
    virtual ~Vehicul();
    virtual ostream& Afisare(ostream& out) const;
    virtual istream& Citire(istream& in);
    friend ostream& operator<<(ostream& out, const Vehicul& obj);
    friend istream& operator>>(istream& in, Vehicul& obj);
    string getVehicul();
};
int Vehicul::CONTOR=0;
Vehicul::Vehicul():idVehicul(++CONTOR)
{
    tipVehicul="nespecificat";
}
Vehicul::Vehicul(string tipVehicul):idVehicul(++CONTOR)
{
    this->tipVehicul=tipVehicul;
}
Vehicul::Vehicul(const Vehicul& obj):idVehicul(obj.idVehicul)
{
    tipVehicul=obj.tipVehicul;
}
Vehicul& Vehicul::operator=(const Vehicul& obj)
{
    if(this!=&obj)
    {
        tipVehicul=obj.tipVehicul;
    }
    return *this;
}
ostream& Vehicul::Afisare(ostream& out) const
{
    out<<"ID vehicul: "<<idVehicul<<endl;
    out<<"Tip vehicul: "<<tipVehicul<<endl;
    return out;
}
istream& Vehicul::Citire(istream& in)
{
    cout<<"Tip vehicul: ";
    in>>tipVehicul;
    return in;
}
ostream& operator<<(ostream& out, const Vehicul& obj)
{
    return obj.Afisare(out);
}
istream& operator>>(istream& in, Vehicul& obj)
{
    return obj.Citire(in);
}
Vehicul::~Vehicul()
{
    CONTOR--;
}
string Vehicul::getVehicul()
{
    return tipVehicul;
}

class Transport : public Vehicul
{
protected:
    int nrLocuri;
    string companieTr;
public:
    Transport();
    Transport(string tipVehicul, int nrLocuri, string companieTr);
    Transport(const Transport& obj);
    Transport& operator=(const Transport& obj);
    ~Transport()=default;
    virtual ostream& Afisare(ostream& out) const;
    virtual istream& Citire(istream& in);
};
Transport::Transport():Vehicul()
{
    nrLocuri=0;
    companieTr="nespecificata";
}
Transport::Transport(string tipVehicul, int nrLocuri, string companieTr):Vehicul(tipVehicul)
{
    this->nrLocuri=nrLocuri;
    this->companieTr=companieTr;
}
Transport::Transport(const Transport& obj):Vehicul(obj)
{
    nrLocuri=obj.nrLocuri;
    companieTr=obj.companieTr;
}
Transport& Transport::operator=(const Transport& obj)
{
    if(this!=&obj)
    {
        Vehicul::operator=(obj);
        nrLocuri=obj.nrLocuri;
        companieTr=obj.companieTr;
    }
    return *this;
}
ostream& Transport::Afisare(ostream& out) const
{
    Vehicul::Afisare(out);
    out<<"Numar Locuri: "<<nrLocuri<<endl;
    out<<"Compania de transport: "<<companieTr<<endl;
    return out;
}
istream& Transport::Citire(istream& in)
{
    Vehicul::Citire(in);
    cout<<"Numar Locuri: ";
    in>>nrLocuri;
    cout<<"Compania de transport: ";
    in>>companieTr;
    return in;
}

class PachetTransport : public Transport
{
private:
    int reducere;
    float pretTransport;
public:
    PachetTransport();
    PachetTransport(string tipVehicul, int nrLocuri, string companieTr, int reducere, float pretTransport);
    PachetTransport(const PachetTransport& obj);
    PachetTransport& operator=(const PachetTransport& obj);
    ~PachetTransport()=default;
    virtual ostream& Afisare(ostream& out) const;
    virtual istream& Citire(istream& in);
    float getPret();
    bool operator<(const PachetTransport& obj) const;
    void ft();
};
PachetTransport::PachetTransport():Transport()
{
    reducere=0;
    pretTransport=0;
}
PachetTransport::PachetTransport(string tipVehicul, int nrLocuri, string companieTr, int reducere, float pretTransport):Transport(tipVehicul, nrLocuri, companieTr)
{
    this->reducere=reducere;
    this->pretTransport=pretTransport;
}
PachetTransport::PachetTransport(const PachetTransport& obj):Transport(obj)
{
    reducere=obj.reducere;
    pretTransport=obj.pretTransport;
}
PachetTransport& PachetTransport::operator=(const PachetTransport& obj)
{
    if(this!=&obj)
    {
        Transport::operator=(obj);
        reducere=obj.reducere;
        pretTransport=obj.pretTransport;
    }
    return *this;
}
ostream& PachetTransport::Afisare(ostream& out) const
{
    Transport::Afisare(out);
    out<<"Reducere: "<<reducere<<"%"<<endl;
    out<<"Pret Transport: "<<pretTransport<<endl;
    return out;
}
istream& PachetTransport::Citire(istream& in)
{
    Transport::Citire(in);
    cout<<"Reducere: ";
    in>>reducere;
    cout<<"Pret Transport: ";
    in>>pretTransport;
    return in;
}
float PachetTransport::getPret()
{
    return pretTransport;
}
bool PachetTransport::operator<(const PachetTransport& obj) const
{
    return this->pretTransport<obj.pretTransport;
}
void PachetTransport::ft()
{
    cout<<tipVehicul<<endl;
}

class PachetTuristic
{
private:
    string destinatie;
    float pret;
    string dataPlecare;
    string dataIntoarcere;
public:
    PachetTuristic();
    PachetTuristic(string destinatie, float pret, string dataPlecare, string dataIntoarcere);
    PachetTuristic(const PachetTuristic& obj);
    PachetTuristic& operator=(const PachetTuristic& obj);
    ~PachetTuristic()=default;
    virtual ostream& Afisare(ostream& out) const;
    virtual istream& Citire(istream& in);
    friend ostream& operator<<(ostream& out, const PachetTuristic& obj);
    friend istream& operator>>(istream& in, PachetTuristic& obj);
    string getDestinatie();
    float getPret();
    bool operator<(const PachetTuristic& obj) const;
    void ft();
};
PachetTuristic::PachetTuristic()
{
    destinatie="necunoscuta";
    pret=0;
    dataPlecare="00.00.0000";
    dataIntoarcere="00.00.0000";
}
PachetTuristic::PachetTuristic(string destinatie, float pret, string dataPlecare, string dataIntoarcere)
{
    this->destinatie=destinatie;
    this->pret=pret;
    this->dataPlecare=dataPlecare;
    this->dataIntoarcere=dataIntoarcere;
}
PachetTuristic::PachetTuristic(const PachetTuristic& obj)
{
    destinatie=obj.destinatie;
    pret=obj.pret;
    dataPlecare=obj.dataPlecare;
    dataIntoarcere=obj.dataIntoarcere;
}
PachetTuristic& PachetTuristic::operator=(const PachetTuristic& obj)
{
    if(this!=&obj)
    {
        destinatie=obj.destinatie;
        pret=obj.pret;
        dataPlecare=obj.dataPlecare;
        dataIntoarcere=obj.dataIntoarcere;
    }
    return *this;
}
ostream& PachetTuristic::Afisare(ostream& out) const
{
    out<<"Destinatie: "<<destinatie<<endl;
    out<<"Pret: "<<pret<<endl;
    out<<"Data plecarii: "<<dataPlecare<<endl;
    out<<"Data intoarcerii: "<<dataIntoarcere<<endl;
    return out;
}
istream& PachetTuristic::Citire(istream& in)
{
    cout<<"Destinatie: ";
    in>>destinatie;
    cout<<"Pret: ";
    in>>pret;
    cout<<"Data plecarii: ";
    in>>dataPlecare;
    cout<<"Data intoarcerii: ";
    in>>dataIntoarcere;
    return in;
}
ostream& operator<<(ostream& out, const PachetTuristic& obj)
{
    return obj.Afisare(out);
}
istream& operator>>(istream& in, PachetTuristic& obj)
{
    return obj.Citire(in);
}
string PachetTuristic::getDestinatie()
{
    return destinatie;
}
float PachetTuristic::getPret()
{
    return pret;
}
bool PachetTuristic::operator<(const PachetTuristic& obj) const
{
    return this->pret<obj.pret;
}
void PachetTuristic::ft()
{
    cout<<destinatie<<endl;
}

class EroareRezervare: public exception
{
    public:

    const char* what() const throw()
    {
        return "Eroare Rezervare!";
    }
}eroareRezervare;

template <class T>
class GestionarePachete
{
private:
    T* pachete;
    int lungime;
    map<T, bool> disponibilitate;
public:
    GestionarePachete();
    void push(T val);
    T operator[] (int i) const;
    void rezervare(int i);
    void anulareRezervare(int i);
    bool getDisponibilitate(int i) const;
    int size();
};
template <class T>
GestionarePachete<T>::GestionarePachete()
{
    pachete=NULL;
    lungime=0;
}
template <class T>
void GestionarePachete<T>::push(T val)
{
    lungime++;
    T* copie=new T[lungime];
    for(int i=0; i< lungime-1; i++)
        copie[i]=pachete[i];
    copie[lungime-1]=val;
    if(pachete!=NULL)
        delete[] pachete;
    pachete=copie;
    //setez disponibilitatea
    for(int i=0; i< lungime; i++)
        if(disponibilitate.find(pachete[i]) == disponibilitate.end()) //daca nu exisa
            disponibilitate[pachete[i]]=true;
}
template <class T>
T GestionarePachete<T>::operator[] (int i) const //eroare
{
    if(i<0 || i>lungime-1)
        throw out_of_range("Out of range.");
    else
        return pachete[i];
}
template <class T>
void GestionarePachete<T>::rezervare(int i) //eroare
{
    if(disponibilitate[pachete[i]]==true)
        disponibilitate[pachete[i]]=false;
    else
        throw eroareRezervare;
}
template <class T>
void GestionarePachete<T>::anulareRezervare(int i) //eroare
{
    if(disponibilitate[pachete[i]]==false)
        disponibilitate[pachete[i]]=true;
    else
        throw eroareRezervare;
}
template <class T>
bool GestionarePachete<T>::getDisponibilitate(int i) const
{
    return disponibilitate.at(pachete[i]);
}
template <class T>
int GestionarePachete<T>::size()
{
    return lungime;
}

class Meniu
{
private:
    static Meniu* instance;
    Meniu(){}
    ~Meniu(){}

    Client* cont=new ContUtilizator(); //ca sa am acces la datele clientului
    vector<PachetTuristic*> pacheteTuristice;
    vector<Vehicul*> pacheteTransport;
    GestionarePachete<PachetTuristic> gestionareTuristice; //rezervari
    GestionarePachete<PachetTransport> gestionareTransport;
    
    int indiceTur, indiceTrans;
    float sumaPacheteTur;
public:
    Meniu(const Meniu&)=delete;
    Meniu& operator=(const Meniu&)=delete;
    static Meniu* getInstance();
    static void destructor();
    
    void logIn();
    void afisarePTuristice();
    void afisarePTransport();
    void gestionarePTuristice();
    void gestionarePTransport();
    void introducerePacheteTur(PachetTuristic& pachet);
    void introducerePacheteTrans(Vehicul& pachet);
    void sumaDePlata();
    void afisPacheteRezervate();
    GestionarePachete<PachetTuristic> getGestionareTuristice();
    GestionarePachete<PachetTransport> getGestionareTransport();
};
Meniu* Meniu::instance=NULL;
Meniu* Meniu::getInstance()
{
    if(instance!=NULL)
        return instance;
    else
    {
        instance=new Meniu();
        return instance;
    }
}
void Meniu::destructor()
{
    if(instance!=NULL)
        delete instance;
    instance=NULL;   
}

void Meniu::introducerePacheteTur(PachetTuristic& pachet)
{
    pacheteTuristice.push_back(&pachet);
    gestionareTuristice.push(pachet);
}
void Meniu::introducerePacheteTrans(Vehicul& pachet) //dyamic_cast //Eroare
{
    pacheteTransport.push_back(&pachet);
    if(dynamic_cast<PachetTransport*>(&pachet) != NULL)
    {
        gestionareTransport.push(*dynamic_cast<PachetTransport*>(&pachet));
    }
    else
        throw runtime_error("Cast esuat!");
}
void Meniu::logIn()
{
    cout<<"\nLOGARE CONT:\n\n";
    cin>>*cont;
}
void Meniu::afisarePTuristice()
{
    cout<<"\nPachetele turistice sunt:\n\n";
    for(int i=0; i<pacheteTuristice.size(); i++)
    {
        cout<<i+1<<". "<<pacheteTuristice[i]->getDestinatie()<<'\n';
    }
}
void Meniu::gestionarePTuristice() //detalii despre pachetul turistic ales   EROARE
{
    cout<<"\nSelectati pachetul dorit.\n";
    cin>>indiceTur;
    indiceTur--;
    if(indiceTur<0 || indiceTur>=pacheteTuristice.size())
        throw runtime_error("Input invalid.");

    
    cout<<*pacheteTuristice[indiceTur]<<endl;

    cout<<"1. Rezerva Pachet.\n";
    cout<<"2. Alege Alt Pachet.\n";
    cout<<"3. Rezerva si mai alege un pachet.\n";

    int a;
    cin>>a;
    Meniu* meniu=Meniu::getInstance();
    switch(a)
    {
        case 1:
        {
            try
            {
                gestionareTuristice.rezervare(indiceTur);
            }
            catch(EroareRezervare& eroareRezervare)
            {
                cout<<"Acest pachet a fost deja rezervat.\n";
                meniu->gestionarePTuristice();
            }
            break;
        }
        case 2:
        {
            meniu->afisarePTuristice();
            meniu->gestionarePTuristice();
            break;
        }
        case 3:
        {
            try
            {
                gestionareTuristice.rezervare(indiceTur);
            }
            catch(EroareRezervare& eroareRezervare)
            {
                cout<<"Acest pachet a fost deja rezervat.\n";
                meniu->gestionarePTuristice();
            }
            meniu->afisarePTuristice();
            meniu->gestionarePTuristice();
            break;
        }
        default:
        {
            cout<<"Comanda invalida!\n";
            gestionarePTuristice();
            break;
        }

    }

}
void Meniu::afisarePTransport() //upcasting
{
    cout<<"\nAlegeti transportul: \n\n";
    for(int i=0; i<pacheteTransport.size(); i++)
    {
        cout<<i+1<<". \n"<<(Vehicul)*pacheteTransport[i]<<endl;
    }
}
void Meniu::gestionarePTransport() // EROARE
{
    cout<<"\nSelectati pachetul de transport dorit.\n";
    cin>>indiceTrans;
    indiceTrans--;
    if(indiceTrans<0 || indiceTrans>=pacheteTransport.size())
        throw runtime_error("Input invalid.");
    cout<<*pacheteTransport[indiceTrans]<<endl;

    cout<<"1. Rezerva Pachet.\n";
    cout<<"2. Alege Alt Pachet.\n";

    int a;
    cin>>a;
    switch(a)
    {
        case 1:
        {
            try
            {
                gestionareTransport.rezervare(indiceTur);
            }
            catch(EroareRezervare& eroareRezervare)
            {
                cout<<"Acest pachet a fost deja rezervat.\n";
                gestionarePTransport();
            }
            break;
        }
        case 2:
        {
            Meniu* meniu=Meniu::getInstance();
            meniu->afisarePTransport();
            meniu->gestionarePTransport();
            break;
        }
        default:
        {
            cout<<"Comanda invalida!\n";
            gestionarePTransport();
            break;
        }

    }

}
void Meniu::sumaDePlata()  //dynamic_cast ca sa accesez getPret din PTuristic // info despre plata si facturare
{
    float a=0, suma=0;
    if(dynamic_cast<PachetTransport*>(pacheteTransport[indiceTrans]) != NULL)
         a=dynamic_cast<PachetTransport*>(pacheteTransport[indiceTrans])->getPret();
    
    for(int i=0; i<gestionareTuristice.size(); i++) //calculam pretul pentru toate pachetet turistice
        if(gestionareTuristice.getDisponibilitate(i)==false)
            suma+=gestionareTuristice[i].getPret();
    suma+=a;
    cout<<"Suma totala de achitat este: "<<suma;
    cout<<"\nIntroduceti metoda de plata.\n";
    Plata p;
    cin>>p;
    p.setSumaPlatita(suma);
    cont->setPlata(p);
    cout<<endl;

    cout<<"Datele de facturare:\n\n";
    cout<<*cont;
    
}
GestionarePachete<PachetTuristic> Meniu::getGestionareTuristice()
{
    return gestionareTuristice;
}
GestionarePachete<PachetTransport> Meniu::getGestionareTransport()
{
    return gestionareTransport;
}

void Meniu::afisPacheteRezervate()
{
    cout<<"\nPachetele rezervate de dumneavoastra sun: \n\n";
    for(int i=0; i<gestionareTuristice.size(); i++)
        if(gestionareTuristice.getDisponibilitate(i)==false)
            cout<<i+1<<". "<<gestionareTuristice[i]<<endl;
    
    cout<<"1. Mergi la plata.\n";
    cout<<"2. Anuleaza rezervarea unui pachet.\n";
    int a;
    cin>>a;
    Meniu* meniu=Meniu::getInstance();
    switch(a)
    {
        case 1:
        {
            meniu->sumaDePlata();
            break;
        }
        case 2:
        {
            cout<<"Numar pachet: "<<endl;
            cin>>a;
            a--;
            try
            {
                gestionareTuristice.anulareRezervare(a);
            }
            catch(EroareRezervare& eroareRezervare)
            {
                cout<<"Pachetul nu a fost rezervat.\n";
            }
            meniu->afisPacheteRezervate();
            break;
        }
        default:
        {
            cout<<"Comanda invalida!";
            afisPacheteRezervate();
            break;
        }
    }
}

template <class T>
void fTemp(T pachet) //afis tip veh / destinatia
{
    pachet.ft();
}
template <class T>
float f(T pachet) //returneza pretul pachetului
{
    return pachet.getPret();
}


int main()
{
    // PachetTransport pTrans("avion", 12, "abc", 0, 120);
    // PachetTuristic pTur("romania", 130, "12.22.1222","12.12.1212");
    // cout<<f(pTur)<<endl;
    // cout<<f(pTrans)<<endl;
    // fTemp(pTur);
    // fTemp(pTrans);

    Meniu* meniu=Meniu::getInstance();
    //introducere pachete
    {
    set<string> tari = {"Bulgaria", "Canada", "Brazilia", "Franta", "Germania", "China", "Japonia", "India", "Australia", "Egipt"};
    list<string> veh = {"Avion", "Autocar", "Tren", "Avion", "Autocar", "Tren", "Avion", "Autocar", "Tren", "Avion", "Autocar", "Tren",};
    int i=0;
    for(auto tara=tari.begin(); tara!=tari.end(); tara++) //auto == set<string> tara
    {
        string s=*tara;
        PachetTuristic* p=new PachetTuristic(s, (i+12)*876, "20.08.2024", "27.08.2024");
        i++;
        meniu->introducerePacheteTur(*p);
    }
    i=0;
    for(auto vehicul=veh.begin(); vehicul!=veh.end(); vehicul++) //auto == list<string> vehicul
    {
        Vehicul* t=new PachetTransport(*vehicul, i+132, "Abcd", i*2, (i+1)*50);
        meniu->introducerePacheteTrans(*t);
    }
    }
   
    meniu->logIn();
    meniu->afisarePTuristice();
    int k=0;
    while(k==0)
        try
        {
            meniu->gestionarePTuristice();
            k=1;
        }
        catch(runtime_error)
        {
            cout<<"Pachetul nu exista.\nIntroduceti un pachet valid.\n";
        }
    
    meniu->afisarePTransport();
    k=0;
    while(k==0)
        try
        {
            meniu->gestionarePTransport();
            k=1;
        }
        catch(runtime_error)
        {
            cout<<"Pachetul nu exista.\nIntroduceti un pachet valid.\n";
        }
    
    meniu->afisPacheteRezervate();
    

    Meniu::destructor();
    return 0;
}