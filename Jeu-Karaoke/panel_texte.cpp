#include "panel_texte.h"

Panel_Texte::Panel_Texte(QWidget *parent) :
    QWidget(parent)
{
    //////
    indexLigne=0;
    indexLigneEcriture=0;
    /////
    listeStyle[0]=3;

    // Background du Panel
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setPalette(Pal);
    setAutoFillBackground(true);

    // Curseur_Texte € QTextDocument € QTextEdit € Panel_Texte
    zone_paroles = new QTextEdit(this);
    zone_paroles->setReadOnly(true);

    zone_paroles_doc = zone_paroles->document();

    curseur = new Curseur_Texte(zone_paroles_doc);

    // Liste de styles
    baliseStyle.push_back("color:#A1B5F6;font-size:large;word-spacing:20'>"); // style par défaut
    baliseStyle.push_back("color:red;font-size:large;word-spacing:50'>"); // style pour curseur musique
    baliseStyle.push_back("color:#A1B5F6;font-size:large;word-spacing:20;text-decoration:underline;'>"); // style pour curseur saisie
    baliseStyle.push_back("color:#red;font-size:large;word-spacing:50;text-decoration:underline;'>"); // styles cumulés

    //
    QFont police = zone_paroles->font();
    police.setPixelSize(36);
    zone_paroles_doc->setDefaultFont(police);

    saisie = new Champ_Saisie(this);

    QVBoxLayout *layout_interne = new QVBoxLayout;
    layout_interne->addWidget(zone_paroles);
    layout_interne->addWidget(saisie);
    this->setLayout(layout_interne);

    QObject::connect(saisie,SIGNAL(ecrireMot(const QString&)),this,SLOT(remplacerLigne(const QString&)));
}

Panel_Texte::~Panel_Texte(){
    delete zone_paroles;
    delete saisie;
    delete zone_paroles_doc;
    delete curseur;
}

void Panel_Texte::charger_texte(){


    zone_paroles->clear();
    curseur->init();

    for(int i=0;i<listeLigne.size();i++){
        curseur->insertHtml("<p style='color:#A1B5F6;font-size:large;word-spacing:20'>" + listeLigne[i] + "<br>");
    }


}

void Panel_Texte::re_ecrire(){
    QString texte="";
    int style_numero=0;
    QString style="" ;
    zone_paroles->clear();
    curseur->init();
    cout << "re_ecrire middle" << endl;

    for(int i(0);i<listeLigne.size();i++)
    {
        texte=listeLigne[i];
        style_numero=listeStyle[i];
        style=baliseStyle[style_numero];
        curseur->insertHtml("<p style='" + style + texte + "<br>");
    }


}

// Chargement de la liste de lignes et initialisation de la listeEdit
void Panel_Texte::chargerListeLignes(QList<QString>_listeLigne){

    listeLigne = _listeLigne ;


    for(int i=0 ; i<listeLigne.size() ; i++){
        cout<<"no"<<endl;
        listeStyle.append(0);
        cout<<"yes"<<endl;
        listeEdit.append("");
        QStringList listeTemp = listeLigne[i].split(" ");
        for(int j = 0;j< listeTemp.size() ; j++){
            QString mot ="";
            for(int k=0;k<listeTemp[j].size();k++)
                mot=mot+"_";
            listeEdit[i] = listeEdit[i] + mot+ " ";
        }
    }

    for(int i=0 ; i<listeLigne.size() ; i++){
        cout<<listeLigne[i].toStdString()<<endl;
        cout<<listeEdit[i].toStdString()<<endl;
    }
    charger_texte();

}

void Panel_Texte::afficherLigne(qint64 index){
    cout << "DEBUG" << endl;
    cout<<"indexLigne:"<<indexLigne<<endl;

    cout<<"indexRecu:"<<index<<endl;
    if(index!=indexLigne){

        if(listeStyle[indexLigne]==1)    listeStyle[indexLigne]=0;
        else if(listeStyle[indexLigne]==3)    listeStyle[indexLigne]=2;

        indexLigne=index;
        cout <<listeLigne.at(index).toStdString()<<endl;

        if(listeStyle[indexLigne]==0)    listeStyle[indexLigne]=1;
        else if(listeStyle[indexLigne]==2)    listeStyle[indexLigne]=3;

        refresh();
    }
}

void Panel_Texte::keyPressEvent(QKeyEvent *e){

    if(e->key()==0x41){ //A
        aLaLigne();

    }
    if(e->key()==0x51){ //Q

    }
    if(e->key()==0x5a){ //Z

    }
    if(e->key()==0x53){ //S

    }


    if(e->key()==0x0100003b){ //F12
        curseur->init();
    }
}

void Panel_Texte::refresh(){
    re_ecrire();
}

void Panel_Texte::remplacerLigne(const QString & ligne_new){

    listeEdit.replace(indexLigneEcriture,ligne_new);
    aLaLigne();

}

void Panel_Texte::aLaLigne(){
    if(listeStyle[indexLigneEcriture]==2)    listeStyle[indexLigneEcriture]=0;
    else if(listeStyle[indexLigneEcriture]==3)    listeStyle[indexLigneEcriture]=1;

    indexLigneEcriture++;

    if(listeStyle[indexLigneEcriture]==0)    listeStyle[indexLigneEcriture]=2;
    else if(listeStyle[indexLigneEcriture]==1)    listeStyle[indexLigneEcriture]=3;

    refresh();
}
