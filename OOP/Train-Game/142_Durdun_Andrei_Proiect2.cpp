#include <iostream>
#include <string.h>
#include <vector>
#include <conio.h> //butoane
#include <windows.h>
using namespace std;

class Interfata
{
public:
    virtual istream& citire(istream& in)=0;
    virtual ostream& afisare(ostream& out) const=0;
};

class VehiculFeroviar: public Interfata
{
protected:
    static int CONTOR;
    const int id;
    string numeOperator;
public:

    VehiculFeroviar();
    VehiculFeroviar(string numeOperator);
    VehiculFeroviar(const VehiculFeroviar& obj);
    VehiculFeroviar& operator =(const VehiculFeroviar& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    friend istream& operator >>(istream&, VehiculFeroviar&);
    friend ostream& operator <<(ostream&, const VehiculFeroviar&);
    static int getCONTOR()
    {
        return CONTOR;
    }
    ~VehiculFeroviar();

};

class VagonPasageri: virtual public VehiculFeroviar
{
protected:
    static int NRVAGOANE;
    int clasa;
    int nrLocuri;
public:

    VagonPasageri();
    VagonPasageri(string numeOperator, int clasa, int nrLocuri);
    VagonPasageri(const VagonPasageri& obj);
    VagonPasageri& operator =(const VagonPasageri& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    ~VagonPasageri();

    static int getNRVAGOANE()
    {
        return NRVAGOANE;
    }
};

class VagonMarfa: virtual public VehiculFeroviar
{
protected:
    static int NRVAGOANE;
    string tipMarfa;
    double maxKg; //greutate maxima acceptata
public:

    VagonMarfa();
    VagonMarfa(string numeOperator, string tipMarfa, float maxKg);
    VagonMarfa(const VagonMarfa& obj);
    VagonMarfa& operator =(const VagonMarfa& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    ~VagonMarfa();

    static int getNRVAGOANE()
    {
        return NRVAGOANE;
    }
};

class Locomotiva: virtual public VehiculFeroviar
{
protected:
    string tipMotor;
    int caiPutere;
    int nrMaxVagoane;
public:

    Locomotiva();
    Locomotiva(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane);
    Locomotiva(const Locomotiva& obj);
    Locomotiva& operator =(const Locomotiva& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    ~Locomotiva();

    int getNrMaxVagoane() const
    {
        return nrMaxVagoane;
    }

    
};

class TrenMarfar: virtual public Locomotiva, virtual public VagonMarfa
{
protected:
    string conductor;
public:
    TrenMarfar();
    TrenMarfar(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane, string tipMarfa, double maxKg, string conductor);
    TrenMarfar(const TrenMarfar& obj);
    TrenMarfar& operator =(const TrenMarfar& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    int simulareVagoane(int nrMAxVagoane) const; //cati cai avem nevoie pt un nr dde vagoane
    int simularePutere(int caiPutere) const; //cate vagoane puteam avea pt un nr de cai putere
    ~TrenMarfar();


};

class TrenPasageri: virtual public Locomotiva, virtual public VagonPasageri
{
protected:
    string conductor;
    string controlor;
public:
    TrenPasageri();
    TrenPasageri(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane, int clasa, int nrLocuri, string conductor, string controlor);
    TrenPasageri(const TrenPasageri& obj);
    TrenPasageri& operator =(const TrenPasageri& obj);
    virtual istream& citire(istream& in);
    virtual ostream& afisare(ostream& out) const;
    ~TrenPasageri();
    
};

int VehiculFeroviar :: CONTOR=0;

//VEHICUL FEROVIAR
VehiculFeroviar :: VehiculFeroviar():id(1000+CONTOR++)
{
    numeOperator="Anonim";
}
VehiculFeroviar :: VehiculFeroviar(string numeOperator):id(1000+CONTOR++)
{
    this->numeOperator=numeOperator;
}
VehiculFeroviar :: VehiculFeroviar(const VehiculFeroviar& obj):id(obj.id)
{
    numeOperator=obj.numeOperator;
}
VehiculFeroviar :: ~VehiculFeroviar()
{
    CONTOR--;
}
VehiculFeroviar& VehiculFeroviar :: operator =(const VehiculFeroviar& obj)
{
    if(this!=&obj)
    {
        numeOperator=obj.numeOperator;
    }
    return *this;
}
istream& VehiculFeroviar :: citire(istream& in)
{
    cout<<"Nume Operator: ";
    in>>numeOperator;
    return in;
}
ostream& VehiculFeroviar :: afisare(ostream& out) const
{
    out<<"ID: "<<id<<endl;
    out<<"Nume Operator: "<<numeOperator<<endl;
    return out;
}
istream& operator >>(istream& in, VehiculFeroviar& obj)
{
    return obj.citire(in);
}
ostream& operator <<(ostream& out, const VehiculFeroviar& obj)
{
    return obj.afisare(out);
}

//VAGON PASAGERI
int VagonPasageri :: NRVAGOANE=0;
VagonPasageri :: VagonPasageri():VehiculFeroviar()
{
    NRVAGOANE++;
    clasa=2;
    nrLocuri=50;
}
VagonPasageri :: VagonPasageri(string numeOperator, int clasa, int nrLocuri):VehiculFeroviar(numeOperator)
{
    NRVAGOANE++;
    this->clasa=clasa;
    this->nrLocuri=nrLocuri;
}
VagonPasageri :: VagonPasageri(const VagonPasageri& obj):VehiculFeroviar(obj)
{
    clasa=obj.clasa;
    nrLocuri=obj.nrLocuri;
}
VagonPasageri :: ~VagonPasageri()
{
    CONTOR--;
}
VagonPasageri& VagonPasageri :: operator =(const VagonPasageri& obj)
{
    if(this!=&obj)
    {
        VehiculFeroviar :: operator =(obj);
        clasa=obj.clasa;
        nrLocuri=obj.nrLocuri;
    }
    return *this;
}
istream& VagonPasageri ::  citire(istream& in)
{
    this->VehiculFeroviar :: citire(in);
    cout<<"Vagon De Clasa: ";
    in>>clasa;
    cout<<"Numarul De Locuri: ";
    in>>nrLocuri;
    return in;
}
ostream& VagonPasageri ::  afisare(ostream& out) const
{
    this->VehiculFeroviar :: afisare(out);
    out<<"Vagonul Este De Clasa: "<<clasa<<endl;
    out<<"Numarul De Locuri: "<<nrLocuri<<endl;
    return out;
}

//VAGON MARFA
int VagonMarfa :: NRVAGOANE=0;
VagonMarfa :: VagonMarfa():VehiculFeroviar()
{
    NRVAGOANE=0;
    tipMarfa="Nespecificat";
    maxKg=1000;
}
VagonMarfa :: VagonMarfa(string numeOperator, string tipMarfa, float maxKg):VehiculFeroviar(numeOperator)
{
    NRVAGOANE=0;
    this->tipMarfa=tipMarfa;
    this->maxKg=maxKg;
}
VagonMarfa :: VagonMarfa(const VagonMarfa& obj):VehiculFeroviar(obj)
{
    tipMarfa=obj.tipMarfa;
    maxKg=obj.maxKg;
}
VagonMarfa :: ~VagonMarfa()
{
    CONTOR--;
}
VagonMarfa& VagonMarfa :: operator =(const VagonMarfa& obj)
{
    if(this!=&obj)
    {
        VehiculFeroviar :: operator =(obj);
        tipMarfa=obj.tipMarfa;
        maxKg=obj.maxKg;
    }
    return *this;
}
istream& VagonMarfa ::  citire(istream& in)
{
    this->VehiculFeroviar :: citire(in);
    cout<<"Tip Marfa: ";
    in>>tipMarfa;
    cout<<"Greutatea Maxima Admisa: ";
    in>>maxKg;
    return in;
}
ostream& VagonMarfa ::  afisare(ostream& out) const
{
    this->VehiculFeroviar :: afisare(out);
    out<<"Tip Marfa: "<<tipMarfa<<endl;
    out<<"Greutatea Maxima Admisa: "<<maxKg<<endl;
    return out;
}
int TrenMarfar :: simulareVagoane(int nrMaxVagoane) const //cati cai avem nevoie pt un nr dde vagoane
    {
        int vagCal; //vagon pe cal putere
        vagCal=this->caiPutere/this->nrMaxVagoane;
        return nrMaxVagoane*vagCal;

    }
int TrenMarfar :: simularePutere(int caiPutere) const //cate vagoane puteam avea pt un nr de cai putere
    {
        int vagCal; //vagon pe cal putere
        vagCal=this->caiPutere/this->nrMaxVagoane;//nr de cai pe vagon
        return caiPutere/vagCal;

    }

//LOCOMOTIVA
Locomotiva :: Locomotiva():VehiculFeroviar()
{
    tipMotor="Nespecificat";
    caiPutere=100;
    nrMaxVagoane=10;
}
Locomotiva :: Locomotiva(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane):VehiculFeroviar(numeOperator)
{
    this->tipMotor=tipMotor;
    this->caiPutere=caiPutere;
    this->nrMaxVagoane=nrMaxVagoane;
}
Locomotiva :: Locomotiva(const Locomotiva& obj):VehiculFeroviar(obj)
{
    tipMotor=obj.tipMotor;
    caiPutere=obj.caiPutere;
    nrMaxVagoane=obj.nrMaxVagoane;
}
Locomotiva :: ~Locomotiva()
{
    CONTOR--;
}
Locomotiva& Locomotiva :: operator =(const Locomotiva& obj)
{
    if(this!=&obj)
    {
        VehiculFeroviar :: operator =(obj);
        tipMotor=obj.tipMotor;
        caiPutere=obj.caiPutere;
        nrMaxVagoane=obj.nrMaxVagoane;
    }
    return *this;
}
istream& Locomotiva ::  citire(istream& in)
{
    this->VehiculFeroviar :: citire(in);
    cout<<"Tip Motor: ";
    in>>tipMotor;
    cout<<"Numarul De Cai Putere: ";
    in>>caiPutere;
    cout<<"Numarul Maxim De Vagoane Admise: ";
    in>>nrMaxVagoane;
    return in;
}
ostream& Locomotiva ::  afisare(ostream& out) const
{
    this->VehiculFeroviar :: afisare(out);
    out<<"Tip Motor: "<<tipMotor<<endl;
    out<<"Numarul De Cai Putere: "<<caiPutere<<endl;
    out<<"Numarul Maxim De Vagoane Admise: "<<nrMaxVagoane<<endl;
    return out;
}

//TrenPasageri
TrenPasageri :: TrenPasageri():VehiculFeroviar(), Locomotiva(),VagonPasageri()
{
    conductor="Anonim";
    controlor="Anonim";
}
TrenPasageri :: TrenPasageri(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane, int clasa, int nrLocuri, string conductor, string controlor):VehiculFeroviar(numeOperator), Locomotiva(numeOperator,tipMotor,caiPutere,nrMaxVagoane),VagonPasageri(numeOperator,clasa,nrLocuri)
{
    this->conductor=conductor;
    this->controlor=controlor;
}
TrenPasageri :: TrenPasageri(const TrenPasageri& obj):VehiculFeroviar(obj), Locomotiva(obj),VagonPasageri(obj)
{
    conductor=obj.conductor;
    controlor=obj.controlor;
}
TrenPasageri :: ~TrenPasageri()
{
    CONTOR--;
}
TrenPasageri& TrenPasageri :: operator =(const TrenPasageri& obj)
{
    if(this!=&obj)
    {
        VehiculFeroviar::operator=(obj);
        Locomotiva::operator =(obj);
        VagonPasageri::operator =(obj);
        conductor=obj.conductor;
        controlor=obj.controlor;
    }
    return *this;
}
istream& TrenPasageri :: citire(istream& in)
{
    this->Locomotiva::citire(in);
    cout<<"Vagon De Clasa: ";
    in>>clasa;
    cout<<"Numarul De Locuri: ";
    in>>nrLocuri;
    cout<<"Nume Conductor: ";
    in>>conductor;
    cout<<"Nume Controlor: ";
    in>>controlor;
    return in;
    
}
ostream& TrenPasageri :: afisare(ostream& out) const
{
    this->Locomotiva :: afisare(out);
    out<<"Vagon de Clasa: "<<clasa<<endl;
    out<<"Numarul De Locuri: "<<nrLocuri<<endl;
    out<<"Nume Conductor: "<<conductor<<endl;
    out<<"Nume Controlor: "<<controlor<<endl;
    return out;
}

//TrenMarfar
TrenMarfar :: TrenMarfar():VehiculFeroviar(), Locomotiva(),VagonMarfa()
{
    conductor="Anonim";
}
TrenMarfar :: TrenMarfar(string numeOperator, string tipMotor, int caiPutere, int nrMaxVagoane, string tipMarfa, double maxKg, string conductor):VehiculFeroviar(numeOperator), Locomotiva(numeOperator,tipMotor,caiPutere,nrMaxVagoane),VagonMarfa(numeOperator,tipMarfa,maxKg)
{
    this->conductor=conductor;
}
TrenMarfar :: TrenMarfar(const TrenMarfar& obj):VehiculFeroviar(obj), Locomotiva(obj),VagonMarfa(obj)
{
    conductor=obj.conductor;
}
TrenMarfar :: ~TrenMarfar()
{
    CONTOR--;
}
TrenMarfar& TrenMarfar :: operator =(const TrenMarfar& obj)
{
    if(this!=&obj)
    {
        VehiculFeroviar::operator=(obj);
        Locomotiva::operator =(obj);
        VagonMarfa::operator =(obj);
        conductor=obj.conductor;
    }
    return *this;
}
istream& TrenMarfar :: citire(istream& in)
{
    this->Locomotiva::citire(in);
    cout<<"Tip Marfa: ";
    in>>tipMarfa;
    cout<<"Numarul Maxim De Kg Admise: ";
    in>>maxKg;
    cout<<"Nume Conductor: ";
    in>>conductor;
    return in;
    
}
ostream& TrenMarfar :: afisare(ostream& out) const
{
    this->Locomotiva :: afisare(out);
    out<<"Tip Marfa: "<<tipMarfa<<endl;
    out<<"Numarul Maxim De Kg Admise: "<<maxKg<<endl;
    out<<"Nume Conductor: "<<conductor<<endl;
    return out;
}

//JOC
class Game
{
private:
    bool isGameOver;
    int width, height;

    int locomotivaX, locomotivaY;
    int carburantX, carburantY;
    int score;

    vector<int> vagoaneX, vagoaneY;
    int vagoaneLenght;

    enum eDirection
    {
        STOP=0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    eDirection dir;

public:
    bool getIsGameOver() const
    {
        return isGameOver;
    }
    int getScore() const
    {
        return score;
    }
    void setScore(int score)
    {
        this->score=score;
    }
    int getWidth() const
    {
        return width;
    }
    void setVagoaneLenght(int lenght)
    {
        vagoaneLenght=lenght;
    }
    void Setup();
    void Print();
    void Input();
    void Logic();
};

void Game::Setup()
{
    isGameOver=false;
    score=0;
    width=40;
    height=22;
    dir=STOP;
    score=20;

    locomotivaX=width/2; //plasez sarpele in mijol
    locomotivaY=height/2;

    srand(time(NULL)); //generaza numere aleatoare cu valoare de pornire bazata pe timpul curent
    carburantX=rand() % width; // ca sa nu depaseaca width
    carburantY=rand() % height; 

    vagoaneX.resize(100);
    vagoaneY.resize(100);
}

void Game::Print()
{
    system("cls"); //sterge ecranul

    for(int i=0; i<width+2; i++)
        cout<<"-";
    cout<<endl;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(j==0)
                cout<<"|";

            if(i==locomotivaY && j==locomotivaX)
                cout<<"@";//capul
            else
                if(i==carburantY && j==carburantX)
                    cout<<"#";//carburant
            else
            {
                bool isvagoaneCoord=false;
                for(int k=0; k<vagoaneLenght; k++)
                {
                    if(vagoaneX[k]==j && vagoaneY[k]==i)
                    {
                        cout<<"O";//vagoane
                        isvagoaneCoord=true;
                    }
                }
                if(!isvagoaneCoord)
                    cout<<" ";
            }
            if(j==width-1)
                cout<<"|";//partea dreapta
        }   
        cout<<endl;
    }
    for(int i=0; i<width+2; i++)
            cout<<"-";

        cout<<endl<<endl;
        cout<<"Nivel Carburant: "<<score;
        cout<<endl<<endl;
}

void Game::Input()
{
    if(_kbhit()) //keyboard hit
    {
        switch(_getch()) //get character (ce caracter am apasat)
        {
            case 72:
            {
                dir=UP;
                break;
            }
            case 77:
            {
                dir=RIGHT;
                break;
            }
            case 75:
            {
                dir=LEFT;
                break;
            }
            case 80:
            {
                dir=DOWN;
                break;
            }
            case 27: //ESC 
            {
                isGameOver=true;
                break;
            }
            
        }
    }
}

void Game::Logic()
{
    int prevX=vagoaneX[0];
    int prevY=vagoaneY[0];
    int prev2X, prev2Y; //elem de dinaintea ultimelor

    vagoaneX[0]=locomotivaX;
    vagoaneY[0]=locomotivaY;

    for(int i=1; i<vagoaneLenght; i++)
    {
        prev2X=vagoaneX[i];
        prev2Y=vagoaneY[i];

        vagoaneX[i]=prevX;
        vagoaneY[i]=prevY;

        prevX=prev2X;
        prevY=prev2Y;
    }

    switch(dir)
    {
        case LEFT:
        {
            locomotivaX--;
            break;
        }
        case RIGHT:
        {
            locomotivaX++;
            break;
        }
        case UP:
        {
            locomotivaY--;
            break;
        }
        case DOWN:
        {
            locomotivaY++;
            break;
        }
    }
    // in caz ca depaseste limita din dreapta, sa intre inapoi prin stanga...
    if(locomotivaX>=width)
        locomotivaX=0;
    if(locomotivaX<0)
        locomotivaX=width-1;
    if(locomotivaY>=height)
        locomotivaY=0;
    if(locomotivaY<0)
        locomotivaY=height-1;

    //adaugam carburantul
    if(locomotivaX==carburantX && locomotivaY==carburantY)
    {
        score+=10;

        //adaugam carburant
        srand(time(NULL));
        carburantX=rand() % width;
        carburantY=rand() % height;
    }
   static int ct=0;
   ct++;
   if(ct==5)
   {
    ct=0;
    score--;
   }

   if(score<0)
    isGameOver=true;
    
}

void incepeJoc()
{
    int a=3;
    for(int i=0;i<3;i++)
    {system("cls");
    cout<<"Jocul Va Incepe In: "<<a--<<endl;
    Sleep(700);
    }
    system("cls");
    cout<<"START\n";
    Sleep(500);
}


int main()
{
    vector<VehiculFeroviar*> vagoane;
    Locomotiva locomotiva;
    cout<<"\nFORMEAZA TRENUL:\n"<<endl;
    cout<<"\nIntroduceti Locomotiva: \n"<<endl;
    cin>>locomotiva;
    cout<<endl;
    cout<<"\n1. Introducei Vagoane Pasageri.";
    cout<<"\n2. Introduceti Vagoane Marfa.\n";

    int v;
    cin>>v;
    switch(v)
    {
        case 1:
        {
            int ok,ct=0;
            do
            {
                ct++;
                VehiculFeroviar *p= new VagonPasageri;
                cin>>*p;
                vagoane.push_back(p);
                if(ct<locomotiva.getNrMaxVagoane())
                {
                    cout<<"\n1. Introduceti Inca Un Vagon.\n";
                    cin>>ok;
                }
                else
                    {cout<<"\nLocomotiva Nu Mai Suporta Vagoane.\n";
                    Sleep(1000);
                    ok=0;}
            }
            while(ok==1);
            break;
        }
        case 2:
        {
            int ok,ct=0;
            do
            {
            ct++;
            VehiculFeroviar *p= new VagonMarfa;
            cin>>*p;
            vagoane.push_back(p);
            if(ct<locomotiva.getNrMaxVagoane())
            {
                cout<<"\n1. Introduceti Inca Un Vagon.\n";
                cin>>ok;
            }
            else
                {cout<<"\nLocomotiva Nu Mai Suporta Vagoane.\n";
                Sleep(500);
                ok=0;}
            }
            while(ok==1);
            break;
        }
    }

    
    incepeJoc();

    Game game;
    
    game.setVagoaneLenght(VehiculFeroviar::getCONTOR()-1);
    game.Setup();

    while(!game.getIsGameOver())
    {
        game.Print();
        game.Input();
        game.Logic();
        Sleep(50); //incetineste executia programului cu 100ms
    }
    system("cls");
    cout<<"\nAi Pierdut!\n\n";

    
    return 0;
}
