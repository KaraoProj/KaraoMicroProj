#ifndef CHAMP_SAISIE_H
#define CHAMP_SAISIE_H

#include <QLineEdit>
#include <QAction>
//#include "panel_texte.h"


class Champ_Saisie : public QLineEdit
{
    Q_OBJECT
    //Panel_Texte *zone_texte_parent;



public:
    Champ_Saisie(QWidget *parent = 0/*, Panel_Texte* _parent =0*/);

    virtual ~Champ_Saisie();

    virtual void traiterSaisie(const QString &);

signals:
    void ecrireMot(const QString&);

public slots:
    virtual void validationMot();

};

#endif // CHAMP_SAISIE_H
