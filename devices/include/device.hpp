

#ifndef __VSC_DEVICE_H_
#define __VSC_DEVICE_H_

#define NOMINMAX
#include "ffmpeg_impl.hpp"
#include "tcmalloc.h"
#include "utility.hpp"
#include "conf.hpp"
#include "datasink.hpp"
#include "devicemanagement.h"
#include "media_management/profiles.h"
#include "media_management/streamuri.h"
#include "device_management/capabilities.h"
#include "mediamanagement.h"


using namespace UtilityLib;
using namespace std;
using namespace ONVIF;

class CvCapture_FFMPEG;
typedef std::list<NotificationQueue*> CmdQueueList;
//typedef UtilityListIterator<NotificationQueue> CmdQueueIterator;

typedef void (__cdecl * DeviceDeleteCallbackFunctionPtr)(u32 nId, void * pParam);
typedef std::map<void *, DeviceDeleteCallbackFunctionPtr> DeviceDeleteCallbackMap;

class DeviceParam
{
public:
    DeviceParam();
#if 0
    DeviceParam(u32 nType, u32 nSubType, astring strParam);
    DeviceParam(u32 nType, u32 nSubType, astring strParam, astring strName);
#endif
    DeviceParam(const DeviceParam &pParam);
    DeviceParam(VSCDeviceData &pData);
    ~DeviceParam();
    DeviceParam & operator=(const DeviceParam &pParam)
    {
        memset(&m_Conf, 0, sizeof(m_Conf));

        memcpy(&m_Conf, &(pParam.m_Conf), sizeof(m_Conf));
        m_strUrl = pParam.m_strUrl;
        return *this;
    }

public:
    void UpdateUrl();
    void UpdateUrlOnvif();

public:
    VSCDeviceData m_Conf;
    astring m_strUrl;
};

class Device
{
public:
    Device();
    Device(const DeviceParam &pParam);
    ~Device();
	
public:
    BOOL Start();
    BOOL Stop();
	
public:
    static void Run(void * pParam);
    void Run1();

public:
    void Lock(){m_Lock.lock();}
    void UnLock(){m_Lock.unlock();}
    void LockTime(){m_DataTimeLock.lock();}
    void UnLockTime(){m_DataTimeLock.unlock();}

public:
    NotificationQueue * GetRawDataQueue();
    BOOL ReleaseRawDataQueue(NotificationQueue * pQueue);
    NotificationQueue * GetDataQueue();
    BOOL GetDataQueue(NotificationQueue * pQueue);
    BOOL RegDeleteCallback(DeviceDeleteCallbackFunctionPtr pCallback, void * pParam);
    BOOL UnRegDeleteCallback(void * pParam);
    BOOL Cleanup();
    BOOL GetDeviceOnline()
    {
        BOOL online = FALSE;
        LockTime();
        s32 currentTime = time(NULL);
        VDC_DEBUG( "%s GetDeviceOnline  cur %d  last %d \n",__FUNCTION__, 
            currentTime, m_nLastGetDataTime);
        if (currentTime - m_nLastGetDataTime < 10)//TODO xsmart
        {
            online = TRUE;
        }
        UnLockTime();
        return online;
    }

public:
    BOOL WriteFrame(unsigned char* dataRGB, int step, int width, int height, int cn,
            unsigned char* data, int size);

private:
    CmdQueueList m_RawDataList;
    CmdQueueList m_DataList;
    BOOL m_bStarted;
    DeviceDeleteCallbackMap m_DeleteMap;

private:
    s32 m_nDeviceType;
    s32 m_nDeviceSubType;
    DeviceParam m_param;
    tthread::thread *m_pThread;
    CvCapture_FFMPEG* m_Cap;
    fast_mutex m_Lock;
    s32 m_nLastGetDataTime;
    fast_mutex m_DataTimeLock;
};

typedef DeviceParam* LPDeviceParam;
typedef Device* LPDevice;

inline DeviceParam::DeviceParam()
{
    //static int CameraNum = 0;
    memset(&m_Conf, 0, sizeof(m_Conf));
    m_Conf.data.conf.nId = 0;
    m_Conf.data.conf.nType = VSC_DEVICE_CAM;
    m_Conf.data.conf.nSubType = VSC_SUB_DEVICE_FILE;

    sprintf(m_Conf.data.conf.Name, "CAMERA %d", 1);
    //strcpy(m_Conf.data.conf.Name, "CAMERA ");

    strcpy(m_Conf.data.conf.IP, "192.168.0.1");
    strcpy(m_Conf.data.conf.Port, "80");
    strcpy(m_Conf.data.conf.User, "admin");
    strcpy(m_Conf.data.conf.Password, "admin");

    strcpy(m_Conf.data.conf.RtspLocation, "/");
    strcpy(m_Conf.data.conf.FileLocation, "camera.avi");
    strcpy(m_Conf.data.conf.OnvifAddress, "/onvif/device_service");
    strcpy(m_Conf.data.conf.CameraIndex, "1");

    m_Conf.data.conf.UseProfileToken = 0;
    strcpy(m_Conf.data.conf.OnvifProfileToken, "quality_h264");

}

inline DeviceParam::DeviceParam(VSCDeviceData &pData)
{
    memset(&m_Conf, 0, sizeof(m_Conf));

    memcpy(&m_Conf, &(pData), sizeof(m_Conf));
    //UpdateUrl();
}

inline std::string Replace(std::string &str, const char *string_to_replace, const char *new_string)
{
  // Find the first string to replace
  int index = str.find(string_to_replace);
  // while there is one
  while(index != std::string::npos)
  {
    // Replace it
    str.replace(index, strlen(string_to_replace), new_string);
    // Find the next one
    index = str.find(string_to_replace, index + strlen(new_string));
  }
  return str;
}

inline void DeviceParam::UpdateUrlOnvif()
{
    astring IP = m_Conf.data.conf.IP;
    astring Port = m_Conf.data.conf.Port;
    astring User = m_Conf.data.conf.User;
    astring Password = m_Conf.data.conf.Password;
    astring OnvifAddress = m_Conf.data.conf.OnvifAddress;

    astring OnvifDeviceService = "http://" + IP + ":" + Port + "/" + OnvifAddress;
	astring url = "rtsp://" + IP + ":" + "554" + "/";

    DeviceManagement *pDm = new DeviceManagement(OnvifDeviceService.c_str(), 
                            User.c_str(), Password.c_str());
    
    if (pDm  == NULL)
    {
        VDC_DEBUG( "%s new DeviceManagement error \n",__FUNCTION__);
        return;
    }

    Capabilities * pMediaCap = pDm->getCapabilitiesMedia();
    if (pMediaCap == NULL)
    {
        VDC_DEBUG( "%s getCapabilitiesMedia error \n",__FUNCTION__);
        delete pDm;
        return;
    }

    MediaManagement *pMedia = new MediaManagement(pMediaCap->mediaXAddr(), 
                                User.c_str(), Password.c_str());
    if (pMedia == NULL)
    {
        VDC_DEBUG( "%s new MediaManagement error \n",__FUNCTION__);
        delete pDm;
        delete pMediaCap;
        return;
    }

    Profiles *pProfileS = pMedia->getProfiles();
    if (pProfileS == NULL)
    {
        VDC_DEBUG( "%s new getProfiles error \n",__FUNCTION__);
        delete pDm;
        delete pMediaCap;
        delete pMedia;
        return;
    }
    if (pProfileS->m_toKenPro.size() > 0)
    {
        VDC_DEBUG( "%s m_toKenPro size %d \n",__FUNCTION__, pProfileS->m_toKenPro.size());
		QString strToken;
		if (m_Conf.data.conf.UseProfileToken == 1)
		{
			strToken = m_Conf.data.conf.OnvifProfileToken;
		}else
		{
			strToken = pProfileS->m_toKenPro[0];
		}
		StreamUri *pUri = pMedia->getStreamUri(strToken);
		if (pUri)
		{
			url = pUri->uri().toStdString();
			delete pUri;
		}
        
    }
	std::string strUrl = url;
	
	/* rtsp://admin:12345@192.168.1.1:554/Streaming/Channels/1\
	?transportmode=unicast&profile=Profile_1 */
	astring urlWithUser = "rtsp://" + User + ":" + Password + "@";
	Replace(strUrl, "rtsp://", urlWithUser.c_str());

	m_strUrl = strUrl;

    delete pDm;
    delete pMediaCap;
    delete pMedia;
    delete pProfileS;
    return;
}

inline void DeviceParam::UpdateUrl()
{
    //TODO RTSP ONVIF call onvif sdk to get a Stream URL
    if (m_Conf.data.conf.nSubType == VSC_SUB_DEVICE_FILE)
    {
        m_strUrl = m_Conf.data.conf.FileLocation;
    }

    if (m_Conf.data.conf.nSubType == VSC_SUB_DEVICE_RTSP)
    {
        char url[512];
        sprintf(url, "rtsp://%s:%s@%s:%s%s",
                m_Conf.data.conf.User,
                m_Conf.data.conf.Password,
                m_Conf.data.conf.IP,
                m_Conf.data.conf.Port, m_Conf.data.conf.RtspLocation);
        m_strUrl = url;

    }

    if (m_Conf.data.conf.nSubType == VSC_SUB_DEVICE_ONVIF)
    {
        UpdateUrlOnvif();
    }
    VDC_DEBUG( "%s url %s\n",__FUNCTION__, m_strUrl.c_str());
}

#if 0
inline DeviceParam::DeviceParam(u32 nType, u32 nSubType, astring strParam)
{
    memset(&m_Conf, 0, sizeof(m_Conf));

    m_Conf.data.conf.nType = (VSCDeviceType)nType;
    m_Conf.data.conf.nSubType = (VSCDeviceSubType)nSubType;
    strcpy(m_Conf.data.conf.Param,strParam.c_str());
    strcpy(m_Conf.data.conf.Name,strParam.c_str());
    m_strUrl = m_Conf.data.conf.Param;
}

inline DeviceParam::DeviceParam(u32 nType, u32 nSubType, astring strParam, astring strName)
{
    memset(&m_Conf, 0, sizeof(m_Conf));

    m_Conf.data.conf.nType = (VSCDeviceType)nType;
    m_Conf.data.conf.nSubType = (VSCDeviceSubType)nSubType;
    strcpy(m_Conf.data.conf.Param, strParam.c_str());
    strcpy(m_Conf.data.conf.Name, strName.c_str());
    m_strUrl = m_Conf.data.conf.Param;
}
#endif

inline DeviceParam::DeviceParam(const DeviceParam &pParam)
{
    memset(&m_Conf, 0, sizeof(m_Conf));

    memcpy(&m_Conf, &(pParam.m_Conf), sizeof(m_Conf));
    //UpdateUrl();
}


inline DeviceParam::~DeviceParam()
{

}

inline Device::Device()
:m_bStarted(FALSE), m_nLastGetDataTime(0)
{
}

inline Device::Device(const DeviceParam &pParam)
:m_bStarted(FALSE), m_param(pParam), m_nLastGetDataTime(0)
{
    m_param.UpdateUrl();
    VDC_DEBUG( "%s url %s\n",__FUNCTION__, m_param.m_strUrl.c_str());
}

inline Device::~Device()
{

}

inline NotificationQueue * Device::GetRawDataQueue()
{
    NotificationQueue *pQueue = NULL;

    Lock();
    pQueue = new NotificationQueue;

    m_RawDataList.push_back(pQueue);
    UnLock();

    return pQueue;

}
inline BOOL Device::ReleaseRawDataQueue(NotificationQueue * pQueue)
{
    if (pQueue == NULL)
    {
        return FALSE;
    }

    Lock();
#if 0
    for (;;)
    {
        Notification::Ptr pNf(pQueue->waitDequeueNotification());
        if (pNf)
        {
            SinkNotification::Ptr pWorkNf = pNf.cast<SinkNotification>();
            if (pWorkNf)
            {
                {
                	//FastMutex::ScopedLock lock(_mutex);
                	//std::cout << _name << " got work notification " << pWorkNf->data() << std::endl;
                }
                //Thread::sleep(rnd.next(200));
            }
        }
    else break;
    }
#endif
    m_RawDataList.remove(pQueue);

    delete pQueue;

    UnLock();
    return TRUE;
}

inline BOOL Device::RegDeleteCallback(DeviceDeleteCallbackFunctionPtr pCallback, void * pParam)
{
    m_DeleteMap[pParam] = pCallback;
    return TRUE;
}

inline BOOL Device::UnRegDeleteCallback(void * pParam)
{
    m_DeleteMap.erase(pParam);
    return TRUE;
}

inline NotificationQueue * Device::GetDataQueue()
{
    return NULL;
}
inline BOOL Device::GetDataQueue(NotificationQueue * pQueue)
{
    return TRUE;
}

inline BOOL Device::Start()
{
    if (m_bStarted == FALSE)
    {
        m_pThread = new thread(Device::Run, (void *)this);
        m_bStarted = TRUE;
    }

    return TRUE;
}
inline BOOL Device::Stop()
{
    if (m_bStarted == true)
    {
        VDC_DEBUG( "%s Stop Begin\n", __FUNCTION__);
        m_bStarted = false;
        m_pThread->join();
        delete m_pThread;
        VDC_DEBUG( "%s Stop End\n", __FUNCTION__);
    }

    return TRUE;
}

inline BOOL Device::Cleanup()
{

    VDC_DEBUG( "%s Callback begin\n",__FUNCTION__);
    /* Call the callbacks for this device */
    DeviceDeleteCallbackMap::iterator it = m_DeleteMap.begin();

    for(; it!=m_DeleteMap.end(); ++it)
    {
        void *pParam = (*it).first;
        DeviceDeleteCallbackFunctionPtr pFunc = (*it).second;
        if (pFunc)
        {
            pFunc(m_param.m_Conf.data.conf.nId, pParam);
        }
    }
    VDC_DEBUG( "%s Callback end\n",__FUNCTION__);

    Stop();

    //release all the NotificationQueue

    return TRUE;
}

inline void Device::Run(void * pParam)
{
    int dummy = errno;
    LPDevice pThread = (LPDevice)pParam;

    if (pThread)
    {
        pThread->Run1();
    }
}

inline void Device::Run1()
{
    unsigned char *pData = NULL;
    unsigned char *pDataOrg = NULL;
    int size = 0;
    int step = 0;
    int width = 0;
    int height = 0;
    int cn = 0;
    void *pixels;
    int pitch;



    m_Cap = new CvCapture_FFMPEG;
    VDC_DEBUG( "%s url %s\n",__FUNCTION__, m_param.m_strUrl.c_str());
    m_Cap->open(m_param.m_strUrl.c_str());

    while(m_bStarted == TRUE)
    {
        Lock();

        if (m_RawDataList.size() <= 0)
        {
            //if m_RawDataList is NULL, don't get the raw data
        }
        //TODO get pDataOrg data format
		
        if (m_Cap->grabFrame(&pData, &step, &width, &height, &cn, &pDataOrg, &size)
                == false)
        {
            m_Cap->close();
            delete m_Cap;
            Sleep(1000);
            m_Cap = new CvCapture_FFMPEG;
            m_Cap->open(m_param.m_strUrl.c_str());
            //m_Cap->open("cwbcvideo.avi");
            UnLock();
            continue;
        }
		//VDC_DEBUG( "%s size %d \n",__FUNCTION__, size);
        if (size != 0)
        {
            LockTime();
            m_nLastGetDataTime = time(NULL);
            UnLockTime();
            WriteFrame(pData, step, width, height, cn, pDataOrg, size);
        }

        pixels = NULL;
        UnLock();

        if (m_param.m_Conf.data.conf.nSubType == VSC_SUB_DEVICE_FILE)
        {
            Sleep(40);
        }

    }
    m_Cap->close();
    delete m_Cap;
}

inline BOOL Device::WriteFrame(unsigned char* dataRGB, int step, int width, int height, int cn,
        unsigned char* data, int size)
{
    unsigned char * pMallocData = NULL;
    unsigned char * pMallocDataOrg = NULL;
    int dummy = errno;
    SinkNotification *pSink;


    if (dataRGB != NULL)
    {
        CmdQueueList::iterator it = m_RawDataList.begin();

        while(it != m_RawDataList.end())
        {
            NotificationQueue *pRawQueue = *it;
            if (pRawQueue->size()  < 10)
            {
                //pMallocData = (unsigned char *)tc_malloc(width * height * cn);
                pMallocData = (unsigned char *)malloc(width * height * cn);
                if(pMallocData == NULL)
                {
                    VDC_DEBUG( "%s malloc error !id %d\n",__FUNCTION__, m_param.m_Conf.data.conf.nId);
                    break;
                }
                memcpy(pMallocData, dataRGB, width * height * cn);
                pSink = new SinkNotification;
                pSink->cmd.type = CMN_CMD_TYPE_DATA;
                pSink->cmd.data_type = CMN_DATA_TYPE_RGB24;
                pSink->cmd.w = width;
                pSink->cmd.h = height;
                pSink->cmd.cn = cn;
                pSink->cmd.size = width * height * cn;
                pSink->cmd.data = pMallocData;
            
                pRawQueue->enqueueNotification(pSink);
            }  
            else
            {
                VDC_DEBUG( "%s put error size > 10!\n",__FUNCTION__);
            }

            it ++;
        }

    }

    if (data != NULL)
    {

    }

    return TRUE;
}




#endif // __VSC_DEVICE_H_
