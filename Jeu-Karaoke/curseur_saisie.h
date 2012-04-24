#ifndef CURSEUR_SAISIE_H
#define CURSEUR_SAISIE_H

#include <QTextCursor>
#include "champ_saisie.h"

class Curseur_Saisie : public QTextCursor
{
public:
    explicit Curseur_Saisie(Champ_Saisie *parent = 0);

    virtual void init();
    virtual void selectionner_mot();

signals:

public slots:

};

#endif // CURSEUR_SAISIE_H
