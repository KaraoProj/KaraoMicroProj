#include "panel_texte.h"

Panel_Texte::Panel_Texte(QWidget *parent) :
    QWidget(parent)
{
    // Background du Panel
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::green);
    setPalette(Pal);
    setAutoFillBackground(true);

    // Curseur_Texte € QTextDocument € QTextEdit € Panel_Texte
    zone_paroles = new QTextEdit(this);
    zone_paroles->setReadOnly(true);

    zone_paroles_doc = zone_paroles->document();

    //zone_paroles_doc->setDefaultStyleSheet("../Jeu-Karaoke/GameFiles/paroles.css")
    //cout << zone_paroles_doc->defaultStyleSheet().toStdString() << endl;


    zone_paroles_curseur = new Curseur_Texte(zone_paroles_doc);
    chanson_curseur = new Curseur_Texte(zone_paroles_doc);

    QFont police = zone_paroles->font();
    police.setPixelSize(36);
    zone_paroles_doc->setDefaultFont(police);

    //zone_paroles_curseur->insertHtml("<body><div class='lecture'>Han 1995 <b> mon gang </b>,</div> venu pour mailler sans faire le tapin<br>Tourne ta langue sept fois dans ta grande bouche avant de faire le malin<br>Je me demande d'où ils sortent<br>Se faisant passer pour mes doyens<br>Mais on va se défendre avec le rap et le respect des anciens<br>Crois moi, aussi vrai que 6 fois 1 fait 6<br>Je me tiens à l'écart du vice et reste droit<br>Cheval de troie fixé sur l'industrie du disque<br>Il y a quoi ?<br>On reste les mêmes obsédés par la rime<br>Un beat de Lo'<br>Tu kiffes les flows développés par ma team<br>Avis à çeux qui nous prenaient pour des pitres<br>On revient bousiller le jeu<br>Bien préparer pour le titre");
    //zone_paroles_curseur->insertHtml("<br>LOL<br>LOOOOOL<br>LOOOOOOOOOOOoooOOOOl</body>");


    saisie =new QLineEdit(this);

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
    /*if(e->key()==0x01000033){ // F4
        QString aux;
        QTextCharFormat format_test;

        format_test.setUnderlineColor(Qt::red);
        format_test.setFontUnderline(true);
        format_test.setFontWordSpacing(10);

        aux = zone_paroles_curseur->selectedText();

        zone_paroles_curseur->selectedText().remove(0,aux.size());
        zone_paroles_curseur->insertText(aux,format_test);

    }*/
    if(e->key()==0x0100003b){ //F12
        chanson_curseur->init();
        zone_paroles_curseur->init();
    }
}

void Panel_Texte::keyReleaseEvent(QKeyEvent *e){

}


