#include "Simulator.h"
#include "QuickTx.h"
#include <cstdio>
#include <cstring>
#include <stdexcept>
namespace {
unsigned checks=0;
void check(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
int messages(){for(int p=0;p<Simulator::pageCount();++p)if(!strcmp(Simulator::pageName(p),"Messages"))return p;throw std::runtime_error("Missing Messages page");}
void prepare(Simulator& sim,unsigned channel=0){sim.goToPage(messages());sim.key(13);sim.key(13);for(unsigned n=0;n<channel;++n)sim.key(0xb6);sim.key(13);sim.key(13);check(sim.quickPage()==int(meshis::QuickTx::Page::Confirm),"Actual Simulator reaches explicit TX preview");check(sim.simulatedSends()==0,"Preview never sends");}
void send(Simulator& sim){sim.key(13);check(sim.simulatedSends()==0,"Confirmation queues rather than sending inline");sim.advance(1);}
void failure(Simulator& sim,const char* message){send(sim);check(sim.quickPage()==int(meshis::QuickTx::Page::Failed)&&sim.simulatedSends()==0,message);sim.advance(30001);check(sim.simulatedSends()==0,"Rejected configuration never retries automatically");}
}
int main(){try{
 {Simulator sim;prepare(sim);sim.setSimChannelEpoch(0,1);failure(sim,"Actual simulator adapter rejects channel-key identity changes after preview");}
 {Simulator sim;prepare(sim);sim.setSimChannel(1,"#PUBLIC");failure(sim,"Actual simulator adapter rejects a duplicate canonical name added after preview");}
 {Simulator sim;prepare(sim);sim.setSimChannel(0,"#renamed");failure(sim,"Actual simulator adapter rejects changed names after preview");}
 {Simulator sim;prepare(sim);sim.setSimChannel(0,"");failure(sim,"Actual simulator adapter rejects a removed channel after preview");}
 {Simulator sim;prepare(sim);sim.setSimChannelEpoch(1,1);send(sim);check(sim.quickPage()==int(meshis::QuickTx::Page::Accepted)&&sim.simulatedSends()==1,"Another channel-key change does not invalidate the selected target");check(sim.lastSimulatedChannel()=="#public"&&sim.lastSimulatedText()=="Hallo","Successful simulator send retains exact selected channel and preset text");sim.key(13);sim.advance(1);check(sim.simulatedSends()==1,"One accepted send remains one send");}
 {Simulator sim;prepare(sim,9);sim.setSimChannel(1000000,"#wrong");sim.setSimChannelEpoch(1000000,99);send(sim);check(sim.quickPage()==int(meshis::QuickTx::Page::Accepted)&&sim.simulatedSends()==1,"Out-of-range simulator configuration controls cannot alter a prepared valid slot");}
 printf("PASS: %u actual-Simulator TX configuration/revalidation checks; fake adapter only, no device access\n",checks);return 0;
}catch(const std::exception& error){fprintf(stderr,"FAIL: %s\n",error.what());return 1;}}
