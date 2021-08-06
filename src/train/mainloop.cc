#include "train/mainloop.h"

#define DEBUG
#define DEBUG_CONFIG

constexpr auto GENERAL{ "General" };
constexpr auto DLIB{ "Dlib" };
constexpr auto GRAPH_TYPE{ "GraphType" };
constexpr auto BOUNDS_TYPE{ "BoundsType" };
constexpr auto DRON_TYPE{ "DronType" };
constexpr auto GRAPH_TYPES{ "GraphTypes" };
constexpr auto BOUNDS_TYPES{ "BoundsTypes" };
constexpr auto DRON_TYPES{ "DronTypes" };
constexpr auto THREADSMAX{"ThreadsMax"};
constexpr auto CONFIG{ "Config" };
constexpr auto NAME{ "Name" };
constexpr auto STANDARD_DEVIATION{ "StandardDeviation" };
constexpr auto DRON_NOISE{ "Noise" };
constexpr auto DRON_RAND_SEED{ "RandSeed" };
constexpr auto DRON_CONTRAST{ "Contrast" };

constexpr auto LOGS_FOLDER{ "LogsFolder" };
constexpr auto CONFIG_LINUX{ "ConfigLinux" };
constexpr auto CONFIG_WIN{ "ConfigWin" };

constexpr auto DRON_NOISE_START{ "DronNoiseStart" };
constexpr auto DRON_NOISE_STOP{ "DronNoiseStop" };
constexpr auto DRON_NOISE_DELTA{ "DronNoiseDelta" };
constexpr auto DRON_CONTRAST_START{ "DronContrastStart" };
constexpr auto DRON_CONTRAST_STOP{ "DronContrastStop" };
constexpr auto DRON_CONTRAST_DELTA{ "DronContrastDelta" };



void MainLoop::readConfig(QString configName, QJsonObject& jObject, QString graphType)
{
	#ifdef DEBUG_CONFIG
    Logger->debug("MainLoop::readConfig() configName:{}", configName.toStdString());
	#endif
	ConfigReader* configReader = new ConfigReader();
	QJsonObject _jObject{};
	if (!configReader->readConfig(configName, _jObject))
	{
		Logger->error("MainLoop::readConfig() open {} failed", configName.toStdString());
	}
	jObject = _jObject[graphType].toObject();
	
	delete configReader;
}

void MainLoop::readConfig(QString configName, QJsonArray& jArray, QString graphType)
{
	#ifdef DEBUG_CONFIG
    Logger->debug("MainLoop::readConfig() configName:{}", configName.toStdString());
	#endif
	ConfigReader* configReader = new ConfigReader();
	QJsonObject _jObject{};
	if (!configReader->readConfig(configName, _jObject))
	{
		Logger->error("MainLoop::readConfig() open {} failed", configName.toStdString());
	}
	jArray = _jObject[graphType].toArray();
	delete configReader;
}

void MainLoop::loadConfigs(QJsonObject configPaths, QString graphType)
{
	#ifdef DEBUG_CONFIG
    Logger->debug("MainLoop::loadConfigs() with specific graph type:{}", graphType.toStdString());
	#endif

	m_dlibConfigName.dataset = configPaths["Dataset"].toString();
	m_dlibConfigName.preprocess = configPaths["Preprocess"].toString();
	m_dlibConfigName.postprocess = configPaths["Postprocess"].toString();

	MainLoop::readConfig(m_dlibConfigName.dataset, m_dlibConfig.dataset, graphType);
	MainLoop::readConfig(m_dlibConfigName.preprocess, m_dlibConfig.preprocess, graphType);
	MainLoop::readConfig(m_dlibConfigName.postprocess, m_dlibConfig.postprocess, graphType);
	#ifdef DEBUG_CONFIG
		qDebug() << "MainLoop::loadConfigs() m_dlibConfig.dataset:" << m_dlibConfig.dataset;
	#endif
}

void MainLoop::createConfig(QJsonObject const& a_config)
{
	QTime now = QTime::currentTime();
    int randNumber = now.msecsSinceStartOfDay();

	QString logsFolder = m_logsFolder;
	if(checkAndCreateFolder(logsFolder))
	{
		Logger->error("checkAndCreateFolder cant create:{}", logsFolder.toStdString());
	}
	for (int graf = 0 ; graf < m_graphTypes.size() ; graf++)
	{
		QString logsFolderWithGraph = logsFolder +  m_graphTypes[graf].toString() + m_split; 

		if(checkAndCreateFolder(logsFolderWithGraph))
		{
			Logger->error("checkAndCreateFolder cant create:{}", logsFolderWithGraph.toStdString());
		}
		for (int dron = 0 ; dron < m_dronTypes.size() ; dron++)
		{
			QString logsFolderWithGraphAndDron = logsFolderWithGraph + m_dronTypes[dron].toString() + m_split; 
			if(checkAndCreateFolder(logsFolderWithGraphAndDron))
			{
				Logger->error("checkAndCreateFolder cant create:{}", logsFolderWithGraphAndDron.toStdString());
			}
			// Add graph type to config:
			QJsonObject obj = m_config[DLIB].toObject();
			obj[GRAPH_TYPE] = m_graphTypes[graf].toString();
			obj[DRON_TYPE] = m_dronTypes[dron].toString();
			m_config[DLIB] = obj;
			m_dlibConfig.config = m_config;

			// Load rest of configs:
			MainLoop::loadConfigs(m_configPaths, m_graphTypes[graf].toString());

			// Add noise:
			for (int i = 0; i < 101; i += 5)
			{
				for(int j = 0 ; j < m_dlibConfig.preprocess.size() ; j++)
				{
					if(m_dlibConfig.preprocess[j].toObject()[CONFIG].toObject()[NAME].toString() == "AddMultipleDron")
					{
						randNumber++;
						QJsonArray arrObj = m_dlibConfig.preprocess;
						QJsonObject obj = arrObj[j].toObject();
						QJsonObject config = obj[CONFIG].toObject();
						config[DRON_RAND_SEED] = randNumber;
						config[DRON_TYPE] = m_dronTypes[dron].toString();

						config[DRON_NOISE_START] = double(i);
						config[DRON_NOISE_STOP] = double(i + 0.1);
						config[DRON_NOISE_DELTA] = double(0.01);

						config[DRON_CONTRAST_START] = 100.00;
						config[DRON_CONTRAST_STOP] = 100.1;
						config[DRON_CONTRAST_DELTA] = 0.01;

						obj[CONFIG] = config;
						arrObj[j] = obj;
						m_dlibConfig.preprocess = arrObj;
						#ifdef DEBUG_CONFIG
						qDebug() << "config[DRON_NOISE_START]:" << config[DRON_NOISE_START];
						qDebug() << "config[DRON_NOISE_STOP]:" << config[DRON_NOISE_STOP];
						qDebug() << "config[DRON_NOISE_DELTA]:" << config[DRON_NOISE_DELTA];
						qDebug() << "m_dlibConfig.preprocess[j].toObject()[CONFIG].toObject():" << m_dlibConfig.preprocess[j].toObject()[CONFIG].toObject();
						#endif
					}
				}
				m_dlibConfigs.push_back(m_dlibConfig);
			}
		}
	}
	#ifdef DEBUG_CONFIG
	Logger->debug("MainLoop::createConfig() createConfig() m_dlibConfigs.size():{}", m_dlibConfigs.size());
	#endif
}

void MainLoop::createStartupThreads()
{
    Logger->trace("MainLoop::createStartupThreads()");
	m_dataMemoryThread = new QThread();
	m_dataMemory = new DataMemory();
	connect(m_dataMemory, &DataMemory::memoryLoaded, this, &MainLoop::onMemoryLoaded);
	m_dataMemory->moveToThread(m_dataMemoryThread);
	connect(m_dataMemoryThread, &QThread::finished, m_dataMemory, &QObject::deleteLater);
	m_dataMemoryThread->start();

	m_dlib = new DlibCase(m_dataMemory);

	m_fileLoggerThread = new QThread();
	m_fileLogger = new FileLogger() ;
	m_fileLogger->moveToThread(m_fileLoggerThread);
	connect(m_fileLoggerThread, &QThread::finished, m_fileLogger, &QObject::deleteLater);
	m_fileLoggerThread->start();

	m_fileLoggerJSONThread = new QThread();
	m_fileLoggerJSON = new FileLogger();
	m_fileLoggerJSON->moveToThread(m_fileLoggerJSONThread);
	connect(m_fileLoggerJSONThread, &QThread::finished, m_fileLoggerJSON, &QObject::deleteLater);
	m_fileLoggerJSONThread->start();

	m_timer = new QTimer(this);
	m_timer->start(1000);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(onUpdate()));
	connect(m_dlib, &DlibCase::newConfig, this, &MainLoop::onNextConfig);
	connect(m_dlib, &DlibCase::dlibConfigured, this, &MainLoop::onDlibConfigured);

	connect(m_dlib, &DlibCase::configureLogger, m_fileLogger, &FileLogger::configure);
	connect(m_dlib, &DlibCase::configureLoggerJSON, m_fileLoggerJSON, &FileLogger::configure);

	connect(m_dlib, &DlibCase::appendToFileLogger, m_fileLogger, &FileLogger::appendFileLogger);
	connect(m_dlib, &DlibCase::logJsonBest, m_fileLoggerJSON, &FileLogger::logJsonBest);
}

void MainLoop::createThreads()
{ }

MainLoop::MainLoop(QJsonObject a_config)
	:m_config{ a_config },
	m_dataMemoryLoaded{false},
	m_dlibConfigured{ false },
	m_validTask{false},
	m_firstTime{true},
	m_graphType{ a_config[DLIB].toObject()[GRAPH_TYPE].toString()},
	m_logsFolder("logs/"),
	m_split("/")
{
	#ifdef DEBUG
		qDebug() << "MainLoop::MainLoop() a_config:" << a_config;
		Logger->debug("MainLoop::MainLoop() m_graphType:{}", m_graphType.toStdString());
		Logger->debug("MainLoop::MainLoop() m_boundsType:{}", m_boundsType.toStdString());
	#endif
	
	#ifdef _WIN32
	m_split = "\\";
	#endif // _WIN32
	#ifdef __linux__
	m_split = "/";
	#endif // _UNIX

	MainLoop::createStartupThreads();
	MainLoop::configure(a_config);
}

void MainLoop::configure(QJsonObject const& a_config)
{
	#ifdef DEBUG_CONFIG
		Logger->debug("MainLoop::configure()");
	#endif
    #ifdef _WIN32
    m_configPaths = a_config[CONFIG_WIN].toObject();
    #endif // _WIN32
    #ifdef __linux__
    m_configPaths = a_config[CONFIG_LINUX].toObject();
    #endif // __linux__
	#ifdef DEBUG_CONFIG
		qDebug() << "MainLoop::configure(a_config) a_config:" << a_config;
	#endif

	m_logsFolder = m_configPaths[LOGS_FOLDER].toString();
	m_graphTypes = a_config[DLIB].toObject()[GRAPH_TYPES].toArray();
	m_dronTypes = a_config[DLIB].toObject()[DRON_TYPES].toArray();
}

void MainLoop::onUpdate()
{
	Logger->trace("MainLoop::onUpdate() m_validTask:{}", m_validTask);
	if (m_firstTime)
	{	
        Logger->trace("MainLoop::onUpdate() firstTime");
		m_firstTime = false;
		createConfig(m_config);
		m_validTask = true;
		if (m_dlibConfigs.size() > 0)
		{
			#ifdef DEBUG_CONFIG
			Logger->debug("m_dataMemory->configure:");
			qDebug() << "m_dataMemory->configure: config:"<< m_dlibConfigs[0].dataset;
			#endif
			m_dataMemory->configure(m_dlibConfigs[0].dataset);
		}
    }

    if (m_validTask)
	{
        Logger->trace("MainLoop::onUpdate() m_validTask m_dlibConfigs.size():{}",m_dlibConfigs.size());
		if (m_dlibConfigs.size() > 0)
		{
			m_validTask = false;
			m_dataMemory->preprocess(m_dlibConfigs[0].preprocess);
			m_dlib->configure(m_dlibConfigs[0].config, m_dlibConfigs[0].preprocess, m_dlibConfigs[0].dataset, m_dlibConfigs[0].postprocess);
		}
	}

    if (m_dataMemoryLoaded && m_dlibConfigured)
	{
		Logger->trace("MainLoop: emit process to dlib");
		m_dlib->process();
		
	}
}

void MainLoop::onNextConfig()
{
    Logger->debug("MainLoop::onNextConfig() configs left:{}", m_dlibConfigs.size());
	m_dataMemoryLoaded = false;
	m_dlibConfigured = false;
	if (m_dlibConfigs.size() > 0)
	{
		#ifdef DEBUG_CONFIG
		Logger->debug("MainLoop::onNextConfig() pop config");
		#endif
		m_dlibConfigs.pop_front();
		m_validTask = true;
	}

	if (m_dlibConfigs.size() == 0)
	{
		#ifdef DEBUG_CONFIG
		Logger->debug("MainLoop::onNextConfig() no config left, create new configs:");
		#endif
		createConfig(m_config);
	}
}

void MainLoop::onDlibConfigured()
{
	Logger->debug("MainLoop::onDlibConfigured()");
	m_dlibConfigured = true;
}

void MainLoop::onMemoryLoaded()
{
	Logger->debug("MainLoop::onMemoryLoaded()");
	m_dataMemoryLoaded = true;
}