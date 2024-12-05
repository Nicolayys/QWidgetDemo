#include "PageWidget.h"
#include <QUuid>
#include <QApplication>
#include <QCheckBox>

#include <QStandardItemModel>
PageWidget::PageWidget(QWidget *parent)
    : QWidget(parent)
{
    initPagingUi();
    initPagingStyle();
    execSqlWork("SELECT * FROM students");
}

PageWidget::~PageWidget()
{
}

void PageWidget::setModel(QStandardItemModel *_model)
{
    paging_control_table_->setModel(_model);
    standard_item_model_=_model;
    connect(standard_item_model_, &QAbstractItemModel::dataChanged, this, &PageWidget::onDataChangedSlot);
}

void PageWidget::setHeadNamesList(QStringList _head_list)
{
    heads_list_ = _head_list;
}

void PageWidget::translateHeadNames(QMap<QString, QString> &_head_trs)
{

}

void PageWidget::exec(const QString &_exec_sql)
{

}

QString PageWidget::lastExecSql() const
{

}

void PageWidget::setDelegateForColumn(int _column, QAbstractItemDelegate *_delegate)
{
    if(!_delegate){
        return;
    }
    paging_control_table_->setItemDelegateForColumn(_column,_delegate);
}

int PageWidget::columnCount()
{

}

void PageWidget::setColumnWidth(int _column, int _width)
{
    paging_control_table_->setColumnWidth(_column,_width);
}

void PageWidget::seekPreviousPageSlot()
{

}

void PageWidget::seekNextPageSlot()
{

}

void PageWidget::seekOnePageSlot()
{

}

void PageWidget::switchPageRowSlot(int _index)
{

}

void PageWidget::hideColumnSlot()
{

}

void PageWidget::hideEmptyColumnSlot()
{

}

void PageWidget::onDataChangedSlot(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QList<int> &roles)
{
    if (topLeft.column() == 0) {
        bool allChecked = true;
        bool anyChecked = false;

        // 检查每一行复选框的状态
        for (int row = 0; row < standard_item_model_->rowCount(); ++row) {
            Qt::CheckState state = static_cast<Qt::CheckState>(standard_item_model_->data(standard_item_model_->index(row, 0), Qt::CheckStateRole).toInt());
            if (state == Qt::Unchecked) {
                allChecked = false;
            } else if (state == Qt::Checked) {
                anyChecked = true;
            }
        }

        // 根据行复选框的状态设置表头复选框的状态
        if (allChecked) {
            check_head_view->setCheckState(Qt::Checked);
        } else if (anyChecked) {
            check_head_view->setCheckState(Qt::PartiallyChecked);
        } else {
            check_head_view->setCheckState(Qt::Unchecked);
        }

        check_head_view->viewport()->update();  // 重新绘制表头
    }
}

void PageWidget::updateCheckBoxStateSlot(Qt::CheckState _checked)
{
    qDebug() << "复选框状态:" << (_checked ? "选中" : "未选中");
    // 检查每一行复选框的状态
    int row = standard_item_model_->rowCount();
    qInfo()<<row;
    for (int row = 0; row < standard_item_model_->rowCount(); ++row) {
        QModelIndex model_index = standard_item_model_->index(row,0);
        Qt::CheckState state = static_cast<Qt::CheckState>(standard_item_model_->data(model_index, Qt::CheckStateRole).toInt());
        if (_checked == Qt::Unchecked) {
            standard_item_model_->setData(model_index,Qt::Unchecked,Qt::CheckStateRole);
        } else if (_checked == Qt::Checked) {
            standard_item_model_->setData(model_index,Qt::Checked,Qt::CheckStateRole);
        }
    }


}

void PageWidget::initPagingUi()
{
    paging_control_table_ = new QTableView();
    hide_col_btn_ = new QToolButton();
    hide_empty_btn_ = new QToolButton();
    previous_page_btn_ = new QToolButton();
    seek_page_btn_ = new QToolButton();
    next_page_btn_ = new QToolButton();
    select_page_max_row_cb_ = new QComboBox();
    seek_page_led_ = new QLineEdit();
    total_count_label_ = new QLabel("共0条");
    current_page_label_ = new QLabel("0/0页");
    select_page_max_row_cb_->setObjectName("brightComboBox");

    QVBoxLayout* main_layout = new QVBoxLayout();
    this->setLayout(main_layout);


    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->addWidget(paging_control_table_, 1);

    QHBoxLayout * control_layout = new QHBoxLayout();
    main_layout->addLayout(control_layout);
    control_layout->setContentsMargins(20, 10, 20, 10);

    control_layout->addWidget(hide_empty_btn_);
    control_layout->addSpacing(20);
    control_layout->addWidget(hide_col_btn_);
    control_layout->addStretch(1);
    control_layout->addWidget(total_count_label_);
    control_layout->addWidget(select_page_max_row_cb_);
    control_layout->addWidget(previous_page_btn_);
    control_layout->addWidget(current_page_label_);
    control_layout->addWidget(next_page_btn_);
    control_layout->addWidget(new QLabel("跳转到"));
    control_layout->addWidget(seek_page_led_);
    control_layout->addWidget(seek_page_btn_);

    select_page_max_row_cb_->addItem("50条/页", 50);
    select_page_max_row_cb_->addItem("100条/页", 100);
    select_page_max_row_cb_->addItem("200条/页", 200);
    select_page_max_row_cb_->addItem("300条/页", 300);
    select_page_max_row_cb_->setMinimumSize({ 120, 30 });

    connect(previous_page_btn_, &QToolButton::clicked, this, &PageWidget::seekPreviousPageSlot);
    connect(next_page_btn_, &QToolButton::clicked, this, &PageWidget::seekNextPageSlot);
    connect(seek_page_btn_, &QToolButton::clicked, this, &PageWidget::seekOnePageSlot);
    connect(hide_col_btn_, &QToolButton::clicked, this, &PageWidget::hideColumnSlot);
    connect(hide_empty_btn_, &QToolButton::clicked, this, &PageWidget::hideEmptyColumnSlot);
    connect(select_page_max_row_cb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PageWidget::switchPageRowSlot);
    connect(select_page_max_row_cb_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PageWidget::switchPageRowSlot);
    connect(paging_control_table_, &QTableView::clicked, this, &PageWidget::mouseClickCellSignal);

    check_head_view = new CheckboxHeadView(Qt::Horizontal,paging_control_table_);

    // 连接复选框状态变化的信号
    connect(check_head_view, &CheckboxHeadView::checkStateChanged, this, &PageWidget::updateCheckBoxStateSlot,Qt::UniqueConnection);
    paging_control_table_->setHorizontalHeader(check_head_view);

    // 第一列的复选框状态变化更新表头
    // standard_item_model_ = new QStandardItemModel();

}

void PageWidget::initPagingStyle()
{
    //设置跳转页输入限制
    seek_page_led_->setValidator(new QIntValidator(1, 1, this));
    //设置表格样式
    // paging_control_table_->setHorizontalHeader(new PageingSortHeader(Qt::Horizontal, paging_control_table_));
    paging_control_table_->setColumnWidth(0,300);

    paging_control_table_->horizontalHeader()->setMinimumHeight(40);//最小高度
    paging_control_table_->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);//表头文字左对齐
    paging_control_table_->horizontalHeader()->setStretchLastSection(true);//最后一列拉伸
    paging_control_table_->setAlternatingRowColors(true);//隔行换色
    paging_control_table_->verticalHeader()->setVisible(false); //隐藏列表头
    paging_control_table_->setShowGrid(false);//不显示格子线
    paging_control_table_->horizontalHeader()->setDefaultSectionSize(200);//设置默认列宽
    paging_control_table_->verticalHeader()->setDefaultSectionSize(44);//设置默认行高
    paging_control_table_->setEditTriggers(QTableView::NoEditTriggers);//不可编辑
    paging_control_table_->horizontalHeader()->setSortIndicatorShown(true);//设置表头排序指示器可见
    paging_control_table_->horizontalHeader()->setSectionsClickable(true);//设置表头可点击
    paging_control_table_->setContextMenuPolicy(Qt::CustomContextMenu);//添加右键菜单
    paging_control_table_->setSelectionMode(QAbstractItemView::SingleSelection);//设置选中模式
    paging_control_table_->setSortingEnabled(true);
    paging_control_table_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);// 设置 QTableView 的列宽根据内容自动调整


    hide_empty_btn_->setFixedSize(18, 18);
    hide_empty_btn_->setToolTip("隐藏空列");
    hide_col_btn_->setFixedSize(18, 18);
    hide_col_btn_->setToolTip("选择显示列");

    previous_page_btn_->setObjectName("pageLeftBtn");
    next_page_btn_->setObjectName("pageRightBtn");
    seek_page_btn_->setObjectName("goBtn");
    seek_page_led_->setObjectName("lineEdit");
    hide_empty_btn_->setObjectName("hideEmptyBtn");
    hide_col_btn_->setObjectName("colDispalyBtn");

    auto all_texts = findChildren<QLabel*>();
    for (int index = 0; index < all_texts.count(); ++index) {
        all_texts[index]->setObjectName("textLabel");
    }

    seek_page_btn_->setText("跳转");
}

void PageWidget::execSqlWork(const QString &_exec_sql)
{
    // QSqlDatabase paging_control_db = createDatabase();
    QSqlDatabase paging_control_db = QSqlDatabase::addDatabase("QSQLITE");
    paging_control_db.setDatabaseName("sqlite.db");
    if(!paging_control_db.open()){
        qInfo()<<"open is false";
    }else{
        qInfo()<<"open is true";
    }

    QSqlQueryModel * query_model = new QSqlQueryModel;
    query_model->setQuery(_exec_sql);
    query_model->setHeaderData(0,Qt::Horizontal,"id");
    query_model->setHeaderData(1,Qt::Horizontal,"name");
    query_model->setHeaderData(2,Qt::Horizontal,"age");


    paging_control_table_->setModel(query_model);
    paging_control_table_->show();
    // QSqlQuery exec_query(paging_control_db);
    // exec_query.exec(_exec_sql);
    // while(exec_query.next()){

    // }
    removeDatabase(paging_control_db);


}

QSqlDatabase PageWidget::createDatabase()
{
    qDebug() << QSqlDatabase::drivers();

    QSettings database_ini_file(":/file/database.ini", QSettings::IniFormat);
    database_ini_file.beginGroup("Database");

    QString current_thread_id = QString::number((qint64)QThread::currentThreadId());
    QSqlDatabase create_database;

    if(QSqlDatabase::contains(current_thread_id)){
        create_database = QSqlDatabase::database(current_thread_id);
    }else{
        /* 使用当前线程ID作为连接名 */

        QString name = database_ini_file.value("type").toString().toUpper();
        create_database = QSqlDatabase::addDatabase(database_ini_file.value("type").toString().toUpper(), current_thread_id);
        create_database.setHostName(database_ini_file.value("ip").toString());
        create_database.setPort(database_ini_file.value("port").toInt());
        create_database.setDatabaseName(database_ini_file.value("db_name").toString());
        create_database.setUserName(database_ini_file.value("user").toString());
        create_database.setPassword(database_ini_file.value("password").toString());

    }
    if(!create_database.isOpen()){
        create_database.open();
    }
    if(!create_database.isOpen()){
        qCritical() << QString("数据库打开失败.");
        QString text =  create_database.lastError().text();
        qInfo()<<text;
    }
    return create_database;
}

void PageWidget::removeDatabase()
{
    QStringList connection_name_list = QSqlDatabase::connectionNames();
    for(QString connection_name : connection_name_list) {
        QSqlDatabase database = QSqlDatabase::database(connection_name);
        if(database.isOpen()){
            database.close();
        }
        QSqlDatabase::removeDatabase(connection_name);
    }
}

bool PageWidget::removeDatabase(QSqlDatabase _database)
{
    QString conection_name = _database.databaseName();
    if(!QSqlDatabase::contains(conection_name)){
        return false;
    }
    if(_database.isOpen()){
        _database.close();
    }
    QSqlDatabase::removeDatabase(conection_name);
    return true;
}

QString PageWidget::generateUUID()
{
    return QUuid::createUuid().toString().remove("{").remove("}").toLower();
}

CheckboxHeadView::CheckboxHeadView(Qt::Orientation orientation, QWidget *parent) : QHeaderView(orientation,parent)
{
}

CheckboxHeadView::~CheckboxHeadView()
{

}

void CheckboxHeadView::setCheckbox(QCheckBox * _check_box)
{
    check_box_ = _check_box;
}

bool CheckboxHeadView::getCheckedState()
{
    return _is_checked;
}

void CheckboxHeadView::setCheckState(Qt::CheckState _state)
{
    check_state_ = _state;
}

void CheckboxHeadView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    if(logicalIndex == 0){
        QStyleOptionButton option;
        option.rect = rect.adjusted(10,5,-5,-5);
        option.state = QStyle::State_Enabled;

        if (check_state_ == Qt::Checked) {
            option.state |= QStyle::State_On;
        } else if (check_state_ == Qt::PartiallyChecked) {
            option.state |= QStyle::State_NoChange;
        } else {
            option.state |= QStyle::State_Off;
        }
        //第四个参数用来应用样式设置
        QCheckBox * check_obx = new QCheckBox();
        QApplication::style()->drawControl(QStyle::CE_CheckBox,&option,painter,check_obx);

    }else{
        QHeaderView::paintSection(painter,rect,logicalIndex);
    }
}

void CheckboxHeadView::mousePressEvent(QMouseEvent *event)
{
    int section = sectionViewportPosition(0);
    int width = sectionSize(0);
    QRect check_rect(section+5,0,width-10,height());
    if (check_rect.contains(event->pos())) {
        // 切换复选框状态
        if (check_state_ == Qt::Checked) {
            setCheckState(Qt::Unchecked);
        }
        else {
            setCheckState(Qt::Checked);
        }
        // 更新复选框状态
        viewport()->update();
        emit checkStateChanged(check_state_);
    } else {
        QHeaderView::mousePressEvent(event);
    }

}

CustomQueryModel::CustomQueryModel(QObject *parent)
{

}

CustomQueryModel::~CustomQueryModel()
{

}

bool CustomQueryModel::setName(int studentId, const QString &name)
{
    QSqlQuery query;
    query.prepare("update student set name = ? where id = ?");
    query.addBindValue(name);
    query.addBindValue(studentId);
    return query.exec();
}

void CustomQueryModel::refresh()
{
    setQuery("select * from student");
    setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    setHeaderData(1, Qt::Horizontal, QObject::tr("name"));
}

Qt::ItemFlags CustomQueryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags falgs = QSqlQueryModel::flags(index);
    if(index.column() == 1){
        falgs |= Qt::ItemIsEditable;
    }
    return falgs;
}

QVariant CustomQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
/*    if (role == Qt::TextColorRole && index.column() == 0)
        return qVariantFromValue(QColor(Qt::red));*/ //第一个属性的字体颜色为红色
    return value;
}

bool CustomQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // if (index.column() < 1 || index.column() > 2)
    //     return false;
    // QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
    // int id = data(primaryKeyIndex).toInt(); //获取id号
    // clear();
    // bool ok;
    // if (index.column() == 1) //第二个属性可更改
    //     ok = setName(id, value.toString());
    // refresh();
    // return ok;
}
