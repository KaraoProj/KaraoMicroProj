#include "panel_texte.h"

Panel_Texte::Panel_Texte(QWidget *parent) :
    QWidget(parent)
{
    // Background du Panel
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setPalette(Pal);
    setAutoFillBackground(true);

    // Curseur_Texte € QTextDocument € QTextEdit € Panel_Texte
    zone_paroles = new QTextEdit(this);
    zone_paroles->setReadOnly(true);

    zone_paroles_doc = zone_paroles->document();

    zone_paroles_curseur = new Curseur_Texte(zone_paroles_doc);
    chanson_curseur = new Curseur_Texte(zone_paroles_doc);

    QFont police = zone_paroles->font();
    police.setPixelSize(36);
    zone_paroles_doc->setDefaultFont(police);

    saisie = new Champ_Saisie(this);

    QVBoxLayout *layout_interne = new QVBoxLayout;
    layout_interne->addWidget(zone_paroles);
    layout_interne->addWidget(saisie);
    this->setLayout(layout_interne);

}

Panel_Texte::~Panel_Texte(){
    delete zone_paroles;
    delete saisie;
    delete zone_paroles_doc;
    delete zone_paroles_curseur;
}

void Panel_Texte::charger_texte(const string& chemin){



    ifstream monFlux(chemin.c_str());                                               //Ouverture d'un fichier en lecture

    if(monFlux)                                                                     // Si le fichier s'est ouvert
    {
        string nom_chanson;
        string texte;
        string aux;

        //Pour l'instant on en fait rien
        getline(monFlux, nom_chanson);
        getline(monFlux, aux);

        zone_paroles->clear();
        zone_paroles_curseur->init();


        while(getline(monFlux, texte))                                             //Tant qu'on n'est pas a la fin, on lit
        {
            QString texte_ok(texte.c_str());
            zone_paroles_curseur->insertHtml("<p style='color:#A1B5F6;font-size:large;word-spacing:20'>" + texte_ok + "<br>");

        }





    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }


    monFlux.close();


}

void Panel_Texte::essai_defilement(){
    zone_paroles_curseur->init();
    chanson_curseur->init();
    for(int i(0); i<50; i++){
        cout << "mot n°:" << i+1 << endl;
        for(double time(0); time<1000000000; time++){}
        chanson_curseur->avancer();
    }


}

void Panel_Texte::keyPressEvent(QKeyEvent *e){
    if(e->key()==0x01000030){ //F1
        essai_defilement();
    }
    if(e->key()==0x01000031){ // F2(Left)
        zone_paroles_curseur->avancer();
    }
    if(e->key()==0x01000032){ // F3(Right) -> Bug
        zone_paroles_curseur->movePosition(QTextCursor::MoveOperation(8),QTextCursor::MoveMode(0),1);
        zone_paroles_curseur->selectionner_mot();
    }
    if(e->key()==0x0100003b){ //F12
        chanson_curseur->init();
        zone_paroles_curseur->init();
    }
}

void Panel_Texte::keyReleaseEvent(QKeyEvent *e){

}


