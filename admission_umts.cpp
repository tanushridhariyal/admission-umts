#include "admission_umts.h"
#include "QtGui"


class SimpleItem : public QGraphicsItem
 {
 public:
     QRectF boundingRect() const
     {
         qreal penWidth = 1;
         return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                       20 + penWidth, 20 + penWidth);
     }

     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget)
     {
         painter->drawRoundedRect(-10, -10, 40, 20, 10, 5);
     }
 };

admission_umts::admission_umts(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	QGraphicsScene *scene;
	scene = new QGraphicsScene(this);
	SimpleItem *item;
	item = new SimpleItem();
	item->setVisible(true);
	scene->addItem(item);
	ui.graphResults->setScene(scene);
}

admission_umts::~admission_umts()
{

}
