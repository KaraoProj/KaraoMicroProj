#include "panel_texte.h"

Panel_Texte::Panel_Texte(QWidget *parent) :
    QWidget(parent)
{
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::green);
    setPalette(Pal);
    setAutoFillBackground(true);


    zone_paroles=new QTextEdit(this);
    zone_paroles->setReadOnly(true);
    QFont police = zone_paroles->font();
    police.setPixelSize(26);
    QTextDocument* text_doc = zone_paroles->document();
    text_doc->setDefaultFont(police);
    QTextCursor curseur(text_doc);
    curseur.insertText("Han 1995 mon gang, venu pour mailler sans faire le tapin\nTourne ta langue sept fois dans ta grande bouche avant de faire le malin\nJe me demande d'où ils sortent\nSe faisant passer pour mes doyens\nMais on va se défendre avec le rap et le respect des anciens\nCrois moi, aussi vrai que 6 fois 1 fait 6\nJe me tiens à l'écart du vice et reste droit\nCheval de troie fixé sur l'industrie du disque\nIl y a quoi ?\nOn reste les mêmes obsédés par la rime\nUn beat de Lo'\nTu kiffes les flows développés par ma team\nAvis à çeux qui nous prenaient pour des pitres\nOn revient bousiller le jeu\nBien préparer pour le titre");

    saisie =new QLineEdit(this);

    QVBoxLayout *layout_interne = new QVBoxLayout;
    layout_interne->addWidget(zone_paroles);
    layout_interne->addWidget(saisie);
    this->setLayout(layout_interne);

}

Panel_Texte::~Panel_Texte(){
    delete zone_paroles;
    delete saisie;
}
