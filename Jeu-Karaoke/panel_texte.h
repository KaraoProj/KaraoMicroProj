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
    Curseur_Texte* zone_paroles_curseur;
    Curseur_Texte* chanson_curseur;


public:
    explicit Panel_Texte(QWidget *parent = 0);
    ~Panel_Texte();

    virtual void charger_texte(const string&);


    virtual void essai_defilement();

protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);


signals:

public slots:

};

#endif // PANEL_TEXTE_H
