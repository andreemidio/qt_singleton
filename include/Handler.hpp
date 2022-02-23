// WHOLE .h
#include <QDebug>
#include <QObject>
#include <QString>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QVariant>
#include <QSqlDriverPlugin>
#include <qsqldriver.h>
#include <QSharedPointer>

class Handler : public QObject
{
	Q_OBJECT
	private slots:

	  void
	  slot_DBNotification_Recieved_NotifiAndPayload(const QString &name, QSqlDriver::NotificationSource source,
													const QVariant &payload);

	public:
	  explicit Handler(QString driver, QString hostname, QString database, int port, QString user,
					   QString password, QString notification);

	  ~Handler();

	private:
	  QSqlDatabase MyDB;

};

class Database
{

	private:

	  Database(QString driver, QString hostname, QString database, int port, QString user, QString password,
			   QString notification);

	  ~Database();

	  static QSharedPointer<Database> singleton;

	  Handler handler;

	public:
	  static QSharedPointer<Database> get_instance();

	  static QSharedPointer<Database>
	  get_instance(QString driver, QString hostname, QString database, int port, QString user, QString password,
				   QString notification);

};

