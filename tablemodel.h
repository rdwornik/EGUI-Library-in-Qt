#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include<QString>
#include<QAbstractTableModel>
#include<QList>
struct Book{
    QString title;
    QString author;
    QString year;

//    Book(){
//        QString title = NULL;
//        QString author = NULL;
//        QString year = NULL;
//    }
//    Book(const QStringList& data){
//            this->author = data[0];
//            this->title = data[1];
//            this->year = data[2];
//        }

    bool operator==(const Book &other) const{
        return (title == other.title &&
                author == other.author &&
                year == other.year);
    }
};

inline QDataStream &operator<<(QDataStream &stream, const Book &book)
{
    return stream << book.author << book.title << book.year;
}

inline QDataStream &operator>>(QDataStream &stream, Book &book)
{

    return stream >> book.author >> book.title >> book.year;
}

class TableModel : public QAbstractTableModel
{
     Q_OBJECT
public:
    TableModel(QObject *parent = 0);
    TableModel(QList<Book> book, QObject *parent = 0);

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
        bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
        QList<Book> getBooks() const;

private:
    QList<Book> books;
};

#endif // TABLEMODEL_H
