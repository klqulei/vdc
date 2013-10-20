#ifndef __V_MEDIADB_H_
#define __V_MEDIADB_H_
#include "vpoco.hpp"

#include "debug.hpp"
#include "datasink.hpp"

using namespace UtilityLib;

namespace MediaDB
{

class RecoderSink : BasicSink
{
public:
    void handleSink(SinkNotification* pNf)
    {
        std::cout<<"Recoder: "<<pNf->name()<<std::endl;
        Debug::DebugPrint("ID %d\n", pNf->nId);
        pNf->release();
    }
};


class MediaDB
{
public:
    void init(std::string &strPath);
    void addRepository(std::string &strPath, s32 nSize);
    void removeRepository(std::string &strPath);
	
public:
    BOOL startRecord(s32 nId);
    void stopRecord(s32 nId);

};

inline BOOL MediaDB::startRecord(s32 nId)
{
    return TRUE;
}

}










#endif /* _VDC_UTILITY_H_ */
