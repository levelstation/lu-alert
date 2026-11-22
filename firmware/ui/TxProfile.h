#pragma once
// LU-Alert profile: explicit menu labels only. No keys or persisted channel configuration.
namespace meshis {
struct TxPreset {const char* label;const char* text;bool botConfirmed;};
constexpr unsigned txChannelCount(){return 8;}
inline const char* txChannel(unsigned n){static const char* const names[]={"#Public","#Test","#LU-Alert","#trafic","#luxembourg","#saarloorlux","#trier","#bot"};return n<txChannelCount()?names[n]:"";}
inline const char* txMenu(unsigned n){static const char* const names[]={"PUBLIC // QUICK TX","TEST // QUICK TX","NOSRV // LU-ALERT","TRAFIC // QUICK TX","LUXEMBOURG // TX","SAARLOORLUX // TX","TRIER // QUICK TX","BOT // QUICK TX"};return n<txChannelCount()?names[n]:"QUICK TX";}
inline unsigned txCount(unsigned n){const unsigned counts[]={4,3,4,8,4,4,4,1};return n<txChannelCount()?counts[n]:0;}
inline bool txAwaitsReply(unsigned n){return n==2 || n==3 || n==7;}
inline TxPreset txPreset(unsigned channel,unsigned item){
 static const TxPreset publicItems[]={{"Hallo","Hallo",false},{"Moin","Moin",false},{"Wie geht’s?","Wie geht’s?",false},{"ACK 75","ACK 75",false}};
 static const TxPreset testItems[]={{"Ping","Ping",false},{"Test","Test",false},{"Hop","Hop",false}};
 static const TxPreset alertItems[]={{"Meteo","meteo",true},{"Hochwasser","hochwasser",false},{"RAD","",false},{"Warnungen","",false}};
 static const TxPreset trafficItems[]={{"Traffic","traffic",false},{"Info","info",false},{"A1","A1",false},{"A3","A3",false},{"A4","A4",false},{"A6","A6",false},{"A7","A7",false},{"A13","A13",false}};
 if(item>=txCount(channel))return {"Unavailable","",false};
 if(channel==7)return {"Befehl folgt","",false};
 return channel==1?testItems[item]:channel==2?alertItems[item]:channel==3?trafficItems[item]:publicItems[item];
}
}
