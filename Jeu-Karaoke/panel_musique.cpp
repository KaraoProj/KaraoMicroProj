#include "panel_musique.h"

Panel_Musique::Panel_Musique(QWidget *parent) :
    QWidget(parent)
{

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setPalette(Pal);
    setAutoFillBackground(true);


    // Gestion du fichier audio
    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory,this);
    mediaObject = new Phonon::MediaObject(this);

    mediaObject->setTickInterval(1000);                                  // Emission d'un tick toutes les secondes
    connect(mediaObject, SIGNAL(tick(qint64)),this, SLOT(tick(qint64))); // On va passer le temps écoulé (tick) à l'attribut "temps"
    //connect(mediaObject, SIGNAL(tick(qint64)),

    source = "../Jeu-Karaoke/Sound/1995_LaSuite.wav";
    mediaObject->setCurrentSource(source);
    titre = "La Suite";
    artiste = "1995";

    Phonon::createPath(mediaObject,audioOutput);    //Relie le gestionnaire du son au diffuseur de son

    setActions();
    setStateMachine();
    setUI();
}

Panel_Musique::~Panel_Musique()
{

}

void Panel_Musique::tick(qint64 time){
    QTime displayTime(00, ( time / 60000 ) % 60, ( time / 1000 ) % 60,0);
    temps->display(displayTime.toString("mm:ss"));
    suiveurMS =time/1000;
    qint64 index;
    qint64 i=0 ;
    while(listeDeparts[i]<suiveurMS){
        i=i+1;
        index=i;
        }
    cout<<"index avant emit:" <<i<<endl;
    if(i==0) emit topDepart(i);
    else emit topDepart(i-1);
}

void Panel_Musique::qActionsManager(){

    if(sender() == playState){
        playAction->setEnabled(false);
        pauseAction->setEnabled(true);
        stopAction->setEnabled(true);
    }
    if(sender() == pauseState){
        playAction->setEnabled(true);
        pauseAction->setEnabled(false);
        stopAction->setEnabled(true);
    }
    if(sender() == stopState){
        playAction->setEnabled(true);
        pauseAction->setEnabled(false);
        stopAction->setEnabled(false);
        temps->display("00:00");
    }
}

void Panel_Musique::setActions(){

    playAction = new QAction(QIcon(":/images/play.png"),tr("Play"),this);
    playAction->setDisabled(false);
    pauseAction = new QAction(QIcon(":/images/pause.png"),tr("Pause"),this);
    pauseAction->setDisabled(true);
    stopAction = new QAction(QIcon(":/images/stop.png"),tr("Stop"),this);
    stopAction->setDisabled(true);

}

void Panel_Musique::setStateMachine(){

    mac = new QStateMachine() ;
    playState = new QState();
    pauseState = new QState();
    stopState = new QState();

    playState->addTransition(pauseAction,SIGNAL(triggered()),pauseState);
    playState->addTransition(stopAction,SIGNAL(triggered()),stopState);

    pauseState->addTransition(playAction,SIGNAL(triggered()),playState);
    pauseState->addTransition(stopAction,SIGNAL(triggered()),stopState);

    stopState->addTransition(playAction,SIGNAL(triggered()),playState);
    stopState->addTransition(pauseAction,SIGNAL(triggered()),pauseState);

    mac->addState(playState);
    mac->addState(pauseState);
    mac->addState(stopState);
    mac->setInitialState(stopState);

    QObject::connect(playState, SIGNAL(entered()), mediaObject, SLOT(play()));
    QObject::connect(playState,SIGNAL(entered()), this, SLOT(qActionsManager()));
    QObject::connect(pauseState, SIGNAL(entered()), mediaObject, SLOT(pause()));
    QObject::connect(pauseState,SIGNAL(entered()), this, SLOT(qActionsManager()));
    QObject::connect(stopState, SIGNAL(entered()), mediaObject, SLOT(stop()));
    QObject::connect(stopState,SIGNAL(entered()), this, SLOT(qActionsManager()));

    mac->start();
}

void Panel_Musique::debug(){
    qDebug() <<"DEBUG";

}

void Panel_Musique::setUI(){

    QHBoxLayout * principalLayout= new QHBoxLayout;     // Layout principal

    QVBoxLayout *  interactiveLayout = new QVBoxLayout; // Layout d'interaction avec boutons, volume et barre de lecture

    barreLecture = new Phonon::SeekSlider(this);
    barreLecture->setMediaObject(mediaObject);          // On relie la barre de lecture au mediaobject

    QHBoxLayout * controlLayout = new QHBoxLayout;      // Boutons + Volume

    QToolBar * barreControle = new QToolBar;            // Barre d'outils Pause, Play, Stop
    barreControle->addAction(playAction);
    barreControle->addAction(pauseAction);
    barreControle->addAction(stopAction);

    barreVolume = new Phonon::VolumeSlider(this);
    barreVolume->setFixedSize(200,20);
    barreVolume->setAudioOutput(audioOutput);

    controlLayout->addWidget(barreControle);
    controlLayout->addWidget(barreVolume);

    interactiveLayout->addWidget(barreLecture);
    interactiveLayout->addLayout(controlLayout);

    QVBoxLayout* informationLayout= new QVBoxLayout;    // Barre d'information : Titre, temps écoulé

    QLabel* titreLabel = new QLabel(titre);                 // Titre
    QLabel* artisteLabel = new QLabel(artiste);             // Artiste
    temps = new QLCDNumber;

    informationLayout->addWidget(titreLabel);
    informationLayout->addWidget(artisteLabel);
    informationLayout->addWidget(temps);


    principalLayout->addLayout(interactiveLayout);
    principalLayout->addLayout(informationLayout);


    this->setLayout(principalLayout);
}

void Panel_Musique :: keyPressEvent (QKeyEvent *e){

    if (e->key()== 82 ) // r
        cout << this->suiveurMS <<endl;
}

void Panel_Musique :: keyReleaseEvent(QKeyEvent *e){

}


