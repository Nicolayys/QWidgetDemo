#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QToolButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QIntValidator>
#include <QListWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QPainter>
#include <QComboBox>
namespace Ui {
class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageWidget(QWidget *parent = nullptr);
    ~PageWidget();


    /* 设置标题的名称翻译
        _head_trs			翻译字段集合， key = 原始名称，value = 翻译名称
    */
    void translateHeadNames(QMap<QString, QString> & _head_trs);
    /* 执行查询语句 */
    void exec(const QString & _exec_sql);
    /* 获取最后执行的SQL */
    QString lastExecSql() const;
    /* 为某一列设置代理样式 */
    void setDelegateForColumn(int _column, QAbstractItemDelegate * _delegate);
    /* 添加一列数据 */
    void appendColumns(const QString & _head_name, QVariantList _values);
    /* 插入一列数据 */
    void insertColumns(int _column, const QString & _head_name, QVariantList _values);
    /* 获取表的总列数 */
    int columnCount();
    /* 获取表格总行数 */
    int rowCount();
    /* 获取表格页内行数 */
    int rowPageCount();
    /* 设置每页显示行数值 */
    void setPageRows(QList<int> _page_rows);
    /* 设置是否按行选择 */
    void setEnableSelectRow(bool _enable);
    /* 设置是否可以多行选择 */
    void setEnableMultiSelect(bool _enable);
    /* 获取指定单元格的数据（page内） */
    QVariant cellValue(int _row, int _column);
    /* 获取指定单元格的数据（page内） */
    QString convertVariant(QVariant & _variant);
    /* 获取指定单元格的Item（page内） */
    QStandardItem* cellItem(int _row, int _column);
    /* 获取当前页数 */
    int currentPage();
    /* 设置列的宽度 */
    void setColumnWidth(int _column, int _width);
    /* 获取指定列的表头名称 */
    QString headName(int _column, bool _is_translate);
    /* 查询选择的对应列的全部数据 */
    QVariantList selectValues(int _column);
    /* 查询选择的对应列的全部数据, 二维数组 */
    QList<QVariantList> selectValues();
signals:
    /* 执行错误信号 */
    void execErrorSignal(const QString & _error);
    /* 查询结果总条数据 */
    void execResultTotalSignal(int _query_count);
    /* 鼠标点击Cell信号  */
    void mouseClickCellSignal(const QModelIndex & _index);
private slots:
    /* 跳转到前一页 */
    void seekPreviousPageSlot();
    /* 跳转到下一页 */
    void seekNextPageSlot();
    /* 跳转到指定页 */
    void seekOnePageSlot();
    /* 切换每页显示行数 */
    void switchPageRowSlot(int _index);
    /* 设置显示和隐藏列 */
    void hideColumnSlot();
    /* 隐藏当前页面中的空列 */
    void hideEmptyColumnSlot();
private:
    /* 初始化分页控件界面布局 */
    void initPagingUi();
    /* 设置界面样式 */
    void initPagingStyle();
    /* SQL执行工作 */
    void execSqlWork(const QString & _exec_sql);
private:
    // Ui::PageWidget *ui;

    /* 当前使用的SQL语句 */
    QString																							exec_sql_string_;
    /* 数据表控件 */
    QTableView *																					paging_control_table_;
    /* 控制列的显示隐藏 */
    QToolButton*																					hide_col_btn_;
    /* 控制显示隐藏空数据列 */
    QToolButton*																					hide_empty_btn_;
    /* 跳转到上页 */
    QToolButton*																					previous_page_btn_;
    /* 跳转到下页 */
    QToolButton*																					next_page_btn_;
    /* 跳转 */
    QToolButton*																					seek_page_btn_;
    /* 数据总数显示 */
    QLabel*																							total_count_label_;
    /* 当前页数 */
    QLabel*																							current_page_label_;
    /* 每页显示的行数选择 */
    QComboBox*																					select_page_max_row_cb_;
    /* 跳转到某页输入框 */
    QLineEdit*																						seek_page_led_;
    /* 表头翻译 key = 原始名称   value = 翻译名称 */
    QMap<QString, QString>																	translate_headers_;
    /* SQL 执行等待监视线程 */
    QFutureWatcher<void>*																	exec_sql_watcher_;
    /* 数据Model缓存 */
    QFutureWatcher<void>*																	model_cache_watcher_;
    /* 记录当前的数据视图模型 key = 字段名称，value = 此字段对应的一列数据 */
    QMap<QString, QVariantList>															record_querys_;
    /* 数据Model缓存 key = 缓存的页数，value = 缓存的model*/

    // QMap<int, PageingSortModel*>														cache_models_;

    /* 总页数 */
    int																									total_table_page_;
    /* 每页显示的行数 */
    int																									page_row_;
    /* 当前所在页数 */
    int																									current_page_index_;
    /* 总数据条数 */
    int																									total_table_row_;
};

#endif // PAGEWIDGET_H
