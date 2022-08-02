#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "noteviewpane.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GLOBAL_FUNC_RUN
    CANMOVE

    InitMainPaneLayout();

    QString title = "top";

    m_pNoteViewPane = new NoteViewPane;

//    m_pNoteViewPane->show();

   m_listNoteItems = new QListWidget;

   int nCount = m_listNoteItems->count();

    QListWidgetItem *item1 = new QListWidgetItem();
    item1->setSizeHint(QSize(10, 50));
    item1->setData(Qt::UserRole, NOTE);

     m_listNoteItems->addItem(item1);

     m_listNoteItems->setCurrentRow(nCount);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitMainPaneLayout()
{
//    QHBoxLayout *mainLayout = new QHBoxLayout(m_pMainPane);

//    mainLayout->addWidget(m_pNoteViewPane);
//    mainLayout->setMargin(1);
//    mainLayout->setSpacing(0);
}

void MainWindow::CreateAllChildWnd()
{
//    NEW_OBJECT(m_pMainPane, QWidget);

//    NEW_OBJECT(m_pNoteViewPane, NoteViewPane);

}

void MainWindow::InitCtrl()
{

}

void MainWindow::InitSolts()
{

}

void MainWindow::Relayout()
{

}

void MainWindow::PlayCloseAnimation()
{
    setDisabled(true);
    setMinimumSize(0,0);

    QPropertyAnimation* closeAnimation = new QPropertyAnimation(this,"geometry");
    closeAnimation->setStartValue(geometry());
    closeAnimation->setEndValue(QRect(geometry().x(), geometry().y()+height()/2, width(), 0));
    closeAnimation->setDuration(500);
    m_bCloseAnimationState = true;

    closeAnimation->setEasingCurve(QEasingCurve::OutBounce);  // 缓和曲线风格

    connect(closeAnimation,SIGNAL(finished()),this,SLOT(close()));
    closeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!m_bCloseAnimationState)
    {
        PlayCloseAnimation();
        event->ignore();
    }
    else{
        event->accept();
        exit(0);
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *evt)
{
    switch (evt->type())
    {
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        case QEvent::MouseMove:
        case QEvent::KeyPress:
        case QEvent::KeyRelease:
        case QEvent::Move:
        {
            m_timeMouseTrigger = QTime::currentTime();
        }
        break;
    }

    return QObject::eventFilter(obj, evt);
}

void MainWindow::paintEvent(QPaintEvent *e)
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
    last = event->globalPos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget)
    {
        int dx = event->globalX() - last.x();
        int dy = event->globalY() - last.y();
        last = event->globalPos();
        move(x()+dx, y()+dy);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int dx = event->globalX() - last.x();
    int dy = event->globalY() - last.y();
    move(x()+dx, y()+dy);
    isPressedWidget = false; // 鼠标松开时，置为false
}

void MainWindow::on_actionConversation_triggered()
{
    ui->conversation->show();
    ui->lecture->hide();
}

void MainWindow::on_actionLecture_triggered()
{
    ui->lecture->show();
    ui->conversation->hide();
}
