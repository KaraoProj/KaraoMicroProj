#ifndef PANEL_MUSIQUE_H
#define PANEL_MUSIQUE_H

#include <QWidget>
#include <phonon/mediaobject.h>
#include <phonon/seekslider.h>
#include <phonon/audiooutput.h>
#include <phonon/volumeslider.h>
#include <QAction>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QState>
#include <QStateMachine>
#include <QtDebug>
#include <iostream>
#include <QLCDNumber>
#include <QTime>
#include <QToolBar>
#include <QKeyEvent>
#include <QEvent>


using namespace std ;

class Panel_Musique : public QWidget
{
    Q_OBJECT
public:
    explicit Panel_Musique(QWidget *parent = 0);

    Phonon::SeekSlider *barreLecture;   // Barre de lecture
    Phonon::MediaObject *mediaObject;   // Permet de gérer la musique
    Phonon::AudioOutput *audioOutput;   // Permet d'écouter la musique
    Phonon::VolumeSlider *barreVolume;  // Barre de volume
    QAction *playAction;                ///
    QAction *pauseAction;               // Boutons play, pause, stop
    QAction *stopAction;                ///
    QString source;
    QStateMachine * mac;                        // Machine à état
    QState * playState,*pauseState,*stopState;
    QLCDNumber *temps;                  // Affichage du temps de lecture
    QString artiste,titre;
    qint64 suiveurMS ;                  // Pour la synchronisation
    /////////////////////
    QList<qint64> listeDeparts;        // Liste des top pour chaque ligne
/////////////////////////

public:
    ~Panel_Musique();

    void setUI();               // Interface Utilisateur
    void setActions();          // Initilialise les QActions
    void setStateMachine();      // Initialise la machine à état
    void chargerListeDeparts(QList<qint64> _listeDeparts){ listeDeparts = _listeDeparts;};

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
/////////////
signals:
    void topDepart(qint64 top);
//////////////
public slots:
void debug();
void tick(qint64 time);     // Envoie le temps écoulé de mediaObject vers  l'afficheur LCD
void qActionsManager();

};

#endif // PANEL_MUSIQUE_H
