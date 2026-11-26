#include <array>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <CommonCrypto/CommonDigest.h>
#include "FramebufferDisplay.h"
#include "QuickTx.h"
#define MAX_GROUP_CHANNELS 12
#define MAX_ANON_CONTACTS 0
#define MAX_TEXT_LEN 160
namespace mesh {struct Utils {static void sha256(uint8_t* out,size_t count,const uint8_t* source,int bytes){uint8_t digest[CC_SHA256_DIGEST_LENGTH];CC_SHA256(source,bytes,digest);memcpy(out,digest,count);}};}
struct Group {uint8_t secret[32]={};};
struct ChannelDetails {char name[32]={};Group channel;};
struct ContactInfo {char name[32]={};};
struct FakeMesh {
 ChannelDetails channels[MAX_GROUP_CHANNELS];unsigned sends=0;char sent[161]={},node[32]="DEMO NODE";
 bool getChannel(int index,ChannelDetails& channel){if(index<0||index>=MAX_GROUP_CHANNELS||!channels[index].name[0])return false;channel=channels[index];return true;}
 unsigned getNumContacts(){return 0;}bool getContactByIdx(unsigned,ContactInfo&){return false;}
 const char* getNodeName(){return node;}
 bool sendGroupMessage(uint32_t,Group&,const char*,const char* text,size_t size){++sends;memcpy(sent,text,size+1);return true;}
} the_mesh;
struct Clock {uint32_t getCurrentTime(){return 1782864000;}} rtc_clock;
#include "MeshCoreMessages.h"
static uint32_t now=1000;
uint32_t millis(){return now;}
static meshis::QuickTx quickTx;
static MeshCoreMessages messageMesh;
// The include is extracted from the actual prepared UITask.cpp, not a copied test hook.
void ingest(ChannelDetails& channel_details,const char* text){
#include "rx-channel-callback.inc"
}
namespace {
unsigned checks=0;
void check(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
struct Frame:FramebufferDisplay {std::array<uint8_t,1024> pixels{};Frame():FramebufferDisplay(nullptr){bindFramebuffer(pixels.data());}bool isOn()override{return true;}void turnOn()override{}void turnOff()override{}void endFrame()override{}};
void reset(){
 meshis::keyLock()={};meshis::textMarquee().reset();meshis::textReadSession().reset();quickTx={};messageMesh={};the_mesh={};
 for(unsigned index=0;index<meshis::txChannelCount();++index){snprintf(the_mesh.channels[index].name,32,"%s",meshis::txChannel(index));the_mesh.channels[index].channel.secret[0]=index+1;}
}
void receive(unsigned index,const char* text="SIMULATION: local sample only"){++now;ingest(the_mesh.channels[index],text);}
void render(Frame& frame){meshis::textMarquee().setNow(now);frame.startFrame();quickTx.render(frame,messageMesh);check(frame.textOverflows()==0,"128x64 channel/inbox rendering stays inside framebuffer");}
void profile(){
 const char* expected[]={"#public","#test","#lu-alert","#trafic","#luxembourg","#hammradio","#bot","#emergency","#saarland","#trier"};
 check(meshis::txChannelCount()==10,"All ten requested Wio channels present");
 for(unsigned i=0;i<10;++i){check(!strcmp(expected[i],meshis::txChannel(i)),"Requested Wio channel order and spelling");check(meshis::txCount(i)>0,"Every channel has explicit preset state");}
 check(!*meshis::txChannel(10)&&meshis::txCount(10)==0,"Channel bounds are checked");
 check(!*meshis::txPreset(meshis::txBotChannel(),0).text,"Unknown bot command remains unsendable");
}
void chooser(){
 reset();Frame frame;quickTx.open();quickTx.input(0xb6,messageMesh,now);quickTx.input(13,messageMesh,now);
 check(quickTx.page()==meshis::QuickTx::Page::Inbox&&quickTx.inboxFilter()==-1,"Existing Live RX entry starts in All view");
 quickTx.input(13,messageMesh,now);check(quickTx.page()==meshis::QuickTx::Page::RxChannels,"Physical ENTER opens RX chooser");
 for(unsigned option=0;option<=10;++option){render(frame);quickTx.input(13,messageMesh,now);check(quickTx.inboxFilter()==int(option)-1,"ENTER selects each of All plus ten channels");quickTx.input(13,messageMesh,now);quickTx.input(0xb6,messageMesh,now);}
 quickTx.input(27,messageMesh,now);check(quickTx.page()==meshis::QuickTx::Page::Inbox&&quickTx.inboxFilter()==9,"Back from chooser preserves applied filter");
 check(the_mesh.sends==0,"Opening, browsing and selecting RX filters never transmits");
}
void independentReception(){
 reset();Frame frame;
 for(unsigned selected=0;selected<10;++selected){
  quickTx={};quickTx.selectInboxFilter(selected,messageMesh);receive(selected);
  check(quickTx.inboxVisibleCount()==1,"Every configured channel receives into its matching view");
  receive((selected+1)%10);check(quickTx.count()==2&&quickTx.inboxVisibleCount()==1,"Another channel still receives without replacing selected view");
  render(frame);quickTx.selectInboxFilter(-1,messageMesh);check(quickTx.inboxVisibleCount()==2,"All view retains messages from other channels");
 }
 quickTx={};quickTx.selectInboxFilter(-1,messageMesh);for(unsigned i=0;i<14;++i)receive(i%10);
 check(quickTx.count()==8&&quickTx.inboxVisibleCount()==8,"Global RX RAM ring remains bounded to eight messages");
 unsigned filtered=0;for(unsigned i=0;i<10;++i){quickTx.selectInboxFilter(i,messageMesh);filtered+=quickTx.inboxVisibleCount();render(frame);}
 check(filtered==8,"Stored messages are assigned to exactly one configured channel");
 snprintf(the_mesh.channels[11].name,32,"#other");the_mesh.channels[11].channel.secret[0]=100;receive(11);
 quickTx.selectInboxFilter(-1,messageMesh);check(!strcmp(quickTx.preview(0)->channel,"#other")&&quickTx.inboxVisibleCount()==8,"Other configured channels remain accessible in All");
 check(the_mesh.sends==0,"RX collection and filtering have no RF send side effect");
}
void configurationChanges(){
 reset();Frame frame;quickTx.selectInboxFilter(0,messageMesh);receive(0,"SIMULATION: old channel-key message");
 const auto original=the_mesh.channels[0];the_mesh.channels[0].channel.secret[0]=91;
 quickTx.refreshInboxFilter(messageMesh);check(!quickTx.inboxFilterAvailable()&&quickTx.inboxVisibleCount()==0,"Changed key invalidates the selected channel view");receive(0,"SIMULATION: new channel-key message");
 quickTx.selectInboxFilter(0,messageMesh);check(quickTx.inboxFilterAvailable()&&quickTx.inboxVisibleCount()==1,"Reselecting the new key excludes previous-key messages");
 quickTx.selectInboxFilter(-1,messageMesh);check(quickTx.inboxVisibleCount()==2,"Historical received records stay accessible in All without relabeling");
 the_mesh.channels[11]=the_mesh.channels[0];quickTx.selectInboxFilter(0,messageMesh);check(!quickTx.inboxFilterAvailable()&&quickTx.inboxVisibleCount()==0,"Duplicate names are unavailable rather than guessed");render(frame);
 the_mesh.channels[11]={};the_mesh.channels[0]={};quickTx.selectInboxFilter(0,messageMesh);check(!quickTx.inboxFilterAvailable(),"Missing channels are not silently configured");render(frame);
 the_mesh.channels[11]=original;quickTx.selectInboxFilter(0,messageMesh);check(quickTx.inboxFilterAvailable()&&quickTx.inboxVisibleCount()==1,"A known channel moved to another slot retains identity");
 check(the_mesh.sends==0,"Channel reconfiguration tests never queue a message");
}
void textAndLock(){
 reset();Frame frame;quickTx.selectInboxFilter(0,messageMesh);receive(0,"SIMULATION: This deliberately long public test message is wider than the OLED so its text can keep moving while messages arrive on another configured channel.");
 render(frame);const auto start=frame.pixels;now+=1700;render(frame);check(frame.pixels!=start,"Filtered long message keeps real marquee rendering");
 receive(1);render(frame);check(frame.pixels!=start&&quickTx.inboxVisibleCount()==1,"Unrelated RX does not restart selected long-text reading");
 meshis::keyLock().menuPress(now);now+=100;meshis::keyLock().menuPress(now);now+=100;meshis::keyLock().menuPress(now);meshis::keyLock().poll(now+450);
 check(meshis::keyLock().blocks(),"Keylock is active for RX control guard test");
 quickTx.selectInboxFilter(1,messageMesh);quickTx.input(13,messageMesh,now);
 check(quickTx.inboxFilter()==0&&quickTx.page()==meshis::QuickTx::Page::Inbox,"Locked filter/ENTER cannot alter the UI");
 const unsigned before=quickTx.count();receive(1);check(quickTx.count()==before+1,"Other-channel reception continues during keylock");
 check(the_mesh.sends==0,"Locked RX/filter actions never queue transmissions");meshis::keyLock()={};
}
void sending(){
 reset();
 for(unsigned channel=0;channel<10;++channel){
  quickTx={};quickTx.open();quickTx.input(13,messageMesh,now);for(unsigned i=0;i<channel;++i)quickTx.input(0xb6,messageMesh,now);quickTx.input(13,messageMesh,now);quickTx.input(13,messageMesh,now);
  const unsigned before=the_mesh.sends;
  if(channel==meshis::txBotChannel()){check(quickTx.page()==meshis::QuickTx::Page::UnknownCommand,"No invented bot message");quickTx.input(13,messageMesh,now);quickTx.poll(messageMesh,now);check(the_mesh.sends==before,"Unknown bot command cannot send");continue;}
  check(quickTx.page()==meshis::QuickTx::Page::Confirm&&the_mesh.sends==before,"All channel presets require explicit send confirmation");
  quickTx.input(13,messageMesh,now);check(the_mesh.sends==before,"Requested send waits for queue processing");quickTx.poll(messageMesh,now);check(the_mesh.sends==before+1,"Each configured channel sends once after confirmation");
  quickTx.input(13,messageMesh,now);check(quickTx.page()==meshis::QuickTx::Page::Inbox&&quickTx.inboxFilter()==int(channel),"Accepted TX can open the same channel Inbox");
  quickTx.input(13,messageMesh,now);quickTx.input(13,messageMesh,now);quickTx.poll(messageMesh,now);check(the_mesh.sends==before+1,"Inbox/channel chooser ENTER cannot resend");
 }
 quickTx={};quickTx.open();quickTx.input(13,messageMesh,now);quickTx.input(13,messageMesh,now);quickTx.input(13,messageMesh,now);const unsigned before=the_mesh.sends;the_mesh.channels[0].channel.secret[0]++;
 quickTx.input(13,messageMesh,now);quickTx.poll(messageMesh,now);check(quickTx.page()==meshis::QuickTx::Page::Failed&&the_mesh.sends==before,"Key changes after preview block stale prepared TX");
}
}
int main(){try{profile();chooser();independentReception();configurationChanges();textAndLock();sending();printf("PASS: %u Wio RX-channel checks; QuickTx RAM=%zu bytes; no identity/key values exported\n",checks,sizeof(meshis::QuickTx));return 0;}catch(const std::exception& error){fprintf(stderr,"FAIL: %s\n",error.what());return 1;}}
