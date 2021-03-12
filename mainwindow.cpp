#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QFontDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupFontTree();

    connect(ui->fontTree, &QTreeWidget::currentItemChanged,this, &MainWindow::showFont);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QApplication::quit();
}


void MainWindow::on_pushButton_3_released()
{
   ui->stackedWidget->setCurrentIndex(2);
   ui->textEdit_2->document()->setDefaultFont(font);
}

void MainWindow::on_pushButton_4_pressed()
{
}

void MainWindow::setupFontTree()
{
    QFontDatabase database;
    ui->fontTree->setColumnCount(1);
    ui->fontTree->setHeaderLabels({ tr("Font") });

    const QStringList fontFamilies = database.families();
    for (const QString &family : fontFamilies) {
        const QStringList styles = database.styles(family);
        if (styles.isEmpty())
            continue;

        QTreeWidgetItem *familyItem = new QTreeWidgetItem(ui->fontTree);
        familyItem->setText(0, family);
        familyItem->setCheckState(0, Qt::Unchecked);
        familyItem->setFlags(familyItem->flags() | Qt::ItemIsAutoTristate);

        for (const QString &style : styles) {
            QTreeWidgetItem *styleItem = new QTreeWidgetItem(familyItem);
            styleItem->setText(0, style);
            styleItem->setCheckState(0, Qt::Unchecked);
            styleItem->setData(0, Qt::UserRole, QVariant(database.weight(family, style)));
            styleItem->setData(0, Qt::UserRole + 1, QVariant(database.italic(family, style)));
        }
    }
}

void MainWindow::showFont(QTreeWidgetItem *item)
{
    if (!item)
        return;

    QString family;
    QString style;
    int weight;
    bool italic;

    if (item->parent()) {
        family = item->parent()->text(0);
        style = item->text(0);
        weight = item->data(0, Qt::UserRole).toInt();
        italic = item->data(0, Qt::UserRole + 1).toBool();
    } else {
        family = item->text(0);
        style = item->child(0)->text(0);
        weight = item->child(0)->data(0, Qt::UserRole).toInt();
        italic = item->child(0)->data(0, Qt::UserRole + 1).toBool();
    }

    QString oldText = ui->textEdit_6->toPlainText().trimmed();
    bool modified = ui->textEdit_6->document()->isModified();
    ui->textEdit_6->clear();
    QFont font(family, 32, weight, italic);
    font.setStyleName(style);

    ui->textEdit_6->document()->setDefaultFont(font);
    QTextCursor cursor = ui->textEdit_6->textCursor();
    QTextBlockFormat blockFormat;
    blockFormat.setAlignment(Qt::AlignCenter);
    cursor.insertBlock(blockFormat);

    if (modified)
        cursor.insertText(QString(oldText));
    else
        cursor.insertText(QString("Numata J1-MX6").arg(family).arg(style));

    ui->textEdit_6->document()->setModified(modified);
}



void MainWindow::on_pushButton_2_released()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->textEdit->document()->setDefaultFont(font);
}

void MainWindow::on_pushButton_4_released()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->textEdit_3->document()->setDefaultFont(font);
}

void MainWindow::on_pushButton_6_released()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->textEdit_4->document()->setDefaultFont(font);
}

void MainWindow::on_pushButton_5_released()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->textEdit_5->document()->setDefaultFont(font);
}

void MainWindow::on_pushButton_7_released()
{
}

void MainWindow::on_pushButton_7_pressed()
{
   ui->stackedWidget->setCurrentIndex(5);
}
