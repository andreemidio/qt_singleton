//WHOLE .cpp
#include "../include/Handler.hpp"
#include <cstdlib>
#include <QCoreApplication>
#include <iostream>

QSharedPointer<Database> Database::singleton;


Handler::Handler(QString driver, QString hostname, QString database, int port, QString user, QString password,
				 QString notification)
{
	this->MyDB = QSqlDatabase::addDatabase(driver);

	MyDB.setHostName(hostname);
	MyDB.setPort(port);
	MyDB.setDatabaseName(database);
	MyDB.setUserName(user);
	MyDB.setPassword(password);

	MyDB.open();

	if (MyDB.isOpen())
	{
		std::cout << "Connected to DB!" << std::endl;

		connect(this->MyDB.driver(), SIGNAL(notification(const QString &, QSqlDriver::NotificationSource, const QVariant
													&)), this,
				SLOT(slot_DBNotification_Recieved_NotifiAndPayload(const QString &, QSqlDriver::NotificationSource, const QVariant &)));

		MyDB.driver()->subscribeToNotification(notification);


	} else
		qDebug() << "NOT connected to DB!";
}

Handler::~Handler()
{

}

void Handler::slot_DBNotification_Recieved_NotifiAndPayload(const QString &name,
															QSqlDriver::NotificationSource source,
															const QVariant &payload)
{
	std::cout << name.toStdString() << " " << payload.toString().toStdString() << std::endl;
}


QSharedPointer<Database> Database::get_instance()
{
	return Database::singleton;
}

QSharedPointer<Database>
Database::get_instance(QString driver, QString hostname, QString database, int port, QString user, QString password,
					   QString notification)
{

	if (Database::singleton.isNull())
	{
		Database::singleton = QSharedPointer<Database>(
				new Database(driver, hostname, database, port, user, password, notification));
	}

	return Database::singleton;
}

Database::Database(QString driver, QString hostname, QString database, int port, QString user, QString password,
				   QString notification)
		: handler(driver, hostname, database, port, user, password, notification)
{

}

Database::~Database()
{

}

int main(int argc, char **argv)
{
	QCoreApplication app(argc, argv);

	Database::get_instance("QPSQL", "localhost", "postgres", 5432, "postgres", "postgres", "servicos");


	return app.exec();
}
