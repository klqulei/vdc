
#ifndef __VSC_FACTORY_H_
#define __VSC_FACTORY_H_
#include "confdb.hpp"
#include "device.hpp"


typedef std::list<LPDevice> DeviceList;
typedef std::list<DeviceParam> DeviceParamList;
typedef std::map<int, LPDevice> DeviceMap;
typedef std::map<int, DeviceParam> DeviceParamMap;
#define FACTORY_DEVICE_ID_MAX 2048

class Factory
{
public:
    Factory();
    ~Factory();
public:
    BOOL Init();
    s32 InitAddDevice(DeviceParam & pParam, u32 nIndex);

public:
    /* UI can use this for display device tree */
    BOOL GetDeviceParamMap(DeviceParamMap &pMap);

    s32 AddDevice(DeviceParam & pParam);
    s32 GetDeviceParamById(DeviceParam & pParam, s32 nIndex);
    BOOL DelDevice(s32 nIndex);

public:
    BOOL StartDevice(s32 nIndex);
    BOOL StopDevice(s32 nIndex);

public:
    NotificationQueue * GetRawDataQueue(s32 nIndex);
    BOOL ReleaseRawDataQueue(s32 nIndex, NotificationQueue * pQueue);
    NotificationQueue * GetDataQueue(s32 nIndex);
    BOOL GetDataQueue(s32 nIndex, NotificationQueue * pQueue);
    BOOL RegDeleteCallback(s32 nIndex, DeviceDeleteCallbackFunctionPtr pCallback, void * pParam);
    BOOL UnRegDeleteCallback(s32 nIndex, void * pParam);
    BOOL GetDeviceOnline(s32 nIndex);

public:
    void Lock(){m_Lock.lock();}
    void UnLock(){m_Lock.unlock();}

public:
    s32 GetDeviceID(void);
    BOOL ReleaseDeviceID(s32 nID);
    BOOL LockDeviceID(s32 nID);
public:


private:
    DeviceMap m_DeviceMap;
    DeviceParamMap m_DeviceParamMap;
    fast_mutex m_Lock;

private:
    s8 m_strDeviceMap[FACTORY_DEVICE_ID_MAX];
    ConfDB m_Conf;
};

typedef Factory* LPFactory;

inline void OnvifLog(char * str)
{
    VDC_DEBUG( "%s\n", str);
    return;
}


inline Factory::Factory()
{

}

inline Factory::~Factory()
{

}

inline BOOL Factory::Init()
{

    s32 i = 0;

    for (i = 0; i < FACTORY_DEVICE_ID_MAX; i ++)
    {
        m_strDeviceMap[i] = 'n';
    }

    astring strPath = "C:\\VSCloud\\VSCloudNode\\config";

    m_Conf.Open(strPath);

    VSCConfData sysData;
    m_Conf.GetSysData(sysData);
    for (s32 i = 1; i < CONF_MAP_MAX; i ++)
    {
        if (sysData.data.conf.DeviceMap[i] != CONF_MAP_INVALID_MIN )
        {
            VDC_DEBUG( "%s Init %d\n",__FUNCTION__, i);
            VSCDeviceData Data;
            m_Conf.GetDeviceData(i, Data);
            DeviceParam mParam(Data);
            LockDeviceID(Data.data.conf.nId);
            InitAddDevice(mParam, Data.data.conf.nId);
            VDC_DEBUG( "%s Id %d\n",__FUNCTION__, Data.data.conf.nId);
        }
    }


	return TRUE;
}

inline BOOL Factory::GetDeviceParamMap(DeviceParamMap &pMap)
{
    pMap = m_DeviceParamMap;

    return TRUE;
}

inline s32 Factory::InitAddDevice(DeviceParam & pParam, u32 nIndex)
{
    m_DeviceMap[nIndex] = new Device(pParam);
    m_DeviceParamMap[nIndex] = pParam;

    return TRUE;
}

inline NotificationQueue * Factory::GetRawDataQueue(s32 nIndex)
{
    NotificationQueue * pQueue = NULL;
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        pQueue = m_DeviceMap[nIndex]->GetRawDataQueue();
    }

    UnLock();

    return pQueue;
}

inline BOOL Factory::ReleaseRawDataQueue(s32 nIndex, NotificationQueue * pQueue)
{
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        m_DeviceMap[nIndex]->ReleaseRawDataQueue(pQueue);
    }

    UnLock();

    return TRUE;
}
inline NotificationQueue * Factory::GetDataQueue(s32 nIndex)
{
    return NULL;
}

inline BOOL Factory::GetDataQueue(s32 nIndex, NotificationQueue * pQueue)
{
    return TRUE;
}

inline BOOL Factory::RegDeleteCallback(s32 nIndex, DeviceDeleteCallbackFunctionPtr pCallback,
        void * pParam)
{
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        UnLock();
        return m_DeviceMap[nIndex]->RegDeleteCallback(pCallback, pParam);
    }

    UnLock();

    return TRUE;
}

inline BOOL Factory::GetDeviceOnline(s32 nIndex)
{
    BOOL online = FALSE;
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        online =  m_DeviceMap[nIndex]->GetDeviceOnline();
    }

    UnLock();

    return online;
}

inline BOOL Factory::UnRegDeleteCallback(s32 nIndex, void * pParam)
{
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        UnLock();
        return m_DeviceMap[nIndex]->UnRegDeleteCallback(pParam);
    }

    UnLock();

    return TRUE;
}


inline BOOL Factory::StartDevice(s32 nIndex)
{
    Lock();
    if (m_DeviceMap[nIndex] != NULL)
    {
        m_DeviceMap[nIndex]->Start();
    }
    UnLock();

	return TRUE;
}
inline BOOL Factory::StopDevice(s32 nIndex)
{
    Lock();

    UnLock();

	return TRUE;
}

inline s32 Factory::AddDevice(DeviceParam & pParam)
{
    s32 nId = GetDeviceID();

    VDC_DEBUG( "%s GetDeviceID %d\n",__FUNCTION__, nId);

    Lock();
    pParam.m_Conf.data.conf.nId = nId;
    m_DeviceMap[nId] = new Device(pParam);
    m_DeviceParamMap[nId] = pParam;

    m_Conf.AddDevice(pParam.m_Conf, nId);
    UnLock();
    return nId;
}

inline BOOL Factory::DelDevice(s32 nIndex)
{
    VDC_DEBUG( "%s DelDevice %d\n",__FUNCTION__, nIndex);
    if (nIndex <=0 || nIndex >= FACTORY_DEVICE_ID_MAX)
    {
        return FALSE;
    }

    //TODO check is this device can be delete or not
    Lock();
    VDC_DEBUG( "%s Cleanup Begin\n",__FUNCTION__);
    m_DeviceMap[nIndex]->Cleanup();
    VDC_DEBUG( "%s Cleanup End\n",__FUNCTION__);
    delete m_DeviceMap[nIndex];
    m_DeviceParamMap.erase(nIndex);
    m_Conf.DelDevice(nIndex);
    ReleaseDeviceID(nIndex);
    UnLock();
    return TRUE;
}

inline s32 Factory::GetDeviceParamById(DeviceParam & pParam, s32 nIndex)
{
    VDC_DEBUG( "%s GetDeviceParamById %d\n",__FUNCTION__, nIndex);
    if (nIndex <=0 || nIndex >= FACTORY_DEVICE_ID_MAX)
    {
        return FALSE;
    }

    Lock();
    pParam = m_DeviceParamMap[nIndex];
    UnLock();

    return nIndex;
}

inline s32 Factory::GetDeviceID(void)
{
    s32 id  = -1;
    s32 i = -1;

    Lock();
    for (i = 1; i < FACTORY_DEVICE_ID_MAX; i ++)
    {
        if (m_strDeviceMap[i] == 'n')
        {
            id = i;
            m_strDeviceMap[i] = 'y';
            UnLock();
            return id;
        }
    }

    UnLock();
    return id;
}

inline BOOL Factory::ReleaseDeviceID(s32 nID)
{
    if (nID <=0 || nID >= FACTORY_DEVICE_ID_MAX)
    {
        return FALSE;
    }
    Lock();
    m_strDeviceMap[nID] = 'n';
    UnLock();

    return TRUE;
}

inline BOOL Factory::LockDeviceID(s32 nID)
{
    if (nID <=0 || nID >= FACTORY_DEVICE_ID_MAX)
    {
        return FALSE;
    }
    Lock();
    m_strDeviceMap[nID] = 'y';
    UnLock();

    return TRUE;
}



#endif // __VSC_FACTORY_H_
