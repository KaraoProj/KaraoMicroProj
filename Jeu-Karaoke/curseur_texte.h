#ifndef CURSEUR_TEXTE_H
#define CURSEUR_TEXTE_H

#include <QTextCursor>
#include <iostream>


class Curseur_Texte : public QObject, public QTextCursor
{

    Q_OBJECT

public:

    explicit Curseur_Texte(QTextDocument * document=0);

    virtual ~Curseur_Texte();

    virtual void dire_position();
    virtual void init();
    virtual void selectionner_mot();
    virtual void selectionner_ligne();






    /*virtual void avancer_coloriser();
    virtual void remplacer_mot(const QString&);
    virtual void souligner_mot_a_suivre();*/


    //virtual void setFormat_mot(const int, const QString&);

signals:
    void demande_position();

public slots:


};

#endif // CURSEUR_TEXTE_H
