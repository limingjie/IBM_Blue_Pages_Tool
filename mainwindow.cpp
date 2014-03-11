#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    readSettings();

    setWindowTitle("BluePages Tool V0.1");
    setWindowIcon(QIcon(":/images/bp.png"));

    createUI();
    createActions();
    createMenu();
    createContextMenu();
    createStatusBar();

    textEdit->setFocus();

    querying = false;
    isSearchChanged = false;
}

MainWindow::~MainWindow()
{
    cancel();
}

void MainWindow::readSettings()
{
    QSettings s("settings.ini", QSettings::IniFormat);

    QVariant var;

    var = s.value("window/geometry");
    if(var.isNull())
    {
        resize(800, 600);

        QDesktopWidget *desktop = QApplication::desktop();
        move((desktop->width()  - width() ) / 2,
             (desktop->height() - height()) / 2);
    }
    else
    {
        restoreGeometry(var.toByteArray());
    }

    var = s.value("data/headers");
    if(var.isNull())
    {
        size_t i, size = bp.columns_lite.size();
        for(i = 0; i < size; i++)
        {
            headers.append(bp.columns_lite[i].c_str());
        }
    }
    else
    {
        headers.clear();
        headers.append(var.toStringList());
    }

    var = s.value("data/columns");
    if(var.isNull())
    {
        size_t i, size = bp.columns_lite.size();
        for(i = 0; i < size; i++)
        {
            columns.append(bp.columns_lite[i].c_str());
        }

        size = bp.columns.size();
        for(i = 0; i < size; i++)
        {
            if(!headers.contains(bp.columns[i].c_str()))
            {
                columns.append(bp.columns[i].c_str());
            }
        }
    }
    else
    {
        columns.clear();
        columns.append(var.toStringList());
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    // F9 - switch between search view & search for view
    if(key == Qt::Key_F9)
    {
        int index = stackWidget->currentIndex();

        stackWidget->setCurrentIndex((index + 1) % 2);

        if(index == 0 && isSearchChanged)
        {
            prepare();
            prepareDetailTable();

            isSearchChanged = false;
        }
    }
    // Paste anywhere to search for box
    else if(event->matches(QKeySequence::Paste))
    {
        stackWidget->setCurrentIndex(0);
        textEdit->clear();
        textEdit->paste();
        textEdit->setFocus();
    }
    // Ctrl+Enter - Query shortcut
    else if((key == Qt::Key_Return || key == Qt::Key_Enter) &&
        (event->modifiers() & Qt::ControlModifier))
    {
        query();
    }

    QMainWindow::keyPressEvent(event);
}

void MainWindow::saveSettings()
{
    QSettings s("settings.ini", QSettings::IniFormat);

    s.setValue("window/geometry", saveGeometry());

    QVariant varColumns(columns);
    s.setValue("data/columns", varColumns);

    QVariant varHeaders(headers);
    s.setValue("data/headers", varHeaders);
}

void MainWindow::createUI()
{
    comboBox = new QComboBox();
    size_t size = bp.functions_description.size();
    for(size_t i = 0; i < size; i++)
    {
        comboBox->addItem(bp.functions_description[i].c_str());
    }
    comboBox->setCurrentIndex(0);
    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(searchChanged()));

    goButton = new QPushButton();
    goButton->setText(tr("&Go"));
    connect(goButton, SIGNAL(clicked()), this, SLOT(query()));

    hLayout = new QHBoxLayout();
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->addWidget(comboBox, 1);
    hLayout->addWidget(goButton, 0);

    textEdit = new QTextEdit();
    textEdit->setAcceptRichText(false);
    connect(textEdit, SIGNAL(textChanged()), this, SLOT(searchChanged()));

    detailTable = new QTableWidget();
    detailTable->verticalHeader()->hide();
    detailTable->showGrid();
    detailTable->setAlternatingRowColors(true);
    detailTable->setSelectionMode(QTableWidget::NoSelection);
    detailTable->setColumnCount(3);
    detailTable->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("Search For")));
    detailTable->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("Search Type")));
    detailTable->setHorizontalHeaderItem(2, new QTableWidgetItem(tr(" # ")));
    detailTable->resizeColumnsToContents();

    searchLayout = new QVBoxLayout();
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->addWidget(new QLabel(tr("Search Type")));
    searchLayout->addLayout(hLayout);
    searchLayout->addWidget(new QLabel(tr("Search For (F9 switch to search details)")));
    searchLayout->addWidget(textEdit);

    searchWidget = new QWidget();
    searchWidget->setLayout(searchLayout);

    detailLayout = new QVBoxLayout();
    detailLayout->setContentsMargins(0, 0, 0, 0);
    detailLayout->addWidget(new QLabel(tr("Search Detail (F9 switch to normal view)")));
    detailLayout->addWidget(detailTable);

    detailWidget = new QWidget();
    detailWidget->setLayout(detailLayout);

    stackWidget = new QStackedWidget();
    stackWidget->addWidget(searchWidget);
    stackWidget->addWidget(detailWidget);

    resultTable = new QTableWidget();
    resultTable->showGrid();
    resultTable->setSelectionMode(QTableWidget::ContiguousSelection);
    connect(resultTable, SIGNAL(doubleClicked(QModelIndex)),
            resultTable, SLOT(resizeColumnsToContents()));
    connect(resultTable, SIGNAL(doubleClicked(QModelIndex)),
            resultTable, SLOT(resizeRowsToContents()));
    setTableHeader();

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->addWidget(new QLabel(tr("Search Result")));
    rightLayout->addWidget(resultTable);

    rightWidget = new QWidget();
    rightWidget->setLayout(rightLayout);

    splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(stackWidget);
    splitter->addWidget(rightWidget);
    splitter->setStretchFactor(1, 1);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(splitter);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);

    this->setCentralWidget(mainWidget);
}

void MainWindow::createActions()
{
    exportAction = new QAction(tr("Export"), this);
    exportAction->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAction->setStatusTip(tr("Export spreadsheet"));
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportFile()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy selected cells to clipboard"));
    connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

    selectAllAction = new QAction(tr("Select &All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), this, SLOT(selectAll()));

    headerAction = new QAction(tr("C&olumns..."), this);
    headerAction->setShortcut(tr("Ctrl+O"));
    headerAction->setStatusTip(tr("Arrange columns"));
    connect(headerAction, SIGNAL(triggered()), this, SLOT(changeTableHeader()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setIcon(QIcon(":/images/bp.png"));
    aboutAction->setStatusTip(tr("About BluePages Tool"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

//    aboutQtAction = new QAction(tr("About &Qt"), this);
//    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
//    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exportAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(copyAction);
    editMenu->addAction(selectAllAction);
    editMenu->addAction(headerAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createContextMenu()
{
    resultTable->setContextMenuPolicy(Qt::ActionsContextMenu);
    resultTable->addAction(copyAction);
    resultTable->addAction(selectAllAction);
    resultTable->addAction(headerAction);
}

void MainWindow::createStatusBar()
{
    statusLabel = new QLabel();
    statusLabel->setMinimumWidth(200);
    statusLabel->setText(tr(" Welcome"));
    statusBar()->addWidget(statusLabel, 1);
}

void MainWindow::searchChanged()
{
    isSearchChanged = true;
}

void MainWindow::prepare()
{
    bool autotype = false;
    QString function;

    int index = comboBox->currentIndex();

    if(index == 0)
        autotype = true;
    else
        function = bp.functions[index].c_str();

    lines = textEdit->toPlainText().split("\n");
    functions.clear();

    for(int i = lines.size() - 1; i >= 0; i--)
    {
        lines[i] = lines[i].trimmed();
        if(lines[i].size() == 0)
        {
            lines.removeAt(i);
            continue;
        }

        if(autotype)
            functions.push_front(bp.autoType(lines[i]));
        else
            functions.push_front(function);
    }

    queryCount = lines.size();
}

void MainWindow::prepareDetailTable()
{
    size_t i;
    QTableWidgetItem *item;

    detailTable->clearContents();
    detailTable->setRowCount(queryCount);

    for(i = 0; i < queryCount; i++)
    {
        item = new QTableWidgetItem();
        item->setText(lines[i]);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        detailTable->setItem(i, 0, item);

        item = new QTableWidgetItem();
        item->setText(functions[i]);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        detailTable->setItem(i, 1, item);
    }

    detailTable->resizeColumnsToContents();
    detailTable->resizeRowsToContents();

    int width = detailTable->width() - 2;
    width -= detailTable->verticalScrollBar()->sizeHint().width();
    width -= detailTable->columnWidth(1);
    width -= detailTable->columnWidth(2);
    detailTable->setColumnWidth(0, width);
}

void MainWindow::updateDetailTable(size_t index, size_t count)
{
    QTableWidgetItem *item;

    item = new QTableWidgetItem();
    item->setText(QString("%1").arg(count));
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    detailTable->setItem(index, 2, item);
}

void MainWindow::refreshResultTable()
{
    size_t row, col;
    size_t rowCount, columnCount;
    QTableWidgetItem *item;

    QColor color = this->palette().color(QPalette::AlternateBase);
    bool alternative = true;

    rowCount = bp.row_count();
    columnCount = headers.size();

    resultTable->clearContents();
    resultTable->setRowCount(rowCount);
    resultTable->setColumnCount(columnCount);

    for(row = 0; row < rowCount; row++)
    {
        if(bp.result(row, "REPEAT") == "N") alternative = !alternative;

        for(col = 0; col < columnCount; col++)
        {
            item = new QTableWidgetItem();
            if(alternative) item->setBackgroundColor(color);
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            item->setText(QString(bp.result(row, headers[col].toStdString()).c_str()));
            resultTable->setItem(row, col, item);
        }
    }

    resultTable->resizeColumnsToContents();
    resultTable->resizeRowsToContents();
}

void MainWindow::selectAll()
{
    resultTable->selectAll();
    resultTable->setFocus();
}

void MainWindow::copy()
{
    QList<QTableWidgetSelectionRange> ranges = resultTable->selectedRanges();
    if(ranges.isEmpty()) return;

    QTableWidgetSelectionRange range = ranges.first();

    int i, j;
    int rowCount = range.rowCount();
    int columnCount = range.columnCount();

    QString text;
    QTableWidgetItem *item;
    for(i = 0; i < rowCount; i++)
    {
        if(i != 0) text += '\n';
        for(j = 0; j < columnCount; j++)
        {
            item = resultTable->item(range.topRow() + i, range.leftColumn() + j);

            if(j != 0) text += '\t';
            if(item)text += item->text();
        }
    }

    QApplication::clipboard()->setText(text);
}

void MainWindow::query()
{
    if(!querying)
    {
        bp.clear();
        refreshResultTable();

        prepare();

        if(queryCount)
        {
            querying = true;
            queryIndex = 0;

            stackWidget->setCurrentWidget(detailWidget);
            prepareDetailTable();
            isSearchChanged = false;

            progressDialog = new ProgressDialog(this);
            progressDialog->setCurrentProgress(0, 100);
            progressDialog->setOverallProgress(0, queryCount);
            connect(progressDialog, SIGNAL(rejected()), this, SLOT(cancel()));
            progressDialog->show();
            this->setDisabled(true);
            progressDialog->setEnabled(true);

            http = new QHttp();
            connect(http, SIGNAL(done(bool)), this, SLOT(done(bool)));
            connect(http, SIGNAL(dataReadProgress(int,int)),
                    progressDialog, SLOT(setCurrentProgress(int,int)));

            queryNext();
        }
        else
        {
            QMessageBox::warning(this, tr("BluePages"),
                tr("Search For box is empty or contains only empty lines!"));
        }
    }
}

void MainWindow::queryNext()
{
    if(queryIndex >= queryCount)
    {
        stop();
        return;
    }

    string function = functions[queryIndex].toStdString();

    QString line = lines[queryIndex];
    if(!line.endsWith('%') && function != "directReportsOf")
    {
        line.push_back('%');
    }
    line.replace(" ", "%20").replace("&", "%26");

    string parameter = line.toStdString();
    QString link(bp.url(function, parameter).c_str());
    QUrl url(link);

    http->setHost(url.host());
    http->get(link);

    progressDialog->setText(lines[queryIndex]);
    progressDialog->setOverallProgress(queryIndex, queryCount);
}

void MainWindow::done(bool error)
{
    string page;

    if (error)
    {
        QMessageBox::critical(this, "Network Error :(", http->errorString());
        cancel();
        return;
    }
    else
    {
        page = http->readAll().data();
        size_t count = bp.translate(page);
        progressDialog->increase(page.size());
        updateDetailTable(queryIndex, count);
        refreshResultTable();
    }

    http->close();

    if(querying)
    {
        queryIndex++;
        queryNext();
    }
}

void MainWindow::cancel()
{
    stop();
}

void MainWindow::stop()
{
    if(querying)
    {
        http->clearPendingRequests();
        http->close();
        disconnect(http, SIGNAL(done(bool)), this, SLOT(done(bool)));
        delete http;

        querying = false;
        lines.clear();

        progressDialog->setOverallProgress(queryCount, queryCount);
        progressDialog->close();
        delete progressDialog;

        stackWidget->setCurrentWidget(searchWidget);

        this->setEnabled(true);
    }
}

void MainWindow::exportFile()
{
    int rowCount = resultTable->rowCount();
    int columnCount = resultTable->columnCount();

    if(rowCount == 0)
    {
        QMessageBox::warning(this, "BluePages", "Search result is empty.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Export"), ".",
        tr("Text (Tab delimited) (*.txt);;CSV (Comma delimited) (*.csv)"));

    if(fileName.isEmpty()) return;

    QChar delimiter;
    if(fileName.endsWith(".csv"))
    {
        delimiter = ',';
    }
    else
    {
        delimiter = '\t';
    }

    int i, j;
    QString str, text;

    for(i = 0; i < columnCount; i++)
    {
        if(i != 0) str += delimiter;
        str += headers[i];
    }

    QTableWidgetItem *item;
    for(i = 0; i < rowCount; i++)
    {
        str += '\n';
        for(j = 0; j < columnCount; j++)
        {
            item = resultTable->item(i, j);

            if(j != 0) str += delimiter;
            if(item)
            {
                text = item->text();
                if(text.contains(','))
                {
                    str += "\"" + text + "\"";
                }
                else
                {
                    str += text;
                }
            }
        }
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::warning(this, tr("BluePages"),
            tr("Cannot write file %1:\n%2.")
               .arg(file.fileName())
               .arg(file.errorString()));
        return;
    }

    file.write(str.toAscii());
}

void MainWindow::changeTableHeader()
{
    HeaderDialog dialog(this);
    dialog.setValues(&columns, &headers);
    connect(&dialog, SIGNAL(accepted()), this, SLOT(setTableHeader()));

    dialog.exec();
}

void MainWindow::setTableHeader()
{
    int i, size;

    size = headers.size();
    resultTable->setColumnCount(size);
    for(i = 0; i < size; i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(headers[i]);
        resultTable->setHorizontalHeaderItem(i, item);
    }
    resultTable->resizeColumnsToContents();

    refreshResultTable();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About This Tool"),
        tr("<b>BluePages Tool V0.1</b>"
           "<p>Batch query BluePages, organize and save search result to file.</p>"
           "<p>Copyright &copy;forever  Mingjie Li</p>"
           "<p>Email: <a href=\"mailto:limingjie0719@gmail.com\">limingjie0719@gmail.com</a><br>"
           "Email: <a href=\"mailto:limingjie@outlook.com\">limingjie@outlook.com</a></p>"
           "<p>Qt GNU LGPL V2.1<br>"
           "Statically linked by Microsoft Visual Studio 2010</p>"
           ));
}
