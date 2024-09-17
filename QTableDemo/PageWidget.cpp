#include "PageWidget.h"
#include "ui_PageWidget.h"



PageWidget::PageWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageWidget)
{
    ui->setupUi(this);

    initPagingUi();
    initPagingStyle();
}

PageWidget::~PageWidget()
{
    delete ui;
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


}

void PageWidget::initPagingStyle()
{
    //设置跳转页输入限制
    seek_page_led_->setValidator(new QIntValidator(1, 1, this));
    //设置表格样式
    // paging_control_table_->setHorizontalHeader(new PageingSortHeader(Qt::Horizontal, paging_control_table_));
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
    QSettings database_ini_file(":/file/database.ini", QSettings::IniFormat);
    database_ini_file.beginGroup("Database");
    QString current_thread_id = "";
    /* 获取当前线程id的数据库连接,如果已经连接则不再添加数据库连接 */
    {
        QSqlDatabase paging_control_db;
        current_thread_id = QString::number((qint64)QThread::currentThreadId());
        if (QSqlDatabase::contains(current_thread_id)) {
            paging_control_db = QSqlDatabase::database(current_thread_id);
        }
        else {
            /* 使用当前线程ID作为连接名 */
            paging_control_db = QSqlDatabase::addDatabase(database_ini_file.value("type").toString().toUpper(), current_thread_id);
            paging_control_db.setHostName(database_ini_file.value("ip").toString());
            paging_control_db.setPort(database_ini_file.value("port").toInt());
            paging_control_db.setDatabaseName(database_ini_file.value("db_name").toString());
            paging_control_db.setUserName(database_ini_file.value("user").toString());
            paging_control_db.setPassword(database_ini_file.value("password").toString());
        }

        if (!paging_control_db.open()) {
            emit execErrorSignal(paging_control_db.lastError().text());
        }
        else {
            QSqlQuery exec_query(paging_control_db);
            if (!exec_query.exec(_exec_sql)) {
                emit execErrorSignal(paging_control_db.lastError().text());
                return;
            }


            paging_control_db.close();
        }
    }

    QSqlDatabase::removeDatabase(current_thread_id);
    if (total_table_row_ == 0) {

        return;
    }

}
