#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "global.h"

class NoteViewPane;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    GLOBAL_FUNC

    void InitMainPaneLayout();
    void PlayCloseAnimation();

    void closeEvent(QCloseEvent *event);

protected:
    bool eventFilter(QObject *obj, QEvent *evt);

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放


private slots:
    void on_actionConversation_triggered();

    void on_actionLecture_triggered();

private:
    bool isPressedWidget;
    QPoint last;                        //窗口拖动用变量
    QWidget *m_pMainPane;
    NoteViewPane *m_pNoteViewPane;

    bool m_bCloseAnimationState;

    QTimer *m_pMouseWatcher;
    QTime m_timeMouseTrigger;

    QListWidget *m_listNoteItems;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
