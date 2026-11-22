#pragma once
// LU-Alert profile: explicit menu labels only. No keys or persisted channel configuration.
namespace meshis {
enum class TxArgument:unsigned char { None, Place, Station, Page };
struct TxPreset {const char* label;const char* text;bool botConfirmed;TxArgument argument;
 constexpr TxPreset(const char* l="",const char* t="",bool confirmed=false,TxArgument arg=TxArgument::None):label(l),text(t),botConfirmed(confirmed),argument(arg){}
};
constexpr unsigned txChannelCount(){return 8;}
inline const char* txChannel(unsigned n){static const char* const names[]={"#Public","#Test","#LU-Alert","#trafic","#luxembourg","#saarloorlux","#trier","#bot"};return n<txChannelCount()?names[n]:"";}
inline const char* txMenu(unsigned n){static const char* const names[]={"PUBLIC // QUICK TX","TEST // QUICK TX","NOSRV // LU-ALERT","TRAFIC // QUICK TX","LUXEMBOURG // TX","SAARLOORLUX // TX","TRIER // QUICK TX","BOT // QUICK TX"};return n<txChannelCount()?names[n]:"QUICK TX";}
inline unsigned txCount(unsigned n){
#if defined(MESHIS_HELTEC_PRG) || defined(LU_ALERT_BOT_CATALOG)
 const unsigned counts[]={4,3,30,24,4,4,4,1};
#else
 const unsigned counts[]={4,3,4,8,4,4,4,1};
#endif
 return n<txChannelCount()?counts[n]:0;
}
inline bool txAwaitsReply(unsigned n){return n==2 || n==3 || n==7;}
inline TxPreset txPreset(unsigned channel,unsigned item){
 static const TxPreset publicItems[]={{"Hallo","Hallo",false},{"Moin","Moin",false},{"Wie geht’s?","Wie geht’s?",false},{"ACK 75","ACK 75",false}};
 static const TxPreset testItems[]={{"Ping","Ping",false},{"Test","Test",false},{"Hop","Hop",false}};
#if defined(MESHIS_HELTEC_PRG) || defined(LU_ALERT_BOT_CATALOG)
 // Canonical commands supplied by the user. Actual bot responses remain UNTESTED.
 static const TxPreset alertItems[]={{"Meteo","meteo",true},{"Hilfe","help",false},{"RAD / Cattenom","rad",false},{"Pegel-Menue","pegel",false},{"Pegel Vianden","pegel vianden",false},{"Pegel nach Ort","pegel",false,TxArgument::Place},{"Pegel Stationsnr.","pegel",false,TxArgument::Station},{"Pegel alle","pegel alle",false},{"Pegel alle: Seite","pegel alle",false,TxArgument::Page},{"Pegel Mosel","pegel mosel",false},{"Hochwasser","hochwasser",false},{"Erdbeben","erdbeben",false},{"Erdbeben aktuell","erdbeben aktuell",false},{"Erdbeben letzte","erdbeben letzte",false},{"Verkehr","trafic",false},{"Verkehr A1","trafic A1",false},{"Verkehr A3","trafic A3",false},{"Verkehr A4","trafic A4",false},{"Verkehr A6","trafic A6",false},{"Verkehr A7","trafic A7",false},{"Verkehr A13","trafic A13",false},{"Unfaelle","unfall",false},{"Pannen","panne",false},{"Stau","stau",false},{"Baustellen","baustelle",false},{"Wartung","wartung",false},{"Wartung aktuell","wartung aktuell",false},{"Wartungsarbeiten","wartungsarbeiten",false},{"Stoerungen","stoerung",false},{"Hindernisse","hindernis",false}};
 static const TxPreset trafficItems[]={{"Hilfe","help",false},{"Verkehr aktuell","trafic",false},{"Verkehr: Seite","trafic",false,TxArgument::Page},{"A1","trafic A1",false},{"A3","trafic A3",false},{"A4","trafic A4",false},{"A6","trafic A6",false},{"A7","trafic A7",false},{"A13","trafic A13",false},{"A1: Seite","trafic A1",false,TxArgument::Page},{"A3: Seite","trafic A3",false,TxArgument::Page},{"A4: Seite","trafic A4",false,TxArgument::Page},{"A6: Seite","trafic A6",false,TxArgument::Page},{"A7: Seite","trafic A7",false,TxArgument::Page},{"A13: Seite","trafic A13",false,TxArgument::Page},{"Unfaelle","unfall",false},{"Pannen","panne",false},{"Stau","stau",false},{"Baustellen","baustelle",false},{"Wartung","wartung",false},{"Wartung aktuell","wartung aktuell",false},{"Wartungsarbeiten","wartungsarbeiten",false},{"Stoerungen","stoerung",false},{"Hindernisse","hindernis",false}};
#else
 static const TxPreset alertItems[]={{"Meteo","meteo",true},{"Hochwasser","hochwasser",false},{"RAD","",false},{"Warnungen","",false}};
 static const TxPreset trafficItems[]={{"Traffic","traffic",false},{"Info","info",false},{"A1","A1",false},{"A3","A3",false},{"A4","A4",false},{"A6","A6",false},{"A7","A7",false},{"A13","A13",false}};
#endif
 if(item>=txCount(channel))return {"Unavailable","",false};
 if(channel==7)return {"Befehl folgt","",false};
 return channel==1?testItems[item]:channel==2?alertItems[item]:channel==3?trafficItems[item]:publicItems[item];
}
}
