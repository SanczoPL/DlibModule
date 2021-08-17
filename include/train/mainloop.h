#ifndef TRAIN_MAINLOOP_H
#define TRAIN_MAINLOOP_H

#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QThread>
#include <QTimer>

#include <deque>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "data.h"
#include "foldermanagement.h"

#include "dlibcase.h"

struct configsName
{
	QString dataset;
	QString preprocess;
	QString postprocess;
};
struct configs
{
	QJsonObject dataset;
	QJsonArray preprocess;
	QJsonArray postprocess;
	QJsonObject config;
};


class MainLoop : public QObject {
	Q_OBJECT

public:
	explicit MainLoop(QJsonObject m_config);

private:
	void readConfig(QString configName, QJsonObject& jObject, QString graphType);
	void readConfig(QString configName, QJsonArray& jArray, QString graphType);
	void loadConfigs(QJsonObject configPaths, QString graphType);

private:
	void createConfig(QJsonObject const& a_config);
	void createStartupThreads();
	void createThreads();
	void configure(QJsonObject const& a_config);

private:	
	bool m_firstTime{};
	bool m_dataMemoryLoaded{};
	bool m_dlibConfigured{};

	std::deque<configs> m_dlibConfigs;
	struct configs m_dlibConfig;
	struct configsName m_dlibConfigName;

private:
	QTimer* m_timer;

private:
	QJsonObject m_config;
	QJsonObject m_dataset;
	QJsonObject m_preprocess;
	QJsonObject m_configPaths;

	QJsonArray m_graphTypes;
	QJsonArray m_dronTypes;

private:
	QThread* m_dataMemoryThread;
	DataMemory* m_dataMemory;
	
	QThread* m_fileLoggerTrainThread;
	FileLogger *m_fileLoggerTrain;

	QThread* m_fileLoggerTestThread;
	FileLogger *m_fileLoggerTest;

	QThread* m_fileLoggerJSONThread;
	FileLogger *m_fileLoggerJSON;

	DlibCase* m_dlib;

signals:

public slots:
	void onUpdate();
	void onMemoryLoaded();
	void onDlibConfigured();
	void onNextConfig();

private:
	QString m_graphType{};
	QString m_boundsType{};
	QString m_logsFolder{};
	QString m_videoLogsFolder{};
	QString m_split{};
	bool m_validTask{};
	
};

#endif // TRAIN_MAINLOOP_H
