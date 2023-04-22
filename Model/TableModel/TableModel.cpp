#include "TableModel.hpp"

TableModel::TableModel(QObject *parent): QAbstractTableModel(parent)
{

}

void TableModel::setTableHeader(QVector<QString> *value){
    if(value == nullptr){
        throw std::invalid_argument("In function \"setTableHeader\" argument \"value\" = nullptr");
    }
    if(__table_header != nullptr){
        removeColumns(0, __table_header->count());
    }

    __table_header = value;

    insertColumns(0,__table_header->count());
}
void TableModel::setTableData(QVector<QVector<QVariant>> *value){
    if(value == nullptr){
        throw std::invalid_argument("In function \"setTableData\" argument \"value\" = nullptr");
    }
    if(__table_data != nullptr){
        removeColumns(0, __table_data->count());
    }

    __table_data = value;
    insertRows(0,__table_data->count());
}
QVector<QString> TableModel::getTableHeader(){
    if(__table_header == nullptr){
        return QVector<QString>();
    }
    return *__table_header;
}
QVector<QVector<QVariant>> TableModel::getTableData(){
    if(__table_header == nullptr){
        return QVector<QVector<QVariant>>();
    }
    return *__table_data;
}
QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount()){
        qDebug() << "Section ERROR " << section ;
        return QVariant();
    }
    qDebug() <<"Section "<< __table_header->at(section) << " ColumnCount = " << columnCount();
    return __table_header->at(section);
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

    QVariant result;

    switch (column) {
    case 0:
        result = (*__table_data)[row][POS_S_NAME];
        break;
    case 1:
        result = (*__table_data)[row][POS_S_IP];
        break;
    case 2:
        result = (*__table_data)[row][POS_S_PORT];
        break;
    case 3:
        result = (*__table_data)[row][POS_S_COUNT_PLAYER];
        break;
    }

    return result;
}
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const{
    return Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}
QHash<int, QByteArray> TableModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    size_t row = index.row();
    size_t column = index.column();

    if (row >= rowCount() || column >= columnCount()){
        return false;
    }
    emit dataChanged(index,index,{role});
    (*__table_data)[row][column] = value;

    return true;
}
bool TableModel::insertRows(int row, int count, const QModelIndex &parent){

    beginInsertRows(parent,row,row+count-1);

    for(int i = 0 ; i < count; i++){
        for(int j = 0; j < __table_data->at(i).count(); j++){
            setData(createIndex(row + i,j),(*__table_data)[row + i][j]);
        }
    }
    endInsertRows();

    return true;
}
bool TableModel::removeRows(int row, int count, const QModelIndex &parent){

    if(row + count > rowCount()){
        return false;
    }
    if(__table_data == nullptr){
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
    if(__table_header == nullptr){
        return false;
    }

    beginRemoveColumns(parent,column,column+count);
    for(int i = 0; i < count; i++){
        __table_header->removeAt(column);
    }
    endRemoveColumns();

    return true;
}
TableModel::~TableModel(){

}
