#ifndef CHAMP_SAISIE_H
#define CHAMP_SAISIE_H

#include <QLineEdit>
#include <QAction>

class Champ_Saisie : public QLineEdit
{
    Q_OBJECT

    QAction* validationAction;


public:
    explicit Champ_Saisie(QWidget *parent = 0);

    virtual ~Champ_Saisie();


signals:


public slots:
    virtual void validationMot();

};

#endif // CHAMP_SAISIE_H
