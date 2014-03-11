#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtNetwork>
#include <QStringList>

#include "bluepages.h"
#include "progressdialog.h"
#include "headerdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bluepages      bp;
    bool           querying;
    size_t         queryIndex;
    size_t         queryCount;

    QHttp          *http;

    bool           isSearchChanged;
    QStringList    lines;
    QStringList    functions;

    QList<QString> columns;
    QList<QString> headers;

private:
    QHBoxLayout    *mainLayout;
    QSplitter      *splitter;
    QStackedWidget *stackWidget;
    QVBoxLayout    *searchLayout;
    QVBoxLayout    *detailLayout;
    QHBoxLayout    *hLayout;
    QVBoxLayout    *rightLayout;

    QWidget        *mainWidget;
    QWidget        *searchWidget;
    QWidget        *rightWidget;
    QWidget        *detailWidget;

    QComboBox      *comboBox;
    QPushButton    *goButton;
    QTextEdit      *textEdit;
    QTableWidget   *detailTable;
    QTableWidget   *resultTable;
    QLabel         *statusLabel;

    QMenu          *fileMenu;
    QMenu          *editMenu;
    QMenu          *helpMenu;

    QAction        *exportAction;
    QAction        *exitAction;
    QAction        *copyAction;
    QAction        *selectAllAction;
    QAction        *headerAction;
    QAction        *aboutAction;
//    QAction        *aboutQtAction;
    QAction        *separatorAction;

    ProgressDialog *progressDialog;

private:
    void readSettings();
    void keyPressEvent(QKeyEvent *event);

    void createUI();
    void createActions();
    void createMenu();
    void createContextMenu();
    void createStatusBar();

    void prepare();
    void prepareDetailTable();
    void updateDetailTable(size_t index, size_t count);
    void refreshResultTable();

    void queryNext();
    void stop();

private slots:
    void selectAll();
    void copy();

    void searchChanged();

    void query();
    void done(bool error);
    void cancel();

    void exportFile();
    void changeTableHeader();
    void setTableHeader();

    void about();

public:
    void saveSettings();
};

#endif // MAINWINDOW_H
