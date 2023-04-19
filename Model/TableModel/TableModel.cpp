#include "TableModel.hpp"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{

}

void TableModel::setTableHeader(QVector<QMap<int,QString>> &value){
    if(value == nullptr){
        throw std::invalid_argument("In function \"setTableHeader\" argument \"value\" = nullptr");
    }
    if(__table_header != nullptr){
        delete __table_header;
    }
    *__table_header = value;

}
void TableModel::setTableData(QVector<QVector<QVariant>> &value){
    if(value == nullptr){
        throw std::invalid_argument("In function \"setTableData\" argument \"value\" = nullptr");
    }
    if(__table_data != nullptr){
        delete __table_data;
    }
    *__table_data = value;
    insertRows(0,__table_data->count());
}
QVector<QMap<int,QString>> TableModel::getTableHeader(){
    if(__table_header == nullptr){
        return QVector<QMap<int,QString>>();
    }
    return *__table_header;
}
QVector<QVector<QVariant>> TableModel::getTableData(){
    if(__table_header == nullptr){
        return QVector<QVector<QVariant>>();
    }
    return *__table_data;
}

int TableModel::rowCount(const QModelIndex &parent) const{
    if(__table_data == nullptr){
        return 0;
    }
    return __table_data->count();
}
int TableModel::columnCount(const QModelIndex &parent) const {
    if(__table_header == nullptr){
        return 0;
    }
    return __table_header->count();
}
QVariant TableModel::data(const QModelIndex &index, int role) const{
    size_t row = index.row();
    size_t column = index.column();
    if(__table_data == nullptr){
        return QVariant();
    }
    if (row >= rowCount() || column >= columnCount() || role !=  Qt::DisplayRole){
        return QVariant();
    }


    return __table_data->at(row).at(column);
}
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const{
    return Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    size_t row = index.row();
    size_t column = index.column();

    if (row >= rowCount() || column >= columnCount()){
        return false;
    }

    (*__table_data)[row][column] = value;
    emit dataChanged(createIndex(row,column),createIndex(row,column));

    return true;
}
bool TableModel::insertRows(int row, int count, const QModelIndex &parent){
    beginInsertRows(parent,row,row+count);
    endInsertRows();

    return true;
}
bool TableModel::removeRows(int row, int count, const QModelIndex &parent){

    if(row + count > rowCount()){
        return false;
    }

    beginRemoveRows(parent,row,row+count);
    for(int i = 0; i < count; i++){
        __table_data->removeAt(row);
    }
    endRemoveRows();

    return true;
}
bool TableModel::insertColumns(int column, int count, const QModelIndex &parent){
    beginInsertColumns(parent,column,column+count);
    endInsertColumns();
    return true;
}
bool TableModel::removeColumns(int column, int count, const QModelIndex &parent){
    if(column + count > columnCount()){
        return false;
    }

    beginRemoveColumns(parent,column,column+count);
    for(int i = 0; i < count; i++){
        __table_data->removeAt(column);
    }
    endRemoveColumns();

    return true;
}
TableModel::~TableModel(){

}
