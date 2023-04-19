#pragma once
#include <qqml.h>
#include <QAbstractTableModel>
#include <QVector>
#include <QMap>

#define POS_S_NAME 2
#define POS_S_IP 0
#define POS_S_PORT 1

class TableModel: public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT

private:

    QVector<QString> *__table_header = nullptr;
    QVector<QVector<QVariant>> *__table_data = nullptr;

public:
    TableModel(QObject *parent = nullptr);
    virtual ~TableModel();


    QVector<QString> getTableHeader();
    QVector<QVector<QVariant>> getTableData();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void setTableHeader(QVector<QString> *value);
    void setTableData(QVector<QVector<QVariant>> *value);

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
};
