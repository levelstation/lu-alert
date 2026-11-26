"""Reversible Wio-LU receive-channel identity hook; no radio or profile changes."""
from pathlib import Path
import sys

ROOT=Path(__file__).resolve().parents[1]
TARGET=ROOT/'upstream/examples/companion_radio/ui-new/UITask.cpp'
OLD='  quickTx.receive(channel_details.name,"GROUP (unverified)",text,millis());'
NEW='''#if defined(LU_ALERT_RX_CHANNELS)
  quickTx.receive(channel_details.name,"GROUP (unverified)",text,millis(),{},messageMesh.receivedChannelIdentity(channel_details));
#else
'''+OLD+'''
#endif'''

def main():
    mode=sys.argv[1] if len(sys.argv)==2 else ''
    if mode not in ('strip','apply'):raise SystemExit('Choose strip or apply')
    if not TARGET.exists():
        if mode=='strip':return
        raise SystemExit('Prepared UI missing')
    original=TARGET.read_text();source=original
    if mode=='strip':
        if NEW in source:
            assert source.count(NEW)==1,'Ambiguous channel identity hook'
            source=source.replace(NEW,OLD,1)
    elif NEW not in source:
        assert source.count(OLD)==1,'Channel receive hook conflict; no write performed'
        source=source.replace(OLD,NEW,1)
    if source!=original:TARGET.write_text(source)

if __name__=='__main__':main()
