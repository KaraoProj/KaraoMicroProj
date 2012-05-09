#ifndef PANEL_TEXTE_H
#define PANEL_TEXTE_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <fstream>
#include <iostream>
#include <QString>
#include <QKeyEvent>
#include <QTextCharFormat>


#include "curseur_texte.h"
#include "champ_saisie.h"

using namespace std;

class Panel_Texte : public QWidget
{
    Q_OBJECT



    Champ_Saisie* saisie;
    QTextEdit* zone_paroles;
    QTextDocument* zone_paroles_doc;
    Curseur_Texte* curseur;

    ////////////////////////
    QList<QString> listeLigne;
    QList<int> listeStyle;
    QList<QString> listeEdit;
    QList<QString> baliseStyle;
    qint64 indexLigne;
    qint64 indexLigneEcriture;
    ////////////////////////

public:
    explicit Panel_Texte(QWidget *parent = 0);
    virtual ~Panel_Texte();

     void chargerListeLignes(QList<QString> _listeLigne);

    virtual void charger_texte();
    virtual void re_ecrire();

     virtual void aLaLigne();

   // virtual void essai_defilement();

protected:
    void keyPressEvent(QKeyEvent *);

/////////////
signals:

public slots:
    void afficherLigne(qint64 index);
    virtual void refresh();
    virtual void remplacerLigne(const QString &);
//////////////

};

#endif // PANEL_TEXTE_H
