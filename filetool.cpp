#include "filetool.h"
#include <QFile>

FileTool::FileTool(QObject *parent) : QObject(parent)
{

}


void FileTool::saveConnections(QString file,Setting setting[],int num){
    if(setting != NULL){
        QFile f(file);
        if(f.open(QIODevice::WriteOnly)){
            for(int i=0;i < num;i++){
                if(setting->protocol == Protocol_SSH){

                }else if(setting->protocol == Protocol_Serial){
                    Setting<SerialSetting> *SerialSetting = setting[0];

                    f.write((char*)SerialSetting,sizeof(Setting<SerialSetting>));
                }
            }
            f.close();
        }
    }
}
